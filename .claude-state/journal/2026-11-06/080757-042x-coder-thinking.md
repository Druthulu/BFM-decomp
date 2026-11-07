---
ts: 2026-11-06T15:07:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yuDsNBKxUZTjDRyxAhQO
---
Interesting: in b4's sched1 log, insn 476 (set vol from div) has priority 12, and 478 (vol &= 0xFFFF) priority 12. 467/469/472/481/484 all priority 1. So no birth boost visible there... Wait, priority 12 for 476 — that's after adjust_priority? The log line ";; insn[NNN]: priority = X, ref_count" appears at the start. Hmm.

Wait, 476 sets reg 196 (vol) from the div result. reg_n_sets[196] = 2 in b4, so no boost. Yet priority 12 — probably from ref_count/live length, not boost.

Hmm, but the boost sets priority = max_priority (a huge number like 2147483345 seen at line 22148). Let me check which insns get the huge priority in the b4 log (sched1 region lines ~1600-2300). Line 22148 seems to be in sched2 or the final dump. Let me search the sched1 section for 2147483.

Actually, let's compare with orig (the launder version) which matches. In orig, reg_n_sets[vol] = 2 as well (the asm is a set). So b4 should behave like orig for the boost. But b4 differs at the delay slot only — so scheduling is essentially right! The remaining issue is just reorg's delay-slot choice (andi vs sll). Wait, but earlier c1 gave 236 ins (pan first) — that means c1's second set didn't count (maybe cse merged vol's sets or the tree folded). Let me check c1's dump later if needed.

Actually b4 scores 2 with only the delay-slot difference. So b4 is very close! The vol mask works for the boost. Now I need to fix the delay-slot choice.

Idea: make the mask an insn that reorg will not consider, or place it so that the sll is still the nearest eligible insn before the bne. reorg's fill_simple_delay_slots scans from the insn BEFORE the branch backwards? Let me check reorg.c. In `fill_simple_delay_slots`, for each insn it tries `try_merge_delay_insns` / looks at the previous insn. Actually for a simple branch, reorg calls `fill_slots_from_thread` with the branch's target and fall-through.

The andi (478) is before the branch and after the mults. The sll is after the branch. Reorg first tries "fill_simple_delay_slots" which moves an insn from BEFORE the branch into the slot; if it finds the andi eligible, it takes it. If not, it tries the thread copy.

To prevent the andi from being eligible: reorg won't move an insn into a delay slot if the insn's destination is used... conditions: `slots_to_fill` etc. An insn is eligible if it's not a jump, not a call, doesn't reference the branch condition... Also reorg checks `sets_cc0_p` (not MIPS) and whether the insn can be moved (no dependency on the branch). Also it checks if the insn is in the same basic block and if `insn` has a REG_DEAD note etc. There's also the condition that it won't move an insn past a "resource" conflict.

Hmm — in the target (orig with launder), the andi doesn't exist, so the sll gets copied. In b4 the andi exists before the branch.

What if I place the mask AFTER the sll in source? Then the pre-branch insn nearest the branch is the sll — wait, source order would be:
```
sx = (sx + 0xA0) / 0x14;   → mult, ..., set sx
if (sx == 0x10) sx = 0xF;  → bne, li
sx = sx << 8;              → sll
vol = vol & 0xFFFF;        → andi  (AFTER the sll, before the call)
func(...)
```
Now reorg's pre-branch candidate: the sll is right before the branch? No — the branch comes before the sll in program order (the if). Let me get the actual order: 
- sx div (mult, ..., subu a2)
- bne a2, 16
- (delay) 
- li a2, 15
- sll a2, a2, 8
- li a0, 2715
- ...
So the branch is at 588, and insns after it: li a2,15; sll; li a0; ori; or; jal; andi(final).
The andi (my mask) placed after the sll: order = ..., sll, andi, li a0, ori, or, jal.
Reorg's fill_simple_delay_slots looks at insns BEFORE the branch (from the branch backwards): the immediately preceding insn is `subu a2,v1,v0` (the pan result). Would reorg move that into the delay slot? It's needed by the branch (bne a2,v0) — no, it's the operand, can't move past the branch. Then earlier: `sra v1,a2,3`, etc. — moving those before the branch... they're dependencies of the branch operand; reorg won't. So no pre-branch insn eligible (matching target). Then fill_slots_from_thread copies the sll from the fall-through. 

So placing the mask after the sll could give the target exactly! But will the mask then merge with the final `& 0xFFFF`? Let's test. Write:

```
sx = sx << 8;
vol = (vol & 0xFFFF);
func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
Hmm, but combine might simplify. Let's just test (d1).

Another variant: assign vol at the call as c1 but keep the mask in the call (c2 gave score 4 with 237). Let me look at c2's diff later.

Let me test d1.
