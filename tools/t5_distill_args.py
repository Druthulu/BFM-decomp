#!/usr/bin/env python3
"""tools/t5_distill_args.py — build the R16 distill slate for a Claude wave (P31 S63 T5).

Usage: t5_distill_args.py --wave .run/t5a --wfdir <workflow transcript dir> [--label 'P31 S63 t5a'] [--all-arms]

Only BYTE-PROVEN transcripts are distilled (the distiller's contract: "the whole-binary byte-gate
ACCEPTED the final draft, so the final body is ground truth"), so the slate = the wave's banked set
from `<wave>/judge.json`, joined to the drafting agents' transcripts via the workflow's
`journal.jsonl` (result rows carry fn/arm/note; the transcript is `agent-<agentId>.jsonl`).
By default only the arm that BANKED each fn is distilled (--all-arms keeps every arm's attempt).
Coverage is asserted (R32): a banked fn with no transcript is reported and counted, never skipped
silently. Writes <wave>/distill_args.json for
  Workflow(scriptPath=tools/workflows/claude_wave_distill.js, args=<that file's content>)."""
import argparse, json, os, sys
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__))); os.chdir(REPO)

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--wave', required=True)
    ap.add_argument('--wfdir', required=True, help="the drafting run's transcript dir (holds journal.jsonl + agent-*.jsonl)")
    ap.add_argument('--label', default='', help="provenance string for the cookbook header, e.g. 'P31 S63 t5a'")
    ap.add_argument('--all-arms', action='store_true')
    ap.add_argument('--out', default='')
    a = ap.parse_args()
    jd = json.load(open(os.path.join(a.wave, 'judge.json')))
    banked_by_arm = {arm: set(v.get('banked', [])) for arm, v in jd.get('arms', {}).items()}
    banked = set().union(*banked_by_arm.values()) if banked_by_arm else set()
    union = set(jd.get('union', {}).get('banked', []))
    picked = jd.get('union', {}).get('picked', {})
    jp = os.path.join(a.wfdir, 'journal.jsonl')
    if not os.path.exists(jp): sys.exit('no journal.jsonl in %s' % a.wfdir)
    rows = [json.loads(l) for l in open(jp) if l.strip()]
    tr = {}
    for r in rows:
        res = r.get('result') or {}
        if isinstance(res, dict) and res.get('fn'):
            tr[(res['fn'], res.get('arm'))] = (os.path.join(a.wfdir, 'agent-%s.jsonl' % r['agentId']), res.get('note', ''))
    out, missing = [], []
    for fn in sorted(banked):
        arms = sorted(banked_by_arm) if a.all_arms else [picked.get(fn) or next(x for x in banked_by_arm if fn in banked_by_arm[x])]
        for arm in arms:
            if fn not in banked_by_arm.get(arm, ()): continue
            hit = tr.get((fn, arm))
            if not hit or not os.path.exists(hit[0]): missing.append('%s/%s' % (arm, fn)); continue
            out.append({'fn': fn, 'arm': arm, 'transcript': hit[0], 'note': hit[1]})
    print('banked %d (union-gated %d); transcripts found %d; label %r' % (len(banked), len(union), len(out), a.label))
    if missing:
        print('NO TRANSCRIPT for %d banked draft(s) — NOT distilled (R32, reported not skipped): %s'
              % (len(missing), ' '.join(missing[:20])))
    p = a.out or os.path.join(a.wave, 'distill_args.json')
    json.dump({'targets': out, 'label': a.label or os.path.basename(a.wave.rstrip('/'))}, open(p, 'w'), indent=1)
    print('wrote %s' % p)
if __name__ == '__main__':
    main()
