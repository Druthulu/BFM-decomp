---
ts: 2026-11-06T12:19:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_f5ydIncJ8z70I5ASzOzR
---
Not directly applicable.

Let me think again about the target's shape: maybe I'm wrong that the andi input is the param. Let me check whether `a1v` could be a value born in a1 for another reason: a1 is the "second argument register"; gcc's local-alloc prefers a1 for pseudos that... hmm.

Alternative plan: maybe restructure so gcc naturally emits `andi a1,a1,1` because arg1's pseudo lives in a1 and dies there, with the later uses reading a copy that gcc keeps because the copy is born BEFORE the andi and is live simultaneously. That requires the copy to not be propagatable.

Idea: make the copy from a *different* expression that's still the same value at that point but opaque to gcc: e.g., the copy is `a1s = arg1;` where a1s is declared `volatile`? A volatile local would force memory (bad).

What about using the value twice in one expression: `if (!(arg1 & 1))` then later `arg1 & 0x8000`... 

Hmm, what if we add a real second set that gcc can't fold: the later tests use `a1s = arg1 + 0`... folds.

OK here's another thought: maybe gcc's flow DOES propagate `a1s = arg1`, but the reason target has the copy is not C-level. So a real-C crack must produce the copy some other way, e.g., by making arg1's pseudo die at the andi and forcing a copy because the value is needed later through a different *hard-register-constrained* use.

Wait — what if the later uses go through `(s16)` casts? `(s16) arg1` in the tests: `if ((s16) arg1 & 0x8000)`. That's `(s16)arg1` computed each time: sll/sra from a1. That keeps arg1 live in a1, no copy. Not target.

Let me reconsider the whole thing: maybe the target's `move t3,a1` is not a copy of arg1 for later tests; maybe it's `pos`?? pos = arg2 = a2, and move t4,a2 is separate. Hmm no.

What about a1v? `a1v` pinned $5 and launder-tied to arg1. In the generated code, andi a1,a1,1 is a1v = arg1&1 in a1. The t3 copy is arg1's value for the later tests. Yes.

So the real-C must produce: a copy of arg1 used later, and the first test computed in place in a1.

Let me try: `s32 a1s = arg1;` but place the copy LATER in the source, after the first test? Impossible (need original value).

Hmm, what about using a1s in a context where gcc needs it to be a separate value: e.g., the copy is created by an assignment that gcc's cse can't merge because of a memory clobber? There are global loads/stores between.

Actually! The copy `a1s = arg1` could be moved by gcc. What if we place it right before the first test but with a global store between the copy and the test? Copy propagation works across stores. Hmm.

Let me try a different real-C trick from the catalog: "pointer reuse" / "self-reassign". 

What about making a1v a POINTER: `u8 *a1v = (u8 *)arg1;` no.

Let me step back and consider the possibility that this item is hard; the budget is 20-30 min/item, 4 items. I've spent ~15 min on item 1. Let me timebox: try a few more shapes quickly, then maybe record a WALL and move on.

Shapes to try:
1. `s32 a1s = arg1; if (!(arg1 & 1))` with a1s declared before pos (a3) — done, merged.
2. Put the copy inside the if's delay... no.
3. Use `if (!(arg1 & 1))` with later tests on `a1s` where a1s is assigned AFTER the first test but from a copy taken before? e.g.
```
s32 t = arg1;   // copy
if (!(arg1 & 1)) {...}
...
a1s = t;        // used later
```
Same thing.

4. Maybe the trick is `do{}while(0)` around the copy to add loop refs (C0535): `do { a1s = arg1; } while (0);` — this is a "real" construct that adds loop_depth refs, raising a1s's priority so it gets allocated t3 first. But does it prevent copy propagation? gcc's copy propagation works on notes; a do-while(0) becomes a NOTE_INSN_LOOP_BEG/END and an EBB boundary; maybe propagation across it is blocked? Actually gcc's flow copy propagation does consider loop notes? Hmm.

Actually, more importantly, the issue isn't propagation of the copy but that gcc merged a1s and arg1. Let me test a small experiment to see what gcc does with do-while(0).

5. Alternative: make the first test use `arg1 & 1` but make arg1's last use be the andi by having the LATER uses reference a global store of arg1's value... no.

6. Use `a1s = arg1;` and then use `a1s` in a comparison that gcc can't fold to arg1, e.g. after modifying... 

Let me just test several shapes quickly with sc.sh in one go. Write a4..a7.

