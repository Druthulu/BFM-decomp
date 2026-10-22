---
ts: 2026-10-22T00:27:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_t8cNWqVD4y9bI5Yghem1
---
Target:
```
95 sh v0,14(s0)
96 lw a0,32(s0)    ; t = p->unk20 (the call's arg)
97 li a1,320       ; 0x140
98 jal func_8001D0E8
99 li a2,240       ; 0xF0 (the delay slot!)
100 j ...
```
So the target: the load at 96, then li a1 at 97, the call at 98, and li a2 in the delay slot.

Mine: the load at 97 (one later) — so mine has something at 96. Mine's 96 = ? (not shown; the diff says mine[96] is "--" i.e. nothing to insert, and mine[97] = "lw a0,32(s0)").

Hmm, so mine has the load at 97 and the target at 96. What's at mine[96]? Probably "li a1,320"? Hmm, then mine = [96: li a1][97: lw a0][98: jal]?

Hmm, the target = [96: lw a0][97: li a1][98: jal][99: li a2].

So in the target, the load comes BEFORE the li a1; in mine, after. That's the SCHED_GROUP_P effect: the call + its arg setup move as a unit. The re-tie (the asm) is between the load and the call → the asm is not part of the call group → the load stays before the group's start.

Hmm, so without the asm, the load joins the call's group (the load is the a0 setup) and gets ordered within the group (after li a1?).

How to fix in plain C? We need the load to be outside the call's group. The group = the call + the insns that set the arg registers. The load sets a0 (the arg). To keep it out of the group... hmm.

Option: make the call's first argument NOT be the loaded value directly, e.g. pass it through a variable that... hmm, the arg setup IS the load.

Option: reorder the source so the load happens earlier (e.g. before the previous statement)? The load is `t = p->unk20;` — it's already right before the call. If we moved the load EARLIER in the source (e.g. before the "sh v0,14(s0)" store), the load might be scheduled earlier ✓. Hmm, but the store is to p+0xE and the load is from p+0x20 — different addresses, but p is a pointer → they may alias → the load can't be hoisted above the store.

Hmm.

Option: use a compound assignment to give the load's dest a 2nd set (kill the boost) → the load stays at its source position (before the call group) ✓ = the target!

The load's dest: `t` (a local s32). Its pseudo has 1 set. To give it 2 sets: `t = ...->unk20;` then a real second set. Hmm: what if we write the call as `func_8001D0E8(t, 0x140, 0xF0);` and t is used only there.

Hmm, what about: `t = ...->unk20; t |= 0;`? Folded.

What about making the load's dest a variable that's ALSO assigned elsewhere? E.g. reuse an existing variable.

Hmm! What about this: the "birth boost" of the load. The load's dest pseudo (t) is single-set → boosted → placed as late as possible → into the call group (as the a0 setup) → after li a1. The target has it before the group.

To kill the boost, the load's dest needs 2 sets. What if the value is loaded into a variable and then that variable is used in a way that creates a second set...

IDEA: use the compound assignment trick with a REAL operation. E.g.:
```
s32 t;
t = ((Unkstruct_80126B58 *)p)->unk20;
t &= 0xFFFFFFFF;   /* no-op */
```
Probably folded at the RTL level (the AND with all-ones is removed) — but does the *SET* survive? In gcc, `x &= 0xFFFFFFFF` where x is s32: the fold happens in expand_assignment: the result is x itself → the RTL is just x (no insn) → the 2nd set disappears. So no.

Hmm, what about `t += 0;`? Same.

What if the value is used twice: e.g. `func_8001D0E8(t, 0x140, 0xF0);` — the value t is used once.

Hmm, what if we pass t to the call AND use it in a comparison? That adds code.

Hmm, what about a different framing: instead of killing the load's boost, make the load NOT be the arg setup: e.g. copy the value into another variable first:
```
s32 t;
s32 u;
t = ((Unkstruct_80126B58 *)p)->unk20;
u = t;
func_8001D0E8(u, 0x140, 0xF0);
```
Then the load's dest (t) is single-set → boosted → sinks to just before its consumer (the copy u = t) → the copy is the arg setup (in the call group) → hmm, the load would be right before the copy → which is before the group? The copy (move u,t) is in the call group (it sets a0) → so the load sinks to just before the group ✓ = the target's position (96, before li a1 at 97? hmm, the group = [move u,t][li a1,320]?).

Hmm, in the target, the arg setup is "lw a0,32(s0)" (the load itself) and "li a1,320" and "li a2,240". The group = the call + the preceding arg-setup insns. In the target, the load is at 96 and li a1 at 97 — both before the call at 98. Hmm, so the group would be [lw a0][li a1][jal][li a2] — the load IS in the group.

