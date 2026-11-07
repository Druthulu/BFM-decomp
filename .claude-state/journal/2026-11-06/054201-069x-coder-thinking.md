---
ts: 2026-11-06T12:42:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9XFMcNTwXF7C63ckLgr0
---
The expert clarifies the PARTIAL semantics: if a row's kinds are not fully gone, it's a WALL, not a PARTIAL. My MATCH rows must have all kinds gone (which they do for item 1).

Now continue item 2. Time check: I'm ~12 min in. Let me try more variants for the sched order.

The hazard cost is per function unit; both insns are probably in the same unit (memory?). Hmm.

Let me approach differently: what if the store of v0 and the li are in *different basic blocks*? Then sched1 can't reorder them. A basic block boundary can be created by a do-while(0)? Apparently not (c4 didn't help).

What about the order in which the two statements are *emitted*: sched1 can only reorder within a block. The store `unkD8 = call(...)` and `ret = 7` are in the same block.

What if `ret = 7` is emitted in a different block? e.g.:

```
if (unk70 == 0x28) {
   ...
   unkD8 = call(...);
}
if (unk70 == 0x28) { ret = 7; goto STORE; }   // silly, duplicates the test
```
No.

Alternative: use the `do { } while (0)` trick around the store and the ret assignment separately? c4 put both inside. What if the ret assignment is inside its own do-while(0) AFTER the store statement? Let me try: 

```
unkD8 = call(...);
do { ret = 7; } while (0);
goto STORE;
```
Hmm, would that create a block boundary that sched1 respects? Probably not.

Different approach: change what the store's value is, so the hazard ordering differs. E.g. the target stores v0 = call result. What if the C stores the call result through a temp declared at block scope, so the store's source is a pseudo (not v0)? Then the store would be `sw r,216(s1)` where r is a pseudo — but the target has `sw v0,216(s1)`. With a pseudo, sched1's hazard computation might differ and flip the order! But then the store's source register differs (v0 vs the temp) — after allocation the temp might be v0 anyway (it's the call result, tied to v0 by the call). Yes! The call result is in v0; the temp r is copy-propagated to v0 by local-alloc (it's a call-return copy). So `sw r` becomes `sw v0` and the hazard calc might change.

I tried c3 with a temp — no change (score 55).

Hmm.

What about the ORDER of the two stores in the arm: target has unkCC store in the jal's delay slot then unkD8 after. Both from v0.

Let me think about "potential_hazard": it depends on the insn's unit and `unit_n_insns`. Both are single-insn.

Alternatively: maybe I can dodge the whole conflict by making ret's live range NOT include the store, e.g. by making the STORE use a *different* pseudo that is tied to ret... e.g.:

```
STORE:
    unk2 = ret;
    return ret;
```
Both uses are at STORE. The live range def(li)→STORE crosses the store insn if the li was scheduled before it.

Hmm, what if the arms do `goto STORE;` and STORE reads `ret`... the live range is what it is.

What if the C assigns ret in a way that its def is *after* the store by construction: i.e., the arm does `goto STORE` where STORE is:
```
STORE:
    unk2 = <expr>;
```
Hmm.

What if we make the store use the constant per arm and return ret? no.

Radical: what if the arms set `ret` and the store happens BEFORE the assignment via a different structure:
```
if (unk70 == 0x28) {
    ...
    unkD8 = call(...);
    goto STORE;
}
...
STORE:
    unk2 = ret;   /* ret assigned where? */
```
No.

Hmm, hold on. What about making ret's value *depend on the store's value* — like `ret = 7 + (unkD8 == 0);`? Fake, changes insns.

Let me look at the target's other arms: the 0x2A arm has no ret after a call store (unk20+4 = 0x80000000 then ret = 0x16). The 0x2B arm: unkCC = D_801EED54[...], unkD8 = call, ret = 0x19. Same shape.

The 0x2D arm: `func_8012A828(param_1, D_801ED34C); unk1C = 0x58; ret = 0x1D; goto STORE;` — here the last store before ret is `unk1C = 0x58` (a constant store, not v0). In the target: `li v1,0x58? ...`. Let me check the target's 0x2D arm and mine. If the ordering issue is only with v0 stores, the other arms would be fine.

