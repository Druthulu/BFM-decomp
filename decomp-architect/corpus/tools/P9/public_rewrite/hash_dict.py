#!/usr/bin/env python3
"""hash_dict.py — the dictionary of EVERY old commit hash → its inert token (P33 C1/C2).

    tools/public_rewrite/hash_dict.py [--repo PATH] [--write-mailmap]

Writes .run/public_rewrite/dict.json (private: it holds every old hash):
  * every commit OBJECT in the store — reachable or not (`git cat-file --batch-all-objects`), because a doc may cite a
    commit that was later rewritten away (S86: 119 unreachable commit objects; one cited by tools/verify_worktree.py);
  * main's commits → ordinal 1..N in `git rev-list --reverse main` order (token `commit:NNNN`, zero-padded to 4);
  * every other commit → the ordinal of its TWIN on main — same (tree, author timestamp, subject); the S76 tag lineage
    is 126 such re-authored twins — else `orphan-K`;
  * the prefix index (every prefix 7..40 of every hash) is rebuilt on load; ambiguous prefixes (two commits sharing
    one) are recorded and MUST be 0 (measured 0 at 7 chars over 4,420 objects); prefixes that are also prefixes of a
    cited CONTENT hash (the manifest / check.*.sha / dumps sha1s, the sha256 checksums, the redump CRC32) are recorded
    as `excluded` — the scrub leaves such tokens untouched (expected < 1; R41 prints the count).
`--write-mailmap` also writes .run/public_rewrite/mailmap from the history's identities (never a literal anywhere).
"""
import argparse
import collections
import datetime as dt
import json
import sys

sys.path.insert(0, str(__import__("pathlib").Path(__file__).resolve().parent))
import common as C  # noqa: E402


def build(repo):
    objs = [oid for oid, typ, _ in C.iter_all_objects(repo, types=("commit",))]
    main = C.git(["rev-list", "--reverse", "main"], repo).split()
    ordinal = {h: i + 1 for i, h in enumerate(main)}
    cf = C.CatFile(repo)
    meta = {}
    for oid in objs:
        _, typ, raw = cf.get(oid)
        d = C.parse_commit(raw)
        subject = d["message"].split(b"\n", 1)[0]
        meta[oid] = (d["tree"], d["author"][2], subject)
    cf.close()
    twin_key = {}
    for h in main:                              # first main commit with a key wins
        twin_key.setdefault(meta[h], ordinal[h])
    commits, n_twin, n_orphan = {}, 0, 0
    orphans = sorted(h for h in objs if h not in ordinal and meta[h] not in twin_key)
    orphan_no = {h: i + 1 for i, h in enumerate(orphans)}
    for h in objs:
        if h in ordinal:
            commits[h] = {"kind": "main", "ord": ordinal[h]}
        elif meta[h] in twin_key:
            commits[h] = {"kind": "twin", "ord": twin_key[meta[h]]}
            n_twin += 1
        else:
            commits[h] = {"kind": "orphan", "orphan": orphan_no[h]}
            n_orphan += 1
    # prefix index → ambiguity
    index = {}
    ambiguous = set()
    for h in objs:
        for p in C.prefixes_of(h):
            if p in index and index[p] != h:
                ambiguous.add(p)
            index.setdefault(p, h)
    # collisions with cited content hashes
    content = C.cited_content_hashes()
    excluded = sorted(p for h in content for p in C.prefixes_of(h) if p in index)
    return {
        "built_from": {"repo": str(repo), "head": C.git(["rev-parse", "HEAD"], repo).strip(),
                       "date": dt.datetime.now(dt.timezone.utc).isoformat(timespec="seconds")},
        "main_count": len(main),
        "commits": commits,
        "ambiguous": sorted(ambiguous),
        "excluded": excluded,
        "stats": {"objects": len(objs), "main": len(main), "twins": n_twin, "orphans": n_orphan,
                  "prefixes": len(index), "ambiguous": len(ambiguous), "excluded": len(excluded),
                  "content_hashes": len(content)},
    }


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--repo", default=str(C.REPO))
    ap.add_argument("--write-mailmap", action="store_true")
    a = ap.parse_args(argv)
    C.SCRATCH.mkdir(parents=True, exist_ok=True)
    d = build(a.repo)
    C.DICT_FILE.write_text(json.dumps(d, indent=0), encoding="utf-8")
    s = d["stats"]
    print(f"hash_dict: {s['objects']} commit objects ({s['main']} on main, {s['twins']} twins, {s['orphans']} orphans), "
          f"{s['prefixes']} prefixes 7..40, {s['ambiguous']} ambiguous, {s['excluded']} collide with {s['content_hashes']} "
          f"cited content hashes -> {C.DICT_FILE}")
    if d["excluded"]:
        print("  excluded (left untouched by the scrub): " + ", ".join(d["excluded"][:20]))
    if a.write_mailmap:
        ids = C.write_mailmap(repo=a.repo)
        print(f"hash_dict: mailmap written ({len(ids)} personal identities -> the noreply identity) -> {C.MAILMAP_FILE}")
    if d["ambiguous"]:
        print(f"hash_dict: {len(d['ambiguous'])} AMBIGUOUS prefixes (scrub would emit commit:amb-N) — FAIL, investigate",
              file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
