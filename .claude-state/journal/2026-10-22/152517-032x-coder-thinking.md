---
ts: 2026-10-22T21:25:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_F2HJzrpaiYwfhBJGKRvq
---
Excellent! In the initial RTL (with the barrier present):
- arm1's store (insn 104): `(set (mem/s:HI ...) (reg:HI 106))` where reg 106 = const -80 with REG_EQUAL. So even arm1 stores through a REG at RTL level.
- arm3's store: k = reg/v:HI 121 = const -80 (insn 159), then the store `(set (mem/s:HI) (reg/v:HI 121))` presumably.

So at RTL, both arms have a REG source. By jump2 both are const. The difference in the ROM must be that arm3's reg survives as a register.

Note: arm1's temp reg 106 has `REG_EQUAL (const_int -80)` but arm3's k (reg/v:HI 121) has NO REG_EQUAL note (it's a user variable). Yet by cse2 both became const stores... because cse2 knows the constant from the `set` insn.

Interesting: arm1's reg 106 has REG_EQUAL, k doesn't. But cse2's fold_rtx would still see `set (reg k) (const -80)` and record k = -80 in its table for that EBB. Then the store `(reg k)` folds to const → movhi_internal2.

Hmm, unless cse's `cse_insn` refuses to fold a REG whose REG_EQUAL... no.

OK. Now the crucial question: in the ROM's build, the arm3 store kept the reg. What plain C makes cse2 not know k's value? If k's definition is in a *different* EBB than its use, cse2 won't fold (no REG_EQUAL note on k's def... hmm, would cse2 propagate across EBBs? gcc's cse does `cse_basic_block` per EBB; constants are not propagated across EBBs except via REG_EQUAL notes on the def which cse2 *does* use in `fold_rtx` when the reg is `reg_eqv`-equivalent... 

Hmm, in gcc, `cse_set_around_loop` and `cse_end_of_basic_block` handle cross-block. But there's also `record_jump_equiv`. Honestly, if k's def is in a different block, cse2 MIGHT still propagate via REG_EQUAL notes — cse adds REG_EQUAL notes to insns and `fold_rtx` uses `REG_EQUAL` for a reg: in fold_rtx, for a REG it looks up `reg_eqv_table` (equivalences computed within the block) and also `REG_EQUAL` notes only for CALL insns.

Actually gcc's fold_rtx:
```
    case REG:
      ...
      /* If we have a known equivalence for this register... */
      elt = &table[...];
      if (elt->first_same_value ...)
```
It uses the *table* built during cse_insn processing, per EBB. Cross-block, the reg would not be in the table (new EBB starts empty), so no folding.

So: if k is defined in a block OTHER than arm3's block, cse2 won't fold it. But the target shows the `li v0,-80` INSIDE arm3 (at 14cc), before the stores. Hmm — that contradicts a def in another block: the li would be emitted at the def site.

Unless... the def is in the *preceding* block (the cond3 test block) and the li is emitted there! Look: cond3's block: 14ac lh v0,20(sp); 14b0 nop; 14b4 slti v0,v0,896; 14b8 beqz v0,14e0; 14bc li v0,113 (delay slot). No li -80 there.

Hmm. What about the def being in arm3 but in a *separate basic block* within arm3 (e.g. after a nested if)? Like:

```
} else if (sp10.v[2] < 0x380) {
    s16 k;
    ...
    k = -0x50;
    unk30 = k;
}
```
Same block.

OK, so what if k's value is a const but its REG is set via a copy from another reg? e.g. `s16 k = j;` where j is -0x50 from elsewhere — no.

Time check: ~15:40. I'm at 28 min on this item. I have ~10 scored tries. The WALL bar is ≥20 min AND ≥30 scored tries. I should either crack it or reach 30 tries.

Let me do a rapid batch of 12+ variants. Ideas I can implement quickly (each a sed):

1. k at function top (before if-chain), s16.
2. k at function top, s32.
3. k assigned in the cond3 test block? Can't — it's inside an else-if.
4. arm3 with k = -0x50 assigned in a nested block: `{ s16 k; k = -0x50; }` — same block.
5. arm3: k declared at function top, assigned right after `sp10 = D_80126940;` — def in the entry block, use in arm3. li would be at the top (mismatch) but let's see: maybe flow moves it? Try.
6. arm1 uses a variable too (both regs) → still identical, merges.
7. arm3's store through `(s16 *)sp10.v`? no.
8. arm3 stores k with a `+ 0`? folds.
9. arm3: `s16 k = -0x50; ... unk30 = k;` where the two zero stores come AFTER the k store in source order — sched1 reorders? Order in target: sh0-36, sh0-46, sh v0,48. If source order were unk30 first, sched1 might keep it. Try: it changes RTL order → different from arm1 → no merge. If sched1 restores the target order, MATCH!
10. Similarly: in arm3, reorder unk20/unk22 stores.
11. arm3: write the stores with unk2E before unk24 (swap) — sched1 may restore.
12. arm3: put the `k` store before unk24/unk2E.

Variants 9-12 are the most promising: a source-order difference that sched1 undoes. That's a classic "real C move" (statement order).

Actually careful: sched1 with no deps between independent stores — does it preserve source order? The dbr/sched may reorder. The target order sh0-36 then sh0-46 matches source order.

Let me build variants:
- v9: arm3 order: unk20, unk22, unk24, unk30=k, unk2E.
- v10: arm3 order: unk20, unk22, unk30=k, unk24, unk2E.
- v11: arm3 order: unk30=k, unk20, unk22, unk24, unk2E.
- v12: arm3 order: unk20, unk22, unk2E, unk24 (swap the zeros).
- v13: arm1 order changed instead: unk20, unk22, unk24, unk30, unk2E.
- v14: k at function top s16.

Let me write these with python (easier than sed).
