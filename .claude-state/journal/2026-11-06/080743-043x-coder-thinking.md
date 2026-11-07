---
ts: 2026-11-06T15:07:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9tgGdWtU3jrMxHNSxB9E
---
The grep is noisy. Let me directly extract the function's RTL from each dump for the pre-loop a0 set. Search for `(set (reg/v:SI 4 a0)` — a0 is a pinned hard reg. In the no-launder body, `a0 = s0 << 10` pre-loop. Let me find the insn in the .rtl dump and follow it. Let me grep for "ashl" near the start.

Better: extract the function region from each dump file and look at the first ~20 insns. Let me find the function start line in the .rtl dump.
