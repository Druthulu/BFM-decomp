# Concurrency Contract — overlapping draft / gate / propagate / R22 without weakening the byte-gate

**Status:** design (P30), authored by a Fable-5 planning pass 2026-08-07. **Not yet implemented.**
**Scope:** the pipeline around `tools/gate_stage.py`, `tools/bulk_harvest.py`,
`tools/harvest_verify.py`, `tools/dedup_propagate.py`, `tools/wave_snapshot.py`, and the R22
clean-fleet verify.

**The one-sentence contract:** a byte-gate verdict is a property of a *(draft, tree-state)* pair;
concurrency is sound exactly when (1) no other actor writes any element of a gate's read-set while
that gate runs, and (2) the terminal claim ("matched") is only ever published for a **commit**
whose own clean R22 passed — because the R22 at a frozen state re-derives everything and is
therefore immune to every race that happened before it.

---

## 1. Resource / conflict map

Fleet today: ~213 binaries (main + resident + `OVERLAY_BINARIES` + `MODULE_BINARIES`,
`Makefile:54-59`). "Gate(b)" = `gate_stage.run_gate` → `harvest_verify` for binary *b*; "Prop" =
`dedup_propagate`; "Draft" = an agent wave + `match_one`; "R22" = `make clean && make extract-all
&& make check-all`.

