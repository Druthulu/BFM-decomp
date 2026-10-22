---
ts: 2026-10-22T00:43:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_oTFzxAAFlMoPMk0iVmXr
---
pad[2] → frame 32 (the target's frame!).

So the frame fix: `s32 pad[2];` (8 bytes) → the frame is 32.

Now let me combine: the cast (v0 = (s16)v0) + pad[2]. Let me create that variant and score it.

Let me also do the same for func_8017EF0C (item 5, same shape).

Let me write a small script to build the combination.
