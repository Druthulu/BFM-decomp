---
ts: 2026-11-06T11:02:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_U0S68tQgvasJo7RrFber
---
Now I see:
- fdc: `beqz v0, ff8` with the delay slot `addiu v0,s1,1` at fe0. The branch target ff8 is `move s1,v0`. Hmm, the delay slot has `addiu v0,s1,1` which is also at ff4 (after the call). So reorg copied the addiu into the delay slot from... ff4 is the fall-through path. Actually the delay slot at fe0 is `addiu v0,s1,1`, and at ff4 the same insn appears. So it's a copy from the fall-through (the "duplicated addiu" the comment mentions).

The comment says: with the asm fence, "the `beqz` slot is filled from the branch TARGET instead — the duplicated `addiu $v0,$s1,1` the target has in both the delay slot and after the call". Hmm, whatever.

So the target has the addiu in the delay slot at fe0 and again at ff4.

Without the fence, reorg fills the slot differently (my base has `beqz v0,ff0` and no addiu in the slot? Actually mine has `beqz v0,ff0` with the target address ff0 instead of ff8 — a different branch target).

Hmm, wait: mine's beqz target is ff0 (vs target ff8). That means in mine, the `addiu v0,s1,1` (at ff4 in the target) is at ff0, i.e., the insn order differs: in mine, after the call: move s0,v0; addiu v0,s1,1; move s1,v0? Let me dump mine.

This is deep reorg territory. The wall tag `dbr-delay-fill` fits.

Given the time, let me try the obvious real-C moves for lever 5 (the loop if-body) and lever 3/4, then record a wall if they don't work.

Lever 5 replacement ideas:
- Wrap the if-body in a do-while.
- Change the loop shape (e.g., `for` instead of do-while).
- Move the `i++` inside the if.
- Use a `goto` structure.

Lever 3/4 replacement ideas:
- restructure the if/else to a ternary or a shared n=3.

Let me generate ~10 variants and score them. Time is short (maybe 20 min left in a reasonable session). Let me do it.

Variants (from base or v_sa):
1. v_sa (5).
2. v_sa + `n = 3;` before the if (restructure).
3. v_sa + ternary n.
4. v_sa + do-while around the if-body (lever 5).
5. v_sa + do-while around both n=3 sites.
6. v_sa + `for (i = 0; i < cnt; i++)` loop.
7. v_sa + `if (n != 0)` removed / `while (i < cnt)`.
8. v_sa + `i++` before the call.
9. v_sa + the if-body as `if (D_80115158[i].h) {...}`.
10. v_sa + `w++` moved.

Let me write a generator.

Actually, the C currently is:
```
i = 0;
if (n != 0) {
    cnt = n;
    do {
        if (D_80115158[i].h != 0) {
            __asm__("");
            ot = call(ot, w, i);
        }
        i++;
        w++;
    } while (i < cnt);
}
```
Lever 5 was `__asm__("")` at the head of the if-body. Without it, the delay slot fill differs.

Let me try: `do { if (...) { do {} while(0); ot = call(...); } ... }`. Hmm, `do{}while(0)` as a statement before the call.

Let me test a batch.
