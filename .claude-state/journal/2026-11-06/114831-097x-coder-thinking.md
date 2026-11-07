---
ts: 2026-11-06T18:48:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QH4PBZcyHNmGGHq9PYwv
---
The standalone candidate's asm: `la $3,D_8011FD10; move $7,$3` — the symbol goes to $3 and is copied to $7. So a7=$3, v1=$7. But the dispositions said 74→7, 76→3. Hmm, which pseudo is which? Maybe 74 is v1 and 76 is a7!

Let me re-check: the RTL: insn 14 `(set (reg/v:SI 7 a3) (symbol_ref))` — wait, that RTL was from the WRONG dump (the real pinned header). Let me re-read the correct standalone RTL now. Let me look at the new dump's .rtl.
