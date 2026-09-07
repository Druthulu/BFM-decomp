#!/usr/bin/env python3
"""gate_scan.py — the first-push gate over HISTORY: no ROM-derived blob reachable from the given refs (P33 C1).

    tools/public_rewrite/gate_scan.py --all [--worktree] [--expect-fail EXPECTED.txt] [--emit-ids FILE] [--repo PATH]
    tools/public_rewrite/gate_scan.py --refs main [--worktree]

Four checks, every one derived (R33) from the repo's own declarations:
  1. PATHS — every path ever touched by any commit reachable from the refs (`git log --name-only`) against the purge
     rules in purge_set.txt;
  2. CONTENT — every reachable blob's content SHA1 against the ROM set (the manifest's non-empty payloads, every
     config/check.*.sha, dumps/CHECKSUMS.sha1, the redump Track-1 SHA1) — a renamed copy is caught by content;
  3. SIGNATURES — `PS-X EXE` at offset 0; a 2,097,152-byte RAM image carrying the resident blob's first 16 bytes at
     0xCEDF8 or the EXE's entry code at 0x10000; a blob beginning with the EXE's entry code (a header-less EXE copy);
     PsyQ `LIB\\x01` / `LNK\\x02` magics. The signature bytes come from the extracted payloads on disk (refused if absent
     — a scan that silently skips a check is not a gate, R32);
  4. SIZE — any blob > 50 MiB.
`--emit-ids FILE` (default .run/public_rewrite/rom_blob_ids.txt) writes the blob ids that must die everywhere:
content/signature hits ∪ every blob that ever sat under a purge path (`git log --raw`), for `--strip-blobs-with-ids`.
`--expect-fail EXPECTED.txt` is the R39 NEGATIVE CONTROL: lines `<purge rule>\\t<min offending paths>`; exit 0 only when
every listed rule has at least that many offending paths AND no content/signature/size offender sits outside the purge
rules (an unexpected ROM blob elsewhere is exactly what the gate exists to find). Without it: exit 1 on any offender.
`--worktree` additionally runs tools/audit_public.py over the tracked files (the tip).
"""
import argparse
import collections
import hashlib
import subprocess
import sys

sys.path.insert(0, str(__import__("pathlib").Path(__file__).resolve().parent))
import common as C  # noqa: E402


def signatures():
    exe = C.REPO / "extracted" / "retail" / "SLUS_007.26"
    res = C.REPO / "extracted" / "retail" / "MAIN.CD.dir" / "FILE_010.dir" / "1.1"
    if not exe.exists() or not res.exists():
        C.die(f"signature sources missing ({exe}, {res}) — run make disc-extract; refusing to scan without them (R32)")
    with open(exe, "rb") as f:
        head = f.read(0x810)
    with open(res, "rb") as f:
        res16 = f.read(16)
    return {"exe_entry": head[0x800:0x810], "resident16": res16}


def reachable_blobs(repo, refs):
    """[(blob id, first path)] reachable from refs."""
    out = C.git(["rev-list", "--objects"] + refs, repo)
    ids, paths = [], {}
    for ln in out.splitlines():
        parts = ln.split(" ", 1)
        ids.append(parts[0])
        if len(parts) == 2:
            paths[parts[0]] = parts[1]
    chk = C.git(["cat-file", "--batch-check"], repo, input="\n".join(ids) + "\n")
    blobs = []
    for ln in chk.splitlines():
        p = ln.split()
        if len(p) >= 3 and p[1] == "blob":
            blobs.append((p[0], paths.get(p[0], "")))
    return blobs


def paths_ever(repo, refs):
    return set(C.git(["log", "--name-only", "--format="] + refs, repo).splitlines()) - {""}


