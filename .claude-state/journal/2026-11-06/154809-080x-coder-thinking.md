---
ts: 2026-11-06T22:48:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Y5XXdoW5ZpfJHIZwABKG
---
The sibling func_8012BB3C used a do-while around the div block to lift div's refs 7→9 so div gets $s0 and a gets $s1. That's the same trick as our do-while on the cast (raising d's refs).

For OUR function, the do-while on the cast raises d's refs to 9 (pri 10000 > s1ang's 6363). That works for d/s1ang. But the u5/iVar4 shift remains.

Hmm, in our w6, the u5/iVar4 shift is the residual. In the sibling, the residual was just the cast temp. So the sibling's approach nearly worked.

Let me look at our target's u5/iVar4 requirement again. The target: u5=$a0, iVar4=$v1. Our w6: u5=$v1, iVar4=$a1.

Maybe the difference is the *preference* on iVar4 for a1, which in the target doesn't exist. In the target (pinned), iVar4 = $v1. Hmm.

Wait, actually — maybe the target's allocation is a consequence of d being pinned, and any lever-free body will shift u5/iVar4 because d becomes a pseudo with a preference. The sibling 8012BB3C's target: a=$s1, div=$s0, q=$v1, d=$v0 — and their win.c got div=$s0, a=$s1 with the residual being only the cast temp. So their u5-equivalent (cur) was correct.

Hmm, our residual is different: u5/iVar4 shifted. Why does ours shift but the sibling's doesn't?

Our w6 residual: u5=$v1 (target $a0), iVar4=$a1 (target $v1).
Sibling's residual: cur=$v1 (target $a0?), iVar4=$a3 (target $v1)? The sibling's note says "frees $v1 at cur's birth, so the caller bank shifts (cur $v1 vs $a0, iVar4 $a3 vs $v1) -> 22". So the sibling ALSO had cur $v1 vs $a0 and iVar4 $a3 vs $v1 in one variant! And their best 2 had only the cast temp issue.

So the sibling found a formulation where cur=$a0 and iVar4=$v1. That's the "two-statement div<<16; div>>16" variant? Let me re-read: "Two-statement `div<<16; div>>16` is in-place (no temp) but frees $v1 at cur's birth, so the caller bank shifts (cur $v1 vs $a0, iVar4 $a3 vs $v1) -> 22." So that variant scored 22 with the shift. Their win.c (best 2) has the do-while cast block and the cast via `(s16)div`, which keeps the temp.

Hmm, so their win.c's residual is only the cast temp ($v1 temp vs in-place). Their cur/u5 and iVar4 are correct. What's different in our function?

Let me look at their win.c's structure vs ours:
- They have `a = arg2; div = arg3;` at the top (two copies).
- `ang = ratan2(...); ang = ang - 0x400;`
- do-while { div=(s16)div; a = a & 0xFFF; cur = ang & 0xFFF; }
- if (a == cur) ...
- do-while { if (diff>=0) {...} else {...} }

Their mask-in-place is `a = a & 0xFFF` (a = the s1ang equivalent) and `cur = ang & 0xFFF` (cur = u5 equivalent). They keep `cur` as a separate variable!

In our function, u5 is `(ratan2(...) - 0x400) & 0xFFF` and u6 = s1ang & 0xFFF. The target's u5 = $a0 and u6 = $s1.

Hmm, in the sibling, the mask-in-place is on `a` (s1ang) and `cur` (u5) separately, both inside the do-while.

Let me try to mimic the sibling's structure exactly:
```
d = arg1;
s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
u5 = (ratan2(...) - 0x400) & 0xFFF;
do {  // !FAKE: do-while
d = (s16)d;
s1ang = s1ang & 0xFFF;
} while (0);
if (s1ang == u5) return 0;
iVar4 = u5 - s1ang;
...
```
Wait, that's w6 but with both the cast and mask inside the do-while. In w6, I had the do-while only on the cast and the mask outside. Let me put both inside a single do-while, like the sibling.

Also the sibling has the div block in a do-while. Let me try adding that too.

Let me create w8 = w6 with the mask inside the same do-while as the cast:
```
do { // !FAKE: do-while
    d = (s16)d;
    s1ang = s1ang & 0xFFF;
} while (0);
```
And w9 = w8 + the div block in a do-while.

Let me test both.
