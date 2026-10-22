---
ts: 2026-10-22T10:11:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_hWeAYVyL9zD6Wxfkr91K
---
For v1: our order is [.. li v0,51; sb v0,39(a0); ...; addiu a1,s0,36] and the target is [.. addiu a1,s0,36; ... li v0,51; ... sb v0,39(a0)].

Let me get the full asm of both to see the exact context. Let me dump our candidate's asm and the target's asm for this function side by side.

The target (from the notes):
```
36: move a0,s1
37: addiu a1,s0,36
38: lui a2,0x0
39: addiu a2,a2,0
40: li v0,51
41: jal func_80128EA8
42: sb v0,39(a0)     (delay slot)
```
Ours (v1):
```
36: move a0,s1       (presumably)
37: li v0,51
38: sb v0,39(a0)
39: lui a2,0x0
40: addiu a2,a2,0
41: jal func_80128EA8
42: addiu a1,s0,36   (delay slot)
```
Hmm interesting: ours has "addiu a1,s0,36" in the delay slot and the store early.

So both have 63 insns; the difference is the ORDER of 4 insns: {addiu a1, li v0, sb v0} placement.

In the target: a1 setup (37) is early — right after "move a0,s1" (36); then lui/addiu a2 (38-39); then li v0 (40); jal (41); sb (42).
In ours: li v0 (37); sb (38); lui a2 (39); addiu a2 (40); jal (41); addiu a1 (42).

So in ours, the `addiu a1,s0,36` (the p argument = ent+0x24) is sunk into the delay slot, while the target has it early.

Why? Because in ours, the value `p = (s32)((u8 *)ent + 0x24)` is computed late (it's used only by the call) — the scheduler sinks it into the delay slot. In the target, the arg setup is at the top of the arm.

The launder forced q, p, e into registers before the asm, so their values were computed early.

Hmm, and the store: in the target the store is in the delay slot (after the call), in ours it's before the call (early). So the target's store was scheduled AFTER the call — meaning the store's value (0x33) was materialized ("li v0,51") before the call and the store itself was placed in the delay slot.

So in the target: the whole arm is "arg setup first, then the call, with the store in the delay slot". This is what you get when the *source order* is: store first? no...

Hmm, let's think: in the target, the store (a memory write to q->unk27) comes after the call. In our v1 (store before the call in the source), gcc scheduled it before the call. In our v2 (store after the call in the source), gcc scheduled it... let me see v2's asm: the diff shows ours has [39: lui a2? ...]. Hmm, v2's diff:
```
insert mine[37:37] target[37:38]:  --  | addiu a1,s0,36
insert mine[39:39] target[40:41]:  --  | li v0,51
delete mine[40:42] target[42:42]: addiu a1,s0,36 / li v0,51 | --
```
So in v2 ours = [36: move a0,s1; 37: lui a2; 38: addiu a2; 39: addiu a1,s0,36; 40: li v0,51; 41: jal; 42: sb v0,39(a0)]?

Hmm, that's close to the target! The target = [36: move a0,s1; 37: addiu a1,s0,36; 38: lui a2; 39: addiu a2; 40: li v0,51; 41: jal; 42: sb].

So in v2 the only difference is the position of "addiu a1,s0,36" (ours at 39, target at 37) — i.e., ours computes a1 AFTER the a2 setup, the target BEFORE.

Hmm, so v2 is very close: the target's order is a0, a1, a2 (the natural arg order) while ours is a0, a2, a1.

Why does ours put the a1 setup after the a2 setup? Because the "lui a2 / addiu a2" (the constant D_801817B0) is scheduled earlier (it's a constant materialization, which sched1 likes to hoist), while the a1 setup (ent+0x24) is sunk.

So the target's order (a1 before a2) means the a1 setup was NOT sunk. Why? Because in the target, the value p (=ent+0x24) was computed EARLY (before the call, at the top of the arm) — as it was laundered into a register before the asm.

So: to get the a1 setup early (not sunk into the delay slot), the value `ent + 0x24` must be computed early. In our source, `p = (s32)((u8 *)ent + 0x24);` is a statement in the else arm; the scheduler sank its use.

Hmm, so how do we make the scheduler hoist the a1 computation? Options:
- Compute p EARLIER in the source (e.g. before the `if`): but then the arm's structure changes (the value would be computed in the preheader → different asm).
- Use p in more places (more uses → higher priority?).
- Make p's value depend on something that forces early computation.

Hmm! Actually, the key: in the target, the arg setup `move a0,s1 / addiu a1,s0,36 / lui a2 / addiu a2` is at the TOP of the arm — that's the classic "call arg setup at the top of the block" that happens when the call is the LAST thing in the block and the scheduler hoists the arg setup... Hmm, or when the values are already in registers.

Hmm, what if the issue is that our `p` is a *pseudo* that gets its value late (the addiu is scheduled into the delay slot), while in the target the value was computed at the top.

What if we compute the address EARLIER in the source — e.g. assign p before the `if (*(s16 *)((u8 *)ent + 0x2E) != 0)`? That changes the code flow (p computed unconditionally) → the asm would have the addiu in the preheader ✗.

Hmm, what about assigning p right after `q = sub;`? It already is (p = ent+0x24 comes right after q = sub). The scheduler still sinks it.

Hmm, why does the scheduler sink the a1 setup into the delay slot? Because the delay slot is filled with the last instruction before the call, and sched2/reorg picks an instruction with no dependencies. In the target, the delay slot holds the store.

The difference: in the target, the delay slot holds "sb v0,39(a0)" (the store) while ours holds "addiu a1,s0,36".

Hmm! So maybe the fix is: make the store schedulable into the delay slot. In the target, the store is after the call in program order (since the delay slot executes after). In ours (v2, store after the call in the source), the store IS in the delay slot ✓ (v2's asm shows "sb v0,39(a0)" at 42 = the delay slot). And the a1 setup is at 39 instead of 37.

So for v2, we need "addiu a1,s0,36" to move from position 39 to 37 (before the lui a2).

What determines that? The scheduler's ordering of independent instructions. The lui a2 (constant materialization) has a "birth boost" (sched1 hoists constants). Hmm.

If the a1 computation were NOT independent — e.g. if it depended on the value in a1... hmm.

What if p's value were computed from a variable that's live earlier? E.g. `p = (s32)((u8 *)ent + 0x24)` where ent is $16 (pinned). The addiu depends on s0 (ent).

Hmm, what if the a1 setup were a separate statement whose value is also used elsewhere (e.g. the store)? Hmm.

Idea: what if we introduce a *second* use of p so that the addiu can't be sunk into the delay slot? E.g. p is also used... hmm, p is only used by the call.

Idea: what if the store's base were p instead of q? no.

Idea: what if the call's first arg were q (a0) and the store also through q (a0) — that's the case. The delay slot store needs a0 = q.

Hmm, what if we swap the order of the store and the call in the source AND make the store use a value that must be computed before the call (e.g. the constant 0x33 in v0) — that's v2 ✓ (the "li v0,51" is at 40 in the target and at 41 in ours — hmm, ours has li v0,51 at 41? The diff says "delete mine[40:42] target[42:42]: addiu a1,s0,36 / li v0,51" — so ours has [40: addiu a1,s0,36; 41: li v0,51] and the target has [40: li v0,51].

So ours: 36 move a0,s1; 37 lui a2; 38 addiu a2; 39 addiu a1,s0,36; 40 ??? hmm. Let me just dump our v2 asm to see exactly.

Let me do that.
