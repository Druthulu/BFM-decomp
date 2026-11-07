---
ts: 2026-11-06T12:47:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EHVDR4V65d7WpAAPwv6q
---
Mine:
```
ba7c andi v0,a1,0x10
ba80 beqz v0, ba8c
ba84 move a0,v1      <- delay slot (else value) 
ba88 addiu a0,v1,-256
ba8c lbu v0,0(s2)    <- join
```
So mine puts the else's `move a0,v1` in the beqz delay slot and the tc-arm `addiu` as fall-through. Clever: since the else is a single move, dbr fills the delay slot with it. Target:
```
beqz v0, ba8c
? (delay slot)
j ba90
addiu a0,v1,-256  (j delay slot)
ba90: ...
```
Hmm target uses a j because... target's delay slot for beqz is something else and then j.

So target does NOT fill the beqz delay slot with the else move. That's dbr behaviour: the barrier in the else arm made the else block non-trivial (an asm insn), so the delay slot couldn't be filled with the move, and the layout used a `j`.

Real-C way to stop dbr from filling the delay slot: make the else arm longer / not a simple move. But the else must be `ua = ub;` — a single move.

Options:
(a) Give the else arm a second insn. E.g. `else { ua = ub; }` where ua/ub are different pseudos → but it's one move.
(b) Make the tc arm longer so the branch layout changes.

Hmm. What if I write the else as `ua = ub + 0;`? That's the same move (folded).

What about making `ub` and `ua` live differently... 

Alternative: restructure to a single conditional with an explicit temp:
```
s32 dv = tc ? 0x100 : 0;
ua = ub - dv;
```
That gives a different shape (no branch at all, or a conditional move). Hmm.

Alternatively:
```
if (tc) {
    ua = ub - 0x100;
    ...
}
```

Hmm, let me think about what dbr does: it fills the delay slot of `beqz` with the insn from the else block (the fall-through-to-target path). Target didn't. In target the else block is at ba8c? No — target's beqz jumps to ba8c which is the else. And the delay slot at 271 is some other insn. Then j ba90 with addiu in the delay slot.

So target's else block is at ba8c: `move a0,v1` then join at ba90? Let me reconstruct target:
```
269 andi v0,a1,0x10
270 beqz v0, ba8c     ; if !tc goto else
271 <delay slot: something>
272 j ba90
273 addiu a0,v1,-256  ; delay slot of j
ba8c: move a0,v1     ; else
ba90: lbu ...
```
Wait but then the beqz delay slot at 271 would be executed on both paths — must be an insn valid for both. And `j ba90` skips the else.

So target does NOT put the else move in the beqz delay slot; it puts it at ba8c. Whereas mine does.

Why? Because in the target the else block is not "the fall-through target of the branch in the other direction"... dbr's delay-slot filling takes the insn at the branch target only if the target block's first insn can be moved? No — filling a delay slot with an insn from the branch *target* is not valid.

Actually in mine, `move a0,v1` at ba84 is in the beqz delay slot and the branch target is ba8c (the join). That means mine has NO else block — the else's move is in the delay slot (executed unconditionally), and the tc arm's addiu is fall-through. That's a valid optimization: since the else arm is a single move and the join is right after, dbr fills the delay slot with the else value, then the tc arm overwrites a0 if taken.

Target instead has an explicit else block with the move and a j.

To stop this in real C: make the else block have 2+ insns. For example, make the else compute something else too. But semantics...

Idea: `ua = ub;` where ub is a different type — e.g. if `ub` is s32 and `ua` is s32. It's one move.

Idea: change the structure to avoid the branch entirely:
```
tc = tpage & 0x10;
ub = sy;
ua = ub - (tc ? 0x100 : 0);
```
That's f3 → 10, 407. Same shape.

Idea: make the condition produce a value: `ua = ub + (tc ? -0x100 : 0);` same.

Idea: move the `ub = sy;` assignment differently: `ua = sy; ub = sy; if (tc) ua -= 0x100;` → f2 = 10.

Hmm. What about making the else arm contain a *store* (real work)? Not semantics-preserving.

What about making the tc arm a *call-free* but longer sequence so gcc's if-conversion differs: e.g.
```
if (tc) {
    ua = ub - 0x100;
} else {
    ua = ub;
}
ub = ua + rec->h - 1;
```
Target's ub = ua + rec->h - 1 computed at join.

Alternative real-C: use the `tc` value arithmetically with a mask:
```
ua = ub + (tc >> 4) * -0x100;   // tc is 0 or 0x10
```
No.

Hmm, let me reconsider: maybe I should not crack barrier 3 via the tc-arm shape but instead make the *else arm* contain an extra real statement that folds away. E.g.:

```
} else {
    ub = sy;
    ua = ub;
}
```
That's a redundant store to ub — would be folded (ub already sy). Probably deleted.

Or:
```
} else {
    ua = ub;
    tc = 0;
}
```
Dead store, deleted by flow.

Or make `ua` a s16/u16 cast: `ua = (u16)ub;`? That adds an andi insn. Not allowed (extra insn).

What about making the else arm compute `ua = ub;` where `ub` was just written in the tc arm too... 

New idea: swap which variable is the branch target by computing `ua` from `tc` in the arm and having the else do the *other* work. I.e., restructure as:
```
if (tc) {
    ua = ub - 0x100;
} else {
    ua = ub;
}
```
The real problem is dbr filling the delay slot. To prevent dbr from doing that, the else block must be longer than 1 insn or the branch must be "needed" differently.

What if I put a `do {} while(0)` inside the else? An empty loop... `else { do { ua = ub; } while (0); }` — do-while(0) with a single statement is folded away by jump opt (no loop notes at RTL? C0535 says it splits cse1 EBB, so it survives to cse1). If it survives as a NOTE_INSN_LOOP_BEG/END, dbr might not fill the delay slot across a loop note? Worth a try.

Let me try:
- g1: `else { do { ua = ub; } while (0); }` // !FAKE: do-while
- g2: `if (tc) ua = ub - 0x100; else do { ua = ub; } while (0);`
- g3: put the do-while around the whole if.
- g4: `else { ua = ub; ub = ub; }` (dead)
- g5: swap: `if (tc) { ua = ub - 0x100; } else { ua = ub; }` but with `tc` computed differently: `tc = (tpage >> 4) & 1;`? That changes the andi. Target has `andi v0,a1,0x10` so tc = tpage & 0x10. Keep.

Also, maybe use the original b3.c single-removal context? No, we need the combined.

Let me also try making the else arm two statements that are semantically one: `ub = sy; ua = ub;` where `ub = sy` was moved inside the else (and outside for the tc arm)? The code before is `ub = sy;` then if/else. If I move `ub = sy;` into both arms:
```
if (tc) { ub = sy; ua = ub - 0x100; } else { ub = sy; ua = ub; }
```
The tc arm then has 2 insns (move + addiu), else 1 (move). Target's tc arm is 1 insn (addiu). Hmm, but ub=sy is a `move v1,a1`? Actually sy is already in a reg; ub = sy is a move.

Let me just try a batch.
