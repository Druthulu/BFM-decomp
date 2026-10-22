---
ts: 2026-10-22T08:41:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_vtLIeGT1sopIwjSa1HQt
---
The scratch dir has the candidate TU source (cand: the full TU with my body substituted). I can copy that to my shard dir and run cc1_dumps_tu.sh on it to get the .greg dump, then run alloc_table.py.

But the dumps are large (the TU is 250k chars). The dump dir would be big. Disk is capped (~4GB free). Let's check available disk first.

Also cc1 dumps for a 8000-line TU could be tens of MB. That's fine.

Plan:
1. Copy the candidate TU .c into my item dir (e.g. tu_c1.c) — 250KB, fine.
2. Run cc1_dumps_tu.sh with DUMP_ROOT under my shard dir and the .c file → produces dumps.
3. Run tools/alloc_table.py <tag> func_801815AC <dump_root> to see the allocation table.

That tells me the priority of q vs others and the conflicts.

Let me check disk space and the alloc_table usage.
