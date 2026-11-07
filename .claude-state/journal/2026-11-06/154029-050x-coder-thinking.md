---
ts: 2026-11-06T22:40:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_s0KyFZ6oRscS2u8Fo2bl
---
The RTL order differs: in w0, insn 16 (lw pointer) comes later (after 43, 35...) while in w6 insn 16 is early (right after the loop note). So the scheduling (sched1) differs.

Interesting: in w0, the order is: insn 25 (lh 14), 29, 43, 35... and insn 16 (lw) is elsewhere. In w6: 16 (lw), 20 (lh s1ang), 25, 29...

The difference is because of the loop note: `(note 59 56 25 "" NOTE_INSN_LOOP_CONT)` in w0 → next insn 25; in w6 → next insn 16.

Hmm, so sched1 (before local-alloc) ordered them. The source difference (mask-in-place) changed the dependencies slightly? In w0, the s1ang def is `s1ang = load` and `u6 = s1ang & 0xFFF` (a separate def). In w6, `s1ang = load` and `s1ang = s1ang & 0xFFF`. Both depend on the load.

Hmm, but sched1 runs before local-alloc; the RTL it sees is the same except for the mask-in-place's def target. The scheduling priority might differ.

This is a rabbit hole. Let me think about whether there's a formulation where s1ang is global but the schedule stays like w0.

Key: w0's schedule is the target's. The difference in w6 is caused by... hmm, actually wait: in w0, the s1ang load is `lh $16,18($2)` at insn 20, and the pointer lw at insn 16 is scheduled LATER (after 35). In w6, the lw is scheduled FIRST.

Hmm, why? In w0, the pointer (r81) is tied with r72 (arg0) via the lw, so the lw must be after the lh uses. But that's local-alloc, after sched1. sched1's order is what we see in the RTL... 

Wait, the lreg dump is AFTER local-alloc but the insn ORDER was set by sched1. So sched1 ordered w0's insns as 25,29,43,35,...,16 and w6's as 16,20,25,... The source difference changed sched1's ordering. Odd but plausible: the mask-in-place changes the data dependencies of the s1ang chain.

Hmm, in w0 the s1ang load (insn 20) is scheduled... let me see w0's full order. The grep only showed 25 insns. Let me get the full order for both.

Actually, let me try a different globalisation that keeps `u6` as a separate def. Idea: reassign s1ang AFTER u6:
```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
iVar4 = u5 - u6;
s1ang = s1ang & 0xFFF;   // globalise: reassign s1ang, then use it in the arms
if (iVar4 > 0x800) { t = s1ang + 0x1000; ... }
```
The second `s1ang = s1ang & 0xFFF` is in block 2 (after the return). cse2 might merge it with u6 → `s1ang = u6` (copy). Then s1ang is used in the arms (blocks 3,5) → global. The copy is coalesced by global-alloc. So s1ang becomes a global pseudo with refs in block 2+ and the load... hmm, but the *load* value (s1ang raw) is used in block 0 (u6 = s1ang & 0xFFF) and in block 2 (s1ang = s1ang & 0xFFF, merged to copy u6). So s1ang raw is referenced in blocks 0 and 2 → global! And the copy `s1ang = u6` is coalesced away.

Wait, if cse2 merges `s1ang = s1ang & 0xFFF` into `s1ang = u6`, then the use of s1ang raw in block 2 is gone; but s1ang (the variable) is reassigned in block 2 and used in the arms. The pseudo for the load (raw) is used only in block 0 (u6). The reassigned s1ang is a different pseudo. So the raw load pseudo is still local!

Hmm. Unless the reassignment is `s1ang = s1ang & 0xFFF` NOT merged (different block, cse2 might merge though).

Let me think again: we want the LOAD pseudo (the one crossing the call) to be global. The load pseudo is used by the mask. If the mask is computed in block 0 (for the compare), the load pseudo is local. If we ALSO use the load pseudo in another block, it becomes global.

So: use s1ang (raw) in a later block. The only semantically valid use is `& 0xFFF`. So we need a second mask computation in a later block. That's an extra andi unless cse merges it (which would kill the globalisation).

BUT: what if the second mask is in a block where cse2 does NOT merge (multiple preds), and the extra andi is *combined* into an existing instruction? Hmm.

Alternatively, what if the second use of s1ang raw is in the *compare* (block 0) and the first is... no.

Hmm, what if the mask is computed in a later block and the compare uses the raw s1ang in block 0? The compare is `u6 == u5` where u6 = s1ang & 0xFFF. Can't use raw.

What if we change the comparison: `if ((s1ang & 0xFFF) == u5) return 0;` and then `u6 = s1ang & 0xFFF;` — cse merges.

OK, what if we exploit the mask-in-place (w6) but fix the scheduling by keeping the pointer load's REG_EQUIV from forming? The w6 issue is that the `lw` got a REG_EQUIV note and r72 stayed live.

Hmm, actually, let me look again: in w6, the lw is scheduled FIRST (insn 16 before the lh uses), so r72 is live after it. In w0, the lw is scheduled AFTER the lh uses. The scheduler's choice depends on the insn priorities. In w6, the mask-in-place made the s1ang chain shorter (one less pseudo?), changing the priorities.

What if I add the mask-in-place but keep `u6` for the compare (so the dependency graph resembles w0)? E.g.:
```
u6 = s1ang & 0xFFF;         // block 0, compare
if (u6 == u5) return 0;
iVar4 = u5 - u6;
s1ang = s1ang & 0xFFF;      // reassign for the arms (globalises the load)
if (iVar4 > 0x800) { t = s1ang + 0x1000; ... }
```
Here the load pseudo is used in block 0 (u6) and block 2 (s1ang = s1ang & 0xFFF). If cse2 merges the second mask to `s1ang = u6`, the load pseudo is only used in block 0 → local. Hmm.

But wait: cse2 runs before local-alloc. If cse2 merges, no globalisation. If it doesn't (different block), the load pseudo is global but there's an extra andi.

Ugh.

Let me reconsider. Maybe the cleanest: use the mask-in-place (w6) and fix the schedule. The w6 schedule issue might be fixable with a do-while or statement reorder.

Actually, hold on. Let me look at w6's diff more carefully. Score 38, 74 ins (one less than target). The missing instruction is `move $2,$4`. Everything else is a register/order difference. Let me get the full diff of w6 to see exactly.
