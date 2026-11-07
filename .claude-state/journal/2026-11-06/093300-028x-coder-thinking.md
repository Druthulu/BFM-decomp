---
ts: 2026-11-06T16:33:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7bPFt5RDHWaa11NrPciq
---
Same. Cross-jump merged the branches again (the beqz at 2ba0 is shared, then arm jumps into it via bnez at 2b94? Actually here bnez v0,2ba0 is the unk70 test jumping to the shared beqz).

Hmm, so cross-jump aggressively merges. The only thing that stopped it was an RTL difference. Let's look at what jump2 does with the barrier version. Build dumps for the src (with asm) version to see the shape. I need a TU scratch with the barrier. I can make a candidate v0.c identical to orig (with asm) and --keep, then copy that TU to dumptu. Then dump. Let's do it and compare jump2.

Actually, more useful: understand which insns differ. Let me dump orig (asm) version.
