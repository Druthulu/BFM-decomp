#include "common.h"
#include "../shared/func_80144B9C.h"


/* func_801457A4 @ 0x801457A4 — an -O0 function stranded at the whale's end boundary (it is the
 * FIRST fn of the -O2 "after" segment, but its target is -O0: frame-pointer + per-case stack
 * reloads). It can only bank in an -O0 object, so it lives here: _o0b is already -O0-compiled and
 * its .text ends exactly at 0x801457A4 (right after func_80144B9C), placing this fn at its true
 * address with no linker/Makefile change. Its stub was removed from ov_SC01_077_after.c. Def sig
 * conformed byte-neutrally to func_80144B9C.h's decl `void *func_801457A4(s32)` (the whale calls it
 * that way); byte-proven at -O0 (match_one --o0 79/79) and by the whole-binary gate. Phase-29 bank. */
extern int D_801852D4;

void *func_801457A4(s32 param_1) {
    switch (param_1) {
    case 0x1010:
    case 0x1052:
    case 0x1077:
    case 0x1094:
    case 0x2013:
    case 0x2015 ... 0x201a:
    case 0x2055 ... 0x205b:
    case 0x207a ... 0x2080:
    case 0x2097 ... 0x209d:
        return (void *)(&D_801852D4)[param_1 & 0xffff0fff];
    default:
        return (void *)D_801852D4;
        break;
    }
}
