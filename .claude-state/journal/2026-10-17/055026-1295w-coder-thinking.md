---
ts: 2026-10-17T11:50:26.981Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
I'm tracing register k, which lands in a3 globally, against the target's local use of v0 for the mask-and-shift operation — checking whether k's live range there would conflict with a2, which seems to be the reason k avoids that register in the first place.

Checking the target code confirms k loads directly into a3, matching K3's assignment, while a2's conflict there explains the preference leak into m. The real fix seems to require forcing a conflict between m and k — perhaps by noting m is actually the function-scope index temp (v0) that's live precisely when k is born in the K3 region, which would naturally block the coalescing that's causing the leak.
