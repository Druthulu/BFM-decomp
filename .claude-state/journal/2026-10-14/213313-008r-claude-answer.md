---
ts: 2026-10-15T03:33:13.433Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a1ce918197a39b8ec
model: claude-opus-5-5[1m]
effort: medium
turnId: aa27e162-4e37-4415-af47-d4f34f5bcfc6
usage: {input: 10, cacheRead: 93548, cacheWrite: 969, output: 577}
---

PA3 has been updated from 3.28 to 3.28.1. It's a small release with two fixes:

- The status line shows the titles of queued tasks again, including tasks whose plan line doesn't name a status.
- The seed-size warning now appears only when an expert starts with a context above 40k tokens. Before, it also fired just because a seed had grown.

This update changed the mod's own files, and the new mod only loads when Claude Code next starts or when you run /reload-plugins. No task will start until then, so please do one of those when convenient. The memory curator is still next once the work goes on.
