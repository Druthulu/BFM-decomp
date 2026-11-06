---
ts: 2026-10-22T21:28:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_umoUlFTN7alLzml6lnLX
---
So even at cse2 the store source is `(reg/v:HI 121)` — a register, not a const! So the RTL never folds. And after reload, reg 121 becomes a hard register (v0) and the store is `sh v0,48`.

So the patterns ARE different: arm1's store source is `(reg:HI 106)` (a compiler temp, movhi_internal2), arm3's is `(reg/v:HI 121)` (a user variable). But cross-jump's rtx_equiv_p renames registers — so both become equivalent under a renaming (106 ↔ 121). That's why it merges.

So cross-jump's renaming defeats the register difference. Damn.

Therefore, to defeat the merge, the *asm* must differ in the suffix... but the target's asm is identical. Contradiction!

Unless the ROM's compiler does NOT do this renaming for these, or cross-jump is blocked for another reason.

Hmm, but wait: the target's arm2/arm4 merge shows cross-jump runs. And arm1/arm3 are identical in asm yet not merged. So the ROM's arm1/arm3 must differ in RTL in a way rtx_equiv_p sees.

What does rtx_equiv_p compare? In gcc's jump.c:
```
int rtx_equiv_p (x, y, set_p) {
  ...
  if (code != GET_CODE(y)) return 0;
  ...
  /* compare operands */
}
```
It handles `MEM` by comparing `MEM_ALIAS_SET`? No. It compares operands via exp_equiv_p with a `labels` table.

One important case: `rtx_equiv_p` for a `MEM` with different `MEM_IN_STRUCT_P` — probably not compared.

Hmm. What about a difference in the *number of insns in the block* — the target arm1 and arm3 both have 8.

What if one of them is a *fall-through* (no jump) and the other has a jump? In the target, both have j.

OK, radically different thought: maybe the ROM's arm3 block ends with a j to 14fc, and arm1 too, but cross-jump requires the two blocks to have the SAME successor — they do.

Hmm, so why not merged in the ROM?

Maybe because in the ROM's build, one of the blocks is a jump target that cross-jump refuses... Let me look at gcc 2.7.2's jump.c. Maybe the source is available: tools/bin/gcc-2.7.2-psx? Let me check if there's a source tree in the repo.

Actually, gcc's cross_jump has this important guard (from jump.c):

```
	  /* Don't try to merge blocks if either of them is the target of a jump
	     table or ... */
```
and

```
      /* If the insns are not equivalent, we can't merge. */
```

and crucially this one I remember:
```
	  /* Do not allow the two blocks to be merged if the first block's
	     last insn is a jump that jumps to the second block's label ... */
```

and:
```
	  /* If we have a NOTE_INSN_LOOP_BEG ... */
```

Hmm, there's also `struct rtx_renaming` handling of `LABEL_REF`.

Let me search for the gcc source in the repo.

Actually — hold on. Let me reconsider the problem. Maybe the ROM's arm1 and arm3 differ in the *first* store's value register: arm1's `li v0,113` is in the *delay slot of the branch* (1448) — that insn belongs to the branch block, not arm1. In arm3, `li v0,113` is also in the branch's delay slot (14bc). Same.

Hmm hmm.

What if the difference is that arm1's block has a REG_DEAD/REG_UNUSED note? Notes aren't compared by rtx_equiv_p — actually `rtx_equiv_p` compares PATTERN only. But `find_cross_jump` also checks `insn == BB_HEAD` conditions and `get_attr`... no.

Let me look at the real gcc source. Check if it's in the repo (maybe under tools/src or docs). Let me search for jump.c.
