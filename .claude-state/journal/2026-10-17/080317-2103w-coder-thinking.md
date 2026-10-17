---
ts: 2026-10-17T14:03:17.299Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
The body-only proof hits the same extern conflict, so I'm wondering if a K&R-style definition without the promoted signature could sidestep the redeclaration clash.

With a K&R-style definition, GCC checks compatibility against the prior prototype using default argument promotions: s16 and u16 both promote to int, so they'd match a prototype using int. But this only works if s32 is actually typedef'd as int rather than long -- if it's long, the type mismatch would still trigger a prototype error despite both being 32-bit on MIPS, so I need to confirm how s32 is defined and how old-style parameter passing handles the narrowing conversion back to s16/u16.
