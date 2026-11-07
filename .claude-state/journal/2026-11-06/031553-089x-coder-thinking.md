---
ts: 2026-11-06T10:15:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iXEWYHmQO0n7nSPrns4k
---
Target item 3:
```
move s1,a2   # a = arg2 → s1
move s0,a3   # div = arg3 → s0
...
sll s0,s0,0x10   # div sign-ext
andi s1,s1,0xfff # a mask
andi a0,v0,0xfff # cur
bne s1,a0
sra s0,s0,0x10
```
So a=s1, div=s0. Confirmed.

Now, priority: a must have LOWER priority than div (so div is allocated first). Currently a pri 6086 > div 5384.

Let me think about how to increase div's refs or shorten its live.

Actually, here's an idea: the target's prologue order is `move s1,a2` (a) BEFORE `move s0,a3` (div). So a is born first (earlier), making a's live LONGER. In our nopin, the order is `move s0,a2` (a→s0) then `move s1,a3` (div→s1) — same source order (a then div). 

Hmm, a's live is 23, div's 26. Even though a is born first, a dies earlier (before the divs). 

To make div's pri > a's: 
Option 1: div refs 8. 
Option 2: a refs 6.
Option 3: div live < 23 (move `div = arg3` later — but the target has it early).
Option 4: a live > 26 (move a's last use later).

Option 4: a's last use is `t = a + 0x1000` or `t = a - 0x1000`. If we could move one of those after the divs... but they're in the if-blocks before.

Hmm, wait: actually, a is used in `diff = cur - a` (block 1), `t = a + 0x1000` (block 1), `t = a - 0x1000` (block 2). The divs are in blocks 3,4. So a dies in block 2, div in block 4. div's live is longer.

To make a's live longer than div's, a would need a use after the divs. No.

Option 2: reduce a's refs from 7 to 6. floor_log2(6)=2, 2*6/23 = 5217 < 5384 → div wins! 

How? a's refs: let me count from the RTL. `a = arg2` (def, 1), `a = a & 0xFFF` (use+def = 2), `if (a == cur)` (use, 1), `diff = cur - a` (use, 1), `t = a + 0x1000` (use, 1), `t = a - 0x1000` (use, 1) = 7.

Hmm, if we could eliminate one use... e.g., the `a == cur` comparison. If we wrote `if (a == cur) { d = 0; }` — needed.

What if `diff = cur - a` is computed from `a` and the `t` uses... 

Option 1: div refs 8. div: `div = arg3` (def), `div = (s16)div` (use+def), div1 (use), div2 (use), plus the zero-check bnez ×2? Hmm, the bnez uses div too. Let me count: 7. To get 8, add a use.

What if we write the division as `q = diff / div;` twice — already. What if `if (div == 0) ...`? adds code.

Hmm.

What if div is used in the `if (a == cur)` condition? No.

Hmm, let me reconsider: maybe the LIVE LENGTH can be changed by the source order of `div = (s16)div`. The self-set's position doesn't change birth/death (birth is `div = arg3`, death is the last div).

Wait, actually: does `div = (s16)div` create a NEW pseudo? In item 3's nopin, let me check the RTL. Let me look at the alloc table's r76/r77 and the lreg.

Let me grep the lreg for item 3's function to see if div is a self-set or two pseudos.
