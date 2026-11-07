---
ts: 2026-11-06T21:57:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Tyn2SAjv0pzQI749swTu
---
t09 (tmp u32): the dst bank is now correct! The remaining issues:
1. `lh v1,208(s1)` vs `lw v1,208(s1)` at 139, 173, 350, 381: mine loads a halfword (`lh`) where target loads a word (`lw`). That's `dst = *(s32*)(arg0+0xD0)` — wait, 208(s1) = 0xD0. Mine uses `lh`?! That means tmp being u32 changed... no. Hmm, `lh v1,208(s1)` — 208 = 0xD0. The target `lw v1,208(s1)`. So mine loads a halfword. Why? Because `dst` is s32 but... wait t09 only changed tmp to u32. How does that change the dst load to lh? 

Oh! Maybe the struct field at 0xD0... no. Let me check: the source `dst = *(s32 *)(arg0 + 0xD0);`. That's a word load. Unless... hmm, t09 = src.replace('    s32 tmp;', '    u32 tmp;'). That shouldn't affect dst.

Wait, maybe my index mapping is off. Let me check which variant t09 actually is. i=8 is tmp s32, i=9 tmp u32. But `types = ['s32','u32','int','long','s16','u16','u8']`. i increments: after the dst loop i=7, then tmp loop: i=8 s32, 9 u32, 10 int, 11 long, 12 s16, 13 u16, 14 u8. Yes t09 = tmp u32.

But `lh` vs `lw` for 0xD0 load... Maybe the load at 208(s1) isn't dst=arg0+0xD0 but `src = *(s32*)(arg0+0xD0)`? No.

Hmm, wait: could `lh` be for `((Unkstruct_800B5CB8 *)arg0)->unkCC`? 0xCC = 204, not 208.

Let me look at the source around the dst block: `dst = *(s32 *)(arg0 + 0xD0);` → 0xD0=208. A `lw`. Why `lh`?

Unless t09 is not what I think. Let me grep t09.c for tmp decl and the dst line.
