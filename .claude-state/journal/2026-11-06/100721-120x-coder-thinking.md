---
ts: 2026-11-06T17:07:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ReIgcbY6JgcXBq4OmwaH
---
All still >0. The best are 10 (b5, b8 — 119 ins). None 0.

Note b1/b2/b3/b7/b9/b10 are 12 (117 ins) — same as the plain no-pin.

Let me think about the cse canonicalization once more. The target's branch tests v0 (the call result, a hard reg). cse's make_regs_eqv prefers pseudos over hard regs, so the pseudo temp becomes canonical. UNLESS the temp's last use is not beyond the EBB.

Wait, actually re-read the rule:
```
if (! (firstr < FIRST_PSEUDO_REGISTER && FIXED_REGNO_P (firstr))
    && (new >= FIRST_PSEUDO_REGISTER || REGNO_REG_CLASS (new) != NO_REGS)
    && ((new < FIRST_PSEUDO_REGISTER && FIXED_REGNO_P (new))
        || (new >= FIRST_PSEUDO_REGISTER
            && (firstr < FIRST_PSEUDO_REGISTER
                || ((uid_cuid[last_uid[new]] > cse_basic_block_end
                     || uid_cuid[first_uid[new]] < cse_basic_block_start)
                    && (uid_cuid[last_uid[new]] > uid_cuid[last_uid[firstr]]))))))
```
new=temp (pseudo), old=v0 (hard, not fixed). firstr=v0. The third condition: new >= FIRST_PSEUDO (true) && (firstr < FIRST_PSEUDO (true, v0 is hard) || ...) → true. So the temp becomes canonical. So cse rewrites the branch to the temp.

But wait — in the target, the temp is the pinned n ($16), a HARD reg. new=16 (hard, not fixed since $16 is callee-saved... is $16 FIXED? no). old=v0 (hard). The condition: new < FIRST_PSEUDO && FIXED_REGNO_P(new) → $16 is not fixed → false. And the second branch (new >= FIRST_PSEUDO) false. So the temp does NOT become canonical → the branch stays on v0. Exactly.

So the target's behavior REQUIRES the temp to be a hard register. Since the pin is the only way to force a hard reg, and register vars are forbidden... this looks like a genuine WALL.

But wait — maybe there's another way to get a hard register: a *parameter* passed in a register! E.g., if n were a function parameter (in $a0-$a3), it's a hard reg. But our function has one param a0. We can't change the signature.

Hmm, but the temp could be an argument to... no.

Alternatively, make the temp's last use NOT beyond the EBB: if the temp's uses are all in the same EBB as the copy, the pseudo stays non-canonical and the branch keeps v0. The EBB ends at the branch target (the join label). The uses (shifts, sub) come after the join → different EBB.

But what if the join label is NOT a cse EBB boundary? cse splits EBBs at labels that are jump targets with multiple predecessors. The join label 137 is targeted only by the branch at 134 (one predecessor). Hmm, but cse_basic_block_end is set at... let me check how cse determines the block end. In cse.c, `cse_basic_block (from, to, next_branch)`: it scans until a label or a branch? Let me look at how the EBB ends. `cse_end_of_basic_block` returns the end. It ends at a CODE_LABEL that has a jump target, or at a conditional branch? Let me check.

If the EBB ends at the conditional branch itself, then the temp's uses after the branch are beyond. If the EBB continues to the join label (single predecessor), the uses are within.

In our z6 dump, cse DID make the temp canonical, so its last use was beyond cse_basic_block_end. So the EBB ended at the branch.

Hmm. Could we restructure so the branch doesn't end the EBB? cse_end_of_basic_block: let me read.
