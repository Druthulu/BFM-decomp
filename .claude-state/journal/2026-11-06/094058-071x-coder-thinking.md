---
ts: 2026-11-06T16:40:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OpHnmF3ACr4EAbt09lov
---
All variants: entry/then use $5 (a1), else uses $4 (a0). So the else block keeps using a0 — the param pseudo. The difference from target: else should use a1.

Also then-arm registers: mine has p=v0, f=v1 (`lw $2,32` p→v0, `lw $3,220` f→v1); target p=v1, f=v0. And else: mine q=v1, g=v0; target q=v0, g=v1.

So really 3 issues.

Let's tackle the else a0 issue by making the else block NOT see a0 as a valid equivalent. The else uses a0 because the else block's self uses were rewritten to the param pseudo (72). In s0's RTL, block2 (else) uses 73 (self)? Earlier w1 greg said 72 in 5, 73 in 4; the else asm uses $4=a0=73. And then uses $5=a1=72. So block1 uses 72, block2 uses 73. So in the RTL, block1 (then) uses 72 (param!) and block2 uses 73 (self). Let me verify from w1's RTL block1.
