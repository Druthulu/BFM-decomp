#!/usr/bin/env python3
"""delever_oracle.py — the fast byte oracle for a single-translation-unit source edit (Phase 36 T2, 2026-09-09).

    tools/delever_oracle.py --recipes [-j N]              # capture every object's exact build command via `make -n -W` -> .run/P36/delever/recipes.json
    tools/delever_oracle.py --calibrate ov_SC04_011 main  # compile every TU of the named binaries UNTOUCHED: 100 % object equality with build/,
                                                          # twin == primary, then the POSITIVE control (a nop injected -> DIFFERS); exit 1 otherwise
    tools/delever_oracle.py --status                      # is the calibration current for this HEAD / Makefile?
    tools/delever_oracle.py --snapshot-baseline           # build/**/*.o + every binary's link inputs -> .run/P36/delever/baseline/ (after a GREEN check-all)
    tools/delever_oracle.py --linked-control              # Phase 37 T3: the f3 known-true (reloc spelling: whole-object DIFFERS, linked IDENTICAL) + its negative

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
  * THE LINKED MODE (Phase 37 T3, 2026-09-12 — the T2 finding (h)): a correct global-block edit can be whole-object DIFFERS while the
    LINKED bytes are identical, because only the RELOCATION SPELLING changed (`D_801F8872` vs `D_801F8870`+2 resolve to one address;
    the immediate field and the symbol differ in the .o). `judge_linked` therefore runs the build's OWN tail on the candidate object:
    the binary's snapshot `.ld` with the one object pointed at the candidate and every other object at the snapshot's copy, the
    Makefile's exact `ld … -T <undefined_syms> -T <undefined_funcs> [-T build/psyq/*_externals.ld] --no-check-sections`, `objcopy -O
    binary`, the <=3-byte end-align trim, and SHA1 against config/check.<alias>.sha — nothing of HI16/LO16 pairing is re-implemented
    (R110: the tree's own bytes through the build's own tail). ~0.3 s per judgement; run only AFTER a whole-object DIFFERS, when the
    edit is flagged relocation-spelling or `reloc_only_diff` says the .text words agree modulo relocation operands. The snapshot
    (`--snapshot-baseline`) therefore also carries every binary's link inputs (`_link/<alias>/`, `links.json`), so a clean fleet
    rebuild can run beside a live linked judgement (R112).
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
CPP_CONTEXT_LINE = re.compile(r"^\s*(\d+\s*\|.*|\|\s*)$")            # modern cpp's source-context lines under a redefinition warning


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
                and ": In function" not in ln and not JOB_STATUS_LINE.match(ln)
                and not CPP_CONTEXT_LINE.match(ln) and ": note:" not in ln]        # cpp's `NNN | #define …` / `|` context + notes (P37 T3)
        # gcc 2.7.2's `At top level:` is a PREFIX line; keep the message lines ahead of it in the cap
        errs.sort(key=lambda ln: ln.rstrip().endswith("At top level:"))
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
    records the HEAD it was taken at so a reader can tell what it is.

    THE GUARD (T3, 2026-09-12): every object whose bytes CHANGE in the snapshot is re-derived — its TU compiled UNTOUCHED through
    its own recipe must reproduce the new bytes — else the previous snapshot copy is restored and the refresh is REFUSED, naming
    the object. Why: a `make build BINARY=x` run with a candidate in place (T2's relocation control) writes build/ with an object
    that links identically but is not the tree's; a refresh then carried it into the snapshot, and the linked-mode control read
    `IDENTICAL` for a spelling the tree does not have. build/ is a build product, the snapshot is an oracle input (R56/R112) —
    the guard is what makes the second true."""
    import shutil, subprocess as sp
    n, changed = 0, []
    BASELINE.mkdir(parents=True, exist_ok=True)
    for src in sorted((REPO / "build").glob("**/*.o")):
        rel = src.relative_to(REPO / "build")
        dst = BASELINE / rel
        dst.parent.mkdir(parents=True, exist_ok=True)
        if not dst.exists() or dst.stat().st_mtime < src.stat().st_mtime or dst.stat().st_size != src.stat().st_size:
            old = dst.read_bytes() if dst.exists() else None
            new = src.read_bytes()
            if old != new:
                changed.append(("build/" + rel.as_posix(), old))
            shutil.copy2(src, dst)
        n += 1
    refused = []
    if changed:
        by_obj = load_recipes()["recipes"]
        for obj, old in changed:
            r = by_obj.get(obj)
            if r is None:
                continue                      # asm/asset/psyq objects: no TU recipe to re-derive from
            v, dt, err = judge(r, None, tag="snap")
            if v != "IDENTICAL":
                refused.append((obj, v, err[-120:]))
                dst = BASELINE / obj[len("build/"):]
                if old is not None:
                    dst.write_bytes(old)
                else:
                    dst.unlink(missing_ok=True)
    if refused:
        print(f"delever_oracle --snapshot-baseline: REFUSED — {len(refused)} changed object(s) do not reproduce from an untouched compile "
              f"of their TU (build/ is not the tree's; run the clean fleet gate first, R22/R56):")
        for obj, v, err in refused:
            print(f"   {obj}: {v} {err}")
        return 0
    head = sp.run(["git", "rev-parse", "HEAD"], cwd=REPO, capture_output=True, text=True).stdout.strip()
    (BASELINE / "TAKEN_AT.txt").write_text(f"{head}\n{n} objects\n{len(changed)} changed since the previous snapshot\n")
    table = snapshot_links()
    ok = sum(1 for v in table.values() if not v.get("error") and v.get("ld_script_snap"))
    print(f"delever_oracle --snapshot-baseline: {n} object(s) under {BASELINE.relative_to(REPO)} at {head[:9]}; link inputs for "
          f"{ok}/{len(table)} binaries under {LINKDIR.relative_to(REPO)} (links.json)")
    return n


