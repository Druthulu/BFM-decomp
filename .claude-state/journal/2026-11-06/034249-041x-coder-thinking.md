---
ts: 2026-11-06T10:42:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_B5UpPQHHnQov6pBHfYsR
---
Same 11 (load hoisted to 19). Let me check the diff: probably same as v_param: load at 19, then ori/sw and store order.

Hmm.

New approach: use the enumeration. Let me write a generator that produces variants systematically:
- with/without do-while around S2
- permutations of S2,S3,S4
- |= vs temp
- with the temp and store orders

Let me script it. Each candidate: score via sc.sh (it accepts multiple files). I'll generate ~24 variants and score them.

Template: take the v_param body (parameter-direct, no pins/barrier, t temp) and substitute the tail lines.

Let me write a Python script gen.py in the item dir that emits variants and then run sc.sh on all. Actually sc.sh prints one line each; 24 lines is fine.

Let me define the tail as a placeholder. I'll build from v_param.c by replacing the 4-line block.

Simpler: write the whole body in the generator as a template with {TAIL}.

Let me do it.
