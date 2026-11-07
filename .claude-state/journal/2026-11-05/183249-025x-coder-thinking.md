---
ts: 2026-11-06T01:32:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XL9xmk3kP8ySAfAbPVuA
---
Only binaries. But there's a tarball gcc-2.7.2-psx.tar.gz. Extracting it would be huge and disk is capped. But maybe the source tree exists elsewhere (docs?). Let me search project for "insns_match_p" in tarball? Instead, the src comments already explain semantics. Let me read src/ov_SC03_099/ov_SC03_099_jr_8012ACE0.c around 1355 and the after.c note (32) for how cross-jump works and how people defeated it.
