---
ts: 2026-11-06T05:25:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_At406U5wxONJVOPI4UvW
---
Now the probe reproduces frame 16! So the frame artifact IS from the asm + the real body (the earlier probe was invalid due to parse errors). Now let me bisect what makes the 16-byte frame: is it the memory clobber alone? Let me test the same body with `__asm__("")` (no clobber) and with no asm.

Actually, we know from the real TU: nobar → frame 0, noasmclob (`__asm__("")`) → score 30, mine 49 ins. Let me check the frame for noasmclob in the real TU: I'll dump it.

But more important: what C construct can produce this 16-byte frame? Let me understand *why* the clobber creates a temp slot. Let me look at the greg/rtl of the probe t5 (small, easy to read) and find the stack slot. Let me grep t5.i.rtl for `reg:SI 29` / `virtual-stack`.
