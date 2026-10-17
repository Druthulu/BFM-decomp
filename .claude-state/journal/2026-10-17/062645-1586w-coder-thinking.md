---
ts: 2026-10-17T12:26:45.185Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
Since MIPS doesn't define SMALL_REGISTER_CLASSES, x can be a hard register like v0. I need the pattern `if (cond) x = a; else x = b;` where x = a is a single instruction before the simplejump, and x = b is a constant or register after it, collecting all jumps to the else label (multiple branches allowed via nuses) so I can transform it into `x = b; if (...) x = a`.

Testing this against `if (A && B) return expr; else return 0;` — the expansion requires v0 = expr to be exactly one instruction (temp3 = prev_active_insn(insn)), but if expr itself takes several instructions to compute before the final copy into v0, that breaks the single-instruction requirement. I'm considering whether flipping the order helps: `if (!(A&&B)) return 0; else return expr`, making x = a the trivial `v0 = 0` (one instruction) and x = b the `v0 = expr` side, which just needs to be a REG/SUBREG/constant source rather than a single instruction — so if expr was computed into a temporary first...

I'm wondering whether the computation could sit between the two jump passes — jump optimization runs again after cse, so combine might later merge the move into the xori directly even though scheduling itself can't cross the branch.

Also considering whether MIPS's RTL expansion of `sle` comparisons emits the slt+xori pair as a single multi-instruction pattern, which would explain the ordering without needing to invoke scheduling or combine at all.

But scheduler can't move addiu after the bnez since the delay slot is nop instead—unless addiu writes v0, which is live across the branch and would clobber the result on the taken path, forcing it to stay as nop rather than fill the slot. So the real constraint seems to be register allocation conflicts with v0 preventing the reorg from filling that delay slot.

I'm thinking I should go look at cross-jumping or related code around jump.c lines 850-1000 for more context.
