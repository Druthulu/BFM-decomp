---
ts: 2026-11-06T12:03:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5N3hghj3m8eikkUckNef
---
Only difference: the two stores in the loop body use `v0` in target but `a2` in mine. Specifically:
```
q[0] = ((uint)(q + -5) & m2) | c3b;   -> addiu/and/or/sw using v0 (target) vs a2 (mine)
r[-1] = u6 | (p2 & 0xffff) | uVar5;   -> andi/or/or/sw using v0 vs a2
```
The target uses v0 as the scratch; mine uses a2 ($6).

The keepalive `asm("" : : "r"(uVar2))` forces uVar2 into a register and keeps it alive, affecting allocation. uVar2 is pinned to $6 (a2) via `register uint uVar2 __asm__("$6")`. So uVar2 = a2. The keepalive uses uVar2, extending its live range so that a2 is occupied, forcing the stores' scratch to v0.

Without the keepalive, a2 is free and the stores use it.

So the keepalive's effect: keep uVar2 (a2) live across the stores so the scratch uses v0.

Real C: uVar2 is used in `rval = (uVar2 * 8 + 8) | 0x4000;` which comes AFTER the stores in the target order? Let me check the target order:
```
q[0] = ...
r[-1] = ...
[keepalive]
rval = (uVar2*8+8)|0x4000
rval = base6|rval
r[-2] = c74v
r[0] = rval
```
So uVar2 is used after the stores (in rval). So it's live across the stores naturally! Without the keepalive, uVar2 is still used later, so it should stay live in a2...

But the allocator chose to use a2 for the stores' scratch, meaning it considered uVar2's value not needed in a2 (maybe it rematerializes or the pinned a2 is reused because uVar2's last use... hmm).

Wait, `register uint uVar2 __asm__("$6")` pins it to a2. The stores use a2 as scratch, which would clobber uVar2. That's only valid if uVar2 is dead after the stores. But uVar2 is used in rval AFTER the stores. Unless the compiler moved the uVar2 use before the stores (scheduling).

The target's keepalive forces uVar2's value to be live at that point.

Hmm, without the keepalive, the compiler may have recomputed uVar2 or moved its use. Let me look at mine's order around there. The diff only shows the two store groups using a2 instead of v0; the rest is identical. So in mine, uVar2's use (rval = uVar2*8+8) must still be there. If a2 is used for the scratch stores and then uVar2 is used, that's a conflict unless uVar2 is dead and the compiler uses a2 freely... but the pin forces uVar2 to a2.

Wait, if uVar2 is pinned to a2 and also used later, the stores can't clobber a2. Unless the scheduler moved the uVar2 use BEFORE the stores. Let me look at mine's asm around lines 130-150.

Let me print both around the loop.
