"""common.py — shared pieces of the public-flip rewrite tooling (P33 C1). Not a CLI.

Everything ROM-derived, personal or old-hash-bearing lives ONLY under .run/public_rewrite/ (gitignored): the
dictionary of old commit hashes, the mailmap, the blob-id list, the bundle, the bare clone. No personal address and
no old hash is ever a literal in this package — they are derived from the repository at run time.
"""
import fnmatch
import hashlib
import json
import os
import pathlib
import re
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parents[2]
TOOLS = REPO / "tools"
HERE = pathlib.Path(__file__).resolve().parent
SCRATCH = REPO / ".run" / "public_rewrite"
PURGE_FILE = HERE / "purge_set.txt"
DICT_FILE = SCRATCH / "dict.json"
MAILMAP_FILE = SCRATCH / "mailmap"
ROM_IDS_FILE = SCRATCH / "rom_blob_ids.txt"
OLD_TO_NEW_FILE = SCRATCH / "old-to-new.tsv"
CLONE_DIR = SCRATCH / "repo.git"
COMMIT_MAP_PUBLIC = REPO / "docs" / "commit-map.tsv"

NOREPLY_NAME = "Drew T"
NOREPLY_EMAIL = "50529377+Druthulu@users.noreply.github.com"
ZEROS = "0" * 40

# The one hash regex (validated at HEAD, S86: 711 resolving citations, 0 word-embedded false hits; `func_800D128C` and
# `0x800d128c` do not match because \b needs a non-word char on both sides and `_`/`x` are word chars).
HEX_RE = re.compile(rb"\b[0-9a-f]{7,40}\b")
# The inert token: non-hex inside its first 7 chars, so it can never re-match HEX_RE.
TOKEN_RE = re.compile(rb"\bcommit:(?:(?P<ord>[0-9]{4,})|orphan-(?P<orphan>[0-9]+)|amb-(?P<amb>[0-9]+))\b")
TRAILER_RE = re.compile(rb"(?m)^Claude-Session:[^\n]*\n?")
SESSION_URL_RE = re.compile(rb"https://claude\.ai/code/session[^\s)>\"']*")
MIN_PREFIX = 7
SIZE_CAP = 50 * 1024 * 1024


def git(args, repo=REPO, text=True, check=True, input=None):
    r = subprocess.run(["git", "-C", str(repo)] + list(args), capture_output=True, text=text, check=False, input=input)
    if check and r.returncode != 0:
        err = r.stderr if text else r.stderr.decode("utf-8", "replace")
        raise RuntimeError(f"git {' '.join(args)} failed in {repo}: {err.strip()[:300]}")
    return r.stdout


def die(msg, rc=1):
    print(f"{pathlib.Path(sys.argv[0]).name}: {msg}", file=sys.stderr)
    sys.exit(rc)


# ---------------------------------------------------------------- purge rules (the one file, filter-repo syntax)
def purge_rules():
    prefixes, globs = [], []
    for ln in PURGE_FILE.read_text(encoding="utf-8").splitlines():
        ln = ln.strip()
        if not ln or ln.startswith("#"):
            continue
        if ln.startswith("glob:"):
            globs.append(ln[5:])
        elif ln.startswith("regex:"):
            die(f"regex: rules are not supported by this tooling ({ln})")
        else:
            prefixes.append(ln)
    if not prefixes and not globs:
        die(f"{PURGE_FILE} holds no rules — refusing (R43)")
    return prefixes, globs


def under_purge(path, prefixes, globs):
    """The rule a path falls under, or None. `path` is a str; directory prefixes match everything beneath."""
    for p in prefixes:
        if path == p or path.startswith(p if p.endswith("/") else p + "/"):
            return p
    for g in globs:
        if fnmatch.fnmatchcase(path, g):
            return "glob:" + g
    return None


# ---------------------------------------------------------------- the content-hash sets (derived, never typed)
def rom_content_sha1s():
    """SHA1s of ROM-derived artifacts the repo itself declares: the manifest, every check.*.sha, the dumps, the disc."""
    out = {}
    man = REPO / "extracted" / "retail" / "manifest.jsonl"
    if not man.exists():
        die(f"{man} missing — cannot derive the ROM hash set (R32)")
    for ln in man.read_text(encoding="utf-8").splitlines():
        if ln.strip():
            o = json.loads(ln)
            if o.get("size", 1) > 0:                 # the zero-length payloads' sha1 is the empty-file sha1 — not ROM bytes
                out[o["sha1"].lower()] = "manifest:" + o["path"]
    checks = sorted((REPO / "config").glob("check.*.sha"))
    if not checks:
        die("no config/check.*.sha — cannot derive the binary hashes (R32)")
    for c in checks:
        for ln in c.read_text(encoding="utf-8").splitlines():
            parts = ln.split()
            if len(parts) >= 2 and len(parts[0]) == 40:
                out[parts[0].lower()] = f"{c.name}:{parts[1]}"
    dumps = REPO / "dumps" / "CHECKSUMS.sha1"
    if dumps.exists():
        for ln in dumps.read_text(encoding="utf-8").splitlines():
            parts = ln.split()
            if len(parts) >= 2 and len(parts[0]) == 40:
                out[parts[0].lower()] = "dumps:" + parts[1]
    sys.path.insert(0, str(TOOLS / "bfm_extract"))
    from extract_exe import REDUMP_TRACK1_SHA1  # noqa: E402
    out[REDUMP_TRACK1_SHA1.lower()] = "redump:Track 1"
    return out


