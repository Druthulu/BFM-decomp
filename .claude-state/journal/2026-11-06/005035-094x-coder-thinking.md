---
ts: 2026-11-06T07:50:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rf54M6XGrRlyuYCpcGIB
---
v29_twlocal score 3, 134 ins (2 extra). Not great. v26 score 7, 133 ins.

The base is 6. v5/v7 are 5. None 0.

Let me reconsider. Maybe the answer is a different real-C move entirely: change the `u32 w3c` variable to `s32`? Same. Or the `L.w3C` field type? The struct field `u32 w3C`. If we change the local variable type or the assignment order.

Wait — maybe the target's natural C does NOT have the `w3c` variable for the loaded value; instead it uses a named variable `w3C` local? Hmm.

Let me look at the problem from the register preference angle: the s5 preference for w3c comes from the load `lw s5,0(s5)`. If the load's base were not s5, the preference changes. In the target, the base IS s5. But maybe in the natural C, the load is `lw a0,0(s5)` because the value's pseudo was already assigned a0 by *local-alloc's qty ordering* before the copy preference applies.

The base w1: r79 is a GLOBAL allocno (dies in 2 places) with preference s5. In target, the natural C might make the value a LOCAL pseudo (dies in one place) if the variable is used once. The value is used once (stored to L.w3C). If it's a temp (not reused), it dies in one place → local-alloc. Local-alloc would assign it within the block, preferring s5 (copy sugg). Hmm, same.

Wait, but in v5_split, the loaded value w3c is used once (dies at L.w3C store) and got a0! So a once-used loaded value gets a0 (local-alloc, no s5 preference because... hmm). Let me check v5's .lreg for r79: r79 in 4. Why a0? Maybe because local-alloc's find_free_reg for the load's dest: the copy suggestion s5 comes from combine_regs only if the base dies in the insn AND the dest pseudo is tied... In v5, the load `lw a0,0(s5)` has s5 dying; the dest (w3c) is a local pseudo. combine_regs suggests s5. But local-alloc first tries qty_min_class (GR_REGS) with `just_try_suggested=0` — it uses find_free_reg with used=fixed_reg_set ∪ regs_live_at. At the load insn, s5 is live (source), so s5 is excluded → a0. Then it doesn't even use the suggestion. Wait, but in w1 (single variable), the global allocno r79 got s5 despite s5 being live at the load? Because global-alloc's liveness might treat the death differently.

Hmm, the difference: in w1, w3c is GLOBAL (dies in 2 places), so global-alloc assigns it and the s5 "preference" is a copy preference that global-alloc honors if s5 isn't conflicting. Global-alloc's conflict check might not consider s5 live at the load's death point (twicep dies exactly there), so no conflict → s5.

In v5, w3c (once-used) is LOCAL, and local-alloc excludes s5 because it's live at the load insn (regs_live_at). So a0.

So: to get a0 for the single variable, either make it local (used once) — impossible since it's reused for the pointer — or make it conflict with s5 globally.

OR: split into two variables where the pointer ALSO gets a0. In v5, the pointer w3d got v1 because it was born at insn 59 before w3c's death at 60. If we can make the pointer's birth after w3c's death, it reuses a0. The source order is `L.w3C = w3c; w3d = (u32)L.o1;` — the pointer is born after the store in source, but sched1 moved the addiu before the store (insn 59 vs 60). Why? sched1 schedules the addiu earlier because it's independent and the store has a delay. In the target, the store comes first. The store is `sw a0,60(sp)`; the addiu is `addiu a0,sp,16`. In target they're in source order (store then addiu). In v5 mine, addiu then store.

Hmm, the difference: in v5, the addiu writes v1 (a different reg), so it's independent and can be hoisted. In target, the addiu writes a0 (same as the store's source), creating a dependency (anti-dependence: store reads a0, addiu writes a0) that forces the store first. So it's circular: if the pointer gets a0, the order is forced; if it gets v1, it's hoisted.

So if I can make the pointer conflict with v1 and prefer a0... In target, the pointer reuses a0 because w3c (a0) dies at the store. Global-alloc for the pointer allocno: it should see a0 free after the store. But in v5, the pointer (w3d) was born BEFORE the store in RTL (sched1 hoisted), so it conflicts with a0.

To prevent the hoist, make the pointer's computation depend on the stored value or be after it. E.g., `w3d = (u32)L.o1;` is independent. If we write the pointer computation as part of the store's next statement with a dependency... The target's dependency is exactly the shared register.

Alternative: keep the single variable w3c but force it to be LOCAL by... hmm, if w3c is used twice (load + pointer), it dies in 2 places → global. What if we restructure so the loaded value and the pointer are the SAME value semantically? No.

What if we use a union or a pointer cast so w3c is used once? E.g.:
```
w3c = *(u32 *)twicep;
...
L.w3C = w3c;
gte_stsv((u16 *)(w3c = (u32)L.o1));  // ugly
```
No.

Hmm, let me reconsider the natural C. Maybe the original used a `u16 *dst` variable AND the loaded value directly:
```
L.w38 = *(u32 *)twicep;
...
L.w3C = *(u32 *)twicep;   // direct store, no var
...
dst = L.o1;
gte_stsv(dst);
```
But target's load at 40 and store at 59 separated → not direct.

Let me look at the actual original source style in this project: functions often use `s32 v0;` temps. The `w3c` variable is probably faithful. The keepalive was added for a reason: the original must have had twicep live longer. 

Maybe the original used `twicep` in the final call `func_800174DC()`? Let me check func_800174DC's signature. If it takes an argument and the source passes twicep... The target's final call has no a0 setup (jal with sh in delay). But if the argument were twicep and twicep were already in a0? twicep is in s5, not a0. So a move would be needed. No.

Maybe the original uses `oncep`/`twicep` in the q-block? `L.q28 = t | 0x680;` no.

Let me look at the P36 pack for this function to see the original lever rationale. The comment says "NEEDED DIFFERS (P36 rung B t8_tus2)". The pack might have a mechanism.md. Search .run/P36/agents for 800CB900.

Earlier grep for 800CB458 found nothing in agents. Let me search for the function in .run/P36 more broadly, e.g. in the census/ledger. The ledger.jsonl may have the site details with a "needed" reason. Let me grep.
