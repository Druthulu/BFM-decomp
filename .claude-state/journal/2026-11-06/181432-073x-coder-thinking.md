---
ts: 2026-11-07T01:14:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fooil7UgWPhOLfsyPLaI
---
This is the REG_EQUIV replacement path, which applies to a register set once with a REG_EQUIV note and referenced exactly twice. Our case: r72 has many refs.

Hmm, but our substitution was r72 → a0 in the store. Let me look for `optimize_reg_copy_1`: "If this is a register-register copy where SRC is not dead, see if we can optimize it." — `optimize_reg_copy_1 (insn, dest, SET_SRC)` is called when `dest = REG, src = REG, src NOT dead`. 

Our copy: `a0 = r72` where r72 IS dead at that insn (REG_DEAD (reg/v:SI 72)) → in .sched, insn 46 has REG_DEAD 72. So the condition `! find_reg_note (insn, REG_DEAD, SET_SRC (set))` is FALSE → goes to the else-if: dest must be a PSEUDO (a0 is hard) → skipped.

Hmm, so neither applies. But the RTL changed between .sched and .lreg. Let me look more carefully: maybe the change is from local-alloc's `optimize_reg_copy_1` on a different copy, or from `combine_regs`.

Wait — maybe I mis-attributed. The .sched dump is AFTER sched1 but the lreg dump is after local-alloc. Let me check whether local-alloc or the *flow* pass... Actually, hold on: maybe the substitution happened during **sched1** itself? The .sched dump (after sched1) shows insn 43 with base r72. So no.

Let me look at local-alloc.c more: there's also `optimize_reg_copy_3` and the "combine_regs" qty tying. Hmm.

Actually — maybe it's `reg_renumber`-driven in `local_alloc`: local-alloc assigns r72? No, r72 crosses a call.

Wait, actually: is the store's base change possibly done by **global_alloc**? The .lreg dump is taken after local-alloc but the dump name ".lreg" might be emitted after global alloc too? The alloc_table read both .lreg and .greg; the .greg dump is during global alloc. The .lreg dump (after local-alloc) shows the change already.

Let me check: is there a `regmove` or `flow` pass between sched1 and local-alloc? In gcc 2.7.2's toplevel: ... sched1 (schedule_insns), then local_alloc, then global_alloc, then ... The dump flags: -dL = local-alloc dump (lreg), -dg = global-alloc (greg). So .lreg is after local-alloc.

So local-alloc did it. Which function? Let me search local-alloc.c for code that replaces a use of one reg with another: `optimize_reg_copy_1` does: "If SRC is not dead, and the copy is in a loop, replace uses of SRC with DEST"? Let me read it.

Actually, let me search for where local-alloc modifies insns with `replace_rtx` or `reg_renumber`.

Hmm, but this is a rabbit hole. The practical question: is there a C-level lever? 

Since the mechanism is the equivalence between a0 and r72 created by the call-arg copy, and sched1 places the copy before the store, the lever would be to keep them in different basic blocks or make the copy not a simple copy.

Let me try a few more things:
- `func_80171990((u8 *) (s0));` with the arg computed into a fresh pseudo via a cast to `u8 *` from a `char *` — same.
- Call the function through a different expression: `((void (*)(u8 *))func_80171990)(s0);` — changes the call RTL slightly (maybe an extra cast) but the copy remains.
- Make the call arg `(u8 *)s0` but with s0 being the *second* copy: e.g. `void *s0 = a0;` then `char *n2 = (char*)s0;` and the call arg `(u8*)n2`. Same.

What about making the store's base a pseudo that is NOT r72 by using a *second* copy of s0 that is kept separate: e.g., `char *n2 = (char *)s0;` and the store uses n2, while the call uses s0. cse merges n2 with r72... unless n2 is set after the call and the store uses n2 — cse merges anyway (both are copies of the same pseudo).

Hmm, cse's make_regs_eqv merges regs that are equal. n2 = s0 → equal → merged.

What if the store's base is `(char *)s0 + 0x204` and the call arg is `(u8 *)s0`? The store base is r72+516 → base r72.

What if the store base is a *memory load* of s0 from the stack? e.g., spill s0? That adds instructions.

I think this is a genuine WALL (sched1-argcopy-hoist), as the prior agent concluded.

BUT: there's one more idea — what if the *second store* is placed such that sched1 cannot hoist the copy above it, by making the copy depend on the store? E.g., the store's value v0 could be reused as the call argument? No, the arg is the pointer.

Or make the copy depend on a value the store defines: e.g., after the store, `v0 = ...` and the call arg... no.

What about a *do-while block* around the call setup + call? w14 (do-while around the call) = 4 (ORDER). Hmm.

What if the call is inside a do-while that also contains the store? w13 = 4.

The target's schedule is: copy, jal, store (delay slot). Our best body gives: copy, li, store1, li, copy, jal, store2. Wait no — the target also has the store2 in the delay slot. So both have the same schedule; the difference is only the base reg.

Given the mechanism, the base reg depends on whether the store's RTL operand is a pseudo or hard reg. Lever-free = pseudo → replaced.

Hmm, but WAIT: what if the store's base pseudo is *not* the same as the copy source? Then update_equiv wouldn't replace it. The copy source is r72 (s0's pseudo). The store's base is r72 (because new_var == s0). To have a different pseudo, the store's base must be a value not cse-equal to s0... but numerically equal. Any real-C way? `(char *)s0` is a copy.

What about the store base being `s0 + 0x204` where s0 is a *different variable* that was assigned from a0 *after* the call? E.g.:

```
  s0 = a0;
  call1(a0);
  s1 = (char *)a0;   // ?? a0 is clobbered
```
No.

What if the pointer used for the stores is reloaded from a local variable stored on the stack? That would add insns.

OK, WALL. But I need 20 min on item 2 (until ~18:29) and 30 tries (done: ~31).

Let me use the remaining ~13 min productively: 
1. Try a few more exotic variants (10-15 more tries).
2. Confirm with the pass dump that sched1's hoist is the cause (I have it: .sched shows insn 43 with base r72 and insn 46 before it; .lreg shows a0). Actually let me verify the *order*: in .sched, is insn 46 before 43? The .sched output showed insn 43 at position 46→48, and insn 46 was before it. Let me check the sched dump order to confirm the hoist.

Let me look at the .sched dump around those insns.