def baseline_bytes(obj):
    p = baseline_path(obj)
    return p.read_bytes() if p.exists() else None


# ----------------------------------------------------------------------------------------------------------------------
# the linked mode (Phase 37 T3): the build's own link on the candidate object
# ----------------------------------------------------------------------------------------------------------------------
LINKDIR = BASELINE / "_link"
LINKS = BASELINE / "links.json"
_MAKE_QUERY = "__q:\n\t@echo \"$(BINARY)|$(LD)|$(OBJCOPY)|$(LD_SCRIPT)|$(UNDEF_SYMS)|$(UNDEF_FUNCS)|$(EXE)|$(CHECK_SHA)|$(OUT)\"\n"
OBJ_IN_LD = re.compile(r'"?((?:build|asm|assets)/[^\s"()]+\.o)"?')


def link_vars(alias):
    """The Makefile's OWN link variables for one binary (R33: asked of make, never re-typed): dict(ld, objcopy, ld_script,
    undef_syms, undef_funcs, exe, check_sha, out, syms_frags, exe_size). syms_frags = main's `-T build/psyq/*_externals.ld` list in
    the Makefile's order, the files that exist (the recipe's `[ -f ]` tests); empty for every other binary (the ifeq skips them)."""
    r = subprocess.run(["make", "-s", "-f", "Makefile", "-f", "-", f"BINARY={alias}", "__q"], cwd=REPO, input=_MAKE_QUERY,
                       capture_output=True, text=True)
    if r.returncode != 0 or "|" not in r.stdout:
        raise RuntimeError(f"link_vars({alias}): make query failed rc={r.returncode}: {r.stderr.strip()[:200]}")
    f = r.stdout.strip().splitlines()[-1].split("|")
    d = dict(alias=f[0], ld=f[1], objcopy=f[2], ld_script=f[3], undef_syms=f[4], undef_funcs=f[5], exe=f[6], check_sha=f[7], out=f[8])
    frags = []
    if alias == "main":
        mk = (REPO / "Makefile").read_text()
        for m in re.finditer(r"^(\w+_SYMS)\s*:=\s*(build/psyq/\S+)\s*$", mk, re.M):
            if (REPO / m.group(2)).exists():
                frags.append(m.group(2))
    d["syms_frags"] = frags
    exe = REPO / d["exe"]
    d["exe_size"] = exe.stat().st_size if exe.exists() else None
    d["want_sha"] = (REPO / d["check_sha"]).read_text().split()[0] if (REPO / d["check_sha"]).exists() else None
    return d


def snapshot_links(aliases=None):
    """Copy every binary's link inputs into the snapshot (`_link/<alias>/<basename>`; main's externals under `_link/psyq/`) and
    write links.json. Called by snapshot_baseline; the .ld's object paths stay `build/…` — judge_linked redirects them."""
    import shutil
    dirs = src_dirs()
    table = {}
    for a in sorted(dirs):
        if aliases and a not in aliases:
            continue
        try:
            v = link_vars(a)
        except RuntimeError as ex:
            table[a] = dict(error=str(ex))
            continue
        dst = LINKDIR / a
        dst.mkdir(parents=True, exist_ok=True)
        for key in ("ld_script", "undef_syms", "undef_funcs"):
            src = REPO / v[key]
            if src.exists():
                shutil.copy2(src, dst / pathlib.Path(v[key]).name)
                v[key + "_snap"] = str((dst / pathlib.Path(v[key]).name).relative_to(REPO))
        snap_frags = []
        for fr in v["syms_frags"]:
            (LINKDIR / "psyq").mkdir(parents=True, exist_ok=True)
            shutil.copy2(REPO / fr, LINKDIR / "psyq" / pathlib.Path(fr).name)
            snap_frags.append(str((LINKDIR / "psyq" / pathlib.Path(fr).name).relative_to(REPO)))
        v["syms_frags_snap"] = snap_frags
        table[a] = v
    LINKS.write_text(json.dumps(dict(head=head(), stamp=config_stamp(), generated=time.strftime("%Y-%m-%d %H:%M"), links=table), indent=1) + "\n")
    return table


