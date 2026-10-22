---
ts: 2026-10-22T08:55:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_IIWEz2cknhb0v63znyoS
---
Line 82: `(insn 4 2 5 (set (reg/v:SI 72) (reg:SI 4 a0))` — the parameter copy: arg (a0) → pseudo 72. That's "copy from hard reg a0 to pseudo 72" → set_preference(72, 4)?? Hmm! But the dump doesn't show "72 preferences: 4"... Hmm, r72 (arg) → s0 in the disposition. Hmm.

Hmm, wait: set_preference(r1=72, r2=4): "the pseudo 72 prefers the hard reg 4 (a0)". But the arg ended up in s0 ($16) — because the arg is live across calls → callee-saved only (K4). Hmm, and the dump doesn't show "72 preferences: 4".

So maybe the preferences print ISN'T "pseudo → preferred reg". Let me re-read the dump lines:

```
;; 5 regs to allocate: 73 74 76 83 72
;; 72 conflicts: 72 74 83 2 3 4 29
;; 73 conflicts: 73 76 29
;; 73 preferences: 4
;; 74 conflicts: 72 74 83 2 29
;; 74 preferences: 4
;; 76 conflicts: 73 76 29
;; 83 conflicts: 72 74 83 2 29
```

Note: r72 has NO "preferences" line, even though there's a copy (reg/v:SI 72) ← (reg:SI 4 a0). Hmm! And the print order: 72 conflicts, 73 conflicts, 73 preferences, 74 conflicts, 74 preferences, 76 conflicts, 83 conflicts.

So the print is: for each pseudo in order: "conflicts:" then (if any) "preferences:". And "73 preferences: 4" lists ONE entry: 4. And "74 preferences: 4".

Hmm, so what is "preferences"? Given r72 (arg) has the param copy from a0 but no preferences line, the "preferences" must be something else — maybe the *copy preferences* (set_preference) where a pseudo prefers another PSEUDO (not a hard reg)?

Hmm: "73 preferences: 4" — 4 could be... hmm.

Wait, maybe the number after "preferences:" is a *count*! ";; 73 preferences: 4" = pseudo 73 has 4 preferences?? Hmm, that doesn't fit either since r72 has none.

Hmm, let me look at GCC 2.7's global.c dump_global_alloc for real. I'll reason about the actual code (GCC 2.7.2 global.c):

```c
static void
dump_global_alloc (file)
     FILE *file;
{
  int i, j, k, n;
  int regno;

  n = n_global_allocnos;
  fprintf (file, "\n;; %d regs to allocate:", n);
  for (i = 0; i < n; i++)
    fprintf (file, " %d", regno_order[i]);
  fprintf (file, "\n");

  for (i = 0; i < n; i++)
    {
      regno = regno_order[i];
      ...
      fprintf (file, ";; %d conflicts:", regno);
      for (j = 0; j < n; j++)
	if (i != j && conflicts_test[j][regno])
	  fprintf (file, " %d", regno_order[j]);
      fprintf (file, "\n");
    }
  ...
```
Hmm, but the observed "conflicts" lines list hard regs too (2 3 4 29), so the conflict print includes the hard-reg conflicts.

And the preferences:
```c
  /* Print the preferences.  */
  for (i = 0; i < n; i++)
    {
      ...
      fprintf (file, ";; %d preferences:", regno);
      for (j = 0; j < n; j++)
	if (reg_preferred[j] == regno)
	  fprintf (file, " %d", regno_order[j]);
      fprintf (file, "\n");
    }
```
With this, "73 preferences: 4" would print a pseudo from regno_order — but 4 isn't in {73,74,76,83,72}. So no.

OK, alternative: maybe the dump prints, for each *allocno*, the list of hard regs it prefers:
```c
      fprintf (file, ";; %d preferences:", regno);
      for (j = 0; j < n; j++)
	if (reg_preferred[j] == regno)  ...
```
Hmm.

