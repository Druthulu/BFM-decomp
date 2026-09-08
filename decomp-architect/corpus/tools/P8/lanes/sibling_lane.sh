#!/usr/bin/env bash
# The FREE sibling lane, via the tool that SYNTHESIZES declarations instead of carrying them.
#
# family_sweep --hseq templates the seed's whole declaration layer into the destination TU, and
# decl-agreement is its dominant failure: 331 of 458 verdicts in S49's ledger, and 14/14 PLUMBING
# on the P31 S58 probe (`conflicting types for func_8018A8E8` — the BODY was correct).
# aprop_autodraft emits one extern per referenced symbol and only the typedefs the body actually
# names. Measured this morning: 390 banked of 511 gated (76%), zero model tokens.
set -u
cd /home/musashi/bfm-decomp
say(){ echo "[$(date +%H:%M:%S)] $*"; }
say "1/3 regenerate A-prop cards (stale by ~1,700 banks; each new exemplar creates new PURE seeds)"
.venv/bin/python tools/family_cousins.py --aprop-cards 2>&1 | tail -2
say "2/3 aprop_autodraft — mechanical drafts, no model"
.venv/bin/python tools/aprop_autodraft.py --outdir .run/aprop_s58b --slate .run/aprop_s58b_slate.json 2>&1 | tail -3
say "3/3 reloc_identity pre-filter"
.venv/bin/python - <<'PY'
import json
s=json.load(open('.run/aprop_s58b_slate.json'))
json.dump([{'fn':r['fn'],'binary':r['binary'],'draft':r['draft']} for r in s],
          open('.run/reloc_aprop_s58b.json','w'), indent=1)
print(len(s),'drafts')
PY
.venv/bin/python tools/reloc_identity.py --batch .run/reloc_aprop_s58b.json -j 12 --out .run/reloc_aprop_s58b.out.json 2>&1 | tail -2
say "SIBLING LANE DRAFTS READY (gate them when the gater is free)"
