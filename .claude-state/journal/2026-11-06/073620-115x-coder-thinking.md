---
ts: 2026-11-06T14:36:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dhOX2PNYUA6y5jLjzmGF
---
Hmm, the sched2 dump for block 3 has the same structure. But the .s shows a1 late. Let me look at the full block 3 sched2 to see the order and identify insn 47.

Actually, let me reconsider: maybe the .s is generated with a different insn order because the .s I read is from _dc1 (c1 scratch TU), but the score is computed by delever_search which compiles the ORIGINAL TU with the body substituted — a slightly different TU (same body). The scratch TU should be identical.

Hmm wait, maybe the issue: cc1_dumps_tu compiles the TU with the c1 body, and the .s in _dc1 is that compile. The score (dt.sh) compiles via delever_search with the same body. They should match. And the diff said a1 is late in "mine". So the .s should show a1 late. But the sched dumps suggest a1 early.

Let me just re-read the .s more carefully. Maybe I misidentified which la is a1. `la $5,D_8019DC34` sets $5 = a1. In the .s, there are two `la $5`: one for D_8019DC18 (the func_8012B1B4 arg) and one for D_8019DC34. Let me re-read the c1.s around the call.

From my earlier read of c1.s:
```
	la	$5,D_8019DC18
	jal	func_8012B1B4
	move	$4,$16
	move	$4,$16
	li	$2,-655360
	li	$16,4
	sw	$2,20($4)
	la	$2,D_8019DAFC
	...
	la	$5,D_8019DC34
	la	$6,D_8019DC3C
```
So a1 (la $5,D_8019DC34) is at the late position. But the sched dump says insn 47 (a1) is scheduled second. 

OH WAIT. Maybe the sched dump's "launching" order is the reverse: T-20 is the LAST cycle, and T-1 is the first. So the emission order is T-1 first (105), T-2 (104), ..., T-20 (45). That means 105 is emitted FIRST and 45 LAST. That would put a1 (47) near the END (second-to-last). That matches the .s (a1 late)! 

Yes: the scheduler works backwards (schedules the last insn first at T-1), and the final order is T-20...T-1 reversed? Hmm, let me think again. In a backward list scheduler, T-1 is the last time slot. The insn at T-1 executes LAST. So the emission order (first to last) is T-20, T-19, ..., T-1. That gives 45, 47, ..., 105. So a1 (47) second. Contradiction with .s.

Alternatively, T-1 is the FIRST slot. Then 105 first, 104 second, ... 45 last. That gives a1 (47) near the end. Matches .s!

But "ready list at T-1: 105" with 105 being a jump/branch — the branch should be last, not first. Hmm.

Wait, block 3 ends at insn 105 which is the jump at the end of the `if` body? Actually the block ends at 105 (the branch to $L893). In the .s, the last insns of the block are `jal func_8002D4C8; move $5,$0` then `$L893:`. Hmm, insn 105 might be the `j $L893`? Let me look at the .s: after `jal func_8002D4C8; move $5,$0`, there's `$L893:`. So the block's last insn is the delay-slot move or the call. The jump to L893 might be implicit (fall-through).

Hmm, I'm confusing myself. Let me directly compare: the .s order is the ground truth. a1 is late in c1, early in orig (target). The sched dump's numbers: in c1 block 3, insn 47 = a1. In orig block 3, insn 47 = a1 too? Let me check orig's .rtl.

The difference between orig and c1 block 3: orig has 2 more insns (the asm). Orig block 3: 43-107; c1: 43-105. So the asm insn is at 49 or 50 (orig), and everything after shifts by 2.

In orig's sched dump, block 3 insn list: 45,47,49,52,55,57,60,63,66,69,72,74,77,79,88,91,96,98,100,102,106,107. In c1: 45,47,49,52,58,61,64,67,70,72,75,77,86,89,94,96,98,100,104,105.

Hmm, orig has 55,57,60,63,66,69,72,74; c1 has 58,61,64,67,70,72,75. So orig's insn numbers are shifted +2 relative to c1 after insn 52 (because the asm is 2 insns? no, an asm is 1 insn but the la might expand...). Actually the asm insn is 1 insn; why +2? Maybe the asm expands to 2 insns (the #APP/#NO_APP are comments, but the asm_operands might be 1 insn). Hmm.

This is too deep. Let me just compare the final .s orders and try real-C variants empirically.

The target order: a1 early (position 22).
c1 order: a1 late (position 31).

The keepalive forces a1 early. Real C ideas tested so far: v1 (do-while around a1), v2 (a1 before a0), v3 (a1=a1), all 4.

Let me try:
- v4: do-while(0) around `a0 = s0; a1 = ...;`
- v5: a1 assigned before the func_8012B1B4 call.
- v6: use a1 in the store address? no.
- v7: declare a1 as a parameter? no.

