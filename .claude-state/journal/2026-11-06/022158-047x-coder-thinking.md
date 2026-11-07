---
ts: 2026-11-06T09:21:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Dyza03X6jpe1g2f4p2WI
---
So at combine output, insn 145: `(set (reg:SI 126) (and:SI (reg:SI 8 t0) 16))` with REG_DEAD on t0. So the AND uses pseudo 126 (v0 eventually) — combine did NOT fold dest into t0; the destination is 126.

But the final asm has `andi t0,t0,0x10`. So the fold to t0 happens later — in local-alloc? No, local-alloc assigns 126 to t0 because 126 is short-lived and t0 is free. That's it: reg 126 gets t0 in local/global alloc. With the keepalive, t0 is live longer, so 126 can't get t0 and gets v0.

So the lever is *register allocation*: pseudo 126 (the AND result) gets t0 because t0's live range ends at 145 (REG_DEAD). To keep 126 out of t0, t0 must be live past 145.

Real C must extend t0's live range past the AND. The asm does it artificially. Real C: use bVar1 after the AND.

Wait... what about the *second* bVar1 use in the &0x60/&0x80 test? That's before. Hmm.

But hold on — could we reorder the source so that a bVar1 test that currently occurs *before* the &0x10 test occurs *after* it? The &0x60/&0x80 test's store (param_1+8) precedes the 0x2a computation and the +0xa store in the target. But the *test* could be moved later than the AND while the *store* stays? In C, `if (cond) store;` — the test and store are together. Unless we compute a condition value early and apply it later. E.g.:

```
int neg = (bVar1 & 0x60) == 0 || (bVar1 & 0x80) != 0;
... compute sVar5 for +0xa ...
if ((bVar1 & 0x10) != 0) ...   // this uses bVar1 after `neg` computed
...
if (neg) *(s16*)(param_1+8) = -...;
```
But then the +8 negation store would move after +0xa — wrong order.

Alternatively, keep the store where it is but make its *condition* evaluated later? Not possible in C without a temp, and the temp's computation is the test.

Hmm. What if we use the bVar1 value in the *division* for the second sVar5? No.

What if we change the &0x10 test to use `bVar1` via a variable whose live range extends? Consider:

```
u8 f = bVar1 & 0x10;   // no
```

Alternative approach: avoid needing t0 live by making pseudo 126 *not* allocatable to t0 through a different constraint: e.g., if 126's value must live longer (used twice). The AND result is used once (beqz). If we make the condition's result used twice — e.g., test `if ((bVar1 & 0x10) != 0)` and also use the same subexpression later — cse would share it and extend 126's live range. E.g.:

```
if ((bVar1 & 0x10) != 0) {
    *(s16 *)(param_1 + 0xa) = -sVar5;
}
...
if ((bVar1 & 0x10) != 0) {   // no, semantics
```

Hmm, what about the fc block: `if (fc < limit)` etc. Could the &0x10 test be folded into a condition with fc? No.

OK, maybe accept: item 2 may be a WALL. But the budget says 20-30 min per item; let me try a handful of realistic restructurings first. Actually, let me reconsider: is there a real C construct that keeps a register variable live? A register variable's value is a local reg; if the function has a `goto` label after... no.

Wait — what about the pinned `bVar1` being used in the `memcpy`... no.

Hmm, let me reconsider the whole function: maybe the original C had bVar1 used in the second branch too. Look at the else branch (uVar2==1) — it uses `memcpy` and `*(s16*)(param_1+8)` etc. No bVar1.

What about using bVar1 as an argument to a call in the first branch? `func_8013AA24(iVar11, param_1)` — 2 args. No.

Given the constraint "no new lever of any kind", a real C use must be genuine. Since bVar1 is genuinely dead, the only genuine use after the AND would be if the source had a different structure where bVar1 is read later. E.g., if the &0x10 test were written as:

```
if (bVar1 & 0x10) {
    ...
}
```
That's the same.

What if the +0xa computation itself used bVar1? E.g., `sVar5 = ... * (uVar2b & 0xffff) / 0x2a;` no.

OK: What if we reorder the *loads*: currently `bVar1 = *(u8*)(iVar11 + 0x22)` at line 17, and the &8 test at line 36. What if the bVar1 load is moved to just before the &8 test? Then t0's live range is shorter — no.

What if bVar1 is loaded twice (two loads)? Then the second load's dest is a new pseudo... changes insns (extra lbu). No.

