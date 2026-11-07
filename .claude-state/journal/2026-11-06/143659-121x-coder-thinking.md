---
ts: 2026-11-06T21:36:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_s3bC1lng6S50xV8PwMIO
---
Let me interpret:
- insn 6: `(set (reg/v:SI 17 s1) (reg:SI 5 a1))` — d = arg1 → s1. So d is allocno 74 (in s1).
- insn 20: `(set (reg/v:SI 16 s0) ...)` — s1ang load → s0. So s1ang is allocno 77 (in s0).
- insn 55: `(set (reg/v:SI 17 s1) (sign_extend...))` — this is the d cast `d = (s16)d` → s1.
- insn 57: `(set (reg/v:SI 16 s0) (and ...))` — u6 = s1ang & 0xFFF → s0.

So d=74→s1, s1ang=77→s0. Confirmed.

77's preference for s0 comes from... its `preferences: 16`. Where? Maybe the load's target preference or a copy. Let me look at insn 20's context. Actually, the "preferences: 16" for allocno 77 means global-alloc assigned it s0 as a preference (a tie-break). 

To make d (74) get s0: raise 74's priority above 77's, or remove 77's preference for s0.

74's pri = 5185, refs 7, live 27. 77's pri = 10000, refs 5, live 10. So 77 has a higher priority (shorter live → higher pri). To beat it, d needs pri > 10000, i.e., refs/live ratio higher. d has live 27 (long, crossing the call and the divisions). If I shorten d's live range or add refs...

d's live range: from `d = arg1` (insn 6) to the divisions (late). That's long (27 insns). s1ang's live: from insn 20 to insn 57 (compare) — 10 insns? But s1ang is used at the compare (insn 57) which is before the divisions. So s1ang dies early.

Hmm. To raise d's priority, add refs (do-while loop weight). d has 7 refs. If do-while adds loop weight, refs could become higher. Let me check the C0535 mechanism: flow's `REG_N_REFS` gets incremented by `loop_depth` for each use? Actually in GCC 2.7.2 flow.c, `REG_N_REFS (regno) += loop_depth` per use? Let me check.

Actually, the do-while(0) in C0535 worked by "splitting cse1's EBB" (scheduling) and "flow REG_N_REFS += loop_depth" (priority). So a do-while(0) is seen as a loop by flow (loop_depth 1) even though it runs once.

In w5 (div do-while), the score was 21 (same as w3), suggesting no priority change. Maybe the do-while on the div block didn't survive to flow (it's inside an if/else and got optimized). Or maybe it did add refs but not enough.

Let me check the w5 alloc table to see if d's refs changed. Let me dump w5 quickly. Or check w4.

Actually, let me try a different approach to raise d's priority: add *more* refs by wrapping d in multiple do-whiles, or by making d used in the cast loop. E.g.:
```
do { do { d = (s16)d; } while (0); } while (0);
```
That adds loop depth 2.

Or use `while (0) { }`? Same.

Alternatively, lower s1ang's priority: make s1ang's live range longer? That lowers pri. E.g., move the `u6 = s1ang & 0xFFF` later (after the divisions)? But that changes the target order. Hmm.

Or remove s1ang's preference for s0: where does it come from? Maybe from the `lh` load being assigned s0 by local-alloc (block-local) and then global-alloc inheriting the preference. If s1ang is used only in one block (block 0), local-alloc might assign it s0, and global-alloc... but it crosses the call? s1ang is loaded before the ratan2 call and used after (u6 and compare). So it crosses the call → global.

Hmm, the preference for s0 might come from a copy: `s1ang` is loaded into a pseudo that's then copied to s0? Let me look at insn 20.

Let me read insns 20-60 in the greg dump.
