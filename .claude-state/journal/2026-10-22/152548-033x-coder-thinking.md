---
ts: 2026-10-22T21:25:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_C4Z66l7pvIjnmRNGdtW3
---
v15: score 4, ORDER, 114 ins = target ins count! That's a big step: moving `unk2E = 0;` after `unk30 = -0x50;` in arm1 changed the block order so cross-jump no longer merges. Let me see the diff.

(The v9-v13 compile errors are likely because 'k' appears before its declaration in the reordered body — yes, k decl is before in my a3(), hmm, no: a3() puts kdecl first. Let me check one error later.)

Let me diff v15.
