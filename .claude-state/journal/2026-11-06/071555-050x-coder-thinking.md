---
ts: 2026-11-06T14:15:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qJN25QcoKfle9aZPWUf1
---
The increment extra-ref at 2300 is inside `mark_used_regs` (auto-inc optimization in `flow_analysis`). This applies when flow converts `x = x + const` + a load/store into an auto-increment addressing mode. But on MIPS, there are no auto-increment addressing modes, so this path won't trigger (the `validate_change` with inc_code would fail). So REG_INC extra refs probably don't apply here.

Let me look at the other ref-count increments: lines 2067, 2315, 2501, 2711. Line 2067 is in the "regs set" path: `reg_n_refs += loop_depth` for each set. Line 2501 and 2711 — let me check.

Actually, the count 11 for dst and 11 for i without asm. Let me count occurrences:
i: set at `i=0` (1), i++ set (1), i in slt (1 use). Occurrences: 3.
dst: set at `dst=src+n` (1), use in store (1), set in dst++ (1), use in dst++ (1). Occurrences: 4.

But refs are 11 each. So weighting is substantial. Loop depths: block 13 (setup) depth 1, block 14 (body) depth 2, block 17 (latch) depth 2? Let's compute:
i: set i=0 in block13: +1; i++ in block17: set +1*2=2; slt in block17: use +2. Total 5. Not 11.

Hmm, maybe loop_depth is 3 for the do-while? block13 depth 1? Actually, the setup block (n, i=0, src, dst) is inside `if ((arg0->cmd & 0xFFFF) == 9)` inside `while`, so depth 1. The do-while body depth 2, latch depth 2. Then i = 1 + 2 + 2 = 5. Still not 11.

So reg_n_refs counts more than loop_depth per occurrence. Maybe it's `loop_depth` where loop_depth counts... let me check how loop_depth is computed. In flow.c, `loop_depth` is a static set by `find_loop_depth`? Let me grep.