a4: do-while copy:
```
s32 a1s;
s32 pos = arg2;
do { a1s = arg1; } while (0);
if (!(arg1 & 1)) ...
if (a1s & 0x8000) ...
if (a1s & 1) ...
```
But `do{}while(0)` needs `// !FAKE: do-while`? The constraint says `do{}while(0)` only with `// !FAKE: do-while`. Hmm — that comment marker means it IS considered a fake lever? "do{}while(0) only with `// !FAKE: do-while`" — so it's allowed but must be marked. But the brief says "no new lever of any kind" and "Lever-free = none of the row kinds remain". do-while is presumably allowed (C0535 is a legit move). The marker is required for style. But if do-while(0) is a lever, it's not among the row kinds (barrier,keepalive,launder,pin), and "no new lever of any kind" — hmm, "no new lever of any kind" means don't introduce new asm-style levers. do-while(0) is a real-C construct from the catalog (C0535), so allowed. But `// !FAKE: do-while` suggests it's flagged as fake-ish. The brief explicitly says `do{}while(0)` only with `// !FAKE: do-while` — so allowed with the marker.

Let me try a few.

a5: use a separate u32 for the copy? `u32 a1s = arg1;` later uses `a1s & 0x8000`, `a1s & 1`.

a6: copy via a struct-ish pointer? no.

a7: reverse: first test uses a1s (=arg1), later uses arg1:
```
s32 a1s = arg1;
if (!(a1s & 1)) ...
if (arg1 & 0x8000) ...
```
Merged as well likely.

Let me also consider: maybe the andi in-place can be obtained by making the first test's value a1v come from a real `& 1` of a *different* variable that happens to be in a1... e.g., `a1v = arg1 & 1` where arg1 is used later only in ways that gcc reloads from... no.

Hmm wait. Actually, what about the ORDER of the first test's use of arg1 vs the copy? In target, `move t3,a1` comes BEFORE `andi a1,a1,1`. gcc inserted the copy right before the andi because that's where a1's value gets destroyed. If in C we write:

```
s32 a1s = arg1;    // copy at entry
...
if (!(arg1 & 1))
```
gcc sees arg1 live until the test, a1s born at entry, overlapping → a1s can't be a1, gets t3, copy emitted at entry: move t3,a1. Then arg1 (a1) used in the test: andi a1,a1,1. That IS target! The only problem is copy propagation merged a1s with arg1.

Does gcc 2.7.2 flow do copy propagation of `a1s = arg1`? Yes, if a1s is not used before... Flow's `flow_analysis` / `propagate_block` does copy propagation with `reg_n_sets == 1`. It should merge.

But wait, in a3, we saw arg1's pseudo moved to t4 at entry and used everywhere — meaning the merge happened the other way: the param pseudo (arg1) was allocated t4 and a1s/a1v uses read t4. Actually that's gcc assigning the *parameter* to t4 and copying at entry (because a1? no). Hmm, why would gcc copy the param to t4 at all? That's local-alloc: the param pseudo's hard reg a1 is needed by other things? 

Let me test a minimal case to understand. But time. Let me just try the shapes.

Actually, an important observation: in all my candidates the param arg1 got moved to a temp at entry. That's suspicious. Why? Because the param is used 3 times and there's a `&1` and `&0x8000` and `&1`... gcc's local-alloc moves params out of their incoming registers when the incoming reg is call-clobbered and there are no calls? No calls here! With no calls, a1 is never clobbered, so keeping the param in a1 is fine. Hmm, but gcc's global alloc might prefer to give the long-lived value a temp reg (t3/t4) since... no, moving costs an insn.

Wait — maybe the move `move t4,a1` is not the param move but the copy from the `a1v = arg1 & 1`? No, andi uses t4.

Let me test a minimal body to see. Actually let me test the pure original lever-free without a1v: that's a1.c which also had move t4,a1. So gcc ALWAYS moves arg1 to t4 in this function even with plain uses. Why? 

Because arg1 is live across the division? No... The param arg1 is used at the first test and much later (0x8000 test at c98). The value must survive across the whole computation. a1 is caller-saved; no calls, so fine. But gcc 2.7.2's global alloc (which runs after local) might spill params to callee-saved... 

Hmm, maybe the move is because the param pseudo gets a preferred reg and local-alloc assigns it t4 because a1 is... hmm.

