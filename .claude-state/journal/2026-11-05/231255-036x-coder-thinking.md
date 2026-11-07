---
ts: 2026-11-06T06:12:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TDyssSAnMoK1nlHzIJFU
---
So a hard reg is live if it's in basic_block_live_at_start or set/clobbered. For $16, nothing in this function sets it. Unless a call clobbers... In MIPS, calls clobber caller-saved only.

Hmm, so why does r72 conflict with 16? Let me check `record_conflicts`... 

OH WAIT. I misread. Look again at the line:
```
;; 72 conflicts: 72 73 74 75 76 77 78 80 134 140 167 2 3 4 5 16 29
```
Hmm, but where's 82..? The list includes allocnos and hard regs. Note 16 could be... hmm, all these conflict lines include "2 3 4 5 29" — those are v0,v1,a0,a1,sp. And 72's includes 16 additionally. r72 is the param which crosses calls. Its conflict set with hard regs: 2,3 (call-clobbered), 4,5 (the incoming param regs a0,a1!), 29 (sp), 16.

Hmm, "4 5" = a0,a1 — why? Because at function entry, the params are in $4,$5 and r72 is born at the prologue copy: it conflicts with the hard regs it's copied from. And $16... 

AH. I bet the answer: the function is called from somewhere? No.

Wait, maybe there's another hard-reg variable in this function used in a *different* block: e.g., `register ... __asm__("$16")` inside the TU elsewhere in the same function? We grepped the body: no asm.

Hmm, but maybe the conflict with 16 comes from local-alloc: a local pseudo got $16 and is in the same block as r72's live range? In .lreg, no s0 appears. But `reg_renumber` at global_conflicts time — hmm, the .lreg dump is after local-alloc, so local pseudos already have hard regs; we found no s0.

Let me try another approach: search the .greg dump for "16" within the conflict lines... Only r72 has 16. Interesting. So r72 specifically conflicts with $16.

Hypothesis: the loop pointer or something has a hard reg? No.

Alternative hypothesis: `global_conflicts` marks hard regs live at the *start* of the function from `basic_block_live_at_start[0]`, which includes the *callee-saved registers that the function's own prologue will save*? No.

Hmm, what about `regs_set_between_calls`... 

Let me actually look for hard reg 16 in the .cse2 dump (pre-local-alloc). Or in the .rtl dump.

Hmm, actually — maybe it's from the FIRST function in the TU. The dump section boundaries: the .greg dump prints ";; Function func_801804A0" then the order/conflicts. My reading at line 1947+ is definitely that section.

Wait... unless alloc_table grabbed the wrong section. It printed `79 pseudo(s) in the .lreg table`. The order line 78 77 134... belongs to func_801804A0.

Let me test the hypothesis directly: make the param's conflict with $16 go away? Can't directly.

Alternative: maybe $16 is live at the start of some block because of `D_801202A0`... no.

Let me grep the .lreg section (2316 to next Function) properly and look at what hard regs appear.
