---
ts: 2026-11-06T09:56:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8OQoG9keN9j12c87gFmS
---
Lever-free baseline for func_80023BF0 is 102, COUNT class. The residual is a register-allocation shift: t0->t1, a0->t0, t1->t2, a2->a3, t2->t3, t3->t4 — it's a global shift of the caller-saved bank by one (i.e., everything is one register lower). Plus s0->s2.

The original comment says the 13 fences are pure live-length arithmetic: "0 -> 15, 8 -> 13, 10/11/12 -> 7, 13 -> MATCH". So the barriers add live length to `pkt`/`base`? Actually fences add zero insns but affect live length of pseudos across them (each asm clobbers nothing but is a scheduling barrier; does it affect liveness? An empty asm volatile creates a BARRIER in flow? Actually `__asm__ __volatile__("")` with no operands — GCC 2.7.2 treats it as an asm insn with no outputs/inputs; it doesn't change register liveness unless clobbers. But it does split basic blocks for scheduling and affects sched1 priority (birth order) and possibly live_length? Hmm, the comment says "pure §47 live-length arithmetic". 

Wait — a plain `__asm__ __volatile__("")` in GCC without clobbers... The barrier in the comment is `__asm__ __volatile__("")`. It creates an insn that references nothing. How does it change live length? Possibly by being a scheduling barrier that prevents reordering, thereby changing insn order and hence live ranges. Anyway.

Lever-free, we're at 102 with a systematic shift. Hmm, that's a big gap. 20-30 minutes per item.

Let me think about what the shift means. Registers mine->target: t0->t1 (23), a0->t0 (19), t1->t2 (17), a2->a3 (11), t2->t3 (10), t3->t4 (8), s0->s2 (4), t6->t7 (4).

Mine uses registers one lower than target: mine's t0 should be t1; mine's a0 should be t0 (a0=4, t0=8 — not one lower; that's a jump). Hmm, mapping: mine a0->target t0 means mine's $4 corresponds to target's $8. Mine t0($8)->t1($9). Mine t1($9)->t2($10). t2($11)->t3? no t2 is $10, t3 is $11: t2->t3 means $10->$11. t3($11)->t4($12). So the caller-saved temps are shifted up by one, while a0($4) becomes t0($8). And a2($6)->a3($7).

This suggests target uses one extra caller-saved register at the low end? Or mine allocates an extra pseudo taking $4 (a0) which pushes others. Actually if mine has a pseudo in $4 (a0) that target doesn't have... Hmm.

This is getting deep. The barriers were doing live-length arithmetic to fix exactly this. Without them, we need real C to change live lengths.

Let me consider the moves catalog: C0505 real C moves (temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse).

Given the complexity (281 insns, huge function), cracking this lever-free in 20-30 min is likely a WALL. But let me try a few targeted things.

Actually, wait. Let me reconsider the purpose. These are "singleton crack shards" where the coder tries to find a lever-free body. Many will be WALLs. The deliverable is one results.tsv row per item with result MATCH/PARTIAL/WALL, best score, tries, wall tag, evidence.

The instruction: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)." So I need to do at least 30 scored tries for a WALL. Hmm, 30 compiles per item × 4 items. Each compile is ~1-2 s? Let me time it. The dt.sh took a few seconds. 30 tries × 4 items = 120 compiles, maybe 5-10 minutes. Plus thinking.

Let me be systematic: write a search script that generates candidate bodies by applying a set of real-C moves, and scores them via delever_search --try. There's sc.sh which does "one line per candidate". Let me look at sc.sh.
