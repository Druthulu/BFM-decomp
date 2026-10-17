---
ts: 2026-10-17T16:09:24.856Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
CSE would just fold the constant into the use since it tracks known register values within extended basic blocks, which in gcc 2.x follow fall-through paths across branches — so without an actual store/load barrier, the constant propagation isn't defeated here since the whole path is fall-throughs.

I'm wondering if inserting a label that's a real jump target (a join point) before the use would break CSE's knowledge, since CSE flushes its table at multi-predecessor labels — but I also need to check cse2, gcse's absence in 2.x, and whether update_equiv_regs in local-alloc might still rematerialize the constant across basic blocks. Looking at the actual control flow, there's already a natural join point at the label after the inner conditional block, where the fall-through paths merge — this could be the spot to exploit.

I'm realizing that -O2's -fcse-follow-jumps and -fcse-skip-blocks let CSE treat this join as still part of one extended basic block, meaning the value table persists right through it anyway. So I need another way to break the chain — maybe by repositioning where s1 gets set, though scheduling won't move it across block boundaries since it's set early in the first block before any branches.

I'm trying to figure out what kind of control flow CSE genuinely can't follow — something other than this skip-blocks pattern, since calls alone don't flush the constant table. Maybe restructuring the condition into a single combined check with a goto doesn't actually change anything structurally. Perhaps instead I should try making s1 appear non-constant to CSE, rather than fighting the control flow itself.

I'm considering MIPS address costing in cse—whether symbolic addresses are weighted differently than register-plus-offset forms, and whether D_80078EC1's separate symbol reference would prevent folding with s1's load. I'm also exploring whether restructuring control flow with a goto could break the join that cse relies on to merge the two accesses.

I'm examining the skip-block mechanism in cse_end_of_basic_block: a jump around a block is only followed if the target label has exactly one use, so adding a second goto to the skip label might disable that optimization and force the desired code shape.

I'm also considering whether the jump pass runs before CSE and already simplifies things, and whether wrapping the problematic code in a do-while loop could exploit the NOTE_INSN_LOOP_BEG boundary where cse_end_of_basic_block stops -- though my earlier attempt with that approach didn't pan out.

I'm now trying a different arrangement where a label gets reached from two separate branches, hoping that forces CSE to treat the shared comparison differently.

I'm wondering whether volatile could hide the constant from cse, but that would turn s1 into a stack variable rather than preserving the intended semantics. I'm also considering whether cse only substitutes memory addresses when the cost comparison favors it, weighing a register-plus-offset form against a constant symbol-plus-offset form.

I'm trying different structural variants to see if cse folds the constant plus offset the same way—testing index variables, pointer arithmetic forms, and loop restructuring, but several attempts yield the same score. I'm now considering whether placing the use after a label with multiple references changes how cse treats the equivalence.

The set has to live in block 0, the target, since gcc 2.x doesn't schedule across blocks, so that rules out moving it. Maybe the original source expressed the address differently in a way that cse never folded it, meaning the "launder" is really about how the value was originally computed rather than any path-length limit in cse.

Also wondering if cse stops following across a label with multiple uses, like a loop back-edge, versus my dead do-while(0) which has zero uses of the loop label and thus wouldn't break cse's chain — a real loop would alter the code shape entirely. I'm running low on time and want to test two quick ideas: a dead `if(0) goto` that's eliminated before cse runs, or a plain pointer variable assigned from the data symbol with the set occurring in the first block.

Trying a function-scope struct alias for the pointer, same result as before, and checking whether the pointer survives as an argument expression evaluated alongside another function call — none of these variants seem to budge. I'm logging my best wall-time result as 14.
