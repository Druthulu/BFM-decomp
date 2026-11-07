---
ts: 2026-11-06T20:27:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NbAECavecarxcdDKuSUA
---
Identical residuals. The do-while was removed (jump2 deleted it).

Let me think differently about both clusters.

Cluster 1 (barrier/dbr): target has `bnez v0,2194; nop` and the xori after the join. Mine has `bnez v0,219c; xori` (delay slot filled). The barrier asm stopped reorg's search. Real-C alternatives?

reorg's `stop_search_p` stops at CODE_LABEL (labels_p=1) and JUMP_INSN/BARRIER. So if there were a label between the else-arm and the xori, the fill would stop. The else arm ends and the join begins. A `do{}while(0)` around the *else arm* might leave a label at the join? Or an if/else structure change.

Wait — actually, what about restructuring the source so that the xori is not the first insn of the join block? E.g., make the two arms differ so the xori is in a block with a label. The target's xori at 2198 is preceded by a nop at 2194 (which is the bnez target). Hmm.

Alternatively: change the control flow so reorg can't do the copy. reorg's fill_slots_from_thread for a conditional branch: it scans the thread (the branch target path) for a candidate insn to move into the delay slot and redirect. The candidate xori is at the join, reachable from the branch target.

What if the branch's delay slot is already occupied by something? The `p = s0` copy (move a0,s0) went into the *first* beqz's delay slot (216c: beqz; 2170 move a0,s0). 

Idea: make the then-arm's `return` produce a different structure... 

Alternatively, maybe a real C change to the `v ^= 1` expression: if the xori were part of a larger computation, reorg wouldn't copy it. E.g., `v = v ^ 1;` is the same. What if we use `v = (v ^ 1) & 0xFFFF;`? The store is `sw v` (32-bit). unkDC is s32. Hmm, `& 0xFFFF` would change the value if v has high bits. Not safe.

What about `v = ~v & 1`? no, different.

Hmm, what if we make the xori's destination a different register so reorg can't copy it into the branch's delay slot? Reorg's copy requires the insn to be safe (no side effects, and its operands not clobbered by the branch path). `v` is in v0. If the xori wrote to a different register, reorg might still copy.

Alternatively, what about making the join block start with something that can't be moved? Like the call? Hmm.

Wait, maybe I should look at the actual reorg decision in the .dbr dump for nolau vs orig. In orig, the asm barrier stopped it. Let me see what the dbr dump says about the branch.

Actually, let me reconsider: maybe there's a different C formulation of the whole if/else that yields the target structure without the barrier. The target:

```
214c bnez v0,2164      ; if (func_8012BEE8(a0) != 0) goto L2
2150 nop
2154 lh v0,252(s0)
2158 nop
215c beqz v0,21fc      ; if (unkFC == 0) return
2160 nop
L2 2164 lh v0,252(s0)
2168 nop
216c beqz v0,2190      ; if (unkFC == 0) goto else
2170 move a0,s0        ; p = s0 (delay)
2174 lw v0,220(s0)     ; v = unkDC
2178 nop
217c bnez v0,2194      ; if (v != 0) goto join2
2180 nop
2184 li v0,5
2188 j 21fc
218c sh v0,2(s0)       ; unk2 = 5 (delay)
2190 lw v0,220(s0)     ; else: v = unkDC
2194 nop
2198 xori v0,v0,1
219c jal func_8012B200
21a0 sw v0,220(s0)     ; delay
```

So the target's code has the `v = unkDC` load in BOTH arms (then-arm at 2174 and else-arm at 2190), and the join at 2198 has the xori.

Mine matches this except the bnez at 217c: target `bnez v1,2194; nop`, mine `bnez v0,219c; xori`.

Hmm, interesting: in the target, the bnez's delay slot is a nop and the branch goes to 2194 (the nop after the else's load). In mine, reorg filled the delay slot with the xori and redirected to 219c (skipping the else's xori at 2198).

Wait, in mine, is the else's xori at 2198 still there? Mine's listing: 2190 lw v0; 2194 nop; 2198 xori; 219c jal. Yes, the else path still has the xori. So mine duplicates the xori in the delay slot for the then path.

Reorg's "eager filler": it copied the xori from the join into the bnez's delay slot (the then path) and redirected the branch past the join's xori.

To stop it: `stop_search_p` at a CODE_LABEL. The search that found the xori started from the branch's thread (2194). Between 2194 and 2198 there's no label. If we could get a label there...

What if the `v ^= 1;` statement is preceded by a statement that generates a label? E.g., a `do{}while(0)` around the else arm? Or an empty statement?

Alternatively, what if the join code is arranged so the xori is not immediately after the label? For instance, if the then-arm's `v = 0x20` assignment were moved... no.

Hmm, let me look at the reorg dump for nolau to see exactly which optimization fired. Search for the branch insn and "delayed branch" messages. The .dbr dump may have comments like ";; delayed branch" or the fill decisions. Let me grep around the xori.

Actually the .dbr dump in this build might not annotate. Let me grep for "fill" or "delay" in reorg.c's dump output.

Let me check what the dbr dump prints.
