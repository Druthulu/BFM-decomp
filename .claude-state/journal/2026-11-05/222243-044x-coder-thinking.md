---
ts: 2026-11-06T05:22:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_561RuGnu5x6LaFi3rSrc
---
w4 and w6 score 0! MATCH!

w4: `do { raw = t; } while (0);` — do-while splitting the EBB, giving the load result v1.
w6: `raw = (s16)t;` — HImode copy.

Both score 0. Great. Let me verify: w4 is a do-while around `raw = t` in v3 (with the copy before the branch). Let me confirm w4 content and that it's lever-free (no pin/launder/asm/barrier/keepalive). The do-while has the // !FAKE: do-while comment. 

Let me verify w4 with a full dt run and check the asm matches. Also confirm the kinds are gone.

Let me copy w4 to win.c and re-score. Also, is `do { } while (0)` allowed? Yes, with the // !FAKE: do-while comment (C0535). Not a "lever" in the row kinds (launder,pin), and the constraint says "no new lever of any kind" — do-while is a real C construct (allowed, per moves.md C0535 and the constraint "do{}while(0) only with // !FAKE: do-while").

Hmm, but is do-while(0) considered a lever? The constraints say "no new lever of any kind" but explicitly allow do-while with the comment. So it's fine — it's a real C construct.

Let me finalize w4 as win.c and verify.

Time check: ~30 min on item 1. Good.

Let me look at w4 content.
