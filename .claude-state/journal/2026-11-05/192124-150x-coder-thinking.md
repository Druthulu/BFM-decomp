---
ts: 2026-11-06T02:21:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_t27d5SL2lURZ0aV9m1t8
---
Label 374 is the last insn; next_active_insn(374) = 0. So the redirect at line 656 SHOULD fire and convert the jump to RETURN. But we saw condjump_p true at 0x80f31cb (the line-664 check) — meaning the redirect did NOT convert it.

Ah, maybe the order is: line 653-656 redirect check; but the redirect requires `JUMP_LABEL (insn)` non-null. Our jump's JUMP_LABEL... At the start of the pass, mark_jump_label sets JUMP_LABEL for jumps. For a jump to label 374, yes.

Hmm, but maybe `redirect_jump(insn, NULL_RTX)` returns 0 because validate_change fails when the jump is the last insn before the label? No.

Wait, maybe the code at 656 is guarded by something in this version — let me re-read lines 650-660 exactly in the reference source. Earlier I saw:
```
	  reallabelprev = prev_active_insn (JUMP_LABEL (insn));

	  /* If a jump references the end of the function, try to turn
	     it into a RETURN insn, possibly a conditional one.  */
	  if (JUMP_LABEL (insn)
	      && (next_active_insn (JUMP_LABEL (insn)) == 0
		  || GET_CODE (PATTERN (next_active_insn (JUMP_LABEL (insn))))
		      == RETURN))
	    changed |= redirect_jump (insn, NULL_RTX);
```

This is in the reference source. But the pinned cc1 may be built from a *different* (PSX-patched) source where this differs! The reference tree is vanilla 2.7.2; the psx build may have modifications. Hmm.

Anyway, the empirical fact: the jump-to-next is deleted at the first pass. So no trailing jump.

Let me now think about the ORIGINAL source differently: maybe the original zero block did NOT fall through to the epilogue; maybe the epilogue was reached via a jump from zero, and the *final* layout (zero falling through) is the result of the jump being deleted at jump2. For the jump to survive to jump2, it must not be a jump-to-next at the earlier passes. Since the label is at the end, it IS jump-to-next. Unless the jump targets a DIFFERENT label that is not next: e.g., the original zero block ends with `goto L;` where L is a label in the MIDDLE of the function (a backward jump)! A backward jump is not jump-to-next and survives. Then jump2 might thread/redirect it to the epilogue label... but the final asm would have a `j` (backward) in zero, not a fall-through.

Hmm, but the final target zero block has NO jump. So the jump was eliminated at jump2 by the cross-jump? Wait — if zero's block ends with a backward jump (not to the epilogue), then dec's cross-jump comparison i2 = that jump (not the store) → no merge. Then later, jump2's jump threading might redirect the backward jump to the epilogue and delete it if it becomes jump-to-next? jump2's condjump-to-next deletion (line 664) would then delete it (since condjump_p includes simple jumps!). YES! That's it!

Sequence: 
1. Source: zero block ends with a `goto` to a label that is NOT the next insn at the first passes (so the jump survives all early jump passes).
2. At jump2, the pass threads/redirects that jump to the epilogue label (via jump-to-jump threading: "Detect a jump to a jump"), making it a jump to the next insn.
3. When the pass reaches zero's jump (after dec's jump), it deletes it as jump-to-next.
4. Meanwhile, dec's cross-jump at jump2 saw i2 = zero's jump (not the store) → no merge.

But wait: at jump2, dec's jump is processed BEFORE zero's jump (forward order). At that moment zero's block ends with the backward jump → no merge. Then zero's jump gets redirected/deleted. 

But does the jump-to-jump threading happen before dec's jump is processed? The "Detect a jump to a jump" optimization is at the END of the loop body (the `else` branch at line 1790), and the pass processes insns in order. zero's jump is after dec's. So when dec's jump is processed, zero's jump still points backward → no merge. Then zero's jump is processed and redirected to the epilogue → becomes jump-to-next → but is it deleted in the same pass? The jump-to-jump code redirects the jump; then the next iteration of the while(changed) loop would process it and delete it as jump-to-next. So after the pass, zero's jump is gone → fall-through. 

So the original C likely had the zero block ending with a `goto` to an earlier label (a backward jump), which gcc threads to the epilogue. Which earlier label? Perhaps the original C was structured with a `goto` to a common exit label at the top? Hmm, the function has many `return;` statements (which jump to the epilogue label). A `goto` to a label placed where? 

