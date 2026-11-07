---
ts: 2026-11-06T12:43:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_42fmjgcEBpDjXZrzwziI
---
Pre-sched order is: call(120) → 122 (v0→pseudo 109) → 124 (store pseudo 109) → 127 (ret=7) → jump. Correct source order.

After sched1 (lreg dump): 120 → 127 → 124 (with 122 folded into the store). So sched1 moved 127 (li) before 124 (store).

Why? Because sched1 found the li's potential hazard higher (or the store wasn't ready due to the v0 dependency on the call — the call's result is available only after... in sched1, a call insn has a latency; the store depends on v0 from the call (via 122), so the store can't be scheduled until the call's result is available. The li has no such dependency, so it's scheduled earlier.

In the target, the store `sw v0,216(s1)` also depends on v0 from the call... and the li writes v0. Hmm, if the li writes v0, it must wait for the store's read (WAR) — but also, since the call writes v0, the li (writing v0) has an anti-dependency on the call itself (WAR with the call's v0 result... no, the store reads v0 first).

So in the target: the store must be scheduled before the li (WAR on v0 between store-read and li-write). Both after the call. The store is ready at time T (call latency), the li is ready immediately but can't go before the store. So the order is forced: store, then li.

In mine: the li (pseudo 73) has no dependency → scheduled early.

So to fix: make the li's destination be v0. Without a pin, impossible... UNLESS the C makes ret's def and the store's value interact through a pseudo that local-alloc ties to v0.

Hmm! What if ret is assigned the value through a copy of the call result?! Like:

```
s32 r = call(...);
unkD8 = r;
ret = 7;    /* still independent */
```

What if instead:

```
ret = 7;
```
where the assignment is *after* the store and gcc's sched1 sees a dependency because ret is a pseudo that... no.

Alternative: make ret's def depend on r:
```
s32 r = call(...);
unkD8 = r;
ret = 7;
```
No.

Hmm, what about making ret's value depend on the *store's address* base? Like `ret = 7;` — no.

OK here's another thought: what if we make the store use `ret`'s future value... no.

Alternatively: prevent sched1 from moving the li by making the block boundary. Sched1 splits regions at basic block boundaries. The arm is one basic block: call, store, li, j. Could we split it? A basic block ends at a jump/label. What if the arm has an `if` at the end that creates a new block? That adds insns.

What about making the `ret = 7` statement into a *separate basic block* via a goto?

```
unkD8 = call(...);
goto SET7;
SET7:
ret = 7;
goto STORE;
```
The label SET7 creates a basic block boundary → sched1 can't move the li before the store. But gcc would delete a label with only one use? A label used by a goto is kept; jump optimization might merge the blocks (it's an unconditional jump to the next insn → deleted, merging blocks). Hmm, jump_optimize deletes jumps to the next insn — which merges the blocks again.

But wait: does the block boundary even prevent reordering? Sched1 works per basic block; if the li is in a different block, yes.

Alternatively `if (1) { ret = 7; }`? gcc folds that away.

Hmm, what about `if (ptr) { ret = 7; } else { ret = 7; }`? Fake and adds code.

What about a `switch`? no.

OK, alternative idea: maybe make sched1 not move the li because of a *scheduling barrier*: a `use` of a value... The classic C-level scheduler barrier is a volatile access or a function call. Hmm.

Wait — maybe there's a neater trick: since sched1 moves the li earlier because it's independent, what if we make the li depend on the *store's address computation*, e.g. ret's value computed from the same base? no.

Let me think about the ARM in the target differently: what if in the target's C, `ret = 7` is written BEFORE the unkD8 store but with the value being a *constant expression* and the store after? No, the RTL order in the target (post-sched) is store, li. Pre-sched order in the target could be li, store and sched1 could have moved the store before the li due to the WAR (if ret were v0, pre-sched order li-then-store would be a WAR violation that sched1 must fix... but the pin makes it v0 from the start, so the RTL has the hard reg; the scheduler respects it).

