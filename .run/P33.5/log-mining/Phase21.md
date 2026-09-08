# Log mining — Phase21
Files/ranges: phase-ends/logs/Phase21.md:1-799  ·  Lines read: 799 of 799
Candidates considered: 27 · NEW: 3 · ALREADY-BANKED: 24

Grep corpus used for every "already banked?" test (`$CORP`):
`docs/matching-cookbook.md docs/cookbook-index.md docs/decision-log.md docs/accelerators.md docs/retrospective.md
docs/wave-playbook.md docs/how-to-ai-decomp/*.md decomp-architect/corpus/decomp-kernels.md
decomp-architect/templates/registry-E.decomp.md phase-ends/DIGEST.md`

## NEW

### C1 — An unattended agent run that looks throttled is usually blocked on an interactive approval prompt; check the pending prompt before diagnosing the provider
- **Evidence:** `phase-ends/logs/Phase21.md:731-732` —
  `**Wave-2 "6.5h" was NOT throttling** — it was idle on a CC **permission prompt** (Drew approved on check-in);`
  `waves 1 & 3 ran in ~25–32 min. (R14: corrected my earlier rate-limit read.)`
- **What happened / what it cost:** The overnight worker loop was launched for an ~8h hands-off run. Wave 2 sat for
  ~6.5 hours against a measured 25–32 min per wave, and I recorded it as provider throttling; the true cause was the
  harness waiting on a permission prompt that only cleared when the human checked in. The cost is the whole delta —
  roughly six wasted hours of a run whose entire premise was that it would keep working while nobody watched, plus a
  false rate-limit entry in the session record that a later session would have planned around.
- **Not banked — greps:** `grep -n -i -E 'permission prompt' $CORP` → 0; `grep -n -i -E 'waiting for (a )?(user|human|approval)|blocked on (a )?prompt' $CORP` → 0;
  `grep -n -i -E 'rate.?limit.{0,40}(wrong|not|actually)|not throttl|throttling' $CORP` → 2 (`docs/how-to-ai-decomp/09-economics.md:67` counts outage casualties, `docs/matching-cookbook.md:1283` calls a deterministic step "immune to throttling" — neither is the stall cause);
  `grep -n -i -E 'idle' $CORP` → 11 (all about lane idleness from stopping a lane or from batch stragglers, none about an approval gate). Adjacent but not the same: R40 exonerate the instrument (`docs/how-to-ai-decomp/04-oracles-and-instruments.md:64`) lists rate limits as a cause to clear on the way to judging the *subject*, and R55 (`:68`) says an unattended lane must leave evidence — neither names the harness's own approval gate as the thing that stops an unattended run.
- **Proposed home:** accelerator (or a DK on unattended lanes)
- **Portable because:** every agent harness with a permission/approval gate can silently hold an autonomous run; the diagnosis order — "is a prompt pending?" before "is the provider throttling?" — costs one glance and is true on any harness and any project.

### C2 — A class-distribution assessor only sees the population that has already been attempted; "analyse ALL remaining work" is a cheap triage pass, not a static analysis
- **Evidence:** `phase-ends/logs/Phase21.md:63-67` —
  `**THE ONE REAL GAP … `--assess` clusters the BACKLOG (already-DRAFTED near-misses), not ALL remaining stubs.**`
  `A function's "decomp issue" is only known AFTER a draft attempt (the residual = the class). So "analyze ALL`
  `remaining" = a **TRIAGE wave**: point `worker_wave` at the UN-drafted pools → each draft self-reports `// @class``
- **What happened / what it cost:** The phase's flywheel model was "when out of fuel, analyse all remaining functions,
  group them by decomp issue, learn one idiom per group". The tool built for it (`idiom_loop.py --assess`) clustered
  the *backlog* — i.e. only functions a wave had already drafted — so every "next idiom to learn" verdict was computed
  over a biased sample and the un-drafted majority was invisible to planning. The resolution needed no new tool: send a
  cheap triage wave at the un-drafted pools so each target self-reports a residual class, and only then assess.
- **Not banked — greps:** `grep -n -i -E 'triage wave' $CORP` → 0; `grep -n -i -E 'never attempted|not attempted|un-?drafted' $CORP` → 7 (all about the *gate/oracle* being blind to work never attempted, e.g. `docs/decision-log.md:704`, `docs/matching-cookbook.md:3689`, or about a per-run count — none about a class distribution computed over the attempted subset);
  `grep -n -i -E 'class label|classifier' $CORP` → 14, nearest `docs/how-to-ai-decomp/03-bootstrap-order.md:86-87` ("Build the classifier before the backlog is large; 91% of BFM's open backlog carried no class label") — that says build the labeller early, not that the assessor's population is the attempted one and must be widened by attempting;
  `grep -n -i -E '@class|self-report' $CORP` → 10 (self-reports as unreliable verdicts, R14 — the opposite concern).
