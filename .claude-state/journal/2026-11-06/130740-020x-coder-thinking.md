---
ts: 2026-11-06T20:07:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UoWT4UdVuyx3EccdJsIK
---
Now with `r`, the loop matches except the `-0x400` store: mine uses s4 = -1024 (a callee-saved reg held across the whole function, `li s4,-1024` hoisted to the top) and stores `sh s4,10(v0)`, while target does `li v0,-1024; sh v0,10(v1)`.

So the constant -0x400 got hoisted out of the loop into a callee-saved register s4 in mine, but target rematerializes `li v0,-1024` inside the loop. The extra insn count: mine has li s4 at top (+1), sw s4,32(sp) (+1), lw s4,32(sp) (+1) = 3 extra vs target. Exactly the 3.

Why does mine hoist the constant? Because the constant -1024 is used in the loop and gcc hoists constants out of loops when profitable (loop.c: `move_movables`? or "loop invariant" motion). Target keeps it inside.

To prevent hoisting: make the constant expression not loop-invariant? Or make the store not a constant in a way the loop pass can hoist. Options:
- Write the store differently: `CAST_NONSTRUCT(s16, *p, 0xA) = -0x400;` The value -0x400 = -1024. It's a constant, hoisted.
- Use a variable initialized inside the loop: `s32 c = -0x400; ... = c;` — but loop may hoist the init.
- Use a variable that's set conditionally? Too fake.
- Use the value from a computation involving loop-varying data.

In target, `li v0,-1024` then `sh v0,10(v1)`. Hmm.

Alternatively, block loop hoisting by making the constant's use have a different form: e.g., `= ~0x3FF;` gives li -1024 too? ~0x3FF = 0xFFFFFC00 = -1024. Same constant, still hoisted.

What if the store value is typed as u16: `*(u16*)... = 0xFC00;`? Then target sh v0 with li -1024? 0xFC00 as u16 → li 0xFC00 (which is `li v0,64512` = ori v0,zero,0xFC00; but sh truncates; gcc might use li 0xfc00 → `li v0,0xfc00` encodes ori v0,zero,0xfc00 = 1 insn). Target shows `li v0,-1024` = addiu v0,zero,-1024. Both 1 insn. But score compares instruction text? The score is a COUNT diff of mnemonics probably including operands. If target says li v0,-1024, we need the same.

The issue is only hoisting. To defeat loop hoisting of a constant, gcc's loop.c has `move_movables`: it hoists insns whose operands are loop-invariant (constants included) when the insn is in the loop. `threshold`/`loop_invariant` checks: constants are invariant. It hoists if `reg_single_usage` etc.

Hmm, but wait: the pin version (orig) scored 0 presumably? Let's check: orig.c (with pin) should score 0? The list says these items have the lever; the task is to remove the lever while keeping score 0. The pin version scored 0 presumably. Let me verify by scoring orig.c. If orig scores 0, then the pin somehow prevented the hoist (the pinned $2 forced the -1024 into v0 inside the loop, and loop.c wouldn't hoist a hard-reg constant? Actually `li v0,-1024` in the loop; with the pin, v0 is a fixed hard reg, and loop.c can still hoist constants... but maybe the register pressure or the `v0` being pinned makes the hoist not happen because the pinned pseudo can't be moved out of the loop).

Let me confirm orig scores 0.

Then, the crack: prevent loop hoisting of -1024 by real C. Ideas:
1. Make the constant part of an expression involving the loop var, e.g. `-0x400 + (off & 0)` — identity, not allowed (identity spelling).
2. Compute it from `t`? No.
3. Put the store inside a `do{}while(0)` — C0535 says do-while splits cse1 EBB; but loop hoisting is loop.c, unaffected.
4. Use a variable that is assigned inside the loop from a non-invariant source but still -0x400? e.g. `s32 c = -0x400;` inside the loop; loop.c may hoist the assignment if invariant.

Wait, actually why does target keep it in the loop? Because target's source presumably has the store as written, and gcc *did* hoist constants? Let me check target: `li v0,-1024` inside the loop at 214c. So target does NOT hoist. Mine hoists. Difference caused by the pin? Interesting: in target, the value is in v0 (call-clobbered, no callee-save needed) and used once. Loop hoisting decides based on `reg_single_usage`/`loop_reg_used_before_after`: it hoists if the register would be better used... Actually loop.c hoists constant loads only if "the insn is not a constant load that can be rematerialized"? Hmm.

Let me look at loop.c move_movables conditions for CONST_INT.

Actually maybe it's not loop hoisting but cse's constant pool / combine. `li s4,-1024` at function top, before the switch. That's loop.c `move_movables` hoisting to the loop preheader, and then it needed a callee-saved reg because the loop is inside a switch case, so the reg must survive... The preheader is inside case 2, but s4 is callee-saved because it's live across? Actually s4 is loaded at function top (line 40 region, before the switch) — that's not loop preheader but global cse or "constant propagation across the function"? The diff says mine[40] `li s4,-1024` deleted vs target. Let me see where line 40 is in the listing — after the switch dispatch? Line 40 of 200... the loop starts around line 42 maybe. Let me see mine's listing fully.

I need the disassembly. Let me get it via --keep. Let me check what --keep prints.
