---
ts: 2026-11-06T06:21:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ImcACBtrzVMLzINeMe9S
---
So w4 wrapped BOTH func_801823D4 calls (both loops), and it scored 36 with an extra insn and pf moved. OK.

So the symmetric wrap doesn't work either.

Let me reconsider. w4's diff:
```
124  move a3,s7   | move a3,s6     (pf)
125  move a0,s2   | move a0,s1     (otz)
128  move s2,v0   | move s1,v0     (otz = result)
132  addiu s6,s6,8| --             (extra insn!)
139  sll a0,s2,0x2| sll a0,s1,0x2
142  move a0,s2   | move a0,s1
145  slti v0,s1,12| slti v0,s2,12
```
Wait, at 145: mine slti v0,s1,12 (i in s1), target slti v0,s2,12 (i in s2). And the extra `addiu s6,s6,8` — pf (s6) being incremented? No, `addiu s6,s6,8` = pa++? pa was s5... Hmm, in mine pf=s7 and something s6 gets incremented — that means `pb` or `pa` took s6 and the increment is in loop 2 (pa++). Actually in loop 2, pa is reset: `pa = (V8*)(arg0+0x2C)`. Hmm, `addiu s6,s6,8` at 132 in loop 1 — that's pa++ or pb++. In target pa=s5, pb=s4. In mine, maybe pa=s6.

This is a cascade. Let me abandon the second do-while.

NEW ANGLE: maybe the issue is that in w2 the `do { otz = RotTransPers4(...); } while (0)` makes the loop block, and jump merges it, so combine folds. What if the do-while *body* contains the call AND the following statement so that the arg copy is inside the loop and the source is outside? That's the RM1 pattern: the copy inside, the source outside.

The copy here is "a0 = otz" which is part of the call statement. What if we split:

```
do {
    otz = RotTransPers4(...);
} while (0);
```
The copy is outside. In RM1, the copy was inside the do-while and the source outside.

So try:
```
otz = RotTransPers4(...);
do {
    otz = func_801823D4(otz, -0x1A);
} while (0);
```
That's w4 (both loops) = 36.

Hmm. What about wrapping just ONE of them (loop 1) — w4 wrapped both. Let me make w6: wrap only loop 1's second call (the first occurrence).

Actually in w4 both got wrapped because replace() replaced all. Let me test wrapping only the first occurrence.

Also w7: wrap only loop 2's.

Let me do that.
