---
ts: 2026-10-22T00:20:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Bzop0AspQ6mFtLLBGHS6
---
The target's structure (from 138):
```
138 lw v0,64(v0)      ; the 2nd store's load: *(u32*)(ot+0x40)
139 and v1,v1,a0      ; pv & 0xFF000000  (a0 = the constant)
140 and v0,v0,a3      ; X & 0xFFFFFF (a3 = 0xFFFFFF)
141 or v1,v1,v0
142 sw v1,0(s1)        ; the FIRST store: *(u32*)p = ...
143 lhu v1,0(a2)       ; the 2nd volatile bidx load
144 nop
145 sll v0,v1,0x2
...
157 lhu v0,0(a2)       ; the 3rd volatile bidx load
```
Interesting! So the FIRST store (sw v1,0(s1) at 142) comes AFTER the constant's use. And the 2nd store (sw v0,64(v1) at 156) is later.

So the target's schedule: [lw pv][lui mask][and][and][or][sw] — the constant's lui is at 137 (just before the and at 139) and the lw at 130 (early).

So in the target, the *first store* is at 142 and the lw pv at 130 — the load is early relative to the store. And the constant's lui is right before its consumer (139) = boosted (sunk to its consumer) ✓ my model.

In mine: the lui at 130 (early) and the lw at 137 (just before the and at 139) → the load is boosted.

Hmm OK. So: the load is boosted in mine, the constant in the target.

Now, KEY INSIGHT: what if the load's chain priority were LOWER than the constant's boosted priority? The load's chain pri is 2 (load latency 2). The constant's chain pri is 1, but boosted to max_priority. What IS max_priority? In gcc's sched.c, `max_priority` is a variable set to the priority of the launching insn (the insn whose successors were scheduled) — i.e., the priority of the *consumer* (the AND at 139, pri 2). So the boost sets the single-set def's priority to 2 (the consumer's priority).

So in the target: the constant's lui is boosted to pri 2 = the same as the load's chain pri 2 → TIE → the LUID tie-break decides: the higher LUID is picked first → placed last. The constant's lui has a higher LUID (it's later in the RTL) → placed last (137) ✓, and the load (lower LUID) placed at 130 ✓.

