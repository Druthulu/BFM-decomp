---
ts: 2026-11-06T11:58:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GtHDlo1AtUpLSnkvtu6C
---
The barriers are §47 live-length SLIDERs: zero-byte insns placed where `my` is live and `mny` is dead, lengthening ONLY `my` so the allocno priority ties with `mny`, and creation order gives mny $a2.

This is a global-alloc priority tie (like item 2's mechanism 1). The slider is a zero-byte insn. Real C can't add a zero-byte insn.

BUT: maybe a real-C change can lengthen `my`'s live range: e.g., move a use of `my` into that region, or restructure the if/else.

The slider sits between `my = ((XFT3*)pkt)->y0;` and `mny = ((XFT3*)pkt)->y1;`. It lengthens my's live range by 2 insns (the slider count).

Real C: make `my` live longer without adding code. E.g., compute `my` earlier, or add a use.

Hmm, one classic real-C trick: reorder the assignments so my is computed before the if, or use my in the else branch too.

What about computing `my` and `mny` via a max/min expression that extends liveness? E.g.:
```
my = ((XFT3 *)pkt)->y0;
mny = ((XFT3 *)pkt)->y1;
```
No.

Let me think about what determines the live length: `my` is set in one branch and `mny` in the other, then both are used later. The liveness difference is the position of the assignments.

The target: mny takes $a2, my takes $a3 (from the earlier v3 diff, mine had them swapped).

Idea: swap the assignment order within the then-branch:
```
my = ((XFT3 *)pkt)->y0;
mny = ((XFT3 *)pkt)->y1;
```
→ already that order.

What if we write it as:
```
mny = ((XFT3 *)pkt)->y1;
my = ((XFT3 *)pkt)->y0;
```
? That would lengthen mny instead. Hmm, we want my lengthened. The current order (my then mny) means my is live longer already... but not enough.

Real C to lengthen my: use `my` between the two assignments in a way that emits no code. E.g.:
```
my = ((XFT3 *)pkt)->y0;
if (my == 0) {}   // no code but a use
mny = ((XFT3 *)pkt)->y1;
```
An empty if on my — would the compiler remove it? It's a real use; flow might delete the empty branch. Hmm, but the branch itself would emit code (beq). No good.

What about a real statement that's optimized away but keeps liveness, like a self-assignment `my = my;`? Removed by the compiler, no liveness effect.

Hmm, what about computing my as `my = ((XFT3 *)pkt)->y0 + 0;`? folds.

What about using my in the mny assignment: `mny = ((XFT3 *)pkt)->y1;` → `mny = ((XFT3 *)pkt)->y1 + (my - my);`? folds.

Hmm. The classic real-C liveness extender: make the value flow through a variable used later. E.g., move a *later* use of my earlier? `if (my >= -0x6E && mny < 0x6F)` uses my at line 205.

Actually, maybe I can change the *allocation* differently: the goal is mny → $a2. Perhaps reordering the *declarations* of my/mny (creation order) would flip it! The comment says: "global.c allocno_compare falls through to creation order -> mny (created first) takes $a2". So mny is created first and takes $a2. If the tie is exact, creation order decides. So without the slider, the tie isn't exact (my's priority differs).

Hmm, "lands int(K/L_my) on int(K/L_mny) -> exact allocno tie". So the slider adjusts L_my to make the priorities equal.

Real C: lengthen L_my by 2. Options: move the `my` assignment 2 insns earlier, or add a use.

What if I reorder the if branches:
```
if (y0 > y1) {
    my = y0;
    mny = y1;
} else {
    ...
}
```
Currently the assignments are in this order. The slider is between them.

What if I use a temporary:
```
s32 t0 = ((XFT3*)pkt)->y0, t1 = ((XFT3*)pkt)->y1;
if (t0 > t1) { my = t0; mny = t1; } else { mny = t0; my = t1; }
```
That changes the code (the loads happen before the compare) — the target loads y0/y1 inside the branches? Let me look at the target's code for this region.

Alternatively, use `my` in the *condition*: `if (my >= -0x6E && mny < 0x6F)` — already after.

Hmm. What about moving the `my = ((XFT3 *)pkt)->y2;` update? `if (((XFT3*)pkt)->y2 > my) my = ...` at line 203 — that's after both.

Real C idea: in the then-branch, swap the two statements but with a dependency: `my = y0; mny = y1;` → what if `mny` is computed first and `my` after, but then a later use of my... 

Let me look at the actual target code for the FT3 y-min/max region to understand what the slider achieves.

Actually, let me just try a few real-C variants:
- e1: in the then-branch, compute my, then a temp, then mny: `my = y0; mny = y1;` with a cast.
- e2: declare my/mny in a different order (creation order) — but the comment says creation order already gives mny first.
- e3: swap the if branches.
- e4: `my = ((XFT3 *)pkt)->y0; mny = ((XFT3 *)pkt)->y1;` → add `my = my;`? no.
- e5: use `my` in the mny expression: `mny = ((XFT3 *)pkt)->y1;` → `mny = ((XFT3 *)pkt)->y1 + (my & 0);`? folds.

Hmm. What about making `my` live *through* the mny load by reordering the loads: the target's code has `lw y0; ... lw y1`. If we compute mny from a temp that's loaded before my... 

Let me look at the target code around this. Let me find the FT3 arm's y compare in the target disassembly. Search for the constant -0x6E (0xFFFFFF92) and the preceding loads.

Actually, let me first check: does the score-0 d1 body (with barriers) mean the barriers are still needed? Let me test d1 with the barriers removed → that's v1-with-dead-resets. Let me score that (call it e0).
