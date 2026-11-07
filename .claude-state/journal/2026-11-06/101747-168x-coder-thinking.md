---
ts: 2026-11-06T17:17:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_deV7Coh7SHCP10MUNsL7
---
The key: "Order the qtys so we assign them registers in order of decreasing length of life" — wait, the comment says that but qty_compare divides by (death-birth), so shorter life = higher priority (earlier). Hmm, the comment may be stale.

Let me look at qty_compare again: pri = floor_log2(refs)*refs*size/(death-birth); return pri2 - pri1 → higher pri first. So shorter life (smaller death-birth) → higher pri.

For the mask: refs 13 → 3*13*4=156; life? If life is large (813), pri = 0.19.
For the constant: refs 2 → 1*2*4=8; life 101 → 0.079.

Mask > constant → mask first. So the mask should get the first free reg. Unless at the mask's allocation the register scan doesn't include t6 because of a conflict with an *already allocated* qty... but allocation order is by priority, so only higher-priority qtys are allocated before the mask. A higher-priority qty could hold t6 and be live at the mask's birth.

Which qty holds t6 before the mask? In the final, t6 is the 0x8E constant (lower priority) — but maybe at the mask's allocation, t6 was free and the mask took... 15? find_free_reg returns the *lowest-cost* free register, not the lowest number! The cost depends on `reg_pref` / the preferred class and the number of conflicts. find_free_reg computes for each free reg the "cost" = number of conflicts in the qty's conflict set? Let me look at find_free_reg.
