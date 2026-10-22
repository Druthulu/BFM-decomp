---
ts: 2026-10-22T06:56:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Uf2DEPTNJqD1BjLZ1Qit
---
cand12 (do { rgb = arg2; } while(0)) gives 99 ins but a different order: the li a0,16 moved AFTER the jal! (delay slot area). So the do-while changed the block structure.

Interesting: the target has li a0,16 BEFORE the jal. In cand12, `jal` comes before `li a0,16`?? That's the "li in the delay slot" phenomenon (the li is placed in the jal's delay slot, which is wrong for MIPS but gcc does it with .set noreorder?). Actually the diff shows mine: 8 sw s0, 9 move s0,a2, 10 jal, 11 li a0,16 → the li is in the delay slot of the jal. And the target: 5 sw s0, 6 move s0,a2, 7 li a0,16, 10 jal.

So in cand12, the whole block got shuffled: the sw s0/move s0,a2 pair moved AFTER the li? no wait: mine: [1-4 prologue], 5 ?, 6 ?, 7 ?, 8 sw s0, 9 move s0,a2, 10 jal, 11 li a0,16.

Hmm, mine has something at 5,6,7 (deleted lines "--"). The diff says "insert mine[5:5] target[5:8]" meaning the target has 3 instructions at 5,6,7 that mine lacks at that point; and "insert mine[7:7] target[10:11]" = the jal.

So mine: 5,6,7 = ? (3 insns that the target has elsewhere). Mine's 8,9,10,11 = sw s0, move s0,a2, jal, li.

So in cand12 the order is: [3 other insns], sw s0, move s0,a2, jal, li a0,16. The target: sw s0, move s0,a2, li a0,16, [other], jal.

So in cand12 the li ended up after the jal (in the delay slot) — a bigger mess. But interesting: the sw s0/move s0,a2 pair is BEFORE the li in cand12 too! So the boost effect was killed by the do-while? Hmm, in cand12 the move s0,a2 is at 9 and the li at 11 → the move is before the li ✓ (but the jal is in between).

So the do-while DID kill the boost (the do-while's copy is a second set that survived!) but the li got placed in the delay slot.

Hmm! Actually maybe the do-while made the block have a different structure so sched1 couldn't put the li in the delay slot...

Interesting. So a do-while CAN give the pseudo a second set that survives (because the copy inside the loop isn't cse-merged with the one outside — loop.c/cse treat them separately). But it costs a loop construct.

So: the do-while(0) gives 2 sets. Now the problem is the li landing in the jal's delay slot. The difference between cand12 and the tree: the tree's chain is [move][asm][li][call] — the asm between the move and the li creates a "distance" so the li isn't adjacent to the call.

Hmm, in cand12 the chain would be [move][li][call] with the li adjacent to the call → the delay-slot fill.

So if I use the do-while trick to kill the boost, I need to also prevent the li from being scheduled right before the call (adjacent → delay slot).

In the tree, the ASM insn sits between the move and the li, so the li isn't adjacent to the call (the asm is between? no — the tree's chain is move, asm, li, call → the li IS adjacent to the call!). Hmm, but in the tree the li is NOT in the delay slot. Hmm, because the delay-slot fill is a dbr-pass thing: the dbr pass fills the delay slot of the jal with an instruction from the following block (backward scan) or the preceding one. In the tree, the li (insn 20) precedes the call (22) and there's the asm (17) before it. The dbr "fill" pass looks backward from the branch to fill the delay slot; if the preceding insn is safe to move, it does. In the tree, the preceding insn is the li (safe? it sets a0 which the call needs — moving it INTO the delay slot is fine). But the dbr pass didn't fill it. Why? Because the li's "birth"...

Hmm, in cand12 the li ended up in the delay slot — that means the dbr pass filled the delay slot with the li. In the tree it didn't (maybe because the asm before it blocks the backward scan? The dbr backward fill requires the insn to be movable: the li sets a0 which is used by the call — the delay slot of a jal can hold the arg setup (that's the classic MIPS pattern: `li a0,16` then `jal` with `li` in the delay slot). In the tree, the li was NOT filled.

What's different? The tree's li had NO REG_EQUAL note while cand's li HAS "(expr_list:REG_EQUAL (const_int 16))". Hmm, that's a reload artifact.

