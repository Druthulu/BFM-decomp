---
ts: 2026-11-06T12:01:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MPuvE0t83Om5Hv0TKkd3
---
The target's FT3 y compare (3b98-3bc8):
```
lh v1,-26(t2)   ; y0
lh v0,-18(t2)   ; y1
move a1,v0
slt v0,v0,v1    ; y1 < y0?
beqz v0,3bc0
move a0,v1      ; delay: a0 = y0
  move a3,a0    ; a3 = my = y0
  j 3bc8
  move a2,a1    ; delay: a2 = mny = y1
3bc0: move a2,a0   ; a2 = mny = y0
      move a3,a1   ; a3 = my = y1
```
So my → a3, mny → a2.

In mine (e0), it's a2 = my, a3 = mny (swapped).

The earlier x-compare (3b0c-3b38) uses a0/a1/t0/t1 — different regs (the x min/max for the outer bbox? no, that's the first one at 3b0c).

OK so the target: my=$a3, mny=$a2.

The slider's job: make int(K/L_my) == int(K/L_mny) so creation order decides, and mny (created first) gets $a2.

Real-C: extend L_my by 2. 

Hmm, what if I extend L_my by using `my` in the FT3 arm's *next* comparison in a way that's already there... 

Wait — maybe a simpler real-C move: declare `my` and `mny` such that the creation order changes. The comment says "mny (created first) takes $a2". If I can make *my* created first AND fix the tie, then my would take $a2 — wrong (we want mny=a2). So creation order matters: mny must be created first.

Hmm, currently mny is created first (per the comment) and with the exact tie takes a2. Without the slider, my's priority is higher (shorter live range → higher priority?) so my is allocated first and takes a2? Let's see: priority = refs*10000/live_length. Shorter L → higher priority → allocated first → gets the preferred reg. So without the slider, my (shorter) has higher priority and takes... a2? But mine has a2=my. Yes! So the slider lengthens my's L so the priorities tie.

So: lengthen L_my by 2, or shorten L_mny by 2.

Shorten L_mny: move mny's set later. In the then-branch, mny = y1 (a load). Its next use is the y2 compare. If we could set mny closer to its use... The y2 compare is `if (y2 > my) my = y2; else if (y2 < mny) mny = y2;`.

What if we compute mny AFTER the y2 max update? No, the else-if uses it.

Hmm, what about a real-C restructure that changes the liveness: 
```
if (y0 > y1) { my = y0; mny = y1; } else { mny = y0; my = y1; }
```
The liveness of mny starts at its set in the branch. If the branch code were shorter...

What about using conditional expressions instead of if/else?
```
my = (y0 > y1) ? y0 : y1;
mny = (y0 > y1) ? y1 : y0;
```
This would emit two compares (or one) — different code.

Hmm.

What about lengthening my by adding a real use that emits no code: e.g., using `my` as a *condition* in the y2 compare: it already is.

Let me try: move the `if (y2 > my) my = y2; else if (y2 < mny) mny = y2;` — no.

OK here's another idea: what if we extend my's live range by computing `my` from a chain: `my = ((XFT3 *)pkt)->y0;` → `my = (s16)(((XFT3 *)pkt)->y0 + 0);`? folds.

What about making my's value pass through a real register copy that survives: `s16 t = ((XFT3*)pkt)->y0; my = t;` — f5 = 53, no.

Hmm. What if I extend L_my by 2 by moving the *declaration* of the y2 temp... no.

Let me try the "set my before the if" restructure and a few others. Actually, the target's code has the load `lh v1,-26(t2)` (y0) and `lh v0,-18(t2)` (y1) *before* the compare, and the moves after. So the source might be:
```
if (y0 > y1) { my = y0; mny = y1; } else { mny = y0; my = y1; }
```
The target loads both, then compares. Same as the current C.

Hmm.

Let me try a batch:
- g1: `my = ((XFT3 *)pkt)->y0;` moved before the if, with the else fixed up (the restructure above).
- g2: swap the if condition: `if (((XFT3*)pkt)->y1 < ((XFT3*)pkt)->y0) {`.
- g3: use `>=` instead of `>` with swapped branches? changes semantics for equal values but the code...
- g4: reorder the y2 compare to test mny first.

Let me try g2 and g4 quickly (cheap), plus g1.

Actually, g2 (swapping the comparison operands) changes the `slt` operand order → big diff. Skip.

g4: `if (y2 > my) my = y2; else if (y2 < mny) mny = y2;` → `if (y2 < mny) mny = y2; else if (y2 > my) my = y2;` — this changes the branch structure. Could change liveness. Let me try.

Also: what about adding a real C statement between the two assignments that the compiler removes, like a cast of a value:
```
my = ((XFT3 *)pkt)->y0;
mny = ((XFT3 *)pkt)->y1;
```
→
```
my = ((XFT3 *)pkt)->y0;
mny = ((XFT3 *)pkt)->y1;
```
Hmm.

What about computing mny from a *subexpression* that adds 2 insns? No.

I'll do a few more tries and then settle for PARTIAL:barrier (score 0). Given PARTIAL is a good outcome, I shouldn't burn too much time.

Let me do g1, g4, and one more, then finalize.
