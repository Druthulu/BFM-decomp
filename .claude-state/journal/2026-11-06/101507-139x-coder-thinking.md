---
ts: 2026-11-06T17:15:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NAmHiBc8q89Flqn4Z1dG
---
Item 4: kinds = launder. Levers present: two pins (`ang` $4, `pv` $3) — NOT row kinds (row kind is launder), so they may stay per the constraint "levers of other kinds the def already had (pins under other causes) may stay, never added". And the launder: `__asm__ __volatile__("" : "=r"(pv));` at the end — an out-only asm that creates a zero-byte 2nd SET of pv to kill the sched1 birthing boost.

So I need to remove the launder and reproduce with real C. The launder's purpose: a second set of pv (out-only asm) so pv is multi-set, demoting sched1's birthing boost.

The pv computation:
```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (...);
```
The asm after everything: `__asm__ __volatile__("" : "=r"(pv));` — a second definition of pv, dead.

Real C: a real second set of pv. The catalog: "launder->real 2nd set pv &= 0xFF000000" etc. From moves.md: "launder->real 2nd set pv &= mask; win.c keeps $4 ang pin only (0)" and "launder: pv = *p; pv &= 0xFF000000 split (real 2nd set)".

So the crack: split the `pv & 0xFF000000` into a separate statement so pv gets a real second set:
```
pv = *(u32 *)p;
pv = pv & 0xFF000000;
*(u32 *)p = pv | (CAST_NONSTRUCT(...) & 0xFFFFFF);
```
Wait, the current source computes `pv = *(u32 *)p;` then uses `(pv & 0xFF000000) | ...`. A real second set: `pv &= 0xFF000000;` then `*(u32 *)p = pv | (...)`.

Let me try that. The original expression:
```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (CAST_NONSTRUCT(u32, *(s32 *)((u8 *)&D_800A651C + (*bidx * 20)), 0x40) & 0xFFFFFF);
```
→
```
pv = *(u32 *)p;
pv = pv & 0xFF000000;
*(u32 *)p = pv | (CAST_NONSTRUCT(...) & 0xFFFFFF);
```

Let me test. First diff orig vs src.
