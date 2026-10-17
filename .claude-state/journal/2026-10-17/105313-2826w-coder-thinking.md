---
ts: 2026-10-17T16:53:13.985Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm checking combine's can_combine_p logic to see why it refuses to merge insn 23 into 26 — likely blocked by a check on whether the destination is a user variable that shouldn't be substituted away.

For the target case, insn 26 sets register 74 and insn 23's source is also 74, so combining into `74 = 74 - 1` should be fine since they're adjacent. But in the pinned version where v1 = v0 + $0, combine would need to fold a plus-of-plus with a hard register operand that isn't a literal zero, which it can't simplify — so the addition stays separate and shows up as `addu v1,v0,zero` instead of collapsing into a move.

I'm now wondering what would actually make a `move v1,v0` survive — that requires v1 to still be live after insn 26 rather than immediately redefined. That could happen if register allocation differs: perhaps the loaded short value sits in one pseudo for the comparison while a sign-extended copy is kept separately for later use in the then-branch, meaning the extend and the raw load value are different registers that just happen to get coalesced into a move.

I'm also checking the similar 0x108 branch case, which has the same pattern: load into v1, compare, then copy into a0 for later use. That suggests combine refuses to merge the copy instruction when the destination of the copy matches the source register used elsewhere, which would explain why the move persists instead of being folded away.

I'm recalling the specific conditions in can_combine_p from the GCC 2.7.2 source — checking rules about not eliminating a store to the stack pointer, and restrictions around ZERO_EXTRACT or STRICT_LOW_PART destinations, plus special handling for self-referential sets with REG_EQUAL notes.

Still checking more combine restrictions...

Checking more conditions for rejecting the combination: volatile UNSPEC or asm shouldn't move across other insns unless adjacent, the source register's value shouldn't be invalidated by intervening sets (unless there's a REG_EQUIV note), and if DEST has a REG_NO_CONFLICT note in I3 or SUCC, skipping the combine gives better register allocation anyway.

There's also the reverse case where I2 is reversed, plus the handling for double-word pseudos set to constants, and the loop in combine_instructions that tries each insn against the ones it links back to, and the early exit checks for CALL_INSN involvement in I1/I2/I3.

I'm also considering the hard-register copy avoidance logic — combine won't merge if I2 copies a hard reg that's in a likely-spill class, under SMALL_REGISTER_CLASSES. For my case, I'm working through whether v1 needs to stay alive past insn 26, or whether the source value differs, tracing through the addiu/sh/sll/sra sequence to see if v1 gets reused afterward.

Now I'm exploring whether the copy could instead originate at reload time rather than from the original RTL — imagining a pseudo loaded into v1 and another pseudo in v0 at the branch point, checking if they could tie together during global allocation, and sketching out an alternate source where the decrement variable is distinct from the tested variable, with the tested one used again later.

Actually, maybe the loaded value and the register holding it afterward differ because that's a compiler-inserted copy, not register allocation. That copy and the subsequent add might sit in separate basic blocks if there's a label between them, which would break LOG_LINKS and prevent combine from merging them — like inside a loop or at a goto target.

But a jump optimization pass might delete a label with no remaining jump references before combine even runs, so I need another explanation. Maybe instead the copy occurs *before* the branch in block A while its use is in block B, and cse (working across the extended basic block through fallthrough) decides which register is canonical based on which one lives longer — explaining why it kept the value in a1 rather than v0.

This also means combine can't merge the copy into the branch across the block boundary, so the move survives and reorg schedules it into the branch's delay slot, matching the target's `beqz v0; move v1,v0` pattern. That suggests the source had `v1 = v0;` right before the `if (v0 != 0)` check — though I need to check whether cse would also rewrite the branch test itself from v0 to v1 if v1 becomes the canonical register.
