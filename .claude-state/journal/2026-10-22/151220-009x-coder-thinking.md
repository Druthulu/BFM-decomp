---
ts: 2026-10-22T21:12:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0TgdkEYe72O6RoaSEgK7
---
Score 13, 106 vs 114 ins. So lever-free, the compiler cross-jumps: arm3 (the one with the barrier) shares its tail with... let's think. The target has 114 ins: all four arms separate. Mine has 106: 8 fewer ins — the arm3 tail (sh v0,32; li 1536; sh; li -80; sh zero; sh zero; j; sh) — that's 8 insns merged.

Actually cross-jumping merges arm1 and arm3 (identical bodies). The target keeps them separate (arm3 has the barrier). Hmm, the target has both arms fully duplicated.

So I need plain C that keeps the two arms separate. The difference in target arm3: `unk30 = k` where k = -0x50 born above the barrier so sched1 can hoist the li.

Key insight: the barrier is between the birth of k and its use. In the target, `li v0,-80` appears in the arm at slot 52 (before sh zero at 53,54), i.e. hoisted. Actually let's look at target disassembly to understand. Let me get the full target disassembly.

Actually the mechanism: cross-jumping (jump.c / the "cross-jump" pass) merges identical tails. To prevent it in plain C, the two arms must differ in RTL. Since arm1 and arm3 bodies are identical, we need to make arm3's body textually/semantically different in a way that produces the same instructions — e.g. different expression spelling that yields the same insns but different RTL before the cross-jump pass.

Options:
- Use `k` variable (s16 k = -0x50) which is already there, and in arm1 write -0x50 directly as a literal. They already differ that way... but they produce the same RTL after expansion? Actually arm1 stores the constant -0x50 directly (`sh` with li -80), arm3 stores k. Since k is a local variable born right there, it's likely propagated. So RTL identical → cross-jump merges.

To break cross-jumping in plain C: make one arm's last store use a different expression that still yields `li v0,-80; sh v0,48(s0)` but with different RTL structure. E.g. `unk30 = -0x50 - 0;`? That folds. `unk30 = (s16)(k);`? Hmm.

Alternative approach: reorder the statements in arm3 so the RTL differs in order... but then the insn order in the output changes.

Hmm, wait. Maybe the real point is different. Let me look at the target disassembly vs mine more fully to understand which arms merged.

Let me get the target and mine full disassembly. Is there a tool? dt.sh gives diff. Let me check delever_search.py options.

Actually, let me first look at how other shards cracked `barrier` kind. Let me grep moves.md for "barrier".
