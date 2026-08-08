#!/usr/bin/env python3
"""idxtab_map.py — the MASTER LOAD MAP: payload -> owning binary -> load address.

Repeats the §S45-p6 `ov_SC03_001` decode for EVERY onboarded binary. Two halves, both
register-verified (§155 — window-pairing is not evidence):

  IDXTAB   a per-binary DATA table of s16 GLOBAL payload indices, `-1`-terminated. Candidate runs
           are found by SHAPE, then kept ONLY if code in the same binary materializes the run's
           start address. That reference is the discriminator a pure shape scan lacks (§155a):
           the shape alone fires on ordinary s16 data everywhere.

  DESTPTR  the per-binary word holding the destination the wrapper `func_80128CFC` loads into.
           Found by register-tracking the `lw`s in the wrapper's neighbourhood, then reading the
           word at that address out of whichever image covers it.

Together: for each binary, WHICH payloads it requests and WHERE they land.

R32/R35 — CONTROLS RUN FIRST and this exits non-zero if they fail. The two byte-proved rows from
`docs/memory-map.md` §S44/§S45-p6 are:
    ov_SC01_000  IDXTAB @0x8017EEC8 (37 entries)   DESTPTR 0x801A3234 -> 0x801A58E8
    ov_SC03_001  IDXTAB @0x8018D7BC (5: 224,231,232,234,233)  DESTPTR 0x801EBC68 -> 0x801EF468
An oracle that cannot reproduce those is not evidence about anything else.

Usage:
    tools/idxtab_map.py                     # controls + full fleet -> .run/idxtab_map.json
    tools/idxtab_map.py --binaries ov_SC03_001,ov_SC01_000
    tools/idxtab_map.py --controls-only
"""
import argparse
import collections
import glob
import json
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import find_addr_refs as FAR          # ONE register-tracker for the whole project (R33)

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def _jobs():
    try:
        j = int(os.environ.get("JOBS", "0"))
    except ValueError:
        j = 0
    # leave headroom: a byte-gate sweep may be running on the same box
    return max(1, j or max(1, (os.cpu_count() or 4) // 4))

# The shared per-overlay wrapper func_80128CFC sits at a position-locked vram in every overlay, so
# its neighbourhood is a fleet-stable window. Both documented DESTPTR reads (0x80128CD0, 0x80128D34)
# fall inside it; widen only with a control to prove the widening.
WRAPPER_LO, WRAPPER_HI = 0x80128C00, 0x80128E00
RAM_LO, RAM_HI = 0x80010000, 0x80200000          # plausible PS1 main-RAM window for a load address

CONTROLS = {
    "ov_SC01_000": dict(idxtab=0x8017EEC8, n=37, destptr=0x801A3234, dest=0x801A58E8),
    "ov_SC03_001": dict(idxtab=0x8018D7BC, n=5, entries=[224, 231, 232, 234, 233],
                        destptr=0x801EBC68, dest=0x801EF468),
}


# ---------------------------------------------------------------- the global payload index space
def cd_bases():
    """{CD: first global index} + the total, DERIVED from the extracted tree (R33).

    The global index is the LIST.CD ordinal: MAIN's sub-files first, then SC01's, ... Counting the
    extracted FILE_nnn entries per CD reproduces the §S44 table (MAIN 0, SC01 49, SC02 135, SC03
    178, SC04 318, SC05 349, SC06 379, SC07 418) without hardcoding it — so a re-extract that
    changed a count would move the map instead of silently mislabelling every index."""
    order = ["MAIN", "SC01", "SC02", "SC03", "SC04", "SC05", "SC06", "SC07"]
    bases, run = {}, 0
    for cd in order:
        bases[cd] = run
        d = os.path.join(REPO, f"extracted/retail/{cd}.CD.dir")
        n = len({os.path.basename(p).split(".")[0]
                 for p in glob.glob(os.path.join(d, "FILE_[0-9][0-9][0-9]*"))})
        run += n
    return bases, run


def gi_name(gi, bases):
    cd = None
    for c, b in bases.items():
        if gi >= b and (cd is None or b > bases[cd]):
            cd = c
    return f"{cd}/{gi - bases[cd]}" if cd is not None else f"?/{gi}"


# ---------------------------------------------------------------- images
def load_images(only=None):
    out = []
    for alias, path, base in FAR.binaries(only):
        out.append(dict(alias=alias, base=base, data=open(path, "rb").read(), path=path))
    return out


def read_u32(images, addr, prefer=None):
    """Read the word at `addr` from whichever image covers it.

    Overlays all map at the SAME vram, and module-class payloads share slots, so an address can be
    covered by many images. Return every DISTINCT value found with its witnesses instead of picking
    one — an ambiguity the caller must see is not an ambiguity the tool should hide (P9)."""
    vals = collections.defaultdict(list)
    for im in images:
        off = addr - im["base"]
        if 0 <= off <= len(im["data"]) - 4:
            vals[struct.unpack_from("<I", im["data"], off)[0]].append(im["alias"])
    if prefer:
        for v, who in vals.items():
            if prefer in who:
                return v, [prefer], len(vals)
    if not vals:
        return None, [], 0
    v, who = max(vals.items(), key=lambda kv: len(kv[1]))
    return v, who, len(vals)


# ---------------------------------------------------------------- half A: DESTPTR
def destptr_candidates(im):
    """Addresses the wrapper neighbourhood LOADS from, register-verified, most-read first."""
    counts = collections.Counter()
    for va, kind, addr, _det in FAR.scan_all(im["data"], im["base"]):
        if kind == "lw" and WRAPPER_LO <= va < WRAPPER_HI:
            counts[addr] += 1
    return counts


# ---------------------------------------------------------------- half B: IDXTAB
def idxtab_at(im, addr, maxgi, min_len=2, cap=512):
    """The `-1`-terminated s16 run STARTING at `addr`, or None.

    Anchored on the address, not on the shape. The first cut of this searched for MAXIMAL runs of
    in-range s16 and then asked whether the run's start was referenced — which cannot work: ordinary
    data preceding a table is often in range too, so the maximal run starts EARLIER than the table
    and the code reference (to the table) never matches its start. Both byte-proved controls failed
    that way. Iterating the referenced addresses and testing the shape AT each is the right order —
    the reference defines the start, the shape confirms the table (§155a)."""
    data = im["data"]
    off = addr - im["base"]
    if off < 0 or off % 2 or off + 2 > len(data):
        return None
    vals = []
    while off + 2 <= len(data) and len(vals) <= cap:
        v = struct.unpack_from("<h", data, off)[0]
        if v == -1:
            if len(vals) < min_len:
                return None
            # A run of ZEROS ending in -1 is not an index list — it is zero-filled data that happens
            # to butt against 0xFFFF. 106 of the first fleet run's 452 "tables" were exactly this
            # (`MAIN/0 ×58`), and shipping them would have padded the ledger with pure noise (R32:
            # count what you reject, don't quietly pass it on). MAJORITY-zero is the same artifact
            # wearing a disguise (`MAIN/0 ×4, MAIN/8, MAIN/0, MAIN/0`) — index 0 is a real payload,
            # so a table may legitimately contain it, but a run that is mostly zeros is data.
            return None if sum(1 for x in vals if x == 0) * 2 >= len(vals) else vals
        if not 0 <= v <= maxgi:
            return None
        vals.append(v)
        off += 2
    return None


def referenced_addrs(im):
    """Every address code in this binary materializes (any form) — the §155a discriminator."""
    return {addr for _va, _kind, addr, _det in FAR.scan_all(im["data"], im["base"])}


# ---------------------------------------------------------------- per-binary decode
def scan_one(job):
    """The per-binary half that needs ONLY this binary: its IDXTABs and its DESTPTR candidates.

    Split out so the fleet run can use a PROCESS pool — the register walk is pure Python, so threads
    would serialise on the GIL (unlike the byte-gate, which is subprocess-bound). Cross-binary
    resolution of the DESTPTR *value* happens in the parent, once, afterwards."""
    alias, path, base, maxgi, min_len = job
    im = dict(alias=alias, base=base, data=open(path, "rb").read())
    refs = referenced_addrs(im)
    tabs = []
    for a in sorted(refs):
        e = idxtab_at(im, a, maxgi, min_len)
        if e:
            tabs.append(dict(addr=a, entries=e))
    # Two referenced addresses inside ONE run (the code indexes the same list from two entry
    # points) describe the same table twice. Keep the longest — same terminator, same list.
    byend, keep = {}, []
    for t in tabs:
        end = t["addr"] + 2 * len(t["entries"])
        if end not in byend or len(t["entries"]) > len(byend[end]["entries"]):
            byend[end] = t
    keep = sorted(byend.values(), key=lambda t: t["addr"])
    return dict(alias=alias, base=base, idxtabs=keep,
                destptr_addrs=dict(destptr_candidates(im).most_common()))


def decode(im, maxgi, bases, images, min_len=2):
    """The whole decode for ONE already-loaded image (used by the controls)."""
    refs = referenced_addrs(im)
    tabs = []
    for a in sorted(refs):
        e = idxtab_at(im, a, maxgi, min_len)
        if e:
            tabs.append(dict(addr=a, entries=e, names=[gi_name(g, bases) for g in e]))
    dp = destptr_candidates(im)
    dests = []
    for addr, nread in dp.most_common():
        val, who, nvals = read_u32(images, addr, prefer=im["alias"])
        if val is not None and RAM_LO <= val < RAM_HI:
            dests.append(dict(destptr=addr, dest=val, reads=nread, via=who, ambiguity=nvals))
    return dict(alias=im["alias"], base=im["base"], idxtabs=tabs, destptrs=dests)


# ---------------------------------------------------------------- controls
def run_controls(images, maxgi, bases, min_len):
    ok = True
    by = {im["alias"]: im for im in images}
    for alias, exp in CONTROLS.items():
        if alias not in by:
            print(f"  [SKIP] {alias} not in the selected binaries — control NOT exercised")
            ok = False
            continue
        r = decode(by[alias], maxgi, bases, images, min_len)
        tab = next((t for t in r["idxtabs"] if t["addr"] == exp["idxtab"]), None)
        if not tab:
            print(f"  [FAIL] {alias}: IDXTAB 0x{exp['idxtab']:08X} not recovered "
                  f"(recovered {len(r['idxtabs'])}: "
                  f"{', '.join('0x%08X' % t['addr'] for t in r['idxtabs'][:6])})")
            ok = False
        else:
            n_ok = len(tab["entries"]) == exp["n"]
            e_ok = "entries" not in exp or tab["entries"] == exp["entries"]
            print(f"  [{'PASS' if n_ok and e_ok else 'FAIL'}] {alias}: IDXTAB 0x{tab['addr']:08X} "
                  f"{len(tab['entries'])} entries (expected {exp['n']}) "
                  f"{'' if e_ok else '- ENTRIES DIFFER: ' + str(tab['entries'])}")
            ok = ok and n_ok and e_ok
        d = next((d for d in r["destptrs"] if d["destptr"] == exp["destptr"]), None)
        if not d:
            print(f"  [FAIL] {alias}: DESTPTR 0x{exp['destptr']:08X} not recovered "
                  f"(recovered: {', '.join('0x%08X' % x['destptr'] for x in r['destptrs'][:6])})")
            ok = False
        else:
            d_ok = d["dest"] == exp["dest"]
            print(f"  [{'PASS' if d_ok else 'FAIL'}] {alias}: *0x{d['destptr']:08X} = "
                  f"0x{d['dest']:08X} (expected 0x{exp['dest']:08X}) via {','.join(d['via'])}")
            ok = ok and d_ok
    return ok


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--binaries", help="comma list (default: every onboarded binary)")
    ap.add_argument("--controls-only", action="store_true")
    ap.add_argument("--min-len", type=int, default=2, help="min IDXTAB entries (default 2)")
    ap.add_argument("--out", default=".run/idxtab_map.json")
    a = ap.parse_args()

    bases, total = cd_bases()
    maxgi = total - 1
    print(f"global payload index space: 0..{maxgi} "
          f"({', '.join(f'{c}@{b}' for c, b in bases.items())})\n")

    only = set(a.binaries.split(",")) if a.binaries else None
    if only:                                   # controls must always be loaded, even if not asked for
        only |= set(CONTROLS)
    images = load_images(only)
    print(f"loaded {len(images)} image(s)\n== CONTROLS (R32/R35) ==")
    ok = run_controls(images, maxgi, bases, a.min_len)
    if not ok:
        print("\n*** CONTROLS FAILED — the map below would not be evidence. Stopping. ***")
        return 1
    print("  [R32 ok] both byte-proved rows reproduced from the images alone.")
    if a.controls_only:
        return 0

    jobs = [(al, p, b, maxgi, a.min_len) for al, p, b in FAR.binaries(only)]
    print(f"\n== scanning {len(jobs)} binaries ({_jobs()} processes) ==")
    from concurrent.futures import ProcessPoolExecutor
    with ProcessPoolExecutor(max_workers=_jobs()) as ex:
        raw = list(ex.map(scan_one, jobs))
    rows, n_tab, n_dest = [], 0, 0
    for r in raw:
        for t in r["idxtabs"]:
            t["names"] = [gi_name(g, bases) for g in t["entries"]]
        dests = []
        for addr, nread in sorted(r.pop("destptr_addrs").items(), key=lambda kv: -kv[1]):
            val, who, nvals = read_u32(images, addr, prefer=r["alias"])
            if val is not None and RAM_LO <= val < RAM_HI:
                dests.append(dict(destptr=addr, dest=val, reads=nread, via=who, ambiguity=nvals))
        r["destptrs"] = dests
        n_tab += len(r["idxtabs"])
        n_dest += len(dests)
        rows.append(r)
    out = os.path.join(REPO, a.out)
    os.makedirs(os.path.dirname(out), exist_ok=True)
    json.dump(dict(index_space=dict(bases=bases, total=total), binaries=rows),
              open(out, "w"), indent=1)
    with_tab = [r for r in rows if r["idxtabs"]]
    print(f"\n== {len(rows)} binaries: {len(with_tab)} with a referenced IDXTAB "
          f"({n_tab} tables), {n_dest} DESTPTR candidate(s) -> {a.out}")

    # payload -> requesters (the ledger's point: who asks for this payload, and where does it land)
    owners = collections.defaultdict(set)
    for r in rows:
        for t in r["idxtabs"]:
            for nm in t["names"]:
                owners[nm].add(r["alias"])
    print(f"== payloads referenced by at least one IDXTAB: {len(owners)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
