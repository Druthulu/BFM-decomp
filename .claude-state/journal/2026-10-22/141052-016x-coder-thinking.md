---
ts: 2026-10-22T20:10:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hChhw2wNor5ZNDEYGd0T
---
Right: without the launder, cse substitutes the symbol address into each load → lui per load. Score 20.

So the target's copy is a block move from the symbol held in a1: the source address is loaded once (lui/addiu a1) and 8 lw with constant offsets. That's exactly `*(Mat32 *)m = D_800AE620;` (struct copy) — the movstr/struct assign from the global. Good, c_struct approach is right.

Now the remaining issue: the dest address pseudo. In target, dest stores are sp-relative direct; and the call arg address is rematerialized. Mine: dest stores also sp-relative direct (same as target), and the call arg is in s1.

Wait — maybe in the target, the address pseudo for the call args is *not* cse-merged with anything, and it's a `symbol_ref`-like... no, it's sp+16.

Difference: the target's m is likely a local array `int m[8]` accessed by the calls as `(void *)m`. Mine identical. Hmm.

Let me compare with what the launder+pin body produces (score 0) to see how the address is handled there. Score the original with levers: dt.sh orig.c. Actually the src def scores 0 by definition; let me dump it.
