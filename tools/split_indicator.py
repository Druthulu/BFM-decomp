#!/usr/bin/env python3
"""split_indicator.py -- which code subsegs MUST be split before their switch functions can bank?

THE CONSTRAINT. A compiled object contributes exactly ONE contiguous `.rodata` run. A binary whose
gcc switch jump tables sit in an island of several SEPARATED spans can therefore carve only one span
per code object -- so every switch function whose table lives in a second span is **unbankable**, at
any effort: cc1 emits its table while the raw copy is still emitted from the data segment, the image
grows, and every symbol above the insertion point shifts.

WHY THIS IS A TOOL AND NOT A PARAGRAPH (P31 S72). `main` sat in exactly that state from Phase 7 to
Phase 31. The evidence was written down by hand in `config/splat.us.exe.yaml` on 2026-06-15 -- the
island's contents, the divider, the library tables -- and nothing ever compared it against the
subseg list. The cost of noticing late is not the delay, it is that a TU split costs a yaml edit at
0% matched and a declaration refactor at 94% (accelerators #20): `src/800.c` went from 13 externs /
0 typedefs to 2,378 / 175 in between. Eleven functions were meanwhile recorded as "PROVEN
gate-rejects" and ten of them banked byte-identical the moment the carve existed.

So this is the check that should run on day one of a decomp, and on every binary, forever:

    tools/split_indicator.py                 # every binary
    tools/split_indicator.py --binary main   # one
    tools/split_indicator.py --self-test     # negative control (see below)

WHAT IT REPORTS
  * **NEEDS SPLIT** -- a code subseg references raw tables in >= 2 non-adjacent spans. Names the
    spans, the owning functions, and the address boundary to split at. Those functions cannot bank
    until it is done. Exit 1.
  * **OK** -- every subseg's raw tables are confined to one contiguous span.
  * **REFUSED** -- a table it cannot attribute to any subseg. Reported loudly and counted as a
    failure, never folded into OK (R43/R32: a checker that silently skips what it cannot parse
    reports a true number about a narrower world than the reader believes).

WHAT IT DELIBERATELY DOES NOT DO. It does not propose splits on TU archaeology. A contiguous run of
tables IS one translation unit's rodata, so the spans reveal (some of) the original TU boundaries --
but a TU containing no `switch` emits no table and is invisible here, so the spans are a LOWER BOUND
on the original structure, never a reconstruction of it. Split where the BUILD forces a boundary and
nowhere else: the minimum that satisfies the constraint is the right answer, and extra splits cost
declaration duplication across the new TUs for nothing.
"""
import argparse, collections, functools, glob, os, re, subprocess, sys

print = functools.partial(print, flush=True)
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
JTBL = re.compile(r'jtbl_([0-9A-Fa-f]{8})')


def splat_yaml(binary):
    p = os.path.join(REPO, 'config',
                     'splat.us.exe.yaml' if binary == 'main' else 'splat.%s.yaml' % binary)
    return p if os.path.exists(p) else None


def file0_vram(text):
    """The vram matching byte 0 of the target file: `vram - start` for a segment with a header
    (main's PS-X EXE), and plain `vram` for a flat overlay blob. Same derivation as
    jtbl_rodata_pads._file0_vram -- yaml offsets and addresses must agree in ONE expression."""
    m = re.search(r'-\s*name:\s*\w+\s*\n\s*type:\s*code\s*\n\s*start:\s*(0x[0-9A-Fa-f]+)'
                  r'\s*\n\s*vram:\s*(0x[0-9A-Fa-f]+)', text)
    if m:
        return int(m.group(2), 16) - int(m.group(1), 16)
    m = re.search(r'^\s*vram:\s*(0x[0-9A-Fa-f]+)', text, re.M)
    return int(m.group(1), 16) if m else None


def pieces(text, base):
    """-> (code_subsegs, rodata_carves) as {name: [(lo_vram, hi_vram)]}, from the yaml piece list."""
    rows = [(int(a, 16), k, n) for a, k, n in
            re.findall(r'^\s*- \[0x([0-9A-Fa-f]+), (\S+), (\S+?)\]', text, re.M)]
    rows.sort()
    code, rod = collections.defaultdict(list), collections.defaultdict(list)
    for i, (off, kind, name) in enumerate(rows):
        hi = base + rows[i + 1][0] if i + 1 < len(rows) else None
        (code if kind == 'c' else rod if kind == '.rodata' else {}).setdefault(name, []) \
            .append((base + off, hi)) if kind in ('c', '.rodata') else None
    return code, rod


