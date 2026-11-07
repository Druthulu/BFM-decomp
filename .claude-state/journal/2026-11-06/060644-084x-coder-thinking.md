---
ts: 2026-11-06T13:06:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mSh8VBxZqFXSXsOcAKv4
---
31 tries on item 3. Best 9 (a1 and many others). Time: item 3 started ~06:05, now ~06:15.

Record: WALL best 9, tag dbr-delay-fill.

Actually, hold on. Let me reconsider one thing: is the residual really only the nop? Yes: score 9 is all the shifted jump targets caused by the 1 missing nop.

Hmm, could I add a *real* insn that the target also has elsewhere... no, count is fixed at 218.

One more idea before recording: what if the second test is written so that the `li v0,10` comes *before* the first branch in source, i.e. hoist the constant? Like:

```
s16 t = 0xA;   // no
```

What if I write the second comparison as `if (D_8011512C == 0xA)` but move the *load* of D_8011512C to after the first test:
```
if (D_8011512C == 4) return;
if (D_8011512C == 0xA) return;
```
→
```
if (D_8011512C == 4) return;
{ s16 v = D_8011512C; if (v == 0xA) return; }
```
t5 = 9 (with v shared). With a fresh load it'd be an extra lh.

OK, record. Let me also double check: is the *nop* perhaps fillable in another way — what if the first branch's delay slot is filled with the *load*? No.

Record WALL.

Actually, wait. I want to double-check one specific alternative: `if (D_8011512C == 4) { return; }` — what if I make the first test a `switch` with a single case? `switch (D_8011512C) { case 4: return; }` — gcc might emit a compare tree with different delay-slot behavior. Cheap to try. And `if (D_8011512C == 4) goto epi; ... epi: return;`.

Let me try 2-3 more (bonus) then record. Actually 31 tries is enough; but a couple more cheap shots are fine. Let me do 3 more with a fresh idea: put the two tests in the opposite nesting with `&&`:

x1: `if (D_8011512C == 4 || D_8011512C == 0xA) return;` (a4 dup)
x2: `switch (D_8011512C) { case 4: return; }` then the second if.
x3: make the first test `if (D_8011512C == 4) { return; }` and the second `if (D_8011512C == 0xA) { return; }` with `i` initialized before.

Let me just do x2 and record.

Actually, time is better spent on items 4 and 5. Let me record item 3 now.

win.c = a1.c (barrier removed, score 9, 217 ins).

Hmm, but for a WALL, "best = lowest score of a lever-free body" = 9.

Let me write notes, results row, moves line.
