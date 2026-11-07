---
ts: 2026-11-06T22:28:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PyijHamUrgSTSJOkOH0Y
---
Interesting. In w0:
- .greg order: 78 80 79 74 77 76
- r74 = d (9 refs, 27 live, conflicts v0,v1,a0,a1,s0,sp) → assigned s1
- r77 = s1ang (5 refs, 10 live, prefers s0) → assigned s0

Wait, .greg order 78 80 79 74 77 76. r78 gets...? r78 has no hard reg shown (dash) — hmm, but the .greg order lists allocnos considered for global allocation. Some got assigned to hard regs but the table shows `-`? Actually the table shows hard column: r78 `-`, r80 `-`, r79 `-`, r74 `-`, r77 `-`, r76 `-`. But .greg order is those 6. Wait, but r74 ends in s1 and r77 in s0 — but the table says r74 `-` and r77 `-`. Hmm, maybe the alloc table lists allocnos that got a hard reg elsewhere? Actually the table seems to list pseudos with their hard reg if assigned at that stage; `-` means not yet? Confusing.

Hold on: w0's table shows r75 s0 and r74 has no hard. But the final code has d in s1, s1ang in s0. Hmm, r77 "prefers s0" → s0. r74 conflicts s0 → gets s1. r75 s0 (2 refs/7, crosses 1 call) — that's maybe a temp? Hmm.

Wait, the alloc table is probably from global-alloc; local-alloc runs before global-alloc? In GCC 2.7.2, local_alloc runs first (register allocation order: local-alloc then global-alloc). Actually flow: local_alloc() assigns hard regs to block-local pseudos; then global_alloc() assigns global pseudos from the remaining. The alloc_table tool likely parses the .lreg dump and the .greg order.

Anyway: the key numbers:
w0: r74=d pri 10000, r77=s1ang pri 10000, TIE → "lower allocno wins, global.c:607". The .greg order is 78 80 79 74 77 76 — so r74 before r77! Yet d got s1, s1ang got s0. Why? Because r77 "prefers s0" (a copy preference?) and r74 conflicts s0. In global-alloc, the allocno ordering is the .greg order, but when assigning r74, s0 is... free? Unless s0 is reserved for r77 due to "prefers s0"? Hmm, no. global-alloc has a "preference" mechanism: if a pseudo has a preferred hard reg (copy), it gets it. But s0 conflict: r74 conflicts s0 — meaning r74's live range overlaps some pseudo already assigned s0, or a hard reg s0 is live. Which pseudo already has s0? r75 gets s0 (pri 2857, local? block 0, crosses 1 call). But .greg order doesn't include r75, so r75 was assigned by local-alloc to s0. Yes! r75 (2 refs, 7 live, block 0, crosses 1 call) is block-local-ish (blk 0, single block?) — local-alloc gave it s0. So r74 conflicts s0 because r75 occupies s0, and r77 prefers s0... wait, but r77 got s0. Contradiction: if r75 has s0, r77 can't have s0.

Hmm. Unless r75's live range ends before r77's. r75: 2 refs, live 7, block 0, crosses 1 call. Which pseudo is r75? Maybe it's u5's temp or the `t` temp in the branch arms. Actually r75 conflicts... the table says r75 s0.

Hmm wait, in w0 table r75 s0 and r77 also would be s0. The table lists hard reg for each allocno: r77 `-` (not assigned by local-alloc; it's global). r74 `-`. r75 `s0` means local-alloc assigned s0 to r75. Then global-alloc must see s0 taken during r75's live range.

Let me look at the actual dumps to understand. But maybe simpler: the target has d=s0, s1ang=s1. We need lever-free to give d=s0. Since r74 (=d) conflicts s0 (due to r75 in s0), we need either r75 to not get s0, or d's live range to not conflict.

What is r75? Let me look at the .lreg dump. Let me grep the dump file. Let me see what dumps exist.
