---
ts: 2026-11-06T16:29:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dh0bwH6prIp2YN79VHfC
---
Ordering by floor_log2(n_refs)*n_refs*size, then... In local-alloc, assignment order is by that priority (larger first). For q (2 refs: load into q, lhu; plus?) and g (2 refs). Both same → tie broken by regno probably.

Target original had pins so not informative for priority. But target after crack must match.

Approach: I should experiment with C-level changes and score. Let's try pointer-typed self and reordered declarations.

Candidate 2: use pointer self.

```c
void func_8017EAD8(arg0)
s32 arg0;
{
    Unkstruct_8017EAD8_2 *self;
    s32 mask;
    s32 flag;

    self = (Unkstruct_8017EAD8_2 *)arg0;
    ...
}
```

But that's a cast copy; cse may still equate Pmode pseudo to arg0? arg0 is SImode; converting SImode→Pmode on this target is a no-op but gcc may keep different modes; cse uses mode when comparing regs? In cse, `make_regs_eqv` / `record_jump_equiv`... For copy propagation, reg_eqv with different modes? In gcc 2.7.2 cse, `record_reg_vals`... Actually cse's equivalence class is per register, and it checks `GET_MODE` in `cse_insn`? It might equate anyway with a SUBREG. Hmm.

Alternatively, use a cast that is a real no-op but opaque: pointer arithmetic? e.g. `self = (Unkstruct_8017EAD8_2 *)(arg0 + 0);` combine folds +0.

Better idea: use a union? Or make self `u32` and cast at use sites? That would produce extra? no, casts at use sites are free (address arithmetic).

Hmm. Actually maybe simpler: the target's use of a1 in else arm could be achieved if self is still a separate pseudo. What real C creates a non-foldable copy? A copy through memory? no.

Wait — the move a1,a0 at entry exists in mine too, so mine also has self in a1, and the then arm uses a1. The else arm was rewritten to a0 by cse. Why would cse rewrite only the else arm? Because at the bnez, the path to else: self's value in a1 is available but maybe cse decides a0 is equivalent and the copy a1,a0 is in the same block; both are equivalent. Then for each use, cse picks the canonical register. Canonical = the earlier/regno? `make_regs_eqv` sets the canonical to... whichever has higher "canonical" priority (first-seen?). The then arm uses a1 though. Hmm, the then arm is straight-line after entry; the else arm too. Difference: the then arm has `li a0,-129` (mask) — a0 is clobbered there, so self's uses in the then arm cannot use a0 (its value is dead after mask assignment) → they use a1. The else arm has no a0 clobber → uses a0.

Target keeps a1 everywhere because the pinned zr made self = arg0 + zr an arithmetic result, not equivalent to arg0.

So I need a way to make self not equivalent to arg0. A pointer cast is the best bet: (Unkstruct *)arg0 — Pmode vs SImode. In gcc 2.7.2, Pmode == SImode on mips32 (both SImode), so still SImode. Equivalence probably still happens.

What about `self = (s32)(arg0 + 0u)`? folds.

What about declaring the parameter type differently? Can't change signature? "no signature or decl change outside the body". The body can have a local copy.

Alternative real-C: make `self` a `u32` and use `self` in a context where it's compared/used such that cse can't merge? Hmm.

Alternative: get rid of `self` entirely and use arg0 directly everywhere! Then target would need a1 = arg0 for all arms — but target has move a1,a0 and uses a1. If we use arg0 directly, code uses a0 everywhere with no move. That's not target.

Hmm, what about introducing a genuine copy that cse can't remove because arg0 is modified? E.g., `arg0 += 0;`? Then param pseudo is modified; self = arg0 after modification... The `move a1,a0` at entry suggests self is a separate register. If we do `arg0 = arg0 + 0;` combine folds at RTL: add with const 0 folds to copy. cse still equates.

What creates a distinct pseudo that cse cannot equate but costs no instruction? An assignment of the parameter to a local of *different machine mode* where conversion is a no-op in the target but represented as a subreg: e.g. `s16`/`u16`? That inserts sign-extension (sll/sra) or andi — extra insns. Not good.

What about `self = (s32)(u32)arg0;` — same mode, folds.

Hmm. Consider instead making cse unable to propagate a0 to the else arm by having a0 modified before the branch in a way that's still correct... e.g., compute mask before the if! If `mask = ~0x80;` is hoisted before the branch (it's in the then arm only, but we can move it before the if — target has li a0,-129 inside then arm after the branch, in the delay-slot region). If we assign mask before the if, a0 would be clobbered before the else → else arm would use a1! But then the instruction order changes: `li a0,-129` would appear before bnez, and target has it after. But maybe sched1 or reorg moves it? Unlikely.

Alternative: assign mask to a variable before the if but... no.

Better: make `self` used in the else arm in a way that's not a plain use of the parameter — e.g., pointer arithmetic on self: `q = ((Unk*)self)->unk20;` — that's exactly the same.

OK think about cse canonical choice. In cse.c 2.7.2, `make_regs_eqv(reg, elem)` — canonical is elem. When a copy `self = arg0` is seen, record: `make_regs_eqv (self, arg0)`? Let me look at the source to see which becomes canonical.
