---
ts: 2026-11-06T10:13:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GYcj2MruljoPfObvfImt
---
03:13, started 02:54 → ~20 min elapsed total. I have time.

Item 4 dir is 23M due to dumps. I should delete the dumps once read (per constraints). I've read what I need; let me keep for now or delete. Let me delete the dumps dirs after I'm done with item 4 analysis. Actually I may still want them. I'll delete before finishing.

Let me try item 1 with keepalive-only + real-C folds.

For item 1, the source:
```
void func_8017F1F0(s32 a0, s32 a1)
{
    extern s32 D_801EEAEC[];
    s32 rv;
    s32 x = D_801EEAEC[0];
    s32 y = a1;
    s32 d;

    if (y < a0) {
        if (x < y) { x = x + 0x5A0; }
        y = y + 0x5A0;
    }
    if (a0 >= x) { rv = -1; goto done; }
    if (x >= y) { rv = -1; goto done; }
    d = x - a0;
    if (d < 16) { rv = d * 2; goto done; }
    d = y - x;
    if (d < 16) { rv = d * 2; goto done; }
    rv = 31;
done:
    keepalive(rv);
}
```

Target: rv in v0, x in v1.

Variants:
- `if (a0 >= x || x >= y) { rv = -1; goto done; }`
- Move rv decl to top.
- Reorder d assignments.
- Use `else`.

Let me generate and score with keepalive kept.

Actually, more importantly: maybe I should first verify whether the keepalive is even needed if the pin is present... yes orig = 0.

Hmm, let me think about what the *ideal* PARTIAL is: the fewest levers that still score 0. Both pin+keepalive are needed (we verified keepalive-only = 6, pin-only would be 15 since dead). So PARTIAL:keepalive,pin.

Given that, spending time trying to make keepalive-only score 0 for item 1 is worthwhile only if it works. Let me try a handful of variants.

Actually, wait. What if we use the `$2` pin but drop the keepalive, and instead make rv live via... no.

Hmm, what if the *pin* itself keeps the variable live? Let me test: pin kept, keepalive removed → score? The pin makes rv a hard reg; without a use, flow deletes the dead sets. Let me verify quickly. Actually the original w1 (no pin, no keepalive) = 15. Pin-only: probably 15 too (dead).

Let me test pin-only for item 1 (and item 2, 3). This determines the minimal lever set.

Let me run a batch.