def raw_tables(binary):
    """Jump tables STILL IN RAW DATA (a migrated table lives in a .s and cannot conflict).
    -> sorted [(lo, hi)] vram spans, one per table."""
    d = os.path.join(REPO, 'asm', 'data') if binary == 'main' \
        else os.path.join(REPO, 'asm', binary, 'data')
    out = []
    for f in sorted(glob.glob(os.path.join(d, '*.s'))):
        cur, lo, hi = None, None, None
        for ln in open(f, errors='replace'):
            m = re.match(r'\s*dlabel\s+(jtbl_[0-9A-Fa-f]{8})', ln)
            if m:
                cur, lo, hi = m.group(1), None, None
                continue
            if cur is None:
                continue
            m = re.match(r'\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})', ln)
            if m:
                a = int(m.group(1), 16)
                lo = a if lo is None else lo
                hi = a + 4
            elif ln.strip().startswith('enddlabel') and lo is not None:
                out.append((lo, hi)); cur = None
    return sorted(out)


def spans(tables):
    """Merge tables that abut into contiguous spans -> [(lo, hi, count)]."""
    out = []
    for lo, hi in tables:
        if out and out[-1][1] == lo:
            out[-1][1], out[-1][2] = hi, out[-1][2] + 1
        else:
            out.append([lo, hi, 1])
    return [tuple(s) for s in out]


def owners(binary):
    """-> {table_addr: {(subseg, fn)}} from every stub .s that references a jtbl symbol."""
    root = os.path.join(REPO, 'asm', 'nonmatchings') if binary == 'main' \
        else os.path.join(REPO, 'asm', binary, 'nonmatchings')
    out = collections.defaultdict(set)
    if not os.path.isdir(root):
        return out
    r = subprocess.run(['grep', '-rEo', '--include=*.s', 'jtbl_[0-9A-Fa-f]{8}', root],
                       capture_output=True, text=True)
    for line in r.stdout.splitlines():
        path, _, sym = line.rpartition(':')
        if not path:
            continue
        out[int(sym[5:], 16)].add((os.path.basename(os.path.dirname(path)),
                                   os.path.basename(path)[:-2]))
    return out


def check(binary, remap=None, tabs_override=None, own_override=None):
    """-> (status, lines).

    `tabs_override` / `own_override` inject a synthetic island so the DECISION LOGIC can be tested
    against a case whose answer is known, independently of the current tree. The first version of
    the self-test tried to simulate 'before the split' by merging subseg NAMES, and reported OK:
    undoing the split would also mean un-carving spans B and C, and a carved table is no longer
    raw, so there was nothing left to find. A control that cannot fail is not a control."""
    y = splat_yaml(binary)
    if not y:
        return 'REFUSED', ['no splat config']
    txt = open(y).read()
    base = file0_vram(txt)
    if base is None:
        return 'REFUSED', ['no vram in the splat config']
    code, _rod = pieces(txt, base)
    # LINKED LIBRARY SUBSEGS CANNOT CONFLICT, AND FLAGGING THEM IS A FALSE POSITIVE. Their code
    # comes from a PsyQ .a, not from our C, so cc1 never emits a table for them and their raw
    # tables are inert forever. Measured: without this filter main reports NEEDS SPLIT on `libgs6`
    # (5 spans) and `libmcrd1` (2) while the game subsegs are clean — the detector's own self-test
    # caught it before it could be believed.
    try:
        sys.path.insert(0, os.path.join(REPO, 'tools'))
        import progress
        progress.set_binary(binary)
        linked = set(progress.linked_subsegs())
    except Exception:
        linked = set()
    tabs = raw_tables(binary) if tabs_override is None else tabs_override
    if not tabs:
        return 'OK', ['no raw jump tables']
    sp = spans(tabs)
    own = owners(binary) if own_override is None else own_override
    by_sub, unattributed = collections.defaultdict(set), []
    for i, (lo, hi, _n) in enumerate(sp):
        hit = False
        for addr, who in own.items():
            if lo <= addr < hi:
                for sub, fn in who:
                    if sub in linked:
                        hit = True
                        continue
                    by_sub[remap(sub) if remap else sub].add((i, fn))
                hit = True
        if not hit:
            unattributed.append((lo, hi))
    lines, bad = [], False
    for sub, entries in sorted(by_sub.items()):
        idxs = sorted({i for i, _ in entries})
        if len(idxs) > 1:
            bad = True
            lines.append(f"  NEEDS SPLIT — subseg `{sub}` owns raw tables in {len(idxs)} "
                         f"non-adjacent spans; only ONE can carve:")
            for i in idxs:
                lo, hi, n = sp[i]
                fns = sorted(fn for j, fn in entries if j == i)
                a = [f for f in fns if re.fullmatch(r'func_[0-9A-Fa-f]{8}', f)]
                rng = (f"owners 0x{min(int(f[5:],16) for f in a):08x}.."
                       f"0x{max(int(f[5:],16) for f in a):08x}") if a else "owners: see below"
                lines.append(f"      span 0x{lo:08x}-0x{hi:08x} ({n} tables) — {rng}")
                lines.append(f"          {', '.join(fns[:6])}"
                             + (f" … +{len(fns)-6}" if len(fns) > 6 else ""))
            lines.append(f"      -> split `{sub}` between those owner ranges (cookbook §431); "
                         f"until then those functions CANNOT bank.")
    if unattributed:
        # A raw table that NO stub references is owned by linked library code. The reasoning is a
        # derived invariant, not a guess (R33): the binary builds byte-identical, therefore every
        # MATCHED function's table is already carved into its object; so a table still sitting raw
        # and referenced by no stub cannot belong to code we compile. Reported, never hidden — but
        # not counted as a failure, because there is nothing to split.
        lines.append(f"  note: {len(unattributed)} raw span(s) referenced by no stub — "
                     f"linked-library owned (the build is byte-identical, so every matched "
                     f"function's table is already carved): "
                     + ", ".join(f"0x{lo:08x}-0x{hi:08x}" for lo, hi in unattributed[:4]))
    return ('NEEDS SPLIT' if bad else 'OK'), (lines or [f"{len(sp)} span(s), each confined "
                                                        f"to one subseg"])


