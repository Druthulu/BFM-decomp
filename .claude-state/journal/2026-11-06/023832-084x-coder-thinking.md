---
ts: 2026-11-06T09:38:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uQ6mNj6vXg4DKFumhC3i
---
In both, sched1 schedules insn 86 (the store) LAST (at T-15/T-14), after the copy (99/97) and the RMW. So sched1 puts the store last in both. But the final code has the store at 37 *before* the copy in orig, and at 40 (after the copy) in win.

Wait, in orig the final code: `sh zero,392(s0)` at 37, `move a0,s0` at 38. In the sched dump, insn 86 (store) is scheduled at T-15 (last) and 99 (copy) at T-13, 91 at T-12... so the sched order would be: ... 91, 99, 88, 86. Hmm, that means the store (86) comes AFTER the copy (99). But the final asm has the store BEFORE the copy!

Hmm, the sched dump's insn numbers are pre-sched RTL uids, and the "launching" order is the scheduled order... The final insn order (from the .sched dump's reordered listing?) — the .sched file includes the schedule trace then the reordered insns. Actually sched1 writes the insns in the new order into the dump? The dump shows the trace and then the block's insns in scheduled order.

But the final asm differs. So maybe sched1's order is not what I think, or the copy 99 is not the move a0,s0.

Wait: in the o lreg dump, insn 99 = `(set (reg:SI 4 a0) (reg/v:SI 74))` — the copy. In the sched trace, the order from T-12 to T-15: 91 (load via a0?), 99 (copy), 88 (asm), 86 (store). That order (91 before 99) can't be right because 91 uses a0 defined by 99.

The trace lists the ready list and the "launching" of insns; the numbers in "ready list at T-k" are insn uids with priorities. At T-12 it says "launching 91 before 93" — so 91 is scheduled at T-12. Then T-13: 99, T-14: 88, T-15: 86. So the scheduled order (T increasing = later) is: ... 91 (T-12), 99 (T-13), 88 (T-14), 86 (T-15). Since scheduling runs backwards (T-1 is the last insn, T-N the first), higher T = earlier in the block. So the final order is: 86 (T-15, first), 88 (T-14), 99 (T-13), 91 (T-12), ... Yes! sched1 runs from the end backwards, so T-15 is the *first* insn. So the order is: 86 (store), 88 (asm), 99 (copy), 91 (load)... exactly matching orig.

In win: T-14: 97 (copy? in w, the copy is insn 97), T-13: 97/86... let me read: "ready list at T-13: 97 (1) 86 (1), now 97 86; insn 86 has a greater potential hazard, now 86 97; ready list at T-14: 97 (1), now 97; total time = 14". So the order: T-14 = 97 (copy) first, then 86 (store) at T-13. So win's order: copy, store, load... matching the bug.

So sched1 placed the store last (T-13) in win because "insn 86 has a greater potential hazard" — the store was delayed behind the copy. In orig, the asm (88) sat between, and sched1 placed 86 first (T-15) because the asm... hmm, actually in orig, 86 was placed at T-15 = first.

