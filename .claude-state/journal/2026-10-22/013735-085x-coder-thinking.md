---
ts: 2026-10-22T07:37:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_p60BcmCgnoWeP3zJ3uAg
---
The scorer works with fn=SCAN: it scored 0 for the tree's own region (as expected — the tree matches itself). The "function" SCAN is scored by comparing the whole TU object (3991 ins).

So the body = the region text (lines 3097-3111), and splicing it replaces that region in the TU.

Now the task: replace the launder in that region with a lever-free equivalent that still scores 0.

The launder:
```
        { s32 _m = (s32)&D_801C8344;
          __asm__ __volatile__("" : "=r"(_m) : "0"(_m));
          ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)((s0) + 0x20) + 0x34, _m, (s32)(v10)); }
```

The lever-free replacement must keep the address &D_801C8344 rematerialised (not hoisted into a callee-saved reg).

Options:
(a) Just remove the asm: `{ s32 _m = (s32)&D_801C8344; ... }` — then _m has 1 set → the address might be hoisted → different code.
(b) The "dead-reset CSE-breaker" (my item 1's move): use the address in a variable, then reset it to 0 → breaks cse's equivalence → the address is re-derived at each site.

Hmm, but here the block is a single use. The launder's role (per the comment): each expansion gets a FRESH pseudo that cse can't unify with the other sites' identical symbol_ref → so the address is rematerialised at every call instead of hoisted once into a callee-saved register.

Hmm, so with 3 sites (each with its own `_m` block), cse might unify the three `_m` pseudos (they're all &D_801C8344) → one address pseudo with 3 uses → hoisted into a callee-saved register. The launder's asm gives each `_m` a 2nd set → hmm, but that wouldn't prevent cse from unifying them...

Hmm, actually: the asm's output is `_m` (a pseudo) and its input is `_m` → the asm's set makes `_m` a 2nd-set pseudo. Hmm, and cse's "make_regs_eqv" for the symbol_ref address: the three `_m` pseudos each = &D_801C8344 → cse would unify them into one pseudo (all equal to the same address) → then the address is computed once and hoisted.

With the asm, each `_m` has 2 sets → hmm, does that prevent the unification? The asm's input/output tying might make cse treat them as distinct (the "reg_equiv" chain is broken by the asm).

Whatever the mechanism, the lever-free equivalent should break the unification of the three address sites so each is rematerialised.

The dead-reset trick (from my item 1 and the moves.md G10 lines): use a variable for the address, then reset it to 0 after the use — cse's forward scan invalidates the class at the reset → each site re-derives the address.

But careful: the reset must not change the code (the reset is dead → removed).

Hmm, but in THIS region (lines 3097-3111) there's only ONE launder site (the other two are outside the region). The scorer compares the WHOLE TU object (3991 ins) — so the whole function's code must stay byte-identical. So my replacement must preserve the whole TU's code, including the other two sites' behavior.

Hmm! Interesting: if the three sites' addresses were unified by cse, then changing only one site (in my region) would change the whole function's code.

Let me look at the other two launder sites (3036, 3051) and the ones at 3116, 3156, 3158, 3244, 3258. They're all the same pattern with D_801C8344.

Let me check the target's assembly to see how the address is materialized at each site: `la $a1, D_801C8344` (lui+addiu) at each call ✓ (per the comment).

So the lever-free version must keep the address rematerialised at each of the (relevant) sites.

Approach: for the site in my region, replace:
```
        { s32 _m = (s32)&D_801C8344;
          __asm__ __volatile__("" : "=r"(_m) : "0"(_m));
          ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)((s0) + 0x20) + 0x34, _m, (s32)(v10)); }
```
with:
```
        { s32 _m = (s32)&D_801C8344;
          ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)((s0) + 0x20) + 0x34, _m, (s32)(v10));
          _m = 0; }
```
Hmm, the dead reset after the use. Does that break cse's equivalence so the address is rematerialised? The reset is dead (removed by flow) but it breaks the cse class ✓ (that's the §373 DEAD-RESET CSE-BREAKER from my item 1).

Hmm, but wait: in my item 1, the reset was BEFORE the next site, and the effect was that each site re-derived the address. Here the reset is after the use in the same block — the next site (a different block) would see the reset ✓ (cse's forward scan invalidates the class at the reset point).

Hmm, but the OTHER sites (outside my region) still have their launders → they'd still be "2nd set" and might unify with each other.

Since the scoring compares the whole object, let me just try:
cand01: the region with the asm removed (plain).
cand02: the region with the dead reset after the use.
cand03: the region with the dead reset before the use? no, that would break the value.

Let me test cand01 and cand02.

Note: the body I submit replaces lines 3097-3111 of the TU. So my body must be a valid replacement for that region.

Let me write thecandidates.
