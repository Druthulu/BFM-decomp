#!/usr/bin/env python3
"""strand_census.py — every draft ALREADY ON DISK whose function is still open.  (P31 S67)

WHY THIS EXISTS.  The S66 free-wins audit measured the single largest free lever in the project:
**147 of 591 open functions already had a byte-correct draft on disk**, each stranded on ONE of four
integration blockers.  Roughly 56 of that session's 416 banks came from ZERO drafting agents — from
work already written.  The question "is there already a draft?" must therefore be answered BEFORE any
wave is drawn, and answering it by hand is how drafts get re-derived: measured, ~109 of 240 agents in
waves w2/w3 re-drafted functions whose answer was already on disk or already banked.

WHAT IT IS.  A deterministic, zero-token join of three things the repo already knows:

    wave manifests  (.run/<wave>/{targets,cards}.json)   -> which fn belongs to which binary/TU
    the filesystem  (.run/<wave>/<arm>/<fn>.c)           -> which drafts exist
    corpus.stubs()                                       -> which of those are STILL OPEN

R32 COVERAGE.  Every manifest must parse, every entry must name a known binary, and the report
prints its denominators: manifests read, targets seen, targets whose fn is banked already, targets
with no draft file.  A census that silently narrows its scope is the dominant defect class in this
project (see the `silently-narrowed-tool-scope` note), so the gap is printed, never assumed empty.

R48 KEYING.  Rows are keyed `binary:fn`, never a bare function name — the same `func_8013F350` name
lives in several overlays with different bodies, and three fn-keyed collision defects came from
exactly this.

USAGE
    tools/strand_census.py                       # report to stdout
    tools/strand_census.py --json .run/strand.json
    tools/strand_census.py --binary ov_SC03_105  # one binary
    tools/strand_census.py --main                # main only (LINKED addrs are NOT excluded here;
                                                 #   draw_waves.py owns that refusal)
Then feed the JSON to blocker_probe / rtu_match / gate_stage.  This tool never compiles anything and
never writes to the source tree.
"""
import argparse
import concurrent.futures as cf
import glob
import json
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
sys.path.insert(0, HERE)

import corpus  # noqa: E402
from o0_detect import detect_o0  # noqa: E402
import progress  # noqa: E402


def _binary_of(row):
    """The binary a manifest row belongs to.

    Older wave manifests predate the `binary` field and carry only an asm path.  The overlay layout
    is `asm/<binary>/nonmatchings/<subseg>`; main's is `asm/nonmatchings/<subseg>` (no binary
    component).  Derive from that rather than guessing, and return None if neither shape applies —
    the caller turns that into a loud refusal (R43), never a silent skip.
    """
    if row.get("binary"):
        return row["binary"]
    for field in ("asmdir", "asm", "sub"):
        p = row.get(field)
        if not p:
            continue
        parts = p.split("/")
        if len(parts) >= 2 and parts[0] == "asm":
            return "main" if parts[1] == "nonmatchings" else parts[1]
    return None


def _manifest_rows(path):
    """Yield (fn, binary, row) from a targets.json / cards.json (both are lists of dicts)."""
    with open(path) as fh:
        doc = json.load(fh)
    if not isinstance(doc, list):
        raise ValueError("%s: expected a JSON list, got %s" % (path, type(doc).__name__))
    for row in doc:
        if not isinstance(row, dict):
            raise ValueError("%s: non-dict row" % path)
        fn = row.get("name") or row.get("fn")
        binary = _binary_of(row)
        if not fn or not binary:
            # A manifest row that cannot be keyed is a coverage hole, not a skip.
            raise ValueError("%s: row missing name/fn or binary: %r" % (path, row))
        yield fn, binary, row


