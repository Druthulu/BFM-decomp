---
ts: 2026-11-06T15:32:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kP3FWv4XLmUTj4cUD6V0
---
The spliced TU from --try has the asm lines *stripped*! delever_search likely strips `__asm__` launder lines when building the candidate (that's what "lever-free" means). So --try with orig.c actually strips the launders automatically? But orig.c scored 0...

Wait, that can't be: if --try strips the asm, orig.c would score 14. Unless --try's stripping only applies... Hmm. Let me check: the a7_tu.c also had no asm (a7 has none anyway). Let me look at delever_search's strip logic.
