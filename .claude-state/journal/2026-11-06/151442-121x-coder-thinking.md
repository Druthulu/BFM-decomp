---
ts: 2026-11-06T22:14:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zPwyOjCPfPXmt90CRFBa
---
l1 = 3 (same). The mask temp doesn't change it.

The residual is purely a sched1 tie for the constant. Let me look at the sched1 dump for i2 vs the target... but we don't have the target's RTL. However, we can reason: the mask `lui/ori` pair is scheduled at position 163/167 in mine vs 166/170 in target.

What determines the position? sched1 processes the ready list; the constant materialization has no dependencies, so it's ready from the start; its priority is based on the length of the dependency chain to the end. If the mask's use (the `and`) is late, the constant's chain is short → low priority → scheduled late (when few other insns are ready). The target has it later than mine.

If I make the mask's use slightly *later* in the RTL, the constant would be delayed. The use is `and v0,v0,a1` after the otp load. If the otp load/address were computed slightly later, the mask would move later. But the address computation matches the target.

Alternatively, increase the priority of the other insns so they fill the slots before the mask. Hmm.

What if we add a dependency: make the mask depend on something available at position ~166? E.g., `((u32)pkt & 0xFFFFFF)` where pkt is loaded at 174... no, pkt is a3 (available early).

Idea: write the mask as `0xFFFFFF ^ 0`? constant-folded.

Idea: use a shift to build the mask from the 0xFF000000 value: `~(0xFF000000)` — same constant.

Idea: make the mask a *global* constant load? No.

Idea: compute the low part as `(u32)pkt & 0xFFFFFF` but write it as `(u32)(pkt) << 8 >> 8`? That changes insns (sll/srl).

Hmm.

The residual is 3 ORDER positions — the only difference. This is exactly the kind of wall the walls.txt has tags for: "sched1-ready-order" (O03x), "sched1-const-pair-hoist" (O01x), "sched1-la-sink" (O02x). Here the constant pair (lui/ori) is scheduled *early* relative to the target (target keeps it later). The existing tag "sched1-const-pair-hoist" = "sched1 hoists a constant pair above the store the target keeps first (O01x)". That fits: sched1 hoists the const pair.

But wait — maybe I can fix it by changing the do-while span so the scheduler boundary changes. i2's EBB starts at the do-while; the target's schedule has the mask at 166. Let me try wrapping *more* before (e.g., include the `w = mulc; vv = e[1]; if...` lines) or *less*.

Actually, the do-while affects cse1/sched1 EBB boundaries. What if I wrap the *sxy stores* (lines 156-171 in source) in a do-while? That would change the EBB before the mask.

Let me try: wrap the six `*(s16*)...` sxy store lines in a do-while (with !FAKE). The target's schedule for those matches; the EBB change might shift the mask.

Also try: wrap the `pkt[0x14]...pkt[0x25]` block.

Let me test a few.
