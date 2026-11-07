---
ts: 2026-11-06T01:50:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AXQ6ko7U2LQSSFzp16su
---
stmt.c:2532 in expand_value_return: `if (GET_CODE (return_reg) == REG && REGNO < FIRST_PSEUDO_REGISTER) emit_insn(gen_rtx(USE, VOIDmode, return_reg));` — only for functions returning a value. Our function is void.

function.c:5397: in expand_function_end, `emit_insn (gen_rtx (USE, VOIDmode, real_decl_result))` if the function returns a value.

Hmm, what if the function were declared to return something? The signature must stay (constraint: no signature change). It's `void func_80184E8C(s32 a0)`.

What about a variable-length/alloca? stmt.c:750 emits USE of fp/sp/chain for... let me look at that context. Probably for `__builtin_alloca` or varargs. Not usable.

OK, another idea: get a real insn that emits zero bytes AND is not a lever: a `(note)`? no.

Hmm, what about the target's own structure: maybe the original zero block ended with a CALL whose delay slot is the store? No.

Let me step back and reconsider the possibility that the merge is prevented by the *dec* side: if dec's store is not the insn immediately before its jump at jump2. What if in the original source, dec is written as:
```
if (t >= 0x1E) {
    unk1C--;
    return;
}
```
The `return;` after `unk1C--`. RTL: store; jump. Same.

What if dec's store and jump are separated by an insn that dbr moves into the delay slot instead of the store? Target's delay slot has the store. So the store is immediately before the jump.

What if the original dec block ended with a jump that is NOT simplejump_p at jump2 — e.g., a `return` (jr ra)? Target shows `j 180c`.

Hmm, what if the merge happened at jump2 in the original too, but the *target* bytes correspond to a build where... no.

Let me look at the actual merged vs unmerged instruction counts: nopin 136, target 138. The difference: the merged version has dec's `j 1800` + delay addiu + shared store, while target has dec's `lw; nop; addiu; j 180c; sw`. So the target dec has 5 insns vs merged 4 (lw; j; addiu; + shared store counted in zero). Total -2.

OK here's another thought: maybe the original C for dec was:
```
((Unk*)a0)->unk1C--;
return;
```
and the zero block's store... and the cross-jump didn't merge because the two stores were NOT identical: maybe the target's dec store uses `$v0` but zero's uses `$v0` — yes identical.

Hmm, unless the two stores differ in the *relocation* or a REG_EQUIV note... find_cross_jump ignores notes.

Wait wait wait. Let me re-read find_cross_jump's comparison: `rtx_renumbered_equal_p (p1, p2)`. For MEM: it recurses into operands; the MEM's `MEM_IN_STRUCT_P` flag is not compared; the address (plus (reg s0) (const 28)) compared; the reg compared via reg_renumber (hard). So identical.

Unless the two stores' PATTERNs differ in the *mode* of the MEM: `mem/s:SI` vs `mem:SI`? The 's' is MEM_IN_STRUCT_P, not part of the RTX code comparison. The mode: both SI.

Hmm, what about the REG_EQUIV notes? Not compared.

OK, radical idea: maybe the original zero block's store was `sw v0,28(s0)` and dec's was also, but at jump2 the two insns had different *insn codes* or the dec store was inside a SEQUENCE? No.

Let me try yet another angle: use the `-dJ` dump of the TARGET? We don't have the target's RTL, only bytes.

Time check: it's probably ~19:15 now, item 1 has taken ~45 min. I should record a WALL if needed but let me try a few more promising C shapes.

Idea: Make zero's block end with a *conditional* jump that survives to jump2 and is deleted at jump2 by the condjump-to-next deletion. Wait — the condjump deletion at line 664 happens in the SAME pass, and the pass iterates forward: dec's jump is processed BEFORE zero's condjump (which is later in the stream). So at dec's processing time, zero's condjump still exists. Then the cross-jump comparison: dec's jump vs label; i2 = prev of label = ... zero's block would be: store; condjump; label. i2 = condjump → differ. jump_chain retry: other *simplejumps* to the label — a condjump is not in the jump_chain (only simplejumps are chained, line 220). So no retry. → NO MERGE! Then later the condjump is deleted (reallabelprev == insn && condjump_p) if it jumps to the next insn.

