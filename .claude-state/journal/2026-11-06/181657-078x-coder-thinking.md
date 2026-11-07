---
ts: 2026-11-07T01:16:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nMEfJ8cgXoh2K6S6QXpN
---
All 1. Total tries for item 2: 30 + 13 + 6 + 8 = 57 (excluding compile errors).

Time 18:16:44. Item 2 start 18:09 → ~8 min. Need until ~18:29.

Let me do one last creative attempt before wrapping: the "keep r72 alive past the store" idea, which directly targets the equivalence.

What if the second store uses `new_var` AND the call arg uses `s0`, and we add a real use of `new_var` AFTER the call? E.g.:

```
  func_80171990((u8 *) s0);
  new_var = new_var;  // dead
```
No.

What if the function's last statement uses s0: `func_80171990((u8 *) s0);` is the last.

What if we swap: `func_80171990((u8 *) s0);` before the store... semantic change.

What if the call arg is `(u8 *)s0` and the store base is also s0 but the store comes AFTER the call? Then the store wouldn't be in the delay slot.

Hmm.

Another thought: what if the second store's base is `new_var` where new_var is assigned from `s0` *inside* the same do-while block as the store (so cse can't propagate across the block boundary)? cse does global propagation across blocks (cse1 is global). But `do{}while(0)` splits the EBB, and cse1's "make_regs_eqv" works per EBB? cse1 is a global cse with reg_eqv across blocks (it tracks per-block). The moves.md note says "do{}while(0) splits cse1 EBB" — so a copy inside a do-while block might not be propagated out.

Let me try:
```
  // !FAKE: do-while
  do
  {
    new_var = (char *) s0;
    v0 = 0x100000;
    *((s32 *) (new_var + 0x204)) = v0;
  } while (0);
```
Then new_var is a separate pseudo from s0 (if cse doesn't merge across the EBB boundary). Then the store's base is new_var, not r72 → the equivalence with a0 (from the call arg copy `a0 = r72`) wouldn't apply!

But the allocation: new_var would be a pseudo with refs 2 (set + use), live short → local-alloc'd to a caller-saved reg or a callee-saved? It's born after the call, in a block after the call → no call crossing → local-alloc can give it a caller-saved reg (v0/v1/a0...). The target uses $16. So the store would use e.g. v0 or a1 → mismatch.

Unless new_var gets $16: for that, it must be a global allocno or tied. Hmm.

But wait — the target's store base is $16 = the s0 register. If new_var is a separate pseudo allocated a different reg, mismatch. If it's coalesced with r72, we're back to the equivalence.

Hmm, but maybe local-alloc's copy preference ties new_var to r72's hard reg ($16)! In local-alloc, a copy `new_var = s0` with new_var's block-local live range would prefer the same hard reg ($16) as s0 — if $16 is free in that block. Then the store would be `sw $2,516($16)` — MATCH!

Interesting! And since the copy is in a different EBB (do-while block), cse1 might not merge it, and sched1 can't move the call-arg copy above it (block boundary)... wait, the call-arg copy `a0 = r72` is for call 2 which comes after the store. sched1 can move it within its block. If the store is in a separate block (the do-while), the copy can't move above the block's start.

Then local-alloc: new_var's qty is local (one block); it's a copy of r72 which is in $16 → local-alloc's copy preference would tie new_var to $16 if possible. But r72 is live in that block? r72 (s0) is live from entry to the call — yes, it's live during the store block. So $16 is occupied by r72 → new_var can't get $16.

Hmm, unless new_var is coalesced with r72 (same qty) — then it's the same reg and the equivalence... but the store's base would be the pseudo new_var, which local-alloc merged into r72's qty → after allocation it's $16. And update_equiv_regs wouldn't see new_var as equivalent to a0 (it's r72's qty but a different pseudo?).

Hmm, wait: if local-alloc merges new_var and r72 into one qty (combine_regs), then the store's base operand is still the pseudo new_var, which gets $16. update_equiv_regs' replacement targets pseudos with REG_EQUIV; new_var has no equivalence with a0 (only r72 does, via the copy a0 = r72). So the store would keep new_var → $16 → MATCH!

But this requires:
1. cse not merging new_var into r72.
2. local-alloc tying new_var to r72's $16 (same qty or copy preference).

Let me test it! Variants:
- `do { new_var = (char*)s0; v0 = 0x100000; *((s32*)(new_var+0x204)) = v0; } while (0);`
- Same but with the first store inside too.
- Same but the do-while contains only the assignment.

Also try the `cse1 EBB split` trick without a do-while: an `if (1) { ... }` block? That also splits EBBs.

Let me generate these.

Note: the empty `do { } while (0);` at the top already splits the entry EBB. Maybe putting the *copy* inside a do-while right before the store works.

Let me write gen6.py with these block-scoped variants. This is the most promising idea — C0535 from MOVES+.

Variants:
- ba: do-while around `new_var = (char*)s0;` + store2 (with v0 = 0x100000 inside).
- bb: do-while around only `new_var = (char*)s0;`.
- bc: do-while around store2 only, with new_var assigned inside.
- bd: if (1) { new_var = (char*)s0; v0 = 0x100000; store2; }
- be: do-while around store1 and the new_var assignment.
- bf: do-while around both stores and the assignment.

Let me write them.
