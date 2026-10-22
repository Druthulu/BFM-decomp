---
ts: 2026-10-22T00:59:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ZDORnGomaNQJfvtFiQHr
---
pg017 (cast on v1 + do-while on e): score 2, an ORDER difference — the `li a0,409` (callarg0 = 0x199) is one slot later in mine.

This is a *statement order* / scheduling issue. The `li a0,409` is the setup for the call `func_8012C658(callarg0, argmode, s0)`.

In the target, the `li a0,409` is at 44 and in mine at 45. Hmm, a one-slot difference in the delay-slot scheduling.

Options to fix: reorder the source statements. E.g. in the case0 branch:
```
callarg0 = 0x199;
e = unk20;
argmode = 2;
```
The `li a0,409` comes from callarg0. The order of the assignments might matter. Let me try permutations of the three assignments in case0/case1 (statement order is in the C0505 catalog!).

Let me generate variants with the statements in case0 and case1 permuted.

Let me write a quick generator for this item: permute the 3 assignment lines in case0 and in case1 (6 × 6 = 36 combos) with the base = pg017.

Let me do that.
