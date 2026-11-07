---
ts: 2026-11-06T16:32:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2RkGieKeYLkpY1ea59Mi
---
Note the `done:` block is a third near-identical sequence: func_800D2D44(0); func_800468FC(); func_8002D8D4(); then func_80043830 instead of func_800D2AA0. So cross-jump merges block1 and block2 (identical 4 calls + j ret), not with done.

Interesting: the two if-blocks both `goto ret`. `ret:` label then `func_80010A98(); v0r=1;`. So both jumps target `ret`.

Now write the generator. I'll make a Python script producing variants by string replacement on w1.

Variants:
A. Tail / keepalive-related (v0r):
 a1: delete `    s32 v0r;\n` and `    v0r = 1;\n` (no v0r) → expect 20.
 a2: replace `    v0r = 1;` with `    v0r = 1;\n    (void)v0r;`
 a3: `    v0r = 1;\n    if (v0r) {\n    }`
 a4: `    v0r = 1;\n    i = v0r;`
 a5: `    i = 1;` and drop v0r (dead i)
 a6: `    v0r = 1;\n    if (v0r != 0) {\n        i = 0;\n    }` (i dead)
 a7: `    switch (v0r = 1) { case 1: break; }`
 a8: `    do { v0r = 1; } while (0);  // !FAKE: do-while`  (no, do-while requires marker only if used; it's a real C construct but harness may want marker; include marker)
 a9: `    v0r = 1, v0r;`
 a10: declare v0r as `s32 v0r = 1;` at decl and delete tail assignment (init at decl!) — C0505 catalog mentions "init at decl". With init at decl, flow might keep it? It's still dead. But try.
 a11: `    i = v0r = 1;`
 a12: use `arg0`? no.

B. Barrier / cross-jump:
 b1: wrap block1 in `do { ... } while (0);  // !FAKE: do-while`
 b2: wrap block2
 b3: wrap both
 b4: block1 calls reordered (swap 800468FC and 8002D8D4)
 b5: block2 reordered
 b6: block1 `func_800D2AA0((u8 *)0);`
 b7: block2 `func_800D2AA0((u8 *)0);`
 b8: block1 if spelled `if (!(func_800D2454(...) == 0))`
 b9: block2 if spelled `if (!(func_800D2704(...) == 0))`
 b10: block1 `if (func_800D2454(...))` (nonzero test)
 b11: block2 `if (func_800D2704(...))`
 b12: introduce temp `s32 r;` `r = func_800D2454(...); if (r != 0) {` 
 b13: temp for second
 b14: block1 with `goto ret;` replaced by `goto after;`? no, semantics differ.
 b15: duplicate a nop-ish statement in block1 that folds: e.g. `p = p;` (self-assign folds to nothing) — would it leave an RTL insn? Probably folds away.
 b16: in block1 add `D_800EC9F4 = D_800EC9F4;`? changes code.
 b17: convert the two ifs into `if (f1()) {...goto ret;} else if (f2()) {...goto ret;}` (else-if chain)
 b18: swap the two blocks (second if first)
 b19: use `for (;;) { ... break; }` around block1? no.
 b20: `while (0) { calls; }` in block1 → folds away.
 b21: put `ret:` label before the first if? no.
 b22: make block1's calls into a `switch (0) { default: calls; }`
 b23: make block2's `goto ret` into `if (1) goto ret;`
 b24: block1 `goto ret; ret: ` hmm.

C. Pin / register:
 c1: declare v0r before i
 c2: declare v0r in a nested block at end: `{ s32 v0r; ... }`
 c3: reuse i as the value: `i = 1;` at end (dead)
 c4: `p` declared `s32 *p = (s32*)arg0;` init at decl, drop the assignment
 c5: reorder decls (i before p)
 c6: make i `s32 i = 0;` init at decl
 c7: v0r as `s32 v0r = 1;` decl + tail no-op (same as a10)
 c8: tail `func_80010A98(); return;`? return in void is fine.

Also combine a few.

That's ~35. Let me write the generator. I must be careful that all variants remain lever-free (no asm, no register). Yes.

For the do-while marker: the constraint says `do{}while(0)` only with `// !FAKE: do-while`. So append the comment on the same line.

Let me write gen1.py.
