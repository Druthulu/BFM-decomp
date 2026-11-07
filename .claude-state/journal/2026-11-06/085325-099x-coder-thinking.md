---
ts: 2026-11-06T15:53:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TlSjbbgaHmedN0lBBAZi
---
The dump is huge. This is taking time. Let me step back and consider the budget. Item 4 is hard; I have ~20-30 min per item. I've been on it maybe 15 min.

Let me try a few more promising ideas for the arg launder, then move on if needed. The item can be PARTIAL if I keep the pins (which are not the row kind) but must remove the launders. Actually the row kind is only "launder". So PARTIAL is only for keeping some launders. I need MATCH to fully crack.

Hmm wait — the results row: result MATCH (win.c scores 0) | PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers). If I can't remove the arg launder, I could keep it and score 0 → PARTIAL:launder. But the goal is a MATCH.

Let me think differently about the arg launder. What if the `arg` variable is *not* a local but the address is used in the call *and* the variable is declared at the top with an initializer? Same.

What if we make the set survive by making it a *memory* access that cse keeps? no.

New idea: what if the call's argument is `arg` and arg is assigned from `&D_800AF648` where D_800AF648 is declared with a *different type* such that the address expression is not a simple constant? E.g. declare `extern u8 D_800AF648[];` (array) vs `extern u8 D_800AF648;` (object) — both give symbol_ref. 

What about `extern u8 D_800AF648;` and `arg = &D_800AF648;` where the type is `void *`? Same.

Hmm, what if arg is assigned `(u8 *)&D_800AF648` and the call is `func_80052E38((void *)arg)` — combine still folds.

What if the call argument is `(void *)((u32)arg & 0xFFFFFFFF)`? identity.

OK here's a thought: what if we make the *first set* be used by the OT computation legitimately? The OT base `ot = (u32)&D_800A6610[...]` — different symbol.

What if we use arg as a *temporary* in the pointer setup, e.g. `arg = &D_800AF648;` then reuse the variable for something else (a second set) and still pass it to the call? No.

Hmm, let me look at the target's register usage: `la a0` early, and a0 is not clobbered before the call (all the setup uses v0,v1,s*). So a0 holds the arg. If the C had a second use of arg, it'd need another reg or a reload.

Wait — maybe the original source didn't have an `arg` variable at all; maybe the *call* was placed first in the source and then moved? No.

Alternatively, maybe the original used a *different function call* early that takes &D_800AF648: e.g. `func_80052E38(&D_800AF648)` where func_80052E38 is called with the constant directly — the la would be at the call. Unless the call is the first statement... 

Let me test: move the call to the first statement (before r = ...) with the direct constant, and see if the rest still matches (the OT setup would then be after the call — the target has ot computed before the call: `sll v0,v0,0xe; jal` — the ot load is before the call in the target). If the call were first in C, the ot would be after → wrong.

Hmm, but wait: the target's call at insn 35 has the OT computation just before it. The source order has ot then call. So the call is last in the prologue. So the la must be a *separate* early set.

OK, let me try the keepalive-style *real* second use: what if `arg` is passed to the call AND used in the loop for the OT? Like `ot = (u32)arg + ...`? wrong address.

I think I should try the second-declaration trick for the *set* vs the *call*: 
```
arg = (u8 *)&D_800AF648;      /* first decl */
func_80052E38((u8 *)&D_800AF648_b);   /* second decl, direct */
```
Then arg's set is dead → deleted. No.

What if:
```
arg = (u8 *)&D_800AF648;      /* first decl */
func_80052E38(arg);
```
and declare D_800AF648_b and use it in the *assignment*:
```
arg = (u8 *)&D_800AF648_b;
func_80052E38(arg);
```
As analyzed, combine substitutes symbol_ref_b → la at copy (late). Same.

Unless rtx_equal_p for the copy's REG_EQUAL symbol_ref_b vs... no, the substitution always happens for a single-set constant register.

So the ONLY way to keep the set alive is to make arg multi-set or make the value non-constant.

Multi-set: what if arg is assigned twice with *different* constants but the value at the call is the right one? E.g.
```
arg = &D_800AF648;
arg = &D_800AF648;   /* same */
```
Tested (d2 earlier for item 2; for item 4 not). Let me test `arg = &D_800AF648; arg = &D_800AF648;` — cse sees 2 sets, each REG_EQUAL same constant; the copy might still fold. Let me test.

Also test a conditional second set that's real: `if (D_800B9A02) arg = &D_800AF648;`? changes semantics/adds branch.

Hmm, what about an *unconditional* second set with a different expression that evaluates to the same address: `arg = &D_800AF648; arg = (u8 *)((u32)&D_800AF648);` — the second set's value is the constant too; combine folds. The first set is dead (overwritten). No.

