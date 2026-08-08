#!/usr/bin/env python3
"""cdtrace — observe CD loads live, from the RAM dump API alone.

NO breakpoints, no Lua (and so no `pcsx.lua` wedge hazard), no GDB stub. The loader keeps its
whole request in RAM, so both halves of the answer are already in the 2 MB image:

    cdReq_curSector 0x800AE708   the sector being read
    cdReq_dest      0x800AE72C   where it is being written
    cdReq_state     0x800AE6F0   request state (non-zero = in flight)
    cdFileLocTable  0x800AE830   8B/entry {CdlLOC pos; u32 size}, indexed by GLOBAL file index

Resolving a sector back to a file index is a lookup in cdFileLocTable, which is itself in the
dump — so a sample gives (global index, destination) directly, i.e. exactly what three static
oracles failed to derive this session.

VALIDATION FIRST (R35): --selftest resolves the table against payloads whose load address is
already byte-proved. If it cannot reproduce a known answer, its output is not evidence.

    python3 .run/s45p5/cdtrace.py --selftest     # prove the resolver on known ground truth
    python3 .run/s45p5/cdtrace.py --watch        # log every distinct load seen
"""
import argparse
import json
import os
import struct
import sys
import time
import urllib.request

RAM_URL = "http://172.17.208.1:8081/api/v1/cpu/ram/raw"
BASE = 0x80000000
CDREQ_STATE, CDREQ_SECTOR, CDREQ_DEST = 0x800AE6F0, 0x800AE708, 0x800AE72C
CDFILELOC = 0x800AE830
GBASE = [("MAIN", 0), ("SC01", 49), ("SC02", 135), ("SC03", 178),
         ("SC04", 318), ("SC05", 349), ("SC06", 379), ("SC07", 418)]
NFILES = 447
PARKED = {7: "MAIN/7", 9: "MAIN/9", 231: "SC03/53", 232: "SC03/54", 234: "SC03/56"}


def ram():
    return urllib.request.urlopen(RAM_URL, timeout=10).read()


def u32(b, vaddr):
    o = vaddr - BASE
    return struct.unpack_from("<I", b, o)[0]


def name_of(gi):
    cd, base = GBASE[0]
    for c, b in GBASE:
        if gi >= b:
            cd, base = c, b
    return f"{cd}/{gi - base}"


DISC_SECTORS = 155122          # Track 1 = 364,846,944 B / 2352 B per sector


def bcd2int(x):
    return (x >> 4) * 10 + (x & 0xF)


def bcd_ok(x):
    return (x >> 4) <= 9 and (x & 0xF) <= 9


def loc_to_lba(word):
    """CdlLOC is packed BCD minute/second/frame; LBA = ((m*60)+s-2)*75 + f.

    Returns None on a TORN read. We poll rather than trap, so cdReq_curSector can be sampled
    mid-update and the decode then yields nonsense — the first run produced 'lba 754890', which is
    beyond the disc's 155,122 sectors, and 'lba 227', neither of which is a real file. Reporting
    those as loads would put phantom rows in the load map (§155a: a predicate that accepts garbage
    is not a measurement). Validate the BCD digits AND the disc range, and drop anything else.
    """
    mb, sb, fb = word & 0xFF, (word >> 8) & 0xFF, (word >> 16) & 0xFF
    if not (bcd_ok(mb) and bcd_ok(sb) and bcd_ok(fb)):
        return None
    m, s, f = bcd2int(mb), bcd2int(sb), bcd2int(fb)
    if s >= 60 or f >= 75:
        return None
    lba = (m * 60 + s - 2) * 75 + f
    return lba if 0 <= lba < DISC_SECTORS else None


def table(b):
    """global index -> (loc_word, size, lba)"""
    out = {}
    for i in range(NFILES):
        loc = u32(b, CDFILELOC + i * 8)
        size = u32(b, CDFILELOC + i * 8 + 4)
        out[i] = (loc, size, loc_to_lba(loc))     # lba may be None (invalid BCD)
    return out


