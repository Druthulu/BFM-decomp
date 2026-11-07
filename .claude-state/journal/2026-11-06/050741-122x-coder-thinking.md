---
ts: 2026-11-06T12:07:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pGsvF45IBn8OZrbIMXrM
---
Best lever-free is still 38 (w3/c3), 191 ins.

Hmm, wait — w3 = 38 with 191 ins; c3 = 38 with 191 ins. Let me check if some variant gets lower. Let me try a couple more:
- c4: base assignment + arr for later accesses + barrier removed.

Actually z1 (arr for base accesses) = 30 with the barrier kept. Combined with the barrier removed → let me try.

Let me also try: keep the launder but remove the barrier, then find a real-C way to make base stay in a register.

Hmm, I realize I haven't tried the *dead-reset* C0414 trick on the launder here. The launder is `base = <same value>`. A C0414 dead reset would be `base = 0;` AFTER the last use of base. That doesn't help (base is used throughout).

What about `arr = 0;` after the slot computation? That would empty arr's class.

Hmm.

Actually — maybe the right real-C move for the launder: since the launder forces base into a register, use `base` in an expression that can't be rematerialized, e.g. pass `base` to a function that takes it as a pointer... it's used in loads only.

What about `slot = (u32 *)(param_1 * 4 + (s32)base - 0x48);` — keeping the `- 0x48` inside. Then arr is only used for... hmm.

Let me try a few more and then settle. Time: it's 05:06-ish. Let me do 4 more tries.

Actually, let me reconsider the problem: maybe the launder's effect can be achieved by *making base's address computation depend on a variable*. What if:

```
base = (u8 *)&D_8011F7F0;
```
and then at the first use: `*(u16 *)(base - 0x34)`.

What if I write `base = (u8 *)&D_8011F7F0;` and then `arr = base - 0x48; slot = (u32 *)(param_1 * 4 + (s32)arr);` and later use `(u8*)((s32)slot - param_1*4 + 0x48 - 0x34)`? Ugly.

Let me instead check whether the target's base register s2 is used because of the *launder* or because of the surrounding structure. In w1, base is rematerialized as `lui a3` + `lhu a3,-52(a3)`. In the target, `lhu a3,-52(s2)`.

The rematerialization happens because base's value is a known constant at the use point. gcc's cse/regmove does this.

Real C: make base not a known constant. E.g., `base = (u8 *)((s32)&D_8011F7F0);` — the cast is a no-op; still constant.

What if base is loaded from a *pointer* that's assigned the constant? `u8 **pp = &base;` no.

Hmm, what about making `base` an argument of an inline function? no.

OK. Let me try one thing: the `volatile` qualifier on the pointer declaration: `volatile u8 *base;` — the loads become volatile; that might change code (volatile loads are not cse'd/rematerialized). Let me test (it's a new lever, but let me see the score for information).

Actually no — that's a lever. Skip.

Let me finalize item 4 as WALL best 38. I need ≥30 tries for a WALL. I have:
w1,w2,w3 (3), y1,y2,y3 (6), y5,y6 (8), z1,z2,z3 (11), c1,c2,c3 (14). Plus orig? No.

I need ~16 more scored tries. Let me generate a batch of lever-free permutations to (a) reach 30 tries and (b) possibly find a better score.

Let me generate 16 variants of w3 (both levers gone) with:
- base assignment forms
- statement order changes
- the index expression forms
- declaration order changes

Let me do a batch of 8 first, then 8 more.

Actually, let me be smart: the best score is 38 with 191 ins (3 extra). The 3 extra come from the base rematerialization (lui+lhu per use, 4 sites → +3 or so) and the barrier ordering.

Let me try:
- d1: `base = (u8 *)&D_8011F7F0;` but declare base as `u8 *base` — already.
- d2: use `(u8*)&D_8011F7F0` directly in the later expressions (no base variable at all):
  `*(u16 *)((u8*)&D_8011F7F0 - 0x34)` — the compiler would use lui+addiu each time (rematerialize). Same as w1.
- d3: keep base but compute it via a variable: `u32 b = (u32)&D_8011F7F0; base = (u8*)b;` — b is a constant, folds.

Hmm.

Let me try `slot`-derived base:
```
arr = (u8 *)&D_8011F7F0 - 0x48;
slot = (u32 *)(param_1 * 4 + (s32)arr);
...
```
and use `base` nowhere; replace `*(u16*)(base-0x34)` with `*(u16*)((u8*)slot - param_1*4 + 0x14)`. Hmm, that's a different computation (would use slot's register + param_1*4). Probably worse.

Let me just generate 16 quick variants and score them, to satisfy the WALL requirement and maybe find a better best.

Actually, the tries count is "scored tries on that item" — I can count each sc.sh line. Let me generate 16 variants systematically: vary (a) the base expression, (b) the barrier replacement, (c) statement order.

Let me do it.
