# PhaseEnd — Phase 37: the structs phase, part one — the census, the struct map, the engine and the declaration layer to its ledgered floor
**Date:** 2026-09-29 · **Project Version:** 2.3.0 · **Phase Status:** Complete **as RE-SCOPED by Drew at a task boundary** (2026-09-29: *"rescope p37 and defer remaining tasks to p38"* — T0–T4 are this phase; T5–T10 carry verbatim to Phase 38) · **Generation:** Gen3 (the third phase; Drew's order dedup → pins → **structs** → names)

> Chartered at gate 1 (S106, 2026-09-11, plan mode, Max) from `docs/gen3-handoff.md` item 4 (the types doctrine, R95) and
> `docs/gen3-standards.md`, with Drew's four forks: **grind to zero** on raw casts, lying declarations and levers; **placeholders + cited
> evidence** for names; T7 = **the P36 agent lane at his cap**, started only on his word; **the full canonical declaration layer**. R107–R117
> ratified by the plan approval. Ran **three sessions (S106–S108, 2026-09-11 → 2026-09-13)** and **115 commits** (`0a55cb0fd..bbe54b9cc` on the
> baseline `79b2f6f15`, the P36 close — committed by Claude and pushed on Drew's word, two one-off R6 waivers; **no tags or releases at phase
> closes from here on**, Drew S106). The phase then sat at the T4/T5 boundary (tree clean, the S108 checkpoint current) until **2026-09-29**, when
> Drew chose to **close it at that boundary so the repository can move to ProjectArchitect 3.0 between phases**, and to carry T5–T10 into
> Phase 38. The granular trail — every batch's verify line, every instrument defect with its cause, the S108 checkpoint (items 1–8, the complete
> T5 seed) and the gate-1 plan verbatim — is at **`phase-ends/logs/Phase37.md`** (R19, on demand; 1,236 lines).

## Build Log

**The phase in one line:** a self-asserting type census and a fleet-wide struct map measured the struct debt (503,016 raw cast dereferences,
7,261 struct definitions, 98,648 lying call declarations over 1,609 callees); a probe priced every rung on the bytes; a rewrite engine with a
byte oracle that also links (`tools/restruct.py`) was built; and the declaration layer was driven through the whole fleet to its measured floor
— **≈107,000 (TU, callee) declarations made canonical, 5,262 K&R sites marked apart, 133 of 149 alias-defined functions back under their real
names, 10 of 12 parked P36 signatures landed, lying declarations 98,648 → 1,796 (−98.2 %), every survivor ledgered by cause** — with 218/218
byte-identical after every change.

**Files created/changed and complete — do not recreate** (category summaries; the per-commit list is `git log 79b2f6f15..bbe54b9cc`):

