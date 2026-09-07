# jtbl automation — carve → draft → bank (P31 S59)

**Status: BYTE-PROVEN.** The proof section at the bottom carries the commands, SHA lines and
object-level discriminators for the end-to-end targets. Companion docs:
`jtbl-island-split.md` + `-review.md` (the §260 mechanism this builds on), cookbook §8/§8a/§8b/
§8e/§61b/§61c/§61d/§62/§105/§129/§154-A/§260.

## 0. The finding that shapes everything: the pipeline already existed at the gate

The S58 framing was "every piece exists and nothing joins them." The load-bearing half of that
sentence is *where* the pieces already are: **`harvest_verify` has carried the complete per-draft
jtbl machinery since Phase 29** — `_jtbl_prep_one` (temporary splice → `jtbl_carve` →
auto-`jr_isolate_all` on the §8b walls → un-splice → re-extract → corpus reload), `_jtbl_reconcile`
(the §62 post-carve TU reconcile), full config+src snapshot/undo (§61d), and the CARVE-REFUSED
honest verdict (S22). `gate_stage.run_gate` invokes it with `--chunk 1`, and `sweep_parallel` is
just workers calling `run_gate`. So the campaign's own gate could already bank an ov_* jtbl draft
end to end — **what was missing was (a) anything that ever *hands* it a jtbl draft (the wave draw
excludes the lever), (b) the md_* island class (refused at carve), and (c) proof either way.**

This session joined them: the §260 island split is now automated inside the same prep, a read-only
structural probe routes what is reachable, a serial lane drives it, and the wave draw can carry the
lever safely. Three functions were then carried carve→draft→bank byte-identically, one per class.

## 1. When does the carve happen? — AT GATE TIME, inside the byte-gate, per draft

**Decision: carve-on-demand at gate time** (`harvest_verify._jtbl_prep_one`), never before the
draw and never before the draft. Argued against the campaign's real concurrency:

* **The pre-draft order is byte-refuted, not just inferior.** §61b: the same-subseg
  non-contiguity that requires isolation is only *detectable* once the body is in the object.
  Carving the unspliced function "succeeds" with a spec that fails when the body lands — and it
  cannot auto-isolate. The S58 `idiom_serial` ledger is the measurement: 8 jtbl attempts, 0 banks,
  6 prepare-failures (2 of them exactly the walls the gate-time prep dissolves automatically).
* **A pre-drawn carve is a poisoned tree state.** It sits in `config/` as a stub-owned `.rodata`
  piece for the whole draft lifetime: §129b-stranded (`jr_inventory` then refuses every later
  isolation in that binary), and — fatally — the campaign's R42 gate-entry step **commits dirty
  trees rather than reverting them**, so the poisoned state would be *committed by design* the
  next time any gate ran.
* **Locks only exist at the gate.** A carve writes `config/splat.<bin>.yaml` and the fleet-shared
  `config/overlays.mk`. The only write path serialized against the running gater is the gater's
  own: the per-binary flock (`.run/auto/gate.<bin>.lock`) plus the fleet shared lock
  (`shared_lock.hold`, EXCLUSIVE whenever the arity pre-pass is armed — which it is for every
  `sweep_parallel` worker and for this lane). Gate-time carving inherits both for free; a pre-draw
  carve would have to reimplement the same critical section to be safe, at which point it *is* a
  gate.
* **The drafter needs nothing.** `match_one` verifies a jtbl draft against the *uncarved* stub
  `.s` (reloc-masked; §81/§129a), so drafting is untouched — the campaign's drafter never stops
  and never learns the word "carve."

## 2. What happens on failure? — the carve is REVERTED; the invariant and its checks

**Invariant maintained:** *outside a gate's own critical section, a `.rodata` carve piece exists
in config iff its owning function is matched C in the same tree state.* (The one refinement: an
md_* §260 island-split piece whose owner is still a stub is byte-neutral **only because** the
stub's `.s` migrates the table into the same object — the committed md_SC03_076 stage-1 state.
The automation never *creates* that state persistently: a failed md gate reverts the split too.)