_links_cache = None


def links():
    """The snapshot's link table (alias -> link_vars + snapshot paths); refuses when the snapshot has none (R43)."""
    global _links_cache
    if _links_cache is None:
        if not LINKS.exists():
            raise RuntimeError("no links.json in the baseline snapshot — run `tools/delever_oracle.py --snapshot-baseline` after a GREEN check-all")
        _links_cache = json.loads(LINKS.read_text())["links"]
    return _links_cache


def judge_linked(recipe, cand_bytes, tag="x"):
    """(verdict, seconds, err) for a candidate OBJECT: the binary linked with this object in place of the recipe's, everything
    else from the snapshot, through the Makefile's own ld/objcopy/trim, SHA1 against config/check.<alias>.sha. verdict in
    IDENTICAL | DIFFERS | LINK-ERROR | NO-LINK-INPUTS."""
    alias, obj = recipe["alias"], recipe["obj"]
    lv = links().get(alias)
    if not lv or lv.get("error") or not lv.get("ld_script_snap") or lv.get("exe_size") is None or not lv.get("want_sha"):
        return "NO-LINK-INPUTS", 0.0, f"the snapshot carries no link inputs for {alias}"
    flat = obj[len("build/"):].replace("/", "__")[:-2] + f".{tag}"
    SCRATCH.mkdir(parents=True, exist_ok=True)
    cand = SCRATCH / (flat + ".lnk.o")
    ld_s = SCRATCH / (flat + ".ld")
    elf = SCRATCH / (flat + ".elf")
    binp = SCRATCH / (flat + ".bin")
    t0 = time.time()
    try:
        cand.write_bytes(cand_bytes)
        script = (REPO / lv["ld_script_snap"]).read_text()

        def redirect(m):
            path = m.group(1)
            if path == obj:
                return str(cand)
            snap = BASELINE / path[len("build/"):] if path.startswith("build/") else None
            return str(snap) if snap is not None and snap.exists() else path
        script2 = OBJ_IN_LD.sub(redirect, script)
        if str(cand) not in script2:
            return "LINK-ERROR", time.time() - t0, f"{obj} is not named in {lv['ld_script_snap']}"
        ld_s.write_text(script2)
        cmd = [lv["ld"], "-T", str(ld_s)]
        for key in ("undef_syms_snap", "undef_funcs_snap"):
            if lv.get(key):
                cmd += ["-T", lv[key]]
        for fr in lv.get("syms_frags_snap", []):
            cmd += ["-T", fr]
        cmd += ["--no-check-sections", "-o", str(elf)]
        r = subprocess.run(cmd, cwd=REPO, capture_output=True, text=True)
        if r.returncode != 0:
            errs = [ln for ln in r.stderr.splitlines() if ln.strip() and "warning" not in ln.lower()]
            return "LINK-ERROR", time.time() - t0, "\n".join(errs[:6])[-400:]
        r = subprocess.run([lv["objcopy"], "-O", "binary", str(elf), str(binp)], cwd=REPO, capture_output=True, text=True)
        if r.returncode != 0:
            return "LINK-ERROR", time.time() - t0, r.stderr[-300:]
        data = binp.read_bytes()
        d = len(data) - lv["exe_size"]
        if 0 < d <= 3:
            data = data[:lv["exe_size"]]          # the Makefile's shrink-only end-align trim
        got = hashlib.sha1(data).hexdigest()
        if got == lv["want_sha"]:
            return "IDENTICAL", time.time() - t0, ""
        return "DIFFERS", time.time() - t0, f"linked sha {got[:12]} != {lv['want_sha'][:12]} (size {len(data)} vs {lv['exe_size']})"
    finally:
        for p in (cand, ld_s, elf, binp):
            try:
                p.unlink()
            except OSError:
                pass


