---
ts: 2026-11-06T08:40:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cVKGLaLmi43YNXvAQY3P
---
c2 scores 0! Moving the pointer assignment before the outer if makes it match. Interesting — so the addiu is placed correctly.

But wait: c2 declares `void *a0pin;` at function scope and assigns before the outer if. Does that mean the address computation is at the right place? Score 0, 57 insns. 

But is c2 "lever-free"? It has no asm. Yes: kinds = keepalive, and there's no asm/keepalive macro. The `void *a0pin;` + `a0pin = sp18;` is real C. Good.

However, one concern: the assignment `a0pin = sp18;` before the if is a dead assignment when D_801270C8==0 — but it's real C and compiles to the target. Fine.

Let me double-check c2's body and verify it scores 0 via dt.sh (which uses the tail). Also check no leftover asm.

Actually sc.sh reported score 0 (OTHER; mine 57 target 57). Good.

Now write win.c = c2, append results row, notes, then moves.md line.

Wait — before that, let me double check the diff to make sure it's byte-identical (score 0 means so). Also I should ensure win.c is a bare definition.

Let me look at c2 content.
