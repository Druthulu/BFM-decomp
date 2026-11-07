---
ts: 2026-11-06T12:37:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JkidazP8u2HfnfTugYIX
---
Interesting: `;; 8 regs to allocate: 73 72 187 104 90 74 93 87`. Reg 73 goes in 4 (a0)! Reg 73 = ? Looking at dispositions: `73 in 4`.

Which pseudo is `ret`? Let me find where pseudo 73 is defined as the return value. In the RTL, ret is a pseudo. Let's grep for "(reg:SI 73" near the STORE.

Also interesting: the conflicts list for 73: `73 conflicts: 72 73 2 3 29` — so 73 can't be v0 (2) or v1 (3)? It conflicts with 2 and 3! That means at some point pseudo 73 is live where v0/v1 are hard-live.

That's why: `ret` conflicts with v0. So even the target's C would conflict... unless in the target, ret's live ranges avoid v0-live points. Hmm, but the target has ret IN v0, so no conflict there.

The conflict arises because in c2, at the point where ret is live, v0 is also live (used by something else). E.g., in an arm: `li v0,N` for the comparison, then `ret = ...`. Look at the target's arm: `li v0,41; bne v1,v0; ...; j; li v0,7`. Here v0 holds the comparison constant, then ret=7 overwrites v0.

In c2 (ret in a0), the comparison constant is in v0 (`li v0,41`) and ret goes to a0. So ret's live range spans across the comparison (`li v0,41`) → conflict with v0 → can't be v0.

Why does ret's live range span the comparison? Because the C's arms are sequential `if (unk70 == 0x28) {...ret=7; goto STORE;} if (unk70 == 0x29) {...ret=10; goto STORE;}` — ret's live range from its def in arm A to the STORE use... no, it's dead after the goto.

Hmm, the conflict could come from the *last* arm (0x2D) where after the if-chain, ret is defined at line 166 and used at STORE. Or from the uninitialized early returns (removed in c2).

Wait, actually: `ret` is assigned in arm A then `goto STORE`. At STORE, `unk2 = ret; return ret;`. The live range is def→STORE. In between: nothing (the goto jumps). Fine.

But global.c computes conflicts from live ranges; if the goto's RTL flow is such that ret stays live through the following blocks (because of the CFG), hmm.

Let's find pseudo 73's definitions/uses in the RTL dump to see the live range. Let me grep "(reg:SI 73" in the greg dump near the end.
