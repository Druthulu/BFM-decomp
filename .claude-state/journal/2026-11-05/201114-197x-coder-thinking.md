---
ts: 2026-11-06T03:11:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fFdnBXSELQfX7nG0hqeI
---
n2 has the right instruction count and the right structure (the tails are separate!) but the register allocation differs (v1 vs v0). The two-if structure prevents the cross-jump (good) but changes the register assignment: mine uses v1 for d and a1/a0 for the operands, target uses v0 for d and a0/v1.

The target's register usage:
- lh a0,10(s1) — unkA
- lh v1,26(sp) — buf1
- subu v0,a0,v1 — d = unkA - buf1
- bltz v0, else
- slti v0,v0,513
- ...
- else: subu v0,v1,a0 — d = buf1 - unkA

Mine (n2): lh a1,10(s1); lh a0,26(sp); subu v1,a1,a0; bltz v1; slti v0,v1,513; ... bgez v1,4c08; subu v1,a0,a1; slti v0,v1,513.

So mine uses a1/a0 and v1; target uses a0/v1 and v0. The difference: which pseudo gets which register. This is a register-allocation residual (MIXED, score 8).

Hmm, but n2's structure has an extra `bgez v1,4c08` where the target has `j 4c08`. So n2's first if-body ends with a conditional `bgez` instead of an unconditional j — because with two separate ifs, the second if's test is re-evaluated: after the first if (d>=0), the second `if (d < 0)` uses the same d. The compiler emits `bgez v1, REST` to skip the second if's body. The target has `j REST` (unconditional) because it's an if-else.

So n2 is structurally different: `bgez` vs `j`.

We need: separate tails (no merge) + if-else structure (j REST). The barrier did it. Real-C?

What if we write the if-else with the else arm's test using a *different* comparison that produces the same slti but a different block? Hmm.

Alternative: make the first arm's inner if test *different* from the else's in a way that keeps the same instruction: e.g., first `if (d > 0x200)`, else `if (d >= 0x201)`. At the RTL level, `d > 0x200` = `(gt:SI d 512)` and `d >= 0x201` = `(ge:SI d 513)`. These may expand to the same slti but the RTL *before* jump2 is different (gt vs ge) — but after expand, the MIPS backend generates `slti` insns; the comparison is expanded during RTL generation (gen_cond), so by jump2 both are `slti v0,v0,513; beqz`. Identical. Hmm.

Wait, maybe not: `d > 0x200` might expand to `slti v0,d,513; beqz` (branch when !(d<513)), while `d >= 0x201` expands to `slti v0,d,513; beqz` — same.

What if one uses `d > 0x200` and the other `0x200 < d`? Same.

Hmm. What if one arm's test is `if (d > 0x200) goto TAIL;` and the other is `if (d - 0x200 > 0) goto TAIL;`? Codegen: subu d,512; sgtz? Different. ✗

What about the *delay slot* difference: in the target, both beqz have a nop delay. Same.

OK, what about making the first arm's block end with a jump that isn't cross-jumpable because its *preceding* insns differ? The cross-jump merges the tails: in mine, the merged suffix is the `beqz` (1 insn, since one side falls through). If we make the first arm's beqz not identical to the else's beqz... they're the same insn (beqz v0,TAIL).

Hmm, but wait: in mine, the merge produced a shared `beqz v0` at 4bf0, where the first arm's slti is in the bgez delay slot and the else's slti before. The first arm's test `slti v0,v0,513` and the else's `slti v0,v0,513` are identical too. The cross-jump merged at least the beqz (minimum 1 because the else falls through).

To prevent, the else's block must not fall through to the shared label with an identical tail. The barrier made the else's block end with... the barrier insn after the beqz? The barrier is placed AFTER `if (d > 0x200) goto TAIL;` in the else arm, i.e., after the beqz's block, before the merge point. So the else's block tail (before the merge point REST) was the barrier insn, not the beqz. Hence no merge.

Real-C equivalent: make the else block end with something other than the beqz. E.g., an empty statement? No code. A `goto REST;`? That would emit a jump (extra insn).

Hmm, what if the else arm's last statement is a *store* that the target also has? The target's else block: subu; slti; beqz TAIL; nop; (falls to REST). No extra.

What if the else arm is written so the `if (d > 0x200) goto TAIL;` is the last statement and the block falls through — same.

OK, maybe the real difference is the *order* of the arms or the inversion. Let me look at the target's shape again: `bltz v0, else` — the compiler did NOT invert. In mine (nopin), the compiler inverted to `bgez REST` because the if-body ends with a jump to REST and the else follows. The inversion transform (jump.c 1733) fires when the conditional jump is followed (after its target label) by an unconditional jump. 

