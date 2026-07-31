#!/usr/bin/env python3
"""cookbook_index.py — generate docs/cookbook-index.md, a SYMPTOM-keyed index of the cookbook.

WHY (P30 wave-1, measured): the cookbook is 716 KB / 226 sections with no index. Three agents in
one wave reported "NEW idiom" findings that were ALREADY DOCUMENTED — the asm-label alias for
type-conflicting shared globals (line ~2516, including the same "address-of perturbs regalloc"
mechanism) and the void->s32 non-neutrality (§41d, byte-proven in Phase 26; the agents cited the
very entry §41d corrects). They had been told to consult the cookbook and did; they could not FIND
the entries. That is a discoverability failure, not a coverage failure, and it is a compounding tax:
every wave re-derives what a previous wave already paid for, which is the exact opposite of the
flywheel R16 exists to build.

The fix an agent can actually use is a map from the SYMPTOM IT OBSERVES (what the diff looks like)
to the sections that address it — not a table of contents ordered by discovery date. Section titles
already carry that information; this derives the index from them (R33: derived, never hand-kept, so
it cannot drift from the cookbook it indexes).

  tools/cookbook_index.py            # -> docs/cookbook-index.md
  tools/cookbook_index.py --check    # non-zero if the committed index is stale (for tools-health)
"""
import argparse
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(REPO, "docs/matching-cookbook.md")
OUT = os.path.join(REPO, "docs/cookbook-index.md")

# symptom -> the words that appear in a section title addressing it. Ordered: the first bucket a
# section matches owns it in the "primary" listing, but a section is listed under EVERY bucket it
# matches (an idiom that fixes two symptoms should be findable from both).
BUCKETS = [
    ("delay slots & branches",
     r"delay[- ]slot|branch|bne|beq|bgez|reorg|dbr|jump.?to|nop\b|cross-?jump|tail-?merge"),
    ("instruction scheduling",
     r"schedul|sched\d?|hoist|sink|fence|barrier|order of|reorder|LUID"),
    ("register allocation & pins",
     r"regalloc|register|allocno|pin|\$s\d|\$v\d|\$a\d|local-?alloc|global-?alloc|spill|live range|liveness"),
    ("CSE / redundancy / rematerialization",
     r"\bcse\b|common sub|redundan|remat|canon_reg|copy prop|invariant|volatile"),
    ("loops & induction variables",
     r"\bloop|induction|\biv\b|biv|giv|unroll|strength|latch|back edge"),
    ("structs, block moves & memcpy",
     r"struct|block[- ]move|movstr|memcpy|block copy|field|anon|/s\b|packed"),
    ("types, signedness & load/store width",
     r"signed|unsign|\bs8\b|\bu8\b|\bs16\b|\bu16\b|\bs32\b|\bu32\b|width|lhu|lbu|\blh\b|\blb\b|cast|typedef|type"),
    ("declarations, prototypes & K&R",
     r"K&R|prototype|proto\b|decl|extern|arity|conflicting types|signature|sig[-_ ]|canonical|def-?sig|void\b"),
    ("jump tables & switches",
     r"jump ?table|jtbl|switch|\bjr\b|carve|rodata|tablejump"),
    ("optimisation level (-O0/-O2)",
     r"-O0|-O2|opt(imi[sz]ation)? level|whale|o0b|per-file"),
    ("family propagation & sweeps",
     r"famil|propagat|sweep|dedup|h_seq|h_exact|remap|template|member|reach|×\d|x13[48]"),
    ("integration / TU plumbing",
     r"integrat|plumbing|TU\b|translation unit|de-?macroize|splice|stranded|self-?contained|include|header"),
    ("build graph, splat & the harness",
     r"splat|build|link|segment|object|makefile|harvest|gate|oracle|tool|scanner|manifest|corpus"),
    ("process, measurement & doctrine",
     r"law\b|doctrine|discipline|measur|probe|verify|honest|refut|correction|R\d\d|lesson"),
]

