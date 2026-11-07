---
ts: 2026-11-06T19:00:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_v4GjKEyf31ZJmpNiit16
---
All score-2 variants have the same residual: the a3 increment one slot late.

The 20 score-2 variants: h049-h071 (odd) and h161-h175 (odd). Let me decode: n = ((perm_index)*2 + init_index)*2*2 + load*2 + ret + 1. With 4 dims: perm (0-23), init (0-1), load (0-1), ret (0-1). n = perm*8 + init*4 + load*2 + ret + 1.

h049: n=49 → perm = (49-1)//8 = 6 → perm index 6 = (A,C,D,B)? Let me list permutations of "ABCD": index 0=(A,B,C,D), 1=(A,B,D,C), 2=(A,C,B,D), 3=(A,C,D,B), 4=(A,D,B,C), 5=(A,D,C,B), 6=(B,A,C,D), 7=(B,A,D,C), ...
h049: perm 6 = (B,A,C,D) = v1, a7, a6, a5. init = ((49-1)%8)//4 = 0 → INIT1; load = ((48)%8 %4)//2 = (0)//2=0 → LOAD1; ret = 48%2=0 → a7.
h051: perm 6, init 0, load 1, ret 0.
h161: n=161 → perm = 160//8 = 20 → (D,A,B,C)? Let me index: 20 = (D,A,B,C)? The permutations in itertools order... whatever.

The common thread: the increment order starts with B (v1) first in h049 etc. Hmm, but some score-2 variants may have other perm orders (h161: perm 20).

Let me look at what these have in common: maybe all have B before A (v1 before a7). h049-h071 (perm 6-8?) and h161-h175 (perm 20-21).

Since all 20 have the same residual (the a3 increment), the increment order in the source doesn't fix it. So I need a different lever for the sched1 order of the two increments.

The increments: `a7 += 0x68` and `v1 += 0x68`. The target schedules a7's first. Mine schedules v1's first.

What if the a7 increment is expressed with a dependency on v1 (old value)? E.g., `a7 = (unsigned short *)((char *)v1 + 0x68);` — since a7 == v1 at that point, this is equivalent, and it creates a dependency: a7's increment reads v1's OLD value, so it must be scheduled BEFORE v1's increment (which writes v1). That would force a7 first!

