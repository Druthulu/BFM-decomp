---
ts: 2026-11-06T11:34:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Zn1DqQMMFN1OBTaSatWi
---
I need the TU's object path. The oracle record has "obj". Let me just find it from the build dir. For header item, the TU is src/shared/ov/func_8012A1BC.h — not a TU. Hmm, the "tu" file for a header item is the header itself? Let me check: tu contains "src/shared/ov/func_8012A1BC.h". And dt.sh passes that as TU to delever_search. So delever_search handles header TUs specially.

Let me check how the record's obj is found for a header. Let me grep for ".h" handling.
