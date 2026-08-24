# Distillation — waves ax · bm (batch `.run/distill_inflight/axbm.json`)

**PROPOSED ONLY — nothing here has been applied to `docs/matching-cookbook.md` or `docs/cookbook-index.md`.**
Reviewer lands the sections. All A/B evidence lives under `.run/s59_distill2/` — every variant file
re-runnable via `tools/match_one.py <fn> --c <file> --asm-subdir <the card's own asm dir>` (the
homonym trap bit this review's own harness once: `find`-first-hit returned ov_SC06_030's
func_80181164.s, 265 ins — always pass the card's exact subdir).

## 0. The ledger — counts first (R41: every number's denominator stated)

**82 candidate notes read** — all of them — from 2 files: `ax` 41, `bm` 41 (matches the batch
manifest's `novel: 82`).

| disposition (primary, one per candidate) | rows | of 82 |
|---|---|---|
| **Already covered** (cited § per row below) | **67** | 81.7% |
| **Feed a proposed addendum** (ADD-1…ADD-10 below) | 9 | 11.0% |
| **Feed the proposed new law §268** | 2 | 2.4% |
| **Refuted** (6 distinct claims; 4 by live `match_one` A/B, 1 by artifact, 1 definitional) | 4 | 4.9% |

**§266 sweep (the mandated inert-rider audit): 19 solo-lever verdicts across 13 banked functions,
34 valid `match_one` runs (13 baselines — all reproduced MATCH — plus 21 variants). 6 of 19 levers
are INERT RIDERS; 13 are load-bearing.** Full table in part 1a. Two standing §257 dead-end-ledger rows
acquired byte-proven bounds out of this sweep (§257-2, §257-8).

**Batch-hygiene notes for the campaign:**
- Wave `ax` is dominated by the gate-null/integration era: ~20 of its 41 rows are §259-4/§236
  process reports ("body byte-exact, fault outside the card") from the wave-revert period, and at
  least five re-mine functions the cookbook already cites BY NAME (`func_8017ECA8`→§236-6,
  `func_8017FE54`→its at-wave verdict, `func_8017F10C`→§257-6, `func_8018944C`→§254,
  `func_801853F0`→§224-addendum-4). A dedup guard keyed function→cookbook-exemplar would have
  shrunk `ax` by a third.
- **One non-MATCH card leaked through the "byte-gate ACCEPTED" filter**: the ax `func_8017FB04`
  note is a LENGTH-DRIFT/−4 residual report — and it analyzes the HANDWRITTEN ov_SC03_030 homonym
  for the second consecutive batch (previous batch's REF-3; §265's cautionary tale). Harvester
  should gate candidate rows on the verdict column, not just the wave file.
- `func_8017F328` appears in BOTH waves (same function, consistent notes) — counted once per wave
  per the manifest, distilled once here.

### 0a. Per-candidate disposition (one line each; spot-check any row)

Verdicts: `cov §X` = already covered (drop; ⊕ = also a cross-confirmation card worth appending per
§259's standing instruction — collected in ADD-10). `ADD-n` = feeds proposed addendum n. `§268` =
feeds the proposed new law. `REF` = refuted (part 3).

**Wave ax (41):**

| fn | verdict |
|---|---|
| func_801A23CC | cov §14b (leaf = true gate) + §167-27 + §259-4 (residual points at sibling stubs) |
| func_800CF010 | cov §51/§166/§259-4 (self-cited; gate-null) |
| func_8017FB04 | **REF-1** — analyzes the HANDWRITTEN ov_SC03_030 homonym again (prev. REF-3, §265); note is not even a MATCH |
| func_801824E4 | **ADD-2** (silent-splice decl default: `()` beats fleet-vote) + cov §255-1 (its empty-case lever cited there by name) + §165-36 decoy warning |
| func_8017F10C | cov **§257-6 — cited there by name** ("two independent notes") + §249 (volatile self-copy) + §21/L1844 (u16\* → `ori`) ⊕ |
| func_8017FCBC | cov §150-B-data + §250 (array-vs-scalar) + §238 (re-read the destination before re-deriving) ⊕; corroborates ADD-2 |
| func_800CF078 | cov §259-4 + §261/§18-P29 (-O0 carve fragility) |
| func_801A06AC | cov §259-4 (wave revert semantics); cites line numbers `s1144/s1284` → §14/§14d (gap #5) |
| func_8017EF50 | cov §236-2 + §103 (file→block scope move) |
| func_80185760 | cov §214 (0.69 twin misdirect) + §194-E (in-TU dispatchers are the real relatives) |
| func_801A23A8 | cov §259-4 + §28 + §236-family (duplicate inline defs in TU = infra fault) |
| func_8017ECA8 | cov **§236-6 — its own exemplar, re-noted verbatim** |
| func_800CEFBC | cov §259-4 (the "undocumented class" IS documented: §236 + §259-4 — gap #6) |
| func_80181D20 | cov §28 (cited as line `§2329`) + §43/§94 block-scope practice (gap #5) |
| func_800CF370 | **ADD-3** (cross-binary same-name DIFFERENT-body defs; resident.c:281 verified) |
| func_8017DBD8 | cov §238 (wrong-function Ghidra seed) + §217 (stack-arg decode) |
| func_801884F4 | cov §259-4 |
| func_8018944C | cov **§254 — cited there by name** (3-arg, a1/a2 dead, caller-pinned arity) + §259-11/§236-4 (standalone include fact) |
| func_80180CE0 | cov §164-74 (self-cited) + §150-B (non-authoritative fleet row → ground-truth the callee's own .s) ⊕ |
| func_80180634 | cov §259-4 (session cut at submit boundary) |
| func_80180D14 | cov §259-4 |
| func_80183038 | cov §259-4 (unswapped INCLUDE_ASM slot = the revert face; splice never landed) |
| func_80181A98 | cov §259-4 + §215-9 (checked, inapplicable) |
| func_80180EE0 | cov §259-4 + §3-T4 (pre-if temp hoist is standard) |
| func_801820B0 | cov §251-2 (`&= ~0x10` → `addiu -0x11`) + §213/§226 (u16[3] as three statements) + §3-T2 |
| func_80182CF4 | cov §236-2 ⊕ (strongest DATA-symbol card: two incompatible block-scope decls + a file-scope third kills the TU; block-scope move cures) |
| func_8017E4D0 | cov §236-PROCEDURE (its 4-point checklist is §236's procedure) + §259-4 |
| func_801856C0 | cov §217 + §252-reading + §3-T4 + §239 (the "operand-swapped `*8+base`" = §239's plus-tree operand order) |
| func_80183BA0 | cov §164-59 (self-cited: callee return parked in mult→mfhi window) ⊕ |
| func_8017E0C0 | cov §259-4 |
| func_8018ACD4 | cov §162d1/§165-19 (named single-set temps; barrier-blocks-sink = §257-8 family) ⊕ |
| func_8017FE54 | cov §164-57/§195-F + §211 — **same function, same verdict as the previous batch** (dup re-mine) |
| func_800CEED0 | **ADD-1** (volatile REQUIRED on the head-interposed asm — bounds §257-8; A/B-proven this review) |
| func_8017F328 (ax) | **ADD-9** (case-body source order probed on the 29-case tree) + cov §55a/§222/§224 |
| func_8017F964 | **§268 card 1** (pins on $4/$2 honored — non-call-crossing ranges; strip = 14-mismatch) |
| func_801853F0 | cov **§224-addendum-4 — cited there by name** (goto target = innermost else-arm label) |
| func_801811D0 | cov §235 + **caution**: deliberate probe constant in a submission = §235's blind spot weaponized (banked tree carries the true `0x7FFFFFFF` — line 4535) |
| func_80180AE0 | cov law 2/§194-E (same-TU twin style cloning) |
| func_801A06E8 | cov §193-A/§194-E + §259-4 |
| func_801A9FA8 | cov §193-A + §259-4 ("len-vein" is card jargon, not a cookbook term — no gap) |
| func_80183740 | cov §165-17-correction (L19102: the temp's TYPE is the sched dial — u8 retype fixed the swap) + §194-D |

**Wave bm (41):**

| fn | verdict |
|---|---|
| func_8017F0A8 | **ADD-5** (s16 sign-test face; 3 rider components refuted by 4-way A/B — REF-5) + cov §222-add-1/§255 (3-case switch) + §224 (inline increment per case) + §76-family (named boolean) |
| func_801810CC | cov **§237-escape-2** (def-side asm-label alias "ALSO FOR A RETURN-TYPE CLASH" — the exact cure) + §43-L3217 (pedwarn drop) + §85/§73 + §236-8 ⊕; gap #2 (cited `§2535` = §38's line) |
| func_80181164 | **ADD-4** (§167-37 companion row: store INSIDE the arm — both alternatives measure 2-mismatch, A/B'd) |
| func_801A6A38 | cov §257-6/-9 (unpin first) + §229 ⊕ (negative face: plain store reorder does NOT drag the `la`) + §162c/§251(3) + §250 |
| func_8017D164 | **ADD-8** (§30a third column: `p++` vs cast-PLUS vs `p[k]`; bare-index A/B = 16-mismatch WIDTH/lhu!=lui) |
| func_8018BAC4 | **REF-2** (volatile-load lever inert by A/B) · pins load-bearing → §268 corroboration · select shape cov §194-B family |
| func_8017FDC4 | cov §176-B3 (self-cited) + §220-addendum (named temp bought a second s-reg) + §223 (j-rejoins-tail read) |
| func_8017DB9C | cov §193-A + §229 (`&D` passed by address) — self-declared no-gap |
| func_8017F2A4 | cov §238 (wrong-binary .s path) + §165-36 step-0 + §225-family grouping |
| func_8017E448 | cov §238 (wrong .s path — ov_SC07_001 homonym trusted half a session) + §211-addendum-4 (descending init = emission order) + §214 (twin literals never transfer) |
| func_80182AC4 | **ADD-7** (named single-set loop constant pins the prologue init order; literal = 4-mismatch cse profile, A/B'd) |
| func_8018A0E0 | cov §236 + §37 (block-scope asm aliases) + §259-4 |
| func_801F0D88 | **REF-4** (byte-offset-IV spelling inert by A/B — indexed form also MATCHes) · guard structure cov §10/§1412 · `match_one` prepends common.h = documented in the tool |
| func_8017F328 (bm) | **ADD-9** (same function as ax; the probe run once) + cov §55a (plain local; case bodies in source order) + §224 (cross-jump makes the shared tails) |
| func_8018687C | cov §3-T4 (bounded) + §165-L14292 tell (tie + sliding block = layout) + §5 (phantom frame) |
| func_8017D0AC | cov §193-A/§214 (twin constants don't transfer; store order per-card) |
| func_801818D4 | cov §193-A (byte-identical sibling transplant) + §238 (stale backlog draft discarded) |
| func_8017CDBC | cov §161c (self-cited) + §238 (seed invented the symbol) |
| func_800CB3D8 | cov §48-C2/§160a (8-word block = struct assign) + §229/§20 (named cross-call pointer) + §30 (u8\* unscaled) |
| func_8017E4A4 | cov §220/§220-addendum + §176-A · **REF-6 (wording)**: "parameter NAME = target register" — names are alpha-inert |
| func_801827A0 | cov §208 row 2 (self-cited; split call-result/final-value locals) ⊕ |
| func_800CAF24 | cov §3-T4 + §263-family (arg literal-vs-register error surfaces as LENGTH-DRIFT) + §193-A |
| func_800CB5DC | cov §193-A + §3-T2 (OR after byte stores = plain source order) |
| func_8017F01C | cov §3-T4/§247 (negated compare places the arms) + §199-E + §237 + §238 (wrong reference in prior session) |
| func_80182480 | **§268 card 2** ($16 pin as live-range shrinker; nopin = +2, frame 0x20 vs 0x18, A/B'd) + ADD-6 |
| func_801819BC | cov §256 (goto dispatch; positive `==2` goto → beq+j; shared store reached by fall-through) |
| func_8017FE78 | **REF-3** ($17 pin inert by A/B) · $16 pin load-bearing → §268 corroboration + ADD-6 · cast-call cov §237 |
| func_8017DFE4 | cov §238 (same-VA different-overlay transcript trap) + §176-A (both stores before the call) + law 2 |
| func_801A060C | cov §193-A/§194-E — self-declared no-gap |
| func_80181D08 | cov §252/§253 ⊕ (postfix-old-value axis reaches STORE PLACEMENT — second card for single-observation §253) + §213-3/§267-ADD-9 (anonymous struct by address) + §226-add (0x7FFF last) + §227 |
| func_8017F4C8 | cov §238 (target re-carved mid-task; re-read the .s after any interruption) |
| func_801856F0 | cov **§210 — the exact lever** (name the mask; `andi`+`sltiu` vs `srl/xori`) ⊕ my A/B is its second live gate; gap #1 |
| func_801A0DA4 | cov §251-2 (`addiu -0x5` reads as `&= ~0x4`, never `~0x5`) + §193-A |
| func_801862C8 | cov §243 (sh blocks CSE ⇒ re-derive inline, lw appears twice) + §234 (`-0x100000` for bare lui) |
| func_8017ED38 | cov §229/§20 (pointer-local for the u16 global RMW; bare `|=` = two lui/$at expansions) |
| func_8017F8C0 | cov §167-30 + §164-56/§167-31 + §194-D + §239 (named temp for `subu` operand order) — composition, no gap |
| func_8017D8D0 | cov **§162d1** ⊕ — supplies its missing independent A/B gate (two-statement form −1, mask folds into jal-2's slot) |
| func_801EFC30 | cov §195-D/§235 ⊕ (transposed-digit `jal` = false clean at 10 ins; the post-MATCH walk is not optional) |
| func_801835F4 | cov §164-73/§164-74 (stores-per-arm; no cross-bb CSE rematerializes the pointer per arm) |
| func_8017D7C4 | cov §220-addendum (raw `a0` self-reuse — self-declared standard) + §214 (macro twin) |
| func_80180150 | cov **§214-addendum** (twin is an INCLUDE_ASM stub ⇒ grep engine_core.h `DEFINE_` for the tail sequence — the exact retrieval note) |

---

## 1. Proposed new section

### §268 — A `register __asm__` PIN ON A CALL-CLOBBERED REGISTER IS HONORED EXACTLY WHEN THE PINNED RANGE CROSSES NO CALL (P31 S59c; three A/B'd cards, unifying §257-2's two)

**The symptom you see in a diff — two opposite faces.** Face A (§257-2's): you add a `$2`/`$4` pin
and the output does not move an instruction — the pin "is silently ignored." Face B (this batch's):
a REGALLOC-LOCAL / REGALLOC-PERM residual where values rotate through `$v0`/`$v1`/`$a0` and no
naming, ordering, or width spelling sticks — and a pin FIXES it, in a function that has calls, which
§257-2 says should not work.

**The mechanism (behavioral; both directions byte-proven).** The pin binds the variable to the hard
register only where the value's live range avoids calls. A range that crosses a `jal` cannot live in
a call-clobbered register, and gcc-2.7.2 neither errors nor saves/restores — it silently falls back
to ordinary allocation (that is §257-2's observed identical-to-unpinned output). A range that sits
**between** calls is honored fully, and inside that window the pin also steers first-fit for every
neighboring value. §257-2 is therefore not "pins on call-clobbered regs do nothing"; it is "pins on
call-CROSSING values do nothing." **Check which one you have before writing the pin off — or in.**

**The C spelling.** Pin only values born after one call and dead before the next:

```c
register s32 x __asm__("$4");
register s32 r __asm__("$2");
...
r = rand() & 0xF;                    /* born from $v0, used immediately */
x = *(u16 *)(s0 + 6) - 8;
*(u16 *)(s0 + 6) = x + (*(u16 *)(param_1 + 0x104) + r);   /* both dead before next jal */
```

**The evidence.**
- `func_8017F964` (ov_SC05_001, 45/45, banked, THREE calls): both pins' ranges are call-free windows.
  Solo strip → **14 mismatched, REGALLOC-LOCAL** (`$a0`/`$v0`/`$v1` rotate). Honored, load-bearing.
  A/B: `.run/s59_distill2/func_8017F964_{base,nopins}.c`.
- `func_8018BAC4` (ov_SC04_011, 32/32, banked, LEAF): `$2/$3/$4` pins, `$3` shared by two disjoint
  ranges (`r`/`x`). A leaf has no calls anywhere, so every pin is honored: strip → **+3
  LENGTH-DRIFT / 34 mismatched**. A/B: `func_8018BAC4_{base,nopins,bare}.c`.
- `func_80182480`/`func_8017FE78`: pins on CALLEE-SAVED `$16` — outside this law's register class
  (callee-saved pins are always honored) but confirming the strip-test discipline; see ADD-6.
- §257-2's `func_8018270C` / `func_8017F790`: `$2` pins on values living ACROSS calls → output
  identical to unpinned. Ignored. (Unchanged; now explained.)

**What was tried and failed.** The `func_8017F964` drafter burned its session on free-local
spellings and parenthesisations ("no free-local spelling reaches that assignment") — correct, and
now explained: inside a call-free window the assignment is local-alloc first-fit, which C spelling
barely reaches; the pin is the intended tool there. Conversely REF-5 of the previous batch
(`func_801816C8`) and this §'s Face A are the SAME test read in the other direction.

**Boundary and composition.** §257-6 still stands (pinning MORE than the target's callee-saved set
blocks `jal`-slot filling — pin only what allocation would choose anyway); §257-3 (pins on
parameters are a syntax error); §162p/§37 (a pin forfeits ×134 family propagation — try the unpinned
spelling first, §257-9). And compose with §266: before CREDITING a pin, strip it; before DISMISSING
one as a rider, check whether its range crosses a call. Grep bait: `pin ignored`, `pin did nothing`,
`call-clobbered pin`, `$2 pin rand`, `pin between calls`, `REGALLOC-LOCAL pins`.

### 1a. The §266 sweep — every solo-lever A/B run for this batch

All files in `.run/s59_distill2/`; every baseline re-verified MATCH before the strip.

| fn (banked ins) | lever stripped/varied | solo A/B result | verdict |
|---|---|---|---|
| func_8017F0A8 (91) | named shifted temp `t = v1 * 0x10000` → inline expr | **MATCH** | INERT RIDER |
| func_8017F0A8 | `* 0x10000` spelling → plain `(s16)v1 < 0` | **MATCH** | INERT RIDER |
| func_8017F0A8 | init-then-override → plain `if/else` select | **MATCH** | INERT RIDER |
| func_8017F0A8 | s16 sign test → raw s32 `v1 < 0` | DIFF −1, 61 mism. | load-bearing (semantic) |
| func_8018BAC4 (32) | `volatile` on the three `u8` loads | **MATCH** | INERT RIDER |
| func_8018BAC4 | the `$2/$3/$4` pins | DIFF +3, 34 mism. | load-bearing |
| func_800CEED0 (13) | `__volatile__` on the interposed asm | DIFF 5 mism. (sw $ra↔sll swap) | load-bearing → ADD-1 |
| func_80181164 (48) | store moved above the guard | DIFF 2 mism. | load-bearing → ADD-4 |
| func_80181164 | named local removed (§167-37 no-name form) | DIFF 2 mism. | load-bearing → ADD-4 |
| func_8017FE78 (52) | both `$16`/`$17` pins | DIFF +3, 46 mism. | load-bearing (as a set) |
| func_8017FE78 | `$17` pin alone | **MATCH** | INERT RIDER |
| func_801856F0 (24) | named mask temp → `return (s0&0x8000)==0` (and `!` form) | DIFF +1, 9 mism. (`srl/xori`) | load-bearing → §210 ⊕ |
| func_80182AC4 (27) | named `val = 1` → literal store | DIFF 4 mism. (cse profile) | load-bearing → ADD-7 |
| func_8017D8D0 (28) | one-expression rand-sum → two statements | DIFF −1, 22 mism. | load-bearing → §162d1 ⊕ |
| func_8017F964 (45) | `$4`/`$2` pins | DIFF 14 mism. REGALLOC-LOCAL | load-bearing → §268 |
| func_80182480 (22) | `$16` pin → plain local | DIFF +2, 21 mism. (frame 0x20≠0x18) | load-bearing → ADD-6 |
| func_801F0D88 (33) | byte-offset IV → indexed `D[i][0]`, `i++` | **MATCH** | INERT RIDER |
| func_8017D164 (20) | cast-PLUS → bare `p[k]` index | DIFF 16 mism. WIDTH/lhu!=lui | load-bearing → ADD-8 |
| func_8017F328 (307) | case 2/3 SOURCE blocks swapped | DIFF 1 mism. IMM-OFFSET/−8 | load-bearing → ADD-9 |

**6 of 19 credited levers are riders (32%)** — the same one-in-three rate §266 measured on the
previous batch (4 of 8). The harvest-note convention ("banked WITH X; X not solo-A/B'd") is not yet
being followed by drafters; every rider above arrived stated as a certainty.

---

## 2. Proposed addenda (append each under its named section)

### ADD-1 → §257-8 addendum — THE INTERPOSED ASM'S `__volatile__` IS A PER-SHAPE DIAL, AND THE "NO-OUTPUT ASM IS IMPLICITLY VOLATILE" LORE IS BYTE-FALSE IN gcc-2.7.2

§257-8 records that §16x's interposed-asm prologue lever DIES under `__volatile__` and only the
non-volatile `__asm__("" :: "r"(arg))` flips the save pair (`func_80186C0C`, banked twice). The
opposite polarity is now equally byte-proven: `func_800CEED0` (md_MAIN_003, 13/13, banked) needs the
prologue order `sw $ra` FIRST and gets it **only with** `__asm__ __volatile__("" : : "r"(idx))` on
the `$2`-pinned incoming index; the non-volatile spelling swaps `sw $ra` below the `sll` (5
mismatched, OPCODE-MIXED — A/B `.run/s59_distill2/func_800CEED0_{base,novol}.c`). Two corollaries:
(1) the volatile-ness of an interposed asm is a per-shape ~20-second A/B, not a rule — do not carry
either polarity between functions; (2) the folk rule "an asm with no outputs is implicitly volatile"
does NOT hold behaviorally in this cc1 — the explicit keyword changes scheduling. Grep bait:
`interposed asm volatile`, `prologue save order asm`, `sw $ra first`.

### ADD-2 → §236 addendum (item 1 corollary) — THE SILENT-SPLICE DECLARATION LADDER: WHERE THE TU HAS NO SPELLING, UNPROTOTYPED `()` BEATS THE FLEET VOTE

§236-1 says in-TU beats fleet consensus, always. The vacuum case needed stating: at a splice point
where the TU carries NO declaration for a callee (defined below, never declared above), the robust
default is the **unprototyped `()` extern for every callee** — C89-composite with any later
prototype or definition, immune to §236's classes 1/3/5/8. Copying the atlas/fleet def-signature
instead is what failed the gate once on `func_801824E4` (ov_SC02_031, 63 ins — atlas
`('void',('void*',))` lifted, gate red; `()` banked). `func_8017FCBC` (ov_SC03_030, 230 ins)
corroborates: canon votes for its callee come from OTHER binaries' same-address functions (§150-B),
so a prototyped canon lift would be actively wrong; `()` vs prototyped verified byte-neutral. The
ladder: in-TU spelling > unprototyped `()` > fleet vote — the fleet is LAST even in a vacuum
(§196's loss extended). Grep bait: `no in-TU spelling`, `undefined splice point`, `unprototyped
default`, `fleet vote vacuum`.

### ADD-3 → §238 addendum — TWO BINARIES CAN EACH DEFINE THE SAME `func_` NAME WITH DIFFERENT BYTES, AND NO GENERATED REPORT SHOWS IT

`func_800CF370` is defined in `src/md_MAIN_003/md_MAIN_003.c:141` (13 ins, this card's bytes) AND in
`src/resident/resident.c:281` with contradicting content — both correct for their own binaries
(separate links; resident's own comment admits its disassembly matches neither image).
`duplicates.cross.md` inventories only byte-IDENTICAL groups, so a byte-DIFFERENT same-name pair is
invisible to every generated report, and a "reconcile" toward either side silently breaks the other
binary. This is §150-B's "same address + same name ≠ same body" restated at the DEFINITION level:
before trusting an in-TU splice for a `func_800xxxxx`/shared-address symbol, grep the
sibling-binary TUs (`src/resident/`, other `src/md_MAIN_*/`) for a second definition, and never
conform one binary's def to another's. Grep bait: `cross-binary duplicate`, `same name different
bytes`, `resident twin`, `reconcile trap`.

### ADD-4 → §167-37 addendum — THE FIFTH PRECONDITION, NOW MEASURED: DOWNSTREAM FIELD RE-READS ⇒ NAME IT **AND** STORE **INSIDE** THE ARM

§167-37's boundary note ("do not widen past its four preconditions") now has its byte-proven
counter-case. `func_80181164` (ov_SC05_005, 48/48, banked): same three-line shape (call result,
stored to `+0x20`, null-guarded, handed to the next call) **plus** downstream uses through five
field re-reads — and the target's store sits in the **`jal`'s slot inside the else arm** (`addu
$a0,$v0` in the `bnez` slot, `sw $a0,0x20($s0)` in the call's slot), not in the guard's slot. Both
prescriptions §167-37 would suggest measure 2-mismatch by solo A/B: the no-local store-and-re-read
form AND the named-local store-before-guard form each swap `sw`↔`move` at idx 6/14
(`.run/s59_distill2/func_80181164_{preguard,noname}.c`). The winning spelling names the result and
places the store between the guard and the first consuming call, inside the arm. **Read the store's
HOME first:** store in the GUARD's slot ⇒ unconditional, §167-37/§252-reading (write it before the
`if`); store in the ARM's call slot ⇒ conditional, this row (write it inside the arm). Mechanism per
§48-A4: the named local dies at the second call's argument setup, so its range crosses zero calls
and takes the arg-register copy preference; dbr then fills both slots. Grep bait: `store inside the
arm`, `sw in jal slot inside arm`, `name nothing failed`, `167-37 counter`.

### ADD-5 → §267-ADD-6 / §172b-1 addendum — THE SIGN-TEST FACE: `(s16)v < 0` IS `sll 16` + `bgez` ON THE SHIFTED COPY, RAW STAYS LIVE — AND THE HALFWORD-ABS SHAPE NEEDS NO RITUAL

ADD-6 (§267) gave the ZERO-test face (`(x<<16) != 0`). The SIGN face: testing `(s16)v < 0` —
equivalently `(v << 16) < 0` or `v * 0x10000 < 0` — emits a lone `sll $t,$v,16` feeding
`bgez`/`bltz` on the SHIFTED copy with **no `sra`** (only the sign is needed), while raw `v` stays
live for both arms. The halfword-abs composition seen on `func_8017F0A8` (ov_SC03_092, 91/91,
banked) — `subu; sll 16; bgez (slot: addu $a0,raw); negu $a0,raw` — is reached by ANY select
spelling over that test: named-shifted-temp, inline expression, `(s16)` cast, and plain
`if/else` all compile byte-identical (4-way A/B, `.run/s59_distill2/func_8017F0A8_*.c`). The ONLY
load-bearing choice is the semantics: the raw s32 test `v < 0` drops the `sll` and drifts −1. The
drafter's "two-liveness" construction (`t = v1 * 0x10000; a0 = v1; if (t < 0) a0 = -v1;`) is three
inert riders around one s16 cast — do not transcribe the ritual into future drafts. Reading rule: a
`bgez` on a freshly-`sll`'d copy whose ARMS use the unshifted register = abs/negate-select of the
low halfword; write `if ((s16)x < 0)` and any select shape. Grep bait: `sll 16 bgez`, `abs idiom`,
`negu delay slot abs`, `sign test halfword`, `two liveness`.

### ADD-6 → §220-addendum — THE FOURTH FACE: WHEN THE NAMED COPY ITSELF BUYS THE EXTRA CALLEE-SAVED, PIN THE COPY TO `$16`

§220-addendum's three faces end at "an explicit named local is the reliable way to pin a
callee-saved copy." The fourth face: sometimes the plain named copy is what OVERSHOOTS — parameter
pseudo and copy each take a callee-saved register. `func_80182480` (ov_SC03_098, 22/22): plain
`s32 s0 = arg0;` → +2 LENGTH-DRIFT, frame 0x20 vs 0x18, extra `$s1` save/restore;
`register s32 s0 __asm__("$16"); s0 = arg0;` banks — the pin unifies copy and home so the parameter
pseudo dies at the copy. `func_8017FE78` (ov_SC02_017, 52/52) is the same face at two registers:
stripping both pins costs +3 with the whole s-register file shifted (`$s0`→`$s1`, constant→`$s2`).
Both solo-A/B'd (`.run/s59_distill2/func_80182480_nopin.c`, `func_8017FE78_nopins.c`). Distinct
from §136d-1 (pin-as-CSE-defeat): this pin SHRINKS a live range. Compose with §266 — FE78's second
(`$17`) pin was a rider (strip-tested MATCH); pin the copy, not the constants. And the standing
tax: a pin forfeits ×134 propagation (§162p) — try §220's plain-parameter form first; reach for the
pin only when the plain copy demonstrably buys the extra register. Grep bait: `pin the copy`,
`extra callee-saved from local`, `s16 pin live range`, `frame 0x20 vs 0x18`.

### ADD-7 → §229 addendum — THE VALUE FACE: A LOOP-STORE CONSTANT SPELLED AS A LITERAL HAS NO SOURCE POSITION; NAME IT TO PIN THE PROLOGUE INIT ORDER

§229's law is stated for ADDRESSES. The same birth-order mechanism reaches a plain constant:
`func_80182AC4` (ov_SC01_080, 27/27, banked) needs the prologue order `la $a1(D_801C7560)`,
`li $a2,1`, `li $v1,3`, `la $v0(D_801C755C)`. Writing the loop store as literal `*p = 1` leaves the
constant with no statement of its own — gcc materializes it at its own rank and the surrounding
address setups re-order (4 mismatched, ADDRESSING/lui!=addiu, profile=cse — A/B
`.run/s59_distill2/func_80182AC4_lit.c`). A single-set named local (`val = 1;` before the loop,
`*p = val;` inside) gives the constant a birth position, and §3-T2's source-order law then governs
all four inits. Boundary note for §3-T2: a literal OPERAND is not a statement — source order cannot
place what has no statement. Grep bait: `literal loop constant`, `prologue init order`, `li reordered
against la`, `name the constant`.

### ADD-8 → §30a addendum — THE THIRD COLUMN: `*p++` IS ALSO SERIALIZED BUT BURNS `addiu`; ONLY CAST-PLUS GIVES SERIALIZATION *AND* DISPLACEMENT FOLDING

§30a#1 documents that `*(T*)((s32)p + k)` denies `/s` (NOP_EXPR over the PLUS) while bare `q[k]`
grants it. Complete the matrix with the third spelling and the codegen-shape consequences, from
`func_8017D164` (ov_SC01_000, 20/20, banked — six lockstep lhu/lui/sh pairs):

| spelling | `/s` | consequence |
|---|---|---|
| bare `p[k]` | granted | loads hoist above the aliasing stores into a 3-load cluster — 16 mismatched, WIDTH/lhu!=lui (A/B `.run/s59_distill2/func_8017D164_index.c`) |
| `*p++` | denied | serialized, but real `addiu` pointer steps materialize — LENGTH-DRIFT (+2 per drafter's bracket) |
| `*(u16*)((s32)p + k)` | denied | serialized AND `combine` folds `k` into the load displacement — zero extra instructions; the only column that matches a lockstep copy chain |

Grep bait: `p++ addiu burn`, `cast plus displacement`, `serialized field copy`, `three spellings
aliasing`.

### ADD-9 → §255 "AND CASE-BODY PLACEMENT" bound / §222-addendum-3 — ON A LARGE SPARSE TREE, BODIES FOLLOW **SOURCE** ORDER (measured by a one-word probe)

§255 states case bodies emit in DFS order (root body first) and §222 holds source order for dense
switches. Measured on the 29-case sparse balanced tree `func_8017F328` (ov_SC01_001, 307/307,
banked): swapping the SOURCE positions of the `case 2:`/`case 3:` blocks (identical instruction
shapes, only masked symbols differ) moves exactly ONE unmasked word — the dispatch `beq`'s target
(1 mismatched, IMM-OFFSET/−8; A/B `.run/s59_distill2/func_8017F328_swap23.c`). Bodies are laid in
source order here, and the drafter's recovery rule holds: **the tree's `beq` targets, read in
ascending physical order, name the source case sequence.** Both regimes now have measured
exemplars — when reading a switch, recover case VALUES from the `beq`/`slti` chain (per §255), and
recover BODY order from the physical layout only on the source-order regime; when transplanting a
big switch, preserve the source case order exactly. Grep bait: `case body order`, `switch source
order probe`, `beq targets name cases`.

### ADD-10 → Cross-confirmation card block (per §259's standing instruction: confirmation, not news)

- **§210** ← `func_801856F0` (bm, 24/24) — second live gate for name-the-mask, at the `== 0`
  polarity (`sltiu $v0,$v0,0x1`); both direct spellings (`(x&M)==0`, `!(x&M)`) measure +1 with the
  `srl 15/xori/andi` extract. The section's two fixes stand exactly.
- **§162d1** ← `func_8017D8D0` (bm, 28/28) — the missing independent A/B its own text asks for:
  two-statement split = −1 (first mask folds into jal-2's slot, cross-call `addu $s0,$v0` copy
  deleted); the one-expression sum is load-bearing.
- **§237-escape-2** ← `func_801810CC` (bm) — strongest return-axis-only card yet: stale `void`
  self-decls left by BANKED CALLERS (:4650/:4700), cured in-body by the def-side
  `__asm__("func_801810CC")` alias; the §85 widen verified as the alternative. Also a process
  fact worth §236-8's margin: fixes prescribed in NOTES never reach the gate — the cure must ride
  in the submitted code.
- **§257-6** ← `func_8017F10C` (ax; its own third note) and `func_801A6A38` (bm; "first thing to
  try on a redraft-lever card: the unpinned direct spelling" — §257-9 restated).
- **§236-2** ← `func_80182CF4` (ax) — the DATA-symbol face: two incompatible block-scope decls of
  `D_801888B0` in sibling functions + a new file-scope extern = whole-TU cc1 death with a green
  oracle; moving the three data externs to block scope cured it.
- **§150-B** ← `func_80180CE0` (ax; a non-authoritative fleet row `('s32',...)` for a callee whose
  own `.s` proves `void` — ground-truth unbanked callees against their `.s`) and `func_8017FCBC`
  (ax; address-taken array beats the scalar plurality).
- **§253 / §165-06** ← `func_80181D08` (bm) — second card for single-observation §253: the
  postfix-vs-compound axis also decides STORE PLACEMENT (`var = (*p)++;` keeps the store after the
  `mfhi`/`bnez` pair in its own slot; bare `++`/pre-increment sink it before the div).
- **§235 / §195-D** ← `func_801EFC30` (bm) — a transposed digit in a `jal` symbol
  (`func_80116714` for `func_80016714`) scored MATCH at 10 ins; the post-MATCH relocation walk is
  not optional at any size. Plus the §235 boundary caution from `func_801811D0` (ax): a deliberate
  probe constant in a SUBMISSION weaponizes the same blind spot — probes belong in scratch A/Bs;
  the whole-binary gate is unmasked (the banked tree carries the true `0x7FFFFFFF`).
- **§229** ← `func_801A6A38` (bm; negative face: reordering plain stores does NOT drag the
  hoisted `la` down — address birth position is independent of its consumers' statement order).
- **§164-59** ← `func_80183BA0` (ax). **§251-2** ← `func_801A0DA4` (bm; `addiu -0x5` reads
  `&= ~0x4`, never `~0x5`) + `func_801820B0` (ax; `&= ~0x10` → `addiu -0x11`). **§243** ←
  `func_801862C8` (bm; an intervening `sh` blocks CSE ⇒ the double `lw 0x20` is inline re-derivation,
  not a local). **§164-73/-74** ← `func_801835F4` (bm). **§214-addendum** ← `func_80180150` (bm;
  stub twin ⇒ grep `DEFINE_` in engine_core.h by tail sequence). **§254** ← `func_8018944C` (ax;
  already cited there). **§224-addendum-4** ← `func_801853F0` (ax; already cited there).

---

## 3. Refuted claims (checked and found wrong — do NOT let these harden into laws)

Four refuted by **live `match_one` A/B against the banked body** (files in `.run/s59_distill2/`),
one by artifact, one definitional. Rate check: 6 of 19 solo-tested levers were riders — the same
one-in-three §266 measured last batch.

1. **`func_8017FB04` (ax): the bgez/OR-fallthrough/two-entry-merge analysis and its "§199-F is
   byte-inert here" lever list.** MIS-ATTRIBUTED, for the SECOND consecutive batch — the note's
   subject (lh `D_80126CB0+0x300`, 8×ctc2, rtps hazard nops, the bgez tail) is ov_SC03_030's
   HANDWRITTEN homonym (previous batch REF-3; §265's cautionary tale, "no compiler law can be
   extracted from hand-written asm"). The note is not even a MATCH (LENGTH-DRIFT/−4). Harvester
   hygiene: the wave file's verdict column must gate candidacy.
2. **`func_8018BAC4` (bm): "the volatile-load lever — `*(volatile u8*)pa` makes the load
   non-substitutable by combine, so x survives as a real pseudo that first-fit grants $v1; two pin
   placements were silently ignored."** INERT RIDER — the banked body minus every `volatile`
   MATCHes 32/32 with the pins present; stripping the PINS instead breaks it (+3 / 34 mismatched).
   The attribution inverts: the pins are the lever (leaf function — §268), the volatile carries no
   bytes. The claimed combine mechanism does not operate in the banked context.
3. **`func_8017FE78` (bm): "an early-constant-in-s1 prologue is what forces the twin-style
   `register s32 s1 __asm__(\"$17\")` declaration."** INERT RIDER — removing the `$17` pin alone
   still MATCHes 52/52 (the constant colors to `$17` by itself once `$16` is pinned). The
   load-bearing pin is `$16` on the pointer copy (both off = +3). ADD-6 records the true rule.
4. **`func_801F0D88` (bm): "a plain counted for-loop over an array of structs degrades to dual
   walking pointers vs a single scaled IV depending purely on source spelling."** NOT REPRODUCIBLE —
   the indexed spelling (`D_801F8334[i][0]`, `i += 1`, bound `i < cnt`) also MATCHes 33/33 under the
   same `if (cnt>0) do..while` guard. The IV spelling is byte-inert here; whatever the failing
   intermediate did differently (likely the guard/do-while structure, §10/§1412, or the C89 decl
   errors the note also reports), it was not this. The claimed §246-row addendum is withdrawn.
5. **`func_8017F0A8` (bm): "neither `if (x<0) x=-x` nor any conditional-expression spelling
   produces this; what does is keeping TWO livenesses: `t = v1 * 0x10000; a0 = v1; if (t < 0)
   a0 = -v1;`."** THREE of the four components are riders (named temp, `*0x10000` spelling,
   init-then-override — all strip-tested MATCH); the only load-bearing content is testing the s16
   sign rather than the s32 sign (`(s16)v1 < 0` MATCHes; raw `v1 < 0` drifts −1). The salvage is
   ADD-5. "Worth a section" as written would have shipped a three-part ritual.
6. **`func_8017E4A4` (bm, wording-grade): "parameter stays a plain s32 NAMED a0 — naming it a2 or
   pinning $6 produced a spurious extra copy."** A C variable's NAME cannot reach codegen —
   renaming is alpha-conversion, byte-inert by construction. The substantive dial is §220's
   plain-param-vs-named-copy (cov). Flagged so "name your locals after target registers" never
   hardens into lore; no A/B spent (definitional).

---

## 4. The discovery-gap list (knowledge existed; the drafter did not find it)

1. **`func_801856F0` (bm)** — needed the `andi K`+`sltiu` vs `srl n`+`xori` dial; grepped
   "boolean-tail idioms", wrote "not in the cookbook under the names I grepped". It is **§210**,
   whose title contains the exact instruction pair. *Index fix: add the literal strings
   `andi sltiu`, `sltiu 0x1`, `single-bit return`, `bit test ==0` to §210's symptom line.*
2. **`func_801810CC` (bm)** — found the asm-label cure but cited it as "§2535 asm-label pattern"
   (a cookbook LINE inside §38's memcpy note); the governing entries are **§237-escape-2 / §124 /
   §37**. The L→§ alias table now exists — wave prompts should name
   `tools/cookbook_index.py --resolve <N>` beside the "grep the index first" line.
3. **`func_8017F0A8` (bm)** — cited "§16011/§15367" (line numbers inside §167) for the negu
   coverage. Right reading, broken citation form — same fix as #2.
4. **`func_801F0D88` (bm)** — cited "§10813/10814" for the do-while guard law; those LINES resolve
   to §156 (preference-donor merge), an unrelated section. The knowledge is §10/§1412. Stale line
   citations are actively misleading, not just unfindable.
5. **`func_801A06AC` / `func_80181D20` (ax)** — cited "cookbook s1144/s1284" (→§14/§14d) and
   "§2329" (→§28). Same class as #2-4.
6. **The ax gate-null cluster (~20 cards)** — several state "no documented class exists for
   match_one-MATCH-but-no-bank" (`func_800CEFBC`, `func_800CF078`, `func_80180D14`,
   `func_80181A98`…). The class IS documented — §236 (nine ways + PROCEDURE) and §259-4 — and
   landed in the S58b commit these sessions predate or missed. Same recommendation as the previous
   batch: re-issue drafter prompts pointing at §233-§259 so the standing complaint stops recurring;
   these cards' honest audits are otherwise §259-3-grade compliance reports.
7. **`func_8018944C` (ax)** — called the missing `#include "common.h"` an undocumented
   bank-failure class; it is the §259-11/§236-4 standalone-harness fact (and `match_one` itself
   documents that it prepends common.h — `tools/match_one.py:146`).
8. **`func_8017D8D0` (bm)** — searched near §55a for the cross-call-lifetime rule; it is §162d1
   (indexed under "anonymous temp single-set"). *Index fix: add `call pair one expression`,
   `two rand sum`, `mask folded into jal slot` to §162d1's row.*
9. **`func_8017F10C` (ax)** — "no section states that over-pinning is itself the blocker" —
   **§257-6 states exactly that and cites this function's own two earlier notes.** The flywheel
   wrote the lesson; the drafter did not find the dead-end ledger. *Index fix: key §257's rows
   individually (at minimum `pin blocks delay slot`, `volatile fence breaks packing`).*

---

## 5. Plain-language summary for the reviewer

Of 82 notes, 67 are already written down — this batch's coverage rate (82%) sits between the
previous batch's 88% and the §233 harvest, and five of its "cookbook did not tell me" complaints
name sections that cite the very same function. The §266 sweep is the headline: 19 credited levers
were strip-tested against their own banked bodies, and 6 — a third, the same rate as last batch —
are inert riders shipped as certainties, including one whole proposed section (the "two-liveness
abs ritual") that dissolved into a single `(s16)` cast. The sweep also produced the batch's one
genuinely new law: **§268**, which turns §257-2's "pins on call-clobbered registers are ignored"
into a usable rule with a precondition (ignored only when the pinned range CROSSES a call — honored
and load-bearing between calls, proven live on two cards and refuted-by-strip on none). Two §257
dead-end rows gained byte-proven bounds (ADD-1's volatile dial; §268 itself), and eight further
addenda land measured corrections: the §167-37 counter-case, the §30a third column, the §255
source-order probe, the §220 pin-the-copy face, the §229 value face, the §236 silent-splice ladder,
and the cross-binary duplicate-definition trap. Six claims were refuted outright — five by live
A/B — and the batch confirms the standing process gaps: drafters still cite cookbook line numbers
as section ids, and one non-MATCH handwritten-homonym card leaked past the harvest filter for the
second batch running.
