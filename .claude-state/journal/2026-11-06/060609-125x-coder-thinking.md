---
ts: 2026-11-06T13:06:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3T4lPgmdDFxGrYV57jeE
---
Still 2. The li/addiu order is stubborn — a sched1 wall.

Time: 06:06. Item 3 at 14 min. Tries: 48 + u1-u4 (4) + v1,v3,v4 (3) + w1-w4 (4) = ~59. Time ≥ 20 min? Not yet (14 min). Hmm, the wall rule wants ≥20 min. Let me spend 6 more minutes trying, then record.

Ideas left for the li/addiu:
- Change `c36`'s type (u32) → `li v0,36` same.
- Make `dp` a `s32 *` vs `u8 *`: `dp = dp + 1` with s32* = +4.
- Try `dp = dp + 1;` placed between `tmp = tmp << 4;` and `ba = ...` (current) vs before `df` (s1: 2).
- Try `dcount = *dp;` AFTER `c36 = 0x24;` (r2: 2).

What about making the load `lw` come from a different pointer so that the lw and addiu are not adjacent? e.g. `dcount = D_80127548[0];` (m-style): then `la`+`lw`, no dp use... but dp is still needed for ba: `dp = D_80127548 + 1; ba = (u16*)(tmp + (u8*)dp);`. Hmm! That's a real C change: `dp` computed as the base+1 directly. Then the addiu becomes part of the la/addu. The target has `la a0,D_80127548; lw v1,0(a0); li v0,36; addiu a0,a0,4`. If dp were `D_80127548 + 1`, the addiu would still be needed (la + 4).

Let me try: `dcount = D_80127548[0]; dp = D_80127548 + 1;` — hmm, that changes the load to `la a0; lw v1,0(a0)` still, and dp = la + 4.

Actually that's the same code. The order might differ.

Another idea: make `c36`'s li emitted *later* in the RTL: currently `c36 = 0x24;` is before `df`. What if `c36` is assigned inside the df expression... can't.

What if I use `df = 0x24 - dcount;` (s2: 2) — same.

Hmm, what if the constant is 36 decimal vs 0x24 hex? Same.

Let me try one thing: the target's `li v0,36` — v0 = $2. In mine, `li v0,36` too. So the register is right; only the position differs.

Let me try making `dcount` load later: `df = c36 - dcount;` where `dcount` is loaded via a temp:
```
s32 dc = *dp;   → hmm
```

Honestly, let me try the `dp = D_80127548 + 1` shape (x1) and `dcount = D_80127548[0]` (x2), then stop.

Actually, a cleaner idea: what if the `lw` and the `li` are forced adjacent by making the addiu depend on the li? E.g. `ba = (u16 *)((tmp + (u8 *)dp) + 0);`... no.

Let me just do x1/x2 and then write up the WALL.
