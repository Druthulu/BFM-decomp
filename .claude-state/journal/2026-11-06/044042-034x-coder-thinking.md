---
ts: 2026-11-06T11:40:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LJgTh48HFFqrOugOYkbh
---
Key: "Memory is invalidated by non-constant calls." — a CALL_INSN that is not CONST_CALL_P invalidates ALL memory. So the ratan2 call at the end invalidates. But the second load is before the call.

Wait — in the target, the second load is at 32f0 which is BEFORE the jal at 3304. Hmm, but what if we reorder the C so that the second read happens after a call? No.

Hmm, but here's a thought: the ratan2 call at 3304 — is it a CONST_CALL_P? No. So any load after a call is not forwarded. 

What if we write the C so the second read happens after a call... The `sVar4 = ratan2(...)` call's args include the reads. Can't reorder.

BUT: what about the first read `bb = *(u16*)(p+0xAE)`? If we put a call between the first read and the second read... no.

Alternatively: what if the first read is *after* a call? No.

OK here's another angle: maybe use a store to memory that cse invalidates. `writes_memory` for a store to a stack slot: the stack pointer is constant (sp/fp), so `cse_rtx_addr_varies_p(dest)` false, and it does `invalidate(dest)` — only the exact address. It doesn't invalidate p+0xAE. Unless the address "varies".

What makes a store invalidate everything? `note_mem_written`: let me look at it. A store through an unknown pointer (varies) → `writes->nonscalar` or `all`.

Let me read note_mem_written.
