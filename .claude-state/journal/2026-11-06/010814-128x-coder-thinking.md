---
ts: 2026-11-06T08:08:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_No3CBUlnAiyPRn8CjN1b
---
v33_vt_dw scores 0! Let me verify: it swaps the two stores AND reorders v/t loads before m/ang AND wraps m/ang in a do-while. Score 0, 68 ins.

Wait, but the do-while is `// !FAKE: do-while` — allowed per constraints ("`do{}while(0)` only with `// !FAKE: do-while`"). And it's not a keepalive/launder; it's the C0535 block-split move. Good.

Let me verify v33 with dt.sh and check no asm/register. Then win.c.

But hold on: is v33's source a legitimate real-C body? It reorders statements (allowed: statement order) and adds a do-while block (allowed, C0535). The do-while is 0 bytes and splits cse1's EBB. Good.

Let me double check the score with a fresh dt.sh run.
