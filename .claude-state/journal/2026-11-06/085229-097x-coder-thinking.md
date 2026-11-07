---
ts: 2026-11-06T15:52:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kCT4s7H3FFOiH8djkmgB
---
All 4. Let me check vc4's diff — maybe the residual changed. Actually all say score 4 ORDER, likely the same la position.

Hmm. Let me think about the keepalive: "keepalive 2nd use blocks merge". A keepalive is `__asm__("" : : "r"(arg))` — an asm use. Not allowed (lever kind).

Is there a *real* second use that doesn't add instructions? What if arg is used as the *OT base*? No.

Wait — maybe the original source used `arg` in the call and also as a *base for the D_800AF648 matrix*... Actually, what IS D_800AF648? Let me check the symbol's size/type. It might be a matrix/struct used by func_80052E38. Maybe the original code was `func_80052E38(&D_800AF648);` — no variable.

Hmm, the target's la a0 first strongly suggests the source had a named variable set first and used at the call, with the set surviving. Since combine deletes a single-use constant set, the launder was used. Is there a plain-C way to keep a single-use constant set alive?

Yes! If the variable is *volatile*: `u8 *volatile arg; arg = &D_800AF648; func_80052E38(arg);` — the read of arg becomes a load from the stack (adds insns). Not good.

What if the variable's address is taken? adds.

Hmm, what about `arg` being a *static*? no.

Let me reconsider: maybe we don't need the set to survive; maybe we can get the la first another way. The la at the copy position has a LUID derived from the copy insn. Where is the copy insn? In c2, la at 15-16, before the ot load. So the copy insn's LUID is between vb and ot. That's the `arg = &D_800AF648` statement's position? No, arg is first.

Wait — maybe cse's substitution moved the constant into the *first set* position, i.e., it changed `arg = const` to nothing and `a0 = arg` to `a0 = const`, but the `a0 = const` insn was created at the call copy's position... Let me look at the .rtl or .cse dump to see. Actually, let me look at the flow/rtl dump for c2.

Alternatively, maybe the la at 15-16 IS the first statement but sched2 placed it after the spills/setups because its LUID is... no, sched2 picks lowest LUID first, and the first statement has the lowest LUID. Unless the callee-save spills have even lower LUIDs (prologue insns). The spills are placed first (they're prologue). Then the setups. Then the la.

Hmm, in the target, the la is BEFORE the spills! `addiu sp`; la a0; sw s4; ... So the la has a lower LUID than the spills?? That's odd — prologue spills usually have the lowest LUIDs. Actually sched2 schedules the block; the spills are in the block. The target's la is at position 2, before the spills. So the la's LUID is very low (the first statement's LUID), and sched2's backward scheduler put it first... Actually sched2 is backward: it picks insns and links them before the previous pick; the *last* pick ends up first. The rule from the comment: "rank_for_schedule ties -> the highest LUID is picked first", so the lowest LUID lands first. Prologue spills presumably have high LUIDs (they're emitted at the end of the block by the compiler) and land later. The first statement's set has the lowest LUID → lands first. Yes! So the target's la IS the first statement's set, surviving.

In c2, the la at 15-16 is the *copy* at the call's arg setup; its LUID is higher than the pointer setups? But the pointer setups (r, mlo, mhi, c, va, vb) are source statements 2-7, and the call is statement 9. If the copy's LUID is the call's (9th), it would land after the pointer setups — which it does (after vb). Yes, that matches: la at 15-16 after all the pointer setups, before ot (ot is statement 8, before the call... wait ot is statement 8, the call is 9). Hmm, the la is BEFORE the ot load, so the copy's LUID is between vb (7) and ot (8)? Odd.

Anyway. To get the la first, the set must survive at statement 1's LUID.

Plain C options to keep a single-use constant set alive:
- A second use of the variable that doesn't add code.

What if the second use is in the *OT computation*: `ot = (u32)&D_800A6610[...]` — no relation.

Hmm, what if arg is used as the base of a *dead* store? refused.

What if we make the call take TWO arguments where the second is a no-op copy? C0505 R19: "a call passed at its REAL arity (the extra arg costs 0 bytes — jump2 deletes the no-op copy)". Hmm, that's about the callee's arity.

Wait, maybe the real original source passed the address *directly*: `func_80052E38(&D_800AF648);` and the la first comes from something else? No — if the argument is a direct constant, the la is materialized at the call copy (late). Target has it early.

Unless... the original had `arg = &D_800AF648;` used in the call, and the *call was the first statement*? No, the call is late.

Let me look at this from another angle: what does the .cse dump of c2 show for arg? Let me dump and inspect to see exactly what happens. I have the dump helper pattern. Let me use the keep path.

Actually, time check: item 4 started ~08:52? Let me check. The budget is 20-30 min per item. This is the hard one. Let me be efficient.

Let me look at the cse/combine dump for c2 to understand. But maybe a simpler idea: the target la is a0 = &D_800AF648 and the call's arg copy is deleted (the la IS the arg). In mine, the la is a0 = const (same thing!) just at a different position. So the code is identical except the la's position. To move it earlier, its LUID must be lower. The LUID of the insn comes from the source statement. In mine, cse substituted the constant into the copy at the call; the copy's LUID is derived from... let me find out by looking at the .rtl/.flow dump.

Alternatively: give the la a lower LUID by making the *assignment* be the value that's passed, i.e., prevent the copy substitution so the la stays at the assignment. The assignment is statement 1 → LUID lowest.

