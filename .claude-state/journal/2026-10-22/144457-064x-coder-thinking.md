---
ts: 2026-10-22T20:44:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_b9D1YHEoblrI2B2Kqh1e
---
All 4, as expected. So the n2=2 was an artifact of uninitialized `off` (invalid C). Discard.

Best legitimate = 4 (gen_base and many). Hmm.

Let me think harder about the target's mechanism. The target has `addiu a1,v1,0x658C` in the delay slot of `j 4664`. This is a two-step address computation, which gcc does when `it` is in a register and the addend is an immediate. If `it`'s value were known constant at that point, gcc would fold into `lui a1; addiu a1,lo+K` (2 insns) — as in mine. The target has 3 insns (lui v1; addiu v1; addiu a1). So the target's `it` is a register value not known constant.

In the target, `it` = v1 = D_80120194 loaded by lui/addiu. If cse knew v1 = symbol, it would fold. So the target's `it` value is opaque to cse = the launder.

Since the item's kinds = launder, this is a WALL of the cse-const-addr family. The prior coder's 35 variants agree (best 4).

But wait — the launder is in TWO places in the def (else branch and test branch). Maybe only one is needed? The kinds row says launder must go entirely (no launder of any kind). So both must go.

Is there any real-C way? Hmm, what about making `it` a *pointer* and `p` an int, with the add done via pointer arithmetic on a *u8* pointer: `p = (s32)((u8 *)it + 0x658C);` — cse folds (tested n3=4).

What if the add is done via `it` being a `s32` but the constant stored in a *parameter*? No.

What about a `switch` on a value that forces... no.

