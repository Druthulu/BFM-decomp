---
ts: 2026-11-06T11:33:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RiE1TpQdxSRToYBgeydK
---
Body is spliced at the definition span. Good.

Now let me set up. Working dir is .run/P40/T11. I'll write files under G30/<dir>/.

First item: func_80015B6C. Copy orig.c: extract lines 2429..2487 (externs + def) — but note body_span covers only the definition (line of `void func...` through closing brace). Externs must be inside the body or already in TU. The orig has `extern void *func_80010A08(s32 a0); extern u16 D_800B9A02;` at file scope above; if I put externs in the body file they'd be inserted inside the function definition span? No — body file replaces only the definition span (line of def start to end). So the externs at 2429-2430 stay in the TU. For my body, I can include block-scope externs as in the example.

Wait: the block-scope `extern struct { s32 a; s32 b[4]; } D_800A651C[];` is inside the body already.

So orig.c should be lines 2432..2487 (just the definition). Let me generate with sed. Then a nopin/v0 body.

Actually "Start from the current def in src (copy to <dir>/orig.c)". Fine.

Let me use a python script to extract body spans? Simpler: sed -n '2432,2487p'. But freshness check: I'll verify by diffing later. Let me write a small script .run/P40/T11/G30/mk.py? The brief says scripts not inline python. Use Write tool for scripts under G30.

Actually simple sed commands are fine (ranged read allowed). Let me do:
sed -n '2432,2487p' ../../../src/800.c > G30/func_80015B6C__800/orig.c

Hmm, writing with `>` is fine.

Then v0: remove the 4 `__asm__ __volatile__("");` barrier lines and the 2 launder lines (2457-2458). Keep pins.

But wait — the launders at 2457-2458 are `__asm__("" : "=r"(x) : "0"(x));` which force x and y into regs at that point? Actually they're barriers/launders to keep x,y copies... Removing them changes codegen.

Let me write v0 and score.

Score via bin/dt.sh G30/func_80015B6C__800 G30/func_80015B6C__800/v0.c 4.

Let me first check what score the orig body gets (should be 0) — a calibration. dt.sh with orig.c.

Let's do it.
