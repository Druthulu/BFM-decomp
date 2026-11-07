---
ts: 2026-11-06T13:03:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ezNWi87x2ryfR1lacb0z
---
`-z` does show zero words (242 of them) and there are no "..." lines. So my extraction should have found them. But I filtered `len(p)<4` — a zero word line is `  1050:\t00000000 \tnop` which has 3 tab parts? Let's see: `1050:\t00000000 \tnop` splits on '\t' into ['  1050:', '00000000 ', 'nop'] = 3 parts! That's why they're excluded. My filter `len(p)<4` drops nop lines (which have no operand column).

So the nop lines were dropped. That's why 196.

OK so the missing insn in mine is a nop. Let me redo the diff including 3-part lines.
