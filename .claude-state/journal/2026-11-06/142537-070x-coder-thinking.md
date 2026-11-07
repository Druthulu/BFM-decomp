---
ts: 2026-11-06T21:25:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_e08Ws4ffYceGgma1OyY3
---
The wall tag `sched1-ready-order` (O03x: "sched1 ready-list tie order puts two independent insns opposite to the target") fits perfectly: the li and the move are two independent insns, all priority 1, and the ready-list tie order differs.

Item 2's wall time: started 14:09, now 14:25 = 16 min. Hmm, I need 20 min for item 2. But I've moved on to item 3. Hmm.

Wait — I need to be careful: the wall requirement applies per item. Item 2 has 70 tries but only ~16 min of wall clock. Item 3 has ~10 min so far.

Hmm. The intent is clearly "don't give up too early; 20 min of effort and 30 tries". I've done 70 tries on item 2 — that's ~2x the try bar. But the time bar is explicit. I could continue item 3 work until 14:30 and then record item 2's end time as 14:30 (since I was working in the same session, but not on item 2...).

Honestly, the rule's purpose is to prevent premature walls; 70 tries is strong evidence. But to comply literally, let me continue doing item-3 work now (which is progress) and record item 2's end when I finish it — the wall record will say 14:09-14:30 (21 min) which includes the item-3 overlap. That's not honest.

Better: continue item 2 for 4 more minutes? That's wasteful. Alternatively, note the honest times: item 2 start 14:09, end 14:25 (16 min) — but then the WALL doesn't meet the bar.

Hmm. Let me re-read: "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

I think the intent: you must spend at least 20 minutes trying before declaring a wall. I've spent 16 min on item 2 (with 70 tries, which took real time). Let me do a few more item-2 attempts to reach 20 min — but that's ~4 min of genuine exploration. I could revisit item 2 with new ideas:

Item 2 ideas not yet tried:
- The function's return type via a *local extern* trick? no.
- What about `*a0 = rv;` where rv is the result of a *call* that returns a0? e.g., `rv = (s32)func_XXX(...)`. no.
- What about making the copy `rv = (s32)a0` be a *call argument* to a function that returns... no.

Hmm, what about the possibility that the `move v0,s0` comes from `rv = (s32)a0;` if rv is used in the *store* as the value: `*a0 = rv` where rv=a0? That's `*a0 = a0` — wrong.

Wait, actually — what if the *target's* store `sw v0,0(s0)` is the store of rv=sp20 and the `move v0,s0` is... yes.

Alternatively: could the C be `*a0 = rv;` and then `return;` with the function's return type being void, but the *caller* expects... no.

I'll do a couple more item-2 variants (e.g., using `s32 *a0p = a0; *a0p = rv; ...` or `a0[0] = rv;`) — already tried v36/v37.

Hmm, honestly, there's nothing left. Let me just wait until 14:30 doing item-3 exploration and then record item 2's times honestly as 14:09-14:30 (21 min), noting that the last few minutes were item-3 analysis. That would be dishonest in the log.

Alternative: continue item 2 with a genuinely different approach for 4 minutes: e.g., dump the cc1 flow dump to verify that flow deletes the set (evidence for the wall). That IS item-2 work (verifying the mechanism), and it's useful for the evidence field. Let me do that: dump item 2's body and check the .flow/.lreg to show the copy is deleted by flow. That's legitimate item-2 work.

Let me do that: splice w1 into the item-2 TU (I have splice.py), dump, and check whether the `rv = (s32)a0` set exists before flow and is gone after.

The TU is src/ov_SC03_110/ov_SC03_110_jr_8017FBC8.c. Splice w1.c (but w1 has no `rv = (s32)a0` at all!). I need a variant with `rv = (s32)a0` (v02-ish). Let me use v02.c (which has `rv = (s32)a0;` at the end). Dump and look at .flow to confirm the set is deleted.

That's a solid verification of the wall mechanism. Let me do it.
