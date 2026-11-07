---
ts: 2026-11-06T11:34:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lE46TFJKVK4s8wK99xWy
---
So the diffs:
1. mine[60] nop vs target li v0,3 — the delay slot of the outer bne needs the `li v0,3` copy (lever 3/4 issue). Without `+ zr`, one of the `n = 3` got eaten. Actually target has `li v0,3` at 60; mine has nop. This is the RC-12 opaque copy issue.
2. mine[73] beqz v0,100c vs target beqz v0,1010 — branch target differs (offsets differ due to extra insn).
3. mine[83] beqz v0,ff0 vs target beqz v0,ff8; target also has addiu v0,s1,1 at 84 (delay slot fill from branch target). This is lever 5 (barrier).
4. mine[93] bnez v0,fc0 vs target bnez at 94 (offset shift).
5. mine has extra lui at + sw s0,0(at) at 128-129 that target has later at 134-135 — the D_801151D0 store ordering (lever 6, barrier).

So the count: mine 143, target 144. The missing insn is the `addiu v0,s1,1` in the beqz delay slot (target[84]) — mine has nothing there (nop or skipped). Actually mine[83] beqz with delay slot... Let me think. And the store position shift.

So lever-free is close: score 9. To reach 0 I need to reproduce:
(a) the `li v0,3` in the outer bne delay slot (opaque copy) — without the zr pin.
(b) the duplicated `addiu v0,s1,1` in the inner beqz delay slot (needs reorg to not fill from fall-through; barrier did it).
(c) the D_801151D0 store to be scheduled after the OT-link RMW (needs the memory barrier).

These are exactly the three load-bearing levers. Can real C reproduce them?

Let me think about each.

(a) `li v0,3` opaque copy: `n = 3 + zr`. Without zr, `n = 3` is a plain constant; cross-jump can merge the two `n=3` arms and reorg copies the insn into the delay slot. Actually the comment says "being the SAME rtx in both arms it stays cross-jumpable, so the outer bne targets the shared insn and reorg COPIES it into the delay slot." Wait that's the `+zr` version. Without zr, "the noop-move deletion eats the outer else arm entirely (its value is already in $v0 from the compare constant)". So `n=3` plain gets deleted; the delay slot becomes nop. To get `li v0,3` there, need the value to be a non-constant rtx.

Could use a variable: e.g. `s32 three = 3;` then `n = three` in both arms? Then it's a register copy, cross-jumpable, and reorg could copy. But that would add a pseudo and might produce `move` not `li`. Hmm. Actually the target has `li v0,3` — loading constant 3 into v0 in the delay slot. So the shared insn is `li v0,3` (a constant load) and reorg copies it into the delay slot. With plain `n = 3` in both arms, gcc's noop-move deletion (or constant propagation) removes the redundant load since v0 already = 3 from the compare? Wait the compare `D_80115126 == 3` puts 3 in a reg, and D_8011511A == 3 too. Hmm.

Let me try a real-C move: make the two `n = 3` sites share via a temp declared and assigned once? But they're in different branches.

Alternative real-C: `n = 3;` before the if, then override in the else? Like:
```
n = 3;
if (D_80115126 == 3) {
    if (D_8011511A == 3) { ot = ...; }
    else { n = 4; }
}
```
Then n=3 is a single insn before the branch, not in the delay slot. Different.

Hmm. The catalog C0414 (dead-reset cse-breaker) and C0535 (do-while splits cse1 EBB). Let me check the cookbook for moves relevant to opaque-copy/delay-slot.

Actually, maybe try: use a non-constant that folds to 3, e.g. `n = (s16)3` or `n = 3u`? Width changes might create a different rtx. Or `n = 3; n = n + 0;`? That's identity (launder-like), not allowed as a crack? "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". `n + 0` is identity too, so no.

What about reading a value that is provably 3 from memory? No.

Consider `n = D_8011511A` in the inner-true arm? No, that's the condition ==3.

Hmm, maybe `n = 3` with a different type: `n = (s32)3` same.

Let me think about what "real C" could yield `(plus (reg 0) 3)`: an opaque copy. The only real C that yields an add of 0+3 is `x + 3` where x is a zero register... not real C.

Alternatively, restructure so that the constant load isn't deleted: e.g., make the else arm do `n = 4 - 1`? That folds to 3 at compile time (constant folding) -> same constant.

What if `n = 3` and the value is used in a context that prevents noop-move deletion, e.g., `n = 3;` then `cnt = n;`... same.

Actually the noop-move deletion: when both arms assign the same constant 3 to the same pseudo, and v0 already holds 3 (from the comparison constant), gcc deletes the assignment as a redundant move. To keep it, the value must not be recognized as already in v0. 

Maybe use a loop-carried or a different variable? Hmm.

Let me look at what other shards did for similar "RC-12 opaque copy" cracks. Let me grep moves.md for "RC-12" or "opaque". Also grep for "li v0" / delay slot.

Let me grep moves.md for "opaque" and "zr".
