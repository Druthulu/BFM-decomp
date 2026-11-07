---
ts: 2026-11-06T22:05:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ptddF90wwQJvY3xU2QEq
---
Off by one: prev_win has an extra `}` at 311. The function ends at 3097? The sed 3092-3100 showed line 3096 = `}`, then blanks, then `#include` at 3100. Wait, that sed output: 
3092: L80190FF8:
3093: unk34 = tmp;
3094: tmp = 0x96;
3095: L80191000:
3096: unk1C = tmp;
3097: }
3098: (blank)
3099: (blank)
3100: #include "common.h"

I misread. So the `}` is at 3097. Let me redo with 2787-3097.

Also there's no $16 pin in this body (notes mentioned $16 on src, but the current src has only dst/tmp pins? grep showed only lines 4 and 7). Wait the notes said "$16 (src)" and "src as plain s32 on top of w1 gives 0 (x3.c) — the $16 pin is redundant". So the $16 pin was already removed in the banked body (win.c = x3.c). Current orig has only dst $3 and tmp $2 pins. Good.

Let me redo.
