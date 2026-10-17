---
ts: 2026-10-17T09:35:48.105Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab0fc0b10970aee54
model: claude-opus-5-5[1m]
effort: medium
turnId: e67ec4d7-2552-463e-a4a7-26524910e47f
---
I notice the trailing fake markers got left behind after the pins were removed, so now I have stale orphan markers that census will flag. Rather than running the broader scrub, I should just strip those marker comments from lines where no actual asm code remains, and double-check that the restored author markers line up correctly with the unchanged code.

Also confirming the generic rewrite logic treats pre-existing markers like "tus9" as generic, leaving them unrestored under T8.c1's convention—that checks out fine.
