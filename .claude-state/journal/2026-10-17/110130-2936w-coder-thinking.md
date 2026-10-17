---
ts: 2026-10-17T17:01:30.919Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
I'm checking the parameter copy order in the function prologue, comparing how the target assigns s4←a0, s6←a1, s5←a2 against my own ordering of self/dst register moves to make sure arg0 lines up correctly.

Now I'm testing whether skipping the self-copy and only keeping dst changes the live-range interference numbers — but that pushes dst's range too far and loses the tiebreak. I'm also considering different placements for the self/dst initializer statements relative to the decls, and whether restructuring the var_s3 hoist avoids the extra prologue load instruction.

Trying to nudge the ratio in var_s2's favor: if I can trim var_s3 down to 8 references instead of 9, the priority ratio drops just enough (0.47 vs 0.52) to flip the ordering in var_s2's favor. Now I'm scanning its use sites — the assignment, the entry test, and so on — to see which reference could be eliminated.

Actually that self/dst copy probably isn't cse evasion but a genuine parameter copy, matching the prologue pattern. The real issue might just be ordering mismatch, so I should try quick variants of statement order and placement for the self/dst assignments and var_s3.
