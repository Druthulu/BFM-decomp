---
ts: 2026-11-06T06:07:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nEFSjuq59sspbzdt4ran
---
Score 74, same insn count. This is the s2/$18 pin removal effect: `s2` (the u16* loop pointer) now allocates differently. Target has s1 where mine has s0 in the tail. Also the launder removal changed things.

Let me look at the diff more carefully. Let me use dt.sh with a larger tail. Actually let me get a full diff — use --keep? The dt.sh prints score + diff tail. Let me check delever_search's --explain to see residual.

Let me run dt.sh with tail 40.
