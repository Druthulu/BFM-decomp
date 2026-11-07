#!/usr/bin/env python3
"""ledger_backup.py — phase-close backup of the two big run ledgers (P3.40 T15, R3.40-007).

    tools/ledger_backup.py               # write both copies, self-verify, commit the full copy in the local archive
    tools/ledger_backup.py --scan        # report, per JSON path, how many string values look like disassembly
    tools/ledger_backup.py --phase 3.41  # override the phase (default: the `# Phase X.YY` header of PHASE_PLAN.md)

Ledgers (each streamed once, line by line; the sources are never modified):
  restruct-ledger  .run/P37/restruct/ledger.jsonl
  delever-ledger   .run/P36/delever/ledger.jsonl
Outputs (gzip, deterministic: mtime 0, no file name):
  FULL    ../BFM-decomp-archive/ledgers/P<phase>/<name>.jsonl.gz — every line unchanged; committed in that clone
          (`ledgers: P<phase> snapshot`), NEVER pushed (the developer pushes). Cloned with depth 1 when absent.
  PUBLIC  docs/ledgers/<name>-P<phase>.jsonl.gz — each record with the DROP paths removed (tracked in this repo).
DROP paths (a JSON path; list indices collapse to `[]`; a dropped key is removed whole):
  restruct-ledger: residual.pairs (objdump word+mnemonic pairs), hint (fixed by the plan)
  delever-ledger:  sites[].detail (register/mnemonic operand), sites[].why (fixed by the plan); before_text,
                   after_text, source, record.direct[].delta (the 3.40 --scan: `$reg` tokens in C pin annotations,
                   `register s32 x __asm__("$2")`, `/* $s0 */`, `a $2 pin`, `$2`)
  The --scan of 3.40 (every string of every record, recursive) hit only these paths: residual.pairs 60413/83056 strings;
  sites[].detail 41634/67587, before_text 10242/11790, after_text 2235/11790, source 3/11790, record.direct[].delta 1/363.
Predicate (disassembly-shaped string, applied per line of every string): audit_public.DISASM_RES, an 8-hex-digit
instruction word next to a MIPS mnemonic, a mnemonic with a register first operand (`lhu v1,118(s1)`, `addu $2,$3`),
a `$reg` token (`$23`, `$sp`).
Self-verify (rc 1 with a message on any failure): every public line parses, record count == source count, predicate
hits == 0, gz < 50 MB. One summary line per ledger. Restore: `zcat docs/ledgers/<name>-P<phase>.jsonl.gz | ...`.
"""
import argparse
import gzip
import json
import os
import pathlib
import re
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
from audit_public import DISASM_RES  # noqa: E402

ARCHIVE = REPO.parent / "BFM-decomp-archive"
ARCHIVE_REPO = "Druthulu/BFM-decomp-archive"
PLAN = REPO / "phase-ends" / "current" / "PHASE_PLAN.md"
PUBLIC_DIR = REPO / "docs" / "ledgers"
SIZE_CAP = 50 * 1024 * 1024
LEDGERS = [
    ("restruct-ledger", REPO / ".run" / "P37" / "restruct" / "ledger.jsonl", ("residual.pairs", "hint")),
    ("delever-ledger", REPO / ".run" / "P36" / "delever" / "ledger.jsonl", ("sites[].detail", "sites[].why",
                                                                         "before_text", "after_text", "source", "record.direct[].delta")),
]

MNEM = ("add addi addiu addu and andi b bal beq beql beqz bgez bgezal bgtz blez bltz bltzal bne bnel bnez break div divu "
        "j jal jalr jr la lb lbu lh lhu li lui lw lwc2 lwl lwr mfc0 mfc2 mfhi mflo move mtc0 mtc2 mthi mtlo mult multu "
        "negu nop nor not or ori sb sh sll sllv slt slti sltiu sltu sra srav srl srlv sub subu sw swc2 swl swr syscall "
        "xor xori cfc2 ctc2 rfe").split()
_M = "(?:" + "|".join(sorted(MNEM, key=len, reverse=True)) + r")(?:\.[a-z]+)?"
_REG = r"(?:\$(?:\d{1,2}|zero|at|v[01]|a[0-3]|t\d|s[0-8]|k[01]|gp|sp|fp|ra)|zero|at|v[01]|a[0-3]|t\d|s[0-8]|k[01]|gp|sp|fp|ra)"
EXTRA_RES = [
    re.compile(r"\b[0-9a-f]{8}\b\s+" + _M + r"\b"),                         # `96230076 lhu` (objdump word + mnemonic)
    re.compile(r"(?:^|[\s\"'`])" + _M + r"\s+" + _REG + r"\s*,"),           # `lhu\tv1,118(s1)`, `addu $2, $3`
    re.compile(r"\$(?:\d{1,2}|zero|at|v[01]|a[0-3]|t\d|s[0-8]|k[01]|gp|sp|fp|ra)\b"),  # `$23`, `$sp`
]


def disasm_like(s):
    for ln in s.splitlines() or [s]:
        if any(r.search(ln) for r in DISASM_RES) or any(r.search(ln) for r in EXTRA_RES):
            return True
    return False


def walk(obj, path, out):
    """Yield (leaf path, string) for every string value; list indices collapse to []."""
    if isinstance(obj, dict):
        for k, v in obj.items():
            walk(v, f"{path}.{k}" if path else k, out)
    elif isinstance(obj, list):
        for v in obj:
            walk(v, path + "[]", out)
    elif isinstance(obj, str):
        out.append((path, obj))


