---
ts: 2026-11-06T10:20:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_e5etClgWyNexxPCnysyn
---
All 23. As expected — the lever-free body can't recover the dead return values or the param copy.

Item 2 tries now: w1 + n0-n8 (9) + orig (baseline) + wp + wk = ~13. Need 30. Let me add more variants (another ~20) to reach 30.

Let me think about what else to try for item 2:
- Different casts for the struct fields.
- Reordering the field stores.
- Using separate variables for the loads.
- `if (dzsq >= arg1)` with a goto structure.
- Reuse of dzsq.
- Different arithmetic spellings (dz*dz vs dz^2).
- Pointer variable p for the stores.
- `s16` vs `s32` for dy.
- Splitting the condition.

Let me generate ~20 more. Also, I should count each scored file as a try.

Actually, the "tries" column probably means the number of scored candidate bodies. Let me be accurate: count all --try/sc.sh scores for the item.

Item 2 so far: orig (baseline), w1, wk, wp, n0-n8 = 13. Need 17 more.

Let me generate 18 more variants.

Similarly for items 1 and 3.

Let me write a bigger batch for item 2.

Variants (lever-free):
o1: p pointer for all field accesses.
o2: unk6 accessed via p.
o3: dy as s32 from a u16 load.
o4: `dzsq = dz * dz + dy * dy;` combined.
o5: `if (dzsq < 0x1901) dzsq = dzsq + 0x4000;` no braces.
o6: store order: unk18 before unk10.
o7: store unk10/unk18 via p.
o8: `((Unkstruct_80180AC4 *)a2)->unk6 -= (s16)((Unkstruct_80180AC4 *)a2)->unk6 >> 5;` no, dy.
o9: reorder dy computation after dzsq.
o10: a2 = arg0 + 0.
o11: `s32 a2 = arg0; Unkstruct_80180AC4 *p = (void *)a2;` all via p.
o12: `CAST_SIGN(u16, a2, 0xE) -= dz / 32;` (division instead of shift) — same for powers of 2.
o13: `dy >> 5` vs `dy / 32`.
o14: `(s16)(p->unk6)` vs `p->unk6`.
o15: `dzsq += 0x4000;` vs `dzsq = dzsq + 0x4000;`
o16: `if (0x1901 > dzsq)`.
o17: `if (dzsq < 0x1901) { } else { }` inverted.
o18: ret assignment order.

Let me write them. I'll do a generic replacement approach on the base.

Actually, to save time, let me write one script generating all remaining variants for items 1, 2, 3, then score them in three calls.

Let me do item 2 first (18 variants).
