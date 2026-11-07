---
ts: 2026-11-06T18:31:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HtmNYbA5HZU0zvvtYzRb
---
The initial RTL: a1's value is pseudo 77 (symbol_ref D_801A15AC) at insn 55. The use at insn 94 (`a1 = 77`).

sched1's block 3 (43..105) schedules these. Target order in the final asm:
```
22-23 lui/addiu a1   (insn 55)
24 lui v0,0xfff6     (58)
25 li s0,4           (61)
26 sw v0,20(a0)      (64)
27-28 lui/addiu v0 D_801A1474 (67)
29 lui v1,0x4000     (70)
30 or                (72)
31 lui v1,0x2000     (75)
32 or                (77)
33-34 lui/addiu a2 D_801A15B4 (80)
35 li a3,0x20        (83)
36 sh s0,2(a0)       (86)
37 sw v0,88(a0)      (89)
38 move a0,s0? (92: a0 = a0 — this is the pinned a0 copy; the target has TWO moves at 20,21)
...
```
Wait the target's first two moves (20,21) are at the beginning of the block: `move a0,s0` twice. In the RTL there's insn 52 (a0 = 73, the pin) and insn 92 (a0 = a0, the call arg setup). The sched1 order in the target places both at the start (20,21).

Our build (w1) order: same except the a1 load pair at 31-32 (i.e., insn 55 scheduled after insn 77).

So sched1's ordering differs. In the trace, all these insns have priority 1 and ref_count 1 or so; the order is determined by the ready-list ties. The keepalive asm (a volatile insn using a1) created a dependency that forced insn 55 early (it had to precede the asm) and the asm a barrier.

Real-C: I need sched1 to schedule insn 55 (the a1 symbol_ref) early. Options:
(a) Give insn 55 a higher priority (e.g., more refs / a use). sched1 priority = insn's own priority computed from deps (max over successors). The a1 load feeds insn 94 which feeds the call — a long chain. Hmm, priority 1 for everything.
(b) Create a dependency forcing 55 before something scheduled early.
(c) Split the block (do-while) so 55 is in an earlier block.

Option (c) is attractive: put `a1 = (s32)&D_801A15AC;` in a do-while(0) block right after `a0 = s0;` — then a1's insn is in its own block and can't be moved later. But a new block boundary also changes the *call* scheduling? The target has the a1 load at 22-23 and everything else after — consistent with a block split at that point: block A: move a0,s0 (x2), lui/addiu a1; block B: the v0 chain, stores, call. Hmm, but the target's two moves at 20,21 come before a1. In the RTL, insn 52 (a0 = 73) is the pin assignment; insn 92 (a0 = a0) is the call setup — sched1 moved 92 to the top (target 21). 

If I split with do-while around just the a1 assignment, the resulting blocks would be: block X: [52 a0=73, 55 a1=77] then block Y: everything else. Then sched1 schedules block X: 52 and 55 in some order → target has move a0 first (20), then a1 (22-23). Wait, the target's 21 is the second move (insn 92) — hmm, 92 is in block Y but sched1 moved it to the top of block Y (21). Then the a1 load in block X would come BEFORE both moves (block X is emitted before block Y). Target: moves at 20,21 then a1 at 22. So the a1 must be in the same block as the moves, after them.

Hmm. So a do-while split before a1 would put a1 before the moves → wrong order (a1 at 20, moves after).

Unless the do-while wraps the *v0 chain* (after a1): block X: [52 move, 55 a1], block Y: [58..]. Then sched1's block X: 52 (move a0,s0) and 55 (a1) → order? Target: move then a1. And block Y: the rest including insn 92 (the second move) — sched1 in block Y would schedule 92 at the top? The target's second move at 21 is before the a1 load (22), so it's in block X. Hmm, but insn 92 is a call-arg setup that logically comes late.

Wait, let me re-examine the target's asm:
```
8010: jal func_8012B1B4
8014: move a0,s0      <- delay slot of the jal? 
8018: move a0,s0
801c: lui a1
8020: addiu a1
```
Ah, 8014 is the delay slot of the jal at 8010! The jal's delay slot contains `move a0,s0`. Then 8018 is another move a0,s0. In the RTL: insn 52 is `a0 = 73` (the pin assignment `a0 = s0`), and insn 92 is `a0 = a0` (the call arg copy). sched1/reorg: insn 52 (a0 = s0) was placed in the jal's delay slot at 8014, and insn 92 (a0 = a0) at 8018? Both are `move a0,s0` in the asm.

Hmm, the target asm shows the a1 load at 801c/8020 right after the second move. In the RTL, the order after the call: 52 (a0=73), 55 (a1=77), 58...

So the block starts at 52: [52, 55, 58, 61, 64, ...]. The target's scheduled order: 52, 92, 55, 58, 61, 64, 67, 70, 72, 75, 77, 80, 83, 86, 89, ... Wait, 92 is `a0 = a0` which in the target's asm is the move at 8018. So the target order is 52, 92, 55, 58, ... In our build: 52, 92, 58, 61, 64, 67, 70, 72, 75, 77, 55, 80, 83, ... (the a1 pair at 31-32 = after 77, before 80).

So sched1 in the target put 55 right after 92; in ours it put 55 after 77.

Both have the same priorities (all 1). The tie-break is the ready-list order. The keepalive asm in the original forced 55 before it.

How to make sched1 put 55 early with real C? Options:
- Increase 55's priority: priority = max over successors' priorities + 1? Actually sched1's priority is the length of the longest path to the end. 55 feeds 94 (a1 = 77) which feeds the call 100 — all ref_count 1. Hmm, the priority numbers in the dump are all 1, so no.
- The ready-list order: sched1 picks the insn with the highest priority; ties are broken by ... the order in the list (which is reverse of the RTL scan?). Hmm.

What if we make the a1 value *used earlier* in a way that adds a dependency: e.g., `a1 = (s32)&D_801A15AC;` then `a1 = a1;`? no.

What if we use a1 in the unk14 store? no.

**Idea: give a1 more references** (like the keepalive did). E.g., make a1's value used twice: the call uses it once. If the source used a1 in a second place that costs no insns... 

Hmm, what about `a2 = (s32)&D_801A15B4; a3 = 0x20;` moved before the v0 chain? That would change a2/a3's positions (target has them after the or chain at 33-35). If we move the a2/a3 assignments up, sched1 might reorder differently... but the target's order is what it is.

What about the source order: the target's order suggests the source was:
```
a0 = s0;
a1 = &D_801A15AC;
v0 = 0xFFF60000;
s0 = 4;
unk14 = v0;
v0 = &D_801A1474; v1 = 0x40000000; v0 |= v1; v1 = 0x20000000; v0 |= v1;
a2 = &D_801A15B4; a3 = 0x20;
unk2 = s0; unk58 = v0;
if (func_8012D5E4(a0,a1,a2,a3)==1) ...
```
which is exactly the source. sched1 reordered the a1 load to later in our build.

The keepalive asm was a volatile insn: sched1 does not move insns across volatile asm? Let me check sched.c: `if (GET_CODE (insn) == INSN && GET_CODE (PATTERN (insn)) == ASM_OPERANDS && MEM_VOLATILE_P(...))` — there's a `volatile_insn` check in sched.c that sets `sched_insns`... Let me grep sched.c for volatile.
