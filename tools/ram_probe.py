#!/usr/bin/env python3
"""ram_probe.py — PCSX-Redux RAM capture / diff / read for actor-struct field-typing (T5; R10/R11).

Fetches the 2 MB main RAM over the PCSX-Redux web API (Windows-native emulator, bridged to WSL).
Dump offset i maps to PS1 vaddr 0x80000000 + i. Snapshots persist under .run/ram/ so we can diff
across the controlled scenarios Drew runs (walk/jump/swing/charge/damage/zone-change) and, per R10,
type each actor field (pointer vs scalar) + name it by which action moves it.

  tools/ram_probe.py snapshot still                      # capture RAM -> .run/ram/still.bin
  tools/ram_probe.py diff still walked --lo 0x80120000 --hi 0x80200000   # changed words A->B
  tools/ram_probe.py read still 0x801a0014 --n 8 --width 4                # read values
  tools/ram_probe.py ptrs  still --lo 0x801a0000 --hi 0x801a0260         # offsets holding a RAM ptr
  tools/ram_probe.py field still walked jumped --base 0x801a0000        # values at the inferred
                                                                         #   actor offsets across snaps

Default host 172.17.208.1:8081 (R11 NAT gateway); pass --host if the bridge IP changed (check SETUP §3).
"""
import argparse, os, sys, struct, urllib.request

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RAMDIR = os.path.join(REPO, ".run/ram")
BASE = 0x80000000
RAM_SIZE = 2 * 1024 * 1024
PTR_LO, PTR_HI = 0x80010000, 0x80200000   # plausible main-RAM pointer range


def fetch(host):
    url = f"http://{host}/api/v1/cpu/ram/raw"
    with urllib.request.urlopen(url, timeout=15) as r:
        data = r.read()
    if len(data) != RAM_SIZE:
        sys.stderr.write(f"[warn] got {len(data)} bytes (expected {RAM_SIZE})\n")
    return data


def load(name):
    p = os.path.join(RAMDIR, name + ".bin")
    if not os.path.exists(p):
        sys.exit(f"no snapshot {name} ({p})")
    return open(p, "rb").read()


def vrange(a, lo, hi):
    lo = max(lo - BASE, 0); hi = min(hi - BASE, len(a))
    return lo, hi


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["snapshot", "diff", "read", "ptrs", "field"])
    ap.add_argument("args", nargs="*")
    ap.add_argument("--host", default="172.17.208.1:8081")
    ap.add_argument("--lo", type=lambda x: int(x, 0), default=BASE)
    ap.add_argument("--hi", type=lambda x: int(x, 0), default=BASE + RAM_SIZE)
    ap.add_argument("--n", type=int, default=4)
    ap.add_argument("--width", type=int, default=4, choices=(1, 2, 4))
    ap.add_argument("--base", type=lambda x: int(x, 0), help="actor base vaddr (field cmd)")
    a = ap.parse_args()
    os.makedirs(RAMDIR, exist_ok=True)

    if a.cmd == "snapshot":
        name = a.args[0] if a.args else "snap"
        try:
            data = fetch(a.host)
        except Exception as e:
            sys.exit(f"FETCH FAILED ({e}). Is PCSX-Redux running BFM with the web server on {a.host}?")
        open(os.path.join(RAMDIR, name + ".bin"), "wb").write(data)
        print(f"captured {len(data)} B -> .run/ram/{name}.bin")

    elif a.cmd == "diff":
        x, y = load(a.args[0]), load(a.args[1])
        lo, hi = vrange(x, a.lo, a.hi)
        w = a.width
        changed = []
        for off in range(lo, hi - w + 1, w):
            if x[off:off + w] != y[off:off + w]:
                xv = int.from_bytes(x[off:off + w], "little")
                yv = int.from_bytes(y[off:off + w], "little")
                changed.append((BASE + off, xv, yv))
        print(f"{len(changed)} changed {w}-byte words in [0x{a.lo:X},0x{a.hi:X})  ({a.args[0]} -> {a.args[1]})")
        for v, xv, yv in changed[:80]:
            print(f"  0x{v:08X}: {xv:#010x} -> {yv:#010x}  ({xv} -> {yv})")
        if len(changed) > 80:
            print(f"  ... +{len(changed)-80} more")

    elif a.cmd == "read":
        x = load(a.args[0]); va = int(a.args[1], 0); off = va - BASE; w = a.width
        for i in range(a.n):
            o = off + i * w
            v = int.from_bytes(x[o:o + w], "little")
            tag = " <ptr?>" if PTR_LO <= v < PTR_HI else ""
            print(f"  0x{BASE+o:08X} (+0x{i*w:X}): {v:#0{2+w*2}x} ({v}){tag}")

    elif a.cmd == "ptrs":
        x = load(a.args[0]); lo, hi = vrange(x, a.lo, a.hi)
        for off in range(lo, hi - 3, 4):
            v = int.from_bytes(x[off:off + 4], "little")
            if PTR_LO <= v < PTR_HI:
                print(f"  0x{BASE+off:08X}: -> {v:#010x}")

    elif a.cmd == "field":
        if not a.base:
            sys.exit("field: pass --base <actor vaddr>")
        snaps = [(n, load(n)) for n in a.args]
        # the inferred actor offsets (from .run/wall_taxonomy struct inference); fallback to a dense scan
        offs = list(range(0, 0x250, 4))
        print(f"actor @ 0x{a.base:08X}; values across {', '.join(n for n,_ in snaps)} (w=4):")
        for fo in offs:
            o = a.base - BASE + fo
            vals = [int.from_bytes(d[o:o + 4], "little") for _, d in snaps]
            if len(set(vals)) > 1 or any(PTR_LO <= v < PTR_HI for v in vals):
                tag = " <ptr?>" if any(PTR_LO <= v < PTR_HI for v in vals) else (" *changes*" if len(set(vals)) > 1 else "")
                print(f"  +0x{fo:03X}: " + "  ".join(f"{v:#010x}" for v in vals) + tag)


if __name__ == "__main__":
    main()