So: make zero's block end with a conditional jump whose target is the epilogue label and which falls through to... hmm, if the condjump jumps to the label and the label is the next insn, the deletion fires. In C: 
```
if (some_condition) return;
```
where some_condition is known false? Or:
```
if (0) return;
```
The front end folds `if (0)`. What about `if (unk1C == 0x1D) return;`? That's a real condition — emits a branch, which would be a real instruction (not deleted) and change the bytes.

We need a condjump that is deleted at jump2, i.e., a conditional jump to the immediately-following label. In C, that's `if (c) goto L; ... L:` where L is the next statement — the compiler might not even emit the branch (front end removes empty if?). Hmm.

What about `if (0) return;`? The front end constant-folds `if (0)` and emits nothing. `if (1) return;` → unconditional return, elided.

Hmm, what about a conditional expression that the compiler can't fold but that's always true at runtime... e.g., `if (unk1C == 0x1D) return;` — real branch. The target has no branch. Unless the branch is deleted because the condition is provably true? gcc 2.7.2 has no VRP. But cse might know unk1C = 0x1D just stored? The store is to memory; the condition `unk1C == 0x1D` would reload — cse could fold the load to 0x1D via store-to-load forwarding? cse1 does handle memory? Probably not reliably.

Hmm, but there's a neat trick: a `do { ... } while (0)` produces a conditional jump to the loop exit (which is the next insn) that is deleted at jump2 by the condjump-to-next rule! And the do-while(0) is a known real-C lever (C0535). The loop's back-edge is a jump to the loop start; the loop exit... Actually a do-while(0) creates: body; condjump back to start. loop.c may remove the loop entirely. Hmm.

Alternatively: `switch (x) { ... }` with a single case? Emits a branch.

Let me test the idea: wrap the tail of zero in a construct that produces a conditional jump to the next label. What C construct produces `if (cond) goto L; L: ...`? An empty if with a goto? The compiler removes `if (0)`. `if (c) ;` → branch to next → probably deleted at parse? Actually `if (c) ;` emits a condjump to the join label, which is the next insn; the jump pass deletes it as jump-to-next. That's a real-C no-op! And it would be in the stream at jump2's start, positioned after the store, before the label. Then dec's cross-jump sees i2 = condjump ≠ store → no merge. Then the condjump itself is deleted at jump2 (condjump to next) — but WAIT: the pass iterates forward, so dec's jump (earlier) is processed first, then the condjump later. So the merge is prevented. 

But would the condjump survive until jump2? The earlier jump passes would delete it as a condjump-to-next (line 664) already. Damn — the first pass would delete it too.

Unless the condition has a side effect or the jump is not to the next at the earlier pass but is at jump2. Hmm.

Wait, actually: maybe we WANT it deleted at jump2 only. But the first pass also deletes condjumps to next. So no.

Hmm, BUT: what if the condjump is to a label that is next at jump2 but not at the earlier passes? Nothing changes layout.

OK, what if the construct's condjump is NOT deleted at all (real branch) but reorg/other pass removes it? Unlikely.

Let me look at the actual mechanics of the earlier passes: does the first jump pass (after_regscan=1, before cse) really delete condjumps to next? Yes (line 664). So any conditional jump to the next insn dies in the first pass.

So the only surviving non-note insn at the end of zero's block at jump2 would be something real.

Hmm, let me reconsider the problem: maybe the ORIGINAL zero block's final instruction before the label at jump2 was NOT the sw, because the original source had the store to unk1C *before* the sh (v1 shape: li; sw; sh) and then sched2 (post-reload scheduling, which runs before jump2!) reordered them to li; sh; sw!

v1 gave score 2 with sw;sh order. But maybe sched2 in v1 didn't reorder because of the REG_DEAD notes or dependencies. Let me look at v1's sched2/dbr dumps to see why.

Actually, in v1 the source order is sh;... wait no. v1 = base.replace(SH+STORE, STORE+SH) → source order: unk1C = 0x1D; then sh=0. So emit: li v0,29; sw v0,28; sh zero,244. The target order: li; sh; sw. So we need a swap of the last two.

sched2 runs after reload, before jump2. sched2's list scheduler could reorder two independent stores. In v1 it didn't. Why? Let me look at the sched2 dump for v1.

Alternatively, maybe the original source order was sh;sw (as in src) and the cross-jump was prevented by a *different* thing: the dec block's store being separated. Ugh.

