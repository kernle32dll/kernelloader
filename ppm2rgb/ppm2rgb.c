/* Copyright (c) 2007 Mega Man */
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_BUFFER 4096

int readBehindWhitespaceAndNoComment(FILE *fin)
{
	char c;

	do {
		do {
			if (feof(fin)) {
				fprintf(stderr, "Error: file has incomplete header.\n");
				return -1;
			}
			c = fgetc(fin);
		} while(isspace(c));

		/* Jump over comments. */
		if (c == '#') {
			do {
				if (feof(fin)) {
					fprintf(stderr, "Error: file has incomplete header.\n");
					return -1;
				}
				c = fgetc(fin);
			} while(c != '\n');
		}
	} while (isspace(c));

	return c;
}

const char *readIntoBuffer(FILE *fin)
{
	static char buffer[MAX_BUFFER];
	char c;
	int i;

	c = readBehindWhitespaceAndNoComment(fin);
	if (c < 0) {
		return NULL;
	}

	i = 0;
	buffer[i] = c;
	i++;
	while (!feof(fin)) {
		c = fgetc(fin);
		if (isspace(c)) {
			break;
		}
		buffer[i] = c;
		i++;
		if (i >= MAX_BUFFER) {
			fprintf(stderr, "Line to long.\n");
			return NULL;
		}
	}
	buffer[i] = 0;
	return buffer;
}

int main(int argc, char *argv[])
{
	FILE *fin = NULL;
	FILE *fout = NULL;
	const char *buffer;
	int width;
	int height;
	int depth;
	int size;
	char *copyBuffer = NULL;
	char *prefix = NULL;
	int i;

	if (argc != 5) {
		fprintf(stderr, "Usage:\n");
		fprintf(stderr, "%s [ppm input file] [raw outputfile] [output header file] [Macro prefix]\n", argv[0]);
		fprintf(stderr, "\n");
		fprintf(stderr, "Convert PPM image to raw binary data (excluding header).\n");
		return -99;
	}

	prefix = argv[4];
	i = 0;
	while(prefix[i] != 0) {
		prefix[i] = toupper(prefix[i]);
		i++;
	}

	fin = fopen(argv[1], "rb");
	if (fin != NULL) {
		char c;

		do {
			c = fgetc(fin);
			if (c == 'P') {
				c = fgetc(fin);
				if (c == '6') {
					c = fgetc(fin);
					if (isspace(c)) {
						printf("Found image header.\n");
						break;
					}
				}
			}
		} while (!feof(fin));

		buffer = readIntoBuffer(fin);
		if (buffer == NULL) {
			fclose(fin);
			return -3;
		}
		width = atoi(buffer);

		buffer = readIntoBuffer(fin);
		if (buffer == NULL) {
			fclose(fin);
			return -4;
		}
		height = atoi(buffer);

		buffer = readIntoBuffer(fin);
		if (buffer == NULL) {
			fclose(fin);
			return -5;
		}
		depth = atoi(buffer);

		size = 3 * width * height;
		if (depth > 255) {
			size *= 2;
		}
		
		printf("Width %d height %d depth %d Size %d\n", width, height, depth, size);

		copyBuffer = malloc(size);
		if (copyBuffer != NULL) {

			if (fread(copyBuffer, size, 1, fin) != 1) {
				fclose(fin);
				fprintf(stderr, "Error: Failed to read image data.\n");
				return -7;
			}
			fclose(fin);
			fin = NULL;
			fout = fopen(argv[2], "wb");
			if (fout != NULL) {
				if(fwrite(copyBuffer, size, 1, fout) != 1) {
					fclose(fout);
					fprintf(stderr, "Error: Failed to read image data.\n");
					return -7;
				}
				fclose(fout);

				fout = fopen(argv[3], "wt");
				if (fout != NULL) {
					fprintf(fout, "/* File generated by %s. */\n", argv[0]);
					fprintf(fout, "#ifndef _%s_H_\n", prefix);
					fprintf(fout, "#define _%s_H_\n", prefix);
					fprintf(fout, "\n");
					fprintf(fout, "/** Image width. */\n");
					fprintf(fout, "#define %s_WIDTH %d\n", prefix, width);
					fprintf(fout, "/** Image height. */\n");
					fprintf(fout, "#define %s_HEIGHT %d\n", prefix, height);
					fprintf(fout, "/** Color depth, maximum color value. */\n");
					fprintf(fout, "#define %s_DEPTH %d\n", prefix, depth);
					fprintf(fout, "\n");
					fprintf(fout, "#endif /* _%s_H_ */\n", prefix);
					fclose(fout);
				} else {
					fclose(fin);
					fprintf(stderr, "Can't write to file \"%s\".\n", argv[3]);
					return -2;
				}
				return 0;
			} else {
				fclose(fin);
				fprintf(stderr, "Can't write to file \"%s\".\n", argv[2]);
				return -2;
			}
		} else {
			fclose(fin);
			fprintf(stderr, "Out of memory.\n");
			return -6;
		}
	} else {
		fprintf(stderr, "Can't open input file \"%s\".\n", argv[1]);
		return -1;
	}
}
