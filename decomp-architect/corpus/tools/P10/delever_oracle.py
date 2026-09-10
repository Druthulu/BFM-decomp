#!/usr/bin/env python3
"""delever_oracle.py — the fast byte oracle for a single-translation-unit source edit (Phase 36 T2, 2026-09-09).

    tools/delever_oracle.py --recipes [-j N]              # capture every object's exact build command via `make -n -W` -> .run/P36/delever/recipes.json
    tools/delever_oracle.py --calibrate ov_SC04_011 main  # compile every TU of the named binaries UNTOUCHED: 100 % object equality with build/,
                                                          # twin == primary, then the POSITIVE control (a nop injected -> DIFFERS); exit 1 otherwise
    tools/delever_oracle.py --status                      # is the calibration current for this HEAD / Makefile?

THE QUESTION IT ANSWERS: "does this candidate text for TU X still produce the byte-identical object?" — and only that. The whole-binary
gate (`make check BINARY=…`, and the clean fleet run, R22) remains the arbiter of every batch; this oracle is the inner loop that
decides one lever site at a time in ~0.3–5 s instead of ~90 s.

HOW (the design settled at gate 1 + the plan agent's review, R57: the instrument's own path is part of the instrument):
  * the recipe of every object is the Makefile's OWN command, printed by `make -n -W <src> <obj> BINARY=<alias>` (0.04–0.15 s each;
    captured once per Makefile/config state, ~4,300 objects at -j16 in ~30 s). It carries the per-object -O0 overrides, the
    jtbl_rodata_pads stage of main/module objects, the reorder island, the twin rule (the primary's source into the twin's object).
    tools/compile_only.py's re-typed pipeline omits the pad stage and is NOT used.
  * a candidate compiles IN PLACE at the real path (objects embed the source path as an STT_FILE symbol) with `-o` and `-MF`
    redirected to scratch — build/ is never written, so the baseline object of the fleet run stays the reference; the TU's text is
    restored from the caller's in-memory snapshot (never `git checkout`, R102). Workers own whole TUs: no two candidates of one TU at once.
  * verdict = whole-object byte equality with build/<obj> (R56: build/ must come from a clean fleet run of THIS tree — --calibrate proves it).
  * CALIBRATION (R39/R57): every sampled TU compiled untouched reproduces its object byte for byte; a twin's object equals its primary's;
    a deliberately altered body reports DIFFERS. `.run/P36/delever/calibration.json` records HEAD, the Makefile/config mtimes and the
    per-object seconds (the scheduler's cost model); an --apply of the de-lever tool refuses without a current calibration.
"""
import argparse
import hashlib
import json
import os
import pathlib
import re
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))

RUN = REPO / ".run" / "P36" / "delever"
RECIPES = RUN / "recipes.json"
CALIB = RUN / "calibration.json"
SCRATCH = RUN / "obj"
RECIPE_RE = re.compile(r"^set -o pipefail; (.*) -o (build/\S+\.o)$")
SIGNAL_LINE = re.compile(r"^\s*\d+\s+(Aborted|Segmentation fault|Illegal instruction|Floating point exception|Bus error|Killed)[^\n]*", re.M)
JOB_STATUS_LINE = re.compile(r"^(bash: line \d+: )?\s*\d+\s+(Done|Exit \d+)\b")


# ----------------------------------------------------------------------------------------------------------------------
# enumeration: (alias, src, obj) for every object of every binary — derived from the Makefile's own rules (R33)
# ----------------------------------------------------------------------------------------------------------------------
def src_dirs():
    import corpus
    return dict(corpus.src_dirs())


def twin_of_map():
    import share_census
    return share_census.twin_of_map()