Let me try v1 with modifications that might make sched2 swap the stores:
- Make the sh store's value a variable? 
- Change the base expression of the sh (e.g., via a cast pointer) so sched2 treats them as independent (currently maybe it thinks they alias, preventing reorder). If they alias (both MEM_IN_STRUCT_P same base), sched2 keeps order. To make sched2 swap, it must believe they're independent, and then it needs a reason to prefer sh first. Hmm.

Actually maybe the target order arises not from a swap but from the *source* order being sh;sw with the merge prevented by another mechanism.

Let me look at v1's residual more: only the order of the two stores differs. If sched2 (or sched1) would swap them under some C variation, we'd get 0.

What if the sh store is to a *different base expression*: `CAST_WIDTH(s16,a0,0xF4) = 0;` uses a0 (the parameter) or s0? In target, both use s0. In the RTL, a0 was copied to s0 (the struct base). Hmm.

Idea: make the sh store address depend on the sw's value? No.

Idea: write the zero block as:
```
unk1C = 0x1D;
CAST_WIDTH(s16, a0, 0xF4) = 0;
```
and hope sched2 swaps. It didn't.

Idea: introduce a dependency that forces the sh after the sw in the *pre-reload* RTL but the scheduler then swaps? no.

Alternatively: maybe use sched1's behavior: sched1 runs before reload. In v1's sched dump, check the order. Actually the final order after sched2 is what matters.

Let me look at v1's .sched and .sched2 dumps around the tail to see where the order is decided. Time is limited though.

Actually, let me try a completely different idea: make the zero block's store instruction differ by using a *volatile-free* different addressing: e.g., store through a local pointer variable that is assigned `a0` — then the store's base is a different pseudo that gets allocated to s0? At jump2 it's hard s0 anyway.

Hmm, what if we make the store's base a *different* register that ends up as s0 only in the final? Post-reload regs are fixed, so no.

What if the store is `sw v0,28(s0)` in target and we make zero's store `sw v0,28(s0)` but dec's `sw v0,28(s0)` — identical. Dead end.

Let me reconsider whether the merge really happens at jump2 or somewhere else. The nopin .jump2 shows label 386 created before the store. The .jump (first pass) — does it already show the merge? Let me check j1_nopin.rtl for a label before the store. Earlier j1_nopin tail showed: insn 366 store, note BLOCK_END, label 371 — no extra label. So the merge is at jump2. Good.

Now, at jump2, the insn stream before the merge: dec block: 317 lw, 319 addiu, 321 store, 323 jump→371; then barrier, label 325 zero, ..., 364 li, 361 sh, 366 store, note, label 371.

Wait a moment: the pass processes insns in order. It reaches jump 323 (dec) BEFORE the zero block's store 366. At that point, the label 371's predecessor is store 366 (already in the stream). So merge. Yes.

What if the zero block's store were placed AFTER the label at jump2? Not possible.

What if dec's jump were processed when the label's predecessor was different? The label 371 is the return label at the end; its predecessor is fixed.

OK: so the only real-C solutions: (a) zero block ends with a jump/insn at jump2, (b) the stores differ, (c) the dec jump isn't simplejump.

For (a): the jump must survive the first jump passes. A jump to a label that is NOT the next insn at the first passes but becomes next at jump2? The layout doesn't change... BUT WAIT: the return label's position DOES change! expand_function_end places the return label at the end, but the *epilogue* code might be emitted in RTL for non-leaf functions? Let me check: in the orig .rtl dump, after the return label 373/374, is there anything? The orig .rtl tail showed label 374 last. And the mini test's .rtl — let me check mini2.c.rtl: does label 29 come last with nothing after? The mini2 asm shows `$L1: j $31` — the epilogue `j $31` is generated in final, not RTL.

Hmm.

For (c): make dec's jump not simplejump_p. What if dec's block ends with a `return` insn (jr ra) instead of j? Target has j.

For (b): make the stores differ. The only way: different hard register or different address. Target shows identical.

I'm stuck on the theory. Let me look at the ACTUAL original source hint: maybe the function exists in another overlay with a different form! The function is templated across overlays? The TU is ov_SC03_007_jr_80183894. Other overlays may contain the same function (same address func_80184E8C). Search src for other definitions of func_80184E8C.
