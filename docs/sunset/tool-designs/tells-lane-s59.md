# Tells lane S59 — measured taxonomy, byte-proven idioms, and the path to 75%

**Investigation date:** 2026-08-24 (P31 S59). All artifacts under `.run/s59_tells/` (inventory,
re-run results, streams, gap scans, and every probe `.c`). Nothing in `tools/` or `src/` was
edited; every change below is a proposal.

**The one-line answer:** the tells lane is not failing on the tells. It is failing on (1) a
**discovery gap** — the card vocabulary (`extend-tell`) has zero hits in the cookbook, so 650
transcripts grepped and missed; (2) **stacked micro-idioms** — a tells function carries 3–5
independent gcc-2.7.2 spelling laws, and missing any one reads as LENGTH-DRIFT; (3) **pipeline
losses** — 26% of in-band failures are drafts that already shape-match and reloc-agree, lost at
gate/integration, and another 12% are permuter-bucket residuals no permuter ever visits; and
(4) **budget caps** — 36% of final attempts ended at the turn/cost cap, not at surrender.
5–50 ins is cumulatively at 75% already; 50–80 needs only the pipeline fixes; 80+ is where the
real wall is, and 75% there is NOT supported by current evidence.

---

## 1. Denominators (assert before believing any rate below)

Completed tells-lane waves at analysis time: **ao, as, at, au, aw, az, bb, bd, bg, bi** (wave bk
was in flight and is excluded; `at` was a mixed draw that also carried non-tell levers).
Cards → `.run/wave_??_cards.json`; drafts → `.run/wave_??/shard*/`.

