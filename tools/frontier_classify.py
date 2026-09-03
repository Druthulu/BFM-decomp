#!/usr/bin/env python3
"""frontier_classify.py — classify EVERY remaining open stub by its TRUE BLOCKER, deterministically.

WHY THIS EXISTS (P31 S75). "69 functions left" is a count of stubs, not a measure of difficulty, and
this session proved the difference is enormous: five functions carried as a five-session "codegen
wall" were one jump-table extent bug, and `ov_SC03_108:func_8016AE5C` -- logged as
"match_one MATCH but the whole-binary gate rejected -- CAUSE NOT DETERMINED" -- banked with a
byte-perfect body the moment the carve was fixed. A frontier list that does not name the BLOCKER
routes drafting agents at problems that are not drafting problems.

Everything here is computed from artifacts already on disk (R33 / offline-tooling-first): the .s,
the sig registries, the backlog, the corpus. Zero tokens, no agents, no builds.

    tools/frontier_classify.py [--json out.json]
"""
import argparse, collections, glob, importlib.util, json, os, re, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, 'tools'))

def _load(m, rel):
    s = importlib.util.spec_from_file_location(m, os.path.join(REPO, rel))
    x = importlib.util.module_from_spec(s); sys.modules[m] = x; s.loader.exec_module(x); return x

LINKED = set('apicard1 apicard2 apicard3 apicard4 libc2_1 libc2_2 libcd1 libcd2 libetc libgpu '
             'libgs1 libgs2 libgs3 libgs4 libgs5 libgs6 libgte1 libgte10 libgte11 libgte12 libgte13 '
             'libgte14 libgte15 libgte16 libgte17 libgte18 libgte19 libgte2 libgte20 libgte21 '
             'libgte22 libgte3 libgte4 libgte5 libgte6 libgte7 libgte8 libgte9 libmcrd1 libmcrd2 '
             'snd1 snd2 snd3 snd4 snd5 snd6 snd7 snd8 snd9'.split())
INS = re.compile(r'\s*/\* [0-9A-F]+ [0-9A-F]{8} ')



def fleet_binaries():
    """The REAL fleet, derived from the Makefile + the two .mk lists (R33 — never a hardcoded list)."""
    out = {'main', 'resident'}
    for f, var in (('config/overlays.mk', 'OVERLAY_BINARIES'), ('config/modules.mk', 'MODULE_BINARIES')):
        p = os.path.join(REPO, f)
        if os.path.exists(p):
            m = re.search(rf'^{var}\s*:=\s*(.*)$', open(p).read(), re.M)
            if m:
                out |= set(m.group(1).split())
    return out


def open_stubs():
    """[(fn, binary, path, asm_path, nins)] for every live non-LINKED INCLUDE_ASM stub."""
    out = []
    for root, _d, files in os.walk(os.path.join(REPO, 'src')):
        for f in files:
            if not f.endswith('.c') or f[:-2] in LINKED:
                continue
            p = os.path.join(root, f)
            rel = os.path.relpath(root, os.path.join(REPO, 'src'))
            binary = 'main' if rel == '.' else rel
            for line in open(p, errors='ignore'):
                m = re.match(r'\s*INCLUDE_ASM\("([^"]+)",\s*(\w+)', line)
                if not m:
                    continue
                a = os.path.join(REPO, m.group(1), m.group(2) + '.s')
                n = sum(1 for l in open(a, errors='ignore') if INS.match(l)) if os.path.exists(a) else 0
                out.append((m.group(2), binary, os.path.relpath(p, REPO), a, n))
    return out


