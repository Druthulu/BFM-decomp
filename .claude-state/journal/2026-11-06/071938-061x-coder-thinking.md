---
ts: 2026-11-06T14:19:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DmGfovO1YsaJ3VjMafZA
---
The for-loop/while-loop changes the stack frame: frame becomes 32 instead of 24, and one more callee-saved register (s2? no, frame 32 with s0,s1,s2 at 8,12,16 -> 24 bytes needed, but 32). Actually target frame 24, mine 32. The extra 8 bytes suggests an extra spill or the `pad[8]` local. Wait — the pad[8] local is in the function and gives frame 0x10 -> 0x18. Hmm, target frame is 24 (0x18). Mine is 32. So the loop form changed register pressure, spilling more.

So for/while forms are worse. The do-while with the `if (n>0)` guard is the right shape.

OK. Back to the priority problem. I need i priority > dst. Let me think about what changes I can make that don't alter the emitted code.

Key insight: flow computes refs/live on the RTL BEFORE combine and sched1. So I can change the C in ways that affect the pre-sched RTL (refs, live ranges, statement order) but sched1+combine produce the same final code.

The live_length is the number of insns between birth and death (with adjustments). If I move dst's definition earlier in the C source (before other statements), its live range extends. The final code might still be the same if sched1 moves it back to the delay slot.

Let me try: move `dst = src + n;` to the very beginning of the block, right after `n = ...`. But dst needs src. I could reorder src first:
```
src = arg0->data;
dst = src + n;
n = arg0->w * arg0->h;   // but n needed by dst! can't.
```
Hmm, dst needs n. n needs arg0->w/h. src needs arg0->data.

Order options:
- n; src; dst; i  (b3: gave 6)
- src; n; dst; i
- n; dst requires src.

To extend dst's birth, I want as many statements as possible BEFORE `dst = src + n`. Currently after dst there's only `i = 0` (if I move i after) and the if. So at most I can put i after dst: n; src; dst; i (b2/b3 = 6). That's only +1 live.

What if I add MORE real statements before dst? E.g., hoist some of the computations that are currently after the if? No, those are in the loop.

Alternatively, compute dst as `arg0->data + n` and move it before `src = arg0->data`:
```
n = arg0->w * arg0->h;
dst = arg0->data + n;
i = 0;
src = arg0->data;
```
Now dst is born before i=0 and src. dst's birth moves up by 2-3 insns. And `src = arg0->data` becomes a second load of arg0->data — cse2 merges them into one load, and `dst = <loaded> + n`. But the load's position? cse2 would place the load at the earliest use... Hmm, actually cse would replace the second load with the first pseudo. The final code: `lw $9,0($13)` once, `addu $11,$9,$2`. Same as target! And dst's birth in the RTL: `dst = arg0->data + n` — the load of arg0->data happens at the dst computation point (before src assignment). So the load moves earlier in the RTL. Then flow computes live ranges on that RTL. dst born earlier.

But this also changes src's live range: src is defined later (the second load is CSE'd to the first pseudo, so src = the same pseudo as dst's base). Hmm, this could actually make src and dst share the loaded pointer pseudo. Let me test.

Actually, wait: cse merges the two loads, so the RTL becomes:
```
p = arg0->data;    (load)
dst = p + n;
i = 0;
src = p;           (copy, might be deleted by cse/combine)
```
Then dst = p + n, src = p. In the target, `src` is the loaded reg ($9) and dst = src + n. So src = p and dst = p + n. Fine.

But the copy `src = p` might be eliminated (copy propagation), leaving src and p as the same pseudo. Then src's refs and dst's refs change. Let me just test.

Let me create g1:
```
n = arg0->w * arg0->h;
dst = arg0->data + n;
i = 0;
src = arg0->data;
```
and g2:
```
n = arg0->w * arg0->h;
dst = arg0->data + n;
src = arg0->data;
i = 0;
```
and g3 (dst first):
```
dst = arg0->data + arg0->w * arg0->h;   // needs n... 
```
No.

Let me test g1/g2.

Also g4: keep src first:
```
src = arg0->data;
n = arg0->w * arg0->h;
dst = src + n;
i = 0;
```
Here dst is after src and n, but i=0 moved after dst. Compared to current (n; i=0; src; dst), this moves i=0 later by 2 and keeps dst's birth similar. i's live shrinks by 2 -> 37, priority 33/37=0.892 < dst 0.917. Still not enough.

Let me focus on extending dst's birth. g1/g2.

Actually, even better: what if dst is initialized with `dst = arg0->data + n;` BEFORE `n` is... no, n needed.

Hmm, what if I move the `n = arg0->w * arg0->h;` computation and dst together early? They're already early.

Let me just test g1/g2 and dump refs.

Actually, I realize the live_length might be affected by the loop: dst is live across the loop back edge (from its def to the store, then the loop repeats). The live range includes the whole loop body and back edge. Moving the def earlier by 2 insns adds 2 to live_length. Need +4. Hmm.

Wait, let me recompute the target: dst live 37 (with asm). Our c1 dst live 36. Only 1 different. And i live 39 (c1) vs 41 (target). So in the target, i's live is LONGER (41 vs 39) and refs higher. Hmm, the asm on i extends its live range? The asm is in block 14, between i's birth (block13) and death (block17), so it doesn't extend the range. But the asm changes... hmm, the target dump's live 41 vs c1's 39. Why 2 more? Maybe because the asm insn itself counts as a live insn? Or the presence of the asm changes the insn numbering. Actually live_length counts insns where the reg is live; the asm insn is one more insn, and the register is live across it, so +1. Also the ref at the asm adds to live_length? reg_live_length is incremented per insn where live. The asm adds 1 insn. Hmm, 41-39=2.

Anyway. The point: in c1, i live 39. If I add an asm-like use... but that's what we're removing.

Let me think about the margin again: I need i priority > dst. With i=11/live39=0.846 and dst=11/live36=0.917. 

What if I extend dst's live to 40+? Moving dst's def earlier by 4. g1 moves it before i=0 and before src's load. The load itself moves too. Hmm.

Let me just test g1/g2 and dump.

Actually, let me reconsider a totally different lever: reduce i's live range. i's live = 39. If i=36, priority 33/36 = 0.9167 == dst's 0.9167 (exact tie) -> i wins by allocno number. How to shorten i's live by 3? Move `i = 0;` later. Currently i=0 is before src and dst. Move it to just before `if (n > 0)`: order n; src; dst; i=0. That's b2 (gave 6). Let me check b2's i live. Let me dump b2's lreg register table.

Actually, let me dump b2 quickly.
