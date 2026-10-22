---
ts: 2026-10-22T06:48:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_d3ZxDUKG1GPj8tDM58gL
---
So in the cand's post-sched RTL (this is the RTL after sched1? or the input?), the order is:
- insn 18: set a0 = 16  (the `li a0,16`)
- insn 15: set s0 = a2  (move s0,a2)
- insn 20: call

Note "(insn 18 52 15 ...)": the format is (insn uid prev next). So insn 18's next is 15. So the final order is 18 then 15 then 20. That's the CANDIDATE order: li a0,16 then move s0,a2. ✓ matches the disassembly.

Now the tree: let's look at the same region in tree.i.sched. Expect: insn X: set s0 = a2, then set a0 = 16.

Also note "(reg/v:SI 16 s0)" — the /v flag means it's a pseudo that got allocated? "reg/v" means the reg is a pseudo that has been assigned a hard reg in this dump? In gcc dumps, "reg/v" indicates a pseudo that has been given a hard register (v = "virtual" with regno?). Hmm, reg/v:SI 16 s0 = pseudo 16? Actually in RTL dumps, a pseudo is printed as "(reg:SI 16)" where 16 is the pseudo number, and if it has been allocated, gcc prints "(reg/v:SI 16 s0)"? Hmm, but 16 = $16 = s0 coincidence?

Actually in gcc's RTL dump, pseudo registers are printed as `(reg:SI 5)` etc. and after allocation "reg/v" indicates a virtual register that's been assigned. The number after reg/v is the pseudo number, and "s0" is the hard reg it's been allocated to. So pseudo 16 → s0. And the tree's insn 15's set has "reg/v:SI 16 s0" too? Let's check.

Anyway. The boost on insn 15 in cand = the birth of pseudo 16 (rgb's pseudo) — matches C0391: birthing_insn_p boosts the insn that births a pseudo with reg_n_sets==1. In the tree, the same insn (set s0 = a2) is NOT boosted because the asm gave the pseudo a second set.

And the effect: boosting insn 15 made it be scheduled... LATER in the final order (after insn 18)? In the cand, insn 15 was launched at T-21 (the trace shows "ready list at T-21: 15 (7f000001) 18 (1), now 15 18"). So insn 15 was launched at T-21, and insn 18 at T-22. Wait the trace: T-21: "15 (7f000001) 18 (1), now 15 18" → launches 15 first. T-22: 18. So the order is 15 then 18?? But the final RTL shows insn 18 before insn 15!

Hmm, the trace's "now X Y" lists the ready list order after launching. Let me re-read: ";; ready list at T-21: 15 (7f000001) 18 (1), now 15 18" — the ready list at T-21 contains 15 and 18, and "now 15 18" means after the launch, the list is 15 18? The launched insn is removed from the list. Hmm, in gcc's trace format: "ready list at T-N: <list>" then "now <list>" where the launched insn is removed. So at T-21 the list was "15 18"? and after launching one it's "15 18"... confusing.

Let me instead compare the tree's trace at the same point.

Actually, more useful: what matters is that in the tree, the set s0=a2 is scheduled BEFORE set a0=16, and in cand it's after. The boost in cand prioritized insn 15, but scheduling order put it later? That's odd — unless the launch order in the trace is reversed from the final RTL order? No, sched1 produces the final RTL in launch order.

Hmm wait. Maybe the trace's insn numbers are pre-scheduling and the final RTL list at line 243+ is the *input* RTL (the dump file contains the RTL after the pass...). Let me verify with the tree: check its final order of the two insns.

Let me grep the tree sched dump around the same place.
