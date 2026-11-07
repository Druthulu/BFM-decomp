---
ts: 2026-11-06T05:00:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nbOJdi2N4QtxLgbePdHW
---
Same as q1. So the remaining differences:
1. s0/s1 swap: base ↔ a1.
2. Third block: the load of EA6 (for `< 0x80`) is in v1 instead of v0, and the inner reload is missing.

For issue 2: the target reloads EA6 after the store:
```
lh v0, EA6     (for < 0x80)
slti v0,v0,128
beqz v0, join
lw v0, EA4
addu v0,v0,s1
sw v0, EA4
lh v0, EA6     (reload for >= 0x81)
slti v0,v0,129
bnez ...
```
Mine (q1): uses v1 for the first load and reuses it for the second comparison (no reload). So cse kept the loaded value in v1 across the store.

To force the reload, we need cse to not have the value available. The memory clobber did that. Real C: a dead-reset (C0414) or an aliasing store.

Idea: in the third block, load EA6 into a temp before the store, then after the store load it again explicitly:
```
if ((s16)D_80078EA6 < 0x80) {
    do { D_80078EA4 += a1; } while (0);
    if ((s16)D_80078EA6 >= 0x81) ...
}
```
cse will reuse the first load if it can prove no alias. The store to EA4 is a different symbol → no alias → reuse.

To break it: make the store potentially alias the EA6 load. Hmm, same problem as before.

BUT: cse's equivalence is killed by a *call* (function call clobbers memory). Is there a call in this block? No.

What about a dead-reset (C0414)? The dead-reset trick: `p1 = 0;` kills a *register* equivalence, not a memory one. For memory, a store to the same location kills it. `D_80078EA6 = D_80078EA6;`? That would be a real store (same value) — cse might delete it as redundant. If it survives, it kills the equivalence of the EA6 load and forces a reload. But it would add instructions.

Hmm. What about `D_80078EA4 += a1;` written so the compiler can't prove it doesn't alias EA6? If the store went through a pointer with unknown alias... but then the reloc changes (the store must be D_80078EA4).

Wait — the *load* could be through a pointer! `s16 *q = (s16 *)&D_80078EA6;` with reloc D_80078EA6 (same symbol!). Then the load `*q` has a register base (q), and the store to D_80078EA4 is a symbol store. For cse, a load through an unknown pointer can't be reused across a store → reload! And the reloc for the load would be... gcc computes `q = &D_80078EA6` → `lui v0, D_80078EA6; addiu v0,v0` — hmm, that's `lui+addiu` into a register, whereas the target has `lui v0; lh v0,0(v0)` (the assembler macro). Different instruction sequence!

Hmm, unless gcc uses the macro: for `*(s16 *)&D_80078EA6`, gcc emits `lui v0; lh v0,%lo(D_80078EA6)(v0)`? Let me test: p2 (EA6 through a pointer q) gave 134 — worse, but let me look at what it generated. It probably materialized the address.

Alternatively — maybe the second load can be forced by *reordering* the source so cse sees a different expression: e.g., `if ((s16)*(volatile ...))` no.

Hmm, what about making the third block's inner condition read EA6 through a *different expression* that cse doesn't equate: e.g., `if ((s16)(D_80078EA6 + 0) >= 0x81)` — cse folds +0.

What about `(s16)D_80078EA6 >= 0x81` vs `(s32)(s16)D_80078EA6 > 0x80`? Different expression, maybe not merged by cse. Let me test: change the inner condition to `(s32)(s16)D_80078EA6 > 0x80`. cse might not equate the two loads (different comparison), but the *load* itself is the same MEM, and cse would still reuse the loaded register for the MEM regardless of the comparison. cse's equivalence is on the MEM expression, not the comparison. So the load is reused.

Unless the load is not in cse's table because of a block boundary. If the second load is in a different EBB, cse can't reuse across the store... but cse's EBB spans straight-line code; a store to an aliasing location kills the equivalence. Different symbols → cse keeps it.

Hmm, so how did the target avoid the reuse? The memory clobber asm. cse treats asm memory clobber as a store to memory → kills all MEM equivalences → reload.

Real-C alternative: a *real* store that cse can't prove doesn't alias EA6. If the store is `D_80078EA4 += a1` (symbol), cse knows it's a different symbol. Unless we make the store through a pointer with unknown base AND keep the reloc D_80078EA4... 

