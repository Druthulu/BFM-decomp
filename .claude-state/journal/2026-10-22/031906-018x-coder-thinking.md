---
ts: 2026-10-22T09:19:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_lWHndd7rWkbA8fFbDXgU
---
The spliced TU is there: ov_SC02_005_jr_80181D30.c (171KB) with our candidate body substituted. I can dump it with cc1_dumps_tu.sh (which accepts a .c file) into a dir under my shard.

DUMP_ROOT env var can be set to my shard dir: `DUMP_ROOT=.run/P40/T11/RM2/dumps bash tools/cc1_dumps_tu.sh <file> rm2_28`.

But wait: the spliced TU file at .run/P36/engine/score/... is outside my shard; reading it is fine, but I shouldn't write there. The dump goes to DUMP_ROOT.

However: dumps of the full TU are big (each pass dump of a 5000-line TU). The brief says cc1 dumps go under my item dir and are deleted after reading. A full-TU dump could be hundreds of MB. Disk is capped (75GB, 4GB free). Let me be careful: maybe I can extract just the function's section from the dump file.

Alternative: use `-dr` style dumps but grep the function's block. The dumps contain all functions of the TU. The .cse / .combine dumps are big but I can grep for the relevant insn.

Let me first check size: run the dump for the candidate and check sizes, then immediately grep the function's RTL.

Actually, do I even need dumps? For 80184828, the question is which pass swaps the add operands. The dump would show: after combine, the tree is (plus (reg v0) (reg a1)) in mine. In the target it's (plus a1 v0) presumably because in the original code the expression was written differently, e.g. `p + off` where p is a pointer and off int → (plus p off) but combine reassociates (plus p (mult x 8)) → (plus (mult x 8) p)?

Hmm! That's a very plausible mechanism: gcc 2.7's combine has a rule that converts `x * 2^n + y` into `(x << n) + y` — i.e., it moves the shift to the front? Let's think: the target asm has sll v0,v0,3 then addu v0,a1,v0 — pointer in a1 added to the shifted index. If the tree were (plus (sll x 3) p) then the add would naturally be `addu v0,v0,a1`? No wait: the asm `addu v0,a1,v0` means dest=v0, op1=a1, op2=v0. GCC's asm output for (plus A B) is "addu dest,A,B" where dest is a fresh reg and A,B in order. If tree = (plus a1 v0) → addu v0,a1,v0. If tree = (plus v0 a1) → addu v0,v0,a1.

So in mine the tree is (plus index ptr) and target is (plus ptr index).

combine in gcc 2.7.2 does have this in the PLUS case:

```
	    case PLUS:
	      ...
	      /* Try to combine ... */
```
and importantly in `combine_insns` there's this code for commutative ops:

```
      /* If we are adding two constants, ... */
```

Hmm, and in `simplify_rtx`? Let me actually search the gcc 2.7.2 source... maybe the repo has it: check tools/bin/gcc-2.7.2-psx — probably just binaries. Let me check if source is around.

Alternatively, empirically: the target presumably was compiled from the original decompiled source of the ROM (the "target asm" is the ground truth asm of the original game). The original C code that produced `addu v0,a1,v0` — from the original game source (decomp of Silent Hill?) — the address was probably computed as `*(s16 *)(D_80195AF6 + unk100*8 + 4)` written in a way that yields (plus ptr (plus (mult..) 4))? Hmm, but the +4 constant would be folded into the load offset. The load at target: after addu v0,a1,v0 comes probably `lw v0,4(v0)`? Actually 85/86 replace; insn 86 in ours. Let's look at the surrounding asm of the target. The diff output shows only that one line. Let me get more context: run dt.sh with tail 20 to see nearby instructions.

Let me look at more of the diff/asm context.
