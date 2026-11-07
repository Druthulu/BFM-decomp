---
ts: 2026-11-06T18:33:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6IfJEh2UwEVYh1beiLOV
---
Very interesting! In the scheduled RTL, the a1 symbol_ref insn became `(insn 94 77 86 (set (reg:SI 5 a1) (symbol_ref D_801A15AC)))` — i.e., it was **combined into the call-argument move**: the pseudo 77 was coalesced/folded into the call setup, so the a1 materialization is now insn 94 (the call arg move), scheduled at position 12 (after 77, before 86).

So the a1 value's materialization is a separate insn (94) that was scheduled late. In the target, it's at position 3 (after 52 and the second move 92).

Why is our a1 late? sched1's trace: ready list at T-16: "58 (1) 52 (1)" → 58 scheduled; T-17: 52; ... The insn 94 (a1) appears in the ready list at T-7: "94 (1) 86 (1) 77 (1)" → then T-6: 94 89 86 → "insn 89 has a greater potential hazard" → 89; T-7: 94 86 77 → "86 greater hazard" → 86; T-8: 94 77 61 → 94 chosen? Wait the trace lists "now ..." as the next choice.

Let me read the trace: it's printed in reverse (T-1 = last). The ready list entries are the candidates. The final order is the reverse of the T sequence. Anyway.

