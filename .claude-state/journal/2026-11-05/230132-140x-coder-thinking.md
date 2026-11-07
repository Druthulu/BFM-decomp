---
ts: 2026-11-06T06:01:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_05Vrs2IyTmsaOgrvMSec
---
Item 5: func_8017EF9C, kinds launder,pin. Two pins ($16 s0, $3 v1) and one launder (pa0).

I'll handle it after item 4. Let me get back to item 4 and finish the wall budget. Time now ~23:02.

Let me do a few more experiments on item 4 (until ~23:11), then write up.

Let me try some more ideas:
- The `one` variable: what if it's a *parameter-like* value from the stack? no.
- What if we use `!= 1` and `== 1` with the literal (no variable)? The pin made `one` a variable. Without it, gcc uses `li`.

Hmm, what if `one` is not needed as a variable at all and the target's `li s2,1` comes from... the pin forces it. So without the pin, `li` would be a temp.

Let me try the item-4 k10 body with `one` replaced by the literal 1 everywhere (no variable) — the target has `li s2,1` once and uses s2 in 3 comparisons. With a literal, gcc would emit `li v0,1` or use `addiu`? Hmm, comparing to 1: `bne s1,1` isn't a valid MIPS insn (needs a register) → `li at,1; bne`. Same.

Let me try it: replace `one` with `1` in k10 (remove the variable).

Also try: declare `one` as `s32 one = 1;` at the top (m1 = 11).

Let me run a couple.

Actually, let me try to think about what the *decomp's* original source (before the pins were added) looked like. The pins were added by a previous phase to make it match. The comments explain. So a lever-free body may simply not exist for this item.

Let me spend the remaining time trying ~8 more variants and then write the WALL.

Variants:
x1: literal 1 instead of `one`.
x2: `one` as `s32 one; one = 1;` placed after the cc assignment (m2 = 11).
x3: the first test `if (cc != 1)` and the second `if (cc == 1)` (no variable).
x4: k10 with the mask `(cc & 0xFFFF)` but cc declared `u16`.
x5: the second test `if (cc == one) { goto rejoin; }` with the first test `if (cc != one) { goto second; }` — the source as-is but with `goto` labels renamed? no.

Let me run x1/x3/x4 and a couple more.
