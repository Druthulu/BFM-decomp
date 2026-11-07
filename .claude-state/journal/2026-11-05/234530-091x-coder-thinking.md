---
ts: 2026-11-06T06:45:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4Hkff9ipBhpND9xztxhG
---
Order: 78 80 85 73 76 72 75 74.
- r78: 34 refs, live 64, pri 26562 — the big one (var_v0? the reused temp).
- r80: 4 refs, live 8, 10000
- r85: 5 refs, live 11, 9090, prefers v1
- r73: 5 refs, live 24, 4166, crosses 2 calls → a callee-saved
- r76: 3 refs, live 8, 3750
- r72: ? 
- r75, r74: ?

The target: var_fp=s8, var_s7=s7, var_a0=a0, var_t7=$3.

In mine, the s7/s8 swap suggests the order of the two callee-saved allocnos swapped.

Let me see the rest of the table (r72, r75, r74).

Actually, let me focus: the residual is mostly a v0/v1 swap in the early part and s7/s8 in the tail. 

Since time is short (item 4 started 23:45, now ~23:52), let me try a batch of variants:
1. Split `var_v0` uses (it's reused as a temp everywhere).
2. `var_fp = var_v0 = ...` → two statements.
3. Declaration order swaps (var_fp/var_s7, k50/kF0/k100).
4. Reorder the k assignments.

Let me look at what the pins did: k50=$20 (s4), kF0=$18 (s2), k100=$19 (s3). In the target, the constants k40,k50,kF0,k100 are in callee-saved regs.

Hmm, r78 (34 refs, live 64) conflicts with s0,s2,s3,s4,s5 — that's a variable that conflicts with callee-saved regs, so it must be caller-saved. That's probably var_v0 (the reused temp).

Let me just run a batch. I'll write a generator with ~15 variants.

Given the time, let me be efficient and focus on the two visible issues:
(a) var_a0 → $4 in the target vs $3 in mine.
(b) var_fp/var_s7 s8/s7 swap.

For (a): the source is `var_a0 = var_v0 = 0x20 - var_s0;`. The target: `subu v0,v0,s0; move a0,v0`. So var_a0 = the unshifted value, and var_v0 = the same value then shifted.

Hmm, if I write `var_a0 = 0x20 - var_s0; var_v0 = var_a0; var_v0 <<= 16;` — same thing.

What if I write `var_v0 = 0x20 - var_s0; var_a0 = var_v0; var_v0 <<= 16;`? Then var_a0 is a copy of var_v0 → cse merges them (the pin made them distinct: `move a0,v0`).

Hmm, the target's `move a0,v0` is a real copy — because var_a0 is used later. cse would merge var_a0 and var_v0 into one pseudo... but var_v0 is reassigned afterwards, so cse's copy propagation would rewrite uses of var_a0 to var_v0 only if var_v0 isn't redefined. Since var_v0 is redefined (var_v0 = 0x50000000 etc.), the copy must be materialized. Actually, `move a0,v0` exists in the target.

In mine, at insn 50 `move v0,v1` — a copy exists too, just in different regs.

So the issue is only the register choice for var_a0: $4 (a0) in the target vs $3 in mine.

Hmm, var_a0's refs: assigned once, used 6 times (sp10.b[13], b[9], b[14], b[10]...). Wait, `var_v0 = var_a0; sp10.b[13] = var_v0; ...` — so var_a0 is copied to var_v0 then used.

Hmm, the target's `move v0,a0` at insn 71: `var_v0 = var_a0` → v0 = a0. Yes.

So var_a0 is live from the `move a0,v0` to the `move v0,a0` — a short range across the intervening code. It's a caller-saved reg choice ($4).

In mine, var_a0 is in $3? and the copy `move v0,v1`.

So local-alloc gives var_a0 $3 in mine and $4 in the target. Hmm, both are caller-saved.

Let me try: make var_a0 a separate declaration or change the order of the assignments. Or declare `var_a0` earlier/later in the decl list (allocno numbering tie-break).

Actually, the priorities: var_a0 (a local, block 11?) — in the table, block-11 locals: r79 (v0), r114 (a1), r101/r105/r109/r111 (a1).

Hmm, the alloc order for the block-11 locals: r79 (pri 20000) first.

Let me look for the var_a0 pseudo. Ugh, time.

Let me take the pragmatic path: generate a batch of ~20 variants and score; if any hits 0, great; otherwise record the best.

Variants:
- split var_v0 into v0a/v0b for the three (0xC0, 0xE0, 0x20) computations
- reorder the three computations
- declare var_a0 before var_fp
- change the k decl order
- reorder the k assignments
- different spellings of `var_v0 = var_fp`

Let me write it.
