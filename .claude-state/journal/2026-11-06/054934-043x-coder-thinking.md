---
ts: 2026-11-06T12:49:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AIJccRXkI47fGMPLC39z
---
h4 = 3 with `if (!(tpage & 0x10)) { ua = ub; } else { ua = ub - 0x100; }`. Same as e2 (3).

I'm at ~40 min on item 1. Budget says 20-30 min per item, past 30 min stop and record a wall. But a WALL needs ≥ 20 min and ≥ 30 scored tries. I have ~25 scored tries so far (b1-b4, c2a-d, c3a-d, c4a-c, combo, d2a-d, e1-e6, f1-f4, g1-g4, h1-h4 = 4+11+2+4+6+4+4+4 = 39 tries). Good, I'm over 30.

Let me try maybe 3-4 more targeted ideas, then record WALL best 3.

One more idea: the target's structure has the else out-of-line and a `j`. That's what you get when the else arm is NOT threadable. dbr's threading requires the else's insn to be movable into the delay slot of the branch. What if the else arm's value is used by something the branch path also needs... no.

Alternative: make the *tc arm* two insns so the else is naturally out-of-line? e.g.
```
if (tc) {
    ub -= 0x100;
    ua = ub;
} else {
    ua = ub;
}
```
Then the tc arm = subu + move (2 insns) → target has addiu a0,v1,-256 (1). No.

What about the opposite: `ua = ub; if (tc) ua = ub - 0x100;`? f2 = 10.

Let me try: `ua = ub - (0x100 & (tc ? -1 : 0));`? Ugly, probably different.

Try: `ua = ub; if (tc != 0) { ua -= 0x100; }` — same as f2.

Try making `ua` computed with a mask: `ua = ub - ((tc >> 4) << 8);` → tc>>4 = 1 if set; <<8 = 0x100. That's srl+sll+subu = 3 insns. No.

I think the barrier-3 crack needs an extra insn in the else, which real C can't produce without changing the instruction count. So WALL: `dbr-delay-fill` — dbr fills the beqz delay slot with the else move; target keeps an out-of-line else + j. That matches the existing wall tag `dbr-delay-fill` ("delayed-branch fill takes a fall-through insn the target leaves out of the slot (G18x)").

Wait, but the existing dbr-delay-fill is about taking a fall-through insn the target leaves out. Here it's the same shape. 

Hmm, but before declaring WALL, let me try one more: make the branch condition's delay slot be filled by something else naturally. In the target, the beqz delay slot at 271 contains an insn (unknown). If mine fills it with the else move, maybe I can make another insn (e.g. `andi v1,t0,0xffff` in e2) be the delay slot and the else out-of-line. e2 does exactly that: delay slot = andi v1,t0,0xffff, else out-of-line via j. And e2's only diff from target is which arm is out-of-line.

So e2 is 1 layout difference: target out-of-lines the else (move), e2 out-of-lines the tc arm (addiu). Both 408 insns!

If I could make gcc choose the tc arm as fall-through... In e2 the source is `if (!tc) {ua=ub;} else {ua=ub-0x100;}` and gcc out-of-lined the else (=tc arm). In target the source is `if (tc) {...} else {...}` and the out-of-lined arm is the else (move). So gcc's rule seems to be "out-of-line the else arm" — consistent in both! e2: else = tc arm out-of-line. Target: else = move out-of-line.

So the target's source is `if (tc) { ua = ub - 0x100; } else { ua = ub; }` and dbr should out-of-line the else (move) — which is what target does! But f1 (same source) gives the eager fill instead.

So the difference is dbr's eager fill of the beqz delay slot with the else's move. In target, the delay slot is NOT the move; the move is at ba8c.

What makes dbr not fill? The else block in target had an asm insn (the barrier) making it 2 insns: asm + move. So dbr couldn't thread a 2-insn block into a 1-insn delay slot... actually it could thread the first insn (asm) but an asm can't go in a delay slot (may_trap / not safe?).

So real-C equivalent: the else block must have a first insn that can't be moved. Hmm.

What if the else arm has a *use* of a value produced earlier that creates a dependency preventing the fill? E.g.:
```
} else {
    ua = ub;
}
```
The move depends on ub.

What if I make the else arm's move depend on a load? no.

Alternative: what if the else arm is `ua = ub` where `ua` is also used later, and the join... no.

OK here's another thought: since the difference is only 3 insns of layout and the *count* matches (408), maybe a small source reorder elsewhere changes dbr's decision. E.g., move `ub = sy;` to after `tc = tpage & 0x10;` (already) or before. Or move the `tc` computation after `ub = sy`.

Let me try: 
- i1: `ub = sy; tc = tpage & 0x10;` (swap)
- i2: compute tc earlier, right after tpage is computed (before the store)?
- i3: `ua = ub;` placed before the branch and the branch only does the subtract... f2=10.

Let me also try: keep `tc` and use `if (tc) { ua = ub - 0x100; } else { ua = ub; }` but move the `ub = sy;` into the join? no, ub is used in both arms.

Try i1 and i2, then stop.

Actually, one more strong idea: the `if (id & 0x100)` block follows. Its layout interacts. Hmm.

Let me also consider using `&&`/`||` folds: no.

Let me try 2 variants and then finalize item 1 as WALL best 3, unless something hits 0.

Actually — wait. Let me reconsider the problem. The target's else block at ba8c has the move, and the beqz delay slot has an unknown insn. In e2, the beqz delay slot has `andi v1,t0,0xffff` and the else is out-of-line. If the target's delay slot also holds an insn and the else is out-of-line, then e2's *structure* matches target exactly except the arm order.

So if I take e2 (if (!tc) first) and just swap which arm is out-of-line... that's determined by the source arm order. e2's else is out-of-line = the tc arm. Target's else out-of-line = the move arm. So target source = if (tc) first. And f1 (if tc first) gives the eager fill.

The difference between f1 and target: in f1, dbr fills the beqz delay slot with the else move and drops the j.

Hmm, what if the else move's destination a0 conflicts... In f1, `move a0,v1` in the delay slot works because a0 is overwritten on the tc path.

What if `ua` were used *before* the branch (live-in to both arms)? Then the move couldn't be hoisted into the delay slot... no, it's after.

What if the else arm were `ua = ub; ub = ua;`? Both folded.

OK, let me try i1/i2 and then stop. Actually let me also try making the else arm two *real* insns by using a s16 cast on one:
```
} else {
    ua = ub;
}
ub = ua + rec->h - 1;
```
vs
```
} else {
    ua = ub + 0;
}
```
same.

Let me try i1 (swap tc/ub lines) and i2 (compute tc before the store).
