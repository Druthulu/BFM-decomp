---
ts: 2026-11-06T19:02:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XRm5YpLqrNkdLlYLE6JJ
---
h049: 76 (pri 19285, refs 9, live 14) → $3; 74 (pri 9600, refs 8, live 25) → $7. And per the asm, a7=$7, v1=$3 → so 76 = v1, 74 = a7.

g001 (a7-first increments): the earlier w1 table: 76 (pri 20000, refs 10, live 15) → $3; 74 (pri 5833, refs 7, live 24) → $7. In w1, per the asm, a7=$3 and v1=$7 → 76 = a7, 74 = v1.

So the pseudo numbering/assignment flips: in h049, 76 = v1 (the current pointer) and 74 = a7; in w1, 76 = a7 and 74 = v1. That's the cse canonicalization difference driven by the statement order.

In h049, 76 (v1) has pri 19285 and is allocated before 74 (a7, 9600) → 76 gets $3 (v1=$3 ✓) and 74 gets $7 (a7=$7 ✓).

So the allocation follows the pseudo numbers: 76 always gets $3 (allocated second), 74 gets $7 (last). The cse/expand assigns 76 to whichever variable appears "first" in some sense.

The source statement order determines this. With the increments v1-first, v1 becomes pseudo 76. With a7-first, a7 becomes 76.

But 76 = $3 and 74 = $7 always. So: the variable that becomes pseudo 76 gets $3. The target needs v1=$3, so v1 must be pseudo 76 → the increments must be v1-first (or some other statement making v1 first).

And the target needs the increment order a7-first in the asm.

So: v1 must be pseudo 76 (statement order v1-first somewhere) AND the RTL increment order a7-first.

The pseudo numbering is determined by the first *use/def* order in the RTL. In h049, v1's increment is first (the source order), making v1 pseudo 76. In w1, a7's increment is first.

Wait, actually the pseudo numbers: a7 = 74 or 76? The initial RTL always creates a7 first (insn 14: a7 = symbol → pseudo 74 or 76?). Hmm, in the initial RTL (w1), insn 14 = 74 (a7), insn 17 = 76 (v1). In h049's .lreg, insn 14 = 76, insn 17 = 74 — the cse swapped them.

So cse's copy propagation decided which pseudo is which: it rewrote `(set 76 (reg 74))` etc. Hmm.

The key: the cse canonicalization. cse makes the *older* pseudo canonical? The wall tag "cse-copy-canonical" (W48) says: "cse canonicalises a reg copy onto the older pseudo; target keeps the pinned reg". 

So cse canonicalizes the copy `v1 = a7` onto the older pseudo (a7, created first). Then the canonical pseudo is a7 = 74? But in h049, 76 = v1...

Hmm, the .lreg shows insn 14 sets 76 = symbol and insn 17 sets 74 = 76. So after cse, the symbol's pseudo is 76 and the copy's dest is 74. So cse renamed the variables: the symbol goes into 76 (which is v1's number?) and the copy into 74.

Ugh, the numbering is confusing. Let me think in terms of the source variables:
- h049: the increments are v1-first. The cse made the symbol go into the v1 pseudo and the copy into a7. So v1 = the canonical (older) pseudo → 76 (higher pri) → $3.
- w1: a7-first → a7 = 76 → $3.

So cse makes the variable that is "canonical" (the one whose uses come first?) get the symbol. Actually cse's copy propagation: for `v1 = a7`, cse may rewrite uses of v1 to a7 (making a7 canonical) or vice versa, depending on which has more uses / is older.

In h049, v1 has MORE uses (the load, the store, the increment) than a7. cse's `make_regs_eqv(dest, src)` sets the canonical as... the one that lives longer or has more uses? Hmm, but both are similar.

Empirically: the increment order flips the canonical. So the increment order determines which variable gets the symbol pseudo.

To get: v1 = the symbol pseudo (76 → $3) AND the RTL increments a7-first. The increment order in the source determines the canonical... Hmm, but if the increments are a7-first, a7 becomes canonical (w1).

What if the a7 increment is first but the v1 variable has more uses? It already does (v1 is used in the load/store). Hmm.

What if I add uses to v1 elsewhere without changing the code? E.g., `v0 = v1;` is already there. The stores use v1 (`*v1 = *a0`).

Hmm, what if the copy `v1 = a7` is spelled as `v1 = (unsigned short *)a7;`? same.

What if I write the init as `a7 = &D_8011FD10; v1 = &D_8011FD10;` (two symbol_refs, no copy)? Then cse merges them (same value) and the target's `move v1,a3` would be missing? Actually cse would keep both materializations? It'd probably common them into one and one copy.

Let me try: init with two separate symbol assignments:
```
a7 = &D_8011FD10;
v1 = &D_8011FD10;
```
The target's init: `la a3; move v1,a3` — a copy. With two symbol_refs, cse would produce... maybe `la a3; la v1` (two la's) or common them.

Alternatively, use a temp: `s32 t = (s32)&D_8011FD10; a7 = (unsigned short*)t; v1 = a7;` — same.

Let me try a few more variants around the canonicalization:
- v1-first increments + a7-first init (h049 is INIT1 = a7 first) — the sweep covered both inits.
- What about making the a7 increment *depend* on v1's old value via a different spelling that still produces `addiu a3,a3,104`? Impossible.

Hmm, what if the a7 increment uses a *temp*: `s32 t2 = (s32)a7; a7 = (unsigned short *)(t2 + 0x68);` — combine folds to addiu a3,a3,104? The temp is a copy of a7; combine would fold. The RTL might have an extra copy or not. Let me test: it might change the canonicalization/scheduling.

Similarly, the v1 increment via a temp.

Let me try a batch:
1. a7 increment via a temp (s32 t; t = (s32)a7; a7 = (unsigned short*)(t + 0x68);) with v1-first increments.
2. v1 increment via a temp with a7-first increments.
3. Both.
4. The init via a temp.
5. `v1 = a7 + 0`? no.

Let me also consider the order of the *load* (`v0 = v1`) — covered.

Let me write these and score. Time: 12:02; item 2 at ~17 min. Tries ~230.
