#!/usr/bin/env python3
"""scrub.py — THE one scrub function of the public-flip rewrite (P33 C1), and its sample / self-test.

    tools/public_rewrite/scrub.py --test                 # known-true cases (R39)
    tools/public_rewrite/scrub.py --sample [--rev HEAD]  # every tracked blob of a tree: hits, files, per-length counts,
                                                         #   the 7-char replacements in context, an INDEPENDENT oracle
    tools/public_rewrite/scrub.py --file IN --out OUT    # scrub one file (debugging)

What it does to a text blob or a commit message:
  * every hex token 7..40 chars long that is a prefix of exactly one OLD commit hash (the dictionary) becomes the
    inert token `commit:NNNN` (main ordinal), `commit:orphan-K`, or `commit:amb-K` for an ambiguous prefix; tokens
    that are also prefixes of a cited CONTENT hash are left alone (the exclusion set); anything else is untouched;
  * every personal e-mail address (from the scratch mailmap) becomes the noreply address;
  * for MESSAGES only: `Claude-Session: …` trailer lines are dropped (60 on main, 130 over all refs at S87).
Binary blobs (a NUL in the first 8 KiB) are never touched. The function is idempotent: scrub(scrub(x)) == scrub(x).
"""
import argparse
import collections
import re
import sys
import time

sys.path.insert(0, str(__import__("pathlib").Path(__file__).resolve().parent))
import common as C  # noqa: E402


class Scrubber:
    def __init__(self, dictionary=None, personal_emails=None):
        d = dictionary if dictionary is not None else C.load_dict()
        self.commits = d["commits"]
        self.index = {}
        for h in self.commits:
            for p in C.prefixes_of(h):
                self.index.setdefault(p, h)
        self.ambiguous = {p: i + 1 for i, p in enumerate(d["ambiguous"])}
        self.excluded = set(d["excluded"])
        self.emails = [e.encode() for e in (personal_emails if personal_emails is not None
                                            else C.personal_emails_from_mailmap())]
        self.noreply = C.NOREPLY_EMAIL.encode()
        self.stats = collections.Counter()
        self.replaced = collections.Counter()    # token -> count (for the sample)

    def token_for(self, tok):
        """The replacement for one hex token (bytes) or None."""
        t = tok.decode()
        if t in self.excluded:
            self.stats["excluded"] += 1
            return None
        if t in self.ambiguous:
            self.stats["ambiguous"] += 1
            return b"commit:amb-%d" % self.ambiguous[t]
        h = self.index.get(t)
        if h is None:
            self.stats["unresolved"] += 1
            return None
        e = self.commits[h]
        if e["kind"] in ("main", "twin"):
            return b"commit:%04d" % e["ord"]
        return b"commit:orphan-%d" % e["orphan"]

    def _sub(self, m):
        r = self.token_for(m.group(0))
        if r is None:
            return m.group(0)
        self.stats["replaced"] += 1
        self.stats[f"replaced_len{len(m.group(0))}"] += 1
        self.replaced[m.group(0)] += 1
        return r

    def scrub_text(self, data):
        if C.is_binary(data):
            self.stats["binary"] += 1
            return data
        out = C.HEX_RE.sub(self._sub, data)
        for e in self.emails:
            if e in out:
                self.stats["emails"] += out.count(e)
                out = out.replace(e, self.noreply)
        return out

    def scrub_message(self, msg):
        out, n = C.TRAILER_RE.subn(b"", msg)
        self.stats["trailers"] += n
        out = self.scrub_text(out)
        if n:
            out = out.rstrip(b"\n") + b"\n"
        return out


# ---------------------------------------------------------------- self-test (known-true cases)
def selftest():
    fake_main = "0123456789abcdef0123456789abcdef01234567"
    fake_twin = "fedcba9876543210fedcba9876543210fedcba98"
    fake_orphan = "1111111111111111111111111111111111111111"
    content = "abcdef0123456789abcdef0123456789abcdef01"     # a "manifest" sha1: prefix abcdef0 collides with nothing
    d = {"commits": {fake_main: {"kind": "main", "ord": 12}, fake_twin: {"kind": "twin", "ord": 3},
                     fake_orphan: {"kind": "orphan", "orphan": 2}},
         "ambiguous": [], "excluded": sorted(C.prefixes_of(content))}
    s = Scrubber(d, personal_emails=["someone@example.com"])
    cases = [
        (b"see 0123456789a for the fix", b"see commit:0012 for the fix", "9-char main prefix"),
        (b"(" + fake_main.encode() + b")", b"(commit:0012)", "full 40-char main hash"),
        (b"twin fedcba98 here", b"twin commit:0003 here", "8-char twin prefix -> the twin's ordinal"),
        (b"lost 1111111 commit", b"lost commit:orphan-2 commit", "orphan"),
        (b"func_800D128C and 0x800d128c stay", b"func_800D128C and 0x800d128c stay", "word-embedded hex untouched"),
        (b"abcdef0123 is a manifest sha1 prefix", b"abcdef0123 is a manifest sha1 prefix", "excluded content-hash prefix"),
        (b"deadbeefcafe is not a commit", b"deadbeefcafe is not a commit", "unknown hex untouched"),
        (b"012345 too short", b"012345 too short", "6 chars never match"),
        (b"mail someone@example.com now", b"mail " + C.NOREPLY_EMAIL.encode() + b" now", "personal address -> noreply"),
        (b"\0binary 0123456789a", b"\0binary 0123456789a", "binary untouched"),
    ]
    bad = 0
    for src, want, name in cases:
        got = s.scrub_text(src)
        ok = got == want
        bad += not ok
        print(f"  {'ok ' if ok else 'BAD'} {name}: {got!r}")
    msg = b"subject 0123456789a\n\nbody\n\nClaude-Session: https://example/x\n"
    got = s.scrub_message(msg)
    want = b"subject commit:0012\n\nbody\n"
    ok = got == want
    bad += not ok
    print(f"  {'ok ' if ok else 'BAD'} message: trailer dropped + hash tokenized: {got!r}")
    idem = s.scrub_text(s.scrub_text(b"x 0123456789a y fedcba98")) == s.scrub_text(b"x 0123456789a y fedcba98")
    bad += not idem
    print(f"  {'ok ' if idem else 'BAD'} idempotent")
    print(f"scrub --test: {'OK' if not bad else f'{bad} FAILED'}")
    return 1 if bad else 0