def asm_facts(asm_path):
    """Structural tells read straight from the function's own .s."""
    if not os.path.exists(asm_path):
        return {}
    txt = open(asm_path, errors='ignore').read()
    return {
        'jtbl':  bool(re.search(r'\bjtbl_[0-9A-Fa-f]{8}\b', txt)),   # owns a switch jump table
        'jr':    bool(re.search(r'\bjr\s+\$(?!ra)', txt)),           # indirect jump (dispatch)
        'jalr':  bool(re.search(r'\bjalr\b', txt)),                  # indirect call
        'mult':  bool(re.search(r'\b(mult|multu|div|divu)\b', txt)),
        'float': bool(re.search(r'\b(cop2|mtc2|mfc2|ctc2|cfc2)\b', txt)),
        'calls': len(re.findall(r'\bjal\s+\w', txt)),
    }


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--json', default=None)
    a = ap.parse_args()

    corpus = _load('corpus', 'tools/corpus.py')
    stubs = open_stubs()

    # ---- evidence layers, all pre-existing artifacts -------------------------------------------
    close, verdict, draft = {}, {}, {}
    bl = os.path.join(REPO, '.run/backlog.jsonl')
    if os.path.exists(bl):
        for ln in open(bl):
            try: r = json.loads(ln)
            except Exception: continue
            n = r.get('name')
            if not n: continue
            if r.get('closeness') is not None: close[n] = r['closeness']
            if r.get('where_stuck'): verdict[n] = r['where_stuck']
            if r.get('best_draft'): draft[n] = r['best_draft']
    for p in glob.glob(os.path.join(REPO, '.run/harvest_failed.*.classified.txt')):
        for ln in open(p):
            q = ln.rstrip('\n').split('\t')
            if len(q) >= 2 and q[0] not in verdict:
                verdict[q[0]] = q[1]

    # h_exact reach: is this function byte-identical to code in another binary? (a twin is a REMAP,
    # never a redraft -- §168) and is any twin already MATCHED (i.e. is there a proven exemplar)?
    #
    # THE SIG DIRECTORY IS NOT THE FLEET (P31 S75 — caught by the known-true check, R14). Alongside
    # the 213 real binaries `.run/` also holds `SLUS_007.26` (a STALE duplicate of main under the ROM
    # filename), `resident_image`, and two CROSS-BUILD binaries — `sep8_SLUS_007.26` and
    # `aug31_USA_DEMO.EXE`. Counting those as peers made every main stub look like it had a
    # byte-identical twin ALREADY BANKED somewhere: 38 functions / 7,516 instructions of pure
    # artifact, most of them "proven" in main ITSELF under its other name, the rest in a PROTOTYPE
    # that R13 forbids as verified evidence. Derive the fleet from the Makefile and refuse the rest.
    fleet = fleet_binaries()
    seen_sigs = {os.path.basename(q)[4:-6] for q in glob.glob(os.path.join(REPO, '.run/sig.*.jsonl'))}
    dropped = sorted(seen_sigs - fleet)
    if dropped:
        print(f"[classify] IGNORING {len(dropped)} non-fleet sig registr(ies) as twin evidence: "
              f"{', '.join(dropped)}", file=sys.stderr)
    if not fleet:
        sys.exit("frontier_classify: could not derive BINARIES from the Makefile — refusing to "
                 "classify against an unknown fleet (R32)")
    sig, banked_addrs = {}, set()
    for p in glob.glob(os.path.join(REPO, '.run/sig.*.jsonl')):
        b = os.path.basename(p)[4:-6]
        if b not in fleet:
            continue
        for ln in open(p):
            try: r = json.loads(ln)
            except Exception: continue
            sig.setdefault(int(r['addr'], 16), []).append((b, r.get('h_exact')))
    open_pairs = {(f, b) for f, b, _p, _a, _n in stubs}
    for addr, rows in sig.items():
        for b, _h in rows:
            if (f'func_{addr:08X}', b) not in open_pairs:
                banked_addrs.add((addr, b))

    # Any stored draft on disk, anywhere under .run — ONE pruned walk, not a `.run/S7*` glob.
    #
    # The glob was `.run/S7*/**/*.c`, which is NARROWER THAN THE CLAIM IT SUPPORTED (P31 S75, R32 —
    # the session's recurring defect, committed by me in the very tool written to classify it). Real
    # drafts live in `.run/S69m2/`, `.run/S68m1/`, `.run/s67m1/` (lowercase), `.run/wave_ds2/`,
    # `.run/gate_lane/`, `.run/backlog_drafts/` — none of which match `S7*`. Result: all 32 drafted
    # main functions were classified H-VIRGIN ("never drafted -- genuine new drafting work"), which
    # would have sent agents to redraft 6,328 instructions that already have drafts sitting on disk.
    # The worktrees are pruned because they are full repo copies (7.4 GB) of the SAME sources.
    disk_drafts = collections.defaultdict(list)
    for dp, dn, fns in os.walk(os.path.join(REPO, '.run')):
        dn[:] = [d for d in dn if d != '.git' and not d.startswith('wt_')
                 and d not in ('pgate', 'obj40', 'audit')]
        for f in fns:
            if f.endswith('.c'):
                disk_drafts[f[:-2]].append(os.path.join(dp, f))

    rows = []
    for fn, binary, path, asm, nins in stubs:
        try: addr = int(fn[5:], 16)
        except ValueError: addr = None
        f = asm_facts(asm)
        h = None; twins = []
        if addr in sig:
            me = [x for x in sig[addr] if x[0] == binary]
            h = me[0][1] if me else None
            if h:
                twins = [b for b, hh in sig[addr] if hh == h and b != binary]
        proven_twin = [b for b in twins if (addr, b) in banked_addrs]
        c = close.get(fn)
        v = (verdict.get(fn) or '')
        o0 = False
        try: o0 = bool(corpus.is_o0(binary, addr)) if addr else False
        except Exception: pass

        # ---- the blocker ladder: most specific evidence first ----------------------------------
        if proven_twin:
            k = 'A-TWIN-REMAP'          # a byte-identical copy is ALREADY BANKED elsewhere
        elif f.get('jtbl'):
            k = 'B-CARVE'               # owns a switch table -> the S75 carve class
        elif c == 0:
            k = 'C-PLUMBING'            # body proven, TU refuses it
        elif c is not None and c <= 25:
            k = 'D-NEAR'                # permuter fuel, not drafting
        elif o0:
            k = 'E-O0'                  # -O0 island
        elif c is not None and c <= 150:
            k = 'F-FAR'                 # a draft exists but is materially wrong
        elif fn in disk_drafts or fn in draft:
            k = 'G-DRAFTED-UNKNOWN'     # tried, no usable verdict recorded
        else:
            k = 'H-VIRGIN'              # never drafted: genuine new work
        rows.append(dict(fn=fn, binary=binary, nins=nins, klass=k, closeness=c,
                         jtbl=f.get('jtbl'), jr=f.get('jr'), jalr=f.get('jalr'), o0=o0,
                         calls=f.get('calls'), twins=len(twins), proven_twin=proven_twin[:3],
                         drafts=len(disk_drafts.get(fn, [])), verdict=v[:90], path=path))

    rows.sort(key=lambda r: (r['klass'], -r['nins']))
    by = collections.defaultdict(list)
    for r in rows: by[r['klass']].append(r)
    NAME = {
        'A-TWIN-REMAP':     'a byte-identical copy is ALREADY BANKED elsewhere -> mechanical remap',
        'B-CARVE':          'owns a switch jump table -> the S75 jtbl_carve class',
        'C-PLUMBING':       'closeness 0: body proven, the TU refuses the signature',
        'D-NEAR':           'closeness <=25 -> permuter fuel, NOT drafting',
        'E-O0':             '-O0 island',
        'F-FAR':            'a draft exists but is materially wrong -> redraft',
        'G-DRAFTED-UNKNOWN':'drafted before, no usable verdict on record',
        'H-VIRGIN':         'never drafted -- genuine new drafting work',
    }
    tot_n = sum(r['nins'] for r in rows)
    print(f"OPEN STUBS: {len(rows)}  ({len({r['fn'] for r in rows})} distinct)  {tot_n:,} instructions\n")
    print(f"{'class':20s} {'fns':>4s} {'ins':>7s}  what it actually needs")
    print('-' * 100)
    for k in sorted(by):
        g = by[k]
        print(f"{k:20s} {len(g):4d} {sum(x['nins'] for x in g):7,d}  {NAME[k]}")
    print('-' * 100)
    print(f"{'TOTAL':20s} {len(rows):4d} {tot_n:7,d}")
    for k in sorted(by):
        print(f"\n== {k} — {NAME[k]}")
        for r in by[k]:
            extra = []
            if r['closeness'] is not None: extra.append(f"close={r['closeness']}")
            if r['jtbl']: extra.append('jtbl')
            if r['jr']: extra.append('jr')
            if r['o0']: extra.append('-O0')
            if r['twins']: extra.append(f"twins={r['twins']}")
            if r['proven_twin']: extra.append(f"proven@{','.join(r['proven_twin'])}")
            if r['drafts']: extra.append(f"drafts={r['drafts']}")
            print(f"   {r['nins']:5d}  {r['fn']:20s} {r['binary']:14s} {' '.join(extra)}")
            if r['verdict']: print(f"          verdict: {r['verdict']}")
    if a.json:
        json.dump(rows, open(a.json, 'w'), indent=1)
        print(f"\n-> {a.json}")


if __name__ == '__main__':
    main()
