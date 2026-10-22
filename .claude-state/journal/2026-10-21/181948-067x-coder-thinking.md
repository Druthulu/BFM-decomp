---
ts: 2026-10-22T00:19:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_GltVA2bOjDShbzGDYyGj
---
base5 (launder removed) = 11, same as V1 (split) = 11. So the split changed nothing.

So for item 5, removing the launder leaves 11 register-transposition mismatches. The order (lui/lw) also differs? Let me look at the base5 diff in full to see the order.

From the V1 diff: mine[130] = lui a2,0xff00 and mine[137] = lw v1,0(s1); target[130] = lw v1,0(s1), target[137] = lui a0,0xff00.

So the ORDER differs (lui/lw swapped) AND the registers differ.

To fix: I need the lw early and the constant late, and the registers a2/a0 as in the target.

Since the boost is the mechanism and the launder killed the load's boost...

Hmm, hold on! Let me reconsider: maybe the boost killed by the launder is not the load's but the CONSTANT's! I.e., the launder ADDS a boost? No...

Let me think about the two boosted candidates: the load (pri 2 chain) and the constant (pri 1 chain). In the target: the constant is LATE (137) → the constant was boosted (max pri) and placed last. The load is at 130 (early) → the load was NOT boosted (pri 2) and placed before the constant (max pri > 2).

In mine: the load is LATE (137) → the load was boosted (max pri) and placed last. The constant is early (130) → not boosted (pri 1).

Both cases: exactly ONE of them got the boost. In the target, the constant; in mine, the load. Since the load is in an earlier bb (before the call) and the constant's use is also before the call (the first store) — hmm, both in the same bb? The pv load and the first store are both before the call to func_80016638 → same bb.

So within one bb, both are candidates; the boost went to the load in mine and to the constant in the target. What distinguishes them? The load's dest pseudo has 2 sets in the target (launder) → not a candidate → the constant wins.

In mine, both are candidates (1 set each). The load won → the load was placed last (max pri). Why did the load win over the constant? Both would be max pri; the tie-break is LUID → the highest LUID is picked first → placed last. The load has a LOWER LUID (earlier in the RTL) than the constant's lui? Hmm, if so, the constant (higher LUID) would be picked first → placed last → the constant would be LATE. But in mine the load is late. So the load has the higher LUID?

The constant's lui: where is it in the RTL? The constant pseudo is created by expand at the point of the AND (in the first store's RHS). But the RTL order of the *first store's* expression expansion vs the pv load statement: the pv load statement comes first in the source → its RTL insn has a lower LUID.

Hmm, but cse/flow may reorder: the constant's lui might be placed early in the RTL (at the top of the bb) by flow (as a "rematerializable" constant hoisted to the bb start) → giving it a lower LUID! Hmm.

Whatever. The empirical fact: in mine the load is boosted, in the target the constant is.

Now: how to make the constant win in plain C? Make the LOAD not a candidate: its dest must have 2 sets. The load's dest = a temp (the loaded value). To give it 2 sets, the temp must be SET twice. Since the load's value is used once (by the AND), gcc's flow will...

IDEA: use the loaded value TWICE in a way that requires the same temp:
```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (X & 0xFFFFFF);
```
→ what if the AND's result is stored back into pv (V1) — in-place in the RTL? gcc: `pv = pv & 0xFF000000` → the AND's dest is a new pseudo P2, and pv's pseudo P1 is read. Then flow: the SET to P1 (from the load) is fine, P2 is used by the OR.

