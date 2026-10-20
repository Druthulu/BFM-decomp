---
ts: 2026-10-17T17:27:05.631Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
All 10 rows are done now. Since the do-while trick worked so well and I'm well under the 20-30 min budget on most wall items, it's worth going back to retry a few walls with that same approach, starting with func_80182424 where keepalive merges might crack with the do-while rewrite.

I also want to try wrapping copies and frame logic in func_8017FBCC and func_80128ED8, test the delay-slot scan workaround in func_8017DD80, and see if the loop-note CSE boundary behavior helps in func_800CB138. I'll start with func_8017FBCC by wrapping the copy assignment in a do-while(0) block.
