---
ts: 2026-10-22T11:20:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_47fX4k9iaSxE9aTbt63u
---
Timestamps have 1-second resolution — not useful. But the `-d` flags order in cc1_dumps_tu.sh: `-dr -ds -dj -dl -dg -df -dc -dS -dL -dR -dt -dJ -dd`. GCC's -d flags:
- `-dr` = dump RTL after each pass ("rtl")
- `-ds` = "final" (after all) → sched2? Hmm, -ds is "final"
- `-dj` = "jump" (after jump)
- `-dl` = "loop"
- `-dg` = "global" (greg)
- `-df` = "flow"
- `-dc` = "cse"
- `-dS` = "combine"? no, -dS = "cse2"? 
- `-dL` = linenum
- `-dR` = "reload"
- `-dt` = "cse2"
- `-dJ` = "jump2"
- `-dd` = "delayed"

Hmm. GCC 2.7's -d options:
-dc : cse, -dC : ce1/ce2/ce3, -dj : jump, -dJ : jump2 (?), -dg : global, -dl : loop, -dr : rtl, -ds : final, -dt : cse2? Hmm. -dS: "combine"? Actually:
- `-dS` = "cse2"? no, -dt = cse2.

Whatever. The key question: does flow run before sched? The presence of both doesn't tell order.

Let me test empirically instead: does a `goto` survive to sched? I can check by dumping my goto variant and looking for a `jump` insn in the .sched dump.

But my goto variant scored 2 = same as v01, so it clearly didn't change anything.

Let me now focus: **the practical goal** is to get the load scheduled before the li a1.

From `rank_for_schedule` (sched2) we can't tell about sched1. But the key GCC-2.7 fact for sched1 is in `sched1.c`'s `rank_for_schedule`, which is similar: it compares INSN_PRIORITY first, then classes, then LUID.

`INSN_PRIORITY` for sched1 is set in `compute_priorities`:
```c
/* Return the priority of an insn ... */
```
In sched1.c, `compute_priorities` sets `insn->priority` = 1 + sum of dependency priorities, and for calls there's a special rule.

Hmm. Since we have GCC's `sched.c` (sched2) and not sched1.c, let me think about whether GCC 2.7.2's sched1 is the same file... Actually! In GCC 2.7, the file `sched.c` contains BOTH `sched1` (the forward scheduler, pass_sched) and `sched2`? No — in GCC 2.7, `sched2` was a separate file `sched2.c`? Hmm, but our sched.c has `rank_for_schedule` with "last_scheduled_insn" and "LOG_LINKS" — that's backward scheduling.

Hmm, in GCC 2.6/2.7, the file `sched.c` had `pass_sched` (forward, `sched1`) AND `pass_sched2` (backward, `sched2`)? Actually GCC 2.7 introduced `sched2` in a NEW file `sched2.c`? Let me check our sched.c for "sched1".

Let me grep.
