---
ts: 2026-11-07T01:17:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OiGXcPXuatOTbG0hSgwk
---
ba: the code is identical except the *order* of the `move a0,s0` and `jal` — mine has jal then move (delay slot), target has move then jal. Wait:

mine[8:8] target[8:10]: target has `move a0,s0; jal` at positions 8-9, while mine has `jal; move a0,s0` at 9-10.

Hmm, the target has move a0,s0 BEFORE jal? That's the call to func_8017EE68 (the first call). Wait, the target's first call: `jal func_8017EE68` with `move s0,a0`? Let me re-read the earlier target listing.

Actually, from my e1.s dump (my body):
```
jal func_8017EE68
move $16,$4
```
So mine has jal then move (delay slot).

The target (from the score diff) has at 8-9: `move a0,s0; jal func_8017D5C0`? Hmm, "jal 0 <func_8017D5C0>" — that's the first call in the SC03_126 includer context (the reloc target name differs). So target: `move a0,s0` then `jal` (NOT in the delay slot).

Wait, that means the target's first call has the move BEFORE the jal (a nop or something in the delay slot?). Let me look at the target listing for item 2. Let me dump the target function from the build object.

Interesting: so in the target, the arg copy `move a0,s0` is NOT in the delay slot; it's before the jal. Hmm, but then the delay slot is filled with something else.

Hold on: this diff is for ba, where I moved the new_var assignment into a do-while. The diff says mine has jal at 9, move at 10; target has move at 8, jal at 9. So target order: move a0,s0; jal. Mine: jal; move a0,s0.

So the target does NOT use the delay slot for the copy! Let me get the full target listing to be sure. The earlier a1.c diff (score 1) showed only insn 10 differing, so mine and target agree on the rest: both have jal then move? No — the diff for a1.c showed only insn 10 differing, meaning insns 8-9 were equal. If the target had move;jal and mine jal;move, that would differ.

Hmm, but ba has a different structure (the do-while moved the copy), which changed the schedule at insn 8-9.

Wait, the diff's "insert mine[8:8] target[8:10]" means the target has TWO insns where mine has none, and mine has two extra later. The target's insns 8-9 are `move a0,s0; jal 0 <func_8017D5C0>`. So the target's first call is preceded by the copy. And the delay slot after the jal must contain... the next instruction (insn 10).

Hmm! So in the target, `move a0,s0` is NOT in the delay slot. Let me re-examine: the target's listing from the e1.s (my body, which scores 1) — my body has `jal; move $16,$4`. The score-1 diff said only insn 10 differs (the store base). So the target ALSO has `jal; move $16,$4` at insns 8-9... 

I'm confusing myself. The diff indices: for ba, mine has 16 insns, target 16. The insert/delete says mine lacks `move a0,s0; jal` at positions 8-9 and has `jal; move a0,s0` at 9-10. So in ba, the compiler placed the copy before the jal; the target has jal then move (delay slot). OK, consistent: the target (and my w00) has jal; move.

So ba's do-while changed the first call's schedule (the copy moved out of the delay slot). Score 4 (2 insns shifted).

OK. So EBB splits hurt the schedule.

Time 18:17:40. Let me now write the item 2 notes and row, then the log. That takes ~10 min, ending ~18:28 — matching the 20-min mark from 18:09.

Let me write the notes first.

Actually, wait. Before wrapping, let me reconsider whether a MATCH is truly impossible. The target's 16 insns: let me get the full target listing to know exactly what we're aiming for. From my e1.s (which scores 1, differing only at insn 10):

```
0  subu sp,sp,24
1  sw $16,16(sp)
2  sw $31,20(sp)
3  jal func_8017EE68
4  move $16,$4
5  li $2,8
6  sw $2,512($16)
7  li $2,0x100000
8  move $4,$16
9  jal func_80171990
10 sw $2,516($4)      <- mine; target: sw $2,516($16)
11 lw $31,20(sp)
12 lw $16,16(sp)
13 addu sp,sp,24
14 j $31
15 nop? (16 ins total)
```
Hmm, 16 insns: the listing showed 15 lines? Let me count: subu, sw, sw, jal, move, li, sw, li, move, jal, sw, lw, lw, addu, j = 15. Plus a nop? The .s showed `j $31` then `.end` — maybe a nop after j. Yes, gcc emits a nop after j? In the .s there's no nop visible... The dump shows 15 insns; the score says 16. Maybe the jal's delay-slot move is counted, etc.

Anyway: the target differs ONLY in insn 10's base register. So we need the second store to use $16.

The only way: the store's base must not be rewritten by the equivalence pass. The rewrite happens because sched1 puts `a0 = r72` before the store.

What if we could make the store's base r72 *and* have sched1 keep the copy after the store? Then the delay slot would be... the store is after the copy in the target's final code anyway (the store is in the delay slot of the second jal). So the copy is before the store in the final code.

At the RTL level (post-sched), the order is: move a0,r72; jal; store. The equivalence pass sees the copy before the store → rewrites.

In the pinned body, the same order exists, but the store's base is hard $16 → no rewrite.

So MATCH requires the base to be a hard reg → impossible lever-free.

=> WALL, best 1.

Let me write the notes/row/log now. And clean up the dumps dir.

Also: the moves.md append (one line per item): `kind | func | MATCH: move / WALL tag — mechanism (P1x)`.

For item 1: `launder | func_80177940 | WALL callee-saved-order — p (r72, 14refs/34live pri 12352) is the first s-bank allocno -> $s0; target p=$s3 is pin-forced ($16/$17/$18 reserve s0,s1,s2); 132 lever-free bodies, best 41 (P1x)`

For item 2: `pin | func_8017E98C | WALL sched1-argcopy-hoist — sched1 hoists a0=r72 above the 0x204 store, local-alloc equivalence rewrites the pseudo base to a0; pinned base is hard $16; 63 lever-free bodies, best 1 (P1x)`

Let me write the notes.
