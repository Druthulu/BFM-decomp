"""Deterministic SHA1 manifest of the extracted disc (Validation Stage 1).

Walks the extraction output tree and records one JSON object per file --
``{"path", "size", "sha1"}`` -- sorted by path with pinned JSON serialization, so
the manifest is byte-identical across machines and re-runs given the same dump.
``manifest.sha1`` holds the SHA1 of ``manifest.jsonl`` itself: the single value a
contributor diffs to prove their own extraction matches.

See PROJECT_CONTEXT.md "Testing & Validation" stage 1. Pure stdlib.
"""

from __future__ import annotations

import hashlib
import json
from pathlib import Path

MANIFEST_NAME = "manifest.jsonl"
MANIFEST_SHA1_NAME = "manifest.sha1"
_HASH_CHUNK = 1 << 20  # 1 MiB streaming reads
# The manifest's own files are never recorded inside it.
_SELF = {MANIFEST_NAME, MANIFEST_SHA1_NAME}


def _sha1_file(path: Path) -> tuple[int, str]:
    h = hashlib.sha1()
    size = 0
    with open(path, "rb") as fh:
        while True:
            chunk = fh.read(_HASH_CHUNK)
            if not chunk:
                break
            h.update(chunk)
            size += len(chunk)
    return size, h.hexdigest()


def _list_files(out_root: Path) -> list[str]:
    """Sorted POSIX-relative paths of every file under ``out_root`` (excluding
    the manifest itself)."""
    return sorted(
        p.relative_to(out_root).as_posix()
        for p in out_root.rglob("*")
        if p.is_file() and p.name not in _SELF
    )


def build(out_root: Path) -> list[dict]:
    """Deterministic record list for every file under ``out_root`` (sorted)."""
    records = []
    for rel in _list_files(out_root):
        size, sha1 = _sha1_file(out_root / rel)
        records.append({"path": rel, "size": size, "sha1": sha1})
    return records


def render(records: list[dict]) -> str:
    """Pinned, deterministic JSON-Lines serialization (locale-independent)."""
    return "".join(
        json.dumps(r, separators=(",", ":"), ensure_ascii=True, sort_keys=True) + "\n"
        for r in records
    )


def write(out_root: Path, records: list[dict]) -> str:
    """Write manifest.jsonl + manifest.sha1; return the manifest's own SHA1."""
    text = render(records)
    (out_root / MANIFEST_NAME).write_text(text, encoding="ascii", newline="\n")
    digest = hashlib.sha1(text.encode("ascii")).hexdigest()
    (out_root / MANIFEST_SHA1_NAME).write_text(digest + "\n", encoding="ascii", newline="\n")
    return digest


def verify(out_root: Path) -> tuple[bool, list[str]]:
    """Re-hash every file named in manifest.jsonl and compare to the recorded
    size/sha1; also flag any file on disk that the manifest does not list.
    Returns ``(ok, problems)``.
    """
    mpath = out_root / MANIFEST_NAME
    if not mpath.is_file():
        return False, [f"missing {mpath}"]
    problems: list[str] = []
    seen: set[str] = set()
    for line in mpath.read_text(encoding="ascii").splitlines():
        if not line.strip():
            continue
        rec = json.loads(line)
        rel = rec["path"]
        seen.add(rel)
        fp = out_root / rel
        if not fp.is_file():
            problems.append(f"missing file: {rel}")
            continue
        size, sha1 = _sha1_file(fp)
        if size != rec["size"] or sha1 != rec["sha1"]:
            problems.append(f"mismatch: {rel}")
    for rel in sorted(set(_list_files(out_root)) - seen):
        problems.append(f"unlisted on disk: {rel}")
    return (not problems), problems