def cited_content_hashes():
    """Every hash a doc may legitimately cite by prefix and that must NEVER be mistaken for a commit: the ROM sha1s
    above, plus every 64-hex sha256 in the tracked checksum files, plus the redump CRC32 (an 8-hex token)."""
    hashes = set(rom_content_sha1s())
    for f in (TOOLS / "bin" / "CHECKSUMS.sha256", TOOLS / "psyq_CHECKSUMS.sha256"):
        if f.exists():
            hashes.update(m.group(0).lower() for m in re.finditer(r"\b[0-9a-f]{64}\b", f.read_text(encoding="utf-8")))
    sys.path.insert(0, str(TOOLS / "bfm_extract"))
    from extract_exe import REDUMP_TRACK1_CRC32  # noqa: E402
    hashes.add(REDUMP_TRACK1_CRC32.lower())
    return hashes


def prefixes_of(h, lo=MIN_PREFIX, hi=40):
    return {h[:n] for n in range(lo, min(len(h), hi) + 1)}


# ---------------------------------------------------------------- identities (derived from the log, never literal)
def personal_identities(repo=REPO):
    """(name, email) pairs in the history whose email is not the noreply one."""
    seen = set()
    for ln in git(["log", "--all", "--format=%an%x00%ae%x00%cn%x00%ce"], repo).splitlines():
        an, ae, cn, ce = ln.split("\0")
        for n, e in ((an, ae), (cn, ce)):
            if e != NOREPLY_EMAIL:
                seen.add((n, e))
    return sorted(seen)


def write_mailmap(path=MAILMAP_FILE, repo=REPO):
    ids = personal_identities(repo)
    lines = [f"{NOREPLY_NAME} <{NOREPLY_EMAIL}> <{e}>" for _, e in ids]
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return ids


def personal_emails_from_mailmap(path=MAILMAP_FILE):
    if not path.exists():
        die(f"{path} missing — run hash_dict.py --write-mailmap first")
    out = []
    for ln in path.read_text(encoding="utf-8").splitlines():
        m = re.match(r".*<([^>]+)>\s*<([^>]+)>\s*$", ln)
        if m:
            out.append(m.group(2))
    return out


# ---------------------------------------------------------------- the dictionary
def load_dict(path=DICT_FILE):
    if not path.exists():
        die(f"{path} missing — run hash_dict.py first")
    return json.loads(path.read_text(encoding="utf-8"))


def is_binary(data):
    return b"\0" in data[:8192]


def git_blob_id(data):
    h = hashlib.sha1()
    h.update(b"blob %d\0" % len(data))
    h.update(data)
    return h.hexdigest()


class CatFile:
    """A persistent `git cat-file --batch` over one repo (bytes in, (id, type, data) out)."""

    def __init__(self, repo):
        self.p = subprocess.Popen(["git", "-C", str(repo), "cat-file", "--batch"], stdin=subprocess.PIPE,
                                  stdout=subprocess.PIPE, bufsize=0)

    def get(self, ref):
        self.p.stdin.write(ref.encode() + b"\n")
        self.p.stdin.flush()
        hdr = self.p.stdout.readline().decode()
        parts = hdr.split()
        if len(parts) < 3 or parts[1] == "missing":
            return None, None, None
        n = int(parts[2])
        data = b""
        while len(data) < n:
            chunk = self.p.stdout.read(n - len(data))
            if not chunk:
                break
            data += chunk
        self.p.stdout.read(1)            # the trailing newline
        return parts[0], parts[1], data

    def close(self):
        try:
            self.p.stdin.close()
            self.p.wait(timeout=10)
        except Exception:
            self.p.kill()


def iter_all_objects(repo, types=("blob",)):
    """(id, type, size) for every object in the store (reachable or not), via --batch-all-objects."""
    out = git(["cat-file", "--batch-all-objects", "--batch-check"], repo)
    for ln in out.splitlines():
        oid, typ, size = ln.split()
        if typ in types:
            yield oid, typ, int(size)


def parse_commit(raw):
    """Parse a raw commit object (bytes) → dict(tree, parents, author, committer, message) with (name, email, ts, tz)."""
    head, _, msg = raw.partition(b"\n\n")
    d = {"parents": [], "message": msg}
    for ln in head.split(b"\n"):
        if ln.startswith(b"tree "):
            d["tree"] = ln[5:].decode()
        elif ln.startswith(b"parent "):
            d["parents"].append(ln[7:].decode())
        elif ln.startswith(b"author ") or ln.startswith(b"committer "):
            key, _, rest = ln.partition(b" ")
            m = re.match(rb"(.*) <([^>]*)> (\d+) ([+-]\d{4})$", rest)
            if not m:
                raise ValueError(f"unparsable {key.decode()} line: {rest[:80]!r}")
            d[key.decode()] = (m.group(1).decode("utf-8", "surrogateescape"), m.group(2).decode(),
                               int(m.group(3)), m.group(4).decode())
    return d
