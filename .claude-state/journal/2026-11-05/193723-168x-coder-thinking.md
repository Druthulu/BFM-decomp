---
ts: 2026-11-06T02:37:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ezme0KISDg2wB0dQIoUR
---
No luck. Item 2: ~22 min, ~22 scored tries. Let me try a handful more (need ≥30 for a WALL, and maybe crack it):

More ideas:
- Make the addiu's result live at the target by making the epilogue use v0: the function is void, but what if we add `return;` with an expression? no.
- Change the branch condition's register: `if (state == 0)` instead of `if (unk98 == 0)`? That changes the load.
- Make the addiu write to a register that IS live at the target: e.g., compute `unk34 = state + 1` where state is in s0? If we write `((Unk*)s0)->unk34 = (s32)s0 + 1`? That changes the value.
- Reorder the if body: put the two calls first, then the store (b10 → score 20).
- Put the store last but after a `do{}while(0)` around the calls.

What about making the addiu not the first insn of the fall-through: add a *real* insn before it that reorg can't steal, so reorg leaves a nop? But then the target's first insn after the nop is the addiu — any extra insn changes the bytes.

Hmm, what if reorg's fill picks the addiu but the addiu's *scheduling* changes? No.

Let me look at the target more: is the nop really after bnez, or is it a load-delay nop? Target: a74 lh v0,152(s0); a78 nop (load delay); a7c bnez v0,b3c; a80 nop (branch delay). Yes, branch delay.

OK here's another idea: make the addiu depend on the branch's *condition* value in a way that reorg's `insn_sets_resource_p(trial, &opposite_needed)` triggers: v0 is the condition register. opposite_needed = live regs at the target. If v0 is live at the target... The target (epilogue) doesn't use v0. BUT `mark_target_live_regs` might mark v0 live because the epilogue's `jr ra` returns to the caller, and the function's *return value* convention: for a void function, no.

