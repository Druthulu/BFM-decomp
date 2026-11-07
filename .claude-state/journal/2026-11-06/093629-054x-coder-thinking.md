---
ts: 2026-11-06T16:36:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ej1IypjT9MBaVaxkT96H
---
The unspliced t.i gives the TARGET-ish assembly: `addu $5,$4,$0` (self=a1), then `lh $2,170($5)`... and `lw $3,32($5); lw $2,220($5); lhu $3,24($3)` — that's p in v1, f in v0! Exactly the target.

So the unspliced t.i compiles correctly. But my spliced o1.i compiled differently. So my splice corrupted something! What? In o1.i, the body came from orig.c lines 3916-3948. Let me diff the spliced region against the original t.i region. Maybe my splice.py replaced the function but the K&R `void func_8017EAD8(arg0)` line search matched... or the brace matching ended early.

Actually, notice: o1.s had `addu $4,$4,$0` — self=a0, meaning `self = arg0 + zr` where zr pin... In the unspliced, `addu $5,$4,$0` self=a1. The difference: the pins! In o1.i the pins might have been dropped? Wait no, orig.c has the pins. Hmm, in o1.s, `lhu $5,24($5)` suggested g pin... 

OH! I bet the splice put the body but my splice.py's brace matching counted braces in *lines* including the function's opening line `{` on its own line. Fine.

Let me diff the function region of t.i and o1.i.
