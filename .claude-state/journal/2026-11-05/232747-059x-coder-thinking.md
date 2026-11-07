---
ts: 2026-11-06T06:27:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Q91LsxML5WQHN7uCWPOd
---
Now I see it precisely. In my lever-free candidate:

"Insn 45: giv reg 91 src reg 73 benefit 4 ... mult 4 add (reg:SI 88)"
"Insn 47: dest address src reg 73 benefit 5 ... mult 4 add (reg:SI 88)"
"giv at 45 combined with giv at 47" → "giv at 47 reduced to (reg:SI 135)" and "giv at 45 reduced to (reg:SI 135)".

So there are THREE givs on the array address: insn 43 (the load `D_8018E894[i]`), insn 45 (another address using the same), insn 47 (dest address). Hmm — reg 88 is the base address pseudo.

In the target dump, only "Insn 43: giv reg 90 src reg 73 benefit 2 used 1 lifetime 1 replaceable mult 4 add 0" — just ONE giv, and it's "not worth while, 0 vs 62".

Interesting! In the target there's only one giv (the load at insn 43); in mine there are three (43, 45, 47). Why? Because in the target, the address `&D_8018E894[i]` appears once... but in mine it appears three times? 

Wait: insn 45 and 47 use `mult 4 add (reg:SI 88)` — reg 88 is a base address. Hmm, in the target there's no reg 88 giv. 

Hold on. The loop has: `u = D_8018E894[i]` — one use. What else addresses with mult 4? Nothing in the loop... unless the loop.c insn numbers 43/45/47 refer to insns in the *inner* loop? No, this is the outer loop (29-202).

Hmm, insns 43,45,47 are consecutive — that's the `u = D_8018E894[i]` expansion? No, that's one load.

OH WAIT. I bet these are from the *pins removed* change: `hh` and `tmp` are no longer hard regs, so the RTL has more pseudos... no.

Hmm, let me look at the target's insn 43 vs mine. Actually, in the target dump the outer loop's giv list has only insn 43. In mine, 43, 45, 47. What are insns 45 and 47 in mine?

The difference: in the target, `tmp` is a hard reg ($2) so the insn sequence around 43-47 differs — but the array access is once.

Hmm, "mult 4 add (reg:SI 88)" — reg 88 could be the *array base address* `&D_8018E894` materialized in a register, with the giv being `base + i*4`. So the address is a giv on reg 73 (i) with base reg 88.

In mine there are two more givs (45, 47) with the same base reg 88 — meaning there are 2 more memory refs at `base + i*4 + offset`? The array access is once... 

Unless the loop contains `D_8018E894[i]` AND the compiler generated two extra address computations because of... hmm.

Wait, maybe insn 45/47 are in the inner loop after all — loop.c numbers insns by uid, not by position. "Loop from 29 to 202: 58 real insns" — the outer loop contains the inner loop. The inner loop's insns are included. So insns 43,45,47 could be the array load and two other memory refs... but what other mult-4 refs are in the loop?

Hmm, `D_8018E59C` with `((rand()&1)<<2)` — that's a mult 4 address with a *different* base (D_8018E59C), and the index is rand()&1, not i. So not a giv on reg 73.

`pos` array accesses are stack-relative.

Hmm, so what are 45 and 47? They must be pseudo-instructions from the address computation. 

Hmm, honestly, maybe the difference is that in the target, `u` (reg 88?) ... 

Let me just look at the RTL in the target's loop dump around insns 43,45,47 vs mine. Let me grep both dumps for "insn 45" and "insn 47" in the .loop dumps.

Actually, a faster route: the mechanism I need is "make the array GIV not worth while". In the target, the single giv at insn 43 is benefit 2, "not worth while, 0 vs 62" — the threshold is 62 (the loop's insn count). In mine, "0 vs 58" — the giv at 43 is also not worth while, BUT givs 45 and 47 were reduced! That's what created the pointer increment (reg 135).

So the hoisting in mine comes from givs 45/47, not from 43.

What are insns 45 and 47 in my RTL? Let me look. In the target RTL, insns 43,45,47 exist too presumably (same source) but only 43 is a giv.

The difference must be the pins: with `tmp` pinned to $2, some address computations differ.

Let me look at the target's RTL for insns 43-50 and mine. Grep the .loop dumps.
