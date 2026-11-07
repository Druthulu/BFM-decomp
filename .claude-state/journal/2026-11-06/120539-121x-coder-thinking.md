---
ts: 2026-11-06T19:05:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qrFDWWjCsdqXiY7hJozE
---
In w1's .cse: insn 14 sets 76 (the symbol) and insn 17 sets 74 (the copy). So after cse, the symbol's dest is 76 and the copy's dest 74.

The initial .rtl (w1) had: insn 14 sets 74 (a7), insn 17 sets 76 (v1). So cse RENAMED: a7's symbol → 76 and v1's copy → 74. I.e., cse swapped the register numbers of a7 and v1.

Why? cse's copy propagation: `v1 = a7` → cse records the equivalence and may rewrite one to the other. The rewritten one gets... cse uses `make_regs_eqv` and then `reg_eqv` — it can substitute uses of the newer reg with the older. If cse decides v1 (76) is equivalent to a7 (74) and rewrites all uses of 74 to 76, then the symbol's dest becomes 76 and the copy's dest 74? Hmm, that's the observed swap.

In h049's .lreg: insn 14 = 76, insn 17 = 74 — the same numbering! So in h049, the symbol's dest is also 76. But h049's mapping to variables differs: the variable that gets 76 in h049 is v1 (because the source's first use order differs).

So the pseudo numbers 74/76 are assigned to the *variables* by the order they first appear in the RTL (expand): a7 is declared/assigned first (a7 = &D_8011FD10 → the first use), so a7 = 74, v1 = 76. Then cse swaps the numbers?? The .cse dump shows the symbol (a7's statement) with dest 76. That means cse rewrote a7's register to 76 — a genuine renaming.

Hmm, that's weird. Unless cse's "copy propagation" rewrites `(set 74 (symbol))` + `(set 76 (reg 74))` into `(set 76 (symbol))` + `(set 74 (reg 76))`: it propagated the symbol value into the copy's dest (76) and turned the original into a copy. Yes! cse propagates the constant into the *use* (the copy's source → dest), then the original becomes a copy.

So the symbol ends up in whichever pseudo is the copy's DEST (76 = v1 in the initial numbering). In w1, v1 = 76 → v1 gets the symbol → v1 = 76 = $3? But the asm showed a7=$3!

Argh. Let me re-examine: in w1's asm, `la $3; move $7,$3` — the symbol's dest is $3 and the copy's dest $7. The dispositions: 76 in 3, 74 in 7. So 76 (the symbol's pseudo) = $3. And 76 = the copy's dest in the initial numbering = v1. So v1 = $3?? But the loop's current pointer is v1 and it's in $3 in the asm (`lhu $2,0($3)`)... and the return pointer a7 is $7.

Hold on: in w1's asm, the symbol's pseudo ($3) is used in the loop as the load address (`lhu $2,0($3)`) — which is v1's role. So v1 = $3 ✓ (v1 = 76 = $3). And the copy's dest (74 = $7) is a7 = the return pointer ✓.

So in w1: a7 = 74 = $7, v1 = 76 = $3 — THE TARGET'S ASSIGNMENT! But the dt.sh score says w1 has `lui v1` (the symbol in $3) vs the target's `lui a3` (the symbol in $7).

So the difference is: in w1, the symbol is materialized in v1's register ($3) and copied to a7 ($7); in the target, the symbol is materialized in a7's register ($7) and copied to v1 ($3).

So the *semantic roles* (a7=$7, v1=$3) match, but the *initialization* order differs: the compiler propagated the symbol into the copy's dest (v1) rather than the original's dest (a7).

In the target (pinned), the symbol is materialized in a7 (the hard reg $7) and copied to v1. So the cse propagation went the other way there (or the pin forced it).

Hmm! So the actual issue is cse's copy propagation direction: it propagates the constant into the copy's dest, making the "copy" the real one and the original a copy.

To get the target's init: the symbol must be materialized into a7 and copied to v1. In C: `a7 = &D_8011FD10; v1 = a7;` — the natural RTL has a7 = symbol, v1 = copy. cse flips it (propagates into v1). 

Why does cse flip it? Because of the copy `v1 = a7`: cse's `cse_insn` sees the SET of v1 from a7; it records the equivalence and, when it later processes uses... Actually the flip happens because cse propagates the *symbol_ref* (a constant expression) from a7's SET into the uses of a7 — but a7 has only the copy as a use, so it rewrites `v1 = a7` → `v1 = symbol` and leaves `a7 = symbol` (still a symbol SET). Then cse sees both SETs of the same value and... hmm, the dump shows `a7 = v1` (a copy) — so cse turned the original into a copy.

This is cse's "make_regs_eqv" canonicalization: it made v1 the canonical (since v1 is used more), rewriting a7's uses to v1. So `a7 = symbol` became `v1 = symbol`, and `v1 = a7` became `a7 = v1`.

