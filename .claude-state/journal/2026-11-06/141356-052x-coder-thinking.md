---
ts: 2026-11-06T21:13:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4vhvO0FOdJaArwLghioB
---
Confirmed: after flow, only one set of v0 (the lw), and the move is gone. The dump matches 42 ins. So the pass deleting it is flow (or expand before). Let me check the .rtl (pre-flow) for the move. Actually the .rtl dump is after each pass; let me check the .cse or .combine dump for `set (reg:SI 2 v0) (reg/v ... a0)`. Let me grep the .combine dump.

Actually the evidence is enough: the target's `move v0,s0` is a dead set of v0 that flow removes; the only way to keep it is the $2 pin + asm. Let me confirm the pre-flow RTL had it. Grep .combine for "set (reg:SI 2 v0)" count.