Actually! Maybe the move at entry is because the parameter is `arg1` and gcc's "function.c" puts params in pseudos; with -O2, `expand_function_start` copies incoming args into pseudos. The pseudo then gets a register; if that register is not the incoming hard reg, a move is emitted. gcc's local-alloc might choose t4 because... a1 is a "call-clobbered" register and the pseudo's live range crosses a call? There are no calls... but there ARE calls? No jal in this function.

Wait, maybe there are calls in the function? Looking at the target listing: no jal. Right.

Hmm, so why move? Let me check: maybe because the pseudo is used in a `div` and mult? No.

OK, empirically: gcc moves arg1 (and arg0 to t2) at entry. arg0 also moved (move t2,a0). Both params moved to temps. That's a global-alloc decision: with -O2, params are copied to temps when their pseudo is long-lived? Actually gcc's local-alloc assigns pseudos to registers; for a param pseudo that is used a lot, it may get a different reg, and the "move" is emitted at the top by `reload` or by the caller-save insertion.

Whatever. The target's arg1 copy to t3 is exactly this same param move! `move t3,a1` at b08 IS the param's home register being t3. And `move t4,a2` is arg2's param move to t4. And move t2,a0 is arg0's param move to t2.

Oh! That changes everything. So in target: arg1's home = t3, arg2's home = t4, arg0's home = t2. In mine: arg1 = t4, arg2 = t3, arg0 = t2.

And the first test `andi a1,a1,1` uses the INCOMING a1 (before the move!), i.e., a1v was computed from the raw param in a1 before the param move? But the move is at b08 and the andi at b0c — after. Yet the andi uses a1, which still holds the param value. So a1v = arg1&1 computed from the incoming reg (a1), and the param's home copy is t3.

Interesting: so a1v is computed at the point where arg1 is still in a1 — because the param move to t3 hasn't "destroyed" a1 yet (the move copies). The andi writes a1, destroying the param's incoming copy — that's fine because the param now lives in t3.

So the codegen: param arg1 moved to its home t3 at entry; a1v computed from the still-live a1.

In C terms: `s32 a1v = arg1 & 1;` computed from arg1 before... gcc would normally use the home reg. But since the andi comes right after the move and a1 still has the value, local-alloc/regalloc could tie a1v to a1? Hmm, but that requires a1v's input to be the incoming a1, not the home pseudo.

Hmm, in gcc, the param pseudo IS the incoming a1; the move to t3 happens because the pseudo's home is t3 and reload/caller-save emits a move at entry. Then all uses of the pseudo use t3. There's no "incoming a1 still live" concept — the move at entry copies a1 to t3, and then uses read t3.

But target's andi reads a1! That means the andi is reading the pseudo BEFORE the move was inserted, or the move was placed after the andi by the scheduler? The move at b08 is before b0c. So a1 at b0c still holds the param value (move doesn't destroy source). The compiler generated andi a1,a1,1 because the pseudo's home was t3? No, then it'd be andi v0,t3,1.

Unless... the scheduler moved the move up. The order at b08 move t3,a1, b0c andi a1,a1,1. If the pseudo's home is t3, the andi should read t3. So the andi reads a1 = the incoming param register, meaning a1v was computed from the *hard reg a1* directly (the asm's tied operand was a1!). Right: the launder's asm input was tied to arg1's register a1, and the asm output a1v was pinned to $5. So the asm forced reading a1.

So in the lever-free world, we need `andi a1,a1,1` — reading the incoming param register a1 directly and writing it. For gcc to do that, the value must be computed before the param is moved to its home... but the move at b08 is just an artifact; gcc emitted it at entry and the andi could use a1 if gcc knows a1 still holds the param (it does, until something clobbers a1).

Hmm, gcc's reload does "output reload"/"input reload": if the insn requires a1 and the pseudo is in t3, it would copy t3→a1 first. Here the andi is a 3-operand-ish; gcc could allocate a1v to a1 and read the param pseudo from a1 if the param pseudo is still in a1 at that point — but the param pseudo's home is t3, so gcc would use t3.

I think the actual mechanism: gcc's local-alloc tied the andi's output to a1 (hard reg from the asm pin) and the input (arg1 pseudo) was still assigned a1 (its incoming home) at that point because... the param pseudo's home is a1 (its natural incoming reg), and the move t3,a1 is for the LATER uses? No, the later uses read t3.

