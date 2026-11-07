---
ts: 2026-11-06T02:03:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7egr0QbOgs8424zBQlj2
---
Started 18:28, now 19:02 → 34 minutes on item 1, with ~32 scored tries (nopin + vA + v1-v8 + w1-w20 + orig control = 31ish). That satisfies a WALL (≥20 min, ≥30 scored tries). But before declaring, let me make a couple of targeted attempts based on the strongest insight.

Actually — wait. Let me reconsider the v1/w15 result (score 2, 138 ins). The only diff is the order of the two stores at the very end. What if the ORIGINAL source order is sh;sw (target) but with the store's *insn* preceded by a nop or the sh... 

Alternatively, what if we can make the zero block's store not merge by placing the `sh` between the `li` and the `sw` in a way that... no.

Let me look at the v1 residual from the other direction: mine = li; sw; sh; target = li; sh; sw. If I could get the scheduler to swap the stores in v1, we'd be done. sched1 and sched2 both preserve. What if the two stores are made *dependent* in a way that forces sh first? E.g., make the sh's address depend on the sw's value? No.

What if the sh store is written as a separate *basic block* before the sw? Like `if (1) sh=0;` — the if folds. Hmm.

What if we write the sh store BEFORE the call func_8012B200 and the sw after? Target order: call; li; sh; sw. The sh must be after the call.

What if the source order is sh; sw but the *store* is in a `do-while` whose body also contains the sh, and the do-while changes the order? w1 (do-while around sh+store, order sh;store) gave 136 (merged). Because the store is still last.

Hmm.

OK here's one more idea, based on the C0535 note: "do{}while(0) splits cse1 EBB". The cross-jump at jump2 might be prevented if the store is in a different basic block than the label's block... but the label is the function exit; the store's block ends at the label regardless.

Let me try a fundamentally different approach: make the zero block's store *conditional* in a way that produces the same bytes but a different block structure. E.g.:
```
if (t == 0) { ... }  // instead of goto
```
Hmm.

Actually, let me reconsider the possibility that the original source had the store in the `zero:` block AND the block was NOT the fall-through predecessor of the epilogue because the epilogue label was preceded by a *jump from another block that was physically placed after zero*. I.e., the RTL block order could be: dec; zero; [a block with just a jump to epilogue]? No, the epilogue label is at the end.

Hmm, what if the original function had a trailing block after zero that is empty (e.g., a label with no code)? The label would be a CODE_LABEL (skipped by find_cross_jump). No help.

What if the original had a trailing `if (0) { ... }` that emits nothing?

I think the WALL is the honest outcome for item 1. But wait — the item's target might have been produced by a source where the zero block's last statement was `unk1C = 0x1D;` and the block ended with a `return;` that was NOT elided because... let me test one specific thing: what if the zero block's return is `return;` but the function's last statement is something else AFTER the zero block that emits a jump to the epilogue? E.g.:

```
zero:
   ...
   unk1C = 0x1D;
   return;
dead:
   ...
```
No.

Hmm, what if the LAST statement of the function is a `return;` that is reachable and the zero block's `return;` is not last? Then the zero block's jump survives (not jump-to-next), and the final block's return is elided. But the target's zero block is last...

Wait, actually: the layout! What if the source has the zero block NOT last, but the compiler's jump optimization REORDERS blocks so zero ends up last? gcc 2.7.2's jump pass does "delete jumps to next" and "jump threading" but not block reordering. Hmm, but there's `thread_jumps` which can redirect jumps, not reorder.

OK, decision: record a WALL for item 1 with the mechanism (jump2 fall-through minimum=1; the only lever-free shapes that break it move the store before the sh, leaving a 2-insn order residual; sched1/sched2 preserve source order). Best = 2 (v1/w15, 138 ins).

Wait — but actually, "best = lowest score of a lever-free body" — best 2.

Hmm, but hold on: before giving up, let me reconsider whether the target might have the store order li; sh; sw coming from a source where the sw is *after* the sh but the block ends with a jump that survives. What if the zero block's `return;` is written INSIDE a do-while that also contains the store, and the do-while's back-edge jump keeps the block from falling through? w1 was do-while around sh+store with no return. Let me try do-while around {store; return;}. And do-while around the whole zero tail with a `return` inside. The loop's structure might keep a jump.

Let me try a few more (cheap): 
x1: do { sh; store; return; } while (0)
x2: do { store; return; } while (0)  (store before sh? no)
x3: `if (t == 0) { ...; store; return; }` — restructure the zero block as an if instead of goto, with the return inside.
x4: goto-based with the return inside a do-while.
x5: put `return;` inside `if (1) {}`? 

Let me also try: swap the order of the zero block and dec block in source (zero before dec). That changes layout; probably big residual, but the merge would be prevented. Not target.

Let me run x1-x4.
