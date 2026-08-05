#!/usr/bin/env python3
"""S2 — sweep the has_mid_jr MATCHED-EXEMPLAR families via the carve path (jtbl_family_bank).

WHY THIS EXISTS SEPARATELY FROM family_sweep --hseq:
`family_sweep --hseq` REFUSES has_mid_jr families by design (§53 interlock). That refusal is
correct — their exemplars only banked because a jump-table carve preceded the splice, and a 0% from
the carve-less path is a TOOL ARTIFACT, which is exactly what manufactured the Phase-26 "structural
families ~0%" doctrine and steered two phases of strategy. So the families the interlock skips are
not dead; they are simply addressed to a different tool. This driver is that tool's front end.

DERIVED, NOT TRANSCRIBED (§138 rule 4 + R33):
 - the family set = every manifest family with has_mid_jr AND a matched exemplar;
 - the members = those still in corpus.stubs (the map's `members` list is unmatched-only, but a
   member can be banked between a map regen and this run, so re-check);
 - NB a JUST-BANKED head leaves `members` and becomes `exemplar.kind='matched'` — that is why the
   family is looked up by its EXEMPLAR, not by scanning member lists.

--raw is passed because these exemplars banked through harvest_verify's post-carve reconcile, i.e.
at the `reconciled` stage, and a reconciled body is TU-specific (§41c: uniquified type names,
TU-targeted casts). extract_unit would hand the sweep a polluted template and every sibling would
gate-fail. jtbl_family_bank's own docstring records this (func_80178D40: 0/4 until --raw).

COMMITS PER FAMILY because jtbl_family_bank REFUSES a dirty tree — correctly: its per-sibling revert
restores from HEAD, so an uncommitted prior family would be destroyed by the next family's first
failure. R22 runs once over the whole batch afterwards.

Usage: jr_family_sweep.py [--dry] [--limit N] [--raw-dir DIR]
"""
import sys, os, json, glob, subprocess
sys.path.insert(0, 'tools')
import corpus

DRY   = '--dry' in sys.argv
LIMIT = int(sys.argv[sys.argv.index('--limit') + 1]) if '--limit' in sys.argv else None
RAWD  = sys.argv[sys.argv.index('--raw-dir') + 1] if '--raw-dir' in sys.argv else '.run/w6'

WALLS    = {0x801412a8, 0x80178004, 0x80144b9c}
LEDGERED = {0x8017c294, 0x8017f7b4, 0x801898e4, 0x80186e24, 0x801758fc, 0x80132018, 0x8018a808}

fam = json.load(open('.run/family_hseq.json'))['families']
_sc = {}
def stubs(ov):
    if ov not in _sc:
        try: _sc[ov] = corpus.stubs(ov)
        except Exception: _sc[ov] = {}
    return _sc[ov]

targets = []
for f in fam:
    if not f.get('has_mid_jr') or f['exemplar'].get('kind') not in ('matched', 'matched-ov077'):
        continue
    ex_ov, ex_addr = f['exemplar']['ov'], int(f['exemplar']['addr'], 16)
    if ex_addr in WALLS | LEDGERED:
        continue
    members = [[ov, hex(int(a, 16))] for ov, a in f['members']
               if int(a, 16) in stubs(ov) and (ov, int(a, 16)) != (ex_ov, ex_addr)]
    if not members:
        continue
    targets.append((f['nins'] * len(members), f, ex_ov, ex_addr, members))

targets.sort(key=lambda t: -t[0])
if LIMIT:
    targets = targets[:LIMIT]

print(f"{'exemplar':>12} {'overlay':<14} {'nins':>5} {'open':>5} {'templ ins':>10}  raw-seed")
tot = 0
for ti, f, ex_ov, ex_addr, members in targets:
    raw = os.path.join(RAWD, ex_ov, f'func_{ex_addr:08X}.c')
    print(f"  0x{ex_addr:08x} {ex_ov:<14} {f['nins']:>5} {len(members):>5} {ti:>10,}  "
          f"{'yes' if os.path.exists(raw) else 'NO (uses banked unit)'}")
    tot += ti
print(f"\nTOTAL: {len(targets)} jr matched-exemplar families / {tot:,} open templatable ins")
if DRY:
    sys.exit(0)

os.makedirs('.run/jrprop', exist_ok=True)
for ti, f, ex_ov, ex_addr, members in targets:
    fn = f'func_{ex_addr:08X}'
    mf = f'.run/jrprop/{fn}_members.json'
    json.dump(members, open(mf, 'w'))
    cmd = ['.venv/bin/python', 'tools/jtbl_family_bank.py', fn, ex_ov, hex(ex_addr), mf]
    raw = os.path.join(RAWD, ex_ov, f'{fn}.c')
    if os.path.exists(raw):
        cmd += ['--raw', raw]
    print(f"\n== {fn} ({f['nins']} ins x {len(members)} open) ==", flush=True)
    r = subprocess.run(cmd, capture_output=True, text=True)
    out = (r.stdout or '') + (r.stderr or '')
    open(f'.run/jrprop/{fn}.log', 'w').write(out)
    for l in [x for x in out.strip().splitlines() if x.strip()][-3:]:
        print('   ', l[:170])
    dirty = subprocess.run(['git', 'status', '--porcelain', '--', 'src', 'config'],
                           capture_output=True, text=True).stdout.strip()
    if dirty:
        subprocess.run(['git', 'add', '-A', 'src', 'config'], check=True)
        subprocess.run(['git', 'commit', '-q', '-F', '-'], text=True, check=True, input=(
            f"feat(phase-30 S38/S2): jr-family sweep — {fn} x{len(members)} sibling slots\n\n"
            f"jtbl_family_bank (the §53 carve path; family_sweep --hseq refuses has_mid_jr families\n"
            f"BY DESIGN — a 0% from the carve-less tool is an artifact, not a wall). Each sibling\n"
            f"individually byte-gated: carve -> extract -> remap -> whole-binary build, kept iff\n"
            f"byte-identical else reverted. Committed per family because jtbl_family_bank requires a\n"
            f"clean tree between families. R22 clean-fleet runs once over the batch.\n"))
        print(f"    committed ({len(dirty.splitlines())} paths)")
print("\nDONE — now run R22: make clean && make extract-all && make check-all")