- **Proposed home:** DK (a kernel, alongside the residual-classifier kernel) — or how-to chapter 03
- **Portable because:** on any project, the label that routes work (a residual class, an error class, a failure mode) is *produced by an attempt*. Any planner that clusters a work ledger is therefore planning over the attempted subset, and the fix — one cheap attempt per un-attempted item, purely to generate labels — is compiler- and console-independent.

### C3 — Say which currency a wave buys — percentage or idioms — before launching it, and judge it in that currency
- **Evidence:** `phase-ends/logs/Phase21.md:475` and `:18` —
  `**Waves 17–29 — reach-1 (×1) smallest-first harvest:** ~183 banks but fleet only **+0.06%** … **LESSON: reach-1 is`
  `poor fleet-ROI; its value was ov_SC01_077 completeness + idiom-mining.**` / `reach-1 is ×1, % negligible BY DESIGN;`
  `value = ov_SC01_077 completeness + idiom-mining`
- **What happened / what it cost:** Thirteen waves banked ~183 functions and moved the fleet 61.16% → 61.22%. The very
  next two waves, aimed at the high-reach pool, banked 26 and moved it +0.97% — about sixteen times the entire earlier
  run, per wave. The reach-1 run was not worthless (it was the phase's idiom mine and it completed one overlay), but it
  had been launched and reported as if it were percentage work, so thirteen waves' worth of head-count progress read as
  progress it wasn't. When reach-1 was later run again deliberately, the log states the currency up front — "% negligible
  BY DESIGN; value = … idiom-mining" — and the same pool became a defensible spend.
- **Not banked — greps:** `grep -n -i -E 'idiom-mining|idiom mining' $CORP` → 0; `grep -n -i -E 'not for (its|the) yield|value was the (idiom|knowledge)|training, not production' $CORP` → 0;
  `grep -n -i -E 'curriculum' $CORP` → 11 (all the Phase-25 *exemplar-crack* curriculum, a different thing). Nearest adjacency, read and judged: `docs/matching-cookbook.md:5113` "for the 0-stubs completion contract that is real progress; for the decomp.dev display number it is not. **Say which one you are buying**" and `:6903` (byte-variant families move RE-completeness, high-reach families move the display number) — both are about choosing between two *progress metrics*; neither treats knowledge production as an output a wave can be bought for. DK-42 (`decomp-architect/corpus/decomp-kernels.md:541`) rules the opposite direction only (instruction weight over head count).
- **Proposed home:** accelerator, or a line in DK-42
- **Portable because:** every campaign has a low-yield population that is nonetheless the cheapest source of new knowledge for its flywheel; the rule is to name the output (percent vs. lessons) at draw time so the wave is judged against what it was for, which holds for any target, compiler or harness.

## ALREADY-BANKED (one line each)

- Under a harness's `run_in_background`, do not also `nohup … &` inside — completion fires for the wrapper while the real job runs on (`:30`) — lives at `docs/matching-cookbook.md:9576-9577`.
- Delegate hand-matching and deep RE to isolated agents; doing them inline bloats the orchestrator's context (`:86-89`) — lives at `docs/how-to-ai-decomp/08-models-and-budgets.md:70-71`.
- The gate's own repair transforms regressed near-miss closeness and the tool logged the regressed value, hiding permuter-eligible drafts (`:20`, `:176-180`) — lives at `docs/matching-cookbook.md:2328` (re-log with true closeness + raw draft) and `docs/decision-log.md:1449-1455` (check what a ranking scalar measures before consuming it).
- A canonicalisation repair run unconditionally destroys an already-correct hand-pinned crack; gate first, repair only the failures (`:221-226`) — lives at `docs/matching-cookbook.md:2208-2218`.
- Batch propagation that is all-or-nothing lets one poisoned member revert ten clean banks and read as a wall (`:310-315`) — lives at `docs/how-to-ai-decomp/02-byte-gate.md:50-52` (bisect so one bad draft cannot sink the rest).
- A wrapper that swallows a subprocess's non-zero exit turns a failure into a false measurement (`:313`) — lives at `phase-ends/DIGEST.md:238` (R53), `docs/how-to-ai-decomp/02-byte-gate.md:30-32`, `docs/decision-log.md:2078-2084`.
- A crashed agent self-check is indistinguishable from a failed draft, so the wave drafts blind and nobody is told (`:319`) — lives at `docs/decision-log.md:1455` and `docs/matching-cookbook.md:4500-4503`.
- A per-function differ that builds without deleting the stale `.o`/`.elf` reports false byte-matches (`:407-410`) — lives at `docs/matching-cookbook.md:2059-2076` and `:1673-1676`.
- `objdump` elides runs of zero words, so cop2/GTE functions read as mismatched and a whole family was filed "unproducible"; verify on raw bytes (`:486`, `:514`) — lives at `docs/matching-cookbook.md:1980-1987`; the general "objdump's rendering elides repeated words" at `docs/decision-log.md:3043`.
- A drafting agent appended unverified idioms straight into the shared cookbook; that write path was blocked (`:530-531`) — lives at `docs/matching-cookbook.md:1997-1998` (the incident + the block) and `docs/how-to-ai-decomp/06-knowledge-base.md:32-33` ("harvest only from proven results").
- `h_exact`-style relocation-masked reach over-counts real propagation; probe shareability on the cracked exemplar before waving a class (`:235-241`) — lives at `docs/matching-cookbook.md:2195-2205`.
- A recommender that counts already-banked work and cannot separate never-tried from tried-and-failed re-burns a dry lever every session (`:119-126`) — lives at `docs/matching-cookbook.md:2218-2246` (§26).
- A backlog closeness achieved BY THE PERMUTER is not source closeness; `match_one` the saved draft before assuming a pin crack (`:143-146`) — lives at `docs/matching-cookbook.md:2269-2274`.
- Giants do not auto-bank: a 1.16M-token six-giant wave banked 0; they are hand-finish/permuter fuel (`:168-175`) — lives at `docs/matching-cookbook.md:2310-2318` (§27).
- An autonomous grinder without a persistent gate-rejection blacklist re-permutes the same impossible functions forever (banked 0 in ~8h) (`:735-739`) — lives at `docs/matching-cookbook.md:2024-2048` (§22) and `:178-179`.
- Rank targets by duplication reach, not head count: 183 banks ≈ +0.06%, 26 high-reach banks ≈ +0.97% (`:475-476`) — lives at `decomp-architect/corpus/decomp-kernels.md:541-548` (DK-42) and `decomp-architect/templates/registry-E.decomp.md:57-60` (G7).
- Same-compiler sibling projects carry their own flag deltas, so an inherited idiom must be re-proven on your own bytes (`:38`) — lives at `decomp-architect/templates/registry-E.decomp.md:395-401` (G67) and `decomp-architect/corpus/decomp-kernels.md:45-53` (DK-3).
- Cross-project byte-identical code between same-compiler games exists only in the vendor SDK/BIOS — zero engine code (`:39`, `:42`) — lives at `docs/decision-log.md:2025-2027`; "negative results with evidence are the product" at `docs/decision-log.md:2317`.
- Don't build a probe until you have read what the existing instrument already computes (the resolved-reach probe was withdrawn, unbuilt) (`:138-141`) — lives at `decomp-architect/templates/registry-E.decomp.md:215` (G33, never re-implement a gate you have) and `docs/matching-cookbook.md:5125` (§65d, measure the existing ladder first).
- Objects built with different flags (`-O0`, overlay-local) must be excluded from cross-object propagation or they poison it (`:312`, `:317`, `:323`) — lives at `docs/matching-cookbook.md:2388`, `:1595`, `:2552`.
- Long foreground build/VCS commands are killed by the harness; detached jobs survive (`:653`, `:719-720`) — lives at `docs/wave-playbook.md:738-740` and `docs/matching-cookbook.md:34804-34805`.
- Wave arguments must be pasted from a derived manifest, never hand-transcribed (`:375`, `:590`, `:649`) — lives at `docs/matching-cookbook.md:8861-8863`.
- The draw must exclude self-MATCH-but-gate-rejected and repeatedly-redrafted walls, or waves re-draft churners; a router in auto-mode grinds a saturated class (`:488`, `:589`, `:759-763`) — lives at `docs/wave-playbook.md:37-49` + `:76-78`, `docs/how-to-ai-decomp/12-failure-museum.md:28`, `docs/how-to-ai-decomp/03-bootstrap-order.md:67` (R45).
- A per-function cache must be keyed by the entry address, not by the decompiler's default `FUN_<hex>` label (`:786`) — lives at `docs/matching-cookbook.md:12859` (§164-45) and `docs/wave-playbook.md:236-238`.