def blobs_under_purge(repo, refs, prefixes, globs):
    """(under, shared): blob ids of every version of every path that ever sat under a purge rule (`git log --raw`),
    and the subset that ALSO appears under a NON-purge path somewhere in history. A shared blob must never be stripped
    by id: the trial rewrite (S87) had the EMPTY blob in the list (an empty file once sat under a purge path) and
    `--strip-blobs-with-ids` then dropped every "file emptied" change in history — those files silently kept their
    previous content and one restore commit became empty and was pruned."""
    out = C.git(["log", "--raw", "--no-renames", "--no-abbrev", "--format="] + refs, repo)   # --no-abbrev: full blob ids
    under, elsewhere = set(), set()
    for ln in out.splitlines():
        if not ln.startswith(":"):
            continue
        meta, _, path = ln.partition("\t")
        f = meta.split()
        if len(f) < 4:
            continue
        target = under if C.under_purge(path, prefixes, globs) else elsewhere
        for oid in (f[2], f[3]):
            if len(oid) == 40 and set(oid) != {"0"}:
                target.add(oid)
    return under, under & elsewhere


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--all", action="store_true")
    g.add_argument("--refs", nargs="+")
    ap.add_argument("--worktree", action="store_true")
    ap.add_argument("--expect-fail")
    ap.add_argument("--emit-ids", default=str(C.ROM_IDS_FILE))
    ap.add_argument("--repo", default=str(C.REPO))
    a = ap.parse_args(argv)
    refs = ["--all"] if a.all else a.refs
    prefixes, globs = C.purge_rules()
    rom = C.rom_content_sha1s()
    sig = signatures()
    offenders = []                       # (kind, path, detail, blob id or "")
    # 1. paths
    for p in sorted(paths_ever(a.repo, refs)):
        r = C.under_purge(p, prefixes, globs)
        if r:
            offenders.append(("path", p, f"purge rule {r}", ""))
    # 2–4. blobs
    blobs = reachable_blobs(a.repo, refs)
    cf = C.CatFile(a.repo)
    content_hits, nbytes = set(), 0
    for oid, path in blobs:
        _, _, data = cf.get(oid)
        if data is None:
            continue
        nbytes += len(data)
        why = []
        if len(data) > C.SIZE_CAP:
            why.append(f"{len(data):,} bytes > 50 MiB")
        h = hashlib.sha1(data).hexdigest()
        if h in rom:
            why.append(f"content sha1 == {rom[h]}")
        if data[:8] == b"PS-X EXE":
            why.append("signature PS-X EXE")
        if len(data) == 2097152 and (data[0xCEDF8:0xCEDF8 + 16] == sig["resident16"] or data[0x10000:0x10010] == sig["exe_entry"]):
            why.append("signature 2 MiB RAM image")
        if data[:16] == sig["exe_entry"]:
            why.append("signature EXE entry code at 0")
        if data[:4] in (b"LIB\x01", b"LNK\x02"):
            why.append("signature PsyQ LIB/LNK")
        if why:
            content_hits.add(oid)
            offenders.append(("blob", path, "; ".join(why), oid))
    cf.close()
    by_kind = collections.Counter(k for k, *_ in offenders)
    under, shared = blobs_under_purge(a.repo, refs, prefixes, globs)
    if by_path := sum(1 for k, *_ in offenders if k == "path"):
        if not under:
            C.die(f"{by_path} purge-path offenders but NO blob under any purge rule — the --raw parser is broken (R43)")
    # strip by id: every content/signature hit (wherever it lives) + purge-path blobs that live NOWHERE else
    ids = sorted(content_hits | (under - shared))
    with open(a.emit_ids, "w", encoding="utf-8") as f:
        f.write("\n".join(ids) + ("\n" if ids else ""))
    # report
    print(f"gate_scan: refs {refs}: {len(blobs)} reachable blobs ({nbytes / 1e9:.2f} GB) scanned against {len(rom)} ROM "
          f"sha1s + 5 signatures + 50 MiB; paths ever touched checked against {len(prefixes) + len(globs)} purge rules; "
          f"offenders: paths {by_kind['path']}, blobs {by_kind['blob']} ({len(content_hits)} content/signature ids); "
          f"rom_blob_ids: {len(ids)} ({len(under)} ever under a purge path, {len(shared)} of them shared with a non-purge path and "
          f"therefore NOT stripped by id: {', '.join(x[:12] for x in sorted(shared)[:5])}) -> {a.emit_ids}")
    rc = 0
    if a.expect_fail:
        want = {}
        for ln in open(a.expect_fail, encoding="utf-8"):
            ln = ln.strip()
            if ln and not ln.startswith("#"):
                rule, _, n = ln.partition("\t")
                want[rule.strip()] = int(n or 1)
        per_rule = collections.Counter(d.split("purge rule ", 1)[1] for k, p, d, _ in offenders if k == "path")
        for rule, n in sorted(want.items()):
            ok = per_rule.get(rule, 0) >= n
            print(f"  {'ok ' if ok else 'BAD'} rule {rule}: {per_rule.get(rule, 0)} offending paths (expected ≥ {n})")
            rc |= not ok
        stray = [(p, d) for k, p, d, _ in offenders if k == "blob" and not C.under_purge(p, prefixes, globs)]
        print(f"  {'ok ' if not stray else 'BAD'} content/signature/size offenders outside the purge rules: {len(stray)}")
        for p, d in stray[:20]:
            print(f"    STRAY {p}: {d}")
        rc |= bool(stray)
        print(f"gate_scan --expect-fail: {'PASS (the scan fails exactly as expected)' if not rc else 'FAIL'}")
    else:
        for k, p, d, oid in offenders[:40]:
            print(f"  OFFENDER [{k}] {p} {oid[:12]} {d}")
        if len(offenders) > 40:
            print(f"  … {len(offenders) - 40} more")
        rc = 1 if offenders else 0
        print(f"gate_scan: {'PASS — 0 offenders' if not offenders else f'FAIL — {len(offenders)} offenders'}")
    if a.worktree:
        sys.path.insert(0, str(C.TOOLS))
        import audit_public
        wrc = audit_public.main([])
        rc |= wrc
    return int(rc)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
