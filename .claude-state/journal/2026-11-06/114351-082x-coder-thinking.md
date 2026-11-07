---
ts: 2026-11-06T18:43:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4TjoBxGu03OXvRnDk9mu
---
birthing_insn_p: an insn setting a register that is live at block start AND `reg_n_sets[i] == 1` (set only once in the function). Such insns get max_priority → scheduled early.

Our a1 materialization: `(set (reg 5 a1) (symbol_ref))` — sets hard reg a1? No, after combine it's `(set (reg:SI 5 a1) ...)`. Is a1 live at block start? No (it's set here). So `bb_live_regs` doesn't have a1 → returns 0. Hmm.

But if the a1 value were a *pseudo* live at block start? no.

The birthing boost applies to insns that set a register live at the block start (a redefinition) — e.g., `v0 = ...` where v0 was live before. In our block, insn 74 (v0 = &D_801A1474) sets v0 which was live (0xFFF60000 used at 66)? Maybe.

Hmm, so if the a1 materialization set a register that was live at block start and set only once, it'd be boosted. a1 is set once in the function (reg_n_sets[a1] == 1) but a1 is not live at block start (it's set in the block).

What if the a1 assignment were *before* the first call (live across)? Then a1 is live at the block start? The block starts after the first call. Hmm.

What if we make a1 set once and live at the block start... no.

OK. Let me now also consider: maybe the target's a1 position is achievable by making the a1 materialization a *birthing insn*: e.g., if a1 were live-in to the block and redefined. In the source: `a1` is assigned after the first call, so not live-in.

I'm going to call item 1 a WALL. Time 11:44; started 11:30 → 14 min. Need 20 min. Hmm.

Let me think if there's anything else worth trying... 

Actually, WAIT. Let me reconsider the problem: maybe I should check whether the *pinned a0* can be used to force the a1 early. The target's order has the two moves (52, 94) first, then a1. In w1, the order is 52, 92, then the v0 chain, then the a1 materialization (94), then a2/a3, stores, call.

What if the a1 materialization is made to depend on the *self-copy* 92 (a0 = a0)? E.g., `a1 = (s32)&D_801A15AC + (a0 - a0)`? launder.

What if `a1` is computed from a0 legitimately? Like `a1 = (s32)&D_801A15AC;` — no.

Hmm, what if the source passes `a1` to the call as the *first* argument (a0) instead? no.

What if we make a1 = (s32)&D_801A15AC and then use `a1` in the comparison of the call result: `if (func_8012D5E4(a0, a1, a2, a3) == 1 && a1 == (s32)&D_801A15AC)` — adds a test.

OK, let me look at this from yet another angle: what if the a1 materialization could be *hoisted above the v0 chain by cse*? cse's `cse_insn` can hoist expressions? cse doesn't move insns.

Let me check the `.combine` dump for w1: which pass folds the symbol into the call arg? If it's combine, maybe preventing the fold with a `do{}while(0)` around the call (C0535 splits the EBB, so cse/combine won't propagate across the block boundary!). C0535: "do{}while(0) splits cse1 EBB" — cse1 works on EBBs; splitting prevents cse/combine from folding across.

Hmm! If I put a do-while(0) boundary between the a1 assignment and the call, combine might not fold 77 into the call arg. But the boundary must not add insns or change the block structure badly.

Actually, C0535's mechanism is about cse1's EBB constant propagation. Let me test: wrap the v0 chain (which includes the call?) in do-while... w2 wrapped the chain but not the call (score 9).

Let me try wrapping the *whole* if-body after the a1 assignment in a do-while(0):
```
a1 = ...;
do {  // !FAKE
   v0 = ...; ...; if (call) ...; func_8002D4C8(...);
} while (0);
```
Hmm, that would put the a1 in block X and everything else in block Y.

Or wrap just the call: `do { if (func(...)==1) {...} func_8002D4C8(...); } while(0);`.

Let me test a few do-while placements:
- d1: do-while around the call+result+final call.
- d2: do-while around the a1 assignment only.
- d3: do-while around the stores + call.

Let me test.
