---
ts: 2026-11-06T22:15:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JFVstmzsTvGWWyCCVrrm
---
m2 = 4 (ORDER), m4 = 7 (ORDER). i2 = 3 remains best.

m2 wraps the pkt[0x14] block in a do-while: score 4 (one more ORDER position). m4 wraps the w2 block: 7.

Let me combine m2 + i2 (the otp do-while): m2 keeps the otp do-while? Yes, m2 = i2 + p14 do-while. Score 4 — worse than i2's 3 by one position.

Hmm.

Let me look at m2's diff to see the extra mismatch. Maybe combining differently (p14 do-while without the otp do-while) gives a different schedule.

Actually, let me try wrapping the p14 block AND the sxy block differently, or using a do-while around the `oidx` line + otp.

Alternatively, since the residual is the constant pair, let me try to make the constant's *first use* later by reordering the packet store: the mask is used in the packet store's `and`. If the packet store expression used a different mask spelling that combine splits differently...

What if we compute the low 24 bits via `(u32)pkt & 0xFFFFFF` but write the packet store as `(*otp-style)`? no.

Let me think about the sched1 dump for i2 to see why the constant is placed at 163. Maybe there's a REG_DEAD/dependency note difference. The target's RTL (with pins) had the mask (r193) set at insn 401/402 and used at 365. In i2 (lever-free), the RTL might differ slightly (e.g., r193's definition order).

Actually, the pin affected the RTL: with the $2/$3 pins, the register allocator... no, sched1 runs before local-alloc, so the pin (a hard-reg variable) affects the *RTL* via expand (the variable is a hard reg, so the RTL uses (reg:SI 2) directly, not a pseudo). That changes the sched1 dependencies! With pins, the hard regs create anti-dependencies (REG_DEP_ANTI) between insns using the same hard reg, which constrains the schedule. Lever-free, those anti-deps are on pseudos and handled differently by sched1.

That's why the mask placement differs: with pins, the scheduler had different constraints.

So to reproduce the target's schedule lever-free, we need to recreate the same dependency structure without pins — hard.

Given i2 = 3 (only 3 ORDER positions, all one constant pair), this is very close. Maybe one more perturbation fixes it. Let me try:
- n1: i2 + a do-while around the sxy block? (m1 = 11, worse)
- n2: i2 + a do-while around the p14 block (m2 = 4)
- n3: i2 with the p14 block *reordered* (e.g., move pkt[0x24]/pkt[0x25] earlier).
- n4: i2 with the sxy stores reordered.

Since the target's schedule for everything else matches i2, the only issue is the constant. Let me try a `do{}while(0)` around just the packet store's mask subexpression? Can't wrap an expression.

What about making the mask a `static const`? No.

What about computing the mask via a variable initialized at declaration (C0505 "init at decl")? e.g., add `u32 mask24 = 0xFFFFFF;` at the top of the function and use it in both stores. That changes the RTL: the constant is materialized at function entry (or when needed) and kept in a pseudo. The target materializes it late (166), so an early variable would be worse... unless the compiler rematerializes.

Hmm. Let me try `u32 mask24 = 0xFFFFFF;` declared just before the tail (inside the block) and used twice. Sched1 might keep it near the first use.

Also try `u32 hi_mask = 0xFF000000;` similarly.

Let me test n5: declare `u32 m24 = 0xFFFFFF;` right before the packet store, use it in both.
n6: use `m24` only in the otp store (packet store keeps the literal).

Let me run.
