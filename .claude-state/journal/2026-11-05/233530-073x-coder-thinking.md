---
ts: 2026-11-06T06:35:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uZ4M6ILeP0jCo5RZrfl0
---
Only a v1↔a0 swap in the tail: the packet tag load (`lw v1,0(a3)` vs `lw a0,0(a3)`) and the D_800A6614 index pointer.

mine: `lw v1,0(a3)` (packet tag), `lw a0,20(sp)` (g.otz), `sll a0,a0,2` (oidx), `addu v0,a0,v0`, `and v1,v1,a2`, `or v1,v1,v0`, `sw v1,0(a3)`.
target: `lw a0,0(a3)`, `lw v1,20(sp)`, `sll v1,v1,2`, `addu v0,v1,v0`, `and a0,a0,a2`, `or a0,a0,v0`, `sw a0,0(a3)`.

So in the target, the *tag value* is in a0 and oidx in v1. In mine, swapped. This is a local-alloc/reload register choice between two locals.

The tag load `*(u32 *)pkt` is a dereference: `(*(u32 *)pkt & 0xFF000000)`. The compiler creates a temp for the loaded value. In the target it's a0; mine v1.

The pin `oidx` ($3 = v1) forced oidx into v1! That's the pin's job. So now I need oidx to land in v1 naturally.

Local-alloc: oidx = g.otz << 2 — actually in the target, oidx is recomputed at the end (`lw v1,20(sp); sll v1,v1,2`). Wait — `oidx = g.otz << 2;` at line 93 and used at lines 95 and 96. The target's tail shows `lw v1,20(sp); sll v1,v1,2` — so g.otz is reloaded and shifted. Hmm, so oidx is *not* held; it's recomputed once for both uses? Let me look: `lw v1,20(sp)` at 6e78, `sll v1,v1,0x2` at 6e88. Then at 6ec8 `sll v0,v0,0xe; addu v1,v1,v0; addu v1,v1,a0; lw v0,0(v1)` — v1 = oidx + (D_800A6614 offset) + &D_800A6614. So oidx (v1) is used in both places.

So oidx is a local-alloc pseudo in v1, competing with the tag-load temp (a0).

Hmm, why would the tag temp get a0 and oidx v1? Because the tag temp is created first (at line 94, `*(u32 *)pkt`) and oidx at line 93. Order: oidx assigned first, then the tag load.

Local-alloc assigns $2/$3/$4... to local pseudos by qty priority (refs/live). Hmm, but a0/v1 are caller-saved: $2=v0, $3=v1, $4=a0.

So the competition is for v1 and a0 among: the tag temp, oidx, the mask constant (0xFF000000 → in a2? target: `lui a2,0xff00; ori a1,0xffff`...).

Hmm, this is a fine-grained local-alloc choice. Options: change the order of statements, or the width of oidx, or split oidx.

Let me try:
1. Move `oidx = g.otz << 2;` after the tag load? The source:
```
oidx = g.otz << 2;
*(u32 *)pkt = (*(u32 *)pkt & 0xFF000000) | (...[oidx + ...] & 0xFFFFFF);
otp = (u32 *)&D_800A6614[oidx + (...)];
*otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
```
Hmm, the target recomputes `lw v1,20(sp)` — meaning oidx was NOT kept from an earlier computation? Actually line 93 assigns oidx; the target emits `lw v1,20(sp)` there (reloading g.otz from the stack because g.otz isn't in a register). So oidx = g.otz << 2.

2. Try `oidx` as u16/s16 → tested (v2 s16 = 68, v3 u32 = 68 — worse because removing the pin changes other things? Hmm, v2/v3 are based on w0 which already has the pins removed... wait, v2 = w0 with oidx s16 = 68. But v0 = w0 with w2 s16 = 13. So oidx width changes hurt.

Let me now try variants based on v0 (w2 s16, oidx plain):
- a: oidx declared s16 → probably worse.
- b: swap the order of `oidx = ...` and the tag store.
- c: split oidx into two variables (one per use).
- d: reorder the two uses.
- e: `oidx` as `s32 oidx = g.otz << 2;` at decl.

Let me try b, c, e and a couple of statement reorderings.

Actually, since only v1↔a0 is swapped, maybe a simple statement reorder fixes it. Let me try a few.

Also: the mask `0xFF000000` and `0xFFFFFF` constants are in a2/a1.

Let me generate variants from v0.
