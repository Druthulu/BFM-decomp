---
ts: 2026-10-22T10:33:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_JinGmug2pmtQVrIP3xUa
---
In the sched dump, the magic's pseudo 152 is set at insn 357 (the lui/ori) and used by the two mults at 300 and 312. So the scheduler placed the materialization (357) right before the first mult (300) — i.e. the constant is scheduled adjacent to its use.

In the target, the materialization is at the top of the tail block (before "li v0,160"), i.e. ~4 insns earlier.

So it's a scheduling difference of a few instructions. Hmm! That means the target's magic was scheduled EARLIER. Why? Because in the target, the pseudo was in $a0 (allocated differently) — the allocation is affected by the scheduling.

Circular. Hmm.

OK, decision time. It's 04:35. Let me spend the remaining required wall time on 8018389C and 8017D81C with more batches of variants (mechanical but legitimate), then write up.

Let me do 3-4 more batches of ~12 variants each for both items, spread over the next ~15 minutes. To use the time well, let me think of new move classes:

8018389C new classes:
- The `L` struct's field accesses (L.v[], L.sxy[], L.z, L.flag) — reorder the assignments.
- The `RotTransPers` call's args.
- The condition's `0x9F`/`0x13F`/`0x77`/`0xEF` constants' spellings.
- The `x = x << 8` → `x = x * 256` (tried).
- The `if (x == 0x10) x = 0xF;` → `x = (x == 0x10) ? 0xF : x;` (a ternary — a real C move!).
- The `flg` variable → the inline constant (tried).
- The call `func_8002D4C8(0xA9B, ...)` → 2715 decimal.
- The vol computation inside the condition.
- The `ax` pin's spelling.

8017D81C new classes:
- The `do{}while` → `while` with the increment at the end (tried for-loop).
- The p increments.
- The store constants' spellings.
- The `((Unkstruct_800B5CB8 *)a0)->unk2` spelling.
- The order of the two initial calls.
- The `v == 0` check.
- The declaration of `p` as `u8 *` vs `void *`.

Let me write these batches. I'll run 2 batches per item.
