---
ts: 2026-11-06T08:44:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CEFJecfDDXWoPKHiB4WB
---
Confirmed: mine has `move v1,s1` in the delay slot (from the if branch) and `negu v1,s1` in the else. Target has `negu v1,v1`.

So the else's copy is merged. We need to keep it.

Real-C idea: make the negation's operand a value that is *not* directly nudge, by having the copy produce a value used twice. What if the else does:

```c
val = nudge;
val = -val;
```
What if instead:
```c
val = nudge;
val = val ? -val : 0;
```
adds branch.

What about using a *function-like macro*? no, that's a lever if it's asm.

What about `val = -val;` written as `val = ~val + 1;`? Let me test whether combine turns ~x+1 into neg. In GCC 2.7.2, `simplify_rtx` for `(plus (not x) 1)` → `(neg x)`? There is a rule: `~x + 1 = -x` handled in simplify_unary_operation? I think combine does fold `-x` from `~x+1`. Worth a test.

`val = 0 - val;` → combine folds to neg (c4 tested, same score 1).

What about `val = (s32)(0u - (u32)val);`? same.

What about making the negation a *multiply by -1 with a variable*: `val = val * -1;` → strength reduction → neg. But if we use a variable `s32 neg1 = -1;`? adds an insn (li).

What about `val = -nudge + (val - nudge);`? That's identity-ish and adds insns.

Hmm, what about making the copy survive via *two uses* of val in the else:
```c
val = nudge;
val = -val;
```
The merge produces val=-nudge, and nudge (s1) is used later? nudge is not used after (target). If nudge were used after the negation, would combine still merge? Yes: it would keep nudge in s1 and set val = -s1. Mine does exactly that.

What if the negation is `val = -val;` and then `val` is used in a way... no.

OK, what about the "lreg" angle: maybe we don't need to block the merge; maybe we can make `nudge` die so the register allocator gives the negu operand v1? No, the merge is a combine issue (score family REG-mixed: one reg pair differs).

Wait, actually: is the merge really combine, or is it that the RTL already is val=-nudge because cse propagated? The score family REG-mixed just says a register pair. The instruction is negu v1,s1 vs negu v1,v1. In target, v1 holds nudge (via move). In mine, s1 holds nudge and v1 is the result.

What if we make `nudge` and `val` the *same pseudo*? I.e., write the else as `val = nudge;` where gcc coalesces val and nudge into one register (s1) — then negu would be `negu s1,s1`? No, target is v1.

Hmm, target: val is in v1; nudge in s1. The move copies s1→v1. So val has its own register.

Could we get the target by making `val` a separate variable that local-alloc gives v1, with the negation done in two insns? The two insns are the move (which exists in both) and the negu. Mine's negu uses s1 because combine replaced val's use with nudge.

So we MUST block the combine.

Let me think about GCC 2.7.2 combine: try_combine merges i2 into i3 if i2's destination is used only in i3 and i2 is a single set. Here i2 = val=nudge, i3 = val=-val. val is used in i3 and later (stores). Since val is used in i3, and i2 is the copy, combine merges: val = -nudge. Then the later uses of val are the merged set. That's a standard merge.

Blocking requires the intermediate val to have another use, or the sets to be in different blocks, or a register-class/side-effect difference.

Another use of val between the copy and the negation that costs no instruction... What if the negation is `val = -val;` and the copy is used in the *store address*? no.

What if we write the else as:
```c
val = nudge;
if (val) {
    val = -val;
}
```
Adds a branch.

Hmm what about a `?:` with a constant condition that combine folds but that separates the sets? e.g. `val = nudge; val = (hi, -val);` — comma with hi (already in s2) — the RTL would include a use of hi? `(hi, -val)` as an expression statement: the comma operator's left operand `hi` has no side effect, so gcc drops it at tree level.

What about `val = nudge; val = (s32)((u32)val ^ 0);`? fold.

What about a *cast to a different type* that survives: `val = (s32)(u16)val;` — this is a real operation (andi) that changes semantics; not identity but would add an instruction and change behavior. Not allowed (changes bytes).

What about using a `union`? no.