In the target, the inversion did NOT fire. Why? Because in the target's RTL, the else body's tail (the slti/beqz) was NOT identical to the if body's tail? Hmm, or because the conditional's target label (else) was not immediately followed by the unconditional jump? Let me think about the RTL before the jump pass:
- if (d>=0) → bltz? The RTL: condjump (ge d 0) to ELSE; then the if-body: subu; slti; beqz TAIL; j REST; then ELSE label; else body.
- The inversion transform at 1733: `this_is_condjump && reallabelprev != 0 && GET_CODE(reallabelprev)==JUMP_INSN && prev_active_insn(reallabelprev)==insn && no_labels_between_p(insn, reallabelprev) && simplejump_p(reallabelprev)`. Here insn = the outer condjump (ge), reallabelprev = prev_active_insn(JUMP_LABEL(insn)) = the insn before the ELSE label = the `j REST` (the if-body's end). prev_active_insn(reallabelprev) = the beqz? not insn. So the condition `prev_active_insn(reallabelprev) == insn` requires the jump to be immediately after the condjump — not our case (the if-body is in between). So this transform is NOT the inversion we saw.

Hmm, so the `bgez` in mine came from a different optimization: maybe the "if-else inversion" in jump.c or the cross-jump itself. Actually mine's shape `bgez REST; ...; else body; REST:` means the compiler moved the if-body to the fall-through and inverted the branch — this is the standard "if (c) A else B" layout where A ends with a jump: the compiler could lay out B first (fall-through) and A after with the branch inverted. gcc's jump pass does "swap_jump"/invert for such cases.

The cross-jump then merged the tails.

In the target, the layout is A first (fall-through after bltz to B), then B, then REST. So the compiler did NOT invert. Why? Because B's tail (slti/beqz) is identical to A's tail → the cross-jump merged them, which then enabled/changed the layout. With the barrier, no merge, so the layout stayed A-first.

So the real-C lever must prevent the cross-jump. The two tails are identical insns; the only way is a CFG difference (a label/barrier) or an insn difference.

Insn difference idea: make the first arm's `d > 0x200` test use a *different register* so the slti's operand differs? The target has both `slti v0,v0,513`. Same.

Hmm, what if the two arms' `d` computations produce different pseudo values such that the slti's *source pseudo* differs at jump2? At jump2 (post-reload) they're hard regs: target both v0. Same.

So at jump2 the tails are identical: `slti v0,v0,513; beqz v0,TAIL; nop`. The cross-jump merges. Unless the blocks aren't cross-jumpable due to the CFG.

The else block: subu; slti; beqz; falls to REST. The if block: subu; slti; beqz; j REST.
Cross-jump: for the if block's `j REST`, find_cross_jump(insn=j, JUMP_LABEL=REST, minimum=1): i1 = prev_nonnote(j) = the beqz; i2 = prev of REST = the else's beqz (fall-through predecessor). Match (beqz vs beqz) → minimum 0 → merge. That's it.

To prevent: the label REST's predecessor must not be the else's beqz. The barrier insn made it the barrier.

Real-C: what if the else arm ends with a *statement that emits an insn but is the same in the target*? The target's else arm ends at the beqz. No.

What if REST is not immediately after the else body? In the target, REST (4c08) is right after the else's nop delay slot. Yes.

Hmm, so in the target, the cross-jump didn't merge despite the identical tails. Why?! Maybe because at jump2, the else's beqz had a different *insn code* or the delay slot was filled? The delay slots are filled by reorg AFTER jump2. So at jump2 both beqz are `(set (pc) (if_then_else ...))` with the same operands.

Unless the target's else block at jump2 ended with an extra insn after the beqz: e.g., a `(note)`? Notes are skipped.

Wait — maybe the target's else block is NOT the fall-through predecessor of REST at jump2! What if REST's label at jump2 was preceded by a BARRIER (from the if-body's jump)? The if-body ends with `j REST`, followed by a barrier! Then the insn before REST is the else body (which comes after the barrier). Hmm: RTL order: if-body: ... beqz TAIL; j REST; barrier; ELSE label; else body: subu; slti; beqz TAIL; REST label. So the barrier is after the j REST, before the ELSE label. The else body follows. REST's predecessor is the else's beqz. Still merge.

Hmm, unless in the target's RTL the else body is placed elsewhere...

I'm going too deep again. Let me try more empirical variants focused on the cross-jump:

o1: make the else arm's `d > 0x200` test use `d >= 0x201` (different RTL comparison, same insn).
o2: make the first arm's test `d > 0x200` and the else's `d >= 0x201`.
o3: make the first arm's test `0x200 < d`.
o4: add a `do{}while(0)` around the else's if (block split).
o5: add a `do{}while(0)` around the first arm's inner if.
o6: wrap the else's d computation and test in a do-while.
o7: `if (d > 0x200) goto TAIL;` vs `if ((s32)d > 0x200) goto TAIL;`
o8: use `else if` chains.

Let me test o1,o2,o4,o5,o6,o7.
