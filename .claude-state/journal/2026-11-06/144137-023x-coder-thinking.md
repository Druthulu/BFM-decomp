---
ts: 2026-11-06T21:41:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2EUS49Rbu3wXj7iDP2BU
---
Identical structure. Generate w1 with a sed script. I'll write a small python script? sed is fine with careful escaping. Let me use python -c? Rule: "Scripts, not inline python -c". Use sed.

Transforms:
- line 30 delete (the register line)
- line 37 replace `    ot = (s32 *)D_801151D0;` → `    ot = (s32 *)((struct S151D0 *)&D_801151D0)->v;`
- line 72 `    cnt = n + zr;                                            /* [3] */` → `    cnt = (s16)n;`
- line 75 → `        lim = (s16)cnt;`
- line 78 → delete; and insert after the call line 79 `                do { } while (0);  // !FAKE: do-while`
- line 94 delete
- line 95 → `    ((struct S151D0 *)&D_801151D0)->v = (s32)ot;`
- after line 1 (`void func_8017E6BC(void) {`) insert struct decl.

sed with addresses is fragile; use python script file under .run/P40/T11/RM3x/. Write a small script `mkbody.py` that does these replacements on a file. Actually since item 1's win.c is the template and only symbols differ, better: take item 1's win.c, and replace symbol names according to a mapping derived from diff. That is: func name, D_801A3458→D_801CD9A8, Rec20_...E050→...E6BC, D_8019E8B8→D_801BB2DC? Wait mapping:

item1: D_8019E8B8 (label for else), D_8019E8CC (label), D_8019F70C, D_8019F730, D_8019F770, D_8019F7BC, D_8019F010.
item2: D_801BB2DC, D_801BB2F0, D_801C3C70, D_801C3C94, D_801C3CD4, D_801C3D20, D_801BBA34.

From diff: `label = &D_801BB2F0;` corresponds to `label = &D_8019E8CC;` (line 44 in both). And `label = &D_801BB2DC;` ↔ `&D_8019E8B8;`. So:
D_8019E8CC → D_801BB2F0
D_8019E8B8 → D_801BB2DC
and the order in decl list: D_8019E8B8, D_8019E8CC, D_8019F70C, D_8019F730, D_8019F770, D_8019F7BC, D_8019F010 ↔ D_801BB2DC, D_801BB2F0, D_801C3C70, D_801C3C94, D_801C3CD4, D_801C3D20, D_801BBA34.

Also D_801A3458→D_801CD9A8, func names, aliases.

But careful with substring collisions: D_8019E8B8 vs D_8019E8CC distinct. Replace longer first is fine.

Simplest safe approach: sed replacements in one pass with distinct tokens. Order: replace D_8019E8CC first then D_8019E8B8 (no overlap issue since full tokens differ).

Let me write the sed chain.
