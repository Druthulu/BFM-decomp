#!/usr/bin/env python3
"""gate_stage.py — Phase 21 shared deterministic bank/log stage.

The single entrypoint the worker Workflow AND the grinder daemon both call after producing
candidate drafts. Runs the proven Phase-19/20 recovery pipeline, byte-gates, propagates the
byte-matches fleet-wide, and logs every non-match to the backlog ledger — then prints ONE
compact JSON summary (so the orchestrator's context stays lean).

  drafts dir
    -> canon_resident_calls   (func_<ADDR> -> curated resident name; link-miss recovery)
    -> cast_call_sites        (per-site fn-ptr cast for callee-conflicts; §17a-1 cap tool)
    -> sig_unify              (unify callee externs + own def-sig to canonical)
    -> harvest_verify --chunk 1   (THE byte-gate; sole arbiter G3/P9 — banks byte-matches, reverts the rest)
    -> dedup_propagate --auto-from   (lift each banked match -> engine_core.h macro -> x reach overlays)
    -> backlog.append_record(...)    (every non-match: closeness + class + best draft, for hand-finishing)

Each transform is a pure draft-text rewrite; only harvest_verify mutates the byte-locked tree
(and it reverts anything that isn't byte-identical). A wrong draft can never bank.

Usage:
  tools/gate_stage.py --drafts .run/drafts-X [--binary ov_SC01_077] [--source-tag worker|grinder]
      [--src ...] [--asm-subdir ...] [--good-sha ...] [--no-propagate] [--commit]
Prints a JSON summary; importable as run_gate(...)->dict.
"""
import argparse, fcntl, glob, json, os, re, shutil, subprocess, sys, time
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import backlog

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, 'tools'))
import corpus   # the derived corpus oracle (Phase 26-A)
import shared_lock  # Stage 1: the fleet-shared RW lock (docs/concurrency-design.md)
PY = ".venv/bin/python"
# ov_SC01_077 defaults (the canonical harvest binary)
OV = "ov_SC01_077"
DEF_SRC = f"src/{OV}/{OV}.c"
DEF_ASM = f"asm/{OV}/nonmatchings/{OV}"
DEF_OUT = f"build/{OV}/{OV}"
DEF_SHA = "d19c9580a02dc63ba1f0e7e0c770f3b10de35635"
DEDUP_YAML = "config/dedup.us.yaml"
_MANIFEST = None


def sh(cmd, timeout=None):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=timeout)


def _isdir(p):
    return os.path.isdir(os.path.join(REPO, p))


def _check_sha(binary):
    """The bare locked SHA1 for a binary (config/check.<bin>.sha is sha1sum format '<sha>  <name>')."""
    p = os.path.join(REPO, f"config/check.{binary}.sha")
    return open(p).read().split()[0] if os.path.exists(p) else None


def _xform(tool, ov, indir, suffix, extra=None):
    """Run a draft-dir transform; return its out dir, or the in dir if the tool no-ops/fails.

    The out dir is CLEARED first. It used to be reused across runs, and the transform tools only
    WRITE the drafts they are given — so every stale draft from every previous run survived in
    `<drafts>-cn/-cast/-rc/-uni` and was handed to the byte-gate again. Measured 2026-07-21: the
    grinder submitted ONE permuter winner and the gate processed THIRTY-FOUR drafts and banked TWO
    — the extra one a leftover from an earlier session. Nothing wrong entered the tree (the
    whole-binary gate is the sole arbiter, G3/P9, and it banks only byte-identical output), but the
    run banked a function it was never asked to try and would have committed it under a message
    naming a different one. A stage that silently widens its own input set is the same defect class
    as a scanner that silently narrows it (R32): in both, the report and the work diverge."""
    out = indir + suffix
    shutil.rmtree(os.path.join(REPO, out), ignore_errors=True)
    cmd = [PY, f"tools/{tool}", "--overlay", ov, "--in", indir, "--out", out] + (extra or [])
    r = sh(cmd, timeout=900)
    return out if _isdir(out) else indir


def _corpus_reset():
    """Drop corpus caches after a config/extract change — the stub set and each stub's home TU
    have moved, and every later stage derives from them."""
    for f in (getattr(corpus, "stubs", None), getattr(corpus, "sig", None),
              getattr(corpus, "o0_sources", None), getattr(corpus, "symbols", None),
              getattr(corpus, "src_files", None)):
        if hasattr(f, "cache_clear"):
            f.cache_clear()


