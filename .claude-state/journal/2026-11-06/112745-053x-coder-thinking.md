---
ts: 2026-11-06T18:27:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Tr6SryTdKBfVq4a9XCwT
---
The condition: `else if (! ((obey_regdecls && !DECL_REGISTER(parm) && !DECL_INLINE(fndecl)) || TREE_ADDRESSABLE(parm) || ...))` → put the parm in a pseudo. So if `TREE_ADDRESSABLE(parm)` (address taken), it uses the stack, not a pseudo. Not helpful.

The pseudo is always made for a normal param. So the prologue copy always exists.

OK — item 3 is a WALL: global-alloc merges the parameter copy's $4 preference into the load result via expand_preferences at the REG_DEAD, and no real-C spelling of the body removes it (32 tries). Evidence: gcc-2.7.2/global.c expand_preferences (line 777) + find_reg pref override (line ~1010); the .greg dump shows "76 preferences: 4" and order 75 76 72 74.

Let me record it and move on. Time 11:28. Item 3: 17 min, 32 tries. Hmm, the WALL requirement is ≥20 min and ≥30 tries. Let me spend 3 more minutes on one more idea, or just accept ~17 min... The brief says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I should make it to 20 min. Let me spend the next 3 minutes on a couple more tries, then record.

Extra ideas:
- w12: `if (v0 < a1) { ... } else { if (v0 < a2) ... }` with the arms swapped (w4 did this) — done.
- w13: make v1 s32 but load via `*(s32 *)((char *)a0 + 0xCC)`.
- w14: add a `s32 pad;` dead variable? no.
- w15: `v1 = ((Unkstruct*)a0)->unkCC; v0 = 1;` vs target li first — the sweep covered.
- w16: use `while` loop? no.

Let me try the "base temp in block 0" idea (extra insn, but let's see if combine folds it) — if it scores 1 (one extra insn) it tells us the mechanism; if combine folds, it could be 0. 

w12: 
```
s32 base;
base = (s32)a0 + 0xCC;
...
v1 = *(s32 *)base;
```
with the store `*(s32 *)(v1 + 0xB0) = v0`.

Hmm, the load `*(s32*)base` = `(set 76 (mem (reg base)))`. The base is a global pseudo used in 2-3 blocks; combine can fold `base = a0+0xCC` into the load only if used once. With 2-3 uses it stays → 16 insns. But then 76 has no pref (base has no pref; set_preference(76, mem(reg base)) → src = (reg base) → GET_RTX_FORMAT(REG)[0]='e'? For REG, format is "i" — hmm, `GET_RTX_FORMAT(REG)[0]` is 'i'? Let me check: in rtx.def, REG has format "i". So `GET_RTX_FORMAT(GET_CODE(src))[0] == 'e'` is false for REG → copy stays 1 → then src is REG → src_regno = base (a pseudo, not hard) → the preference code requires `dest_regno < FIRST_PSEUDO_REGISTER && src_regno >= FIRST_PSEUDO_REGISTER` → dest is a pseudo, so no pref. Right.

So with base, 76 gets no pref → $3, but we pay an addiu. Score 1? Unless the addiu can be eliminated by cse/combine via copy propagation into the loads (the loads have different offsets; folding one addiu into multiple loads isn't possible). 

Hmm, but wait: what if the loads use `*(s32*)(base + 0)`? Combine might fold `base` (a0+0xCC) into the load address if base has one use... it has 2-3 uses.

What if only ONE load uses base and the other uses a0 directly? Then refs and prefs change. Hmm.

Actually! What if we make the load's base a *different* pseudo in one arm only? E.g., arm A uses `(char*)a0 + 0xCC` computed inline (folded, base = 72) and arms B/C use... no.

Let me just test the base idea to see the score; it's informative. And also test a variant where base is used for the store too.

Actually, time. Let me test w12 (base temp) and w13 (load via char* cast), then record WALL.
