---
ts: 2026-11-06T12:47:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JlhonxWWM47KxdfcECeV
---
So the barrier is treated as a memory use; then sched adds deps: everything after depends on it. But it doesn't split the BB — the asm insn is IN the block. So the scheduler has: lw, sw, asm, lhu... and the asm blocks the lhu from moving above it. Hence nop.

Now lever-free: we need something that keeps the lhu from moving above the sw. What about a dependence through memory: make the store and the load share an address? No, they must not (different values).

Alternative: change what the first RMW reads so it depends on t. But target's lhu reads sp10[0].

Hmm — what if I reorder so the RMW uses a different spelling that makes the dependency: e.g. `sp10[0] = (sp10[0] & 0xFFFF) + ...`? no.

Let's think about the *scheduler's* own rules. sched1 in 2.7.2 processes backward. The delay-slot rule: in `schedule_block`, there's code about `TARGET_DELAY_SLOTS` / `deps`. For MIPS, `DELAY_SLOTS`? Actually the branch-delay slot filling is reorg.c; the load-delay slot is handled by sched1 using `md->...`. In 2.7.2, sched.c has `#ifdef DELAY_SLOTS`? Hmm, the load delay handling: mips.h defines `SLOW_BYTE_ACCESS`? No — it's `sched.c`'s "the insn that follows a load must not use the loaded reg" modeled via `insn_latency`? In 2.7.2 sched.c there's `dead_or_set` / `MD_SCHED_INIT`. Hmm, mips.md has a define_delay? For the load delay, 2.7.2 mips uses `TARGET_DELAY_SLOTS`? Let me grep sched.c for "load".

Actually the mechanism: in sched.c, `sched_note_insn` etc.; the load delay is handled by the machine description's `define_delay` in mips.md? Let me grep mips.md for "define_delay".
