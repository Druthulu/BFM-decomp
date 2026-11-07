---
ts: 2026-11-06T16:43:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eRvtO8aVVnbq4P837win
---
The dumptu/t.c differs from p4's TU! My cp happened before the --keep finished? No — the command was: --keep, then cp p4/... to dumptu/t.c. But the diff shows dumptu has `func_801822A4(param_1); return;` at 4542 while p4 has `goto docall;`. So p4's TU is w4 but dumptu is the OLD copy — the cp must have failed or the p4 TU was written after my cp? Actually the --keep for w4 wrote p4; then I cp'd p4/... to dumptu. The diff says dumptu has the v3-like text (call+return) — that's the v3 TU. So the cp of p4's TU didn't take effect? Wait, the previous dumptu copy was from v3. Hmm, the cp command in the same bash call: `cp .run/P36/.../p4/ov_SC01_084_jr_8017F690.c $D/dumptu/ov_SC01_084/t.c` — it should have copied. Unless p4 didn't exist yet... the --keep output said p4/cand.o. Then cp. Hmm, but the diff shows dumptu/t.c = v3 content. Maybe the cp ran before delever finished writing the TU? They're sequential in bash. 

Wait, actually looking at the diff output: it's `diff dumptu/t.c p4/...c` showing lines 4542-4543 differ: dumptu has `func_801822A4(param_1); return;`, p4 has `goto docall;`. The v3 variant had `func_801822A4(param_1); return;` inside each arm — two occurrences. Line 4542 is in the source region. So dumptu is v3.

Hmm, why did cp not work? Maybe the p4 TU file is named differently (e.g. the scratch dir has the TU only when --keep and the name is the TU basename). Let me check ls of p4.

Anyway — the dump I read was v3's, not w4's. The actual w4 (score 0) is verified by disassembly. Good. I don't strictly need the dump; the disassembly proves the target layout. But for evidence I want the mechanism. The disassembly shows the unmerged layout: then arm has beqz+j, else arm beqz. So the branch forms must differ. Since the score is 0, that's enough evidence: "jump2 cross-jump did not merge: then arm branch normal form (eq v0,0 -> docall) vs else inverted (ne v0,0 -> skip)".

Let me confirm by dumping the correct w4 TU. Let me find p4's TU name.
