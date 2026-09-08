#!/usr/bin/env python3
"""run_filter.py — compose and run the git-filter-repo rewrite inside the bare clone (P33 C4c).

    tools/public_rewrite/run_filter.py --sample            # = scrub.py --sample (R37: measure before the real run)
    tools/public_rewrite/run_filter.py [--clone PATH]      # the rewrite; refuses outside a bare clone under .run/public_rewrite/

The filter, via the git_filter_repo module API (2.47.0), equals:
    git filter-repo --force --invert-paths --paths-from-file <purge rules, comments stripped>
        --strip-blobs-with-ids .run/public_rewrite/rom_blob_ids.txt --mailmap .run/public_rewrite/mailmap
        --prune-empty auto --replace-refs delete-no-add
plus a blob callback (scrub every text blob: old hashes -> tokens, personal addresses -> noreply) and a message
callback (the same + the `Claude-Session:` trailer lines dropped). Why each flag: `--prune-empty auto`, never `always`
(main carries one pre-existing empty commit that must survive); `--replace-refs delete-no-add` (no refs/replace/<old>
may be minted — they would leak old hashes); `--strip-blobs-with-ids` (the EXE dies wherever it was renamed);
`--force` (the clone is no longer a "fresh clone" once the S76 tag is deleted in it — the only deviation).
Preconditions asserted: the clone is bare, lives under .run/public_rewrite/, has exactly refs/heads/main, one pack, no
loose objects; dict.json, mailmap and rom_blob_ids.txt exist. Logs versions + wall time to .run/public_rewrite/filter.log;
afterwards counts the commit-map rows (and how many map to zeros), asserts no refs/replace, reports packs and size.
"""
import argparse
import os
import subprocess
import sys
import time

sys.path.insert(0, str(__import__("pathlib").Path(__file__).resolve().parent))
import common as C  # noqa: E402


def precheck(clone):
    clone = clone.resolve()
    if C.SCRATCH.resolve() not in clone.parents:
        C.die(f"{clone} is not under {C.SCRATCH} — refusing (the rewrite runs only on the scratch bare clone)")
    if C.git(["rev-parse", "--is-bare-repository"], clone).strip() != "true":
        C.die(f"{clone} is not a bare repository")
    refs = C.git(["for-each-ref", "--format=%(refname)"], clone).split()
    if refs != ["refs/heads/main"]:
        C.die(f"the clone must hold exactly refs/heads/main before the rewrite; it holds {refs} (delete the tag/others first)")
    co = dict(ln.split(": ") for ln in C.git(["count-objects", "-v"], clone).splitlines())
    if co.get("packs") != "1" or co.get("count") != "0":
        C.die(f"the clone must be one pack with zero loose objects; count-objects: {co}")
    for f in (C.DICT_FILE, C.MAILMAP_FILE, C.ROM_IDS_FILE):
        if not f.exists():
            C.die(f"{f} missing")
    # the dictionary must describe THIS history: a stale one (built before the last commit) would leave commits without
    # an ordinal and drop rows from the public map (R43; trial #2 matched only because it was built from the same HEAD)
    d = C.load_dict()
    n_clone = int(C.git(["rev-list", "--count", "main"], clone))
    if d["main_count"] != n_clone or d["built_from"]["head"] != C.git(["rev-parse", "main"], clone).strip():
        C.die(f"dict.json is STALE (main {d['main_count']} @ {d['built_from']['head'][:9]} vs the clone's {n_clone} @ "
              f"{C.git(['rev-parse', 'main'], clone).strip()[:9]}) — rebuild it: hash_dict.py --write-mailmap, then gate_scan")
    return clone


def clean_rules_file():
    out = C.SCRATCH / "purge_rules.filter-repo.txt"
    lines = [ln.strip() for ln in C.PURGE_FILE.read_text(encoding="utf-8").splitlines()]
    lines = [ln for ln in lines if ln and not ln.startswith("#")]
    out.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return out


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--sample", action="store_true")
    ap.add_argument("--clone", default=str(C.CLONE_DIR))
    a = ap.parse_args(argv)
    if a.sample:
        import scrub
        return scrub.main(["--sample"])
    clone = precheck(__import__("pathlib").Path(a.clone))
    import git_filter_repo as fr
    import scrub
    s = scrub.Scrubber()
    rules = clean_rules_file()
    argv_fr = ["--force", "--invert-paths", "--paths-from-file", str(rules),
               "--strip-blobs-with-ids", str(C.ROM_IDS_FILE), "--mailmap", str(C.MAILMAP_FILE),
               "--prune-empty", "auto", "--replace-refs", "delete-no-add"]
    log = C.SCRATCH / "filter.log"
    with open(log, "a", encoding="utf-8") as lf:
        lf.write(f"\n=== run_filter {time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())} clone={clone}\n")
        lf.write(f"git: {C.git(['--version']).strip()}  git-filter-repo: {getattr(fr, '__version__', '?')} ({fr.__file__})\n")
        lf.write(f"args: {' '.join(argv_fr)}\n")
        lf.write(f"rules: {rules.read_text()}")
    old_head = C.git(["rev-parse", "main"], clone).strip()
    n_before = int(C.git(["rev-list", "--count", "main"], clone))
    os.chdir(clone)
    t0 = time.time()

    def blob_cb(blob, metadata):
        blob.data = s.scrub_text(blob.data)

    def message_cb(message):
        return s.scrub_message(message)

    args = fr.FilteringOptions.parse_args(argv_fr)
    f = fr.RepoFilter(args, blob_callback=blob_cb, message_callback=message_cb)
    f.run()
    wall = time.time() - t0
    # post-run facts
    cmap = clone / "filter-repo" / "commit-map"
    rows = [ln.split() for ln in cmap.read_text().splitlines() if ln and not ln.startswith("old")]
    zeros = sum(1 for r in rows if r[1] == C.ZEROS)
    refs = C.git(["for-each-ref", "--format=%(refname)"], clone).split()
    co = dict(ln.split(": ") for ln in C.git(["count-objects", "-v"], clone).splitlines())
    n_after = int(C.git(["rev-list", "--count", "main"], clone))
    st = dict(s.stats)
    summary = (f"run_filter: DONE in {wall:.0f} s; commit-map rows {len(rows)} ({zeros} -> zeros = pruned); main {n_before} -> "
               f"{n_after} commits (old tip {old_head[:9]} -> {C.git(['rev-parse', 'main'], clone).strip()[:9]}); refs {refs}; "
               f"count-objects {co.get('packs')} packs, {co.get('count')} loose, size-pack {int(co.get('size-pack', 0)) // 1024} MB; "
               f"scrub stats {st}")
    print(summary)
    with open(log, "a", encoding="utf-8") as lf:
        lf.write(summary + "\n")
    bad = [r for r in refs if r.startswith("refs/replace/")]
    if bad:
        C.die(f"refs/replace minted: {bad}")
    if zeros != 1:
        print(f"run_filter: WARNING — expected exactly 1 pruned commit (the purge-only 'session archive update'), got {zeros}",
              file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