def strip(obj, path, drop, counts):
    if isinstance(obj, dict):
        res = {}
        for k, v in obj.items():
            kp = f"{path}.{k}" if path else k
            if kp in drop:
                counts[kp] = counts.get(kp, 0) + 1
                continue
            res[k] = strip(v, kp, drop, counts)
        return res
    if isinstance(obj, list):
        return [strip(v, path + "[]", drop, counts) for v in obj]
    return obj


def records(path):
    with open(path, "rb") as f:
        for n, raw in enumerate(f, 1):
            if not raw.strip():
                continue
            try:
                yield raw, json.loads(raw)
            except json.JSONDecodeError as e:
                sys.exit(f"ledger_backup: {path.relative_to(REPO)}:{n} is not JSON ({e}) — refusing a partial copy")


def gz_open(path):
    raw = open(path, "wb")
    return raw, gzip.GzipFile(filename="", mode="wb", fileobj=raw, mtime=0, compresslevel=9)


def scan():
    for name, src, drop in LEDGERS:
        seen, hits, nrec = {}, {}, 0
        for _, rec in records(src):
            nrec += 1
            out = []
            walk(rec, "", out)
            for p, s in out:
                seen[p] = seen.get(p, 0) + 1
                if disasm_like(s):
                    hits[p] = hits.get(p, 0) + 1
        print(f"{name}: {nrec} records, {len(seen)} string paths, {len(hits)} matching")
        for p in sorted(seen):
            mark = "DROP" if any(p == d or p.startswith(d + "[]") or p.startswith(d + ".") for d in drop) else "keep"
            print(f"  {mark} {p}: {hits.get(p, 0)}/{seen[p]}")


def phase_default():
    m = re.match(r"# Phase (\d+\.\d+)", PLAN.read_text(encoding="utf-8").splitlines()[0])
    if not m:
        sys.exit(f"ledger_backup: no `# Phase X.YY` header in {PLAN.relative_to(REPO)}; pass --phase")
    return m.group(1)


def ensure_archive():
    if ARCHIVE.is_dir():
        return
    r = subprocess.run(["gh", "repo", "clone", ARCHIVE_REPO, str(ARCHIVE), "--", "--depth", "1"])
    if r.returncode:
        sys.exit(f"ledger_backup: clone of {ARCHIVE_REPO} into {ARCHIVE} failed (rc {r.returncode})")


def backup(phase):
    ensure_archive()
    adir = ARCHIVE / "ledgers" / f"P{phase}"
    adir.mkdir(parents=True, exist_ok=True)
    PUBLIC_DIR.mkdir(parents=True, exist_ok=True)
    bad = []
    for name, src, drop in LEDGERS:
        full, pub = adir / f"{name}.jsonl.gz", PUBLIC_DIR / f"{name}-P{phase}.jsonl.gz"
        ftmp, ptmp = full.with_suffix(".gz.tmp"), pub.with_suffix(".gz.tmp")
        fraw, fz = gz_open(ftmp)
        praw, pz = gz_open(ptmp)
        counts, nsrc = {}, 0
        for raw, rec in records(src):
            nsrc += 1
            fz.write(raw if raw.endswith(b"\n") else raw + b"\n")
            pz.write(json.dumps(strip(rec, "", drop, counts), ensure_ascii=False).encode("utf-8") + b"\n")
        for z, r in ((fz, fraw), (pz, praw)):
            z.close()
            r.close()
        os.replace(ftmp, full)
        os.replace(ptmp, pub)
        npub, nhit = 0, 0
        with gzip.open(pub, "rb") as f:
            for n, ln in enumerate(f, 1):
                try:
                    rec = json.loads(ln)
                except json.JSONDecodeError as e:
                    bad.append(f"{pub.name}:{n} does not parse ({e})")
                    continue
                npub += 1
                out = []
                walk(rec, "", out)
                nhit += sum(1 for _, s in out if disasm_like(s))
        size = pub.stat().st_size
        if npub != nsrc:
            bad.append(f"{name}: public records {npub} != source {nsrc}")
        if nhit:
            bad.append(f"{name}: {nhit} disassembly-shaped strings left in the public copy")
        if size >= SIZE_CAP:
            bad.append(f"{name}: public gz {size / 1e6:.1f} MB >= 50 MB")
        dropped = ", ".join(f"{p} {c}" for p, c in sorted(counts.items())) or "none"
        print(f"{name}: records {nsrc}, dropped {dropped}, public {size / 1e6:.1f} MB, "
              f"full {full.stat().st_size / 1e6:.1f} MB, hits {nhit}")
    if bad:
        for b in bad:
            print(f"ledger_backup: FAIL {b}", file=sys.stderr)
        return 1
    rel = f"ledgers/P{phase}"
    subprocess.run(["git", "-C", str(ARCHIVE), "add", rel], check=True)
    if subprocess.run(["git", "-C", str(ARCHIVE), "diff", "--cached", "--quiet"]).returncode:
        subprocess.run(["git", "-C", str(ARCHIVE), "commit", "-q", "-m", f"ledgers: P{phase} snapshot"], check=True)
    head = subprocess.run(["git", "-C", str(ARCHIVE), "rev-parse", "--short", "HEAD"], capture_output=True,
                          text=True).stdout.strip()
    print(f"archive: {ARCHIVE}/{rel} committed at {head} (not pushed)")
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--scan", action="store_true", help="per-path predicate match counts; writes nothing")
    ap.add_argument("--phase", help="phase id, e.g. 3.40 (default: PHASE_PLAN.md header)")
    a = ap.parse_args()
    if a.scan:
        scan()
        return 0
    return backup(a.phase or phase_default())


if __name__ == "__main__":
    sys.exit(main())
