---
ts: 2026-10-22T20:48:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wlp9ERhJnGGUqesYCanr
---
Key: after cse1, insn 74 is still `(set (reg 73) (plus (reg 74) (const 25996)))` with a REG_EQUAL note of the constant symbol+25996. So cse1 did NOT fold the add — it just added a REG_EQUAL note. The fold into `lui a1, symbol+25996` happens LATER (combine or reload), using the REG_EQUAL note.

So the difference from the target: the target doesn't use the REG_EQUAL note to fold. When does gcc use a REG_EQUAL note on an insn to fold the following code? In cse2 or combine. The note says "reg 73 = const(symbol+25996)". Then a later use of reg 73 (the beq with reg 74?) — the note would let cse2 replace uses of 73 with the constant. In the target, the value p (a1) is used in `beq a1,v1` (the loop) and `bnez a1` — those are compares/branches; cse2 could substitute the constant into the compare, but the target keeps `beq v1,a1`.

Mine folded at insn 24 (the delay slot): the `jump_insn 76` (j test) — wait, the fold produced `lui a1; addiu a1,lo+K` which is the *materialization* of the constant `symbol+25996` into a1. That's reload using the REG_EQUAL note to rematerialize the constant instead of using the register! I.e., reload decided to rematerialize `p` (reg 73) from its REG_EQUAL note rather than keeping it in a register.

Ah, that's the mechanism: `p`'s value is a constant (symbol+K) known via REG_EQUAL, so reload rematerializes it at each use (cheaper than a register). In the target, `p` is in a1 (a register) — so the target's REG_EQUAL note must be absent or not used.

Why? In the target, `p = it + K` where `it`'s value is opaque (launder) → no REG_EQUAL note → reload keeps p in a register → `addiu a1,v1,K`.

In mine, cse1 added the REG_EQUAL note because `it` (reg 74) had a known constant. So the note is the problem.

How to prevent the REG_EQUAL note with real C? The note is added by cse1 when it knows the operand's constant. So `it` must be opaque. Back to the same wall.

BUT: maybe I can make reload *prefer* the register over rematerialization: e.g., if p is used more times, or if the constant is expensive. Reload rematerializes a constant address when... Hmm.

In the target, p (a1) is used at: beq v1,a1, bnez a1, and the call arg (a1). That's 3 uses. In mine, p is rematerialized: `lui a1; addiu a1` once at the else block, then the same a1 is used? Let me look at mine's actual code: `21 lui a1; 22 addiu a1,a1,25996; 24 nop` then presumably `beq a1,v1` etc. So mine materialized the constant ONCE into a1 and used it — that's not per-use remat; it's just that the *register 73* was replaced by its constant value (a constant address), and reload materialized it into a1 because it needed a register for the compare/loop.

Hmm, so mine's a1 = symbol+25996 (one lui/addiu), the target's v1 = symbol and a1 = v1+K. Both end with p in a1. The difference is only whether the addition was folded.

So the REG_EQUAL note led cse2/reload to fold `p`'s value into the constant, and then the register 73 (p) is a constant → materialized directly.

To prevent: kill the REG_EQUAL note. The note exists because cse1 knew `it` = symbol. Opaque `it` → no note.

Alternatively: make `p` not rematerializable by using it in a way that requires a register with a specific... no.

OK, so it's the same wall. The launder is needed. WALL at 4.

Hmm, one more thought: what if the else branch's add is written so that cse1 can't compute a constant REG_EQUAL: e.g. `p = it + 0x658C;` where `it` is a *pointer* variable of type `s32 *`: `p = (s32)it + 0x658C`? cse1 knows the constant.

What if `it` is assigned *inside a loop* (do-while(0))? cse1's table... a loop body is a separate BB; the assignment and the add would be in the same BB (the do-while(0) body). But the loop note might make cse1 not fold? n4 (do-while(0) around the add) = 4.

What if the assignment is in one BB and the add in another, with a jump between? n1 (goto mid) = 4 — cse1 still propagated across? The goto creates a BB boundary, so cse1's table resets... but the fold still happened (n1=4). Hmm, maybe because the jump was to the next insn and gcc merged the BBs, or the REG_EQUAL note was added by the second cse pass.

Since cse1 is per-BB, but cse2 runs on the whole function (no, cse2 is also per-BB with more optimization).

What about an actual barrier between them: an `if` statement whose branch is never taken? e.g. `if (a0 == 0x7FFF) goto skip; skip:` — adds code.

