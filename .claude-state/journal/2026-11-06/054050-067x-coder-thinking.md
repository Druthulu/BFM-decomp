---
ts: 2026-11-06T12:40:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GMLMUpndm8QjukM997qT
---
So "insn 124 has a greater potential hazard, now 124 127" means 124 is moved to the front → 124 is scheduled before 127.

But the final RTL has 127 before 124!? Let me double check the lreg dump order: 

```
(insn 127 120 124 (set (reg/v:SI 73) (const_int 7)) ...)
(insn 124 127 129 (set (mem/s:SI ...) (reg:SI 2 v0)) ...)
```
The format is (insn UID PREV NEXT PATTERN). So insn 127's prev = 120, next = 124. So 127 comes before 124 in the stream. So sched scheduled 127 before 124? But the dump says 124 was moved to the front at T-2...

Hmm, wait. Maybe I misread: the ready list is scanned from index i to j and the best (highest hazard) is moved to the FRONT of the *remaining* list. The printed "ready list at T-2: 124 (1) 127 (1), now 127 124" is printed BEFORE the hazard scan? Let's look at the code order: line 2682 prints ", now" with the ready list, then prints the hazard message. So "ready list at T-2: 124 127, now 127 124" — hmm, the first print shows the ready list at that moment as "124 (1) 127 (1)" and then ", now 127 124"?? That's contradictory unless the "now" list is printed after some reordering... Let me read more context above line 2661.