Let me try a completely different tactic for w1: instead of extending t0's live range, prevent pseudo 126 from being assigned t0 by making it live across a call or longer. E.g., compute the &0x10 mask result into a variable used in the fc block's condition? Not semantics.

Alternatively, *tie* the AND result elsewhere: e.g. write `if ((bVar1 & 0x10) != 0)` inside a `do{}while(0)`? The do-while changes EBB splitting (C0535) — could alter scheduling/allocation. Let me try wrapping the &0x10 test in `do { ... } while (0);` — that's allowed with the // !FAKE comment. Hmm, the brief says `do{}while(0)` only with `// !FAKE: do-while`.

Let me try some candidates quickly and score them:
A) w1 + `do { if ((bVar1 & 0x10) != 0) {...} } while (0);`
B) w1 with the &0x10 test written as `if ((bVar1 & 0x10) != 0)` but with the negation moved into a temp used twice? no.
C) w1 with `s16 t2 = sVar5; if ((bVar1 & 0x10) != 0) t2 = -sVar5; *(s16*)(param_1+0xa) = t2;`

Actually, let me think about what the real original C likely was. The keepalive lines were added by decomp agents in Phase 36 to force differences. The "real" original C probably had the *tests in a different order* or used a different structure that naturally produced the target. Hmm.

Let me look at the other keepalives and see if maybe a *single* real-C restructure removes all three: e.g., the whole `if (uVar2 != 1)` block could be restructured.

Let me try the most promising: for w1, make bVar1 genuinely live by reordering the two bVar1-derived negations such that the &0x60/&0x80 *test* comes after the &0x10 *test*, but the *stores* remain in order. We can do this with a boolean temp:

```
int neg8 = ((bVar1 & 0x60) == 0 || (bVar1 & 0x80) != 0);
...
if (neg8) *(s16*)(param_1+8) = -*(s16*)(param_1+8);   // must happen before +0xa computation
```
No good: the store must be before.

What about moving the &0x10 test *later*, after the fc block? Target order: 69-73 (&0x10), then fc block 74-101, then the call at 102. If we moved the &0x10 negation to after the fc block (just before the call), the store order would differ — target would show the +0xa store after the fc stores. No.

Hmm, what if we move the &0x10 test *earlier*, before the +0xa division? Target: division at 58-68, then andi at 69. If moved earlier, order changes.

So the &0x10 test's position is fixed, and bVar1 is genuinely dead after it. Real C cannot extend bVar1's liveness. Unless... the *register variable* bVar1's live range is special: in GCC 2.7.2, a local register variable's hard reg might be considered live until the end of the basic block regardless? Apparently not, given REG_DEAD at 145.

So w1 = WALL? The mechanism: local-alloc assigns the AND temp (126) to t0 once bVar1's REG_DEAD marks it free. Tag: lreg-hardreg-live-end? The wall list has "lreg-hardreg-live-end — local-alloc: a hard reg stays live to the block end, so the target pairing cannot form (G25)". Hmm, that's the opposite. Here the hard reg dies too early. New tag maybe `lreg-hardreg-dead-early` or `lreg-free-hardreg-reuse`.

But wait — maybe we can crack it with a real use: the function returns `void`, but what if the target C actually used bVar1 in the *else* branch's call? No.

Hold on, let me reconsider: could the real C be that the &0x10 test is written on a *wider* expression that also keeps bVar1 alive through a different use, e.g. the store `*(s16 *)(param_1 + 0xa) = -sVar5;` where sVar5 is computed with `(bVar1 & 0x10)` in the numerator? No.

OK let me look at item 3 quickly (maybe easier), and then return to item 2 with the remaining budget. Actually, let me first try a few candidate moves for item 2 and score them; the wall requires ≥30 scored tries and ≥20 min. I've done ~6 tries so far (orig, all-removed, w1,w2,w3, np8). Time started 02:13; now ~02:25.

Let me try:
1. w1 + do-while around the &0x10 test.
2. w1 + do-while around the whole +0xa block.
3. All keepalives replaced by: use bVar1 in the fc block somehow? 

Actually, wait. Let me reconsider the possibility of a *genuine* use of bVar1 after the AND that the compiler won't optimize away and that matches the target: what if we change the condition to read bVar1 *again* in the same expression, e.g. `if ((bVar1 & 0x10) != 0 && bVar1)`? That's a second use of bVar1 after the AND! Semantics: `(bVar1 & 0x10) != 0 && bVar1` — if bVar1 is nonzero (it has bit 4 set, so nonzero), this is equivalent. But it would add a compare/branch (beqz t0) → extra insns. No.

