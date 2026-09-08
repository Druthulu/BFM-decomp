#!/usr/bin/env python3
"""verify_rewrite.py — the pairwise proof that the rewrite changed ONLY what it was told to (P33 C5).

    tools/public_rewrite/verify_rewrite.py [--old ~/bfm-decomp] [--new .run/public_rewrite/repo.git]

For every (old, new) pair in the clone's filter-repo commit-map (old commits read from the ORIGINAL repo — the clone
has gc'd them away; new commits from the clone):
  * author and committer: name/e-mail equal after the mailmap; BOTH timestamps and zones equal;
  * message: new == scrub_message(old) — byte-equal (hash tokens, addresses, the trailer lines);
  * parents: new parents == map(old parents) with every pruned commit spliced out (its own parent substituted);
  * trees (`git ls-tree -r`): every path REMOVED sits under a purge rule or its blob id is in rom_blob_ids.txt; every
    path CHANGED has the same mode and its new blob id == git-hash(scrub_text(old blob)); any path ADDED fails; gitlinks
    (submodules) must be identical.
Then: the new main's commit count == old − pruned; the author/committer timestamp sequences match with the pruned
commits removed; the pre-existing EMPTY commit on main (tree == parent's tree) survived. Every failure is named; exit 1
on any. Cost: ≈4,000 pairs × (2 cat-file + 2 ls-tree) ≈ 3–5 min.
"""
import argparse
import subprocess
import sys

sys.path.insert(0, str(__import__("pathlib").Path(__file__).resolve().parent))
import common as C  # noqa: E402
import scrub  # noqa: E402


def commit_map(new):
    for cand in (new / "filter-repo" / "commit-map", new / ".git" / "filter-repo" / "commit-map"):
        if cand.exists():
            rows = [ln.split() for ln in cand.read_text().splitlines() if ln and not ln.startswith("old")]
            return {o: n for o, n in rows}
    C.die(f"no filter-repo/commit-map under {new}")