Hmm! So in the target, the load is in the group but FIRST. In mine, the group = [li a1][lw a0][jal][li a2]? i.e. the load is second.

So within the group, the order of the arg setups differs: the target has the load (a0) first, then li a1 (a1), then li a2 in the delay slot. Mine has li a1 first, then the load.

Within the group, the order is determined by... the LUID/source order? The source: `func_8001D0E8(t, 0x140, 0xF0);` → the args are evaluated left to right → the load (a0) then li a1 (a1) then li a2. So the target matches the source order ✓, and mine has them swapped (the scheduler moved the load after li a1 — because the load has a higher priority (a load feeding the call) → placed later in the backward scheduler).

Hmm! So the re-tie (the asm) makes the load NOT part of the call's group (the asm is between the load and the call) → hmm, but the load is still the a0 setup.

Hmm, the doc: "SCHED_GROUP_P: a call + its immediately-preceding USE argreg insns move as one unit". The asm is between the load and the call → so the "immediately-preceding USE argreg" insn is the ASM, not the load! So the load is NOT in the group ✓ → the load keeps its own position (source order) → it's at 96, before the group [li a1][jal][li a2]... hmm, but the target has li a1 at 97 (after the load) ✓ and the jal at 98 ✓ and li a2 in the delay slot ✓.

So the target's group = [li a1,320][jal][li a2,240] and the load is outside it, just before.

In mine, the load is IN the group (as the a0 setup) and the group's internal order puts it after li a1.

So: to reproduce, the load must not be immediately before the call — something must be between it and the call (an asm). In plain C: put another statement between the load and the call! E.g.:

```
            t = ((Unkstruct_80126B58 *)p)->unk20;
            <something>;
            func_8001D0E8(t, 0x140, 0xF0);
```
But the "something" must not emit any instruction (or the count changes). Hmm! A statement that emits nothing: e.g. `t = t;`? (folded, but it might still break the "immediately preceding" relationship in the RTL — if the folded statement produces NO RTL insn, the load is still immediately preceding the call in the RTL).

Hmm. What if the something is a *call* to a function that returns nothing... no, that adds instructions.

What about a statement that produces an RTL insn with no code (like a "nop" pseudo)? Hmm.

What about making the arg setup not a "USE argreg"? E.g. if the call's first argument were passed in a way that isn't a direct register setup...

Hmm! Alternative: what if the value is loaded into a variable that is used by a LATER call, so the load is not the arg setup? E.g.:
```
t = ...->unk20;
func_8001D0E8(t, 0x140, 0xF0);
```
The load IS the a0 setup.

Hmm, what if we reorder the source so the load is not immediately before the call:
```
t = ((Unkstruct_80126B58 *)p)->unk20;
if (t) { }    /* hmm */
```

What about a compound statement that creates a barrier-ish insn without code? E.g. `t = t ^ 0;`? Folded.

