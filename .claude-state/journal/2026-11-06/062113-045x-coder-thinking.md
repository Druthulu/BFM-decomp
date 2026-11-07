---
ts: 2026-11-06T13:21:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MHDwPON8fJ2fkqXim7ss
---
Very close: an `addiu a1,sp,16` (buf address) is born 5 insns later in mine than in the target. The barrier was between `nn = (s32)buf;` and the s0 computations. Removing it lets sched1 sink the `addiu a1,sp,16` (the buf address) later (or the barrier held it).

Target: addiu a1,sp,16 at index 109 (right after nn = (s32)buf presumably), mine at 114.

The pins aa($4), nn($5). nn is `register s32 nn __asm__("$5")` — so nn = (s32)buf generates `addiu a1,sp,16; move $5,a1`? Hmm, the target shows `addiu a1,sp,16` — with a1? But nn is pinned to $5. Let me look at the actual code around there in both.

Let me dump the target and mine around index 100-120.