def objects(aliases=None):
    """[(alias, src_rel, obj_rel)] — the pattern rule build/src/%.o: src/%.c, and for a twin the primary's sources renamed into the
    twin's own object names (Makefile twin block)."""
    import compile_only
    dirs = src_dirs()
    twins = twin_of_map()
    out = []
    for a in sorted(dirs):
        if aliases and a not in aliases:
            continue
        prim = twins.get(a)
        for p in compile_only.tus_of(a, dirs):
            src = p.relative_to(REPO).as_posix()
            if prim:
                # src/<prim>/<prim><suffix>.c -> build/src/<twin>/<twin><suffix>.o
                stem = p.name[:-2]
                if not stem.startswith(prim):
                    continue
                obj = f"build/src/{a}/{a}{stem[len(prim):]}.o"
            else:
                obj = "build/" + src[:-2] + ".o"
            out.append((a, src, obj))
    return out


def config_stamp():
    files = [REPO / "Makefile"] + sorted((REPO / "config").glob("*.mk"))
    h = hashlib.sha1()
    for f in files:
        st = f.stat()
        h.update(f"{f.name}|{int(st.st_mtime)}|{st.st_size}\n".encode())
    return h.hexdigest()[:12]


def head():
    return subprocess.run(["git", "rev-parse", "--short", "HEAD"], cwd=REPO, capture_output=True, text=True).stdout.strip()


# ----------------------------------------------------------------------------------------------------------------------
# recipes
# ----------------------------------------------------------------------------------------------------------------------
def capture_recipe(alias, src, obj):
    r = subprocess.run(["make", "-n", "-W", src, obj, f"BINARY={alias}"], cwd=REPO, capture_output=True, text=True)
    if r.returncode != 0:
        return None, f"make -n rc={r.returncode}: {r.stderr.strip()[:200]}"
    lines = [ln for ln in r.stdout.splitlines() if ln.startswith("set -o pipefail;")]
    if len(lines) != 1:
        return None, f"expected ONE pipeline line, got {len(lines)}"
    m = RECIPE_RE.match(lines[0])
    if not m or m.group(2) != obj:
        return None, f"unparsed recipe: {lines[0][:160]}"
    return dict(alias=alias, src=src, obj=obj, pipeline=m.group(1)), None


def build_recipes(jobs, aliases=None):
    objs = objects(aliases)
    recipes, errors = {}, []
    t0 = time.time()
    with ThreadPoolExecutor(max_workers=jobs) as ex:
        for (a, src, obj), (rec, err) in zip(objs, ex.map(lambda t: capture_recipe(*t), objs)):
            if rec:
                recipes[obj] = rec
            else:
                errors.append(f"{a} {src} {obj}: {err}")
    return dict(stamp=config_stamp(), head=head(), generated=time.strftime("%Y-%m-%d %H:%M"), n=len(recipes),
                seconds=round(time.time() - t0, 1), recipes=recipes, errors=errors)


def load_recipes(refresh=False, jobs=16):
    if RECIPES.exists() and not refresh:
        d = json.loads(RECIPES.read_text())
        if d.get("stamp") == config_stamp():
            return d
    d = build_recipes(jobs)
    RUN.mkdir(parents=True, exist_ok=True)
    RECIPES.write_text(json.dumps(d, indent=1) + "\n")
    return d


