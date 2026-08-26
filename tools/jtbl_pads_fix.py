#!/usr/bin/env python3
"""jtbl_pads_fix.py — repair a stale JTBL_PADS spec by SEARCH + BYTE PROOF, never by guessing.

THE DEFECT CLASS THIS ENDS (P31 S60, three instances in one day).
`JTBL_PADS` is a per-object spec written by tools/jtbl_carve.py at CARVE time: one entry per
rodata `.align 3` the object emits, each 0 or 4, first always 0. It describes the object's jump
TABLE POPULATION — a property of the current source — and it is stored, not derived, so ANY change
to that population invalidates it and nothing notices:

  * ov_SC02_005, ov_SC07_006 — wave dd banked a function carrying a `switch`; the table count
    changed under a spec that still described the old population.
  * ov_SC04_018 — the identical symptom from the opposite cause: a maintenance pass REVERTED a
    banked function and its table went with it.

The build then dies with "consumed N rodata .align(s) but M pad spec(s) given", which is
jtbl_rodata_pads doing exactly the right thing (R43: refuse, never mishandle) — but the binary is
RED until a human looks, and a RED binary rejects every draft gated against it, so the cost is
paid in drafts that had nothing wrong with them.

WHY NOT JUST DERIVE THE SPEC. The COUNT is derivable from the assembly stream; the VALUES are not.
A pad records where the ORIGINAL image has an inter-table `.align 3` pad, which depends on the
retail layout, not on anything in our source. Guessing wrong shifts every downstream data symbol —
a silent byte corruption, the worst possible outcome. So this tool does not derive: it ENUMERATES
the small candidate space (2^(N-1) specs: first entry 0, the rest in {0,4}) and lets the whole-binary
byte gate pick. A candidate is accepted only when it is the UNIQUE one that rebuilds the binary
byte-identical to config/check.<bin>.sha. Zero matches or two matches => refuse and restore.

  tools/jtbl_pads_fix.py <binary> [--apply] [--max-tables 5]

Exit 0 = repaired (or nothing to repair). Exit 1 = refused; a human should look.
"""
import argparse
import mk_write
import itertools
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MK = os.path.join(REPO, "config", "overlays.mk")
PAD_ERR = re.compile(r"consumed (\d+) rodata \.align\(s\) but (\d+) pad spec\(s\) given")
# make prints "*** [Makefile:687: build/src/.../x.o] Error 1" — the bracket carries a
# "Makefile:NNN: " prefix, and the original regex required it to START with build/src, so
# find_drift returned None over a failing build and the tool reported "no pad-count drift"
# for six genuinely drifted binaries (S61; the R40 instrument class this tool exists to end).
OBJ_ERR = re.compile(r"\[(?:Makefile:\d+:\s*)?(build/src/[^\]]+\.o)\]")
# the OTHER drift direction: a NEW table appeared (a banked `switch`), so the object emits
# MORE .aligns than the spec has entries; jtbl_rodata_pads phrases that without the emitted count.
PAD_ERR_MORE = re.compile(r"more rodata \.align directives than pad specs \((\d+)\)")


def sh(cmd, **kw):
    return subprocess.run(cmd, cwd=REPO, shell=True, capture_output=True, text=True, **kw)


def good_sha(binary):
    p = os.path.join(REPO, "config", f"check.{binary}.sha")
    with open(p) as fh:
        return fh.read().split()[0]


def armed_objects(binary):
    """The objects that carry a JTBL_PADS spec for this binary (they alone run the pad filter)."""
    out = []
    with open(MK) as fh:
        for line in fh:
            if line.startswith(f"build/src/{binary}/") and ": JTBL_PADS" in line:
                out.append(line.split(":")[0].strip())
    return out


def build_sha(binary):
    """Build under the SAME per-binary lock every gate takes; return the built sha1 or None.

    THE ARMED OBJECTS ARE DELETED FIRST (P31 S60, caught by this tool's own first test). JTBL_PADS
    is a target-specific MAKE VARIABLE: changing it does not make the .o out of date, so an
    incremental build silently keeps the object built with the PREVIOUS spec. The first run of this
    tool reported "no pad-count drift" against a spec I had deliberately broken, and a candidate
    search built on that would have scored every candidate identical — R22's incremental trap,
    wearing a config costume.
    """
    out = os.path.join(REPO, "build", binary, binary)
    # DELETE THE OUTPUT TOO (P31 S60). A failed object build leaves the PREVIOUS binary sitting in
    # build/<bin>/<bin>, and `make build; sha1sum build/<bin>/<bin>` then reports the OLD artifact's
    # hash as if it were this build's — a false GREEN over a build that never linked. It read as a
    # verified fix twice before the make exit code was checked. Same family as R49: an error inside
    # something that looks like success.
    for obj in armed_objects(binary) + [out]:
        try:
            os.remove(os.path.join(REPO, obj) if not os.path.isabs(obj) else obj)
        except OSError:
            pass
    r = sh(f"flock .run/auto/gate.{binary}.lock make build BINARY={binary}")
    if r.returncode != 0 or not os.path.exists(out):
        return None, (r.stdout or "") + (r.stderr or "")
    return sh(f"sha1sum build/{binary}/{binary}").stdout.split()[0], ""


