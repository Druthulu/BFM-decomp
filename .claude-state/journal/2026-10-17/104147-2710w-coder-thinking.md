---
ts: 2026-10-17T16:41:47.197Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I'm weighing whether c4 deserves a PARTIAL label since it retains the same kinds (pin, keepalive) despite fewer levers, versus just noting win.c's reduction from three pins to one as the more useful win worth recording.

The else-branch's v0=NULL assignment only matters for a function that returns a value, so switching that function to a void signature would let flow analysis drop both the NULL assignment and the call result's v0 slot entirely—worth a new tag like flow-void-return to capture this.