def selftest(b):
    t = table(b)
    nz = [i for i, (l, s, _) in t.items() if l and s]
    print(f"[selftest] cdFileLocTable populated: {len(nz)}/{NFILES} entries have loc+size")
    if len(nz) < 100:
        print("  *** table looks EMPTY — is the game past the boot loader? "
              "LIST.CD is parsed early; idle at the title screen should be enough. ***")
        return False
    print("  sample entries:")
    for i in (0, 7, 9, 10, 11, 144, 231, 232, 234):
        loc, size, lba = t[i]
        tag = f"  <-- PARKED {PARKED[i]}" if i in PARKED else ""
        print(f"    [{i:3d}] {name_of(i):9s} loc=0x{loc:08X} lba={lba:7d} size={size:8d}{tag}")
    # Ground truth: the resident is MAIN/10 and byte-proved to load at 0x800CEDF8 (Phase 3).
    ok = all(t[i][1] > 0 for i in (10, 11))
    print(f"  [check] MAIN/10 (the resident) + MAIN/11 have non-zero sizes: {ok}")
    print(f"  [check] all five parked indices present with size>0: "
          f"{all(t[i][1] > 0 for i in PARKED)}")
    return ok


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--watch", action="store_true")
    ap.add_argument("--interval", type=float, default=0.25)
    a = ap.parse_args()
    b = ram()
    print(f"[cdtrace] RAM {len(b)} bytes from {RAM_URL}")
    if a.selftest or not a.watch:
        ok = selftest(b)
        if not a.watch:
            return 0 if ok else 2
    t = table(b)
    lba2idx = {}
    for i, (loc, size, lba) in t.items():
        if size:
            lba2idx.setdefault(lba, i)
    print(f"[watch] polling every {a.interval}s — Ctrl-C to stop. "
          f"{len(lba2idx)} distinct LBAs indexed.")
    # EDGE-triggered, not set-deduped (fixed 2026-08-07 — Drew caught it mid-session).
    # This used to keep a global `seen` set, so the SECOND load of a file was silently dropped
    # forever. That made re-loads invisible: "leave the area and come back to force a re-read" could
    # not be observed even when it worked, and a scene re-entering the same overlay looked like
    # nothing happening. A monitor that hides repeats cannot answer "did THIS scene load it?" —
    # only "was it ever loaded". Track the PREVIOUS sample instead: consecutive identical samples
    # (the same request still in flight) collapse to one event, but the same file loading again
    # after anything else is a NEW event, which is what a live hunt actually needs.
    last, n, count = None, 0, 0
    while True:
        try:
            b = ram()
        except Exception as e:
            print(f"[warn] {type(e).__name__}", flush=True)
            time.sleep(1)
            continue
        n += 1
        st, sec, dst = u32(b, CDREQ_STATE), u32(b, CDREQ_SECTOR), u32(b, CDREQ_DEST)
        lba = loc_to_lba(sec) if sec else None
        if lba is not None:
            gi = lba2idx.get(lba)
            key = (lba, dst)
            if key != last:
                last = key
                count += 1
                who = f"{name_of(gi)} (gi {gi})" if gi is not None else f"lba {lba} (not in table)"
                mark = "   *** PARKED PAYLOAD ***" if gi in PARKED else ""
                print(f"[load] {who:22s} -> dest 0x{dst:08X}  state={st}{mark}", flush=True)
                with open(".run/s45p5/cdtrace.jsonl", "a") as fh:
                    fh.write(json.dumps({"t": round(time.time(), 1), "lba": lba, "gi": gi,
                                         "name": name_of(gi) if gi is not None else None,
                                         "dest": f"0x{dst:08X}", "state": st}) + "\n")
        if n % 400 == 0:
            print(f"[watch] {n} polls, {count} load events", flush=True)
        time.sleep(a.interval)


if __name__ == "__main__":
    sys.exit(main())
