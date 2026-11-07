---
ts: 2026-11-06T05:23:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Yl1zzKgBmuDGEJJi2EUD
---
`S_AE7BC` = {u32 *f0; s32 pad[4]} = 20 bytes; `S_AF634` = {s32 g0; s32 pad[2]} = 12 bytes.

Hmm, `D_800AF634[*q].g0 = acc + ((...))` — reading/writing a struct member. No temp.

Let me test the probe with these exact structs and the acc/t block. Maybe the `s32 t = ... - 0x14;` and `>> 2` with the asm causes a temp. Let me refine gen2 with the real body exactly (minus the include) — actually the real body IS what I have. Let me just bisect by deleting parts of the real body and checking the frame via hdump. That's a compile per variant (a few seconds). Let me automate: write variants of orig.c and check `.frame` from the .s.

Actually, simpler: use the probe harness with the exact struct types and the full body (with dummy symbols). Let me write gen3 with the real body text.
