---
ts: 2026-11-06T15:48:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_59x3VWcqOOxSYidlkwJY
---
Target (orig) prologue: `lui a0; addiu a0` (D_800AF648) FIRST, then sw s4, lui s4 (D_8019B7B8)...

Mine (c1): the `la a0` moved to after the pointer setup (insn 15-16), and the register allocation shifted (s3 instead of s4 for r).

So the `arg` launder is load-bearing for the prologue position. The mechanism from the comment: the launder blocks combine's substitution of cse's REG_EQUAL constant into the call-site copy and deletes the first set. Without it, combine substitutes the constant into the call and deletes the first set; then the `la` is materialized later (at the call site). With the launder, the first set survives and is materialized first (lowest LUID → first in sched2).

Real-C replacement: need `arg = &D_800AF648;` set early, and the call `func_80052E38(arg)` NOT to have the constant substituted. The C0414 dead-reset: `arg = &D_800AF648; ...; func_80052E38(arg); arg = 0;`? But the dead reset must be immediately after the use, and the use is the call at line 3022. The problem: combine substitutes the REG_EQUAL constant into the call arg copy because arg has a single constant set. If we add a second set (dead reset after the call), the first set is no longer single → combine can't substitute? Hmm, the dead reset is *after* the call, so at the call the value is known.

Actually the issue is cse's REG_EQUAL constant substitution: `arg` is set to a constant symbol; cse replaces uses of arg with the constant, and combine folds the copy. If arg has a second set anywhere, cse can't treat it as a constant globally... but at the call site, the local value table still knows arg == constant (from the dominating set). fold_rtx would substitute. Hmm.

Wait, in the C0414 dead-reset, the mechanism is: cse's forward scan invalidates the equivalence at the second set. The substitution happens in cse itself: when it sees `set (a0) (reg arg)` and arg's equivalence is the constant, it changes to `set (a0) (const)`. With a later dead reset, the equivalence at the time of the call is still valid... unless cse processes backwards? No, cse is forward.

Hmm, but the C0414 doc says it stops cse merging two computations of the same address. In our case, the substitution is of arg into the call arg. Let me look at what happens with a dead reset after the call: `arg = &D_800AF648; func_80052E38(arg); arg = 0;`.

Actually, maybe the trick is different: make arg's *first* set not a constant substitution target by having the value come from something. Hmm.

Let me just test the dead reset variants. Also try setting arg to 0 then to &D_800AF648, etc.

Test variants:
d1: add `arg = 0;` after the call.
d2: `arg = 0;` after the call + move the call later? no.
d3: make arg a second set before: `arg = &D_800AF648; arg = &D_800AF648;`
d4: use a different variable for the call arg: `func_80052E38(&D_800AF648)` directly — then no first set at all (the la is at the call site).
d5: `arg = &D_800AF648; ...; func_80052E38(arg); arg = 0;`

Let me generate these and score, but note the function also has the 2-output launders which also need removal — the score 43 is from all three removed. Let me first isolate the `arg` launder: keep the 2-output launders, remove only arg, and test replacements. Then handle the 2-output ones.

Actually, a cleaner approach: keep c1 (all removed) and try to fix each issue. But the register allocation interacts. Better to work incrementally:
- c1: all 3 removed → 43.
- Remove only `arg` launder (keep 2-output asm) → see score.
- Remove only 2-output launders (keep arg asm) → see score.

Let me do those two.