def ls_tree(repo, rev):
    out = C.git(["ls-tree", "-r", "-z", rev], repo, text=False, check=True)
    d = {}
    for ent in out.split(b"\0"):
        if not ent:
            continue
        meta, _, path = ent.partition(b"\t")
        mode, typ, oid = meta.decode().split()
        d[path.decode("utf-8", "surrogateescape")] = (mode, typ, oid)
    return d


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--old", default=str(C.REPO))
    ap.add_argument("--new", default=str(C.CLONE_DIR))
    a = ap.parse_args(argv)
    old_repo, new_repo = __import__("pathlib").Path(a.old), __import__("pathlib").Path(a.new)
    cmap = commit_map(new_repo)
    pruned = {o for o, n in cmap.items() if n == C.ZEROS}
    prefixes, globs = C.purge_rules()
    rom_ids = set(C.ROM_IDS_FILE.read_text().split()) if C.ROM_IDS_FILE.exists() else set()
    personal = set(C.personal_emails_from_mailmap())
    s = scrub.Scrubber()
    cf_old, cf_new = C.CatFile(old_repo), C.CatFile(new_repo)
    fails, n_pairs, n_changed_blobs, n_removed = [], 0, 0, 0
    old_commits = {}

    def old_commit(h):
        if h not in old_commits:
            _, _, raw = cf_old.get(h)
            old_commits[h] = C.parse_commit(raw)
        return old_commits[h]

    def splice(p):
        while p in pruned:
            par = old_commit(p)["parents"]
            if len(par) != 1:
                return None
            p = par[0]
        return cmap.get(p)

    def ident_ok(old_id, new_id):
        name, email, ts, tz = old_id
        exp = (C.NOREPLY_NAME, C.NOREPLY_EMAIL, ts, tz) if email in personal else old_id
        return exp == new_id, exp

    for old, new in cmap.items():
        if new == C.ZEROS:
            continue
        n_pairs += 1
        o = old_commit(old)
        _, typ, raw = cf_new.get(new)
        if raw is None:
            fails.append(f"{old[:9]} -> {new[:9]}: new commit missing"); continue
        n = C.parse_commit(raw)
        for who in ("author", "committer"):
            ok, exp = ident_ok(o[who], n[who])
            if not ok:
                fails.append(f"{old[:9]}: {who} {n[who]} != expected {exp}")
        want_msg = s.scrub_message(o["message"])
        if want_msg != n["message"]:
            fails.append(f"{old[:9]}: message differs from scrub(old): {n['message'][:80]!r} vs {want_msg[:80]!r}")
        want_par = [splice(p) for p in o["parents"]]
        if want_par != n["parents"]:
            fails.append(f"{old[:9]}: parents {n['parents']} != expected {want_par}")
        if o["tree"] != n["tree"]:
            to, tn = ls_tree(old_repo, o["tree"]), ls_tree(new_repo, n["tree"])
            for path in tn:
                if C.under_purge(path, prefixes, globs):
                    fails.append(f"{old[:9]}: purge path SURVIVES in the new tree: {path}")
            for path in set(to) - set(tn):
                n_removed += 1
                mode, typ, oid = to[path]
                if not C.under_purge(path, prefixes, globs) and oid not in rom_ids:
                    fails.append(f"{old[:9]}: path REMOVED outside the purge set: {path} ({oid[:12]})")
            for path in set(tn) - set(to):
                fails.append(f"{old[:9]}: path ADDED by the rewrite: {path}")
            for path in set(to) & set(tn):
                (mo, tyo, ido), (mn, tyn, idn) = to[path], tn[path]
                if ido == idn and mo == mn:
                    continue
                if mo != mn or tyo != tyn or tyo != "blob":
                    fails.append(f"{old[:9]}: {path}: mode/type changed {mo}/{tyo} -> {mn}/{tyn}"); continue
                n_changed_blobs += 1
                _, _, data = cf_old.get(ido)
                want = C.git_blob_id(s.scrub_text(data))
                if want != idn:
                    fails.append(f"{old[:9]}: {path}: new blob {idn[:12]} != git-hash(scrub(old {ido[:12]})) {want[:12]}")
        if len(fails) > 200:
            fails.append("… stopping after 200 failures"); break
    cf_old.close(); cf_new.close()
    # whole-line checks
    old_main = C.git(["rev-list", "--reverse", "main"], old_repo).split()
    new_main = C.git(["rev-list", "--reverse", "main"], new_repo).split()
    pruned_on_main = [h for h in old_main if h in pruned]
    if len(new_main) != len(old_main) - len(pruned_on_main):
        fails.append(f"main count: new {len(new_main)} != old {len(old_main)} - pruned {len(pruned_on_main)}")
    old_ts = [ln for h, ln in zip(old_main, C.git(["log", "--reverse", "--format=%at %ct", "main"], old_repo).splitlines()) if h not in pruned]
    new_ts = C.git(["log", "--reverse", "--format=%at %ct", "main"], new_repo).splitlines()
    if old_ts != new_ts:
        fails.append("author/committer timestamp sequences differ (after removing the pruned commits)")
    # the pruned set must be exactly the commits whose every change was a purge path (derived, not "1")
    expected_pruned = set()
    for h in pruned | set(old_main):
        raw = C.git(["show", "--raw", "--no-renames", "--format=", h], old_repo).splitlines()
        changed = [ln.partition("\t")[2] for ln in raw if ln.startswith(":")]
        if changed and all(C.under_purge(pth, prefixes, globs) for pth in changed):
            expected_pruned.add(h)
    if pruned != expected_pruned:
        fails.append(f"pruned set {sorted(x[:9] for x in pruned)} != commits whose every change is a purge path "
                     f"{sorted(x[:9] for x in expected_pruned)}")
    empties = [h for h in old_main if len(old_commit(h)["parents"]) == 1 and old_commit(old_commit(h)["parents"][0])["tree"] == old_commit(h)["tree"]]
    for h in empties:
        if cmap.get(h, C.ZEROS) == C.ZEROS:
            fails.append(f"pre-existing empty commit {h[:9]} was pruned (use --prune-empty auto, never always)")
    print(f"verify_rewrite: {n_pairs} pairs checked ({len(pruned)} pruned = the {len(expected_pruned)} purge-only commits, {len(pruned_on_main)} on main); {n_changed_blobs} changed "
          f"blobs re-derived, {n_removed} path removals justified; empty commits on old main: {len(empties)}; "
          f"new main {len(new_main)} commits; failures {len(fails)}")
    for f in fails[:60]:
        print("  FAIL " + f)
    print("verify_rewrite: " + ("PASS" if not fails else "FAIL"))
    return 1 if fails else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
