---
ts: 2026-11-06T10:32:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_p0gh15AplIYlR0ZyRpif
---
Item 2: 24 + 8 = 32 tries. Best lever-free = 21 (nopin). Wall.

Wait, u3 scored 27 (REG-mixed) — the separate `e` variable. Still not 0.

Item 2 wall tag: the pin (d→s0) fails because s1ang (local) takes s0. Tag `lreg-qty-priority` or `lreg-hardreg-live-end` or `global-hardreg-reserve`. The mechanism: local-alloc gives the local s1ang $s0, so the global d can't. Tag `lreg-qty-priority` (local-alloc qty priority gives the hard reg to the other pseudo).

Hmm, actually there's a more specific tag: `lreg-hardreg-live-end` — "a hard reg stays live to the block end, so the target pairing cannot form". Not quite. `lreg-copy-pref-dying-base`? No.

I'll use `lreg-qty-priority` for item 2.

Item 3: ~34 tries already. Best lever-free = 5. Wall tag: the do-while cracked the pin; remaining is the keepalive ordering (sched1) + the sign-ext temp. Tag `sched1-birth-order` or `lreg-qty-priority`. Hmm, the residual is the a-mask hoist (sched1) and the sign-ext temp (local-alloc). Let me use `lreg-qty-priority` for the sign-ext temp? Or `sched1-birth-order`.

Actually, the best lever-free body (f1) had the a-mask hoisted (sched1) and the sign-ext temp (local-alloc). Two mechanisms. Let me use the primary one: `sched1-birth-order` (sched1 orders the andi before the call). Hmm.

Actually, let me reconsider: maybe with the keepalive cracked by a real anchor, the score would be 2. The anchor is the issue. Let me use tag `sched1-birth-order`.

Hmm, wait. Let me reconsider item 3's wall: maybe I should try harder to crack the keepalive. The keepalive anchors `ang`. What real C use of ang is there? `cur = ang & 0xFFF`. If I move `cur = ang & 0xFFF` to right after `ang = ang - 0x400` (before the div sign-ext), then ang is used there. But the target order has cur AFTER the a-mask.

Hmm, but sched1 might still order the a-mask correctly if ang's use is early? Let me test: f1 with cur computed right after ang.

Actually, I did k1 (cur before a) → score 5. Let me test cur right after ang (before div sign-ext).

Hmm, let me try a couple more item 3 variants since it's close (best 5):
- p1: f1 with `cur = ang & 0xFFF;` immediately after `ang = ang - 0x400;`
- p2: f1 with a real use of ang in the div sign-ext? e.g., `div = (s16)div;` no.

Let me test p1.

Actually, I realize I should manage context/time. I've used a lot. Let me prioritize finishing: item 4 needs ~21 more tries, then write results and log.

Let me do item 4's batch now (21+ variants), then write everything.

Item 4 variants: generate many perturbations.