# ---------------------------------------------------------------- the sample over one tree (R37: measure first)
def sample(rev, repo):
    s = Scrubber()
    entries = [ln.split("\t")[1] for ln in C.git(["ls-tree", "-r", rev], repo).splitlines()]
    ids = {ln.split("\t")[1]: ln.split()[2] for ln in C.git(["ls-tree", "-r", rev], repo).splitlines()}
    cf = C.CatFile(repo)
    t0 = time.time()
    files_hit, nbytes, ctx7 = 0, 0, []
    all_tokens = collections.Counter()
    for path in entries:
        _, _, data = cf.get(ids[path])
        if data is None or C.is_binary(data):
            continue
        nbytes += len(data)
        before = s.stats["replaced"]
        out = s.scrub_text(data)
        if s.stats["replaced"] != before:
            files_hit += 1
        for m in C.HEX_RE.finditer(data):
            all_tokens[m.group(0)] += 1
            if len(m.group(0)) == 7 and s.token_for(m.group(0)):
                a, b = max(0, m.start() - 40), min(len(data), m.end() + 40)
                ctx7.append(f"{path}: …{data[a:b].decode('utf-8', 'replace')}…".replace("\n", "⏎"))
    cf.close()
    wall = time.time() - t0
    # INDEPENDENT oracle: which distinct tokens does GIT ITSELF resolve to a commit object?
    distinct = sorted(t.decode() for t in all_tokens)
    resolved_by_git = set()
    for i in range(0, len(distinct), 2000):
        chunk = distinct[i:i + 2000]
        out = C.git(["cat-file", "--batch-check"], repo, input="\n".join(f"{t}^{{commit}}" for t in chunk) + "\n", check=False)
        for tok, ln in zip(chunk, out.splitlines()):
            if " commit " in ln:
                resolved_by_git.add(tok)
    ours = {t.decode() for t in s.replaced}
    only_git = sorted(resolved_by_git - ours)
    only_ours = sorted(ours - resolved_by_git)
    per_len = {k: v for k, v in sorted(s.stats.items()) if k.startswith("replaced_len")}
    print(f"scrub --sample {rev}: {len(entries)} tracked paths, {nbytes / 1e6:.0f} MB of text scanned in {wall:.1f} s "
          f"({nbytes / 1e6 / max(wall, 1e-9):.0f} MB/s); {s.stats['replaced']} replacements in {files_hit} files; "
          f"{len(ours)} distinct tokens replaced; excluded {s.stats['excluded']}, ambiguous {s.stats['ambiguous']}, "
          f"unresolved hex tokens {s.stats['unresolved']}, e-mail replacements {s.stats['emails']}")
    print(f"  per length: {per_len}")
    print(f"  independent oracle (git cat-file on every distinct hex token, {len(distinct)} tokens): git resolves "
          f"{len(resolved_by_git)} to commits; ours {len(ours)}; only-git {len(only_git)} (expected: the excluded "
          f"content-hash prefixes, if any); only-ours {len(only_ours)} (MUST be 0)")
    for t in only_git[:10]:
        print(f"    only-git: {t} {'(excluded)' if t in s.excluded else '(!! dictionary gap)'}")
    for t in only_ours[:10]:
        print(f"    only-ours: {t} !!")
    print(f"  7-char replacements in context ({len(ctx7)} — READ them, R63):")
    for c in ctx7[:60]:
        print(f"    {c[:200]}")
    return 1 if only_ours or any(t not in s.excluded for t in only_git) else 0


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--test", action="store_true")
    ap.add_argument("--sample", action="store_true")
    ap.add_argument("--rev", default="HEAD")
    ap.add_argument("--repo", default=str(C.REPO))
    ap.add_argument("--file")
    ap.add_argument("--out")
    a = ap.parse_args(argv)
    if a.test:
        return selftest()
    if a.sample:
        return sample(a.rev, a.repo)
    if a.file:
        s = Scrubber()
        data = open(a.file, "rb").read()
        out = s.scrub_text(data)
        open(a.out or (a.file + ".scrubbed"), "wb").write(out)
        print(f"scrub: {dict(s.stats)}")
        return 0
    ap.error("one of --test / --sample / --file")


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
