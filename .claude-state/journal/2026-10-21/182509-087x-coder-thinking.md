---
ts: 2026-10-22T00:25:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_AT03ZTxy2tN2A4MWpfJP
---
Base for item 4: score 39, mine 110 vs target 111.

The target:
```
26 lw v0,108(s1)      ; o = param_1->unk6C
28 lhu v0,6(v0)       ; v6 = o->unk6
29 lui v1,0x0         ; p10 = &D_80190048
30 addiu v1,v1,0
31 sh v0,0(v1)        ; *p10 = v6
32 lw v0,108(s1)      ; o = param_1->unk6C (again)
```
Mine:
```
26 lw a1,108(s1)
28 lhu v1,6(a1)       ; v6
29 lw a1,108(s1)     ; the second o load moved up!
30 (?)
31 lhu v0,10(a1)
32 lui at,0x0
33 sh v1,0(at)
```
So in the target, the v6 load (28) is immediately followed by the p10 materialization (29-30) and the store (31) — i.e. the store `*p10 = v6` happens right after the load, and the *second* `o = param_1->unk6C` load (32) comes after.

In mine, the second o load (29) is hoisted before the store, and the v6 load's register is v1 (not v0).

So the differences: (a) the order of the two `o` loads, (b) the register of v6 (v1 vs v0), (c) the p10 materialization (lui at vs lui v1).