def _gate1(binary, src, asm, out, good_sha, d, verified_out=None, failed_out=None):
    """Whole-binary byte-gate (G3/P9, sole arbiter) on draft-dir d; return the verified func list.
    harvest_verify reads the CURRENT src as its baseline (so verified fns ACCUMULATE across calls —
    a stage-1 winner is no longer a stub for stage 2), substitutes + KEEPS byte-matches, reverts the
    rest. --chunk 1 so one compile-fail can't sink a chunk (§20). verified_out/failed_out are
    per-WORKER paths (default the shared .run/harvest_*.txt) so bulk_harvest can gate distinct
    binaries in parallel without cross-reading each other's results."""
    vo = verified_out or ".run/harvest_verified.txt"
    fo = failed_out or ".run/harvest_failed.txt"
    # --src is passed ONLY when a caller explicitly restricts the gate to one TU. Omitted, the gate
    # derives each draft's home TU from the tree and splices it there (Phase 26-A) — every TU links
    # into the same image, so one `make build` still gates them all.
    cmd = [PY, "tools/harvest_verify.py", "--binary", binary]
    if src:
        cmd += ["--src", src]
    sh(cmd + ["--out", out, "--good-sha", good_sha, "--drafts", d, "--chunk", "1",
              "--verified-out", vo, "--failed-out", fo], timeout=7200)
    vp = os.path.join(REPO, vo)
    return [w for w in (open(vp).read().split() if os.path.exists(vp) else []) if w.startswith("func_")]


def _manifest_class(name):
    global _MANIFEST
    if _MANIFEST is None:
        p = os.path.join(REPO, ".run/fuel_manifest.json")
        _MANIFEST = {t["name"]: t for t in json.load(open(p))["targets"]} if os.path.exists(p) else {}
    return _MANIFEST.get(name, {})


def _dedup_group_count():
    p = os.path.join(REPO, DEDUP_YAML)
    if not os.path.exists(p):
        return 0
    return len(re.findall(r"^\s*-\s*id:", open(p).read(), re.M)) or \
        len(re.findall(r"^[A-Za-z]", open(p).read(), re.M))


def match_one_closeness(fn, cpath, asm, binary=None):
    """('match',0) | ('near', n) | ('fail', None) via match_one (relocation-masked).

    The asm subdir is derived PER FUNCTION from the stub that names it (Phase 26-A). One subdir for
    a whole batch is the same single-TU bug: an overlay has TWELVE, and pointing match_one at the
    wrong one scores a draft against a DIFFERENT function's asm — a phantom non-zero closeness that
    then lands in the backlog as a matching failure and feeds reserved_walls()."""
    o0 = []
    if binary:
        st = corpus.stubs(binary)
        hit = next((s for s in st.values() if s.symbol == fn), None)
        if hit is not None:
            asm = hit.asm_dir
            # ...and the OPT LEVEL, from the same stub (Phase-29 Task-13A). Same bug as the asm
            # subdir, one level down: an -O0-compiled TU's target bytes are -O0, so scoring its
            # draft at -O2 yields a residual that is 100% artefact — recorded here as a matching
            # failure, ranked into the backlog, and read by the autopsy as evidence of a compiler
            # wall. corpus.is_o0 derives the answer from the Makefile's own rules (R33).
            if corpus.is_o0(hit.path):
                o0 = ["--o0"]
    if not asm:
        return ("fail", None, None)
    try:
        r = sh([PY, "tools/match_one.py", fn, "--c", cpath, "--asm-subdir", asm, "--json"] + o0,
               timeout=180)
    except subprocess.TimeoutExpired:
        return ("fail", None, None)
    # Task-12: parse the JSON result line (structured residual for the autopsy); text-fallback on any issue.
    try:
        j = json.loads([l for l in r.stdout.strip().splitlines() if l.strip()][-1])
        if j.get("status") == "match":
            return ("match", 0, [])
        if j.get("status") == "near":
            return ("near", int(j["closeness"]), j.get("residual"))
        return ("fail", None, None)
    except Exception:
        first = (r.stdout.strip().splitlines() or ["?"])[0]
        if first.startswith("MATCH"):
            return ("match", 0, [])
        m = re.search(r"(\d+) mismatch", first)
        return ("near", int(m.group(1)), None) if m else ("fail", None, None)


