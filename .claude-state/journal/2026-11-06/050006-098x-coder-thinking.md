---
ts: 2026-11-06T12:00:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_94FigvZsJELSOSdjciLf
---
f9/f10 (single-arm swap) = 51 (741 ins). Slightly better than 53 but not 0.

Let me think again about the slider: it adds 2 zero-byte insns between `my = y0;` and `mny = y1;`. That extends L_my by 2.

Real C: I need my's live range 2 insns longer without extra output. 

What if the *load* of y1 is moved into a temp before my's assignment? E.g.:
```
my = ((XFT3 *)pkt)->y0;
mny = ((XFT3 *)pkt)->y1;
```
The 2 zero-byte insns sit between. The RTL: [load y0 → my][slider][slider][load y1 → mny]. L_my = distance from set to last use.

A real-C equivalent: insert 2 real insns between that are dead/removed? No.

Alternative: extend my's live range by moving a *later* use earlier? No, that shortens.

Hmm. Actually, the allocno priority = refs*1e4/live_length. We want L_my == L_mny exactly. Instead of lengthening my, we could *shorten* mny by 2. E.g., move mny's assignment later (closer to its use). mny's next use is the y2 comparison (line 204: `else if (y2 < mny)`).

What if we compute mny just before the y2 comparison? I.e., restructure:
```
if (y0 > y1) { my = y0; } else { mny = y0; my = y1; }
mny = ...;  /* can't, branch-dependent */
```

Hmm.

What about a real-C change that alters the live lengths of BOTH: e.g., use my and mny in a different order in the y2 comparison:
```
if (y2 > my) my = y2; else if (y2 < mny) mny = y2;
```
This is where both are used. If we swap to `if (y2 < mny) mny = y2; else if (y2 > my) my = y2;` — changes semantics? max/min: if y2 > my → my = y2 (update max); else if y2 < mny → mny = y2 (update min). Swapping the order: if y2 < mny → mny = y2; else if y2 > my → my = y2. Logically equivalent (the conditions are mutually exclusive given mny <= my). But the code order changes (the branch tests differ) → probably a big diff.

Hmm.

Let me think about `live_length`. In global.c, the allocno live length is computed from the RTL liveness: the range from the first to the last reference. For `my`: first set at `my = y0`, last use later. For `mny`: set at `mny = y1`, used later.

Adding 2 zero-byte insns between the two assignments lengthens my's range by 2 but not mny's (mny's set is after them).

Real-C way to lengthen my's range by 2: move my's *set* 2 insns earlier. E.g., load y0 before the comparison:
```
s16 ty0 = ((XFT3 *)pkt)->y0;
if (ty0 > ((XFT3 *)pkt)->y1) { my = ty0; mny = ...; }
```
But then the set of my is still in the branch. Hmm, if `my` were set before the if... but its value depends on the branch.

Wait — in the then-branch, my = y0 and mny = y1. In the else, mny = y0 and my = y1. So my is set in both branches. The live range of my starts at the branch. If we hoist the y0/y1 loads before the if (f2 did that, but the assert failed earlier... let me check f2 — it wasn't generated due to the earlier assert. Let me generate f2 properly).

f2: hoist the loads to temps before the if:
```
s16 ty0 = ((XFT3 *)pkt)->y0;
s16 ty1 = ((XFT3 *)pkt)->y1;
if (ty0 > ty1) { my = ty0; mny = ty1; } else { mny = ty0; my = ty1; }
```
This would load both before the branch; then my/mny are copies. The code would change (both loads unconditional). The target has the loads inside the branches (I think). Let me check the target disassembly.

Let me look at the target's FT3 y-region. Let me find it by searching the disassembly for the two lh from pkt offsets (y0/y1 are at offsets 2 and 6? XFT3: x0,y0,x1,y1,x2,y2 = 0,2,4,6,8,10).

Let me grep the target disassembly for "lh" near a compare.

Alternatively, let me just try f2 and a few others and score.

Let me generate:
- f2: hoist loads (FT3 arm).
- f3: hoist loads (FT4 arm): `s16 ty0 = tmpxy[0].vy; s16 ty1 = tmpxy[1].vy;`
- f4: use a temp for mny: `mny = ((XFT3*)pkt)->y1;` → `mny = (s16)(((XFT3*)pkt)->y1);`
- f5: `my = ((XFT3 *)pkt)->y0;` → `my = (s16)((XFT3 *)pkt)->y0;` (cast might add insns)

Let me also try moving the y2 comparison before the mny assignment? No.

Let me try f2, f3, f4, f5.
