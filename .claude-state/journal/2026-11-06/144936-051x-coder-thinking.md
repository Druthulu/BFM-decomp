---
ts: 2026-11-06T21:49:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ye6qdiJI2n8ay6pIKOHH
---
This is hard to read without context. Let me find the insns around the iv2c region. Search the .cse dump for "iVar2"/"iv2c"? Dumps use reg numbers with decl names maybe in comments (`reg/v:SI 75`). The .rtl dump usually has `;; iv2c` comments? No.

Alternative approach: find the compare `beq` / the constant 1.

Let me take a different tack: try candidates and measure. Quick hypotheses to test:

H1: `s16 tmp;` declared at function scope, `tmp = (s16)iVar2; iv2c = tmp;` (like func_80182ED4).
H2: `u16 tmp; tmp = iVar2; iv2c = tmp;`
H3: `iv2c = iVar2; ` then reassign: `iv2c = (s16)iv2c;`? The second set is a real set that stales cse... hmm, `iv2c = (s16)iv2c;` is a self-reassign conversion — might be seen as a launder? It's a real conversion though. If the sign-extend folds to a copy, we'd get `move v1,v1`? no.

H4: Use a 16-bit variable for iv2c itself: `s16 iv2c;` then `iv2c = iVar2; one = 1; if (iv2c != one) uVar5 = 0;` — the compare widens iv2c back to int → sign_extend. cse can't equate iv2c(HI) with iVar2(SI). Then combine might fold the sign_extend into a copy or into the compare. The compare `if (iv2c != one)` with one=1: after sign_extend, beq. Maybe combine folds `sign_extend(iv2c) != 1` into comparing the HI reg with 1... but the target has `move v1,a0` then `beq v1,v0` where v0=one (a register). Since `one` is pinned to $2, the compare is reg-reg. With iv2c s16, we might get `sll/sra` or a direct `beq`.

H5: Assign iv2c via a conditional: no.

H6: Make iVar2's value pass through a `short` *function parameter-like variable*: 

H7: What about making the copy a real 32-bit copy that cse can't propagate because the destination is *also* assigned a different value on another path? cse's reg_eqv: a register that is set by a copy in one block and by something else elsewhere has no global class; but within the block it's still propagated.

Hmm — actually does cse really propagate `iv2c = iVar2` into the compare? In cse.c, for `SET (reg, reg)` cse records `reg_eqv_table[dest].equiv = src`. Then a use of dest... in cse_insn, `src_eqv` is only used for comparisons of memory addresses. Actually 2.7.2's cse does record copy equivalences to fold subsequent comparisons? Let me check cse.c for "make_regs_eqv" and how uses get replaced.

Actually the observed evidence: `beq a0,v0` — a0 = iVar2's hard reg, so the compare uses iVar2. This could also be from *local_alloc coalescing*: iv2c's qty merged with iVar2's qty (coalescing requires the source to die at the copy... local_alloc's combine_regs allows coalescing only if one dies). Hmm, iVar2 lives on (used at `sll v0,a0,0x3`). So not coalesced — rather cse rewrote the use.

Wait, actually, is `sll v0,a0,0x3` using iVar2? Insn 42 `sll v0,a0,0x3` — yes, a0 = iVar2. So iVar2 is live. So cse rewrote the compare's operand from iv2c to iVar2.

Let me check cse.c 2.7.2 for copy propagation of reg-reg sets.
