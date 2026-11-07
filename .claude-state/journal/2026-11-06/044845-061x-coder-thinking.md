---
ts: 2026-11-06T11:48:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tZJoE1YnZxN96jnxeoPc
---
The difference: target has `lw a1,-4(s1)` before `lw v0,-8(s1)`; mine has them swapped. This is sched1 birth order: two independent loads `part->xx` and `part->zz`? Let's see the C:

```
wx = part->xx;      // lw v0,-8(s1)? or -4?
mn = wx;
mx = wx >> 16;
wz = part->zz;
wv = wz >> 16;
```
Hmm: `part` = arg1+0x14, then `part++` → +0x20 each. The loads at -8(s1) and -4(s1) are part->xx and part->zz (after the addiu s1,s1,32). Target loads -4 first (zz) then -8 (xx). Mine loads -8 (xx) then -4 (zz).

Wait, but source order is xx then zz. Mine follows source; target reversed. The launder (which was after `wv = wz>>16`) doesn't affect this. Hmm, but v2 removed the launders and this ORDER residual appeared. Interesting: so the launder removal caused this? Let me check: the target (with launders) has -4 first. v2 (no launders) has -8 first. So the launder's presence affected the scheduling of these two loads (birth order). Hmm, the launder #2 is after `mny = wy + dy;` (line 2833) and before `my = (wy >> 16) + dy;`. The loads of xx/zz happen earlier.

Wait, actually maybe the register allocation changed: `s1` is part. The two loads are xx and zz. In target, a1 = zz (used for wv = zz>>16 → srl a2,a1,0x10) and v0 = xx. Mine: v0 = xx, a1 = zz, but the *order* differs: mine does lw v0,-8 first.

Hmm, this is sched1 ordering of two independent insns. The C order is xx then zz. Target does zz then xx. Why would the target (with launders) reverse it? Because sched1 reorders based on birth/priority; the launder changes the birth insn for wz.

Actually wait: `wx = part->xx;` → lw v0,-8; `wz = part->zz;` → lw a1,-4. Hmm, but which offset is which? part->xx at offset 0, zz at offset 4? After `part++`, part = base+0x20, so xx is at -8? Hmm: `part = (Part*)(arg1+0x14)` then `part++` adds 0x20 → s1 = arg1+0x14+0x20. So part->xx at s1-8 = arg1+0x14+0x20-8 = arg1+0x2C. Hmm, the struct layout: xx at 0? Then zz at 4 → -4(s1).

OK so target loads zz first, then xx. Mine loads xx first. Since both are independent, sched1 orders them by birth priority. The launder (on wz) is a use of wz that... hmm.

Actually, maybe it's not sched1: maybe it's the *local-alloc* order. In the target, a1 = zz's value, v0 = xx's. The two loads are in one EBB. sched1 could reorder.

Let me test: does adding a *real C* statement change this? The launder was at line 2833: after `mny = wy + dy;`. Its purpose: "zero-byte re-tie #2". Removing it changed the schedule of the loads.

Hmm, what if instead of removing both launders, I remove them but add something real? Let me first check whether removing only launder #1 or only #2 gives what.

Let me test individually:
- v5: only launder #1 removed.
- v6: only launder #2 removed.

That will tell which one causes the ORDER diff.
