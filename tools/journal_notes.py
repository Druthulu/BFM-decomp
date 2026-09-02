#!/usr/bin/env python3
"""Per-function PAST-ATTEMPT fuel, mined from the agent journals (P31 S71, cookbook §409/§411).

WHY THIS IS A PACK STEP AND NOT AN AUDIT. Every drafting agent writes one note per target into its
workflow journal (`subagents/workflows/wf_*/journal.jsonl`): what it tried, what it measured INERT,
which lever moved the residual, and where its draft sits on disk. Until S71 those notes were written
and never read, so each new wave re-derived the dead ends the last one had already paid for.

MEASURED, S71 wave 1 (50 one-agent workflows over the hardest 210-function frontier, every target
having already refused at least one earlier wave):
  * 38 / 39 agents returned MATCH at closeness 0 (97.4%), vs S70's 124 / 131 (94.7%) on an EASIER pool;
  * 29 / 39 (74%) cite a prior attempt or the pack's history as what they used;
  * 4 / 39 (10%) RECOVERED a previously-MATCHing body straight off disk instead of re-deriving it
    (`ov_SC05_003/func_80181720`: the pack's warm-start was a FAILED draft while attempt 3's MATCH
    was still sitting under `.run/S70x_1/opus`);
  * 11 / 39 (28%) matched on the first compile.
The failure modes it removes are the expensive ones: re-testing a measured-inert lever, and
re-deriving a body that already exists.

  python3 tools/journal_notes.py --wave .run/<wave>          # append to every pack in the wave
  python3 tools/journal_notes.py --fn func_X --binary B      # print what we hold on one function

R32: prints coverage (targets with notes / targets) so a silent zero cannot pass as "no history".
R41: every rate carries its denominator.
"""
import argparse, collections, glob, json, os, re, sys

JOURNALS = os.path.expanduser(
    '~/.claude/projects/-home-musashi-bfm-decomp/*/subagents/workflows/*/journal.jsonl')
HEADING = "## PAST ATTEMPTS ON THIS EXACT FUNCTION (mined from the agent journals)"
MIN_NOTE = 120


def load(paths=None):
    """-> {(binary|None, fn): [ {status, closeness, klass, note} ]}, newest journals last."""
    out = collections.defaultdict(list)
    for j in sorted(glob.glob(paths or JOURNALS)):
        for line in open(j, errors='replace'):
            try:
                r = json.loads(line)
            except ValueError:
                continue
            res = r.get('result')
            if not isinstance(res, dict):
                continue
            fn = res.get('fn') or res.get('name')
            note = res.get('notes') or res.get('note') or ''
            if not fn or not isinstance(note, str) or len(note) < MIN_NOTE:
                continue
            out[(res.get('binary'), fn)].append(
                {'status': res.get('status'), 'closeness': res.get('closeness'),
                 'klass': res.get('klass'), 'note': note})
    return out


def notes_for(idx, binary, fn):
    """Notes about (binary, fn). A note whose row carries no binary is included — the journal shape
    varies by era — but one stamped with a DIFFERENT binary is never served (R48: the same name is a
    different function in another overlay, §238)."""
    return idx.get((binary, fn), []) + idx.get((None, fn), [])


def render(rows, cap=6):
    out = ["\n\n" + HEADING + "\n",
           "Notes written by earlier agents who worked THIS function and did not bank it.",
           "They are EVIDENCE, not instruction: verify any claim against the .s before acting on it.",
           "Do NOT re-try an approach one of them already measured as inert, and if one names a draft",
           "path, read that draft before writing your own — 10% of S71's agents banked by recovering",
           "a body that already matched.\n"]
    for i, x in enumerate(rows[:cap], 1):
        head = " · ".join(str(v) for v in [
            x.get('status'), x.get('klass'),
            ('closeness %s' % x['closeness']) if x.get('closeness') is not None else None] if v)
        out.append("**Attempt %d** (%s)\n\n%s\n" % (i, head or 'no verdict recorded', x['note'][:3000]))
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--wave', help='wave dir: append to <wave>/packs/<fn>.md for every target')
    ap.add_argument('--fn'); ap.add_argument('--binary')
    ap.add_argument('--journals', default=None)
    ap.add_argument('--cap', type=int, default=6)
    a = ap.parse_args()
    idx = load(a.journals)

    if a.fn:
        rows = notes_for(idx, a.binary, a.fn)
        print(render(rows, a.cap) if rows else '(no journal notes for %s)' % a.fn)
        return 0
    if not a.wave:
        ap.error('give --wave or --fn')

    targets = json.load(open(os.path.join(a.wave, 'targets.json')))
    done = hit = 0
    for t in targets:
        fn = t.get('name') or t.get('fn')
        p = os.path.join(a.wave, 'packs', '%s.md' % fn)
        if not os.path.exists(p):
            continue
        rows = notes_for(idx, t.get('binary'), fn)
        if not rows:
            continue
        hit += 1
        if HEADING in open(p, errors='replace').read():   # idempotent: never append twice
            continue
        open(p, 'a').write(render(rows, a.cap))
        done += 1
    print('journal_notes: %d/%d target(s) have past-attempt notes; appended to %d pack(s) '
          '(%d already carried them)' % (hit, len(targets), done, hit - done))
    return 0


if __name__ == '__main__':
    sys.exit(main())
