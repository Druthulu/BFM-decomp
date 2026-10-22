---
ts: 2026-10-22T08:50:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_t2dcwH5Pqw6CXr73K9G1
---
Very useful. C0409 "THE RELOAD-REMAT CONSTANT" and C0469 "A `la $tN` + `addiu` PAIR CAN BE A RELOAD ARTIFACT THAT NO C SPELLING REACHES". Also §467 "GLOBAL-ALLOC TIES BREAK ON *DECLARATION* ORDER".

Let me look at C0409 (the reload-remat constant) — it might describe the mechanism for choosing a reload reg. And C0471 "A LAUNDER'S REAL COST IS AN ALLOCNO, AND `$t0` IS RELOAD'S".

Let me read C0409 and maybe C0471. These are cookbook files: cookbook/C0409.md.

Let me check the index format to find the file names.
