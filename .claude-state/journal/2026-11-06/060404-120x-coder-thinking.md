---
ts: 2026-11-06T13:04:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UfNCcIL8dQzEl30goHn2
---
Still 2. Let me look at this from the sched angle: maybe the difference isn't sched1 but the *emission order* — the target's `addiu a0,a0,4` after `li v0,36` might come from the RTL order: if the C has `dp = dp + 1;` AFTER `c36 = 0x24;` and before `df = ...`? I tried s1 (moved dp++ after c36) → 2.

Hmm, but s1's asm? Let me check if s1's RTL order is lw, addiu, li or lw, li, addiu.

Actually, let me look at the p2 dump's pre-sched RTL (.rtl) to see the order and then think about what sched1 did.

Time: item 3 is at ~35 min now (05:52 → 06:27). I'm past the 30-min budget. Per the brief: "past 30 min stop and record a wall". I have 48+ tries and ≥20 min. Let me stop item 3 now as a WALL (best 18 lever-free; note p2 = 2 with the launder kept).

Let me check the time to be sure.