Hmm, the "memory" clobber in the launder prevents the compiler from moving the loads across the re-ties. Without them, the second o load is hoisted up (it's a load from the same address — the compiler CSE'd/hoisted it since there's no intervening store... hmm, actually the store `*p10 = v6` writes to D_80190048 which is a different address than param_1->unk6C, so the load can be hoisted ✓).

In the target, the store comes BEFORE the second load → the load of unk6C is after the store. Since the store is to a different address, the load could still be hoisted — unless the launder's "memory" clobber prevents it!

So the v6/p10 launders with the "memory" clobber act as barriers for memory reordering. To reproduce in plain C: we need the load of param_1->unk6C (the second one) to stay after the store. Hmm, in plain C the compiler will hoist it (it's a redundant load of the same address; gcc might CSE the two loads into one! In the target there are 2 loads (26 and 32) — so gcc did NOT CSE them (the launder's memory clobber prevents it).

Without the launder: gcc hoists/CSEs the second load to the first one (1 load) → 110 ins vs 111 ✓ (mine has 1 fewer insn).

So the fix: prevent the CSE of the two loads of param_1->unk6C. In plain C: make the two loads syntactically different so CSE can't merge them? E.g.:
- o = ((Unkstruct_80185380 *)param_1)->unk6C;
- o = CAST_ALIAS(s32, param_1, 0x6C);   ← the source already uses a different spelling for the second one!

Look at the source:
```
            o = ((Unkstruct_80185380 *)param_1)->unk6C;
            v6 = ((Unkstruct_80185380_2 *)o)->unk6;
            [launder v6]
            p10 = &D_80190048;
            [launder p10]
            *p10 = v6;

            o = CAST_ALIAS(s32, param_1, 0x6C);
            D_8019004A = ((Unkstruct_80185380_2 *)o)->unkA - 0x40;
```
So the second load is spelled differently (CAST_ALIAS) but CSE still merged them (same address).

To prevent the CSE, we could make the two loads different in a way gcc can't unify... e.g. use a volatile pointer for one of them? That would be a "barrier" lever.

Hmm, alternatively: since gcc hoisted the second load BEFORE the store, and the target has it after — what if we reorder the source so the second o load is used earlier? Hmm, the order in the target is fixed by the code.

Hmm. What if the store `*p10 = v6` is moved later in the source? The target's order: [load o][load v6][lui/addiu p10][sh][load o][...]. If in the source the store came after the second o load, then the hoisting wouldn't matter... but the target has the store BEFORE the second load.

Hmm, so we need the store to be scheduled before the second load, and the second load not hoisted above the store. The hoisting is prevented by the memory clobber.

Plain C alternative: make the second load depend on the store! E.g. if the second `o` load were after a use of the stored value... Hmm: `D_8019004A = ((Unkstruct_80185380_2 *)o)->unkA - 0x40;` — the second o load feeds this. And the first store writes to D_80190048. If the second o load were made dependent on the stored value (e.g. `o = ...; o = o + 0*(*(s32*)p10)`? no, silly).

Hmm, what if the source order is changed so that the store is the LAST thing in the block? Then the second o load (earlier in the source) would be hoisted... no wait: the target has the store before the second load. If the source had the store last, the compiler would put the load first (source order) → the opposite of the target.

Hmm, the target's order (store before the second load) is a *scheduling* outcome: the store was boosted (single-set? no...).

Hmm, let me think: the launder's memory clobber creates a scheduling barrier in gcc (asm with "memory" clobber = a barrier for memory ops) → the load can't move above the asm → the load stays after the store.

Without the barrier, the load is hoisted (it's a "ready" insn with a higher priority? or CSE'd).

To reproduce: the second load must not be hoistable above the store. Since the store is to a different address, gcc hoists the load freely. UNLESS the load is *dependent* on the store: e.g. if the compiler can't prove the store doesn't alias the load's address! `*p10 = v6` where p10 = &D_80190048 (a global) and the load is `param_1->unk6C` (a pointer deref) — gcc can't prove they don't alias (param_1 could point to D_80190048!) → so the load CANNOT be hoisted above the store! But gcc DID hoist it in my base.c. Hmm, because the hoisting happened *before* the store in the source order anyway?

Wait, in the source, the second o load is AFTER the store. So gcc hoisted it above the store (an anti-dependency violation) — that would be a bug unless gcc proved no aliasing. Hmm, gcc's alias analysis: D_80190048 is a global (a known address) and param_1 is a pointer → they may alias → gcc can't move the load above the store. But my base.c shows the load at 29 (before the store at 33) — hmm, wait, let me re-read:

mine:
```
26 lw a1,108(s1)      ; o = param_1->unk6C
28 lhu v1,6(a1)       ; v6 = o->unk6
29 lw a1,108(s1)      ; o = param_1->unk6C (2nd)
31 lhu v0,10(a1)      ; ??? hmm, unkA is at offset 0xA → lhu v0,10(a1) ✓
32 lui at,0x0
33 sh v1,0(at)        ; *p10 = v6
```
So mine: the 2nd o load (29) is before the store (33) — hoisted above the store. And the "lhu v0,10(a1)" (the unkA load, 31) is also before the store.

In the target:
```
26 lw v0,108(s1)
28 lhu v0,6(v0)      ; v6
29 lui v1,0x0
30 addiu v1,v1,0
31 sh v0,0(v1)       ; the store
32 lw v0,108(s1)     ; the 2nd o load
33 lhu v0,10(v0)     ; the unkA load
34 addiu v0,v0,-64
```
So in the target, the 2nd o load and the unkA load are AFTER the store.

So the target's store is scheduled EARLY (right after the v6 load) and the subsequent loads after it. In mine, the store is scheduled LAST (after the other loads).

That's a scheduling difference: the store's position. In the target, the store is at 31 (right after its operands are ready: v6 loaded at 28, p10 at 29-30) → the store is at its "source position" (the source order is: v6 load, p10, store, then the o load) ✓. In mine, the store is delayed to 33 (after the other loads) → the store was SANK.

Why would the store sink? The "single-set def sinks to its consumer" boost applies to defs, not stores. Hmm, but a store is also an insn with a priority. The store's chain: the store depends on v6 (loaded) → pri 2; the other loads (o, unkA) also pri 2.

Hmm, the boost: the store is not a SET (it's a MEM) → no boost. The loads are SETs (single-set) → boosted → placed late. So the loads (o, unkA) get boosted → placed late → the store (not boosted) placed earlier ✓ = the target. But in mine the loads are EARLY and the store is LATE.

So in mine, the loads are NOT boosted. Why? Because their dest pseudos have 2 sets? Hmm: `o` is assigned twice (in both spellings) → o's pseudo has 2 sets → no boost → o's load is not boosted → it stays at its source position (early) ✓ mine. And the store... hmm, the store should be at its source position (after the p10 materialization) → but in mine it's at 33 (after the loads).

Hmm, and in the target, the o load (32) is AFTER the store — the opposite.

So in the target, the o load IS boosted (single-set) → sunk to its consumer (the unkA load at 33) → after the store ✓. And in mine, the o load is not boosted (2 sets of o's pseudo) → stays early.

AH, so the difference: in the target, the two `o` loads are NOT CSE'd and each has its own dest pseudo (1 set each) → boosted → sunk. In mine, gcc CSE'd them (or merged the pseudos) → 1 load.

Wait, in mine there are 2 loads (26 and 29) of the same address, so no CSE, but the *dest* pseudo: the first load's dest is o's pseudo (2 sets: the two assignments) → hmm, the second load's dest is also o's pseudo → so o's pseudo has 2 sets → the loads are not boosted → they stay at their source positions.

In the target, the loads' dests are different pseudos? Hmm, in the target, the 2nd load (32) writes v0 and the 1st (26) writes v0 too. Hmm.

OK, whatever the mechanism: the key is that the launder's memory clobber prevents the two loads from being CSE'd/unified and forces the store to be scheduled before the second load.

Plain-C alternative to prevent the CSE of the two loads of param_1->unk6C: make them different types or different spellings that gcc can't merge. E.g., the first as `((Unkstruct_80185380 *)param_1)->unk6C` and the second as `CAST_ALIAS(s32, param_1, 0x6C)` — gcc merged them anyway (both are the same address, and the cast is a no-op).

What if the second is `*(s32 *)((u8 *)param_1 + 0x6C)`? Same address → merged.

Hmm, what if the second load is *volatile*? e.g. `o = *(volatile s32 *)((u8 *)param_1 + 0x6C);` → a volatile load can't be CSE'd or hoisted ✓ and it emits the same "lw" instruction ✓. But is a volatile load a "new lever"? It's a "barrier"-ish construct. The lever census's AB_KINDS doesn't include volatile, but the rules mention "a byte-needed `volatile`" as class C/D. The brief says "no new lever of any kind" — a volatile load is arguably a new lever (it constrains the scheduler).

Risky. Hmm.

Alternatively: can we make the second o load NOT redundant by using the *value* differently? E.g. in the target, the second load is at 32 and the unkA load at 33 — both after the store.

Hmm, what if the source order were changed so that the store comes last in the source? Then the compiler would... hmm, the target's order has the store early, which is NOT the source order (the store is before the second o load in the source, so it IS the source order!). Hmm: source order = v6 load, p10, store, o load, unkA load, ... → the target's order = v6 load, p10, store, o load, unkA ✓ EXACTLY the source order! And mine = v6 load, o load, unkA load, p10, store → NOT the source order (the store was sunk past the loads).

So in the target, everything is in source order; in mine, the store sank below the other loads.

Why did the store sink in mine? Because the store's priority: the store depends on v6 (a load, latency 2) → pri 2; the o load (also a load) → pri 2... hmm, equal. And the LUID tie-break: among equal priorities, the one with the higher LUID is placed LAST. The o load (later in the source) has a higher LUID → placed later. Hmm, but that would put the o load AFTER the store, not before.

Hmm, mine has: o load (29), unkA load (31), p10 (32-33), store (33). So the p10 materialization and the store are LAST. The store's operands: v6 (loaded at 28) and p10 (materialized at 32). Since the store depends on p10's materialization (lui/addiu) — and p10's pseudo is single-set → boosted → sunk to its consumer (the store) → so p10's materialization sinks to just before the store ✓ (mine: 32-33 right before the store at 33). And the store is after p10's materialization.

In the target, p10's materialization (29-30) is right before the store (31) too! ✓ Same. And the o load (32) and unkA load (33) are AFTER the store in the target, but BEFORE in mine.

So the difference is just where the o/unkA loads go: target = after the store; mine = before.

In mine, the o load is at its source position? No! The source has the o load AFTER the store. So in mine the o load was HOISTED above the store. And the unkA load too.

Why can they be hoisted? Because the store (to D_80190048, a global) can't alias the load (param_1->unk6C)? gcc's alias analysis: `*p10 = v6` where p10 = &D_80190048 → a known global address; the load is from param_1 (a pointer) → they MAY alias → gcc can't hoist the load above the store.

Hmm, but gcc DID hoist it. Because p10 is a *variable* (u16 *p10) assigned &D_80190048 — gcc's alias analysis may lose track (the pointer's value is known but the analysis may be conservative in the other direction). Hmm.

Hmm, so how do I prevent the hoisting in plain C? The load must be "dependent" on the store, or the store must be volatile, or the load must be volatile.

Hmm! What if the store's address is computed through a pointer that gcc can't resolve (e.g. p10 is a variable that gcc doesn't track)? It already is a variable... but gcc constant-propagated it.

What if p10 is declared as `u16 *p10 = &D_80190048;` — gcc's points-to analysis would know it points to the global → the load from param_1 might alias it → gcc should NOT hoist. But it did hoist. So gcc's alias analysis in 2.7 is weak: it may treat the store as "may alias" — hmm, if it may alias, it can't hoist.

Hmm, maybe the hoisting isn't a hoist but a *scheduling* decision: the loads are boosted (single-set dest) → placed as late as possible → hmm, "late" = just before their consumer. The o load's consumer is the unkA load (33 in mine). Hmm, in mine the o load (29) and unkA (31) are adjacent ✓ — consistent with "the o load sinks to just before its consumer (the unkA load)"! And the unkA load's consumer is the "addiu v0,v0,-64" (34) → in mine, the unkA load is at 31 and the addiu at... hmm, mine[34] = "addiu v0,v0,-64"? The diff showed mine[31:34] vs target[34:48]: mine 31 lhu v0,10(a1), 32 lui at,0x0, 33 sh v1,0(at) | target 34 lhu v0,10(v0), 35 nop, 36 addiu v0,v0,-64.

So in mine, the unkA load (31) is NOT right before its consumer (the addiu) — the p10 materialization and the store are in between (32-33). Hmm, so it's not "just before the consumer".

OK, I need to stop analyzing and start experimenting. The key question for item 4: can plain C keep the second o load (and the unkA load) after the store?

Options:
(a) Reorder the source: put the `o = ...` load and its use AFTER... it already is.
(b) Make the store's address opaque so gcc thinks it may alias: e.g. store through a pointer that gcc can't resolve: `*(u16 *)p10 = v6;` where p10 = &D_80190048 — hmm.

Hmm! What if we make the store's value depend on the second o load? No, that changes the order.

(c) What if the second o load is spelled as a *different* address expression that gcc can't prove equal → then it can't be hoisted above the store (it would be a different address, so hoisting is fine anyway...). Hmm, no: hoisting above the store is only blocked by potential aliasing.

Hmm, so what blocked it in the target? The "memory" clobber of the asm = a full memory barrier ✓.

So plain C can't block it... unless the store's address is unknown to gcc (then it may alias anything → the load can't be hoisted). Currently p10 = &D_80190048 → gcc knows the store's address exactly → it can then prove the load (from param_1) doesn't alias? No — param_1 is unknown, so the load MAY alias the global. Hmm, but gcc 2.7's alias analysis might treat the store to a global as "may alias" a load through a pointer...

Ugh, but empirically gcc hoisted it.

What if we make p10's value opaque so gcc can't tell where the store goes? E.g. p10 = &D_80190048 could be replaced by a value that gcc can't trace but which is the same at runtime: e.g. `p10 = (u16 *)&D_80190048;` (the same) or via a function call (no).

Hmm, what about: the store could be written as `*p10 = v6;` where p10 is a *volatile* pointer? `volatile u16 *p10` → the store is volatile → it can't be reordered with the loads ✓ and the emitted instruction is the same "sh" ✓. But that's a new lever (volatile).

Hmm. But hold on: is the emitted code identical with a volatile store? A volatile store is not eliminated/reordered — the emitted "sh v0,0(v1)" is the same ✓.

But the constraint "no new lever of any kind" — a volatile store is arguably a "barrier" lever (it prevents reordering). The lever census might classify `volatile` as... let me check the census: AB_KINDS = {pin, barrier, launder, keepalive, instruction, gte-lever, asm-body}. A volatile store isn't in the list; the census's "sites" are asm-based levers. Hmm, but the rules mention "a byte-needed `volatile`" as a class C/D site — meaning the census tracks volatile uses! Let me check lever_census.py for "volatile".

If the census tracks volatile, then adding a volatile would be a new lever site → not allowed. Let me check quickly.

Given the time, let me check the census's site kinds.
