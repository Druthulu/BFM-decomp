---
ts: 2026-11-06T12:05:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GUs4uIAItpwvyD1u6AYS
---
k3_inline = 12 (ORDER, 158 insns — same count as target!). Interesting: inlining `(u8*)&f.cx` in the call drops the extra insn.

Let me explore k3 further: it's lever-free, 158 ins, ORDER class, score 12. Let me see its diff.
