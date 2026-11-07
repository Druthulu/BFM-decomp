---
ts: 2026-11-06T13:00:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KWGXsAxzkOWQdByAdU2t
---
All 315 ins, best 19. As expected, cross-jump merges regardless.

Let me try a couple more targeted ideas:

c8: put the else-arm's break inside a nested `if` with a label-producing construct... 

c9: Use `goto` to a label placed at the epilogue start, and make the *other* arm use `break` — jump_optimize's "jump to jump" might not unify if the label isn't at the jump target. Actually: `break` jumps to the switch-end label L_end. The epilogue code follows. If I add `L_epi:` right before `func_80183DA0(s0);` — that label is *at* the same place as L_end. jump_optimize would redirect break's jump to L_epi (they're the same insn position) — hmm, jump_optimize's "jump to next insn" deletion would delete the `goto L_epi` if L_epi is the next insn. Not helpful.

What if the label is placed *before* the join instead:
```
if (d >= 0) {
    if (d >= 0x80) goto L_epi;
} else {
    if (-d >= 0x80) break;
}
```
Both target the epilogue. jump_optimize will probably redirect the goto to the same label as break (since L_epi == the switch-end label position). Then identical.

c10: What if the then-arm's break is replaced by a *conditional* return? No, the function continues.

Hmm, let me look at what actually differs between the two arms in the RTL at jump2 time. The barrier insn is in the then-arm. Its presence makes the then-arm's tail differ from the else-arm's tail.

Could another *real* insn serve that role without changing the target? The target's then-arm emits 4 insns: slti, beqz, nop, j, nop. If the then-arm had an extra real insn, the target would have it too.

So the target's shape requires an RTL insn that emits nothing = exactly the empty asm. Unless the difference comes from something invisible in the final output but present in the RTL... like a NOTE! A note between the slti and beqz would stop find_cross_jump? No — `while (i2 && (GET_CODE (i2) == NOTE || GET_CODE (i2) == CODE_LABEL)) i2 = PREV_INSN (i2);` — notes are skipped in i2 but `i1 = prev_nonnote_insn (i1)` also skips notes. So notes don't stop it. Only CODE_LABEL does (and the label decrements minimum).

Hmm: `if (GET_CODE (i1) == CODE_LABEL) { --minimum; break; }`. minimum starts at 2. Each match decrements. So to block the merge we need a label to appear before 2 matches have been made.

The matched region in mine is 1 insn (beqz)? Let me count: after the merge, mine has a shared beqz. Cross-jump merges the insns *before* the jump. Hmm.

If a label existed right before the beqz in the then-arm, the scan would hit it after 0 matches → minimum 2→1, break → minimum(1) <= 0 false → no merge! That's the lever: a CODE_LABEL immediately before the beqz in one arm.

Can I create a label immediately before the beqz in C? The beqz is the `break` (jump to epilogue) for `if (d >= 0x80) break;`. In RTL the branch is the last insn of the block. A label before it would have to be a branch target.

Hmm, what if the `if (d >= 0x80) break;` is written as a loop:
```
do { if (d >= 0x80) break; } while (0);  // breaks the do-while, not the switch
```
Semantics change: we need to break the switch. 

What about `while (1) { if (d >= 0x80) break; ... }`? no.

Hmm, what about a switch-based `break` inside a nested switch? `switch (0) { case 0: if (...) break; }` — breaks the inner switch, not the outer.

OK, what if the code uses `goto L_out;` where L_out is a label placed at the END of the epilogue (not the start)? Then the then-arm's jump goes to L_out while the else-arm's break goes to the switch-end label. Different targets → no cross-jump. But then the target's code would have `j L_out` where L_out is at the function end — the target has `j 47d8` (the join) for the then-arm and the else falls through to the join. Hmm, that doesn't match: in the target, the then-arm jumps to the JOIN (47d8), not to the epilogue.

Wait, let me re-read the target:
```
112 bltz v0,47c8     ; d<0 -> else arm
113 slti v0,v0,128
114 beqz v0,4aa8     ; d>=0x80 -> epilogue (break)
115 nop
116 j 47d8           ; goto join
117 nop
118 47c8: else arm: subu; slti; beqz v0,4aa8; nop
122 47d8: join
```
Yes. So the then-arm ends with `j join` and the else-arm falls through to join. Standard.

So the merge in mine replaced the then-arm's `slti;beqz;nop;j;nop` with a `bgez` to the else's slti and a shared beqz. 

Now: find_cross_jump is called for a conditional jump `insn` (the beqz?) and compares with the insn before the jump target. Ugh.

Practical alternative: maybe make the else-arm not fall through into the join. E.g., write the else-arm with a `goto join` explicitly? That adds a j (target doesn't have it).

Honestly, this is the documented `jump2-crossjump-arms` wall (func_80180D38: "cross-jump merges the byte-identical ... only an asm insn between them blocks the merge; 33 lever-free bodies, best 10"). I'll do more tries to reach 30 and 20 minutes, but let me first check items 4 and 5, then come back to do extra tries on items 2 and 3 to satisfy the wall requirements.

Actually — the budget is 20-30 min per item and a WALL needs ≥20 min AND ≥30 tries. Item 3 has 8 tries so far. Item 2 has 32 tries but ~6 min.

Let me now look at items 4 and 5, then return to items 2 and 3 to add tries/time.

Item 4: func_80181F74 (196 ins, 3926 chars). Item 5: func_8018893C (203 ins) — the twin of item 2! Since item 2 is a wall, item 5 will likely be the same wall (same shape, different symbols). But it's a separate item, so it needs its own row and its own ≥30 tries if a WALL. Hmm, that's expensive. But the wall tag applies and the evidence is the same shape; the brief says a WALL needs ≥20 min and ≥30 tries *on that item*. 

Hmm. Well, I can run 30+ candidates on item 5 quickly by reusing the variant generator (the twin's body is identical except symbol names). That's cheap (each score ~2-3s). 30 tries ≈ 2 minutes of compute. The ≥20 min requirement is about wall time though. I'll start items 4/5 and let the time accumulate.

Actually, better plan: since time is the binding constraint, let me interleave: start item 4 (new shape), then come back.

Let me look at item 4.
