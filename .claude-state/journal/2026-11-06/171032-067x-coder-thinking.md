---
ts: 2026-11-07T00:10:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_trI6G3THdS6Oob4zA8I8
---
Same instruction count (61). Only register assignments differ. Target:
- x1 = s0, x0 = s1, white = s4, base = s3.
- Also s2 = ? (target's s2 is used for `addiu s2,s2,3` = y1 = a1+3? Let me see).

Mine: x1=s4, x0=s0, white=s2, base=s3.

Hmm, target's prologue:
```
sw s1,36(sp); move s1,a0     ; x0 = a0 → s1
sw s2,40(sp); move s2,a1     ; y1? = a1 → s2
sw s5,52(sp); addiu s5,s2,-3 ; y0 = a1-3 → s5
addiu s0,s1,3                ; x1 = a0+3 → s0
addiu s2,s2,3                ; y1 = a1+3 → s2
addiu a0,sp,16
move a2,zero
li s4,255                    ; white = 255 → s4
addiu s1,s1,-3               ; x0 = a0-3 → s1
```
So target: x0=s1, y1=s2, y0=s5, x1=s0, white=s4, base=s3.

Mine:
```
move s0,a0        ; x0 = a0 → s0
sw s1,36(sp); move s1,a1   ; y1 = a1 → s1
sw s5,52(sp); addiu s5,s1,-3 ; y0 = a1-3 → s5
addiu s4,s0,3     ; x1 = a0+3 → s4
addiu s1,s1,3     ; y1 = a1+3 → s1
addiu s0,s0,-3    ; x0 = a0-3 → s0
addiu a0,sp,16
move a2,zero
sw s2,40(sp); li s2,255   ; white → s2
```
So mine: x0=s0, y1=s1, y0=s5, x1=s4, white=s2, base=s3.

So the permutation: target x0=s1 vs mine s0; y1=s2 vs mine s1; x1=s0 vs mine s4; white=s4 vs mine s2.

Hmm, this is a pure allocation-order difference. Let me check the allocno priorities.

The variables: x1 (s16), x0 (s16), base (u8*), white (s16), y0 (s16), y1 (s16). Plus the struct `line` (on the stack).

Target: x1=s0, x0=s1, y1=s2, base=s3, white=s4, y0=s5.
Mine: x0=s0, y1=s1, white=s2, base=s3, x1=s4, y0=s5.

Interesting: base=s3 in both, y0=s5 in both. So the priorities of base and y0 are the same relative position, but the others are permuted.

Let me dump the allocno table for this function. I need the TU: the includer src/ov_MAIN_012/ov_MAIN_012_jr_80135EB0.c. Let me splice.

Actually, the header include line is probably `#include "../shared/ov/func_80136F3C.h"`. My splice.py is hardcoded for func_8012DBD0.h. Let me generalize it.

Let me write a generic splice script or adapt. I'll make splice2.py that takes the header basename.

Let me do it.
