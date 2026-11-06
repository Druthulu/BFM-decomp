---
ts: 2026-10-22T20:40:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IV0nNsrl2B6kCDTKksBN
---
Target full:
```
45f8 addiu sp,-24
45fc sw ra,16(sp)
4600 lhu v0,10(a0)
4604 nop
4608 andi v0,0x800
460c beqz v0, 464c     (else branch)
4610 nop
      // if branch (flag set)
4614 lui v1, D_80120194
4618 addiu v1,v1,0
461c addiu a1,v1,0x6480
4620 beq a1,v1, 4690
4624 nop
4628 lhu v0,0(a1)
462c nop
4630 beqz v0, 4694
4634 nop
4638 addiu a1,a1,-0x10C
463c bne a1,v1, 4628
4640 nop
4644 j 4694
4648 move a1,zero
      // else branch
464c lui v1, D_80120194
4650 addiu v1,v1,0
4654 j 4664
4658 addiu a1,v1,0x658C
465c j 4694
4660 move a1,v1
4664 lui v1, D_801202A0
4668 addiu v1,v1,0
466c beq v1,a1, 4690
4670 nop
4674 lhu v0,0(v1)
4678 nop
467c beqz v0, 465c
4680 nop
4684 addiu v1,v1,0x10C
4688 bne v1,a1, 4674
468c nop
4690 move a1,zero
4694 bnez a1, 46a4
4698 move a2,zero
469c j 46b8
46a0 move v0,zero
46a4 lhu v0,10(a0)
46a8 nop
46ac ori v0,0x8000
46b0 jal func_8012C890
46b4 sh v0,10(a0)
46b8 lw ra,16(sp)
46bc addiu sp,24
46c0 jr ra
46c4 nop
```

Notable: in the *if* branch, the target also does `addiu a1,v1,0x6480` — the same two-step pattern (lui v1, addiu v1, then addiu a1,v1,K). So both branches compute `base + K` as a two-step add, NOT folded. So `base`/`it` are registers holding the symbol and the +K is a separate addiu in both branches.

In gen_base (score 4), the if branch presumably matches (base is live in the loop), but the else branch folds because `it` is dead.

Wait — in the if branch, `base` is live (used in the loop: `beq a1,v1`), so no fold. In the else branch, `it` is dead (reassigned) → fold.

So to fix the else branch, `it` must be live at the fold point. But the target's own code shows v1 reused at 4664 (the test block), so the first it dies there. Yet the add wasn't folded!

Unless the fold is blocked because `it` is live in the *C sense* (used at copy) and gcc's cse doesn't do the fold when the operand is live? No, cse folds regardless.

Hmm, maybe gcc's cse folds `reg + const` only via REG_EQUAL notes when the *result* isn't used in a way... Actually the fold in mine happened at expand/simplify? `lui a1; addiu a1,lo+K` — that could come from combine or cse. The launder in the src def prevented it.

What if the difference is the *type*: in the if branch, `base` is `s32` and `p = base + 0x6480` — the target keeps the two-step. In the else, same. Both use a two-step in the target. So the target's C keeps both `base`/`it` values in registers.

For the if branch, `base` is live. For the else, `it` is dead in the CFG. So the target's else branch's it must be live in the CFG — meaning the `copy: p = it;` path uses the FIRST it (not the reassigned one)! But the target's copy path (`move a1,v1` at 4660) uses v1 which at that point is the scan pointer... 

Hold on: is the copy path reachable only after the reassignment? The copy path is reached from `beqz v0,465c` in the loop, which is after `test:` reassigned v1. So yes, at copy v1 = scan pointer.

But here's the thing: if the C's `copy: p = it;` refers to the same variable, then the first it is dead in the CFG, so gcc could fold. Yet the target has `addiu a1,v1,0x658C` at 4658, computed BEFORE the reassignment. That means the *value* it+K was computed early (in the else block) rather than at use. Hmm, p is a variable; gcc computed it right there. Fine.

The question remains why no fold. Maybe gcc 2.7.2's cse does not fold `(plus (reg) (const))` where reg has a REG_EQUAL constant when the result is a *register* (not a memory address)? But mine DID fold: `lui a1; addiu a1,lo+K` is a single symbol+K address. So it folded in mine.

What differs in mine? The `it` in mine is dead, so cse replaced `it` with the constant, then `+K` folded. In the target, `it` is live (so cse might avoid substituting a constant into a live pseudo? No...). Hmm, actually cse's constant substitution into an expression: it replaces uses of a pseudo that has a known constant value with the constant, *provided* the pseudo's value is not needed. It doesn't check liveness; it just does it. But if the pseudo is live, cse still substitutes.

