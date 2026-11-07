---
ts: 2026-11-06T08:41:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FDeqC1yzu4WBfP7BfBDz
---
The greg "Register dispositions" shows 72 in 7 (a3), 77 in 6 (a2), etc. — same as lreg, so local-alloc assigned all of them (all are local to the single block). Wait, the dispositions line in .greg is the final assignment after global-alloc (which respects local-alloc's assignments). Since there's a single block and no calls in this function... but the function does call func_8012C51C at the end. r72 is live across that call (used as arg), but "crosses calls" — it's live *at* the call. For global alloc, an allocno that is live across a call cannot be in caller-saved regs? No — it's live at the call but not across (it dies in the call instruction itself, as an argument). Global alloc's `allocno_live_through_calls` might still treat it as crossing? If it crosses calls, global alloc restricts it to callee-saved regs or gives it a save/restore... but here it got a3 (caller-saved). Hmm, in gcc 2.7.2, global alloc: if allocno crosses calls, it can't use call-clobbered regs unless `flag_caller_saves`. The TU presumably uses -fcaller-saves? 

Anyway: both w1 and w2 assign all pseudos via local-alloc (single block). The dispositions are the same. So the question is local-alloc's ordering.

Local-alloc sorts by qty_cmp: compare refs/live etc. The priority formula in the alloc table is `floor(log2 refs)*refs/live*1e4`, which is exactly global.c's allocno_compare? No — local-alloc uses `qty_cmp`: it compares `reg_qty` fields: refs and deaths: 
```
static int qty_cmp (qty1, qty2) { ... }
```
Actually local-alloc.c: qty_cmp compares `qty_n_refs` and `qty_death`? Let me read tools/reference/gcc-2.7.2/local-alloc.c qty_cmp.
