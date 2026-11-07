---
ts: 2026-11-06T22:42:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AtXq4EXlK0qTscWzSgHQ
---
Interesting! `--explain` on the *current src* (which has both levers) reports score 21 with only register-pair diffs s1->s0 x6, s0->s1 x4. Wait, the current src has the pin and keepalive, so it should score 0? No — the src still holds the OLD body which is NOT banked; the current src's body scores 21? The brief said "src still holds the old body (not banked)". Hmm, the current src (orig.c) scores 21? But the baseline prev_win (which is the win.c from W50x) scores 0.

Wait, --explain runs the *current tree* (src with the old body). The tree's function body is the src body. Hmm, but score 21 means the src body doesn't match?! Let me re-read: "--explain TU FN: read one body's residual (no writes)". It explains the *current* body in the tree, which is src's body (pin+keepalive). Score 21? But earlier the notes said "orig.c == current header body ... Baseline orig.c: score 0 on every includer sampled."

Hmm, contradiction. Wait, maybe --explain uses a different includer or the body_span extraction. Actually score 21 with mine 75/target 75. The diff shows mine has `move s1,a1` and target `move s0,a1`. So the current src (with pin) gives d=$s1?? That can't be right if the pin is `__asm__("$16")`.

Oh wait — maybe --explain's "mine" is the body *without* the lever (it explains the residual after removing levers?). The site list shows pin and keepalive as NEEDED. And the diff is exactly w3-like (both removed): score 21. So --explain strips the levers to show the residual. Yes: "read one body's residual" = the body after delever.

OK so the residual is the register swap only: s1->s0 x6 (d) and s0->s1 x4 (s1ang). That matches the notes. And importantly, in this residual, u5 and iVar4 are ALREADY correct (v1/a0)! Because the pin+keepalive body, when delevered by the tool (which removes the asm lines but keeps the variable structure), gives a different RTL than my w0?

Wait, the tool's delever removes the `register ... __asm__("$16")` qualifier and the keepalive asm. That's exactly w0-ish (no do-while though). Score 21. My w0 (with do-while cast) scored 38. Hmm, the do-while changed things. And the diff for the score-21 residual shows only register swaps — u5=$a0 and iVar4=$v1 correct.

Interesting! So the pure lever-removal (no do-while) gives score 21 with ONLY the d/s1ang swap. My w0 added the do-while which fixed the sll scheduling but shifted u5/iVar4? No wait, w0's diff had u5/iVar4 differences too.

Hmm, let me re-run w0's full diff to compare properly.

Actually wait, the --explain diff: mine[20:23]: `andi s0,s0,0xfff; bne s0,a0; sra s1,v1,0x10` vs target `sll s0,s0,0x10; andi s1,s1,0xfff; bne s1,a0; sra s0,s0,0x10`. So the residual has the sll placement issue too (score 21 = register swaps + the ORDER).

Hmm, so the residual is 21 and includes the cast-order issue. w7 (do-while) fixed the order but... 

Let me compare: my w0 = pin removed + do-while cast = 38. The tool's delever = pin removed, no do-while = 21. The notes said w3 (both removed) = 21. And w1 (keepalive removed, pin kept) = 2.

So the do-while (w7 with pin kept) fixed the order. Without the pin, the do-while gives 38 (w0). The residual without the do-while is 21.

Let me get the full diff of the 21 residual (the --explain output above shows it). The diff shows:
- mine[2:5]: missing `sw s0,16(sp); move s0,a1; sw ra,24(sp)` — the prologue order (register swap).
- `lh s0,18(v0)` vs `lh s1,18(v0)` — s1ang.
- `sll v1,s1,0x10` at 17 vs target `sll s0,s0,0x10` at 19-20 — order.
- etc.

So the residual (21) has the same u5/iVar4? Let me see: `subu v1,a0,s0` vs `subu v1,a0,s1` — u5=a0 ✓, iVar4=v1 ✓. YES! The residual has u5=$a0 and iVar4=$v1 correct. Only d/s1ang are swapped.

But w0 (do-while) had u5=$v1, iVar4=$a1. So the do-while on the cast changed the allocation of u5/iVar4! Hmm, why? The do-while adds a loop block around the cast, changing refs/live ranges.

So: the no-do-while body (score 21) has only the d/s1ang swap. If I can fix the d/s1ang swap WITHOUT the do-while (which perturbs u5/iVar4), I'd get a MATCH. But the cast order issue (sll placement) also needs fixing — the do-while was the fix. Hmm, but wait: the score-21 residual shows the sll placement as part of the swap? Let me look: mine[20:23] `andi s0,s0,0xfff; bne s0,a0; sra s1,v1,0x10` vs target[19:23] `sll s0,s0,0x10; andi s1,s1,0xfff; bne s1,a0; sra s0,s0,0x10`. The mine has the sll at insn 17 (before andi s0) and the target has it after the andi. So the sll placement differs (the keepalive removal issue). That's the "ORDER" difference the notes mentioned (w1 = keepalive removed, pin kept = 2).

So we need BOTH: the do-while (or another anchor) for the sll placement AND the d/s1ang fix.

Hmm, but the do-while perturbs u5/iVar4. Unless there's a different anchor.

Wait, the notes said w1 (keepalive removed, pin kept) = 2 with only the sll born 2 slots early. And w7 = w1 + do-while = 0. So the do-while fixed the sll placement with the pin kept.

Now without the pin, the do-while gives 38 (u5/iVar4 perturbed). Hmm, but maybe the u5/iVar4 perturbation is caused by the do-while, not the pin removal. Let me test: pin kept + do-while = w7 = 0 (no perturbation). So with the pin, the do-while doesn't perturb u5/iVar4. Without the pin, it does.

So the pin's presence stabilizes u5/iVar4. Removing the pin while keeping the do-while perturbs them.

Hmm. Let me check: what if I use the mask-in-place (which fixes d/s1ang) but WITHOUT the do-while? Then maybe u5/iVar4 stay correct (as in the 21 residual), but the sll placement is wrong. Let me test: w7 = mask-in-place, no do-while:
```
s1ang = *(s16 *)(...);
u5 = (ratan2(...) - 0x400) & 0xFFF;
s1ang = s1ang & 0xFFF;   // mask-in-place (no do-while)
if (s1ang == u5) return 0;
...
```
Wait, but we need the cast `d = (s16)d;`. In the no-do-while version, it's `d = (s16)d;`.

Let me test this: w7 = w0 without the do-while (plain cast) + mask-in-place.

Let me create it and score + dump.

Actually, the order of statements: in the target source, the cast `d = (s16)d;` is after the u5 computation. In w0 I have the do-while cast there. For w7, use a plain `d = (s16)d;`.

And the mask-in-place: `s1ang = s1ang & 0xFFF;` after the cast (as in w6).

Let me write w7.
