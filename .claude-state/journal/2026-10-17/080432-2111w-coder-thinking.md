---
ts: 2026-10-17T14:04:32.342Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
So CSE deleted both references after following jumps into label 425, which only had one use. I'm trying to figure out why adding another use didn't change that behavior, wondering if the jump pass or the front-end's handling of the constant initialization for z is what's folding things away.

Looking at the actual CSE path-following logic in cse_end_of_basic_block, it only follows a conditional jump if -fcse-follow-jumps is on, the path length limit isn't hit, the jump target is a label used exactly once, and there's a following insn — then it walks backward through the label checking for notes or other labels that would block the traversal.

If it hits a BARRIER while scanning backward, it treats the jump target as an extension of the basic block and takes that branch. Since L had two uses in c1, this condition shouldn't apply directly, which makes me wonder whether some other path — maybe through skip_blocks or the opposite branch — is responsible for the move actually getting deleted.

I need to check how jump1 could have deleted the jump by looking at the actual use counts for c1.
