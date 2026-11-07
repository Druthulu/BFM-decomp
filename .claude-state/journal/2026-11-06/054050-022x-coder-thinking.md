---
ts: 2026-11-06T12:40:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WJagH5JDUpUX6FW1leSU
---
Hmm, parts[2] is the mnemonic only because operands are in parts[3]. Whatever — the point is insn 376 = `sw`, not `lui a2,0xff00`. So delever_search's index is not from the object's function start... maybe it strips the delay slots / uses a different base. Hmm.

Wait — maybe delever_search's "mine" index counts from the function's first instruction but the object I kept (p3/cand.o) is not the same candidate? I ran --keep with b4. Yes it is.

Hmm, maybe delever_search compares only a window or uses instruction list of the function extracted by symbol size, and indices might be 1-based including... Let me check how delever_search computes indices. Actually, easier: find where `lui a2,0xff00` is in this object and see its index.

Let me search for "lui\ta2,0xff00".
