---
ts: 2026-11-06T10:25:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1Ec2NBbWX7l0eDFcFT7R
---
Lever-free CF3E8 is 110 with 460 vs 469 insns — 9 insns short. The pins here force values into specific registers, and removing them changes a lot. This is a big function (469 insns). 110 diffs is far.

This is very likely a WALL. But I need ≥30 tries and ≥20 min. Let me do a batch of variants (real-C moves) and score, then record WALL.

Given the size, cracking is unlikely. Let me generate ~30 variants quickly:
- Reorder declarations.
- Change types (u16/s16).
- Remove barriers already done.
- Maybe some pins can be replaced by making the values single-use.

Actually, the 9-insn deficit suggests the pins/barriers changed codegen substantially (the barriers split blocks and the pins prevent copies). Getting to 0 is implausible in 20 min.

Let me do a broad batch and record WALL. Time is limited (item 3 + item 4 still). Let me be efficient: generate 30 variants with a script applying type/decl/statement moves, score them, take best.

Actually, let me first check the time budget overall. Started 02:54. Now 03:32. 38 min elapsed, 2 items done. Items 3 and 4 at 20-30 min each → finish ~04:30. That's fine.

Let me look at the CF3E8 body to design moves. It's 194 lines with 3 blocks (blk1, blk2, final). The pins are on pC($3), p3($9), q5($13), mq2($8), tv2($15). 

The barriers: two `__asm__("")` in blk1 (one after ADDPRIM2 of pA, one between pC->v0=0 and pC->clut).

Let me just do the batch. Variants:
1. Reorder declarations (tv2, q5, mq2, pC, p3 order).
2. Change tv2 type u32→s32.
3. mq2 u32→s32.
4. q5 s32→u32.
5. pC/p3 pointers → Sprt24* (already).
6. Remove `idx` init at decl → assign separately.
7. Change `s32 idx = D_800B9A02;` to `s32 idx; idx = D_800B9A02;`.
8. Use direct stores instead of temps.
9. Reorder the final block.
10. etc.

Given the 9-insn deficit, maybe the barriers themselves emitted... no, empty asm emits 0 insns. The deficit is from pins preventing/forcing moves.

Hmm, 460 vs 469 — the target has 9 more instructions. The pins might force extra moves. Without them, the compiler fuses things.

Realistically WALL. Let me generate 30 variants and record.

Let me write a generator with ~30 transformations.
