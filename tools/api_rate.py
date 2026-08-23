#!/usr/bin/env python3
"""api_rate.py — read .run/api_rate.jsonl and report MEASURED request rate + 429 attribution.

Exists because a flush=True print into a block-buffered shard log makes "no 429s" and "the buffer
has not filled" indistinguishable (P31 S58). This reads the append-only telemetry instead.

  tools/api_rate.py [--window 60] [--path .run/api_rate.jsonl]
"""
import argparse, collections, json, os, sys, time

ap = argparse.ArgumentParser()
ap.add_argument('--window', type=int, default=60, help='trailing seconds for the live rate')
ap.add_argument('--path', default='.run/api_rate.jsonl')
a = ap.parse_args()

if not os.path.exists(a.path):
    sys.exit(f'no telemetry yet at {a.path}')
recs = []
for line in open(a.path):
    line = line.strip()
    if line:
        try: recs.append(json.loads(line))
        except json.JSONDecodeError: pass
if not recs:
    sys.exit('telemetry file is empty')

now = time.time()
posts = [r for r in recs if r.get('ev') == 'POST']
h429 = [r for r in recs if r.get('ev') == '429']
span = max(1e-9, posts[-1]['t'] - posts[0]['t']) if len(posts) > 1 else 0
win = [r for r in posts if now - r['t'] <= a.window]
win429 = [r for r in h429 if now - r['t'] <= a.window]

print(f'requests total   : {len(posts)}')
print(f'429s total       : {len(h429)}  ({100.0*len(h429)/max(1,len(posts)):.1f}% of requests)')
if span:
    print(f'mean rate        : {60.0*len(posts)/span:.1f} req/min over {span/60:.1f} min')
print(f'last {a.window}s        : {len(win)} req = {60.0*len(win)/a.window:.1f} req/min, {len(win429)} 429')
print(f'live workers     : {len({r["pid"] for r in win}) if win else 0} pids posting in the window')
if h429:
    print('\n429 attribution:')
    for k, v in collections.Counter(r.get('src', '?') for r in h429).most_common():
        print(f'  {v:5d}  {k}')
else:
    print('\n429 attribution: NONE RECORDED - no rate limit has been hit yet.')

per_min = collections.Counter(int(r['t'] // 60) for r in posts)
if per_min:
    print(f'\npeak observed    : {max(per_min.values())} req in one clock minute')
