---
ts: 2026-10-22T06:54:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_THwzF35GBRViWTrj9Kc2
---
In the tree's .sched2: the order is s2, a0(→s2), s4, a1(→s4), s0, a2(→s0), then a0=16. So move s0,a2 BEFORE li a0,16 ✓ (matches the assembly).

In cand's .sched2: s2, a0, s4, a1, a0=16, then s0, a2 → li BEFORE move ✓ (matches cand's assembly).

And .sched2 is the final (post-regalloc, post-sched2) RTL, matching the assembly.

So the question: at which pass did the order diverge? The .sched dump (sched1) already showed the divergence, so it happened at or before sched1.

Now: is the .sched dump the INPUT or OUTPUT of sched1? gcc's dump file for a pass contains the RTL after the pass. But the sched1 trace is also written to that file (during the pass), and gcc writes the RTL dump at the END of the pass → so the trace appears FIRST, then the final RTL. So the RTL in .sched IS the post-sched1 RTL. Hmm, but then the trace's launch order should match the chain order.

Unless gcc's sched1 (in 2.7.2) schedules the block and then REVERSES? Hmm.

Hold on, maybe not. Let me re-read the trace format from gcc 2.7 sched1.c:

```
	      /* Print the ready list ... */
	      if (dump_file)
		{
		  fprintf (dump_file, ";; ready list at T-%d: ", time);
		  for (insn = rlist; insn; insn = next_insn)
		    fprintf (dump_file, "%d (%d) ", INSN_UID (insn), ...);
		  fprintf (dump_file, ", now ");
		  for (insn = rlist; insn; insn = next_insn)
		    fprintf (dump_file, "%d ", INSN_UID (insn));
		  fprintf (dump_file, "\n");
		}
```
Hmm, and the launched insn is `insn` chosen; the "now" list is printed AFTER removing it? If "now" = the list after removing the chosen insn, then at T-4 "now 64 62 60 58" means the remaining list is 64,62,60,58 — but the chosen was... the list at T-4 was "58 60 62 64" (4 items) and "now" has 4 items → so nothing was removed → "now" is the SORTED list. So the chosen insn is the first of "now"? Then the launch order in the tree = 68, 66, 64, 56, 62, 60, 58, 51, 49, 44, ... and the chain is 4,6,15,17,20,...,71 → the chain is NOT the launch order.

Therefore the .sched RTL must be the INPUT to sched1 (i.e., the state before scheduling), and the trace shows how sched1 scheduled it. But then the .sched file would contain the pre-pass RTL — which contradicts gcc's convention...

Hmm, unless: gcc's dump for the "sched" pass is written at the START? Actually! In gcc, `dump_rtl` with the pass's dump file: the RTL is dumped when the pass completes (via the `pass` wrapper `do_per_function_toporder` → `dump_state`). Hmm.

OK, empirically: does the trace's launch order correspond to the final chain reversed? Let's verify with a distinguishing feature: in the tree, the launch order at T-2 was 68 (boosted) — the boosted insn in the chain is at the END. In cand, the boosted insn 15 (move s0,a2) is at chain position 4 (second-to-last before the call). Hmm, so boosted → near the end of the chain in both. Consistent with "chain = reverse of launch order".

Wait, that's a strange scheduler. Let me double check by looking at the tree's chain near the end: the last insns in the tree's chain: ... 54?, 56, 58, 60, 62, 64, 66, 68, 71. And the launch order was 68, 66, 64, 56, 62, 60, 58, 51, 49, 44, ... So launched 68 first → chain last. Launched 66 second → chain second-to-last. Yes: chain = reverse of launch.

So gcc's sched1 here builds the chain in reverse?? Hmm, actually maybe I mis-assume: maybe the trace prints the ready list at time T and the insn launched at T-1... i.e., the trace is printed BEFORE the launch, and "now" is the sorted list; the launched one is the LAST of "now"? At T-4: "now 64 62 60 58" → launched 58? Then the chain would be: launched 58 (T-4) → chain position? The tree's chain has 58 at position... the chain ascending: ..., 56, 58, 60, 62, 64, 66, 68. If the launch order is 68,66,64,56,62,60,58 (T-2..T-8) and the chain is ascending 56,58,60,62,64,66,68 → the mapping isn't a clean reversal (56 was launched at T-5, before 62,60,58 which are earlier in the chain).

Whatever the exact semantics, the key facts:
1. In cand, the birthing insn (move s0,a2) has the 7f000001 boost; in the tree it doesn't (2 sets).
2. In cand, the move ends up AFTER the li a0,16; in the tree, BEFORE.
3. Everything else is identical.

So we need pseudo 16 to have 2 sets.

Now: **what if we give pseudo 16 a second set via a plain-C construct that emits an instruction we can AFFORD?** No — extra instruction = score mismatch (99 vs 100).