def census(only_binary=None):
    known = set(progress.BINARIES)
    manifests = sorted(glob.glob(os.path.join(REPO, ".run", "*", "targets.json"))
                       + glob.glob(os.path.join(REPO, ".run", "*", "cards.json")))
    # binary -> set of open fn names, computed once (corpus.stubs is coverage-asserting).
    open_by_bin = {}

    def is_open(binary, fn):
        if binary not in open_by_bin:
            open_by_bin[binary] = {s.symbol for s in corpus.stubs(binary).values()}
        return fn in open_by_bin[binary]

    # A (binary, fn) pair appears in MANY manifests — the same target gets redrawn across waves, and
    # its draft may exist in only one of them.  Classify each PAIR once, after merging every
    # manifest's view of it; bucketing per manifest row double-counts and is how a pair lands in
    # both "no draft" and "has draft" at the same time.
    merged = {}          # (binary, fn) -> record
    unknown_bin = set()

    for man in manifests:
        wave_dir = os.path.dirname(man)
        wave = os.path.basename(wave_dir)
        for fn, binary, row in _manifest_rows(man):
            if binary not in known:
                unknown_bin.add((binary, man))
                continue
            if only_binary and binary != only_binary:
                continue
            rec = merged.setdefault((binary, fn), {
                "binary": binary, "fn": fn, "drafts": [], "waves": [],
                "nins": None, "sub": None, "asm": None, "tu": None,
            })
            if wave not in rec["waves"]:
                rec["waves"].append(wave)
            for d in sorted(glob.glob(os.path.join(wave_dir, "*", fn + ".c"))
                            + glob.glob(os.path.join(wave_dir, fn + ".c"))):
                rel = os.path.relpath(d, REPO)
                if rel not in rec["drafts"]:
                    rec["drafts"].append(rel)
            for field in ("nins", "sub", "asm", "tu"):
                if rec.get(field) is None and row.get(field) is not None:
                    rec[field] = row[field]

    rows = {}             # "binary:fn" -> record, open AND drafted
    seen_targets = set(merged)
    banked = set()
    nodraft = set()
    for (binary, fn), rec in merged.items():
        if not is_open(binary, fn):
            banked.add((binary, fn))
        elif not rec["drafts"]:
            nodraft.add((binary, fn))
        else:
            rows["%s:%s" % (binary, fn)] = rec

    # R32: the denominator this census is a fraction OF.  `frontier_*` is the one that matters —
    # a census of the wave manifests is silent about every open function that was never DRAWN, and
    # reporting only "193 have drafts" without "of 530 open" is exactly the R41 defect.
    frontier = 0
    for b in (([only_binary] if only_binary else list(known))):
        frontier += len(corpus.stubs(b))
    coverage = {
        "manifests": len(manifests),
        "targets_seen": len(seen_targets),
        "already_banked": len(banked),
        "open_no_draft": len(nodraft),
        "open_with_draft": len(rows),
        "frontier_open_total": frontier,
        "frontier_never_drawn": frontier - len(nodraft) - len(rows),
        "unknown_binary_rows": sorted({b for b, _ in unknown_bin}),
    }
    acc = coverage["already_banked"] + coverage["open_no_draft"] + coverage["open_with_draft"]
    if acc != coverage["targets_seen"]:
        raise AssertionError("coverage gap: %d classified != %d seen" % (acc, coverage["targets_seen"]))
    return rows, coverage, sorted(nodraft)


# --------------------------------------------------------------------------------------------
# classification — WHY is each stranded draft still stranded?
# --------------------------------------------------------------------------------------------
# rtu_match compiles the whole split TU with the draft spliced in and INCLUDE_ASM neutralised, so
# its verdict carries the real ambient declaration context (the thing match_one is structurally
# blind to).  Its five outcomes route to five DIFFERENT lanes, and mis-routing is expensive:
#
#   MATCH      -> gate it.  Byte-correct in its real TU; whatever stops it is whole-binary plumbing
#                 (or, for a jtbl-bearing draft, the carve — the SERIAL gate only).
#   CC1-FAIL   -> the recovery ladder (scope-demote / block-scope typedef strip / cast-at-use).
#   NEAR(n)    -> n mismatched instructions.  n<=3 is register-pin or wall-ledger territory,
#                 8-20 is the permuter with a long budget, >20 is a redraft (F20, measured).
#   CPP/AS/... -> a broken draft, not a matching problem.
#   ERR        -> the harness could not run.  R40: that is not a verdict about the draft.
_VERDICT_RE = re.compile(r"^(MATCH) \((\d+) ins\)|^(DIFF)\s+\S+\s+mine=(\d+) ins, target=(\d+) ins, (\d+) mismatched")


