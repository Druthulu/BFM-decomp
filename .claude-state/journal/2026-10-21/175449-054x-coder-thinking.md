---
ts: 2026-10-21T23:54:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_7Wbq1x5wfcqvjVOAmQqH
---
cc1_dumps_tu.sh needs a work dir containing <fn>/t.c — a spliced real TU. For a header item, the "real TU" would be an includer's .c file (with the header included). I could use an includer .c file directly as the first arg (the script accepts a .c FILE).

But it needs the header's content — the includer includes it via `#include "../shared/ov/func_8014C308.h"` ✓ (it compiles the real TU with the header as-is → the pinned version). But I want to dump MY candidate body, not the pinned one. I can create a modified copy of the includer .c with the header content replaced... but the includer includes the header by path; I'd need to shadow it.

That's what the --try scratch does (shadow include dir). Complex.

Time check: this is getting expensive. Let me weigh: 7 items, ~35 min spent on item 3. Remaining 6 items need ~2.5-3 hours. The overall session may be long but that's the task.

DECISION for item 3: try ONE more cheap idea (the "1"-pseudo's qty boost via a different structure), then record a WALL with a new tag and move on. If time remains at the end, come back.

Actually, let me try the most promising remaining idea: make the "1"-pseudo GLOBAL (live across blocks) with a copy preference to $2. Currently the "1" is set in the chain block and used in the arm blocks — is it global? Its live range crosses block boundaries → global-alloc handles it → and global-alloc would assign it a callee-saved reg ($16+) normally, but the copy preference (to $2) can win.

Hmm, but in mine, the "1" is NOT a pseudo at all (folded). So the question stands.

What if the "1" is used in a way that creates a copy preference: e.g. the arms `return v0;` where v0 is a pseudo → the copy to $2 is exactly the copy preference. But the folding kills the pseudo first.

Hmm, the folding (combine) happens in the RTL optimizer, before regalloc. Combine folds `set $2, v0` where v0 = 1 → `set $2, 1`. So the pseudo dies in combine. Yes.

UNLESS the copy is not foldable: e.g. if the pseudo's value is a constant but the copy has a "register" destination that... no.

Hmm, what if the pseudo's set is not a constant but the pseudo's value is *conditionally* 1? Like:
```c
v0 = (arg2 == 9) ? 1 : 1;   /* folded */
```

What if v0's value comes from a *function call*? e.g. `v0 = func();` where func returns 1? Not the ROM.

OK. What if we avoid the constant by making the "1" the result of a computation that the ROM does too? Look at the ROM again: `li v0,1` — could it be the result of `sltu`/`slt`? No, it's `li`.

Alright: the conclusion is that the ROM's `li v0,1` in the delay slot comes from a hard-reg pseudo (the ROM's original source likely had `register int v0 asm("$2")`? unlikely) OR from a compiler behavior difference.

Hmm, hold on. Actually! What about the possibility that the ROM's source had the "1" assigned to a variable that is ALSO assigned the final comparison result — i.e. variant F — and the compiler kept it as a real variable because it has 2 sets! Then the "1" set (const 1) would still be folded into the copies... but the SECOND set (the comparison) is real → v0 is a real pseudo → global-alloc sees v0 with a copy preference to $2 (it's returned) → v0 gets $2 ✓✓ → and the "1" set is materialized... where? If v0 = 1 is folded into the copies, the copies are `set $2, 1` — but if v0 is $2, the copies are no-ops → the arms branch directly to the epilogue ✓ and the "1" set remains in the chain block as `set $2, 1` → materialized as `li v0,1` in the chain block ✓✓✓ → sched1 places it in the delay slot ✓.

YES! That's variant F's shape! But F scored 18 — because of the final expression: F wrote `v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1; return v0;` and gcc produced `lw v0,376(a1)` (a1 instead of a0!) and other differences.

Hmm, in F the diff showed mine[33] `lw v0,376(a1)` vs target[31] `lw v0,376(a0)`. Interesting — the argument register differs: mine loads from a1, the target from a0. That means in F, the compiler swapped the roles of arg0/arg1 (maybe because `arg0` was used only there...). Hmm, actually it means my F candidate's final expression used a1 — wait, no: my F wrote `v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;` → the load is from arg0 = a0. But the compiled code loads from a1?! That means the compiler assigned the parameters differently... Hmm, actually the head of F matched the target exactly (ins 0..19 use a1) — so a1 = arg1 ✓. And the final load should be a0.

Hmm, unless gcc swapped the parameter registers: since the function's params are arg0..arg3 = a0..a3, and the head uses a1 (arg1) ✓, the final load should use a0.

Unless... in F, the "arg0" name got shadowed? No. Hmm, `*(s32 *)((u8 *)arg0 + 0x178)` — 0x178 = 376 ✓. So `lw v0,376(a1)` is wrong?! Unless gcc swapped arg0/arg1 in the register assignment because... no, params are fixed.

