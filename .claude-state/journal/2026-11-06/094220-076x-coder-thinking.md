---
ts: 2026-11-06T16:42:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NilbdtsKCKAkb43mvi9I
---
Now all uses are $5 (a1)! The self issue is solved with s13 (no self variable, param used directly). Score still 16 — so the remaining mismatch is the arm register allocation:
- then: mine p=$2(v0), f=$3(v1); target p=$3(v1), f=$2(v0).
- else: mine q=$3(v1), g=$2(v0); target q=$2(v0), g=$3(v1).

So we need to swap p/f and q/g register assignments.

Then arm: target f in v0 (pinned $2), p in v1 (pinned... no, p wasn't pinned; g was $3). In the original, f was pinned to $2 and g to $3. p got v1 because f took v0.

Now lever-free: need f to get v0 and p v1. As computed, priority: p has more refs (p is redefined). Let's split p into two pseudos to lower its refs, or reorder.

For the else: need q v0 and g v1. Currently q=v1, g=v0 (g shorter life wins v0). To make q win v0: increase q's refs or shorten q's life. Splitting q's address temp from the loaded value gives 2 pseudos: t (addr) and v (value). Then t and v both short; which gets v0? Tie-break by qty number (t first) → t=v0, then v=v1? But v's life is shorter → higher priority → v=v0. Then t=v1. Hmm, target has q (the loaded value) in v0 and the address temp also v0 (reused: `lw v0,32; lhu v0,24(v0)`). So the address temp and the value share v0 (target: `lw v0,32(a1)` then `lhu v0,24(v0)`). So target's q is ONE pseudo in v0. To get q=v0, q must beat g in priority.

q refs: def(load) + use(addr) + def(lhu) + use(sh) = 4. g refs: def(load) + use(ori) + def? `g |= 0x80` → g is used and redefined in one insn: refs counted per insn maybe 2 for that insn (one use, one def) + load def + store use = 4? Hmm.

Let me get the actual qty priorities from the dumps? The lreg dump doesn't print priorities. But I can compute from reg_n_refs in the flow dump? The .flow dump prints register info including refs/live. Let me check s13's flow dump for the function.