# ----------------------------------------------------------------------------------------------------------------------
# compile + compare
# ----------------------------------------------------------------------------------------------------------------------
def compile_obj(recipe, text=None, tag="x", write_path=None):
    """Compile the recipe's source (with `text` written IN PLACE first — to `write_path` when the edited file is a header the
    source includes, else to the source itself; the CALLER restores it) to a scratch object. Returns (bytes | None, seconds, errors)."""
    src = REPO / (write_path or recipe["src"])
    obj = recipe["obj"]
    out = SCRATCH / (obj[len("build/"):].replace("/", "__")[:-2] + f".{tag}.o")
    out.parent.mkdir(parents=True, exist_ok=True)
    dep = str(out)[:-2] + ".d"
    pipeline = recipe["pipeline"]
    pipeline = re.sub(r"-MF \S+", f"-MF {dep}", pipeline, count=1)
    cmd = f"set -o pipefail; {pipeline} -o {out}"
    if text is not None:
        src.write_text(text, errors="surrogateescape")
    t0 = time.time()
    r = subprocess.run(["bash", "-c", cmd], cwd=REPO, capture_output=True, text=True)
    dt = time.time() - t0
    if r.returncode != 0 or not out.exists():
        # a pipeline member killed by a signal (cc1 2.7.2 aborts on some candidates — e.g. a variable whose only definition was a
        # launder that got deleted): bash prints the job-status block ("Done" / "Aborted (core dumped)" / "Segmentation fault")
        # and the pipeline's rc is >= 128 — that is a CRASH verdict, not a diagnostic (R103: the real message forms)
        sig = SIGNAL_LINE.search(r.stderr)
        if sig or r.returncode >= 128:
            return None, dt, "CRASH: " + (sig.group(0).strip() if sig else f"rc={r.returncode}")
        # gcc 2.7.2 prints errors without the word "error" and the assembler floods stderr with `$at` warnings: keep every
        # non-warning line (R103), then the tail
        errs = [ln for ln in r.stderr.splitlines()
                if ln.strip() and not re.search(r"\bwarning:", ln, re.I) and not ln.startswith(("In file included", " " * 16))
                and ": In function" not in ln and not JOB_STATUS_LINE.match(ln)]
        return None, dt, ("\n".join(errs[:8]) or r.stderr[-400:])
    data = out.read_bytes()
    try:
        out.unlink()
        pathlib.Path(dep).unlink(missing_ok=True)
    except OSError:
        pass
    return data, dt, ""


BASELINE = RUN / "baseline"        # the snapshot `make clean` cannot reach (see baseline_path)


def baseline_path(obj):
    """The object a score is compared against — the SNAPSHOT when one exists, else `build/`.

    Everything in this engine scores a candidate against the fleet run's object under `build/`, and the R22 gate begins
    with `make clean`, which deletes exactly that. With agents scoring in parallel (T7's burst, S102) a fleet gate would
    make every live `--try` compare against a missing or half-written baseline and report nonsense in the agent's own
    voice. The snapshot decouples the two: the baseline is the ORIGINAL game's bytes, which never change as we bank (a
    bank is byte-identical by construction), so a copy taken from any green fleet is valid until the fleet stops being
    green. Refresh it with `--snapshot-baseline` after a green `check-all`; a missing object simply falls back to
    `build/`, so nothing silently scores against half a snapshot."""
    if obj.startswith("build/"):
        p = BASELINE / obj[len("build/"):]
        if p.exists():
            return p
    return REPO / obj


def snapshot_baseline():
    """Copy every object under `build/` into the snapshot. Run it after a GREEN `check-all` — the caller states that; this
    records the HEAD it was taken at so a reader can tell what it is."""
    import shutil, subprocess as sp
    n = 0
    BASELINE.mkdir(parents=True, exist_ok=True)
    for src in sorted((REPO / "build").glob("**/*.o")):
        rel = src.relative_to(REPO / "build")
        dst = BASELINE / rel
        dst.parent.mkdir(parents=True, exist_ok=True)
        if not dst.exists() or dst.stat().st_mtime < src.stat().st_mtime or dst.stat().st_size != src.stat().st_size:
            shutil.copy2(src, dst)
        n += 1
    head = sp.run(["git", "rev-parse", "HEAD"], cwd=REPO, capture_output=True, text=True).stdout.strip()
    (BASELINE / "TAKEN_AT.txt").write_text(f"{head}\n{n} objects\n")
    print(f"delever_oracle --snapshot-baseline: {n} object(s) under {BASELINE.relative_to(REPO)} at {head[:9]}")
    return n


def baseline_bytes(obj):
    p = baseline_path(obj)
    return p.read_bytes() if p.exists() else None


def judge(recipe, text, tag="x", write_path=None):
    """(verdict, seconds, err): verdict in IDENTICAL | DIFFERS | COMPILE-ERROR | NO-BASELINE."""
    base = baseline_bytes(recipe["obj"])
    if base is None:
        return "NO-BASELINE", 0.0, ""
    data, dt, err = compile_obj(recipe, text, tag, write_path)
    if data is None:
        return ("COMPILE-CRASH" if err.startswith("CRASH:") else "COMPILE-ERROR"), dt, err
    return ("IDENTICAL" if data == base else "DIFFERS"), dt, ""


