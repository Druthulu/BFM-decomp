---
ts: 2026-10-17T14:00:48.105Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
Casting through float wouldn't help here since we're dealing with FP. I'm wondering whether cse equivalences like pos=arg2 survive into a new basic block — since else-branches start with a label, that triggers a new cse block, and I recall cse tables get flushed at block boundaries, so the equivalence likely wouldn't persist there.

But maybe it isn't cse at all — maybe it's register allocation tying the pseudos together. If cse canonicalized branch uses to pos and arg2 died at the copy, then local/global allocation could tie arg2's pseudo to a2 and pos's pseudo to the other register, which matches what I'm seeing. So the real question becomes how to prevent cse from making that substitution in the first place.

That trick doesn't help either—checking if arg1's known-bit pattern could let a copy like `arg1 & 0x8001` simplify away, but with multiple uses the andi wouldn't fold and would add an extra instruction anyway. It seems like the long-lived copy in the target really is just a plain move, so maybe the only way to force it is through an opaque identity that blocks optimization.

Then I consider another path: maybe combine itself merges the initial parameter copy into the later test instruction, substituting the original hard register directly into the AND operation even though the copy register is still needed elsewhere.

I'm checking whether SMALL_REGISTER_CLASSES matters on MIPS for hard-reg substitution rules, but that doesn't explain why my test case didn't combine the copy into the and-insn — they're in the same block with adjacent log links, so something else must be blocking it. Maybe the determining factor is whether the parameter's value is actually read again after the test, which would force combine to keep the original set alive.

Perhaps the real difference is in how a promoted HImode/u16 parameter gets expanded in assign_parms — if the nominal mode differs from the promoted mode, GCC may emit an explicit sign/zero-extend at function entry, creating two distinct pseudos rather than a simple move. That would explain why the target's prologue just does a plain register move for arg1, since there's no promotion mismatch to extend.

I'm tracing how arg2 gets treated as promoted without conversion, matching the sign-extend pattern against the target's sll/sra sequence on a2, but the (s16) cast on arg2 doesn't quite line up since the assembly explicitly re-sign-extends it rather than trusting a promoted value.

Shifting focus to CSE's label-handling behavior: new_basic_block resets reg_qty for every register, so after a label, pos and arg2 lose their established equivalence and the else-branch ends up reading arg2 directly instead of reusing pos.

Thinking about cse's extended-block path following, I realize it extends through conditional jumps when a label has only one use, so both branch paths get treated as extended blocks either way — this particular approach won't break the equivalence. Given limited time remaining, I should check the clock and consider just trying the T1 approach directly on the full translation unit instead.
