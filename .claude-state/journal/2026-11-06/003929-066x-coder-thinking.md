---
ts: 2026-11-06T07:39:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vJ0kJMtpdVRuVgzUmK61
---
Score 0! We cracked item1. The lever-free body calls func_800CAF84(arg0) through a cast (needed because of the leaked `(void)` prototype), keeping a0 live across the copies.

Wait — but does the cast count as a "new lever"? It's a real C spelling, not a register lever. It's not a launder/identity. It's a function-pointer cast to pass the argument. Hmm, is it "real C"? The original source likely had the call with arg0 and a proper declaration; the leak forces the cast. The cast itself has no codegen footprint. But is it a "lever of a new kind"? The allowed moves are "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)". A function-pointer cast is a real C spelling, arguably "decl scope" related. It doesn't steer registers artificially; it passes a real argument that the callee uses. Actually, the callee func_800CAF84 at line 88 DOES use its arg0 (unk28 etc.). So passing arg0 is semantically correct! The lever-free body is more correct than the original (which called with no args).

But careful: does the kind "keepalive" still exist in win.c? We removed the asm keepalive and the pin. The cast is not an asm/register lever. So MATCH.

However, is the cast "an identity-statement launder"? No. Is it a "new lever of any kind"? It's a type cast to express a call through a mismatched prototype; the compiler's leak forces it. I think it's legitimate real C. But let me consider whether there's an even cleaner spelling: use a local declaration with the correct prototype that does NOT conflict. The conflict came from the K&R definition type vs `(void*)`. Let me test declaring `extern void func_800CAF84(s32);` inside the body (prototype with s32). Would that conflict with the K&R definition? The K&R def has `void *arg0`, so `s32` conflicts. What about `extern void func_800CAF84(void *);` → conflicted earlier (v31). Hmm, "conflicting types" at line 88. Why would `(void*)` conflict with the K&R def `void *arg0`? It shouldn't. Unless the leaked `(void)` type from func_800CB400 (line 238) is what conflicts! v31's local decl at line 253 is AFTER func_800CB400, so the global type is already `(void)` from the leak, and a new `(void*)` decl conflicts with it (and the error points at line 88 as previous declaration). So no prototype works.

Alternative cleaner spelling: assign the function to a local pointer variable at file... no.

The cast is the minimal way. Alternatively, call with no args but keep a0 live via a real use of arg0 somewhere else. The cast is better because it's semantically the real call.

Actually, wait: is the cast even needed to keep a0 live, or would a plain `func_800CAF84(arg0)` work if we avoided the leak by... no, it doesn't compile.

Could we write `func_800CAF84(arg0);` and add a local `extern void func_800CAF84();`? We tested v33 — failed due to the leak.

So the cast is the route. But does the cast introduce a "new lever"? Let me think about how the expert will judge: MATCH = the kinds (keepalive) gone. The cast is a declaration-scope workaround forced by a pre-existing TU quirk (func_800CB400's block-scope `(void)`). It is real C: passing the actual argument the callee expects. I'll note it in notes.md and the log.

Hmm, but hold on: is passing arg0 semantically identical to the target? The target calls func_800CAF84 with a0 = arg0 (since a0 is live and the jal has no move). So yes, the target passes arg0! The banked source (with no-arg call) was WRONG semantically but byte-identical because a0 happened to hold arg0 due to the lever. Our body is the true original C. Great.

Now let me confirm the win.c: copy v40_cast.c to win.c, verify score 0 with dt.sh, and also verify the kinds are gone (no asm/register). Also check that the body still has no `register` vars.

Let me also double check: does the function-pointer cast produce any extra insn? Score 0 says byte-identical.

Let me create win.c and notes.md, results row, moves.md line.

But first, the FRESH check: "at each item's start diff <dir>/orig.c against the def in the current src". I extracted orig.c from the current src at the start, so fine. But src may change as other batches bank. I'll note the extraction time.

Also, the constraint says "no signature or decl change outside the body (callers stay as they are)". We changed the call inside the body only. Good.

Now item 1 done. Time: started 00:20, now maybe 00:50. ~30 min. The budget is 20-30 min per item; item1 took ~30. Let me proceed efficiently.

Let me write win.c, notes, and results row. Also append to moves.md.

results.tsv row format: `dir file func kinds result best tries wall evidence` tabs.
dir = func_800CB458__md_MAIN_016
file = src/md_MAIN_016/md_MAIN_016.c
func = func_800CB458
kinds = keepalive
result = MATCH
best = 0
tries = number of scored tries on this item. Let me count: w1, w2, base(control? maybe not a "try"), va..vg (7), v10..v26 (17, some compile errors), v30, v31, v32, v33, v40. That's ~30. Let me count exactly later; I'll say 31.
wall = - for MATCH
evidence = "cse1/global-alloc: passing arg0 to func_800CAF84 (cast call) keeps $4 live across the struct copies; copies take a1-a3 as target" ≤140 chars.

Let me make sure the evidence mechanism: the target's a1-a3 allocation comes from a0 being live; passing arg0 does it. The pass: global/local-alloc. I'll say "local-alloc/global: $4 live across the copies (arg0 passed to func_800CAF84) -> temps take a1-a3".

Now write files. First win.c from v40_cast.c. Use cp? The instruction: scratch files under shard. cp is a command. Let me use `cp` — allowed? It's a shell command. Should be fine. Actually writing via Write is safer. Let me Write win.c with the content. I have the content from mk40 output (printed). Let me just cp.
