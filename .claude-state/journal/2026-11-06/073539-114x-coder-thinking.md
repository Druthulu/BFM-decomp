---
ts: 2026-11-06T14:35:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tWxwjUycrWNNg7R1Av8g
---
In c1's .rtl (pre-sched):
- insn 43: something (reg 86)
- insn 45: `(set (reg:SI 4 a0) ...)` — a0 = s0 (move $4,$16)
- insn 47: `(set (reg:SI 5 a1) ...)` — a1 = &D_8019DC34 (the la)
- insn 49: something
- insn 52: `(set (reg/v:SI 4 a0) ...)` — hmm, a0 again?
- insn 55: reg 77
- insn 58: reg 74

Wait, the .rtl dump is BEFORE sched1? The .rtl dump is dumped after expand/jump? Let me check: toplev dumps .rtl at some point. The insn numbers here (43,45,47) match the .sched dump's block 3 start (43). So the .sched dump uses these numbers.

So in c1, insn 45 = a0 = s0, insn 47 = a1 = la. In the sched dump, the order is 45 then 47 (both at T-20/T-19). So the a1 la IS scheduled early (second)! But the final asm shows it late. 

Wait, the sched dump's final order: T-20=45, T-19=47, T-18=49, T-17=52, ... So the emitted order is 45, 47, 49, 52... which means a1 is second! But the asm shows a1 at position 31. Contradiction!

Unless the .s output is from a DIFFERENT schedule. Hmm, wait — maybe the .s I read (c1.s) is correct and the sched dump order is reversed. Let me re-read: "ready list at T-19: 45 (1) 47 (1), now 47 45" — the ready list AFTER is "47 45". Then "ready list at T-20: 45 (1), now 45". So at T-19, the launched insn is 47 (head of "now 47 45")? And at T-20, 45. 

The scheduler emits insns from T-1 backwards? Or T-1 is the last cycle? "total time = 20". The insns are emitted in the order they're launched: T-1, T-2, ..., T-20? Or T-20 down to T-1?

Looking at the dump: at T-1, insn 105 is launched (the last insn of the block, a branch/jump). At T-2, 104. So the emission order is T-1 first (105), then 104, ... down to T-20 (45). That means the final order is 45 (T-20, emitted last?) No...

Actually, the scheduler works backwards: it computes the schedule from the end. "launching 16 before 18" etc. The final emitted sequence is the reverse of the launch order? Let me think: at T-1, the last insn of the block (105) is placed at the end. At T-2, 104 is placed before it. So the emitted order is: T-20, T-19, ..., T-1 = 45, 47, 49, ..., 105. So a1 (47) IS second. 

But the .s shows a1 at position 31 (after the or's). Hmm. Unless the .s was generated from a different compile. Wait — I dumped c1 with cc1_dumps_tu on the scratch TU. The .s in _dc1 is the final assembly. Let me check if _dc1/dumps_c1/c1.s has a1 early or late.

I read c1.s from _dc1 earlier: it showed `la $5,D_8019DC34` at the late position. Hmm, but that contradicts the sched dump.

Wait, maybe the .s output in _dc1 is from the LAST compile in cc1_dumps_tu, which uses the same TU. The sched dump is from the same compile. So they should agree.

Unless the sched1 dump shows the schedule but sched2 (post-reload) reorders it! sched2 runs after reload and could move the la. The .s is after sched2. Let me check sched2's dump.

Hmm, but sched1's schedule should be the input to reload/sched2. If sched1 puts a1 early, sched2 might move it late. Let me check the .sched2 dump.

Actually wait, maybe I misread the .s. Let me re-read c1.s around the a1 la. From my earlier read:
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
	la	$5,D_8019DC34
	la	$6,D_8019DC3C
```
So a1 is at position 31. But sched1 says 47 (a1) is second. So sched2 moved it. Let me check the .sched2 dump.

Hmm, if sched2 moves it, then the keepalive's effect might be on sched2, not sched1. Or sched1's schedule is changed by reload.

Actually, maybe the .sched dump I'm reading is sched1, and the .s is after sched2. Let me check the .sched2 dump for the block.

Actually, wait. Let me reconsider the sched dump emission order. Maybe T-1 is the FIRST cycle (not the last). Let me re-read the dump structure:
```
;; ready list at T-1: 105 (7fffffa5), now 105
;; ready list at T-2: 104 (7f000001), now 104
```
"ready list at T-1" — the ready list BEFORE launching at time T-1. Hmm. The scheduler's `schedule_block` processes insns and assigns them to cycles. The dump might print from the last cycle backward. 

The line "launching 16 before 18 with 1 stalls at T-2" in block 0. And block 0 has insns 4-18. Hmm.

Let me just check the .sched2 dump. If sched2 moved the la, the fix must target sched2.

Actually, let me check: the .dbr (delayed branch) dump or the .sched2 dump. Let me look at the .sched2 dump for func_80183130.
