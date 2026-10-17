---
ts: 2026-10-17T05:19:31.385Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f214c1b8ceabcd8
model: claude-opus-5-5[1m]
effort: medium
turnId: edd2b196-9038-4e7d-9ca7-b103d9ac818f
---
I'm checking whether these functions' return values are actually consumed by their callers—for SC03_111 and SC06_018, since callers never use $v0, declaring them void seems correct even though a jal technically sets a return register.

For SC03_011, the preamble declares func_8017E3F0 as s32 but there's no actual call consuming a return value, so that declaration should be fixed to void. The other definitions (SC04_009, SC06_015) are consistently void with no callers to contradict that.

I'm now wondering if the "return-type lies" flagged in the earlier log might actually come from other overlay binaries that declare func_8017E3F0 differently, so I should grep for all declarations of this function across binaries outside these six directories to compare against its real definition.
