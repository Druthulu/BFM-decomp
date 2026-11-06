---
ts: 2026-10-22T15:56:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Vok95hbU0g3x6tjq1xqf
---
The TU includes `../shared/ov/func_80128158.h` — a *different* header path than func_8012B4B8.h! The shared body has multiple headers aliasing the same function (dedup). The scratch `shared/ov/func_8012B4B8.h` is one of several; the TU includes `func_80128158.h` (the canonical one for MAIN_012). So my body substitution went into func_8012B4B8.h but the TU uses func_80128158.h — which likely #includes func_8012B4B8.h? No... Let me check: does src/shared/ov/func_80128158.h include func_8012B4B8.h?

Actually the dump shows the launder, so func_80128158.h must contain the same body (maybe a copy or an include). Let me check.

Wait: the item's tu is src/shared/ov/func_8012B4B8.h (the header itself). delever_search --try <tu> finds recipes for that TU — includers of that header? It compiles a TU that includes it. Hmm, but the scratch TU includes func_80128158.h. Let me look at how the recipe works: maybe `src` of the recipe is the includer .c and the header gets copied to its own path. Let me check src/shared/ov/func_80128158.h.

Hmm, the scratch includes ../shared/ov/func_80128158.h — that file might be a thin alias header that #includes func_8012B4B8.h? Let me check.
