---
ts: 2026-10-17T12:29:14.091Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm trying to pin down the actual GCC pass ordering—whether sched1 runs before local-alloc and whether REG_EQUIV notes set during local-alloc's update_equiv_regs are still relevant given that sched1 only runs with -fschedule-insns.

Since reg_known_value only applies to pseudos, the base register s0 being a hard reg would be opaque during sched2, meaning sched1 (if it ran) must be the pass that actually had visibility into the symbolic base. I'm now considering memrefs_conflict_p behavior in 2.7.2 when comparing two different constant symbols, and trying to figure out under what conditions cse would fail to attach a REG_EQUAL note for a constant set — likely if the source isn't recognized as a known constant at the time cse1 runs.

I'm also exploring whether combine could later fold an unrecognized plus expression into a load-address pattern that cse missed, or whether multiple real sets of base (not dead ones removed by flow) across branches of a conditional could explain the lack of a known value, though that seems inconsistent with how cse1 would see the label. I'm circling around pointer increment patterns too, like a base pointer being incremented per block, wondering if that's how the target ends up treating the base as constant across blocks despite multiple sets.

Now I'm considering whether the base could be set in a separate extended basic block reached through a conditional structure that doesn't leave loop notes behind, and whether cse1 could fold a conditional jump to a constant destination in a way that deletes the branch but leaves the label intact long enough to matter, especially since -fcse-follow-jumps is likely active at this optimization level.

I'm tracing through cse_main's behavior: when a label sits in the middle of a path and starts a new extended basic block, cse_basic_block resets its equivalence table via new_basic_block, meaning the base register's known value from before the label wouldn't carry forward into the new block even if a REG_EQUAL note on the original set still exists.

Then I'm questioning whether cse2, running after loop optimization with flag_rerun_cse_after_loop at -O2, would fold base+k into an absolute address once the jump is gone and the whole thing is one EBB — but the f2 test result with loops suggests cse2 doesn't actually perform that fold, based on the insn transformation it produces.

So I'm trying to pin down why cse1 treats the base as unknown in the first place — possibilities include the EBB boundary from a surviving label/jump, or find_best_addr picking the register form over the constant because of relative address costs on MIPS.

I'm now considering whether cse_end_of_basic_block's jump-following logic plays a role: if an `if (base != 0)` conditional gets folded differently, that could affect whether the label survives for cse to flush at, but in 2.7.2 that symbol comparison doesn't appear to fold the way I'd expect.

But what would fold in cse1 and not jump1 is a known variable like `i = 0; if (i == 0)` — something cse tracks but jump doesn't. That edges toward the "do-nothing statement" restriction though, since an if on a known constant could be seen as trivial, so I'm weighing whether a loop pattern like `for (i = 0; i < 3; i++) { if (i == 0) ... }` reads as natural rather than contrived.

Maybe the real structure wasn't a conditional at all but a struct access — something like a record pointer dereferencing fields where some accesses go through a register and others resolve to absolute globals directly, and the mixture of absolute vs. register-relative accesses across the two blocks might reflect how the optimizer chose addressing rather than anything in the source itself.

This is consistent — the various stores to D_800A5E94-12, D_800A5E94[0], and D_800A5E94+4 all relate back to the same symbol through the register. So I need to figure out which pseudo holds the symbol value exactly: likely the first materialized reference, D_800A5E94-0xC forced into a1, becomes the anchor that all related offsets build from.

For older MIPS gcc with -G0, legitimate addressing doesn't accept bare symbols, so each constant address of this symbol gets forced into a temp pseudo at expand time; cse1 then rewrites later temps as offsets from the first one via related-value tracking. Whichever reference appears first in the extended basic block becomes that anchor.

Now I'm reasoning through which expression comes first in the source and how that affects scheduling — if the anchor is the `D_800A5E94 - 0xC` store, the scheduler would already know its value through the REG_EQUAL note from cse, and the same applies to any `temp2 = temp1 + k` rewrites, since those also carry REG_EQUAL notes with constants. I'm now considering what this known-value information implies for the scheduler's alias analysis — specifically whether stores to sym+k conflict with loads from a different symbol like D_801F1558.

With a known base, memrefs_conflict_p can tell there's no overlap, so loads of D_801F1558 get hoisted above the stores. But with an unknown base, the store and load are assumed to conflict, so in the target code the stores happen before the lbu loads in both blocks, matching true dependency order rather than being hoisted — meaning the scheduler is simply preserving source order due to alias uncertainty rather than reordering for latency.

Thinking about what makes a register's base opaque to alias analysis: for pseudos, reg_known_value and REG_EQUAL notes can pin down a constant base, but after reload, hard registers like s0 have no such known value, so sched2 treats s0+offset as conflicting with any symbol-based memory reference. This suggests sched1 (with pseudos, possibly still knowing the base) scheduled things one way, and then sched2, operating on hard registers with no alias info, couldn't undo or further reorder what sched1 already fixed in place.

So the real question becomes whether sched1 itself saw a conflict between the store and load via memrefs_conflict_p once canon_rtx substitutes in the known symbol for the base register — if sched1 also computed matching symbolic addresses for both the store and the load, it would treat them as conflicting and preserve their order, consistent with what's observed.

Unless the pseudo holding the base address isn't actually resolvable to a constant symbol at cse1 time, say because its value comes from `base = &arr[i]` with a variable index that only becomes constant later.

Another path: if the base pseudo gets set twice -- say reused for different pointer values across the function -- then reg_n_sets[base] would be greater than one, which could prevent CSE and later passes from recognizing it as a known constant address.

I'm now wondering where the target's loads diverge from source behavior—those absolute lui/lbu pairs in the target seem independent per symbol. Thinking through cse's behavior more carefully: constant-spelled addresses get forced into temps at expand time, then cse rebases related values to reg+k form, while a base+k with a known base folds directly to lui/%lo addressing, which explains the asymmetry between free.c and c0/c2's codegen.

For c0's anchor pattern, I suspect the sched pass can see through the temp because cse attaches a REG_EQUAL note once it rebases temp2 to temp1+k, and then combine likely merges that into the memory reference directly, deleting the original temp2 set entirely.

Rather than keep theorizing, I should check memrefs_conflict_p and true_dependence directly in 2.7.2, and better yet just test empirically by looking at c0.c and its diff output.
