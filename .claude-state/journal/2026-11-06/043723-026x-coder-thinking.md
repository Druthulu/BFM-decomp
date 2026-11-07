---
ts: 2026-11-06T11:37:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xHPLecYHCUSZDDiThDQ8
---
Only the tmp→sVar3 copy issue: mine computes `andi s1,v0,0xfff` directly (value into s1), target `andi a1,v0,0xfff` + `move s1,a1` in delay slot.

The launder's job: prevent cse from merging tmp and sVar3. Without it, the copy disappears and global-alloc assigns s1 directly.

Wait, but tmp is pinned to a1. With the launder removed, the C is `register s32 tmp __asm__("$5") = ...; s32 sVar3; sVar3 = tmp;`. The copy from hard reg a1 to a pseudo should still exist... but apparently the compiler folded: `andi s1,v0,0xfff` — so the value was computed directly into s1, meaning tmp's a1 pin got... hmm, that means the pin assignment got dropped? Or the pin is a1 but the value is computed into s1 and the hard reg never used?

Actually with the launder removed, maybe gcc's local-alloc sees tmp (hard reg a1) and sVar3 can be coalesced: `sVar3 = tmp` where tmp is a hard reg... a copy to a hard reg can be coalesced by choosing sVar3 = a1? But then it's in a1. Yet mine has s1. So instead, the compiler propagated: sVar3's value is the expression, and tmp's use is only in the copy → it computed the expression into sVar3 (s1) and dropped tmp entirely. The pin didn't force anything because tmp is only used in a copy that gets folded.

Hmm. So the launder is needed to force the hard-reg copy. Can we get the same with real C?

The launder `asm("=r"(tmp):"0"(tmp))` makes tmp appear used/defined so the copy can't fold. Real C alternative: make tmp genuinely used in another way, so its value must live in a1 and be copied to sVar3.

Idea: use tmp in the case 0x41 arm too? But target's 0x41 arm doesn't use it.

Alternative: make sVar3 a *different* type or make the copy non-foldable by a real C construct. E.g., a union pun, a cast to volatile...

What if sVar3 is declared as u32 and tmp as s32? A conversion could keep the copy? `s32 tmp = ...; u32 sVar3 = tmp;` — no conversion needed, still a copy that can fold.

What about `sVar3 = tmp & 0xFFFFFFFF`? folds.

Hmm, the key mechanism: the target's `move s1,a1` is a copy from a hard reg to a callee-saved pseudo. Real C where a value must be in a specific reg... impossible without a pin.

