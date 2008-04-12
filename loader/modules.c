/* Copyright (c) 2007 Mega Man */
#include <stdio.h>
#include <string.h>
#include <kernel.h>
#include <iopheap.h>
#include <loadfile.h>
#include <sbv_patches.h>
#include <sifrpc.h>
#include <iopcontrol.h>

#include "modules.h"
#include "graphic.h"
#include "loader.h"
#include "rom.h"
#include "eedebug.h"
#include "configuration.h"

/** Structure describing module that should be loaded. */
typedef struct
{
	/** Path to module file. */
	const char *path;
	/** Parameter length. */
	unsigned int argLen;
	/** Module parameters. */
	const char *args;
	/** True, if ps2smap. */
	int ps2smap;
} moduleLoaderEntry_t;


static moduleLoaderEntry_t moduleList[] = {
	{
		.path = "eedebug.irx",
		.argLen = 0,
		.args = NULL
	},
#ifdef RESET_IOP
	{
		.path = "rom0:SIO2MAN",
		.argLen = 0,
		.args = NULL
	},
	{
		.path = "rom0:MCMAN",
		.argLen = 0,
		.args = NULL
	},
	{
		.path = "rom0:MCSERV",
		.argLen = 0,
		.args = NULL
	},
#endif
	{
		.path = "rom0:PADMAN",
		.argLen = 0,
		.args = NULL
	},
#ifdef RESET_IOP
	{
		.path = "rom0:CDVDMAN",
		.argLen = 0,
		.args = NULL
	},
	{
		.path = "ioptrap.irx",
		.argLen = 0,
		.args = NULL
	},
	{
		.path = "iomanX.irx",
		.argLen = 0,
		.args = NULL
	},
#ifdef PS2LINK
	{
		.path = "poweroff.irx",
		.argLen = 0,
		.args = NULL
	},
	{
		.path = "ps2dev9.irx",
		.argLen = 0,
		.args = NULL
	},
	{
		.path = "ps2ip.irx",
		.argLen = 0,
		.args = NULL
	},
	{
		.path = "ps2smap.irx",
		.argLen = 0,
		//.argLen = 39,
		.args = NULL,
		//.args = "192.168.0.10\000255.255.255.0\000192.168.0.1",
		.ps2smap = 1
	},
	{
		.path = "ps2link.irx",
		.argLen = 0,
		.args = NULL
	},
#endif
#endif
	{
		.path = "usbd.irx",
		.argLen = 0,
		.args = NULL
	},
	{
		.path = "usb_mass.irx",
		.argLen = 0,
		.args = NULL
	},
	{
		.path = "fileXio.irx",
		.argLen = 0,
		.args = NULL
	},
	{
		.path = "ps2kbd.irx",
		.argLen = 0,
		.args = NULL
	},
};

static int moduleLoaderNumberOfModules = sizeof(moduleList) / sizeof(moduleLoaderEntry_t);

/** Parameter for IOP reset. */
static char s_pUDNL   [] __attribute__(   (  section( ".data" ), aligned( 1 )  )   ) = "rom0:UDNL rom0:EELOADCNF";

int loadLoaderModules(void)
{
	int i;
	int rv;

#ifdef RESET_IOP
	graphic_setStatusMessage("Reseting IOP");
	FlushCache(0);

	SifExitIopHeap();
	SifLoadFileExit();
	SifExitRpc();
	SifStopDma();

	SifIopReset(s_pUDNL, 0);

	while (SifIopSync());

	graphic_setStatusMessage("Initialize RPC");
	SifInitRpc(0);

	graphic_setStatusMessage("Patching enable LMB");
	sbv_patch_enable_lmb();
	graphic_setStatusMessage("Patching disable prefix check");
	sbv_patch_disable_prefix_check();
#else
	SifInitRpc(0);
#endif

	graphic_setStatusMessage("Add eedebug handler");
	addEEDebugHandler();

	graphic_setStatusMessage("Loading modules");
	for (i = 0; i < moduleLoaderNumberOfModules; i++) {
		rom_entry_t *romfile;
#ifdef RESET_IOP
		/* Load configuration after mc modules loaded. */
		if (i == 4) {
			loadConfiguration();
		}
#else
		/* Load configuration after eedebug. */
		if (i == 1) {
			loadConfiguration();
		}
#endif
		graphic_setStatusMessage(moduleList[i].path);
		printf("Loading module %s)\n", moduleList[i].path);

		if (moduleList[i].ps2smap) {
			moduleList[i].args = getPS2MAPParameter(&moduleList[i].argLen);
		}
		romfile = rom_getFile(moduleList[i].path);
		if (romfile != NULL) {
			int ret;

			ret = SifExecModuleBuffer(romfile->start, romfile->size, moduleList[i].argLen, moduleList[i].args, &rv);
			if (ret < 0) {
				rv = ret;
			}
		} else {
			rv = SifLoadModule(moduleList[i].path, moduleList[i].argLen, moduleList[i].args);
		}
		if (rv < 0) {
			error_printf("Failed to load module \"%s\".", moduleList[i].path);
		}
	}
	graphic_setStatusMessage(NULL);
}
