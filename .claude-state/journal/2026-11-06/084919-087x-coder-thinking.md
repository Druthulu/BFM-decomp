---
ts: 2026-11-06T15:49:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9A5BH7GLQPaHeZY6p38E
---
Only the `la a0` position differs: target has it at insn 1-2 (first), mine at 15-16 (after the pointer setups). The launder makes the first set survive and be scheduled first.

So I need `arg = &D_800AF648;` to materialize FIRST in the prologue. The launder blocks combine's substitution. Real-C replacement:

Option: dead reset after the call: `arg = 0;` — but the substitution happens before/at the call. Let me test.

Option: make arg used again after the call so it can't be deleted. E.g. `arg = &D_800AF648; ...; func_80052E38(arg);` and later use arg: `func_80052E38(arg)` again? That adds a call.

Hmm, the mechanism per comment: combine substitutes cse's REG_EQUAL constant into the call-site copy and deletes the first set. With the launder, the asm makes arg's value opaque, so no substitution.

What plain C makes the value opaque? A second set after the call doesn't help at the call.

What if the first set is used *before* the call in a way that forces materialization? E.g. `arg = &D_800AF648; ...` and then use `arg` as an argument to something earlier... 

Actually, the simplest: use `arg` in the loop or somewhere after the call — then the first set is used twice; combine can still substitute both uses with the constant. Hmm.

What about assigning arg from a non-constant expression: `arg = &D_800AF648;` is constant. What if we write `arg = (u8 *)&D_800AF648;` — same.

What if we use the *address of a local copy*? no.

Hmm. Let's think about what combine does: the call insn has `(use (reg a0))` after the arg copy `set a0 = reg arg`. cse set `set a0 = (symbol_ref D_800AF648)` (substituted). combine then sees `set a0 = const` and deletes the earlier `set arg = const` as dead (arg unused). The `la` then materializes at the a0 set position — which is at the call site (late).

To keep the la early, we need a *use* of arg that is not the call arg, or make arg's set not dead. If arg is used later (after the call), the first set can't be deleted, so the la stays at the first set's position (early). But would combine still substitute the call-site copy? If arg is used both at the call and later, cse substitutes the constant at both; combine deletes... no, if arg has another use, the set isn't dead. But the call-site copy could still be `set a0 = const` (substituted), and then arg's set is still needed for the later use. The la would be at arg's set (early) AND at the call site (a0 = const, late) — two `la` pairs? That'd add instructions.

Hmm. Unless the later use is a *dead reset* — `arg = 0;` after the call. Then arg has 2 sets: the first (constant) and the second (0, dead). cse's substitution at the call still happens? The set to 0 doesn't affect the call's use. But combine's dead-set deletion: arg's first set is still dead (the value isn't used after the call because arg is overwritten at the dead reset before any use). flow deletes the dead set. Hmm, so the first set is still dead.

Wait, but C0414 works because cse's equivalence at the second set is invalidated for *merging* expressions. Here we need the set to survive.

Let me just test `arg = 0;` after the call and see.

Other options:
- Use `arg` as a value in the call only, but force materialization: `func_80052E38(arg);` where arg is declared `volatile u8 *`? volatile would force a load.
- Make arg a parameter-like variable? no.
- Set arg from a runtime value that equals &D_800AF648: no.

Hmm, what about using the dead reset BEFORE the call in a way that... no.

Let me test the dead reset after call, and a few others:
a1: `func_80052E38(arg); arg = 0;`
a2: `func_80052E38(arg); arg = &D_800AF648;` (second set)
a3: move the call to after the pointer setup? The target has the la first because arg's set is the first statement. If we reorder the statements so the call is early... no, the la position depends on the set's LUID.

Wait — actually, maybe we can keep the la early by making the call argument *not* be a simple copy: e.g. `func_80052E38(arg + 0)`? identity (disallowed) and might fold.

What about `func_80052E38((void *)arg);` — cast, same.

Hmm. What if arg is assigned via a *second* variable: `arg = &D_800AF648;` and the call uses `arg`; but arg is also the base of a store later? no.

Let me test a1/a2 and see.