OH WAIT. Maybe in F the value `arg0` was passed... hmm. Whatever, F had issues.

Let me retry F with a cleaner tail: use a SEPARATE variable for the final result (so v0 keeps its "1" role but is a real variable):

```c
    s32 v0;   /* the 1 */
    s32 v1;   /* const temp */
    s32 v2;   /* final result */
    ...
            v0 = 1;
            v1 = 9;
            if (arg2 == v1) return v0;
            v1 = 0x11;
            if (arg2 == v1) return v0;
            v1 = 0x29;
            if (arg2 == v1) return v0;
            v1 = 0xA;
            if (arg2 == v1) return v0;
            v2 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;
            return v2;
```
Here v0 has 1 set + 4 uses — still foldable ✗ (v0 is not reused for the final result, so the pseudo still dies).

So F's shape (v0 reused for the final result) is the one that keeps v0 alive. Let me redo F carefully and see the diff. In F the final expression was `v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1; return v0;` — the compiled code showed `lw v0,376(a1)` — hmm, that IS strange. Unless the compiler CSE'd: `arg1` vs `arg0`...

OHHH. I bet the issue is that in F, `v0` (holding 1) and the final value are the same variable, and gcc's "compare with 0" logic... no, the register operand a1 vs a0 is about WHICH argument register holds arg0.

Hmm, wait: maybe in F the compiler decided to swap arg0 and arg1 because arg0 is only used once and arg1 many times? No, parameters are fixed to a0, a1...

Hmm, unless the head in F also differs: the diff showed the head ins 0..19 matching the target (using a1) — so a1 = arg1 ✓, and then `lw v0,376(a1)` = loading from arg1+0x178?! But my source says arg0+0x178. So gcc compiled arg0 → a1?? That can't be...

...unless the `!= arg1` part is what got CSE'd: the target's ins 33 is `xor v0,v0,a1` (comparing with arg1) ✓ both have that. And the load: mine[33] `lw v0,376(a1)` vs target[31] `lw v0,376(a0)`.

Hmm, so in F the load came from a1 and in the target from a0. Both have `xor v0,v0,a1` afterwards? Let me look at F's full diff again... The diff printed only up to mine[36]. I saw mine[33] `lw v0,376(a1)`. Hmm, and then presumably mine[34] `xor v0,v0,a1`? Hmm, but then the loaded value would be from arg1 and compared with arg1 — nonsense.

Wait, maybe I misread and it's `lw v0,376(a0)`. Let me re-read the F diff output:

```
  replace mine[31:34] target[31:32]
       31  j	6ac4 <func_8014C308+0x9c>        | lw	v0,376(a0)
       32  li	v0,1                            | --
       33  lw	v0,376(a1)                      | --
```
So mine[33] = `lw v0,376(a1)`. Hmm. And in the target, ins 31 = `lw v0,376(a0)`.

Interesting: mine has `lw v0,376(a1)` — so in F, the final expression's load used a1. But my F source says `*(s32 *)((u8 *)arg0 + 0x178)`. Hmm! Unless the compiler CSE'd the earlier `lw v0,88(a1)`? no, different offset.

OH WAIT. I bet gcc noticed that `arg0` is unused elsewhere and `arg1` is used a lot, and... no. Hmm, could it be that the F candidate I wrote had `arg0`/`arg1` mixed up? Let me re-read my vF file: I wrote

```c
            v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;
            return v0;
```
Yes, arg0. So gcc compiled the load from a1?! That means in F, the parameter registers got swapped: arg0 → a1, arg1 → a0?? But the head uses a1 for the mask loads (arg1+0x0 etc.) ✓ and it matched the target...

Unless gcc swapped them BECAUSE in F, `arg0` is used once and `arg1` is used many times, and gcc 2.7's "parameter renaming"?? There IS an optimization in old gcc: "reverse parameter order"? no.

Hmm, whatever. F's approach: make v0 a real variable by reusing it. Let me test a variant F2 that keeps the final return expression EXACTLY as the original (`return *(s32 *)((u8 *)arg0 + 0x178) != arg1;`) but where v0 is reused... can't (v0 must hold the "1").

Alternatively: make the "1"-pseudo real by using it in a harmless way that gcc keeps: e.g. `v0 = 1;` and then in the final expression: `return v0 & (*(s32 *)((u8 *)arg0 + 0x178) != arg1);` → adds an `and` ✗ (the ROM has no and).

Hmm, but hold on: `v0 & x` where v0 = 1 → gcc folds to x ✗ (and the pseudo dies).

OK: the only way to keep the "1" alive is to have v0 hold the final result too (F). Let me retry F but check WHY the load used a1. Maybe I should write the final expression differently to keep the a0 load:

```c
            v0 = *(s32 *)((u8 *)arg0 + 0x178);
            v0 = v0 != arg1;
            return v0;
```
Hmm, that's 2 statements. Or:
```c
            v0 = (*(s32 *)((u8 *)arg0 + 0x178) != arg1);
            return v0;
```
same as F.