Actually, simpler: the original zero block might end with `goto dec;`? No, that would loop.

Hmm, but which label would the zero block jump to that is backward and threads to the epilogue? If the zero block's `return;` is not the last statement of the function, the compiler emits a jump to the *return label* — which is at the end (forward, next). Deleted early.

Unless the return label is NOT at the end at that time. Hmm.

Wait — what if the zero block ends with `return;` but the function has MORE code after the zero block that is unreachable/dead but present in the RTL? E.g., the source has the zero block, then a `return;` for another path that the compiler places after. Then the return label is after that code, not next to the zero block's jump. The zero block's jump survives; at jump2, dec's cross-jump fails (i2 = zero's jump); then... the zero block's jump is to the return label, which is at the end after the extra code. It wouldn't be jump-to-next, so it survives → the final asm would have a `j` in the zero block. Target has none.

Hmm.

What if the zero block ends with `goto L;` where L is a label at the START of the function (backward)? Then the jump survives to jump2, dec's cross-jump fails. Then jump2's jump-to-jump: L is a label at the start; the code at L is not a jump, so no threading. The jump survives → final asm has a backward jump. Target has none.

So the zero block's jump must be eliminated by jump2 via jump-to-jump threading. That requires the target label to be itself a jump to the epilogue. So: zero's block ends with `goto L;` where L is a label placed on a block that ends with `j epilogue`. Which block? Any block that ends with `return;`. E.g., the `dec` block! If the zero block ends with `goto dec;`... no, that would be semantically wrong (it would decrement again).

But maybe the original C had a shared exit: `goto out;` where `out:` is placed at a block that returns. Hmm, but the target's zero block's last insn is the store; if the source had `goto out;` the final asm would have a `j` unless threaded and deleted.

Threading: "Detect a jump to a jump": if insn is a jump to label L, and L's block begins with a jump to M, then redirect insn to M. If M is the epilogue label and it's the next insn... but the epilogue is at the end, far from zero. So after redirect, zero's jump targets the epilogue (forward, far) → not jump-to-next → survives → final has a j. Unless the jump-to-next deletion at 664 requires reallabelprev == insn, i.e., the target label's prev active insn is the jump itself. For the epilogue label at the end, prev_active = zero's jump (if zero is the last block) → yes! reallabelprev == insn → delete_jump! 

So: zero's block ends with `goto L;` where L is a label at the start of some block that jumps to the epilogue. At jump2:
- dec's jump processed first: i2 = zero's jump (goto L) → differs from dec's store → no merge.
- zero's jump processed later: "jump to a jump" → redirect to the epilogue label. Then, since reallabelprev (computed at the start of this iteration, before redirect?) hmm. reallabelprev = prev_active_insn(JUMP_LABEL(insn)) computed at line 653 with the OLD label L. Then the redirect happens later in the iteration (line ~1790). Then in the NEXT iteration of while(changed), the jump (now to the epilogue) is processed: reallabelprev = prev_active_insn(epilogue) = zero's jump itself (since zero is last) → == insn → condjump_p true → delete_jump! 

So the final asm: zero block ends with the store, falls through to the epilogue. And dec's block wasn't merged. That's exactly the target!

Now, what C produces `goto L;` at the end of zero where L is a block ending with a jump to the epilogue? In C: a `goto` to a label placed just before a `return;`. E.g.:

```
zero:
    ...
    unk1C = 0x1D;
    goto out;
...
out:
    return;
```
But the `out: return;` block would be emitted after the zero block, adding code after zero (a return block), changing the layout: the epilogue would be preceded by the `out` block, not zero. Hmm. Unless the `out:` label is placed on an EXISTING return block earlier in the function (backward goto). E.g., the label is placed at the `dec:` block? No.

Alternatively, the original C might have a shared "return" path at the top: many functions in this codebase use `goto` to a common cleanup/exit label placed earlier. Hmm.

But wait: the target's zero block is followed directly by the epilogue label 180c, which is targeted by ~10 jumps. If there were an `out:` block at the end, it would be between zero and the epilogue. Unless the `out:` block is *empty* and merged into the epilogue label: e.g.:

```
    goto out;
out:
    ;
}
```
The `out:` label would be placed right after the goto, and the return label after it. Then the jump to `out` is jump-to-next → deleted early. No.

Hmm, what if the label is placed at the START of the zero block (backward)? `goto zero;` at the end of zero → infinite loop. No.

