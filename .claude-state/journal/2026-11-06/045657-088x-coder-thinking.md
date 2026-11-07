---
ts: 2026-11-06T11:56:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8s765nSz4pnnqJFBq0zZ
---
The lbu is BACK! `lbu a0,6(s0)` at line 12 — cse did NOT forward! The intervening store invalidated the entry. But the register allocation is now different (a0/v1/v0 swapped) and the `sh 16` is out of order.

So the mechanism works, but the schedule/regalloc is off. Now I need to get the schedule and registers right. The intervening store changed things:
- temp_a0 got v1, temp_v0 got a0, temp_v1 got v0.
- The `sh 16` stays before the lbu? No: mine has `sb a0,6` then `lbu a0,6` then `addiu v1` then `sh v0,16` then `sb v1,5`... So the `sh 16` moved after the lbu (sched1 moved it back!). Good — the intervening store got reordered after the lbu by sched1, but cse already ran before sched1, so the invalidation happened at cse time. 

So the schedule is close to target but the registers differ. Target: temp_a0=a0, temp_v0=v0, temp_v1=v1. Mine: temp_a0=v1, temp_v0=a0, temp_v1=v0.

Why did the allocation change? Because the intervening store's presence at cse time changed the insn order/uid and hence allocation? The final asm order is nearly identical except the register assignment.

Hmm, the final asm order: mine has `sh v0,16` right after `addiu v1` and before `sb v1,5`; target has `addiu a0`, `sb a0,5`, `sh v1,16`. So the `sh 16` is one position early in mine. And the registers are rotated.

So the intervening-store trick works for cse but perturbs the schedule. I need to find the right placement of the intervening store so that sched1 restores the target order.

Ideas: move a different store (0x12, 0xE, 0x14, 0x16) between; or move the `sb +5` store between (but that's `addiu`+`sb`).

Actually, the target order after the lbu is: addiu a0; sb a0,5; sh v1,16; sh v1,12; sh v0,22; ... In mine, sh 16 came before sb 5.

What if I put the intervening store as the LAST sh store (0x14) instead of 0x10? Then sched1 might move it to the end. Let me test different intervening stores.

Also, the register rotation might be caused by the different insn order at cse time. Let me try each of the 6 sh stores as the intervening one, and also try putting the intervening store as the `sb +5`.

Let me generate these variants:
- y02: intervening = sh 12
- y03: intervening = sh 22
- y04: intervening = sh 18
- y05: intervening = sh 14
- y06: intervening = sh 20
- y07: intervening = addiu/sb +5 (move the +5 store between sb+6 and lbu+6)

Let me write them with a generator.

Also consider: maybe the intervening store should be the `sh 16` but placed differently in source so sched1's order matches.

Let me generate.
