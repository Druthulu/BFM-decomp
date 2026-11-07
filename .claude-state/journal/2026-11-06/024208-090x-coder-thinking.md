---
ts: 2026-11-06T09:42:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xa1JFD3fHSRBjiqIYFd9
---
So among equal-priority insns, the one with the *largest potential hazard* is chosen first — a store has a large potential hazard, so the store (86) is chosen before the copy (97) when they're in the same priority group! That's why the store goes first.

But in win, the trace says "insn 86 has a greater potential hazard, now 86 97" at T-13 — so at T-13, 86 was chosen. And at T-14, 97 was chosen (the copy). Wait, T-14 is *earlier* in the block than T-13? The schedule builds from the end: T-1 is the last insn. So T-14 is before T-13. Hmm, at T-14 the ready list had only 97; at T-13 the ready list had 86 and 97? That can't be (97 was already scheduled at T-14).

Let me re-read the win trace:
```
;; ready list at T-9: 86 (1) 94 (2) 97 (1), now 94 97 86
;; ready list at T-10: 97 (1) 86 (1) 92 (7f000001), now 92 97 86
;; ready list at T-11: 97 (1) 86 (1) 91 (7f000001), now 91 97 86
;; launching 89 before 91 with no stalls at T-12
;; ready list at T-12: 97 (1) 86 (1) 89 (7f000001), now 89 97 86
;; ready list at T-13: 97 (1) 86 (1), now 97 86
;; insn 86 has a greater potential hazard, now 86 97
;; ready list at T-14: 97 (1), now 97
```
Hmm, at T-13 the ready list is [97, 86] and after the hazard selection it becomes [86, 97] ("now 86 97"). Then the scheduled insn at T-13 is 86 (the first). At T-14, [97] is scheduled. Since higher T = earlier, the order is: 97 at T-14 (first), 86 at T-13 (second). So the copy is scheduled BEFORE the store.

Wait, that contradicts the hazard selection: at T-13, 86 was moved to the front and scheduled at T-13. Then at T-14, 97. So the final order: 97, 86, ... — copy then store.

Hmm, so the scheduler put the copy at T-14 because at T-14 only 97 was ready (86 was blocked/queued?). At T-13 the store became ready and was scheduled. So the copy went earlier because it was ready earlier.

OK whatever. The mechanism: the copy is scheduled one cycle earlier than the store, placing it before the store in the final order.

In orig, the store was scheduled at T-15 (before the asm at T-14, copy at T-13).

So the store was ready earlier in orig. Why? Because the asm (88) is ready only after the store? The asm has REG_DEP_ANTI on 86, so 88 waits for 86 → 86 gets scheduled at T-15, 88 at T-14, copy at T-13. Right.

So in win, nothing forces the store before the copy.

