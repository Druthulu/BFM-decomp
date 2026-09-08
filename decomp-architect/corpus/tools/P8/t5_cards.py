#!/usr/bin/env python3
"""tools/t5_cards.py — BUILD the card fuel for a wave's own targets (P31 S63 T5).

Usage: t5_cards.py --wave .run/t5b [--out <wave>/cards.json]

WHY (byte-measured, P31 S63 wave t5a). `claude_wave_packs.py` looked cards up by BARE FUNCTION NAME
across `.run/wave_*_cards.json`; overlays share names at equal addresses, so 48 of 48 t5a targets
(and 15 of T4's 20) got ANOTHER binary's card — wrong banked twin, wrong TU neighbours, wrong
declarations. Nine agents independently reported discarding it. Keying by (binary, fn) fixes the
mis-attribution but leaves K-class ("never touched") targets with NO fuel at all, and `_fuel()`
then emits nothing: no `tu_ref`, no `decl_prior`. Yet t5a's agents cracked function after function
by finding an already-banked sibling in their own TU BY HAND ("in-TU twin ~150 lines earlier",
"structural twin in the SAME TU") — which is exactly what `tu_ref` is (§194-E, 62% of targets).

So this builds the two computable fields for the target ITSELF, from the same oracle
`build_wave_atlas` uses (`tools/wave_card_fuel.py`, R33):
  tu_ref      already-banked functions in the target's OWN TU, ranked by symbols shared with the
              target's .s relocations
  decl_prior  the fleet's consensus signature for every symbol the .s references (§196) — kills
              the two-arity A/B compile §195-A proved the asm cannot answer
`seed_ref` (the cross-TU banked twin) needs the atlas knn and is NOT built here: a card with no
seed_ref makes `_fuel` say "no banked twin — derive from the .s", which is TRUE, where the old
name-keyed card pointed confidently at an unrelated function. Coverage is printed (R32/R41)."""
import argparse, json, os, sys
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__))); os.chdir(REPO)
sys.path.insert(0, 'tools')
import wave_card_fuel as F
import decl_prior as DP
import seed_ref as SR

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--wave', required=True)
    ap.add_argument('--out', default='')
    a = ap.parse_args()
    targets = json.load(open(os.path.join(a.wave, 'targets.json')))
    idx = DP.load()
    cards, n_tu, n_dp, n_sr = [], 0, 0, 0
    for t in targets:
        tu = t.get('tu') or F.home_tu(t['binary'], t['name'])
        tu_ref = F.tu_neighbours(t['binary'], t['name'], tu, t['asm'])
        try:
            dp = DP.for_asm(t['asm'], tu, idx=idx, binary=t['binary'])
        except Exception as e:
            print('  decl_prior failed for %s/%s: %s' % (t['binary'], t['name'], str(e)[:80])); dp = []
        # seed_ref — THE CROSS-TU BANKED TWIN. Built from the signature hashes the corpus already
        # computes (NOT the atlas knn, which is why this was skipped before). Measured cost of not
        # having it: an opus agent spent 102,193 tokens re-deriving ov_SC03_107:func_8013DD68, whose
        # body is banked verbatim at the same address in ov_MAIN_012 — because the card asserted
        # "no banked twin". 87 open stubs fleet-wide have one; 41 of those sit in twin_sweep's
        # refusal ledger, so they are invisible to BOTH tools at once.
        try:
            sr = SR.for_stub(t['binary'], t['name'])
        except Exception as e:
            print('  seed_ref failed for %s/%s: %s' % (t['binary'], t['name'], str(e)[:80])); sr = None
        n_tu += bool(tu_ref); n_dp += bool(dp); n_sr += bool(sr)
        cards.append({'fn': t['name'], 'binary': t['binary'], 'addr': t.get('addr'), 'nins': t['nins'],
                      'sub': t['sub'], 'tu_ref': tu_ref, 'decl_prior': dp, 'seed_ref': sr})
    p = a.out or os.path.join(a.wave, 'cards.json')
    json.dump(cards, open(p, 'w'), indent=1)
    n_ref = sum(1 for c in cards if (c.get('seed_ref') or {}).get('mechanical_remap_refused'))
    print('cards: %d built for %s (tu_ref %d/%d = %.0f%%; decl_prior %d/%d = %.0f%%; '
          'seed_ref %d/%d = %.0f%%, of which %d were mechanically refused — copy the BODY, expect a '
          'declaration blocker)'
          % (len(cards), a.wave, n_tu, len(targets), 100.0 * n_tu / max(1, len(targets)),
             n_dp, len(targets), 100.0 * n_dp / max(1, len(targets)),
             n_sr, len(targets), 100.0 * n_sr / max(1, len(targets)), n_ref))
    print('wrote %s' % p)
if __name__ == '__main__':
    main()
