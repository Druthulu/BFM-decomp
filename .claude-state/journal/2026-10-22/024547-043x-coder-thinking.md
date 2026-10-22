---
ts: 2026-10-22T08:45:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_3UCd1o08loR3yWOqZCxH
---
The pinned orig scores 0 — so the build is current and the target is the pinned version.

Now, let me try many variants for item 1. Let me write a batch of candidate files and score them all with sc.sh (one line each). I'll write a helper to generate variants quickly. Let me write them as separate files c5..c15.

Variants to try:
c5: decl order: q declared last (after val).
c6: val as s16.
c7: st as s16 (would change the lhu? `st` is u16; if s16, the compare changes → different code. Skip? Actually `switch(st)` with s16 → the comparison would use sign extension → different insns. Probably worse but let's see. Actually the target's dispatch: `lhu v1,2(a0)` then compares with 1 and 2. If st were s16, we'd need `lb`+sign extend → different. Skip.)
c8: pointer reuse: `u16 *qp` for stores.
c9: q as u32.
c10: the call result into a temp `s32 r = func_8012BD14(ptr); if (r > 0x9000)`.
c11: `q` init at decl.
c12: arg used directly (no ptr) but keep ptr for the call.
c13: reorder the stores.
c14: the whole thing with `switch` → if/else if.
c15: q declared as `s32 q = ((Unkstruct_801815AC_2 *)arg)->unk64;` at decl (init at decl) — that changes when the load happens (before the switch) → shape changes.

Let me think about which could plausibly help:
- (c10) adding a temp for the call result changes the pseudo structure: the call result currently is a pseudo r77 (local). With a temp `s32 r`, it might become a global? no, still local to the arm. Hmm, but adding a temp could change the local const's reg! E.g., if the temp r occupies v0 in the arm... no, v0 is the call result.

Hmm, what about the idea of making the *value* (val) a global that takes v0 and making the *const* a global? Hmm.

Let me think about the alloc order: "73 74 76 83 72" = q, ptr, val, switchval, arg. r73 (q) is first (highest priority) but got a0 because v1 was blocked and v0 was... wait, was v0 blocked for r73? r73's conflicts = {73, 76, 29} — no v0. So v0 was available for r73?! But q got a0, not v0!

Hmm! Why not v0? Because r73 has a *preference* for reg 4 (a0)? The preference is honored over the reg order. So if I could remove the preference, q might get v0 (also wrong, but it shows preferences matter).

So: what creates the preference for a0? "73 preferences: 4". Since the copy `(set (reg:SI 4 a0) (reg/v:SI 74))` is for r74 (ptr), the preference for r74 is a0. For r73 (q), what copy involves q and a0?

Hmm! Maybe the preference is not from a copy but from the *reload* pattern: q is loaded from memory (arg->unk64) and used as an address in the join. Hmm.

Wait, maybe the .greg dump's "preferences" line lists the pseudos that are *connected by copies* to this pseudo — "73 preferences: 4" would then mean "pseudo 4 is connected to 73". Pseudo 4 in the .rtl numbering... but the .rtl dump uses regno 72-85 for the function's pseudos. Hmm, but in the .greg dump, the "conflicts" lines use numbers 72,73,74,76,83 — the same numbering. So "preferences: 4" = reg 4 = a0.

Hmm, in GCC 2.7 global.c's dump_global_alloc:

```
  for (i = 0; i < n; i++)
    {
      ...
      /* Print the preferences of this pseudo. */
      for (j = 0; j < n; j++)
	if (reg_preferred[j] == regno[i]) ...
```
Hmm, if it printed "for each pseudo, the pseudos that prefer it", then "73 preferences: 4" doesn't fit (4 is a hard reg).

Let me look at GCC 2.7's actual source. Maybe the gcc source is available in the repo? Let me check for a gcc source tree: tools/bin/gcc-2.7.2-psx might have source. Let me look.
