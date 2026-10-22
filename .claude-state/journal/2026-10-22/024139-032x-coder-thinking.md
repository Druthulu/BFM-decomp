---
ts: 2026-10-22T08:41:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_1yOAWlB2tcXvE48iLqID
---
Excellent! This is very informative.

The .greg order: 73 74 76 83 72 — the allocation order of globals.

- r73: pri 10000, refs 4, live 8, conflicts sp, prefers a0
- r74: pri 10000, refs 4, live 8, conflicts v0,sp, prefers a0
- r76: pri 6000, refs 3, live 5, conflicts sp
- r83: pri 6000, refs 3, live 5, conflicts v0,sp
- r72: pri 4444, refs 4, live 18, conflicts v0,v1,a0,sp

Hmm, only 5 globals. r72 has live 18 and conflicts v0,v1,a0 → that's `ptr`? It conflicts with v0 (val), v1 (?), a0. Hmm.

r73/r74 are the two arm copies of q (each defined in an arm, used in the join): each has 4 refs? Hmm, q has 2 defs and 2 uses = 4 refs total. r73 and r74 each have 4 refs, live 8, and both "prefer a0"! And both conflict sp.

So the two q assignments are SEPARATE pseudos (r73, r74) — gcc didn't merge them because... they're in different blocks (each defined in an arm). Interesting! And the conflict sets: r73 conflicts sp, r74 conflicts v0,sp.

And r72 (live 18, conflicts v0,v1,a0,sp) is `ptr`: it conflicts with v0 (val), v1 (st/const), a0 (?).

Wait but where's `val`? val is a global (defined in 2 arms, used in join) — hmm, r76 and r83 (pri 6000, refs 3, live 5) might be the two val copies? But val's stores in the join use v0... r84/r85 are v0 with 2 refs live 4 in blocks 0 and 1 — those are the two `li v0,3`/`li v0,4`? no, those are local (block 0 and 1). Hmm, r84: v0, refs 2, live 4, block 0; r85: v0, refs 2, live 4, block 1. Those are the two val copies in each arm (defined in arm, used in join) — they're globals? The table says block 0/1 which means... hmm, "blk" for non-global is the block; for globals it's None. r84/r85 have blocks 0 and 1 → they're LOCAL pseudos in blocks 0 and 1! So val is NOT a global: each arm's val is a local pseudo in its block, and the join uses...

Hmm wait, in the asm, `li v0,3` in arm 2 and `li v0,4` in arm 1, and the join does `sh v0,2(v1)` — so v0 carries the value across the join. If the two vals were separate local pseudos in different blocks, then at the join, v0 must be the same pseudo... unless the join's `sh v0` reads a phi-like merged value. In GCC 2.7 (no SSA), the join block would need a single pseudo. So val must be one pseudo defined in both arms (2 defs) = r76 or r83? But r76/r83 have "None" block = global, refs 3, live 5.

Hmm: r76 (pri 6000, refs 3, live 5, conflicts sp) and r83 (pri 6000, refs 3, live 5, conflicts v0,sp). These could be the two val copies! But then the join's `sh v0,2(v1)` uses v0 which is r84/r85? That doesn't work across blocks.

Hmm, maybe the values 3/4 are stored into a common pseudo. Hmm, but r84 and r85 are local (block 0, block 1) with 2 refs each, live 4, and both allocated v0. So in the join, the value used is... 

Ahh, I bet: the two arms each compute their val into a *global* pseudo (r76/r83?) and then the join's store uses that. But r76/r83 have live 5 and refs 3, no hard reg assigned ("-").

Hmm, and r73/r74 (pri 10000, refs 4, live 8, prefer a0, no hard reg "-") — these are the two q's! q has 2 defs and 2 uses = 4 refs. Hmm, but two pseudos each with 4 refs?

Hmm, maybe r73/r74 are the two q copies: each q_i defined in an arm (1 def) and used in the join (2 uses: the two stores) = 3 refs. Not 4.

Whatever the exact mapping, the key output: the .greg order is "73 74 76 83 72" and priorities: r73 10000, r74 10000, r76 6000, r83 6000, r72 4444.

The allocation: global_alloc allocates in this order. r73 first, then r74, etc. r73 and r74 both "prefer a0" and conflict only sp / v0,sp.

Yet the result: q ended in a0! And r72 (ptr) has live 18 and conflicts v0,v1,a0,sp → r72 can't use v0, v1, or a0 → so r72 (ptr) got... it has no hard reg in the table ("-"). Hmm, all globals show "-" because the .greg dump is the INPUT to global allocation.

Right, the tool says: "a global allocno's hard register prints as `-` here; that is the dump's shape, not a gap, and the order line plus the preferences are what decide it."

So the .greg order line "73 74 76 83 72" is the allocation order, and each pseudo's conflicts/preferences decide the reg.

Key: r72 = ptr? conflicts v0,v1,a0,sp and live 18 → ptr is live from the entry load to the last call in the arms (long live range, 18). It conflicts with v0 (val), v1 (?), a0 (q's copies r73/r74 prefer a0!).

So the globals: r73, r74 (the q copies), r76, r83 (the val copies), r72 (ptr).

Now, the target (pinned q) — let me get the same table for the pinned version to see the difference. That's the key comparison! Let me dump the current src TU (with the pin) and read its table.

Wait, but with the pin, q is a hard reg and r73/r74 wouldn't exist as globals.

Let's think about what determines the final assignment in mine: q in a0, val in v0, const in v1, st in v1, ptr in a0.

global_alloc order: r73 (q copy 1), r74 (q copy 2), r76 (val copy 1), r83 (val copy 2), r72 (ptr).

For r73: conflicts {sp}, prefers a0. Available regs in GR_REGS: v0,v1,a0,a1,a2,a3,t0..t9,s0..s7. It gets a0 (its preference). Same for r74: conflicts {v0,sp} → also a0 (both can share a0 since they don't conflict? they conflict each other? r73 and r74 both prefer a0 and their conflict sets don't include each other's regs).

Then r76 (val copy 1): conflicts {sp} → but a0 is taken by r73/r74? Since they don't conflict with r76 (r76's conflict set is {sp}), r76 could also use a0! But the result has val in v0. Hmm, so global_alloc must be using conflict info between globals too.

OK. The .greg dump has more info. Let me look at the actual .greg dump section for this function to see the conflict sets and the "order" and preferences, which is the real input. Let me extract the function's section from c1.i.greg.

The file might be big; let me extract just the func_801815AC section with awk.

Actually the tool said: the order line ";; N regs to allocate: …" and ";; N preferences: …". Let me look at the raw .greg section.