Hmm, what about a `do { } while (0);` — the brief allows it with a "// !FAKE: do-while" marker. An empty do-while generates NO code in gcc (it's optimized away) → the RTL is unchanged → the load is still immediately preceding the call.

Hmm. But what if the do-while contains a statement that creates an RTL insn without a machine instruction? Hmm.

What about the "ref boost" trick from the worked example (T10's func_80181F4C): "do { r = p + i; } while (0);" — a real statement inside a do-while, which changes the flow structure (the loop) and the ref counts.

Hmm.

OK, alternative approach for item 7: what if the call's arg setup order can be changed by making the load's priority lower? The load feeds the call → pri 2 (the call is pri 1 + the load's cost 2 → the call's pri = 2? hmm, the call's pri = max(pred pri + cost - 1) = the load's pri (1) + 2 - 1 = 2). And li a1 (an ALU) → pri 1. So the call's pri = 2 → the group is scheduled at pri 2. Within the group, the members' order: the load (pri 2 chain) vs li a1 (pri 1) → the higher-pri one is placed later (backward scheduler) → the load after li a1 ✓ mine.

In the target, the load is BEFORE li a1 → the load must be outside the group (or have a lower pri).

Hmm, so: if the load's dest has 2 sets (no boost)... hmm, the boost isn't the issue here; the group's pri is.

Hmm, what if the load is not part of the call's arg group because the arg is not the loaded value directly? E.g.:
```
s32 t;
s32 u;
t = ((Unkstruct_80126B58 *)p)->unk20;
u = t;
func_8001D0E8(u, 0x140, 0xF0);
```
Then the a0 setup is "move u_reg, t_reg" (a copy) — hmm, but the copy would be coalesced away (u = t → same reg) → the a0 setup is still the load.

Hmm.

What if the argument is computed as an expression that doesn't reference t directly? e.g. `func_8001D0E8(t + 0, 0x140, 0xF0);` → gcc folds t+0 → t.

Hmm.

What if we use a *volatile* variable for t? `volatile s32 t;` → the load is a volatile load → it can't be moved/merged, and the call's arg setup would be a copy of the volatile value → hmm, that adds instructions (a load + a move?). Actually: `volatile s32 t; t = p->unk20;` → the store to t is a memory write (stack) and the read is a memory read → 2 extra instructions. NO.

Hmm, what about the reverse: make the *call* not the consumer of the load — e.g. the load's value is used by a later statement, and the call gets a different value? Semantics change.

OK, so how about this: the group order. What if the source evaluated the args in a different order? E.g.:
```
func_8001D0E8(t, 0x140, 0xF0);
```
The target's arg setup order: a0 = the load, a1 = li 320, a2 = li 240 (in the delay slot). Mine: a1 = li 320, a0 = the load, a2 = li 240.

What if we swap the argument order in the call? No (semantics).

Hmm, what if the constant 0x140 were loaded differently so that... no.

What if the load were given a lower priority by using it in a longer chain? E.g. if the arg were `t` but t's load is preceded by... hmm.

Honestly, item 7 at score 2 is tantalizingly close. Let me try a couple of cheap variants:
(a) Add a dummy statement between the load and the call that generates an RTL insn without a machine instruction. Hmm, what generates an RTL insn without code? A "call to a function that returns void and is empty"? no.

Hmm, what about assigning to a variable that is dead but whose assignment the compiler keeps? E.g. `t = t;` → gcc removes it (no RTL).

What about a "volatile" read of a *dummy* variable? Adds instructions.

(b) What if the load is moved earlier in the source (before the store "sh v0,14(s0)")? Then the load's source position is earlier, and if it's not in the call group... hmm, it would still be the a0 setup. But maybe with a different source position the group's internal order changes? The group order is by priority, not source.

Hmm, (c): what if the arg is passed as a *different* variable that is assigned from t, with the copy NOT coalesced? E.g. if the copy can't be coalesced (e.g. because u is volatile)... no.

(d) What if the load's dest pseudo has 2 sets (kill the boost) → the load's priority... hmm, the boost raises the priority to max. If the load is NOT boosted, its pri = 1 (the chain length) → then the call's pri = max(load pri + 2 - 1, li a1's chain) = 2 → hmm, the call's pri is still 2 (from the load's latency).

Hmm, but the group order: the load (pri 1) vs li a1 (pri 1) → tie → the LUID decides: the load's LUID is lower (earlier in the source) → hmm, in the backward scheduler, the higher LUID is placed later → the load (lower LUID) is placed EARLIER ✓ = the target!

So killing the load's boost would put the load first in the group ✓. And the boost is killed if the load's dest has 2 sets.

So I need the load's dest (t) to have 2 sets. The load is `t = p->unk20;` and t is used once (the call arg).

Hmm! What if t is assigned a second time EARLIER in the function (a real second set)? E.g. declare t at the top and assign it twice? The second assignment's value must be used... Hmm, the 2nd set must survive flow.

Hmm, what about this: the load's dest is the pseudo for t. If t is ALSO the dest of another load earlier (e.g. `t = something` earlier in the function) and that value is used → t's pseudo has 2 sets ✓ and the boost is killed for BOTH loads. But adding an assignment changes the code (extra load).

Hmm, unless the extra assignment is a value that's already loaded! E.g. if the function already loads p->unk20 somewhere else... Let me check: `((Unkstruct_80126B58 *)p)->unk20` appears once.

Hmm. What about `t` being used for something else?

OK, let me try the "compound assignment" idea on a DIFFERENT variable to see if the group order can be flipped: e.g. what if the call's a0 arg is `t` but t is a u16/s16? no.

Alternatively: what if the call is written as a call through a function pointer or with a cast, so the arg setup isn't recognized as a "USE argreg" group member? E.g. `((void (*)(s32, s32, s32))func_8001D0E8)(t, 0x140, 0xF0);` — hmm, that might change the group detection (the doc's "special pins: SCHED_GROUP_P: a call + its immediately-preceding USE argreg insns"). The USE argreg insns are the "use" of the arg registers before the call. A cast to a function pointer type doesn't change that.

