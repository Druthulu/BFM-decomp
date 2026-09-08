#!/usr/bin/env python3
"""exclude_audit.py -- classify every entry of a wave exclude list by its CURRENT blocker, and
regenerate the list so it never silently becomes "work we have decided not to do".

THE STANDING RULE THIS ENFORCES. An exclude list records **what the TOOLING could not do at the
moment it was written**, and is treated thereafter as a property of the FUNCTIONS. Nothing in the
pipeline re-examines it, so every tool improvement leaves behind a population that is now tractable
and still marked impossible -- invisible, because the draw filters it out before anything measures
it. S71 re-probed 68 such entries and found 17 newly carveable, banked 9, four of them in 57 seconds.

MEASURED ON `.run/S71_exclude.txt` AT P31 S72 (107 entries, written the day before):

      28  BANKED         -- already matched; the entry is dead
      58  RE-PROBE/LINKED-- the blocker that put them here is GONE, or they were never targets
      16  CARVE-BLOCKED  -- still real: their subseg owns >1 raw jtbl span (split_indicator)
       5  WALL           -- a curated per-function compiler fact

i.e. **74 of 107 entries were wrong**, one day after the list was written.

THE CLASSES, and why each is decided the way it is:
  * `BANKED`        -- the `INCLUDE_ASM` stub is gone. The source is the oracle, not any ledger.
  * `LINKED`        -- the function lives in a PsyQ LINKED subseg. It is not a matching target at
                       all and `draw_waves` already refuses those, so the entry is pure noise.
  * `CARVE-BLOCKED` -- it has a jump table and its subseg still owns raw tables in >= 2 non-adjacent
                       spans (`split_indicator`), so it genuinely cannot bank yet. KEEP.
  * `RE-PROBE`      -- it has a jump table and its subseg is now CLEAN. Whatever refused it has since
                       been fixed. **DROP, loudly** -- this is the population the rule exists for.
  * `WALL`          -- no jump table, so the jtbl machinery is not why it was excluded. A curated
                       per-function compiler fact (§188 epilogue, §332 `la`-in-delay-slot). KEEP,
                       because it cannot be re-derived here -- but it should carry its refutation
                       list so a later idea can be checked against it cheaply.

    tools/exclude_audit.py .run/S71_exclude.txt              # report
    tools/exclude_audit.py .run/S71_exclude.txt --write OUT  # regenerate (KEEP classes only)
    tools/exclude_audit.py .run/S71_exclude.txt --assert-fresh   # exit 3 if stale (the draw prereq)
"""
import argparse, collections, functools, os, re, sys

print = functools.partial(print, flush=True)
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, 'tools'))

KEEP = ('CARVE-BLOCKED', 'WALL')
STALE = ('BANKED', 'LINKED', 'RE-PROBE')


def parse(path=None, text=None):
    """-> (rows, unparseable). Accepts a FILE or a comma/space-separated string, because
    `draw_waves --exclude` takes the latter and the freshness prerequisite must cover both."""
    src = open(path, errors='replace').read() if path else (text or '')
    rows, bad = [], []
    # STRIP COMMENTS PER LINE **BEFORE** SPLITTING ON COMMAS, never after. The regenerated list
    # carries a `# CLASS: reason` note on every entry and prose in its header, and those contain
    # commas -- splitting first turned `# ...compiler fact, not a tooling limit` into a second
    # "entry" reading `not a tooling limit`. Caught only because this function REPORTS what it
    # cannot parse instead of dropping it (R32); a silent parser would have quietly under-excluded.
    for line in src.splitlines():
        body, _, note = line.partition('#')
        # AN EXPLICIT CLASS ANNOTATION IS AN INPUT, NOT DECORATION (P31 S72). A curated WALL is a
        # per-function compiler fact that this tool CANNOT re-derive — it has no jump table, so the
        # derived logic would happily call it RE-PROBE and drop it. Merging the seven historical
        # walls ledgers in without honouring `# WALL` would have silently discarded two
        # byte-measured walls and spent agents re-proving them (playbook §1b: that costs a full
        # agent run each time).
        pinned = 'WALL' if re.match(r'\s*WALL\b', note) else None
        # Carry the ORIGINAL note. A wall entry's value is its refutation list — what was measured
        # and found inert — so a later idea can be checked against it cheaply. Replacing that with
        # boilerplate turns a piece of evidence into a bare "do not try".
        why = re.sub(r'^\s*WALL\s*:?\s*', '', note).strip() or None
        for chunk in body.split(','):
            s = chunk.strip()
            if not s:
                continue
            if ':' not in s:
                bad.append(s); continue
            b, _, f = s.partition(':')
            rows.append((b.strip(), f.strip(), pinned, why))
    return rows, bad