I'm now fairly convinced: the target's C has the pin (as the src shows) and no lever-free C form can create this dependency.

BUT — wait. What about this trick: assign the constant to a *s16* variable and store it... no.

What about: `ret = 7;` where the constant is loaded from memory? no.

Hmm, what about making ret's live range end at the store by having the store use ret too? I.e., `unkD8` stores the call result AND ret is used... no.

Let me consider the LAST resort trick: make the li's def *after* the store in the RTL by making the store's insn a dependency of the li's def. E.g.:

```
s32 r = call(...);
unkD8 = r;
ret = (r, 7);   /* comma: evaluates r (dead), then 7 */
```
The comma would produce `ret = 7` with r as a dead operand — gcc would optimize `(r, 7)` to just 7 at the tree level, so no RTL dependency.

What about `ret = 7 + (r - r);`? fold-const simplifies to 7 at the tree level too.

`ret = (s32)(0, 7)` no.

OK: what if the store and the li are forced into one statement: `unkD8 = call(...), ret = 7;` — the comma operator at statement level creates a COMPOUND_EXPR; gcc emits both insns. Does that change sched1? No, same RTL.

Alright. Let me reconsider the problem completely: maybe there's a different way to get ret into v0 that doesn't need the WAR: make ret NOT conflict with v0 by ensuring ret is dead at the store points. That is: what if the ret assignment in the arm comes AFTER the store in the RTL — which is the source order! The problem is sched1 moved it. So: prevent sched1 from moving it, or make sched1 move the store first.

sched1's choice at T-2 involved "potential_hazard": the store won the hazard comparison and was moved to the front... and the result was the li first?! 

Wait, maybe I misread the dump. Let me recheck: "ready list at T-2: 124 (1) 127 (1), now 127 124" — hmm, maybe "ready list at T-2" prints the list BEFORE adding the newly-ready insns and "now" prints after. Ugh.

Let me look at the actual final order in the sched dump for block 6 by looking at the .s output of the -ds dump? The sched dump also prints the final RTL. Let me grep the sched dump for the reordered region (the .sched file prints the RTL at the end).

Actually the simplest: the lreg dump shows the order (127 before 124). Fine.

Let me try to make the store's hazard/priority higher: `sched1` orders by priority first (INSN_PRIORITY). Both are 1. Then within the same priority, the hazard decides. The store won the hazard → moved to front. If front = scheduled first, then the store should be first — contradicting the lreg dump.

Unless the lreg dump's order is 124 then 127 and I misread the (insn UID PREV NEXT) triple: `(insn 127 120 124 ...)` means UID=127, PREV=120, NEXT=124. And `(insn 124 127 129 ...)` means UID=124, PREV=127, NEXT=129. So the chain is 120 → 127 → 124 → 129. Yes, 127 before 124.

Hmm, but wait: this dump might be the *pre-sched* order if the lreg dump prints the RTL before... no, lreg runs after sched.

Hmm, but hold on: maybe sched1 did NOT reorder and the change from 122/124 to a direct store happened elsewhere. The pre-sched RTL: 120 (call) → 122 (pseudo109 = v0) → 124 (store pseudo109) → 127 (li) → 129 (jump). Post-sched: 127 before 124 with 122 folded.

So sched1 moved 127 before 124. Confirmed.

So "greater potential hazard" moved 124 to the front of the ready list, and the ready list's front is scheduled LAST? That means the hazard logic *delays* the hazardous insn. Yes! That makes sense: the insn with a greater potential hazard is scheduled later (put at the front of the list where "front" = last to be popped). Hmm, actually the comment says "Move the best insn to be front of the ready list" and the scheduling pops from... whatever.

If the hazard logic DELAYS the store, then to get the store first I'd want the store to have a LOWER hazard. The store's hazard comes from its memory unit blockage. The li is ALU. Hmm.

