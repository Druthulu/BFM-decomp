---
ts: 2026-10-22T00:26:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_SUlsssIZpd14tAzU2an8
---
Item 7: base = score 2! Just one instruction out of place: the load `lw a0,32(s0)` should be at 96 but is at 97.

So we're one insn away. The launder's effect: the load of t (unk20) should come one slot earlier.

The target:
```
95 ?
96 lw a0,32(s0)     ; the load of t (the call's arg)
97 ?
98 ...
```
Mine has it at 97.

So the load needs to move up by one instruction. That's a scheduling/latency thing.

The re-tie `__asm__ __volatile__("" : "=r"(t) : "0"(t));` before the call: it makes the load's dest have 2 sets → the load is not boosted → it stays at its source position (before the call's arg setup group).

Without the re-tie: the load is boosted → placed as late as possible → just before its consumer (the call arg setup) — but the arg setup is the call itself, so it lands in the "call group"...

The difference is one position. Options to fix:
(a) Move the call's argument into a variable so the load happens earlier: e.g.
```
s32 t;
t = ...->unk20;
func_8001D0E8(t, 0x140, 0xF0);
```
→ the call arg is t (already). Hmm.

(b) The target's order: the load at 96 is one slot earlier. What is at 95/97 in both? Let me dump the target around 90-100 to see the context.

Let me look at the target and mine.

Let me dump the target for func_8017E780 (indices 85-105).