def classify(path=None, rows=None):
    """-> ([(binary, fn, klass, note)], unparseable). Unparseable lines are reported, not dropped."""
    import corpus, progress, split_indicator as SI
    if rows is None:
        rows, bad = parse(path=path)
    else:
        bad = []

    rows = [(tuple(r) + (None, None))[:4] for r in rows]   # tolerate older 2/3-tuples
    by = collections.defaultdict(list)
    for b, f, _p, _w in rows:
        by[b].append(f)

    blocked, linked_of, stubs_of = {}, {}, {}
    for b in by:
        try:
            _st, lines = SI.check(b)
            blocked[b] = {m.group(1) for l in lines
                          for m in [re.search(r'subseg `([^`]+)`', l)] if m}
        except Exception:
            blocked[b] = set()
        try:
            progress.set_binary(b); linked_of[b] = set(progress.linked_subsegs())
        except Exception:
            linked_of[b] = set()
        try:
            stubs_of[b] = {x.symbol: x for x in corpus.stubs(b).values()}
        except Exception:
            stubs_of[b] = None

    out = []
    for b, f, pinned, why in rows:
        stubs = stubs_of.get(b)
        if stubs is None:
            out.append((b, f, 'WALL', 'binary not readable — kept, unverified')); continue
        st = stubs.get(f)
        if st is None:
            out.append((b, f, 'BANKED', 'no INCLUDE_ASM stub in the source')); continue
        sub = os.path.basename(os.path.dirname(st.asm_path))
        if sub in linked_of.get(b, ()):
            # LINKED outranks a pinned WALL (P31 S79 #5). A wall verdict is a fact about a compiler and
            # a function; whether the function is OURS to match is a provenance question that precedes
            # it. With the pin checked first, PopMatrix/PushMatrix sat here as "compiler walls" for
            # eleven sessions while living in libgte3 (LINKED since Phase 8), and the four §332
            # "%lo-in-a-delay-slot" walls survived the day libpad 4.2.1 linked their objects (§490).
            out.append((b, f, 'LINKED', f'subseg {sub} is linked PsyQ — never a target')); continue
        if pinned == 'WALL':
            # BANKED and LINKED win above -- a wall that got matched or linked is simply no longer a wall.
            out.append((b, f, 'WALL',
                        why or 'curated compiler fact (pinned in the list; not re-derivable)'))
            continue
        txt = open(st.asm_path, errors='replace').read()
        # §401: a jtbl function jumps through a register that is NOT $ra; `jr $ra` ends every function
        if re.search(r'\bjr\s+\$(?!ra\b)\w+', txt):
            if sub in blocked.get(b, ()):
                out.append((b, f, 'CARVE-BLOCKED', f'{sub} owns >1 raw jtbl span — needs a split'))
            else:
                out.append((b, f, 'RE-PROBE', f'{sub} is clean now — the blocker is gone'))
        else:
            out.append((b, f, 'WALL', 'no jump table — curated compiler fact, not a tooling limit'))
    return out, bad


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('path')
    ap.add_argument('--write', metavar='OUT', help='regenerate, keeping only still-valid entries')
    ap.add_argument('--assert-fresh', action='store_true',
                    help='exit 3 if any entry is stale (the draw-time prerequisite)')
    a = ap.parse_args()
    os.chdir(REPO)
    rows, bad = classify(a.path)
    cnt = collections.Counter(k for _, _, k, _ in rows)
    print(f"{a.path}: {len(rows)} entries")
    for k, v in cnt.most_common():
        print(f"  {v:4d}  {k}{'   (STALE)' if k in STALE else ''}")
    if bad:
        print(f"  !! {len(bad)} unparseable line(s), kept out of the count: {bad[:3]}")
    stale = [r for r in rows if r[2] in STALE]
    for k in STALE:
        ex = [f"{b}:{f}" for b, f, kk, _ in rows if kk == k]
        if ex:
            print(f"\n  {k} ({len(ex)}): " + ", ".join(ex[:8]) + (" …" if len(ex) > 8 else ""))

    if a.write:
        keep = [r for r in rows if r[2] in KEEP]
        with open(a.write, 'w') as fh:
            fh.write(f"# regenerated by tools/exclude_audit.py from {a.path}\n"
                     f"# {len(keep)} still-valid of {len(rows)}; "
                     f"{len(stale)} dropped as stale (banked / linked / blocker-since-fixed).\n"
                     f"# An exclude list records what the TOOLING could not do — regenerate it as\n"
                     f"# part of every tool fix, or it becomes a list of work you decided not to do.\n")
            for b, f, k, note in keep:
                fh.write(f"{b}:{f}  # {k}: {note}\n")   # `# WALL:` is re-read as a pin by parse()
        print(f"\nwrote {a.write}: {len(keep)} kept, {len(stale)} dropped")

    if a.assert_fresh and stale:
        print(f"\n*** STALE — {len(stale)} of {len(rows)} entries no longer describe reality. "
              f"Regenerate with:\n    tools/exclude_audit.py {a.path} --write <new>\n"
              f"Drawing against this list would silently filter out work that is now doable.")
        return 3
    return 0


if __name__ == '__main__':
    sys.exit(main())
