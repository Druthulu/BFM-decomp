---
ts: 2026-10-17T09:22:29.764Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab0fc0b10970aee54
model: claude-opus-5-5[1m]
effort: medium
turnId: d5f3c548-1279-4293-8954-e6ee5462dd24
---
I'm thinking about the orphan marker problem — if the original use-line comment has no corresponding site after macro expansion, it becomes dangling. I'm planning to expand the macro so each lever line carries its own trailing marker comment, and considering whether to drop the original use-line marker text to avoid duplication.

I'm reconsidering marker wording since old text like "lever inside #define" goes stale once expanded — but delever --apply --rejudge rewrites markers with verdicts generically anyway, so exact wording matters less. Dead-code macros don't need markers when deleted, and ENGINE_SHB_NV becomes irrelevant since all SHB paths are dead.

Now I'm looking at how the census classifies site lines for multi-line macros versus one-liners — checking RTP_SND's register pin assembly against XFER's laundering inline asm, and noting that RTP_SND may have two different definitions in SC06_030 that need separate handling.

I'm writing a small expander script that parses #define blocks with backslash continuations into params and body lines, then needs to locate each use site, including ones embedded inline with other code like inside an else-if branch — so I should print out all the use lines first to see their shapes.
