#!/usr/bin/env python3
"""tools/wave_args.py — emit the EXACT Workflow args for a drafting wave, asserted (P31 S66).

Usage: wave_args.py .run/<wave> [--out <wave>/wf_args.json]

WHY THIS EXISTS (measured, P31 S66). `tools/workflows/claude_wave_draft.js` takes its targets as
an INLINE args object, so the orchestrator has to reproduce `<wave>/targets.json` by hand into the
tool call. I did exactly that for wave r1 and hand-typed `sub` as `ov_SC03_112/jr_80181D08` when
the truth is `asm/ov_SC03_112/nonmatchings/ov_SC03_112_jr_801817E0` — a DIFFERENT subdirectory,
not merely a shorter spelling (a stub's asm dir is named for its jr-carve block, not for itself).
Every agent's `match_one --asm-subdir` would have pointed at a path that does not exist, so all 19
oracles would have failed identically and the wave would have read as a model failure (R40:
exonerate the instrument). Caught before launch only because the .s paths were re-read.

So: never retype a wave's targets. Run this, paste its output. It ASSERTS, per target (R32/R43):
  * targets.json carries every field the workflow prompt interpolates
  * the .s file exists on disk, and `sub` is exactly its parent directory
  * the pack the agent is told to read in full exists
and REFUSES to emit anything if a single target fails — a partly-correct args blob is the failure
mode this tool exists to delete.
"""
import argparse, json, os, sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__))))

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FIELDS = ('name', 'binary', 'nins', 'sub', 'arm')


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('wave', help='wave dir, e.g. .run/r1')
    ap.add_argument('--out', default=None, help='also write the args JSON here (default <wave>/wf_args.json)')
    a = ap.parse_args()
    wave = a.wave.rstrip('/')
    tgt_path = os.path.join(REPO, wave, 'targets.json')
    if not os.path.exists(tgt_path):
        sys.exit('REFUSED: no %s' % tgt_path)
    targets = json.load(open(tgt_path))

    # OPENNESS IS AN ASSERTION, NOT A CONVENTION (P31 S66, measured — see F14).
    # A wave drawn at T and launched at T+2h is stale by construction: gates land continuously, and
    # sibling propagation banks targets nobody drafted. Measured on this session's own waves,
    # against corpus.stubs at gate time: w2 80 drawn / 12 still open (85% wasted), w3 80/39 (51%),
    # x1 80/71 (11%). ~109 of 240 agents in w2+w3 re-derived already-banked functions; they detected
    # it themselves only AFTER reading the pack and burning their budget. So refuse a closed target
    # here, where it costs nothing.
    import importlib
    corpus = importlib.import_module('corpus')
    closed, open_cache = [], {}
    for t in targets:
        b = t.get('binary')
        if not b:
            continue
        if b not in open_cache:
            try:
                open_cache[b] = {v.symbol for v in corpus.stubs(b).values()}
            except Exception as e:            # a refusing oracle is reported, never silently trusted
                print('WARN: stub oracle refused %s (%s) — openness unchecked for it'
                      % (b, str(e)[:80]), file=sys.stderr)
                open_cache[b] = None
        live = open_cache[b]
        if live is not None and t['name'] not in live:
            closed.append('%s:%s' % (b, t['name']))
    if closed:
        print('SKIPPING %d of %d target(s) already banked since the draw: %s%s'
              % (len(closed), len(targets), ', '.join(closed[:8]),
                 ' …' if len(closed) > 8 else ''), file=sys.stderr)
        targets = [t for t in targets
                   if open_cache.get(t.get('binary')) is None
                   or t['name'] in open_cache[t['binary']]]
    if not targets:
        sys.exit('REFUSED: every target in %s is already banked — nothing to draft.' % wave)

    bad = []
    for t in targets:
        miss = [f for f in FIELDS if not t.get(f) and t.get(f) != 0]
        if miss:
            bad.append('%s: missing field(s) %s' % (t.get('name', '?'), ','.join(miss))); continue
        asm = t.get('asm') or os.path.join(t['sub'], t['name'] + '.s')
        if not os.path.exists(os.path.join(REPO, asm)):
            bad.append('%s: asm does not exist: %s' % (t['name'], asm)); continue
        if os.path.dirname(asm) != t['sub'].rstrip('/'):
            bad.append('%s: sub (%s) is not the .s parent (%s)' % (t['name'], t['sub'], os.path.dirname(asm)))
        pack = os.path.join(REPO, wave, 'packs', t['name'] + '.md')
        if not os.path.exists(pack):
            bad.append('%s: no pack at %s' % (t['name'], os.path.relpath(pack, REPO)))
    if bad:
        print('REFUSED: %d of %d target(s) failed the assertion:' % (len(bad), len(targets)), file=sys.stderr)
        for b in bad:
            print('  ' + b, file=sys.stderr)
        sys.exit(2)

    args = {'wave': wave,
            'targets': [{k: t[k] for k in FIELDS} for t in targets]}
    blob = json.dumps(args, separators=(',', ':'))
    out = a.out or os.path.join(REPO, wave, 'wf_args.json')
    open(out, 'w').write(blob + '\n')
    arms = {}
    for t in args['targets']:
        arms[t['arm']] = arms.get(t['arm'], 0) + 1
    print('OK: %d target(s) asserted (%s); args written to %s' %
          (len(targets), ', '.join('%s %d' % kv for kv in sorted(arms.items())), os.path.relpath(out, REPO)),
          file=sys.stderr)
    print(blob)


if __name__ == '__main__':
    main()