def run_gate(drafts, binary=OV, src=None, asm=None, out=None, good_sha=None,
             propagate=True, source_tag="worker", commit=False, src_file=None,
             lock_path=None, verified_out=None, failed_out=None, compute_fleet=True):
    # Serialize: the grinder and the orchestrator both call this, and it mutates the shared
    # build tree + git. One gate at a time (blocking flock) — never two builds/commits racing.
    # lock_path: pass a PER-BINARY lock (.run/auto/gate.<bin>.lock) so bulk_harvest can gate
    # DISTINCT binaries concurrently (their build/<bin>/** trees are isolated); default = the
    # global lock (serial), so grinder/orchestrator/lora_grind are unaffected. verified_out/
    # failed_out/compute_fleet likewise default to today's behavior; bulk_harvest overrides them
    # per-worker + skips the in-gate fleet% (computed once in its serial tail).
    # src_file: the overlay SPLIT .c the drafts target (ov_SC01_077_a.c / _o0.c). When set, BOTH cast
    # and sig_unify canonicalize against THAT file's decls (via --src-file; sig_unify.py:151 reads the
    # split file's stubs so split-file drafts are NOT dropped). dedup_propagate is already split-aware.
    # Default None = main .c.
    os.makedirs(os.path.join(REPO, ".run/auto"), exist_ok=True)
    _lock = open(os.path.join(REPO, lock_path or ".run/auto/gate.lock"), "w")
    fcntl.flock(_lock, fcntl.LOCK_EX)
    # Stage 1 (docs/concurrency-design.md): take the FLEET-SHARED lock in the mode that matches what
    # this gate will actually do. Per-binary resources are already covered by the flock above; this
    # one covers src/shared/*, config/overlays.mk, config/dedup.us.yaml and the overlay .c files that
    # propagation rewrites. EXCLUSIVE iff this gate will write them — i.e. it will propagate, or the
    # arity pre-pass is enabled (it edits the shared header). Otherwise SHARED, so distinct-binary
    # gates still run concurrently (bulk_harvest phase B) but can never overlap a writer.
    # shared_lock exports BFM_SHARED_LOCK_HELD so the dedup_propagate / fix_arity_callers children
    # we spawn below do not deadlock re-acquiring it.
    _writes_shared = bool(propagate) or not os.environ.get("GATE_NO_ARITY")
    try:
        with shared_lock.hold(exclusive=_writes_shared,
                              announce=f"gate {binary} ({'writer' if _writes_shared else 'reader'})"):
            return _run_gate_locked(drafts, binary, src, asm, out, good_sha, propagate, source_tag,
                                    commit, src_file, verified_out, failed_out, compute_fleet)
    finally:
        fcntl.flock(_lock, fcntl.LOCK_UN); _lock.close()


