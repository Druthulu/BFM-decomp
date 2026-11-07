---
ts: 2026-11-06T20:21:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Xr84cbZjbbXFwDFI1HQu
---
Mine:
```
21b8 move a0,s0
21bc li v0,7
21c0 sh v0,2(s0)
21c4 jal
21c8 lui a1,0xfff8   <- delay slot
```
Target:
```
21b8 move a0,s0
21bc lui a1,0xfff8
21c0 li v0,7
21c4 jal
21c8 sh v0,2(s0)     <- delay slot
```
So mine: the lui is rematerialized at the call (in the delay slot), and the sh moved before the jal. Target: lui at source position, sh in delay slot.

Also the first cluster: mine has `bnez v0,219c; xori v0,v0,0x1` — the xori copied into the bnez delay slot AND the branch target changed (219c vs 2194), plus the join path. Target: `bnez v1,2194; nop` and then at 2190 `lw v0,220(s0)`, 2194 `nop`, 2198 `xori`. Hmm, the target's structure: the bnez branches to 2194 (after the lw at 2190), then nop, then xori at 2198, then jal at 219c.

Mine: bnez v0,219c with xori in the delay slot; at 2190 lw v0; 2194 nop; 2198 xori; 219c jal.

Wait, mine's bnez goes to 219c and has the xori in its delay slot. Target's bnez goes to 2194 with nop.

So the barrier prevented reorg from filling the bnez delay slot and redirecting. This is the classic dbr issue: the "xori" at the join (after the if/else) is copied into the bnez's delay slot.

The barrier `__asm__("")` before `v ^= 1;` stops reorg's search (stop_search_p halts on an asm insn).

Real-C replacement for a barrier is hard: it's a compiler-level fence. The cookbook mentions C0535 do{}while(0) splits cse1 EBB — maybe a do-while around `v ^= 1;` would split the block so reorg can't copy it? Let me think: reorg's delayed-branch fill looks for an insn after the branch that can be moved into the delay slot. The xori is at the join point after the if/else. The bnez is the branch of the if/else (unkFC != 0). The xori follows the join. Reorg copies the xori into the bnez delay slot and redirects the branch.

If we split the basic block between the join and the xori (e.g., with a do{}while(0)), the xori would be in a different block, and reorg wouldn't move across a label.

C0535: "do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item". A do-while(0) creates a NOTE_INSN_LOOP_BEG/END or a jump? In gcc, `do { } while (0)` generates a NOTE_INSN_LOOP_BEG... and a `jump` to the loop end, which reorg/jump may optimize. It splits basic blocks at the jump.

Let me check how do{}while(0) is emitted: gcc's expand_end_loop for a do-while(0) emits a NOTE_INSN_LOOP_BEG, the body, NOTE_INSN_LOOP_END, and a JUMP_INSN (the backward branch). With a constant 0 condition, it's a jump to the next insn → jump_optimize deletes it? It would create a label and a jump; jump opt turns `jump L; L:` into nothing, but the label may remain as a block boundary.

C0535 says it splits cse1's EBB — so it survives to at least cse1. Does it survive to reorg (after reload, jump2)? Probably jump2 deletes the redundant jump but the block boundary may persist for reorg's delay-slot search? reorg works on the insn chain; the search for a delay-slot filler crosses labels? `stop_search_p` stops at labels? Let me check reorg.c: the delay slot search looks at the next insn(s) after the branch; a code label might stop it (since the branch target could be there).

Hmm, the barrier here is needed because the xori is right after the join label, and reorg copies it into the bnez delay slot. If a label/block boundary exists between the bnez and the xori... but the xori is at the join which is the branch target of the else path. Actually the xori is the join point's first insn.