# The separator is OPTIONAL. The first draft of this regex required an em/en-dash and silently
# dropped 50 sections — including §1 (the idiom catalog), §2 (writing matching C) and §5a
# (cross-jump), i.e. the foundational entries, because the early sections separate with a space.
# An index missing its own most-cited entries is worse than no index: it converts "I could not
# find it" into "it is not there." Caught by asserting coverage against an over-approximating
# candidate set (R32) — the same discipline the scanners had to learn.
HDR = re.compile(r"^(#{2,4})\s*(§[0-9a-zA-Z.\-]+)\s*(?:[—–:-]\s*)?(.+?)\s*$")
ANY_SECTION = re.compile(r"^#{2,4}\s*§")


def sections():
    out, candidates = [], 0
    for i, line in enumerate(open(SRC, errors="replace"), 1):
        line = line.rstrip("\n")
        if ANY_SECTION.match(line):
            candidates += 1
        m = HDR.match(line)
        if m:
            out.append({"ref": m.group(2), "title": m.group(3), "line": i})
    # R32: compare what we extracted against the over-approximating candidate set and FAIL on a gap.
    if len(out) != candidates:
        sys.exit(f"cookbook_index: parsed {len(out)} of {candidates} '§' headers — "
                 f"{candidates - len(out)} silently dropped; fix HDR before trusting this index (R32)")
    return out


def render(secs):
    L = []
    L.append("# Cookbook index — find the entry by the SYMPTOM you are looking at\n")
    L.append("> **Generated by `tools/cookbook_index.py` — do not hand-edit** (R33). Regenerate after "
             "adding a cookbook section.\n>\n"
             "> `docs/matching-cookbook.md` is ~716 KB / %d sections. Grepping it blind is how three "
             "P30 wave-1 agents each \"discovered\" an idiom that was already written down. **Start "
             "here, then read the section.** A section appears under every symptom it addresses.\n"
             % len(secs))
    L.append("**How to use:** name what you SEE in the diff (a stolen delay slot, an extra `la`, a "
             "swapped register pair, a `conflicting types` error), find that symptom below, read those "
             "sections first. If nothing fits, THEN grind — and add a section when you win.\n")

    L.append("\n## By symptom\n")
    for name, pat in BUCKETS:
        rx = re.compile(pat, re.I)
        hits = [s for s in secs if rx.search(s["title"])]
        if not hits:
            continue
        L.append(f"\n### {name}  ({len(hits)})\n")
        for s in hits:
            L.append(f"- **{s['ref']}** — {s['title']}  <sub>L{s['line']}</sub>")
    uncovered = [s for s in secs
                 if not any(re.search(p, s["title"], re.I) for _, p in BUCKETS)]
    if uncovered:
        L.append(f"\n### (unbucketed — title matched no symptom vocabulary)  ({len(uncovered)})\n")
        for s in uncovered:
            L.append(f"- **{s['ref']}** — {s['title']}  <sub>L{s['line']}</sub>")

    L.append("\n\n## All sections, in order\n")
    for s in secs:
        L.append(f"- **{s['ref']}** — {s['title']}  <sub>L{s['line']}</sub>")
    return "\n".join(L) + "\n"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true",
                    help="exit non-zero if docs/cookbook-index.md is stale vs the cookbook")
    a = ap.parse_args()
    secs = sections()
    if not secs:
        sys.exit("cookbook_index: parsed 0 sections — the header format changed; fix HDR (R32)")
    text = render(secs)
    if a.check:
        cur = open(OUT, errors="replace").read() if os.path.exists(OUT) else ""
        if cur != text:
            print(f"cookbook-index STALE ({len(secs)} sections in the cookbook) — run tools/cookbook_index.py",
                  file=sys.stderr)
            return 1
        print(f"cookbook-index OK ({len(secs)} sections)")
        return 0
    open(OUT, "w").write(text)
    print(f"cookbook index -> docs/cookbook-index.md ({len(secs)} sections, "
          f"{sum(1 for _ in BUCKETS)} symptom buckets)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
