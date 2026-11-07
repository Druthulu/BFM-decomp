---
ts: 2026-11-06T18:53:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xGNDBfu9R2IMfTPQktBs
---
Now g007's asm: `la $7,D_8011FD10; move $3,$7` — the symbol goes into $7 (a3) and is copied to $3 (v1) — MATCHING the target's init! 

And the loop: `lhu $2,0($3)` (v1=$3), the stores use $4/$5, and at the end `move $2,$7` (return a7=$7). 

The only remaining diff (score 2) is the position of `addiu a3,a3,104` in the loop tail. Let me see the tail of g007's asm (lines 58+).
