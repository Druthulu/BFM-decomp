---
ts: 2026-10-22T12:29:02.374Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a94c6b13493f87646
model: claude-opus-5-5[1m]
effort: medium
turnId: 9c9b7ae4-bfab-4fb2-aa68-e89ba2a0dbfd
---
I need to build bank_B4.txt covering shards G14, G15, RM1, RM1x, RM2, RM2x, but G14 and G15 already banked their earlier MATCHes so I need to check whether bank_swap is idempotent on those — swapping an already-banked win.c again should be a no-op since TSV rows are already dropped, but new WALL rows (like G14's func_80191020 and G15's additions) still need handling, while previously-banked MATCH rows should just be dropped.

The RM shards were retries of rows previously walled by other models, so their TSV entries may already carry an earlier wall cause that bank_rows needs to overwrite — that's fine. Now I'll write the brief incorporating these adjustments.