Since the store's hazard is inherent, and the target also has a store... In the target, the WAR dependency forces the store first regardless of hazard.

OK. Decision time: I've spent ~20 min on item 2. Let me do ONE more experiment: a variant where the arms' `ret = N` is written as `return`-adjacent... 

Actually WAIT. New idea! What if `ret` is assigned in the arm BEFORE the call but the call's result store is the last thing, and the value assigned to ret is used... no.

Hmm, what about the possibility that the target's C uses a *different variable per arm*? E.g.:

```
if (unk70 == 0x28) {
    ...
    unkD8 = call(...);
    ret = 7;
    goto STORE;
}
```
What if instead the arms assign to `ret` via the struct: no.

Let me try one thing: what if the arms' `ret = N;` is replaced by `ret = (s32)(s16)N;`? Doesn't create a dependency.

Alternatively, does the target's `li v0,7` in the j delay slot suggest that the li was scheduled AFTER the jump by reorg (steal from the taken thread)? The j is unconditional; reorg fills its delay slot from the following insn (the store? no, the store is before the j).

Order in target: `sw v0,216(s1)` (1b08), `j` (1b0c), `li v0,7` (1b10). The li is in the j's delay slot, meaning the li was AFTER the jump in the RTL and reorg moved it into the delay slot. So in the target's post-sched RTL, the order is: store, j, li.

With the pin, sched1's RTL would be: store, li, j (WAR forces store before li; the li is independent otherwise, so it might be scheduled anywhere after the store). Then reorg moves the li into the j's delay slot.

In mine: li, j, store → the store got moved into the j's delay slot instead.

Since sched1 orders by priority within the block and the jump has the highest priority (2147483418 = INT_MIN-ish negative?), the jump is scheduled last...

OK: given the mechanism is the WAR on v0, and we can't pin, I think this is a WALL. But wait — maybe there's a pure-C way to make the li write v0: what if `ret`'s value is computed via an expression that gcc puts in v0, like a function call result? No.

Hmm, hold on, one more idea: what if the arm's last statement is not `ret = 7` but a *copy from a variable that lives in v0*? E.g., if there's a variable that's known to be v0 at that point (like the call result temp r), then `ret = r - r + 7`? fold-const... `ret = 7` after `s32 r = call(...)` — what if we write `ret = 7;` as `ret = (s32)(u32)7;`? no.

What if we make ret's assignment `ret = 7;` and ALSO use `r` (the call result) in a way that's free: e.g. `ret = 7;` → no.

OK, one more: what if the store to unkD8 is written through the same pointer as ret's... no.

Let me try the "separate basic block" idea concretely, since it's cheap:

```
unkD8 = call(...);
goto L7;
L7:
ret = 7;
goto STORE;
```
gcc's jump_optimize will delete `goto L7` (jump to next insn) → merging blocks. So no.

What about:
```
if (unk70 == 0x28) { ... unkD8 = call; }
if (unk70 == 0x28) { ret = 7; goto STORE; }
```
This creates two basic blocks separated by the second `if`'s branch. The second `if` re-tests unk70 — but unk70 is reloaded anyway in the target (`lh v1,112(s1)` per arm). Adding a second test per arm adds 2 insns per arm (6 arms = 12). Too many.

Alright: WALL. But before giving up, let me quickly try one more variant: what if `ret = 7` is replaced by a *store to unk2* followed by a return of the reloaded value... no.

Hmm, actually — wait! What about assigning `ret` from a *narrower* type to make the def an extend of v0? For example, if `ret` were `s16` and the call result... no.

Let me look at the time budget: item started 05:30, now ~05:52 (22 min). I need ≥20 min and ≥30 scored tries for a WALL. I have: orig(baseline), c1, c2, c3, c4, c5, c6 = 6 tries (baseline counts? probably as a try). Need 30 scored tries for a WALL. That's a lot of compiles but each is ~10-15 s; 24 more = ~5 min. Hmm, the rule: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I should generate and score ~24 more variants. That's feasible with a script (batch scoring via sc.sh in one command, maybe in background).

