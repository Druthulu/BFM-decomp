---
ts: 2026-10-21T23:35:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_DZMotSnPzwJvdoj9dn03
---
Item 2: func_80180D54, launder kind. The launder is `__asm__("" : "=r"(p0) : "0"(p0))` for p0 and p1.

The launder for p0/p1 (stack array pointers) is used to prevent gcc from folding `sp10` / `sp10+4` into the calls. func_800D20C0(p0, p1, 1) — the target presumably has `addiu a0,sp,0x10; addiu a1,sp,0x18`.

Without the launder, gcc would... hmm. Let's just test: copy def to orig.c, remove launders, score.

Let me set up. First let me understand the setup: `tu` file contains the TU path, `fn` the function name, and dt.sh runs delever_search.py --try <TU> <fn> <bodyfile> --body.

Let me check what the existing dirs have (func_80180D54 dir has orig.c already? it listed orig.c, tu, fn, kinds, a1.c a2.c b1.c b2.c). So a prior run started this item. Let me check what's there.