`if ((bVar1 & 0x10) != 0)` — what about `if (bVar1 & 0x10 & bVar1)`? That's `bVar1 & 0x10 & bVar1` = same value; the compiler would simplify to `bVar1 & 0x10` (cse). But the RTL might have two uses of bVar1... no, simplified at tree level.

What about `if ((bVar1 & 0x10) != 0 || 0)`? Folded.

Hmm, "identity-statement launders do NOT count as a crack" — so even if it works, it's not allowed.

Let me think about the *target's* source: the target has `andi v0,t0,0x10` where t0 dies right after (in the target, t0 IS dead after the andi — there's no later use of t0 in the target either!). So the target's t0 dies at 69 too, yet the andi dest is v0. That means in the target compilation, the AND temp was NOT allocated to t0 despite t0 being free. Why? Because at local-alloc time, t0 was still live? In the target's build, the same source with keepalive. Hmm, but the target binary is the ground truth from the original game — it was compiled from the original C without keepalives!

Right: the target binary is the real game's code, compiled in 1998 from real C. So the real C did produce `andi v0,t0,0x10` — meaning in the real compilation, t0 was live past the AND. So the real C must have a genuine use of bVar1 after the AND! Or the AND temp was assigned v0 for another reason.

What real C could have a use of bVar1 after the AND? Let's reconsider the target insns 69-73:
```
69 andi v0,t0,0x10
70 beqz v0, 0x128
71 sh v1,10(a2)
72 negu v0,v1
73 sh v0,10(a2)
74 lh a1,12(a2)
```
and 44-53:
```
44 andi v0,t0,0x8
45 bnez v0,0xc4
46 sh v1,8(a2)
47 negu v0,v1
48 sh v0,8(a2)
49 andi v0,t0,0x60
50 beqz v0,0xd8
51 andi v0,t0,0x80
52 beqz v0,0xe8
...
```
All bVar1 tests use v0. bVar1 stays in t0 through 52. Then the &0x10 test at 69 uses t0.

What if in the real C, bVar1 was NOT a register variable but an ordinary variable, and the compiler chose t0 for it? Then at the AND, t0 dies. Hmm, same.

Unless the real C used bVar1 later for something not visible... no.

OR: the AND temp got v0 because t0 was live at that point for a *different* reason — e.g., bVar1's value was needed in the else path? Let's look: the else-if at 91: `slt v0,a0,a1`. No t0.

Wait, maybe bVar1 was *reused* as a live value because of the outer `if (sVar2 != 0 && sVar2 < 7)`? No.

Hmm, alternatively the AND at 69 might not be `bVar1 & 0x10` from a separate test but part of a combined expression whose result register is v0 by constraint. E.g., if the source were `if ((bVar1 & 0x10) != 0)` and GCC's combine tied it... 

Actually, maybe in the real build, the register allocator assigned pseudo 126 to v0 because t0 was NOT dead at insn 145 — perhaps because of the `REG_DEAD` note missing in that build? The REG_DEAD comes from the RTL: the last use of reg 8. The last use is the AND. So dead.

Unless the real C had TWO ANDs on bVar1 after each other, e.g. `if ((bVar1 & 0x10) != 0)` and later `if ((bVar1 & 0x10) != 0)`? No.

Hmm wait, what about the possibility that in the real C, the value tested is a *different variable* that happens to be in t0, e.g. `sVar2`? No, sVar2 = uVar2 (u16).

Let me look at the target insns again: the value in t0 comes from `lbu t0,34(s8)` = *(u8*)(iVar11+0x22) = bVar1. Yes.

Could the real C have kept bVar1 live via the *last* test being `if ((bVar1 & 0x10) != 0) ... else ...` with an else that uses bVar1? The target has no else.

Hmm, what if the real C computed all four tests' values up front into variables? E.g.:
```
u8 f8 = bVar1 & 8, f60 = bVar1 & 0x60, f80 = bVar1 & 0x80, f10 = bVar1 & 0x10;
```
Then bVar1's last use is the f10 computation; f10 used once. Same.

