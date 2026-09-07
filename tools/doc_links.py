#!/usr/bin/env python3
"""doc_links.py — every relative Markdown link in the public-facing docs resolves (P33 D5; in tools-health).

    tools/doc_links.py                          # the default document set; exit 1 on a broken link
    tools/doc_links.py --strict                 # also fail on links listed as PENDING (for gate 2 / the PhaseEnd)
    tools/doc_links.py FILE…                    # an explicit set

A link `[text](target)` whose target is not a URL/mailto/anchor must resolve relative to the linking file (or to the
repository root when it starts with `/`); `#fragment`s are stripped. Targets listed in docs/doc_links_pending.txt
(`path<TAB>the task that creates it`) are reported as PENDING instead of BROKEN — a README may promise a page that a
later task of the same phase writes, but the promise is tracked, and `--strict` (gate 2) refuses any pending entry.
Coverage is printed with its denominator (R41): files scanned, links checked, pending, broken.
"""
import argparse
import pathlib
import re
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
DEFAULT = ["README.md", "THIRD_PARTY.md", "CLAUDE.md", "src/NOTICE.md", "tools/README.md", "docs/SETUP.md",
           "docs/verification.md", "docs/public-flip-runbook.md", "docs/decision-log.md", "docs/accelerators.md",
           "docs/story.md", "docs/story-timeline.md", "docs/retrospective.md", "phase-ends/README.md", "phase-ends/DIGEST.md",
           "docs/gcc-2.7.2-map/README.md", "tools/xsig/README.md",
           "docs/permuter-ils.md", "docs/matching-drafter-pipeline.md",
           "docs/gen3-handoff.md", "docs/decompme-preset.md"]
# whole directories in the default set (P33 F3): the wiki pages and the how-to chapters — every file, so a new page is
# checked the moment it exists (the glob is expanded at run time; the count is printed with the rest, R41)
DEFAULT_GLOBS = ["docs/wiki/*.md", "docs/how-to-ai-decomp/*.md"]


def default_files():
    out = list(DEFAULT)
    for g in DEFAULT_GLOBS:
        out += [p.relative_to(REPO).as_posix() for p in sorted(REPO.glob(g))]
    return out
PENDING_FILE = REPO / "docs" / "doc_links_pending.txt"
LINK_RE = re.compile(r"(?<!\!)\[[^\]]*\]\(([^)\s]+)(?:\s+\"[^\"]*\")?\)")
SKIP_PREFIX = ("http://", "https://", "mailto:", "#", "ftp://")


def pending():
    out = {}
    if PENDING_FILE.exists():
        for ln in PENDING_FILE.read_text(encoding="utf-8").splitlines():
            ln = ln.strip()
            if ln and not ln.startswith("#"):
                path, _, task = ln.partition("\t")
                out[path.strip()] = task.strip() or "?"
    return out


def check(files, strict):
    pend = pending()
    n_links, broken, pend_hits = 0, [], []
    for f in files:
        fp = REPO / f
        if not fp.exists():
            if f in pend:
                pend_hits.append((f, "<the document itself>", pend[f]))   # promised by a later task, tracked
            else:
                broken.append((f, "<file itself>", "document missing"))
            continue
        text = fp.read_text(encoding="utf-8", errors="replace")
        for m in LINK_RE.finditer(text):
            tgt = m.group(1)
            if tgt.startswith(SKIP_PREFIX):
                continue
            n_links += 1
            path = tgt.split("#", 1)[0]
            if not path:
                continue
            resolved = (REPO / path.lstrip("/")) if path.startswith("/") else (fp.parent / path)
            if resolved.exists():
                continue
            rel = str(resolved.resolve().relative_to(REPO)) if resolved.resolve().is_relative_to(REPO) else str(resolved)
            if rel in pend:
                pend_hits.append((f, tgt, pend[rel]))
            else:
                broken.append((f, tgt, "does not exist"))
    print(f"doc_links: {len(files)} documents, {n_links} relative links checked, {len(pend_hits)} pending "
          f"({len(pend)} planned targets on the list), {len(broken)} broken")
    for f, t, why in broken:
        print(f"  BROKEN  {f}: ({t}) {why}")
    for f, t, task in sorted(set(pend_hits)):
        print(f"  PENDING {f}: ({t}) — created by {task}")
    if broken:
        return 1
    if strict and pend_hits:
        print("doc_links --strict: pending links remain — the promised pages must exist before gate 2")
        return 1
    print("doc_links: OK" + (" (with pending, allowed outside --strict)" if pend_hits else ""))
    return 0


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("files", nargs="*")
    ap.add_argument("--strict", action="store_true")
    a = ap.parse_args(argv)
    return check(a.files or default_files(), a.strict)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