What if the label is at the end of the *dec* block? I.e., the zero block ends with `goto dec_end;` where dec_end is a label right after the dec block's store? But then the dec block would have to end with a return after that label... 

Hmm, let me reconsider: maybe the label is at the start of a block that ends with a `j` to the epilogue, and that block is *the zero block itself*? No.

What about this structure: the original C might be a `switch` where each case ends with `break`, and the code after the switch has the zero logic... no.

Let me think about the target's actual layout and what source structure yields it:
```
16d4: t = unk1C
16dc: beqz v0, 17d0 (zero)
16e4: slti; beqz -> 17bc (dec)
16ec: unkFE check; bnez -> 1748 (second)
1704: call BD3C; bne -> 1748
1718: shared: ...; j 180c
1748: second: call BD3C; bne -> 179c (turn)
1764: call 5D3C; bnez -> 1718 (shared)
1778: ...; j 180c
179c: turn: call B8E4; ...; unk12 += r
17bc: dec: unk1C--
17c8: j 180c
17d0: zero: ...
1808: sw
180c: epilogue
```

The `dec` block falls into... dec ends with `j 180c`. The zero block is placed after dec (source order). The blocks that end with `j 180c` are the returns.

For the zero block to end with a jump at jump2 that threads to the epilogue, the source must have `goto L;` where L is a label on a block ending with `j 180c`. The nearest such block is dec (17bc-17c8). So maybe the source is:

```
    goto dec_tail;   // at the end of zero
...
dec:
    unk1C--;
dec_tail:
    return;
```
But then dec_tail's return would emit a jump; the label dec_tail is at the return. Hmm, but the zero block is AFTER dec in the layout, so a goto from zero back to dec_tail is a BACKWARD jump. Then the dec_tail label is inside dec's block. In the target, dec's block is: 17bc lw; 17c0 nop; 17c4 addiu; 17c8 j; 17cc sw. If there were a label before `j 180c`, it would be at 17c8. A backward goto from zero to that label would produce `j 17c8` in zero. At jump2, dec's cross-jump: i2 = zero's jump → no merge. Then zero's jump is threaded: label 17c8's block starts with a jump to the epilogue → redirect to epilogue → next iteration deletes it as jump-to-next (since zero is last and the epilogue is next). Final: zero falls through. And dec's block is unchanged!

This is plausible! But what C would have `goto` to a label right before the return in the dec block? Hmm, that seems odd. But maybe the original C had a shared tail: e.g., a `switch` or a common exit where the dec case's `return` is a label shared by multiple paths.

