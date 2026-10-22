---
ts: 2026-10-22T09:45:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8GewDnyUMuZAQsgv2ri9
---
Confirmed: the .rtl dump is right after expand (get_insns), before cse. And the .cse dump is after cse.

But our .cse dump showed the address as (plus (symbol) (reg 118)) with pattern "-1 (nil) (nil)" — an unexpanded insn?! In the cse dump, the insns should have patterns (after expand, patterns are set). Hmm, "(insn 190 188 193 (set ...) -1 (nil) (nil))" — pattern -1 means no pattern. That's the RTL *before* the final expansion into machine instructions — which is normal for the rtl dump. But the cse dump should show the same (patterns are assigned during expand, before cse)... Actually, pattern assignment happens in `reload`/`reload1` (final insn expansion) — no, patterns are set by `expand_insn`? In gcc, the RTL insns get their PATTERNs during the "final" expansion (function.c's `final_expand_insn`?). Hmm, in gcc 2.7, insns are expanded into machine patterns during `expand_function` (in expand.c) — that's before the rtl dump. So patterns should be present.

Hmm, in the .combine dump the same insn had pattern 125 {extendhisi2_internal}. In the .rtl dump: "-1 (nil) (nil)". So the .rtl dump shows no pattern — meaning the rtl dump happens BEFORE the final expansion (which happens in reload1/final). OK whatever.

But the .cse dump ALSO showed "-1 (nil) (nil)" for insn 190 — meaning the .cse dump is also pre-pattern. Fine, consistent.

So: .rtl and .cse both show (plus (symbol) (reg 118)); .combine shows (plus (reg 118) (symbol)).

So the swap happened in COMBINE (which runs after cse) ✓ — consistent with simplify_rtx's "put a constant last" rule.

And the newval address (plus (symbol) (reg idx)) was NOT swapped — because combine didn't touch that insn (it didn't try to combine it).

Now: to avoid the swap, the tree at combine time must be (plus (reg p) (reg idx)).

Since the substitution of p's constant into the address happened before combine (at expand), we need expand to keep the reg.

How does expand substitute? Let me look at gcc 2.7.2's expand.c... not available. BUT: cse.c is available and cse runs before combine. Could cse have done the substitution? The .cse dump shows the symbol already there, and the .rtl dump ALSO shows it → so it happened at expand (before cse). Yes: the .rtl dump (post-expand) has the symbol in the address.

So expand substituted. In gcc 2.7's expand.c, I now recall there IS a mechanism: `expand_expr` case REG:

```c
    case REG:
      ...
      /* If this is a pseudo-register with a constant value (from a
	 constant initializer), and it is used in an address, use the
	 constant.  */
```

Hmm, alternatively the C front end (c-type.c) has `expand_expr` for VAR_DECL with `DECL_INITIAL`... The front end's c-type.c has:

```c
    case VAR_DECL:
      ...
      if (DECL_EXTERNAL (decl) ...) 
```
Hmm.

AH WAIT. I remember!! In gcc 2.7's c-type.c (the C front end's expand_expr), there's this:

```c
    case VAR_DECL:
      ...
      /* Handle the case of a variable that is not initialized... */
```
and importantly, gcc's C front end does "fold" a variable whose initializer is a constant into its uses when the variable is "const"? Hmm, no.

Alternatively — the front end's `expand_expr` for VAR_DECL checks `optimize && TREE_CONSTANT (decl)` (a "const" variable) → uses the constant directly. Our p is not const.

Hmm. Let me test empirically: does the substitution depend on the number of uses? Let me look at expand.c's source in the OTHER gcc copies... "tools/reference/gcc-2.7.2" has no expand.c, but maybe "tools/reference/gcc-papermario/gcc-2.7.2" exists under a different path. Earlier `ls tools/reference/gcc-papermario/` showed a full gcc source tree listing (BUGS, ChangeLog, gcc-2.7.2 dir?). The listing showed "gcc-2.7.2" as an entry in the ls of tools/reference/gcc-papermario/? Actually the first ls output was of tools/reference/gcc-papermario/ and it showed "gcc-2.7.2" among the entries (BUGS, COPYING, ..., gcc-2.7.2, gcc-papermario, psx_tomba, ...). Hmm no — that listing was of tools/reference/ (the second ls). Let me re-check: the command was `ls tools/reference/gcc-papermario/ | head -40; ls tools/reference/`. The output showed BUGS...TAGS, then "alloca.c"... then "gcc-2.7.2 gcc-papermario psx_tomba psyq-sdk sotn-decomp vagrant-story xenogears-decomp" — that's the second ls (tools/reference/). And the first ls (gcc-papermario/) showed BUGS, COPYING, ... TAGS? Hmm, confusing. The find command showed no expand.c anywhere under tools/reference.

Wait, the find command was `find tools/reference -name "expand.c"` → no output. So no expand.c. Hmm, but gcc-papermario might have a different layout. Let me check quickly: find tools/reference/gcc-papermario -maxdepth 3 -name "expand.c".

Actually the earlier `ls tools/reference/gcc-papermario/` output (first part) listed BUGS, COPYING, ChangeLog... which suggests gcc-papermario IS a gcc source tree (papermario's gcc). Then expand.c should be there! But find didn't locate it... because find printed nothing? The command was `find tools/reference/gcc-papermario -maxdepth 2 -name "expand.c" -o -maxdepth 2 -name "*.c" -name "expand*" | head` — the -maxdepth 2 might be too shallow. And the second `find tools/reference -name "expand.c" | head` printed nothing. Hmm, that find should have found it if present.

Let me look again.
