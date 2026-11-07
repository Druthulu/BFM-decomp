---
ts: 2026-11-06T17:09:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_16MvcfQONDm1f70cpbPd
---
Pseudo 117 = the 0x8E constant: 2 refs (def at 168, use at 170), 12 insns in lreg (due to hoisting). Priority = floor_log2(2)*2/life. In the flow dump: insns 168→170, life 2 → 2/2 = 1.0. But in lreg (after sched1 hoisting), its live range is 12 insns → 2/12 = 0.17.

Hmm, sched1 hoisted the constant to insn ~5, extending its lreg live range to 12 insns (not 71). And the mask's lreg range is 179 insns → 0.218. So the mask (0.218) > constant (0.17): the mask should win. Yet the constant got t6.

Wait, but both could use t6 at different times. Let me look at the lreg assignment: reg 117 in 14 (t6), mask 87 in 15 (t7). If the mask had higher priority, it should be allocated first and get the lowest free reg. Which regs were free at the mask's allocation? The mask's qty conflicts with many (all the live pointers). The mask's live range (insn 16..195) overlaps nearly everything, so most registers are taken. The lowest free at that point might be t7 if t6 is taken by a *live* pseudo at the mask's birth.

Who's live at the mask's birth (insn 16) and holds t6? The constant 117 is live from insn ~5 to 76 (in lreg terms) — that OVERLAPS the mask's live range! So 117 (t6) and the mask (87) conflict. Priority decides who gets t6: the mask should win (0.218 vs 0.17) and take t6, pushing 117 to t7. But it didn't.

Maybe my priority numbers are off. Let me compute exactly:
- 87 (mask): n_refs=13 (flow says 13 times), size 4, life = death-birth in lreg. The lreg says "used 13 times across 179 insns" — life 179. pri = floor_log2(13)*13*4/179. floor_log2(13)=3. 3*13=39; *4=156; /179 = 0.87.
- 117 (constant): n_refs=2, size 4, life 12 (lreg) → floor_log2(2)=1; 1*2*4=8; /12 = 0.67.

Mask 0.87 > constant 0.67. Mask should be allocated first and get the lower reg (t6). Hmm.

Unless the qty priority uses `qty_n_refs` which sums over tied regs, and the mask is tied with something.

Alternatively, the allocation order is not global over the block: local_alloc processes quantities in `qty_order` sorted by priority, but the *register choice* is by find_free_reg with `qty_min_class` and preferences. The mask's qty might have a *copy preference* or a suggested hard reg? No.

Wait — maybe the mask's priority is lower because its death-birth is computed differently. In the lreg dump, "Register 87 used 13 times across 179 insns" — but lreg's qty_death-birth might be based on insn UIDs (not counts). The UID difference could be much larger than the insn count (UIDs increment per insn, so same).

Hmm, let me look at the actual order in the lreg dump's disposition comment:
```
;; Register 117 in 14.
;; Register 87 in 15.
...
```
The comment list is in allocation order! Let me look at the full list around 87/117.
