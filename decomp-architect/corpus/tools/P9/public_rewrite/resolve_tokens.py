#!/usr/bin/env python3
"""resolve_tokens.py — at the tip of the ADOPTED (rewritten) checkout, turn `commit:NNNN` tokens back into hashes (P33 C7).

    tools/public_rewrite/resolve_tokens.py            # rewrites tracked text files in place; prints the residue
    tools/public_rewrite/resolve_tokens.py --check    # exit 1 if any resolvable token remains at HEAD; lists the residue

Each `commit:NNNN` (an ordinal of the original main, main or twin) becomes the SHORTEST UNIQUE abbreviation (≥ 9 chars)
of the rewritten commit, from docs/commit-map.tsv — uniqueness asserted with `git rev-parse --verify` in THIS repo.
The residue that stays as tokens, listed for the tip commit's message: ordinals whose row is the pruned commit (40
zeros), `commit:orphan-K` (a cited commit that exists in no lineage — e.g. tools/verify_worktree.py cites a dropped
TEMP commit) and `commit:amb-K` (an ambiguous old prefix; measured 0). The fixed-point rule: this runs ONLY at the tip,
after the rewrite — a new hash must never be written into a historical blob.
"""
import argparse
import re
import subprocess
import sys

sys.path.insert(0, str(__import__("pathlib").Path(__file__).resolve().parent))
import common as C  # noqa: E402


def load_map(path=C.COMMIT_MAP_PUBLIC):
    if not path.exists():
        C.die(f"{path} missing — run build_commit_map.py first")
    m = {}
    for ln in path.read_text(encoding="utf-8").splitlines():
        if ln.startswith("#") or ln.startswith("ordinal\t"):
            continue
        o, new, *_ = ln.split("\t")
        m[int(o)] = new
    return m


_abbr_cache = {}


def abbrev(h, repo):
    if h in _abbr_cache:
        return _abbr_cache[h]
    for n in range(9, 41):
        r = subprocess.run(["git", "-C", str(repo), "rev-parse", "--verify", "--quiet", h[:n] + "^{commit}"],
                           capture_output=True, text=True)
        if r.returncode == 0 and r.stdout.strip() == h:
            _abbr_cache[h] = h[:n]
            return h[:n]
    C.die(f"{h} does not resolve in {repo} — is this the adopted (rewritten) checkout?")


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--repo", default=str(C.REPO))
    ap.add_argument("--map", default=str(C.COMMIT_MAP_PUBLIC), help="the commit map (a scratch path for a trial run)")
    a = ap.parse_args(argv)
    repo = __import__("pathlib").Path(a.repo)
    m = load_map(__import__("pathlib").Path(a.map))
    files = C.git(["ls-files", "-z"], repo, text=False).decode("utf-8", "surrogateescape").split("\0")
    n_files, n_resolved, residue, remaining = 0, 0, {}, 0
    skipped = 0
    for rel in files:
        if not rel or rel == "docs/commit-map.tsv":
            continue
        if rel.startswith("tools/public_rewrite/"):      # the token grammar's own definition + self-test fixtures, never citations
            skipped += 1
            continue
        p = repo / rel
        if not p.is_file():
            continue
        data = p.read_bytes()
        if C.is_binary(data) or not C.TOKEN_RE.search(data):
            continue

        def sub(mt):
            nonlocal n_resolved, remaining
            if mt.group("ord"):
                o = int(mt.group("ord"))
                new = m.get(o)
                if new and new != C.ZEROS:
                    if a.check:
                        remaining += 1
                        return mt.group(0)
                    n_resolved += 1
                    return abbrev(new, repo).encode()
                residue[mt.group(0).decode()] = residue.get(mt.group(0).decode(), 0) + 1
                return mt.group(0)
            residue[mt.group(0).decode()] = residue.get(mt.group(0).decode(), 0) + 1
            return mt.group(0)

        out = C.TOKEN_RE.sub(sub, data)
        if out != data and not a.check:
            p.write_bytes(out)
            n_files += 1
    if a.check:
        print(f"resolve_tokens --check: {remaining} resolvable tokens remain at HEAD ({'OK' if not remaining else 'FAIL'}); "
              f"residue (unresolvable, left as tokens): {sum(residue.values())} in {len(residue)} distinct")
        for t, n in sorted(residue.items()):
            print(f"  residue {t} ×{n}")
        return 1 if remaining else 0
    print(f"resolve_tokens: {n_resolved} tokens resolved in {n_files} files ({skipped} files under tools/public_rewrite/ skipped by rule); residue {sum(residue.values())} "
          f"({', '.join(f'{t}×{n}' for t, n in sorted(residue.items())) or 'none'})")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