I'm confident it's a wall. Time now ~14:55 (19 min). Let me write the notes/row after a couple more tries to pass 20 min, then move to item 3 (func_801372B0) which has 91 lines — bigger, and I have limited time? No hard limit overall, but I should be efficient.

Actually — wait. One idea I haven't tried: the note is `REG_EQUAL (const (plus symbol K))`. Reload rematerializes it. If p were used in a way that makes the register necessary and the constant expensive... The target has the same uses.

What if the add is done in a *different order*: `p = 0x658C + it`? Same.

What if the source writes `p = it + 0x658C` but with `it` being `s32` and `0x658C` being a *negative* constant or a different form? Same fold.

What about `p = it + 0x658C; p -= 0;`? folded.

OK. Wall.

Hmm, hold on. Let me reconsider the possibility of making `it` opaque with a *union type-pun of a runtime value*: e.g.
```
union { s32 v; void *p; } u;
u.p = D_80120194;   // hmm, D_80120194 is a symbol/array
it = u.v;
```
gcc folds the union member access (constant).

What about `it = (s32)D_80120194;` where D_80120194 is declared as an `extern` *function*? no.

What if `it` is assigned from the *low half* of a 64-bit value? gen_decl_ull = 35.

Enough. Wall at 4.

Let me now double-check the "best" candidate to report: gen_base.c (4). Are there other 4s with different diffs? All the 4s are MIXED 52 ins with the same else-branch fold. Fine.

Record: result WALL, best 4, tries ~55, wall tag `cse-const-addr` (existing: "cse folds or substitutes a constant/absolute address the target keeps base-relative"). Mechanism: cse1 adds REG_EQUAL const(symbol+0x658C) on p=it+K; reload rematerializes the constant into a1 (lui/addiu) instead of `addiu a1,v1,K`; the if-branch's base stays a register only because... hmm, wait, the if branch's p = base+K also gets a REG_EQUAL note, yet it's not folded. Why? Because in the if branch, p is compared with base (`p != base`) and then p is decremented in a loop — p is a *loop variable*, so it must be in a register (reload can't rematerialize it inside the loop). In the else branch, p is only used in compares/branch and the call arg — reload rematerializes it. Interesting!

So the difference: p in the else branch is used at a compare and the call; reload chose remat. In the target, p stays in a1.

Can I make p non-rematerializable? If p were used in a context requiring a register *modification* (e.g., p += 0), it'd be a real register... but that changes code.

Hmm, what about the REG_EQUAL note being killed by a *second set* of p? E.g. `p = it + K;` — single set with a note. If p had a second set (e.g., in the copy block: `p = it`), the note on the first set remains (notes are per-insn).

What if the add's result is *not* a single-set? E.g. `p = it + 0x658C; p = p + 0;`? folded.

What if we write `p = it + 0x658C;` and then in the copy block `p = it;` — that's the existing structure; p has 2 sets (one in else, one in copy). Yet reload still rematerialized the first set's value at its uses. Because the uses (beq, bnez, call) may be reached only from the first set path? p is used at the test/body blocks; both paths set p. The value in a1 at the compare... hmm, in mine, a1 = symbol+25996 materialized once before the jump, and the compare uses a1. So p (reg 73) was replaced by the constant and materialized into a1 at the definition.

Since the note is on the definition insn, cse2 or reload replaced reg 73 with the constant everywhere in that path.

To kill the note: make the add's operand opaque (launder) — the wall.

Alternatively: make the add produce a value that isn't a pure constant *and* is used in a register context: e.g. compute p as `it + K` and then use p in an arithmetic op... the target doesn't.

OK. WALL. Let me write it up. Time ~14:57 → 21 min. Good.

Actually, let me try ONE more thing: what if `it` is *also* used as the loop's scan variable and the compiler's REG_EQUAL note gets killed by the reassignment? No.

And one more: what if the else branch's `p = it + K` is moved into the *test* block (before the compare), i.e.:
```
else { it = (s32)D_80120194; goto test; copy: ...; test: p = it + 0x658C; ... }
```
No, p is used in the compare after test.

Let me also consider: the copy block sets `p = it` (reg 73 = reg 74). At the test block, `beq v1,a1` compares. Fine.

Wall it.

Write notes.md + results row + moves line. Then item 3: func_801372B0 (91 lines).

Note: item 3 is also a header with 141 includers. If any item MATCHes, I must verify all includers (141 × 2s = ~5 min each). For WALLs, no need.

Let me write item 2's files.
