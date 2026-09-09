#!/usr/bin/env python3
"""recover_integration.py — Phase-24 T6 batch integration-recovery for leaf-MATCH-but-gate-rejected fns.

A wave logs many functions as `match_one` MATCH (byte-correct body) yet whole-binary-gate REJECTED —
"declaration/TU plumbing". The gate_stage pipeline (canon_resident_calls -> cast_call_sites ->
sig_unify) recovers the CALLEE-side conflicts, but NOT the dominant residual: a CALLER (in
engine_core.h OR the overlay's OWN inline src) declares the banked fn with a conflicting prototype
(`extern void func_X(void)` / a narrower arg type) vs the real def. gcc: `conflicting types for
func_X`. (Proven this phase on func_8014E048 (s16*->u16*) + the flagship straggler ov_SC02_005.)

THE MISSING STEP: `fix_arity_callers --any-proto --binary <bin>` (extended T6 to scan the overlay src,
not just engine_core.h) no-protos every conflicting caller decl -> compatible with any promotion-safe
def, byte-NEUTRAL (the call emits identical code). Then gate_stage banks + propagates. This driver
batches it and REVERTS the caller edits for anything that doesn't bank (so the shared header/src carry
no-proto only where it bought a match). The whole-binary byte-gate is the sole arbiter (G3/P9).

SESSION-16 (cookbook §65) added the mode this was missing and the blocker it could not reach:

  * `--draft-dir` consumes a WAVE dir directly. The backlog is the wrong source for fresh strandeds:
    its `closeness` is unreliable (byte-correct drafts logged closeness>0) and its drafts are
    overlay-specific. The wave dir's drafts are already matched to the right overlay.
  * The dominant blocker is NOT the caller-arity class this driver was built for — measured over 36
    stranded drafts it is `self_decl_hdr` (21/36): a `DEFINE_func_*` macro in engine_core.h declaring
    the draft's own fn incompatibly. `fix_arity_callers` structurally cannot fix it, and rewriting the
    shared decl is fleet-blind (§63 UPDATE: 3/3 per-binary, then R22 139/140). `demacroize.py` expands
    the offending instantiations in the overlay's OWN TU instead — a T1 edit (§65b).
  * BLAST-RADIUS TIERS (§65a) are now enforced, not remembered: each stage declares T0/T1/T2, the
    driver MEASURES the write set (`git status --porcelain`) and asserts containment, and picks the
    validator from the tier — per-binary gate for T0/T1, R22 clean-fleet for T2. The §63 disaster was
    a T2 edit validated by a T1 validator; stating the tier makes that mistake structural to catch.
  * PROPAGATION is fleet-tier too, and was the write the tier machinery did not cover (it was also the
    default): it needs `--max-tier fleet` AND `--r22`, and is refused outright after a `demacroize`
    stage, whose banks are ×1 by construction. (Phase 29 SESSION-17, found by exercising the success
    path — `assert_write_set` cannot see it, because under `--commit` the writes are already committed.)
  * Bank truth comes from `banked_from_source()` (the stub is GONE from src), never from a gate report
    — `.run/harvest_verified.txt` accumulates across runs and yields phantom banks (§55b trap 4);
    `--run-id` also gives every run its own result files so concurrent runs cannot read each other's.

  recover_integration.py [--auto | --funcs f,g | --from-file L | --draft-dir D ...]
                         [--binary ov_SC01_077] [--limit N] [--commit] [--no-propagate]
                         [--run-id ID] [--stages demacroize] [--max-tier binary] [--r22]
                         [--probe-only] [--report PATH]

--auto pulls leaf-MATCH candidates from the backlog (status capped / near-close-0, reach>=2), filtered
to those STILL a stub in the binary AND STILL match_one-MATCH on their best draft (drift-safe, R14).
"""
import argparse, collections, fcntl, glob, json, os, re, shutil, subprocess, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import backlog, corpus, gate_stage

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = ".venv/bin/python"
DRAFT_RE = re.compile(r"^func_[0-9A-Fa-f]{8}\.c$")   # wave dirs also hold scratch: _b.c, try2.c, …