Hmm, what about the *number* of arguments? no.

Let me try the simplest experiments:
V1: move the load earlier in the source: put `t = ((Unkstruct_80126B58 *)p)->unk20;` before the block of assignments? Hmm, the load is from p->unk20 and the stores are to p+0xE etc. — the compiler may not hoist it above the stores (they may alias).

Hmm, let me think about the "birth boost" once more: the load's dest (t) is single-set → the load is boosted → its priority = max_priority → in the group, it's placed LAST (after li a1) ✓ mine. If the boost were killed, the load's pri = 1 = li a1's pri → the LUID tie-break: the higher LUID placed later → the load has a lower LUID (it's earlier in the source: the load statement precedes the call statement, and li a1 is part of the call statement's expansion → the load's LUID < li a1's LUID) → the load is placed earlier ✓ TARGET.

So: kill the boost of the load. The load's dest = t's pseudo. We need 2 sets on t's pseudo.

What if t is declared as `register s32 t;`? Hmm, a register var without a pin — the census counts "register" as a lever (class C/D: "register" qualifier). The brief says no new levers. Hmm, but "register" without an asm pin is just a hint... The census tracks "volatile-in-pin" and register declarations ("declarations inside bodies" are class C). Hmm, risky.

What if t is assigned in two places with a real use? E.g.:

```
            s32 t;
            t = ((Unkstruct_80126B58 *)p)->unk20;
            func_8001D0E8(t, 0x140, 0xF0);
```
→ 1 set.

Hmm, what if the same value is loaded into a *different* variable and one of them is used? E.g.
```
            s32 t;
            s32 u;
            t = ((Unkstruct_80126B58 *)p)->unk20;
            u = t;
            func_8001D0E8(u, 0x140, 0xF0);
```
The copy u = t: gcc's cse would propagate (u is used once) → the copy disappears → same as before. Hmm, but wait: would it? cse propagates the copy into u's use → the call's arg becomes t's reg → the load is the a0 setup again. Same.

Hmm, what if u is used TWICE (so the copy survives)? E.g. `func_8001D0E8(u, 0x140, 0xF0);` and ... only one use.

OK, what about: the call's arg is `t` and t is ALSO used after the call (a real use). E.g. is t used later? No. But we could restructure: the value could be used twice if the call took it twice? No.

Hmm, hmm. What about giving the LOAD's dest a second set via a *different* variable that is loaded from the same address? Like:
```
t = p->unk20;
u = p->unk20;    /* the second load is CSE'd away */
```
no.

OK, let me consider: maybe the fix is not about the boost but about the group. What if the call is not a "call group" member because the load is not "immediately preceding"? What if we insert a statement between the load and the call that generates a *harmless* RTL insn? Options: an assignment to a variable that the compiler keeps but emits no code for? Hmm, an assignment of a constant to a dead local → gcc removes it.

What about `t = t + 0;`? Removed.

What about a "volatile" dummy? Adds a load.

Hmm, what about a function call that returns a value we ignore? Adds a call.

Hmm. What about the C0505 catalog: "loop shape"! A do-while(0) around the call:
```
            t = ((Unkstruct_80126B58 *)p)->unk20;
            do {
                func_8001D0E8(t, 0x140, 0xF0);
            } while (0);   /* !FAKE: do-while */
```
A do-while(0) creates a LOOP in the RTL → the call inside is in a loop body → the "immediately preceding" relation breaks (the load is outside the loop) → the load is not in the call group ✓. And the emitted code: the do-while(0) is optimized away (the loop is never entered) → the same instructions! Hmm, but gcc might add loop overhead (a branch). With `while (0)`, gcc 2.7 typically generates the body inline with no branch (it knows the condition is false) — but the RTL may have a loop structure that the branch/jump optimization removes. Risky but worth a try!

Note the worked example from T10 used exactly this trick ("do { r = p + i; } while (0);" — with a ref boost). And the brief explicitly allows do-while with the `// !FAKE: do-while` marker.

Let me try:
V1: wrap the call in do-while(0).
V2: wrap the load+call in do-while(0)? Hmm.

Let me try V1.

Also V3: keep the load inside and the call outside? no.

Let me generate V1 from base.c:
old:
```
            t = ((Unkstruct_80126B58 *)p)->unk20;
            func_8001D0E8(t, 0x140, 0xF0);
```
new:
```
            t = ((Unkstruct_80126B58 *)p)->unk20;
            do {
                func_8001D0E8(t, 0x140, 0xF0);
            } while (0);   /* !FAKE: do-while */
```
Let me do that with sed -z.
