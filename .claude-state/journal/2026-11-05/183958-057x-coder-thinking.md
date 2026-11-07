---
ts: 2026-11-06T01:39:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QRi0U6a4zHUanxYptCi0
---
In vA, the `return;` jump was deleted by the first jump pass (as expected, jump-to-next). The .jump2 shows label 386 created before the store — merge happened again. So vA fails.

Hmm, where is the jump-to-next deletion for unconditional jumps? It seems it happened. Let me find it: maybe in `delete_jump` called from the condjump path only... but the jump disappeared in .jump. Let me search for "next_active_insn (insn)" or "JUMP_LABEL (insn) == next" patterns. Search "reallabelprev".
