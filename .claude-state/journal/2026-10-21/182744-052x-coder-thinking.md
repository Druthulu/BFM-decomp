---
ts: 2026-10-22T00:27:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_NBCAaNFKzSDjtjAPfArY
---
c19 = 63 ins, same as c1. So the redundant set didn't block the fold (cse removed it early).

Let me reconsider: maybe the COND_EXPR fold is not the mechanism. Let me test the hypothesis directly: what if the true path's return is not 1 but something else? Hmm, the target has li v0,1.

Let me test a diagnostic: take the if-arm and make the true path `return 2;` — if the shape becomes "li v0,2", then the fold "return c?1:0" isn't happening (it'd be "return c?2:0" → also foldable to a select?). Hmm.

Better diagnostic: does the *first* block (which has the same "if (diff<0x10) return 1;" pattern) get folded? In the first block, the target has "bnez v0,9cfc; li v0,1" — NOT folded into "return the boolean"! And the first block's C (in c1) is identical to the source's first block, and the compiled first block in c1 matched the target exactly (the residual differences started at index 49, the second block).

So in the first block, GCC did NOT fold "if (diff<0x10) return 1;" into "return (diff<0x10)". Why? Because in the first block, the "return 1" path is NOT the only exit — the false path continues the function (more code follows). The fold "if (c) return 1; else return 0" requires both paths to return.

In the second block, the false path returns 0 and the true path returns 1 → foldable → folded.

So the fold is a CFG-level thing: both successors return constants → the phi folds to the condition.

To prevent the fold, the true path must contain something besides the return. Any real statement in the true path blocks it. But the statement must produce no code (else the instruction count changes).

