/*
 * sbcalls.h - SBIOS interfaces.
 *
 * Copyright (c) 2003 Marcus R. Brown <mrbrown@0xd6.org>
 * Copyright (c) 2008 Mega Man
 *
 * See the file LICENSE, located within this directory, for licensing terms.
 */

#ifndef TGE_SBCALLS_H
#define TGE_SBCALLS_H

#include "tge_sbios.h"

typedef void (*SbiosEndFunc_t)(void *, int);

/* misc.c */
int sbcall_getver(void);
int sbcall_halt(tge_sbcall_halt_arg_t *arg);
int sbcall_setdve(tge_sbcall_setdve_arg_t *arg);
int sbcall_putc(tge_sbcall_putc_arg_t *arg);
int sbcall_getc(void);
int sbcall_setgscrt(tge_sbcall_setgscrt_arg_t *arg);
int sbcall_setrgbyc(tge_sbcall_setrgbyc_arg_t *arg);

/* sifdma.c */
int sbcall_sifinit(void);
int sbcall_sifexit(void);
int sbcall_sifsetdma(tge_sbcall_sifsetdma_arg_t *arg);
int sbcall_sifdmastat(tge_sbcall_sifdmastat_arg_t *arg);
int sbcall_sifsetdchain(void);
u32 sbcall_sifsetreg(tge_sbcall_sifsetreg_arg_t *arg);
u32 sbcall_sifgetreg(tge_sbcall_sifgetreg_arg_t *arg);
int sbcall_sifstopdma(void);

/* sifcmd.c */
int sbcall_sifinitcmd(void);
int sbcall_sifexitcmd(void);
int sbcall_sifsendcmd(tge_sbcall_sifsendcmd_arg_t *arg);
int sbcall_sifcmdintrhdlr(void);
int sbcall_sifaddcmdhandler(tge_sbcall_sifaddcmdhandler_arg_t *arg);
int sbcall_sifremovecmdhandler(tge_sbcall_sifremovecmdhandler_arg_t *arg);
int sbcall_sifsetcmdbuffer(tge_sbcall_sifsetcmdbuffer_arg_t *arg);
int sbcall_sifsetsreg(tge_sbcall_sifsetsreg_arg_t *arg);
int sbcall_sifgetsreg(tge_sbcall_sifgetsreg_arg_t *arg);
int sbcall_sifgetdatatable(void);
int sbcall_sifsetsyscmdbuffer(tge_sbcall_sifsetsyscmdbuffer_arg_t *arg);

/* sifrpc.c */
int sbcall_sifinitrpc(void);
int sbcall_sifbindrpc(tge_sbcall_sifbindrpc_arg_t *arg);
int sbcall_sifcallrpc(tge_sbcall_sifcallrpc_arg_t *arg);

/* iopheap.c */
int sbcall_iopheapinit(tge_sbcall_rpc_arg_t *carg);
int sbcall_iopaheapalloc(tge_sbcall_rpc_arg_t *carg);
int sbcall_iopheapfree(tge_sbcall_rpc_arg_t *carg);

/* mc.c */
int sbcall_mcinit(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcgetinfo(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcgetdir(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcopen(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcclose(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcseek(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcread(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcwrite(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcflush(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcmkdir(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcsetfileinfo(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcdelete(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcformat(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcunformat(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcgetentspace(tge_sbcall_rpc_arg_t *carg);
int sbcall_mcrename(tge_sbcall_rpc_arg_t *carg);

/* pad.c */
int sbcall_padinit(tge_sbcall_rpc_arg_t *carg);
int sbcall_padend(tge_sbcall_rpc_arg_t *carg);
int sbcall_padportopen(tge_sbcall_rpc_arg_t *carg);
int sbcall_padportclose(tge_sbcall_rpc_arg_t *carg);
int sbcall_padsetmainmode(tge_sbcall_rpc_arg_t *carg);
int sbcall_padsetactdirect(tge_sbcall_rpc_arg_t *carg);
int sbcall_padsetactalign(tge_sbcall_rpc_arg_t *carg);
int sbcall_padinfopressmode(tge_sbcall_rpc_arg_t *carg);
int sbcall_padenterpressmode(tge_sbcall_rpc_arg_t *carg);
int sbcall_padexitpressmode(tge_sbcall_rpc_arg_t *carg);
int sbcall_padread(tge_sbcall_padread_arg_t *arg);
int sbcall_padgetstate(tge_sbcall_padgetstate_arg_t *arg);
int sbcall_padgetreqstate(tge_sbcall_padgetreqstate_arg_t *arg);
int sbcall_padinfoact(tge_sbcall_padinfoact_arg_t *arg);
#if 0
int sbcall_padinfocomb(tge_sbcall_padinfocomb_arg_t *arg);
#endif
int sbcall_padinfomode(tge_sbcall_padinfomode_arg_t *arg);

/* cdvd.c */
int sbcall_cdvdinit(tge_sbcall_rpc_arg_t *carg);
int sbcall_cdvdreset(tge_sbcall_rpc_arg_t *carg);
int sbcall_cdvdready(tge_sbcall_rpc_arg_t *carg);
int sbcall_cdvdread(tge_sbcall_rpc_arg_t *carg);
int sbcall_cdvdstop(tge_sbcall_rpc_arg_t *carg);
int sbcall_cdvdgettoc(tge_sbcall_rpc_arg_t *carg);
int sbcall_cdvdreadrtc(tge_sbcall_rpc_arg_t *carg);
int sbcall_cdvdwritertc(tge_sbcall_rpc_arg_t *carg);
int sbcall_cdvdmmode(tge_sbcall_rpc_arg_t *carg);
int sbcall_cdvdgeterror(tge_sbcall_rpc_arg_t *carg);
int sbcall_cdvdgettype(tge_sbcall_rpc_arg_t *carg);
int sbcall_cdvdtrayrequest(tge_sbcall_rpc_arg_t *carg);
int sbcall_cdvdread_video(tge_sbcall_rpc_arg_t *carg);

/* Sound .*/
int sbcall_soundinit(tge_sbcall_rpc_arg_t *carg);
int sbcall_soundend(tge_sbcall_rpc_arg_t *carg);
int sbcall_soundgetreg(tge_sbcall_soundgetreg_arg_t *arg);
int sbcall_soundsetreg(tge_sbcall_soundsetreg_arg_t *arg);
int sbcall_soundgcoreattr(tge_sbcall_rpc_arg_t *carg);
int sbcall_soundscoreattr(tge_sbcall_rpc_arg_t *carg);
int sbcall_soundtrans(tge_sbcall_rpc_arg_t *carg);
int sbcall_soundtransstat(tge_sbcall_rpc_arg_t *carg);
int sbcall_soundtranscallback(tge_sbcall_rpc_arg_t *carg);
int sbcall_soundremote(tge_sbcall_rpc_arg_t *carg);

#endif /* TGE_SBCALLS_H */