To force the AND to write into P1 (the load's temp), we'd need... hmm, gcc's "combine"/"cse" would rewrite `P2 = P1 & C` to be in-place if P1 is dead after: gcc's cse does "make_regs_eqv" but not in-place rewriting of the AND. However, gcc's RTL generation for a variable assignment `pv = expr` where pv's pseudo is P1: the RHS is computed into P2 and then `SET(P1, P2)`. cse would then propagate P2 into P1's uses and delete the copy → the AND's dest stays P2 (1 set), and P1 (the load's dest) has 1 set.

So the load's temp always has 1 set. UNLESS the load writes directly into a pseudo that is also written elsewhere.

What if the loaded value is assigned to a variable that is LATER assigned again, with the later assignment's value used? I.e., we need a 2nd SET of the same pseudo that survives. The later assignment `pv = X` would be SET(P1, ...) — but cse/flow would propagate X into pv's uses and delete the SET... unless pv's uses are in a place where the copy can't be folded.

Hmm, this is the "t5/t6 proof" territory: plain C 2nd assignments don't survive.

Hmm, BUT: what if the 2nd set is a STORE to memory of the loaded value? Like:
```
pv = *(u32 *)p;
*(u32 *)p = ...;
```
The store's value is the OR, not pv.

What if we restructure so that the store writes pv's masked value and the OR is done differently? Hmm.

What about: make the load's value be stored to memory TWICE? No, the target has one store.

OK, alternative approach for item 5: attack the register transposition instead! The residual is 11 register mismatches: a0↔a2 and v1↔a0. Note the target uses a0 for the bidx result and a2 for the base; mine uses a0 for the base and v1 for the bidx.

Hmm, what if the *order* difference (lui/lw) is the root cause of the register difference? If the lw were early (as in the target), $3 (v1) would be occupied from 130 on, so the bidx result couldn't use v1 → it'd use a0 → and the base would get a2. So fixing the ORDER would likely fix the registers too.

So the whole thing hinges on the order = the boost.

Hmm, let me think about "how to make the constant win the boost" differently: what if the constant is NOT a single-set def? E.g. if the mask were materialized twice (2 sets) — then the constant wouldn't be boosted, and the load would be boosted → mine. We want the opposite.

What if the load's dest had 2 sets by loading into a variable that is ALSO assigned by a *later* statement in the same bb whose value is used? E.g.:

```
    pv = *(u32 *)p;      /* SET(P1) */
    ...
    pv = pv & 0xFF000000;   /* SET(P1) again? */
```
For the 2nd SET to survive, the value of pv after the 2nd assignment must be used. It is (in the store). But cse propagates: the store uses the AND's result P2; the SET(P1, P2) is dead → removed. So P1 has 1 set (the load).

UNLESS the store's value is pv itself (so the store reads P1 directly):
```
    pv = *(u32 *)p;
    pv = pv & 0xFF000000;
    *(u32 *)p = pv | (X & 0xFFFFFF);
```
The store reads pv → cse propagates P2 into the store's expression → the SET(P1,P2) becomes dead → removed. Same.

Hmm, what if the store reads pv AND the value is used in a way that prevents propagation: e.g. `*(u32 *)p = pv | ...` where pv is a *volatile* variable → then the assignment to pv is a real memory write (volatile) → the load/store to memory → completely different code. NO.

What about making pv a *global*? A global's pseudo can't be propagated away... but a global would be a memory access. NO.

OK. So killing the load's boost in plain C seems impossible. What about the OTHER direction: make the constant's chain priority HIGHER than the load's, so the constant is placed later even without a boost? The constant's chain: lui→and→or→store (pri 1). The load's chain: lw→and→or→store (pri 2). The difference comes from the load's latency (2) vs ALU (1). "Priorities can only be RAISED by C edits, never lowered."

To raise the constant's chain priority above 2, the constant's chain would need a load in it. E.g. if the mask constant came from a load: `mask = *(u32*)&some_global`? That changes the code (extra load + the constant value would need to be in memory). NO.

Hmm, so item 5 might be a WALL (tag: sched1-birth-boost).

Hmm, wait. But hold on! What if the *source order* is different: what if the pv load statement came AFTER the first store in the original source? No...

Let me reconsider: maybe the target's order can be reached by making the two chains' priorities EQUAL. The load's chain pri 2 (load latency). The constant's chain pri 1. If the constant's chain also had a load... hmm.

What if the ORDER of the two mask uses is swapped: i.e. the second store's mask comes first? Not possible (the second store depends on ot).

Hmm, what if we could make the pv load NOT feed the AND directly, but feed it through something that lowers its priority? No, priorities can't be lowered.

What if the pv load is moved into a LATER bb? E.g. if the pv load were after the call to func_80016638 — no, semantics.

OK, alternative: what if the *first store* is moved to a later bb (after the call)? Then the pv load (in the earlier bb) and the constant (in the later bb) — the bb order would put the load first, and within the later bb the constant is boosted (single-set) → placed late. Hmm! That might work: the target's order is [lw pv][lui mask][and] — but the target has the lw at 130 and the lui at 137, with the and at 139, and the store... where's the first store? Let me look at the target's instructions 130-160 to see the store positions.

Let me dump the target's 120-175 region.

Hmm, I realize the first store `*(u32 *)p = ...` — the target's instructions around 140-160. Let me dump.

Let me do that now — I need the full picture.
