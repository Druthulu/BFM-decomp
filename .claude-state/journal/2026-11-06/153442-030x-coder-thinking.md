---
ts: 2026-11-06T22:34:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DlqS7ZhDjGfnvOiMX1gS
---
"flag_schedule_insns means schedule insns within basic blocks (before local_alloc)." So sched1 runs BEFORE local-alloc. So if the source order has the s1ang load after the call but sched1 hoists it before the call, then local-alloc sees the hoisted order and the pseudo still crosses the call. And the target instruction order is achieved. But the RTL order (for live range) would be the scheduled order? Sched1 reorders the insns in the RTL stream, so yes.

But would sched1 hoist a load above a call? Let me check sched.c: calls are `CALL_INSN` and the scheduler may move insns across them if the dependencies allow. Typically sched1 treats a call as a barrier for regs but memory loads can be hoisted if no aliasing. Let me just test.

Test candidate w3: reorder source so u5's ratan2 is computed first, then s1ang load:
```
d = arg1;
u5 = (ratan2(...) - 0x400) & 0xFFF;
s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
do { d = (s16)d; } while (0);
u6 = s1ang & 0xFFF;
...
```
If sched1 hoists the lh before the call, we might match. Let's try.

Actually, wait. In the target, the order is: lh arg0+0xE, lh D_80126CB8, lh arg0+6, lw arg0+0x20, subu, lh D_80126CB4, lh s1ang, jal, subu. So s1ang's load is *last* among the pre-call loads, right before the jal. That's consistent with the source having the s1ang load AFTER the u5 computation and sched1 hoisting it up to just before the call (the scheduler moves it as early as dependencies allow, which is late because the address (arg0+0x20 pointer) is loaded... hmm, actually the lw $2,32($2) is before).

Hmm, in the source, s1ang's load is BEFORE u5's computation. The `lw $2,32($2)` (pointer) is loaded early, then `lh $17,18($2)` after `lh $3,D_80126CB4`. This ordering could be from sched1.

Let me just test w3 (reordered source) and see the score.

Actually, better: let me think about what sched1 does with the current order. The current source order: 
1. d = arg1
2. s1ang = load
3. u5 = (call - 0x400) & 0xFFF
4. cast
5. u6 = s1ang & 0xFFF

The scheduler reorders within block 0. The target order has s1ang's lh just before the call. If the source order is s1ang first, the scheduler might sink it? No, it's a load; sched1 hoists.

Let me just test both orders and see. w3 = u5 before s1ang.

Let me also consider that maybe the local-alloc issue can be sidestepped by making the s1ang load's pseudo NOT cross the call because sched1 sinks the load to after the call (if the source has it after). Then the target order (lh before jal) wouldn't match.

Let me test w3.
