---
ts: 2026-11-06T01:45:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4kdVvp5glPfi1wV07nkk
---
C0049.md line 44-45: "cross-jumped them into one block (−2 ins). Giving loop3 its own pseudo frees it into $v1, so `sw $zero,0($v1)` ≠ `sw $zero,0($a0)` and the blocks stay distinct." — This is the key: make the store's BASE register differ! But our target requires both stores use s0. Hmm, but wait: maybe in the target the two stores do use different regs and objdump shows... no, target shows `sw v0,28(s0)` at both 17cc and 1808.

Hmm wait, let me double check the target dec store: at 17cc `a602001c sw v0,28(s0)`. And zero at 1808 `ae02001c sw v0,28(s0)`. Both s0. Identical.

So the ONLY difference is context. And the original compiler did not merge them. How?

Let me look at C0168.md:323 "The RETURN-label half is REFUTED. jump.c:2005-2031 cross-jumps RETURN insns against each other at..." — let me read that.
