---
ts: 2026-11-06T17:39:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jKnDGGm2k9WPY2cnbACx
---
j3: 41 (260 ins). No.

Time 13.4 min. Let me do a final ~6.5 min of tries. Let me try a few more random-ish but legitimate variants:

k1: `sh16 = angle << 16;` → `sh16 = angle << 16, sh16 = sh16;`? no.
k2: declare sh16 as `u32` + cast in the expression.
k3: use `p[0x79] = (u16)((sh16 >> 16) + (s32)((u32)sh16 >> 31)) / 2;` (div) — no.
k4: `sh16 = (angle << 16) | (angle >> 16);`? wrong.
k5: use `s32` casts on the shift count.
k6: change the store `p[0x79] = (u16)(...)` to `*(u16 *)(p + 0x79) = ...`.

Let me run k2, k6, and a couple.

Actually, let me reconsider whether the *other* 3 instructions (the two slls) can be made to match differently: the target's first sll is `sll v0,a0,0x10` (in the delay slot of beq). Mine: `sll v1,a0,0x10` in the delay slot. So the only difference is the destination register. If sh16's register changed to v0, everything would match (the chain would follow).

So it's purely the sh16 allocno register. The preference for v1 is the blocker.

One idea: change the *first setter's source* so that its local reg is v0. The first setter's source is `angle` (77), which local-alloc put in a0 (4). Why a0? Because the copy from the call result (v0) to angle, and angle is used in the store... If angle were in v0, the preference would be v0 → sh16=v0!

How to make angle be in v0? angle = call result. If angle is a *block-local* pseudo in the block where the call is (the block before the branch), local-alloc might give it v0 (the lowest free). In the target's build, angle is in a0 (`move a0,v0`), so the copy exists.

The copy `angle = func(...)` — the call result is in v0 (hard reg); local-alloc's combine_regs ties angle to v0 (a copy preference!) → angle gets v0? But the asm shows `move a0,v0`, meaning angle is in a0 and the v0 value is copied. Hmm, if angle had a copy preference for v0, it'd stay in v0 and no move. The move exists because angle is live across the func_8014CB7C call (in the else path) — v0 is call-clobbered! So angle can't be in v0; it's copied to a callee-saved... a0 is also call-clobbered. Hmm, a0 is caller-saved too. But the func_8014CB7C call happens after the branch; on the then path angle is used before any call.

Anyway, angle=a0.

So the preference for 75 comes from 77=a0? But the dump says 3 (v1). I keep failing to explain it.

Let me just try changing angle's register by making it live differently: e.g., add a use of angle after the call in the else path? no.

Time: let me run a few more, then record the WALL.

Let me try: `sh16 = (s32)(angle << 16);` in the then arm and `sh16 = (s32)(p[0x79] << 16);` in the else. (g3=7).

I'll do a last batch of 4 and then record.
