---
ts: 2026-11-06T08:34:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_inZ7AyhyzwD2L78ZQygM
---
Only cand.o. Where does the target come from? Probably from `build/asm/` or the reference object of the *original* build (a "target object" per bank). Let me grep delever_search.py for how it loads target — a short grep of a tool source is fine (not a doc). Actually rule: "An expert learns a tool from the card's Tools table and <tool> --help, never from its source" — that's for experts. As a coder, I can grep. But maybe simpler: use objdump on cand.o and compare with the diff. The target instructions I need are already shown in the diff for the mismatched region, and for the rest mine == target. So I know the target fully: it's mine with those two changes. Mine (c1) has at 28 beqz with nop delay; target has addiu in the beqz delay slot and no addiu at 34.

Wait, that's odd: the target puts `addiu a0,sp,24` in the *delay slot of beqz v0* at 28. And then at 33 `bnez v0` with what in its delay slot? Mine at 34 has the addiu (in bnez's delay slot). Target at 33 bnez then insn 34 = next (target has 57 insns, mine 58; target[34] would be mine[35]). So the target's bnez delay slot is filled by mine[35] (the same insn that follows in mine). Let me see mine[35] — need the listing. The diff only shows mismatched regions. Let me objdump cand.o around the function.

Actually, easier: since target = mine minus one addiu and with the addiu moved, the target's beqz delay slot contains the addiu. In GCC, a branch delay slot is filled by reorg from an insn that would execute regardless; here the addiu a0 is placed in beqz's delay slot. For that, the compiler must have emitted the addiu *before* the beqz (then reorg moved it into the slot? no, reorg fills slots with preceding insns or following ones depending). GCC 2.7.2 reorg fills delay slots with the next instruction if safe, else previous. Placing addiu after beqz suggests it's the next insn in the schedule and safe to move into the slot.

For mine, the addiu is after bnez (in its delay slot). So the difference: in target's schedule, the addiu comes right after the first beqz; in mine, right after the second bnez.

This is scheduling of a live range: the a0 value is born after the first branch in target, after the second in mine. To birth it earlier, we need its first use to be earlier — the only use is the call. Hmm.

Unless... in target, the address is born from an instruction *before* the beqz? Actually the insn at 28 is beqz; at 29 addiu (delay slot). The addiu is executed before the branch target is taken. So effectively a0 is set before the bnez at 33. So yes, the value is born between the two branches.

In GCC, what makes a value born between two branches? If the address computation is an insn scheduled there by sched1 or placed by reorg. In mine, sched1 put it after the bnez. Why would the target have it earlier? Perhaps the original source had the address in a variable assigned in the outer block before the inner if, and gcc 2.7.2 (with -O2 and no scheduler for this TU?) emitted the addiu right after the first beqz because of... Actually gcc 2.7.2's default scheduler is on.

Alternatively, maybe the target body had `func_8012C51C(sp18, param_1)` where sp18's address computation was CSE'd with something... 

Hmm, what if instead of a0pin we make the call's first argument be a *different* expression: e.g. `(void *)&sp18[0]`? Same.

What about making the inner if condition use the address: `if (D_801270CC == 0)` → the address could be computed for the condition? No.

Another real-C idea: declare a pointer that is used to store the array elements, and *initialize the array through the pointer before the branch*? Not in target.

Wait — maybe the answer is simpler: the target computes `addiu a0,sp,24` early because the source's `func_8012C51C(a0pin, param_1)` had its *second* argument as something requiring a0? No.

Let me reconsider: maybe in the target the `addiu a0,sp,24` is not the call arg but the *frame pointer* for the stores, and the call uses a different register? No — the call arg must be in a0.

Let's look at the actual insns around: dump cand.o.