What if the store is `*(s32 *)((u8 *)base + 0x2C)` where base = D_80078E78? The reloc would be D_80078E78 (mismatch) and the address computation uses the base register s0 (target's store uses `lui at, D_80078EA4; sw v0,0(at)`). Mismatch.

Hmm. What if the store is `D_80078EA4 += a1;` but we add a *second* store through an unknown pointer that cse can't eliminate? That adds an instruction.

OK. Let me step back and consider the overall difficulty. Item 2 has a score of 38 with 111 vs 114. That's a PARTIAL-level result but we need 0.

Maybe there's a different approach to the whole function: what if we restructure the C to have the barrier effect via *the control flow*? E.g., the three arms are identical code; the barrier prevented cse from merging them. Wait, did cse merge them? In q1, the three arms are still duplicated (mine has the same structure). So the barrier wasn't preventing merging; it was preventing the load hoist and the reload. OK.

Let me focus on the two remaining issues:
(a) s0/s1 swap
(b) third block's reload + v0/v1

For (b): maybe a *dead-reset* on a register works: C0414 says "dead-reset cse-breaker; cracked 3 launders in G16x". The dead-reset is `x = 0;` where x is dead, which creates a real set that kills the sched1 birth boost or cse equivalence. For a memory equivalence, a dead store to the *same* memory would kill it: `D_80078EA6 = D_80078EA6;` — hmm, that's a self-assignment, likely deleted.

What about `D_80078EA4 = D_80078EA4;`? Also deleted.

What about a store to EA6 of a value that's already there? Not knowable.

Hmm, what about `D_80078EA6 = 0;`? Changes semantics.

Hmm, hold on. Let me reconsider the third block. The target:
```
lh v0,EA6        <- load 1
nop
slti v0,v0,128
beqz v0,join
nop
lw v0,EA4
nop
addu v0,v0,s1
lui at
sw v0,EA4
lh v0,EA6        <- load 2
nop
slti v0,v0,129
bnez v0,skip
lui v0,0x80
lui at
sw v0,EA4
```
Wait, but the source is:
```
if ((s16)D_80078EA6 < 0x80) {
    D_80078EA4 += a1;
    if ((s16)D_80078EA6 >= 0x81) {
        D_80078EA4 = 0x800000;
    }
}
```
The inner condition `>= 0x81` inside `< 0x80` is always false! But gcc doesn't know that (it's a signed comparison on a global). So it generates the check.

Now, since the inner check is after the store, cse would normally reuse the loaded value. The target reloads due to the asm.

To force a reload in real C, we need the store to potentially alias EA6. What if the store is written as a store through a `s16 *` or `u8 *` pointer to EA4? Hmm, the reloc.

Actually — wait. What about `D_80078EA4 += a1;` where D_80078EA4 is declared `s32` — the store is a 4-byte store. EA6 is a 2-byte load at a different symbol. GCC 2.7.2's `memrefs_conflict_p` for two symbol_refs: it compares the symbols. Different symbols → returns 0 (no conflict) — BUT only if neither symbol is "weak" or if the alias sets differ. In C, symbols of different types (s32 vs u16) have different alias sets; in 2.7.2 with `-fstrict-aliasing` off (default), `get_alias_set` returns 0 for most things → all memory is in one alias set → `memrefs_conflict_p` falls back to comparing addresses: two different symbol_refs with constant offsets → `memrefs_conflict_p` may return... Let me check rtlanal.c's memrefs_conflict_p for SYMBOL_REF.

Actually, empirically: the candidate *did* reuse the load (no reload), so cse proved no conflict. So the symbols are distinct.

Hmm, what if we make the two accesses go through the SAME symbol by using an array overlay — but the reloc must stay D_80078EA4 / D_80078EA6. 

Wait... what if the *load* uses D_80078EA4 with an offset (reloc D_80078EA4) — mismatch. What if the *store* uses D_80078EA6? No.

OK, alternative idea for (b): make the second comparison use a *different* value that requires the load. E.g., write:
```
if ((s16)D_80078EA6 >= 0x81)
```
as
```
if ((s16)D_80078EA6 - 0x81 >= 0)
```
Doesn't change the load.

What if we put the inner check *before* the store in the source? Then the load order would be: load1, slti128, load2 (for >=0x81), slti129, then the store. That's different from the target.

Hmm.

What if we use a do-while(0) to split the block between the store and the second load? If they're in different EBBs, cse can't reuse across the boundary. cse works on EBBs: an EBB ends at a label/jump. A do-while(0) note... C0535 says it splits cse1's EBB. If we wrap the inner if in a do-while(0):
```
D_80078EA4 += a1;
do { if ((s16)D_80078EA6 >= 0x81) { D_80078EA4 = 0x800000; } } while (0);
```
then cse's EBB is split before the load → the load can't be reused → reload! That might work!

Similarly for the other blocks: the reload isn't needed there (the target's blocks 1/2 have only one load each).

Let me also reconsider: in q1, the third block's first load got v1 (not v0). If the reload happens, the first load's register might become v0 again (since the pseudo doesn't live across).

Let me test: q1 + do-while around the third block's inner if. Also try the do-while around the third block's outer if.

Actually, simpler: apply the do-while around ALL the ifs (r1) AND around the third block's inner if.

Let me test:
s1: r1 + inner if wrapped.
s2: q1 (stores wrapped) + inner if wrapped.
s3: inner if wrapped only.

Let me also think about (a) the s0/s1 swap. Maybe with the reload restored, the ref counts change and the register assignment fixes itself. Let's test.

Let me generate.
