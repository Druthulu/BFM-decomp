---
ts: 2026-11-06T22:36:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BX4qvkeGI83dU7BCcXyg
---
In w4: r73 = the divisor (9 refs/27, crosses 1 call, conflicts s0) → gets $s1 (presumably). r74 = s1ang raw (2 refs/7, crosses 1 call) → $s0 (local-alloc). Same problem: the local pseudo takes $s0.

So even with arg1 direct, the divisor is global (r73) and conflicts $s0.

OK so the fundamental blocker is the local r74 (s1ang raw) taking $s0.

Hmm, so how did the ORIGINAL compiler get d into $s0? Maybe the original s1ang raw was NOT a separate local pseudo. Maybe the original source had the s1ang value used in a way that made it global, or the original had a different block structure.

Let me look at the target's instruction stream again for a clue about the source:
```
lh $3,14($2)      # arg0+0xE
lh $4,D_80126CB8
lh $5,6($2)       # arg0+6
lw $2,32($2)      # arg0+0x20
subu $4,$3,$4
lh $3,D_80126CB4
lh $17,18($2)     # s1ang
jal ratan2
subu $5,$3,$5
addu $2,$2,-1024
andi $4,$2,0x0fff   # u5
sll $16,$16,16
andi $17,$17,0x0fff # u6
bne $17,$4,$L72
sra $16,$16,16
```
The `lh $17,18($2)` is s1ang. In the target, $17=$s1.

Hmm, what if in the original, the s1ang load was *sunk* after the call and the register allocator still used $s1 because... no, the instruction is before the call.

Wait, actually — what if the original source's s1ang computation was placed AFTER the call, and sched1 moved the `lh` before the call. Then in the RTL *before sched1*, s1ang's def is after the call. But sched1 runs before local-alloc, so the scheduled RTL has it before the call. Hmm, same.

Unless sched1's move happens... let me check whether the s1ang load can be hoisted above the call by sched1. If the source order is: call first, then s1ang load, sched1 might hoist the load above the call (since the call's memory side effects are unknown, sched1 usually does NOT move loads across calls — calls are `CALL_INSN` and sched.c treats them as barriers? Let me check sched.c).

Let me test w3 (which I made: u5 first, then s1ang) — it scored 45, and 75 ins. Let me check its alloc table: does s1ang still cross the call? Let me dump w3.

Actually w3's score 45 with 75 ins means the scheduler produced a different order. Let me look at the w3 alloc.