You know what? It doesn't matter that much. What matters: q (r73) ends up in a0 rather than v1, and the mechanism per the .lreg data is: r73's conflict set doesn't include v0/v1/a0, so the scan order (v0, v1, a0) should give v0 — but it got a0. So SOMETHING excluded v0 and v1 for r73.

What excludes v0 and v1 for r73? The *local* allocation! The locals in blocks 4/7/9: hmm, r73 is live in blocks 4, 7, 9. Which locals are in those blocks? Block 4: r76 (val, but it's global), block 9: nothing local. Hmm, so in blocks 4/7/9, the locals are... none (r76 is global).

Hmm, so v0 and v1 are free in blocks 4,7,9. Then why not v0?

The "regs_used_so_far" rule (K5): pass 0 excludes regs NOT in regs_used_so_far. v0 IS used. Hmm.

So the scan should give v0 for r73. Unless the scan skips v0 because... hmm! Maybe because global.c's find_reg checks `conflict_sets` — the hard-reg conflict for r73 vs v0: the .greg dump says r73's conflicts = {73, 76, 29} — no 2. Hmm, so v0 is not conflicting.

Hmm, but WAIT: the .greg "conflicts" for r73 lists the *allocnos* it conflicts with (73, 76) and the hard regs (29 = sp). Hmm, 29 is sp. So r73 conflicts with sp only among hard regs.

So the scan should pick v0 ($2) for r73! But it picked a0. So there must be a *preference* (K5: "Copy preferences can override the scan-order winner within the class").

So the preference for r73 = a0 (4) is real, and it overrides the scan (v0). And the preference came from a copy (set (reg:SI 4 a0) (reg/v:SI 73))... which I couldn't find in the .lreg RTL.

Hmm! Unless the preference print means: "the hard reg 4 (a0) is preferred BY pseudo 73"? I.e., the print is: for each hard reg, which pseudo prefers it. Hmm: "73 preferences: 4" = pseudo 73's preferred reg is 4.

OK whatever the print means, empirically: q prefers a0. And the only copy into a0 in the function is the call-arg copy for ptr. Hmm! Could it be that BOTH r73 and r74 prefer a0 because of the *same* copy — i.e., a copy chain: `(set (reg:SI 4 a0) (reg/v:SI 74))` where 74 is... hmm.

OH WAIT!!! Maybe the pseudo numbering in the .greg dump is different from the .lreg/.rtl dump! The .greg dump uses "allocnos" (global.c's own numbering: allocno numbers, not regnos!). In GCC 2.7's global.c, `regno_order[i]` are *allocno* numbers (global.c renumbers the global pseudos: `regno = gen_reg_rtx(...)`? hmm). Actually, global.c creates a "global_allocno" for each global pseudo, and the dump prints the *regno* of the pseudo.

Hmm, the numbers 72, 73, 74, 76, 83 match the .lreg regnos exactly, so they're regnos.

So in the .greg dump, r73 = q, r74 = ptr, r76 = val, r83 = the switch value, r72 = arg.

And "73 preferences: 4" → q prefers a0. And the only a0 copy in the RTL is the ptr one (insn 22 and 53).

UNLESS the copy is created later — by *reload* — and global.c's dump... no, the dump is at global_alloc time.

Hmm, hold on! What about the possibility that the copy is created by local_alloc, and the .lreg dump is printed AFTER local_alloc? Let me check: the .lreg RTL shows r78/r79 still as pseudos → if the dump were after local_alloc, they'd be hard regs. So the .lreg dump is before.

Hmm, but wait: maybe local_alloc creates a copy for the *q* pseudo because of the "qty_phys_copy_sugg" mechanism? Hmm.

Hmm, let me look at the actual .greg dump RTL for the join block in the lever-free version — the stores' base. If the base is a0 and there's a copy `(set (reg:SI 4 a0) (reg/v:SI 73))` in the post-alloc RTL, that would be the copy (it would have been folded into the store's address, but the dump shows the pre-fold RTL).

Let me look at the .greg RTL for the join block (insns 101, 104).
