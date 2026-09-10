#!/usr/bin/env python3
"""decl_repair — widen every call declaration that lies, and measure on the BYTES which repairs are free.

THE QUESTION (Drew, P36 S102). `argcheck` found 110,478 declarations narrower than the callee's real definition, over
1,912 callees. Only a few hundred of those sit in a body that still holds a register pin; the rest are in functions that
already match byte-for-byte. Those do not block anything — but they are wrong C: a call declared to take nothing that
really takes a pointer compiles and matches through the calling convention, not because the declaration is true, and
every one of them is a lie the names and types phases would inherit.

WHY THIS IS NOT HOUSEKEEPING. Repairing a declaration can CHANGE THE BYTES — that is exactly why it removes pins
elsewhere. So the repair is not free by assumption, it is free or not by measurement, one translation unit at a time:

  * IDENTICAL — the widened declarations produce the same object. The repair is FREE and can be applied with the gate as
    its proof.
  * DIFFERS   — this unit's code depends on the false declaration. That is the interesting list, not the failure list:
    each one is a body quietly compensating for a wrong signature, and some of them are pins waiting to come off.
  * COMPILE-ERROR — the widened form conflicts with something else in the unit (a second declaration, a K&R definition).

Nothing is written into the tree: each candidate is compiled from a scratch copy of the unit through that unit's own
recipe, and compared against the baseline snapshot the fleet gate cannot wipe. Run it while agents are working.
"""
import argparse, collections, concurrent.futures as cf, json, os, pathlib, re, subprocess, sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import argcheck, delever_oracle as oracle, lever_census as lc

REPO = pathlib.Path(__file__).resolve().parent.parent
SCRATCH = REPO / ".run" / "P36" / "declrepair"
DECL = re.compile(r"(\bextern\s+)([A-Za-z_][\w \t*]*?)\b([A-Za-z_]\w*)(\s*\()([^;)]*)(\)\s*;)")


CALLSITE = re.compile(r"(?<![\w.>])([A-Za-z_]\w*)\s*\(")


def call_arities(masked, callee):
    """[n] — how many arguments each call to `callee` in this unit actually passes."""
    out = []
    for m in re.finditer(r"(?<![\w.>])" + re.escape(callee) + r"\s*\(", masked):
        depth, j = 0, m.end() - 1
        while j < len(masked):
            if masked[j] == "(":
                depth += 1
            elif masked[j] == ")":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        if j >= len(masked):
            continue
        args = masked[m.end():j].strip()
        out.append(0 if args == "" else args.count(",") + 1)
    return out


def widen(text, defs):
    """(new text, [(callee, declared, real)]) — the declarations this unit can HONESTLY repair.

    A declaration is only rewritten when EVERY call to that function in this unit ALREADY passes at least the real
    number of arguments. That is the free-correctness set: the code already does the right thing and only the promise is
    wrong, which is what m2c leaves behind when it emits `extern void f();` and then calls `f(x)`.

    The first version of this tool widened every narrower declaration and left the call sites alone, which is not a
    repair at all — a prototype that demands an argument the call does not pass is a hard error, so 1,766 of the first
    3,250 units could not compile BY CONSTRUCTION and not one was IDENTICAL. A measurement that cannot come out any
    other way is not a measurement (R40: clear the instrument before believing its subject). Calls that pass too few
    arguments are the OTHER population — R19's, where the argument has to be chosen and the bytes decide.

    The RETURN TYPE is never touched: this repairs arity, not results."""
    masked = lc.sc.mask_text(text)
    fixed = []

    def sub(m):
        callee, params = m.group(3), m.group(5)
        real = defs.get(callee)
        if real is None:
            return m.group(0)
        dec = argcheck.arity(params)
        if dec >= real[0]:
            return m.group(0)
        calls = call_arities(masked, callee)
        if not calls or any(n < real[0] for n in calls):
            return m.group(0)                              # a call still passes too few: R19's job, not this one
        fixed.append((callee, dec, real[0]))
        return m.group(1) + m.group(2) + m.group(3) + m.group(4) + real[1] + m.group(6)

    return DECL.sub(sub, text), fixed


_SEC_CACHE = {}


def sections(objpath, tag):
    """The bytes of `.text`, `.rodata` and `.data` — the CODEGEN, without the object's embedded source path.

    A whole-object comparison cannot work here: the candidate is compiled from a scratch copy, so its file name is
    recorded in the object and every candidate DIFFERS by construction. The first fleet run of this tool returned
    0 IDENTICAL of 3,634 units for exactly that reason and I believed it for one report — the negative control that
    would have caught it in a second (compile the UNCHANGED text through the same path and require IDENTICAL) is now
    part of every unit's judgement below (R39). With the path excluded, the control's sections match exactly."""
    key = (str(objpath), tag)
    if key in _SEC_CACHE:
        return _SEC_CACHE[key]
    out = b""
    for sec in (".text", ".rodata", ".data"):
        dst = SCRATCH / "_sec" / (re.sub(r"\W+", "_", str(objpath)) + tag + sec)
        dst.parent.mkdir(parents=True, exist_ok=True)
        r = subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", f"--only-section={sec}",
                            str(objpath), str(dst)], capture_output=True)
        out += dst.read_bytes() if (r.returncode == 0 and dst.exists()) else b""
    _SEC_CACHE[key] = out
    return out


