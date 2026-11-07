---
ts: 2026-11-06T10:36:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6xeqIBT5V2011kmDPrKx
---
r8 (single-expression `(div << 16) >> 16`) = 2, same as r1. The two-statement forms (r5/r6/r7) shift the bank.

So the in-place shift via two statements always shifts the bank because the temp disappears and v1 frees.

Hmm. What if I keep the temp but make it s0? Let me think again about the temp's allocation. The temp is a local qty. local-alloc: it gets the first free reg in reg_alloc_order for its live range. At the temp's live range (positions 14-18), the live regs are: v0 (ang), s1 (a), s0 (div), and possibly others. v1, a0-a3 free.

Unless... I can make the temp's live range overlap a hard reg that's busy. Hmm.

What if `cur` is computed BEFORE the div sign-ext? Then cur would be live during the temp's range, occupying v1? No, cur would take v1 itself.

Hmm.

OK, alternative: what if I make the div sign-ext use a `s16` variable that forces the load's sign extension? E.g., if the divisor were loaded as s16... no.

Let me reconsider: the target's in-place sll/sra means the temp was allocated to s0. Since the temp is local and s0 is callee-saved, the only way is if local-alloc ran out of caller-saved regs. OR if the temp was tied to div (s0) via a copy preference.

Actually — combine_regs! For `(set (reg div) (ashiftrt (reg temp) 16))`: ureg=temp, sreg=div. temp dies here (REG_DEAD). If div has a qty (global, reg_qty=-1), the code path `if (reg_qty[sreg] >= -1) return 0` — for a global sreg, reg_qty = -1 → return 0. So no tie.

BUT: what if div is LOCAL (reg_qty >= 0)? Then combine_regs would tie temp to div. div is global (used in multiple blocks). Can't.

Hmm.

What if the temp is tied to a local div? If I split div into div_local (block 0) and div_global (used in the divisions)... the sign-ext of div_local would tie to a local div, and the temp would get div_local's register. But div_local would be s0? div_local is local and crosses the call → gets s0 (if it's the only local-crossing qty). Then the temp ties to div_local → s0 → in-place! And div_global (the sign-extended value) would be global.

Wait, this is the "separate dd" idea (s1). Let me reconsider with the do-while structure:
```
s32 d0;   // raw arg3, local
s32 div;  // sign-extended, global
d0 = arg3;
ang = ...;
div = (s16)d0;   // sign-ext of d0
a = a & 0xFFF;
cur = ang & 0xFFF;
...
q = diff / div;
```
- d0: local, born at prologue, dies at the sign-ext (block 0), crosses the call. local-alloc gives it s0 (only local-crossing qty). refs 2, live ~20.
- div: global, born at the sign-ext, used in the divisions.
- The sign-ext temp: combine_regs ties it to d0 (local, dies at the sign-ext)? For `(set temp (ashift d0 16))`: ureg=d0, sreg=temp. d0 doesn't die here. For `(set div (ashiftrt temp 16))`: ureg=temp (dies), sreg=div (global) → no tie.

Hmm, the temp would still get v1.

Unless the extendhisi2 temp is created and immediately used... hmm.

OK, let me try the separate-variable approach empirically with the do-while:
- r9: r1 with d0/div split.

Also, let me try making the sign-ext of a `s16` variable (which might use a different pattern).

Let me test r9.

Actually, s1 (separate dd) scored 27 without the do-whiles. Let me combine with r1's do-whiles.

Let me create r9.
