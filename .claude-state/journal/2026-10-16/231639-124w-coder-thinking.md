---
ts: 2026-10-17T05:16:39.844Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f214c1b8ceabcd8
model: claude-opus-5-5[1m]
effort: medium
turnId: edd2b196-9038-4e7d-9ca7-b103d9ac818f
---
That's odd that grep isn't finding these definitions directly — they might live in shared headers, use asm alias names, or come from a source file included under a different build directory, like SC03_015 possibly mapping to SC03_014's source as an alias binary. I should check the Makefile for that mapping and also search more broadly for "8017E3F0" in case SC06_018's reference uses a different symbol name.