OK, but here's a thought: the AND temp in the target is v0. In GCC 2.7.2 local-alloc, a pseudo gets a hard reg by qty priority; if t0 is free, why not? Because v0 might be the "preferred" reg? Actually local-alloc tries to assign each pseudo a reg; if the pseudo's live range doesn't conflict, it picks... The AND's operands: reg 8 (t0) and const. Perhaps local-alloc prefers to put the result in a reg that... hmm, `reg_alternate_class`? 

Let me compare with the earlier ANDs: `andi v0,t0,0x8` — at that point t0 is live after, so v0 is forced. `andi v0,t0,0x60` — t0 live after (for &0x80). `andi v0,t0,0x80` — t0 dies after this one? Then t0 is live? The &0x80 test is the last before... wait the &0x80 AND is at 51 and then t0 is used at 69 (&0x10). So t0 is live across 51..69 because of the &0x10 test. Right! So the &0x10 test itself keeps t0 live *until* the AND at 69. After 69, dead.

So at 69, the AND temp is created; t0 dies at the same insn. Local-alloc still gave v0, not t0. Why? Because the source and dest pseudo live ranges overlap at the insn boundary? In GCC, REG_DEAD at the insn means the reg is dead after this insn, so the destination could reuse it (that's how combine/regmove tie). But local-alloc assigns *before* REG_DEAD-based reuse; local-alloc would assign pseudo 126 a reg not conflicting with reg 8's live range. If reg 8's live range includes insn 145 (it's used there), then 126 (defined at 145) conflicts? In GCC, a def and a use in the same insn conflict unless tied; local-alloc's `reg_live_through`... Actually local-alloc computes live ranges over insn indices; reg 8 is live at 145 (use), so its live range covers 145; pseudo 126 is born at 145. Whether they conflict depends on the allocator's convention: if reg 8 is live *at* 145 (dying), and 126 is defined at 145, a conflict may exist, preventing reuse. So without the keepalive, why did mine reuse t0?

In w1's RTL (combine output) pseudo 126 = (and (reg 8) 16) with REG_DEAD on 8. So the AND is in the same insn as the last use. Yet in w1's final asm it's `andi t0,t0,0x10` — the *destination* is t0, meaning the allocator chose t0 for 126, i.e., it did allow reuse. In the target, it didn't.

Difference with keepalive: t0 is live past 145 (asm use), so conflict → v0.

So the real C must have kept t0 live past 145. Given the target binary, there must be a real use after. What could it be? Perhaps the real source's &0x10 test was written with bVar1 used again in the *branch* body? E.g.:
```
if ((bVar1 & 0x10) != 0) {
    *(s16 *)(param_1 + 0xa) = -sVar5;
}
```
No bVar1 in the body.

Or maybe the real source had the tests in a different *order* where the &0x10 test came *before* the &0x60/&0x80 test but the compiler reordered? No, GCC doesn't reorder stores across tests like that.

Hmm, actually! What about this: the target's `andi v0,t0,0x10` at 69 might be from a source where the tested value is bVar1 but the *register* t0 is live after because bVar1 is used in the *else* branch of the outer if (uVar2==1)? Let me re-check the outer structure: `if (uVar2 != 1) { ... } else { ... }`. In the else branch, no bVar1. Hmm.

But wait, is bVar1 used anywhere in the else branch of the *inner* if (sVar2 != 0 && sVar2 < 7)? The inner if has no else.

Let me look at the C source again... `bVar1` only appears at lines 17, 36, 39, 44.

Hmm, what if the *real* source computed `sVar5` for +0xa using bVar1? Unlikely.

Given the target uses t0 for bVar1 and v0 for all its tests, maybe the real source declared bVar1 NOT as a register variable but as a normal `u8`, and the compiler assigned it t0; and crucially, the real source's *last* use of bVar1 was NOT the &0x10 test but something else. Hmm.

Wait wait. Let me re-read the target insn at 49-52:
```
49 andi v0,t0,0x60
50 beqz v0, 0xd8
51 andi v0,t0,0x80
52 beqz v0, 0xe8
```
These are from `(bVar1 & 0x60) == 0 || (bVar1 & 0x80) != 0`. In mine (w1), the same. Fine.

Now, maybe the target's source order is different: what if the real source put the &0x10 test *before* the &0x60/&0x80 test but *after* the +0xa computation? No, the +0xa computation must precede the &0x10 test.

