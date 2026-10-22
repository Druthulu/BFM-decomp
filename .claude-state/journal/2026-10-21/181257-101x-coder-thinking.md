---
ts: 2026-10-22T00:12:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_6QvpZsGjQSc9UazIHfPr
---
This one (func_8017D81C) has two launders and a pin (z pinned to a0). The row kind is "launder"; the pin is another row.

The launders:
```
__asm__ __volatile__("" : "=r"(x) : "0"(x));
__asm__ __volatile__("" : "=r"(y), "=r"(z) : "0"(y), "1"(z));
```
These force x, y, z into registers. The target's code:
```
18 li v1,-1664     (x = -0x680 = -1664)
19 li a1,-3712     (y = -0xE80 = -3712)
20 li a0,-848      (z = -0x350 = -848)
...
43 sw v1,0(at)     D_80192CE0 = x
44 lui at ; 45 sw a1,0(at)   D_80192CE4 = y
46 lui at ; 47 sw a0,0(at)   D_80192CE8 = z
```
So x → v1, y → a1, z → a0. And the pin on z (a0) is consistent ✓.

Without the launders, gcc would fold the constants into the stores: `sw v1,0(at)` — hmm, the stores use `at` with lui/addiu for the address and the value in a register. The values x, y, z are constants; the launder forces them into registers (v1, a1, a0).

Hmm, and the pin on z (a0) forces z into a0 ✓ (the pin is a separate row and stays).

So: can I remove the launders? The x value is used 3 times (D_80192CE0, D_80192CEC, D_80192D04, D_80192D10 = 4 times) and y 3 times, z 3 times.

The target:
- x (v1) is used at 43 (D_80192CE0 = x), and later (the other x uses).
- y (a1) at 45.
- z (a0) at 47.

Hmm, the constants are materialized once each (li v1, li a1, li a0) and reused ✓.

Without the launder: gcc would compute each constant at each use (4 materializations of x) or CSE them. Hmm, gcc's cse would CSE the constant into one pseudo → one materialization ✓. Hmm! Then the difference would be small.

Hmm, but the ORDER: in the target, the three `li`s (18-20) are at the TOP (before the D_80192CF0 = 0x68 store at 21-23). So the constants are materialized early — the launder forces that (an asm with priority 1 schedules early).

Without the launder, gcc would materialize the constants at their first use (insn 43+) → the `li v1,-1664` would be at 43's place ✗.

Hmm! So the residual would be an ORDER difference (the li's position).

Hmm, the "3-qty sort bug" and the birth boost: the `li` (a constant materialization) is a "birthing" insn → sched1's birth boost → scheduled early?! Hmm, then it'd be early anyway.

Let me just try: remove the launders (keep the pin) and score.

Let me write v1 for this item.

Note: the pin `register s32 z asm("a0")` — hmm, `asm("a0")` without __asm__ — fine, it's in the def.

Let me write the candidate: the def minus the two launder lines.