The key: in orig, insn 88 (asm) is present and its scheduling forced 86 before it. In sched.c, an asm_operands insn is treated specially: `if (GET_CODE (insn) == INSN && GET_CODE (PATTERN (insn)) == ASM_OPERANDS)` — the scheduler may treat the asm as a barrier (can't move insns across it) when it has memory clobbers? Our asm has no clobbers but has an input operand.

In sched.c (2.7.2), `sched_analyze_insn`: for asm_operands, it calls `sched_analyze_2` for inputs and `sched_analyze_1` for outputs; also `if (GET_CODE (PATTERN (insn)) == ASM_OPERANDS) ... ` Hmm.

Anyway: the asm acts as a barrier that keeps the store before it.

Real C equivalent that sched1 treats as a barrier: a *volatile* memory access? Or a call? A call is a barrier. Is there a real call between the store and the copy? No.

What about a volatile store? If the 0x188 store were volatile, sched1 couldn't move it after the copy... Actually it could still move the copy above it? A volatile access is a barrier for scheduling in sched1 (`sched_analyze_2` with volatile mem sets `sched_before`?). Hmm.

Real C: we need something that makes the store "stick" before the copy. Options:
- a `volatile` cast on the store: `*(volatile u16 *)(s0 + 0x188) = 0;` — changes semantics? Volatile prevents reordering/deletion but produces the same instruction (sh). Would it prevent the copy hoist? sched1 treats volatile mem as a barrier (it sets `sched_before_next_call`? no). In GCC, volatile memory references are considered "unchanging" barriers: `sched_analyze_2` for volatile MEM adds a dependency to the previous insn? Let me recall: in sched.c, `if (MEM_VOLATILE_P (x)) { ... sched_before_next... }`. There's `SCHED_GROUP_P` and `sched_before_next_call`.

Hmm, using volatile is a real C construct but might be considered a lever? It's not in the forbidden list (pin/launder/barrier/keepalive). The forbidden "barrier" kind means an asm barrier. A volatile qualifier is a language feature; if the target's C had a volatile store, the code would be identical (volatile affects optimization, not codegen here). But is it a "new lever of any kind"? Arguably volatile is a codegen lever (it changes scheduling). The brief says "no new lever of any kind" and defines lever-free as "none of the row kinds remain: no pin, launder, barrier, keepalive macro or asm; no new lever of any kind." A volatile cast is a hint that changes optimization — it's borderline. I'd avoid it unless it works and looks legitimate. Hmm. Actually "no new lever of any kind" — a volatile qualifier used solely to affect scheduling IS a lever. Avoid.

Other real C: a function call between the store and the RMW. There is none in the target.

What about making the store and the RMW *dependent* through a common value? For instance, the RMW could read a value that the store... no, different addresses.

What about writing the RMW with a *function-like* expression that creates a sequence point? Sequence points don't affect scheduling.

What about a `do{}while(0)` block? It doesn't affect sched1.

What about the store being an assignment through a pointer variable whose value is computed after the copy? Hmm.

Actually, maybe the real C had a different structure entirely: the 0x188 store might have been part of an expression with the RMW, e.g.:

```
*(u16 *)(s0 + 0x188) = 0;
...
```
The target's C probably was exactly this. The original compiler (with the same source) produced the target — so the source at hand (minus keepalive) is *not* the original C; the original C had something else. What could produce the target naturally? The target has the copy after the store. In the original C, maybe there was a genuine use of s0 between the store and the RMW... e.g., the original might have had `s0->unk18A = 0;` again? No, target has one.

OR the original C's RMW was written through a *pointer loaded from s0*? No.

OR the original C had the store `*(u16 *)(s0 + 0x188) = 0;` *after* the RMW in source, and sched1 reordered them so that the store comes before the copy? Let me look at t3's sched: t3 put the store after the RMW in source; the result was score 2 with the store at 40 (via a0). So no.

Hmm, what if the *RMW* came before the store in source and the store after the call? no.

Let me think about sched1's "potential hazard" rule. In win, at T-13 the ready list has 97 (copy) and 86 (store); the scheduler picks 97 first because "insn 86 has a greater potential hazard" (stores are delayed). Then 86 at T-14. In orig, the asm 88 is between them and the order is 86, 88, 99, 91. Why did 86 get scheduled before 88/99? Because of the dependency chain: the asm 88 uses reg 74, and the store 86 also uses reg 74; no dependency. Hmm, but sched1 at T-15 has only 86 available? The ready list at T-15 in orig: "ready list at T-15: 86 (1), now 86". So at T-15, only 86 was ready (88 was not ready yet because... 88 depends on something? The asm has an anti-dependency? The asm at 88 might depend on the store 86? No. Maybe 88 was blocked until T-14 due to the copy 99's REG_DEP_ANTI: the asm's `(insn_list:REG_DEP_ANTI 86 (nil))` — the asm has an anti-dependency on 86! From the lreg dump: `(insn 88 ... (insn_list:REG_DEP_ANTI 86 (nil)))`. So the asm depends (anti) on the store 86 → the store must be scheduled before the asm. And the copy 99 depends on 88 (`(insn_list 88 (nil))`)? insn 99's insn_list is `(insn_list 88 (nil))` meaning it depends on 88? Hmm.

So the asm creates anti-dependencies that pin the order: store → asm → copy → load. The anti-dependency 88 on 86 comes from sched_analyze: the asm reads reg 74 and the store writes memory; the anti-dependency is a register anti-dependency (store doesn't write reg 74 though). Hmm.

Anyway: the asm acts as an ordering anchor.

Real C alternative: is there a *real* operation that creates an anti-dependency between the store and the copy? A real use of reg 74 between them would create: store(74), use(74) — no anti-dep. The asm's anti-dep 88→86 is odd.

Let me look at sched.c for how asm operands get REG_DEP_ANTI. Maybe it's because the asm has no output and reads 74: `sched_analyze_insn` for asm: it processes inputs with `sched_analyze_2` which adds dependencies on the last insn that wrote the reg (or all previous insns if the reg is a hard reg?). reg 74 is a pseudo (s0). Hmm.

Alternatively, the anti-dep could come from `sched_analyze_1` treating the asm as clobbering something.

Let me check sched.c in tools/reference/gcc-2.7.2/sched.c for ASM_OPERANDS handling.

Time: 02:38. Item 3 started 02:32:49 → 5 min. Budget 20-30. I have time. Let me look at sched.c.
