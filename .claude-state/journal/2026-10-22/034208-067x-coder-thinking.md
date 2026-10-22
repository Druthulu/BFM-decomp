---
ts: 2026-10-22T09:42:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_BotPN62iSCWS72UMCrAA
---
No expand.c. OK.

Let me now go empirical, but smart: the key question is "what C spelling keeps the pointer as a REG in the address expression".

Empirical hypothesis to test first (cheap): using p in TWO places prevents the constant substitution (the "lone use" rule from moves.md). Let me test:
- Variant X: `s16 newval = p[idx].f0;` (using p for the newval too) — expect the count to change (110) but let's see the diff; maybe it produces "addu v0,a1,v0" at the final add and only loses the "lui at".

Let me check the score/diff for that variant. If the final add becomes pointer-first, then I know the mechanism, and then I can look for a variant where the newval load still materializes its own symbol copy.

Hmm! Idea: what if p is used twice but the second use is the SAME as the first in a way that cse can share, e.g.:

```c
s16 newval = p[idx].f0;      /* use 1 */
...
D_801270C8 = *(s16 *)((u8 *)p + off + 4);   /* use 2 */
```
With p used twice, cse keeps p as a pseudo (2 uses) → the newval address = (plus (reg p) (reg idx)) → reload materializes p into a1 → the newval add would be "addu at,a1,v0" (using a1, the same reg as the final add) → we lose "lui at" → 110 insns.

Hmm, but wait: maybe not! Maybe reload would materialize the symbol twice anyway: the pseudo p (in a1) for the final add, and the address (plus (reg p) (reg idx))... the same reg → no second materialization. So 110.

Unless the newval expression is written with the symbol directly (as now) AND p has a second use elsewhere that produces no code...

What if p is used in the newval expression as `p[idx].f0` but the compiler CSEs the two addresses? Hmm: the newval address = p + idx*8 and the final = p + off + 4 where off = idx*8 → different.

OK, let me think about what else could give p a second use without changing the asm...

IDEA: What if p is used in a *store* that's dead? no.

IDEA: What if the second use of p is in the same expression, e.g. `(u8 *)p + off + 4` where p appears twice as `(u8 *)p + (u8 *)p - (u8 *)p + off + 4`? That's laundering-ish and silly.

Hmm, wait. Actually, maybe the "lone use" rule isn't about the number of uses of p but about the *set*: "single-set const addr r73 folded into lone use" from moves.md — that note says cse folded a constant address into a lone use. So the fold happened because there was a single use.

If p has 2 uses, does expand still substitute? The substitution at expand time (the .rtl dump already shows the symbol in the plus) — hmm, is the .rtl dump really post-expand? Maybe the .rtl dump is post-cse! Let me verify: in the .rtl dump, was the address (plus (symbol) (reg 118))? Yes. And the .cse dump also. And .combine had (plus (reg 118) (symbol)) — that's the swapped version. So .combine shows the SWAPPED form and .rtl/.cse show the unswapped. If .cse is after .combine, then the form changed between .combine and .cse — impossible unless combine's dump shows a *tentative* (reverted) state.

I bet the .combine dump in gcc 2.7 shows the state after combine's changes, and combine's changes to that insn were REVERTED (the combination was rejected) — no wait, the .combine dump would then show the reverted state too.

Alternatively the file naming is: -dc → .cse?? and -df → .combine? Hmm! Let me check the mapping by content: the .combine file ends with ";; Combiner totals: 0 attempts, 0 substitutions" — hmm, 0 attempts?! That's suspicious: combine did nothing?! But the file contains a full function listing with the swapped tree.

Hmm, "Combiner totals: 0 attempts, 0 substitutions" — maybe that's from a different function (the last one in the file). The totals are printed per function? No, at the end of the file.

OK, let me settle the pass order question empirically: compare the .rtl and .cse dumps for our function — if they're identical, then one of the flags produced a duplicate. Let me diff them.
