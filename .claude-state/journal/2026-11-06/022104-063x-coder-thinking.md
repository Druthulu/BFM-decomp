---
ts: 2026-11-06T09:21:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jQlURqafOOIn4SIZFPXF
---
The dumps were made for item2 (different tag dir). I made dumps_d1 in item2's dir. Let me dump for item 4 candidate and the target (orig). Actually the target's loop dump requires the TU with pin. I can dump both. But this is getting expensive. Let me time-box item 4: try ~8 source variants.

Key hypothesis: target's giv e is NOT eliminated into base; mine's is. What source difference could do that? In the source, `e` is assigned inside the loop (`e = (Sub_80180A54 *)(base + 4);`). Both versions same source! The only difference between orig and p2 is the pin declaration. So loop.c's decision is *not* source-driven but pressure-driven? loop.c runs before register allocation; the pin adds a hard-reg pseudo but loop.c doesn't know about hard regs... Actually loop.c's `insn_count` and `threshold` depend on loop size; same. Hmm, but `regs_live`? loop.c's giv elimination: `v->replaceable`... The pin introduces an extra REG (the hard-reg pseudo $2) that is set in the loop (v0 = base; v0 = 0). Hmm! `v0 = (u32*)base` is a SET of v0 in the loop. In target, v0 is $2. In p2, v0 is a normal pseudo. loop.c's biv/giv analysis sees `v0 = base` (a giv, mult 1, add 0). Maybe this changes the iv_class structure: `base` gets a biv, `e` and `v0` get givs. And maybe the presence of an extra giv using base changes `bl->biv_count`/`n_times_set` such that `maybe_eliminate_biv` behavior changes.

Look: in the target, the value `v0 = base` is $2. loop.c sees SET of a hard reg (regno < FIRST_PSEUDO) — `record_biv` only handles pseudos? Actually `v0 = base` with v0 = hard reg $2: loop.c's record_biv requires dest_reg to be a pseudo (regno >= FIRST_PSEUDO_REGISTER). So the hard-reg set isn't a biv. But it still mentions `base` (as a source). `n_times_set`?

Alternatively: `maybe_eliminate_biv` for `base` fails in the target because of the `v0 = base` insn? No, `v0 = base` is a copy, eliminable.

Hmm, wait. Maybe the difference is in `combine_givs` (giv combination), where two givs (e and v0, both = base + const) are combined: in target, v0=$2 is a hard reg, so combine_givs can't merge e with it. In p2, v0 and e are both pseudos with the same base and add_val 0 vs 4: `combine_givs` merges givs with the same biv and mult_val by choosing one as the "winner" and using offsets from it! Yes! combine_givs picks a giv to be the base for the others. If v0 (add_val 0) and e (add_val 4) share base, combine_givs may pick v0 as the canonical and express e as v0+4 → folded into offsets. That's exactly what mine shows: s0 = v0 = base (add_val 0) and accesses at +6 (4+2). In target, v0 is hard $2 → not a giv → e stays canonical.

So the real-C move: prevent the extra giv `v0 = base` from being a pseudo that combine_givs can merge. Options:
- Change the order: `v0 = (u32*)base;` is inside the if-block, before goto epilogue. e is used throughout. Hmm.
- Make v0's value not `base` directly but `(u32*)base` with a cast that doesn't create a giv? It's already a cast.
- Assign v0 from a different expression, e.g. `v0 = (u32 *)D_801DA130 + i*6`? no.
- Make v0 = base happen outside the loop? It's the return value; could compute it at the epilogue: `epilogue: v0 = ...`? But then it must be base (the found element) — need to keep base. Actually target computes `move v0,s1` at the goto (3268: move v0,s1 in the j delay slot) — v0 = base. And at 327c `move v0,zero` for not-found.

What if we restructure to avoid the `v0 = base` copy: use `goto epilogue` with a separate variable... The copy is needed.

What if the loop uses `e` as the return: `v0 = (u32*)e - 1;`? That changes target.

Hmm. What if we make `v0` a *different type* so it's not a simple copy? E.g., `v0 = (u32 *)base;` is a copy. 

What if the return value is written as `v0 = (u32 *)(base + 0);`? folds.

What if we swap which is canonical by making e not a giv but a direct access: e.g. use `base[4]`-style accesses? Then no e giv, and accesses base+4+off — that's what mine does, and target needs e.

So we need combine_givs to pick e (add_val 4) over v0 (add_val 0)? combine_givs picks based on... let me look at combine_givs in loop.c.
