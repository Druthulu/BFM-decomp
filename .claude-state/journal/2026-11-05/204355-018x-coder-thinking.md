---
ts: 2026-11-06T03:43:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xI9CHDlWPONjgWsvn7yT
---
"the function's instructions are read out of that scratch object... run's baseline object under build/". So target = the tree's own bytes in build/ — i.e., the built object of the current tree? Wait, but then a lever-free body would be compared to the tree's current build? That doesn't make sense if the tree currently contains the lever body. Hmm, "That target is the tree's own bytes — proven by the SHA1 check". So the target is from the pre-built ROM object, which is byte-matching the tree's source... but if we change the body, the target stays the build's baseline object. OK.

So target disassembly is available in build/. Let me find the object and disassemble to see target insns. Where is build? Let me find the target objdump route. Maybe tools/alloc_table.py / cc1_dumps. Let me look at dt.sh with --keep maybe prints candidate object. But for target, perhaps there's a function in delever_search. Let me grep for "tgt".

Actually easier: `tools/delever_search.py --explain TU FN` reads one body's residual. Still no target dump. Let me search tools/ for a disassembly helper of build objects.
