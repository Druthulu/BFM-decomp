---
ts: 2026-10-17T17:47:43.146Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af8c379eaae6cf6ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 4f5d1d7b-243b-4976-9079-51d9b9c05b4b
---
I need to update the comments for func_800391D4 regarding the pin bullet and asm pads, and for func_80140958 note that the keepalive asm removed is now replaced by a continue-as-goto with incrementing j inside a nested do-while(0). I should also check win.c around line 129 for other in-body comments referencing the removed fences, since WH1 suggests win.c may still carry outdated descriptions — let me grep through it.