Hmm, let's look at this from the other end: which real C move in the catalog (C0505) could apply? "temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse". 

Statement order! What if we reorder the statements in the else:
```c
} else {
    val = -val;     // but val is not yet set...
    val = nudge;
}
```
No, wrong semantics.

What about `val = nudge; val = -val;` where the *if* branch is reordered:
```c
if (rand() & 1) {
    val = nudge;
} else {
    val = -val;   // no
```

Hmm. What about making the copy `val = nudge` appear in BOTH branches and the negation only in else — that's the current source.

What if we invert the if:
```c
if (!(rand() & 1)) {
    val = nudge;
    val = -val;
} else {
    val = nudge;
}
```
The branch would be beqz/negated... Target has bnez to skip the negation. With `if (!(rand()&1))` gcc might emit `bnez v0, else` (to the else block, which is out-of-line) → different layout. Or it inverts. Let me test; could produce the same.

Actually GCC lays out blocks: for if/else, the then-block falls through, else is jumped to. Target: bnez v0, 631c (skip to store) with the negation falling through — that's the *else* block falling through! So gcc laid out the else block inline and the then block at 631c (which just stores). Hmm, actually 631c is the join point after both blocks. The then block `val = nudge` was just the move in the delay slot and then fell to 631c. So layout: bnez → 631c; delay move; negu; fall to 631c.

If we invert to `if (!(rand()&1)) { val=nudge; val=-val; } else { val=nudge; }`, the then block (negation) would fall through and the else block would be a jump target — gcc might emit `bnez v0, else_label` with else containing the move, then j join; that's 2 extra insns. Or gcc could swap. Let me just test.

Actually, better idea: keep the if/else but make the then-branch the negation:
```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    val = -val;
}
```
is current. The alternative:
```c
if ((rand() & 1) == 0) {
    val = nudge;
    val = -val;
} else {
    val = nudge;
}
```
Hmm.

Let me think about what the *original source* might have been, given the binary. The binary has:
```
bnez v0, L
move v1,s1     ; delay
negu v1,v1
L: sw v1,16(s0)
```
This is consistent with source:
```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    val = -val;
}
```
where the else's copy wasn't merged. Since the original compiler is the same gcc 2.7.2, why didn't it merge? Because the original source probably had something between — or the else's copy was a different expression.

Hmm! Maybe the original else was:
```c
} else {
    val = nudge;
    val = -val;
}
```
but `val` had a use in the if branch... 

OR maybe the original source's else was:
```c
} else {
    val = -nudge;   // no, then no move
```

OR the original was:
```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    val = 0 - val;
}
```
same merge.

Hmm, what if the original's else had a *third* statement that was optimized away but kept the use at RTL:
```c
} else {
    val = nudge;
    if (val != 0) val = -val;   // no, branch
}
```

What about:
```c
} else {
    val = nudge;
    val = -val;
    val = val;      // dropped
}
```
no.

What about the original being:
```c
val = nudge;
val = -val;
```
inside the else, with `val` being **volatile**? no.

Alternatively, maybe the target's `move v1,s1` is NOT the else's copy but the if-branch's copy, and the else's `negu v1,v1` uses v1 set by... the if-branch's move in the delay slot (which executes always). So the else's negation operates on v1 which was set by the *if branch's* assignment that got hoisted into the delay slot! 