Given the diff output earlier showed `li a0,N; j; sw v0` for several arms, they're all v0-adjacent.

Let me try yet another approach: what if `ret` is used (read) at the STORE *before* the def in the RTL? no.

Time to consider: maybe I should try making the arms' assignment `ret = (s32)(u16)7;`? no.

Practical alternative: try to change the sched order by making the li insn *heavier*: e.g. `ret = 7 + (s32)i70a * 0;`? That would add instructions.

Hmm, what about `ret = 7;` → `ret = 0x07;`... same.

Let me look at the problem from the "which register wins" angle again: maybe I can get ret to v0 not by fixing the conflict but by having the allocator prefer v0 despite the conflict? Impossible — a conflict is absolute.

Alternatively: could ret get v0 if the store insn didn't use v0 but another register? The store's value is the call result → always v0. Unless... the store is of a *different* value: e.g. `unkD8 = (s32)&D_801EE880`? No, the target stores the call result.

OK, wait. Let me re-examine: is the conflict really from this insn? `73 conflicts: 72 73 2 3 29` — conflicts with v0 and v1. Since v1 is used for the comparison constants (`li v0,41` is v0; hmm where's v1?). In the arm `li v1,0x58` maybe.

The conflict set is the union over all of ret's live ranges. If ANY arm has ret live across a v0 or v1 use, conflict. Since the li is scheduled before the v0 store in every arm, that's the cause.

Let me verify by checking one more arm's sched dump... it's the same pattern.

So the fix must flip the sched order in all arms. 

Think about what makes the target's order: the li writes v0 (hard reg) → WAR with the store → sched1 keeps the store first and puts the li in the jump's delay slot (via reorg later). Actually no: sched1 would still schedule the li (it's independent except for the WAR on v0). The WAR means the li can't execute before the store *completes*... In the target's stream the order is store, j, li (li in the delay slot after the j).

So with ret in v0, the dependency chain forces the order.

Lever-free way to create that dependency: make `ret`'s assignment depend on the call result! E.g.:

```
unkD8 = call(...);
ret = 7;  /* independent */
```

What if the C were:

```
if (unk70 == 0x28) {
    ...
    unkCC = &D_801EE880;
    unkD8 = call(param_1, 0x3000);
    ret = 7;
    goto STORE;
}
```
What if we instead write:

```
    ((Unkstruct *)param_1)->unkD8 = ((s32 (*)(s32,s32))func_80143994)(param_1, 0x3000);
    ret = 7 + ((Unkstruct *)param_1)->unkD8 * 0;
```
Fake and adds insns.

Hmm, what about the `(s16)` cast trick to change scheduling? no.

New thought: maybe use a `u16`/`s16` typed temp for the call result so the store's source is a pseudo with an extension... that changes insns.

Let me look at what the FIRST arm's sched dump shows in the *original* (pinned) build to confirm the order there. I can dump the src TU (with the pin). If the pinned version's sched dump shows the store before the li, that confirms the mechanism. That's 1 minute and confirms the theory. But even confirming doesn't give me the fix.

Alternative plan: accept that this item is a WALL? I've spent ~15 min. Let me try 3-4 more quick ideas, then decide.

Idea 1: make the value stored to unkD8 NOT v0 by storing through a temp declared *inside the arm* — tried (c3).

Idea 2: Reorder the arm's statements: `ret = 7;` placed BEFORE the unkCC store? Then ret is live across the call → saved reg. But wait — maybe not! If ret is only live from that point to STORE and the call is between... yes it crosses the call → needs a saved reg. Bad.

Idea 3: Since the arms jump to STORE, what if we make the `ret` assignment part of the STORE block per arm? i.e., the arms set a *different* variable, and STORE... no.

Idea 4: Change the call-result store to use a `s32 *` pointer store: `*(s32 *)((u8*)param_1 + 0xD8) = call(...);` — same insn.

Idea 5: What if the *order of the two statements* in the source is reversed (ret = 7 before the call) but ret is a *different* variable than the one returned... e.g.:

```
s32 rc;
...
rc = 7;                      /* before the call */
unkD8 = call(...);
ret = rc;
goto STORE;
```
That's more insns.

Idea 6: give the store a higher scheduling priority by making something depend on it. In the arm, after the store, `ret = 7` doesn't depend on it. But what if the arm's LAST statement were something that uses the stored value? Not in the target.

Hmm, hold on! Maybe look at the target's order again: `sw v0,216(s1); j; li v0,7`. The li is in the j's delay slot — reorg put it there. In the pre-reorg RTL, the order could be `sw; li; j` with the li moved into the delay slot by reorg. So the RTL order is store then li.

In mine: `li a0,7; j; sw v0,216` — the store is in the delay slot! So sched1 ordered li before store, and reorg put the store in the delay slot.

Since sched1 runs before allocation and the pin makes the li a hard-reg set... Let me test a hypothesis: is the sched order influenced by the pseudo's *register class/preferences* (reg_pref)? At sched1 time, `reg_preferred_class` isn't computed yet (regclass runs after sched1 per toplev: regclass is called right before local_alloc, after sched1). So sched1 sees pure RTL.

In pure RTL, `(set (reg/v:SI 73) (const_int 7))` vs `(set (mem/s:SI ...) (reg:SI 2 v0))`. The hazard: both are single insns. The store's potential_hazard... For MIPS, the memory unit's blockage is maybe 1-2. Both insns are in the same unit? The li is an ALU insn, the store is memory. Different units! potential_hazard returns a cost per unit; the "best" (largest) wins.

The printed message says insn 124 (the store) has a greater potential hazard → it's moved to the front (of the ready list). And the final order has the li first. So "front of the ready list" = scheduled LAST?! 

Looking at the ready list prints: "ready list at T-2: 124 (1) 127 (1), now 127 124". Before the hazard move the list is [124, 127]; after moving best (124) to front... "now 127 124"?? That doesn't match either.

Unless `ready[]` is a stack: ready[0] is the bottom, and the scheduler pops from the end (n_ready-1). "now 127 124" → the last is 124 → popped first → 124 scheduled first. But the final stream has 127 first...

I'm going in circles. Let me just check the pinned version's sched dump to see the difference. Actually, better: let me check whether in the pinned build the RTL order is store-then-li (which would confirm the WAR theory).

Time: ~05:45. Let me do this one check and then decide. Actually, let me instead try the most promising practical idea: make `ret` be assigned *before* the call result store but keep it out of the call's live range by making the assignment in the SAME statement as the store:

```
((Unkstruct *)param_1)->unkD8 = ((s32 (*)(s32,s32))func_80143994)(param_1, 0x3000);
```
vs
```
ret = 7;
```
What if instead: `((Unkstruct *)param_1)->unkD8 = (ret = 7, ((s32 (*)(s32,s32))func_80143994)(param_1, 0x3000));`? Then ret = 7 is evaluated before the call → live across the call → bad.

What about: `((Unkstruct *)param_1)->unkD8 = ((s32 (*)(s32,s32))func_80143994)(param_1, 0x3000), ret = 7;`? A comma expression: evaluates the call+store, then ret = 7. The RTL order is the same but the *statement* structure changes (single statement). Sched sees the same insns.

Hmm.

OK, completely different idea: what if the ORDER of the two v0 stores changes: put the `unkCC` store AFTER the call? no, target has it in the delay slot.

Let me try the "double statement with a do-while around only the ret assignment" (idea from C0535, where the block split affects scheduling). c4 wrapped both; let me wrap only `ret = 7;`:

```
unkD8 = call(...);
do { ret = 7; } while (0);  // !FAKE: do-while
goto STORE;
```
Cheap to test. Also try wrapping only the store.

And another: make the li's value come from a variable, e.g. `ret = N;` where N is a `const` global? no.

Let me batch: c5 (do-while around ret only), c6 (do-while around the unkD8 store only).
