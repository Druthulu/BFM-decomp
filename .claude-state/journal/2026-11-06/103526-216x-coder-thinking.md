---
ts: 2026-11-06T17:35:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dqETCMADrk4Nyg7NNhBy
---
Time 9.7 min. All 7.

Let me try to see the preference's origin via the global.c dump code to know whether it's a copy suggestion.

Actually, let me try a different approach: check if the *pinned* build's temps match the target. Yes (score 0). The pin is $2 = v0.

What if instead of the pin we use a *different* C construct that makes sh16's qty get v0 via a copy preference to v0? E.g., a copy from a v0-valued variable: `sh16 = angle; sh16 <<= 16;`? y1 gave 8.

What about `sh16 = angle << 16;` where angle is assigned from the call result in a way that keeps it in v0... The call result is in v0; angle = func(...) creates a copy to angle's pseudo. If angle were NOT copied (used directly), e.g.:
```
if (r[0x49] == 5) {
    sh16 = func_80029D3C(cmp79) << 16;
}
```
but the call is before (angle = func; p[0x79] = angle; ...). If we inline the call into the then arm, the call would happen only in the then arm — different CFG.

Hmm.

What if angle is not stored before the if? `p[0x79] = angle;` is before. The target stores it before.

Let me try: make the shift's source `angle` a copy of the *stored* value... 

Time is nearly 10 min. I need 20 for a WALL. Let me continue with more variants; there are many spellings left.

Let me try:
e1: `sh16 = angle << 16;` in the then arm → `sh16 = (angle << 16) | 0;`
e2: `sh16 = angle << 16;` → `sh16 = angle << 16u;`
e3: declare sh16 as `s32 sh16;` and use `(s32)(sh16 << 16) >> 16`? no.
e4: the final expression with `s16`/`u16` casts at different points.
e5: swap the two if arms (if (r[0x49] != 5) { else-branch } else { then-branch }) — changes layout; maybe cross-jump makes it identical? Try.

Let me test e5 (inverted condition with swapped bodies) — the target's layout might be reproduced by jump optimization.