But the source order: the a7 increment must come before the v1 increment in the C (to use v1's old value). If I write:
```
a7 = (unsigned short *)((char *)v1 + 0x68);
v1 = (unsigned short *)((char *)v1 + 0x68);
```
Then a7 = v1+0x68 (old) and v1 = v1+0x68 → both incremented. ✓ Semantically equivalent (a7 == v1 before).

The RTL: a7 = v1 + 0x68 (a new insn using v1), then v1 = v1 + 0x68. The target's asm: `addiu a3,a3,104` — but with this spelling, a7's increment would be `addiu a3,v1,104`? Since a7 and v1 are in different registers ($7 and $3), the instruction would be `addu a3,a0?` no: `addiu a3, v1_reg, 104` = `addiu a3,$3,104` — but the target has `addiu a3,a3,104` (a3 = a3+104). Different source register! Unless the register allocator coalesces a7 and v1... they're different registers, so `a7 = v1 + 0x68` becomes `addiu a3,$3,104` ≠ target's `addiu a3,a3,104`.

Hmm. Unless the compiler proves a3 == $3? No, they're separate registers with equal values.

What if the a7 increment uses a7 itself but with a dependency via the *order*? The scheduler's order for two independent insns: the backward pass's ready list. The insn that is "ready" later gets scheduled earlier in the final order? Hmm.

Let me look at the sched1 trace for the loop block of a score-2 variant to see why a3's increment is late. Actually, the final asm order: v1+104, a3+104. The backward pass schedules from the block end: the last insn is the bne; then its delay slot (a5+104), then slt, a6+1, then the two increments (v1, a3), then... So the increments are scheduled in the reverse of the final order: a3 first (backward), then v1. 

sched1's choice between them: both are ready at the same time (after the a6/slt chain). The ready-list order decides. In the target, a3 is chosen first (backward) → a3 later in the final order? Hmm, no: in the backward pass, the insn scheduled first (at T-n) ends up LAST in the final order. The final order is v1, a3 — so a3 was scheduled BEFORE v1 in the backward pass (a3 at T-k, v1 at T-k-1).

To flip, the ready-list insertion order must change. The ready list is built as insns become ready; when both become ready at the same T, they're added in the order the links are traversed (LOG_LINKS order). The a7 increment's LOG_LINK depends on... the a6 increment? No, they're independent; the increments become ready when their uses are scheduled. The a7 increment's use is the return (in another block? no, a7 is used at the return in the else block and in the next iteration). Within the loop block, a7's increment is used by... the next iteration's a7 (loop-carried) and the return. The scheduler's LOG_LINKS within the block: the a7 increment feeds nothing in the same block? Then it becomes ready at the start of the backward pass.

Hmm, the order in the ready list is determined by the order the scheduler examines the insns. sched1 builds LOG_LINKS by scanning forward and adding dependencies; insns with no successors in the block are "ready" at the beginning (T=block end).

This is deep. Practical: try changing the *order of the increments in the RTL* while keeping the allocation: the allocation flip came from the increment order (B first). What if I reorder the increments as (A, B, C, D) but add a dummy statement to flip the allocation? E.g., the init order, the load, the return (the sweep covered 2×2×2 with all 24 perms → 192; none gave 0). 

What about the *store order* in the else block? That affects the allocation too. And the loop test. Let me sweep the store order (7! = 5040, too many). Let me pick a few: swap the first two stores, the last two, etc. Combined with the increment orders that gave score 2.

Alternatively: change the *loop test* position: `while (a6 < 0x14)` at the end (do-while) vs a while loop with the test at the top. The target's loop: the test is at the end (bnez at f18). The do-while is right.

Hmm, what about the a6 increment's spelling: `a6 = a6 + 1;` vs `a6++;` — same insn.

What about the slt: `a6 < 0x14` — the target's `slti v0,a2,20`. ✓.

Let me think about the a3 increment differently: the target has it BEFORE v1's increment. Since both are independent adds of 0x68 to different registers, the only difference is the scheduling. What if the a7 increment were made *dependent* on the a6 increment or the loop test? E.g., place it after the test in the source? The target's order: a3, v1, a6, slt. If the a7 increment were after the a6 increment in the source, sched1 might still place it... hmm.

Actually, wait: maybe the target's a3 increment position is due to the *register* difference: in the target's build (pin), a7 is a hard reg $7, which affects the scheduler's "potential hazard" tie-break! The sched trace showed "insn X has a greater potential hazard" — hazard = register conflicts with the next insn. With a7 as a hard reg, the hazard analysis differs. Lever-free, a7 is a global pseudo in $7; the hazard should be the same after allocation... but sched1 runs BEFORE register allocation (sched1 is pre-reload), where a7 is a pseudo. The pin makes a7 a hard reg in the pre-reload RTL, changing the hazard/scheduling decisions!

Hmm, that suggests the difference is in sched1's hazard tie-break with a pseudo vs a hard reg. The pin (a7 = hard $7) vs a pseudo.

But wait — the pin is forbidden. Is there a real-C way to make a7 a hard reg? No.

Hmm, but the score-2 variants already have the right registers; only the increment order differs. In the target's build, sched1 sees a7 as hard reg $7 → the hazard analysis gives a different order.

Could a real-C change make sched1 order a3's increment first? The hazard: after the v1 increment (writing $3... pseudo), the next insn... 

Let me look at the sched1 trace for the loop block in a score-2 variant and in the orig (pinned). The loop block is small. Let me dump both and compare. The score-2 variant h049: dump it (properly, with externs). The orig: I have the pinned build's dump? The orig scores 0, and its sched trace would show the target's order.

Let me dump h049 and the orig via the scratch header. Then compare the loop block traces.

Time: 12:00; item 2 started 11:45 → 15 min. Tries: w1-w4 (4) + g001-g028 (28) + h001-h192 (192) = 224 tries. Plenty.

Let me dump both loop traces.