# §65a — a stage's write set decides its validator.  T1 is SUFFICIENTLY validated by the per-binary
# gate precisely because `src/<binary>/**` cannot reach another binary; T2 is not, at any confidence.
TIER_RANK = {"draft": 0, "binary": 1, "fleet": 2}
STAGE_TIER = {"arity": "fleet",        # fix_arity_callers writes src/shared/engine_core.h
              "demacroize": "binary",  # expands macros in src/<binary>/ only
              "tu-scope": "binary",    # §103 STU: moves a contested TU decl into its consumers
                                       # (P31 T6 — the sweep-only lever the recovery path lacked;
                                       # writes src/<binary>/*.c, covered by the TU snapshot)
              "macro-externs": "draft",  # §121: rewrite draft decls of DEFINE_-defined callees to
                                         # the macro's own signature (draft text only)
              "self-cast": "binary"}     # §378 (P31 S69): cast the TU's OWN call sites of the
                                         # function being defined. Writes src/<binary>/*.c only.
                                         # THE STAGE ORDER MATTERS AND IS NOT ARBITRARY: `arity`
                                         # no-protos the conflicting forward decl, which makes the
                                         # DRAFT'S DEFINITION the prototype in scope, so the TU's own
                                         # call fails anew with `too few arguments'. self-cast is the
                                         # answer to the error `arity` CREATES, so it must run AFTER
                                         # it, never instead of it.


def tier_ok(stage, max_tier):
    return TIER_RANK[STAGE_TIER[stage]] <= TIER_RANK[max_tier]


def sh(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, **kw)


def _fresh_corpus():
    """Drop the lru_caches — after a bank the source has changed and a cached stub map is a lie."""
    for f in (corpus.stubs, corpus.sig, corpus.symbols, corpus.src_files):
        if hasattr(f, "cache_clear"):
            f.cache_clear()


def stub_map(binary):
    """{func_<ADDR>: (src_rel, asm_subdir)} for every INCLUDE_ASM stub across this binary's split .c
    files (main + _a/_o0/_o0b/_after). The asm subdir is read from the stub LINE, so a fn in a split
    (the post-whale _after region — 263 of ov_SC01_077's stubs) is drift-checked + gated against its
    OWN .s/.c. Fixes the §39 split gap that made --auto silently skip every split-file candidate.

    SESSION-16: derived from `corpus.stubs` rather than re-scanned with a local regex (R33 — one
    oracle). corpus is COVERAGE-ASSERTING: it refuses to answer if any INCLUDE_ASM line fails to
    parse, any symbol fails to resolve, or any stub lacks its `.s`. The old private regex here could
    silently return a short map, and a short map in a SELECTION tool is invisible missing work (R32)."""
    _fresh_corpus()
    return {s.symbol: (s.path, s.asm_dir) for s in corpus.stubs(binary).values()}


def banked_from_source(binary, fns):
    """The ONLY bank oracle: a function is banked iff its INCLUDE_ASM stub is GONE from src.
    Never read this from a gate report — `.run/harvest_verified.txt` accumulates across runs, so a
    stale line reports a phantom bank for a function still stubbed (§55b trap 4, 'still armed')."""
    live = stub_map(binary)
    return sorted(fn for fn in fns if fn not in live)


def git_dirty():
    """Paths git currently sees as modified/added, repo-relative."""
    r = sh(["git", "status", "--porcelain"])
    return {ln[3:].strip() for ln in r.stdout.splitlines() if ln[3:].strip()}


def assert_write_set(before, tier, binary):
    """A stage that writes outside its declared tier ABORTS. §61d: a stage whose undo scope is
    narrower than its write scope destroys work no byte-gate can see — so the write scope must be
    checked, not trusted. (`ghidra/` churn is R23 restart-noise and is never ours.)"""
    wrote = {p for p in (git_dirty() - before) if not p.startswith("ghidra/")}
    if tier == "fleet":
        return wrote
    allowed = (lambda p: p.startswith(f"src/{binary}/")) if tier == "binary" else (lambda p: False)
    bad = {p for p in wrote if not allowed(p) and not p.startswith(".run/")}
    if bad:
        raise SystemExit(f"[recover] ABORT — a '{tier}'-tier stage wrote outside its blast radius: "
                         f"{sorted(bad)}. Restore the snapshot and fix the stage's tier.")
    return wrote


