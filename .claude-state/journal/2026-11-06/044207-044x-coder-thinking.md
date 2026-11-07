---
ts: 2026-11-06T11:42:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WeWxoTeQ9dKtOMVU7G6X
---
Now item 2: func_80182334 (barrier,pin). Def at lines 6672-6708 in src/ov_SC05_008/ov_SC05_008_jr_8017AE2C.c.

The levers:
- `register s32 zr __asm__("$0")` pin
- `a1 = a0v + zr` opaque copy
- `__asm__ __volatile__("" ::: "memory")` barrier
- `cpy = d0 + zr` opaque copy
- `frame_pad[2]` with `(void)&frame_pad` (frame trick, not a lever of barrier/pin)
- `goto skip`

I need to remove zr, both `+ zr`, and the barrier. Let me extract orig.c, baseline, then create a lever-free body.

Let me first extract and baseline. Also note there's a sibling? Let me check moves.md for func_80182334 — earlier grep found nothing. But maybe a similar function was cracked. Let me grep for "0xDC" or "func_801823" or "RC-12" in moves.md. Actually let me first look at the target disassembly and baseline.

Let me extract orig.c and baseline.
