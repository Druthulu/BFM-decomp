---
ts: 2026-11-06T15:50:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DM2NgdDJ2WXPUgR0tIe6
---
The target's `la a0` is only at insn 2-4, used by the call at insn ~? (the call func_80052E38). So it's a single use.

To keep it early, need a second use of the pseudo OR a way to block combine's merge. 

Hmm, what about using a *different variable* for the call and keeping arg live via a zero-cost construct? Not obvious.

Alternative: make the call's argument not a simple copy by making the argument a *computed expression* that combine can't fold into the call: e.g. `func_80052E38(arg + (n & 0))` — identity, disallowed.

Hmm.

Wait — maybe the real source is different: maybe `arg` is passed to `func_80052E38` and ALSO used later as the OT base? No, ot is D_800A6610.

Let me look at the actual target's first instructions: `la a0, D_800AF648` then spills, then the setup. In the C, `arg = &D_800AF648;` is the first statement, and the call is the last of the prologue. The target materializes a0 early and keeps it until the call. Why would gcc do that? Because the assignment `arg = &D_800AF648` is the first insn and sched2 puts it first (lowest LUID). That requires the set to survive (not be substituted).

With plain C, combine substitutes. So the launder is the only way? But maybe a plain-C "second declaration" trick: if the call's argument is `&D_800AF648_b` (second decl) and arg = &D_800AF648 (first decl), then cse sees two different symbol_refs; the copy `a0 = arg` has arg's REG_EQUAL = first symbol; cse substitutes it into the copy → `a0 = &D_800AF648` (first symbol). Then combine: the set arg = &D_800AF648 is still dead? The call uses a0 = const, so yes arg's set is dead and deleted. Hmm.

What if the call is passed the *second* symbol directly and arg is set to the *first* symbol and used... no use.

OK here's another thought: what if we make `arg` an *argument to the call in a way that requires the register*, e.g. `func_80052E38(arg)` where arg is declared `volatile u8 *`? A volatile pointer variable: reading it is a load from the stack; the assignment `arg = &sym` is a store. That adds insns.

What about `register u8 *arg`? register keyword is disallowed by constraints ("no `register` vars"). Hmm, but the pins use register. The constraint says no register vars. So no.

What about declaring arg as `u8 *const arg = &D_800AF648;`? The const might prevent the substitution? Probably not.

Let me test a few:
- `u8 *const arg = &D_800AF648;` (init at decl, remove the assignment).
- Make arg a `void *`?
- Use arg twice: `func_80052E38(arg); func_80052E38(arg);` would add a call — no.

Hmm, wait. Maybe the answer is the *second use* being the argument copy itself plus something zero-cost like the `arg` variable used in a cast that cse can't fold: `func_80052E38((void *)((u32)arg));` — combine might fold to constant. Test.

Let me test several and check scores. Note the 2-output launders are still in c2, so the score baseline is 4 (la position only).

Variants:
- b1: `u8 *const arg = &D_800AF648;` at decl, drop `arg = ...` statement.
- b2: call with `(void *)((u32)arg)`.
- b3: call with `(u8 *)((u32)arg + 0)`.
- b4: set arg, then `func_80052E38(arg);` and add a dead reset `arg = 0;` BEFORE the call? no.

Hmm, let me think about the keepalive mechanism: "keepalive 2nd use blocks merge (best 4)". A keepalive is `__asm__("" : : "r"(x))` — a use. Not allowed.

What about a *store through arg* that's real? no.

Let me look at the C0505 catalog entry: "A parameter copy `T x = argN;` deleted (R35) or moved to a later plain statement". Not applicable.

What about "a call passed at its REAL arity (the extra arg costs 0 bytes — jump2 deletes the no-op copy, jump.c:425-462) (R19)"? If func_80052E38 takes 2 args, passing a second arg could change the arg copy handling. But we don't know the arity. The declaration is `extern void func_80052E38(void *);` — one arg. Changing the declaration (outside the body?) — the constraint says no signature or decl change outside the body; the extern decl is inside the body (function-scope extern), so I could change it? But that would be inventing a call at wrong arity — risky and likely wrong.

Hmm, let me reconsider. Maybe there's a completely different real-C structure: what if `arg` is set from a *parameter-like* value... no.

Let me test b1-b3 quickly.
