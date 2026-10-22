---
ts: 2026-10-22T13:07:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_2xhvt6kYo8DHYv7w8ZN2
---
SVECTOR = { short vx, vy, vz, pad; } → s16 fields. So `out.vx` is a SIGNED short → the load is `lh` (sign-extended).

But the TARGET has `lhu s2,26(sp)`! So the target loads it as UNSIGNED. Hmm! How?

**AH: if the destination variable is UNSIGNED (u16), the load is `lhu`?** Hmm, no: the load's signedness is determined by the SOURCE type (s16 → `lh`). But GCC has an optimization: if the loaded value is only used as unsigned, it can use `lhu` (the sign extension is unnecessary). YES! GCC's "LHI" / load-extension optimization: GCC 2.7's `mips` has a "zero_extend" optimization? Hmm, more generally: GCC's RTL would be (set (reg) (sign_extend (mem))) hmm.

Actually: `ay = out.vx;` with ay as s16 → (set ay16 (mem)) — the load is `lh` (sign-extending into a 32-bit reg, then the value is used as 16-bit).

With ay as u16 → (set ay16 (mem)) — same! The load's signedness is the same (lh) since the MEM is s16.

Hmm, but GCC's mips backend: a load of a s16 MEM into a reg → `lh`. To get `lhu`, the MEM must be a zero_extend of a QImode mem or an unsigned MEM.

Hmm! So the target's `lhu` means the source was loaded as UNSIGNED 16-bit → i.e., the ORIGINAL source read it as u16! E.g. the original might have had `u16 vx` or the struct's field was u16 in the original game source.

Hmm, but the current source compiles to the target exactly (score 0) — with `s16 ay = out.vx`?? Hmm, wait: the current source has `ay = out.vx;` where ay is s16 → `lh`?? But the current source matches the target (lhu)!

Hmm, so in the current source, the load must be `lhu`. How? Because of the LAUNDERS! The launder on ax/by... hmm, no.

Hmm, wait. Let me re-read the current source:
```c
        bx = out.vy;                                         /* $s2 = out.vy (load) */
        ay = out.vx;                                         /* $s1 = out.vx (load) */
```
Hmm, `out.vy` is `short` → the load is `lh`. But the target has `lhu`!

Unless... GCC's mips backend loads a 16-bit signed value with `lh` — hmm, but the target has `lhu`.

Hmm, so how does the current source produce `lhu`? Let me check the actual difference: in the diff, mine[63] = `lh s2,26(sp)` vs target[63] = `lhu s2,26(sp)`. And my g1 changed ay/bx to u32. So with u32 the load became `lh`?! And with s16 (the original) it's `lhu`?

That's backwards from my expectation... unless GCC's rule is: when the loaded value is used as a SIGNED 16-bit value, it must be sign-extended → `lh`; when used as UNSIGNED, it can be `lhu` (zero-extended) — but the MEM is s16, so `lhu` would be wrong for a negative value... unless GCC knows the value is non-negative.

Hmm! Actually GCC's mips has an optimization: `LHI`/`zero_extend` — hmm, in GCC 2.7's mips.md there's an insn "LHI" (load halfword into a register, sign-extended? or "LH"?). Hmm, and there's the "mips_load_zero_extend"? Hmm.

Whatever the mechanism: with ay/bx as s16 (the original), the loads are `lhu` ✓ (matching the target). With ay/bx as u32, they became `lh` ✗ (because the u32 conversion needs a sign extension of the s16 field).

So: **ax/ay/bx must stay s16** (to keep the lhu loads) — but then the (u16)/(s16) casts are no-ops.

Hmm! But g1 (u32) scored 6 with the lhu→lh difference being 2 of the 6 mismatches. So if I could keep the s16 loads AND get the 2nd sets...

Hmm, what if only ax and by become u32 (not ay/bx)? Then:
- ay = out.vx → ay stays s16 → `lhu` ✓
- bx = out.vy → s16 → `lhu` ✓
- ax = ay + 0x7B → ax as u32 → the add is 32-bit ✓ (the same addiu)
- by = bx - 0x5D → by as u32 ✓
- the 2nd sets: ax = (u16)ax → the andi ✗ (an extra insn)

