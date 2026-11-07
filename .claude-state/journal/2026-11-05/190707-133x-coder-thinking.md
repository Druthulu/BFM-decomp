---
ts: 2026-11-06T02:07:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eoC8NgYVST0Y96picqOv
---
So code 27 = INSN, 28 = JUMP_INSN, 29 = CALL_INSN, 30 = BARRIER, 31 = CODE_LABEL.

So the second hit (code 28, JUMP_INSN, delete_computation ← delete_jump ← jump_optimize) is a jump insn with UID 368 deleted in jump_optimize. That's likely OUR vA trailing jump! And it was deleted via `delete_jump`, which deletes the jump and calls delete_computation on its insns.

delete_jump at line 664: `if (reallabelprev == insn && condjump_p (insn))`. Our jump is simple, not cond. Unless after `redirect_jump(insn, NULL_RTX)`... no, condjump_p still false.

Other delete_jump calls: 1130, 1299. Let me read their contexts (condjump x=a;else x=b optimizations). Our jump is not cond.

Hmm, but maybe the jump in question is a different function's uid-368 jump. Let me disambiguate by printing the function name at that hit. current_function_decl → DECL_NAME → IDENTIFIER_POINTER. Offsets unknown. Alternative: print the insn's address and compare with... no.

Alternative: add a unique marker. Let me compile a *single-function* TU: extract just our function plus stubs? Hard due to externs. Alternatively, make the TU contain only our function by commenting out other functions? The TU is huge.

Alternative: print `current_function_decl` address and correlate with the .jump dump order? Hmm.

Better: print the jump's label_ref target UID and its PREV insn code. Our vA jump's label is 374 (epilogue), prev insn is the store (INSN). At the delete_jump hit, delete_computation was called first on the jump's insns (the delay? no). 

Let me print for each JUMP_INSN delete hit: uid, and the label target's uid via the PATTERN. PATTERN at offset 8 (fld[3]? Let me check: INSN_UID=fld[0], PREV=fld[1], NEXT=fld[2], PATTERN? In rtx.h: `#define PATTERN(INSN) ((INSN)->fld[3].rtx)`? Let me check.
