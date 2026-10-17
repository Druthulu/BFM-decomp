---
ts: 2026-10-17T10:42:09.101Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
I'm wondering whether a single-set insn without a REG_EQUAL note could still arise if the base's setting insn gets moved by loop-invariant motion before scheduling sees it, losing the annotation in the process.

I'm wondering whether placing base's set inside the do-while could matter, and considering alternate explanations for f2's behavior — maybe cse2 collapses a second redundant set, or maybe s0 isn't the record base at all but a colour pointer offset by -12, implying the original code might iterate using a pointer into the colour field rather than the record itself.

Thinking further, maybe the real trick isn't in the sets but in the loads: if the load address came from a pseudo that cse could fold to a constant within one EBB but not across the new block boundary, that would explain why the first block gets a constant address while blocks 2/3 fall back to a register-based address — unless the colour pointer gets re-set within each block, which would keep cse from treating it as constant everywhere.

Since the stores go through a base register that's known to equal a fixed symbol, but the loads resolve to constant addresses via cse folding, the conflict test between them collapses to zero because they're different symbols — so to actually get a conflict, the base register must remain unknown at scheduling time, which only happens when there are multiple sets or no REG_EQUAL note, and I'm now considering whether a REG_EQUIV note behaves differently regardless of how many sets there are.

I'm checking whether base could be set by something other than a plain single_set, or whether it's pinned to a hard register, but neither seems to apply. The more promising case is if base register 75 is set from another register (reg 80) that itself holds the symbolic constant, but reg 80's constant value was established in a prior extended basic block — meaning cse in the current block wouldn't know reg 80 is constant, so no REG_EQUAL gets attached and base stays unknown going into scheduling.

But then I realize reg 80 itself would have a REG_EQUAL from its own defining insn, and if its only use is this copy into base, combine could still merge the two insns together, potentially producing the symbolic reference directly in the combined instruction.

Since reg 75 ends up with no REG_EQUAL note and only one set, it becomes opaque to reg_known_value. Now I'm checking where the base copy lands relative to the do-while loop boundary — I need it placed in the second EBB so that the splitting of basic blocks by the loop structure hides it from that CSE pass, while confirming whether CSE2 also respects that same EBB split after jump optimization.

But if CSE2 happens to merge those EBBs anyway, it would see the copy's source as a known constant and attach the REG_EQUAL note there instead, defeating the plan — unless CSE2's own folding mechanism undoes that substitution before it sticks, which seems to be the key to why the count stays preserved in blocks 2 and 3.

Actually c27's rescue note was really about free.c's case, where rescue only applies to addresses held in live registers. In h2 the blocks explicitly use raw constant offsets from the base symbol that end up as k(s0), so I need to actually check the h2 cse2 dump directly to see whether the base's set carries a REG_EQUAL note and whether those addresses retain loop structure.

I'll check h2's dumps to verify whether sched loses visibility into `base`'s value because combine drops the REG_EQUAL note when merging `base = a` with `a = sym`.
