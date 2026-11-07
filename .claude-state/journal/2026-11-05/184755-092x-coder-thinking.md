---
ts: 2026-11-06T01:47:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_APEX8D6FLA38Bco3nvEl
---
No RETURN insns anywhere. So the redirect at 656 didn't fire. Why? Because next_active_insn(374) != 0? The label 374 is not the last in the chain — maybe after the function's insns there's a `(note NOTE_INSN_FUNCTION_END)` and then... the dump shows the note 372 before label 374. After 374: nothing. Hmm.

Wait, maybe the redirect code is guarded by `#ifdef HAVE_return`? Let me look at the exact lines 654-662 again — no ifdef visible. Hmm.

OR maybe the label 374 has `next_active_insn` = the label's NEXT = note 374? In orig's .jump2 the tail was:
```
(code_label 373 370 374 181 "")
(note 374 373 377 "" NOTE_INSN_DELETED)
(note 377 374 0 "")
```
So after label 373 there are notes. In vA's .jump the tail: label 374 (last). Hmm.

Let me look at vA's .jump raw tail again including after label 374 — maybe the section continues with more insns of the same function (e.g., the epilogue RTL?). The dump showed label 374 then ";; Function func_801850B4". So 374 is last.

So next_active_insn(374)=0 → redirect fires → but no RETURN in dump. Contradiction unless... the jump was deleted instead, which is what we observe! Maybe redirect_jump turned it into RETURN, and then the RETURN insn was DELETED by the code at 2005-2031 (cross-jump of RETURN insns, minimum 2)? cross_jump=0, so no.

Hmm, but wait: maybe `delete_jump(insn)` at 664 fired: reallabelprev = prev_active_insn(374) = 368 (the jump itself, skipping barrier+notes). So reallabelprev == insn. `condjump_p(insn)`: condjump_p checks if the jump is conditional. After redirect to RETURN, is condjump_p true? No.

Order: line 653 reallabelprev computed BEFORE the redirect. reallabelprev = prev_active_insn(374) = 368 (the jump). Then line 656 redirect (turns jump into RETURN). Then line 664: `if (reallabelprev == insn && condjump_p (insn))` — condjump_p on a RETURN pattern? condjump_p returns 0 unless IF_THEN_ELSE. So no.

I'm clearly missing something. Let me look at the *actual* code in our pinned cc1's source — maybe tools/reference/gcc-2.7.2 is not the exact source. But close enough.

You know what? Let me stop reverse-engineering and just experiment with the C. The key finding: v1 (store before sh in source) gives 138 ins and only a 2-instruction order residual at the very end. So if I can get sched1 (or any pass) to swap those two stores, I win.

What makes sched1 swap two independent stores? Let me look at v1's sched dump to see why the order is preserved. Actually maybe the stores DO have a dependency: both are MEM in struct with varying? The sh to 244 and sw to 28: same base s0, different constant offsets. sched1's true_dependence for MEM_IN_STRUCT_P both: gcc 2.7.2's `true_dependence`:

```
int true_dependence (mem, mem_mode, x, varies)
{
  ...
  if (GET_CODE (x) == MEM) {
    ...
    /* If the modes are the same, then the insns are dependent unless the addresses are provably different. */
    if (mem_mode == GET_MODE(x) && ! addr_different_p(...))
```
Hmm, `addr_different_p` might compare constant offsets. If the two stores have different constant offsets from the same base, they may be proven independent. Then sched1 could reorder.

But it didn't. Maybe because in the *source* order sw then sh, the scheduler processes them and keeps order (LUID tie-break). To force a swap, we could add a dependency: make the sh's value depend on the sw's value? E.g., `sh = (0x1D - unk1C)`? No, that changes the value.

Alternatively, use a different mechanism to get sh before sw while the store is not the last insn at jump2. Hmm.

Wait, actually — think about the *original* source. What if the original wrote:
```
((Unk*)a0)->unk1C = 0x1D;
CAST_WIDTH(s16, a0, 0xF4) = 0;
```
and the compiler emitted sw;sh but then sched2 (post-reload) or reorg swapped them to sh;sw? v1's residual is at the very end and mine has sw;sh. Let me check which pass: dump v1's sched/sched2/dbr. Maybe sched2 swaps if the ordering differs.

Actually, hold on: maybe I should check the *orig* (barrier) build's RTL: with the barrier, the source order is sh;sw (target). The barrier sits after sw. So in orig, the store order is sh;sw because the source is sh;sw.

Let me think about the delay-slot angle: in target, `sh zero,244` at 1804 and `sw v0,28` at 1808. Hmm.

New idea: keep source order sh;sw (target), but prevent the cross-jump by making the sh store *not* directly precede... no, the sw is last.

What if the sh and sw are emitted as a single... no.

OK here's another thought: what if we add a third store AFTER the sw that is dead and eliminated by dead-store elimination *before* jump2 but after the first jump pass? Hmm, dead store elimination in flow/cse.

Or: what if we make the zero block's store to unk1C use a *different* mode/insn at jump2 that reload changes? E.g., write it as `s16` store then... no, target sw.

Let me look at the problem from the "what did the original C look like" angle: The function's zero block:
```
func_8012B200(a0);
CAST_WIDTH(s16, a0, 0xF4) = 0;
unk1C = 0x1D;
```
and dec block:
```
unk1C--;
```
The original C probably had:
```
unk1C = 0x1D;
```
at the end of a `case 0:` in a switch, or at the end of an if-block with no return. And dec as `unk1C--;`. The compiler did NOT merge them in the original build. But our reconstruction (without barrier) DOES merge. That's strange: if the original C is essentially the same, the original build would merge too!

