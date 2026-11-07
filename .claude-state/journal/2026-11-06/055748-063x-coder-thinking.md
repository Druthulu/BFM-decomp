---
ts: 2026-11-06T12:57:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ra9ecVDd4jgadt2QWNbZ
---
Now clear: c6 (mine) has an EXTRA `sb zero,70(s0)` at 2 sites — because I moved the store before the mask load in case 3, so the store now appears twice? No — mine has an extra sb relative to target at those spots, and mine's count is 2 more (3770 vs 3768 overall, but the function counts said 343=343... hmm, 3770 vs 3768 is the whole object).

Wait, the function counts: mine 343, target 343 per the tool. But my manual dump says the function has 3770-... no, that's the whole object's instruction list (I didn't stop at the function end). OK.

So the function-level diff: mine has an extra `sb zero,70(s0)` at 2 places, and presumably one fewer elsewhere... but the tool says counts are equal. My manual diff shows only insertions (2 extra). So mine = target + 2 insns? But the tool said 343 = 343. Hmm, maybe my extraction includes the next function's insns. Whatever.

Key: with c6 (store first), the sb appears TWICE in the case-3 path? Looking at the context: `move a0,zero; lhu v0,0(s0); [sb zero,70(s0)]; sll v0; addu; lw a1; jal`. So the sb is inserted between the lhu and the sll.

But wait — in c6 the source is:
```
case 3:
    p[0x50] = 0;
    mask = tbl[p->unkA];
    func_8002EFF8(0, mask);
```
That's ONE sb. So why two sb's? Because c6 was built from `nb` which is orig minus the barrier, and I replaced case3's `mask = ...` line with `p[0x50] = 0;\n mask = ...` — keeping the original `p[0x50] = 0;` line that follows! So the store appears twice: once before and once after the mask load. That's a bug in my variant.

So c6 actually = store before AND after. That's why +2 insns.

Let me redo: case 3 should be `p[0x50] = 0; mask = tbl[p->unkA]; func(0, mask);` — replacing both lines.

Let me fix and retest. Also the earlier c1 trick: let me combine ideas.

Let me write a proper variant set:
- k1: case3 = `p[0x50] = 0;` then `mask = tbl[p->unkA];` (store first, only once)
- k2: c1 (u8 dispatch) + case3 store-first
- k3: c1 + case2 tweaks

Let me first do k1.
