---
ts: 2026-11-06T11:02:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dShuPX6AsMKod5Ku5wQC
---
The struct alias fixed the memory-barrier issue (the D_801151D0 store is now in the right place). Score 5, 143 ins.

Remaining: the two RC-12 delay-slot copies:
- position 60: nop vs li v0,3 (outer else cross-jump copy)
- positions 83-84: missing `addiu v0,s1,1` (the loop's delay slot copy — lever 5's `__asm__("")` job)

So issue 1: the outer else `n = 3` copy. Issue 2: the loop's `beqz` delay slot with `addiu v0,s1,1` (lever 5: the asm fence stopped reorg's fill_simple_delay_slots forward scan, so the slot was filled from the branch target instead).

Let me tackle issue 2 (lever 5) first: the `__asm__("")` at the head of the loop's if-body. Real-C replacement: the do-while trick (C0535's second use replaced a scheduling barrier). But this is a reorg delay-slot fill, not sched1. The comment: "reorg.c stop_search_p halts fill_simple_delay_slots' forward scan on an asm insn, so the beqz slot is filled from the branch TARGET instead — the duplicated addiu v0,s1,1".

A real-C way to make the branch target the fill source... Hmm.

The target code: `beqz v0, ff8; addiu v0,s1,1` — the delay slot is the branch target's first insn (copied). Wait, "filled from the branch TARGET instead — the duplicated `addiu $v0,$s1,1` the target has in both the delay slot and after the call".

So the target has `addiu v0,s1,1` in the delay slot AND after the call. Hmm, reorg copies an insn from the target into the delay slot.

Real-C ways to influence reorg's fill: the shape of the branch's arms. The if-body is `if (D_80115158[i].h != 0) { ot = call(...); }` then `i++; w++;`.

Hmm, the comment says the asm fence stops the forward scan so the slot is filled from the target. Without the fence, the slot is filled from the fall-through (an insn that belongs to the branch target... no).

This is the "dbr-delay-fill" wall class: "delayed-branch fill takes a fall-through insn the target leaves out of the slot (G18x)".

Given the time, let me try the do-while variants for lever 5 and a couple of n=3 variants. If nothing, record a wall.

Let me first try the n=3 issue since it's simpler: variants B (restructure), D (variable), F (s16 n).

Actually, let me reconsider issue 1 more concretely. Target:
```
f78 li v0,3
f7c bne v1,v0,fb4      # outer: if (D_80115126 != 3) goto else(n=3)
f80 li v0,3            # delay slot: the outer else's n=3, copied
```
So the branch target fb4 is the else's `n = 3`? Let me look at fb4 in the target.