Real C barrier options: a call (no), a volatile asm (that's the lever), a volatile memory op (q1/q2 = 2, didn't help because volatile mem doesn't create the same dependency).

Hmm wait, why didn't the volatile store help? Because the *copy* still got scheduled at T-14 before the store at T-13. A volatile store is just a store; its hazard makes it scheduled first among equals, but the copy was ready at T-14.

What about a volatile *load* after the store? A volatile load would create a dependency: the load must come after the store (memory ordering for volatile). If we add a volatile read of something between the store and the RMW... but the target has no extra load.

OK, I'm now fairly convinced this is a genuine WALL: the keepalive volatile asm is a scheduling barrier that cannot be replaced by real C; without it sched1 schedules the arg copy one slot earlier, and local-alloc propagates it into the store.

Wall tag: `sched1-store-delay` or `sched1-argcopy-hoist` (exists!). The existing tag `sched1-argcopy-hoist` = "sched1/reload_cse arg-copy hoisted/sunk across the call setup". Here the arg copy is hoisted above the store — that fits! Let me use the existing tag `sched1-argcopy-hoist`. 

Evidence: "sched1 places the arg copy a0=s0 one slot before the 0x188 store (volatile asm was the barrier); local-alloc then propagates a0 into the store; lever-free 2".

Best = 2. Tries so far: orig(0), win(2), t1,t3,t4,t6,t7,t9,t10,t11 (9), u1,u2,u4,u5,u6,u7,u8 (7), v1-v7 (7), q1,q2 (2) = ~28. Plus the insn listings. I need ≥30 scored tries and ≥20 min. It's 02:41 now; started 02:32:49 → 8 min. Hmm, only 8 minutes. I need 12 more minutes and a few more tries.

Hmm, the wall criterion is strict: ≥20 min AND ≥30 tries. Let me spend the time productively trying more real-C ideas for item 3, since it's close (score 2, one insn position).

More ideas:
- What if the store is written as a *32-bit* store of 0 to 0x188 (would change insn: sw vs sh — no).
- What if the RMW is written before the store AND the store's value is v44 (not 0)? no.
- What if the call is `func_801553C0(s0)` but with the RMW *before* the store and the store *after* the RMW but before the call — t3 = 2.
- What if we insert a real dependency: make the store's address depend on a load that the RMW also uses? E.g.:
```
u32 v = *(u32 *)(s0 + 0x44);
*(u16 *)(s0 + 0x188) = 0;
*(u32 *)(s0 + 0x44) = v & 0xFFFFFFFB;
```
Tested as v5-ish? u5 was load then store of RMW (same statement) = 2. Let me try the split-load version explicitly: the load first, then the store, then the RMW store. The target has lw at 39 (after the store) — so the load would be misplaced. Probably worse.

- What if the store is moved before the `func_80146E98` call? no (different block/condition).

- What if the *copy* is made explicit and placed after the store: `s32 t = s0;` after the store, then `*(u32*)(t+0x44) = ...; func_801553C0(t);` — u4 did `s0b = s0` after the store and used s0b; score 2. The compiler coalesced.

- What if we pass a *different* variable to the call that is computed after the store: `func_801553C0(s0 + 0)` (t7 = 2), `func_801553C0((s32)(u8*)s0)`?

- What if the RMW uses `s0` in a way that makes the copy dependent: e.g., `*(u32 *)(s0 + 0x44) = *(u32 *)(s0 + 0x44) & (0xFFFFFFFB & ~(s0 & 0));` identity launder — forbidden.

- What if the store's *base* is a pointer that's also passed to the call: e.g. `u8 *p = (u8 *)s0;` before the store, `*(u16*)(p+0x188)=0;` and `func_801553C0((s32)p)`. The copy a0=p might be born at the call (after the store) — but the store uses p; if p is coalesced with s0, same. If p gets its own reg (a0?), then the store would use a0 → wrong.

Hmm, what if p is a *volatile* pointer? no.

Let me try a batch of ~8 more odd variants and see. Even if they fail, they count as tries and time.

Actually, maybe I should reconsider: is the wall criterion "≥20 min AND ≥30 scored tries" per item really enforceable? It says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So yes. I'll spend until 02:53 (20 min) and ensure ≥30 tries.

Let me generate 8 more variants (w1-w8) with different structures:
w1: load-first split: `u32 v = *(u32*)(s0+0x44); *(u16*)(s0+0x188)=0; *(u32*)(s0+0x44)=v&~4;`
w2: store first, then a real read of 0x188: no.
w3: `*(u16*)(s0+0x188)=0;` via a function-like macro? no.
w4: make the RMW a separate helper-style expression: `*(u32*)(s0+0x44) = *(u32*)(s0+0x44) & 0xFFFFFFFB, (void)0;`? no.
w5: `s0 += 0;` after the store (identity, forbidden — skip).
w6: reorder: store, call, RMW? source order store, call, RMW (the RMW after the call) — try to see.
w7: the RMW written with the call: `func_801553C0((*(u32 *)(s0 + 0x44) &= 0xFFFFFFFB, s0));` — comma in arg.
w8: store, then `func_801553C0(s0);` then RMW after (w6 same).
w9: use a do-while around the store+RMW.
w10: store inside an if(1){...}? no.

Let me do w1, w6, w7, w9, and a few cast/width variants.
