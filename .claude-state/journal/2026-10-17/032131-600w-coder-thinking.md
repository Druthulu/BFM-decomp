---
ts: 2026-10-17T09:21:31.613Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab0fc0b10970aee54
model: claude-opus-5-5[1m]
effort: medium
turnId: d5f3c548-1279-4293-8954-e6ee5462dd24
---
I searched for SHB usage outside of ENGINE_SHB and found nothing, confirming all SHB definitions are dead code with no active references. So for that part, I can simply delete the unused definitions without needing to rename anything.

But I want to double-check — my earlier count only checked .c files with a tight regex, and it's possible there are uses with different spacing like `SHB (x)` in headers that I missed. Let me grep headers specifically for `\bSHB\b` to be thorough before confirming deletion is safe.