def _classify_one(job):
    binary, fn, draft, split, source, asm_subdir, work, o0 = job
    cmd = [sys.executable, os.path.join(HERE, "rtu_match.py"), fn,
           "--split", split, "--source", source, "--c", draft,
           "--asm-subdir", asm_subdir, "--work", work]
    # THE ORACLE-DIVERGENCE GUARD (S66 tool defect #4).  A function whose shipped bytes are -O0 but
    # whose TU compiles -O2 gets an all-instructions-mismatch verdict that says nothing about the
    # draft: measured, md_MAIN_003's nine drafts all read NEAR>20 at -O2.  Detect it from the target
    # bytes (match_one.detect_o0 — the frame-pointer prologue tell) and compile it the way the game
    # shipped it.  These CANNOT be banked until the TU is carved (W4), so the verdict is tagged.
    if o0:
        cmd.append("--o0")
    try:
        p = subprocess.run(cmd, cwd=REPO, capture_output=True, timeout=900)
    except subprocess.TimeoutExpired:
        return dict(binary=binary, fn=fn, draft=draft, verdict="ERR", detail="rtu_match timeout 900s", o0=o0)
    out = (p.stdout or b"").decode("utf-8", "replace")
    tag = {"o0": True} if o0 else {}
    err = (p.stderr or b"").decode("utf-8", "replace")
    first = out.splitlines()[0] if out.strip() else ""
    m = _VERDICT_RE.match(first)
    if m and m.group(1):
        return dict(binary=binary, fn=fn, draft=draft, verdict="MATCH", ins=int(m.group(2)), **tag)
    if m and m.group(3):
        return dict(binary=binary, fn=fn, draft=draft, verdict="NEAR",
                    closeness=int(m.group(6)), ins=int(m.group(4)), target_ins=int(m.group(5)), **tag)
    for stage in ("CPP", "CC1", "MASPSX", "AS"):
        if first.startswith(stage + " FAIL"):
            body = [l.strip() for l in out.splitlines()[1:] if l.strip()]
            return dict(binary=binary, fn=fn, draft=draft,
                        verdict=("CC1-FAIL" if stage == "CC1" else stage + "-FAIL"),
                        detail=(body[0] if body else ""), detail_all=body[:8], **tag)
    # No parseable verdict: the instrument, not the subject (R40).
    return dict(binary=binary, fn=fn, draft=draft, verdict="ERR",
                detail=(first or err.strip().splitlines()[-1] if err.strip() else "no output"),
                rc=p.returncode, **tag)


