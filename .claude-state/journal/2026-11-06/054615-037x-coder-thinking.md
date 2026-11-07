---
ts: 2026-11-06T12:46:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mW2UE6fHhPJb2cNSJXnQ
---
e2's remaining diff is in the tc arm (barrier 3 region), not b2! So the do-while around the ua/ub block fixed b2 (the register allocation), and now the tc block layout differs.

Target:
```
270 beqz v0, ba8c
271 ? 
272 ?
273 addiu a0,v1,-256
274 ?
```
mine:
```
270 bnez v0, ba8c
271 andi a0,t0,0xffff  (from earlier)
...
273 (something)
274 addiu a0,v1,-256
```
Hmm: mine uses `bnez` (inverted) where target uses `beqz`. My c3b swapped arms gave `if (!tc) ua = ub; else ua = ub - 0x100;`. That produces bnez (branch if tc != 0 to else). Target uses beqz → the target's source is `if (tc) { ua = ub - 0x100; } else { ua = ub; }` with a *jump* over the else.

So the original arm order (if tc first) is right; the barrier was preventing... something. With the original order and no barrier we got score 10 (b3.c) and count 407 (missing j).

Now on the e2 base, let me try the original tc shape (if tc first) and see the score.

Also try: `ua = ub; if (tc) ua -= 0x100;`.

Let me create f-variants on e2 base with different tc shapes.
