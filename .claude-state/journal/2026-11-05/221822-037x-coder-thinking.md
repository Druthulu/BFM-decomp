---
ts: 2026-11-06T05:18:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bkXrjWAC0Sg7TtS1ihrB
---
All 46. The copies still collapse. Hmm.

Wait — maybe the issue is that cse is aggressive about the whole chain: raw = t; tmp = (s16)raw; t = tmp. cse: raw ≡ t; tmp = (s16)raw → tmp ≡ (s16)t; t = tmp → t = (s16)t → since t is known in range, no-op.

The func_8017E204 trick worked because there was no back-copy: v0 → t → v1, a one-way copy that cse kept because v1 ≠ v0 (different pseudos with different uses). Wait, but `v1 = t` where t = (s16)v0; cse should equate v1 with t and t with v0... The note says "The HImode copy escapes cse's equivalence class, so v1 keeps its own register and the move v1,v0 survives".

Hmm, in that case cse kept v1 separate because v0 is *reassigned* later? Look: v0 is reassigned in the if arms (`v0 = func(...)`). So v1 = t (copy of old v0) must survive because v0 is clobbered. That's the real reason! The HImode just prevents the sign-extend from adding instructions.

In our case, t isn't reassigned before the store, so the copies are pure no-ops.

Hmm. So we need a situation where a variable is reassigned. In the target, after the stores, `r = func_80012ABC(...)` and `*(s16*)(s1+0x12) = r`. So the store value t is used immediately.

What if we write the stores using `raw` and then `t = raw` where raw is... no.

Let me reconsider the target asm again. Actually — maybe the target's two moves are NOT raw=t;t=raw. Let me look at the pinned orig RTL to see what the launder produces. Let me dump the orig.

Actually, let's dump the ORIG (pinned) TU and look at the RTL around the copies. That tells us exactly what the pins produce, and we can think about what else could produce it.

Let me do that: copy src TU? The orig body is in src; the TU is src/md_MAIN_033/md_MAIN_033.c. I can dump it directly with cc1_dumps_tu.sh (accepts a .c file). DUMP_ROOT under my dir.
