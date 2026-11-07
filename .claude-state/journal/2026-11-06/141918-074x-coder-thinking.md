---
ts: 2026-11-06T21:19:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cgahYvAbWLjWJEOXljpk
---
Item 2: kinds = launder. The launder is `__asm__ __volatile__("" : "=r"(pv));` at the end — an out-only asm that creates a 2nd set of pv, killing the sched1 birthing boost. This is the exact pattern from moves.md line 402: "launder | func_8018AB20 | MATCH: split `pv = pv & 0xFF000000` into its own stmt — a real live 2nd SET (reg_n_sets=2) demotes sched1 birthing boost; bytes identical (W47)".

But here, pv's real 2nd set already exists: `pv = *(u32 *)p;` then `*(u32*)p = (pv & 0xFF000000) | ...`. pv is set once (pv = *p) and used in the store. The out-only asm adds a 2nd set.

Per the moves, the crack: split `pv = pv & 0xFF000000` into its own statement — a real live 2nd set. Here we have `(pv & 0xFF000000)` inside the store expression. We can split:
```
pv = *(u32 *)p;
pv = pv & 0xFF000000;     // real 2nd set, live
*(u32 *)p = pv | (...);
```
This gives pv 2 sets (reg_n_sets=2), demoting the sched1 birthing boost. Bytes should be identical (the and is in the target anyway). This is exactly the W47/W48/W49 move.

But note: there are TWO pins in this function: `register s32 ang __asm__("$4")` and `register u32 pv __asm__("$3")`. The kinds row is only "launder", so the pins are NOT row kinds for this item — they may stay (levers of other kinds the def already had may stay). Wait, the constraint says "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added". So the pins (ang $4, pv $3) may stay. Only the launder asm must go.

So the fix: remove the `__asm__ __volatile__("" : "=r"(pv));` and split pv's mask into a real 2nd set. Let me check the src def matches orig.c (FRESH).

Let me diff orig.c against src. Find the function in src.