Let me consider the target's *scheduling*: the &0x10 andi at 69 is right after the division. If t0 were dead at 69 and the AND temp tied to t0, sched1 moved it early (insn 65 in mine). In the target, the AND is at 69 (its natural position) — because it can't be tied.

OK here's another idea: what if bVar1's last use in the real source is the *&0x80* test, and the &0x10 test uses a *different* variable that also lives in t0? E.g., the real source might have `u8 flags = bVar1;` then test flags — no.

I think this is a genuine WALL candidate: "lreg-free-hardreg-reuse" — local-alloc reuses the dying hard reg for the AND temp; target needs it live.

But before walling, let me try a real-C trick that keeps bVar1 live *genuinely*: what if we move the &0x10 test to *inside* the branch that computes the +0xa store, i.e., merge the store with the test differently... no.

What about using bVar1 in the *store value*: `*(s16 *)(param_1 + 0xa) = -sVar5;` -> `*(s16 *)(param_1 + 0xa) = (bVar1 & 0x10) ? -sVar5 : sVar5;` The andi is used in a ternary; still one use, t0 dead after.

Hmm, unless the ternary's condition value is used twice (test + selection). In a conditional expression, the compiler generates a branch; one use.

Let me try the do-while EBB split (C0535) and a couple of others, then decide. Also try: make the &0x10 test use a *copy* of bVar1 made *after* the +8 tests: `u8 b2 = bVar1;` — a copy insn (move) would appear in the target? No move in target. Unless the copy coalesces.

Actually, let me try something clever: `if ((bVar1 & 0x10) != 0)` -> `if ((bVar1 & 0x10) != 0 && sVar5)`? sVar5 could be 0 — changes semantics. No.

Let me now check whether sVar5 (v1) could be used... no.

Let me try candidates and score. I'll create a few.

Cand A: w1 with the &0x10 test wrapped in do-while.
Cand B: w1 with the &0x10 block rewritten as `sVar5 = (bVar1 & 0x10) ? -sVar5 : sVar5; *(s16*)(param_1+0xa)=sVar5;` — changes +0xa store to happen once? Target: sh v1,10; beqz; negu; sh. The store happens twice (before and after negation). So the ternary form `if (cond) x=-x; store` gives exactly sh before, negu, sh after? Actually target: `sh v1,10(a2)` (store positive) then `beqz`, then `negu v0,v1; sh v0,10(a2)`. That's `*(s16*)(param_1+0xa) = sVar5; if ((bVar1 & 0x10) != 0) *(s16*)(param_1+0xa) = -sVar5;` — note the source currently is `*(s16 *)(param_1 + 0xa) = sVar5; if ((bVar1 & 0x10) != 0) { *(s16 *)(param_1 + 0xa) = -sVar5; }` — yes, two stores. OK.

Cand C: move `bVar1 = *(u8*)(iVar11+0x22)` down to just before the &8 test (after the uVar2 tests). Live range shorter → no.

Cand D: use `sVar5` as the store base? no.

Hmm, let me look at this from the "what real C could produce t0 live after the andi" angle once more. The real C had no keepalive, so what made t0 live? Maybe the real C did the &0x10 test as part of a *loop*? no.

Or maybe the real C's last bVar1 use was a *different* expression: e.g. `if (bVar1 & 0x10)` where bVar1 is `s32` (word) and the AND is on a word — no.

Alternatively, maybe the target's andi dest v0 is due to the AND temp being used in the *delay slot* or scheduled... no, allocation happens before scheduling.

Actually, hold on! What if the AND temp's pseudo is NOT a fresh pseudo in the real build because the C expression reused a variable that's live? E.g., if the source wrote:

```
if ((bVar1 & 0x10) != 0) {
```
The AND result is a temporary. If instead the source used a named variable that is used elsewhere (live), e.g.:

```
u32 m10;
...
m10 = bVar1 & 0x10;
if (m10 != 0) { ... }
...
// m10 not used after
```
Still dies.

What if m10 is used in the fc block? Not semantics.

I'll try a handful and then wall. Let me also consider: maybe replacing the keepalive with `if (bVar1) {}`? No, identity.

Let me be efficient: prepare candidates in files and sc.sh them.

Cand E: move the &0x10 test's condition into a `&&` fold with something real: `if ((bVar1 & 0x10) != 0 && (bVar1 & 0x10) != 0)` — silly, folded.

Cand F: change the &0x10 test to test `(bVar1 & 0x10) != 0` on a *u8 copy*: `u8 bb = bVar1;` before... the copy is a move t0->? and then the test uses bb. If bb is assigned t0... hmm, the move would be coalesced.