Hmm, hold on: maybe the bnez target in the RTL is not the epilogue but a label in the middle (e.g., the label 180c is the return label, and the epilogue is emitted in final AFTER the return label; at reorg time the return label's block is the last block, empty). Live regs at an empty end-of-function label: `mark_target_live_regs` might conservatively mark ALL call-clobbered registers live? Or nothing. Hmm.

What if the target label is the *epilogue* which at final emits `jr ra`; at reorg time the label's block might contain a `(use (reg 31))`? 

Let me just dump the dbr RTL of the orig and nopin and diff the area. The dbr dump shows the final RTL (with delay slots). Maybe the difference is visible. Let me dump both and compare the block around the branch.

Actually, the orig's dbr dump would show the nop slot. Let me look at the .sched2 dump (pre-reorg) of orig vs nopin: the barrier insn sits between the branch and the addiu in orig. In nopin, the addiu is right after. The dbr fill in nopin: takes the addiu.

I need a lever-free way to make the addiu not stealable. Since stop_search_p stops on ASM_INPUT/JUMP/BARRIER/SEQUENCE at the fall-through start, and own_thread_p fails on a CODE_LABEL, and the eligibility check fails if the trial sets a resource live at the opposite thread...

What about making the addiu set a register that is live at the *epilogue*? We need v0 live at the epilogue without emitting code. A USE insn at the end of the function would mark v0 live! `emit_use` from... a `(use (reg v0))` insn emits no code (deleted in final). Can we get a USE of v0 after the switch? 

In C: a call to a function whose return value is unused? The call's result is v0; the RTL has `(reg:SI v0)` set by the call and REG_UNUSED. Not a USE.

What about a statement that reads a variable into a dead local? That emits a load (code).

What about `return;` in a function returning void: no USE.

What about a varargs/alloca: emits USE of fp/sp.

Hmm, what about `__builtin_return_address`? no.

What about an inline asm? Not allowed.

What about a `(clobber)` from `__attribute__((noreturn))`? no.

OK, maybe there's a simpler explanation I'm missing. Let me look at the target's case 0 code once more:

```
a74: lh v0,152(s0)
a78: nop
a7c: bnez v0,b3c
a80: nop
a84: addiu v0,a0,1
a88: sh v0,52(s0)
a8c: li a0,2376
a90: jal func_8002D4C8
a94: move a1,zero
a98: li a0,899
a9c: move a1,zero
aa0: jal func_8012C658
aa4: move a2,s0
aa8: j b3c
aac: nop
```

Interesting: a84 `addiu v0,a0,1` uses a0 (the state loaded at a34 into a0). But wait — a0 is also the function's parameter, copied to s0. At a34 `lhu a0,52(s0)` — a0 = state. Then the switch dispatch uses v1/v0. At a84, a0 still holds state. OK.

Now, why wouldn't reorg move a84 into the delay slot? Because it sets v0, which is the branch condition register. Wait — maybe reorg's `needed` includes the branch's condition register because the branch INSN itself references v0? Let's see: in fill_slots_from_thread, `needed` accumulates resources needed by the insns AHEAD of the trial in the thread. The branch is not in the thread. But `opposite_needed` = mark_target_live_regs(opposite_thread). Hmm.

But there's another check I saw at line 78: `! insn_references_resource_p (trial, &set, 1) && ! insn_sets_resource_p (trial, &set, 1) && ! insn_sets_resource_p (trial, &needed, 1)`. `set` = resources set by insns ahead of the trial in the thread (empty). `needed` = resources needed by insns ahead (empty). So passes.

Then at line ~118: `if (condition == const_true_rtx || (! insn_sets_resource_p (trial, &opposite_needed, 1) && ...))`. For a conditional branch, condition != const_true_rtx. opposite_needed = live at the target. v0 must be in opposite_needed for rejection.

So in the target build, v0 IS live at the epilogue. How? Maybe because the *return value* of the function is v0 and the caller... no, liveness is intra-function.

OR: mark_target_live_regs at the epilogue label computes live regs including those live at the *end of the function* = the function's return value register? For a void function, gcc's `current_function_return_rtx` might still be v0 and marked live? Hmm! In gcc, expand_function_end may emit a USE of the return value register for non-void functions. For void, no.

Hmm, but maybe the target function's RTL had a `(use (reg v0))` because the *last* statement's value... no.

Let me test empirically: make v0 live at the epilogue by adding a statement after the switch that reads the last computed value in a way that emits no code? Hmm.

What about making the function return s32 with a value? The signature constraint forbids changing the signature... but wait: "no signature or decl change outside the body (callers stay as they are)". The signature is `void func_80183ACC(s32 a0)`. Can't change.

Hmm, but we could add a `return;` — no value.

OK, let me look at the problem from the "what did the original C look like" angle: maybe the original case 0 was:
```
case 0:
    if (unk98 == 0) {
        ...
        ((Unk*)s0)->unk34 += 1;
        ...
    }
    break;
```
and the compiler's delay-slot fill differed because of the *switch* structure. Our src is a reconstruction; maybe the original used a switch differently, e.g., a jump table with 3 cases? With 3 cases gcc emits comparisons (as the target shows). Hmm.

What if the original had `state` as an `s32` (not u16) so the dispatch differs? The target's `andi v1,a0,0xffff` shows the switch value is zero-extended u16. So state is u16.

Hmm, what if the original's case 0 body order was different: e.g., the `unk34 = state + 1` store was AFTER `func_8002D4C8(0x948,0)`? b10 tested that: score 20, 75 ins. The target order has the store first.

OK, let me look at the reorg fill from a different angle: maybe the target's nop is because the addiu is in a *different basic block* than the branch at reorg time — separated by a CODE_LABEL that jump2 kept (referenced) but that final deleted because the reference was a jump that reorg's delay-slot machinery absorbed? Hmm.

I'll try a few more variants, then WALL:
e1: add a label referenced by a `goto` from the end of the case (a backward goto that forms a loop) — e.g., `do { ... } while (state == 0xFFFF);`? adds a branch.
e2: `switch (state) { case 0: ...; case 0xFFFF: ... }`? no.
e3: make the case-0 body a `default:` case? 
e4: reorder cases (case 0 last)? changes layout.
e5: `if (unk98 == 0) { ... } else { }` (empty else) — could add a label.
e6: `if (!unk98) {...}` (negated condition) — might change the branch polarity and the fill. The target uses bnez (if (unk98==0) → beqz? hmm, target has bnez v0,b3c where v0 = unk98; so the branch jumps to the exit when unk98 != 0, i.e., `if (unk98 == 0) { body }` compiles as bnez→exit. If we write `if (unk98 != 0) goto end; body; end:` — the same bnez. But maybe the block structure differs and reorg's own_fallthrough changes!

That's promising: writing the condition inverted with a goto could create a different CFG (a label at the end of the case) that affects reorg. Let me try:
```
case 0:
    if (((Unk*)s0)->unk98 != 0) goto end0;
    ...body...
end0:
    break;
```
Hmm, the `end0:` label before break; the break jumps to the epilogue. This might create a label at the end of the body, which could make the fall-through thread different. Let me test.

Also:
e7: `if (unk98) goto end0; ... end0: break;`

Let me score e5, e6, e7.
