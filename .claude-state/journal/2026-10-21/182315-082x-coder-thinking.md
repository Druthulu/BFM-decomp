---
ts: 2026-10-22T00:23:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_HZZNxhyNo0LQTisaZ0ci
---
candC (only the e launder removed) = 6: 89 ins (same count) but the load of e is in the wrong place (mine at 44, target at 36) → address shifts.

So the e launder is load-bearing too (it keeps the load in the case1 arm). Removing it moves the load later.

Hmm! So both launders are load-bearing → this item is likely a WALL unless I find C moves.

For the e case: the load must stay in the case1 arm. In C, the load is `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` in the case1 arm, and e is used in the shared block. gcc sinks the load into the shared block (or CSEs it there).

To keep it in the arm: make e's value used IN THE ARM. E.g. in the case1 arm, add a use of e? That would change the code.

Hmm, alternatively: make the case1 arm's e a DIFFERENT variable from the case0 arm's e (so the load can't be hoisted/sunk into the shared block):
```
case0:
    ...
    e0 = ((Unkstruct_800B5CB8 *)s0)->unk20;
    argmode = 2;
    goto shared;
case1:
    ...
    e1 = ((Unkstruct_800B5CB8 *)s0)->unk20;
    argmode = 3;
shared:
    { s32 t = CAST_WIDTH(s32, e?, 4); ... }
```
but then the shared block needs to know which arm → e must be a single variable. Unless the shared block is duplicated per arm (restructuring → different code).

Hmm, what if the shared block's use of e is replaced by a use of a variable assigned in each arm: e.g. in each arm, `p4 = e + 4;` hmm.

Alternatively: keep the launder's effect by making the load's dest have 2 sets: `e = ...; e = e;`? (identity, disallowed + folded).

Hmm, what about `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` → `e = ((Unkstruct_800B5CB8 *)s0)->unk20; e |= 0;`? gcc folds `x|0` → x, removing the insn but maybe keeping a SET... risky and it's an identity statement (disallowed).

Hmm, what about a compound assignment with a mask that preserves the value: e.g. `e &= 0xFFFFFFFF;`? Also an identity.

OK. Let me consider the "boost" framing again for the e case: the load's dest (e's pseudo) is single-set → boosted → sunk to its consumer (the shared block). To kill the boost we need a 2nd set of e's pseudo that survives cse/flow.

In the case1 arm, after `e = ...`, we could add a *real* second set that is used: e.g. the case1 arm could compute something with e that's also in the target... The target's case1 arm (from the disassembly) — let me look at the target's code around 30-50 to see what the case1 arm does. Let me dump the target for func_8017DE84.

That would help me see exactly what the launder is doing there (the load at 36 in the arm, and the "j 2084").

Let me dump the target 0-60.
