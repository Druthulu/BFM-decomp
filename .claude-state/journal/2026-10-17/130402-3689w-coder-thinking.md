---
ts: 2026-10-17T19:04:02.001Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm trying to figure out who removes that redundant a0 assignment — likely CSE recognizing a0 still equals its original argument value, since nothing clobbers it before the first call, making the self-copy a no-op. But for the branch target, a0 needs to be treated as potentially changed rather than assumed equivalent.

I'm wondering if a different structural trigger — like the register copy occurring after a label, or the value being tracked through a different mode or addressing path — could break that equivalence tracking and prevent CSE from deleting the move.

Reorganizing the branch structure doesn't seem to help since the calls still end up in the same extended basic block through fallthrough. CSE's jump-following behavior still pulls single-predecessor labels into the same tracked region, so restructuring the conditionals isn't enough to break the equivalence.

I'm now suspecting the deletion isn't CSE at all but a later pass noticing the entry move is redundant once register allocation assigns the same hard register, or CSE's equivalence tracking directly linking the pseudo to the hard register a0 when processing that initial move.

That doesn't quite fit either. Maybe the real explanation is simpler: perhaps in gcc 2.7's cse_insn, a set of a register to a value already recognized as equivalent to that register gets deleted outright as a no-op, which would explain the pattern if `s0` and `a0` end up in the same equivalence class before the redundant move.

I'm wondering if the discrepancy actually comes from where the parameter's address is taken, forcing it to live on the stack and requiring an extra store, which would change when cse can establish that equivalence.

Alternatively it could be a K&R-style function signature issue, or some other structural mismatch in how the pointer argument gets computed before the call that breaks cse's ability to merge it with the known-equal value.
