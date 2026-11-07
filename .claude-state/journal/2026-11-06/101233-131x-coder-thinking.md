---
ts: 2026-11-06T17:12:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tnyntCwYEKNuZXYelZr5
---
b43 is clean. It scores 10 (117 ins, REG-mixed: v1→s0). Good.

Let me wait out the remaining ~1.5 min with one more batch (3 tries), then record the WALL.

Actually, let me reconsider one more time whether there's a trick: the cse rule "Among pseudos, if NEW will live longer than any other reg of the same qty, and that is beyond the current basic block, make it the new canonical replacement."

What if the temp's last use is NOT beyond the block because the block extends past the branch (cse follows the branch path when there's only one path?). In cse_end_of_basic_block, it scans `while (p && GET_CODE(p) != CODE_LABEL)` and handles branches via the path mechanism. If the branch is a conditional, cse might follow one path. In our case, the join label stops the scan.

What if we make the join label a *deleted* label? E.g. if the if/else is optimized so the label is removed... 

What if the branch's two arms both continue (no join)? That's not possible with a simple if.

Hmm, one more: what if the temp is assigned in BOTH arms (so the join label is after both assignments) and the uses are after? E.g.:
```
if (q < 0) n = q + 3; else n = q;
```
The temp n is set in both arms; cse's make_regs_eqv for the else arm's `n = q` (new=n, old=q)... same.

OK, wall. Let me do 3 final tries: 
- b49: `if (q < 0) n = q + 3; else n = q + 0;` — identity, no.
- b49: move the `q = rand();` line after the `if`? no.
- b49: use `s32 n = q;` initialized at declaration (init at decl): `s32 n = 0;` then `n = q;`.
- b50: `n = q; if (q < 0) n = q + 3;` with n declared inside the `if` block scope? no.

Let me just run 3 and record.
