---
ts: 2026-11-06T15:07:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zxLuML0TIr5GVdhVy9Ql
---
The scratch TU is there (p3 from the d4 run). Let me run cc1_dumps_tu.sh on it with DUMP_ROOT under my item dir. Then grep the dumps for "a0" and "sll" across passes to find where the fold occurs.

Actually simpler: use hdump.sh? No, that's for headers. cc1_dumps_tu.sh accepts a .c file.

Let me run it. DUMP_ROOT must be under my shard dir. Note cc1_dumps_tu.sh does `d=${DUMP_ROOT:-...}/dumps_$tag; rm -rf "$d"; mkdir -p "$d"`. Fine.

But that scratch TU (p3) is from the d4 run? The last --keep run was d4 → p3. Good, that's the one with move a0,zero and the do-while.

Hmm, actually I want to study the *plain* no-launder candidate. Let me regenerate a --keep run for nolaunder.c, then dump.

Actually let me first think about which pass. The target has sll even though s0=0. Since the launder (asm) prevents folding, the fold is a pass that sees the asm as an opaque set. Both cse and combine do. The asm sets s0 to an unknown value, so:
- cse: qty_const for s0 invalidated by the asm set.
- combine: get_last_value finds the asm set (not a constant) → no fold.

So removing the asm, the *last set* before the shift is `s0 = 0` → fold. 

Now, the label trick: combine's condition needs reg_last_set_label == label_tick. cse's qty_const is per extended basic block — cse invalidates at labels? Let me check cse.c's handling: "A label invalidates ... " cse's cse_basic_block splits at CODE_LABEL. So a label between would block cse too.

So: need a surviving label between `s0 = 0` and `a0 = s0 << 10`, without adding instructions.

What survives? An empty `if` won't. A `do{}while(0)` — does gcc keep the label? In d4 it didn't block the fold, so probably deleted.

But C0535 says do{}while(0) splits cse1's EBB — maybe the difference: they wrapped two copies; gcc keeps a label when the loop body is non-trivial? Hmm, in d4 the loop body was `s0 = 0` — trivial, removed.

What about `do { s2 = (s32)D_8019B538; } while (0);` — no.

Let's think about what actually survives to RTL as a label: `do { ... } while (0)` is compiled by gcc's stmt.c as a loop with a condition; -O2's jump optimization (jump.c) deletes the jump and label if the condition is constant true (0 is constant). gcc 2.7.2 does have jump.c's delete_unreachable/thread. Since the condition is the constant 0, the loop is `do body while(0)` → one iteration; jump.c may simplify. C0535's worked case might have had a `while(0)` that wasn't folded because... hmm, `while (0)` is a constant false.

Hmm wait — maybe in 2.7.2 the front end emits the do-while(0) with a label and jump.c's `jump_optimize` deletes it, but cse runs BEFORE jump? Pass order: cse1 runs after jump? Let me recall gcc 2.7.2 toplev pass order: ... jump_optimize (jump1), cse, ... Actually: expand, jump1 (jump_optimize), cse, ... So jump1 runs before cse1 and would delete the constant-false branch/label before cse. Then cse sees no label. But C0535 claims the split works at cse1 — maybe because the do-while(0) label survives jump1 when... Hmm.

Whatever. Empirically d4's fold survived. Let me instead check what pass does the fold — dump and see. This informs which boundary is needed.

Let me do the dump for the no-launder candidate.
