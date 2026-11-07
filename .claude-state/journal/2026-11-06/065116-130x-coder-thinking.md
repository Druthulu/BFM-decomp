---
ts: 2026-11-06T13:51:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SjrKErjzb9A7t3iqnCFf
---
Now, a final sanity check on the constraints:
- No `register` vars added: my win.c bodies only removed things. Item2's w1.c keeps existing pins (allowed).
- No `__asm__` added: item1's win.c has none (the function had none). Item3/4 win.c have the pre-existing pins? Item3 orig had pins aa/bb/cc — win.c keeps them (other kind, pre-existing). Item4 orig has no pins. Item5 keeps pins.
- do-while only with `// !FAKE: do-while`: check each win.c for `do {` lines and comments.
  - item3 win.c: `do { cc = bb + 8; } while (0);  // !FAKE: do-while` ✓ (and the pre-existing pixel `do {` loop at line 100 — that's a real loop, no comment needed).
  - item4 win.c: two do-while lines with !FAKE.
  - item5 win.c: two do-while lines with !FAKE.
Let me verify quickly.

- MATCH = the kinds in <dir>/kinds gone: barrier gone from items 1,3,4. Item5 PARTIAL keeps one barrier.

Let me grep the win.c files for asm/do-while.

Also double-check item1's win.c has no `__asm__` (it had none) and no register.

Let me also verify the results.tsv rows are exactly 5 (plus header).