But wait — the pins may stay! The $5 pin is allowed to stay (it's not in kinds). So can I keep the pin AND remove the launder, and have the copy survive? Without the launder, the pin alone doesn't force it (v3 shows).

Hmm, but v3 keeps the pin. So the pin + no launder = no copy. The launder is what makes the pin effective.

Alternative real-C: keep the value alive in a1 by using tmp somewhere that forces it. What if the expression's result is used in the switch dispatch: e.g., `switch (bVar1)` on `bVar1 = *(u8*)(p+0xA9)` — unrelated.

What if we write `sVar3 = tmp;` and then also use `tmp` in a dead but non-eliminable way? E.g. `if (tmp == 0x7FFF) ...`? That would add code.

Hmm, let me think about what the target's code actually is: a1 holds the angle value; at the switch dispatch the copy to s1 happens in the delay slot. This means the C source has the value in a variable that is live across the switch. The compiler put it in a1 initially (because... the pin) and copied to s1 at the branch because a1 is clobbered by the calls.

Without the pin, global-alloc just uses s1 directly. With the pin (a1), the hard-reg variable must be moved to a pseudo (s1) before the clobbering path, and the copy lands in the delay slot.

The launder is what prevents the tree/cse from eliminating the hard-reg variable. So the question: what real C makes `tmp` (pinned a1) not foldable?

What if tmp is used in a context where its value must be preserved as an lvalue? E.g., taking its address: `s32 *pt = &tmp;` — forces a stack slot. No.

What if the launder is replaced by a real second use of tmp that produces no code: e.g., `sVar3 = tmp; if (tmp) {}`? The empty if might be eliminated.

What about `sVar3 = tmp, sVar3 = sVar3;`? no.

Hmm, what about making tmp volatile? That's a lever (new kind).

What about the C0414 "dead-reset" technique: assign `tmp = 0;` after `sVar3 = tmp;`? That's a dead store to a hard-reg variable; would it survive? If tmp is pinned to a1 and we do `tmp = 0;` after, that's a real store `move a1,zero` — code. Unless cse/flow deletes it (dead store). A dead store to a hard reg... flow deletes dead stores to pseudos; for hard regs, `insn_dead_p` might not delete. Risky.

Alternatively, restructure the C so that the value is naturally in a1: The target's computation: ratan2 returns in v0; `addiu v0,v0,-1024; andi a1,v0,0xfff`. Why a1 and not v0? Because the result is copied to s1 later anyway; the compiler chose a1 for the intermediate. With the pin gone, it uses s1.

What if the value is passed through a function call... no.

Let me consider: maybe the copy `move s1,a1` can be obtained by having the value live across a *function call that clobbers a1*? No, the target keeps it in a1 and copies to s1 — this is exactly what global-alloc does with a hard-reg variable.

OK, so maybe the answer is: the launder cannot be removed with a real-C move for this one... but wait, v3's only residual is the copy. Score 6, mine 70 ins (one less). What if we add a real-C construct that produces exactly `move s1,a1`? 

Think differently: the target is `andi a1,v0,0xfff` — the value lands in a1, which is the pin. Then `move s1,a1` in the delay slot. What if we write the C such that the pinned variable tmp is used in the switch's case 0x41 arm? No, changes code.

What if `sVar3` is assigned inside the case arms? Like:
```
s32 tmp = ...;  // pinned a1
switch (bVar1) {
case 0x41: ...
case 0x53: case 0x73:
  sVar3 = tmp;
  ...
}
```
Then the copy would be inside the arm, not in the delay slot.

Hmm. Actually — what if the value is *used* in the case 0x41 arm in a way that produces no code? No.

Let's step back. The residual is 1 insn: `move s1,a1` plus register assignment a1 vs s1 for the andi. If I could make the value's pseudo be assigned a1 and then copied... 

What about declaring sVar3 as `register s32 sVar3;`? `register` keyword is not a lever and doesn't force anything.

What about making tmp an lvalue used twice: 
```
s32 tmp = ...;
s32 sVar3 = tmp;
...
sVar3 = tmp; // again? 
```
no.

Hmm — what about `sVar3 = tmp; tmp = sVar3;`? The second assignment would be a copy back; if tmp is dead, maybe cse keeps it.

Actually, here's a thought: the launder is `asm("" : "=r"(tmp) : "0"(tmp))` — a no-op that makes tmp both input and output, so the compiler can't treat tmp's value as the expression. What real C has the same effect? A volatile read of tmp? Lever.

Alternatively — a union: 
```
union { s32 v; u32 u; } pun;
pun.v = (ratan2(...) - 0x400) & 0xFFF;
sVar3 = pun.u;
```
The union pun might be memory (stack) — adds sw/lw. No.

What about a cast through a different mode that requires a conversion insn? e.g. `sVar3 = (s16)tmp;` adds sll/sra. No.

What about `sVar3 = tmp;` where tmp is declared `s32` but assigned via a ternary? no.

Hmm, let me reconsider whether the copy can come from a different source: maybe if the value is used *both* in the case-0x53 arm and somewhere else, global-alloc keeps it in a caller-saved reg... but no other use.

Let me look at the actual mechanism of why `andi s1,v0,0xfff` with no copy. The tree-ssa? No, gcc 2.7.2. The launder forces tmp's value to be a "register" quantity. Without it, `sVar3 = tmp` is a copy; cse's `cse_insn` for a copy from a hard reg... Actually the compiler's `cse` would replace sVar3's uses with a1, then the copy dies. But a hard reg can't be a pseudo replacement across calls? cse2 might.

Anyway. Given budget 20-30 min/item and 4 items, I should consider whether to keep trying or move on. The wall tags are for lever-free best. Let me try a couple of real-C moves quickly.

Move A: put `sVar3 = tmp;` after the switch dispatch... no.

Move B: make tmp used twice:
```
s32 tmp = ...;
s32 sVar3;
sVar3 = tmp;
if (tmp == 0x8000) { }  // no
```

Move C: `sVar3 = tmp + 0;`? folds.

Move D: make sVar3 a `u32` and tmp `s32`, assign via `(u32)tmp`. A conversion from s32 to u32 is a no-op (no insn), copy still.

Move E: use `sVar3 = tmp & 0xFFF;`? That's an extra andi... but tmp is already masked; combine might remove it? The target has andi once. If C says `tmp = (ratan2(...) - 0x400); sVar3 = tmp & 0xFFF;` — hmm, then the andi applies to sVar3, and tmp (a1) would need the unmasked value... target has andi on a1.

Actually! Look at the target: `addiu v0,v0,-1024; andi a1,v0,0xfff`. The andi writes a1 (tmp). Then sVar3 = tmp copy. So the mask is part of tmp.

What if: `s32 tmp = (ratan2(...) - 0x400); s32 sVar3 = tmp & 0xFFF;` → combine could merge the andi into... the result goes to s1. That's mine.

Let me try: does the launder's absence combined with a *use of tmp in the mask* change anything?

Alternatively, maybe there's a simpler crack: what if `sVar3` is used in the case 0x41 arm in a way that the compiler can't remove? No.

Hmm, what about the classic: declare `s32 tmp` then `s32 sVar3 = tmp;` at declaration (init at decl). Might change alloc order slightly. Let me try a batch of cheap variants and score them.

Variants:
- a: `s32 sVar3 = tmp;` at decl, launder removed.
- b: sVar3 as u32.
- c: `sVar3 = tmp; tmp = 0;` dead reset after.
- d: use `if (tmp) ...`? no.

Actually, wait. Let me reconsider the problem: maybe instead of removing the launder, replace the launder with a *real* C statement that keeps tmp alive. The launder is `tmp = tmp` semantically (asm with same in/out). A real-C equivalent that forces the value into the register: an assignment from a volatile... lever.

What about: `sVar3 = tmp;` then later `tmp = sVar3;`? Let me think: after `sVar3 = tmp`, if we later do `tmp = sVar3` and tmp is used... no.

What if the value is used in BOTH arms: case 0x41 returns `... & 0xFF` — no.

Hmm, what about the switch structure: `switch (bVar1)` where bVar1 is loaded after. What if we make the switch on `(bVar1, tmp)`? comma → just bVar1.

OK here's another thought: the launder might be replaceable by a real second read of the ratan2 result through a different path. E.g., compute tmp twice? adds a call.

Let me just try a few and measure. Time budget matters. Let me batch 6 variants.

Variant ideas that might preserve the copy:
1. `s32 sVar3 = tmp;` (init at decl) with launder removed.
2. Declare tmp after sVar3; `s32 sVar3; s32 tmp = ...; sVar3 = tmp;`
3. `sVar3 = tmp;` and use `tmp` in a dummy `if (tmp & 0x1000)`... adds code.
4. Make sVar3 `u32`.
5. `sVar3 = tmp; bVar1 = *(u8*)(p + 0xA9);` order swapped (load bVar1 before the copy) — changes sched maybe.
6. Assign sVar3 inside the case arm.

Let me try 1,2,4,5.

Actually, hold on. Let me reconsider: the launder is `asm("" : "=r"(tmp) : "0"(tmp))`. This is a "launder" used to force the register copy. Removing it loses the copy. But what if we instead keep a *pin-only* structure where tmp's use forces it: e.g., `tmp = tmp;` in real C — the compiler removes it.

What about passing tmp's value through a `s32` variable declared `register`? no.

Another angle: maybe the copy can be produced by making the *expression* be computed into a1 naturally. The value flows: ratan2 returns v0 → addiu v0 → andi. If we write the expression as a separate statement with an intermediate variable, the compiler might use a1 for one of them. E.g.:

```
s32 tmp = ratan2(...);
tmp = (tmp - 0x400) & 0xFFF;
sVar3 = tmp;
```
Might change nothing.

Honestly, the residual is just 6 and the mechanism is the pin+launder. The wall tag could be `global-hardreg-reserve` or `combine-copy-merge` (combine merges a reg copy the target keeps). Actually this is exactly "combine-copy-merge": combine merges the copy `sVar3 = tmp` the target keeps. The existing tag `combine-copy-merge` fits: "combine merges a reg copy the target keeps, so the pin stays (G23)".

But before declaring a wall, I need ≥ 20 min and ≥ 30 scored tries for a WALL. That's a lot. 4 items × 30 tries... Let me be efficient: generate variants programmatically and score in batch with sc.sh.

Wait, but the wall rule: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". Hmm. So each WALL requires 30 scored tries. That's heavy but doable with batch scripts.

Let me first spend a bit more on this one since the residual is tiny.

Let me try the batch.
