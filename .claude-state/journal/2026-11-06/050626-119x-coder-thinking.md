---
ts: 2026-11-06T12:06:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nenxXOy1HHd5eHKF1Qgr
---
Still +1 insn.

Hmm. The extra insn is probably the `at` register usage. Let me look at y5's diff.

Actually, let me step back and think about the barrier mechanism here. The barrier is `asm volatile("" ::: "memory")`. In sched1, a volatile asm with a memory clobber acts as a scheduling barrier. Without it, sched1 hoists the address computation + load above the store.

Real C alternatives that keep the load after the store without adding code:
- a volatile load (y5) → adds 1 insn (189).
- a volatile store (y2) → adds 1 insn.

Hmm, why does the volatile load add an insn? Because a volatile MEM can't be rematerialized/cse'd, so the address is computed in a register rather than using `at`.

Hmm.

What about `__asm__ volatile("" : "=r"(...))`? That's a lever.

What about a real function call? no.

Hmm, let me look at the diff for y5 to see the +1.

Actually, maybe I should consider: is the 8-point difference in w2 (barrier removed, launder kept) really only an ordering? Yes: the 4-insn block moved 2 insns earlier. Since the insn count is identical (188), it's a sched1 ordering issue.

What real-C change would make sched1 keep the order? sched1 respects memory dependencies. If the store `D_8011F83A = idx` and the load `D_8018DB2C[idx]` were recognized as aliasing, sched1 would keep the order. The alias analysis says no alias (different symbols).

Can I make them alias in the compiler's view? E.g., if the array base and the store were through the same pointer type... 

Idea: store `idx` to `D_8011F83A` via a pointer that the compiler can't disambiguate from D_8018DB2C:
```
*(u8 *)&D_8011F83A = idx;   /* same as before */
```
Hmm, D_8011F83A is declared as `extern u8 D_8011F83A;`. The store is `(mem:QI (symbol_ref D_8011F83A))`. The load is `(mem:SI (plus (symbol_ref D_8018DB2C) (reg)))`.

In sched.c, `sched_analyze_2` for a MEM calls `true_dependence (x, ...)` for pending stores. gcc 2.7.2's true_dependence uses `rtx_addr_can_trap_p`/alias sets? In 2.7.2 there's no alias analysis (no alias sets); `true_dependence` calls `rtx_equal_p`-based checks + `addr_side_effect`? Let me look at sched.c's sched_analyze_2 to understand.

Actually, in 2.7.2 `true_dependence` is in alias.c? There's no alias.c in the reference list. Let me grep sched.c.

Given the time, let me consider: the barrier removal gives 8 with the launder kept; the launder removal gives 30. Both needed → WALL (best lever-free 38 or better).

Let me try a few more real-C ideas quickly:
1. Reorder the C: move the `((void(*)(...))func_80024054)(...)` call before the store? No, the target has the store first.
2. Make `idx`'s value depend on the store: `D_8011F83A = idx; idx = D_8011F83A & 0x7F;` then use idx. cse would forward.

Hmm, wait: cse forwarding `D_8011F83A = idx; idx = D_8011F83A` → idx = idx. Then no dependency.

3. Use a pointer variable: 
```
u8 *ip = &D_8011F83A;
*ip = idx;
idx = *ip & 0x7F;
```
cse would still forward (same address).

4. Use `*(u8 *)((u32)&D_8011F83A) = idx;` — folds.

Hmm.

What about making the load volatile but avoiding the extra insn: the extra insn comes from the address materialization. Maybe if the volatile load's address is computed in `at`... 

Let me look at y5's diff to understand the +1.
