#!/usr/bin/env python3
"""Harvest the log-mining slices: list every NEW candidate with its cited log line VERBATIM (R14 — verify the claim against the
bytes, not the agent's summary), and print the denominators. Usage: harvest.py [--full] [slice ...]"""
import pathlib, re, sys

D = pathlib.Path(__file__).resolve().parent
REPO = D.parents[2]
full = "--full" in sys.argv
names = [a for a in sys.argv[1:] if not a.startswith("--")]
files = sorted(p for p in D.glob("*.md") if p.name not in ("BRIEF.md", "HARVEST.md") and (not names or p.stem in names))
tot_c = tot_n = tot_b = 0
lines_read = 0
for f in files:
    text = f.read_text(encoding="utf-8")
    hdr = re.search(r"Candidates considered: (\d+) · NEW: (\d+) · ALREADY-BANKED: (\d+)", text)
    lr = re.search(r"Lines read: (\d+) of (\d+)", text)
    c, n, b = (int(x) for x in hdr.groups()) if hdr else (0, 0, 0)
    tot_c += c; tot_n += n; tot_b += b
    lines_read += int(lr.group(1)) if lr else 0
    new = text.split("## NEW", 1)[1].split("## ALREADY-BANKED", 1)[0] if "## NEW" in text else ""
    cands = re.split(r"^### ", new, flags=re.M)[1:]
    print(f"\n=================== {f.stem}: considered {c} · NEW {n} (found {len(cands)}) · banked {b} · lines read {lr.group(1) if lr else '?'} of {lr.group(2) if lr else '?'}")
    for cand in cands:
        title = cand.splitlines()[0]
        ev = re.search(r"\*\*Evidence:\*\*\s*`?(phase-ends/logs/Phase[\d.]+\.md):(\d+)(?:[–-](\d+))?`?", cand)
        home = re.search(r"\*\*Proposed home:\*\*\s*(.+)", cand)
        print(f"  {title[:200]}")
        if ev:
            path, a, bb = ev.group(1), int(ev.group(2)), int(ev.group(3) or ev.group(2))
            src = (REPO / path).read_text(encoding="utf-8", errors="replace").splitlines()
            if a - 1 < len(src):
                quote = " ".join(src[a - 1:min(bb, a + 2)])
                print(f"      LOG {path}:{a}: {quote[:260]}")
            else:
                print(f"      LOG {path}:{a}: *** LINE OUT OF RANGE ({len(src)} lines) ***")
        else:
            print("      LOG: *** no parsable evidence line ***")
        if full and home:
            print(f"      home: {home.group(1)[:200]}")
print(f"\nTOTAL over {len(files)} slices: considered {tot_c} · NEW {tot_n} · already-banked {tot_b} · lines read {lines_read}")
