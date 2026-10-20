---
ts: 2026-10-17T18:43:36.098Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
I'm comparing the register allocation priorities between s2 (the a0 copy) and s3 (which holds two separate constant values, 0x325 and 0x65). Since s3 is really serving two distinct live ranges bundled into one variable, splitting it into separate variables could change the priority ordering enough to fix things, or alternatively a0 could be referenced directly instead of through s2 in some spots.

I found that the pin is keeping the 0x325/0x65 holder in s3, which causes it to outrank the a0 copy in `s2` during global-alloc. I'll fix this by relocating where s3 is set, splitting it, and adjusting the ref counts.