Ugh, I'm going in circles. Let me look at the actual gcc-generated code for the ORIGINAL source (with levers) — that's target. And for lever-free variants.

Practical approach: manipulate which param gets t3 vs t4 and whether the andi writes a1.

Observation: in mine, arg1's home = t4 and the andi is `andi v0,t4,1`. In target, arg1's home = t3 and the andi is `andi a1,a1,1`.

So two things to change: (1) arg1's home t4→t3 (priority swap with arg2), (2) the andi reads a1 instead of t4 and writes a1.

For (2): if the andi's result a1v were allocated to a1 (tied), the input could be a1 if gcc allows reading the param's incoming reg... Hmm, but the param's home is t3.

Alternatively, maybe the target's andi is not a1v but something else. Let me reconsider: maybe a1v's pin didn't take effect and instead the launder made `a1v` a copy in a1... 

Honestly, the target's exact mechanism is asm-driven; cracking it in real C may require a different shape entirely.

Let me try the "real 2nd set" that the catalog uses: replace the launder with a real second computation. Here: a1v = arg1 & 1 IS a real second set. We tried; gcc produced andi v0,t4,1.

What if we make a1v's use the last use of arg1 by moving the later tests to a copy created as a real second set too:
```
s32 a1v = arg1 & 1;
s32 a1s = arg1;     // copy for later
if (!a1v) ...
```
gcc: a1s = arg1 propagates → same as before.

What if the later tests use `arg1` but we make arg1's home t3 via priority? Then the andi would be `andi v0,t3,1` — still v0.

Hmm, what if a1v is used more than once, e.g. also stored? No.

New idea: make the andi's output be the same pseudo as its input by having the source modify a variable: `arg1 &= 1`? That changes later uses... but if we first copy arg1 to a1s and then do `arg1 &= 1`, the later tests use a1s:
```
s32 a1s = arg1;    // copy for later
arg1 &= 1;         // destructive
if (!arg1) ...
...
if (a1s & 0x8000)
if (a1s & 1)
```
Now arg1 is a real variable that's modified: `arg1 = arg1 & 1` → `andi a1,a1,1` in place (since arg1's home is a1, its incoming reg; the assignment writes the same pseudo). And a1s = arg1 must be a copy taken before — but copy propagation of a1s = arg1 is blocked? a1s = arg1 where arg1 is later modified: the copy must be materialized! But gcc could still coalesce a1s with arg1's pre-modification value... Since arg1 is modified, a1s gets the old value; gcc cannot merge them into one pseudo because their live ranges differ (a1s lives after arg1's modification). So a real copy is emitted: move t3,a1 (or wherever).

Then `arg1 &= 1` compiles to `andi a1,a1,1` — in place! And `if (!arg1)`.

But wait: modifying a parameter — is that OK? The parameter is used after the modification in the ORIGINAL code (the 0x8000 test). We've redirected those uses to a1s, which preserves the original value. Semantics preserved. And the signature is unchanged.

This looks very promising! Order: gcc would emit `move a1s, arg1` (copy), then `andi arg1,arg1,1`. Where does the copy go? Right before the andi (since arg1 dies/becomes modified there). The allocator: a1s born at the copy, live to the end; arg1 (param) live until the andi. a1s can't share a1 (overlap) → gets t3 or t4. arg1's home: the param pseudo is modified, so it can't be the incoming hard reg? If the param is modified, gcc gives it a register; it might still be a1.

Then pos = arg2 gets the other temp.

Let's write a4.c:

```
s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {
    ...
    s32 a1s = arg1;
    s32 pos = arg2;
    ...
    arg1 &= 1;
    if (!arg1) {
        ...
    }
    ...
    if (a1s & 0x8000) { ... }
    ...
    if (a1s & 1) {
```

Careful with `arg1 &= 1` — but the earlier branch code uses `(s16) arg2`, not arg1. Good. And the later uses were `arg1 & 0x8000` / `arg1 & 1` → now a1s.

Wait, but the ORDER: the copy `a1s = arg1` must be before the modification. If I write `s32 a1s = arg1;` at declaration and `arg1 &= 1;` right before the if, gcc will keep the copy at the declaration point (top) unless it sinks it. The target has the copy at b08 (top) — good.

But there's a subtlety: `arg1 &= 1; if (!arg1)` — combine might fold the andi into the branch (andi sets no useful flags on MIPS; gcc emits andi + beqz). Target: andi a1,a1,1; bnez a1. Yes.

Let me try it.
