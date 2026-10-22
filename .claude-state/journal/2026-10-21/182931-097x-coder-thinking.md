---
ts: 2026-10-22T00:29:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_jowUwbKUlERvZh8LGGKt
---
Item 6: func_80180054 has 6 launders:
- 5435: on xa (after `xa = a;`)
- 5438: on xb (in the if arm, after `xb = b;`) — with the template " " (a space!)
- 5442: on xb (else arm) — template "  "
- 5448: on xa — template "   "
- 5451: on xb — template "    "
- 5455: on xb — template "     "
- 5466: on p (at the end of the loop body)

The whitespace templates: an asm with a non-empty template (whitespace only) — the assembler emits nothing, but gcc treats it as a non-volatile asm? Note 5435 and 5466 are `__asm__("" ...)` (empty template) = the "volatile-less" form, while the others have whitespace templates (non-empty → gcc treats a non-empty template as... hmm, in gcc, an asm with a non-empty template is implicitly volatile? No: in GCC, an asm statement with no volatile qualifier but with outputs is not volatile. But an asm with a template that is not empty IS treated as volatile in some compilers. In GCC 2.7, `asm` without volatile is not volatile, but "asm with a non-empty template" — hmm, GCC's rule: "asm statements with a non-empty template are implicitly volatile" was introduced in GCC 4.x? Hmm, in GCC 2.7, the "volatile" keyword is required. But the empty-template vs whitespace-template difference may matter for the *delever census* (the census classifies: "barrier (empty template, no outputs...)").

Anyway, these 6-7 launders all need to go. The mechanisms:
- xa = a; [re-tie] → the re-tie gives xa's reg a 2nd set → the "xa = a" copy isn't coalesced with a? Hmm, or the birth boost of xa's def is killed.
- xb = b; [re-tie] → same.
- p += 2; [re-tie] → the re-tie of p.

The re-tie on `xa = a` (a copy from a): the re-tie creates a copy that survives (as we saw in item 3 with v1 = mode → a real "move" in the output). So the target has explicit moves: "move xa_reg, a_reg".

So the target's code has copies (moves) that plain C would coalesce. Hmm, and these copies are the "launder" effect.

So for item 6, we'd need to reproduce several moves. In plain C, a copy survives if the source is live afterwards. E.g.:
```
a = sxy[1].vy;
b = sxy[0].vy;
xa = a;      /* the copy: survives only if a is live after */
```
`a` is reassigned later ("a = sxy[2].vy;") → so at the time of the copy, `a` IS live (it's overwritten later, but the value is used... hmm, after `xa = a;`, `a` is used in `if (a - b >= 0)` → so a is live after the copy → the copy xa = a CANNOT be coalesced?? Hmm, but gcc's regalloc can still coalesce xa and a into the same register only if their live ranges don't overlap — they DO overlap (a is live after the copy) → so the copy must be a real move!

Hmm! But gcc's cse would propagate: xa's uses could read a's reg... but that would extend a's live range. cse's "make_regs_eqv" does exactly that (it can merge the two if the values are equal and the ranges allow). Hmm, in item 3 the copy vanished (cse merged them).

Here, in the current source, `xa = a;` then `d1 = xa - xb;` — and `a` is used in `if (a - b >= 0)`. So a is live across the copy. cse could still merge xa and a (making them the same reg) since the values are equal and the merged live range is fine.

Hmm, so why does the banked version need the re-tie? Because the re-tie makes the copy opaque → gcc can't merge → the target has the copy as a real move.

Hmm! But if the target has a real move (xa = a) and the source has "xa = a", then without the re-tie gcc merges them (no move) → the score changes. So the re-tie is load-bearing for the move's existence.

Hmm, unless: the value `a` is live across the copy in a way that prevents coalescing... Let me check the target's code to see if there's a move.

Let me look at the target's disassembly for func_80180054. Hmm, that's another dump.

Given the time, let me consider: 6 launders of the "re-tie" kind, all producing copies/boost-kills. Reproducing them all in plain C is unlikely.

Let me quickly assess: extract the function, remove the launders, and score → if the residual is large, it's a WALL.

Let me do that (2 calls), then record.

Also, for items 1 and 2 (the vol launder in ov_SC02_026), let me try the "&= compound assignment" idea? The launder there is on `vol` (a computed value) — hmm, the compound trick requires a real op. In item 1, the launder is between the vol computation and the pan computation. The vol value is used in the OR. Hmm.

Hmm! What about the compound assignment on vol? e.g.
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
```
→ what if we split it as:
```
vol = (0xA0 - av) * 0x7F;
vol /= 0xA0;
```
The compound assignment `vol /= 0xA0` is an in-place division → gcc's expand_div for a compound assignment might generate the same code but with the div's operands in place... The target's code is the same as the current one (the div by 160 with the magic). Hmm, would `vol /= 0xA0` generate the same code as `vol = vol / 0xA0`? Probably yes, and the compound form might create the "2nd set" of vol's pseudo ✓ (the div's result written in place).

But the item-1 problem is the ORDER of the two division chains (a scheduling issue), not a boost. Hmm, but maybe the boost IS involved: the vol chain's mfhi (match_scratch) is single-set → boosted → sunk to its consumer. In the target, the vol chain's mfhi is at 205 (right after the mult at 204) — the "sink to consumer" position ✓ boosted! And the pan chain's mult at 208.

Hmm, in mine (no launder): the pan chain came first. So the launder's effect = the vol chain is boosted and the pan chain isn't?! Hmm, in mine: the pan chain is first (200-201) and the vol chain later (202-207). Hmm, in mine the vol chain's mfhi is at 212 (sunk to its consumer) and the pan's mfhi at 204.

So in mine: the pan chain first (the mult at 201), the vol chain later. In the target: the vol chain first.

The mults: mine[201] = "mult a0,a2" (pan), mine[207] = "mult v1,a2" (vol). The target: 204 "mult v1,a0" (vol), 208 "mult v0,a0" (pan).

Hmm, so the ORDER of the two mults differs. The mults write... the mult's dest is a hard reg ($lo/$hi), and the mfhi writes match_scratch. The two chains are ordered by the match_scratch WAW tie.

In the target, the vol chain is first; in mine, the pan chain is first. The source order is vol first. So mine SWAPPED them (sched1) and the target didn't.

The launder between them is the barrier ✓ (as I analyzed). So a plain-C fix must prevent the swap.

Hmm! What if the vol chain's result gets a 2nd set (via the compound assignment `vol /= 0xA0`), making the vol chain's *priority* higher (more refs)? Hmm, the swap is decided by the chain priorities: the pan chain (dividend = sx+160) vs the vol chain (dividend = 127*(160-av)). Both are mult+mfhi chains with a load... hmm, no loads. Both pri 1?

The tie is broken by the LUID (source order) → the vol chain (earlier in the source) should win ✓ = the target. But mine has the pan chain first → so sched1 swapped them for another reason (the birth boost!).

The birth boost: the mfhi that BIRTHS match_scratch gets max priority → placed late. The vol chain's mfhi is the birth (source order) → boosted → placed LATE → so the pan chain (not boosted) is placed EARLIER ✓ = mine (the pan chain first)!

And in the target, the vol chain is first → so the vol chain's mfhi is NOT the birth → hmm, or the boost went elsewhere.

Hmm! With the launder: the launder's asm output is a pseudo born at the launder... and the match_scratch's birth: hmm.

Hmm, what if the boost is killed for the vol chain's mfhi? The mfhi's dest = match_scratch, which has 2 sets (the two mfhi's) → NOT single-set → no boost! Hmm! Then neither chain is boosted and the order = source order = vol first ✓ = the target!

But in mine the vol chain is second → so the vol chain WAS boosted → so match_scratch has 1 set in mine? Hmm, the two mfhi's both write match_scratch → 2 sets → no boost. Hmm, unless the two divisions use DIFFERENT match_scratch pseudos... but the emitted code shows one constant (a0/a2) used by both mults — hmm, that's the magic CONSTANT, not match_scratch. The match_scratch is where the mfhi writes (t1 in the target: "mfhi t1" and "mfhi a2" — different registers!). So the two chains' mfhi's write DIFFERENT registers (t1 and a2) → different match_scratch pseudos → each is single-set → each is boosted!

Hmm, so the two chains are independent. Then why did sched1 swap them?

The magic constant: the target has "lui a0,0x6666; ori a0,a0,0x6667" (one pseudo, 2 uses) and mine "lui a2; ori a2" (one pseudo, 2 uses). Both chains read it.

Hmm, so why the swap? The chains: vol's = {li v0,160; subu; sll; subu; mult v1,a0; mfhi t1; sra; sra; subu} and pan's = {addiu v0,a2,160; nop; mult v0,a0; mfhi a2; sra; sra; subu}.

Hmm, the pan chain has the "addiu" (a dependency on a2 = sx) — and the mult has a 5-cycle latency (imul cost 12 per the doc!). "imul +11" — the mult's cost is 11-12 → the chain's priority is much higher.

Per the doc's S3: "a chain fed by a load is pri+1, imul +11, idiv +34". So the mult's chain pri = 12! And the priority DOMINATES the LUID tie-break.

So both chains have a mult (pri 12) — equal. Hmm.

Hmm, the vol chain: mult v1,a0 (imul, +11) → pri 12; the pan chain: mult v0,a0 → pri 12. Equal priorities → the LUID decides → the source order (vol first) → the vol chain should be placed... hmm, in the backward scheduler, the higher LUID is placed later. The vol chain (earlier in the source, lower LUID) is placed EARLIER ✓ = the target!

But mine has the pan chain first ✗.

Hmm, so something else. The BOOST: the vol chain's mfhi (match_scratch pseudo, single-set) → boosted to max_priority → placed LAST ✓ = mine (the vol chain second). And in the target, the vol chain's mfhi is NOT boosted → why? Because the launder's asm output pseudo... hmm, the asm is between the chains, and the asm's output is tied to vol's reg. Hmm, that doesn't affect match_scratch.

Hmm, but wait: the boost test is `REG_N_SETS(dest)==1` where dest = match_scratch. In the target, is the vol chain's mfhi's dest a different pseudo from the pan chain's? Yes (t1 vs a2) → single-set each → both boosted. Hmm, then both chains are boosted and the LUID decides → the vol chain (lower LUID) placed earlier ✓ = the target!! And in mine, only the vol chain is boosted??

Ugh, unless in mine the two chains' mfhi's write the SAME pseudo (match_scratch) → 2 sets → no boost for either → and then the order = the LUID → the vol chain first... but mine has the pan first. So no.

I give up on the theory. EMPIRICAL for item 1: try the compound-assignment split of the vol computation:
```
vol = (0xA0 - av) * 0x7F;
vol /= 0xA0;
```
and also:
```
vol = (0xA0 - av) * 0x7F;
vol = vol / 0xA0;
```
and the pan similarly. Cheap experiments. Let me do them after item 6's assessment.

Let me now do item 6's assessment (extract + remove launders + score) in one go.
