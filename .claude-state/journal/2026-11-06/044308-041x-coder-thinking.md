---
ts: 2026-11-06T11:43:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LqI6xnRqVkzZjtDiv92w
---
The dead store `sh v1,16(sp)` survived (flow didn't delete it), and the frame grew. Also only 1 load presumably.

So the dead store survives. flow doesn't delete dead stack stores. So that route adds an insn.

Hmm. What about a store that cse deletes? A store of a value already in memory at the same address. Let's test `*(u16*)(p + 0xAE) = (u16)bb;` (self-store to the same address). If cse deletes it, we get the invalidation without the insn. But we need in-struct on the first load for the nonscalar invalidation... Actually wait: the self-store to the exact same address — cse's final loop invalidates only if the address doesn't vary. The address varies (p is a pseudo). Hmm.

But cse might have a "store into the same location of the same value" elimination that also removes the memory entry? Let's just test empirically.

Actually, here's a cleaner idea: the invalidation we want is of the *exact address*. `invalidate(dest)` is called when `!cse_rtx_addr_varies_p(dest)`. `cse_rtx_addr_varies_p` — let me check: it returns true if the address contains a register that isn't a constant/known. Let me look.