In mine: the load is boosted to pri 2 (its consumer's pri), the constant is NOT boosted (pri 1) → the load (pri 2) > the constant (pri 1) → the load is picked first → placed last (137) ✓, and the constant (pri 1) placed at 130 ✓.

So BOTH the load and the constant are single-set defs, but only ONE gets the boost? Why doesn't the constant get boosted in mine?

Because the boost is applied "on becoming ready" — an insn becomes ready when all its successors are scheduled. Both the load and the constant become ready when the AND is scheduled. Hmm, both should get the boost.

Hmm, unless: the boost is applied only to the insn that "launches" the ready group: in gcc's `schedule_insn`, when an insn's last successor is scheduled, the insn is launched with `adjust_priority(insn)` — each launched insn gets the boost if it's a birthing insn. So both the load and the constant would be boosted to pri 2.

Then in mine, the tie between the load and the constant (both pri 2, both boosted) → LUID: the higher LUID is picked first → placed last. If the constant has the higher LUID, the constant would be placed last (137) → the TARGET. But mine has the load last.

So the LUID order must be: the load has the higher LUID than the constant's lui. That means the constant's lui has a LOWER LUID — i.e. the constant's lui appears EARLIER in the RTL than the load!

Why? Because gcc's `flow`/cse might place the constant's definition early (rematerialization hoisting): the constant pseudo 0xFF000000 is rematerializable, and gcc's RTL might place its definition at the top of the bb (or in the "prologue" position). Hmm! But then the load's LUID > the constant's LUID → the load is picked first → placed last ✓ mine.

And in the target, the launder changed things so that the constant is boosted and the load is not (2 sets) → the constant is the only candidate → placed last ✓.

So the key difference remains: the load must not be a single-set def.

Hmm, so how do we get 2 sets on the load's dest pseudo?

IDEA!!! What if the load's dest pseudo is ALSO the dest of the *store*? I.e., what if the value loaded is stored back to the same place in a way that the target also has? Hmm.

IDEA 2: What if we make the loaded value's pseudo be SET by a *later* instruction that is a copy from a volatile source? no.

IDEA 3: What if the load is *split* into two loads (e.g. `pv = *(u32*)p;` → `pv = *(u32*)p;` used twice)? no.

IDEA 4: Use a *conditional* assignment to pv that creates a second SET:
```
if (cond) pv = 0;    /* extra insn */
```
no.

Hmm, what about this: the load's dest pseudo could get a 2nd set if the SAME pseudo is used as the dest of a later "reload" — e.g. `pv = *(u32 *)p;` and later `pv = *(u32 *)p;` again (two loads) → 2 sets, but 2 loads = extra insn. Unless the second load is dead → flow removes it.

Hmm, what if the 2nd load is in a later bb and its value is used? That changes the code.

OK, so for item 5, plain C can't kill the load's boost. BUT — maybe I can achieve the target's ORDER differently: what if the *pv load* is placed in a different position in the source, such that even when boosted it lands at 130?

The boosted load is placed "just before its consumer" — the consumer is the AND at 139. So it always lands at 137ish. To land at 130, the load's consumer must be at ~131. The consumer is the AND. Hmm.

What if the load's consumer were an earlier instruction? E.g. if the load's value were used by the `sll`/`addu` (the bidx*20 computation)? No.

Hmm, what if the pv load were moved to a position where its consumer is early? The value pv is used only in the first store's AND.

What if the first store came EARLIER in the source (before the bidx computation)? Then the AND would be earlier, and the load would sink to just before it (early!). Hmm! But the target's order is: [lui base][lhu bidx][lw pv][sll][addu][lui mask][and][and][or][sw]. The sll/addu (the bidx*20 computation) come BEFORE the mask's use. So the first store's expression is expanded after the bidx*20 computation. If the first store were moved earlier in the source (before the `ot = ...` line), the order would change: the sll/addu would come after the store's ANDs. Hmm, that changes the target's order (the sll/addu at 131-132 are before the ands at 139-140).

Hmm, but the sll/addu at 131-132 are part of the SECOND store's address computation (bidx*20*4?). Actually "sll v0,a0,0x2; addu v0,v0,a0" = bidx*4 + bidx = bidx*5?? Then "sll v0,v0,0x2" = *20. So that's the `*bidx * 20` computation — which is used by BOTH stores (the X address and the ot address). So it's shared and CSE'd; it appears once at 131-132.

In the target, the shared bidx*20 computation (131-132) comes BEFORE the first store's ANDs (139-140) and before the store (142). And the load pv (130) is before it.

So the target's schedule: the pv load, then the bidx*20 computation, then the first store's ANDs, then the store.

Since the first store's RHS includes the X address (which needs bidx*20), the store must come after the bidx*20 computation. ✓.

And the pv load is independent → it's placed at 130 (early, right after the lhu of bidx at 129).

Hmm interesting: the lhu (bidx) at 129 is a *volatile* load, which can't be CSE'd, so there are 3 lhu's (129, 143, 157). The first lhu at 129 is early.

So in the target: 125-127 = the address of D_800A651C (lui/addiu), 129 = lhu bidx (volatile), 130 = lw pv, 131-132 = sll/addu (bidx*5), 133-136 = ? (equal in both), 137 = lui mask, 138 = ? , 139-141 = ands/or, 142 = sw.

Hmm, so the pv load (130) is placed between the lhu (129) and the sll (131). Why there? Because the load is boosted (max pri = its consumer's pri) → placed as late as possible → just before its consumer. But its consumer (the AND at 139) is way later. Hmm, so it's not "just before its consumer".

Hmm, so the boost doesn't place it just before the consumer; it just raises the priority. OK whatever.

Let me now think about the priority numbers: the pv load's chain: lw→and→or→sw: pri = 2 (load) + 1 = ... The AND is at 139, the OR at 141, the SW at 142. The chain pri for the AND = max(pred pri + cost) = max(load's chain, constant's chain) + 1.

Backward scheduling: the tail is scheduled first. The order of placement: the SW (142) is placed first (it's the last), then the OR (141), then the ANDs (139,140), then their preds.

When the AND (139) is scheduled, its preds (the load, the constant's lui) become ready. Both are single-set defs → both boosted to the AND's priority (pri 2?).

Then the ready list: the load (pri 2, LUID_L) and the lui (pri 2, LUID_C). The tie-break: the highest LUID is picked first → placed last. In the target, the lui ends up at 137 (placed later than the load at 130) → so the lui has the higher LUID. In mine, the load ends up later → the load has the higher LUID.

So the LUIDs differ between mine and the target! The LUID = the RTL position. In mine, the load has a higher LUID than the constant's lui; in the target, the constant's lui has a higher LUID.

Why? Because in the target, the constant's lui is NOT at the top of the bb (it's at 137, right before its use) — its LUID is high (near the end of the bb's RTL). In mine, the constant's lui is at 130 (early) → low LUID.

Hmm, but LUIDs are assigned in RTL order (pre-sched), not in the final order. The final order reflects the schedule. The LUID is the source/RTL order.

Hmm, so in mine the constant's lui has a LOW LUID = it's early in the RTL. Why would the constant's def be early in the RTL? Because gcc materializes rematerializable constants at the START of the bb! Yes — gcc's RTL for a constant used in a bb: `gen_rtx_CONST` / the constant is put in a "constant pool" at the top of the bb? Hmm, in gcc 2.7 the constant pseudo is defined by an insn emitted at the point of expansion.

But in the target, the constant's lui is at 137 (late) → its LUID is high → it was defined late in the RTL. So in the target, the constant's def is NOT early in the RTL.

So the difference is in the RTL order of the constant's definition — which the launder (in a later bb) can't affect... unless the boost applies differently.

Ugh, I'm going too deep. Let me take the practical route: EXPERIMENTS.

Let me try a set of variants for item 5 and check the score. Cheap ideas:
(a) Move the first store's statement ORDER relative to the `ot = ...` line (both orders).
(b) Use a fresh local for the masked value.
(c) Split the second store's masked value.
(d) Swap the two mask uses' expression form: e.g. write the first mask as `(pv & 0xFF000000)` and the second as `(*(u32 *)(ot + 0x40) & 0xFF000000)` — same.

Hmm, (a) is interesting: the target's order has the lhu at 129, the lw at 130, the sll/addu at 131-132, then the lui at 137. If the first store came BEFORE the `ot = ...` line in the source (which it already does)...

Hmm, what about the ORDER of the first store vs the pv load? Currently: pv load, then the store. What if the store came first and the pv load second? Then the load's consumer (the AND in the store) is before the load → the load can't sink before its consumer → the load stays at its source position (after the store) → the order would be [store stuff][load] — different from the target.

Hmm.

OK, let me try yet another idea: what if the pv load is *hoisted* by making it feed something early? no.

TIME CHECK: I'm deep into item 5. Let me now consider the overall budget: 8 items. I should allocate ~20 min each and just do it. For items where the launder is a boost-killer, the answer may be WALL (the doc's own recipes for killing a boost are asm-based). But the moves.md shows launder MATCHes via "real 2nd set" — those were cse-type launders, not boost-type.

Let me classify each item's launder:
- Item 1 (func_801832A8): launder on vol — a scheduling barrier for the two division chains (the "re-tie" of two magic multiplies). The doc's §30 #3 re-tie. Plain C: probably a WALL.
- Item 2 (func_8018389C): the same pattern (vol) in the same TU → probably the same.
- Item 3 (func_8017DE84, ov_SC02_039): launder on s0 at 3237.
- Item 4 (func_80185380, ov_SC03_014): launders on v6 and p10 at 3172-3174 (with "memory" clobber) → those are barrier-ish (volatile + memory clobber).
- Item 5 (func_8018AA98): out-only launder killing a birth boost.
- Item 6 (func_80180054, ov_SC03_030): several launders (xa, xb with whitespace templates! and p).
- Item 7 (func_8017E780, ov_SC03_092): launder on t.
- Item 8 (func_80181CF4, ov_SC03_097): out-only launder killing a birth boost (same as item 5).

Since items 5 and 8 are the same pattern, and the "real 2nd set" recipe is in moves.md for similar cases (G09's func_80184174/80185690/801849AC/80181BA8: "launder->real 2nd set pv &= 0xFF000000 split (real 2nd set)"), let me check what those look like — maybe they're the same "out-only launder" case and the split DID work there. Let me look at one of them: src/ov_SC06_xxx? Let me find func_80184174 in src and see its launder and the win.

That would be a great template. Let me look.