def reloc_only_diff(cand_bytes, base_path, tag="x"):
    """True when the two objects' .text instruction streams agree word for word under the relocation mask and differ only in
    relocation OPERANDS (which symbol/addend a link-time field names) — the shape a global-block respelling produces, and the
    cheap pre-check (~60 ms) before paying for a linked judgement. False on any masked-word or length difference."""
    import masked_diff as md
    SCRATCH.mkdir(parents=True, exist_ok=True)
    tmp = SCRATCH / (hashlib.sha1(cand_bytes).hexdigest()[:12] + f".{tag}.ro.o")
    tmp.write_bytes(cand_bytes)
    try:
        mine = md.insns_from_object(str(tmp))
        tgt = md.insns_from_object(str(base_path))
    finally:
        tmp.unlink(missing_ok=True)
    if not mine or not tgt or len(mine) != len(tgt):
        return False
    ops_differ = False
    for c, t in zip(mine, tgt):
        m = md.mask_for(t["word"], t["reloc_kind"])
        if (c["word"] & m) != (t["word"] & m) or md._j_mismatch(c, t):
            return False
        if (c["reloc_op"] or "") != (t["reloc_op"] or "") or (c["word"] != t["word"]):
            ops_differ = True
    return ops_differ


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


def linked_control():
    """The linked mode's known-true and negative (R39/R110), on the T2 finding (h)'s own body — md_SC07_004 `func_801A4258`, whose
    `s16` globals D_801F8870/72/74 are one array walked through a pointer in the original: spelling `D_801F8872` as `p[1]` changes
    the relocation (`D_801F8870`+2 for `D_801F8872`+0) and NOTHING else, so the object DIFFERS and the linked binary is IDENTICAL;
    `p[2]` for D_801F8872 (a wrong addend) must DIFFER in both. Exit 0 only when all four verdicts are as predicted."""
    tu = "src/md_SC07_004/md_SC07_004.c"
    recs = recipes_by_src(load_recipes()["recipes"]).get(tu, [])
    if not recs:
        print("linked-control: no recipe for", tu); return 1
    r = recs[0]
    path = REPO / tu
    raw = path.read_text(errors="surrogateescape")
    st = path.stat()
    body_a = raw.index("void func_801A4258(void) {")
    body_z = raw.index("\n}\n", body_a) + 3
    body = raw[body_a:body_z]
    if body.count("D_801F8872") != 3 or body.count("D_801F8874") != 3:
        print("linked-control: the control body has changed shape (expected 3 mentions each of D_801F8872/D_801F8874)"); return 1
    good = raw[:body_a] + body.replace("D_801F8872", "p[1]").replace("D_801F8874", "p[2]") + raw[body_z:]
    bad = raw[:body_a] + body.replace("D_801F8872", "p[2]").replace("D_801F8874", "p[3]") + raw[body_z:]
    base = baseline_bytes(r["obj"])
    out, ok = [], True
    try:
        for name, text, want_whole, want_ro, want_link in (("known-true p[1]/p[2]", good, "DIFFERS", True, "IDENTICAL"),
                                                          ("negative p[2]/p[3]", bad, "DIFFERS", True, "DIFFERS")):
            data, dt, err = compile_obj(r, text, tag="lc")
            restore = path.write_text(raw, errors="surrogateescape")
            if data is None:
                out.append(f"  {name}: COMPILE-ERROR {err[:120]}"); ok = False; continue
            whole = "IDENTICAL" if data == base else "DIFFERS"
            ro = reloc_only_diff(data, baseline_path(r["obj"]), tag="lc")
            lv, dt2, lerr = judge_linked(r, data, tag="lc")
            line = f"  {name}: whole-object {whole} · reloc-only {ro} · linked {lv} ({dt2:.2f} s){' ' + lerr if lerr else ''}"
            good_row = (whole == want_whole and ro == want_ro and lv == want_link)
            out.append(line + ("  ✓" if good_row else f"  ✗ expected {want_whole}/{want_ro}/{want_link}"))
            ok = ok and good_row
    finally:
        path.write_text(raw, errors="surrogateescape")
        os.utime(path, ns=(st.st_atime_ns, st.st_mtime_ns))
    print("delever_oracle --linked-control (md_SC07_004 func_801A4258, the f3 shape):")
    print("\n".join(out))
    print("linked-control:", "OK" if ok else "FAIL")
    return 0 if ok else 1


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
    ap.add_argument("--linked-control", action="store_true", help="the linked mode's known-true + negative on md_SC07_004 func_801A4258 (T3)")
    ap.add_argument("-j", "--jobs", type=int, default=16)
    a = ap.parse_args()
    RUN.mkdir(parents=True, exist_ok=True)
    if a.linked_control:
        sys.exit(linked_control())
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
