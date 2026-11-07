---
ts: 2026-11-06T16:43:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hUdBPQHbnT6qYnJ9yfHH
---
Interesting: w5_maskffff (SImode ret, test `(ret & 0xFFFF) == 0`) gives 104 ins and 7. That's the SImode route with an extra andi 0xffff — the branch tests the andi result. But maybe this one has the move! Let me check its diff: if the sequence is `move $3,$2; andi $2,$3,0xffff; beq $2,$0; andi $2,$3,0x8000`, then it's like r16 but with SImode ret — and the andi 0xffff is *dead*? No, it's used by the branch.

Hmm, 104 = one extra. But if the branch used $3 and the andi 0xffff were dead, flow would delete it → 103. Let me look at the diff to see.
