---
ts: 2026-11-06T08:41:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ky6mZNADbQO08z0XvmbA
---
Without the asm, gcc emits `negu v1,s1` (negating nudge directly, which lives in s1), whereas target has `negu v1,v1` — meaning target first did `move v1,nudge` (or the copy) and then negated v1.

Wait: target `negu v1,v1` implies v1 held nudge via a `move v1,s1`? Let me look at the surrounding target asm. Let me disassemble the build object for func_80187988 around insn 45-55.