What if we use the *global variable itself* as the base: `p = (s32)D_80120194 + 0x658C;` — folds to symbol+K (that's what mine does).

The target keeps the symbol and the addend separate, which is the *default* when the value is in a register (opaque). So the only way is opacity.

Real-C opacity without asm: a volatile read or a memory load. What if the value comes from a *global variable* that holds the address? There's no such global.

What if `it` is assigned from `(s32)D_80120194` and then passed through a *local array*: `arr[0] = it; it = arr[0];` — gcc optimizes it away (constant propagation through memory? gcc 2.7 might not; it might do a store/load!). Let me test: `s32 t[1]; t[0] = (s32)D_80120194; it = t[0]; p = it + 0x658C;`. gcc's cse might not propagate through memory → it = lw from stack → adds 2 insns. Not good, but maybe the stack slot is optimized... Let me test; if the store/load survive, score will be high.

Alternatively, use the *volatile* trick: `*(volatile s32 *)&it = (s32)D_80120194; p = it + 0x658C;` — forces a store+load (2 extra insns). Bad.

Hmm. What if `it` is a `static` local? Then the store/load are memory ops to .bss/.data — 2 extra insns.

So no.

Given the wall family and the prior 35 tries, plus my 20, I'll wall this too — but I must satisfy "≥20 min and ≥30 tries". I have ~35 existing scored candidates (gen_*) + my ~20 = plenty of tries. Time: started 14:36, now ~14:50 (14 min). Let me spend a few more minutes on genuinely new ideas, then wall at best 4.

Actually, wait. Let me reconsider the problem: maybe the target's `it` is NOT opaque; maybe the fold in mine comes from a *different* place. In mine (gen_base), the else branch produced `lui a1,0x0; addiu a1,a1,25996` — a1 = symbol+0x658C. The target has v1 = symbol, a1 = v1+0x658C.

What if the C computes p differently: `p = it; p += 0x658C;` where `p` is a *pointer* (`u8 *p`)? Then p += K is pointer arithmetic; gcc would fold. But if p is used later as `p != base` (s32 compare)... the C's p is compared with base and used as an address. If p were a pointer, `*(u16 *)p` works and `p -= 0x10C`... The target's if branch has `addiu a1,v1,0x6480` — also two-step. So both branches keep the base and add.

Maybe the real source uses a *struct* for the base? E.g. `base` is `s32` in the if branch — the src def has `s32 base = (s32)D_80120194; p = base + 0x6480;` and NO launder there, yet the target doesn't fold. Why not? Because `base` is LIVE (used in the loop). That confirms the live→no-fold rule.

So for the else branch, `it` must be live at the add. In the target's code, v1 (it) is reassigned at 4664 — but the add at 4658 happens BEFORE the reassignment, and at that moment v1 is live? Live means "used later on some path". After the add, the only use of the first it is... none (test reassigns). So it's dead.

UNLESS the source's `copy: p = it;` is reached from the else block too — i.e., the copy label is *before* the reassignment on some path. Hmm, what if the source is:

```
else {
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    p = it;
    goto found;
test:
    it = (s32)D_801202A0;
    ...
}
```
Here, is there a path from `p = it + K` to `copy:` without passing through `test:`? No: `goto test` jumps to test.

But wait — in the target's assembly, the copy block is *between* the else block's jump and the test block. The jump at 4654 targets 4664 (test), skipping copy. So no.

Hmm, unless gcc's CFG sees the copy block as reachable from the else block via *fallthrough* in the RTL before the jump is emitted? No.

Let me try one thing: maybe the C's `copy:` block in the original used `it` in a way that made the compiler keep it live, e.g. `copy: p = it; goto found;` where `it` at copy is the *first* it (D_80120194)? That would be a different program semantics: if a zero slot is found, p = D_80120194?? No, that makes no sense... unless the found slot is relative.

Wait, actually, let me reconsider: maybe `it` is not reassigned at test! What if the test block's `lui v1,D_801202A0` is a DIFFERENT variable that happens to reuse v1 (register reuse)? Then `copy: p = it` uses the first it (v1) — but v1 was reassigned, so no.

Unless the copy path's `move a1,v1` uses a v1 that holds the first it because the test block's reassignment is *after* the copy in program order! Look at the layout: copy block at 465c-4660, test block at 4664+. The copy block is *before* the test block in the layout, but reached from the loop at 467c (after the test block). Since the loop is after, v1 = the scan pointer at copy. Unless the copy path is reached from somewhere else... only 467c.

Hmm, hold on: is the `beqz v0,465c` at 467c the only entry? What about the `j 4664` at 4654? That goes to test. Yes.

OK so `it` (first) is dead. The launder is the only explanation. Wall.

Hmm, but one more: what if the launder's effect can be achieved by making the *assignment* itself non-foldable: `it = (s32)D_80120194;` — what if the symbol is read through a *pointer dereference* that gcc can't fold: e.g. `it = (s32)(&D_80120194);` no. The value is the address of a symbol; any C spelling of "address of D_80120194" is a link-time constant.

BUT: what if we take the address of a *local* that's initialized... no.

What about `it = (s32)D_80120194 + (a0 & 0x0);`? folded.

What about `it = (s32)((u8 *)a0 - (u8 *)a0) + (s32)D_80120194;`? folded (a0-a0 = 0).

What about using an uninitialized variable (UB) — no, invalid.

What about `it = (s32)D_80120194; if (a0 == 0x7FFF) it += 4;` — adds a compare, changes code.

So: WALL at best 4.

Wait, but the prior coder's best is 4 and I found nothing better. Let me do a couple more quick tries on the "it live" angle:

Idea: make the first `it` live by using it at the `copy:` block in a *harmless* way that the compiler keeps, e.g. `copy: p = it;` — that's already there but uses the current it. What if I add `if (it == (s32)D_80120194) p = p;`? folded.

Idea: change the loop to use a separate variable `q` for the scan, and at copy use `q`; then `it` (first) is dead → fold (same).

Idea: make the first `it` used in the *zero* block: `zero: p = 0; if (it) ...` — changes code.

I'll wall at 4.

Actually, hmm, wait. Let me reconsider the target's else branch ONE more time. The target:
```
464c lui v1, D_80120194
4650 addiu v1,v1,0
4654 j 4664
4658 addiu a1,v1,0x658C
```
This is 3 insns + a jump. Mine (gen_base):
```
lui a1, symbol+0x658C
addiu a1,a1,0x658C
j 4664
nop
```
So mine has a nop in the delay slot; the target fills it with the addiu.

What if the fold in mine is prevented by using a *different expression* for the base that cse can't fold because the symbol is loaded into a *different* register first: e.g. `it = (s32)D_80120194;` where `it` is declared `volatile`? No.

What about `it` being a `u32` and the add being `p = (s32)(it + 0x658C);` — folds.

Let me try one specific thing: the *type* of the symbol D_80120194. What is it declared as? Maybe `u16 D_80120194[]` or a pointer. `(s32)D_80120194` — if D_80120194 is an array, `(s32)D_80120194` is the address. Fine.

What if I use `(s32)&D_80120194[0]`? Same.

OK — one more idea, then wall: what if the *if branch's* structure is used for the else branch, i.e., write `s32 base = (s32)D_80120194;` (a declaration with initializer) in the else block, then `p = base + 0x658C;`. A declaration with an initializer might produce a different RTL (a separate set) and... the fold would still happen since base is dead.

Hmm, but in the if branch `base` is live. In the else, no.

Actually! What if the else branch's `it` is live because the *loop* also uses `it` as the scan pointer and the compiler's dataflow considers the loop's use a use of the same pseudo? The loop's use is after the reassignment, so no.

Alright: WALL. But the prior coder's notes? None. I'll record best 4 (gen_base), tries ~55 (35 prior gen candidates + 20 mine).

Hmm, wait. Before walling, let me check whether the *src def* (with launder) scores 0 — to confirm the target and the wall's cause. And let me check the "which launder is needed" question: maybe removing only one launder gives 4 while the other matters. The kinds row is launder (both). Fine.

Let me confirm the src def scores 0.
