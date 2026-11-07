---
ts: 2026-11-06T18:46:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hOzI8fLOj2pU6tIJm52G
---
Now the pseudo mapping:
- 72 = a0 (param copy)
- 73 = a6 (loop counter, init 8)
- 75 = a5 (init 0x340)
- 76 = v1 (the loop pointer; set from a3 at insn 17)
- a3 = the hard reg $7 used as a *variable* (reg/v:SI 7 a3)! The `register ... __asm__("7")` pin is GONE in w1, but the RTL shows `(reg/v:SI 7 a3)` — that's because the source still has... wait, w1 removed the `register ... __asm__("7")` line. Let me check: w1.c has `unsigned short *a7;` (plain). But the RTL shows reg/v:SI 7 a3 — that's the hard register 7 used as a variable! How?

Hmm! Because the source declares `a7` and the RTL shows `(reg/v:SI 7 a3)`. A plain C variable can't be a hard reg... unless the declaration line `unsigned short *a7;` was compiled with... no.

OH WAIT. Maybe the TU I dumped is not w1's scratch but something else. The --keep scratch path was ov_MAIN_012__func_80146750/p3, and I dumped `.run/P36/engine/score/ov_MAIN_012__func_80146750/p3/*.c` — the glob may have matched a different file, or the scratch contains the *pinned* orig? Let me check: the w1.c has no `register`. But the RTL shows a3 as a variable. 

Hmm, unless the header include in the TU uses a *different* definition (the includer might have its own copy?). The TU is ov_MAIN_012_jr_801458E0.c which includes the header. The header's body is substituted from my w1.c by delever_search. But maybe delever_search's --body replaces the function in the TU text, and the TU also has the function defined elsewhere? Or the scratch dir has `shared/` and `inc/` subdirs — maybe the .c I dumped is the *includer* with the header include, and the header body was replaced. The RTL shows a3 — meaning the replaced body still had the pin? Let me check the scratch file's content.

Wait, I ran the --keep with w1.c, so the scratch should have w1's body. Let me grep the scratch .c for "register".
