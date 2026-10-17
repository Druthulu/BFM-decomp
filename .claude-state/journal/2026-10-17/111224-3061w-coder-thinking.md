---
ts: 2026-10-17T17:12:24.361Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm figuring out the register allocation timing: r is computed as q+96 before the first call and stays live across two calls, so I need to reorder the instruction scheduling to move a1/s0 ahead of the lui/lw/addiu sequence, which is really the scheduler's responsibility. There are two issues to resolve: register priority between r and the sector variable, and the actual instruction ordering. I also note that pp is cast from q and gets passed into CdIntToPos.

I'm testing a few variants: trying `pp = q` before or after `r = q + 0x60`, or just passing `(CdlLOC*)q` directly into the first call instead of going through pp, since pp gets reused later in the loop and argument evaluation order (likely right-to-left) affects which register gets set first.
