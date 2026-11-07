---
ts: 2026-11-06T15:24:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oce5z1aAperEm2is4uDv
---
s1's residual is identical to nolaunder's: `beq s0,v0,71c; j 740`. So the compiler produced: `if (t==3) goto sel_054; if (t==5) goto sel_094; ...`. It optimized the two gotos to sel_test into direct jumps (threading), and the test folded.

So the jump threading happened at the *branch* level (t==5 → sel_094 directly), not the test. Hmm.

Wait, s1's mine[97] = `beq s0,v0,71c` (t==5 → sel_094) and mine[99] = `j 740`. So the compiler turned:
```
if (t==5) goto sel_test;   → at sel_test, t==5, test true → goto sel_094
```
into `beq t,5,sel_094`. So the compiler DID know t==5 at sel_test and threaded the jump to sel_094. Similarly for t==3 it went to sel_054.

So the intersection at sel_test was NOT conservative — gcc's jump threading propagated each edge's knowledge separately. That's jump.c's `thread_jumps`/`if_then_else`.

Hmm. So the join doesn't help because jump.c threads it.

What if the test at the join is not a simple jump (so it can't be threaded)? E.g., if the test does something before the jump. But the target's test IS a simple jump.

OK, at this point I'm fairly convinced it's a wall. Time: 08:25-ish. Item 2 ~15 min. Hmm, still short of 20.

Let me do a few more minutes of tries with different ideas:

1. What if the t==5 test is a `switch` case (label boundary) and the test is inside the case body? l1 tried this and scored 4. Let me look at l1's diff to see if the test survived... it scored 4, same residual, so no.

2. What if we prevent jump threading by making the t==3 and t==5 paths differ slightly before the test? E.g., the t==3 path does a dummy operation that's removed later. Then threading is blocked because the blocks differ. But the dummy must be zero-cost after optimization... and if it's removed before jump, threading happens.

3. What if we use a `switch (t)` with cases 3 and 5 whose bodies are the same label? gcc would merge the cases.

4. What if the test compares `t` with a value that's in a *different register* due to the structure? no.

Let me try one more idea: make the test's block have two predecessors that reach it via *different* code so threading can't fold:
```
if (t == 5) {
    goto sel_test;
}
if (t == 3) {
    goto sel_test;
}
```
s2 (t==5 first) scored 31 — because the order changed the switch table layout. s1 scored 4.

Hmm.

Let me try: `if (t == 3) goto sel_test; if (t == 5) goto sel_test;` but with the test as `if (t < 4)` or something non-threadable? At sel_test, t ∈ {3,5}: `if (t != 3) goto sel_094` — for t==3 false, for t==5 true. jump.c threads each edge. Any test would be threaded if it's a simple jump on t.

To prevent threading, the test must not be a simple conditional jump — e.g., a comparison whose result is used twice, or a call.

The target's test IS a simple conditional jump (bne). So the target's compiler didn't thread because the asm made it opaque.

OK. Wall.

Let me do a final check of the time and finalize. It's ~08:27. Item 2 from ~08:10 → 17 min. I need 20. Let me do 3 more minutes with 2-3 candidates.

Actually — one more idea that's quite different: the *dead-reset* trick applied to break the jump equivalence via a store to memory that cse treats as invalidating? cse invalidates register equivalences on `set`. What if `t` is stored to a local (address-taken) and reloaded? Changes allocation.

Another: what if we make the t==5 test compare `t` with a value that cse can't fold into a constant — e.g., `if (t == (s16)D_8011514A)`? That's a memory load (extra insn).

OK. Let me finalize.

Actually, hold on. Let me reconsider the problem statement: the item's `kinds` is launder. Maybe the expected solution is simpler than I think and I'm missing a plain-C spelling that keeps the redundant test. 

What if the launder is replaced by a `do { } while (0)` (C0535) — we tried g2 (empty do-while) → 4. And g3/g4.

What if the launder is replaced by the *dead-reset* pattern applied to a DIFFERENT variable that cse uses for the equivalence — specifically, the register holding the constant 5! The RTL showed `(ne (reg t) (reg 116))` where reg 116 holds 5. cse's equivalence: t == 116 and 116 == 5. If we invalidate the *116* equivalence... but it's a compiler temp.

Hmm, what if the source's t==5 test uses a variable `five` that is *reassigned* (dead) after the branch? Then cse's equivalence five==5 is invalidated, so t==five doesn't imply t==5! Let's think:

```
s32 five = 5;
...
if (t == five) {
    five = 0;          // dead reset, invalidates five's const equivalence
    if (t != 3) goto sel_094;
    ...
}
```
cse: at the branch, records t == five and five == 5 → t == 5. Then `five = 0` invalidates five's equivalence. Does that invalidate t's equivalence (t == five)? cse's equivalence classes: setting five breaks five's class membership; t is in the class "t == 5"? Hmm, cse's jump equivalence records t == five as an equivalence class {t, five, 5}? Actually record_jump_cond merges the two operands' equivalence classes. If t and five are merged into one class with the constant 5, then setting five would split five out but t might remain with the constant 5.

Hmm, but if cse records the jump equivalence as "t == five" (a reg-reg equivalence), and five's class contains the constant 5, then t's class also contains 5. Setting five doesn't remove 5 from t's class.

Hmm.

What if the test is `if (t == five)` where five is NOT known to be 5 but is 5 at runtime? We need five = 5 without the compiler knowing. A dead-set trick: `five = 0; five = 5;`? known.

Hmm, what about `five = (s16)a1;` — then five == t, and `if (t == five)` is always true → folds.

OK, I'll finalize now. Let me do the time check and write the final notes/results.

Actually, let me reconsider the "lines" column: 101 for this item. Item 1 had 202 with a 32-line body. Hmm, 202 ≈ 203 lines? No, item 1's body is 32 lines. Item 2's body is 203 lines and its "lines" is 101. Item 3/4/5 are 101. Weird. Maybe "lines" = something else (like the number of scored lines/diff?). Whatever.

Let me finalize item 2.

Actually — wait. I want to double-check one thing: is the target really *impossible* lever-free? The moves.md entry for func_8018656C (line 192) says a launder was cracked with "empty do { } while (0) + a real 2nd set (the same expression) inside the true arm". Hmm — "a real 2nd set (the same expression)". Let me look at that entry: "the launder on diff -> empty do { } while (0) + a real 2nd set (the same expression) inside the true arm; the 'if(c) return 1 else return 0' -> 'return c' fold stays blocked".

Interesting: a real 2nd set of the *same expression* inside the true arm. In our case: `t = (s16)a1;` again inside the t==5 arm? We tried f5 (`t = (s16)a1;` before the test) → 4 (folded). Hmm, but maybe the trick is different: the 2nd set must be of the same expression *and* the fold blocked by the do-while EBB split.

Let me look at the actual case: func_8018656C's launder was on `diff`, and the fold was `if(c) return 1 else return 0` → `return c`. The 2nd set kept the fold from firing. The mechanism there: the 2nd set made diff multi-set so flow couldn't prove it 0/1?

Hmm. In our case, the "2nd set" would need to make t's value unknown. `t = (s16)a1` is the same expression — but cse knows it equals 5? Actually, does it? cse's equivalence from the jump is t == 5 (or t == five). After a set `t = (s16)a1`, cse's equivalence for t becomes (s16)a1. Is (s16)a1 known to be 5? cse would need the equivalence (s16)a1 == 5 from before. The original t was set to (s16)a1 BEFORE the branch; cse may have an equivalence t == sign_extend(a1). If the jump equivalence merged t's class with 5, then (s16)a1's class also has 5? Hmm.

f5 scored 4 — so it folded. But f5 placed `t = (s16)a1;` immediately before the test (inside the t==5 block). Maybe the compiler simplified it to `t = t` (since t already holds (s16)a1) and removed it. 

What if we force a *different* register for the recomputation: `t = (s16)a1;` where a1's value is reloaded? Hmm.

What about `t = (s16)(a1 + 0x10000 - 0x10000);`? folds.

Let me try the "same expression 2nd set" with a do-while wrap, mimicking the recorded crack:
u1: `do { t = (s16)a1; } while (0);` before the test.
u2: `t = (s16)a1; do { } while (0);`

Cheap. Let me test.
