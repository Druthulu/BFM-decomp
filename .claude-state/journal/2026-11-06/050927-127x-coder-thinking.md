---
ts: 2026-11-06T12:09:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1MyrW1ubHrFYL2Vew44N
---
All 4 rows. Shard dir 1.3M, fine.

Now let me write notes.md for each item dir. The brief says "Notes in <dir>/notes.md".

Let me write concise notes for each item.

Then the log file phase-ends/current/logs/T11.cG30x.md with a timeline per item, moves that cracked, walls with evidence.

Also, the FRESH requirement: at each item's start, diff orig.c against the current src def. I generated orig.c from the current src at each item's start, so they're fresh by construction. I should note that in notes.md.

Let me write the notes files. I'll use the Write tool.

Item 1 notes:
- orig.c regenerated from src at 04:40ish (I did sed from the current src). 
- barrier removed alone = 23 (barrier IS the reload cause), launder removed alone = 6.
- launder cracked by u16 sVar3 (keeps the s1 copy).
- barrier: needs a memory clobber; real varying stores survive to output (flow keeps them); self-store survives.
- result PARTIAL:barrier, best 0.

Item 2 notes: from the src header (2701-2743): mechanism (1) global-alloc pri tie needs N zero-byte insns; mechanism (2) sched2 order needs re-ties; 470+ orderings tried.
- v2 (launders gone) = 3; v3 (barrier gone) = 42; both = 45.

Item 3 notes: launder cracked by C0414 dead resets (_pm2=0, _a=0, _b=0) → 0 with the 4 sliders kept (PARTIAL:barrier). Sliders: §47 live-length slider for the my/mny allocno tie; lever-free a2/a3 + s5/s6 grants swap (best 38→ actually e0=53; let me use 53).

Hmm wait, for item 3 the result is PARTIAL:barrier with best 0. The evidence mentions the lever-free best 53? No — the WALL column has the tag; best=0.

Item 4 notes: as above.

Let me write them.
