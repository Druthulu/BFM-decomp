---
ts: 2026-11-06T16:35:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_95kOSN6JyLrUqXsh2HGZ
---
CPPFLAGS in match_one don't include -Isrc/shared or -Isrc. But that's for standalone function compile with includes from the body. My .i came from the real TU. Same cc1.

So why different output? The assembly I generated (`o1.s`) should be identical to build if same cc1 flags and same .i. Unless... the cc1 run used the .i with `# 3970 "src/..."` line markers — irrelevant.

Wait, maybe the difference: build uses -O2 but also the file-level flags from the Makefile (e.g., -fno-delayed-branch?). Let me look at the Makefile for per-file flags. Also check whether the build for ov_SC05_007 uses maspsx (assembly post-processing). But the difference here is in cc1 output (register allocation), not the assembler.

Hmm, actually, is it? My o1.s: `addu $4,$4,$0` for self = arg0+zr. The target build: `move a1,a0`. The target object build must have had self allocated a1. My dump says 73 in 4 (a0) and 81 in 5 (a1)... wait, in o1.greg: "73 in 4 75 in 2 78 in 2 81 in 5". Reg 81 = f pinned $2? No, $2 is v0 (reg 2). "81 in 5" = a1. Hmm the dispositions list 81 in 5, meaning the pseudo 81 got hard reg 5 (a1). And 73 in 4 (a0).

But in the target build, the self pseudo was in a1. So the tree's cc1 gave a different allocation than my run. That means the inputs differ: perhaps the real build's TU has additional content (other functions) affecting... no, register allocation is per function. Unless -O2 vs something, or the `-G0`.

OH WAIT. Maybe the build isn't from the src .c directly: it goes through `maspsx` with `--expand-div`, and maybe through cpp with more flags. But register allocation is cc1's.

Hmm, let me verify: does the current tree build object actually have `move a1,a0`? Yes, from build/src/...o I objdumped: `move a1,a0`.

And my o1.s has `addu $4,$4,$0`. So the same source text gives different RTL. Difference could be cpp: the .i I made may lack something like `-funsigned-char` or the file may be compiled with `-O2` and specific `#pragma`? Or maybe the build uses `-fno-builtin` differences.

Let me look at the Makefile's CC1 invocation.