The key: in the target, the a1 insn (55 in the original RTL, i.e., the symbol_ref pseudo 77's def) was scheduled early. In our build, combine folded 77 into the call arg (insn 94), so the materialization is at the call arg position.

Wait, but the target's asm ALSO has the a1 lui/addiu early (801c) — so in the target, the a1 materialization was early too. Did the target's combine also fold 77 into the call arg? In the target's asm, the a1 pair is at 801c/8020 and the call at 8058. The call arg setup for a1 would be `move a1,a1` (folded). So yes, the target also folded 77 into the call arg, and sched1 placed that insn early.

The difference: with the keepalive asm, the a1 value had an extra use (the asm input), so combine could NOT fold 77 into the call arg (it had 2 uses), and the asm forced its position.

Without the keepalive, combine folds 77 into the call arg move (insn 94), which sched1 schedules late (it's a call arg, and sched1 places call args near the call).

To force it early, I need to prevent combine from folding 77 into the call arg and/or make sched1 place it early.

Hmm! But wait: in the target, the a1 materialization at 801c IS the call arg insn (94) scheduled early by sched1. So the target's sched1 placed insn 94 at position 3. Our sched1 placed it at position 12.

Why the difference? With the keepalive, insn 94 (the call arg) had a dependency? Hmm, in the target's RTL (with keepalive), the call arg insn `(set (reg 5 a1) (symbol_ref ...))` — and the asm insn used a1 (pseudo 77). Let me think: with the keepalive, the RTL has:
- insn 55: (set 77 (symbol_ref D_801A15AC))
- insn 56ish: asm (use 77)
- insn 94: (set (reg 5 a1) (reg 77))

So 77 is a real pseudo used twice (asm + call arg). Combine might fold 77 into the call arg if the asm use didn't exist. With the asm, 77 stays and the call arg insn 94 is `(set (reg 5 a1) (reg 77))` — a copy. sched1 then schedules: the copy 94 depends on 55; the asm depends on 55 and is a barrier; sched1 must place 55 before the asm, and the asm is at its source position (early). So 55 is forced early.

Without the asm, combine folds: insn 94 becomes `(set (reg 5 a1) (symbol_ref))` and 55 is deleted. sched1 places 94 late.

So to force the a1 materialization early with real C, I need a real use of the a1 value that must be scheduled early. Hmm.

What real use? The target's code has a1 used only at the call. So no real use.

Alternative: prevent combine from folding 77 into the call arg by making 77 used twice in real C — e.g., use a1 in another statement. But that adds an insn (the target has none).

Hmm, what about the *asm-free* way: sched1's placement of insn 94 (the call arg with the symbol_ref). Its priority is 1; the ready list order decides. If we could make the call arg insn have a higher priority... its priority is the max over its successors: the call insn's priority is 2147483557 (huge, because it's a call with side effects?). Hmm, the call insn 100 has priority 2147483557 (0x7fffffa5). So insn 94 (a1 arg) should have priority = 1 + priority(successor)? The trace says insn 94 priority 1. Hmm, because the call is a "barrier" insn? Actually the priority computation: `priority = max over successors of (priority(succ) + ...)`? The call's huge priority comes from being a call; the arg insns' priority is 1.

Hmm, in sched.c, `priority()` computes `insn_cost`-based? Let me look: priority = max over SUCC of (priority(succ) + insn_dep_cost)? If the call has a huge priority, the args would inherit... but they show 1. Maybe the call's priority is set to 0x7fffffa5 because it's a call (deadly) and args are excluded.

OK, empirically: the difference between the target and ours is the presence of a *second use* of the a1 pseudo (the asm), which prevents combine from folding and forces sched1 to place the materialization before the asm.

Real-C equivalents: a second *real* use of a1 that costs no insn. What if a1 is used in a store address that's already there? Hmm.

Wait — what about the FIRST call: `func_8012B1B4(s0, (void *)&D_801A1590);` — the a1 there is a different symbol. What if we reuse the same variable for both calls' second args? E.g.:

```
a1 = (s32)&D_801A1590;
func_8012B1B4(s0, (void *)a1);
...
a1 = (s32)&D_801A15AC;
```
Then the second `a1 = ...` has... hmm, a1 is reused; the first assignment is dead after the call. The second assignment is still one use.

What if the call uses the *same* a1 variable: `func_8012B1B4(s0, (void *)a1)` with a1 assigned D_801A1590 before. Then a1 (pseudo) is used by the first call and the second call. But the values differ.

Hmm, what about making the a1 value's materialization have a *dependency* on something early: e.g., a1 = (s32)&D_801A15AC; the symbol_ref is constant.

Let me look at what other keepalive cracks did: "func_801810F8 MATCH: obase set right after pbase and used for the first load too (sched1 then keeps la before the store)". That's a real use.

For our item, the a1 value has no other use. So maybe the crack is impossible → WALL? But wait, maybe there's a different approach: prevent combine from folding 77 into the call arg by making the *call arg* not a simple copy — e.g., use a1 in the call as part of an expression: `func_8012D5E4(a0, a1, a2, a3)` — if a1 is a variable, the arg is `(reg 5 a1) = (reg 77)`, which combine folds. What if we pass `(s32)a1`? same.

What if the call's a1 arg is `a1 + 0`? That would add an insn.

What if a1's value is not a symbol_ref but computed (e.g., `a1 = (s32)&D_801A15AC` is a symbol; if it were a *variable* load, combine couldn't fold it into the call arg — combine can fold a copy but not a load). Hmm! What if a1 is loaded from a global variable? But the target has lui/addiu (a constant address), not a load.

What if a1 = (s32)&D_801A15AC is used in a context where combine can't fold: e.g., if a1 is assigned to another variable first? `s32 t = (s32)&D_801A15AC; a1 = t;` — combine would fold both.

Hmm. Let me think about the ORDER differently: maybe I can make sched1 place the call-arg insn 94 early by adding a dependency between 94 and an early insn. The call arg insn 94 depends on its source (symbol_ref) only. If the a1 value were computed from something early... e.g., `a1 = (s32)&D_801A15AC;` — no.

What if a1's value depends on `a0` (the pinned var)? E.g., `a1 = (s32)&D_801A15AC + ((s32)a0 - (s32)a0)` — launder.

Hmm.

What about the reverse: make the v0 chain *later* instead? The target's order: a1, v0 chain, a2/a3, stores, call. Ours: v0 chain, a1, a2/a3. If I could make the v0 chain scheduled after a1... The v0 chain's first insn is 58 (const 0xFFF60000) — independent.

OK, let me look at the *pinned* version's sched trace (the orig with keepalive) to see how the a1 insn got early: maybe it's not the asm dependency but something else. Let me dump the orig body and diff the sched traces. Quick: run delever_search --try with orig.c --keep, dump, and look at the same block.

Actually, I can reason: with the asm, insn 55 (set 77 sym) exists and the asm uses 77. The asm is placed at its source position (after 55). sched1 must schedule 55 before the asm. Where's the asm in the schedule? The asm is a volatile insn — sched1 treats it as a barrier: it's scheduled at its position with all memory ops after it. The trace would show.

Hmm, this is getting deep. Let me try empirical candidates:

w2: a second real use of a1 that's free: pass a1 to the FIRST call instead of the symbol? No.

w3: `do{}while(0)` around the v0 chain (split after a1) — see the score.
w4: do{}while(0) around the stores.
w5: reorder: put `a2 = ...; a3 = 0x20;` before the v0 chain.
w6: move `a1 = ...` after `v0 = 0xFFF60000;`.
w7: use a temp for the symbol and assign a1 later.
w8: `s32 a1 = (s32)&D_801A15AC;` init at decl inside the if? The decl is at the top; init at decl in the block.

Let me also try the "second use" idea: what if `func_8012D5E4(a0, a1, a2, a3)` is written as `func_8012D5E4(a0, a1, a2, a3)` but with a1 used in the condition too: `if (func_8012D5E4(...) == 1)` — no.

Let me try a batch: w2 (do-while v0 chain), w3 (do-while stores), w4 (a2/a3 before v0), w5 (a1 after v0 const), w6 (do-while a1 assignment alone), w7 (temp), w8 (a1 assignment before a0=s0).

Let me write them.
