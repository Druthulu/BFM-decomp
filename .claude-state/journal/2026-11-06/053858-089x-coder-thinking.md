---
ts: 2026-11-06T12:38:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ScMHmBRMOoxl3GE85MuR
---
Plateaus: launder 2, keepalive 3, barrier 12 (or 7 with j5).

Tries: 8 + 8 + 12 = 28... let me count exactly: v0,l0,bb,k0 (4), n1-n4 (8), j1-j8 (16), q1-q6 (22), w1-w6 (28, w4 didn't run → 27). Plus d202-style... no.

I need ≥30 for a WALL. Let me do a few more combos: since the kinds interact, let me test combos:
- l0 + k0 (launder + keepalive removed) 
- l0 + bb
- k0 + bb
- l0 + k0 + bb (= v0, 13)

And a couple more barrier ideas:
- j5 variant with b4b[1] = var_v0_3 kept AND per-arm? 
- Make the else arm's store use a different expression so jump2 can't merge: e.g. `D_801152AA = -0xFFF;` → `D_801152AA = (s16)-0xFFF;` (j8 = 12).

Hmm, what prevents jump2? Looking at mine: the if-arm jumps to the else's store. jump2 merges the tail `lui at; sh v0,0(at)` — the store is at the END of both arms.

If in the if-arm the store is followed by another insn (the addiu in the delay slot...), jump2 could still merge.

What if the if-arm's store comes BEFORE the b4b load and the else's after? Then the tails differ.

j4 put the store first in both arms = 12.

Hmm, what if the arms differ in the b4b load position:
```
if (arg1 & 1) {
    D_801152AA = 0xFFF;
    b4b = D_8017E918;
    var_v0_3 = pos + 2;
} else {
    b4b = D_8017E918;
    D_801152AA = -0xFFF;
    var_v0_3 = pos - 2;
}
```
Let me try that (k1).

Also: what if `b4b = D_8017E918;` is hoisted before the if AND the store stays per arm? j6 = 14.

Let me also try: keep `var_v0_3` out and store `b4b[1]` in each arm with different forms.

Given time (~07:45, item 4 ~30 min), I should wrap up: 3 more tries to reach 30, then record WALL.

Actually, let me reconsider one thing for the barrier: since removing the barriers LOSES 2 insns, maybe the target's 2 insns ARE the nops emitted by the asm statements. If so, no C move can produce them... but wait: in the target, are they nops? Let me look at target 118-132: no nops visible. The 2 extra insns are the duplicated `lui at,0x0; sh v0,0(at)` (the if-arm's own store). So the barrier's effect is anti-cross-jump, not nops.

To defeat jump2 without an asm: make the two arms' tails differ by at least one insn. The tails:
if: `li v0,4095; lui at; sh v0,0(at); j; addiu v0,t4,2`
else: `li v0,-4095; lui at; sh v0,0(at); addiu v0,t4,-2; sh v0,2(v1)` (hmm, in target the b4b[1] store is in the else tail at 132).

So the target's tails differ only in the li immediate and the addiu. jump2 merges the common suffix `lui at; sh v0,0(at)` — wait, it merges the if-arm's jump target to point at the else's store. The suffix after the store differs (j vs addiu...). Hmm, in the target, the if-arm's `j b84` at 124 goes to 132 (`sh v0,2(v1)`), and the else arm falls through 131→132. So the target's arms share the tail from 132 onward (the b4b[1] store).

But the target does NOT merge the `sh v0,0(at)` (123 vs 130). Why not? Because jump2 only merges the *tail* — the common suffix. In the target, the common suffix of the two arms is `sh v0,2(v1)` (at 132) only (since before it, the arms have different insns: 125 addiu v0,t4,2 vs 131 addiu v0,t4,-2).

In mine, the arms share a longer suffix: `lui at; sh v0,0(at); sh a0,2(v1)`? Let me look: mine's if-arm: 119 addiu a0,t4,2; 120-121 load b4b; 122 j b74; 123 li v0,4095 (delay). Then 124-127 is the else arm, 128-129 the merged store, 130 sh a0,2(v1).

