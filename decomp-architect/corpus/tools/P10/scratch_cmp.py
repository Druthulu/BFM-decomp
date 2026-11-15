#!/usr/bin/env python3
"""scratch_cmp.py — scratch-compile every object an edit touches, at REV and in the working tree, and cmp (3.44 T12).

Recipe: cookbook/C0589.md (make -n -B commands, exit-checked shards), C0590.md (normpath .d deps).
- Edited files: `git diff --name-only REV -- src include` (working tree vs REV), or --files.
- Object set: build/src/**/*.d whose deps (normpath'd) include an edited file.
- Commands: `make -n -B BINARY=<b> <objs>` per binary; `-MF` -> /dev/null, `-o` -> a temp dir (build/ never written).
- Baseline: `git archive REV src include` + symlinks for every other top-level entry; same commands run there.
- Both sides run in -j serial shards, every compile exit-checked; then cmp base vs new, and base vs build/ (sanity).
Temp: .run/<phase>/scratch_cmp/ (phase from PHASE_PLAN.md line 1), removed unless --keep.
Exit 0 only when 0 differ and 0 fail.
"""
import argparse, collections, filecmp, glob, os, re, shutil, subprocess, sys, threading

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def temp_root():
    try:
        first = open(os.path.join(ROOT, "phase-ends/current/PHASE_PLAN.md")).readline()
    except OSError:
        first = ""
    m = re.match(r"#\s*Phase\s+([A-Za-z0-9._-]+)", first)
    phase = m.group(1) if m and m.group(1) not in (".", "..") else None
    return os.path.join(ROOT, ".run", phase, "scratch_cmp") if phase else os.path.join(ROOT, ".run", "scratch_cmp")


def edited_files(rev, files):
    if files is not None:
        return {os.path.normpath(f) for f in files}
    out = subprocess.run(["git", "diff", "--name-only", rev, "--", "src", "include"], cwd=ROOT,
                         capture_output=True, text=True, check=True).stdout
    return {os.path.normpath(f) for f in out.split()}


def object_set(files):
    out = []
    for d in glob.glob(os.path.join(ROOT, "build/src/**/*.d"), recursive=True):
        t = open(d).read().replace("\\\n", " ").split("\n", 1)[0]
        if ":" in t:
            tgt, deps = t.split(":", 1)
            if files & {os.path.normpath(x) for x in deps.split()}:
                out.append(tgt.strip())
    return sorted(set(out))


def binary_of(obj):
    parts = obj.split("/")
    return "main" if len(parts) == 3 else parts[2]


def compile_cmds(objs):
    """(obj, cmd-with-OUTDIR) per object; objects make did not emit a line for are returned as missing."""
    by = collections.defaultdict(list)
    for o in objs:
        by[binary_of(o)].append(o)
    cmds, missing = [], []
    for b, bobjs in sorted(by.items()):
        out = subprocess.run(["make", "-n", "-B", "BINARY=" + b] + bobjs, cwd=ROOT,
                             capture_output=True, text=True).stdout
        want, got = set(bobjs), set()
        for line in out.splitlines():
            m = re.search(r" -o (build/src/\S+\.o)$", line)
            if line.startswith("set -o pipefail;") and m and m.group(1) in want and m.group(1) not in got:
                o = m.group(1); got.add(o)
                line = re.sub(r"-MF \S+\.d", "-MF /dev/null", line)
                cmds.append((o, line[:line.rindex(" -o ")] + " -o OUTDIR/" + o.replace("/", "__")))
        missing += sorted(want - got)
    return sorted(cmds), missing


def make_base(base, rev):
    os.makedirs(base)
    for e in sorted(os.listdir(ROOT)):
        if e not in ("src", "include"):
            os.symlink(os.path.join(ROOT, e), os.path.join(base, e))
    arc = subprocess.Popen(["git", "archive", rev, "src", "include"], cwd=ROOT, stdout=subprocess.PIPE)
    subprocess.run(["tar", "-x", "-C", base], stdin=arc.stdout, check=True)
    arc.stdout.close()
    if arc.wait() != 0:
        sys.exit("scratch_cmp: git archive %s failed" % rev)


