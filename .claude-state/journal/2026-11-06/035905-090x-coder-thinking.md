---
ts: 2026-11-06T10:59:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_utZfEMfCHkomuduSSOXo
---
w_split2 = 7: v1 got a0 again (because v1's birth is early in the block where $4 is free).

In w_split (v1 late), v1 got v1 ✓ but the li/lw order swapped.

So: v1 late in source → correct register but scheduled before the lw; v1 early → wrong register (a0).

Target: v1 early in source (orig) but correct register ($3) and scheduled after the lw. The pin/barrier combination achieves it.

Hmm, in w_split, the li (v1 = 0x4000) is in the block after the RMW (block C) and the unk18 load is in the same block. sched1 put the li first (source order). The target has the lw first.

Why? Because in the target's block, the lw (of unk20) is at the source position after the li... wait, the target's C: `v1 = 0x4000;` then the unk18 stores. sched1 moved the lw above the li? The lw has a dependent (sh) → priority; the li is a constant with a dependent (sh). Both similar. Hmm, but the lw comes from a *later* statement.

The scheduler can reorder independent insns within a block. It chose lw before li in the target.

In w_split, block C starts at `v1 = 0x4000` (li) then the unk18 store (lw, sh). sched1 kept li first.

Difference: in the target, block C also contains the load/address/store/RMW at the start; the scheduler's state differs.

Hmm, what if I move `v1 = 0x4000;` to AFTER the first unk18 store statement in source? Then the li would be born after the lw... but the target has the li after the lw. Let me look at the target: lw v0,32 (34), li v1,16384 (35), sb, sw180, sh v1,24(v0). So the li is between the lw and the sh. In source, the first unk18 store is `((Unkstruct*)*(s32*)((s32)s0+0x20))->unk18 = v1;` — the load of unk20 and the store. The li must precede the sh (uses v1). sched1 placed the lw first, then the li.

So if I put `v1 = 0x4000;` right before the first unk18 store in source, the order would be li then lw... which is what w_split has (li at 35, lw at 36 in mine).

Hmm, mine w_split: li at 34/35, lw at 36. Wait, from the dump: 185c li v1,16384; 1860 lw v0,32. Target: lw at 34, li at 35.

So the difference is a scheduler tie-break: the target prefers the lw.

What if I move the `v1 = 0x4000;` assignment to AFTER the first unk18 store statement? Then the C would be:
```
unk18 = v1;   // uses v1 before it's assigned! Not valid.
```
No.

What if v1 is assigned before the RMW (as in w_split2) but the register issue is fixed another way? The register issue: v1 gets a0 because a0 is dead and local-alloc picks it. If a0 were still live at that point, v1 couldn't take $4. Hmm.

What if I keep a0 live by... using a0 later? That's a keepalive lever.

Alternatively, make v1's qty prefer $3: local-alloc's find_free_reg starts scanning from `reg_preferred_class`/the qty's first_reg. The qty's first_reg is the pseudo's original regno (virtual). The scan order for GR_REGS is given by `reg_alloc_order` in mips.h/md. Let me check the MIPS alloc order: probably $2,$3,$4,...? If so, v1 would get $2 first if free. In w_split2, v1 got $4 — so $2 and $3 were taken (t and the address). In w_split (v1 late), v1 got $3 — because in that block $2 is taken by t (global) and $3 free.

So it's about which regs are free in the block.

OK, w_split (score 2) is one insn off: li vs lw order. Let me try moving `v1 = 0x4000;` to a slightly different spot: after the RMW but in the *same do-while block* as the RMW? No.

What if v1 is assigned in the RMW's do-while block (with the ori/sw) — then the li is in block C with the RMW, and the unk18 stores are in block D. Block D starts with the lw32 → lw first, then sh. And the li would be in block C: ori, sw, li. Target: ori, sw, lw, li, sh. Hmm, the li would come before the lw (different block). Wrong.

What if v1 is assigned *between* the RMW and the unk18 stores but the lw32 is hoisted? It's in the same block.

Hmm, the target's li is after the lw32 in the same block. So we need the scheduler to prefer the lw. In w_split, the li is first in the block, so the scheduler picks it first.

What if the li is NOT first in the block: put a dummy... no.

What if `v1 = 0x4000;` is placed after the first unk18 store's *load* but before its store? Can't express.

Alternatively, declare `v1` with an initializer in the middle? No.

What if I split so that block C = [RMW, v1, lw32, sh...] and the scheduler orders? That's w_split (li first).

Hmm, what if I move `v1 = 0x4000;` AFTER the unk18 store statements but before their uses? The unk18 stores use v1 as the value. So v1 must be assigned before.

What if I inline the constant into the three stores (0x4000) and drop v1? That's the twin of item 1 (which had immediates). Then the code would be: li v0,0x4000 for each? The target has ONE li v1,16384 reused for three stores. If I write 0x4000 three times, gcc would materialize it once into a reg (cse) — probably the same.

Actually, in item 1 (func_8018966C) the source uses the literal 0x4000 in all three stores and the target emits `li v1,16384` once. So the literal form works. For the twin, if I replace `v1` with the literal 0x4000 in the three stores and delete the v1 variable, I get item 1's shape! Then the twin's C is essentially item 1's C. Let me test that: replace v1 with 0x4000 and remove the v1 variable/assignment.

That would make the twin's lever-free body the same as item 1's best. Let me test with the w_split structure and the literal.

Actually, the twin's target IS the same instruction stream as item 1's except for the symbol addresses. So the same C shape should work for both! Let me just take item 1's best candidate (v_dw, score 2) and adapt the globals... but the diff in item 1 was the store sink. For the twin with literals, we'd get item 1's behavior.

Let me test: build the twin with literals (no v1 var) and the w_split structure.
