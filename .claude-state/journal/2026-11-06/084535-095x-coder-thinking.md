---
ts: 2026-11-06T15:45:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_R69MhEYzHSGXhgfPIeuu
---
Item 5 has 3 launders on `mb` (one per face). The pattern:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
__asm__("" : "=r"(mb) : "0"(mb));
func_800491AC(mb + 0x18);
```
Purpose: cse unifies the second `mb + 0x18` through the class of its constant value, and combine folds the symbol; the launder keeps two adds off one call-crossing base.

So the fix: make `mb` opaque or compute the address differently so the two `mb + 0x18` are separate adds. Known moves: the §373 dead-reset (func_80180D54/801815D4: "the §373 dead-reset `p1 = 0;` between the two calls invalidates cse's equivalence, so the second &sp10+4 use is re-derived"). And func_8014964C: "§373 dead-reset `m1 = 0;` after the first call empties cse's &mid class".

So: replace the launder with `mb = 0;` after the first call, and then the second call uses... wait, the second call uses `mb + 0x18` — if mb = 0, that's wrong. Unless the second use is spelled with the original expression: the moves example says "the §373 dead-reset `q = 0; q2 = &sp18;` before the last call — cse's &sp18 class breaks, addiu a2,sp,24 and addiu a0,sp,24 rematerialise".

So pattern: `mb = (u8 *)&D_800AF630; func_8004914C(mb + 0x18); mb = 0; func_800491AC(((u8 *)&D_800AF630) + 0x18);`? Hmm, the dead-reset sets mb = 0 (dead), and the second call uses a fresh spelling of the address.

Wait: the launder is on mb between the calls; the second use `mb + 0x18` reads the laundered mb (same value). With a dead-reset: `mb = 0;` then `func_800491AC(mb + 0x18)` would be `0 + 0x18` — wrong.

The func_80149374 crack: "launder asm dropped + §373 dead-reset `q = 0; q2 = &sp18;` before the last call — cse's &sp18 class breaks, addiu a2,sp,24 and addiu a0,sp,24 rematerialise, no s0 address reg". So they introduce a second variable q2 = &sp18 and use q2 in the second call.

So here: 
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = 0;
func_800491AC(((u8 *)&D_800AF630) + 0x18);   // or a new var mb2 = ...
```
Hmm, but does the dead-reset `mb = 0` even help? The point is to invalidate cse's knowledge of the constant `&D_800AF630 + 0x18` so the second add is re-derived.

Actually let me first test plain removal and see the diff.

Also note there are 3 identical sites. Let me test:
- a1: remove all three asm lines.
- b1: replace each asm with `mb = 0;` and the second call with `mb2 + 0x18` where mb2 = (u8*)&D_800AF630 assigned... 

Hmm, let me think. The pattern in func_80180D54: "the §373 dead-reset `p1 = 0;` between the two calls invalidates cse's equivalence, so the second &sp10+4 use is re-derived (addiu a0,sp,24 in the delay slot) and the address never enters a register".

So they had something like:
```
p1 = &sp10[1];
call1(p1);
p1 = 0;
call2(&sp10[1]);   // or p1 re-derived?
```
Hmm, if p1 = 0 then call2(&sp10[1]) uses a fresh expression.

For our case:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = 0;
func_800491AC((u8 *)&D_800AF630 + 0x18);
```
The second call's argument is the full constant expression `(u8*)&D_800AF630 + 0x18` — combine would fold it into `&D_800AF630 + 0x18` as a symbol+24 (lui/addiu pair) — 2 insns. Target presumably has `addiu a0,a0,0x18` off a base in a register (1 insn after lui/addiu of the base?). Let me look at the target asm.

Let me first score the plain removal.