def recipes_by_src(recipes):
    """src rel -> [recipe] (a twin binary compiles the primary's source into its own object: two recipes, one source)."""
    out = {}
    for r in recipes.values():
        out.setdefault(r["src"], []).append(r)
    for v in out.values():
        v.sort(key=lambda r: r["obj"])
    return out


def judge_all(recipes, text, tag="x", write_path=None):
    """Every recipe of one written file judged in turn (the file is written once, by the first compile; the CALLER restores it).
    Returns (verdict, seconds, err): IDENTICAL only if every object is identical; otherwise the first non-identical verdict."""
    total, first = 0.0, None
    for i, r in enumerate(recipes):
        v, dt, err = judge(r, text if i == 0 else None, tag=tag, write_path=write_path)
        total += dt
        if v != "IDENTICAL" and first is None:
            first = (v, err)
    return (first[0] if first else "IDENTICAL"), total, (first[1] if first else "")


# ----------------------------------------------------------------------------------------------------------------------
# calibration
# ----------------------------------------------------------------------------------------------------------------------
def calibrate(aliases, jobs, recipes):
    """Every object of the named binaries compiled UNTOUCHED -> must equal build/; twin == primary; then the positive control."""
    recs = [r for r in recipes["recipes"].values() if r["alias"] in aliases]
    if not recs:
        sys.exit(f"delever_oracle: no recipes for {aliases} (R43)")
    twins = twin_of_map()
    results = []

    def one(r):
        v, dt, err = judge(r, None, tag="cal")
        return dict(alias=r["alias"], obj=r["obj"], verdict=v, seconds=round(dt, 3), err=err[-200:])
    with ThreadPoolExecutor(max_workers=jobs) as ex:
        results = list(ex.map(one, recs))
    ok = sum(1 for x in results if x["verdict"] == "IDENTICAL")
    bad = [x for x in results if x["verdict"] != "IDENTICAL"]
    # twin == primary on the objects both build
    twin_checks = []
    for a in aliases:
        prim = twins.get(a)
        if not prim:
            continue
        for r in recipes["recipes"].values():
            if r["alias"] == a:
                pobj = r["obj"].replace(f"build/src/{a}/{a}", f"build/src/{prim}/{prim}")
                same = baseline_bytes(r["obj"]) == baseline_bytes(pobj)
                twin_checks.append(dict(twin=r["obj"], primary=pobj, equal=same))
    twin_bad = [t for t in twin_checks if not t["equal"]]
    # the positive control: a nop injected into a REAL function body (the first definition the shared scanner finds in the
    # first recipe's source with a body of >= 3 lines) must DIFFER — a verifier that cannot fail is no verifier (R39/R53)
    import share_census as sc
    ctl = recs[0]
    src = REPO / ctl["src"]
    st0 = src.stat()
    orig = src.read_text(errors="surrogateescape")
    pos_verdict = "SKIPPED"
    defs = [r for r in sc.scan_text(orig, ctl["src"], shared_defs=None) if r["form"] == "def" and r.get("nlines", 0) >= 3 and not r.get("empty")]
    if defs:
        d = defs[0]
        line_starts = [0]
        for ln in orig.split("\n"):
            line_starts.append(line_starts[-1] + len(ln) + 1)
        # at the END of the body (C89: a statement before the declarations is a parse error)
        o = orig.rfind("}", line_starts[d["end"] - 1], line_starts[d["end"]])
        if o >= 0:
            cand = orig[:o] + '    __asm__("nop");\n' + orig[o:]
            try:
                pos_verdict, _, err = judge(ctl, cand, tag="ctl")
                pos_verdict = pos_verdict if pos_verdict != "COMPILE-ERROR" else f"COMPILE-ERROR ({err[-100:]})"
            finally:
                src.write_text(orig, errors="surrogateescape")
                os.utime(src, ns=(st0.st_atime_ns, st0.st_mtime_ns))   # the census's src stamp is stat-based: a restore is not a change
    by_alias = {}
    for x in results:
        d = by_alias.setdefault(x["alias"], dict(objects=0, identical=0, seconds=0.0))
        d["objects"] += 1
        d["identical"] += x["verdict"] == "IDENTICAL"
        d["seconds"] += x["seconds"]
    return dict(head=head(), stamp=config_stamp(), generated=time.strftime("%Y-%m-%d %H:%M"), aliases=sorted(aliases),
                objects=len(results), identical=ok, failures=bad[:20], twin_checks=len(twin_checks), twin_mismatch=twin_bad[:10],
                positive_control=dict(obj=ctl["obj"], verdict=pos_verdict),
                per_alias={a: dict(v, mean_s=round(v["seconds"] / max(v["objects"], 1), 3)) for a, v in by_alias.items()},
                per_object_seconds={x["obj"]: x["seconds"] for x in results},
                ok=(not bad and not twin_bad and pos_verdict == "DIFFERS"))


