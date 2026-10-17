---
ts: 2026-10-17T12:47:23.792Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
Combine's split path calls split_insns on unrecognized PARALLELs, trying define_split patterns when a three-insn combination collapses to a simple SET — most of these MIPS splits only apply post-reload.

I'm now reconsidering a totally different natural candidate: a pointer post-increment loop like `*p++ = ...`. Without hardware autoincrement on MIPS, p++ becomes p = p+4, and if cse can fold each successive p value into a constant offset from a known symbol base, the addressing collapses to absolute form — but that only works if the starting base is already known, otherwise it's circular. I'm also considering two separate variables p and q interacting across blocks, and specifically the case where base's defining insn isn't recognized as constant by cse1/cse2 but becomes foldable once combine simplifies a later use of it into a symbol reference, with the resulting i3 carrying no REG_EQUAL notes forward.

So I'm examining whether cse can fail to see through an EBB boundary (like a LOOP_END) on its first pass but succeed on cse2, meaning base ends up getting a REG_EQUAL note added anyway, which breaks the "laundering" approach — unless the problematic set happens inside a `do { t = SYMBOL; } while(0)` construct positioned before the loop notes take effect, which might dodge the issue.

Looking at f2's residual diff more carefully: my generated prologue puts the store before `move a0, zero`, while the target has `move a0` earlier, right after the stack adjustment. This matches the same barrier-placement pattern — the barrier sits right after LOOP_END, pinning everything before the store in its original order while the `la` stays inside the loop body.

Any loop note in block 1 seems to block hoisting `move a0, zero`, since the barrier always sits before the call, and the a0 assignment in source always happens immediately before the jal — so there's no way to get notes between them. The only way target's ordering works is if the barrier is the very first insn of the function body in the sched2 stream, with prologue and notes preceding it, letting everything after shift forward while `move a0` lands first.

Checking block 3's li a0,2 as a similar case, and the epilogue sequence at the very end — a loop placed there seems harmless since it wouldn't hide base from cse in an EBB sense. So loops don't actually help conceal base here, nor do labels, which means cse1 must fail to know base through some other means — implying base's defining source isn't constant at cse1, so it either gets turned into `la` via combine or comes from something inherently non-constant like a parameter, load, or call result.

With that constraint, I'm hunting for an expression form that cse can't fold but combine can still simplify into a constant address — something like a pointer-difference trick or an address computed through a struct-member cast, since plain identity expressions get folded away by the tree optimizer before they're useful.

So it seems like within the rule set, the only real mechanism for hiding the constant from cse1 and sched1 is an EBB/loop boundary, which conflicts with the target goal. I want to double check whether cse2 really doesn't fold `(mem (plus base k))` addresses, since if that holds, base just needs to be hidden from cse1's reach — and I'm also considering whether cse1's path-following or skip_blocks logic offers another angle, though that seems unlikely to be relevant.

I'm now wondering about invalidation: cse1 invalidates a register's equivalence when it's set or clobbered, and calls only invalidate call-clobbered hard regs — but could a CLOBBER of base itself be emitted somewhere, like before multi-word moves or in emit_no_conflict_block for struct returns? That seems like a stretch for a user-level construct. I'm also ruling out asm clobbers since asm is forbidden, and considering whether a SUBREG partial write to a wider pseudo containing base could be the trigger.

Thinking about whether base could be a SUBREG of a wider DI-mode variable, like a union field — if assigning through the pointer field invalidates the whole thing via a dest SUBREG, that could explain unknown aliasing. I think the fastest path forward is just to test this directly and see what GCC actually allocates.
