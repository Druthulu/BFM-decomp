---
ts: 2026-11-06T10:00:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EmIc7uN0COX0OTxxQ2ms
---
Now v1 changed the code order: mine has lw v1,76; lw a1,84; ... then later sh v1,6; sh a1,14. So sched1 reordered the two loads together and the stores later. That's worse (count diff 7 still). The separate-u variant caused scheduling reorder.

Hmm. So the loads got grouped. Target: lw v0,76; lw v1,84; sh v0,6; ... wait target: 52 lw v0,76; 53 lw v1,84; 54 sh v0,6; ... 58 sh v1,14. Actually target also groups the loads: 52 lw v0,76; 53 lw v1,84; 54 sh v0,6. So target has both loads before the first store! Mine v1 has lw v1,76; lw a1,84; ... and stores later at 58/59. The difference is the store position.

Wait in the original nopin.c: mine 52 lw v1,76; 53 lw v0,84; 54 sh v1,6. So the store came right after the second load, like target. With separate u, the store got delayed to 58. Hmm, because the scoping `{ s32 u = ...; ... }` changed something.

Let me step back. The real issue in nopin.c: t=v1, tb=v0 (swapped), and the store positions are fine (54 sh v1,6 matches target's 54 sh v0,6 position). So nopin is very close: just the v0/v1 assignment and the final move.

So I need t→v0, tb→v1. In nopin, t=v1, tb=v0. My priority reasoning said t should get v0 (higher pri). But it got v1. So maybe tb's priority is actually higher: tb has n_refs=2, t has n_refs=4. pri = floor_log2(nrefs)*nrefs*size/(death-birth).

Wait, I assumed birth/death are insn indices. But qty_birth/death in local-alloc are INSN_UIDs of first/last use. Let me reconsider: maybe t's n_refs is 3 (2 defs + ... ) hmm.

Actually maybe local-alloc's "quantity" for t includes only the second def? Let me look at how many insns each spans.

Let me instead empirically find a C change that flips them. Ideas:
- Make `tb` a different type (u16) — changes size/refs.
- Make `t` used more times (extra ref increases pri).
- Make tb's life longer.
- Change declaration order (affects qty numbering tie-break only if equal pri).

Actually, here's a cleaner idea: the target's t is in v0 for BOTH its defs. In mine t is in v1 for both. What if I split t into two separate variables (one for unk4C, one for unk50)? Then each has n_refs=2, life short. Hmm, I tried u and got scheduling change.

What if instead I make `tb` not a separate variable but a reuse of t? i.e.:
```
t = s0->unk4C; s0->unk6 = t;
t = s0->unk54; s0->unkE = t;
t = s0->unk50; s0->unkA = t - 8;
```
Then only one qty (t) → gets v0. And target uses v0 for unk4C and unk50, but v1 for unk54. So using one variable would put all in v0, mismatch at unk54 (target v1). Unless the store at unkE (sh) uses v0 vs target v1 → mismatch.

Hmm.

Alternative: what makes tb get v0 in mine? tb is defined at insn 53. If tb's priority were lower than t's, t would get v0 first. Let me compute again with real numbers by instrumenting? Hard.

Let me try: increase t's refs by using t an extra time harmlessly, e.g., `s0->unk6 = t;` plus a dead-ish use? A dead use would be eliminated. 

Or extend t's live range: move the unk50 assignment earlier (before the unk54 block) so t lives longer:
```
t = s0->unk4C;
s0->unk6 = t;
t = s0->unk50;
s0->unkA = t - 8;   // but this changes statement order → code order
tb = s0->unk54; ...
```
No, order changes.

Let me look at the qty priority formula precisely: pri = floor_log2(nrefs) * nrefs * size / (death - birth). 

For t in nopin: defs at insn 52, 55; uses at 54, 59. nrefs=4. birth=52, death=59 → span 7. pri = 2*4*1/7 = 8/7 = 1.14.
For tb: def 53, use 58. nrefs=2. birth=53,death=58 → 5. pri = 1*2*1/5 = 0.4.
So t higher → allocated first → should get v0.

But observed t=v1. So either nrefs differ or birth/death differ.

Maybe local-alloc's n_refs counts REG_N_REFS, and t is one pseudo but the first `t = unk4C` and second `t = unk50` are DIFFERENT pseudos (register allocation creates a new pseudo per set? no). Actually GCC's `t` is one pseudo-register with 2 sets. REG_N_REFS counts references.

Hmm, unless cse/regmove split t. 

Alternatively maybe the qty for t and tb is the same qty? No.

Let me just instrument: write a scratch script that compiles nopin and dumps the cc1 -dl (local-alloc debug) output. tools/cc1_dumps_tu.sh might do that. Let me check it.