Hmm, let me think about sched1's priority. The la (insn 47) has priority 1. In orig, the asm (priority 1) is after it. The scheduler in orig places the la early because... hmm.

Actually, maybe the effect is on sched2 (post-reload). Let me check: in c1, the reload might change the la. The keepalive (an asm with a register operand) forces a1 to be in a register at that point, affecting reload. Without it, reload might rematerialize the address late.

Wait — the `la` is a pseudo-instruction that expands to lui+addiu. In c1, it's late. The keepalive's `"r"(a1)` forces a1 to be a register value at the asm point. In reload, the address `&D_8019DC34` might be rematerialized. 

Hmm. Let me look at whether the ORDER difference is from sched1 or sched2. Let me check the .sched2 dump's final order vs the .s. Actually, the .s is the definitive output. The .sched2 dump should reflect the final schedule. Let me look at the sched2 block 3 order and see if a1 (47) is early or late.

In the sched2 dump block 3, the ready list at T-4 includes 86,89,94,96,98. At T-5 includes 77. This looks similar to sched1. Let me read the full sched2 block 3 to see the order.

Hmm, I'm spending too long. Let me try a batch of real-C variants and see if any scores 0. If not, I'll record a WALL (this is a known hard class: ORDER from a keepalive).

Actually, wait. Let me reconsider the problem. The keepalive is `__asm__ __volatile__("" :: "r"(a1));`. It's `volatile`, which might act as a barrier preventing reordering. Without it, sched1/sched2 moves the la.

What if I replace it with a real use of a1 that's already in the code? The `v0` computation and the stores... 

Hmm, what if I use a1 as the destination of the first store? `((Unkstruct_800B5CB8 *)a0)->unk14 = v0;` — no.

What if a1 is used in the `if (func_8012D5E4(...) == 1)` — it is (as an arg). But that's the call, which is later.

What if I add a real use of a1 in the `a2 = (s32)&D_8019DC3C;` statement? Like `a2 = (s32)&D_8019DC3C + (a1 - a1);`? folds.

What if `a2 = (s32)&D_8019DC3C; a2 = a2;`? identity.

Hmm.

Let me try moving the a1 assignment to right after `s0 = 4;` or interleaving. The target order is: move a0; la a1; li v0; li s0; sw; la v0; ... So a1 is right after a0. If I put the a1 assignment right after a0 in the source (it is), sched1 moves it.

What if I put the a1 assignment BEFORE `v0 = 0xFFF60000;` and also make `v0 = 0xFFF60000` depend on a1? Like `v0 = 0xFFF60000 | (a1 & 0);`? folds.

Hmm. What if I write the store `((Unkstruct_800B5CB8 *)a0)->unk14 = v0;` as `*(s32 *)(a1 + (a0->unk14_offset - a1))`? absurd.

Let me try a different tack: maybe the la can be forced early by making a1 a VOLATILE variable? `volatile s32 a1;` — that would prevent some optimizations and force the store/load. But it would add loads/stores. Bad.

What about making a1 `register s32 a1 __asm__("$5")`? That's a pin (a lever of another kind, not allowed to ADD). But the constraint says "levers of other kinds the def already had may stay, never added". So I can't add a pin.

Hmm.

OK, let me look at the actual sched2 dump to determine the mechanism, then decide. Let me read the sched2 block 3 order and compare orig vs c1.

Actually, let me reconsider the time budget: ~15 min on this item. Let me try 3-4 more variants and then decide WALL vs continue.

Variants:
- v4: do-while(0) around a0/a1 assignments.
- v5: a1 assignment before the func_8012B1B4 call.
- v6: reorder: `a0 = s0; v0 = 0xFFF60000; a1 = ...;` (a1 after v0).
- v7: `a1 = (s32)&D_8019DC34;` moved after `s0 = 4;`.
- v8: use a1 in the `v0 = v0 | v1` chain via a real op that folds? no.

Let me test v4, v5, v6, v7.

Actually, wait. Let me reconsider what the target's early la means. Maybe the target's early la is NOT a1 but something else. Let me check the target .s: `move $4,$16; la $5,D_8019DC34; #APP #NO_APP`. $5 = a1. And #APP/#NO_APP is the asm. So yes, the asm is right after the la, forcing the la early.

The asm is empty and volatile. In sched1, the asm has priority 1 and is a use of a1. The scheduler must schedule the la before the asm. Since the asm is scheduled early (why?), the la is early.

Why is the asm scheduled early? Its priority is 1. Hmm. In the sched dump, the asm insn has ref_count... Let me identify the asm in orig's sched dump. The asm is an insn with priority 1 and ref_count maybe 0 or 1.

Actually, the scheduler's order among priority-1 insns is determined by the ready list (which is a queue). The asm might be early because it has no dependencies and is near the front.

Hmm, real C can't easily replicate an empty asm's scheduling.

Let me just try the variants and see. If none works, record a WALL with the evidence.

Let me batch v4-v7.
