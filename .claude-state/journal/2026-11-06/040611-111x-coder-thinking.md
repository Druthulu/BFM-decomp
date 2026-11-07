---
ts: 2026-11-06T11:06:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7kxsrf2e1yduiKRbO2s8
---
z_nu16 adds an andi (u16 → zero extend) — not better.

So item 3: WALL, best 4, tag dbr-delay-fill.

Evidence: "reorg: the if-body asm fence stops the forward scan so beqz fills from the branch target (addiu v0,s1,1); without it reorg fills from the fall-through (move a0,s0); n=s16 fixed the outer cross-jump copy (best 4, 143/144 ins)".

Let me record it, then do item 4.

Item 4: func_8018B238 (the twin of item 3, in ov_SC03_001, calling func_8018B478 directly). Its orig is similar. Let me apply the same treatment: base lever-free + struct alias + n=s16, and score. Then a batch of variants to reach 30 tries, then wall.

Time: it's ~05:00. I've been going for ~1h45. Let me push to finish.

Let me record item 3 and move to item 4.