OK here's another idea, from the "pins under other causes" note: bVar1's pin is $8. What if we *change the pin* to a different hard register that doesn't conflict? No, target needs t0.

Let me now also consider the possibility that the AND dest v0 comes from the real C using `bVar1 & 0x10` *before* the &8 tests (hoisted in source), with the result used later — a temp live across the middle! E.g.:

```
u32 m10 = bVar1 & 0x10;
...
if (m10) ...
```
If m10 were computed at the top (before &8), its live range spans the middle, and its reg would be v0 (t0 busy). But the AND insn would then be at the top, not at 69 — unless sched1 sinks it. sched1 could sink it to 69? sched1 schedules within EBBs; the insn could be placed late. Hmm! Actually, if the C source computes `bVar1 & 0x10` early into a variable used only at 69, sched1 might sink it to just before the use (scheduling tends to place insns near uses when no pressure). And its register would be v0 because t0 is live through the middle (the &8/&0x60/&0x80 tests use t0). Wait, if m10 is computed early, t0's last use would be the &0x80 test, and then... the AND at the top uses t0; after the &0x80 test t0 is dead. The AND's result pseudo lives from top to 69 → v0. And sched1 would place the AND at... the top? sched1 doesn't move insns across basic blocks. The &0x10 test is in the same EBB as the &8 tests? There are branches (beqz) — so they're different EBBs. The &0x10 test is in the EBB after the &0x80 branch. So computing m10 early would put the AND in an earlier EBB. Then the register would be live across EBBs → global-alloc, likely v0 or a callee-saved. The target has the AND at 69, in the same block as its use.

So no.

Hmm, but here's a thought: what if the AND is in the same EBB and computed right there, but the *temp* is the same pseudo as something else... 

Let me just try: C source reordering where the +0xa computation is moved *before* the &8/&0x60 tests? Target order: &8 tests at 44-57, then +0xa division 58-68, then &0x10 test. Source order matches.

I think item 2's bVar1 part is a genuine wall. But the item also has two other keepalives; PARTIAL is possible: win.c scoring 0 while keeping only the keepalives that can't be removed. The result format allows PARTIAL:<kinds still kept> = keepalive, if win.c scores 0 keeping the keepalive kind. But wait: PARTIAL keeps only *some* kinds (e.g. barrier cracked, keepalive kept). Here kinds = keepalive only, so a PARTIAL would be "PARTIAL:keepalive" meaning no progress. That's effectively a WALL. Hmm, but per the format, PARTIAL:<kinds still kept> — if the only kind is keepalive and we keep it, that's not progress. The DONE WHEN says each MATCH/PARTIAL has win.c scoring 0. A PARTIAL with all kinds kept is odd; better WALL with best = lowest lever-free score.

Wait, maybe partial means: win.c keeps *some* keepalives (a subset). E.g., remove 2 of 3 keepalives, keep 1 → win.c scores 0 → PARTIAL:keepalive? The kinds list is per-kind, not per-instance. Hmm, "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". If we keep one keepalive instance, the kind keepalive remains → PARTIAL:keepalive. That's the best achievable if we can remove 2 of 3.

So the goal: find real C for as many as possible; whatever keepalives remain, keep them and score 0 → PARTIAL:keepalive. If we can remove all three, MATCH.

Good. So even if w1 is unremovable, maybe w2/w3 can be cracked, yielding PARTIAL:keepalive with win.c keeping only keepalive #1.

Now, w2/w3: can we replace the keepalives with real C? Same problem: fc's liveness. fc is used in the conditions; the keepalive at line 64 keeps fc live past the if/else. Real use after? None.

w2: iVar7 and t inside the else-if branch. iVar7 is used as `t = iVar7 - 0x400` and then... after the branch, iVar7 dead. The keepalive keeps iVar7 live (through the branch end).

Hmm. So all three are liveness extenders. This item likely walls, or partials if a real-C restructure can genuinely extend liveness.

BUT WAIT. Maybe there's a real-C restructure that makes these variables genuinely live: combine the whole fc block differently. For example, the target's `iVar7 = fc + zr;` with zr pinned $0 is itself a pin-based launder: iVar7 = fc + 0. If instead we write the computations directly on fc, no iVar7. But then the register assignment changes.

