---
ts: 2026-10-22T06:59:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_UVSJbDW2UyHFDw5H96m2
---
In cand22's trace, T-22: "15 (7f000001), now 15" — insn 15 still has the boost! And the chain shows the move (15) at line 248 and the li at 257 (after). So the boost is NOT killed in cand22, yet the order changed!

Wait, the chain: line 224 (move s2,a0), 229 (move s4,a1), 248 (move s0,a2 = reg 6 a2 → wait, "(reg:SI 6 a2)" is the SOURCE; the dest is on the previous line). Let me read the actual lines.

Anyway: insn 15 (the move s0,a2) is boosted in cand22 too, yet the chain has the move BEFORE the li (line 248 before 257). Hmm! So the boost doesn't determine the order?!

Hmm, so in cand22 the move is before the li even with the boost. So my model was wrong.

Let me look at the actual cand22 chain lines 240-260 to see the order.

Hmm, hold on. Let me re-examine cand01: the chain was [move s2,a0, move s4,a1, li(18), move s0,a2(15), call(20)]. And cand22: [move s2,a0, move s4,a1, move s0,a2(15), li(...), ...].

So in cand22, the do-while moved the move s0,a2 BEFORE the li. Why? The do-while creates a loop; the loop body block is scheduled separately, and the "rgb = rgb" self-copy inside the loop is a 2nd set of pseudo 16 → hmm, but the trace shows the boost is still on insn 15.

Hmm! But maybe the boost being on 15 in cand22 is for a different reason: the boost is applied to the *first* set of pseudo 16 which is now... hmm.

Wait, maybe in cand22 the pseudo that gets boosted is different. Let me look at the chain lines 240-260 of cand22 to identify insn 15 and 35 etc.

Let me print those lines.
