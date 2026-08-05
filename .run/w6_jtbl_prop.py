#!/usr/bin/env python3
"""Propagate wave-6's banked jr-family heads via the CARVE path (§53), not the h_seq sweep.

family_sweep --hseq refused these by design: they are `has_mid_jr` families, and its §53 interlock
says a 0% from the non-carve path would be a TOOL artifact rather than a wall — the exact confusion
that manufactured P28's false "B2 = 0/8" wall. The correct route is jtbl_family_bank, which carves
each sibling's jump table before templating.

Members are DERIVED (never transcribed): the family is the one whose member list contains the head,
and the targets are the members that are STILL STUBS per corpus.stubs, minus the head itself.

--raw is passed deliberately: these heads banked through harvest_verify._jtbl_reconcile, i.e. at the
`reconciled` stage, and a reconciled body is TU-specific (§41c — uniquified type names, TU-targeted
casts). extract_unit would hand the sweep a polluted template and every sibling would gate-fail.
The raw crack is the wave draft.
"""
import sys, os, json, subprocess
sys.path.insert(0, 'tools')
import corpus

ALL_HEADS = [   # (overlay, addr) — the wave-6 heads family_sweep routed here
    ('ov_SC02_026', 0x8017FEE0), ('ov_SC03_111', 0x80181CE4), ('ov_SC03_112', 0x80183AE0),
    ('ov_SC06_018', 0x80184C74), ('ov_SC02_000', 0x8017EA84),
]
# jtbl_family_bank REFUSES to start on a dirty tree — correctly: its per-sibling revert restores
# from HEAD, so an uncommitted prior family would be destroyed by the next family's first failure.
# So the driver COMMITS after every family that banks anything. (First run: family 1 banked 15 and
# the remaining four all refused, which is the guard doing its job, not four failures.)
sel = [h for h in sys.argv[1:] if h.startswith('0x')]
HEADS = [h for h in ALL_HEADS if not sel or hex(h[1]) in [s.lower() for s in sel]]

fam = json.load(open('.run/family_hseq.json'))['families']
stub_cache = {}
def stubs(ov):
    if ov not in stub_cache:
        try: stub_cache[ov] = corpus.stubs(ov)
        except Exception: stub_cache[ov] = {}
    return stub_cache[ov]

os.makedirs('.run/w6prop', exist_ok=True)
summary = []
for ov, addr in HEADS:
    fn = f'func_{addr:08X}'
    # A JUST-BANKED head is NOT in its family's `members` list — the map moves it OUT of members
    # and INTO `exemplar` with kind="matched". Searching the member list therefore finds nothing
    # (my first pass reported "NO FAMILY" for all 5 heads while family_sweep had just enumerated
    # those same families from the same file). Key on the exemplar (ov, addr) PAIR — two families
    # can share an exemplar address in different overlays.
    #   NB this does not contradict §138 rule 4 ("never rank off the exemplar field"): that rule is
    #   about TARGET SELECTION, where an exemplar pointing at an already-banked instance HIDES a
    #   family. Here the freshly-banked exemplar is exactly what we are looking the family up BY.
    match = [f for f in fam
             if f['exemplar']['ov'] == ov and int(f['exemplar']['addr'], 16) == addr
             and f['exemplar'].get('kind') == 'matched']
    if not match:
        print(f"== {fn}: no matched-exemplar family in the map — skipping"); continue
    f0 = max(match, key=lambda f: f['n_members'])
    members = []
    for mov, maddr_s in f0['members']:
        maddr = int(maddr_s, 16)
        if (mov, maddr) == (ov, addr):
            continue
        if maddr in stubs(mov):
            members.append([mov, hex(maddr)])
    print(f"== {fn} ({f0['nins']} ins, family n={f0['n_members']}): {len(members)} OPEN sibling(s)")
    if not members:
        summary.append((fn, 0, 0)); continue
    mf = f'.run/w6prop/{fn}_members.json'
    json.dump(members, open(mf, 'w'))
    raw = f'.run/w6/{ov}/{fn}.c'
    r = subprocess.run(['.venv/bin/python', 'tools/jtbl_family_bank.py', fn, ov, hex(addr), mf,
                        '--raw', raw], capture_output=True, text=True)
    out = (r.stdout or '') + (r.stderr or '')
    open(f'.run/w6prop/{fn}.log', 'w').write(out)
    tail = [l for l in out.strip().splitlines() if l.strip()][-4:]
    for l in tail:
        print('   ', l[:160])
    # Commit iff this family actually changed tracked state, so the NEXT family sees a clean tree.
    dirty = subprocess.run(['git', 'status', '--porcelain', '--', 'src', 'config'],
                           capture_output=True, text=True).stdout.strip()
    if dirty:
        subprocess.run(['git', 'add', '-A', 'src', 'config'], check=True)
        msg = (f"feat(phase-30 S38): wave-6 propagation — {fn} x{len(members)} sibling slots\n\n"
               f"jtbl_family_bank (the §53 carve path; family_sweep --hseq refuses has_mid_jr\n"
               f"families by design). Each sibling individually byte-gated: carve -> extract ->\n"
               f"remap -> whole-binary build, kept iff byte-identical else reverted. Committed here\n"
               f"because jtbl_family_bank requires a clean tree between families (its per-sibling\n"
               f"revert restores from HEAD). R22 clean-fleet runs once over the whole batch.\n")
        subprocess.run(['git', 'commit', '-q', '-F', '-'], input=msg, text=True, check=True)
        print(f"    committed ({len(dirty.splitlines())} paths)")
    summary.append((fn, len(members), r.returncode))

print("\n=== SUMMARY (the gate log is the arbiter — see .run/w6prop/*.log) ===")
for fn, n, rc in summary:
    print(f"  {fn}: {n} open sibling(s), jtbl_family_bank rc={rc}")