def find_drift(binary):
    """(object, emitted, declared) for the first object whose pad count drifted, else None."""
    _sha, log = build_sha(binary)
    m = PAD_ERR.search(log)
    more = PAD_ERR_MORE.search(log) if not m else None
    if not m and not more:
        return None
    obj = None
    for line in log.splitlines():
        if "jtbl_rodata_pads" in line:
            continue
        o = OBJ_ERR.search(line)
        if o:
            obj = o.group(1)
    if not obj:
        return None
    if m:
        return (obj, int(m.group(1)), int(m.group(2)))
    # "more than" carries only the spec count: the emitted count is unknown but > declared.
    # Return emitted=None; main() searches declared+1 then declared+2 (a bank adds one table
    # in practice; two is the safety margin) — the byte proof still arbitrates every candidate.
    return (obj, None, int(more.group(1)))


def pad_line_for(obj):
    """(index, line, current pads) for the overlays.mk line that arms this object, else None."""
    with open(MK) as fh:
        lines = fh.readlines()
    for i, line in enumerate(lines):
        if line.startswith(f"{obj}: JTBL_PADS"):
            spec = line.split(":=", 1)[1].split("#")[0].strip()
            return i, lines, [int(x) for x in spec.split(",") if x.strip()]
    return None


def write_pads(idx, lines, pads, note):
    """Rewrite ONE armed-object line, atomically, in the exact live format.

    TWO defects lived here until S61 and one poisoned the whole registry (committed by the
    gater blanket commit commit:2996 as `...o: JTBL_PADS : JTBL_PADS := 0,0` -> make dies at
    parse with "target pattern contains no %" and EVERY build of EVERY binary fails):
    (1) the line was split on ':' but `:=` CONTAINS a colon, so each write appended a second
    `: JTBL_PADS`; (2) the file was written with a raw truncating open(MK,"w") - the S60 wipe
    class all four known sites were converted away from (mk_write); this fifth site never was.
    """
    path = lines[idx].split(":", 1)[0]
    lines[idx] = path + ": JTBL_PADS := " + ",".join(str(p) for p in pads) + "  # " + note + "\n"
    mk_write.write_overlays_mk("".join(lines))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("binary")
    ap.add_argument("--apply", action="store_true", help="keep the proven spec (default: dry run)")
    ap.add_argument("--max-tables", type=int, default=5,
                    help="refuse to search above this many tables (2^(N-1) candidates)")
    a = ap.parse_args()
    os.chdir(REPO)

    drift = find_drift(a.binary)
    if not drift:
        print(f"{a.binary}: no pad-count drift (nothing to repair)")
        return 0
    obj, emitted, declared = drift
    print(f"{a.binary}: {obj} emits {emitted if emitted is not None else '>%d' % declared} table(s), "
          f"spec declares {declared}")
    found = pad_line_for(obj)
    if not found:
        print(f"REFUSED: no JTBL_PADS line for {obj} in config/overlays.mk")
        return 1
    idx, lines, original = found

    # THE CANDIDATE SPACE. pads[0] is always 0 (the first table starts the section, so it can carry
    # no inter-table pad); every other entry is 0 or 4. 2^(N-1) candidates: 1, 2, 4, 8, 16.
    counts = [emitted] if emitted is not None else [declared + 1, declared + 2]
    if max(counts) > a.max_tables:
        print(f"REFUSED: searching up to {max(counts)} tables is above --max-tables {a.max_tables}")
        return 1
    cands = [[0] + list(rest) for n in counts for rest in itertools.product((0, 4), repeat=max(0, n - 1))]
    want = good_sha(a.binary)
    winners = []
    for c in cands:
        write_pads(idx, lines, c, "§8e pads — candidate under test (jtbl_pads_fix)")
        got, _log = build_sha(a.binary)
        mark = "BYTE-IDENTICAL" if got == want else (f"sha {got[:12]}" if got else "build failed")
        print(f"  {','.join(str(x) for x in c):<12} -> {mark}")
        if got == want:
            winners.append(c)

    if len(winners) != 1:
        write_pads(idx, lines, original, "§8e pads (jtbl_carve.py) — restored, repair refused")
        print(f"REFUSED: {len(winners)} candidate(s) rebuild byte-identical — a human should look. "
              f"Original spec restored.")
        return 1

    win = winners[0]
    if a.apply:
        write_pads(idx, lines, win, f"§8e pads — {emitted} table(s), byte-proven by jtbl_pads_fix")
        print(f"REPAIRED {obj}: {','.join(str(x) for x in original)} -> "
              f"{','.join(str(x) for x in win)} (unique byte-identical spec)")
    else:
        write_pads(idx, lines, original, "§8e pads (jtbl_carve.py) — dry run, unchanged")
        print(f"DRY RUN: {','.join(str(x) for x in win)} is the unique byte-identical spec. "
              f"Re-run with --apply.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