The asm does exactly that (it's a "use" of diff with no code). In plain C, a statement with no code effect that survives to RTL:
1. A dead store to a local: gimplify keeps it; the fold is blocked (the true block has 2 statements); later, RTL DCE removes the dead store → the shape might be the target's! But c19 (a redundant set, not a dead store) got folded by cse. A dead store to a *fresh* variable (never read) might survive gimplify but be removed later by DCE. Let me test:
```
if (diff < 0x10) {
    s32 dead = diff;
    return 1;
}
return 0;
```
Hmm, but is a dead store a legit "lever-free" move? It's a statement with no effect — morally a launder (it exists only to perturb codegen). Hmm, but it's a "temp" in the C0505 sense...

Honestly, I think a dead store is exactly the kind of thing the task's constraint tries to exclude ("no new lever of any kind", "identity-statement launders do NOT count"). A dead store is an identity-ish launder: it doesn't change semantics.

Hmm, but hold on. Let me reconsider: is it really "no lever"? The lever kinds are: pin (register steer), launder (a statement that launders a value through a register to defeat optimization), barrier (memory ordering), keepalive (a macro/asm that keeps a value alive). A dead local assignment `dead = diff` IS a launder in nature (it launders diff into a dead temp to defeat the fold). The task says a launder must be GONE. Adding a dead store to replace an asm launder = replacing one launder with another → not a crack.

OK. So for item 1, the honest answer might be WALL.

BUT hold on. What about a *real* use of diff that has no code effect but isn't a launder? For example, if `diff` were used in the *return value* computation of the function in a way that produces the same instructions... e.g.:

What if the function's return value in the true path is `1` but computed as `(diff < 0x10) + 0`? no.

Hmm, what about a *different* structure: what if the two paths return 1 and 0 but one of them is inside a *nested* scope with a *different* function-level statement after? E.g. the false path returns 0 but there's also code after the if (unreachable) — that would prevent the fold!

Like:
```
if (diff < 0x10) { return 1; }
return 0;
```
vs
```
if (diff < 0x10) { return 1; }
if (0) { return 0; }   /* dead */
return 0;
```
Hmm, the `if (0)` is folded away at parse time.

What about making the false path have a real statement whose code is free? Same launder issue.

OK, so what if the *comparison* is restructured so the fold doesn't apply: the fold is "if (c) return 1; else return 0" → "return c". What if the true path returns 1 and the false path returns 0, but the *condition* is used in a way that's not a simple bool? e.g. `if (diff < 0x10) { return 1; } return 0;` — nope.

Hmm, what if the *function* returns something else and the caller... no, the signature is fixed.

What if the true path is `return 1;` and the false path is `return 0;` but they're in different *blocks* separated by a `goto`? Tried (c17).

What about the *order*: the false path first?
```
if (diff < 0x10) { return 1; } else { return 0; }
```
Same.

Let me try one thing: since the first block (which has "if (diff<0x10) return 1;" NOT folded) suggests the fold needs the false path to be a return of 0 — what if the false path returns 0 but the true path is not a "return 1" but a "return 1" that is *not* the only exit... hmm.

What if I make the true path `return 1;` and the false path *fall through* to a `return 0;` that is at the end of the function (as in c5)? c5 gave 8 ins (folded too).

OK: the fold is unavoidable with `if (c) return 1; return 0;`.

THEREFORE: to match the target, the true path must contain a non-return statement → any such statement is a launder/barrier-like lever... UNLESS the statement is a *real* computation whose result is used later in a way that produces the same code!

IDEA: What if the true path's extra statement sets a variable that is *used* later in the function? There is no later code (the function ends).

IDEA 2: What if the extra statement is in the *false* path (the "return 0" path)? The target's shape: the true path = {bnez → epilogue with li v0,1}; the false path = {j epilogue, move v0,zero}. Both are plain. The fold would be blocked if either path has an extra statement. But the fold's result (returning the boolean) would then still be avoided.

What if the false path's extra statement is a *real* store to memory? That changes the code (an extra sw). No.

IDEA 3: Use the *value* diff in the false path for real: e.g. the false path returns 0 — what if instead the false path returns `(diff < 0x10) ? 0 : 0`? Silly.

Hmm, IDEA 4: what if the two returns are not constants but the same *variable* set in both paths? Like:
```
s32 r = 0;
if (diff < 0x10) { r = 1; }
return r;
```
That's a phi → "return (diff<0x10)" again (the phi folds). Hmm, GCC would fold the phi to the condition. Yeah.

IDEA 5: What if the value compared is used in the *return* of a *nested* function call? No.

IDEA 6: What if the comparison is not a simple comparison but an expression that GCC compiles to slti+bnez without the fold? E.g. `if (diff < 0x10 && 1)`. The `&&` fold (in the C0505 catalog!) — `diff < 0x10 && 1` → GCC folds it to `diff < 0x10`. But the fold of "if (c) return 1 else return 0" might be blocked by the extra condition! Let me test: `if (diff < 0x10 && 1) { return 1; } return 0;`. Hmm, GCC's fold would simplify `c && 1` → c before the CFG fold. Hmm.

What about `if (diff < 0x10 || 0)`? Same.

IDEA 7: Use a comparison whose result is a *non-boolean* int: e.g. `if ((diff < 0x10) - 0)`. Hmm.

IDEA 8: Make the true path's return value 1 come from a *conditional* on a different condition: e.g. `if (diff < 0x10) { return 1; } return 0;` → the fold gives "return (diff<0x10)" → the boolean is the comparison result. In the target, the comparison result is materialized and branched. So the difference is *materialization*: in the target, the boolean is in a register and branched on; in c1, the boolean is returned directly.

The materialization is forced by the ASM. Without a use of the boolean...

AH WAIT. What if the boolean is used TWICE? E.g. in the true path, the boolean is used again: `if (diff < 0x10) { ... }`. Hmm, in the target, the boolean (v0) is used by the bnez. In c1, the boolean is the return value.

What if the source used the comparison result in a way that requires it twice? Like:
```
s32 c = (diff < 0x10);
if (c) { return 1; }
return 0;
```
Here the boolean `c` is used once (in the if) → the fold to "return c" applies → same as c1 (c18 = 63). Yeah, c18 tested that.

What if the boolean is used twice:
```
s32 c = (diff < 0x10);
if (c) { return 1; }
if (c) { return 1; }    /* silly */
return 0;
```
The second use is dead → DCE.

Hmm, what if the comparison result is used in a *real* way: e.g. the function returns `c ? 1 : 0` — the fold again.

OK, radical: what if the *true path* is not "return 1" but "return 1" via a *nested* if:
```
if (diff < 0x10) {
    if (1) { return 1; }
}
return 0;
```
The `if (1)` is folded at parse → same.

What about a `while (0) { }`? parsed away.

What about a `for (i = 0; i < 0; i++) { }`? folded.

What about a `switch (0) { case 0: break; }`? folded.

Hmm, what about a `do { } while (0);` (empty body)? The brief allows do-while with a !FAKE comment. An empty do-while(0) in the true path: gimplify creates a loop → the CFG has an extra block → the "if (c) return 1 else return 0" fold is blocked! And the empty loop is removed by later passes (loop removal), leaving the target's shape? Let me TEST it. That's cheap and it's an allowed construct (do-while(0) with a comment).

Let me also test the variant with a statement inside the do-while (but that'd be a dead store → launder-ish; the brief allows do-while but I'd rather keep it empty).

Let me write c22: empty do-while(0) in the true path of both arms.

Actually careful: an empty do-while(0) might be removed at gimplify time (gimplify has a pass that removes empty loops? In GCC 2.7.2, gimplify removes "empty loops" — there's `gimplify_loop`... hmm, in GCC 2.7.x, gimplify.c has code to delete empty loops? I believe `gimplify_stmt` handles loops; the removal of empty loops happens in the RTL/cfg pass (cfg cleanup) or in tree-level "pass_del"?

Let's just test.

Also test c23: the do-while with a real statement inside that is a *use* of diff (dead store to a temp) — as a fallback (if it works, I'll judge the legitimacy then; a "do { t = diff; } while (0);" is explicitly the pattern used in moves.md for ref-boosting, e.g. "do { r = p + i; } while (0);" in the T10 worked example! That example is in the project's own worked example (win.c has `do { r = p + i; } while (0);`) — so a do-while with a real assignment inside is an ACCEPTED lever-free construct in this project!

So c23 (`do { t = diff; } while (0);` in the true path) is acceptable per the project's own precedent.

Let me test c22 and c23.
