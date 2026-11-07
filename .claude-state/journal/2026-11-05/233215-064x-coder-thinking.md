---
ts: 2026-11-06T06:32:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lXim1vBhlfItJvxtIqCy
---
This is func_80183534, 96 ins. Levers:
- pin $2 (w2), pin $3 (oidx)
- launder: `__asm__ ("" : "=m"(D_800A5E60) : "r"(mulc));` — an out-only memory launder with mulc as a "r" input.

Let me first score the orig to confirm baseline, then write a naive delever.

The launder: `__asm__ ("" : "=m"(D_800A5E60) : "r"(mulc));` — it ties mulc into a register for the asm (making it live) and clobbers the memory at D_800A5E60.

Then `pkt = D_800A5E60;` — the store `D_800A5E60 = pkt + 0x28;`.

Let me look at the target asm to understand. First baseline score + naive delever.

Naive: drop pins and the asm. Let me write w0.c.

For the pins: `register s32 w2 __asm__("$2")` → `s32 w2;`, `register s32 oidx __asm__("$3")` → `s32 oidx;`.

For the launder: remove the asm line entirely. But the asm has "=m"(D_800A5E60) which is a memory clobber — removing it might change the load/store ordering. A real-C replacement: maybe a dead-reset (C0414) or the load of D_800A5E60.

Note the comment "L3 — zero bytes" and the launder is "out-only". Since mulc is an input "r", it forces mulc into a register.

Let me score w0 first.