Hmm, wait. Actually, is that true? The scoring compares the instruction streams; an extra instruction would show as a diff. The target has 99 ins; mine must have 99.

Hmm, but what if the extra instruction REPLACES another one? E.g. what if the second set of pseudo 16 is a `move s0,a2` that gets coalesced with the first? local-alloc coalesces a copy with its source: `rgb = arg2` (copy from a2) and `rgb = t` where t is a copy of arg2 → both copies of the same value → cse would merge them anyway.

**What about the following trick**: the second set of pseudo 16 could come from a *subreg* insertion, e.g. `rgb = arg2;` and then `rgb` used in a context that inserts a subreg: like `*(s16 *)&rgb`? Illegal for register vars.

Hmm.

**NEW ANGLE — change the STRUCTURE so the boost doesn't matter**: What if the move s0,a2 is not a "birth" but a copy of another pseudo? E.g.:

```
s32 t = arg2;      /* t's birth: copy from a2 — t is a pseudo */
rgb = t;            /* rgb's birth: copy from t */
```
Now rgb's pseudo is born by a copy from t, and t is born by a copy from a2. After local-alloc coalescing, rgb (in $16) and t (in a caller-saved reg or coalesced) — the copy rgb=t could be coalesced away if t is in $16 too. Hmm, t is used only here, so t and rgb could be coalesced into the same register $16 → the copy insn disappears, leaving `move s0,a2` — but now the BIRTHING insn is t's copy (which is also `move s0,a2` after coalescing) — hmm, at sched1 time (post-reload), the pseudo t is born by a copy and rgb is born by a copy from t. So there are 2 birth-ish insns, both possibly boosted. The relative order of the li vs the copies might then match the tree!

Interesting! But careful: coalescing happens in local-alloc (after sched1) or in reload (before). At sched1 time, the RTL would have: t = a2 (copy), rgb = t (copy). Then local-alloc/reload coalesces.

Hmm, in the tree, the RTL at sched1 was: (set (reg/v:SI 16 s0) (reg:SI 6 a2)) — a single copy, with pseudo 16 already hard-reg-bound (register var). And the li.

If instead we write `s32 t = arg2; rgb = t;`, the RTL at sched1 would be: (set (reg/v:SI t) (reg:SI 6 a2)), (set (reg/v:SI 16 s0) (reg/v:SI t)) — two copies, and after coalescing (reload/local-alloc) they'd merge into one move. But the ORDER of scheduling would be based on 2 insns. Would the li then land between them or after? We need: move s0,a2 (after coalescing) BEFORE the li.

Hmm, this is worth a try! But it might also produce a different instruction (e.g. `move v0,a2; move s0,v0` if not coalesced).

Let me try it: cand23:
```
s32 t;
t = arg2;
rgb = t;
```
Hmm, but with `register` vars, gcc might handle the copy specially.

Let me also try cand24: `rgb = arg2;` + `s32 t = rgb;` (t dead) — no.

And cand25: `rgb = (s32)arg2;` — same.

Let me also try the reverse: what if the copy is `rgb = arg2;` and the *store* uses `arg2` directly (so rgb is dead)? Then no $16 at all → different code.

Let me run a batch of ~10 new variants and score them. Let me write them.

Variants to add:
cand10: `s32 t; t = arg2; rgb = t;` (rgb stays pinned)
cand11: `rgb = arg2;` + `do { rgb = arg2; } while (0);`
cand12: rgb declared u32 (pin $16), store via u32
cand13: `s32 t = arg2; rgb = t;` (init at decl)
cand14: `rgb = arg2; rgb = arg2;` with a `volatile`? no.
cand15: remove the rgb pin entirely
cand16: `rgb = arg2;` then the store `*(u32 *)((u8 *)temp_v0 + 4) = rgb;` (u32 store)
cand17: `rgb = arg2;` + `{ s32 t = rgb; rgb = t; }` (already cand05 - score 2)
cand18: `rgb = (s32)(u32)arg2;` hmm.
cand19: `rgb = arg2;` and `tag0` given 2 sets (control): `tag0 = *(u32 *)temp_v0; tag0 = tag0;` — no effect expected.

Let me write the generator with a more flexible mechanism: each variant = full file text. I'll write them individually as files via a python script with explicit bodies.

Actually simpler: write each candidate file with the Write tool (they're ~50 lines each — verbose). Better: extend mk_cands.py to do textual replacements on orig.c. Let me restructure: the script will take a list of (name, [(old, new), ...]) replacements applied to orig.c.

Replacements:
- Remove the asm line: replace the asm line with "".
- Replace `rgb = arg2;` with something else.
- Change the decl line.
- Change the store line.

Let me write mk_cands2.py with these variants.
