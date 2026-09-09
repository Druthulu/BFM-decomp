#include "common.h"
#include "../shared/ov/func_80144B9C.h"


/* func_801457A4 @ 0x801457A4 — an -O0 function stranded at the whale's end boundary (it is the
 * FIRST fn of the -O2 "after" segment, but its target is -O0: frame-pointer + per-case stack
 * reloads). It can only bank in an -O0 object, so it lives here: _o0b is already -O0-compiled and
 * its .text ends exactly at 0x801457A4 (right after func_80144B9C), placing this fn at its true
 * address with no linker/Makefile change. Its stub was removed from ov_SC01_077_after.c. Def sig
 * conformed byte-neutrally to func_80144B9C.h's decl `void *func_801457A4(s32)` (the whale calls it
 * that way); byte-proven at -O0 (match_one --o0 79/79) and by the whole-binary gate. Phase-29 bank. */
extern int D_8017F22C;

#include "../shared/ov/func_801457A4__b9863ee9.h"