Let me try a variant where the final expression is computed into a DIFFERENT variable and v0 (=1) is also given the final value...

Actually, let me think about what the target's tail looks like:
```
30 nop
31 lw v0,376(a0)
32 nop
33 xor v0,v0,a1
34 j +0x94
35 sltu v0,zero,v0
```
So the final result is computed in $2 (v0) and returned. If in the source the final expression is `return *(s32 *)((u8 *)arg0 + 0x178) != arg1;` then gcc computes it into $2 directly (the return reg) ✓ — that's the natural case (no variable).

If the source is `v0 = (...); return v0;` then v0 (a pseudo) must be allocated... the target shows the result in $2 → v0 = $2 ✓ (with the copy preference). Both work.

So F's tail is fine in principle; the problem was the a1/a0 swap and possibly the "1" not being kept.

Hmm, the a0/a1 swap in F: since F's head matched the target exactly (a1 for arg1), and F's tail load used a1 for arg0+0x178 — that IS a bug-like difference. OH WAIT. I bet I know: in F, since v0 is assigned twice, gcc's "combine" might have CSE'd... no.

Hmm, hold on: maybe in F, the LOAD was `lw v0,376(a0)` but the diff's mine[33] line shows "lw v0,376(a1)"... Let me look at the raw output again:

```
       33  lw	v0,376(a1)                      | --
```
Hmm what if the argument registers in F were swapped because gcc's "tail call"... no.

Whatever, let me just try a couple of F-variants and see:
F2: `v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1; return v0;` (= F) → 18.
F3: use a separate var for the final and make the "1" real by an extra assignment to v0 that gcc keeps:
```c
            v0 = 1;
            ...
            v0 = *(s32 *)((u8 *)arg0 + 0x178);
            v0 = (v0 != arg1);
            return v0;
```
F4: hmm.

Let me think about WHY F differs. In F, the "1" pseudo: v0 = 1 (folded into copies?) — but if v0 is later reassigned, the pseudo v0 is a real variable with 2 sets → the "1" set is still foldable into the copies (constant 1) → the copies become `set $2, 1` → the arms branch to a shared block with `li $2,1` ✗ (that's what mine did).

So F should have the same problem. Indeed F's diff shows mine[31] `j 6ac4` + mine[32] `li v0,1` — the same "return-1 block" ✗.

So F doesn't fix it either.

=> The "1" must be a real pseudo with a non-foldable value. Since the value is the constant 1, the only way is for the copies to be foldable-but-the-set-kept...

Hmm, hmm. What if the copies are NOT copies? What if the arms' `return v0;` is spelled `return (s32)v0;` — same.

What if the arm returns are spelled as `return v0 + 0;`? → `set $2, v0+0` → combine → `set $2, v0` (fold the +0) → same.

What if `return v0 * 1;`? same.

OK. Let me try to think about what OTHER lever-free C could produce a `li v0,1` in a delay slot with the arms branching directly to the epilogue.

What if the value 1 is produced by a *comparison* that the compiler keeps in a pseudo? E.g.:

```c
if (arg2 == v1) return (arg3 == arg3);
```
→ gcc folds `arg3 == arg3` → 1 ✗.

What if the value is `1` but the compiler keeps the set because the pseudo is used in a *store*? no stores here.

What if the function's return type were `unsigned` and the value... no.

Honestly, maybe the answer is that this item's ROM bytes require the pin (it's a "constant pin" — the pin's purpose is to place a constant in a specific register). moves.md has similar walls: e.g. "expand-void-return", "sched1-birth-boost". Let me define a wall tag like "const-fold-return" or "lreg-const-fold": "the returned constant 1 is folded into the return copies by combine; only a hard-reg pseudo keeps the single li $2,1 in the chain block".

Let me do a couple more cheap experiments to make the WALL evidence solid:
1. Try making the "1" a variable that's also stored/used in a way gcc keeps → likely no.
2. Try `s16`/`u16` for v0 → tried (B, C).
3. Try the do-while(0) ref boost on v0 (the sanctioned trick): `do { v0 = 1; } while (0);` → this might make gcc keep the set in the chain block! Because the do-while gives the set a "loop" shape... Actually the T10 worked example used exactly this to win a register. Cheap to test. But is it a "new lever"? It's a loop-shape move (allowed per C0505 "loop shape") with the `// !FAKE: do-while` marker. Let me test it — if it gives score 0, I'd need to decide whether it's acceptable. The brief explicitly mentions "do{}while(0) only with // !FAKE: do-while" as a constraint on HOW to write it, implying it's permitted.

Let me test:
```c
        if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
            do { v0 = 1; } while (0);  // !FAKE: do-while
            v1 = 9;
            ...
```
And also the version with the do-while around the whole chain.

Let me write and test 2 variants:
J1: do-while around `v0 = 1;`
J2: do-while around the whole if-block body? Hmm.

Let me test J1 now.
