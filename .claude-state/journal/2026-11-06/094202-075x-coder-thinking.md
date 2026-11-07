---
ts: 2026-11-06T16:42:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_03AbptYyB8OCo3Cbu33g
---
All fold at expand time to a copy. So we need an expression that expand doesn't fold and combine folds to a move. `arg0 + zr` where zr is a register var works. Without pins, what about `arg0 + *(volatile?)`... no.

What about `arg0 + (flag & 0)`? expand: flag&0 might fold to 0 at expand? Probably yes.

What about `self = arg0 + (s32)(flag * 0);`? expand folds mult by 0? likely yes.

What about an expression whose RTL is a PLUS with a *register* operand that combine can prove zero: e.g., a variable initialized to 0 earlier? A local `s32 zero = 0;` — expand might keep the pseudo and generate `li 74,0` (an instruction!) then plus. combine folds plus with a REG_EQUAL const? If the pseudo has REG_EQUAL 0, combine can fold `arg0 + zero` into a copy. That costs an `li` instruction unless deleted. Hmm, `s32 zero = 0;` used once → the `li` may be removed by cse/combine? Risky.

Alternative: `self = arg0 + (flag == flag ? 0 : 0);` folds.

Hmm, what about `self = arg0; flag = flag;`...

Think differently: maybe we don't need the arithmetic. Maybe we need local-alloc to tie 72 and 73. In w1, why didn't local-alloc tie them? Because cse already replaced 73's uses in block0/1 with 72, leaving 73 used only in block2 (else). Then 73 is block-local to block2 and gets a0 (free there). In o1, 73 is used in all blocks (not merged by cse), so it's global and tied with 72's qty.

So the split is caused by cse merging 73→72 in the entry+then EBB. If we could make cse NOT merge (keep 73 in the then block), then 73 is used everywhere, global-alloc sees 73 live across blocks and... would it conflict with a0? 73's own conflicts would be {2,3,29} maybe, and it could still get a0. Hmm, but in o1 it got a1 because 72 was tied.

Hmm, what if we make the else block use 72 too (the param)? Then everything uses 72 = a0? no.

Let's think about the desired final allocation: self in a1, and the mask in a0 (li a0). Since a0 is clobbered in the then block by the mask, self can't be a0 in the then block — so self must be a1 there. In the else block, no mask, so self could be a0; we need to force it to a1 for consistency (the target uses a1).

What if we make the mask assignment happen in a way that a0 is considered live across the else block? E.g., compute `mask = ~0x80;` in the entry block (before the if) and use mask in both arms? Then a0 is live across the else (mask value), so self can't use a0 anywhere → a1 everywhere. But the target's `li a0,-129` is in the then block, not the entry.

Hmm, unless the mask computation in the entry block is scheduled/sunk into the then block by sched1? sched1 works within a basic block; can't cross the branch.

Alternatively, make a0 live across the else with something that emits no instruction and is dead... e.g., `arg0 = 0;` after the if? dead-set deleted.

What about a *use* of arg0 in the else arm that is dead but not deleted before global-alloc? Dead code elimination (flow's delete_dead... ) runs before local_alloc? Let me check: flow_analysis + combine + sched1 + local_alloc. The dead code elimination `delete_dead_from_cse` runs right after cse1. Also `dead_from...`. Any statement we add that's dead would be removed.

What if the else arm genuinely uses arg0 in a way that produces the target's instructions? The target else has no a0 use.

Hmm OK. What about making the *then* block's self use stay as a1 by keeping self distinct from the param (arithmetic), which we can't do without a pin...

WAIT. Maybe we can make the parameter itself be in a1 and self in a0 — i.e., swap roles! If the C used `arg0` as the base everywhere and self only in the then block... no, target's move is a1=a0 and all uses a1.

Alternatively: what if the source has NO self variable, and uses `arg0` directly, but the *parameter* gets copied to a1 because it's used after a0 is clobbered? E.g.:
```
void f(arg0) {
  s32 mask;
  ...
  if (...) { mask = ~0x80; ... } 
}
```
Using arg0 directly: entry stores use a0; then mask=~0x80 clobbers a0; but the then block needs arg0 → gcc must copy arg0 to another register at entry! That would produce exactly `move a1,a0` and all subsequent uses of arg0 in the then block use a1. But the else block (no clobber) would use a0. Hmm, still split.

Unless the else block also uses arg0 after something... no.

Hmm, but wait: what if the C uses arg0 directly and gcc's global-alloc assigns the param pseudo to a1 because a0 is clobbered in one path? The param pseudo is global (live across blocks); if a0 conflicts anywhere in its live range, it can't be a0. In w1, the param pseudo 72 was block-local? No, 72 is live from entry to insn 11 only (the copy), so it dies before the branch. If instead arg0 is used throughout, its live range spans all blocks; then global-alloc assigns it a register avoiding a0 (because a0 is clobbered in then) → a1! And the else would also use a1.

But then there's no copy `move a1,a0`? There would be: the param pseudo is set from a0 at entry (insn 4: `(set 72 (reg a0))` → move a1,a0). Yes! Exactly the target.

So: remove the `self` variable entirely and use `arg0` directly (cast at each use). Then the param pseudo 72 lives across all blocks, conflicts with a0 (mask) → a1, and the entry copy move a1,a0 appears. That should give the target's a1 base everywhere!

Let me test that: variant s13: no self, use `((Unkstruct*)arg0)` everywhere.

Note: the stores in the entry use arg0; the then uses arg0; the else uses arg0. The param pseudo is global.

Let's generate it.
