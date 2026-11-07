---
ts: 2026-11-06T09:13:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1baJiL0JspWm8MMdBHuL
---
Target's tail: `lui v1; lw v1; nop; beqz v1; move v0,zero; lui v0; addiu v0` — the if/else on flg: res=0 then if (flg) res=&D_801F832C, but the target shows `beqz v1, skip; move v0,zero` then `lui v0...`. Hmm, target keeps res in v0 naturally! And the branch structure differs: target has `beqz v1, 628` then `move v0,zero` (delay slot? no, `move v0,zero` after beqz is the delay slot!) then lui v0, addiu v0.

So target:
```
lui v1,0x0; lw v1,0(v1)   ; flg = D_801F84AC
nop
beqz v1, L
move v0,zero              ; res = 0 (delay slot)
lui v0,0x0; addiu v0,v0,0 ; res = &D_801F832C
L:
```
That's `res = 0; if (flg != 0) res = ...` compiled as branch around the else... Actually `if (flg != 0) { res = &D; }` with res=0 before: the compiler inverted to `if (flg == 0) goto L; res=0;`? Hmm, the target has beqz v1 → L, then move v0,zero, then lui v0/addiu v0. That means: if flg==0 goto L (with res already... no). Wait order: beqz v1,L; move v0,zero (delay slot executes always); lui v0;addiu v0 (res=&D); L: ... So if flg==0 skip the address, res=0. If flg!=0, res=&D. Exactly `res = 0; if (flg) res = &D;` but with res=0 in the delay slot.

Hmm, but my lever-free body has the same source. Why does mine differ (mine is 71 vs 79)? The diff at [65] says target has 8 extra insns there, and mine's tail must be shorter. Let me see mine's tail. Score 14 COUNT; 71 vs 79 — target has 8 more insns. The insert shows target 66-73 extra. So mine dropped the `res` computation entirely? No, mine has 71 insns, target 79. Let me dump mine fully to compare.

Actually mine is missing the whole res tail? Let's see mine[65] onward.