| population | count |
|---|---|
| unique (binary,fn) carded across those 10 waves | 1,120 |
| … of which carry a tell lever (extend 406 / swaprepeat 46 / s16-div 3) | 455 |
| banked by now (INCLUDE_ASM gone from the card's TU, any wave/retry) | 730 |
| still open | 390 |
| still open **with a draft on disk** (newest per fn) | 270 (29,784 ins, median 91) |
| still open with **no draft ever** (worker exhaustion; 43 UNKNOWN / 38 head-crack / 28 extend-tell) | 120 (10,437 ins) |
| of the 270 re-run through `match_one --json`: | **near 216 · shape-MATCH 45 · toolfail 9** |

Re-run harness: `.run/s59_tells/rerun.py` (12-way, `--work` private per binary). "Banked" was
derived from the live tree (a campaign is banking concurrently, so a function open NOW definitely
failed its waves; one banked later by another lane counts as banked — the right population for
"what does the lane still need").

## 2. The residual taxonomy, measured

`tools/residual_class.py` verdicts over the 216 nears (count / instructions at stake):

| klass | extend-tell | swaprepeat | s16-div | non-tell riders | share of nears |
|---|---|---|---|---|---|
| LENGTH-DRIFT | 105 / 12,901 | 11 / 1,577 | 1 / 110 | 23 / 3,465 | **65%** |
| OPCODE-MIXED | 20 / 2,014 | 1 / 102 | — | 7 / 766 | 13% |
| SIZE-MISMATCH (redraft: wrong body) | 5 / 511 | 2 / 292 | — | 4 / 505 | 5% |
| SCHEDULE-REORDER | 6 / 496 | 1 / 76 | — | 3 / 225 | 5% |
| WIDTH | 2 / 178 | 1 / 51 | — | 5 / 388 | 4% |
| REGALLOC-PERM | 4 / 371 | 2 / 204 | — | — | 3% |
| ADDRESSING | 5 / 559 | — | — | 1 / 45 | 3% |
| other (REGALLOC-LOCAL, IMM-VALUE, BRANCH-POLARITY, DELAY-SLOT, STRENGTH) | 4 | 1 | — | 3 | 4% |

Buckets: **permuter 21** (16 of them at closeness ≤ 8), **structural 184**, **redraft 11**.

**LENGTH-DRIFT decomposed** (`.run/s59_tells/ld_scan.py`, greedy resync alignment over the
`--emit-streams` word pairs, 140/140 scanned): gap mass ≤ 3 words: **31** · 4–8 words: **55** ·
> 8 words: **54**. So under half of the dominant class is "one construct spelled wrong"; the rest
are wrong *regions* — misread bodies, which no cookbook section fixes.

**Construct-delta measurement** (170 tell-lever nears, draft-minus-target counts,
`.run/s59_tells/analyze3.py`): drafts run SHORT (Σdlen −417; 78 short vs 46 long), with fewer
`lh` (−79), fewer `sll` (−64), smaller frames (Σ −288 bytes, 39 drafts smaller vs 15 larger), and
MORE nops (+60). **`d_extpair = 0` for 74% of failing extend-tell drafts** — the sll/sra pair
count is usually already right. The standing mental model "tells drafts miss the extend pairs" is
refuted; what they miss is *placement* (which side of a branch/jal, fold-vs-materialize) and the
surrounding fold/alloc laws. The bodies are systematically too *clean*: the original source's
redundancy (textual repeats, mirror variables, opaque bound locals) is load-bearing and the
drafts don't write it.

## 3. The discovery gap (why the cookbook isn't reaching the drafts)

From the 796 transcripts behind still-open fns (`.run/s59_tells/mine_transcripts.py`):
650 grepped the cookbook, 524 read sections — the harness works. But:

- **`grep 'extend-tell'` — 108 times. `grep 'swaprepeat'` — 28 times. Both have ZERO hits** in
  `docs/matching-cookbook.md` (verified). `s16-div-tell`: zero. `grep '172'`: **zero** attempts.
- The knowledge exists at §172a (L16557) / §172b (L16573) under *different words*
  ("sll/sra-16 pair tell", "swapped-arm select tell", "extendhisi2 is MEM-only") — invisible to a
  model searching the only vocabulary it was given.
- The card's entire statement of the lever is `tools/api_agent.py:384-385`:
  `"The atlas labels this card's lever: extend-tell."` — no meaning, no §, no recipe.

The agents' own submit notes (1,101 collected, 420 deduped, 274 non-MATCH,
`.run/s59_tells/submit_notes.json` / `near_notes.json`) repeatedly *re-derive* §172b from the
bytes ("target splits the counter's sign-extend as lhu; sll [delay slot]; sra; slt — every
spelling I reached folds to lh", ov_SC02_005 func_8018A6A0) and then plateau without the recipe.

## 4. Byte-proven idioms (each verified with `match_one` this session; probes in `.run/s59_tells/`)

The whole-binary gate remains the arbiter — these are relocation-masked standalone MATCHes with
the symbol walk done by hand against each target's own reloc lines (law 1c).

### 4.1 `func_8017D8E8` (ov_SC03_108, 33 ins) — near-2 pin-transcription → **MATCH**
Draft `.run/wave_bg/shard114/func_8017D8E8.c` pinned EIGHT registers (incl. caller-saved
$2/$3/$4-$6) to transcribe the asm 1:1 and plateaued at near-2 over 23 oracle calls. Natural C
matched (`.run/s59_tells/fix_8017D8E8.c`):
```c
void func_8017D8E8(s32 arg0) {
    s32 i;  u16 *tbl;
    for (i = 0, tbl = D_8018476C; i < 4; i++)
        func_8012C658(0x199,
            (s16)((i << 10) + *((u16 *)((*(s16 *)(arg0 + 0x70) << 3) + (s32)tbl) + i)),
            arg0);
}
```
Levers, in order of necessity: **(a)** the `(s16)` promotion spelled INLINE in the call argument —
its `sra` lands in the jal delay slot (a temp kills this); **(b)** the table base as a *source
pointer local* so it owns `$s2` across calls (cookbook L2425 rule 1 — gcc-2.7.2 has no cross-bb
CSE); **(c)** `p[i]` indexing so `(field<<3)+base` stays one association unit (writing
`base + f8 + i2` lets fold re-associate the constant out); **(d)** comma-init order `i` then
`tbl`; **(e)** `lh` = read the s16 field directly in the expression (§172a).

### 4.2 `func_801808AC` (ov_SC05_018, 67 ins) — prologue save-order swap → **MATCH**
Draft `.run/wave_bg/shard117/…` plateaued at near-2: `sw $s1` emitted before `sw $ra` (target:
$ra first). 43 match_one calls; its cookbook greps were "frame size", "delay slot|reorg" — wrong
vocabulary. Root cause (sched.md S7 + `sched.c`): saves are emitted descending-regno and woven at
sched2; an anti-dependence from a **bb0 write of $s1** promotes `sw $s1`. The draft's
`i = 0; if (tbl == &A) goto found; i = 1; …` places `i = 0` in bb0. The else-if spelling moves
every `i = K` into its own arm, bb0 stays clean, the fixed order survives:
```c
if (tbl == &D_801B3DC4) i = 0;
else if (tbl == &D_801BBAB8) i = 1;
else if (tbl == &D_801C29C4) i = 2;
else if (tbl == &D_801CB724) i = 3;
else return;
```
(`.run/s59_tells/fix_801808AC.c`, MATCH 67/67.) **General law, new to the cookbook:** a
save-order-only residual ⇒ find which callee-saved reg is written in bb0 and move that first
write into a branch arm (set-in-arm vs set-then-test). reorg then re-creates the target's
`addu $s1,$zero` in the beq delay slot by thread fill.

### 4.3 `func_80180E58` (ov_SC06_000, 34 ins) — LENGTH-DRIFT/−1 stack → **MATCH**
Draft (near-20, pinned $5/$6/$7) vs natural C (`.run/s59_tells/fix_80180E58.c`):
```c
void func_80180E58(u8 *self) {                 /* (a) param IS the variable */
    s32 amt = 0xFFFE4000;  u16 *p = (u16 *)&D_801274EA;
    s32 lim; s32 t; s32 d; s32 v;
    d = *(u16 *)(self + 0xA) - 0x300;          /* (b) fold-blocker temp     */
    t = *p - d;
    v = *(s32 *)(self + 0x204) + amt;
    *(s32 *)(self + 0x204) = v;
    lim = 0x10000;                             /* (c) opaque bound, late    */
    if (v < lim) *(s32 *)(self + 0x204) = lim;
    *p = *p - *(u16 *)(self + 0x206);
    if ((s16)t < 0) { *(s32 *)(self + 0x200) = 0x1E; func_80171990(self); }
}
```
**(a)** Use the *parameter* as the multi-use variable — its expand-time parm copy
(`addu $a2,$a0`) survives exactly when `$a0` is re-used (here by `t` and the call's own arg
copy); a separate `self = arg0` local emits double moves, and a `$6` pin blocks `t` from taking
`$a0` and lets cse pass the raw param to the call (killing the target's `addu $a0,$a2` slot
fill). **(b)** `a - (b - K)` gets distributed by fold; a named temp for the inner term keeps the
target's `addiu −0x300; subu` shape. **(c)** `if (v < 0x10000)` and `if (v <= 0xFFFF)` BOTH
canonicalize to `li 0xFFFF; slt(0xFFFF,v); bnez` — the target's `lui 0x10000; slt(v,K); beqz`
plus the store *reusing the same register* is only reachable with the bound in a local; assign it
LATE so its live range starts after the block temps die (assigned at the top it allocates $a1,
not $v1). **(d)** `(s16)t < 0` emits `sll 16; bgez` (sra elided) for free.

### 4.4 `func_8018A6A0` (ov_SC02_005, 76 ins) — §172b-1's C recipe made concrete
Draft's compare `(vec0[1] << 15 << 1)` → structural STRENGTH/lhu!=sll. `(s16)vec0[1]` → a fresh
`lh` (the compare sits after a two-predecessor label; store-forwarding cannot cross it). The
target's naked `sll/sra` pair on a REGISTER is a **branch-merged multi-def variable** — §172b-1's
"like `mw`", spelled:
```c
vec0[1] = w = *s1;              /* entry def */
…
w = vec0[1] + *(u16 *)(s1 + 2); /* loop def: lhu (real mem re-read) + addu */
vec0[1] = w;
check:
if ((s16)w < *(s16 *)(s1 + 1)) goto body;   /* sll/sra of w after the join */
```
This flipped the residual from structural to REGALLOC-PERM/3 (a pure $v0/$v1 commutative-tie,
`[permuter]` bucket) — the promotion bytes now exact. Six tie spellings probed
(`.run/s59_tells/v_*.c`), all stable at 3: that last mile is permuter fuel, not an idiom.

### 4.5 The honest walls met
- `func_801AE3A4` (25 ins, LD/−1): the missing `addu $v1,$v0` is a same-value copy that plain
  `b = a` cannot produce (cse deletes it; a `"0"(b)` re-tie materializes it — mechanism confirmed
  — but the target's +8 frame slot is §172's documented three-layer canonicalization wall).
  Left unsolved; routed to §172's instrument, not to more spelling probes.
- `func_80187E08` / `func_80182FD0` (swaprepeat siblings, 102 ins): the doubled compare structure
  (§172b-2) is already RIGHT in the drafts; the residual is a 2–10-ins scratch permutation that
  flips between spellings (S11 knife-edge). Permuter fuel; one fix banks both via remap.

## 5. Pipeline losses (free wins, no model change)

1. **45 shape-MATCH drafts sit unbanked** (3,105 ins) — 34 of them also reloc-**AGREE**
   (`.run/s59_tells/shape_matches.json`). 9 are on `main`/md_MAIN, where wave gating cannot bank
   (gate_main is a separate, slate-level path). The remaining ~25 overlay fns died at the
   whole-binary gate on TU plumbing. §173's measured recovery rate on exactly this class is 64%
   (`aprop_symfix --fix` → `recover_integration --stages macro-externs,demacroize,tu-scope`).
2. **21 permuter-bucket nears** (16 at closeness ≤ 8, 1,710 ins) — the lane never runs the
   permuter. `residual_class` already routes them (`match_one --json` carries the verdict); a
   zero-token post-wave permuter pass over `bucket=="permuter" && closeness<=8` drafts is the
   designed use of `tools/permuter/`.
3. **Budget caps bind**: of the 270 newest attempts, 98 ended at the turn cap and 12 at
   cost/API stops (`submit`ted: 160). `tools/ox_campaign.py:264` pins every lane to
   `--max-turns 24 --max-cost-per-fn 0.15`; tells cards are 2.4× default size (median 89–95 vs
   37–39) and my three hand-cracks each took 5–10 oracle iterations WITH the right hypothesis
   already in hand. Wave ao alone logged 562 truncated turns for 185 targets.
4. **120 drawn cards never got a draft at all** (10,437 ins) — worker exhaustion in the 2,000-way
   fan-out; they re-enter only via `--retry-unbanked`.

## 6. Concrete changes (proposed; nothing landed)

### 6.1 Cookbook — make the card vocabulary greppable (3 lines, highest ROI in this doc)
At the §172b header (`docs/matching-cookbook.md:16573`) append an alias line, and mirror it in
`docs/cookbook-index.md:1088`:

> **Lane aliases (grep bait):** `extend-tell` = §172b-1 (+§4.1–4.4 recipes below), `swaprepeat-tell`
> = §172a macro-vs-inline + §172b-2, `s16-div-tell` = §172b-4. Atlas lever labels from
> `tools/atlas.py:441-445` — a drafter grepping the label must land here.

Then add the four byte-proven laws of §4 above as proper cookbook sections (the save-order/bb0
anti-dep law of 4.2 and the opaque-bound-local law of 4.3 are NEW; 4.1 and 4.4 sharpen §172b-1
into C recipes). Per R30/bank-idioms-before-checkpoint, this belongs in the same session that
lands the doc.

### 6.2 `tools/api_agent.py` — put the crib ON the card (replace lines 384-385)
```python
LEVER_CRIB = {
  'extend-tell': (
    "extend-tell = §172b-1 (grep 'sll/sra-16 pair tell'). The target promotes REGISTER-held\n"
    "s16 values. The four placements and their C spellings:\n"
    "  * naked sll/sra pair = a MULTI-DEF s16/u16 variable merged across branches — write\n"
    "    `w` assigned on BOTH paths (mirror the mem slot: `x[i] = w = …`), compare (s16)w;\n"
    "  * plain lh = single promoted use — read the s16 mem DIRECTLY in the expression, no temp;\n"
    "  * sll before a jal + sra IN its delay slot = the (s16) cast INLINE in the call argument;\n"
    "  * lhu + separate sll/sra = the value is also used as u16 — keep the u16 variable.\n"
    "Also: sign test (s16)t<0 emits sll+bgez only. NO register pins first (§17 is last resort):\n"
    "pins block the parm-copy/arg-copy shapes. Param-as-variable: if a param is copied to $aN,\n"
    "type the PARAMETER and use it everywhere; do not invent `self = arg0`.\n"),
  'swaprepeat-tell': (
    "swaprepeat-tell = §172a/§172b-2 (grep 'swapped-arm select tell'). Textual REPEATS are\n"
    "load-bearing: a repeated compare/select re-emits its own slt+branch; write the repeat\n"
    "TEXTUALLY (nested macros repeat operands; inline fns collapse — §172a). Range checks are\n"
    "plain `if (-lim < x && x < lim)` — the 2nd slt rides the 1st beqz's delay slot free.\n"),
  's16-div-tell': (
    "s16-div-tell = §172b-4 (grep 'Division-by-constant sign-correction'). s16/K magic-multiply:\n"
    "keep the promotion as an EXPRESSION (not a temp) so the sign-sra can reuse the <<16\n"
    "intermediate; K's magic pairs are in §167-25 and the odd-part table.\n"),
}
if card.get('lever'):
    out.append(f"\nThe atlas labels this card's lever: {card['lever']}.")
    crib = LEVER_CRIB.get(card['lever'])
    if crib:
        out.append(crib)
        out.append("Universal fold-blockers when a shape refuses: name the inner term of a\n"
                   "nested +/- as a temp (keeps association); hold a non-slti constant bound in\n"
                   "a LOCAL assigned right before its `if` (defeats the 0xFFFF canonicalization\n"
                   "and lets the arm's store reuse its register); hold a global base in a\n"
                   "pointer local when it must live in an $sN across calls (L2425).")
```
And one SYS line (after "THE LAWS THAT MATTER MOST", `api_agent.py:290-314`):
`3. If your card names a lever, grep the cookbook for the § its crib cites BEFORE drafting; a
plateaued diff whose class says [permuter] is DONE — submit NEAR with the class, do not spend
ten more compiles on a 2-ins register swap.`

### 6.3 `tools/build_wave_atlas.py:360` — attach the tell counts
Join each card's member row to `.run/feat.<binary>.jsonl` (keyed by addr; already produced by
`tools/atlas_features.py`) and attach
`'tells': {'extpair': N, 'dupselect': N, 'magic_div': N, 'sign_lh': B, 'sign_lb': B}`;
`_fuel` renders "expect N sll/sra pair sites / N repeated selects". Cost: one dict load per
binary at build time.

