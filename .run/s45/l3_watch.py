#!/usr/bin/env python3
"""S45 L3 watcher: snapshot PCSX-Redux RAM (R11 web API) and report
  (a) the §S44 slot occupants by module-id word (A/B/resident/overlay/SC07),
  (b) any of the 34 parked-for-L3 payloads found in RAM (first-512-byte signature scan),
  (c) append findings to .run/s45/l3_findings.jsonl with a tag.

Usage: l3_watch.py <tag>          e.g. l3_watch.py attract-demo
Read-only against the game; touches nothing outside .run/s45/.
"""
import sys, json, time, urllib.request
from pathlib import Path

API = "http://172.17.208.1:8081/api/v1/cpu/ram/raw"
ROOT = Path(__file__).resolve().parents[2]
EXT = ROOT / "extracted/retail"
SIG_N = 512

SLOTS = {
    "slotA 0x800CAE08": 0x800CAE08, "slotB 0x800CCB1C": 0x800CCB1C,
    "resident 0x800CEDF8": 0x800CEDF8, "overlay 0x80128158": 0x80128158,
    "SC07 0x801A00D8": 0x801A00D8,
}

def parked():
    out = {}
    def add(name, p):
        p = Path(p)
        if p.exists():
            out[name] = p.read_bytes()[:SIG_N]
        else:
            print(f"  [warn] missing payload {p}")
    add("MAIN/7", EXT / "MAIN.CD.dir/FILE_007")
    add("MAIN/9", EXT / "MAIN.CD.dir/FILE_009.dir/0.1")
    add("SC02/9", EXT / "SC02.CD.dir/FILE_009.dir/0.1")
    for n in (53, 54, 56):
        add(f"SC03/{n}", EXT / f"SC03.CD.dir/FILE_{n:03d}.dir/0.1")
    for n in range(73, 80):
        add(f"SC03/{n}", EXT / f"SC03.CD.dir/FILE_{n:03d}.dir/2.1")
    for n in range(132, 139):
        add(f"SC03/{n}", EXT / f"SC03.CD.dir/FILE_{n:03d}.dir/2.1")
    for n in range(24, 31):
        add(f"SC04/{n}", EXT / f"SC04.CD.dir/FILE_{n:03d}.dir/2.1")
    for n in range(23, 30):
        add(f"SC05/{n}", EXT / f"SC05.CD.dir/FILE_{n:03d}.dir/2.1")
    return out

def main():
    tag = sys.argv[1] if len(sys.argv) > 1 else "untagged"
    ram = urllib.request.urlopen(API, timeout=10).read()
    assert len(ram) == 2 * 1024 * 1024, f"unexpected RAM size {len(ram)}"
    sigs = parked()

    gm = int.from_bytes(ram[0xB99DE:0xB99E0], "little")
    print(f"[{tag}] gameMode={gm}")
    slot_report = {}
    for name, vram in SLOTS.items():
        off = vram - 0x80000000
        w0 = int.from_bytes(ram[off:off+4], "little")
        slot_report[name] = f"0x{w0:08X}"
        print(f"  {name}: word0 = 0x{w0:08X}")

    hits = []
    for name, sig in sigs.items():
        i = ram.find(sig)
        while i != -1:
            hits.append({"payload": name, "vram": f"0x{0x80000000 + i:08X}"})
            print(f"  ** PARKED PAYLOAD IN RAM: {name} @ 0x{0x80000000 + i:08X}")
            i = ram.find(sig, i + 1)
    if not hits:
        print("  (no parked payloads in RAM this snapshot)")

    rec = {"t": time.strftime("%H:%M:%S"), "tag": tag, "gameMode": gm,
           "slots": slot_report, "hits": hits}
    with open(ROOT / ".run/s45/l3_findings.jsonl", "a") as f:
        f.write(json.dumps(rec) + "\n")
    # keep the raw dump for any hit snapshot (proof material, R10/R20)
    if hits:
        dump = ROOT / f".run/s45/ram_{tag}_{time.strftime('%H%M%S')}.bin"
        dump.write_bytes(ram)
        print(f"  dump saved: {dump.name}")

if __name__ == "__main__":
    main()
