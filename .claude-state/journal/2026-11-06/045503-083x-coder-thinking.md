---
ts: 2026-11-06T11:55:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4YzGV3VbGT6Ff40sSkPA
---
Still forwards (cse substitutes q's value).

OK. Let me try a `do-while` with a **real condition** that creates a loop but executes once... no.

Let me try the cse dump for w2 to see whether the do-while split the EBB. If the EBB split doesn't happen, maybe a different construct will.

Actually, let me look at how cse_basic_block handles labels/notes. The EBB boundary in cse is determined by `LABEL_NUSES`/`CODE_LABEL` and `NOTE_INSN_LOOP_BEG`. Let me check.

Actually, C0535 worked for another function, so do-while CAN split cse1's EBB. Maybe it needs to be around the two copies (store and load) together, which I did in w6 (score 1). Hmm.

Wait, maybe the split happens but the forwarding is not across a block boundary in that case. Let me dump w2's cse and look at the "Processing block" lines.

Let me do that for w2 (do-while around the store).