What if the first set is the *used* one and the second set is after the call (dead)? Tested vc6 → 4.

Wait, why didn't vc6 work? The second set after the call: `func_80052E38(arg); arg = &D_800AF648;`. The second set is dead (arg never used after) → flow deletes it before cse. So no effect.

What if the second set is *used* by something real? E.g. `arg = &D_800AF648;` ... call(arg); ... `if (arg != 0) ...`? adds branch.

I'm stuck on the arg launder with plain C. Let me look at the moves for "D_800AF648" — line 5305 in src/ov_SC03_099 has the second-declaration trick for the *two calls* case (address materialized afresh per call). Our case is different (one call, early materialization).

Let me reconsider whether the early la might be achievable by moving the `arg` assignment statement's *position* in the source. The la at the copy (15-16) is after the pointer setups. What if the copy insn's LUID is tied to the *call statement*; moving the call statement earlier (but after ot) doesn't help much. What if we move the call *before* the pointer setups but keep ot before it? E.g.:
```
arg = &D_800AF648;
ot = ...;
func_80052E38(arg);
r = ...;
```
Then the call (and its la copy) is early — before the r/mlo/mhi setups. The target has the la at position 2 and the call at ~35 (after the setups). If the call moves early, the call would be at position ~2 too — wrong.

Unless sched2 reorders the call later? Calls have dependencies; sched2 can move other insns before the call if no deps. The call's position relative to the setups... sched1/sched2 can move insns across a call if no dependencies? Actually sched treats calls as barriers? In gcc 2.7.2 sched, a call is a normal insn with memory clobbers; sched2 can move independent insns across it? I believe sched2 does not move insns across calls easily (call has REG_UNSPECIFIED side effects). Hmm.

Let me just test: move the call (and arg assignment) right after ot, before the pointer setup? But the pointer setup must be before the loop; moving r/mlo/mhi/c/va/vb after the call is fine semantically. Let me test a variant where the source order is:
```
arg = &D_800AF648;
ot = ...;
func_80052E38(arg);
r = ...; mlo...; c...; va...; vb...;
for ...
```
Hmm, but `ot` depends on D_800B9A02 only. The target's ot computation is right before the call (`sll v0,v0,0xe` then jal). The pointer setups come before ot in the target? Target insns: la a0, spills, lui/lhu D_800B9A02, lui/addiu D_800A6610, sw ra..., sll v0,0xe, jal. The r/mlo/mhi/c/va/vb setups: where are they? lui s4 (D_8019B7B8) at insn 5-8, lui s3 0xff, lui s7 0xff00, addiu s2/s5/s6 at 15-21 — these are the pointer setups. Then D_800B9A02 load, D_800A6610, spills, sll, jal. So the order matches the source: arg, r, mlo, mhi, c/va/vb (addiu s2/s5/s6), ot, call.

So the call is last. The la a0 is first. So the la's LUID is the *arg assignment*'s LUID (statement 1) — the set survived.

Therefore the target source had a *non-foldable* set. The launder is one way. Another way: make arg's value come from something non-constant... 

OH WAIT. What if the original source was:
```
u8 *arg;
arg = (u8 *)&D_800AF648;
...
func_80052E38(arg);
```
and D_800AF648 was *not* a symbol but a local/static? no.

Hmm, hold on — what if the original source passed `arg` to the call *by reference* or used it in a way that cse couldn't fold because the call might modify memory? The call `func_80052E38(arg)` — combine folding the copy is about the register, not memory.

Let me try the `volatile` idea just to see the cost:
```
volatile u8 *arg;
arg = &D_800AF648;
func_80052E38((void *)arg);
```
A volatile-qualified pointer: `volatile u8 *arg` means the pointed-to data is volatile, not the pointer. The assignment/read of the pointer itself isn't volatile. So no effect.
`u8 * volatile arg;` means the pointer is volatile → each read is a load from memory. That adds a load and a store. Probably 2+ insns.

Let me test `u8 *volatile arg;` and see. Also test the double-set.

Also, what about making the call take the address of a *volatile-qualified* object: `func_80052E38((void *)&D_800AF648);` where D_800AF648 is declared `volatile u8`? The volatile cast makes the address a volatile MEM? No, the address itself isn't volatile. Hmm, but `(void *)(volatile u8 *)&D_800AF648` — a cast of an address; combine still folds.

Let me test a batch: double set, volatile pointer, and a "second use in a cast that survives" (e.g. `func_80052E38(arg); ... if ((u32)arg) {}` no).

Actually — here's a real idea: the target's `la a0` early and a0 live until the call. What if the C passes `arg` to the call AND `arg` is also used as the *base of the OT address* in a way that folds to the same value? The OT is D_800A6610 — different symbol.

Hmm, what if the C uses `arg` in the loop condition? no.

Let me just test volatile and double-set.
