---
ts: 2026-11-06T11:37:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HRKP5Na8LpRKiPv9SW34
---
Same score 81, same result. So sched1 hoists the Blk8#1 to the top regardless.

The problem: Blk8#1 is being scheduled first (highest priority). To prevent that, the Blk8 copy needs a dependency on the earlier stores, or lower priority.

Idea: make the Blk8 copy source/dest overlap with the earlier store target so the compiler sees aliasing. E.g., write the Blk8 copy as a copy of the struct `D_80126960 = *(Blk8*)&D_80120210;` — the addresses are distinct symbols, so no aliasing.

What if the original wrote the Blk8 copies as `memcpy`? No, memcpy would be a call.

What if the target's ordering isn't from sched1 at all, but the Blk8 copy is actually lower priority because... hmm.

Let me look at what sched1 does with the orig (pinned) version — it scores 0. The pins make v0..a3 hard registers. In sched1, hard-register dependencies are explicit: the pinned registers create anti-dependencies/ordering. E.g., r2 is pinned to v0, and Blk8#1 uses v0 as data — so in the pinned version, Blk8#1's `lwl v0,...` conflicts with the pinned v0 holding r2 (a WAR/WAW dependency), forcing Blk8#1 AFTER the group A stores. That's exactly it!

So the barrier is not what orders it; the PINS create the register dependencies that force Blk8#1 after the group A stores (since v0/v1 are pinned to r2/r3 and still live). Without pins, v0/v1 are free, so sched1 hoists Blk8#1.

So to reproduce without pins, I need the group A values to be live in registers that Blk8#1 must reuse... which is a register-allocation outcome, circular.

Alternative: force a dependency in real C between Blk8#1 and the earlier stores. For example, compute the Blk8 source pointer from something loaded earlier. E.g., use a pointer variable that is set from r2? That would change the code.

Hmm. What if the Blk8 copies are written using the SAME variables r2/r3 as data:
```
r2 = *(s32*)&D_80120210; r3 = *(s32*)&D_80120214;  // would be lw not lwl
```
No.

What if I use a union of Blk8 and the scalar globals? E.g., the original might have had:
```
typedef struct { s32 a,b,c,d; ... } State;
```
and copied field by field. Doesn't create dependencies.

Real C dependencies: make the destination address of Blk8#1 depend on a value stored earlier. E.g.:
```
D_80126950 = r2; ...
D_80126960 = *(Blk8*)(&D_80120210);
```
No dep.

Could use: `D_80126960 = *(Blk8*)((char*)&D_80120210 + (r2 & 0));` — that's an identity launder, not allowed.

Hmm.

What about making the Blk8 copy part of a bigger struct copy that includes the scalars? I.e., if the whole thing is ONE struct assignment, the compiler emits a BLKmode copy (lwl/lwr) for the whole 0x?? bytes — no, that wouldn't match (target has individual lw for scalars).

Wait, actually, let me reconsider. What if the target's group A loads are NOT temps but the compiler's own, and the pins weren't needed at all — the original C is different.

Let me look at the target's group A: lw v0,0(v0) — load D_80120200 into v0, then sw v0,0(at) to D_80126950. The store address uses `at` (lui at). Since all addresses are in the same page 0x8012, why separate lui? Because each is a different symbol and cse didn't merge. Fine.

Let me count: are there other functions like this that were cracked? moves.md line 12: "barrier,launder | func_80180100 | MATCH — field-direct &= and -- on s0->unkAC (no temps), dead pad[2] dropped". Not similar.

Let me search moves.md for "Blk8" or "struct copy" or "lwl".
