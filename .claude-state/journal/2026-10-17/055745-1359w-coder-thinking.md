---
ts: 2026-10-17T11:57:45.256Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I'm checking adjust_priority logic for the birthing insn case—since insn 18 sets register 79 which is reused three times (reg_n_sets != 1), it doesn't qualify as a birthing instruction, so it won't get the max launch priority boost.

The fix: making `a` a set-once variable at insn 18, e.g., splitting into separate variables (a0, a1, a2) per statement rather than reusing one. That would give insn 18 the launch priority boost too, and with tie-breaking by LUID the scheduler should produce the desired order: lw pb0, lhu a, then lw pac, matching the target output. I want to try splitting both `a` and `b` into distinct per-row variables to test this.