def _run_gate_locked(drafts, binary, src, asm, out, good_sha, propagate, source_tag, commit,
                     src_file=None, verified_out=None, failed_out=None, compute_fleet=True):
    # Resolve per-binary paths when unset — binary-agnostic, no silent ov_SC01_077 default an
    # overlay could inherit (the Phase-9 "required-no-default" discipline; the lora_grind mass-run's
    # 0/222 Bug-B). good_sha is normalized to the BARE hash: config/check.<bin>.sha is sha1sum format
    # "<sha>  <name>", but harvest_verify compares it against a bare sha1() — passing the whole line
    # never matches, so banking is 0 for EVERY binary incl. ov_SC01_077 (the 0/12 Bug-A).
    # src/asm are NOT defaulted (Phase 26-A audit, HIGH). harvest_verify now DERIVES each draft's
    # home TU from the tree, so inventing a default here would silently PIN the gate to the main .c.
    # That default is exactly what capped orchestrator.py / grinder.py / idiom_hunt.py — the three
    # callers that pass no src — to 13 of ov_SC01_077's 264 stubs (4.9%), and made 1,290 of the
    # grinder's own 1,298 queued functions UNBANKABLE however good the permuter's output was.
    # Note the negative control below already globs every split .c: this function knew the right
    # answer and then handed the gate the wrong file. Pass src ONLY to deliberately restrict to one TU.
    out = out or f"build/{binary}/{binary}"
    good_sha = (good_sha or _check_sha(binary) or DEF_SHA).split()[0]
    draft_fns = sorted(os.path.basename(p)[:-2] for p in
                       glob.glob(os.path.join(REPO, drafts, "*.c")))
    if not draft_fns:
        return {"drafts": 0, "banked": 0, "propagated": 0, "near": 0, "failed": 0, "verified": []}
    # Negative control (P9 / Phase-9): the drafts MUST be INCLUDE_ASM stubs SOMEWHERE in this
    # binary's sources (main + any _a/_o0 split — a split-only batch is legitimately gated by the
    # per-split run_gate call, so check the UNION, mirroring lora_grind.open_stubs' glob). If a
    # non-empty draft set overlaps ZERO of them, it's a binary/src mismatch (the silent-077-default
    # Bug-B) — warn loudly so a 0 can never again masquerade as "nothing matched".
    bin_stubs = set()
    for cf in glob.glob(os.path.join(REPO, f"src/{binary}/{binary}*.c")):
        bin_stubs |= set(re.findall(r'INCLUDE_ASM\([^,]+,\s*(func_[0-9A-Fa-f]+|DsMix)\)', open(cf).read()))
    if bin_stubs and not (set(draft_fns) & bin_stubs):
        print(f"[gate] WARNING: 0/{len(draft_fns)} drafts are INCLUDE_ASM stubs in {binary} — "
              f"binary/src mismatch (drafts for a different binary?); banking will be 0", file=sys.stderr)

    # STAGE 0 — gate the RAW drafts before ANY transform touches them (P30 T0a). The SESSION-22
    # reproduction of the carried "ladder destroys good drafts" defect: on one draft set the ladder
    # FAILED func_8013B6A0 + func_8013B598 (_o0) and func_80138C60 (jr split) while bare
    # harvest_verify VERIFIED all three, rtu_match confirming real-TU MATCHes — every casualty lives
    # in a SPLIT TU while the plain-TU draft banked fine. Root-cause hypothesis (open): the
    # transforms take ONE batch-wide --src-file while the gate derives each draft's home TU
    # per-draft (Phase 26-A) — a mixed-TU batch gets its decls reconciled against the wrong TU.
    # Stage 0 makes the failure mode impossible by construction regardless: a byte-correct draft
    # banks before any transform can regress it, and the ladder becomes what it was always meant to
    # be — RECOVERY for drafts that don't bank as written. Escape hatch: GATE_NO_STAGE0.
    verified = []
    remaining_fns = list(draft_fns)
    d_stage1_in = drafts
    if not os.environ.get("GATE_NO_STAGE0"):
        verified = _gate1(binary, src, asm, out, good_sha, drafts, verified_out, failed_out)
        remaining_fns = [f for f in draft_fns if f not in verified]
        if remaining_fns and len(remaining_fns) != len(draft_fns):
            # hand the ladder ONLY the stage-0 failures (an input set that silently widens or
            # narrows is the R32 defect class — see _xform's own history)
            d_stage1_in = drafts + "-s1in"
            abs_s1 = os.path.join(REPO, d_stage1_in)
            shutil.rmtree(abs_s1, ignore_errors=True); os.makedirs(abs_s1)
            for f in remaining_fns:
                p = os.path.join(REPO, drafts, f + ".c")
                if os.path.exists(p):
                    shutil.copy(p, os.path.join(abs_s1, f + ".c"))

    # Recovery is CANON-FIRST, sig_unify FALLBACK (§19/§25): sig_unify can REGRESS an already-byte-
    # correct draft (e.g. a hand-pinned crack — it rewrites the def-sig to a banked caller's wrong
    # canonical). So gate canon+cast FIRST (stage 1: already-correct drafts bank), then sig_unify
    # ONLY the stage-1 failures (stage 2: def-side near-misses recover) without regressing stage-1
    # winners. --src-file makes cast/sig_unify read the SPLIT .c (_a/_o0) so those drafts aren't
    # dropped. Each transform is a no-op-safe draft rewrite; the byte-gate is the sole arbiter (G3/P9).
    cast_extra = (["--src-file", src_file] if src_file else None)
    d1 = _xform("canon_resident_calls.py", binary, d_stage1_in, "-cn") if remaining_fns else d_stage1_in
    d1 = _xform("cast_call_sites.py", binary, d1, "-cast", extra=cast_extra) if remaining_fns else d1
    # data-symbol analog of cast_call_sites: rewrite each loose D_XXXX extern -> canonical + a
    # byte-neutral access cast (§33, T7b). No-op/idempotent without a data-decl conflict; the
    # byte-gate is still the sole arbiter.
    #
    # Phase 26-A: reconcile_decls.py -> reconcile_tu.py (R33 — retire the oracle, don't fix it).
    # reconcile_decls asked "what does the FLEET call this symbol?"; C asks "what does THIS TU
    # declare?". The engine is loosely typed, so one fleet-wide answer is wrong for some TU BY
    # CONSTRUCTION — and worse than a skip, because it writes an ACTIVELY WRONG decl into the draft.
    # Measured across ov_SC01_077's 12 TUs: 2,883 of its answers agree with the TU, 548 CONFLICT
    # (cc1 rejects the result), 357 are absent — and it was rewriting 60 of 196 live drafts.
    # reconcile_tu asks cpp what the TU declares (macro-injected externs included) and cc1 whether
    # the draft's decl can coexist; where it cannot, the TU wins and every USE is cast so the
    # draft's intended access is preserved byte-for-byte. It also handles the fn-ptr kind natively,
    # which is why it SUPERSEDES reconcile_decls rather than patching it: teaching the old parser to
    # see `extern void (*D_x[])(void);` would ARM its fn-ptr-blind data_access_subs to rewrite a
    # call-through `D_x[i]()` into `((u8 *)D_x)[i]()`.
    d1 = _xform("reconcile_tu.py", binary, d1, "-rc", extra=cast_extra) if remaining_fns else d1

    # ARITY PRE-PASS (Phase-29 Task-14). The three transforms above all rewrite the DRAFT. The
    # dominant residual blocker does not live in the draft at all: an already-banked SHARED caller
    # macro in src/shared/engine_core.h declares the function being banked with FEWER parameters
    # than its real definition takes (the original calls it K&R-style with fewer args than it
    # reads), so the C89 prototype conflicts with the byte-true definition -> `conflicting types`.
    #
    # DIAGNOSED, not assumed: splicing three top integration failures individually and reading real
    # cc1 stderr gave `conflicting types for func_XXXX` 3/3 — while the label harvest_verify
    # reports for them is the §58 red-herring `conflicting types for built-in function memcpy`,
    # which is a WARNING and not the failure. Byte-probe: func_8016EFC8 (reach-138) went from
    # gate-REJECTED to BANKED byte-identical after `fix_arity_callers --any-proto` rewrote 7 caller
    # decls to the no-prototype K&R form (byte-neutral: an empty call emits identical code, and a
    # no-proto decl is compatible with a definition whose params are default-promotion-safe).
    #
    # This edits SHARED state (engine_core.h), so it is scoped to the drafts in play and REVERTED
    # for every function the gate then rejects — a bank that succeeded needs its no-proto decl kept
    # or the tree stops building. The whole-binary gate remains the sole arbiter (G3/P9).
    # NB: --funcs is REQUIRED (the tool exits "no funcs given" without it) and --drafts is only the
    # narrow-param FILTER. Passing --drafts alone made this stage a silent no-op — sh() does not
    # raise on a non-zero exit, so the try/except below never saw it. Hence the explicit rc check:
    # a pre-pass that quietly does nothing is indistinguishable from one that found nothing to do,
    # which is the whole failure mode this ladder exists to remove (R32).
    # NO jtbl stage HERE — DELETED 2026-07-22 (R33: one implementation, and it is one layer down).
    # This used to be a BATCH pre-pass that carved every table-bearing draft before the gate ran.
    # It was wrong twice over:
    #   1. §61b byte-proved the carve MUST FOLLOW THE SPLICE — the non-contiguity that requires
    #      isolation is only detectable once the body is in the object. Carving an unspliced
    #      function reports "prepared 1/1" and yields a spec that fails when the body lands.
    #      harvest_verify owns the splice, so the prep belongs there, and IS there (_jtbl_prep_one).
    #   2. Its undo snapshotted only config/. But `jr_isolate_all` rewrites region 0 back over the
    #      ORIGINAL src/<ov>/<nm>.c, TRUNCATED — so every rejected draft permanently ate that TU's
    #      stubs, invisibly (the incremental build keeps linking stale objects, §42b). Measured
    #      2026-07-22: a 10-draft ladder run left 5 orphan region files, truncated TUs, and
    #      `undefined reference to func_80192F64` — after which every later draft in the run was
    #      probing a corrupted tree, so its 0/10 was not a measurement (R35).
    # Deleting it is strictly better than fixing it: harvest_verify's per-draft prep is the correct
    # mechanism, snapshots the full source set, and undoes per function.

    _arity_rc = None
    _arity_journal = f".run/arity_journal.{os.getpid()}.json"
    if remaining_fns and not os.environ.get("GATE_NO_ARITY"):
        # P30 T0a: the whole-file snapshot is replaced by fix_arity_callers' own per-decl JOURNAL
        # (--journal / --undo-journal). The snapshot needed two measured special cases — restore
        # ONLY src/shared/ on a partial bank (a full restore reverted 4 fresh banks, Phase-29
        # non-jtbl wave) and restore EVERYTHING on a zero-bank run (§61: "neutral" is not "wanted",
        # ~40 TUs of dead diff otherwise) — because a file-level restore cannot distinguish the
        # pre-pass's edits from the gate's own splices. A per-decl undo can: it round-trips each
        # journaled substitution's literal text, keeps the banked set, and reports (never skips) a
        # decl someone else edited since (R32). One mechanism, shared with every BARE-gate workflow
        # (the other half of the carried defect: arity residue in 17 unrelated TUs, SESSION-22).
        _arity = [PY, "tools/fix_arity_callers.py", "--apply", "--funcs", ",".join(remaining_fns),
                  "--drafts", d1, "--binary", binary, "--any-proto", "--journal", _arity_journal]
        try:
            _r = sh(_arity, timeout=600)
            _arity_rc = _r.returncode
            if _r.returncode != 0:
                print(f"[gate] arity pre-pass FAILED rc={_r.returncode}: "
                      f"{(_r.stderr or _r.stdout).strip()[:200]}", file=sys.stderr)
        except Exception as e:                               # never let the pre-pass sink the gate
            print(f"[gate] arity pre-pass skipped: {e}", file=sys.stderr)

    if remaining_fns:
        verified += _gate1(binary, src, asm, out, good_sha, d1, verified_out, failed_out)

    d = d1
    fails1 = [f for f in draft_fns if f not in verified]
    if fails1 and remaining_fns:                     # stage 2: sig_unify the stage-1 failures, re-gate
        s2in = drafts + "-s2in"
        abs_s2in = os.path.join(REPO, s2in)
        shutil.rmtree(abs_s2in, ignore_errors=True); os.makedirs(abs_s2in)
        for f in fails1:
            p = os.path.join(REPO, d1, f + ".c")
            if os.path.exists(p):
                shutil.copy(p, os.path.join(abs_s2in, f + ".c"))
        d = _xform("sig_unify.py", binary, s2in, "-uni", extra=cast_extra)
        verified += _gate1(binary, src, asm, out, good_sha, d, verified_out, failed_out)

    # THE LADDER ACCUMULATES IN MEMORY; THE FILE DID NOT (P30 S47, byte-witnessed).
    # Each rung hands `verified_out` straight to harvest_verify, which OPENS IT FOR WRITE. So every
    # stage TRUNCATES the previous stage's list, and a ladder whose last rung banks nothing leaves an
    # EMPTY file behind while `verified` (this list, built with +=) is correct. Measured: stage 0
    # banked 23 fns in ov_SC03_107, the JSON verdict listed all 23, and `.run/extend_verified.
    # ov_SC03_107.txt` was 1 byte — so `dedup_extend` read 0, printed "BANKED 0 / 46", and SKIPPED
    # the registry update for 23 banks that were already spliced into the tree and byte-verified.
    # The consumer was not wrong to trust the file; the file was wrong. Rewrite it ONCE, at the end,
    # from the accumulated truth.
    if verified_out:
        _vp = os.path.join(REPO, verified_out)
        os.makedirs(os.path.dirname(_vp) or ".", exist_ok=True)
        with open(_vp, "w") as _vf:
            _vf.write("\n".join(sorted(set(verified))) + ("\n" if verified else ""))

    # UNDO the arity edits for everything that did NOT bank — per-decl journal restore, keeping the
    # banked set. Never `--revert`: it inverts a PLAIN apply but not `--any-proto`, and once
    # round-tripped an unbanked fn's real signature into an invented `(void)` in the fleet-shared
    # header — 138 of 140 binaries failed check-all (measured 2026-07-21; invisible to the
    # single-binary gate, caught only by the full R22 sweep). Running AFTER stage 2 (not between the
    # stages, where the old snapshot-restore ran) also closes a latent parity gap: a stage-2 bank
    # that needed its arity edit used to have it reverted before its own gate attempt.
    # (_arity_rc is not None) ⇔ the pre-pass ran THIS invocation — a stale same-pid journal from a
    # crashed earlier run must not be replayed against today's tree.
    if _arity_rc is not None and os.path.exists(os.path.join(REPO, _arity_journal)):
        try:
            _u = sh([PY, "tools/fix_arity_callers.py", "--undo-journal", _arity_journal]
                    + (["--keep", ",".join(verified)] if verified else []), timeout=300)
            if _u.returncode != 0:
                print(f"[gate] arity undo-journal reported missing decls rc={_u.returncode}: "
                      f"{(_u.stderr or _u.stdout).strip()[:300]}", file=sys.stderr)
        except Exception as e:
            print(f"[gate] arity undo-journal failed: {e}", file=sys.stderr)

    # 5 propagate the banked matches fleet-wide
    propagated = 0
    prop_error = None
    if verified and propagate:
        before = _dedup_group_count()
        # TIMEOUT SCALES WITH THE BANK COUNT, and a timeout must never kill this process mid-write
        # (P30 wave-1, measured): a fixed 3600s is ample for ONE bank and far too short for EIGHT —
        # `dedup_propagate` rewrites every one of ~138 overlays per banked fn. When it blew, the
        # TimeoutExpired propagated out of run_gate and killed the driver **with the fleet half
        # rewritten**: 313 files touched, alphabetically ov_SC01_000..ov_SC03_013, `dedup.us.yaml`
        # never updated — `check-all` 124/140. A raised timeout is not a fix on its own; the
        # combination that matters is (a) scale it, (b) CATCH it, (c) report the tree as DIRTY so
        # the operator reverts instead of building on a half-propagated fleet (§61: undo scope must
        # cover write scope, and a killed process performs no undo at all).
        _budget = min(6 * 3600, 1800 + 1800 * len(verified))
        try:
            pr = sh([PY, "tools/dedup_propagate.py", "--auto-from", binary, "--min-reach", "2",
                     "--recover"], timeout=_budget)
        except subprocess.TimeoutExpired:
            print(f"[gate] FATAL: dedup_propagate exceeded {_budget}s with {len(verified)} banks — "
                  f"the fleet is HALF-PROPAGATED and the tree is DIRTY. Revert (`git checkout -- src/`), "
                  f"then re-gate with --no-propagate and propagate separately.", file=sys.stderr)
            return {"drafts": len(draft_fns), "banked": len(verified), "propagated": 0,
                    "near": 0, "failed": 0, "fleet_pct": None, "verified": verified,
                    "prop_error": ["TIMEOUT — TREE DIRTY, REVERT REQUIRED"], "commit": None}
        propagated = max(0, _dedup_group_count() - before)
        # Surface a REAL failure: dedup_propagate exits non-zero on a byte-gate revert (a false-reach
        # straggler poisoned the all-or-nothing batch) — distinct from the benign "nothing to propagate"
        # empty-plan no-op. A swallowed revert previously hid a real ×134 gain (cont.4); never again.
        pout = (pr.stdout or "") + (pr.stderr or "")
        if pr.returncode != 0 and "nothing to propagate" not in pout:
            errlog = os.path.join(REPO, ".run/auto/last_propagate_error.log")
            try:
                open(errlog, "w").write(pout)
            except OSError:
                pass
            prop_error = [l for l in pout.strip().splitlines() if l.strip()][-3:] or [f"exit {pr.returncode}"]
            print(f"[gate] WARNING: dedup_propagate exited {pr.returncode} ({propagated} groups added); "
                  f"see {errlog}", file=sys.stderr)

    # 6 log every non-match to the backlog (closeness + RESIDUAL class + best draft for the human).
    # The drafter stamps `// @class: <gcc-quirk class>` and `// @stuck: <note>` into the draft (so the
    # residual class travels WITH the file) — use those for the learning flywheel; else fall back to the
    # manifest class. This is what makes class-grouped waves (wave_targets.py --class) possible.
    near = failed = 0
    for fn in [f for f in draft_fns if f not in verified]:
        cpath = os.path.join(REPO, d, fn + ".c")
        body = open(cpath).read() if os.path.exists(cpath) else ""
        kind, close, resid = match_one_closeness(fn, cpath, asm, binary) if body else ("fail", None, None)
        meta = _manifest_class(fn)
        cm = re.search(r"//\s*@class:\s*(.+)", body)
        sm = re.search(r"//\s*@stuck:\s*(.+)", body)
        rclass = cm.group(1).strip() if cm else None       # the worker's self-reported residual class
        note = sm.group(1).strip() if sm else None
        if kind == "match":   # match_one says MATCH but the whole-binary gate rejected
            # ⚠ DO NOT NAME A CAUSE HERE. This used to read "(declaration/TU plumbing)" — a GUESS
            # printed as a finding. `func_8017F2D4` carried that label through SEVEN attempts across
            # five waves while every agent hunted codegen; the body was byte-correct the whole time
            # and the real fault was that the notes named the WRONG DESTINATION TU (a file holding
            # only a caller + prototype). No declaration conflict ever existed. A diagnosis the tool
            # did not measure must not be stated as one — say what is TRUE (the two oracles disagree)
            # and hand over the check that resolves it (P30 S48).
            status, where = "near", note or (
                "match_one MATCH but the whole-binary gate rejected — CAUSE NOT DETERMINED. "
                "FIRST re-derive the destination TU from the asm subdir: "
                "asm/<ov>/nonmatchings/<TU_stem>/<fn>.s => src/<ov>/<TU_stem>.c (the third path "
                "component IS the TU). Only then look for a decl conflict or a codegen residual.")
            near += 1         # …and COUNT it. It was logged as `near` and counted as NOTHING, so a
                              # run of 63 such drafts printed "banked 0, near 0, failed 0" — three
                              # zeros that do not sum to 63, and nobody ever added them up (R32).
        elif kind == "near":
            status, where = "near", note or f"{meta.get('lever') or meta.get('class') or 'residual'}: {close} mismatch"
            near += 1
        else:
            status, where = "failed", note or "won't compile standalone (loose-typing / missing decl)"
            failed += 1
        draft_path = backlog.save_draft(fn, body) if body else None
        backlog.append_record({"addr": meta.get("addr"), "name": fn, "reach": meta.get("reach"),
                               "klass": rclass or meta.get("class"), "nins": meta.get("nins"), "status": status,
                               "closeness": close, "where_stuck": where, "best_draft": draft_path,
                               "residual": (resid[:24] if resid else None),   # Task-12 structured residual telemetry
                               "binary": binary, "source": source_tag})   # binary: lets the grinder gate non-077 near-misses
    backlog.render()

    fp = None
    if compute_fleet:
        try:
            r = sh([PY, "tools/progress.py", "--fleet"], timeout=180)
            # The label this parses is progress.py's, and progress.py renamed it: the single
            # "byte-identical :" line became the THREE-metric block (fn-count / instr-weighted /
            # distinct-code). The old pattern matched nothing from that day on, so `fp` was None and
            # every gate commit message read "fleet None%" — 50 of them before anyone added up the
            # zeros (R32: a silently-nulled number is a defect, not a no-op). Take the instr-weighted
            # line (the decomp.dev-DISPLAY number), keep the legacy label as a fallback, and SAY SO
            # when neither matches so a future rename cannot go quiet again.
            for pat in (r"FLEET instr-weighted\s*:\s*\d+\s*/\s*\d+\s*=\s*([\d.]+)%",
                        r"byte-identical\s+:\s+\d+\s*/\s*\d+\s*=\s*([\d.]+)%"):
                mm = re.search(pat, r.stdout)
                if mm:
                    fp = float(mm.group(1)); break
            if fp is None:
                print("[gate] WARNING: could not parse the fleet %% from progress.py --fleet — its "
                      "label changed again; fix the pattern in gate_stage._run_gate_locked",
                      file=sys.stderr)
        except Exception:
            pass

    commit_sha = None
    if commit and verified:
        # `git add -u src/` = every MODIFIED TRACKED file under src/ — the TU the draft landed in
        # (whichever split that is), engine_core.h, engine_types.h, and every overlay a propagate
        # touched. Two bugs this replaces:
        #   1. it passed `src` straight to git add, and src is DELIBERATELY never defaulted (the
        #      Phase 26-A audit) — so every caller that omits it (grinder, orchestrator,
        #      idiom_hunt) crashed with `TypeError: expected str … not NoneType` THE MOMENT IT
        #      BANKED. Unreachable while the grinder banked nothing; the Task-13A targeting fix
        #      made it win on its first directed run and it crashed immediately.
        #   2. the `src/ov_*/*.c` glob is a name pattern, and a family's members do NOT all live in
        #      the same-named split — the Phase-29 §-lesson (a filename glob silently omitted 4
        #      R22-verified banks from a commit). `-u` cannot miss a modified tracked file.
        sh(["git", "add", "-u", "src/"])
        # P30 T3 pre-work: `-u` cannot stage NEW files — a jr bank's jtbl prep CREATES
        # src/<binary>/<binary>_jr_XXXX.c and edits config/overlays.mk + the binary's splat yaml,
        # all of which the old scope silently omitted (a clone of such a bank commit failed to
        # build; found via T1a's zero-jr-bank runs leaving exactly this residue). Add them
        # binary-scoped. KNOWN BOUNDED HAZARD: a FAILED jr attempt's prep residue in the same run
        # would ride along — the wave runner's post-batch §61 residue sweep (orphan carve = a
        # carve file whose fns are all still stubs) is the guard until harvest_verify's per-draft
        # undo covers config+carve-file restore on reject.
        sh(["git", "add", f"src/{binary}/"])
        sh(["git", "add", "config/overlays.mk", f"config/splat.{binary}.yaml"])
        sh(["git", "add", DEDUP_YAML] + ([src] if src else []))
        sh(["git", "commit", "-q", "-m",
            f"feat({os.environ.get('GATE_PHASE', 'decomp')}): {source_tag} gate — +{len(verified)} fns x{propagated} propagated (fleet {fp}%)"])
        commit_sha = sh(["git", "rev-parse", "--short", "HEAD"]).stdout.strip()

    return {"drafts": len(draft_fns), "banked": len(verified), "propagated": propagated,
            "near": near, "failed": failed, "fleet_pct": fp, "verified": verified,
            "prop_error": prop_error, "commit": commit_sha}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--drafts", required=True)
    ap.add_argument("--binary", default=OV)
    ap.add_argument("--src", default=None)
    ap.add_argument("--asm-subdir", default=None)
    ap.add_argument("--out", default=None)
    ap.add_argument("--good-sha", default=None)
    ap.add_argument("--source-tag", default="worker")
    ap.add_argument("--src-file", default=None,
                    help="overlay SPLIT .c the drafts target (ov_SC01_077_a.c/_o0.c): cast + sig_unify "
                         "canonicalize against it (via --src-file, so split-file drafts aren't dropped). "
                         "Use with --src/--asm-subdir pointing at the split.")
    ap.add_argument("--no-propagate", action="store_true")
    ap.add_argument("--commit", action="store_true")
    # PARALLEL-SAFETY (P30 wave 3). run_gate() has always taken per-worker result paths, but the CLI
    # never exposed them, so every CLI invocation used the SHARED `.run/harvest_{verified,failed}.txt`.
    # Two CLI gates running at once (one per binary — which is safe on every OTHER axis, since the
    # byte-gate is per-binary) would read each other's results and mis-attribute banks: the §55b
    # trap-4 shared-scratch defect that bit match_one in Phase 28, one level up. Default to a
    # PER-BINARY path so parallel gating is safe by construction rather than by remembering a flag.
    ap.add_argument("--verified-out", default=None,
                    help="where harvest_verify writes the verified list (default: per-binary, "
                         ".run/harvest_verified.<binary>.txt — do not share across concurrent gates)")
    ap.add_argument("--failed-out", default=None)
    a = ap.parse_args()
    b = a.binary
    # `src` RESTRICTS the byte-gate to ONE TU. Defaulting it to the main .c silently pinned the gate
    # to 13 of 263 stubs (4.9%): A3 taught harvest_verify to derive each draft's home TU *when --src
    # is omitted* — and this caller never omitted it, so the fix was neutralised by its own caller.
    # Now: pass --src ONLY when a human explicitly restricts the gate. Omitted => derive per draft.
    summary = run_gate(a.drafts, binary=b,
                       src=a.src,
                       asm=a.asm_subdir or f"asm/{b}/nonmatchings/{b}",
                       out=a.out or f"build/{b}/{b}",
                       # NOT `a.good_sha or DEF_SHA` (fixed 2026-07-22). DEF_SHA is ov_SC01_077's
                       # hash, and passing it as a TRUTHY default made run_gate's per-binary
                       # `good_sha or _check_sha(binary)` lookup DEAD CODE on every CLI invocation:
                       # every non-077 binary was gated against 077's SHA, so it could never match
                       # and every draft reported as "near" — indistinguishable from a real codegen
                       # residual. Measured: two ladder runs over ov_SC06_018 returned 0/10 and 0/9
                       # while the same drafts banked byte-identical through harvest_verify directly.
                       # Pass None through and let run_gate read config/check.<bin>.sha (R33).
                       # (grinder/orchestrator call run_gate() directly, so they were never affected
                       # — which is why the grinder could bank in ov_SC03_014 while the CLI could not.)
                       good_sha=a.good_sha,
                       propagate=not a.no_propagate, source_tag=a.source_tag, commit=a.commit,
                       src_file=a.src_file,
                       verified_out=a.verified_out or f".run/harvest_verified.{b}.txt",
                       failed_out=a.failed_out or f".run/harvest_failed.{b}.txt")
    print(json.dumps(summary))


if __name__ == "__main__":
    main()