Hmm, mine's if-arm jumps to 128 = the shared store. So the shared suffix is `lui at; sh v0,0(at); sh a0,2(v1)` — 3 insns. In the target the shared suffix is just `sh v0,2(v1)`.

The difference: in the target the if-arm's addiu (v0,t4,2) happens BEFORE the join and uses v0; in mine the value (a0) is computed in the arm too...

Hmm, actually mine: `addiu a0,t4,2` at 119 is in the arm, then j at 122 → the shared tail is the store + `sh a0,2(v1)`. So mine shares 2 stores; target shares 1.

Why does mine share the `sh v0,0(at)` store while the target doesn't? Because in the target the store comes before the var_v0_3 computation in both arms... no, in the target the if arm is: li v0,4095 (delay of beqz), lui v1, lw v1, lui at, sh v0,0(at), j, addiu v0,t4,2 (delay). So the store precedes the addiu. In mine: addiu a0,t4,2 (in the delay slot of beqz!), then load, then j, li v0,4095 (delay).

So in mine the addiu moved into the beqz delay slot, before the store; in the target the addiu is in the j delay slot.

jump2 merges identical instruction sequences. In mine, after the if-arm's `li v0,4095` (delay slot of j — hmm, that's IN the if arm), the if jumps to the else's store.

The key: in mine, the store `sh v0,0(at)` is at the same position relative to the join, so jump2 merges.

To break it: make the store's position relative to the arm differ. j1/j2/j3 (reordering the C statements) all = 12, because sched1 reorders them back.

Hmm. What about making the if-arm's store value a different expression that generates an extra insn? e.g. `D_801152AA = 0xFFF;` in one arm and `D_801152AA = 0x7FF + 0x800;` in the other (folded at compile time → same).

OK, item 4 = WALL. Best lever-free = 13 (v0). But hmm — should best be the min over lever-free variants? v0 = 13. Let me check whether combining the best per-kind variants helps: n1(2 for launder) + k0(3) + bb(12) → v0 = 13. Let me test n1+k0 and n1+k0+j5-ish. Since n1 = 2 and k0 = 3, and both are REG-caller, they might combine to 5 (independent) or less.

Let me run 3 combos: n1+k0, n1+bb, k0+bb (bb is already in v0).

Then record. That gives 30+ tries.

Actually — wait. Before concluding WALL, let me reconsider the launder once more. The target's head:
```
0 move t2,a0
1 move t3,a1
2 andi a1,a1,0x1
```
Note insn 1 `move t3,a1` copies arg1 to t3 and insn 2 tests a1. In mine (n1):
Let me dump n1's head. If mine has `move t3,a1` then `andi v0,t3,0x1`, the difference is just which register the test uses. A real-C way to force the test on a1: use a1v pinned... which is the launder.

Alternatively: what if the FIRST use of arg1 is a comparison whose result feeds a branch, and arg1's copy to t3 happens after? Statement order is already that.

Hmm, what if I write the test as `if ((a1v & 1) == 0)` vs `if (!(a1v & 1))` — same.

I'll accept WALL for item 4.

Hmm, but hold on. Let me reconsider the whole picture: 1 PARTIAL + 3 WALLs. Is there anything more promising I should try? Item 4's total is 13 with the kinds at 2/3/12. The barrier is the big one and it's a jump2 merge. 

One more barrier idea: make the if-arm and else-arm *not* have identical store code by giving one arm a different store form — e.g. store through a pointer variable:
```
s16 *pa = &D_801152AA;  // adds an insn
```
no.

Another: swap the ARMS (if (arg1 & 1) → else body first)? That changes which arm falls through. jump2 would still merge.

Another: `D_801152AA = 0xFFF;` → `D_801152AA = 0xFFF & 0xFFFF;`? folded.

OK, WALL. Let me do the 3 combos and record.

Actually, one more: j5 (7) had 159 ins — the b4b[1] per-arm plus a var_v0_3 = b4b[1] re-read. Not useful.

Let me run the combos.
