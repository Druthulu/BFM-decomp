---
ts: 2026-11-06T16:45:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h6PHvnTZozIw0NgRP6at
---
Excellent! The twin `func_8017DE00` in ov_SC02_039 has the loop with `a0 = s0 << 10;` as the FIRST statement INSIDE the loop and NO separate pre-loop computation and NO launder! And it matches (it's banked).

So the correct shape is:
```c
s1 = a0p;
s0 = 0;
s2 = (s32)D;
do {
    a0 = s0 << 10;
    v0 = s0 << 1;
    ...
    func_8012C658(a0, a1 >> 16, a2);
} while (s0 < 4);
```
Note: no trailing `a0 = s0 << 10;` at the end of the body — the pre-loop one is the loop's first statement, and the loop back-edge's delay slot gets it from the loop's first statement? Wait, the loop's first statement `a0 = s0 << 10` is at the top; the target's back-edge delay slot has `sll a0,s0,0xa`, which is the top statement executed in the delay slot of the branch! Because the loop is a do-while: the body's first statement is hoisted before the loop? Let me check the twin's target: the twin's target at 1a50 `sll a0,s0,0xa` before the loop and the back-edge `bnez v0,1a54` with delay `sll a0,s0,0xa`.

Hmm, so the compiler lays it out as: pre-loop `a0 = s0 << 10` (the loop body's first statement, since the do-while body is entered before the test — wait no).

Actually for a do-while, the body executes first, then the test. The back-edge `bnez` jumps back to the body start. If the body starts with `a0 = s0 << 10`, the branch should jump to that instruction, and the delay slot would contain... the target jumps to 1a54 (`sll v0,s0,0x1`), not 1a50. And the delay slot has the `sll a0,s0,0xa`.

So the compiler moved the body's first statement (`a0 = s0 << 10`) into the back-edge delay slot and duplicated it before the loop. That's a classic optimization: the first body statement is the same as the "next iteration's" computation, so it's placed before the loop and in the delay slot. Effectively, the body is rotated.

Anyway, the twin shape is the answer! The twin's C is the same function shape without the launder and with `a0 = s0 << 10;` as the loop's first statement (instead of before the loop + at the end).

Let me verify the twin's target matches ours. Our target:
```
1a50: sll a0,s0,0xa
1a54: sll v0,s0,0x1
...
1a88: slti v0,s0,4
1a8c: bnez v0,1a54
1a90: sll a0,s0,0xa
```
Same shape. 

So for item 2, the C change is:
- remove the launder
- remove the pre-loop `a0 = s0 << 10;`
- add `a0 = s0 << 10;` as the first statement inside the do-while
- remove the trailing `a0 = s0 << 10;` at the end of the loop body

Wait, the orig has:
```
    a0 = s0 << 10;
    do {
        v0 = s0 << 1;
        ...
        a0 = s0 << 10;
    } while (s0 < 4);
```
The twin has:
```
    do {
        a0 = s0 << 10;
        v0 = s0 << 1;
        ...
    } while (s0 < 4);
```
So the a0 computation moves to the top of the loop and the trailing one is removed.

Let me write that and score. Keep the $4/$5 pins (they're not the row kind).

Note the twin also lacks the launder. 

Let me write win.c for item 2.
