---
ts: 2026-11-06T16:34:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PTgbzaeVobyeTFykyBkx
---
c38: 4 insns (the two calls swapped) + li. Best = 5.

Time now 09:34, started 09:26:57 → only 7 min. Need ≥20 min for a WALL. The brief says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item". I have 48 tries but only 7 min. Hmm. "Budget 20-30 min wall per item... past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries". So I need to spend at least 20 min on this item. I could continue trying to crack it for another 13 minutes. Let me use the time on more substantive attempts.

Let me think about the keepalive more: if we crack the keepalive (get li v0,1 in v0 naturally), and the barrier's merge prevention at best costs 4 (reorder), the best would be ~4. Still a wall.

But maybe there IS a way to prevent the merge byte-neutrally. Let me think about `rtx_renumbered_equal_p` more carefully: it compares the *patterns* after reload. What if one block's calls use different *REG_DEAD/REG_UNUSED* notes? Notes don't matter.

What about the call insns' `CALL_INSN_FUNCTION_USAGE`? If one call has a different function-usage list (e.g., because the callee's prototype differs in one spelling), the CALL_INSNs wouldn't be equal! E.g., call `func_800468FC()` in block1 but `((void(*)())func_800468FC)()` in block2 — same RTL? The function usage might include the same. Hmm.

What about calling through a K&R prototype with an extra argument in one block: `func_800468FC(0)` — if func_800468FC is declared `void func_800468FC(void)`, passing an arg is a compile error in strict C but gcc 2.7.2 K&R may allow it (too many args to a (void) prototype = error). If allowed, it emits an extra move → bytes differ.

What if the function is declared K&R `extern void func_800468FC();` — then `func_800468FC(0)` passes a0=0 → extra `move a0,zero` bytes. No.

What about CALL_INSN_FUNCTION_USAGE differences from a *cast* of the function pointer? e.g., `((void (*)()) func_800D2D44)(0)` vs `func_800D2D44(0)`. The first is a direct call through a cast — same RTL? The CALL_INSN_FUNCTION_USAGE is built from the arg list; the function expression is a SYMBOL_REF either way. Probably equal.

Hmm, here's a promising one: `((void (*)()) func_800D2454)` is already used in the first if (a cast). What if we cast one of the *void* calls in block1, e.g. `((void (*)()) func_800D2D44)(0);`? The call insn's function usage may include the SYMBOL_REF identically. But the *pattern* of the call might differ: `call (mem:SI (symbol_ref))` vs `call (symbol_ref)`. In gcc 2.7.2 mips, a direct call to a function name produces `(call (mem:SI (symbol_ref)) (const_int 0))`. Casting the function pointer might produce the same.

Let me just try a batch of "call spelling" variants in block1 only (block2 unchanged) and see if any prevents the merge at 0 cost:
- d1: `((void (*)()) func_800D2D44)(0);`
- d2: `((void (*)()) func_800468FC)();`
- d3: `((void (*)()) func_8002D8D4)();`
- d4: `((void (*)()) func_800D2AA0)(0);`
- d5: `(*(void (**)()) &func_800D2D44)(0);` — indirect? may emit jalr. risky.
- d6: `func_800D2AA0((u8 *)0);` already tried (c20, 20 → merge still). 
- d7: `func_800D2D44(0x0);` same.
- d8: `func_800D2D44(+0);` same.
- d9: `func_800D2D44(0L);` same.
- d10: `func_800D2D44((s32)0);` same.
- d11: `func_800D2D44(NULL);` — NULL may be ((void*)0) → cast, same const0.

Also try the if-condition using a *different type*: `if ((s32)func_800D2454(...))` etc.

Also try splitting a call's args across a temp: no args.

Let me also try: in block1, call `func_800D2D44(0);` then `func_800468FC();` — same as target. The only byte-neutral way to differ is a call-insn metadata difference.

Another idea: `volatile` on a call? no.

Another: `func_800D2D44(0);` vs `func_800D2D44(0);` with different *source line* → line notes are notes, skipped.

Let me test the cast variants. Also test making block1 a `switch` with a single case that falls through — emits a jump? `switch (p[1]) { default: calls }` — the switch on p[1] would add a test. no.

Another idea: use `if (A) { calls; goto ret; }` but write the block as `if (A) { calls; } if (A) goto ret;` — changes control flow (double test).

OK let me test the cast batch.
