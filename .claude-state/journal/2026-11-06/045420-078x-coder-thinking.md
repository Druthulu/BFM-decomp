---
ts: 2026-11-06T11:54:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QPsUjgJNLG9TNvJ0QDHt
---
Still 13. The mask swap is stubborn.

Let me look at the exact register allocation question. Maybe the issue is not a0/a2 for the masks but the *order of the ands*. Let me look at the full p1 disassembly of the else branch vs target.

Target else:
```
3fa0 lui a2,0xff / ori a2 (m24)
3fa8 lui a0,D_800B9A02 / lhu a0
3fb0 lw v1,0(t1)          pv
3fb4 sll v0,a0,2
3fb8 addu v0,v0,a0
3fbc sll v0,v0,2
3fc0 lui at,D_800AE7BC / addu at,at,v0
3fc8 lw v0,0(at)
3fcc lui a0,0xff00 (mFF)
3fd0 lw v0,0(v0)
3fd4 and v1,v1,a0
3fd8 and v0,v0,a2
3fdc or v1,v1,v0
3fe0 sw v1,0(t1)
```
Mine p1:
```
91 lui a0,0xff / ori a0 (m24)
93 lui v1,D_800B9A02 / lhu v1
95 lui a2,0xff00 (mFF)
96 sll v0,v1,2
97 addu v0,v0,v1
...
102 lw v1,0(t1)   pv
104 and v1,v1,a2  (pv & mFF)
105 and v0,v0,a0  (*ot & m24)
```
Two differences: (a) m24/mFF swap, (b) the D_800B9A02 value in v1 (mine) vs a0 (target) — because v1 is pv's pin in both... hmm target uses a0 for the index temp, mine v1. But the pin pv=$3 (v1) is loaded later in both.

Target order: lui a0 for D_800B9A02 then lhu a0; mine: lui v1, lhu v1.

So the *index temp* (a0 vs v1) and the masks (a0/a2) swap. In target, a0 is used both for the index temp AND mFF (after the index temp dies). In mine, v1 is the index temp and m24=a0, mFF=a2.

So really the target allocates: index temp → a0 (dies at 3fbc), then mFF → a0 (reused), m24 → a2. Mine: index temp → v1, m24 → a0, mFF → a2.

The difference: in mine, m24 is allocated before/independently of the index temp.

Why would the index temp take v1 in mine? Because a0 is taken by m24 (allocated earlier, live across the index computation). In target, the index temp gets a0 because m24... wait m24 is in a2 and mFF in a0 later. So in target, a0 is free for the index temp, meaning mFF is not yet born (it's born at 3fcc after the index dies) and m24 is in a2.

In mine, m24 is born at the top (lui a0,0xff at 91) and lives until 105. So a0 is occupied → index temp goes to v1.

So the difference is WHEN m24's materialization is scheduled. Target materializes m24 first too (3fa0) but in a2. So target's m24=a2 from the start.

So the question is just which register m24 gets: a2 in target, a0 in mine. Local-alloc priority: m24 has 2 refs, mFF 2 refs; the index temp has 1-2 refs.

Hmm, local-alloc assigns in qty order (by ref count, then... ). a0 vs a2: both caller-saved. Why a2 for m24?

Maybe because `pv` is pinned to $3 and `at` is reserved... The allocation order among {a0, a1, a2, a3, t0...}: a1 is used for idx (andi a1,s1,0xffff) in the outer block.

I wonder if the pin $3 (pv) or something else causes it. Let me try removing... no, pins may stay but don't have to! The pins are levers of other kinds that MAY stay — we can also remove them if that helps? "levers of other kinds the def already had (pins under other causes) may stay, never added" — so keeping or dropping is fine. Dropping a pin might change allocation!

Let me test p1 without the $3 pin (and without the $6/$4 pins in the if branch) to see if the else branch aligns. Risky: the if branch might break, but let me measure.

Actually the pins $4 (pv, if branch) and $6 (i4) are in the if branch. Let me try removing only the $3 pin in the else.

Let me generate:
- h1: p1 without the $3 pin.
- h2: p1 without $3 pin and with mFF var.
- h3: p1 with m24/mFF as s32.

Test h1.