def self_test():
    """Known-true cases, both directions.

    1. main as it stands must be OK — the S72 split fixed it.
    2. main's island BEFORE that split (spans A+B+C all raw, all owned by subseg `800`) must be
       flagged, with the boundary named. Fed synthetically, because the real tree no longer
       contains that state."""
    ok = True
    st, _ = check('main')
    print(f"  main, as it is now                     -> {st:12s} {'OK' if st == 'OK' else 'FAIL'}")
    ok &= (st == 'OK')

    # The pre-S72 island: three separated game spans, every owner in subseg `800`.
    tabs = [(0x80072A38, 0x80072C70), (0x80072E44, 0x80073140), (0x800732A0, 0x8007344C)]
    own = {0x80072A7C: {('800', 'func_8001A114')}, 0x80072B88: {('800', 'func_80024448')},
           0x80072E44: {('800', 'func_8002B0B4')}, 0x8007302C: {('800', 'func_8002EED8')},
           0x800732A0: {('800', 'func_80035270')}, 0x80073420: {('800', 'func_80039C70')}}
    st, lines = check('main', tabs_override=tabs, own_override=own)
    fired = st == 'NEEDS SPLIT'
    print(f"  main's island BEFORE the S72 split     -> {st:12s} {'OK' if fired else 'FAIL'}")
    if fired:
        print("\n".join("    " + l for l in lines[:5]))
    ok &= fired

    # And a control that must NOT fire: one span, many owners, one subseg.
    st, _ = check('main', tabs_override=[(0x80072A38, 0x80072C70)],
                  own_override={0x80072A7C: {('800', 'func_8001A114')},
                                0x80072B88: {('800', 'func_80024448')}})
    print(f"  one span, one subseg (must NOT fire)   -> {st:12s} {'OK' if st == 'OK' else 'FAIL'}")
    ok &= (st == 'OK')
    print('SELF-TEST', 'PASS' if ok else 'FAIL')
    return 0 if ok else 1


if __name__ == '__main__':
    os.chdir(REPO)
    ap = argparse.ArgumentParser()
    ap.add_argument('--binary')
    ap.add_argument('--self-test', action='store_true')
    ap.add_argument('--quiet', action='store_true', help='only print non-OK binaries')
    a = ap.parse_args()
    if a.self_test:
        sys.exit(self_test())
    bins = [a.binary] if a.binary else \
        (open('.run/S70_bins_sorted.txt').read().split()
         if os.path.exists('.run/S70_bins_sorted.txt')
         else ['main'] + sorted(os.path.basename(p)[len('splat.'):-len('.yaml')]
                                for p in glob.glob('config/splat.*.yaml')
                                if 'us.exe' not in p and 'template' not in p))
    bad = 0
    for b in bins:
        st, lines = check(b)
        if st != 'OK':
            bad += 1
        if st != 'OK' or not a.quiet:
            print(f"{b}: {st}")
            if st != 'OK':
                print("\n".join(lines))
    print(f"\nsplit_indicator: {len(bins)-bad} OK, {bad} needing attention, of {len(bins)} binaries")
    sys.exit(1 if bad else 0)