### 6.4 `tools/ox_campaign.py:264` — per-lane budgets
The tells lane needs `--max-turns 40 --max-cost-per-fn 0.40` (cards are 2.4× bigger and stack
3–5 idioms; 36% of failures ended at the caps). Make both per-lane fields in the lane spec
(`tools/lanes/campaign.sh:33` syntax) rather than constants.

### 6.5 Post-wave recovery (wave-closing step 2, per the standing 7-step sequence)
- `bucket==permuter && closeness<=8` → `tools/permuter/` pass (zero tokens; 16 candidates now).
- shape-MATCH + reloc-AGREE strays → §173 ladder; the 9 `main` ones go to the next gate_main
  slate instead of dying in the wave path.
- `.run/s59_tells/open_drafts.json` + `open_nodraft.json` are the current worklists.

### 6.6 80+ band — stop drafting it wide
Route extend-tell ≥ 80 ins through `tools/idiom_serial.py --lever extend-tell` (built for wall
classes, never yet run on tells — its ledger holds only jtbl rows). Its distill step is the
compounding channel the 2,000-way fan-out lacks, and `.run/idioms_learned.md` (currently absent)
is where 4.1–4.4 should also land so the serial lane reads them.

## 7. The 75% verdict, per band (cumulative bank of carded tell-lever fns, live tree)