def r22():
    """The fleet arbiter. Read check-all's OWN output line — never the wrapper's exit status, which
    has lied three separate ways in this phase (`| tail` masking a failure, grep-no-match returning
    1 on a green run, a background build racing the foreground one)."""
    sh(["make", "clean"])
    e = sh(["make", "extract-all"])
    c = sh(["make", "check-all"])
    line = next((l for l in c.stdout.splitlines() if l.startswith("check-all:")), "")
    ok = " 0 failed of " in line and line.split()[1] == line.split()[-1]
    return ok, (line or (e.stdout.splitlines() or [""])[-1])


def stage_drafts(dirs, dest, binary):
    """[(fn, path)] from wave dirs, filtered to real drafts and to functions that are STILL stubs.
    The strict basename filter matters: the wave dirs carry scratch (`_b.c`, `try2.c`, `scratch/`)
    and `run_gate` globs `*.c` blindly, so unfiltered staging gates and backlog-logs junk."""
    live = stub_map(binary)
    picked, skipped = {}, set()
    for d in dirs:
        for b in sorted(os.listdir(os.path.join(REPO, d))):
            if not DRAFT_RE.match(b):
                continue
            fn = b[:-2]
            if fn in live:
                picked.setdefault(fn, os.path.join(d, b))
            else:
                skipped.add(fn)
    if skipped:                       # R32: name the exclusions; a silent drop manufactures a rate
        print(f"[recover] excluded {len(skipped)} already-banked draft(s): {' '.join(sorted(skipped)[:8])}")
    os.makedirs(os.path.join(REPO, dest), exist_ok=True)
    for fn, p in picked.items():
        shutil.copy(os.path.join(REPO, p), os.path.join(REPO, dest, fn + ".c"))
    return sorted(picked.items())


