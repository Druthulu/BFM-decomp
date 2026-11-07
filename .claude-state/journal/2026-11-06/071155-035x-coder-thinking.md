---
ts: 2026-11-06T14:11:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_S2D7RdCXuCjDJrxUjG2d
---
reg_n_refs += loop_depth for each REG occurrence. So a reg used inside a loop at depth d counts d per occurrence.

In our function: the do-while loop is at depth 2? (outer while depth 1, inner do-while depth 2). So refs inside the do-while count 2 each. Refs in the while body outside the do-while count 1.

Let me compute for i (without asm):
- `i = 0;` — in block 3, which is... where? The i=0 assignment is in the block containing `n = ...; i = 0; src = ...; dst = ...` — is that inside the while loop (depth 1)? Yes, the while body. So i=0 counts 1.
- `i++` inside do-while (depth 2): the RTL set is 1 occurrence -> +2.
- `i < n` inside do-while: 1 occurrence -> +2.
Hmm total 5, not 11. Plus the asm adds... Let me reconsider loop depth. Maybe the outer while is depth 1 and do-while is depth 2, but the block 14 is inside both. 

Actually maybe the asm statements themselves: each asm occurrence of the reg counts loop_depth. The src asm is at depth 1 (outside do-while, inside while) -> +1? Comment said "+2 refs". Hmm.

Wait, maybe loop_depth counts differently. Let me not guess. The table gives actual numbers: i=14 with asm, dst=11.

Let me get the c1 (no asm) numbers by dumping. I'll set up a scratch TU copy properly.

Actually, wait — maybe simpler: the table from the target dump already includes the asm refs. The asm for i is at insn 329 in block 14. What loop depth? Let me check the loop dump for loop_depth. In .loop dump, the loops are numbered. Let me check .loop for func_8013D53C.

Alternatively, let me just compute the difference empirically by dumping c1. Let me set up the scratch TU.

Plan:
- mkdir .run/P40/T11/O02x/_tu/shared
- cp src/shared/engine_prelude.h .run/P40/T11/O02x/_tu/shared/
- cp src/ov_SC01_084/ov_SC01_084_jr_8013C98C.c .run/P40/T11/O02x/_tu/ov_SC01_084/t.c
- Edit t.c to remove the asm lines (or replace with candidate body).
- DUMP_ROOT=... bash tools/cc1_dumps_tu.sh <abs path to t.c> c1

But the cpp line in cc1_dumps_tu: `-Iinclude -I"$(dirname "$tc")" -Isrc/shared -undef ...` and the TU includes "../shared/engine_prelude.h" — resolved relative to dirname(tc) = _tu/ov_SC01_084 -> _tu/shared/engine_prelude.h. Good. Also "common.h" via -Iinclude. Good.

Let me set this up. But first, is there an even better route? Let me check if there are existing worked examples for this exact function or similar. Let me grep moves.md for func_8013D53C.
