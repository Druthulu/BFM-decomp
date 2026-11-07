---
ts: 2026-11-06T10:27:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_phckzdrnDMhcVZ3jiFXq
---
No change. Hmm. The compiler probably cse'd fcopy/flags.

Let me reconsider. The target's flags=a0, fcopy=v1, ret=v0. 

Let me look at the alloc table's r74/r76/r75 and identify. Let me check the lreg.

Actually, let me try the do-while ref-boost trick here: boost `ret`'s refs by wrapping the ret-assignment in a do-while(0). That would raise ret's priority above flags's.

E.g.:
```
do { // !FAKE: do-while
    if (flags & 0x4000) { ret = 2; }
    else if (flags & 0x2000) { ret = 1; }
    else { ret = 4; if ((fcopy & 0x8000) == 0) ret = var_s1; }
} while (0);
```
This boosts ret (+4 refs) and flags (+2) and fcopy (+1). ret would jump to the top → v0. Let me test.

Actually, ret's refs: currently 5 (3 defs + 1 use + ?). With do-while, +4 → 9. floor_log2(9)=3, 3*9/live. flags +2 → 6 refs. Hmm, flags might still compete.

Let me just test.
