---
ts: 2026-11-06T15:25:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Aku7cgomiIU5Vc3JkfXr
---
v1 scored 5 (worse). Others 4.

Time 08:25:23. Item 2 ~15-16 min. I need 20 min. Let me spend ~4 more minutes.

Let me think about whether the target's `bne s0,v1,71c` could come from a test the compiler keeps for a *legitimate* reason: the value t could be 3 or 5 at that point if the CFG merges. We tried the join (s1) but jump threading defeated it.

What if the join's test is not threadable because the test is *not* the first instruction of the join block? E.g., put an instruction before the test that jump.c can't move:
```
sel_test:
    mode = mode;    // hmm
    if (t != 3) ...
```
If the block at sel_test starts with something else, jump threading (which retargets a branch to a block whose first insn is a branch) would fail. But the extra instruction would appear in the code.

Unless the extra instruction is dead and removed after jump.c but before... hmm, jump.c runs before cse; if the extra insn is removed by jump.c itself (dead code), then threading could still happen.

What if the block starts with a *real* instruction that's common? E.g.:
```
sel_test:
    sel = 0;    // dead? no
    if (t != 3) goto sel_094;
```
The `sel = 0` would be an extra insn unless removed.

Hmm.

What about making the join's test compare t against a *different* value such that threading isn't possible? Threading works when the branch target's first insn is a conditional on the same register with a known outcome. If the test were `if ((t & 0xF) != 3)`, jump.c can't thread (it doesn't evaluate). But the andi adds an insn.

OK. Let me also reconsider: maybe the target's bytes can be matched by a *completely different* source structure that happens to produce the same instructions. The residual is only 5 insns. But a MATCH needs exact bytes.

I'm now ~16 min. Let me do 4 more minutes of tries, then finalize.

Ideas remaining:
w1: `if (t != 3) goto sel_094;` with the t==5 test done via a *goto chain* that prevents threading:
```
if (t != 5) goto after;
if (t == 5) {   // redundant, folds
```
w2: `if (t == 5) { if (t != 3) ... }` but with the inner test guarded by `if (t != 5)`:
```
if (t == 5) {
    if (t != 5) goto after;   // folds false
    if (t != 3) ...
```
No.

w3: What if the t==5 test compares t against `(s16)5` stored in a variable that's also used for the t!=3 test... no.

w4: Try `if (t != 3) goto sel_094;` where t is declared `u16`? The function's t is s16. Changing t to u16 changes semantics (negative values). But a1 is compared as s16 elsewhere. Hmm, t is only used in case 5; if t is u16, then `t == 0xC` etc. still work for positive values, but `D_80183478[t]` for negative t would differ (u16 huge). The target's `sra` implies s16. So no.

w5: What about making the test compare t to 3 via `mode`? `if (t != 3 - (mode & 0))` folds.

w6: Use a `goto` from the t==5 branch to a label *after* the test, skipping it, and duplicate the test elsewhere? Changes CFG.

Let me try a couple of "threading blocker" ideas:

x1: put a dead statement at the join that jump.c might not remove before threading but which is removed by flow/cse later:
```
sel_test:
    t = t;      // self-copy; might survive jump.c (removed by cse/flow later)
    if (t != 3) goto sel_094;
```
If `t = t;` survives jump.c (it's an RTL insn), threading is blocked (the target block's first insn is a set, not a branch). Then cse sees `t = t` — does it invalidate the equivalence? If yes, the test survives! And flow deletes the dead self-copy → zero bytes!

Wait, is `t = t;` a "dead set"? flow's dead-code elimination removes `(set t t)`? It's a self-assignment; flow's `dead_code_elim` might remove it. And cse: does it treat `(set t t)` as invalidating t's equivalence? cse's cse_insn for `(set t t)` — it would record that t == t (no-op), possibly deleting it. Hmm. But worth a try!

We tried u3: `do { t = t; } while (0);` inside the if → 4. That's different (the do-while wrap).

Let me try x1: `t = t;` as the first statement at the join label.

x2: `mode = mode;`? mode is used later, not dead.

x3: `sel = sel;`? sel is a variable; a self-copy at the join.

Let me test x1 with the s1 structure (join test).

Actually, simpler: apply the self-copy inside the t==5 block before the test (we did i1: `t = t;` → 4). The join version with the self-copy as the block's first insn might block threading.

Let me construct: take s1 (join structure) and insert `t = t;` at sel_test.

Let me test x1.