Look: the move at 6314 is in the bnez delay slot — it executes on both paths. Which assignment is it? The if-branch's `val = nudge`. If the else's copy were merged, we'd get what mine has. In the target, the else's negation uses v1 — the register set by the if-branch's copy. That means the else's own `val = nudge` was either removed (redundant, since the if-branch's move was hoisted into the delay slot and executes unconditionally!) — wait, no: the if-branch's copy is only executed when the branch is taken, unless hoisted to the delay slot (where it executes always). reorg hoisted it because it's safe (val=nudge is harmless). So in the target, the else's copy is *redundant*: val already equals nudge from the delay-slot move.

But mine also has that move in the delay slot. And mine's else does negu v1,s1. So the compiler in the target kept the else's copy as a separate use of v1, while mine merged.

The difference could be *local-alloc*: in target, `val` is assigned v1 and the else's copy is val=nudge (a real RTL set), which combine didn't merge... 

Hmm, why would combine not merge in the original? Maybe because the original's else had a *different structure*: the copy and negation in separate basic blocks? E.g., the original source might be:

```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
}
if (!(rand() & 1)) {  // no, rand called twice
```

Or the original source might have been:
```c
val = nudge;
if (!(rand() & 1)) {
    val = -val;
}
```
We discussed: the copy would be before the call. But WAIT: what if `nudge` is computed by the `r = rand()` earlier and the `val = nudge` copy is cheap; could gcc sink it after the second call? No.

Hmm, but actually let me reconsider: maybe the source order in the target IS:
```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    val = -val;
}
```
and the original compiler (same version, same flags) produced the target because the *decompiled* source has extra statements that were removed. The decompiler inserted the keepalive to emulate. So the real C is whatever the original programmer wrote, which we must find.

What could the original programmer have written that compiles to this? Perhaps:

```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    val = -val;
}
```
with val declared as `s32` and nudge as... The merge in combine happens when the intermediate is used only once. Here val is used later (2 stores), so the merge is still valid.

What if the original had `val` used in the if branch differently... 

Let me try: what if the else's negation is written as `val = -val, 0;`? no.

Let me try some empirical shots:
c5: `if (!(rand() & 1)) { val = nudge; val = -val; } else { val = nudge; }`
c6: `val = ~val + 1;`
c7: `val = (s32)-(u32)val;`
c8: `val = nudge; { s32 t = val; val = -t; }` (tested c3-ish, same)
c9: `val = nudge; val = -val;` with `val` declared volatile? no.
c10: use a `do { ... } while (0)` around the *whole* if/else? 

Actually, wait. What about making `nudge` a **u32** and val s32? `val = nudge;` then `val = -val;`. combine might not merge across a type... RTL has no types. No.

What about making the else's copy go through a *different variable that is live later*:
```c
s32 t;
...
} else {
    t = nudge;
    val = t;
    val = -val;
}
```
combine: val=t; val=-val → val=-t; t=nudge → val=-nudge. Merges.

Hmm what if `t` is used later (after the if)? Then combine can't eliminate `t=nudge`? It doesn't need to: val=-nudge and t=nudge both remain. Let's think: source
```c
s32 t;
...
} else {
    t = nudge;
    val = t;
    val = -val;
}
... later use of t ...
```
combine: val=t (i2), val=-val (i3) → val=-t. Then t=nudge stays (t used later). So we'd get: move t,s1 (t=nudge); negu v1,t. That's 2 insns + the later use of t. If t is assigned to a register that's... the target has move v1,s1 and negu v1,v1 — not matching (t would be another reg).

What if `t` is `val` itself... circular.

Let me look at what registers are available: target uses v1 for val and s1 for nudge. If the else's copy is `val = nudge` and the negu uses val, then after the copy val is in v1.

Hmm, what if we block the merge by making the *copy* have a second use that combine can't remove: e.g., store val to a memory location that is dead? flow deletes dead stores.

What if we store val into a global? Extra store.

OK, maybe the answer lies in *statement order* within the else: what if the negation comes *before* the copy but on a temp:
```c
} else {
    s32 t = -nudge;
    val = nudge;
    val = t;
}
```
No.

Hmm, hold on. Let me reconsider the possibility that the target comes from a source where the else's `val = nudge` is *hoisted out* because it's identical in both branches — i.e., the compiler itself (cse/flow) might have hoisted it? No, gcc wouldn't hoist an assignment out of both branches into a common dominator and then leave the if-branch's move in the delay slot.

Wait, actually — maybe the original source was:
```c
val = nudge;
if (!(rand() & 1)) {
    val = -val;
}
```
and the compiler moved `val = nudge` *after* the rand() call? Let's test this candidate and look at the actual diff! It's cheap. The move might end up before the jal (diff), but maybe sched1... no. Let me just test.

Actually, better: let me test the inverted-if variants and the `?:`.

Let me create several candidates and score.