def classify(rows, workers, work_root):
    """Run rtu_match over every (fn, draft) pair.  Threads, not processes: each job is a wait on a
    subprocess chain (cpp/cc1/maspsx/as), so the GIL is never the bottleneck."""
    jobs, skipped = [], []
    for key, rec in rows.items():
        binary, fn = rec["binary"], rec["fn"]
        stub = None
        for s in corpus.stubs(binary).values():
            if s.symbol == fn:
                stub = s
                break
        if stub is None:                       # banked between the census and now
            skipped.append((key, "not open"))
            continue
        split = os.path.basename(stub.path)[:-2] if stub.path.endswith(".c") else os.path.basename(stub.path)
        # rtu_match resolves the split as src/<source>/<split>.c; main's TUs are flat in src/,
        # which is what `--source .` means (tool defect #5 in the S66 audit).
        source = "." if binary == "main" else binary
        o0 = detect_o0(os.path.join(REPO, stub.asm_path))
        for draft in rec["drafts"]:
            jobs.append((binary, fn, draft, split, source, stub.asm_dir,
                         os.path.join(work_root, binary), o0))
    # Longest-first: the big TUs dominate wall clock.
    jobs.sort(key=lambda j: -os.path.getsize(os.path.join(REPO, j[2])))
    results = []
    with cf.ThreadPoolExecutor(max_workers=workers) as ex:
        futs = {ex.submit(_classify_one, j): j for j in jobs}
        done = 0
        for fut in cf.as_completed(futs):
            results.append(fut.result())
            done += 1
            if done % 25 == 0:
                print("  ... %d/%d classified" % (done, len(jobs)), flush=True)
    return results, jobs, skipped


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binary", help="restrict to one binary")
    ap.add_argument("--main", action="store_true", help="shorthand for --binary main")
    ap.add_argument("--json", help="write the full record set here")
    ap.add_argument("--nodraft-json", help="write the open-but-undrafted targets here (wave fuel)")
    ap.add_argument("--classify", action="store_true",
                    help="run rtu_match over every stranded draft and bucket the verdicts")
    ap.add_argument("--workers", type=int, default=12)
    ap.add_argument("--work", default=".run/_strand_work", help="scratch root for rtu_match")
    ap.add_argument("--verdicts-json", default=".run/strand_verdicts.json")
    ap.add_argument("--from-verdicts", help="stage from a previously written verdicts JSON instead of re-classifying")
    ap.add_argument("--emit-drafts", help="stage the winning drafts under <dir>/<binary>/ for gate_stage")
    ap.add_argument("--emit-verdict", default="MATCH", help="which bucket to stage (default MATCH)")
    ap.add_argument("--emit-include-o0", action="store_true",
                    help="stage -O0-in--O2-TU functions too (they cannot bank until the TU is carved)")
    args = ap.parse_args()

    only = "main" if args.main else args.binary
    rows, cov, nodraft = census(only)

    print("=== strand census %s===" % ("(%s) " % only if only else ""))
    for k, v in cov.items():
        print("  %-22s %s" % (k, v))
    per_bin = {}
    for rec in rows.values():
        per_bin.setdefault(rec["binary"], []).append(rec)
    print("\n  open functions WITH a draft already on disk: %d across %d binaries"
          % (len(rows), len(per_bin)))
    for b, recs in sorted(per_bin.items(), key=lambda kv: -len(kv[1]))[:30]:
        print("    %-16s %3d   (%s)" % (b, len(recs),
              ", ".join(sorted(r["fn"] for r in recs)[:4]) + (" ..." if len(recs) > 4 else "")))

    if args.json:
        with open(args.json, "w") as fh:
            json.dump({"coverage": cov, "rows": rows}, fh, indent=1)
        print("\n  wrote %s" % args.json)
    if args.nodraft_json:
        with open(args.nodraft_json, "w") as fh:
            json.dump([{"binary": b, "fn": f} for b, f in nodraft], fh, indent=1)
        print("  wrote %s" % args.nodraft_json)

    if args.from_verdicts:
        with open(args.from_verdicts) as fh:
            best = json.load(fh)["best"]
        # R42/wave_args lesson: a verdict file goes STALE the moment anything banks.  Re-check
        # openness against corpus.stubs here rather than staging a draft for a banked function.
        live = {k: v for k, v in best.items()
                if any(s.symbol == v["fn"] for s in corpus.stubs(v["binary"]).values())}
        if len(live) != len(best):
            print("  %d of %d verdict rows are already banked — dropped" % (len(best) - len(live), len(best)))
        if args.emit_drafts:
            n = emit_drafts(live, args.emit_drafts, args.emit_verdict, args.emit_include_o0)
            print("  staged %d %s drafts under %s/<binary>/" % (n, args.emit_verdict, args.emit_drafts))
        return 0

    if args.classify:
        print("\n=== classifying %d stranded functions with rtu_match (%d workers) ==="
              % (len(rows), args.workers))
        results, jobs, skipped = classify(rows, args.workers, args.work)
        if len(results) != len(jobs):                    # R32
            raise AssertionError("classified %d of %d jobs" % (len(results), len(jobs)))
        # Best verdict per function: MATCH beats NEAR beats a compile failure.
        rank = {"MATCH": 0, "NEAR": 1, "CC1-FAIL": 2, "CPP-FAIL": 3, "MASPSX-FAIL": 3,
                "AS-FAIL": 3, "ERR": 4}
        best = {}
        for r in results:
            k = "%s:%s" % (r["binary"], r["fn"])
            cur = best.get(k)
            if cur is None or (rank[r["verdict"]], r.get("closeness", 0)) < (rank[cur["verdict"]], cur.get("closeness", 0)):
                best[k] = r
        buckets = {}
        for r in best.values():
            buckets.setdefault(r["verdict"], []).append(r)
        print("\n  per-function best verdict (of %d functions, %d draft files):"
              % (len(best), len(jobs)))
        for v in sorted(buckets, key=lambda v: rank[v]):
            extra = ""
            if v == "NEAR":
                cl = sorted(r["closeness"] for r in buckets[v])
                extra = "   closeness: <=3 %d · 4-7 %d · 8-20 %d · >20 %d" % (
                    sum(1 for c in cl if c <= 3), sum(1 for c in cl if 4 <= c <= 7),
                    sum(1 for c in cl if 8 <= c <= 20), sum(1 for c in cl if c > 20))
            print("    %-12s %3d%s" % (v, len(buckets[v]), extra))
        if skipped:
            print("    (%d skipped — banked since the census)" % len(skipped))
        with open(args.verdicts_json, "w") as fh:
            json.dump({"per_draft": results, "best": best}, fh, indent=1)
        print("  wrote %s" % args.verdicts_json)

        if args.emit_drafts:
            n = emit_drafts(best, args.emit_drafts, args.emit_verdict, args.emit_include_o0)
            print("  staged %d drafts under %s/<binary>/" % (n, args.emit_drafts))
    return 0


def emit_drafts(best, root, want_verdict, include_o0):
    """Stage the winning draft of each function into <root>/<binary>/<fn>.c — the input shape
    gate_stage.py takes.  -O0-in-an--O2-TU functions are EXCLUDED by default and named on stderr:
    their MATCH is real but the build cannot realise it until the TU is carved, so gating them
    manufactures a 'the gate refused a correct draft' verdict (S66 tool defect #4, R43)."""
    import shutil as _sh
    staged, held = 0, []
    for rec in best.values():
        if rec["verdict"] != want_verdict:
            continue
        if rec.get("o0") and not include_o0:
            held.append("%s:%s" % (rec["binary"], rec["fn"]))
            continue
        d = os.path.join(root, rec["binary"])
        os.makedirs(d, exist_ok=True)
        _sh.copy(os.path.join(REPO, rec["draft"]), os.path.join(d, rec["fn"] + ".c"))
        staged += 1
    if held:
        print("  HELD (-O0 in an -O2 TU — needs the carve, not the gate): %d\n    %s"
              % (len(held), "\n    ".join(sorted(held))), file=sys.stderr)
    return staged


if __name__ == "__main__":
    sys.exit(main())
