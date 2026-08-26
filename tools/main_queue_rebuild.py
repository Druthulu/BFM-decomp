#!/usr/bin/env python3
"""tools/main_queue_rebuild.py — rebuild .run/main_queue_live.json from the tree, never from a stale list.

WHY (P31 S62 T5pre; frontier-analysis-s61 §2.B / §5): the main lane's queue file had 166 entries of
which 156 were already banked — a lane that "gates" a stale queue looks busy and banks nothing (the R32
silently-narrowed-scope class). The open set is DERIVED (R33) from tools/progress.py's classify(): main's
INCLUDE_ASM lines minus the 959 LINKED PsyQ objects, the data blobs and dead lines, plus the 3 NON_MATCHING
promotions. Each open fn gets its NEWEST draft on disk (the queue, ds2 shards, backlog_drafts, any wave
shard); fns without a draft are listed so the next main wave targets exactly them (R41: every count with
its denominator).

Usage: tools/main_queue_rebuild.py [--write]      (default: report only)
"""
import sys, os, glob, json, time
sys.path.insert(0, 'tools')
import progress as P

def newest_draft(fn):
    cands = []
    for pat in ('.run/wave_ds2/shard*/%s.c', '.run/backlog_drafts/%s.c', '.run/wave_*/shard*/%s.c',
                '.run/sweep_resolver/main/%s.c', '.run/stage_main/*/%s.c'):
        cands += glob.glob(pat % fn)
    cands = [c for c in cands if os.path.getsize(c) > 0]
    return max(cands, key=os.path.getmtime) if cands else None

def main():
    write = '--write' in sys.argv[1:]
    P.set_binary('main')
    real, empty, nm, stubs, blobs, linked = P.classify()
    open_fns = sorted(set(stubs)) ; nm_fns = sorted(set(nm))
    old = []
    try:
        old = json.load(open('.run/main_queue_live.json'))
    except Exception:
        pass
    old_by = {e['fn']: e['draft'] for e in old if isinstance(e, dict)}
    queue, nodraft = [], []
    for fn in open_fns + nm_fns:
        d = newest_draft(fn)
        if d is None and old_by.get(fn) and os.path.exists(old_by[fn]):
            d = old_by[fn]
        if d:
            queue.append({'fn': fn, 'draft': d, 'binary': 'main'})
        else:
            nodraft.append(fn)
    stale_old = sum(1 for e in old if isinstance(e, dict) and e.get('fn') not in set(open_fns + nm_fns))
    print('main honest open set: %d stubs + %d NON_MATCHING = %d  (LINKED %d, blobs %d, real %d excluded)'
          % (len(open_fns), len(nm_fns), len(open_fns) + len(nm_fns), len(linked), len(blobs), len(real)))
    print('old queue: %d entries, %d stale (already banked)' % (len(old), stale_old))
    print('new queue: %d with a draft on disk; %d open fns have NO draft anywhere -> the main wave targets'
          % (len(queue), len(nodraft)))
    if write:
        if old:
            os.replace('.run/main_queue_live.json', '.run/main_queue_live.%s.bak' % time.strftime('%Y%m%d-%H%M%S'))
        json.dump(queue, open('.run/main_queue_live.json', 'w'), indent=1)
        json.dump(nodraft, open('.run/main_nodraft.json', 'w'), indent=1)
        print('wrote .run/main_queue_live.json (%d) + .run/main_nodraft.json (%d)' % (len(queue), len(nodraft)))

if __name__ == '__main__':
    main()