| Resource | Read by | Written by | Notes |
|---|---|---|---|
| `asm/<bin>/**` (regenerated, gitignored) | Gate(b) via `INCLUDE_ASM` `.include`; Draft (or its snapshot); `match_one` | `make extract BINARY=b` (Gate(b)'s jtbl prep, `harvest_verify.py:344,404,419`); R22's `extract-all`; **deleted whole by `make clean`** (`Makefile:842`) | Per-binary disjoint. Waves already decoupled via `wave_snapshot.py` (immutable sha1-manifested copy). |
| `src/<bin>/*.c` | Gate(b) (splice base, `harvest_verify.py:178-214`); Prop (member sites); Draft (ambient-decl context, read-only); `OBJS` glob at build parse | Gate(b) (splice/revert, jtbl carve region files); Prop (stub→`DEFINE_…()` rewrites, fleet-wide) | Per-binary disjoint **between gates**; Gate(b) vs Prop genuinely conflict on every member overlay. |
| `src/shared/engine_core.h`, `engine_types.h` | **every** binary's build (via `common.h`) | Prop (`dedup_propagate` macro author); **and — contrary to `bulk_harvest.py:16-17`'s isolation claim — the arity pre-pass inside every gate** (`gate_stage.py:316-335` → `fix_arity_callers.py:39`) | **Finding F1**: phase-B parallel workers each run the arity pre-pass unless `GATE_NO_ARITY` is set, and bulk_harvest does **not** set it. Two workers can concurrently edit + journal-undo the fleet-shared header. |
| `config/overlays.mk`, `config/splat.<bin>.yaml` | every build parse; corpus | Gate(b)'s jtbl prep (`jtbl_carve`/`jr_isolate_all`, snapshotted at `harvest_verify.py:305-310`); onboarding tools | **Finding F2**: `config/overlays.mk` is **one shared file**; two concurrent binaries' jtbl preps race on it, and each restores *its own* snapshot — a lost update on the other's carve. |
| `include/*.inc`, `include/include_asm.h` (generated) | every compile | `make extract` for **any** binary (identical content; `Makefile:762-764` — extract-all seeds them via main serially for exactly this reason) | Concurrent re-writes are content-identical but **tearable**: a reader mid-write gets a truncated macro file → spurious CC1-FAIL (never a false pass — see §2). |
| `build/{src,asm}/<bin>/**`, `build/<bin>/*` | Gate(b) link/check; asm-differ | Gate(b); Prop's per-member `make build` (`dedup_propagate.py:343`); R22 | Per-binary disjoint (`Makefile:757-765`). Prop's write-set spans **many** `build/<bin>` dirs ⇒ conflicts with any concurrent gate. |
| `expected/**` | asm-differ | operator `make expected` (`Makefile:827-837`); deleted by `make clean` | Off the hot path. |
| `config/check.<bin>.sha` | Gate(b) (`gate_stage.py:205`), `make check` | **nobody** during operation | Load-bearing: the only false-bank vector (§2.1). Add a cheap guard. |
| `config/dedup.us.yaml` | `_dedup_group_count`, `dedup_integrate --check` | Prop only (`dedup_propagate.py:315`) | Serial-lane only. |
| git index / worktree | everything | `gate_stage.py:481-495`, `bulk_harvest.git_commit` | Single-writer: `sh()` swallows a `git add` loser of an `index.lock` race → silently short commit (R32 class). |
| `.run` scratch | many | `match_one` (private per-pid, `match_one.py:30-52`); per-binary verified/failed (`gate_stage.py:517-525`); `.run/auto/bulk/*` (cleared wholesale, `bulk_harvest.py:209-210`) | One bulk/sweep driver at a time. |
| `.run/auto/gate[.<bin>].lock` | — | flock at `gate_stage.py:181` | Per-binary when `lock_path` passed; global otherwise. `harvest_verify` invoked **directly** takes no lock. |

**Genuinely conflicting pairs:** Gate(b) ∥ Gate(b) · Gate(*) ∥ Prop · Gate(*) ∥ Gate(*) when
either runs a shared-state stage (F1, F2, extract's include seeding) · anything ∥ `make clean` in
the same tree · two committers.

**Non-conflicting (the free parallelism):** Draft ∥ everything · Gate(b₁) ∥ Gate(b₂) with
shared-state stages disabled · main tree ∥ verify worktree.

---

## 2. The correctness argument (can any of this cause a FALSE BANK?)

### 2.1 The structure that makes the oracle race-proof

1. **The verdict compares against an immutable constant.** `make check` compares the built image's
   SHA1 against `config/check.<bin>.sha` (`Makefile:811-823`) — the hash of the *original retail
   bytes*, written once at onboarding, written by no pipeline stage. `INCLUDE_ASM` pastes the
   original assembly, so a wrong draft always changes some bytes (`harvest_verify.py:173-177`).
2. **The terminal R22 re-derives everything from the state it certifies.** `make clean` deletes all
   derived state (`Makefile:841-844`); `extract-all` structurally invalidates objects
   (`Makefile:571-590`); `check-all` asserts coverage, not absence-of-failure (`Makefile:801-807`).

⇒ **For a wrong draft to be *terminally* accepted, a clean rebuild of the final claimed state would
have to reproduce the original bytes with wrong C in the tree — contradicting (1).** No interleaving
of earlier stages can manufacture that. Races produce only false *failures*, wasted drafts, dirty
intermediate trees, and **verdict decay** — all fail closed at the terminal R22, loudly.

The one surviving false-bank vector is corruption of the comparison constant itself: a write to
`config/check.<bin>.sha`, or `--good-sha` pointing at the wrong hash (the Bug-A/DEF_SHA family,
`gate_stage.py:536-546`). No stage writes these; Stage 1 adds a guard asserting they are clean vs HEAD.

### 2.2 The four required sub-questions

**(a) Target staleness — draft authored against T, gated against T′.** *Sound.* The verdict is
computed entirely at T′. A stale draft can only fail to bank. Staleness is a **throughput**
variable, never a soundness one.

**(b) Concurrent propagation changing a TU's ambient declarations.** *Between* draft and gate: same
as (a), sound. *During* the gate's build: the real hazard. A mid-build write to `engine_core.h` or a
member `.c` can tear a read (fail-to-bank, safe) **or** let the gate compute a verdict true of a
**transient** tree state that will never exist again — **verdict decay**. It cannot put wrong bytes
into a green terminal state, but it mints a bank whose C is not byte-correct against the committed
state; the commit then fails R22 and someone bisects a batch that "all gated green." So Gate ∥ Prop
stays **mutually exclusive** — for verdict *hygiene*, not byte-gate soundness. Mechanism: every gate
holds `.run/auto/shared_state.lock` **SHARED**; propagation, `fix_arity_callers --apply`, and any
jtbl config edit hold it **EXCLUSIVE**. F1 and F2 must be closed for the same reason: in parallel
mode gates run `GATE_NO_ARITY=1` and **defer** (not drop — R32: report a `deferred:` count)
jtbl/arity drafts to the serial lane. Stage 0 (`gate_stage.py:222-247`) already banks byte-correct
drafts with no transforms, so the parallel lane keeps most of its yield.

**(c) `compute_fleet=False` workers vs the serial fleet metric.** *Sound*, already correct
(`bulk_harvest.py:81`, `sweep_parallel.py:22`). Fleet % is telemetry parsed from a moving tree, never
an input to accept/reject. A racy value causes a false **number** (an R32 defect in its own right),
not a false bank. Rule: workers never compute it; the serial lane computes it once, post-commit.

**(d) Can a worktree clean-verify certify the MAIN tree?** **Only its own checked-out commit — and
that is the correct object to certify.** Green at commit C proves *"a pristine checkout of exactly
C's tracked content rebuilds all ~213 binaries byte-identical."* Consequences:
- Claims attach to commit SHAs, never to "the tree": *"R22 213/213 at `<sha>`"*.
- **This is strictly stronger than current practice.** A main-tree R22 verifies the working state
  including untracked files — the `OBJS` glob compiles any stray `src/<ov>/*.c` — so main-tree green
  does **not** certify the commit. Documented at `gate_stage.py:483-491`: `git add -u` cannot stage
  created files, and "a clone of such a bank commit failed to build." The worktree verify detects
  omitted-from-commit files by construction.

**Verdict:** none of the proposed concurrency admits a false bank, **provided** (i) the shared-state
RW lock is honored, (ii) claims are published only per R22-verified commit, (iii)
`config/check.*.sha` stays unwritten. **Dropped idea:** overlapping propagation with gating on
"non-member" binaries — the arity-reconcile path (`dedup_propagate.py:350-359`) can widen the
write-set mid-run (the half-propagated-fleet incident, `gate_stage.py:377-396`); a write-set that can
grow during the run cannot be safely partitioned. Propagation stays globally exclusive.

---

## 3. Recommended architecture — four lanes

- **Lane D — draft (wave N+1), always-on.** Drafts against a `wave_snapshot`, writes only
  `.run/<wave>/`, `match_one` in private per-pid scratch. No locks. Overlaps **everything**.
- **Lane G — parallel gate (wave N).** `bulk_harvest` phase-B / `sweep_parallel` farm verbatim
  (ProcessPool over **distinct** binaries, per-binary lock, per-worker paths,
  `propagate=False, commit=False, compute_fleet=False`) **plus**: hold `shared_state.lock` SHARED;
  `GATE_NO_ARITY=1`; jtbl/arity drafts deferred-and-reported to lane P.
- **Lane P — serial integrate.** Holds `shared_state.lock` EXCLUSIVE. (1) re-gate the deferred queue
  with the full ladder; (2) `dedup_propagate --auto-from` per banking binary; (3) merge backlogs,
  fleet %, **one** commit.
- **Lane V — verify worktree.** Async clean R22 at the latest committed SHA. Green ⇒ publish claims
  (`r22/<shortsha>` tag + `.run/verify/<sha>.json`). Red ⇒ **stop-the-line**.

**Overlap matrix:** D ∥ {G,P,V} ✓ · G ∥ V ✓ · G ∥ P ✗ · P ∥ V ✓ · G(b) ∥ G(b) ✗ · two P ✗ · two V: queue.

**Where `bulk_harvest` already suffices:** phase separation, per-binary locks, per-worker scratch,
round-robin spread, serial commit, resumable tried-set. **Where it falls short:** (1) phase A welded
to local-LLM drafting → extract phases B+C into a shared `gate_farm` module; (2) its isolation
*claim* (`bulk_harvest.py:15-17`) is stale against F1/F2 — true only after Stage 1; (3) no
cross-cycle pipelining; (4) no verify integration.

---

## 4. The verification worktree

**Mechanism.** `tools/verify_worktree.py`: `git worktree add ../bfm-verify <sha>`, provision the
untracked build deps — cc1 from the **committed** tarball verified against
`tools/bin/CHECKSUMS.sha256`; `.venv` (symlink acceptable, read-only at build time);
`git submodule update --init tools/maspsx` (verify `git submodule status` clean — `.gitmodules` has
`ignore = dirty`). Then `make extract-all && make check-all`, writing `.run/verify/<sha>.json`.

**Soundness.** Green certifies **commit C**, full stop. The oracle is output bytes, not the
toolchain: a "wrong" cc1 that still reproduces the bytes does not invalidate a match; one that diffs
produces a false **failure** — hence the checksum preflight (R35). Sparse-checkout excluding
`ghidra/`, `dumps/`, `datasets/` is safe **fail-closed only** (an excluded load-bearing file can only
shrink `OBJS` and diff the image); validate once against a full checkout at the same SHA (R34).

**Cost.** ~1.1 GB sparse. Warm-up: full `extract-all` per verified SHA. **Needs measuring** at 213
binaries with lane G contending for cores.

**Sync.** Verifies **coalesce** — R22 verifies *states, not deltas*, so verifying the newest SHA
certifies the cumulative state. The main tree never runs `make clean` during operations again.

**What green licenses, verbatim:** *"Commit `<sha>`: clean-fleet 213/213 byte-identical from a
pristine checkout; every non-stub function in `<sha>` is matched (G3/P9). No claim about any later
commit or any working tree."*

---

## 5. New silent-failure classes and their detectors

| # | Class | Detector |
|---|---|---|
| 1 | Shared-header mid-air edit during parallel gates (F1) → verdict decay | RW flock + `GATE_NO_ARITY`; **bracketing assertion**: `git status --porcelain src/shared config` identical before/after phase G (R32); backstop = lane V |
| 2 | jtbl config lost-update (F2) | Defer jtbl drafts out of G; `jr_inventory`'s 1:1 ownership assertion as second oracle (R34) |
| 3 | Torn `include/*.inc` → spurious CC1-FAILs booked as walls, poisoning the backlog | R35: any CC1-FAIL naming a generated include gets ONE serial re-probe before a backlog record is written. Deferring jtbl prep removes the only in-G `make extract` |
| 4 | Commit-vs-claim skew: totals published from an unverified commit | Report tooling prints the last `r22/<sha>` tag + a loud `UNVERIFIED: N commits ahead` |
| 5 | Double-gating one binary from two drivers | Per-binary flock + per-binary result paths; extend the flock to direct `harvest_verify` invocations |
| 6 | Worktree provenance drift (stale submodule / wrong cc1) → false failures | Checksum + `submodule status` preflight; provenance in the verdict JSON; a red with bad provenance is an instrument failure (R35) |
| 7 | Silent shrink/widen of the parallel input set (deferred drafts vanishing) | R32: `drafts == banked + near + failed + deferred`, and lane P consumes exactly the deferred list |

---

## 6. Staged implementation plan

**Stage 1 — close F1/F2 and land the RW lock (pure safety; makes today's phase-B claim true).**
`shared_state.lock` (SH in `run_gate`; EX in `dedup_propagate`, `fix_arity_callers --apply`, lane-P
gates); parallel callers set `GATE_NO_ARITY` and `defer_shared=True`.
*Negative controls:* (a) with a gate holding SH, `dedup_propagate` with `LOCK_NB` must refuse loudly
naming the holder; (b) a known arity-needing draft gated in parallel mode must come back `deferred`,
then bank serially; (c) R22 unchanged 213/213.

**Stage 2 — `tools/verify_worktree.py` (lane V).** Sparse first run validated against one full
checkout. *Negative control:* a throwaway commit splicing a known-wrong draft must go red naming
exactly its binary; then delete the commit. Proves the detector fires before any green is trusted.

**Stage 3 — the wave dispatcher (formalize D∥G).** Generalize `split_drafts_by_binary`; extract the
shared `gate_farm`. *Control + measurement:* run a wave while a worktree R22 and one propagation run
mid-wave; assert manifest coverage (R32) and compare bank-rate against a quiet-tree control (R34).

**Stage 4 — pipelined loop + claim ledger.** Publish claims only on green. *Negative control:* kill
the loop between P's commit and V's green; on restart it must refuse to publish and re-enqueue.

**Stage 5 (measure first) — verify coalescing + auto-bisect on red.**

---

## 7. Explicit uncertainties (probes, not assertions)

- R22 wall-clock at 213 binaries in the worktree, with/without a concurrent gate farm.
- Arity/jtbl incidence in cheap-tier waves (sizes lane P's serial tail): count `PLUMBING`-arity +
  jtbl classes in `.run/backlog.jsonl` over recent waves.
- Staleness cost of D∥P: the Stage-3 A/B bank-rate comparison. If real, re-snapshot ambient decls at
  staging time — a throughput fix, never a soundness one.
- `git worktree` + submodule + sparse-checkout interplay on this git version — a 10-minute dry run.
- Whether any current wave prompt reads live `asm/` instead of a snapshot; Stage 3 should assert
  snapshot-only inputs (the manifest makes this checkable).