Let me look at the target structure: 
```
216c beqz v0,2190   (if unkFC != 0)
2170 move a0,s0     (delay slot: p = s0 copy)
2174 lw v0,220(s0)
2178 nop
217c bnez v0,2194   (if v != 0)
2180 nop
2184 li v0,5
2188 j 21fc
218c sh v0,2(s0)
2190 lw v0,220(s0)   <- else arm
2194 nop
2198 xori v0,v0,1
219c jal func_8012B200
```
So the bnez at 217c targets 2194 (the nop after the else's lw at 2190). The xori at 2198 is after that.

Mine:
```
217c bnez v0,219c   -> to the jal
2180 xori v0,v0,1   (copied into delay slot)
2184 li v0,5
2188 j 21fc
218c sh v0,2(s0)
2190 lw v0,220(s0)   (else arm)
2194 nop
2198 xori v0,v0,1
219c jal
```
So mine has the xori duplicated? No: mine's bnez delay slot has the xori and the branch targets 219c (skipping the else's xori? no, the else arm at 2190-2198 has lw+nop+xori then falls into 219c jal). The then-arm (2174-218c) branches to 21fc. So mine executes: if v!=0 → jump to 219c with xori in delay slot (v already loaded at 2174, xori applied). Wait, the bnez is at 217c after `lw v0,220(s0)`. If v != 0, take branch to 219c with the delay slot xori (v ^= 1). Target: if v != 0, branch to 2194 (nop delay), then xori at 2198, then jal. Same semantics.

Reorg copied the xori (from the join at 2198) into the bnez delay slot and redirected the branch past it.

To stop this: a barrier. Real-C alternatives:
- Make the xori not copyable: it's `v ^= 1` where v is a pseudo in v0. Reorg's copy is allowed if the insn has no side effects and its operands are safe.

Hmm, this is the "dbr-delay-fill" wall: "delayed-branch fill takes a fall-through insn the target leaves out of the slot". In walls.txt: `dbr-delay-fill dbr delayed-branch fill takes a fall-through insn the target leaves out of the slot (G18x)`.

But wait — the target DOES have the xori in a delay slot? No: target has `bnez v1,2194; nop` — the nop is the delay slot, and the xori is at 2198, reachable from both paths? Let me re-read the target:

```
217c: bnez v1,2194
2180: nop
2184: li v0,5
2188: j 21fc
218c: sh v0,2(s0)
2190: lw v0,220(s0)
2194: nop
2198: xori v0,v0,1
219c: jal func_8012B200
21a0: sw v0,220(s0)
```
Hmm wait, the target listing above: 2174 `lw v0,220(s0)`, 2178 `nop`, 217c `bnez v0,2194`, 2180 `nop`, 2184 `li v0,5`, 2188 `j 21fc`, 218c `sh v0,2(s0)`, 2190 `lw v0,220(s0)`, 2194 `nop`, 2198 `xori v0,v0,1`, 219c `jal`.

So the then-arm: v = unkDC (lw at 2174); if v==0 → li 5; store; jump to epilogue. If v != 0 → branch to 2194 (nop), then xori, then jal.

The else arm: v = unkDC (lw at 2190), nop (load delay), xori, jal.

So the xori at 2198 is shared by both paths: the bnez target is 2194 (the nop after the else's lw), which falls through to the xori.

In mine, reorg redirected the bnez to 219c and put the xori in the delay slot.

So the target's shape requires reorg NOT to do that. The barrier (asm) stopped the search.

Real-C: prevent reorg from considering the xori. reorg's fill_delay_slot: it examines the insns after the branch; `stop_search_p` stops at a label or an insn that's a branch target. The xori at the join is preceded by a label? In RTL, the join point (after the if/else) has a CODE_LABEL (the else's end/join). Reorg looks at the insn after the branch (2180 nop?) hmm.

Actually, reorg processes each branch: the bnez at 217c. Its delay slot currently has a nop. The fill search looks forward from the branch: insns 2184 (li v0,5), etc. and also considers "the insn after the branch" for the redirect optimization: `reorg` can fill the delay slot with an insn that is the target of... The classic "eager filler" copies an insn from the fall-through path and redirects the branch past it.

The xori is at the join (after the else arm). The bnez's target 2194 is just before the xori.

Hmm, reorg's `fill_slots_from_thread` handles this.

A real-C way to stop it: make the xori not the first insn at the join, e.g., put a non-copyable insn between. Or make the block boundary explicit.

do{}while(0) around `v ^= 1;` would add a jump/label at the join, which might stop reorg (labels stop the search: `stop_search_p` returns 1 for a label? Let me check).

Let me look at reorg.c's stop_search_p.
