#!/usr/bin/env python3
"""tools/t5_distill_args.py — build the R16 distill slate for a Claude wave (P31 S63 T5).

Usage: t5_distill_args.py --wave .run/t5a --wfdir <dir> [--wave .run/t5b --wfdir <dir> ...]
                          [--label 'P31 S63'] [--all-arms] [--out <path>]
--wave/--wfdir may be repeated and are paired POSITIONALLY (the Nth wave with the Nth wfdir), so one
distill run can cover several waves; the slates are concatenated and de-duplicated by (binary, fn).

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
    ap.add_argument('--wave', required=True, action='append',
                    help='wave dir; repeatable, paired positionally with --wfdir')
    ap.add_argument('--wfdir', required=True, action='append',
                    help="the drafting run's transcript dir (holds journal.jsonl + agent-*.jsonl); repeatable")
    ap.add_argument('--label', default='', help="provenance string for the cookbook header, e.g. 'P31 S63 t5a'")
    ap.add_argument('--all-arms', action='store_true')
    ap.add_argument('--novel-only', action='store_true',
                    help="select only transcripts whose agent NOTE carries a novelty signal (says the "
                         "cookbook lacks the lever, or names a lever/negative result). The t5a run measured "
                         "the base rate: 34 distilled -> 16 trivial, 5 novelty claims -> 1 ADDENDUM, so "
                         "distilling every banked transcript spends ~30x the tokens for the same book. "
                         "The FULL denominator is always printed (R41); this filter is reported, not hidden.")
    ap.add_argument('--out', default='')
    a = ap.parse_args()
    if len(a.wave) != len(a.wfdir):
        sys.exit('REFUSED: %d --wave but %d --wfdir; they pair positionally' % (len(a.wave), len(a.wfdir)))
    out, missing, seen, tot_banked, tot_union = [], [], set(), 0, 0
    for wave, wfdir in zip(a.wave, a.wfdir):
        jp = os.path.join(wave, 'judge.json')
        if not os.path.exists(jp):
            print('SKIP %s: no judge.json (wave not gated yet)' % wave); continue
        jd = json.load(open(jp))
        banked_by_arm = {arm: set(v.get('banked', [])) for arm, v in jd.get('arms', {}).items()}
        banked = set().union(*banked_by_arm.values()) if banked_by_arm else set()
        union = set(jd.get('union', {}).get('banked', []))
        picked = jd.get('union', {}).get('picked', {})
        tot_banked += len(banked); tot_union += len(union)
        T = {t['name']: t for t in json.load(open(os.path.join(wave, 'targets.json')))}
        jl = os.path.join(wfdir, 'journal.jsonl')
        if not os.path.exists(jl):
            sys.exit('no journal.jsonl in %s' % wfdir)
        tr = {}
        for line in open(jl):
            if '"result"' not in line: continue
            r = json.loads(line); res = r.get('result') or {}
            if isinstance(res, dict) and res.get('fn'):
                tr[(res['fn'], res.get('arm'))] = (os.path.join(wfdir, 'agent-%s.jsonl' % r['agentId']), res.get('note', ''))
        for fn in sorted(banked):
            arms = sorted(banked_by_arm) if a.all_arms else [picked.get(fn) or next(x for x in banked_by_arm if fn in banked_by_arm[x])]
            for arm in arms:
                if fn not in banked_by_arm.get(arm, ()): continue
                key = (T.get(fn, {}).get('binary', '?'), fn, arm)
                if key in seen: continue          # the same fn can be drawn by two waves (R48: key by binary too)
                seen.add(key)
                hit = tr.get((fn, arm))
                if not hit or not os.path.exists(hit[0]):
                    missing.append('%s/%s/%s' % (os.path.basename(wave), arm, fn)); continue
                out.append({'fn': fn, 'arm': arm, 'transcript': hit[0], 'note': hit[1]})
    NOVEL = ('not in the cookbook', 'not in cookbook', 'cookbook did not have', "cookbook does not",
             'NEW IDIOM', 'NEW:', 'NEW fact', 'the cookbook does not cover', 'does not yet cover',
             'negative result', 'addendum', 'Cookbook-worthy', 'no cookbook lever', 'unlocked it')
    n_all = len(out)
    if a.novel_only:
        out = [r for r in out if any(k.lower() in (r['note'] or '').lower() for k in NOVEL)]
    print('waves %d; banked %d (union-gated %d); transcripts found %d; selected %d%s; label %r'
          % (len(a.wave), tot_banked, tot_union, n_all, len(out),
             ' by novelty signal (%d NOT distilled — no signal in their note)' % (n_all - len(out)) if a.novel_only else '',
             a.label))
    if missing:
        print('NO TRANSCRIPT for %d banked draft(s) — NOT distilled (R32, reported not skipped): %s'
              % (len(missing), ' '.join(missing[:20])))
    p = a.out or os.path.join(a.wave[0], 'distill_args.json')
    json.dump({'targets': out, 'label': a.label or os.path.basename(a.wave[0].rstrip('/'))}, open(p, 'w'), indent=1)
    print('wrote %s' % p)
if __name__ == '__main__':
    main()