def run_side(cwd, outdir, cmds, jobs):
    """Run every command (serial within a shard, -j shards); return the set of objects whose compile failed."""
    os.makedirs(outdir)
    errdir = outdir + ".err"; os.makedirs(errdir)
    shards = [cmds[i::jobs] for i in range(jobs)]
    fails, lock = set(), threading.Lock()

    def shard(items):
        for o, c in items:
            with open(os.path.join(errdir, o.replace("/", "__") + ".txt"), "w") as err:
                rc = subprocess.run(["bash", "-c", c.replace("OUTDIR", outdir)], cwd=cwd,
                                    stdout=subprocess.DEVNULL, stderr=err).returncode
            if rc != 0 or not os.path.isfile(os.path.join(outdir, o.replace("/", "__"))):
                with lock:
                    fails.add(o)

    ts = [threading.Thread(target=shard, args=(s,)) for s in shards if s]
    for t in ts: t.start()
    for t in ts: t.join()
    return fails


def first_err(tmp, side, o):
    """(T7.c15) ` | <first compiler error line>` of a failed compile (its captured stderr), '' when none."""
    try:
        lines = [l.strip() for l in open(os.path.join(tmp, side + ".err", o.replace("/", "__") + ".txt"), errors="replace")]
    except OSError:
        return ""
    hit = (next((l for l in lines if re.search(r":\d+: ", l) and not re.search(r"warning|note:", l.lower())), None)       # cc1: `f.c:12: structure has no member named ...`
           or next((l for l in lines if "error" in l.lower()), None) or next((l for l in lines if l), ""))
    return (" | " + hit[:200]) if hit else ""


def main():
    ap = argparse.ArgumentParser(description="Scratch-compile the objects an edit touches at REV and in the working "
                                 "tree; cmp them. Exit 0 only when 0 differ and 0 fail. Recipe: cookbook C0589/C0590.")
    ap.add_argument("--rev", default="HEAD", help="baseline revision (default HEAD)")
    ap.add_argument("--files", nargs="+", help="edited files (repo-relative) instead of git diff REV")
    ap.add_argument("-j", "--jobs", type=int, default=16, help="shards per side (default 16)")
    ap.add_argument("--list", action="store_true", help="print the object set only")
    ap.add_argument("--keep", action="store_true", help="keep the temp folder")
    a = ap.parse_args()

    objs = object_set(edited_files(a.rev, a.files))
    if a.list:
        for o in objs: print(o)
        return 0
    if not objs:
        print("objects 0 identical 0 differ 0 fail base 0 new 0 base==build/ 0")
        return 0

    cmds, missing = compile_cmds(objs)
    tmp = temp_root()
    shutil.rmtree(tmp, ignore_errors=True)
    try:
        base = os.path.join(tmp, "base")
        make_base(base, a.rev)
        jobs = max(1, a.jobs)
        fb = run_side(base, os.path.join(tmp, "baseo"), cmds, jobs) | set(missing)
        fn = run_side(ROOT, os.path.join(tmp, "newo"), cmds, jobs) | set(missing)
        same, diff, bsame = 0, [], 0
        for o in objs:
            if o in fb or o in fn:
                continue
            n = o.replace("/", "__")
            bo, no = os.path.join(tmp, "baseo", n), os.path.join(tmp, "newo", n)
            if filecmp.cmp(bo, no, shallow=False): same += 1
            else: diff.append(o)
            if os.path.isfile(os.path.join(ROOT, o)) and filecmp.cmp(bo, os.path.join(ROOT, o), shallow=False):
                bsame += 1
        print("objects %d identical %d differ %d fail base %d new %d base==build/ %d"
              % (len(objs), same, len(diff), len(fb), len(fn), bsame))
        for o in diff: print("DIFF " + o)
        for o in sorted(fb): print("FAIL base " + o + (" (no make line)" if o in missing else first_err(tmp, "baseo", o)))
        for o in sorted(fn): print("FAIL new " + o + (" (no make line)" if o in missing else first_err(tmp, "newo", o)))
        if a.keep: print("kept " + os.path.relpath(tmp, ROOT))
        return 0 if not diff and not fb and not fn else 1
    finally:
        if not a.keep:
            shutil.rmtree(tmp, ignore_errors=True)


if __name__ == "__main__":
    sys.exit(main())
