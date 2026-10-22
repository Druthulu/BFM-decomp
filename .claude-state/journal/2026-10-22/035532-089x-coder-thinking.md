---
ts: 2026-10-22T09:55:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_aqnvFY3MKHKPZmloaRRx
---
This is a different (older) gcc; the constant-substitution rule for a local's initializer is likely in the FRONT END (c-decl.c / c-typeck.c) or in `expand_assign`.

Let me search this expr.c for where a local's constant initializer is folded into uses: search for "DECL_INITIAL" with "constant" and "expand" in c-decl.c.

Actually, in old gcc, `expand_start_stmt`/`expand_end_stmt` — hmm.

Let me search c-decl.c (front end) for the folding of a constant initializer into uses: the classic is in `c-decl.c`'s `expand_init`? Hmm.

Honestly, a faster empirical route: test whether a `static` local or a *global* variable behaves differently, or whether the substitution depends on the number of uses...

Actually! NEW IDEA: what if the substitution happens because the variable's DECL_INITIAL is a constant and the front end replaces the variable's RTL with the constant? In gcc 2.7's c-decl.c, there's the "fold" of a variable with a constant initializer into a "constant" — hmm, that's for `static`.

Hmm, what if the variable were declared `static`? Then it'd live in memory → a load. No.

OK, I need to move on. Item 1 = WALL (best 1).

Hmm, but wait. Before I close it: since the score is 1 (ONE instruction), maybe I can find a *PARTIAL*: the brief allows PARTIAL:<kinds still kept> — "win.c scores 0 keeping only those levers". But the row kind here is "launder" — a PARTIAL would mean keeping the launder lever (i.e. the orig with the asm) — that scores 0 but keeps the lever → not a crack. Hmm, PARTIAL is for when only SOME of the row's kinds are cracked. Here the only kind is "launder" — so a PARTIAL would mean "launder" is still kept → that's the orig (score 0 with the lever) — that's not progress. So for this item: WALL.

Hmm, wait. Actually, let me re-read: "result MATCH (win.c scores 0) | PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers) | WALL (best = lowest score of a lever-free body)". So PARTIAL means the body scores 0 but keeps some of the row's kinds (levers). Since the row kind is "launder" and the only lever is the launder asm — a PARTIAL here would be the original body with the launder = score 0 keeping launder. That's a legitimate PARTIAL row: "PARTIAL:launder" (the original scores 0 but keeps the launder). Hmm, but that's not "progress" — it's the baseline.

Hmm, but the notes say the levers under OTHER kinds (pins) may stay. In this item, are there other kinds? kinds file says "launder" only. The orig.c for 80184828 has just the launder asm (no pins). So the lever-free body = the base with the asm removed = score 1.

Hmm, so the row is: WALL, best 1, wall tag combine-commutative-swap (or my refined tag).

Hmm, but hold on! Since the target's asm has the pointer in a1 with the symbol materialized — the LAUNDER is what produces it. The row's kind is "launder" → so cracking means removing the launder and still scoring 0. Not achieved → WALL.

Let me now be efficient with the remaining 4 items. Time check: ~1h40 spent. Let me allocate ~20-25 min per remaining item.

Let me start with item 8018483C (best 5, missing "move s0,v0") — the launder there keeps a pointer copy. Notes: the target materializes &D_800B99DC into $v0 and then copies it to $s0 (`move s0,v0`), while a plain `p = &D_800B99DC` is coalesced into $s0.

Mechanism: cse forwards the reg_equiv of a CONST address pseudo, so the copy is coalesced away.

To crack: make the address a REG at the copy point. The launder `__asm__("" : "=r"(pb) : "0"(pb)); p = pb;` forces pb into a register.

Lever-free idea: hmm, the target's asm:
```
lui  v0,%hi(D_800B99DC)
addiu v0,v0,%lo(D_800B99DC)
move s0,v0
```
So the address is materialized into v0 and then copied to s0 (a callee-saved reg, since p is live across the call).

Our version: `lui s0,%hi; addiu s0,s0,%lo` (materialized directly into s0).

To get the copy, the address must be in a reg (v0) and then copied to s0. In gcc, this happens when the value is computed into a temp reg and then copied — e.g. when the source is a non-constant reg.

Hmm, in the notes: "The zero-byte re-tie fence (cookbook §34) keeps the two pseudos apart" — the orig.c comment mentions a "zero-byte re-tie fence" — but the orig.c doesn't show it? Let me re-read the orig.c for 8018483C:

```c
    {
        u16 *pb = &D_800B99DC;
        __asm__("" : "=r"(pb) : "0"(pb));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus10)
        p = pb;
    }
```
So the lever is the asm.

The mechanism: `p = &D_800B99DC` where p is used across a call → p is in s0 (callee-saved). The address is materialized directly into s0 (lui s0; addiu s0). The target has it in v0 then copied to s0.

For the copy to survive, the address value must be in a REG when the copy happens — i.e. the source must be a non-constant reg. So we need the address to be computed into a temp reg (v0) and then copied. That's what happens if the source of the copy is a *variable* whose value is the address but is not constant-foldable... e.g. if the address came from a load or a function call.

Hmm, but the target materializes it with lui/addiu — a constant address. So the source must be a reg holding the constant, i.e. a pseudo that holds the constant address and is copied to p. In gcc, `p = pb` where pb is a local holding the constant → the copy gets coalesced (cse forwards the reg_equiv).

Hmm, so how does the target have the copy? Because in the ORIGINAL source, the address was probably loaded from a *table* or computed...

Hmm, wait: maybe in the original source the pointer came from a different expression entirely. Let me look at the full function and the target asm.

Let me look at the target's asm for func_8018483C around the beginning.

Given my time budget, let me be pragmatic: for each remaining item, I'll do a couple of batches of variants informed by the mechanism, then record the wall.

Let me now work on item 8018483C.

First, read the def and the target asm.