How it is enforced, three layers deep:

1. **Snapshot-restore in the gate** (`_jtbl_snapshot`/`_jtbl_restore`): text of
   `config/splat.<bin>.yaml`, `config/overlays.mk`, and **every** `src/<bin>/*.c` is captured
   before the prep; on gate rejection everything is restored, files the attempt created are
   deleted (derived from the snapshot's file set, not re-guessed — R33), and the binary is
   re-extracted. §61d/§105 class: undo is restore over the complete write scope, on every exit
   including a throw.
2. **`jr_inventory`'s 1:1 ownership assertion** (R32) is the standing tripwire: any stranded
   carve aborts the next isolation in that binary loudly.
3. **The lane's residue assertion:** after any failed gate, `jtbl_lane` diffs
   `git status --porcelain` (scoped to the binary's paths) against its pre-gate capture and names
   any NEW dirt (R32) — pre-existing dirt is other lanes' uncommitted banked work and is left
   alone (R42).

"Keep the carve because it is byte-neutral" was considered and rejected: neutrality is provable
(§260 stage 1) but a kept stub-owned carve violates §129b, blocks `jr_inventory`, and is exactly
what the campaign's commit-dirty-trees step would then adopt into history. Reverting costs one
redo (an isolate + two extracts, ~1 min) on the retry that banks — cheap against the alternative.

## 3. Which targets are cheap and which are walls? — the probed census

`jtbl_carve.island_probe` (new, read-only) classifies every member structurally;
`tools/jtbl_lane.py --census` runs it over the whole atlas population. **Denominator: 245/245
atlas jtbl-carve members probed (R32).**

| class | members | ins | verdict |
|---|---|---|---|
| `tail` | 173 | 25,765 | **REACHABLE NOW** — standard §8a gate-time carve (merge + auto-isolate included). ov_* 169 minus 1 mislabel, plus resident's 5. |
| `main-manual` | 47 | 6,356 | parked by decision — main's gate is a whole-EXE clean rebuild that bisects (`gate_main.py`, its own cadence); `jr_isolate_all` is also unported for main. NOT in the automated lane. |
| `island-blocked` | 10 | 2,779 | md_* stack-ordered: reachable **later**, one peel at a time (§260: each end-adjacent bank exposes the next; today's blockers are mostly the `island-pads` members ahead of them in md_SC07_003/004 + md_MAIN_011/034). |
| `island-pads` | 6 | 973 | **named wall**: the migrated table carries a trailing pad word (or a 4-mod-8 interior boundary), which a matched body cannot re-emit without §8e `JTBL_PADS` — and every mk-writer in `jtbl_carve` targets `overlays.mk` while md vars live in `modules.mk` (review #11). The lever that opens md_SC07_003/004's deep stacks. |
| `island-end` | 7 | 597 | **REACHABLE NOW** — the automated §260 split. All 7 are ONE family (`b1da4f0f7f14`, the 83/87-ins module state machines): the exemplar draft in this doc remaps to all of them. |
| `covered` | 1 | 83 | md_SC03_076 (the committed S59 split) — banked below. |
| `no-jtbl` | 1 | 132 | ov_SC02_031/func_80183810 — an atlas lever mislabel (its `.s` references no `jtbl_`); it can ride any ordinary wave. |

**Reachable unattended today: 181 members / 26,445 instructions** (tail + island-end + covered).
The 150-singleton shape means most of that is drafting work, not family remap — which is exactly
what the wave route is for; the md island-enders are the one place family leverage exists (one
draft, 7 members, plus each bank converts an `island-blocked` neighbour to `island-end`).

Ranked order for the serial lane (leverage-first, as `atlas_targets` implements): the md
island family (8 members counting covered, one shared draft), then tail members by group mass,
then re-probe (`--census`) as blocked members convert.

## 4. How it hooks into the campaign — named files, named changes

Two lanes, complementary:

1. **The wave route (breadth, ov_*/resident tail members).** The lever is drawable NOW:
   `build_wave_atlas.py` gained (a) a jtbl feasibility filter — `_jtbl_class` skips every member
   `island_probe` calls unreachable, so a jtbl card is *bankable by construction* — and (b) an
   at-most-one-jtbl-card-per-binary-per-wave cap (the §61c batch constraint kept unreachable by
   construction; deferred cards return via `--retry-unbanked`). Both are inert unless
   `jtbl-carve` is in `--levers`, so the running campaign is untouched until the operator opts in.
   **The one-line change that turns it on** (not applied — the drafter lane must not be edited
   while running): in `tools/lanes/drafter.sh`, extend the rotation
   `--lanes 'default:,tells:extend-tell;swaprepeat-tell;s16-div-tell,default:,default:'`
   with a fifth slot `jtbl:jtbl-carve` **and** append a matching band (the two lists rotate in
   lockstep — its own comment warns to change both together; `5-120` fits the §262 size-yield
   table and the population's shape). Gating needs NO change: `sweep_parallel` →
   `gate_stage.run_gate` → `harvest_verify --chunk 1` already carries the jtbl prep.
   Known filter tax, measured mechanism, deliberately not patched this session:
   `ox_campaign.reloc_filter` keeps only `AGREE`, and a *pure-switch* draft (no resolvable
   callee/global relocs) reads `UNRESOLVED` and is dropped before the gate. Most jtbl functions
   carry other symbols and pass; if the tax shows up in the ledger, the fix is one line in
   `reloc_filter` (pass `UNRESOLVED` when the card's lever is jtbl-carve).
2. **The serial lane (depth: md island stack, big exemplars, explicit targets).**
   `tools/jtbl_lane.py` (new): probe → draft (`api_agent`, or `--draft-dir` for any drafter's
   output) → gate via the *exact* `sweep_parallel` worker call
   (`gate_stage.run_gate(..., lock_path=.run/auto/gate.<bin>.lock, propagate=False,
   commit=False)`) → commit the named paths (`src/<bin>/`, `config/splat.<bin>.yaml`,
   `config/overlays.mk`) the moment a bank exists (R42). It holds the campaign's
   `.run/auto/draw.lock` across gate+commit — the same primitive the gater and the maintenance
   lane use, so gates and blanket commits can never overlap. One jtbl target per gate invocation,
   by construction. `idiom_serial.py` now REFUSES `--lever jtbl-carve` and names this lane (R43);
   its pre-draft carve ran the §61b-refuted order.

The md island split itself is wired one layer down, where every route reaches it:
`harvest_verify._jtbl_prep_one` gained the `_ISLAND_WALLS` branch — on jtbl_carve's §154-A
refusal it runs `jr_isolate_all --only` (body still spliced, §61b), then the new
`jtbl_carve --island-split --func` (inserts the one §260 config line; refuses non-end-adjacent
tables — the island is a stack), re-extracts, and re-runs the carve, which now reports the new
covered no-op. `jtbl_carve.apply` recognizes the covered state (piece named for the fn's own
isolated object, extent == the fn's table span) instead of refusing it.

## 5. Failure semantics, unattended (the honest list)

* draft wrong → whole-binary SHA rejects → snapshot-restore → `gate-failed` ledger row. Nothing
  kept, residue asserted absent.
* carve structurally impossible mid-gate (span-fit, table-count drift — the §61b class the probe
  cannot see statically) → `CARVE-REFUSED`, draft never built, named class in the failed ledger.
* island split refused (stack order changed under us) → `island-split REFUSED` + restore.
* isolate fails → `[jtbl] isolate FAILED` + restore.
* anything that raises → harvest_verify's end-of-run tree assertion + the lane's residue check
  name the files (R32); `jr_inventory` blocks compounding damage at the next attempt.

## 6. Proof — three targets, carve → draft → bank, byte-identical

All three drafts verified `match_one` MATCH standalone first, then were carried through
`tools/jtbl_lane.py --targets <fn>@<bin> --draft-dir …` — the campaign-identical gate path
(per-binary flock, exclusive shared lock, draw lock held across gate+commit), with the live
campaign (2,000-agent drafter + gater) running throughout.

### 6a. ov_SC03_014 / func_8017DCC0 — `tail` class (45 ins, 7-member family 85cc5eb043d3)

The table (`jtbl_801E92DC`, 5 entries + 1 trailing pad word) sits in the data tail immediately
after the banked `func_8017AE2C`'s committed carve, in the SAME subseg — so this exercises the
§8b same-subseg ADJACENT MERGE plus the §8e pad-spec machinery (single-table predecessor
recovery), fully automated.

```
$ .venv/bin/python tools/match_one.py func_8017DCC0 --c .run/s59_jtbl/drafts/func_8017DCC0.c \
      --asm-subdir asm/ov_SC03_014/nonmatchings/ov_SC03_014_jr_8017AE2C
MATCH (45 ins)  func_8017DCC0

$ .venv/bin/python tools/jtbl_lane.py --targets func_8017DCC0@ov_SC03_014 --draft-dir .run/s59_jtbl/drafts
[12:20:27] jtbl lane: 1 target(s): func_8017DCC0@ov_SC03_014[tail]
[12:20:27]   waiting for the campaign draw lock (gates never overlap) …
[12:20:27]   gating func_8017DCC0@ov_SC03_014 (per-binary flock + shared lock; the gate carves)
[12:23:48]   BANKED func_8017DCC0@ov_SC03_014 -> commit b801b499e
```

Byte evidence (commit `b801b499e`, live campaign running throughout):

| check | before | after |
|---|---|---|
| whole-binary sha1 | `d84b01a2…` (locked) | `d84b01a2bd4c712e1127707f5cd2007d79f4afb0` == `config/check.ov_SC03_014.sha` |
| `ov_SC03_014_jr_8017AE2C.o` `.rodata` | 0x14 (one table) | **0x28** (two tables, TIGHT — the §8e spec suppressed cc1's interior `.align 3`) |
| carve span (config) | data `tail18` at `0xc1184` | `0xc1198` — the existing piece grew by exactly the 5-entry table, trailing pad word left raw |
| overlays.mk | no line | `…jr_8017AE2C.o: JTBL_PADS := 0,0  # tables=+0x0,+0x14` — the SINGLE-TABLE-PREDECESSOR recovery inferred the banked neighbour's start |
| the stub | `INCLUDE_ASM(…, func_8017DCC0)` | `void func_8017DCC0(u8 *a0) { … }` |

### 6b. md_SC03_076 / func_801F218C — `covered` class (83 ins; §260 stage 2, the missing half)

The committed S59 split (`a931423c7`) proved stage 1 (stub state byte-neutral). This bank is
stage 2: the matched C emits the table itself into the jr object at the same address.
**First md_* jr function ever banked.**

```
$ .venv/bin/python tools/match_one.py func_801F218C --c .run/s59_jtbl/drafts/func_801F218C.c \
      --asm-subdir asm/md_SC03_076/nonmatchings/md_SC03_076_jr_801F218C
MATCH (83 ins)  func_801F218C

$ .venv/bin/python tools/jtbl_lane.py --targets func_801F218C@md_SC03_076 --draft-dir .run/s59_jtbl/drafts
[12:24:21] jtbl lane: 1 target(s): func_801F218C@md_SC03_076[covered]
[12:26:58]   BANKED func_801F218C@md_SC03_076 -> commit bad793c73
```

| check | stub state (§260 stage 1, commit `a931423c7`) | matched (commit `bad793c73`) |
|---|---|---|
| whole-binary sha1 | `9a165e368009a79bcc2ebb06bcb13e6da20d460e` | **`9a165e368009a79bcc2ebb06bcb13e6da20d460e`** — identical bytes |
| `md_SC03_076.o` `.rodata` | 0x268 | 0x268 |
| `md_SC03_076_jr_801F218C.o` `.rodata` | 0x14, migrated from the stub `.s` | **0x14, COMPILER-EMITTED** (`objdump -s`: the five pre-reloc case-label words `3c/138/ac/ec/118`) |
| commit scope | config (the split line) | **src only** — the covered class needs no config change |

`jtbl_carve` reported the covered no-op (`§260 island split in place … nothing to carve`), and the
prep proceeded straight to reconcile + gate. One nuance for drafters: `func_801EF6E4` is called
with NO argument — the `a0 = s0` at the branch is the *else* path's setup eagerly filled into the
delay slot (the one mismatch the first draft attempt had; fixed by `extern void func_801EF6E4(void)`).

### 6c. md_SC03_135 / func_801E5358 — `island-end` class (83 ins): the FULL automated §260 split

md_SC03_135 was virgin (no isolation, no split line). The gate did everything unattended:
spliced the draft, hit the island refusal, isolated, inserted the split line, re-extracted,
took the covered no-op, reconciled, built, SHA-verified, committed.

The draft is the 076 exemplar with symbols remapped from the sibling's own `.s` (the family
invariant — reloc operands in identical order):

```
$ .venv/bin/python tools/match_one.py func_801E5358 --c .run/s59_jtbl/drafts/func_801E5358.c \
      --asm-subdir asm/md_SC03_135/nonmatchings/md_SC03_135
MATCH (83 ins)  func_801E5358

$ .venv/bin/python tools/jtbl_lane.py --targets func_801E5358@md_SC03_135 --draft-dir .run/s59_jtbl/drafts
[12:27:28] jtbl lane: 1 target(s): func_801E5358@md_SC03_135[island-end]
[12:27:29]   BANKED func_801E5358@md_SC03_135 -> commit f74ad7ac8
```

Yes, ~1.1 s wall for the WHOLE §260 pipeline — splice → island refusal → `jr_isolate_all --only`
→ `--island-split` insert → `make extract` → covered no-op carve → un-splice → re-extract →
reconcile → real splice → build → SHA → commit. R40 was applied to that number before believing
it: the artifact mtimes show the ld at 28.54 s, the re-extracted jr `.s` at 28.83, the split
`.c` at 29.19, the jr `.o` at 29.24, the image at 29.26 — an md module is a 34 KB binary with
two TUs; its splat and cc1-2.7.2 really are that fast. (The ov gate above took ~40 s of real
work — a 30-TU overlay.)

| check | before (virgin) | after (commit `f74ad7ac8`) |
|---|---|---|
| whole-binary sha1 | `b901fda5…` (locked) | **`b901fda523c83376bd8b7f1c57104d8e13aef5e4`** == `config/check.md_SC03_135.sha` |
| config | `[0x0 island][0x27C c]` | + `[0x268, .rodata, md_SC03_135_jr_801E5358]` **and** + `[0x2d70, c, …_jr_801E5358]` — split AND isolation, both inserted by the gate |
| `md_SC03_135.o` `.rodata` | 0x27c (whole island) | **0x268** |
| `md_SC03_135_jr_801E5358.o` | did not exist | `.rodata` **0x14** |
| src | one TU | repartitioned: 212 lines moved into the new jr TU (§8c carried-decl layer) + the matched body |

Zero manual steps between `--targets` and the commit, with the live campaign (≈2,000 drafting
agents + the maintenance sweep) running throughout — the maintenance sweep held the draw lock
first, both md gates queued behind it and ran clean. This is the unattended-safety evidence: the
three lanes interleaved through the campaign's own locks exactly as designed.

## 7. What it refuses, and who owns each refusal (R43)

| refusal | owner |
|---|---|
| `main-manual` (47) | `tools/gate_main.py` batch cadence, by hand — the S59 parking decision |
| `island-blocked` (10) | this lane, later — re-probe after each peel converts the next member |
| `island-pads` (6) | future work: §8e `JTBL_PADS` for `config/modules.mk` (jtbl_carve's mk writers are overlays.mk-only — review #11) |
| `o0-stranded` | the -O0 cluster carve (`rollout_o0`), §261 |
| `no-jtbl` mislabel (1) | any ordinary wave — atlas lever fix |
| span-fit / table-count drift at gate | honest CARVE-REFUSED; hand §8e archaeology (`--span-tables`) |
