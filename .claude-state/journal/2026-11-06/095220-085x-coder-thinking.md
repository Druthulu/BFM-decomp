---
ts: 2026-11-06T16:52:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iq0nRGTP1dhmhzh14dPN
---
The dead-reset technique: name the value in a variable p, use it, then `p = 0;` after. This invalidates cse's equivalence.

Our source already has block-scoped `s32 m` per laundered call. The fix: after each call, add `m = 0;` (dead reset). But the m's are block-scoped inside `{ ... }` — after the call, the block ends; adding `m = 0;` inside the block would be deleted by flow before sched1 but still invalidate cse. Since each laundered site has its own m and block, the reset only kills that site's value. But the issue is that cse merges site 1's m with site 4's m (group B). The dead reset after site 1's call would invalidate m's constant before site 4 → no merge. 

But the group B sites (non-laundered) still need resets too, so that their values don't merge with each other or with later sites. Target materializes each fresh.

The structure: 12 calls, 6 symbol constants, each used at 2 sites. If every site gets a dead reset after it, cse won't carry the constant forward, and each site materializes fresh. Let me apply the dead reset to every m site (both laundered and non-laundered) and score.

Actually, better: make m a function-scope variable? No — per-site blocks are fine. Let's add `m = 0;` after each func_8017D8A4 call within the block.

Let me construct: for the 9 laundered sites, the block is `{ s32 m = (s32)SYM; <asm>; func(...); }`. Remove the asm and append `m = 0;` before `}`. For the 6 non-laundered `{ s32 m = (s32)SYM;  func(...); }` sites, append `m = 0;`.

Wait, how many non-laundered blocks are there? 6 (groups B and D). And laundered 9? Let me count: group A 3, group C 3 = 6 laundered. Plus the 6 non-laundered = 12 sites total. Earlier I counted 9 asm occurrences — let me recount: lines show 6 launders? The regex found 9 `__asm__` removals? Actually the file has 9 launder comments? Let me count. Earlier: `print(s2.count('__asm__'), s2.count('!FAKE'))` → 0 0 after removal. Let me count in orig: grep -c "__asm__".