Hmm wait, actually: in the tree's .sched dump, insn 20 = (set (reg:SI 4 a0) (const_int 16)) with no REG_EQUAL; in cand, insn 18 = (set (reg:SI 4 a0) (const_int 16)) WITH REG_EQUAL (const_int 16). Hmm, that difference is odd. Actually maybe I misread. Let me check the tree's insn 20 listing again:

```
(insn 20 17 22 (set (reg:SI 4 a0)
        (const_int 16)) 159 {movsi_internal2} (nil)
```
vs cand:
```
(insn 18 52 15 (set (reg:SI 4 a0)
        (const_int 16)) 159 {movsi_internal2} (nil)
    (expr_list:REG_EQUAL (const_int 16)
        (nil)))
```

Hmm, the cand's has a REG_EQUAL note. Weird. But whatever — both are "li a0,16".

Hmm, actually the difference might be that in the cand, the const 16 comes from a pseudo (the call's arg) with a REG_EQUAL note, whereas in the tree... whatever.

Let me now focus: cand12 shows that a do-while can give the 2nd set. Let's explore variants around that:
- cand12 used `do { rgb = arg2; } while (0);` — the do-while creates a loop (loop.c notes) which might affect other things.
- What about `do { rgb = rgb; } while (0);`? Hmm, `rgb = rgb` inside the loop — a self-copy might survive (cse might merge it with the outer copy since the value is the same... but within a loop, cse treats it separately).

Let me try:
cand22: `rgb = arg2; do { rgb = rgb; } while (0);` — hmm, the self-copy inside the loop: cse might delete it. But the do-while might keep the structure.
cand23: `rgb = arg2; do { rgb = (s32)rgb; } while (0);` — a copy of rgb inside the loop: does it emit an instruction? It's a self-copy → no instruction (gcc deletes it) but might survive as a set.
cand24: `rgb = arg2; do { } while (0);` (cand03, score 4).

Also, maybe a simpler idea: use a plain `for` loop or `while (0)`? Same as do-while.

Hmm, but the do-while costs: cand12's score was 8 (worse). The li landed in the delay slot. But cand03 (empty do-while) scored 4 — different diff. Let me look at cand03's diff to understand.

Let me check cand03's diff (and cand03 = `do { } while (0);` right after rgb = arg2).

Actually, maybe a better structure: put the do-while AFTER the call (so the block structure near the call is unchanged)? But then the 2nd set is later in the RTL. The pseudo's reg_n_sets is what matters (not the position!) — but the position affects where the copy insn is.

Hmm, the boost kill depends on reg_n_sets == 2, which is a global property of the pseudo, not positional. So a do-while ANYWHERE after `rgb = arg2;` would kill the boost. But the do-while must produce a second SET of pseudo 16.

What if the do-while is placed after the call?
```
rgb = arg2;
temp_v0 = func_80010A08(0x10);
...
do { rgb = arg2; } while (0);   /* dead-ish but a 2nd set */
```
But then the do-while's copy would be a real instruction (move s0,a2) → extra insn. Unless it's dead and removed... but then the set is gone.

Hmm, in cand12 the copy inside the do-while apparently did NOT emit an instruction (99 ins) — it was coalesced/removed but the SET remained?! Interesting: 99 ins, so no extra move. So gcc kept the set but no instruction? That means the copy `rgb = arg2` inside the loop was removed by... hmm, if it's removed, the set is gone.

Hmm, but the boost WAS killed (the sw s0/move s0,a2 pair moved before the li). Or maybe the boost wasn't killed and the reordering came from the loop structure.

I'm going too deep. Let me try a batch of do-while variants and see if any scores 0:

cand22: `do { rgb = rgb; } while (0);`
cand23: `do { rgb = (s32)rgb; } while (0);`
cand24: `do { rgb = arg2; } while (0);` (= cand12, score 8)
cand25: `for (rgb = arg2; 0; ) { }` — hmm, weird.
cand26: `while (0) { rgb = arg2; }` — the front end removes `while(0)` loops entirely.
cand27: `do { rgb = arg2; } while (0);` placed at the END of the function (after the if block).
cand28: `do { rgb = rgb; } while (0);` placed at the end.

Also, per the constraint: "do{}while(0) only with `// !FAKE: do-while`" — so I must add that comment.

Let me try these.

Also another idea: **`if (1) { rgb = arg2; }`** — no loop, but cse merges? Probably merged (no loop notes).

And: **a `switch` or `for` with 0 iterations**.

Let me generate and score.
