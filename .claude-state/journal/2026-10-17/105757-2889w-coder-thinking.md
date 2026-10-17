---
ts: 2026-10-17T16:57:57.306Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
This looks similar to func_80185944's launder pattern, matching func_80186B70's behavior where launder sets pv masked, pin $3 gets dropped, and pin $4 angle is kept. Since this is just a launder kind, the other pins may remain unaffected—I want to check those win.c cases elsewhere.

Reading other shards should be fine even if writing to them is restricted, so let me locate the W04 directory for func_80186B70.
