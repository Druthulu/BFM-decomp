---
ts: 2026-10-17T17:21:00.824Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm looking at this header item with 136 includers, similar to the earlier count-copy pattern via launder. The frame_pad keepalive reserves a phantom 0x10 stack frame—in gcc 2.7, unused local arrays still allocate stack space even when the array itself goes unused, so the frame size stays dependent on that padding.

Testing whether dropping just the keepalive or just the launders separately changes the frame size.
