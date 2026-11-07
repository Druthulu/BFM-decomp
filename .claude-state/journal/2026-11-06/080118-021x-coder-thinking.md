---
ts: 2026-11-06T15:01:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_waAbidDChA5iuDm05uca
---
Interesting: mine has `move a0,zero` at 8 (from `a0 = s0 << 10` where s0=0 propagated: a0 = 0<<10 = 0) then presumably at 10 the sll a0,s0,0xa. So without the launder, `a0 = s0 << 10` folds to `move a0,zero` (const propagation), then after the loop s0 updated... hmm.

Target at index 9 has `sll a0,s0,0xa`. Mine has `move a0,zero` at 8, and no sll at 10. So target does the shift from s0. Wait — mine at position 10 is missing the sll? Actually diff: delete mine[8] move a0,zero; insert target[9] sll a0,s0,0xa. So both have 33 ins but differ: mine has move a0,zero where target has something else at 8? Let me see full diff with more lines.

Let me get the full mnemonic diff. dt.sh tail larger.
