---
ts: 2026-11-06T09:19:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fneZYXX0hb5oR5aYAaBf
---
The combine dump starts at 13533 and "Combiner statistics" is for the whole TU? It says 30 successes. Let me find our bVar1 pseudo. In the RTL, bVar1 is a register variable pinned to $8: it appears as (reg:QI 8) probably, since register vars use their hard reg number directly? In GCC RTL dumps, a register variable is `(reg/v:QI 8)`. Let me grep for `reg/v:QI 8` and `(and:QI` / `0x10`.
