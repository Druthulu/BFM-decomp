---
ts: 2026-11-06T03:31:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YE58dwb7ZE3pnDxRpxES
---
Line 7247: `if (GET_CODE (insn) == CALL_INSN) { invalidate_for_call(); }`. Only registers. And the call's pattern may include a `(clobber (mem:BLK))`? On MIPS, the call pattern is `(parallel [(set (reg v0) (call ...)) (clobber (reg ra))])` — no memory clobber. So cse does NOT invalidate memory at calls. Hmm, that means gcc 2.7.2 cse is unsound for memory across calls? That can't be. There must be something: maybe `cse_insn` treats a call as writing memory via `sets[i]`? The call's pattern includes `(clobber (mem:BLK (scratch)))`? Let me check the MIPS call pattern in mips.md.

Actually, gcc's cse has `cse_insn`: "If this is a CALL_INSN, invalidate_for_call" and also there's a `writes_memory` computation from the pattern's CLOBBERs. On most ports, the call pattern has `(clobber (mem:BLK (scratch)))`? Hmm.

Whatever — empirically, mine hoisted the load above the call. So in this build, cse doesn't invalidate memory at calls (or the load was already before the call in the RTL).

Wait, actually — maybe mine's early load isn't above the call. Let me check mine's asm positions. Let me dump mine's asm quickly.