So: block the substitution. The substitution is cse's `equiv_constant` of arg into the copy `set a0 = reg arg`. To block it, arg's value must not be a known constant at that point. The launder does it. Plain C: make arg's value not constant but keep the same runtime value — impossible for a symbol.

UNLESS: we use the second-declaration trick in reverse. What if arg is assigned the address via a *different* declaration than the one cse uses? Hmm, the substitution is register→constant, not symbol identity.

Wait wait. Let me re-read the comment: "combine substitutes cse's REG_EQUAL constant into the call-site copy and deletes the first set". So it's COMBINE (not cse) that substitutes the REG_EQUAL constant into the copy. Combine folds `set a0 = reg arg` with arg's REG_EQUAL = (symbol_ref) into `set a0 = symbol_ref`. Then the first set is dead.

So to block combine, we need the copy insn's source reg to not have a REG_EQUAL constant at combine time. A second set of arg would make cse not record REG_EQUAL? Actually cse records REG_EQUAL on the *set* insn. If arg has two sets, each set may carry REG_EQUAL, but the register is not single-set, so cse won't propagate.

We tested a second set after the call (vc6: `arg = &D_800AF648;` after) → still 4. Hmm, because the second set is identical and maybe cse still... or flow deleted it before cse. Let me test a second set of a DIFFERENT value before the call but after the first set? That changes the value. No.

What about a second set that's *conditional*? e.g.
```
arg = &D_800AF648;
if (0) { arg = 0; }   // invented always-false — refused
```
No.

What about making arg's second set a real one: `arg = &D_800AF648; ... arg = 0;` where the 0 set is *after* the call and *used*: e.g. `arg = 0; func_80052E38(arg)`? That would pass 0 — wrong.

Hmm.

What about using arg for something real after the call that requires the value: there is nothing.

OK here's another thought: what if `func_80052E38`'s argument is not `arg` but the call is `func_80052E38(arg)` where arg is declared as a *pointer to a struct* and the call takes `void*`; the cast may prevent the copy substitution? Tested b2 (cast) → 4.

Let me look at the .combine dump to see if there's a REG_EQUAL on the copy and whether a specific spelling blocks it. Let me dump c2 and grep.

Actually, let me first check: what if we pass arg at a *different offset* that folds to the same address, e.g. `func_80052E38(arg + 0)`? fold. `(arg - 0)`? fold.

What if the call's arg is `(void *)&D_800AF648` directly and arg is used elsewhere? Then arg's set... no use.

Hmm, what if we make arg the OT base? The OT base is `&D_800A6610[...]`. Different symbol.

Let me step back. Maybe the intended real-C crack is: `arg` is not needed at all; instead, the *first statement* should be something else that materializes &D_800AF648 into a0 early. What if the original source had `func_80052E38(&D_800AF648);` and the target's early la is because the *call's arg copy* was hoisted by sched2 to the top? But sched2 wouldn't hoist a la across the call... Actually sched2 CAN move the arg setup earlier if dependencies allow. In c2, the la is at 15-16, not at the call — so sched2 DID hoist it above the ot load. Could it hoist it further to position 1? It's blocked by something? The la has no dependencies except its own LUID; sched2's placement depends on rank (LUID). So no.

Hmm, but in the target the la is at position 2 — before the spills. That's exactly the first-statement LUID.

I wonder if the real source had `arg` as a *parameter*? No, void(void).

What about `arg` being a *global variable*? Then the la would be a load.

Let me try the "second declaration" trick differently: assign arg from the second declaration, and use the first declaration at the call:
```
arg = (u8 *)&D_800AF648_b;   /* second decl */
func_80052E38(&D_800AF648);  /* first decl direct */
```
Then arg's set is dead (no use) → deleted. No.

What if:
```
arg = (u8 *)&D_800AF648_b;
func_80052E38(arg);
```
cse: arg's REG_EQUAL = symbol_ref(D_800AF648) — same string as the first decl? The comment says "its SYMBOL_REF string is a different pointer" — because the asm label creates a separate SYMBOL_REF node with the same string? Hmm, if the strings are different pointers, rtx_equal_p for SYMBOL_REF compares the string pointer, so they're NOT equal! So `arg`'s REG_EQUAL symbol_ref_b is not equal to the call's... wait, the call uses arg (a reg), not a symbol. Combine substitutes arg's REG_EQUAL (symbol_ref_b) into the copy: `set a0 = symbol_ref_b`. Then the arg set is dead → deleted. The la materializes symbol_ref_b at the copy → same late position. So no.

Unless the call uses the *first* declaration directly while arg (second decl) is used elsewhere. No.

Hmm, let me look at the actual .combine dump for c2 to see the REG_EQUAL and think.

Actually — maybe simpler: what if we make arg's set be a *copy from a variable* that holds the symbol? No.

Let me look at the target more: is there anything at the very top that suggests the original source? `addiu sp,sp,-112; lui a0; addiu a0` — the la is literally the first insn after the frame adjustment. 

Hmm, one more idea: make the call's argument *not* a constant by passing arg through a `volatile` *dummy* that costs nothing? no.

What about `func_80052E38((void *)arg);` where arg is `u8 *` — tested.

What if arg is `u32` instead of a pointer? `u32 arg; arg = (u32)&D_800AF648; func_80052E38((void *)arg);` — combine folds the cast+constant. Same.

Hmm. Let me test whether a *second use in the call delay slot* is possible: the target's delay slot is `addu s8,v0,v1` (the OT). Not arg.

OK, time to check the cse/combine dump. Let me dump c2.