def compile_to(rel, rec, text, tag):
    """(object path | None, err) — `text` compiled from a scratch copy of the unit through its own recipe."""
    d = SCRATCH / re.sub(r"\W+", "_", rel)
    d.mkdir(parents=True, exist_ok=True)
    scratch_src = d / os.path.basename(rec["src"])
    scratch_src.write_text(text if rel == rec["src"] else
                           (REPO / rec["src"]).read_text(errors="surrogateescape"), errors="surrogateescape")
    pipeline = rec["pipeline"].replace(" " + rec["src"], " " + scratch_src.as_posix(), 1) \
                              .replace("-Iinclude", f"-Iinclude -I{os.path.dirname(rec['src'])}", 1)
    data, dt, err = oracle.compile_obj(dict(rec, pipeline=pipeline, src=scratch_src.as_posix()), None,
                                       tag=tag + "_" + re.sub(r"\W+", "_", rel))
    if data is None:
        return None, err
    op = d / (tag + ".o")
    op.write_bytes(data)
    return op, ""


def judge(rel, rec, defs):
    try:
        raw = (REPO / rel).read_text(errors="surrogateescape")
    except OSError as e:
        return dict(tu=rel, verdict="UNREADABLE", err=str(e)[:120], fixed=0)
    if "extern" not in raw:
        return None
    new, fixed = widen(raw, defs)
    if not fixed:
        return None
    basep = oracle.baseline_path(rec["obj"])
    if not pathlib.Path(basep).exists():
        return dict(tu=rel, verdict="NO-BASELINE", fixed=len(fixed), callees=[], err="")
    base = sections(basep, "base")
    # R39, in the tool: the UNCHANGED text must reproduce the baseline through this same path, or the verdict below is
    # about the harness rather than the repair.
    ctl, cerr = compile_to(rel, rec, raw, "ctl")
    if ctl is None or sections(ctl, "ctl") != base:
        return dict(tu=rel, verdict="CONTROL-FAILED", fixed=len(fixed), callees=[], err=cerr[:160])
    cand, err = compile_to(rel, rec, new, "cand")
    if cand is None:
        v = "COMPILE-CRASH" if err.startswith("CRASH:") else "COMPILE-ERROR"
    else:
        v = "IDENTICAL" if sections(cand, "cand") == base else "DIFFERS"
    return dict(tu=rel, verdict=v, fixed=len(fixed),
                callees=sorted({c for c, _, _ in fixed})[:8], err=err[:160] if cand is None else "")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("-j", "--jobs", type=int, default=8)
    ap.add_argument("--limit", type=int)
    ap.add_argument("--json", default=".run/P36/engine/decl_repair.json")
    ap.add_argument("--apply", action="store_true",
                    help="write the repairs into the tree, ONLY for units this run judged IDENTICAL (each unit is "
                         "re-judged here, never trusted from a previous run's json — the tree may have moved)")
    a = ap.parse_args()
    defs = argcheck.definitions()
    by_src = oracle.recipes_by_src(oracle.load_recipes()["recipes"])
    units = [(rel, recs[0]) for rel, recs in sorted(by_src.items()) if recs]
    if a.limit:
        units = units[:a.limit]
    print(f"decl_repair: {len(units)} translation unit(s) with a recipe; {len(defs)} definitions; -j{a.jobs}", flush=True)
    rows, n = [], 0
    with cf.ThreadPoolExecutor(max_workers=a.jobs) as ex:
        for r in ex.map(lambda u: judge(u[0], u[1], defs), units):
            n += 1
            if r:
                rows.append(r)
            if n % 250 == 0:
                c = collections.Counter(x["verdict"] for x in rows)
                print(f"  {n}/{len(units)} judged; {dict(c)}", flush=True)
    if a.apply:
        # Only a unit THIS RUN judged IDENTICAL is written, and it is written from the same `widen` output the judgement
        # compiled — never re-derived, never taken from an earlier json (R42's cousin: the tree may have moved under it).
        n_w = n_d = 0
        for r in rows:
            if r["verdict"] != "IDENTICAL":
                continue
            path = REPO / r["tu"]
            raw = path.read_text(errors="surrogateescape")
            new, fixed = widen(raw, defs)
            if not fixed or new == raw:
                continue
            path.write_text(new, errors="surrogateescape")
            n_w += 1
            n_d += len(fixed)
        print(f"decl_repair --apply: {n_w} unit(s) rewritten, {n_d} declaration(s) repaired — now run the fleet gate")
    c = collections.Counter(x["verdict"] for x in rows)
    free = sum(x["fixed"] for x in rows if x["verdict"] == "IDENTICAL")
    held = sum(x["fixed"] for x in rows if x["verdict"] == "DIFFERS")
    print(f"decl_repair: {len(rows)} unit(s) carry a lying declaration; verdicts {dict(c)}")
    print(f"  FREE to repair (the object is byte-identical with the declarations widened): "
          f"{c.get('IDENTICAL', 0)} unit(s), {free} declaration(s)")
    print(f"  the object CHANGES (the code depends on the false declaration): "
          f"{c.get('DIFFERS', 0)} unit(s), {held} declaration(s)")
    pathlib.Path(a.json).write_text(json.dumps(rows, indent=1))
    print(f"  rows -> {a.json}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
