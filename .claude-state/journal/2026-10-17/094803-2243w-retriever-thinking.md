---
ts: 2026-10-17T15:48:03.665Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abc9700d4a3ffcffd
model: claude-haiku-5-5[1m]
effort: medium
turnId: 7ef976bd-e783-42c8-aead-e51ace4d47d5
---
I'm tracing where the lying originated — it looks like T8.c4 changed the return types of func_80026514 and func_800CBA44 from extern void to extern u8*/s32 while keeping K&R-empty parameters, which may be when these decls first became unledgered, since T6 showed lying=0 before T8.

Now I want to confirm by grepping the T8.c4 log for func_800268D0, unbacked, NONSTRUCT, and fix-related entries, plus check T10 log for lying fixes. I also confirmed there's no "wall:cse-const-addr" convention anywhere in the residue TSV, so I can mark that as not found, and I should check the TSV for other naming patterns like cse, sched1, flow, or $sp appearing in survivor rows.
