---
ts: 2026-11-06T21:28:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Q8pLBRlIcIuIwgCqXi3H
---
Key: "When all instructions have a latency of 1, there is no need to move any instructions. Subtracting one here ensures that in such cases all instructions will end up with a priority of one, and hence no scheduling will be done."

So with all priorities 1, sched1 does NO scheduling — it keeps the original order! But the original RTL order is 58, 60, 55, 63, 65, 70, which differs from the target's 55, 58, 60, 63, 65, 70.

Wait — so sched1 didn't reorder; the *original RTL order* (from expand) already has the li/store before the move! Because the C order is:
```
a = arg0;
*(u16 *)((u8 *)q + 0x10) = 0xc00;
*(u16 *)((u8 *)a + 0xb8) = 1;
func_80146CA0(a);
```
But the RTL order is 58 (li 3072), 60 (store q), 55 (move), 63 (li 1), 65 (store a), 70 (call). So the move was placed AFTER the q-store in the RTL even though it's first in the C!

Why? Because expand may defer the assignment? Hmm. `a = arg0;` — expand_assign for a local variable... The RTL order shows 55 after 60. Interesting: maybe cse/combine moved it? No, sched1 runs after cse/combine.

Hmm, wait: the .sched dump shows the RTL *as it was at sched1 input* (after combine). So some earlier pass moved the move after the store. Which pass? Maybe cse1 (cse moves copies)? Or loop? Or combine?

Actually, maybe the RTL order at expand time was: move, li, store, ... and cse1 moved the move down? CSE doesn't reorder insns. Combine can.

Hmm, let me check the .cse (cse1) dump's order for this function.

Actually, maybe the assignment `a = arg0` was *deferred* by expand: GCC's expand for a MODIFY_EXPR to a variable that is not used... hmm, `a = arg0` is a simple reg copy; expand emits it immediately.

Wait — but the target's source has the keepalive asm right after `a = arg0`, so the move stays there. Without the asm, some pass moved it.

Let me check the .cse dump order.