| band | banked now | verdict |
|---|---|---|
| 5–50 | 75/100 = **75%** | already there; retries converge without any change |
| 50–80 | 83/144 = **58%** | **75% reachable** with §6 alone. 75% of 144 = 108 ⇒ 25 more banks needed from the 61 open (41% of failures). The measured ≤80 failure mix (26% shape-MATCH strays × 64% §173 recovery ≈ 17pp, 12% permuter-bucket × ~70% ≈ 8pp, ~22% one-construct LD × crib+budget ≈ 9–13pp, plus mid-gap partials) recovers ~35–45% of failures — 41% sits inside that band, tight but evidenced. No model upgrade required. |
| 80–120 | 34/118 = 29% | 45–55% plausible (crib + budgets + permuter + recovery); **75% not evidenced** — the LD gap-mass shifts to multi-region misreads (54/140 > 8 words) |
| 120+ | 26/93 = 28% | wide drafting is the wrong tool; serial lane + remap or park. 75% out of reach at current drafter tier |

Instruction-weighted honesty: the lane's 86,602 ins sit mostly ABOVE 80 ins (atlas means: extend
76,972/1,010 ≈ 76, but the open residue skews large — the 390 still-open average 103). So "the
lane at 75%" is true only as a ≤80-ins statement; the *instruction* frontier of this population
is a serial-learning problem, not a wave-tuning problem. The three cracked exemplars each carried
3–5 stacked laws; that stacking is the honest reason tells collapse above 80: p(all-k-idioms)
falls geometrically, and only a compounding lane (or the §6.1 cribs raising per-idiom hit rate)
bends it.

**Refuted along the way** (do not re-spend): §235 symbol-identity as the tells failure mode
(body-wrong confirmed: only 6/66–5/47 shape-matches among MISMATCH?); "drafts miss the extend
pairs" (74% have exact pair counts); "the models don't use the cookbook" (650/796 grepped — with
the wrong words).
