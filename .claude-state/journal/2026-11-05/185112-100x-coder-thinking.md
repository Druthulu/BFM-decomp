---
ts: 2026-11-06T01:51:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TTghHmf6BBmUdKaplRli
---
That's a different function at the same address in another overlay (different code entirely). Not helpful.

OK. Let me go back to experiments. Since v1 (source order store;sh) yields 138 ins and only a 2-insn order residual, maybe a slight variation makes sched2 swap. Let me look at v1's sched2 dump tail to understand.

Actually — wait. Maybe the correct original source order is exactly v1 (store then sh) and the target's sh;sw order comes from sched2 with a different dependency. In v1, the two stores are both to s0-based addresses. sched2's dependency analysis: `true_dependence` with MEM_IN_STRUCT_P... Let me check v1's .sched2 dump to see the order at sched2 input and output.

Let me dump v1's passes.