Hmm, let me reconsider: maybe the real C source is different in a way that naturally creates the copies: e.g., the original might compute `s16 fc = *(s16*)(param_1+0xc); s16 t = fc + 0x400;` etc. The current source has the `zr` pin because without it the `+0` copy disappeared. That's another pin (not a row kind).

Let me look at what happens if I drop the zr pin and the keepalives and write natural C:

```
fc = *(s16 *)(param_1 + 0xc);
if (fc < *(s16 *)(param_1 + 0xe)) {
    int t = fc + 0x400;
    ...
} else if (*(s16 *)(param_1 + 0xe) < fc) {
    int t = fc - 0x400;
    ...
}
```
Target has `move v1,a1` (iVar7=fc) before addiu. Without zr, the compiler would compute `addiu v0,a1,0x400` directly, no copy. So the zr pin is needed (not a row kind, may stay).

OK so the keepalives are all "extend liveness of a hard-register-pinned or copy variable". This smells like a wall class: the target build had the variable live because the real C used it later... 

Hold on, maybe the real C DID use these values later! Consider: the real source might have returned or stored something after the call. E.g., `func_8013AA24(iVar11, param_1);` then maybe `return bVar1;`? The function is declared void in our source. The target has no use after the call (insns 102-106: move a0,s8; jal; move a1,a2; j 274c). After the call, `j` to the epilogue. So no.

What about the call's delay slot: `move a1,a2` — param_1. No.

Hmm, what if the real C passed bVar1 to the call? `func_8013AA24(iVar11, param_1)` — target sets a0=s8 (iVar11), a1=a2 (param_1). No bVar1.

OK, let me look at this from a completely different angle: maybe the keepalives can be replaced by *real C that changes the order of the tests* to keep the pinned reg live, in a way that still matches the target. For w1: the target's bVar1 tests are &8, &0x60, &0x80, &0x10. The last one is &0x10. For t0 to be live past the &0x10 AND, there must be a later bVar1 use. None.

Unless... we reorder the *source* so that the &0x10 test comes before the &0x60/&0x80 tests, and the target order is actually achieved by the compiler? Let's check: if source order were: compute sVar5 for +8; if (&8) negate; compute sVar5 for +0xa; if (&0x10) negate; then if (&0x60||&0x80) negate +8? That would change the store order in the target (the +8 negation would come after +0xa). Target has +8 negation at 46-57 before +0xa. So no.

Alright. Let me spend a few more tries on the idea that the AND temp can be kept out of t0 by making it live longer *through the EBB* — e.g., by writing the test as `if ((bVar1 & 0x10) != 0) { *(s16*)(param_1+0xa) = -sVar5; }` and then *also* using the same value in a later real condition that the target has: is there a later comparison in the target that could be the same AND? The fc comparisons use different values.

I'm fairly convinced item 2's keepalives are genuine liveness levers. But wait — the task says these shards exist because *some* keepalives can be cracked by real C. Maybe the trick is: the real C uses the variable in a way that the compiler *cannot* prove dead because of aliasing! E.g., if bVar1 is read after the AND through a pointer, or the stores to param_1 alias bVar1's memory (but bVar1 is a local register var). 

Ooh — here's a real C idea: make bVar1 not a local but a *memory* variable whose reload is needed later... no, target has no reload.

Another idea: the target's t0 might be live past the AND because the AND's destination pseudo is *also* used as... hmm.

Let me test one specific hypothesis: maybe local-alloc assigns 126 to t0 only because of the REG_DEAD note; if the C expression made t0's value used in a *second* AND that cse merged... 

You know what? Let me look at the actual target's alloc: in the target (real build), what pseudo was the AND? We can't see the real build's RTL. But the target's code is the ground truth.

Let me try a completely different real-C spelling of the four bVar1 tests: compute a *mask sum*:
```
if (bVar1 & 8) ...
if (!(bVar1 & 0x60) || (bVar1 & 0x80)) ...
if (bVar1 & 0x10) ...
```
same.

Time check: ~02:30. Let me try the do-while and ternary candidates, then move to item 3, then come back if time.

Actually, let me reconsider the whole thing: maybe I should look for the *original* C in the repo history? The keepalive comments say "P36 rung B headers1". Maybe there's a pre-P36 version in git history of the header! If the original body (before levers) is in git history, I could see what C was there — but the levers were added to make it match; the pre-lever body scored >0. Still, history might show which C form was tried. Let me check git log for the header.
