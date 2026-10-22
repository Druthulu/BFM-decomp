---
ts: 2026-10-21T23:58:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_1bIt8jSVpHoW6BHtF8DD
---
Item: func_8017DA30, kinds = launder. The launder is:
```
__asm__ __volatile__("" : "=r"(q), "=r"(p), "=r"(e) : "0"(q), "1"(p), "2"(e));  // !FAKE: launder — REFUSED launder with 3 outputs
```
3 outputs. And there are pins ($16 ent, $4 q) — the pin is a DIFFERENT row kind (not in this row's kinds), so pins may stay ("levers of other kinds the def already had (pins under other causes) may stay, never added").

Target:
```
9 lui a1,0x0 ; HI16 D_800D387C
10 addiu a1,a1,0
...
18 lui a2,0x0 ; HI16 D_800D3888
19 addiu a2,a2,0
```
and
```
31 lui a1,0x0 ; HI16 D_801817A4
32 addiu a1,a2? no: addiu a1,a1,0
38 lui a2,0x0 ; HI16 D_801817B0
39 addiu a2,a2,0
```
So the constants are materialized into a1/a2 directly (the call args). The launder forces the values into registers (a1, a2) so the call args are set up in the right regs.

Without the launder: `func_8001CC3C(sub, (s32)D_800D387C, 0, 0);` — the constant (s32)D_800D387C would be materialized with `li v0, ...` (a 32-bit constant → lui+ori) and moved to a1 → different insns!

The target has `lui a1; addiu a1,a1,0` — the HI16/LO16 reloc form. gcc emits that when the value is a symbol address (not a plain constant). `(s32)D_800D387C` — the cast to s32 of a symbol address: on a 32-bit target, the cast is a no-op → the address stays a symbol → `lui a1; addiu a1,a1,0` ✓. Hmm, so maybe the launder isn't needed for that.

But the 3-output launder forces q, p, e into registers: q → a0 (the call's first arg), p → a1, e → a2. Without it, gcc would set up the args in some order and might use different regs or materialize the constants differently.

Let me just try: remove the launder (keep the pins) and score. The def with the launder removed:

```
    } else {
        register s32 q __asm__("$4");
        s32 p;
        s32 e;
        func_8001CC3C(sub, (s32)D_801817A4, 0, 0);
        q = sub;
        p = (s32)((u8 *)ent + 0x24);
        e = (s32)D_801817B0;
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
        func_80128EA8(q, p, e);
        hw = 0x1C;
    }
```
Let me score that. Let me set up the item dir (tu, fn, kinds exist?) and write the candidate.

Let me check the item dir first, and write the candidate in one go.

The item dir: func_8017DA30__ov_SC02_004_jr_8017AE2C. Let me check it has tu/fn/kinds/orig.c.

Let me write the candidate (v1) and score.
