---
ts: 2026-11-06T14:13:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HnUAMdy2CDzKi86sGXPk
---
Now I have exact numbers for c1:
- i (160): 11 refs, live 39
- dst (162): 11 refs, live 36
- src (161): 13 refs, live 38
- n (159): 9 refs, live 40

Wait, earlier I estimated i=12. Actually i=11 without asm, so the i asm added 3 refs (14-11=3), matching the comment "+3 refs on i (depth-3)". And src asm added 2 (15-13=2), matching "+2 refs on src (depth-2)".

So without asm:
i: floor_log2(11)*11/39 = 3*11/39 = 0.846
dst: 3*11/36 = 0.917
dst wins (0.917 > 0.846) -> dst gets t2.

Target with asm:
i: 3*14/41 = 1.024
dst: 3*11/37 = 0.892
i wins.

To make i win without asm, I need i's priority > 0.917 (dst's). Options:
- i refs 12: 3*12/39 = 0.923 > 0.917. Very close! But wait, floor_log2(12)=3 (since 2^3=8 <= 12 < 16). 3*12=36; 36/39=0.923. dst=33/36=0.9167. So 0.923 > 0.9167 -> i wins, but the margin is tiny: 0.9231 vs 0.9167, difference 0.0064; *10000 = 64. Non-zero, so i wins.
  But adding a ref to i might also change live_length. If live stays 39, i=12 wins.
- i refs 13: 39/39=1.0.

But hold on: adding a use of i inside the do-while adds loop_depth refs. What is loop_depth at the use? The i asm at insn 329 added 3 refs, and it's in block 14. So loop_depth there is 3?! The comment said depth-3. Hmm, that means the do-while is at loop depth 3? There might be an implicit loop... Actually maybe the outer `while` is depth 1 and the `do-while` is depth 2, and... hmm 3.

Wait, flow.c line 2501 and 2711 also add refs. There might be additional weighting (the increment extra ref). Let me not over-think. Empirically, one asm reg occurrence in block 14 = +3 refs. So a real use of i in block 14 (the do-while body) adds 3 refs.

But can I add a real use of i inside the loop without adding an instruction? Any use must be part of an existing computation.

Hmm. Alternatively, add a use OUTSIDE the loop where loop_depth=1 (adds 1 ref). E.g., a use of i in block 13 (setup) at depth 1 would add 1 ref -> i=12. That would flip it if live length stays 39! But a use in block 13 extends i's live range backward (i is defined at `i=0` in block 13), so live_length might stay the same or grow slightly. And it must not emit an instruction.

What real C use of i can I add in the setup block without emitting code? For example:
```
i = 0;
src = arg0->data;
dst = src + n;
```
If I write `dst = src + n; i = 0;` — reorder. That doesn't add refs.

What about `n = arg0->w * arg0->h; i = 0;` — what if I write `i = n - n;`? That would emit `subu` (or fold to 0). gcc folds `n-n` to 0 at the tree level? Probably `i = 0` after folding. No ref.

What about `i = 0; ... dst = src + i + n;`? That adds i to the address computation: `addu $11,$9,$2` would become... `dst = src + n` where n is already `w*h`. Adding i (which is 0) — gcc folds `+0`? Maybe not in RTL. `dst = src + n + i` with i=0 known? gcc's jump/combine might not know i=0. But it would emit an extra `addu`. Not allowed.

Hmm.

What about making the loop counter part of an existing expression: the store `*dst = out`. If I write `dst[i - i] = out`? folded.

Let me think differently. The cleanest real-C lever: change which variable holds what. For instance, use `i` as the destination pointer's index and eliminate `dst` as a separate variable, OR merge.

Actually — here's a thought: what if I replace the pair (i, dst) with a different formulation where i is used in the store address? E.g.:

```
u16 *dst = arg0->data + n;   // src + n
...
dst[i] = out;   // ??? no, dst already advances
```

Hmm no.

What if the loop is:
```
for (i = 0; i < n; i++) {
    px = src[i];     // src + i*2 each iter -> extra insns
}
```
No.

OK, different idea: since the target's ref counts come from the increment extra-ref (REG_INC) mechanism, maybe I can make `i` an auto-increment in an addressing mode so it gets the extra ref. But the target's `i++` is a plain addu, not an addressing-mode auto-increment.

Wait, actually, let me reconsider. What if I can reduce dst's refs or increase dst's live_length? If dst's live_length increased to 37 (from 36), its priority = 33/37 = 0.8919 < i's 0.846? No: i=0.846 < 0.892. Need dst priority below i's 0.846. dst live_length would need 33/len < 0.846 -> len > 39. dst live is 36; making it 40+ would require extending its life, which changes code.

Alternatively reduce dst refs from 11 to 10: floor_log2(10)=3, 3*10/36=0.833 < i's 0.846. Then i wins! So removing ONE ref from dst would flip it too. Can I remove a ref from dst without changing code?

dst refs = 11 (with i asm; also 11 without since the asm doesn't touch dst). Where do dst's refs come from? `dst = src + n` (set), `*dst = out` (use), `dst++` (use + set + increment extra). Let me count: 
- insn 318: set dst -> +1*loop_depth(block 13, depth 1?) = +1
- insn 391: mem(dst) use -> +loop_depth (block 17, depth 2?) = +2 or 3
- insn 394: dst = dst + 2 -> set + use -> +2*loop_depth = +4 or +6, plus increment extra +loop_depth.

Total with loop_depth 3 in block 17: 1 + 3 + (2*3 + 3) = 1+3+9=13. Hmm, but observed 11. Let me not.

Actually maybe loop depths: block 13 (setup) depth 1, block 14 (body) depth 2, block 17 (latch) depth 2. Let's test: 
- dst set in block 13: +1.
- dst use in block 14 (store): +2.
- dst increment in block 17: use+set = 2 occurrences * 2 = +4, plus increment extra +2 = +6. Total 1+2+6 = 9. Observed 11. Not matching.

Hmm, maybe loop_depth is 3 for the do-while? Then:
- set in block13 depth1: +1
- use in block14 depth3: +3
- increment in block17 depth3: 2*3 + 3 = 9
Total 13. Not 11.

Maybe the do-while is depth 2 and the increments are counted differently. Let me check the loop dump for loop depths.

Actually, this exact accounting doesn't matter much. What matters: can I remove one ref from dst or add one to i with real C that keeps code identical?

Key realization: The asm refs are "fake" refs. The target binary was compiled from code where i naturally had more refs. Perhaps the original source had a different loop structure where i was used more.

Hmm, but we need to match the target exactly. The target code has i in $10 (t2) and dst in $11 (t3).

Let me look at the problem from the sched1 angle instead: maybe it's not global-alloc but sched1? The score category was "REG-caller". The diff showed exactly a register swap of the two caller-saved temps. Let me check the .greg dump to confirm global-alloc assigned the regs.

Let me look at the greg dump for the function: it prints allocno priorities? Let me check.
