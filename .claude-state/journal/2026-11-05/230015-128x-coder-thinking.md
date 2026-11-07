---
ts: 2026-11-06T06:00:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_78ZW9AUyE1k5pOagvCz7
---
All three confirmed. Now append the results rows and moves lines, and write notes.

Evidence for the family MATCH: "struct-member load `sq->v` (u16) for D_800B9A02: MEM_IN_STRUCT_P makes the scalar load invalidated by the nonscalar ptr[K] store, so cse reloads *q after it (target `lhu 0(a2)`), and the 16-byte vars frame appears; 0 on 141/141 includers."

≤140 chars: "struct-member u16 load (sq->v): MEM_IN_STRUCT_P lets the nonscalar ptr[K] store invalidate it -> cse reloads *q after the store + 16B vars frame; 0 on 141/141 includers" — count ~175. Too long. Let me shorten: "struct-member u16 load sq->v is in_struct: the nonscalar ptr[K] store invalidates it, cse reloads *q after it; 16B vars frame; 0 on 141/141" ≈ 145. Trim: "struct-member u16 load sq->v is in_struct: nonscalar ptr[K] store invalidates it, cse reloads *q after it; 16B vars frame; 0 on 141/141" — let me count precisely later.

Let me write rows. Field count 9.

For 75820: dir func_80175820__func_80175820, file src/shared/ov/func_80175820.h, func func_80175820, kinds barrier, MATCH, 0, tries 14, wall -, evidence.
For 758FC: tries 5.
For 759D8: tries 7.

Let me append.