def calibration_current():
    if not CALIB.exists():
        return False, "no calibration"
    d = json.loads(CALIB.read_text())
    if d.get("head") != head():
        return False, f"calibrated at {d.get('head')}, HEAD is {head()}"
    if d.get("stamp") != config_stamp():
        return False, "the Makefile/config changed since the calibration"
    return bool(d.get("ok")), ("ok" if d.get("ok") else "the calibration FAILED")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--recipes", action="store_true", help="(re)capture every object's recipe")
    ap.add_argument("--calibrate", nargs="*", help="binaries to calibrate on (e.g. ov_SC04_011 ov_SC03_015 main)")
    ap.add_argument("--status", action="store_true")
    ap.add_argument("--snapshot-baseline", action="store_true",
                    help="copy build/**/*.o into the snapshot every score compares against (run after a GREEN check-all)")
    ap.add_argument("-j", "--jobs", type=int, default=16)
    a = ap.parse_args()
    RUN.mkdir(parents=True, exist_ok=True)
    if a.snapshot_baseline:
        sys.exit(0 if snapshot_baseline() else 1)
    if a.status:
        ok, why = calibration_current()
        print(f"delever_oracle: calibration {'CURRENT' if ok else 'STALE/MISSING'} — {why}")
        sys.exit(0 if ok else 1)
    if a.recipes:
        d = load_recipes(refresh=True, jobs=a.jobs)
        print(f"delever_oracle: {d['n']} recipes captured in {d['seconds']} s at -j{a.jobs}; errors {len(d['errors'])}")
        for e in d["errors"][:10]:
            print("  ", e)
        sys.exit(1 if d["errors"] else 0)
    if a.calibrate is not None:
        recipes = load_recipes(jobs=a.jobs)
        t0 = time.time()
        d = calibrate(a.calibrate, a.jobs, recipes)
        d["seconds"] = round(time.time() - t0, 1)
        CALIB.write_text(json.dumps(d, indent=1) + "\n")
        print(f"delever_oracle --calibrate {' '.join(d['aliases'])}: {d['identical']}/{d['objects']} objects byte-identical untouched; "
              f"twin checks {d['twin_checks']} ({len(d['twin_mismatch'])} mismatch); positive control {d['positive_control']['verdict']} "
              f"on {d['positive_control']['obj']}; {d['seconds']} s — {'OK' if d['ok'] else 'FAIL'}")
        for a_, v in d["per_alias"].items():
            print(f"   {a_:14s} {v['identical']}/{v['objects']} identical, mean {v['mean_s']} s per object")
        for f in d["failures"][:10]:
            print("   FAIL", f["alias"], f["obj"], f["verdict"], f["err"][-120:])
        sys.exit(0 if d["ok"] else 1)
    ap.print_help()


if __name__ == "__main__":
    main()
