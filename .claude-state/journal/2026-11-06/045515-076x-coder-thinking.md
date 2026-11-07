---
ts: 2026-11-06T11:55:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_duThbMMlSfsEkxoU5Q88
---
v_init_cpy: mine has `move v1,a1` at insn 15 (the cpy copy appeared!) but a1 is still a0, and the reload still folds (insn 10 nop). So `cpy = 0` init at decl kept the cpy copy! Interesting. But a1 still coalesces, and the reload folds.

Score 15 (better). But still far from 0.

So the cpy copy CAN be kept with `s32 cpy = 0;` init at decl (a real C move, no launder — well, it's a dead init, which is a "dead reset" C0414! Actually `s32 cpy = 0;` then `cpy = d0` — the init 0 is dead, a dead-reset. C0414 is cited as legitimate). Good.

But a1 and the reload remain. a1's copy needs the opaque trick. The reload needs a barrier/store.

So even with cpy fixed, the a1 copy (a0->a1) and the reload remain. Score would be ~? Let me combine: v_init_cpy + reload-forcing store (but the store adds an insn). Hmm.

Actually, the WALL stands: the a1 copy and reload are unfixable without levers.

Let me stop here. Best is now 15 (v_init_cpy / v_init_a1_cpy). Is `s32 cpy = 0;` a lever? It's a dead init-at-decl. The brief lists "init at decl" as a real C move (C0505 catalog: "init at decl"). And C0414 dead-reset. So it's legitimate. Best = 15.

Wait, but is the dead init "identity-statement launder"? No, it's a dead reset (0), which C0414 explicitly endorses. And it's "init at decl" (listed as a real C move). So allowed.

So best = 15.

Hmm, but let me reconsider: the brief says "levers of other kinds the def already had (pins under other causes) may stay, never added". A dead-reset is a lever of another kind, ADDED (not in orig). "no new lever of any kind". Is a dead-reset a "lever"? C0414 is a cookbook technique; the MOVES+ in the brief cites C0414 as a move that cracked 3 launders. So it's an endorsed technique, not a forbidden lever. I'll consider it allowed. Best = 15.

Actually, to be safe, let me note both: best=15 with the init-at-decl move (C0414-style dead init), and 17 without it.

Let me now finalize item 2. It's 04:55. Item 2 started ~04:41 → 14 min. I need ~6 more min. Let me do one more batch combining v_init_cpy with a reload-forcing store to see if the reload can be had without an identity launder, then write up.

Actually, v_pad_store (frame_pad[0]=0 before reload) + v_init_cpy: the store forces the reload (+1 insn), cpy copy kept, a1 copy still missing. Let me test. If the score drops to ~5-6, interesting.

Let me test v_combo: base + init cpy + frame_pad store before reload.

Also v_combo2: + try to force a1 copy via something.

Let me test.