Hmm wait, maybe the difference: in the target, `it` is assigned `(s32)D_80120194` and is LIVE at the point of the add — cse would still fold.

Unless in the target, the add is `p = it + 0x658C` where the compiler couldn't fold because `it`'s REG_EQUAL note was killed by the launder... which is what the levers do.

So maybe the target genuinely had the launder (it's in the src def!) and this item is a WALL (the launder is NEEDED DIFFERS). The kinds row says `launder` — the launder must go, but it may be impossible. The prior coder's 35 variants all ≥4.

Given the pattern (this is a header item, 141 includers!), and the wall family, I should check whether the prior coder spent enough. The item's files date 07:13 and the prior log's carry says "Then func_8012C750, func_801372B0" — meaning they were NOT done in the prior run. So this is fresh: I need ≥20 min and ≥30 tries before walling.

I've spent ~5 min. Let me try a focused set of ideas for the else-branch fold:

Idea A: make `it` live by using it in the `copy` path *without* the reassignment dominating. Restructure the C so the copy label is placed such that gcc sees `it` (first value) live. But semantics: the target's copy uses the scan pointer. If I write `copy: p = it;` with the current C, it's the scan pointer.

Hmm, but what if the target's source is:
```
it = (s32)D_80120194;
p = it + 0x658C;
goto test;
copy:
    p = it;
    goto found;
test:
    it = (s32)D_801202A0;
```
and the *compiler* keeps the first it live because the CFG has copy reachable from... no, test reassigns.

Wait, maybe the source's test block reassigns a DIFFERENT variable and the loop's `it` is the first one! Look at the target: at 4664 `lui v1, D_801202A0` — v1 is reassigned. The loop uses v1. The copy uses v1. So one variable. Confirmed.

Idea B: prevent the fold by making `it` not a constant at the add: e.g., `it = (s32)D_80120194; p = it + 0x658C;` → make `it` come from a *pointer variable* declared outside: 
```
s32 *ip = (s32 *)D_80120194;   // hmm
```
Still constant.

Idea C: use the fact that `it` is assigned from `(s32)D_80120194` — if the type were `u16 *`, then `p = (s32)it + 0x658C` — the cast to s32 of a pointer constant is still constant.

Idea D: Make the addition involve a *runtime* value that is provably 0 but not folded: e.g. `p = it + 0x658C + (a0 & 0);`? gcc folds a0&0 to 0.

Idea E: Use a function call result: no.

Idea F: What if `it` is assigned inside a loop or via a goto label so the compiler can't prove it's the constant at the add? E.g.:
```
else {
    it = (s32)D_80120194;
    goto have;
have:
    p = it + 0x658C;
    goto test;
```
Still constant-propagated.

Idea G: `it` as a *volatile* local? Changes codegen.

Idea H: Maybe the real difference is that the target's `it` is used *between* the assignment and the add in a way that keeps it in a register: e.g. `it = (s32)D_80120194; p = it + 0x658C;` — the add itself uses it.

Idea I: What if `p` is computed as `p = it; p += 0x658C;` where p is a *pointer* type? `u16 *p; p = (u16 *)it; p += 0x10C*...`? The target's p increments are 0x10C in the loop. Hmm, if p were `u16 *`, `p + 0x6480` would scale. The target's addiu 0x6480 is unscaled, so p is s32.

Idea J: The C's `it` is `s32` and `p` is `s32`. What if we declare `it` as `s32` but assign via a *cast from a pointer of a different type*, e.g. `it = (s32)(u8 *)D_80120194;`? Constant.

Honestly, the only real-C way to make a constant value opaque is a memory round-trip or volatile. Memory round-trip: store it to a local and reload? e.g.
```
it = (s32)D_80120194;
*(volatile s32 *)&p = it;   // no
```
That adds insns.

Idea K: use `a0` in the expression: `p = it + 0x658C + (a0 - a0);` folded.

Idea L: make the address depend on the flag test: e.g. `it = (s32)(flag ? D_80120194 : D_80120194);` folded.

I think this is the cse-const-addr wall. But let me check the other candidates' diffs — maybe one of the score-4 variants differs elsewhere and the "register pairs a1->v1" line means the diff is only register naming, i.e., the code is structurally the same but with a1/v1 swapped. That would be 4 "MIXED" — let me look at the class. `score 4 (MIXED; mine 52 ins, target 52)`. MIXED means some insns match? Let me get the full diff for gen_base: it showed insns 21-24 and 29 as replaces. So 4 words differ: lui/addiu regs (a1 vs v1), the missing addiu, and the beq operand order.

Wait: the diff listed:
- 21-23 replace: mine `lui a1,0x0; addiu a1,a1,25996` vs target `lui v1,0x0; addiu v1,v1,0` (2 insns replaced)
- 24: mine nop vs target addiu a1,v1,25996 (1)
- 29: beq a1,v1 vs beq v1,a1 (1)
Total 4.

So mine's else branch: it folded into a1 (lui/addiu a1 = symbol+0x658C), then `beq a1,v1` where v1 = ? Hmm, mine has `beq a1,v1` at 29 — v1 must be D_801202A0. So in mine: p in a1, it(second) in v1.

Target: it(first) in v1, p in a1, then test reassigns v1.

So the only real difference is the fold in the else branch. And the register naming follows from it.

Now: is the fold really a launder effect? The launder is on `it` in the else branch (and on the second it). Yes.

Hmm, what if I use the *other* existing pin? This def has no pins (kinds launder only, and no register asm in the body). So no levers available to keep.

Idea M: what if `it` is declared as `register` (plain `register s32 it;`)? Decision 3 in the tool says a bare `register` stays as ordinary C, unmarked. A bare `register` might make gcc keep it in a register and not fold? cse still folds constants regardless of `register`.

Hmm, but actually: `register` locals in gcc 2.7 don't change optimization.

Idea N: make the else branch's `it` used in the *if* branch too? no.

Idea O: What if the source computes p as `p = it + 0x658C` but `it` is assigned from `(s32)D_80120194` where D_80120194 is declared as a *function*? no.

Let me look at the prior coder's gen_use2_* variants — they tried a second use of `it`. The target's it is live only in the else branch. If I add a second use of the first it *after* the add (e.g., in the copy path? no, that's the second it).

Hmm, what about a second use *before* the reassignment, e.g. `p = it + 0x658C;` and also `if (it != p)`? That's the if branch's code.

OK here's another thought experiment: how did the *if* branch (base) escape the fold? Because `base` is live (used in the loop). If cse folds `base + 0x6480` into a constant for p, that's fine (p is separate) — it doesn't need base to die. Yet the target has `addiu a1,v1,0x6480`. So in the target, even with base LIVE, the add wasn't folded! That means cse in this build does NOT fold `(reg with constant value) + const` when the reg is live... or the launder... the src def's if branch has NO launder (look: `s32 base = (s32)D_80120194; p = base + 0x6480;` — no asm there). And the target keeps the add. So with `base` live, gcc doesn't fold. 

So the fold only happens when the register dies! That's cse's behavior: it substitutes a constant for a pseudo only if the pseudo is dead after the use (to avoid extending...). Actually cse's `cse_insn` replaces a register with a constant when `REG_EQUAL` is known and it's "cheap", regardless. But empirically: live → no fold, dead → fold.

So: make the else branch's `it` LIVE at the add. The C's `it` is used at `copy:` — but gcc sees the reassignment at test dominating copy, so it's dead.

How to make the first `it` live in the CFG? Make a path from the add to a use of `it` that doesn't pass through the reassignment. Semantically, the target's copy path uses the *current* it (scan pointer). But if I write the C with a structure where the first it is live... the semantics must still match the target's assembly. Let me think about what the target's assembly does:

- else: it = D_80120194; p = it + 0x658C; goto test.
- copy (reached from the loop when a zero is found): p = it (current scan); goto found.

If the first it were live to the copy path, the copy would use the first it (D_80120194) — but the target's copy uses the current scan pointer (v1 at that point). So no.

Therefore the target's first it is NOT live at copy. Yet the add isn't folded. So my "live → no fold" theory is wrong... unless the target's source has the first `it` used somewhere else in the else branch, e.g. the `p != base`-style test? 

Hmm! Maybe the else branch's source is:
```
it = (s32)D_80120194;
p = it + 0x658C;
```
and the *loop* is written with `it` as the scan pointer, but the compiler's CFG for the copy path... 

Wait, actually maybe the fold didn't happen because cse1 processes the else block and the add in a way where `it`'s constant isn't yet recorded? The order: `it = (s32)D_80120194;` then `p = it + K`. cse1 sees the set of it with REG_EQUAL symbol, records it, then the add. It would fold.

Unless gcc's cse doesn't fold `(plus reg const)` when the result is used as a *pointer-ish* s32 and the constant is a symbol... but mine folded.

Difference between mine and the target: in mine, `it` is dead; in the target, live (maybe). I can test the hypothesis directly: take gen_base and make `it` live by adding a use that doesn't change the code — e.g. add a second use of the first it in a way that the compiler can't fold: `if (p == 0) ...`? no, changes code.

The prior coder's gen_use2_* tried exactly this and got 4/11 — so adding a use didn't change the fold? Hmm, "gen_use2_dead" = use it after the add (dead?) — they explored.

Let me look at one of those gen_use2 files to see what they tried.
