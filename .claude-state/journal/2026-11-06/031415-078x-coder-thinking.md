---
ts: 2026-11-06T10:14:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HH9e2vHnU0f7V60ETU81
---
Interesting! Item 3 pin-only = 3 (39 vs 41). So for item 3, the pins alone keep most of the code (obj and chn pins matter), but rv is dead (missing 2 ins: li v0,0 and maybe something).

So item 3: pin-only = 3; keepalive-only = 27; both = 0.

Hmm. So both needed.

OK. Now, for items 1 and 2, pin-only = 15/23 (rv dead).

So the keepalive is the essential lever for the value; the pin steers.

Now — the key question remains: can we make rv/v0 live with real C? No.

Therefore items 1-3 → PARTIAL:keepalive,pin.

BUT WAIT. Hold on. What about item 3? There, the else branch is `rv = 0;` — and the target has `move v0,zero` at the end. What if the else branch could be written as a real `return`? No (void).

Hmm, what if... the function `func_801803D0` could be restructured so that the else branch's `rv = 0` is the *result of the last expression*? No.

OK, let me now consider: maybe the intended result for these items is indeed PARTIAL. Let me look at the moves.md for the shard's siblings: the shard G26x is listed in the brief as "singleton crack shard". The result format includes PARTIAL and WALL, so it's fine.

Let me now also try to improve item 3's PARTIAL: can we drop the $2 pin on rv but keep the keepalive and the obj/chn pins? Then levers kept = pin (obj $2, chn $3) + keepalive → PARTIAL:keepalive,pin anyway (kinds are the same). The result string only lists kinds, not which sites. So no benefit.

Could we drop the obj $2 pin and chn $3 pin and keep only rv's $2 pin + keepalive? Still PARTIAL:keepalive,pin.

OK so the result for 1-3 is PARTIAL:keepalive,pin with win.c = orig (score 0).

Hmm, but hold on — maybe I should double-check whether a *different real-C body* could score 0 with only the keepalive (no pin) for items 1-3. That would be PARTIAL:keepalive (a strictly better result). For item 1, keepalive-only = 6 (rv in v1). Let me try some real-C moves to steer rv to v0.

Let me look at the alloc table for item 1 wk (keepalive-only) to understand.

Actually, let me do it: dump item 1's wk.

Actually, a cheaper experiment: try variants of item 1 with the keepalive kept:
- rv decl first.
- `||` folds.
- different branch structure.

Let me generate ~10 variants and score.

Let me write gen1.py for item 1.

The function:
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
    keepalive
}
```

Variants:
1. decl order: rv before x.
2. fold the two rv=-1 tests with ||: `if (a0 >= x || x >= y) { rv = -1; goto done; }`
3. `if (a0 >= x) { rv = -1; } else if (x >= y) { rv = -1; } else { ... }` — restructure.
4. Use `d = x - a0; if (d < 16) rv = d*2; else { d = y-x; if (d<16) rv=d*2; else rv=31; }` with a single goto.
5. `rv = (a0 >= x) ? -1 : ...` nested ternary.
6. Use `s32 d = x - a0;` etc.
7. Swap the order of the two d checks.
8. `if (d >= 16) { d = y - x; ... }`.

Hmm, but the target's codegen is known (the current orig matches exactly). Any restructure risks changing the instruction sequence. The residual is only the register. So I need a variant that keeps the exact instruction sequence but changes allocation. Statement-order changes might change the instruction order. Risky but worth trying.

Actually, the cleanest lever for register allocation in these cases: declaration order and the *order of first assignment*. Let me try decl order first.

Let me generate.
