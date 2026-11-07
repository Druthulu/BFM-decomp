---
ts: 2026-11-06T15:50:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ons4KUIOWBUoqpg35RbC
---
Excellent! The technique: a second declaration of the same symbol with a different *decl* → its SYMBOL_REF string is a different pointer → cse doesn't unify. That's a real-C technique (declaration-only).

So for our `arg` launder: `arg = &D_800AF648;` then `func_80052E38(arg);` — the launder blocks the substitution. A real-C alternative: make arg's value not cse-substitutable by using a second declaration? The set is `arg = &D_800AF648;` and the call uses arg. The substitution is of the constant into the call copy. If the symbol_ref for the set and the use are the same, cse substitutes. But if the use is `arg` (a register), not a symbol... The substitution happens because arg's REG_EQUAL is the constant symbol; cse replaces the *use of arg* in the copy `a0 = arg` with the constant. Hmm, that's cse's `equiv_constant` substitution of a register, independent of the symbol identity. So a second declaration won't help here.

Hmm. Wait, the launder makes arg's value opaque. What if we set arg from a second declaration of the symbol? `arg = (u8 *)&D_800AF648_b;` — arg's REG_EQUAL would be the *other* symbol_ref, still a constant → substitution still happens (the use `a0 = arg` becomes `a0 = &D_800AF648_b`). So the la would be materialized at the call site. Not helpful.

We need arg's set to survive and be materialized early. Alternative: make arg's value not constant, but still &D_800AF648. 

Hmm — what about making the *call* take the constant directly but keeping the early la via a *different* variable that is used somewhere? The target's early `la a0` is the value passed to func_80052E38 (a0 is the arg register, and it's not clobbered before the call?). Actually the call is at the end of the prologue; the `la a0` at the top sets a0 early, and nothing clobbers a0 before the call. So the target's compiler kept a0 loaded early because the arg's set had the lowest LUID and was scheduled first (sched2 backward list picks lowest LUID first).

So we need a first-statement set that survives to sched2. Options:
1. Make arg live (used after the call) — but then combine/cse may still substitute the call copy.
2. Use a *volatile*-ish opaque assignment.

Let me test: `arg = &D_800AF648;` used at the call AND after (e.g., `arg = 0;` — dead, or a real use).

Actually, what if we make arg a `u8 *` and set it, then the call, then use arg in the loop as a base for something? That adds code.

Alternatively: assign arg to the *address of a local* and pass... no.

Let me think about the launder's exact RTL effect: `arg = &sym; asm("" : "=r"(arg) : "0"(arg));`. The asm creates a new pseudo for arg with unknown value, tied to the same reg. Then the call copies arg to a0. The first set `arg = &sym` is now used by the asm (not dead), so it survives; its LUID is low → la early. The asm itself is priority 1 and doesn't materialize.

Plain-C equivalent that makes the set non-dead without extra insns: an asm is the only zero-cost "use". Hmm. But maybe a *use in a later dead expression* that flow deletes? E.g. `arg = &sym; ... call(arg); ...` and later `if (arg) {}`? adds branch.

Hmm, what about `*(u8 *)arg;`? load.

What about passing arg to the call *twice*: `func_80052E38(arg)` only takes one arg.

Let me look at the problem from the target's perspective: maybe the target's first `la a0` is NOT from `arg = &D_800AF648` but from the call's argument being materialized early because the *call itself* is scheduled... no, the call is at insn ~30.

Wait, actually the target's `la a0` at insn 1-2 is immediately followed by callee-save spills. sched2 schedules the whole block; the la has the lowest LUID (first statement) and lands first. In mine (c2), the la is at insn 15-16 — after the pointer setups. The first statements in the C are:
```
arg = &D_800AF648;
r = &D_8019B7B8;
mlo = 0xFFFFFF;
...
```
The la for arg is deleted (substituted), and then materialized where a0 is set (at the call copy). But the call is at line 3022 (after the pointer setup and the OT computation). So the la lands there.

If the la set survived, it would be at the top. So we need the first set to survive.

Real C idea: make `arg` used in a way that forces its value *and* is zero-cost. What about using arg as the base of the call via a *pointer cast*: `func_80052E38((void *)(arg + 0))`? fold.

What about assigning arg *after* the pointer setup but before the call? The la would still be late.

Hmm, is there another way to get the la at the very top? The la's position in sched2 depends on LUID. If the `la` is materialized at the call copy, its LUID is the call's LUID (late). So no.

What if we pass the *symbol directly* to the call: `func_80052E38(&D_800AF648);` — the constant is materialized at the call (late). Mine c2 has arg variable; same.

OK, so we need the first set to survive. What plain-C use can keep it alive at zero cost? 

Idea: `arg = &D_800AF648;` and then the call is *not* the only use: use arg in an expression whose result is discarded but that flow/combine can delete *after* the set... e.g. `arg = arg;`? identity (disallowed and deleted).

Idea: pass arg to the call and also use it in the loop condition? adds.

Hmm, wait. Maybe the real source had a different structure: perhaps `arg` was a *parameter* or the address was used for something else. But the signature is void(void), fixed.

Let me look at the moves for "argcopy-hoist" / prologue la. There's "sched1-argcopy-hoist" wall entries. And maybe a known crack for a prologue `la a0` first.

Search moves for "la \$a0" or "prologue".
