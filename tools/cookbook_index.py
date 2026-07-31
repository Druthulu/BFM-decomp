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
    # P30 wave-2 FEEDBACK: agents reported which symptoms the index failed to surface. Their
    # findings are folded in as explicit symptom lines below (SYMPTOM_HINTS) AND as widened
    # vocabulary here — e.g. `match_one` prints the class literally as "BRANCH-POLARITY" while
    # this bucket matched only §5a, so two agents re-derived §3-T4 from scratch.
    ("delay slots & branches",
     r"delay[- ]slot|branch|polarit|invert|bne|beq|bgez|beqz|reorg|dbr|jump.?to|nop\b|"
     r"cross-?jump|tail-?merge|early[- ]exit|return 0|shared[- ]ret|arms? swap|if/else|diamond"),
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
# Curated symptom -> section pointers. Keyword matching over TITLES cannot surface an entry whose
# title never names the symptom; every line here is one an agent hit and could not find (P30 wave 2).
# Keep it short — it is the "read this first" list, not a second index.
SYMPTOM_HINTS = [
    ("wrong branch sense / arms swapped / `beq` where the target has `bne` "
     "(match_one prints this class as **BRANCH-POLARITY**)",
     "**§3-T4** (invert the source condition) + **§32**.2; for a trailing `return 0` vs an early "
     "return see the shared-ret0 note (cookbook L1344)"),
    ("`conflicting types` on YOUR OWN function's definition, where the fleet canon is `(void)`",
     "**§73** (the PARAMS axis) + **§42** — keep the `(void)` signature and read the incoming arg "
     "via `register s32 a0v __asm__(\"$4\")`; §42 is otherwise indexed only under regalloc"),
    ("a shared global declared at a conflicting type (u8 vs s32, signedness) blocking your draft",
     "**§37** asm-label alias `extern T X __asm__(\"D_x\")` — beats `*(T*)&X`, whose address-of "
     "perturbs regalloc. Works for FUNCTION definitions too (P30 wave 2)"),
    ("target reuses ONE address register across two different offsets of the same global",
     "**§20** (the pointer-var-to-the-global bullet, cookbook L1907-1918) — take `T *p = &D_x;` and "
     "index off `p`, never the bare symbol twice"),
    ("an extra `la` / the address hoisted into a callee-saved register across calls",
     "**§20** + `gcc-2.7.2-map/cse_expr.md` §H — `*(T*)&sym` force_regs the address; the asm-label "
     "alias (§37) keeps the direct `%lo` mem form"),
    ("`andi $x,0xFF` folded away in your output but present in the target",
     "**§1/I2** + **§12** name the family; if the prescribed `& 0xff` at the use folds, hold the "
     "masked byte in a **u16** local so only a QI->HI extend survives (P30 wave 2, byte-tested)"),
    ("`slti` where the target has `sltiu` (or vice versa)",
     "**§35** — a separate SIGNED int copy of an unsigned load keeps `slti`; chained bounds get "
     "range-folded, so write each bound as its own `if`/`goto` (**§21**)"),
    ("you are about to hand-derive a body that some overlay already matched",
     "**§71** — grep the callees/globals for an already-matched SIBLING first; in wave 2 this alone "
     "produced iteration-1 MATCHes on 4 of 19 targets"),
    ("gcc stole an instruction into a branch delay slot that the target leaves as `nop`",
     "**§5a** + the zero-byte `__asm__(\"\")` fence (**§34** toolkit) — `reorg.c stop_search_p` halts "
     "the eager filler on an asm insn"),
    ("`void` vs `s32` return — is promoting it byte-neutral?",
     "**NO, not always: §41d** (byte-proven; a `void` body with no `return` gains an instruction). "
     "P30 adds a second mechanism: an `s32` return keeps `$v0` live-out and blocks dbr from filling "
     "a loop-back delay slot"),
]

# Two header shapes exist and BOTH are content: `## §N — title` (the numbered sections) and the
# unnumbered `### T4 — Branch polarity...` / `### I2 — Byte mask...` sub-entries inside §1/§2/§3.
# The second shape is where the most-cited idioms live — §3-T4 is the BRANCH-POLARITY fix that
# match_one names by class, and two P30 wave-2 agents re-derived it because it was not indexed.
HDR = re.compile(r"^(#{2,4})\s+(§?[0-9A-Za-z][0-9A-Za-z.\-]*)\s*(?:[—–:-]\s*)?(.*?)\s*$")
# The candidate set must OVER-approximate (R32's own rule, which the first version of this file
# broke): count EVERY h2-h4 header, not just the §-prefixed ones. Asserting §-parsed == §-candidates
# was a tautology that hid 111 unnumbered headers — the same "assert against a set you already
# narrowed" defect the scanners had, reproduced in the tool written to prevent it.
ANY_HEADER = re.compile(r"^#{2,4}\s+\S")
# Prose scaffolding, not idiom content — excluded explicitly (never silently).
SKIP_TITLES = re.compile(r"^(how to use|contents|index|overview|scope|status|see also|note)\b", re.I)


def sections():
    out, candidates, skipped = [], 0, []
    for i, line in enumerate(open(SRC, errors="replace"), 1):
        line = line.rstrip("\n")
        if not ANY_HEADER.match(line):
            continue
        candidates += 1
        m = HDR.match(line)
        title = (m.group(3) or m.group(2)) if m else ""
        if m and not SKIP_TITLES.match(title.strip()):
            ref = m.group(2)
            out.append({"ref": ref if ref.startswith("§") else "§3-" + ref if len(ref) <= 3 else ref,
                        "title": m.group(3) or m.group(2), "line": i})
        else:
            skipped.append((i, line[:80]))
    if len(out) + len(skipped) != candidates:
        sys.exit(f"cookbook_index: accounted {len(out)}+{len(skipped)} of {candidates} headers (R32)")
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

    L.append("\n## Start here — the symptoms that come up most, with the section that fixes them\n")
    L.append("> Hand-curated from what agents actually hit and, in several cases, RE-DERIVED because "
             "keyword matching alone did not surface the entry (P30 wave-2 feedback). If your symptom "
             "is here, read the named section before anything else.\n")
    for sym, secs_ in SYMPTOM_HINTS:
        L.append(f"- **{sym}** → {secs_}")

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
