---
ts: 2026-11-06T11:49:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Q2LgC1mWr4lfWiviPdZL
---
Very close! p10: only three stores (sh 16, 18, 24) are 3 positions later. In target they come right after `lw t1,16(sp)`? Let's see: target[73:76] = sh s1,16; sh v1,18; sh a0,24 at positions 73-75. Mine has them at 76-78, i.e. after 3 other insns (probably lw t1,24(h_), and, addu).

This is the sched1 ordering: target does sh 16 before the y-add's dependencies; mine delays.

Wait, the diff shows target inserts the three shs at 73 and mine has them at 76. So mine has 3 insns before them that target has after: likely `lw t1,24(sp)`, `and`, `addu s2`. So in mine the y-add chain is scheduled before the x stores; in target the x stores come first.

Hmm, this is sched1 ordering within the second block. The x stores depend on addu s1 (x += w_). In mine: addu s1 at ~70, then...? Let me get the actual disassembly to compare.

Let me dump mine (p10) and target side by side around indices 60-90. I'll use --keep to get the object and objdump, plus the target from build/src/800.o.

Actually simpler: write the two disassemblies to files and read the range. Let me do it with a small script? I can use mipsel-linux-gnu-objdump directly on the kept candidate.

Let me run --try --keep for p10 and dump both.
