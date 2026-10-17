---
ts: 2026-10-17T13:50:52.162Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
I'm realizing that stores through computed addresses like obj+0x14 don't invalidate scalar fields such as D_80126B78, since that's an in-struct reference rather than a plain register store. To invalidate everything, the store would need a plain register address or QImode access, though I suspect CSE might still fold a computed pointer back into the same plus-offset form anyway.
