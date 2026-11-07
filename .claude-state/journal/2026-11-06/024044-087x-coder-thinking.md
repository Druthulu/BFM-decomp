---
ts: 2026-11-06T09:40:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PtPISwo7x8XTqMBhrVGI
---
All 2. The copy hoist is stubborn.

Let me think about the sched1 decision once more: in win, at T-14 the ready list has [97 (copy), 86 (store)] and it picks 97 first. Why? Because "insn 86 has a greater potential hazard". In sched.c, the priority comparison: `rank` uses `INSN_PRIORITY` and hazard. Let me look at the rank function: it prefers insns that are not stores (avoid scheduling a store early) and prefers... The store gets delayed.

Could we make the store *not* a store in the scheduler's eyes? No.

Could we give the copy a lower priority so the store goes first? The copy's priority is 1; the store's priority is 1. The tie-break: "insn 86 has a greater potential hazard" → the store is delayed. Hmm, so the scheduler *wants* to put the store last. In orig, the store was first because the asm blocked everything.

So in the original C, the store must have been forced first by a barrier. The most plausible real-C barrier: another function call or a volatile asm. But the target has neither between them.

Hmm wait — unless the original C had the store *before* the RMW in a different basic block? No.

Wait, maybe the original C's store came *first* because of a real dependency: what if the store's value or address depended on something computed in the RMW? E.g., if the store were `*(u16 *)(s0 + 0x188) = (u16)(*(u32 *)(s0 + 0x44) & 0);`? Identity launder.

What if the original C had the two statements in the opposite order (RMW then store), and sched1 (which delays stores) moved the store... no, sched1 delays stores, so a store at the top stays late; the RMW's store is also a store.

Let me test: RMW-then-store gave t3 = 2. What was t3's insn order? Let me look: t3's diff showed the same (store at 40 via a0). So no.

What if the store is *after* the call (source) — sched1 can't move it above the call → the final order would have the store after the call → not the target.

Hmm, what if the RMW's *load* comes before the store and the RMW's *store* after the call? That's the target's delay-slot arrangement, but source-level it's one statement.

Let me look at the target's order once more: 37 sh, 38 move, 39 lw, 40 li, 41 and, 42 jal, 43 sw. The RMW's store is in the jal delay slot. The RMW's load is before the call. So the source order is: store, RMW, call — and sched1 kept the store first.

In our build: 37 move, 38 lw, 39 li, 40 sh, 41 and, 42 jal, 43 sw. So sched1 put the copy+load before the store, and the store after the `li` (at 40), then the and, jal, sw.

So the difference is the store's position relative to the copy+load. In the target, the store is before the copy.

The scheduler's hazard logic delays the store. In the target, the store was NOT delayed — because it was anchored by the volatile asm in the original? Wait, the original binary has no asm. So what anchored it?

Maybe the original C had the store *after* the RMW in source, and the scheduler moved the store BEFORE the RMW because the RMW's store and the 0x188 store... no, sched1 delays stores.

Alternatively, maybe the original C's RMW was written as `*(u32*)(s0 + 0x44) &= ~4;` and the 0x188 store as a separate statement, and the scheduler's decision differs due to the *load* being before the store... 

Hmm, let me consider: maybe the original C had the RMW *split*:
```
u32 v = *(u32 *)(s0 + 0x44);      // load
*(u16 *)(s0 + 0x188) = 0;          // store
*(u32 *)(s0 + 0x44) = v & ~4;      // store
func_801553C0(s0);
```
Then the load comes first, the 0x188 store second, and the RMW store third. The target: lw at 39 (after the store at 37!). So the load would be at 39, after the store — hmm, the target has sh(37) then move(38) then lw(39). If the source were load-first, the target would show lw before sh. Unless sched1 reordered (it delays stores, so the store would move later, not earlier). So no.

What if the original C's store was `*(u16*)(s0 + 0x188) = 0;` *and* the RMW was `*(u32*)(s0+0x44) &= 0xFFFFFFFB;` — our current source. The scheduler delayed the store in our build. So the original must have had something else.

