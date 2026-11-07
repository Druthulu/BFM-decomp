---
ts: 2026-11-06T22:13:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Tzw3O9TcYfsz9L8tdAsy
---
Hmm, this i2.txt's numbering differs from the diff's (the diff indices are the scorer's instruction indices, likely after removing nops or a different alignment). Let me find the region with `lui a1,0xff` and the branch. Actually the diff said mine[150] lui a1,0xff vs target nop. In my listing, line 163 is `lui a1,0xff`. The scorer's index may exclude some insns.

Anyway, the mask materialization (lui a1,0xff; ori a1,a1,0xffff) is scheduled early. The target has it 2 insns later. This is a sched1 ready-list tie.

To move it later: increase its dependency on something later, or change the statement order. The mask 0xFFFFFF comes from `(*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF)` — the 0xFFFFFF constant. Its use is the `and v0,v0,a1` near the end.

In the target, `lui a1,0xff` appears after `lhu v0,0(sp)` (the sxy[1] loads). In mine, it appears 2 insns earlier.

What if we write the constant as `0xFFFFFF` vs `~0xFF000000`? Different RTL constant (same value) — could change the schedule. Let me try spelling the mask differently in the otp store: `(*otp & ~0xFFFFFF)`... wait the expression is `(*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF)`. The 0xFFFFFF is the mask on pkt. Try `0xFFFFFFU`, `~0xFF000000`, `0x00FFFFFF`, or `(0xFFFFFFFF >> 8)`.

Also try `((u32)pkt & 0xFFFFFF)` → `((u32)pkt % 0x1000000)` (same value, different RTL?). Or `(u32)(pkt) & 0xFFFFFF` (same).

Let me test mask spellings on i2:
k1: 0xFFFFFFU
k2: ~0xFF000000
k3: 0x00FFFFFF
k4: 16777215
k5: (0x1000000 - 1)

Also try swapping the OR operands in the otp store: `((u32)pkt & 0xFFFFFF) | (*otp & 0xFF000000)` — commutative; might change scheduling.

Let me generate and score.
