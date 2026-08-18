#!/usr/bin/env python3
"""gap_triage.py — deterministically pre-filter a wave's index_gap reports against the cookbook.

WHY (P31 S55). Every harvest so far has spent most of its agents rediscovering that a gap was
already answered: 61 of 71 (wave T), 44/64 (U), 76/67 (V), 41/68 (W), 56/63 (X). That majority
verdict is the flywheel working, but PAYING an adversarial verifier to reach it is waste — the
check is a text search, and a text search does not need a model.

This scores each gap against the cookbook's section headers + bodies by distinctive-term overlap and
emits the top candidate sections. It DOES NOT decide anything: a high score means "a reader should
open these sections first", and the harvest prompt carries them so the reader starts from the
existing text instead of a blank page. R32: every gap appears in the output exactly once, asserted.

Deliberately dumb: term overlap, no embeddings, no model. It is a retrieval aid whose failure mode
is a bad suggestion the reader ignores, not a refusal that discards work (R39).

Usage:
  gap_triage.py .run/wave_y_gaps.json [--top 3] [--out .run/wave_y_gap_triage.json]
"""
import argparse, collections, json, os, re, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CB = os.path.join(REPO, 'docs', 'matching-cookbook.md')

# Terms that carry meaning in this domain. Generic English is dropped by the IDF weighting below,
# but these patterns are what actually discriminate one residual class from another.
_TERM = re.compile(r'\b(?:'
                   r'[a-z_]+\.c:\d+'                 # sched.c:2395
                   r'|[a-z_]+\.(?:c|md|h)\b'         # combine.c, mips.md
                   r'|§\d+[A-Za-z0-9\-]*'            # §193-A
                   r'|\$[a-z0-9]+'                   # $v0, $sp
                   r'|(?:lhu|lh|lw|lb|lbu|sh|sw|sb|sll|sra|srl|addiu|addu|subu|ori|lui|jal|jr|beq'
                   r'|bne|beqz|bnez|slt|sltu|slti|sltiu|mflo|mult|div|nop|move)\b'
                   r'|(?:sched1|sched2|cse|combine|reload|regalloc|local_alloc|global_alloc|loop|jump2'
                   r'|cross_jump|reorg|expand|fold|giv|biv|preheader|allocno|pseudo|birthing|luid'
                   r'|delay.slot|epilogue|prologue|frame|stride|alias|clobber|volatile|typedef)\b'
                   r')', re.I)


def sections():
    """[(anchor, text)] for every cookbook section, split on its own headers."""
    txt = open(CB, errors='replace').read()
    out, cur, buf = [], 'preamble', []
    for line in txt.splitlines():
        m = re.match(r'^#{2,4}\s+(§\S+)', line)
        if m:
            if buf: out.append((cur, '\n'.join(buf)))
            cur, buf = m.group(1), [line]
        else:
            buf.append(line)
    if buf: out.append((cur, '\n'.join(buf)))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('gaps'); ap.add_argument('--top', type=int, default=3)
    ap.add_argument('--out', default=None)
    a = ap.parse_args()

    secs = sections()
    sec_terms = [(anc, collections.Counter(t.lower() for t in _TERM.findall(body))) for anc, body in secs]
    df = collections.Counter()
    for _, c in sec_terms:
        for t in c: df[t] += 1
    n = len(sec_terms) or 1

    gaps = json.load(open(a.gaps))
    rows = []
    for g in gaps:
        want = collections.Counter(t.lower() for t in _TERM.findall(g.get('gap') or ''))
        scored = []
        for anc, c in sec_terms:
            # IDF-weighted overlap: a term in 300 sections says nothing, one in 2 says a lot.
            s = sum(1.0 / (1 + df[t]) for t in want if t in c)
            if s: scored.append((round(s, 3), anc))
        scored.sort(reverse=True)
        rows.append({'fn': g['fn'], 'terms': sorted(want)[:8],
                     'candidates': [{'section': anc, 'score': s} for s, anc in scored[:a.top]]})
    assert len(rows) == len(gaps), f"coverage (R32): {len(rows)} rows for {len(gaps)} gaps"

    out = a.out or a.gaps.replace('.json', '_triage.json')
    json.dump(rows, open(out, 'w'), indent=1)
    hit = sum(1 for r in rows if r['candidates'])
    print(f"gap_triage: {len(rows)} gaps vs {len(secs)} cookbook sections -> {hit} with a candidate "
          f"section, {len(rows)-hit} with none -> {out}")
    print("  (a candidate is a STARTING POINT for the reader, never a verdict — the harvest still "
          "runs its own grep and its own adversarial verifier)")
    for r in rows[:5]:
        c = ', '.join(f"{x['section']}({x['score']})" for x in r['candidates']) or '—'
        print(f"    {r['fn']:18s} {c}")


if __name__ == '__main__':
    main()
