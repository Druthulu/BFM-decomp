---
ts: 2026-11-06T10:01:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Do3QPHs2fdVDFa7Hxg7M
---
The lreg dump is per-block. Hmm. The alloc table showed r74 refs 7 live 27 — but the .lreg "Register 74 used 2 times across 2 insns in block 0" is a *different* numbering? The alloc table's numbers come from the .greg dump which has different pseudo numbers (post-local-alloc?). Actually alloc_table reads both .lreg and .greg and merges.

This is getting complicated. Let me instead use the .greg dump directly, which is the input to global allocation and has the order + preferences + conflicts. Let me look at the function's .greg section.
