---
ts: 2026-11-06T14:54:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_imQBKICa7VUPQpYQUsIt
---
Line 2363: "Find the longest possible equivalent sequences... Store zero there if no equivalent preceding instructions are found." and line 2473: it compares two insns with REG_EQUAL/REG_EQUIV notes to the SAME constant, and replaces their sources with the constant. This is `find_cross_jump` / `cross_jump` optimization!

The second jump_optimize is called with `cross_jump=1` (the args are `jump_optimize (insns, 1, 1, 0)` = cross_jump=1, noop_moves=1, after_regscan=0).

The cross-jump optimization finds two similar code sequences and merges them. Hmm.

Actually, the fold `bne t,5,L71; bne t,3,L73` -> `bne t,5,L71; j L73` — maybe cross_jump merged the `bne t,3,L73` with another similar branch?

Wait, let me re-read the jump2 dump. In mine:
```
jump_insn (ne s0,v0) -> L71      # bne t,5,L71
jump_insn (label_ref) -> ?       # unconditional
```
In orig:
```
jump_insn (ne s0,v0) -> L71
asm
jump_insn (ne s0,v1) -> L73
```

So mine's `bne t,3,L73` became `j L73`. This is a conditional-to-unconditional conversion. That's not cross_jump.

Hmm, wait — maybe the `bne t,3,L73` was NOT converted; maybe the C `if (t != 3) goto sel_094;` was compiled as `j sel_094` because the compiler knew t==5 from the earlier `if (t == 5)`. But the first jump pass didn't fold it...

Actually, let me look at the .jump (first pass) dump for c1's case 5 region. If the `bne t,3` is there (3 branches), then the fold is jump2. If it's already folded, it's the first pass.

The jump_insn counts: rtl 72, cse 62, cse2 62, jump 62, jump2 58. So from .cse2 (62) to .jump (62): no change. From .jump (62) to .jump2 (58): -4. So jump2 removed 4 jumps (merged branches). This is the cross_jump / conditional conversion.

Let me look at the jump2 dump's optimization. Actually, the `-4` might be from cross_jump merging sequences elsewhere.

Hmm. Let me look at the actual c1 .jump (first pass) case 5 region to see if the `bne t,3` is there. Let me find the labels in the .jump dump.

Actually, let me compare the .jump dumps (c1 vs orig) normalized — earlier I did and they were identical (except numbering and the asm). So at .jump, both have the 3-branch structure. At .jump2, c1 folded. So jump2 folded it.

Now, jump2's cross_jump: it looks for two insns with REG_EQUAL/REG_EQUIV to the same constant and merges them. Hmm, that's about constants.

Wait, let me look at the jump2 dump for mine: after `bne t,5,L71`, the unconditional `jump (label_ref N)`. Let me determine the target. If it's L73, then the `bne t,3,L73` became `j L73`. How? 

Actually — maybe it's the `delete_unreachable_code` after thread_jumps. Let me think about thread_jumps: it threads jumps through blocks. The `bne t,5,L71` jumps to L71. The fall-through block has `bne t,3,L73`. Hmm.

Let me look at jump.c's `thread_jumps` and the conditional handling. Actually, let me look at the jump2 dump for a comment. The .jump2 dump is just the RTL (no comments about optimizations). 

Let me look at the jump.c code around line 2473 (the cross_jump equivalence merge) and around 1483 (simplify_relational_operation). Line 1483 might be the "if (x == c) ... if (x != c)" simplification.

Let me read jump.c around 1450-1560.
