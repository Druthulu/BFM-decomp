---
ts: 2026-11-06T19:06:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nofhMqNO20JWlajb0LGv
---
In the pinned orig: insn 14 sets hard reg a3 ($7) = symbol; insn 17 sets 76 = a3 (a copy). So cse did NOT canonicalize (the pin prevented it): the symbol stays in a3 and v1 (76) is the copy.

So the pin prevented cse's canonicalization. Lever-free, cse makes v1 canonical (v1 has more uses).

To prevent cse from canonicalizing lever-free, the copy must not be "mergeable": cse's `make_regs_eqv(dest, src)` happens for a copy; it can substitute if the registers are equivalent and one is "preferred". The preference is by `reg_n_refs` or the "older" reg. In the orig, the source is a HARD reg (a3), and cse won't substitute a hard reg for a pseudo (it can't rewrite uses of a hard reg, or it treats hard regs specially).

So lever-free, cse merges a7 and v1 and propagates the constant into the copy's dest.

Can we prevent the merge by making the copy *not* a plain reg-reg copy? Options:
- Make v1 = a7 into a different expression that cse can't merge, e.g., `v1 = a7 + 0` (folds).
- Use different modes: e.g., `v1 = (unsigned short *)((s32)a7)` — a cast, same mode, still a copy.
- Make the copy conditional? adds code.

Hmm. What if a7 is *not* a pseudo but... we can't pin.

What if the copy is `v1 = (unsigned short *)a7;` — same.

What if the init is `v1 = &D_8011FD10; a7 = &D_8011FD10;` (two symbols)? Then cse would common them: both SET the same symbol; cse's constant propagation would make one a copy of the other (or eliminate one). The result might be: a7 = symbol; v1 = a7 (the same as now) or v1 = symbol; a7 = v1.

Hmm.

What if I introduce a *third* variable so the copy chain is longer? E.g., `a7 = &D_8011FD10; v1 = a7; v1 = v1;` no.

What if the copy is between different-typed pointers (unsigned short* vs char*)? Modes are the same (Pmode/SI).

What about making a7's value used in a way that prevents the merge: cse merges only if the registers are "equivalent" and one is a copy. The merge happens at the copy insn. cse's canonical choice: `reg_eqv` uses the "canonical" = the one with the higher "use count" or the older.

Hmm, what if I make a7's use count higher by adding a use in the else branch: the return `return a7;` — could be `return a7 + 0;`? folds.

What if the else branch uses a7 in the store: `*v1 = *a0` → `*a7 = *a0`? That made a7's uses 3, v1's 3 → s3 scored 8 (the store used $7 instead of $3, and one insn fewer). Hmm, s3 = score 8 COUNT (46 ins) — the store used a7 and something merged.

Hmm, s3: 46 ins — one insn fewer. Because if the store uses a7 and the return uses a7, v1's only uses are the load and the increment... maybe v1 merged with a7 entirely (the move disappeared).

OK. Let me consider: is this item a WALL? The mechanism: cse canonicalizes the copy `v1 = a7` onto v1 (more uses), materializing the symbol in v1's register; the pin was the only thing preventing the merge (cse can't substitute a hard reg). The best lever-free score is 2 (the init's symbol register).

Hmm, but wait: the score-2 variants have the SYMBOL in the right register? Let me re-check h049's diff: "insert mine[38:38] target[38:39] addiu a3,a3,104; delete mine[39:40]" — that's the increment order, not the init. So in h049, the INIT matches the target (`la $7; move $3,$7`)! Let me verify: h049's asm earlier (dbody7 = g007, not h049). Let me check h049's asm from the dump (dumph).

If h049's init matches (`la $7; move $3,$7`), then cse did NOT canonicalize in h049! Interesting — the increment order (v1 first) changed the cse behavior.

So in h049, a7 = $7, v1 = $3, and the symbol is in a7 → the init matches. The only residual is the increment order (v1 before a7).

So: with the v1-first increment order, cse keeps the symbol in a7 (the canonical is a7?) — good. And the increments are v1-first (bad).

So I need the v1-first increment order to flip the cse canonicalization, but the a7-first increment order in the RTL. Since the RTL order follows the source, and cse's canonicalization depends on the source order... 

Hmm, wait: maybe the cse canonicalization depends on which variable is used FIRST in the function. In h049, the loop's first use is v1's increment... no, the loop's first use is `v0 = v1` (the load) — v1. Hmm.

Actually, in h049 the increments are B (v1), A (a7), C, D. The first use after the init is the load `v0 = v1` (v1), then the increment v1. In w1, the first use is the load (v1) too, then the increment a7.

Hmm, the difference is subtle. cse's `reg_eqv` canonical might be determined by the "first" pseudo in some table.

What if I keep the a7-first increment order but change the *load* to use a7: `v0 = a7;`? s2 scored 4. Hmm.

What about `v0 = v1;` → `v0 = v1;` (no change) but the *store* `*v1 = *a0` → `*a7 = *a0`? s3 = 8.

Let me try: the increments a7-first, but the load `v0 = a7` AND the store `*v1 = *a0`... s2 = 4.

Hmm.

Let me look at the score-2 variants more: they all have the v1-first increments. The residual is the increment order. What if I can make sched1 reorder them with a *dependency*? For example, if the a7 increment is scheduled after the v1 increment in the RTL but has a higher priority... 

The priorities in the loop block are all 1 because the increments don't feed the branch. What if the a7 increment's result were used by the loop test? E.g., the test uses a7? `while (a6 < 0x14)` — no.

What if the *return* is in the loop block? no.

What if I make the a7 increment feed something in the same block: e.g., the a7 increment's value used by a6's increment? `a6 = a6 + 1 + (a7 - a7)`? launder.

Hmm.

What if the v1 increment is expressed so that it depends on the a7 increment? E.g., `v1 = a7 + 0x68;` (using the NEW a7, after a7 += 0x68). Since a7 == v1 before, a7+0x68 == v1+0x68 = the new v1. ✓ Semantically correct!

Source:
```
a7 = (unsigned short *)((char *)a7 + 0x68);
v1 = (unsigned short *)((char *)a7 + 0x68);   // v1 = new a7
```
The asm: `addiu a3,a3,104; addiu v1,a3,104`? Hmm, v1 = a7_new + 0x68 would be a7 + 0x68 = the value. But the target's v1 increment is `addiu v1,v1,104` (v1 = v1 + 104). With this spelling, v1 = a3 + 104 → `addiu $3,$7,104` — different source register. ✗

Unless the allocator coalesces... no, a7 and v1 are different registers.

Hmm.

What if I express v1's increment as `v1 = (unsigned short *)((char *)v1 + 0x68);` but move it BEFORE a7's in the source, and then move a7's increment's *RTL* position... no.

OK, let me try yet another angle: make the a7 increment's *insn* appear first in the RTL by writing the increment as part of the return expression? no.

Let me look at the cse dump for h049 to see why the canonical flipped. Maybe there's a cleaner lever.

Actually, let me try a few more permutations around the score-2 ones with *different statement orderings of the init and load* but the same increment order (B,A,C,D):
- The load `v0 = v1` could be `v0 = a7` (s2-ish but with B,A,C,D order).
- The init INIT2.
- The return v1.

The sweep covered the init (2), load (2), return (2) with all perms. The score-2 ones are those where the combination works. So no 0.

What about the *store* `*v1 = *a0` — the sweep didn't vary it. Let me try moving the store position or using `*v1 = *a0` vs `*(unsigned short*)v1 = *a0` (same).

What about the store's *source*: `*a0` — same.

Hmm, what about the a5 increment's position (in the perms) — covered.

What about the a6 increment `a6 = a6 + 1` vs `a6++`? same RTL.

What about the loop test `a6 < 0x14` vs `a6 < 20`? same.

I think item 2 is a WALL at score 2. Time: 12:07; item 2 at ~22 min. Tries ~250.

Hmm, but wait — the score-2 residual is ONE insn's position (the a3 increment). Let me look at the exact asm order in h049 vs the target:

h049's loop tail: (from the trace) 37, 40, 43, 46, 111, 112? Let me get h049's actual asm (dumph/dumps_th/th.s).
