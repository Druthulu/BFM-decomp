---
ts: 2026-11-06T15:51:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h3zGDMDZGJIXfBZlJMbK
---
In c2, the la a0 is at insn 15-16 (after the s6 setup, before the D_800B9A02 load), and the call is at insn ~35. So the la is at the *arg assignment's source position* (after the pointer setup statements, before `ot = ...`). Wait, the source order is:
```
arg = &D_800AF648;    <- first
r = ...
mlo = ...
mhi = ...
c = ...
va = ...
vb = ...
ot = ...             <- line 3021
func_80052E38(arg);  <- line 3022
```
The la at 15-16 is right after `addiu s6,s4,4` (vb = r+4) and before the ot load. So it's at the `arg = ...` position? No, arg is the first statement. Hmm, sched2 reordered: the callee-save spills and pointer setups are placed before the la. sched2 picks by lowest LUID... the la's LUID corresponds to the arg set (first), so it should be first. But it's not.

Wait — the la at 15-16 is a *materialization* of the constant, and its LUID is the copy insn's LUID (the call-arg copy). The copy insn is at the call's position... but the la is at 15-16, before the ot load. Hmm.

Actually, maybe combine didn't move it; maybe cse left the arg set as `set arg = const` and combine folded the copy `a0 = arg` into `a0 = const`, deleting the arg set. The resulting `set a0 = const` insn keeps the *copy's* LUID. The copy is created by the call's `use` — its position in the insn stream is at the call. But the call's argument setup insn might be placed early by sched2 due to LUID from... hmm.

Whatever the mechanism, the la is at 15-16 in mine and 1-2 in target. The difference is the LUID/position.

Now, the launder makes the first set survive with a low LUID → la first. 

Plain C alternatives:
- Make the arg set non-dead by a second use.
- Make the call's argument copy not foldable.

What if we pass arg to the call *indirectly through a variable that's assigned after the pointer setup*? no.

Hmm, what if we reorder the statements: put the call (and arg assignment) at the very beginning, before the pointer setup? Then the la would be first, but the call would also be first — the target's call is after the setup (with `sll v0,v0,0xe` before the jal). If we move the call earlier, the target would differ (the call's position/order). But wait — sched2 might still reorder the call after the setup? Calls are barriers-ish; sched1/sched2 don't move calls across... The call is at a fixed position in the stream relative to other insns (sched2 can move non-call insns around but the call stays). If the C has the call first, the call would be first → wrong.

Hmm.

OK, what about making the arg assignment's set survive by using arg *in the loop*? For example, the call func_80052E38(arg) — maybe the original source called it in a different way... no.

Let me look at what func_80052E38 is. It's probably "SetDrawEnv"? No, one arg. Maybe it's `GsInit`? Hmm.

Alternatively, maybe the original source had `arg` used for *two* calls: func_80052E38(arg) at the start and another call later with arg. The target has only one D_800AF648 reloc, so no.

Wait, actually — maybe the original source is:
```
arg = &D_800AF648;
func_80052E38(arg);
```
and gcc 2.7.2 with a *second set* of arg... 

Hold on. Let me reconsider the C0414 dead-reset but placed BEFORE the call in a way that invalidates the equivalence at the copy:
```
arg = &D_800AF648;
arg = 0;              /* dead reset immediately after the set? */
arg = &D_800AF648;
func_80052E38(arg);
```
cse: set1 const; set2 0; set3 const; copy a0=arg → substituted to const. Still folds.

Hmm.

What about making the call's arg come from a *different* variable that is set to arg:
```
arg = &D_800AF648;
arg2 = arg;
func_80052E38(arg2);
```
cse: arg2's value is the constant; copy a0=arg2 folds; arg's set becomes dead? arg is used by arg2's set, so not dead — arg's set survives! Then la materialized at arg's set (first) and the copy folds to const → another la? That'd be 2 las. Unless the copy `a0 = arg2` folds to const and materializes... Let me test: score will tell.

Actually wait — if arg's set survives AND the call copy folds to const, we'd have the la at arg (early) and the const materialized at the copy (late) → 2 las, +1 insn. Target has 1. So no.

Unless combine folds the copy `a0 = arg2` into `a0 = arg` (no constant substitution) — then the la is at arg's set (early) and the copy is a move → target wants a0 = la directly (no move). Hmm.

Let me just try: `arg2 = arg; func_80052E38(arg2);` and see.

Also try: `func_80052E38(arg = &D_800AF648);`? assignment as expression — the set's value used directly; the call copy is the assignment's value. Hmm.

Let me also try making the arg variable's *first* set the call argument through a cast of a *pointer difference*: no.

Let me test a few:
- c4: arg2 = arg; call(arg2).
- c5: call(arg = &D_800AF648) inline.
- c6: arg = &D_800AF648; call(arg); arg = &D_800AF648; (second set after, keeps first alive? the second set is dead and deleted, but flow deletes it before cse? cse runs before flow? Order: cse1 → ... → flow? Actually flow is the first pass; cse1 after. A dead set `arg = &sym` after the call: flow might not delete it (it's not obviously dead? it is). Let me test.)

Let me test c4, c5, c6.