Hold on — maybe simpler: the original zero block ends with `return;` and the compiler emits `j <return_label>`. The return label is at the end. At the first jump pass, this jump is jump-to-next → deleted. UNLESS the return label is preceded by other code (e.g., the epilogue's stack restore RTL) that is emitted in expand_function_end! Wait: in the .rtl dump, the return label 374 is last, with nothing after. But maybe for functions with a frame (non-leaf), expand_function_end emits a `(use (reg 31))` or the epilogue label placement differs? Our mini TU has the same function (non-leaf, frame) and the label is last.

Hmm OK. So the goto-to-a-return-block idea requires a label on a returning block. 

Wait, actually — what about `goto` to a label placed at the very END of the function *before the return label*, where the label is on an EMPTY block? Empty blocks might be eliminated/merged with the return label. If the label merges with the return label (consecutive labels are combined), the goto targets the return label directly and becomes jump-to-next at the first pass. Deleted early.

Hmm.

Let me approach from the "what would a decompiler write" angle: this function is likely from a real game; the C was probably:
```
void func_80184E8C(s32 a0) {
    ...
    if (t == 0) {
        ...
        ((Unk*)a0)->unk1C = 0x1D;
        return;
    }
    ...
}
```
If the zero block is the `if (t==0)` branch placed at the END (compiler layout), the return inside it is the last statement executed but the function body's last statement might be the if itself... The compiler's expander emits the return jump. At the first jump pass it's jump-to-next → deleted. Same.

Hmm, but maybe the original code's zero block is NOT last in source: e.g.,
```
if (t == 0) { zero...; unk1C = 0x1D; }
else if (t >= 0x1E) { dec...; }
else { ... }
```
In this if/else structure, the zero block would be emitted FIRST (right after the test), not last. But the target has zero last! So the source must use gotos to reorder. That means the original source itself had gotos (it's decompiled-style C? no, it's the game's original C, probably not).

Unless the compiler's block reordering put the zero block last. gcc 2.7.2 doesn't reorder blocks, but the *if-else* emission order can put the else branch last. E.g., `if (t != 0) { ...dec/turn... } ...zero...` — the zero code after the if, emitted last. That's the current src structure (if t!=0 {...} then zero). Hmm, the current src uses goto labels; the original may have been:

```
t = unk1C;
if (t != 0) {
    if (t >= 0x1E) { unk1C--; return; }
    ...
    return;
}
/* zero */
...
unk1C = 0x1D;
```

Same as now.

OK, I need to decide: I've spent a lot on item 1. The WALL threshold is met. But this goto-to-return-block idea is testable cheaply! Let me construct a C body where the zero block ends with `goto` to a label placed at the dec block's return. Concretely:

```
    ...
    r = func_8012B8E4(a0, 0x10);
    ((Unk*)*(s32*)(a0+0x20))->unk12 += r;
dec:
    ((Unk*)a0)->unk1C--;
    goto zret;          // label before the return
...
zero:
    ...
    unk1C = 0x1D;
    goto zret;
zret:
    ;
}
```
Hmm, but `zret:` at the end would be after zero, and the goto from dec would jump forward to it. The layout: dec block ends with `goto zret` (j forward), and zret is after zero. That changes dec's block (target: dec ends with j 180c = the epilogue). If zret is placed at the end, it's an empty label; consecutive labels merge with the return label. dec's jump to zret would be a jump to the return label → j 180c (target!). And zero's jump to zret would also be j <epilogue> → jump-to-next (zero is last) → deleted at the first pass. Damn, zero's jump would be deleted early again.

Unless zret is NOT at the end. Hmm.

Wait, I realize the target's dec block ends with `j 180c` — the epilogue label. In the source, dec ends with `return;`. Fine.

For zero's jump to survive the early passes, its target must not be the next insn at that time. The only way: the target is backward or far. If zero's goto targets a label on a *returning block* (like dec's return label at 17c8), that's backward. Then at jump2, jump-to-jump threading redirects zero's jump to the epilogue (forward, and since zero is last, the epilogue is next) → deleted in a later iteration. And dec's cross-jump sees zero's jump (to 17c8) → no merge. 

But what C has a label at dec's return? Perhaps the original C had a shared exit label:
```
    ...
dec:
    unk1C--;
    goto done;
...
done:
    return;
```
with `done:` placed... where? If `done:` is after the zero block, it's forward.

Hmm, unless `done:` is placed between dec and zero in the source:
```
    goto zero;  // hmm
```

Honestly, maybe the original structure is:
```
t = unk1C;
if (t == 0) goto zero;
if (t >= 0x1E) goto dec;
...
goto done;   // shared
...
done:
    return;
zero:
    ...
    goto done;
```
With `done:` placed before the zero block (backward from zero, forward from the others)! Then:
- dec: `unk1C--; goto done;` → j done.
- done: return; → j epilogue.
- zero: ...; goto done; (backward)

Layout: dec, done(return), zero. But the target has dec immediately followed by zero, with the return at the end (180c). If `done:` were between dec and zero, the return would be at 17c8-ish, and zero after. Target: dec at 17bc-17cc, then zero at 17d0. The return label 180c is at the end. Hmm, dec's j targets 180c (end), not a label right after dec.

So `done:` would have to be at the end (180c). Then zero's goto done is forward to the end → at the first pass, is it jump-to-next? zero is the last block, done/return label is right after zero → jump-to-next → deleted early. Argh.

Wait, but maybe not: if the source is `goto done; done: return;`, the `done:` label is followed by the return label; the two labels merge. The jump from zero to done is jump-to-next → deleted at the first pass. So no.

Hmm, so how can zero's jump survive the first pass? Its target must be strictly backward or to a non-next insn. A backward jump to a label on a returning block: e.g., `goto dec_ret;` where dec_ret is at 17c8 (dec's return). That means the source has a label on dec's return. 

Could the original C have:
```
dec:
    ((Unk*)a0)->unk1C--;
    return;
```
and zero ending with `goto dec;`? No (would decrement).

What if zero ends with `goto dec_ret;` where dec_ret is a label placed just before the return in dec's block, e.g.:
```
    if (t >= 0x1E) {
        unk1C--;
        goto dec_ret;   // ?
    }
dec_ret:
    return;
```
That's weird C.

Alternatively, zero ends with `goto shared;` where `shared:` is the label of the SHARED block at 1718 (the one that does the `unk5C &= ~0x200` etc. and returns). That's backward! The shared block is at 1718 and ends with `j 180c` (return). So `goto shared;` from zero is a backward jump to 1718. At jump2:
- dec's jump (17c8) processed: i2 = zero's jump → no merge ✓.
- zero's jump processed: "jump to a jump"? The shared block at 1718 starts with `lhu v0,92(s0)` (not a jump), so no threading. The jump survives → final asm would have `j 1718` in zero. Target has none. ✗

Unless the shared block's first insn is... no.

Hmm, what if zero ends with `goto turn;`? turn at 179c starts with a call. No threading. ✗

What if zero ends with `goto zero;`? self-loop, no.

So the jump must be eliminated. The only mechanism that eliminates a jump at jump2 is the jump-to-next deletion (reallabelprev == insn). That requires the jump's target label's prev active insn to be the jump itself — i.e., the target is the immediately following insn. So zero's jump must end up targeting the next insn after it. Since the epilogue label is next after zero, zero's jump must target the epilogue. But at the first pass, a jump to the epilogue (next) is deleted early. Contradiction!

Unless the epilogue label is NOT next at the first pass but becomes next at jump2 — impossible, layout fixed.

UNLESS the jump is created at jump2 by threading! A backward jump that gets redirected to the epilogue at jump2 (via jump-to-jump threading) and then deleted in the next while-iteration. For threading, zero's target label must be on a block whose first insn is a jump to the epilogue. Are there any such labels? The label at 17c8 (dec's return jump) is inside dec's block, not at its start. The labels at 1718 (shared) start with a load. Hmm.

What about a label placed exactly before a `j 180c`? In the target, dec's block ends with j 180c at 17c8. If there were a label there, it'd be a jump-to-jump threading source. Which source label would be before that j? The `dec:` label is at 17bc (start of the block). No.

What about the labels at 1718 (shared) — the block starts with lhu, not a jump.

Hmm, what about the label at 1748 (second) — starts with li a1.

So no threading.

Therefore, the jump theory fails. The original must have prevented the merge differently. 

Let me revisit the possibility that the two store insns differ at jump2. Since the final bytes are identical, the difference must be in an attribute not encoded in the final instruction but present in RTL: e.g., REG_EQUIV/REG_EQUAL notes (not compared), MEM flags (not compared), or the *mode* (compared), or a SUBREG (compared via rtx_renumbered_equal_p: SUBREG vs REG are both accepted and compared by reg number... but a SUBREG with word 0 of a reg vs a plain REG: the code path at the top handles both, comparing reg numbers and word; a plain REG has word_x=0, and a SUBREG word 0 → equal!). So no.

What about the store's MEM address: one is `(plus (reg s0) (const 28))` and the other `(plus (reg s0) (const 28))`. Same.

What if one store is `(set (mem:SI ...) (reg:SI v0))` and the other `(set (mem/s:SI ...) (reg:SI v0))` — MEM_IN_STRUCT_P is not compared (it's a flag in the RTX, and rtx_renumbered_equal_p compares only the format fields). Same.

Hmm, what about the REG_DEAD notes? Not compared.

So at jump2, if both stores are `sw v0,28(s0)` with the same operands, they're equal. Hence the merge. The target must therefore differ in the CFG/label layout, not the insns.

Let me look at the target's dec block once more: is dec's jump really a simple jump to 180c, or could it be a conditional? Target at 17c8: `08000603 j 180c` — simple jump.

So the only remaining possibility: at jump2, the label 180c's prev active insn was NOT zero's store. What could be between zero's store and the label? A BARRIER! If zero's block ended with a jump at jump2... but we showed a trailing jump is deleted at the first pass. UNLESS the jump was created between the first pass and jump2! Which pass creates jumps? loop_optimize, cse, cse2, jump threading, sched2, and... `reorg`? no. Hmm, what about the epilogue/prologue? 

What about `flow`/`combine`? combine runs before the first jump pass.

What about `loop_optimize` creating a jump at the end of a block? If the zero block's tail were inside a LOOP... no.

What about `cse2`? It can create jumps? cse_main can "simplify" branches but not add a jump at the end.

What about sched2? It doesn't add jumps.

What about `reg_scan`? no.

Hmm, what about the *prologue/epilogue* pass: `expand_function_end` runs before all.

What about `final`'s peepholes? after jump2.

So no.

OK, so maybe the merge in the target was prevented by the *dec* block's jump not being processed as a simple jump to the epilogue label at jump2 — e.g., the jump was to a DIFFERENT label at jump2, which was later threaded/redirected to the epilogue. If dec's `return;` jump targets a label L (not the epilogue) at jump2, then find_cross_jump compares dec's store with L's predecessor. If L is a user label placed elsewhere... Hmm, but the final dec jump targets 180c.

What if the original C had a `goto` at dec's end to a label at the epilogue, e.g., `goto out;` where out is a user label at the end? Then the jump targets `out`, whose prev is zero's store → merge (same as before).

What if dec's block ends with a jump to a label whose predecessor is NOT zero's store? E.g., a label at the start of the zero block! dec: `goto zero;`? That would run the zero code — semantically wrong.

Hmm, I'm going too deep. Let me make a decision: WALL for item 1 with best 2, and move on. I've spent ~1h15 on it. The remaining 4 items need attention.

Actually, WAIT. One more idea, cheap to test: make the zero block's store followed by a `return;` AND make the return label NOT next by adding a *reachable* statement after the zero block in the source that emits code but is unreachable at runtime (e.g., `if (t == 0x123456) { func_8012CBA4(a0); }` after the zero block). That would place code after zero, so zero's return jump targets the return label at the end, which is not next (there's code in between). The zero block would then end with a jump at the first pass (survives!), and at jump2 dec's cross-jump fails (i2 = zero's jump). Then zero's jump to the return label: at jump2, reallabelprev = prev_active_insn(return label) = the last insn of the extra code, not zero's jump → not deleted → the final asm would have a jump in zero and the extra code. That changes the bytes (extra code + jump). ✗

Unless the extra code is eliminated by flow before jump2 (dead code). E.g., `if (0) { ... }` is folded by the front end. `if (t == 0x12345)` — not provably dead.

Hmm, what about a statement after the zero block that emits nothing but prevents the label from being next? A NOTE? Notes are skipped.

What about a label? Labels are skipped by prev_active_insn? Let me check: prev_active_insn stops at INSN/JUMP/CALL, skipping notes AND labels? From the code: it loops while insn and checks NEXT... it breaks on INSN/JUMP/CALL. Labels/notes are skipped. So a label doesn't help.

OK. WALL for item 1. Let me record it and move to item 2. Time is limited (5 items).

Actually, hold on. Let me reconsider one specific cheap variant: what if the zero block's last two stores are ordered sh;sw in source (target) but the sw store is *conditional* in a way that emits the same bytes? No.

Or: what if the `sw` is emitted as part of a `do{}while(0)` loop such that at jump2 the block ends with the loop's back-edge jump (to the loop start, backward), which survives the first pass? Then dec's cross-jump sees i2 = the back-edge jump → no merge! And the final asm: the loop would need to be removed by loop_optimize... but loop_optimize runs BEFORE jump2. Hmm, if loop_optimize leaves the loop, the back-edge jump remains → bytes differ.

But wait: `do { store; } while (0)` — loop_optimize would delete the loop and the back-edge (the condition is constant 0 → the loop is entered once; gcc's loop optimizer might keep the do-while structure until...). w2/w8 (do-while around the store) gave 136 (merged) — so the loop was removed before jump2, and the store was last. So no.

What about `do { store; return; } while (0)`? x2 gave 136 (merged).

Hmm, what if the back-edge jump survives because of `break`? no.

OK, WALL. Let me now also double-check the try count for the record: orig (control, not counted), nopin, vA, v1-v8 (8), w1-w20 (19, but w6 wasn't scored — I skipped w6 in the sc list), x1-x4 (4). Scored: nopin(1) + vA(1) + v1-v8(8) + w1,w2,w3,w4,w5,w7,w8,w9,w10,w11,w12,w13,w14,w15,w16,w17,w18,w19,w20 (18) + x1-x4(4) = 32 scored. Plus orig control. Good: ≥30.

Let me write the results row, notes, moves line, and win.c (= v1.c, the best). Then clean the dumps dir.

Results row format: dir file func kinds result best tries wall evidence. The `wall` field for WALL = a tag from walls.txt or a new `<pass>-<what>`. I'll use `jump2-crossjump-fallthrough`.

Evidence (≤140 chars): "jump2 cross-jump: zero falls through to the epilogue label so minimum=1 and the lone `sw v0,28(s0)` merges dec's; store-before-sh (score 2) breaks it but sched keeps source order."

That's ~170 chars. Trim: "jump2 cross-jump: zero falls through to the epilogue, minimum=1, lone `sw v0,28(s0)` merges dec's; store-before-sh breaks it but order residual 2." ~150. Let me count later.

Let me write the files.
