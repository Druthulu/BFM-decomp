---
ts: 2026-11-07T00:32:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_430CskfPLcAeluiAEg41
---
So the store `(mem:QI (plus (reg) (16)))` → note_mem_written → addr is PLUS, not BLK, not SCRATCH, cse_rtx_addr_varies_p(written): the address `(plus (reg virtual-stack) (const))` — varies → true (unless the reg is a known constant). Then `if (! ((MEM_IN_STRUCT_P(written) || GET_CODE(addr)==PLUS) && mode != QImode)) writes_ptr->all = 1;`

MEM_IN_STRUCT_P || PLUS → TRUE; mode != QImode → QImode so FALSE; TRUE && FALSE = FALSE; !FALSE = TRUE → all=1. So it should invalidate everything!

Then invalidate_from_clobbers → invalidate_memory(w) with all=1 → removes ALL in_memory entries, including our symbol load. So cse1 should have re-loaded. But the output shows a2 reused.

Unless... the sb was placed AFTER the second load in the RTL and sched1 moved it before. Yes! sched1 (after combine) can reorder the sb above the lhu. In the source I placed the dead store before the second use, so in RTL order it's before; but wait the listing shows sb at 33 then lhu at 34 — consistent with source order.

Hmm, but the cse behavior says otherwise. Unless the store was eliminated before cse1 by jump_optimize? No.

Hold on — maybe the two uses are in different cse blocks already? No.

Wait, maybe cse didn't merge the loads because the pointer load *was* re-issued... but mine shows a2 reused at insn 34 (lhu v0,18(a2)). Hmm, so the second use IS via a2 = the same cached pointer.

Unless a2 was re-loaded! Look at the diff: mine[18:21] delete lui a2; lw a2; lhu v1,42(s0). Hmm, that suggests at 18-19 mine has lui a2; lw a2. Where's the second load? Maybe mine has lui a2; lw a2 TWICE and the diff alignment hides one. Let me get the full mine listing. Score 10 with 68 ins both.

Let me dump my candidate's object. dt.sh doesn't support --keep. I'll run delever_search directly with --keep to get the object path. That writes scratch under .run/P36/engine (the tool's own dir) — allowed (read-only shared helper writes its own). Let me do it.

Actually, a cheaper approach: use --explain with a path? Or just look at the full diff with a larger tail — the diff only shows hunks. Let me run --keep.
