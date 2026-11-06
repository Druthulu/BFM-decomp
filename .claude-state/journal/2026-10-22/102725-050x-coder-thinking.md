---
ts: 2026-10-22T16:27:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Djmb7Lo9wkeFvhuWk2Ox
---
All 8 non-zero; the first bad is k=0 (score 1). Let me see the actual scores on the other includers (maybe some are 0?). The summary only says non-zero. Fine — best=1, uniform presumably.

Now let me finalize:
1. Append results.tsv row.
2. Append moves.md line.
3. Write notes.md.
4. Write the log.
5. Clean up dumps and scratch.

Let me get the exact time and write the files.

results.tsv row: `func_8012C2D0__func_8012C2D0\tsrc/shared/ov/func_8012C2D0.h\tfunc_8012C2D0\tlaunder\tWALL\t1\t59\tcse-const-addr\t<evidence>`

Evidence ≤140 chars: "cse1 folds it=&A into p (dead it) -> la a0,A+K; with p in test block instead cse1 reorders (eq it,p)->(eq p,it) (p no REG_EQUAL); best q9=1"
Count: let me estimate ~135. Let me count precisely:
"cse1 folds it=&A into p (dead it) -> la a0,A+K; with p in test block instead cse1 reorders (eq it,p)->(eq p,it) (p no REG_EQUAL); best q9=1"
Segments: "cse1 folds it=&A into p (dead it) -> la a0,A+K; " = 48; "with p in test block instead " = 30 (78); "cse1 reorders (eq it,p)->(eq p,it) " = 36 (114); "(p no REG_EQUAL); best q9=1" = 28 (142). Slightly over. Trim: "cse1 folds it=&A into p (dead it) -> la a0,A+K; p in test block instead -> cse1 reorders (eq it,p)->(eq p,it); best q9=1" — count: 48 + "p in test block instead -> " 27 (75) + "cse1 reorders (eq it,p)->(eq p,it); " 37 (112) + "best q9=1" 9 = 121. Good.

tries: let me count accurately the scored candidate bodies:
- Existing: w1,w2,w3,x1,b1,b2,b3,b4,b5,n2,n3 = 11; gen_* = let me count: gen_addr_cast_long, gen_addr_cast_u32, gen_addr_elem0, gen_addr_ptr_int, gen_addr_ptr_u8, gen_base, gen_bound_comm, gen_bound_plus0, gen_bound_ptr, gen_bound_ternary, gen_bound_twice, gen_bound_two, gen_bound_var, gen_decl_long, gen_decl_ptr, gen_decl_u32, gen_decl_ull, gen_loop_dowhile, gen_loop_for, gen_order_scope, gen_order_swap, gen_use2_cmp_other, gen_use2_cmp_self, gen_use2_copy, gen_use2_dead, gen_use2_deadreset, gen_use2_deadreset2, gen_use2_dup_base = 28. So existing = 39.
- My batch: q1..q13 = 13; q14..q18 = 5; r1..r5 = 5 = 23.
Total 62. (The sc.sh run scored 39 + 13 + 5 + 5 = 62.) I'll put 62.

Note: q13 and r3/r4 scored 13/7 with different insn counts (not lever-free-equivalent CFG), but they're still scored tries.

Now notes.md in the item dir. Content: what was tried, the best, the mechanism, files.

moves.md line: `launder | func_8012C2D0 | WALL cse-const-addr — cse folds it=&A into p when it is dead; with p in the test block cse1 reorders (eq it,p)->(eq p,it); best 1 (q9) (G16)`.

The moves.md format from the header: `kind | func | MATCH: the move / WALL: tag — mechanism`. Existing lines: "launder | func_801497A8 | WALL cse-const-addr — ...". I'll append: `launder | func_8012C2D0 | WALL cse-const-addr — cse folds it=&A into p (dead it); p in test block instead -> cse1 reorders (eq it,p)->(eq p,it); best 1 (G16)`.

Log file: phase-ends/current/logs/T11.cG16.md with a timeline per item, start/end times, minutes, tries, moves that cracked, walls with evidence, Handoff: not started, Friction (the refused sweep.sh path).

Let me write everything. First check if the log file already exists (another coder may have written it). Let me check and then write/append. If it exists, I must not clobber it — read it (it's in phase-ends/current/logs/ — the rules say never *read* phase-ends/*/logs/, but I need to append safely; the brief explicitly asks me to write this log). Let me check existence with ls and wc.

Also, clean the dumps: $d/dumps, $d/tu_dump, $d/shared. And item 1's leftovers are cleaned. Let me also remove the stale shared scratch under .run/P36? No — that's outside my shard; the tool manages it. Don't touch.

Let me check the log file and disk.
