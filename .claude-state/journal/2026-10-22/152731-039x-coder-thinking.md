---
ts: 2026-10-22T21:27:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rJ54b3ELJQemsiRcQA4P
---
So in v12, arm1 is missing its tail: at insn 54 arm1 has `j 14c4` — arm1's tail merged with arm3's tail again (partial merge: sh0-36; sh0-46; j; sh48 shared). Right — because arm1 and arm3 both end with the same 4 insns; only the ORDER of the earlier part differs.

v12 arm3 order P,Q,S,R,k → in arm3 the source order differs from arm1 (P,Q,R,S,const) so sched1... hmm, but the final arm3 has sh0-36 then sh0-46 — same as arm1. So the common suffix is 4 insns → merged.

So the merge is defeated only if the LAST insn differs, i.e. the delay slot store. Hmm, but v15 (arm1 order changed) got 114 with only an ORDER diff — that means no merge. In v15, arm1's order P,Q,R,k,S: sched put sh0-46 in the j delay slot → arm1's last insn differs from arm3's (sh48) → no merge, but the order is wrong.

So: the merge is defeated when arm1's delay slot isn't sh v0,48. But the target requires sh v0,48 in the delay slot... 

Unless the difference is in an earlier insn with the same suffix... no, suffix matching.

Hmm wait, v12 got 114 ins with a merge of 4 insns? Then arm1 would be shorter... 114 total means no net merge? The diff shows arm1 at 14c4 `j 14c4`... wait mine's insn 54 is `j 14c4` and target 54-57 = sh0-36, sh0-46, j, sh48. So mine's arm1 has 1 insn where target has 4 → mine loses 3, but elsewhere mine has 3 extra? The diff at 61c64 etc. Total ins both 114.

OK so v12's merge is 3 insns (sh0-36, sh0-46, sh48) with the j in arm1's position... 

This is getting complicated. Key insight: to prevent the merge, arm1's LAST insn (the delay-slot store sh v0,48) must differ from arm3's. Both are const stores of -80. So the only remaining difference: make arm3's last store a *register* store, which requires k to survive as a reg.

Alternatively: make the *jump* differ — no.

Alternatively: make the last store in one arm not be in the delay slot... the target has it in the delay slot in both arms.

So: k must be a register at jump2. From the earlier RTL dump, k IS a register at RTL (reg/v:HI 121). It gets folded to a const by cse2 or combine. Let's find where: check .cse, .combine, .sched dumps for arm3's store pattern in the base.

If combine folds it, then blocking combine is the key. If cse2, blocking cse2.

Let me grep the base dumps in order.
