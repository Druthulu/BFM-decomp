---
ts: 2026-11-06T15:10:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_M2SSIvgug2xEGByi4ZdM
---
So fill_simple_delay_slots first scans BACKWARD for a candidate. The andi is a candidate unless a resource conflict: `insn_sets_resource_p (trial, &needed, 1)` — needed is the branch's referenced resources. The branch references the condition registers (a2, v0). The andi sets a1 → no conflict. So it's eligible.

Then after the backward scan, `fill_slots_from_thread` for the fall-through.

To make the andi not eligible for the delay slot, we need `insn_sets_resource_p (trial, &needed, 1)` — i.e., the andi must set a register the branch needs. Not possible (vol/a1 isn't the branch condition).

OR: put a LABEL between the andi and the branch! `stop_search_p` stops at a label. If a label sits between the andi and the branch, the backward scan stops before reaching the andi. How to introduce a label between? A control-flow construct: e.g., an `if` before the sx computation creates a branch+label. 

Idea: put the vol mask inside a construct that creates a label right after it, before the sx computation. For example:

```
vol = ((0xA0-av)*0x7F)/0xA0;
if (vol >= 0) vol = vol & 0xFFFF;   // creates a branch; the fall-through has the andi
sx = (sx + 0xA0)/0x14;
...
```
That adds a branch — expensive.

Simpler: `if (vol < 0) vol = 0;`? Adds a branch.

Hmm, what about placing the mask *inside* the existing `if (sx < 0)` structure? The `if (sx<0) av = -sx;` compiles to bgez + negu, with a label after. If I put `vol = vol & 0xFFFF;` in the fall-through right after that if (i.e., at the launder position), the label is before it, not after. The backward scan from the bne would hit the andi before any label (the label is before the andi). So still eligible.

What if the mask is placed INSIDE the `if (sx < 0)` block, before `av = -sx;`? Then the andi is in the branch's fall-through/taken block; the bne (sx==0x10) scan backwards: from the bne, backwards: sx div chain..., then a LABEL (end of the if), so the scan stops before reaching the andi inside the if block. But the andi would only execute when sx<0 — semantically, masking vol before it's set is meaningless but it's a real set of vol (reg_n_sets=2) as long as flow keeps it. vol isn't live there; flow would delete the dead store! Unless vol is used later — a store to a non-live variable is dead. flow's dead store elimination removes it.

Unless the mask is on a value that IS live: e.g. compute vol's real value there? No.

Hmm, wait. Let me reconsider. Actually, maybe I can put the second set in the `if (sx < 0)` block using the actual vol computation. What if the vol computation itself is moved inside a construct? No.

Alternative: use a label-creating construct around the mask that costs zero: a `do { } while (0)`? No labels.

What about `switch`? Costs a jump table.

Hmm, what about the natural structure: the mask could be placed *after* the bne (in the fall-through), where it merges with... 

New idea: make the second set of vol be the existing `li a0,2715` (0xA9B) argument — i.e., reuse vol as the constant holder? `vol = 0xA9B;` then pass vol. But vol is needed for the or. No.

Another idea: the second set could be on a DIFFERENT pseudo if the birth boost target is different. Let me actually determine which insn gets the max_priority boost. Compare orig's sched dump vs no-launder's. Let me find the "priority = 2147483xxx" lines in the sched1 region for both.

Let me first check the b4 dump (which I have but suspect is actually b4 — it showed the andi at 478, consistent with b4). And dump the no-launder version (a0) to compare.

Actually, better: grep b4's sched log for 2147483.
