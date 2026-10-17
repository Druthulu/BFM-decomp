---
ts: 2026-10-17T16:56:53.054Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
I'm working through the register allocation, swapping arg0 with arg2 and var_s3 with var_s2 so that arg0 ends up in s4, arg2 in s5, var_s3 in s3, and var_s2 in s2, since priority order determines which callee-saved register gets assigned first.

Priority seems tied to reference counts and live-range length, so I'm checking whether I can tilt things by adjusting how many times arg0 versus arg2, and var_s2 versus var_s3, are referenced in the body -- maybe by adding an extra use of arg0 or finding a way to reduce arg2's reference count, though the final field stores need to reload from arg2's memory regardless, so those refs seem unavoidable. I'm now considering whether lengthening arg2's live range or shortening arg0's might shift the priority balance instead.

That trick from T10 that adds a loop-weighted reference wouldn't help here. I should check alloc_table.py to see the actual priorities, and use hdump.sh with the right includer to inspect ov_SC01_000_after.c.