Unless the original function is compiled in a context where... hmm, wait. Maybe the target binary was NOT compiled with gcc 2.7.2 -O2? It was. Hmm.

OR: maybe the merge in our build is caused by something else in our reconstruction that differs from the original: e.g., the `pad[8]` local, or the goto labels. The barrier was added by the reconstructor because the merge appeared. Maybe with a *different* (more faithful) body shape, the merge wouldn't happen at all.

Key: find_cross_jump at jump2 merges because zero's block falls through to the label and its last insn (sw) matches dec's last insn before its jump (sw). For the original not to merge, either zero's block didn't fall through (had a jump), or the insns differed.

Given the target's final layout has zero falling through, the original likely had zero's block ending with a jump that was deleted at jump2 (the pass where cross-jump runs!). Order within jump2: the pass iterates insns forward. dec's jump (earlier) is processed BEFORE zero's jump (later). So at dec's jump, zero's jump still exists → jump_chain retry with minimum 2 → 1-insn tail doesn't merge → no merge! Then later in the same pass, zero's jump-to-next is deleted (by whatever mechanism). PERFECT — this explains the target!

But in vA, the jump was deleted in the FIRST jump pass (jump at 2827), not at jump2. Why? The jump-to-next deletion must have happened there. In the FIRST pass, cross_jump=0 but the deletion code runs. So how do we keep the jump until jump2? We need the jump to NOT be a "jump to next" at the first pass, but to become one by jump2. What changes between passes? The layout: reorg hasn't run. Hmm.

Alternatively, the jump could be to a *different* label that later gets redirected. E.g., a `goto` to a user label at the end of the function, which the compiler threads to the epilogue label. Hmm.

Wait — maybe the deletion in the first pass wasn't jump-to-next but the dead-pseudo-set deletion (line 540) deleting something and cascading? No.

Let me actually find where the jump is deleted. Use gdb? Alternatively use cc1's -dj on a minimal test case to see. Let me write a tiny C file with a void function ending in `return;` and compile with the pinned cc1 -dj and see if the jump survives the first pass. That isolates it.

Actually, the TU context matters (the label's next). In a standalone function, the label is last → redirect to RETURN should fire. Let's test to understand.

But time. Let me try a different C shape to keep a jump at the end of zero: what if zero's block ends with `goto end;` where `end:` is a label at the very end of the function *before* the closing brace, and then... that's the same as return; (both jump to a label at the end). The compiler's return_label is placed after the user label, so the goto would be to a user label that immediately precedes the return label → at the first pass, the jump's target is the user label; next_active_insn(user label) = ... the return label? Labels are skipped by next_active_insn? next_active_insn skips only notes; CODE_LABEL is not active? Looking at the code: it stops at CALL/JUMP/INSN; it continues past CODE_LABEL and NOTE. So next_active_insn(user label) = whatever comes after both labels = 0 → redirect to RETURN. Hmm.

OK, let me try the actual experiment: does a trailing `return;` survive the first pass? vA says no. Let me find where by testing with -dj and inspecting. But I already know it's gone after the first pass.

What if the trailing jump is NOT to the function end but to a label that is not next? E.g., restructure: put a `goto done;` at the end of zero, and `done:` label placed BEFORE some code that comes after (like the epilogue is compiler-generated). Hmm, there's nothing after.

What if we reorder the source so the zero block is not last, and the block that IS last has a jump to the epilogue? E.g., write the zero block, then a `dec:` block after it. But the target's physical layout has dec before zero. Layout follows source order of blocks... unless the blocks are reached via gotos and the layout is determined by branch structure? GCC lays out blocks in the order they appear in the RTL, which follows the source/statement order. So the source must have zero last.

Hmm, but wait: what if the zero block is last in source but we add a *dead* block after it that gets removed? Like `if (0) { ... }`? Or an unreachable statement after the return: `return; x = 1;` — the unreachable code might be dropped by the front end.

Alternatively: `goto zero;` where `zero:` is at the end, and after the zero statements we put `goto end; ... end:` hmm.

Let me look at the ORIGINAL target's block layout again: the `dec` block at 17bc falls into... dec ends with `j 180c; sw`. The zero block at 17d0 ends at 1808 (sw) falling into 180c.

Another thought: maybe the original source had zero's block ending with `return;` and the jump was NOT deleted because the function's return label is *not* immediately after — because the compiler places the return label BEFORE the epilogue instructions which are generated in expand_function_end as RTL for this port? Let me check: does gcc 2.7.2 MIPS generate the epilogue in RTL (gen_epilogue)? In `expand_function_end`, for ports without `FUNCTION_EPILOGUE`... Let me check config/mips/mips.c or the .md for `epilogue`. In final.c, `function_epilogue` emits epilogue instructions only if `! HAVE_prologue`? Actually final.c calls `FUNCTION_EPILOGUE (file, size)` if defined; otherwise the epilogue is RTL emitted by expand_function_end via `gen_epilogue`. On MIPS (ELF/PSX), HAVE_epilogue is defined and the epilogue is emitted in final? Hmm, but then the return label would be last in RTL.

Let me test what our actual cc1 does with a simple function. Write a small C file with the same signature and a `return;` at the end, compile with -dj, and inspect. This will reveal whether the trailing jump survives.

Actually, better idea: check the *orig* TU's .rtl dump for a function whose last block ends with `return;`. In the orig .rtl dump (whole TU), look at any function's end: do any end with a jump to the return label? Let me grep the orig .rtl for the last insn of some function... Complex.

Let me just do the small experiment.
