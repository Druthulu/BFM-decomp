---
ts: 2026-10-22T16:06:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HOxUrje1tse5sWwm9It2
---
Wait, that body looks odd — `p = it + 0x658C; goto test; ... it = (s32)D_801202A0; ... if (it == p) goto zero;` This is a decompiled goto soup. The function is in src/shared/ov/func_8012C2D0.h and orig.c matches (ORIG_FRESH). Good, no regeneration needed.

Now let me see the target and the prior candidates. The prior variants.py was written for this item (D_80120194, 0x658C, D_801202A0). Let me score all existing candidates first.

Let me also check how many includers (list.tsv says 19 lines = header lines? 25 lines. Hmm, 19 maybe the includer count). Let me run incl.py to get the count. Actually incl.py takes tu(s). Let me run it.

Also, let me look at the target disassembly and the best candidate's residual.

First score everything.
