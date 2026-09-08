#!/usr/bin/env python3
"""absent_scan.py — nothing that had to go is still anywhere: every object + every message + every ref (P33 C5/C9).

    tools/public_rewrite/absent_scan.py [--repo PATH]      # every object in the store (blobs, commits), every ref
    tools/public_rewrite/absent_scan.py --tree HEAD        # only the blobs of one tree (the tip, after C7)

Offenders (exit 1 on any): a hex token 7..40 that is a prefix of an OLD commit hash (the dictionary; the excluded
content-hash prefixes are not offenders), a personal e-mail address (from the scratch mailmap), a `claude.ai/code/session`
URL, a `Claude-Session:` trailer line in a commit message, an author/committer e-mail that is not the noreply one, a
`refs/replace/*` or `refs/original/*` ref or any tag. INFO only: the count of bare UUIDs (session ids in checkpoint
prose — not in the plan's scope, reported so the owner can decide). On the CURRENT repo this scan must FAIL (its
positive control); on the rewritten clone and the adopted checkout it must pass with 0 / 0 / 0.
"""
import argparse
import re
import sys

sys.path.insert(0, str(__import__("pathlib").Path(__file__).resolve().parent))
import common as C  # noqa: E402

UUID_RE = re.compile(rb"\b[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}\b")


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--repo", default=str(C.CLONE_DIR))
    ap.add_argument("--tree")
    a = ap.parse_args(argv)
    repo = __import__("pathlib").Path(a.repo)
    d = C.load_dict()
    index = set()
    for h in d["commits"]:
        index.update(C.prefixes_of(h))
    excluded = set(d["excluded"])
    unch = C.SCRATCH / "unchanged_commits.txt"          # written by build_commit_map: commits the rewrite left identical
    if unch.exists():
        for h in unch.read_text().split():
            excluded.update(C.prefixes_of(h))
    emails = [e.encode() for e in C.personal_emails_from_mailmap()]
    off = {"old_hash": 0, "email": 0, "session_url": 0, "trailer": 0, "identity": 0, "ref": 0}
    examples, uuids, n_blobs, n_text, n_commits, nbytes = [], 0, 0, 0, 0, 0
    cf = C.CatFile(repo)

    def scan_text(data, where):
        nonlocal uuids
        for m in C.HEX_RE.finditer(data):
            t = m.group(0).decode()
            if t in index and t not in excluded:
                off["old_hash"] += 1
                if len(examples) < 30:
                    a0, b0 = max(0, m.start() - 30), min(len(data), m.end() + 30)
                    examples.append(f"{where}: old hash {t}: …{data[a0:b0].decode('utf-8', 'replace')!r}…")
        for e in emails:
            if e in data:
                off["email"] += data.count(e)
                if len(examples) < 30:
                    examples.append(f"{where}: personal address")
        if C.SESSION_URL_RE.search(data):
            off["session_url"] += len(C.SESSION_URL_RE.findall(data))
            if len(examples) < 30:
                examples.append(f"{where}: claude.ai session URL")
        uuids += len(UUID_RE.findall(data))

    if a.tree:
        ids = [(ln.split()[2], ln.split("\t")[1]) for ln in C.git(["ls-tree", "-r", a.tree], repo).splitlines() if " blob " in ln]
        for oid, path in ids:
            _, _, data = cf.get(oid)
            n_blobs += 1
            if data is None or C.is_binary(data):
                continue
            n_text += 1; nbytes += len(data)
            scan_text(data, path)
    else:
        for oid, typ, size in C.iter_all_objects(repo, types=("blob", "commit")):
            _, _, data = cf.get(oid)
            if data is None:
                continue
            if typ == "blob":
                n_blobs += 1
                if C.is_binary(data):
                    continue
                n_text += 1; nbytes += len(data)
                scan_text(data, f"blob {oid[:12]}")
            else:
                n_commits += 1
                c = C.parse_commit(data)
                if C.TRAILER_RE.search(c["message"]):
                    off["trailer"] += 1
                    examples.append(f"commit {oid[:12]}: Claude-Session trailer")
                scan_text(c["message"], f"commit {oid[:12]} message")
                for who in ("author", "committer"):
                    if c[who][1] != C.NOREPLY_EMAIL:
                        off["identity"] += 1
                        if len(examples) < 30:
                            examples.append(f"commit {oid[:12]}: {who} e-mail is not the noreply identity")
        refs = C.git(["for-each-ref", "--format=%(refname)"], repo).split()
        for r in refs:
            if r.startswith(("refs/replace/", "refs/original/", "refs/tags/")):
                off["ref"] += 1
                examples.append(f"ref {r}")
    cf.close()
    total = sum(off.values())
    print(f"absent_scan {repo}{' tree ' + a.tree if a.tree else ''}: {n_blobs} blobs ({n_text} text, {nbytes / 1e6:.0f} MB), "
          f"{n_commits} commits scanned; offenders: {off}; INFO bare UUIDs: {uuids}")
    for e in examples[:30]:
        print("  " + e[:200])
    print("absent_scan: " + ("PASS — 0 offenders" if not total else f"FAIL — {total} offenders"))
    return 1 if total else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
