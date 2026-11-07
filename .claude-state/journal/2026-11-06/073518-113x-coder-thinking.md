---
ts: 2026-11-06T14:35:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cPlHnWo3TupoFgyaBHgh
---
In c1, the order is:
```
	move	$4,$16
	li	$2,-655360
	li	$16,4
	sw	$2,20($4)
	la	$2,D_8019DAFC
	li	$3,0x40000000
	or	$2,$2,$3
	li	$3,0x20000000
	or	$2,$2,$3
	la	$5,D_8019DC34    <- a1 here (late)
	la	$6,D_8019DC3C
	li	$7,0x20
	sh	$16,2($4)
	jal	func_8012D5E4
	sw	$2,88($4)
```
Target:
```
	move	$4,$16
	la	$5,D_8019DC34    <- a1 here (early)
	#APP #NO_APP
	li	$2,-655360
	li	$16,4
	sw	$2,20($4)
	la	$2,D_8019DAFC
	...
```

So I need the a1 la to move from position 31 to position 22 (right after move $4,$16).

In the sched dump, the ready list at T-19 has 45 and 47. In c1, insn 45 = `move $4,$16` and 47 = ? Let me identify. Actually, the scheduler launches 47 before 45 at T-19/T-20. Hmm, but the final order has move $4,$16 first. Let me not worry about the exact mapping.

The point: without the keepalive, sched1 schedules the a1 la late. The keepalive forces it early.

What real C can force it early? The sched1 priority of the a1 la: it's a `la` (lui+addiu) with priority 1 and some ref_count. The scheduler picks insns based on priority and hazards. The a1 la has priority 1 (same as others). The order among equal-priority insns depends on the ready list order and hazards.

Hmm. The keepalive asm (priority 1) creates a dependency: the la must precede the asm, and the asm is scheduled early? Let me look at the orig sched block 3: insn 49 has ref_count 16, and the asm is likely insn 49? In orig, the asm insn is between the la and the li. Let me map orig insns: 45=move $4, 47=la $5,D_8019DC34, 49=asm? The asm's ref_count would be the number of refs to its input... Hmm.

In orig block 3, insn 49 has ref_count 16 — that's high, maybe the `sw $2,20($4)` (store, ref_count high due to the pointer). Hmm.

Let me look at the orig .rtl dump for the insn numbers. Actually, let me look at the lreg dump (post-sched) for orig, which lists the final insns with numbers. Let me find func_80183130 in _d4's .lreg and read the first 30 insns.

Hmm, time. Let me take a step back.

The mechanism is: the keepalive asm uses a1, and sched1 must schedule the la before the asm. The asm itself is scheduled early (it's an empty asm, priority 1, but it has no dependencies except the la). 

Real C alternative: create a real use of a1 that sched1 will schedule early. The only way is to make a1's value needed by an early instruction.

Idea: what if the store `((Unkstruct_800B5CB8 *)a0)->unk14 = v0;` used a1 somehow? No.

Idea: reorder the source so that a1 is assigned and then immediately used in the `v0` computation. E.g.:
```
a1 = (s32)&D_8019DC34;
v0 = 0xFFF60000;
```
The target has a1 then v0. Without the keepalive, sched1 moves a1 down past v0, s0=4, the store, etc. Why? Because a1's la has no early consumer. 

What if I make the source compute a1 as part of the v0 expression? E.g., `v0 = 0xFFF60000; a1 = ...;` — same.

Hmm. What if the a1 address is used in the `or` chain? Like `v0 = ((s32)&D_8019DAFC) | 0x40000000 | 0x20000000;` and a1 is used to... no.

Wait — maybe the target's early a1 comes from the ORIGINAL source using a1 in a real way that the compiler eliminated later. For example, the original might have been:
```
a1 = (s32)&D_8019DC34;
v0 = ...;
...
if (func_8012D5E4(a0, a1, a2, a3) == 1) ...
```
and the compiler's scheduler just happened to keep a1 early in the original build (different compiler version/flags?). The keepalive was added to reproduce it. So there may be no real-C crack.

But the task says to try. Let me try a few more real-C ideas:

1. Make a1 a function parameter or use it in a way that forces early computation.
2. Use the do-while(0) around the la + the next statement (C0535).
3. Move the la assignment to before the func_8012B1B4 call.

Let me test v5 (a1 before the call) and v4 (do-while around a0/a1).

Actually, let me think about sched1's LUID ordering. sched1 schedules the block. For equal-priority insns, the ready list order matters. The ready list is built in reverse order of LUID? The `ready` list is a priority queue sorted by priority, then... Let me look at sched.c's ready list insertion. Actually, the dump shows "ready list at T-19: 45 (1) 47 (1), now 47 45" — so 47 was inserted before 45 in the ready list, and 47 is launched first. The insertion order into the ready list follows the reverse scan (sched1 scans insns backward to build dependencies, then schedules forward). Hmm.

The LUIDs matter. If I change the source order so that the a1 la has an earlier LUID relative to the other insns, sched1 might pick it first.

In c1, the a1 la is at some LUID; in the target (with keepalive), the asm after it gives it a reason to be early.

Hmm. Let me try moving the a1 assignment to before the func_8012B1B4 call. That gives it a much earlier LUID. Let me test v5.

Actually wait — if a1 is assigned before the call, then the la would be scheduled before the call (in the previous block), which is too early. But maybe sched1 sinks it into the current block? The call is a block boundary (call ends a block). So a1 assigned before the call would be in the block before the call, scheduled before the call. The target has it after the call. So v5 would be wrong.

Hmm.

What if I assign a1 right after `a0 = s0;` (current) but ALSO reference it in the `a2` assignment? Like `a2 = (s32)&D_8019DC3C;` — no.

Let me look at the sched1 ready list more carefully. In c1, the a1 la is insn 47 (I think). The order: 45 (move $4,$16) is scheduled LAST (T-20), and 47 (la a1) at T-19. So the final order is 45, 47, 49, ... Wait, that means the la IS early (second)! But the asm shows it late. Contradiction.

Let me re-map. Maybe insn 45 = the store `sw $2,20($4)` and 47 = something else. Let me look at the .rtl dump for c1 to get the insn numbers.

Let me grep the c1 .rtl dump for the function's insns 43-55.