- **The instruments (T1–T3, extended through T4).** `tools/type_census.py` (definitions with o32 layouts, duplicate tiers, VARIANT camps,
  dead names; six cast-site forms with base/offset/width/sign/access; the declaration layer — K&R-read definitions, in-scope declarations per
  TU, the lying set, multi-spelled callees, aliases, builtins, attributes; K&R and cross-binary sites counted APART; coverage vs the raw regex;
  four controls; `--sites`; selftest 21) and **the struct map** (`.run/P37/census/struct_map.json`, rendered `docs/struct-map.md`: 18,760 types
  over the fleet's bases explaining 99.2 % of sites, membership and evidence class per merge, layouts, conflicts — Drew's gate-1 addition);
  `tools/struct_layout.py` (the o32 layout engine + the writer in the final style + the naming invariant; agrees with cc1 on **5,283 definitions
  / 29,248 named fields, 0 rejected**); `tools/restruct.py` (rungs S / S2 / S+A / X / R / D / L, `--unalias`, `--callee … --body` with `--all-defs`
  / `--tu` / `--with` / `--map-data`, `--headers`, `--redraw VERDICT[:cause]`, the ledger `.run/P37/restruct/ledger.jsonl` + `inflight.json`
  restore, `--write-types` / `--audit-types` / `--audit-layouts` / `--check-ledger`; selftest 54, `--real` 53); `tools/delever_oracle.py`'s
  **LINKED mode** (the build's own `ld/objcopy/trim` on the candidate against the snapshot, SHA1 vs `config/check.*.sha`, ~10 ms) + a snapshot
  that REFUSES an irreproducible or empty/shrunken `build/`; `tools/restruct_cycle.sh` (the detached cycle, R115); `tools/argcheck.py`
  (every definition per name, `resolve_definition` per declaring binary, `cross_binary`, `kr_marked`, indented definitions); the reinterpret
  macros `LOBU/LOH/HIH/LOHU/HIHU/LOW/LOWU` in `include/common.h` (proven equal on cc1's assembly); `tools/share_body.py --retry-excepted`;
  `tools/audit_public.py`'s size cap raised to GitHub's hard 100 MiB with a WARN above 80 MiB (Drew, S107 — only the size check had fired; no
  ROM content was ever pushed).
- **The tree.** Every TU's declarations of every callee rewritten to the definition's ANSI signature where the objects stay identical
  (D1–D59 + the headers HD1–HD8); the byte-proven K&R calls marked `// K&R: n of m args (P37 …)`; 484 asm-label data aliases typed; 143
  `__builtin_abs` → `abs`; 133 alias-defined functions (`s32 aF… __asm__("func_…")`) restored under their real names with byte-true heads (three
  as K&R-style definitions); ten parked P36 signature bodies landed (`func_80157D20` ×132 via `--map-data`; `func_80029D3C` + its three
  zero-argument callers whose `$4` pins WERE the missing argument; `func_80188A30` `void`→`s32`; seven via `--tu`/plain) — 280 levers came off
  with them (4,010 → 3,730); the 3,546 "carried decl layer" banner blocks removed (21,274 comment lines); six TU-CONFLICT dedup classes shared.
- **The record.** Cookbook **§458** addendum and **§459** (the declaration layer's byte facts); `docs/decision-log.md` P37 S106/S107/S108;
  `docs/accelerators.md` P37 S106/S107/S108; SETUP **§P37 S106/S107/S108**; `docs/struct-map.md`; the readability series (the `types` columns,
  snapshots t1/t2/t4/t4-close) and the lever series (81 milestones); README "Types (Phase 37, snapshot 2026-09-13)"; `docs/story.md` §10 and
  `docs/retrospective.md` §7 written ("After 100 %", on Drew's S106 question) and advanced every session; `tools/timeline.py`'s lower panel.
- **Evidence (`.run/P37/`, allowlisted text):** `baseline/` (every R22 log incl. `r22_close.log`), `census/`, `probe/` (the five probe tables),
  `restruct/` (ledger, batch records, run/apply logs, cycle logs, the `--with` bodies).

**Tools/packages installed:** none.

**Verification results (literal):**
- **At this close (2026-09-29, HEAD `bbe54b9cc`, tree clean):** `make clean && make extract-all JOBS=16 && make check-all JOBS=16` →
  `extract-all: 217 extracted, 0 failed of 217 (+ main, serial)` · **`check-all: 218 passed, 0 failed of 218`** · `real 1m35.070s` · exit 0
  (`.run/P37/baseline/r22_close.log`). Every gated commit of the phase (~110) carried its own `check-all: 218 passed, 0 failed of 218`.
- **At T4's close (S108, `bd7d32ec2`; no `src/` change since):** `type_census: … 1796 lying declarations / 76 callees (+5262 K&R sites, +418
  cross-binary apart) · controls 4/4` (T1: 98,648 / 1,609) · `lever_census --check: 3,730 pin/asm sites, 3,730 marked !FAKE, 0 UNMARKED — OK`
  (T1: 4,010) · `readability_progress --snapshot t4-close` + `--check OK` (lying declarations in pinned bodies: 1 in 1, from 33 in 25) ·
  `lever_progress --check OK` (81 milestones) · `progress.py --check` fresh · `share_census … 10,180 satisfied (45 excepted), 0 VIOLATION(S)`.
- T1/T2 at their commits: `type_census: 7255 definitions (527 layouts, 206 duplicate classes, 40 variant camps) · 503016 cast sites in 69497
  bodies … coverage OK · controls 4/4`; `struct_map: 18760 types … explain 498896/503016 sites (99.2 %)`; `restruct --audit-layouts: 5283 …
  rejected 0; unresolved layouts 0`; `--linked-control: OK`; `delever_oracle --calibrate …: 147/147 … positive control DIFFERS … OK`.
- **Not run this phase:** `make tools-health` (last green at P36's close) and `make kit-corpus` after S108's SETUP/cookbook edits — both owed
  first in Phase 38 (the kit's `tool_census --check` may read red until then).

**Milestone achieved (as re-scoped, 2026-09-29 — Drew):** T0–T4 of the gate-1 plan, each ☑ with its verify lines in the archived log: the
baseline and oracle (T0); the type census and the struct map (T1); the probe with every rung priced on the bytes (T2); the rewrite engine,
its linked oracle and the cycle (T3); **the declaration layer at its floor** (T4: 1,796 lying declarations left, every one with its ledger
cause and owner task). The gate-1 milestone items 1, 2 and 4 (0 duplicate definitions, 0 raw casts, 0 levers) and the zero on item 3 belong
to T5–T7 and move to Phase 38 unchanged; item 5 (218/218) holds at this close.

**Carried to Phase 38 — the structs phase continued (T5–T10 as approved at gate 1, verbatim in the archived log's §"Approved plan"):**
- **T5 (Max for the head types' layouts and the canonical file naming; xHigh to run) — struct unification (rung L):** one canonical definition
  per TYPE ("per layout" reads "per type" since S106: layout twins without evidence stay apart) in the final style; VARIANT camps uniquified;
  dead names deleted; PsyQ layouts under Sony's names; the entity type (`Unkstruct_80126B58`, 0x24C) and the player block
  (`Unkstruct_80078E00`) authored from the map; main + `md_*` onboarded. First free win once the types are visible: the **1,120 `parse error`**
  declarations (`--redraw DECL-KEPT`); most of the **417 `conflicting types`** fall to the canonical files. An opaque-tier fold renames members
  (T2: 8 of 20 TUs), so L rewrites accesses too. `--write-types --top 6` previews `Unkstruct_800B5CB8` (90 fields / 44 overlaps) and
  `Unkstruct_80126B58` (146 / 28 overlaps + 1 misaligned) — union vs split per offset is T5's Max decision; `--audit-types`: 26 legacy
  `pad<SIZE>` names to rename.
- **T6 (xHigh) — the cast campaign** (rungs S/S2/S+A/X/R; 503,013 sites; T2's floor estimate ≈4 % kept after S2 + the 24 % the current types
  cannot hold); the 1,723 `ALIAS-KEPT` second-typed-view data aliases; the 450 GTE `_m` variants by a targeted regen (func_8017E830's six come off
  without a struct); `--strict`'s 6,717 direct GTE statements + 314 per-TU asm macros.
- **T7 (agents at Drew's cap, on his word) — the residue lane:** the `md_SC07_004` pair `func_801A1E94`/`func_801A5C44` (the zero-argument
  caller passes its own `$a0` — re-sign one level up in one `--with` unit); the other same-address copies of `func_80185578` (ov_SC03_014),
  `func_80188DF4` (ov_SC02_011, ov_SC03_104), `func_8017FC5C` (ov_SC04_002), `func_80183CC4` (ov_SC03_006/029/090); the five return-type lies
  (`func_80161208`, `func_801376E8`, `func_80150480`, `func_8017E3F0`, `func_801843E0`); `func_8016BF50`; the ten jr-merge alias functions belong
  to the file-layout phase, not T7.
- **T8 (gates + the Ghidra mirror), T9 (the record), T10 (the close)** as written. **Owed by name:** `docs/actor-struct.md` (+0x108/+0x10C are
  4-byte; `D_80078F08/0C` code 4, not 2); the §396(a) correction (its bytes); `make tools-health`; `make kit-corpus`; the 45 TU-CONFLICT rows
  (Sony functions / data declared another way in late-onboarded TUs — T5's canonical layer); the 13 `syntax error` units in `800.c`.
- **Before T5's first batch:** a green R22 → `delever_oracle --snapshot-baseline` → `--calibrate ov_SC04_011 ov_SC03_015 md_SC07_004 main -j
  16` (`--apply` refuses a stale snapshot). Disk: 22 GB free after S108's prune; `.run/P32/` (6.6 GB) and the rest of `.run/P36/` (6.5 GB) are
  the same prunable class. The gotchas (kill → WAIT → restore; bracketed `pgrep` patterns; never edit the phase file between a cycle's R22 and
  its commit; `--redraw` with `VERDICT:cause`, never bare `DECL-NONE`; bucket a flat yield by ledger verdict before stopping) are in the
  archived checkpoint's item 7.

## Roadmap delta (what Phase 37 changed about the road ahead)

- **The structs phase is two phases.** Gen3's order was one phase each (dedup → pins → structs → names). P37 now holds the measurement, the
  engine and the declaration layer; **Phase 38 = the structs phase continued (T5–T10)**; names follows it. The split is at a real seam: every
  remaining counter (definitions, casts, levers) needs the canonical TYPES first, and T5 is a Max design task that deserves a fresh plan.
- **The phase boundary moves the process, not the work:** the repository moves from ProjectArchitect 2.0 to 3.0 between the two halves
  (Drew, 2026-09-29), so Phase 38 opens under PA 3.0's own protocol with this PhaseEnd and the archived S108 checkpoint as its seed.
- **The declaration layer turned out to be the cheap, large win the probe predicted** (T2: 92.6 % IDENTICAL, 0 DIFFERS) — and its floor is a
  TYPES floor: 1,537 of the 1,796 survivors are "the TU cannot see the type" or "a second declaration elsewhere in the TU", both T5's by
  construction. The byte-proven K&R calls (5,262) are the original's calling convention, published apart, not debt.
- **What the census taught about instruments (five blind spots in one day, S108):** a definitions index that did not follow the include graph
  (every P35 shared body read as "external"), a name-keyed signature map (6,415 names carry >1 body), a column-0 definition regex (indented
  file-scope definitions), a redraw key honoured by the planner and not the engine, and a snapshot helper that stamped "fresh" over an empty
  `build/`. Each moved the headline count by thousands; each was found by bucketing the remainder by its ledger verdict and reading one case.
- **Scale, honestly (R41):** the plan priced T0–T4 at about three sessions and T4 at "≈1 unattended session"; they took three sessions and 115
  commits, T4 about 1.5 sessions of detached cycles (≈60 batches, ~90 s R22 each) plus the coordinator's reading. No agent draws this phase
  (T7 never started); the cost was compute and the coordinator's context.

## Deviations

| Item | Plan (gate-1 plan) | Actual | Reason |
|---|---|---|---|
| The phase's scope | T0–T10, closing on "grind to zero" for casts, declarations and levers (v2.3.0) | **re-scoped to T0–T4 by Drew (2026-09-29); T5–T10 carried verbatim to Phase 38** | the ProjectArchitect 3.0 upgrade is done between phases; T4/T5 is the phase's natural seam (the types gate everything left) |
| Milestone | items 1–5 at zero | item 5 (218/218) holds; the declaration counter at its floor (1,796, all ledgered by cause); items 1, 2, 4 and item 3's zero move to P38 | the re-scope |
| T1 | the census | the census **+ the fleet-wide struct map** | Drew's gate-1 question, Claude's recommendation, Drew's "Yes — T1 delivers the map" (P5d) |
| Milestone item 1 wording | one definition per LAYOUT | one definition per TYPE (layout twins without evidence kept apart) | the Plan agent's stress-test: `{s16 ×4}` carries 177 names, some genuinely different types (`Rect` vs `SVECTOR`) |
| The oracle | whole-object equality | + a LINKED mode | a correct global-block edit changes the relocation SPELLING, not the linked bytes (T2's f3 control) |
| T4's population | argcheck's rows | + 149 alias-defined functions (`--unalias`), + the shared headers, + callers of indented definitions, + cross-binary callees | each hidden from argcheck by an instrument blind spot, found from the batch numbers (R34) |
| The parked P36 signatures | 24 classes landed | 10 of 12 signature packs landed; the rest named for T7 | same-address copies that differ per overlay; a caller one level up |
| `audit_public` size cap | 50 MiB | 100 MiB + WARN at 80 MiB | Drew, S107: the P36 ledger (74.8 MiB, our own verdicts) turned the public CI red; checks 1, 2 and 4 were clean |
| Tags and releases | `v2.3.0` tag at the close | none — a normal close commit | Drew, S106: no tags or releases at phase closes |
| `make tools-health` | run at T8/T10 | not run this phase | T8/T10 moved to P38; owed first thing there |

## What we believed, what failed, and what we would do sooner (for the retrospective; the detail is in `docs/decision-log.md` P37)

- **Believed (gate 1):** a union-find over cast sites would give the fleet's types. **Run 1 fused 297,668 sites into one type** — Steensgaard's
  classic over-merge through untyped conduit parameters; it took five runs (typed-use parameters, a width veto, single-source locals,
  positive shared evidence on every inter-function edge) to reach a map worth probing. **Sooner:** state the merge evidence classes before the
  first run, and read the biggest cluster before any number is published.
- **Believed (T2):** a whole-object byte oracle is enough. **A correct global edit DIFFERS whole-object and is byte-identical linked** —
  and the first linked control read IDENTICAL for the wrong reason, because a probe had written a candidate's object into `build/` and the
  snapshot copied it. **Sooner:** the linked control and a snapshot that refuses what it cannot reproduce, on day one of any spelling campaign.
- **Believed (S107–S108):** the lying-declaration count measured the work. **It moved 13,832 → 8,830 → 2,367 → 2,171 → 1,796 through
  instrument repairs as much as through rewrites** — five blind spots, each hiding thousands of rows (the include graph, name-keyed
  signatures, column-0 definitions, a one-sided redraw key, an alias class argcheck could not see). **Sooner:** bucket the remainder by
  ledger verdict and read one case per bucket at every stop — a "flat yield" was twice a blind instrument, never the floor.
- **Believed (S108):** stopping a batch is `kill` then `--restore`. **The judge finishes its in-flight units first**; a restore 8 s after the
  signal consumed the snapshot and left six files with no tool-side restore. **Sooner:** a tool's stop path that waits for itself.
- **Believed (the plan):** a parked signature patch is one function. **Each was a unit** — the definition, its declarations fleet-wide, and
  sometimes its callers (`func_80029D3C`'s three `$4` pins were the missing argument; `func_80157D20`'s 132 copies each name their own datum).
- **Cost:** three sessions, 115 commits, no agent tokens. The machine time was ~60 detached batches with a 90-s fleet gate each; the
  coordinator's cost was reading the remainder after every stop. The one real incident was operator error (the kill/restore race), recovered
  in minutes and written into the gotchas.

## Commit Message
```
(Phase 37 landed as 115 commits 0a55cb0fd..bbe54b9cc, 2026-09-11 → 2026-09-13 (S106–S108), then re-scoped at the T4/T5 boundary by Drew on
2026-09-29 so the ProjectArchitect 3.0 upgrade happens between phases. This close = the archived log + this PhaseEnd + the DIGEST update +
the kit's coverage rows; a normal commit — no tag, no release.)

chore(phase-37): CLOSE (re-scoped to T0–T4) — the type census + struct map, the restruct engine with a linked oracle, and the declaration
layer to its floor: ≈107,000 declarations canonical, 5,262 K&R sites marked apart, 133/149 alias functions back, lying declarations
98,648 → 1,796 (every one ledgered by cause); 218/218 at every step; T5–T10 carried to Phase 38 (v2.3.0)

- PhaseEnd_Phase37.md written; CURRENT_PHASE.md archived to phase-ends/logs/Phase37.md (R19); DIGEST §0/§2/§3 appended (step 3b)
- R107–R117 written in full in DIGEST §3 and dispositioned in config/kit_coverage_map.tsv (+ the P37 S108 accelerator)
- close: check-all 218/218 from clean (.run/P37/baseline/r22_close.log); census at T4's close 1,796 lying / 76 callees, levers 3,730 / 0 UNMARKED
- rules: R107–R117 ratified at gate 1; candidates (a)–(g) proposed for Phase 38 gate 1
- v2.2.0 -> v2.3.0
```

## Rules Added This Phase

**Ratified at gate 1 (2026-09-11):** **R107–R117** (the PhaseEnd_Phase36 candidates (a)–(k)); full text in `phase-ends/DIGEST.md` §3.

**Candidates for Drew to accept, modify or reject at Phase 38 gate 1 (P10):**

| Rule | Reason |
|---|---|
| **(a) A "none / external / already done" verdict is checked on one case known to be the opposite before it is allowed to settle** — a settling verdict is where a blind index hides. | `DECL-NONE` settled 10,495 pairs whose definitions sat in the binary's own shared headers (the include graph was not followed); argcheck called 2,379 correct declarations lies (one signature per bare name). |
| **(b) A function is keyed by its definition (binary, address, body), never by its bare name**, in every index, map and census. | 6,415 names carry >1 body; `setdefault` in file order made a correct `(void)` declaration a "lie" (`func_800CB8A4`), and the map's clusters needed body hashes. |
| **(c) A filter that decides "done" is ONE function used by every side that applies it** (planner and engine, census and tool). | `--redraw VERDICT:cause` lifted the planner's filter and not the engine's: three batches drew TUs and judged 0 units. |
| **(d) A cycle is stopped only after its remainder is bucketed by ledger verdict; a flat yield is a question, never the floor** (R117 at batch granularity). | Twice a "nothing left" stop hid thousands of pairs (3,700 never-judged `md_*` pairs; 2,247 TUs of callers of indented definitions). |
| **(e) A tool's stop is SIGINT → wait for its exit → restore; a restore never races the process it restores after.** | S108: `--restore` 8 s after `kill -INT` consumed `inflight.json`; the judge then wrote 6 files and 197 rows with no restore left. |
| **(f) A snapshot or refresh helper refuses an empty or shrunken input and writes its "fresh" stamp only after the content is proven** (R68 extended to stamps). | `--snapshot-baseline` stamped HEAD and "0 objects" over 7,428 objects of another tree and returned 0. |
| **(g) A signature change is one judged unit: the definition, every declaration of it, and any caller whose bytes carried the missing piece** (a pin, a data name). | `func_80029D3C`'s three `$4` pins were the missing argument; `func_80157D20`'s 132 copies each needed their own datum (`--map-data`). |

*(Techniques stay in the cookbook §458–§459; strategy in `docs/decision-log.md` P37; the portable form in `docs/accelerators.md` P37 S106–S108 and the kit.)*

## PhaseEnd Changelog
**v2.2.0 → v2.3.0 — Phase 37 complete as re-scoped (Gen3's third phase, the structs phase's first half).** The matched C's type debt was
measured by a self-asserting census (503,016 raw cast dereferences, 7,261 struct definitions, 98,648 lying call declarations) and mapped
into the types the fleet needs (18,760 clusters explaining 99.2 % of sites); a probe priced every rewrite on the bytes (struct spelling
90.6 % identical, 100 % after keeping 3.8 % of sites as casts; declarations 92.6 % identical, 0 differing); a rewrite engine with a byte
oracle that also links was built; and the declaration layer was made canonical across the fleet — ≈107,000 declarations, 5,262 byte-proven
K&R calls marked apart, 133 alias-defined functions restored, ten parked signatures landed with 280 levers off — to a floor of 1,796, each
with its cause and owner. 218/218 byte-identical at every step. T5–T10 (struct unification, the cast campaign, the residue lane, the gates,
the record, the close) carry to Phase 38. R107–R117 ratified; seven candidates proposed.

## Plain-English Recap
The decompiled C still treated most game data as raw memory — "read two bytes at offset 0x34 of this pointer" — instead of named structs, and
a hundred thousand of its function declarations described the wrong parameters. This phase counted all of it with a tool that checks its own
counting, grouped the raw accesses into the struct types the code actually needs, and tested on real compiler output which rewrites are safe.
Then it built a rewriting tool that proves every change by rebuilding the affected files and comparing them byte for byte (and, where only
symbol names differ, by linking the whole program). With it, the function declarations across the entire game were corrected: about 107,000
fixed, the 5,262 calls where the original programmers really did pass fewer arguments marked as such, and the few hundred left each labelled
with the reason — almost all of them waiting on the struct types. Every one of the 218 game files stayed identical throughout. The phase is
closed here, at a clean seam, so the project's planning system can be upgraded; the struct types themselves are Phase 38's first task.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase37.md` (R19, via `git mv`); `phase-ends/DIGEST.md` §0/§2/§3 appended
(step 3b; R107–R117 in full); R107–R117 and the P37 S108 accelerator dispositioned in `config/kit_coverage_map.tsv` — **all left uncommitted for
Drew's close commit** (the message is above; no tag, no release). The Phase-37 work is committed (`0a55cb0fd..bbe54b9cc`; not pushed after
`79b2f6f15`). **Drew, from the repository root:**

```
git add -A phase-ends config/kit_coverage_map.tsv .run/P37/baseline/r22_close.log
git commit -m "chore(phase-37): CLOSE (re-scoped to T0–T4) — the type census + struct map, the restruct engine with a linked oracle, and the declaration layer to its floor: lying declarations 98,648 → 1,796 (every one ledgered by cause); 218/218 at every step; T5–T10 carried to Phase 38 (v2.3.0)"
git push origin main
```

Then upgrade the repository to **ProjectArchitect 3.0**, and open **Phase 38 — the structs phase continued (T5–T10)** in a fresh session
(effort **Max**, plan mode) from this PhaseEnd's "Carried to Phase 38" section and the archived S108 checkpoint (`phase-ends/logs/Phase37.md`,
items 1–8). Do **NOT** start Phase 38 here. Keep this file forever.