Let me look at the sched priority: in orig, the store's priority was 1 and the asm's ref_count 7. In win, the store's priority 1. Hmm.

What if the difference is not sched1 but the *pre-sched* insn order: in orig, the store's RTL insn (86) comes before the copy (99) because the copy is at the call. In win, same. So sched1 is the only difference.

Could we influence sched1's choice with a real-C construct that raises the store's priority? INSN_PRIORITY is computed from dependencies: an insn's priority = 1 + max(priority of dependent insns) roughly. The store has no dependents → priority 1. The copy has dependents (the load uses a0) → its priority = 1 + ... hmm, both 1.

What if the store's value depended on a later use? No.

What if we make the store depend on something computed late? E.g., if the store's value were `(u16)fc`? no.

OK, alternative: what if we make the *copy* dependent on the store, i.e., the copy's source is a value computed by the store? The copy is a0=s0; if instead the call argument were `*(s32*)(s0 + 0x188)`? That would load from memory — different code.

What if the call argument were `s0` but the source wrote it as `(s32)(*(u16*)(s0+0x188), s0)`? Comma with a load — extra insn.

Hmm. What if the call's argument is an expression involving s0 that forces the load of 0x188... no.

I think this is a WALL: `sched1-store-delay` — sched1 delays the store behind the arg copy (hazard), and only the volatile keepalive anchored it.

But wait — the wall list has `sched1-load-order` and `sched1-birth-order`. A new tag: `sched1-store-delay`.

Before walling, let me try a couple more creative real-C:
1. Make the store's base a *different* pseudo that is live across the copy: e.g., store via a pointer variable `u16 *q = (u16 *)(s0 + 0x188); *q = 0;` where q is defined before the if... The store's base would be q (a pseudo), and the copy a0=s0 wouldn't be usable for q. But the target's store uses s0 (the same reg as the base). If q is assigned to s0 by local-alloc (it's s0+0x188? no, q = s0+0x188 would be a separate pseudo needing an addiu). Actually if q is a pointer to the field, the compiler would compute s0+0x188 in a register (addiu) — extra insn. No.

2. Use the store *inside* the RMW statement via a comma (v1, 2).

3. Reorder the statements so the store comes after the `li v1,-5`? no.

4. What if the RMW is written *before* the store and the store is written as a *16-bit* store to 0x188 with the RMW's v44 value? no.

5. What if the 0x188 store is placed between the RMW's load and store via a split (as above) — the target order suggests no.

6. What if we use `s0` in the store's *value*: `*(u16 *)(s0 + 0x188) = (u16)(s0 & 0);` — identity launder, forbidden.

7. What if the store were a *volatile* store? That would anchor it (volatile mem ops are barriers in sched1: MEM_VOLATILE_P → the asm-like branch? Let me check sched_analyze_2's MEM case for volatile). If volatile works, is it a lever? The brief forbids "no new lever of any kind" — volatile to influence scheduling is a lever. But hold on: the target binary's original C might genuinely have had a volatile store! If the store were volatile, the code would be the same (sh). Hmm, but we can't know.

Actually, using volatile here would be exactly the kind of "barrier" lever the brief forbids (it defines barrier as an asm barrier, but volatile is the same idea). I'll not use it.

Let me instead check: does the target's `sh zero,392(s0)` perhaps come from a *different* source statement — e.g., the original C might have written the 0x188 store *before* the RMW's load because the RMW was written as `s0->unk44 &= ~4` where s0->unk44 is a `u32` field of a struct pointer — the struct access might generate a different address computation? The target's lw/sw use a0+68 (a0 = s0), so same.

Let me try the volatile experiment just to learn the mechanism (not to keep). If volatile gives 0, it confirms the barrier mechanism and I can report the wall with that evidence... but a WALL means I couldn't crack it. If volatile gives 0, it's a lever, so still a WALL (lever-free impossible). That's useful evidence.

Let me test: `*(volatile u16 *)(s0 + 0x188) = 0;`
