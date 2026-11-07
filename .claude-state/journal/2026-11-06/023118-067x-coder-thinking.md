---
ts: 2026-11-06T09:31:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PLnSbCC1y4ATODhmE7nN
---
02:31:08. Need until 02:33. One more short batch or wait. Let me do one more batch of 6 (l1-l6) — cheap.

Actually, let me use this time to check whether a *partial* is achievable: keep K1 and remove K2+K3 with a real-C fix of the fc/lim swap. Best so far 6 (s251_57, y2, y4, y8, y10, y12, y16, y18, y20, x9, i3). None below 6. So no PARTIAL.

One more idea for the swap: the limit's first pseudo (r137/r149, pri 7500) gets a0; fc (pri ~1000) gets v1; iVar7 gets a1. What if we *lower* iVar7's priority so fc gets a1? iVar7's priority: refs 3? live 4? Let me check the alloc table for iVar7. In the target, iVar7=v1 (the lower-priority reg). So if iVar7's priority were lower than fc's, fc would take a1 and iVar7 v1.

The keepalive for iVar7/t (K2) *adds refs to iVar7 and t*, raising their priority... but K2 is in the *else* branch. Hmm, K2's presence changed the a0/v1 assignments (w2 diff).

What if we give fc *more refs* by using it in the second comparison twice? e.g. `else if (fc > lim && fc != lim)` — extra compare. No.

What if we *reduce* iVar7's refs by computing t = fc ± 0x400 directly but keeping the move via zr: `int t = fc + zr + 0x400;` — then iVar7 disappears, t = fc + zr + 0x400; codegen: move? addiu t0? The target has `move v1,a1; addiu v0,v1,1024`. If we write `fc + zr + 0x400`, the compiler might emit addiu v0,a1,0x400 directly (folding zr), no move. That's why iVar7 exists as a separate statement.

What if `int t = (iVar7 = fc + zr) + 0x400;` — assignment inside expression, iVar7 live? That's y21-ish (12).

OK, wall it. Let me do one more batch to reach 20 min.

l1: allrm + `t = iVar7 + 0x400` with iVar7 as the direct add: `int t = (fc + zr) + 0x400;`
l2: allrm + `int t = fc + 0x400;` and iVar7 kept for the else branch only.
l3: allrm + iVar7 = fc + zr kept, t = iVar7 + 0x400 (orig) but fc load after the iVar7? no.
l4: allrm + `int t = iVar7 + 0x400;` where iVar7 is `register int iVar7 = fc + zr;`
l5: allrm + the clamp comparison `((t << 16) >> 16) > lim` rewritten `(s16)(t) > lim`? tried k2.
l6: allrm + store `*(s16*)(param_1+0xc) = (short)((t<<16)>>16);`

Let me just run 6 quick ones.
