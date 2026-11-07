---
ts: 2026-11-06T21:41:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dReoVODaVttCytaC3eS0
---
Symbol differences only. So the recipe transfers directly. Build w1 for item 2 by taking item 1's win.c and substituting symbols. Easiest: apply the same textual transforms to item 2's orig.c via a small sed script, mirroring the 4 changes:

1. add `struct S151D0 { s32 v; };` after the opening brace
2. remove the `register s32 zr ...` line
3. `ot = (s32 *)D_801151D0;` → struct alias load
4. `cnt = n + zr;                                            /* [3] */` → `cnt = (s16)n;`
5. `do { lim = cnt; } while (0);  // !FAKE: do-while` → `lim = (s16)cnt;`
6. remove barrier [4] line, add `do { } while (0);  // !FAKE: do-while` after the call
7. remove memory barrier, `D_801151D0 = (s32)ot;` → struct store

Let me verify item 2's orig.c has the same lever lines.