But before that, let me try a couple of more promising structural ideas to crack it, because 24 more tries of the same idea is wasteful. Let me think once more...

KEY INSIGHT attempt: the conflict is ret vs v0. What if we eliminate the `ret` variable entirely for the arms by having the STORE block be *inlined* into each arm via cross-jumping? I.e. write each arm as:

```
if (unk70 == 0x28) {
    ...
    unkD8 = call(...);
    ((Unkstruct *)param_1)->unk2 = 7;
    return 7;
}
```
Here `return 7` → `v0 = 7` (hard reg!) → the WAR dependency exists → sched1 puts the store first! And the store to unk2 with a constant: `sh` with an immediate? MIPS `sh` needs a register: gcc would use `li at,7; sh at,2(s1)` or reuse v0: `li v0,7; sh v0,2(s1)`. 

Then jump2's cross-jumping could merge the identical tails across arms... but the tails are `li v0,7; sh v0,2(s1); j` for arm 0x28 and `li v0,10; sh v0,2(s1); j` for 0x29 — the store+jump part is identical, so cross-jump could merge `sh v0,2(s1); j epilogue` into a shared block, giving exactly the target's shape! And the last part `ret = CAST_SIGN(...) + 1; unk2 = ret; return ret;` stays.

That's a very plausible reading of the target: cross-jumping merges the store+return tails. And the early returns `return ret;`... hmm, what about them? In the target they're `j 1e3c` (epilogue) — the same return label.

This is worth trying! Let me construct:

```
if (D_801ED4E4[...] == 0) {
    func_8012CAE4((void *)param_1);
    return ret;      ← what to do here?
}
```

Hmm, the early returns. If the arms do `unk2 = N; return N;`, then the early returns could be `return ret;`... still problematic (uninitialized ret). But if ret is removed entirely, the early returns need something. What did the target do? `j 1e3c` with no value → some expression that costs nothing.

Idea: `return func_8012C1B8();`? no.

Hmm, what if the early returns are `return param_1;`? That's `move v0,a0` — 1 insn.

What if the function returns the *last call's result* implicitly? In C we'd write `return ((s32 (*)(void))func_8012C1B8)();`? no.

Hmm, the target's early return has literally no insn. With the pin + `return ret`, that's natural. Without any pin, the only natural no-insn return is... a pseudo that's already in v0 and dead. 

What if we keep `ret` for the early returns only (uninitialized) and use `unk2 = N; return N;` in the arms? Then ret's live range is entry→early-return (crossing a call) → needs a callee-saved reg → but it's never assigned, so gcc might allocate... it would still allocate a reg (s0? but s0 is used for the address base). Hmm, that could cost the saved reg. Actually with only uses (no defs), the allocator still allocates; a use-only pseudo could be given any reg (even v0!) since it's never defined... it's live from entry. It might conflict with v0 at the uses? At the early returns, v0 is... after a call. Hmm, the use at the return emits `move v0,ret` → if ret gets v0, that's a self-move → deleted. But ret is live from entry to the use, so it conflicts with everything live in between (including v0 at the call).

Ugh.

OK, let me test the "direct return in arms" idea with the early returns as `return 0;` and see the score. If the cross-jump works, we'd get close.

Actually, hold on! Simpler: what if we keep `ret` but assign it in the arms as `ret = 7;` AND ALSO make the store use ret? Hmm no.

Let me just try the direct-return arms. Time: 25 min. Let me be quick: one candidate, then decide.

c7: arms → `((Unkstruct *)param_1)->unk2 = 7; return 7;` (and no goto STORE). Keep the rest.

Wait, but then the final part (line 166-170) is `ret = CAST_SIGN(...)+1; unk2 = ret; return ret;` — keep as is (ret still declared).

The arms would be 6 blocks each doing `sh` + `return`. Let me test.
