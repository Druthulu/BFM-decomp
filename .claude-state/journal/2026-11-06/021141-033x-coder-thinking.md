---
ts: 2026-11-06T09:11:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aakzImggIGPZouWjTmuI
---
Line 287: func_800CD494 — same TU! "void def but callers cast to s32(*) and use the return; flow deletes dead rv; s32 def conflicts with callers extern void src:237; a dead for-loop use reaches 0 but is a new lever (G24)". That's the exact same wall, same TU. So item 1 = WALL expand-void-return.

But interesting: "a dead for-loop use reaches 0 but is a new lever". Hmm, so someone found a trick reaching score 0 but it's a new lever. Not allowed.

Wait, but for func_80184D28 (line 28), MATCH was via "keepalive replaced by return v0; (s32 fn returned nothing...)". So that function's definition was already s32 (the fn returned nothing) and flow kept v0 sets only via asm use. Hmm, that means making the function s32 and adding `return found;`... no, "keepalive replaced by return v0" means they removed the keepalive and... the fn was already s32 in src. So the return value was kept by the callers' use? Actually "flow kept v0 sets only via asm use" - hmm.

Anyway, for our TU, func_800CD494 hit this wall in G24. So item 1: WALL expand-void-return, best 1. But I need ≥30 scored tries and ≥20 min. Let me not overdo: I'll generate a batch of real-C variants quickly (20-30 candidates), score them all, record best, and move on. The rule says "fewer is not an attempt" — I must reach 30 tries on the item if I record a WALL. Let me do that efficiently with a script generating variants.

Actually, wait. Let me reconsider: maybe the wall is avoidable. The G24 note says "a dead for-loop use reaches 0 but is a new lever". What's a "dead for-loop use"? E.g. `for (rv = found; 0; ) ;`? That keeps the value... Hmm, that's a lever (loop.c ref weight). Not allowed.

What about a real C use that produces exactly `move v0,s2`? If found is used in a call to a varargs? no.

OK, WALL. But let me be efficient: I have 5 items and limited time. The 30-tries rule applies per WALL item. Let me write a variant generator for item 1 and run 30 candidates. Actually, generating 30 distinct real-C variants is doable: vary decl order, temp widths, loop shape (while vs do-while vs for), statement order, init at decl, pointer reuse, etc. Most will be near-identical scores. The point is to show none reaches 0.

Hmm, but the rule also says ≥20 min per item. I can spend the time on real attempts.

Let me think about whether there's a smarter approach for the whole shard: all 5 items have kinds keepalive,pin. Likely all are "dead value must reach v0" walls or genuine cracks. Let me quickly look at the other 4 functions first to gauge (cheap: grep the defs). Then plan.

Actually, the brief says do not stop between items, budget per item. Let me look at all 5 defs quickly.
