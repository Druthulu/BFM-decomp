---
ts: 2026-11-06T22:37:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DaowGf3dsGcv8JTKmHRh
---
In w5, r75 (s1ang) still got s0 via local-alloc (blk 0, 3 refs/13 live, pri 2307). The do-while around the load made it 3 refs/13 — still local (blk 0). So the do-while did NOT globalise it (still in block 0). Hmm.

Wait, "blk 0" means it's in block 0 — local-alloc'd. The do-while's loop block might be merged into block 0? The load is in a loop block, but since the loop is trivial, maybe the block boundaries... The alloc table says blk 0 and hard s0, so local-alloc got it.

Hmm, C0535 says do{}while(0) splits the cse1 EBB (not necessarily a basic block). Basic blocks are determined before cse. A do-while creates a NOTE_INSN_LOOP_BEG/END, and loop.c might create a block. But local-alloc uses basic_block_head/end from the CFG. If the do-while generates an actual branch (a loop test), there'd be a block. But since the condition is 0, gcc may eliminate the branch, merging the block.

Hmm, but the refs went 2→3 and live 7→13, so the loop note changed the live range but it stayed in block 0.

Let me try a different way to globalise: put the s1ang load in an if-block that doesn't add instructions? E.g.:
```
if (arg1) { s1ang = ...; }  // adds a branch
```
No.

What about using s1ang in the *return* path of a block? Hmm.

Let me look at how func_8012BA10's coder globalised s1ang. The moves.md says "globalising s1ang lifts its pri 6363 past d 5185 (G27x)". Let me look for the G27x shard's notes for that function to see the exact move.
