---
ts: 2026-11-06T14:26:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dqJbQe3Mli81cViGVUKS
---
Still 6 and same swap. So the copy `t = i` was folded before flow (cse2), adding no ref. Let me verify by dumping g1's flow refs. But likely cse2 removed it.

Hmm. Let me use the do-while(0) split to prevent cse2 from folding. But then combine might not fold across the block boundary, leaving an extra insn.

Actually, wait. Let me reconsider the C0535 trick: `do { t = i; } while (0);` creates a NOTE_INSN_BLOCK boundary? Or a label? The do-while(0) is optimized away by the front-end (it's a compound statement with a constant condition), so it produces NO RTL at all. But it splits the cse EBB? How? The note says "The block boundary splits cse1's extended basic block". Hmm, maybe the do-while(0) becomes a `NOTE_INSN_BLOCK_BEG`/`END`, and cse's EBB detection stops at block boundaries? Actually, cse's `cse_end_of_basic_block` may stop at NOTE_INSN_BLOCK_BEG? Not sure.

Hmm, the do-while(0) with a body of `r = p + i` and then the store after — maybe the mechanism is that the front-end emits the `r = p+i` in a separate statement tree, and the do-while creates a scope/block that... Honestly, let me just test the do-while(0) version.

Let me try:
```
do { t = i; } while (0);
} while (t < n);
```
Wait, the do-while(0) would be inside the loop body, and then the outer condition uses t. The do-while(0) is optimized to nothing at the RTL level (I think gcc's front-end emits the body then discards the loop). But the C0535 note says it DOES affect cse1's EBB. Let me test.

Actually, the C0535 note is about two copies being kept in source order. The mechanism: "The block boundary splits cse1's extended basic block, so the copies are not merged/re-ordered there". So the do-while(0) DOES create a block boundary note in the RTL.

Let me test g2:
```
do {
    ...
    i++;
    src++;
    do { t = i; } while (0);
} while (t < n);
```
Hmm, but if cse can't fold and combine can't fold across the boundary, we'd get an extra `move`. Let me test and see.

Actually, maybe I can put the do-while(0) AFTER the comparison? No.

Let me test g2.
