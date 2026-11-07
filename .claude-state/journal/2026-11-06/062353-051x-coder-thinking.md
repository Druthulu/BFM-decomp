---
ts: 2026-11-06T13:23:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xtDc9GUWX1a7CaL1xBBL
---
The asm with memory clobber creates dependencies against ALL registers and memory: "add_dependence (insn, reg_last_sets[i], 0)" for every set. So the addiu a1 (which sets a hard reg $5) has a dependence with the asm → can't be scheduled after the asm; it must be before. That's the mechanism.

So we need a real-C construct that creates a dependence between the addiu a1 and something that must stay before the s0 chain. Hmm, what if we make the s0 chain depend on nn (a use of nn that emits no code)? Not possible.

Alternatively, make the *addiu a1* depend on something in the s0 chain? No.

Alternatively: since the asm forces ALL register sets to be ordered before it, maybe we can create the same effect with a real memory operation whose value is used later... 

Wait, what about the pins: aa is $4, nn is $5. What if we reorder the source so that `nn = (s32)buf` is placed *before* the s0 chain AND make the s0 chain use a variable whose assignment is before nn... no.

Alternative approach: instead of forcing the addiu early, make the s0 chain *not schedulable above* it... same thing.

What about making the addiu a1 part of a *multi-insn* sequence that must stay together? E.g., compute nn as `(s32)(buf + 0)` no.

Hmm, what about using a `u8 *` variable instead of s32: `u8 *np = buf;` then `func_80015978(aa, (s32*)np)`. The pin is on nn ($5). The conversion `nn = (s32)buf` — what if we do `nn = (s32)(buf + 0);`? fold removes.

What about `nn = (s32)&buf[0];` — same code (v05 = 2).

OK, different idea: change the *source order of the s0 chain* so that sched1's priorities change such that addiu a1 is scheduled first. sched1 is a list scheduler: it picks the highest-priority ready insn. If addiu a1 has the lowest priority, it's scheduled last. To raise its priority, give it a "birth" boost: if its destination is a pseudo (not a hard reg) born there and used later. With the pin, dest is hard $5 → no boost. Without the pin (v21), score 27 — much worse overall (allocation changes).

Hmm, but what if we keep the pin but ALSO introduce a second, unpinned temporary that nn is copied from? e.g.:
```
s32 np = (s32)buf;   // unpinned pseudo, birth boost → scheduled early
nn = np;             // pinned $5, copy from np
```
The copy `nn = np` would be a `move $5, <reg>` — an extra insn! Unless the allocator coalesces np into $5, making move $5,$5 which is deleted. Hmm, but np's birth is the addiu (addiu np,sp,16), then move $5,np. If local-alloc gives np=$5, the move is a no-op deleted, and the addiu writes $5. That gives exactly the target's addiu a1! And the birth boost on the unpinned pseudo makes sched1 schedule the addiu early.

Wait, but local-alloc: np is a pseudo used once (in the move). It would be assigned a hard reg — probably $5 via the copy preference (local-alloc ties the source of a copy to the dest if possible). Actually the pinned $5 is the dest of the move; local-alloc's combine_regs may tie np to $5. Then the move becomes move $5,$5 → deleted. 

But careful: at sched1 time (before local_alloc), the RTL has: addiu np,sp,16; move $5,np; ... The scheduler sees the addiu with a pseudo dest born here and used by the move (1 use). birthing_insn_p requires REG_N_SETS==1 and ... it gives the boost. Then the addiu is scheduled early. After scheduling, the order is: addiu np; move $5,np; then the s0 chain. Then local_alloc coalesces → move deleted → final: addiu $5,sp,16 at the right spot!

Hmm, but is the move deleted before or after sched2? The noop move deletion happens in the final jump_optimize (cross_jump pass, noop_moves=1) which is AFTER sched2. So the move $5,$5 sits through sched2 and then gets deleted. Would sched2 move things? It might. But the move itself occupies a slot; if it's deleted at the end, the final code could match.

Actually wait: if np and $5 are tied, the move is `move $5,$5`; at sched2 it's a no-op that the scheduler may keep or delete? `delete_noop_moves` at the final jump_optimize removes it. But dbr_schedule runs AFTER jump_optimize (line 3142 vs 3167), so the delay slots are filled after deletion. Good.

But there's a risk: local_alloc might NOT tie np to $5 (it could give np another reg, leaving a real move). Let's test.

Actually simpler: what if we make `nn` a pseudo (unpinned) and pass it — v21 gave 27, meaning allocation was wrong. But with an explicit copy trick we keep the pin.

Let me try:
v30: `s32 np = (s32)buf; nn = np;` (replace `nn = (s32)buf;`)
v31: `nn = (s32)buf; { s32 np = nn; nn = np; }`? no.
v32: `u8 *np = buf; nn = (s32)np;`
v33: reverse: `nn = (s32)buf;` but declare `nn` normally and add a pinned copy... no.

Also consider the same trick for aa? aa is fine.

Let me test v30/v32.

Also another idea: use the *address* `&buf[0]` through a pointer variable `u16 *bp = buf;` and then `nn = (s32)bp;`.

Let me generate.
