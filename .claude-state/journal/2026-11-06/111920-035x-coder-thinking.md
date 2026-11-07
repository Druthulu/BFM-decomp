---
ts: 2026-11-06T18:19:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_A8X22Ne2Mdd97xRDJrTj
---
Now it's clear. The initial RTL:
- r72 = param copy of a0 (`p = a0`, from `void *a0` used as `((Unkstruct*)a0)`)! 
- r73 = param a1, r74 = param a2.
- r75 = v0 (loaded D_80078EB1, set to 1/2, stored).
- r76 = v1 (the loaded pointer).
- r77 = the QI temp, r78/r79 = compare temps.

So `v1` is a single pseudo 76 used in all three branches. Global allocnos: 72 (a0 copy, "pointer", dies in 3 places — because the three loads use it), 75 (v0), 76 (v1), 74 (a2). a1 (73) got $5 locally?

Preferences: 76 prefers 4 — from `(set (reg 76) (mem (plus (reg 72) 204)))`? set_preference(dest=76, src=mem) → src = XEXP(mem) = (plus (reg72) 204) → GET_CODE(plus) != REG → return. Hmm.

But maybe combine turned `(set 76 (mem (plus 72 204)))` into a different form... The .greg dump shows `(set (reg/v:SI 4 a0) (mem (plus (reg/v:SI 4 a0) 204)))` — renumbered, so 76 → 4, 72 → 4.

Where does pref 4 come from? Maybe from `expand_preferences` (merging preferences between allocnos that are copies): 76's preference could come from 72's preference. And 72 (the param copy) prefers 4 — from `(set (reg 72) (reg 4 a0))` — a copy from hard reg a0 → hard_reg_copy_preferences[72] = {4} and hard_reg_preferences[72] = {4}. Then expand_preferences propagates preferences between allocnos that are... let me read expand_preferences (line 776): "Expand the preference information by looking for cases where one allocno is set from another". It merges preferences across copies. Is there a copy between 72 and 76? No — 76 is set from a mem using 72, not a copy.

Hmm, but prune_preferences may remove prefs that can't be satisfied. The table says 76 "prefers a0". Let me look for how: maybe `record_reg_classes` also sets preferences for memory operands' base regs? Let me grep global.c for "classes" and "PREF".

Actually, let me look at the .greg dump RTL *before* renumbering... not available. Alternatively use the .lreg? No.

Wait, maybe I mis-attributed: the table's "prefs" column may be derived from the greg order/preference lines: "76 preferences: 4" — that's from the dump itself. So the dump says allocno 76 has a preference for hard reg 4. How? 

In global.c, `set_preference` is called from mark_reg_store for every SET where SRC is a register. For insn 32: dest = (reg 76), src = (mem ...). GET_RTX_FORMAT(MEM)[0] = 'e' → src = XEXP(mem,0) = (plus ...) → not REG → return. Hmm, unless the RTL at that point has `(set (reg 76) (reg 72))` — no.

Hmm, what about `mark_reg_store` being called with setter = the SET and orig_reg = the MEM? For a store to memory, mark_reg_store(orig_reg=mem, setter=set) → GET_CODE(mem) != REG → return.

What about insn 61: `(set (mem (plus (reg 76) 176)) (reg 75))` → mark_reg_store(orig_reg = mem) → not REG → return. And mark_reg_store is called for regs set... the store's address reg 76 is used, not set.

Hmm, so where? Let me look at `expand_preferences`:

```
expand_preferences: for each insn that is a set of one allocno from another allocno (a copy), merge prefs.
```
No copy.

Maybe the preference comes from `record_reg_classes` in regclass.c: `reg_preferred_class`. The table's "prefs" is from the .greg dump line ";; 76 preferences: 4". Let me grep the greg dump for the exact lines and check if the preference is listed as "copy" or normal. The dump prints `;; %d preferences: ...`. Let me look at global.c's dump code. Search "preferences:".
