---
ts: 2026-11-06T14:28:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NB0SMKqDESRmwZ0iUL5E
---
Only reg 17 and 64/65 (hi/lo) spill, same as c1. So no extra pseudo spilled.

The extra 8 bytes must come from the pad local or a phantom. Let me look at the .rtl dump (before flow) for the function's stack locals. Actually, the frame size is determined in the prologue (expand/final). Let me look at the `.final`/`.rtl` dump for the pad.

Hmm, actually, maybe the while loop form caused the `i` variable to be allocated to the stack in a way that's optimized out but still reserves space? 

Let me look at the .rtl dump for the function's `(note 1 ...)` and stack slots. Actually, let me check the .sched2 (post-reload) dump for the frame. 

Alternatively, let me just try removing the pad[8] from f2 and see the frame. Let me test f2nopad.

Actually, wait: the pad is a "dead BLKmode local: frame 0x10 -> 0x18, zero code". So the pad forces the frame from 0x10 (16) to 0x18 (24). In f2, the frame is 0x20 (32). Maybe the while form needs 0x10 of locals naturally (16), and the pad adds 8 more = 24? No, f2 is 32.

Hmm, let me look at the target: vars=8. The pad is 8 bytes (vars=8). In f2, vars=16. So the pad (8) + something (8) = 16. If I remove the pad, vars=8, frame might be 24! Let me test.

Let me create f2nopad: f2 without the `u8 pad[8];` line.

But careful: the pad might be needed for other reasons (it's in the original). If removing it gives frame 24 with the while loop's extra 8, that's a real-C change (decl removal) and might score 0.

Let me test.
