---
ts: 2026-11-06T08:39:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gVQ7z6ciVHQ3gUTIB2Dp
---
Both lose an insn (46 vs 47). Interesting — the target has 47 insns; with keepalives removed we got 47 (score 9 REG). Reordering loses one.

Hmm. The extra insn in target relative to reordered: maybe `nop` count differs.

Let me think differently. Perhaps the answer is a different real-C spelling that keeps the same instruction stream but changes local-alloc priorities. Since we need a0-copy in a2 and t3 in a3: this means local-alloc must assign a2 to t3? No wait, target: t3 in a3, a0-copy in a2. In w1, local-alloc gave t3=a2, a0-copy=a3. To get target, either local-alloc gives t3=a3 (needs a0-copy to be allocated before local-alloc? no) or global alloc gives a0-copy a2 and local-alloc t3 a3.

Actually local-alloc only assigns pseudos that die within the block; a0-copy r72 is global (live across the call? no). Hmm, r72 is used 5 times across 27 insns and lives from insn 4 to the call; local-alloc assigns local pseudos first, but the a0 copy is local to block 0 too (single block!). Why is it global then? The `.greg` phase decides global allocnos as those with refs outside one basic block or used in a loop; here single block. Yet the alloc table shows r72 in .lreg with 27 live, and the table lists all pseudos. The "hard" column comes from lreg dump order lines ("Register 72 in 7" = reg 7 = a3). These lines are from local-alloc (lreg dump). So local-alloc assigned r72→a3 in w1.

Local-alloc processes pseudos in order of quantity number (largest first?) — local-alloc assigns by `qty_cmp` ordering: higher priority first, and each pseudo tries to get its preferred register. The ordering: qty_bigger_p. Let me recall local-alloc.c: it sorts reg_qty by qty_compare (refs/live), allocates in that order. In w1: r78 (t4, 10000) → v0, r75→a0, r76→a1, r77→a2, r72 (3703)→a3, r74→v1.

In target, r72 got a2, r77 got a3. So either r72 was processed before r77 (priority higher) and took a2, then r77 took a3. That's exactly w2's table: r72 pri 3333, r77 pri 1666 — r72 before r77.

So we need r72's priority > r77's. r72 = 3703 (refs 5, live 27), r77 = 4000 (refs 2, live 5). Need to raise r72's or lower r77's.

r72 live 27; if live ≤ 24: 2*5/24 = 4166 > 4000. How to shorten r72's live range by 3 insns without changing code? Live length is from first to last use in insn numbers. r72 first use at insn 4 (the param copy itself), last use at the call (insn ~96). The live length is 27 "insns" counted... Actually "used 5 times across 27 insns" counts from first to last use (27 insns span). Can't shorten.

Lower r77 (t3): pri = floor(log2(refs))*refs/live*1e4. With refs 2, live 5 → 4000. Live 6 → 3333; live 7 → 2857; live 8 → 2500. Need live ≥ 6 → extend t3's live range by ONE insn slot.

How to extend t3's live range by 1 without adding an instruction and without reordering the final code? The live range ends at the store. If the store comes one insn later in the RTL stream (e.g., after t4's load), live becomes 6+; but sched1 reorders to the target order — the insn stream order after sched1 is target. local-alloc runs BEFORE sched1? Order: local-alloc runs before sched1 (sched1 is pre-reload, after local-alloc? Actually pass order: cse, loop, ... local-alloc, global-alloc, then sched1? No: sched1 runs before reload, after local-alloc? Let me recall: toplev.c: (cse1, loop, cse2, ...) then `local_alloc`, `global_alloc`, `reload`, `sched2`. sched1 is before local-alloc? In gcc 2.7.2, `sched1` is called in rest_of_compilation before local_alloc? Let me check toplev.c order. Actually the standard order in 2.7.2: 
```
cse (cse1), ...
if (optimize) { loop_optimize; ... }
...
sched1? 
```
Hmm. I recall gcc 2.7.2 does: `if (optimize) { ... }`, then `local_alloc()`, `global_alloc()`, `reload`, `sched2`. sched1 is `if (optimize) sched1()` early — before local_alloc? Let me check toplev.c in tools/reference.

The live lengths in the .lreg dump (local-alloc input) reflect the RTL after sched1 (if sched1 runs before local-alloc). The w1 lreg dump insn order: insn 4 param copy, 14 sll, 16 addu, 17 sll, 24 lw t0, 29 lw t1, 34 lw t2, 39 lw t3, 42 sw t0, 45 sw t1, 48 sw t2, 51 sw t3, 56 lw t4, 59 sw t4, 65... — this matches the target instruction order. So sched1 ran before local-alloc, and its order determines live ranges.

So in c1 (store t3 after lw t4), sched1 reordered it back to the target order (store before load), and we lost an insn elsewhere (46 vs 47). Hmm why 46? Maybe a nop difference.

Let me look at c1's listing to see.
