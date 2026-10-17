---
ts: 2026-10-17T11:02:46.795Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
Lane 1 failed calibration, so moving to lane 2. For match_one, I need to figure out how to isolate a single function with proper externs — the TU has other functions too, so I should check how delever_search's --try mechanism handles building that scratch compilation unit.

There's a contradiction between the brief saying win.c should be just the function definition and match_one needing full compilation context with externs to pass CC1. I'll keep both a win.c and a win_body.c variant and decide which satisfies the actual test later. Also still need to locate the asm path for ov_SC04_011 to use with --asm-subdir.
