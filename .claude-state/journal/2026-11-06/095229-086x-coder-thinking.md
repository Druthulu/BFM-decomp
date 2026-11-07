---
ts: 2026-11-06T16:52:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_j6eafOkdCzfLf3tVWHhg
---
6 launders, 12 m sites. Each of the 6 symbols appears at 2 sites (one laundered, one not).

Now: add a dead reset `m = 0;` after each call. Let me generate a variant with the reset in every m block. The blocks are one-liners like:
`{ s32 m = (s32)D_8018E2DC;  func_8017D8A4(D_801BFCBC + 0x84, (void *)m, (void *)(m + 0x30), 0, 1); }`

I'll transform: `func_8017D8A4(...); }` → `func_8017D8A4(...); m = 0; }`.

Let me write a python script that finds `{ s32 m = (s32)SYM; ... func_8017D8A4(...); }` and adds `m = 0;` before the closing brace.

Test first on the win.c (asm removed) plus resets.