def auto_candidates(binary, limit):
    """leaf-MATCH-but-unbanked candidates from the backlog, drift-checked against current src + drafts."""
    seen = {}
    for r in backlog.load_best():
        if r.get("name"):
            seen[r["name"]] = r
    smap = stub_map(binary)
    out = []
    for r in sorted(seen.values(), key=lambda r: -(r.get("reach") or 0)):
        fn = r.get("name"); d = r.get("best_draft")
        if fn not in smap or not d or not os.path.exists(os.path.join(REPO, d)):
            continue
        if (r.get("reach") or 0) < 2 or r.get("closeness") not in (0, None):
            continue
        # drift-check: still a leaf MATCH on the recorded draft? (per-fn asm subdir -> split-aware)
        rr = sh([PY, "tools/match_one.py", fn, "--c", d, "--asm-subdir", smap[fn][1]], timeout=180)
        if (rr.stdout.strip().splitlines() or ["?"])[0].startswith("MATCH"):
            out.append((fn, d))
        if len(out) >= limit:
            break
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--auto", action="store_true", help="pull leaf-MATCH candidates from the backlog")
    ap.add_argument("--funcs", help="comma-separated func_XXXX list (their best_draft is used)")
    ap.add_argument("--from-file", help="file with one func_XXXX per line")
    ap.add_argument("--draft-dir", action="append", default=[],
                    help="wave dir to recover from (repeatable); preferred over the backlog")
    ap.add_argument("--binary", default="ov_SC01_077")
    ap.add_argument("--limit", type=int, default=40)
    ap.add_argument("--commit", action="store_true")
    ap.add_argument("--no-propagate", action="store_true")
    ap.add_argument("--run-id", default="r1", help="run-local scratch under .run/recover/<id>/ (§55b trap 4)")
    ap.add_argument("--stages", default="demacroize",
                    help="comma-separated: demacroize,arity,self-cast,tu-scope,macro-externs (default: demacroize). §378 chain = arity,self-cast — in that order.")
    ap.add_argument("--max-tier", default="binary", choices=("draft", "binary", "fleet"),
                    help="refuse any stage whose blast radius exceeds this (default binary = no shared-state edits)")
    ap.add_argument("--r22", action="store_true", help="clean-fleet verify after banking (REQUIRED for fleet tier)")
    ap.add_argument("--probe-only", action="store_true", help="classify blockers and stop; writes nothing")
    ap.add_argument("--report", default=None, help="machine-readable per-fn outcome ledger")
    a = ap.parse_args()
    os.chdir(REPO)
    stages = [s.strip() for s in a.stages.split(",") if s.strip()]
    for s in stages:
        if s not in STAGE_TIER:
            raise SystemExit(f"unknown stage {s!r}; known: {', '.join(STAGE_TIER)}")
        if not tier_ok(s, a.max_tier):
            raise SystemExit(f"stage {s!r} is tier '{STAGE_TIER[s]}' but --max-tier is '{a.max_tier}'. "
                             f"A fleet-tier stage needs --max-tier fleet AND --r22 (§61/§63 UPDATE).")
    if any(STAGE_TIER[s] == "fleet" for s in stages) and not a.r22:
        raise SystemExit("a fleet-tier stage requires --r22: the per-binary gate is "
                         "necessary-not-sufficient for shared state (§63 UPDATE broke 139/140 that way).")

    # PROPAGATION IS ITSELF A FLEET-TIER ACTION, and it was the one write the tier machinery did not
    # cover: `run_gate(propagate=True)` shells out to `dedup_propagate --auto-from`, which writes
    # src/shared/engine_core.h and up to 138 overlay .c files — yet it was the DEFAULT here, so a
    # `--max-tier binary` run could perform the widest write in the toolchain. It cannot be caught
    # after the fact either: `assert_write_set` runs BEFORE the gate, and under --commit the writes
    # are already committed, so `git status` sees nothing. So it is refused UP FRONT, exactly the way
    # the stage tiers are — a declared radius, not a remembered one (§65a).
    # (General rule first, so BOTH refusals stay reachable and testable — a guard whose branch can
    # never fire is untested code, and this driver already shipped two such branches.)
    propagate = not a.no_propagate
    if propagate:
        if a.max_tier != "fleet" or not a.r22:
            raise SystemExit(
                "propagation is a FLEET-tier write (the shared headers under src/shared/ + up to 138 overlay .c): "
                "it requires --max-tier fleet AND --r22, or pass --no-propagate (§65a).")
        if "demacroize" in stages:
            raise SystemExit(
                "refusing to propagate a de-macroized bank: such a bank is ×1 BY CONSTRUCTION (the "
                "byte-true decl lives in this overlay's OWN TU), and `dedup_propagate --auto-from` "
                "would re-macroize the expanded sites and undo it (demacroize.py's stated price; "
                "§55b bans --auto-from regardless). Use --no-propagate, then propagate a genuinely "
                "shared bank with a targeted `dedup_propagate --addr`.")

    # ---- SINGLE-INSTANCE LOCK (P31 S65). This driver is NOT parallel-safe and now says so instead
    # of corrupting the tree: (a) assert_write_set measures a GLOBAL `git status`, so a concurrent
    # run's writes look like THIS run's blast-radius violation and abort it; (b) an abort does NOT
    # restore the stage edits already on disk; (c) gate_stage's commit is a deliberately broad
    # `git add -u src/` (it must be — propagation touches many overlays, and a narrower glob once
    # DROPPED four R22-verified banks), so a concurrent run's --commit sweeps the aborted run's
    # half-applied edits into its own commit. Measured: `xargs -P 4` over 33 binaries put 696 broken
    # lines of ov_MAIN_012 into md_MAIN_026's +1 bank commit and took check-all to 212/213 (R59: a
    # gate commits only its own block). Refuse loudly rather than mishandle (R43).
    # --probe-only is EXEMPT: it writes nothing to the tree (it execs blocker_probe, which compiles in
    # its own scratch dir), so excluding it buys no safety and costs a free diagnostic. Measured
    # 2026-08-29: a t7b drafting agent was refused the probe TWICE by this lock while an unrelated
    # sweep held it, and had to submit with its blocker unconfirmed. Guard the MUTATING path only.
    if not a.probe_only:
        lock_path = os.path.join(REPO, ".run/recover", ".driver.lock")
        os.makedirs(os.path.dirname(lock_path), exist_ok=True)
        _lock_fh = open(lock_path, "w")
        try:
            fcntl.flock(_lock_fh, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except OSError:
            sys.exit("REFUSED: another recover_integration.py is running (%s). This driver is NOT "
                     "parallel-safe — run it SERIALLY. (--probe-only is exempt: it writes nothing.)"
                     % lock_path)
        _lock_fh.write("%d\n" % os.getpid()); _lock_fh.flush()

    run_dir = f".run/recover/{a.run_id}"
    dd = f"{run_dir}/drafts"
    shutil.rmtree(os.path.join(REPO, run_dir), ignore_errors=True)

    # ---- assemble the (fn, draft) work list
    seen = {r["name"]: r for r in backlog.load_best() if r.get("name")}
    work = []
    if a.draft_dir:
        work = stage_drafts(a.draft_dir, dd, a.binary)[:a.limit]
    elif a.auto:
        work = auto_candidates(a.binary, a.limit)
    else:
        names = []
        if a.funcs:
            names += [x.strip() for x in a.funcs.split(",") if x.strip()]
        if a.from_file:
            names += [l.strip() for l in open(a.from_file) if l.strip()]
        for fn in names:
            d = (seen.get(fn) or {}).get("best_draft")
            if d and os.path.exists(d):
                work.append((fn, d))
    if not work:
        print("no candidates"); return
    fns = [fn for fn, _ in work]
    print(f"[recover] {len(fns)} candidate(s): {', '.join(fns[:8])}{'…' if len(fns) > 8 else ''}")

    # ---- stage drafts (the --draft-dir path already staged them into dd)
    if not a.draft_dir:
        shutil.rmtree(os.path.join(REPO, dd), ignore_errors=True)
        os.makedirs(os.path.join(REPO, dd))
        for fn, d in work:
            shutil.copy(os.path.join(REPO, d), os.path.join(REPO, dd, fn + ".c"))

    if a.probe_only:                  # measure, write nothing — the S0 step that re-prices the task
        # MUST come AFTER staging: --funcs/--auto/--from-file stage below this point, so the exec'd
        # probe used to open a directory that did not exist yet and die with a FileNotFoundError
        # traceback (P31 S65). Only --draft-dir, whose drafts stage_drafts() already copied, worked.
        os.execv(PY, [PY, "tools/blocker_probe.py", "--binary", a.binary,
                      "--drafts", ",".join(a.draft_dir or [dd]), "--work", f"{run_dir}/probe",
                      "--json", f"{run_dir}/blockers.json"])

    # ---- snapshot the TU files (engine_core.h + the overlay's own src). Restored EXACTLY between
    # passes — `fix_arity_callers --revert` is LOSSY for --any-proto (it rewrites `()`->`(void)`, not
    # back to the original `(a,b,c)`), which corrupts a non-bank whose caller passed args. So we
    # snapshot/restore verbatim instead. (Bug caught by the clean-rebuild verify, R22.)
    tu_files = sorted(glob.glob(os.path.join(REPO, f"src/{a.binary}/{a.binary}*.c")))   # P35 T6: no macro header to snapshot
    snapshot = {f: open(f).read() for f in tu_files}

    def restore():
        for f, t in snapshot.items():
            open(f, "w").write(t)

    os.makedirs(os.path.join(REPO, run_dir), exist_ok=True)
    listf = os.path.join(REPO, run_dir, "fns.txt")

    smap = stub_map(a.binary)

    def reconcile_and_gate(targets, propagate, commit, draft_rewrite=True):
        """no-proto the targets' conflicting caller decls, then gate each SPLIT-file group separately —
        harvest_verify substitutes into ONE --src/--asm-subdir per call, so _after/_a/_o0 drafts must be
        gated against their own split (§39). run_gate self-filters the drafts dir to each split's stubs;
        its per-group propagate is idempotent (dedup_propagate skips registered addrs).

        `draft_rewrite=False` suppresses the DRAFT-TEXT stages (macro-externs) so the drafter's own
        text is what the gate judges — see the raw-first ladder at PASS 1a (P31 S65)."""
        before = git_dirty()
        open(listf, "w").write("\n".join(targets) + "\n")

        if "arity" in stages:         # T2 — writes src/shared/engine_core.h
            r = sh([PY, "tools/fix_arity_callers.py", "--apply", "--any-proto", "--binary", a.binary,
                    "--from-file", os.path.relpath(listf, REPO), "--drafts", dd])
            if r.returncode:          # §61: a pre-pass that quietly no-ops is indistinguishable from
                raise SystemExit(f"[recover] fix_arity_callers failed: {(r.stderr or r.stdout)[-300:]}")
            print("  " + (r.stdout.strip().splitlines()[-1] if r.stdout.strip() else "(fix_arity_callers: no output)"))

        if "self-cast" in stages:      # P31 S69 — §378: the TU's own call sites of the fn being
            # DEFINED. `arity` fixes `conflicting types'; this fixes the `too few arguments' that
            # fixing it produces, because the draft's definition is now the prototype in scope.
            # Byte-neutral: gcc-2.7.2 folds a cast of a known function symbol back to a direct jal.
            # --sync-decls additionally handles the narrow-param case (a promotion-affected parameter
            # like s16 makes a no-proto decl ILLEGAL in C89, which is exactly why fix_arity_callers
            # skips it), and is safe ONLY because the call sites are cast first.
            jr = f"{run_dir}/selfcast.json"
            r = sh([PY, "tools/cast_self_callers.py", "--apply", "--sync-decls", "--binary", a.binary,
                    "--funcs", ",".join(targets), "--drafts", dd,
                    "--journal", jr])
            if r.returncode:
                raise SystemExit(f"[recover] cast_self_callers failed: {(r.stderr or r.stdout)[-300:]}")
            print("  " + (r.stdout.strip().splitlines()[-1] if r.stdout.strip() else "(self-cast: no output)"))

        if "macro-externs" in stages and draft_rewrite:  # P31 T6 — §121: a draft's decl of a DEFINE_-defined callee
            # must match the macro's OWN definition head (a guessed `extern int f();` collides with
            # the macro's real `void f(s32)` — measured: ONE such draft poisoned an entire probe
            # group's whole-binary builds). Draft-text only; drafts with no DEFINE_ callee untouched.
            import family_sweep as FS
            mds = FS.macro_def_sig_map()
            fixed = 0
            for fn in targets:
                d = os.path.join(REPO, dd, fn + ".c")
                if not os.path.exists(d):
                    continue
                txt = open(d).read()
                orig = txt
                for callee in sorted(set(re.findall(r"\bfunc_[0-9A-Fa-f]{8}\b", txt))):
                    if callee == fn or callee not in mds:
                        continue
                    txt = re.sub(rf"^[ \t]*extern\b[^;\n{{]*\b{callee}\s*\([^;{{]*\)\s*;[ \t]*$\n?",
                                 "", txt, flags=re.M)
                    if not re.search(rf"\bextern\b[^;\n]*\b{callee}\s*\(", txt):
                        txt = f"extern {mds[callee]};\n" + txt
                if txt != orig:
                    open(d, "w").write(txt)
                    fixed += 1
            print(f"  macro-externs: rewrote DEFINE_-callee decls in {fixed}/{len(targets)} drafts")

        def apply_tu_stages(subset):
            """The TU-EDITING stages, applied for ONE group's fns only (P31 T6 isolation fix: a
            stage edit in TU-A persisting while TU-B's drafts gate poisons every whole-binary build
            — measured: one group's demacroize expansion failed 3 other groups' gates)."""
            if "demacroize" in stages:    # T1 — expands the offending macro instantiations in THIS TU
                done = 0
                for fn in subset:
                    d = os.path.join(REPO, dd, fn + ".c")
                    if not os.path.exists(d):
                        continue
                    r = sh([PY, "tools/demacroize.py", "--binary", a.binary, "--fn", fn,
                            "--draft", d, "--apply"])
                    done += (r.returncode == 0)
                print(f"  demacroize: {done}/{len(subset)} had an offending instantiation to expand")
            if "tu-scope" in stages:      # P31 T6 — §103 STU: move a contested FILE-scope TU decl
                # into its consumers (declaration-only, byte-neutral by construction; the
                # sweep-only lever the recovery path lacked). ScopeRefused is loud, never fatal.
                import scope_tu_externs as STU
                moved = refused = 0
                for fn in subset:
                    d = os.path.join(REPO, dd, fn + ".c")
                    if fn not in smap or not os.path.exists(d):
                        continue
                    src_rel, _ = smap[fn]
                    tu_path = os.path.join(REPO, src_rel)
                    tu = open(tu_path).read()
                    mstub = re.search(rf'INCLUDE_ASM\("[^"]*",\s*{fn}\);', tu)
                    if not mstub:
                        continue
                    draft = open(d).read()
                    try:
                        syms = STU.contested(draft, tu, mstub.start())
                        if syms:
                            new_tu, rep = STU.scope(tu, syms, mstub.start())
                            if rep.get("moved"):
                                open(tu_path, "w").write(new_tu)
                                moved += 1
                    except STU.ScopeRefused as e:
                        refused += 1
                        print(f"  [tu-scope] {fn}: {e}", flush=True)
                print(f"  tu-scope: moved contested decls for {moved}/{len(subset)} (refused {refused})")

        tier = max((STAGE_TIER[s] for s in stages), key=lambda t: TIER_RANK[t]) if stages else "draft"
        groups = sorted({smap[fn] for fn in targets if fn in smap})
        by_group = collections.defaultdict(list)
        for fn in targets:
            if fn in smap:
                by_group[smap[fn]].append(fn)
        fleet, propagated = None, 0
        verified_all = []
        for src_rel, asm_sub in groups:
            # group-clean start: this binary's TUs back to COMMITTED truth (includes prior groups'
            # banks under --commit; wipes prior groups' un-banked stage edits). engine_core.h is
            # untouched, so a fleet-tier arity edit persists across groups as intended.
            sh(["git", "checkout", "--", f"src/{a.binary}/"])
            gbefore = git_dirty()
            apply_tu_stages(by_group[(src_rel, asm_sub)])
            # §65a — the write set decides the validator, so CHECK it rather than trusting the label.
            assert_write_set(gbefore, tier, a.binary)
            s = gate_stage.run_gate(dd, binary=a.binary, src=src_rel, asm=asm_sub, src_file=src_rel,
                                    source_tag="t6-recover", propagate=propagate, commit=commit,
                                    verified_out=f"{run_dir}/verified.txt",
                                    failed_out=f"{run_dir}/failed.txt")
            propagated += (s.get("propagated") or 0)
            fleet = s.get("fleet_pct", fleet)
            # Bank truth from the SOURCE, per group and BEFORE the next group's checkout wipes an
            # uncommitted pass-1 splice (§55b trap 4).
            verified_all += banked_from_source(a.binary, by_group[(src_rel, asm_sub)])
        return {"verified": sorted(set(verified_all)), "fleet_pct": fleet,
                "propagated": propagated, "tier": tier}

    # ---- PASS 1: reconcile+gate ALL candidates (no propagate) to find the bankable set.
    #
    # 1a gates the RAW draft text; 1b re-gates ONLY what 1a refused, with the draft-text rewrite
    # (macro-externs) applied.  Order matters and was inverted until P31 S65: macro-externs rewrites
    # a draft's callee decl to the `DEFINE_` macro's own head, but a same-named func_ADDR in ANOTHER
    # overlay is a DIFFERENT function — so the "fix" can install a wrong signature (measured:
    # `extern int func_8017C338(short*,short*,short*,int)` -> `extern void func_8017C338(void)` on a
    # byte-perfect 246-ins draft of func_8017BEBC, which then CC1-FAILed and was reported as the
    # DRAFT's failure; raw banked whole-binary-identical on the first try).  A stage that mutates the
    # thing it is measuring must never be the only variant gated (R57).
    raw_drafts = {fn: open(os.path.join(REPO, dd, fn + ".c")).read()
                  for fn in fns if os.path.exists(os.path.join(REPO, dd, fn + ".c"))}

    def put_draft(fn, text):
        open(os.path.join(REPO, dd, fn + ".c"), "w").write(text)

    print("[recover] pass 1a — gate the RAW drafts (no draft-text rewrite)")
    s1 = reconcile_and_gate(fns, propagate=False, commit=False, draft_rewrite=False)
    variant = {fn: "raw" for fn in sorted(s1.get("verified", []))}
    print(f"[recover] pass 1a banked {len(variant)}/{len(fns)} raw")
    restore()   # exact — undo pass-1a's caller edits AND the substituted defs

    rest = [fn for fn in fns if fn not in variant]
    if rest and "macro-externs" in stages:
        for fn in rest:                       # 1a left the text untouched; be explicit anyway
            if fn in raw_drafts:
                put_draft(fn, raw_drafts[fn])
        print(f"[recover] pass 1b — macro-externs rewrite, {len(rest)} draft(s) the raw gate refused")
        s1b = reconcile_and_gate(rest, propagate=False, commit=False, draft_rewrite=True)
        for fn in sorted(s1b.get("verified", [])):
            variant[fn] = "macro-externs"
        print(f"[recover] pass 1b banked "
              f"{sum(v == 'macro-externs' for v in variant.values())}/{len(rest)} rewritten")
        restore()
    elif rest:
        print(f"[recover] pass 1b skipped ({len(rest)} unbanked; macro-externs not in --stages)")

    banked = sorted(variant)
    print(f"[recover] pass 1 banked {len(banked)}/{len(fns)} "
          f"(raw {sum(v == 'raw' for v in variant.values())}, "
          f"macro-externs {sum(v == 'macro-externs' for v in variant.values())})")
    for fn, how in sorted(variant.items()):   # pass 2 must re-gate each winner's OWN variant
        if how == "raw" and fn in raw_drafts:
            put_draft(fn, raw_drafts[fn])

    if not banked:
        print(json.dumps({"banked": [], "propagated": 0, "fleet": s1.get("fleet_pct")})); return

    # ---- PASS 2: from the clean snapshot, reconcile+gate ONLY the winners (so no non-bank corruption),
    # then propagate. This is the state that gets committed.
    print("[recover] pass 2 — re-bank winners + propagate")
    # stage only the winners' drafts
    for p in glob.glob(os.path.join(REPO, dd, "*.c")):
        if os.path.basename(p)[:-2] not in banked:
            os.remove(p)
    # variants are already baked into dd/<fn>.c by pass 1 — never re-rewrite here.
    s2 = reconcile_and_gate(banked, propagate=propagate, commit=a.commit, draft_rewrite=False)
    banked2 = sorted(s2.get("verified", []))
    print(f"[recover] pass 2 banked {len(banked2)}/{len(banked)}  propagated groups +{s2.get('propagated')}  "
          f"fleet {s2.get('fleet_pct')}%")

    r22_ok = None
    if a.r22:
        r22_ok, line = r22()
        print(f"[recover] R22 clean-fleet: {line}")
        if not r22_ok:
            restore()
            raise SystemExit("[recover] ABORT — R22 failed; snapshots restored. Re-extract the binary "
                             "(a reverted src needs `make extract`, the R22 corollary) and investigate.")

    out = {"banked": banked2, "propagated": s2.get("propagated"), "fleet": s2.get("fleet_pct"),
           "tier": s2.get("tier"), "r22": r22_ok,
           "not_banked": sorted(set(fns) - set(banked2))}
    print(json.dumps(out))
    if a.report:
        json.dump(out, open(os.path.join(REPO, a.report), "w"), indent=1, sort_keys=True)


if __name__ == "__main__":
    main()
