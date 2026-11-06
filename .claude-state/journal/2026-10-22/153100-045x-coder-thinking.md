---
ts: 2026-10-22T21:31:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wU5cGKOEpZHTM6b97RMd
---
v21: single insn position off — `sh zero,36` should be one slot earlier. In v21 arm1's source order is S(unk2E), P(unk20), Q(unk22), R(unk24), k(unk30).

The residual is at mine[53] = 1388+53*4 = 0x1464 → arm1's region. Target[53] = sh zero,36.

Hmm, which arm is it? Let me get v21's full disassembly.

Score 2 with one ORDER mismatch. Let me see exactly.

Let me dump v21.