So the canonical is the pseudo with more uses (v1). In the target (pinned a7=$7), cse... the pin makes a7 a hard reg, so cse cannot make it equivalent to v1? cse avoids substituting hard regs? That's why the target keeps the symbol in a7 and the copy to v1.

So: lever-free, cse canonicalizes onto v1 (more uses) → the symbol lands in v1's register ($3), the copy in a7's ($7). The target has the opposite.

To flip cse's choice: make a7 have MORE uses than v1, so cse canonicalizes onto a7. a7's uses: the increment (in the loop), the return. v1's uses: the load, the store, the increment, the copy.

Hmm, a7's uses: `a7 += 0x68` (1 ref), `return a7` (1 ref) = 2. v1's: `v1 = a7` (1), `v0 = v1` (1), `*v1 = *a0` (1), `v1 += 0x68` (1) = 4.

If I add uses to a7 without changing the asm... hard.

Alternatively, reduce v1's uses: e.g., `v0 = v1; if (*v0 != 0)` — v1 used once here. The store `*v1 = *a0` uses v1. The increment. Hmm.

What if the load is `v0 = v1` and the store uses v0? `*v0 = *a0` — v0 == v1 at that point? After the load and the branch, v0 = v1 (the same pointer) and hasn't changed. So `*v0 = *a0` is equivalent to `*v1 = *a0`! But the register: the store's address would be v0's register ($2) instead of $3 → the target's asm has `sh $2,0($3)` (the address $3). Hmm, but wait: v0 = v1 means v0 is a copy; the allocator might coalesce v0 with v1 → both $3? The load `lhu v0,0(v1)` writes $2 and reads $3. If the store used v0 ($2), it'd be `sh $2,0($2)` — wrong.

Hmm.

What if I add a use of a7 in the loop body that's free? E.g., the load `v0 = a7;`? no.

OK, what about the *init* statement order: if the source is `v1 = &D_8011FD10; a7 = v1;` (INIT2), the natural RTL: v1 = symbol, a7 = copy. cse canonicalizes onto v1 (more uses) → v1 = symbol (already), a7 = copy. The asm: symbol in v1 ($3), copy to a7 ($7) → same as w1's result (score 3). The sweep's INIT2 variants scored 3. Right.

So cse always makes v1 the canonical (more uses) → the symbol in $3. The target has it in $7. The only way: prevent cse from canonicalizing onto v1, e.g., by making a7 have more uses or v1 fewer.

What if the increment of a7 is split into more uses? E.g., `a7 = (unsigned short *)((char *)a7 + 0x68);` is 1 use of a7. What if `a7 = a7 + 0x34; a7 = a7 + 0x34;`? adds an insn.

What if the return uses a7 twice? no.

Hmm, what if I make v1's uses fewer by rewriting the store to use a different variable that's equal? The store `*v1 = *a0` — what if it uses `*v0` where v0 was assigned v1 and NOT reloaded? At that point v0 = v1 (from the load). But the register would be v0's. Unless v0 and v1 are coalesced... The load `lhu v0,0(v1)`: v0 = *v1. Then `*v0 = *a0`? No! v0 holds the LOADED VALUE (the word at *v1), not the pointer. So `*v0 = *a0` would store through the loaded value — wrong semantics.

Wait, no: `v0 = v1;` then `if (*v0 != 0)`. In the else branch, v0 still holds the pointer (= v1). The stores: `*v1 = *a0;` stores the 16-bit word from a0 into *v1. If I wrote `*v0 = *a0`, v0 == v1 → same address. So it's semantically identical! The register would be v0's, but if the allocator coalesces v0 and v1 (they're copies), the store might use $3. The load `lhu v0,0(v1)` requires v0's register for the result; the store's address would need v1's value = v0's value... Since v0 = v1 at that point, the allocator could use either. Hmm, risky.

Let me test it: s1 = w1 with `*v1 = *a0;` → `*v0 = *a0;`.

Similarly, `v0 = v1` could be written as `v0 = a7`? no.

Let me also test making a7's uses higher: the return `return a7;` → could use a7 twice? no.

Let me test s1. Also s2: `*v1 = *a0;` → `*a7 = *a0;` (a7 == v1) — this would add a use of a7 (making a7's uses 3) and remove a use of v1 (3). The store's register would be a7's ($7) → the target's store is `sh $2,0($3)` (v1) → wrong.

Hmm.

OK, let me test s1 (`*v0 = *a0`) and see. If the store uses $3 (coalesced), the cse canonicalization might also change (v1 has one less use → maybe a7 becomes canonical).

Let me also test: `v0 = v1;` → `v0 = a7;` (v0 = a7 is equivalent; v1 = a7). This moves a use from v1 to a7. The load `lhu v0,0(v0)`? no, `*v0` after v0 = a7 → the load's address is v0 (= a7 = v1). The register would be a7's ($7) → the target's load is `lhu $2,0($3)` → wrong.

Hmm, but the allocator might coalesce v0 with v1.

Let me just test a few and see the scores.
