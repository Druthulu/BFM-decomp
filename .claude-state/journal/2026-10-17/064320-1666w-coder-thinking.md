---
ts: 2026-10-17T12:43:20.125Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm spotting two discrepancies: the register assignment (mine has rb in a1, m in a2, versus the target's reversed mapping) and the placement of `move a0,s0` at the head of the else-block. The target computes `m = rb & 0xff` in the branch delay slot, while in the else branch it sets up a0 first before computing d from rb, whereas mine orders things differently.

I'm wondering whether this relates to how the scheduler keeps hard-register argument setups adjacent to their calls — maybe `a0 = s0` gets hoisted early if it's treated as a pinned/pending argument set rather than scheduled near the jal. It's possible the target's call ordering actually places the field_4 store before the call takes effect, since the store sits in the delay slot of the jal and executes prior to the branch.

Maybe it's not about store ordering but about how sched1 treats call argument registers — possibly GCC groups instructions setting hard call registers together with the call itself as a scheduling group, which would explain why a0 gets set immediately before jal regardless of other computations.

Right, so this logic walks backward from the tail insn, excluding argument-loading instructions that immediately precede a call so they stay anchored together—but I'm second-guessing whether this applies since calls typically don't end basic blocks in the scheduler's view.

In my case, `a0=s0` sits right before the call, so it probably stayed at the head of the block because that's where it was placed during argument expansion in the original RTL, before the call's arguments got evaluated.

Maybe the register holding flags happens to be a0, and it dies right before that andi instruction, which would explain why the move to a0 appears where it does in the else block.

In the tree version, a variable pinned to $4 gets copied at the block head so it naturally lands in a0 for the call, but my version has CSE merging that same copy into slot directly, erasing the explicit move. I need to figure out what forces the target compiler to keep that separate assignment instead of folding it away — maybe the value being copied isn't literally slot but something recomputed, which would prevent the merge.

Could the function pointer call be relevant, or is it just a different pseudo being passed as the argument? I'm also wondering if sched1 scheduling, which runs before register allocation, is responsible for hoisting the a0 assignment up to the block head when there's no conflicting instruction in between.

Maybe the actual source has a different call pattern — perhaps an indirect function pointer call where the function address itself gets computed first, forcing the address into a pseudo before the argument setup, which would explain a0's placement differing from my version.

Switching tactics, let me look at the register allocation priority between rb and m instead. The priority formula weighs refs against live range length, so rb (more refs, shorter live range) outranks m — I could try tweaking the else branch to use m instead of rb in that subtraction and see if that shifts allocation order favorably.

I'm also considering whether m could be an unnamed temp rather than a named variable, inlined directly into a function call argument, which would change how the compiler threads it through registers in the branch delay slot.

Checking the alloc_table ordering for flags, rb, t, and m, I notice the target binds m to a1 then copies it to a0, while in mine rb and t both end up sharing a1 since t's last use happens right at the load, letting rb reuse that register afterward.

In the target, m and rb conflict since m is computed as rb masked with 0xff and rb is still needed later, so the allocator must place m before rb in priority order. I'm now working through gcc's register-allocation priority formula involving reference counts and log2 weighting to figure out why m gets scheduled first.

Thinking about ways to shift priority: maybe boosting m's reference count by using it again later, or noting that combine might simplify rb-0x14 directly since rb is already a zero-extended byte equal to m.

If rb weren't used elsewhere, combine would collapse the lbu+andi into just lbu since rb's nonzero bits are already ≤0xff, making the andi redundant. But the target keeps both andi and lbu, so combine apparently isn't treating rb's value as bounded to 0xff at that point—worth checking whether nonzero_bits tracking actually applies here given lbu's zero-extension semantics.

Shifting to the liveness angle: m is computed once before the branch but only used in the then-block, staying dead through the else-block. In the target, m's computation sits right before the branch in a delay slot, which makes me wonder if allocno ordering tie-breaking in register allocation (favoring the lower-numbered allocno) is what's driving this placement difference rather than anything about declaration order.

Priority, using global.c's formula of floor_log2(refs) times refs divided by live length times size times 10000, gives rb a priority around 24000 with 6 refs and m around 10000 with 4 refs. To flip the ordering so m wins over rb, I'd need to cut rb's reference count down to around 3, which would drop its priority below 10000.

Trying the cost formula with raised ref counts doesn't flip it either — 16000 still beats m's 10000. Bumping m's refs to 6 gets closer (15000 vs 24000) but shortening m's live length in the if-block actually makes things worse based on how it's placed there. So I'm considering lengthening rb's live range instead, since rb gets used later in the else branch.

Rather than keep guessing at these cost tradeoffs, let me just check the actual allocation table for d002 directly.
