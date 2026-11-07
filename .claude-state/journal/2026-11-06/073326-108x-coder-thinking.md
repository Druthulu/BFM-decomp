---
ts: 2026-11-06T14:33:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1DhJJLF77EniX461xnUP
---
All still 4. Let me check if v1's order changed at all. Let me diff one. Actually, all score 4, so no.

Let me look at the sched1 dump to understand why the la sinks. Let me look at the .sched dump for func_80183130 in c1 vs orig. The sched1 dump shows the scheduling decisions. But c1's dump isn't available; I only dumped orig (score 0). Let me dump c1's TU via a scratch copy... Actually, cc1_dumps_tu can dump a --try candidate? No, it needs a TU file. Let me create a scratch TU copy for ov_SC04_004 with c1's body, like before.

Hmm, this is getting time-consuming. Let me think about the mechanism differently.

The keepalive `__asm__ __volatile__("" :: "r"(a1))` makes a1 an input to an asm. In sched1, the asm has priority 1 (per C0414 §3). But the asm creates a "use" of a1 at that point, which forces the la to be scheduled before the asm (dependency). Without the asm, the la can be sunk to the call.

Real C: I need a real use of a1 between `a1 = ...` and the call, at position 22. What real operation could use a1 there? 

Hmm, what if the target's `la $5,D_8019DC34` isn't a1 at all? Let me check: `la $5,D_8019DC34` sets $5 = a1. Yes, a1 is the 2nd arg ($5).

What if I write the call argument as `(s32)&D_8019DC34` directly instead of via a1? Then the la would be at the call. No.

What if a1 is used in the store `((Unkstruct_800B5CB8 *)a0)->unk14 = v0;`? No.

Hmm, what if the address is computed as part of a real expression that the target already has? The target's early code: `la $5,D_8019DC34` then `li $2,-655360` etc. Nothing uses a1.

So the target has a genuine "dead" early computation of a1 (it's used only at the call). The original source must have had a use of a1 early. What use? Maybe the original called func_8012B1B4 with a1 as an argument? No, func_8012B1B4(s0, &D_8019DC18) uses &D_8019DC18 ($5).

Wait — maybe the original source had `a1 = (s32)&D_8019DC34;` BEFORE the func_8012B1B4 call, and the call used a1? No.

Hmm, let me look at the target asm again:
```
	la	$5,D_8019DC18
	jal	func_8012B1B4
	move	$4,$16
	move	$4,$16
	la	$5,D_8019DC34
 #APP
 #NO_APP
```
The `la $5,D_8019DC18` is the arg to func_8012B1B4. Then after the call, `move $4,$16; la $5,D_8019DC34`. So a0 and a1 are set up for the later call.

The `#APP #NO_APP` is the keepalive. Without it, sched1 sinks `la $5,D_8019DC34`.

Real-C idea: what if the source assigns a1 and then uses it in the `a2`/`a3` setup? Like `a2 = (s32)&D_8019DC3C;` — no.

Hmm. Let me look at the ORIGINAL source (before the keepalive was added). Maybe the keepalive was added to fix this exact ORDER issue, and there's a real-C form. Let me look at git history? No git allowed for commits, but I can look at the file's history? The task says no git. Let me not.

Let me think about the do-while(0) trick more carefully. The C0535 mechanism: the do-while(0) splits cse1's EBB so sched1 keeps birth order. My v1 wrapped the assignment in do-while(0), but the la still sank. Maybe the do-while(0) needs to be around the assignment AND the following statement, or the split needs to be at a different place.

Actually, maybe the issue is cse1: cse1 might be CSEing the `&D_8019DC34` address with something? No.

Let me look at the sched1 dump. Let me create a scratch TU with c1's body and dump, then compare the .sched for the function. The sched dump shows the ready list and priorities. That will tell me why the la sinks.

Let me set up the scratch TU for ov_SC04_004. Let me check its includes.

Actually, the TU is src/ov_SC04_004/ov_SC04_004_jr_8017AE2C.c. It includes "common.h" and "../shared/..."? Let me check. For cc1_dumps_tu on the real TU, it works. For a scratch copy, I need the include dir trick. But actually, I can use cc1_dumps_tu directly on the real TU only (which has orig, score 0). For c1, I need a scratch. 

Alternative: use the --try --keep scratch object and then... no, I need the TU.

Hmm. Let me instead look at the .sched dump of the ORIG (score 0) to see how the keepalive pins the la, then reason.

Actually, let me look at the .rtl/.sched dump for the function in the orig dump (_d4). Let me find the function in .sched.

Actually, let me first check: maybe there's a simpler real-C change. The la sinks because sched1 sees no benefit in hoisting it. sched1's priority for the la insn depends on its "birth" (the earliest it can be) and the dependency chain. The keepalive asm adds a use right after, making the la's "death" early, which raises its priority (shorter live range -> higher priority) and pins it.

Real C: add a real use of a1 right after the assignment that has the same effect. What if `a1 = (s32)&D_8019DC34;` is followed by a comparison or a store using a1? That would emit code.

Hmm. What if I use a1 in the `v0 = v0 | v1` chain? Like `v0 = v0 | v1 | (a1 & 0);`? folds.

What if the address computation is expressed via a global array access that cse keeps? E.g., `a1 = (s32)&D_8019DC34;` then `v0 = (s32)&D_8019DAFC;` — both are `la` computations. The target has a1's la early and v0's la later. Hmm.

Wait — actually, let me reconsider. Maybe the target's early `la $5,D_8019DC34` is NOT a1 but a leftover from the keepalive's operand handling? No, the asm is empty; the la is a real computation.

Let me look at the .sched dump. Let me find the function in the orig .sched dump.
