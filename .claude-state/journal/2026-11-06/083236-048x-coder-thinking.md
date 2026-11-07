---
ts: 2026-11-06T15:32:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Dglftt033Tzvve84UTpP
---
Line 3187 is `flags = raw;` but there's no asm line right after? The asm for flags is missing from the TU! Let me look at the TU around 3180-3195.

Ah — maybe delever_search *strips* the launders when splicing? No... Or the extract.py-based orig.c has the asm at a line, and the splice inserted it. Let me check.
