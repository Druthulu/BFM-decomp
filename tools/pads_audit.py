#!/usr/bin/env python3
"""tools/pads_audit.py <binary> — DERIVE each object's JTBL_PADS from the bytes instead of searching for it.
For every `build/src/<b>/<tu>.o: JTBL_PADS := …` line: (1) compile the TU through cpp|cc1|maspsx and count
its `.align 3` jump tables (+ entry counts); (2) read the yaml's `.rodata <tu>` carve span(s); (3) scan the
retail words inside the span: runs of code addresses = tables, zero words between = pad 4; (4) print
SPEC vs COMPILED vs RETAIL and a derived spec. Mismatch classes: SPEC-DRIFT (pads wrong, carve right),
CARVE-DRIFT (compiled tables != retail tables inside the span — the yaml must move), NO-CARVE."""
import re, sys, subprocess, struct, os
b = sys.argv[1]
mk = open('config/overlays.mk').read()
y = open('config/splat.%s.yaml' % b).read()
vram = int(re.search(r'^\s*vram:\s*(0x[0-9A-Fa-f]+)', y, re.M).group(1), 16)
tgt = re.search(r'^\s*(?:target_)?path:\s*(\S+)', y, re.M).group(1)
raw = open(tgt, 'rb').read()
segs = re.findall(r'^\s*- \[0x([0-9A-Fa-f]+), (\S+), (\S+?)\]', y, re.M)
segs = [(int(a, 16), k, n) for a, k, n in segs]
def carves(tu):
    out = []
    for i, (a, k, n) in enumerate(segs):
        if k == '.rodata' and n == tu:
            end = segs[i + 1][0] if i + 1 < len(segs) else None
            out.append((a, end))
    return out
def compiled_tables(tu):
    cmd = subprocess.run(['make', '-n', '-W', 'src/%s/%s.c' % (b, tu), 'build/src/%s/%s.o' % (b, tu), 'BINARY=%s' % b], capture_output=True, text=True).stdout
    line = [l for l in cmd.splitlines() if 'cc1' in l][0]
    line = re.sub(r'\|\s*\.venv/bin/python\s+tools/jtbl_rodata_pads\.py[^|]*', '', line)
    line = re.sub(r'\|\s*[^|]*mipsel-linux-gnu-as.*$', '', line)
    line = re.sub(r'^\s*@?set -o pipefail;\s*', '', line)
    s = subprocess.run(['bash', '-c', line], capture_output=True, text=True).stdout
    sizes, cur = [], None
    for l in s.splitlines():
        if re.match(r'\s*\.align\s+3\b', l): cur = 0; sizes.append(0); continue
        if cur is not None and re.match(r'\s*\.word\b', l): sizes[-1] += 1
        elif cur is not None and re.match(r'\s*(\$?L\w+:|\.text|\.ent|\.section)', l) and not re.match(r'\s*\$?L\w+:', l): cur = None
    return sizes
def derive_pads(a, end, comp):
    """Walk the carve span with the COMPILED table sizes: table i either starts immediately (pad 0) or after
    exactly one zero word (pad 4); every entry must be an in-range code address; the walk must end at the
    carve end. Returns (pads or None, note)."""
    lo, hi = vram, vram + len(raw)
    off, pads = a, []
    for k, n in enumerate(comp):
        if k and off + 4 <= end and struct.unpack_from('<I', raw, off)[0] == 0:
            pads.append(4); off += 4
        else:
            pads.append(0)
        for _ in range(n):
            if off + 4 > end: return None, 'span ends inside table %d' % k
            w = struct.unpack_from('<I', raw, off)[0]
            if not (lo <= w < hi): return None, 'non-code word %08X at 0x%x in table %d' % (w, off, k)
            off += 4
    if off != end: return None, 'walk ends at 0x%x, carve ends at 0x%x (%+d bytes)' % (off, end, end - off)
    return pads, ''
for m in re.finditer(r'^build/src/%s/(\S+)\.o: JTBL_PADS := ([0-9,]+)' % b, mk, re.M):
    tu, spec = m.group(1), [int(x) for x in m.group(2).split(',')]
    comp = compiled_tables(tu)
    cv = carves(tu)
    if not cv:
        print('%-11s %-28s spec=%-10s compiled=%s' % ('NO-CARVE', tu, ','.join(map(str, spec)), comp)); continue
    if len(cv) > 1:
        print('%-11s %-28s spec=%-10s compiled=%s carves=%s' % ('MULTI-CARVE', tu, ','.join(map(str, spec)), comp, cv)); continue
    a, e = cv[0]
    pads, note = derive_pads(a, e, comp)
    if pads is None: cls = 'CARVE-DRIFT'
    elif pads != spec: cls = 'SPEC-DRIFT'
    else: cls = 'ok'
    print('%-11s %-28s spec=%-10s compiled=%-16s derived=%-10s carve=0x%x..0x%x %s' % (cls, tu, ','.join(map(str, spec)), comp, ','.join(map(str, pads)) if pads else '-', a, e, note))
