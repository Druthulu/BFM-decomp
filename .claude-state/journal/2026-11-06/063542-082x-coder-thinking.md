---
ts: 2026-11-06T13:35:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_edp8HCySgSNP4lJnHynf
---
Still 2. Total tries now ~31. Time is over budget for item2. Per the brief, a WALL needs ≥20 min and ≥30 scored tries — I have that. But before declaring a WALL, let me think once more about a promising mechanism.

The key: combine (or cse2) folds the no-op `a1 = a1` with REG_EQUAL into `a1 = fp+16` and deletes the early addiu. To prevent this with real C, we need the no-op's REG_EQUAL note to be absent or the combine to be blocked.

Idea: what if `nn` is assigned a value that is NOT rematerializable as an address — e.g., the address of `buf` computed via a variable index `buf[i]` with i=0? `nn = (s32)&buf[0];` → same address. Tested v05 (score 2).

Idea: what if we use `nn` in an expression between the assignment and the chain so the no-op at the call site isn't a no-op: e.g., `nn = (s32)buf; ... func_80015978(aa, (s32*)(nn + 0));` same.

Hmm, what if the call passes `(s32 *)nn` and we also use `nn` in the chain? no.

What if we make the no-op not a no-op by having the call argument be a *different* register than nn? The call uses a1 because nn is pinned to $5. The no-op `a1 = a1` exists because cse's canon_reg replaced the argument's use of the pseudo with the hard reg... 

What if we DON'T pin nn but pin something else? v21 (nn unpinned) = 27.

What if we pin nn to $4 and aa to $5? That swaps the roles; target has aa in a0, nn in a1.

Hmm, what about the possibility that the *orig* source itself could be written without the barrier but with the nn assignment placed *inside* a do-while that also contains... no, do-while notes don't block combine? Actually, do-while creates a LOOP_BEG note — does combine treat loop notes as barriers? Combine processes basic blocks; a LOOP_BEG note... Hmm, v01 (do-while around the chain) gave 4 (worse).

What if the do-while contains the nn assignment AND the chain (so the block boundary is before nn)? Then combine's window... the block boundary at the loop head might stop the REG_EQUAL propagation from crossing. But cse's global propagation already happened (cse2 is before combine and would still fold). Hmm, in v01 the do-while around the chain gave 4, meaning the addiu moved AFTER the jal. 

Let me try do-while around BOTH nn and the chain:
```
do {
  nn = (s32)buf;
  s0 &= 0x1F; ...
  d[2] = s0;
} while (0);
func_80015978(aa, nn);
```
The call is outside the loop. Hmm, the loop note before nn might make combine treat the region as a loop and not do cross-insn value recording? Let's try a few do-while placements quickly (cheap).

Also: what about a `switch(0) { case 0: ... }`? That creates labels and might block.

Another idea: use a *compound statement* with a label target from a `goto` that's optimized to fallthrough... 

Let me try 5 more:
- v53: do-while around nn+chain+d[2], call outside.
- v54: do-while around the whole block from rand? no.
- v55: `if (nn != 0) { chain }` — might not fold if gcc can't prove the address nonnull? Actually gcc knows &buf != 0, and nn = (s32)buf, so it may fold. If not folded, adds a branch.
- v56: `if (1) { nn = ...; chain }` — folds.
- v57: put `nn = (s32)buf;` inside a do-while alone (tested v04 = 2).

Let me try v53 and v55, plus maybe using a *different* local array whose address is taken... 

Honestly, I think this is a WALL (combine-REG_EQUAL-sink). The moves table has similar WALLs: "cse-copy-merge", "combine-copy-merge". Actually this is exactly `combine-copy-merge` — "combine merges a reg copy the target keeps". The wall tag exists: combine-copy-merge (G23). Our mechanism: combine folds the `a1 = a1` REG_EQUAL copy into the call site and deletes the early addiu. That's combine-copy-merge.

But wait — the tag list says combine-copy-merge is "combine merges a reg copy the target keeps, so the pin stays". Close enough; or cse-copy-merge.

Given the budget, let me do 3 more quick tries (do-while placements) and then record a WALL with best=2, tries≈34, wall tag combine-copy-merge, evidence "combine folds the pinned $5 copy's REG_EQUAL into the call site and deletes the early addiu; 33 lever-free bodies best 2 (144 ins)".

Actually, hold on. Let me reconsider the barrier-free body: score 2 is really close. The ONLY difference is one addiu position. If I can't crack it, WALL with best 2.

Let me do the 3 tries.