Hmm, the andi. Let me test: ax/by as u32, ay/bx as s16, with the (u16) 2nd sets.

And to avoid the andi: hmm, what if the 2nd set is a *truncation* that GCC does for free? On MIPS, a truncation from 32 to 16 bits is FREE (the value stays in the register; the high bits are ignored when used as 16-bit). So `ax = (s16)ax;` with ax as u32: the truncation to s16 → the RTL: (set ax16 (subreg:HI ax32)) → GCC's combine would keep ax32 and use the low half → FREE (no instruction) ✓✓✓!

But then the VALUE of ax (as s16) differs from the u32 value (sign vs zero extension) — for the values involved (coordinates), the sign extension is what the original does ✓ (the target's stores are `sh` → the low 16 bits ✓ — the same either way!).

Hmm, but GCC's RTL for `ax = (s16)ax` (ax as u32): the assignment truncates → (set (reg ax HI) (subreg HI (reg ax SI))) → and then the uses of ax (as u32) would need a zero-extension back ✗ (an andi). Hmm, but if ax is declared u32 and we only ever use its low 16 bits (the stores), GCC's "narrowing" optimization keeps the 32-bit value and uses the low half at the store ✓ FREE.

Hmm, but the 2nd set's value: after `ax = (s16)ax`, the value of ax (as u32) = the zero-extended (s16) value — which differs from the original if the value is negative! Hmm, but semantically the stores only use the low 16 bits ✓ — but GCC would still need to model the truncation... With the "narrowing" optimization, GCC keeps the 32-bit reg and just uses the low half for the store → the RTL after combine: the truncation disappears → the 2nd set is folded away → back to 1 set ✗?!

Hmm, but v7 (s32 + (s16)) gave 4 EXTRA instructions (the sign extensions) — so GCC did NOT fold them away (it emitted sll/sra). So the (s16) cast on an s32 costs 2 insns ✗.

And (u16) on a u32 costs 1 insn (andi) ✗.

Hmm! So I need a 2nd set that costs 0 instructions.

**WHAT ABOUT: `ax = (u16)(ax & 0xffff)` — same andi ✗.

**WHAT ABOUT making the 2nd set a *copy* from a 16-bit variable? Hmm.

**WHAT ABOUT: the 2nd set on a variable whose value is used only in 16-bit contexts, so that the truncation is free?** E.g. if `ax` is declared u16 and the 2nd set is `ax = (u16)ax;` → no-op ✗ (folded).

Hmm! **WHAT IF THE 2ND SET IS ON A *WIDER* VARIABLE WHOSE VALUE IS ONLY USED IN 16-BIT CONTEXTS?** E.g. `by` declared u32: `by = (u16)by;` → the andi. Hmm, unless GCC's "narrowing" optimization applies: the truncation to u16 then the uses (the store `sh`) → GCC's combine: the value is used only as 16 bits → the truncation is free → but then the 2nd set's RTL... hmm, if the truncation is free, GCC might keep the 32-bit value and the "set" becomes a no-op → the set count might drop ✗.

Hmm, but empirically g1 (u32 + (u16)) gave 6 with an andi present → so the andi was NOT optimized away (the value IS used in 32-bit contexts? by is used in `prim.y0 = by` (a 16-bit store) and... hmm, `by` is also used in `prim.y0 = by` only. Hmm, so why the andi?

Because the zero-extension result is used... hmm, the andi at mine[85] — hmm.

OK, let me just try more variants empirically:
- h1: ay/bx stay s16; ax/by become u32; the 2nd sets (u16).
- h2: ay/bx stay s16; ax/by become u32; the 2nd sets (s16).
- h3: ay/bx stay s16; ax/by u16; the 2nd sets (u16) [= no-op].
- h4: ax/ay/bx u32 + by u32 with the 2nd sets (u16) [= g1] but the stores cast to (s16).
- h5: g1 but with the 2nd sets as `ax = ax & 0xffff` [= g4, 6].
- h6: g1 but only ax/by u32 (ay/bx s16) with (u16).
- h7: like g1 but with `by = (u16)by;` replaced by `by = by;` hmm.

Let me also think about the SCHEDULING difference (the addiu s1,s1,117 placement) — that might be fixed by the type changes.

Let me run h1, h2, h6 and a couple more.
