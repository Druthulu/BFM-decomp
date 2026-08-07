#!/usr/bin/env python3
"""S45 L3 watcher v2 — continuous tour monitor.

Every ~2.5s: snapshot RAM, log {gameMode, currentLocationId, slot id-words, NAMED overlay
(fingerprint the overlay slot against every onboarded ov_* payload prefix), parked-payload hits}.
Prints a line only when STATE CHANGES (mode/location/overlay) or a parked payload appears.
Appends every distinct state to .run/s45/l3_tour.jsonl; saves a full dump on each parked hit.
Runs until .run/s45/STOP exists or --max samples (default 1200 ≈ 50 min).
"""
import json, re, sys, time, urllib.request
from pathlib import Path

API = "http://172.17.208.1:8081/api/v1/cpu/ram/raw"
ROOT = Path(__file__).resolve().parents[2]
EXT = ROOT / "extracted/retail"
SIG_N = 512

def load_registry(mk):
    exe = {}
    for m in re.finditer(r"^(\w+)_EXE\s+:=\s+(\S+)", (ROOT / mk).read_text(), re.M):
        exe[m.group(1)] = ROOT / m.group(2)
    return exe

def prefixes(exe_map):
    out = {}
    for alias, p in exe_map.items():
        if p.exists():
            out[alias] = p.read_bytes()[:64]
    return out

def parked_sigs():
    out = {}
    def add(name, p):
        if Path(p).exists():
            out[name] = Path(p).read_bytes()[:SIG_N]
    add("MAIN/7", EXT / "MAIN.CD.dir/FILE_007")
    add("MAIN/9", EXT / "MAIN.CD.dir/FILE_009.dir/0.1")
    add("SC02/9", EXT / "SC02.CD.dir/FILE_009.dir/0.1")
    for n in (53, 54, 56):
        add(f"SC03/{n}", EXT / f"SC03.CD.dir/FILE_{n:03d}.dir/0.1")
    for rng, cd, ent in ((range(73, 80), "SC03", "2.1"), (range(132, 139), "SC03", "2.1"),
                         (range(24, 31), "SC04", "2.1"), (range(23, 30), "SC05", "2.1")):
        for n in rng:
            add(f"{cd}/{n}", EXT / f"{cd}.CD.dir/FILE_{n:03d}.dir/{ent}")
    return out

def main():
    max_n = int(sys.argv[1]) if len(sys.argv) > 1 else 1200
    ov_pre = prefixes(load_registry("config/overlays.mk"))
    sigs = parked_sigs()
    stop = ROOT / ".run/s45/STOP"
    log = open(ROOT / ".run/s45/l3_tour.jsonl", "a")
    last_key = None
    print(f"watching: {len(ov_pre)} overlay prefixes, {len(sigs)} parked sigs; touch .run/s45/STOP to end")
    for i in range(max_n):
        if stop.exists():
            print("STOP sentinel — ending")
            break
        try:
            ram = urllib.request.urlopen(API, timeout=10).read()
        except Exception as e:
            print(f"[{i}] API error: {e}")
            time.sleep(5); continue
        gm = int.from_bytes(ram[0xB99DE:0xB99E0], "little")
        loc = int.from_bytes(ram[0xB9A08:0xB9A0C], "little")
        slots = {n: int.from_bytes(ram[o - 0x80000000:o - 0x80000000 + 4], "little")
                 for n, o in (("A", 0x800CAE08), ("B", 0x800CCB1C),
                              ("res", 0x800CEDF8), ("sc07", 0x801A00D8))}
        ovslot = ram[0x128158:0x128158 + 64]
        ov = next((a for a, p in ov_pre.items() if p == ovslot), None)
        hits = []
        for name, sig in sigs.items():
            j = ram.find(sig)
            if j != -1:
                hits.append({"payload": name, "vram": f"0x{0x80000000 + j:08X}"})
        key = (gm, loc, ov, slots["A"], slots["B"], slots["res"], tuple(h["payload"] for h in hits))
        if key != last_key or hits:
            ts = time.strftime("%H:%M:%S")
            line = (f"[{ts}] mode={gm:<2} loc=0x{loc:08X} overlay={ov or '?'} "
                    f"A=0x{slots['A']:02X} B=0x{slots['B']:02X} res=0x{slots['res']:02X}")
            for h in hits:
                line += f"  ** PARKED {h['payload']} @ {h['vram']}"
            print(line, flush=True)
            log.write(json.dumps({"t": ts, "mode": gm, "loc": loc, "overlay": ov,
                                  "slots": {k: hex(v) for k, v in slots.items()},
                                  "hits": hits}) + "\n")
            log.flush()
            if hits and key != last_key:
                (ROOT / f".run/s45/ram_hit_{time.strftime('%H%M%S')}.bin").write_bytes(ram)
            last_key = key
        time.sleep(2.5)
    print("watcher v2 done")

if __name__ == "__main__":
    main()
