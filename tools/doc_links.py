#!/usr/bin/env python3
"""doc_links.py — every relative Markdown link in the public-facing docs resolves, and the wiki-first link policy holds
(P33 D5; extended P33.5 task 7; in tools-health).

    tools/doc_links.py                          # the default document set; exit 1 on a broken link or a policy breach
    tools/doc_links.py --strict                 # also fail on links listed as PENDING (for gate 2 / the PhaseEnd)
    tools/doc_links.py --disk FILE…             # local only: split UNTRACKED citations into PRIVATE (on disk) / DANGLING
    tools/doc_links.py FILE…                    # an explicit set

Checks, each printed with its denominator (R41):
  1. LINKS — a link `[text](target)` whose target is not a URL/mailto/anchor must resolve relative to the linking file (or to
     the repository root when it starts with `/`); `#fragment`s are stripped. Targets listed in docs/doc_links_pending.txt
     (`path<TAB>the task that creates it`) are PENDING instead of BROKEN (R80); `--strict` refuses any pending entry.
  2. THE ARCHIVE — no document may link into docs/sunset/ (the Archive index names archived files as backticked paths so the
     folder can be deleted without breaking a link).
  3. WIKI-FIRST — a wiki page or how-to chapter may link into docs/ (outside the wiki's own sources) only at a target the
     Reference index (docs/wiki/Reference-index.md) or the README links — a file, or anything under a directory they link.
     The allow-list is DERIVED from those two pages (R33); the two index pages are exempt from the rule they define.
  4. COVERAGE — every tracked file under docs/ outside docs/wiki/, docs/how-to-ai-decomp/ and docs/sunset/ is covered the same
     way (a reference file that no index row names is invisible to a reader of the wiki).
  5. CITATIONS — a backticked path `docs/…` or `.run/…` is a citation, not a link. Each is TRACKED (in `git ls-files`, or a
     directory some tracked file lives under) or UNTRACKED — decided by git, never by the disk, so a fresh clone gets the same
     verdict. A wiki page or chapter citing an UNTRACKED path is a failure (a wiki reader must be able to follow every path
     named there); elsewhere the counts are printed and untracked citations are private-tree breadcrumbs. `--disk` adds the
     on-disk PRIVATE / DANGLING split for the maintainer (the R39 control for the cookbook's stale citations). A citation
     written as `path` (not kept) is declared gone by its author and is skipped — that is how a record admits a dead path
     without pretending it is a live one. `path:12` / `path:12-19` cite lines inside a file and look up the file.
  6. WIKI-FIRST WARNINGS (exit 0) — a document outside the wiki and the README that links a docs/ file whose topic has a wiki
     page is listed, so the author can point at the page instead.
"""
import argparse
import pathlib
import re
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
DEFAULT = ["README.md", "THIRD_PARTY.md", "CLAUDE.md", "src/NOTICE.md", "tools/README.md", "docs/SETUP.md",
           "docs/verification.md", "docs/public-flip-runbook.md", "docs/decision-log.md", "docs/accelerators.md",
           "docs/story.md", "docs/story-timeline.md", "docs/retrospective.md", "phase-ends/README.md", "phase-ends/DIGEST.md",
           "docs/gcc-2.7.2-map/README.md", "tools/xsig/README.md",
           "docs/permuter-ils.md", "docs/matching-drafter-pipeline.md",
           "docs/gen3-handoff.md", "docs/decompme-preset.md", "docs/outreach/archipelago.md", "docs/outreach/tools-announcement.md",
           "docs/gen3-standards.md", "docs/phase34-seed.md"]
# whole directories in the default set (P33 F3): the wiki pages and the how-to chapters — every file, so a new page is
# checked the moment it exists (the glob is expanded at run time; the count is printed with the rest, R41)
DEFAULT_GLOBS = ["docs/wiki/*.md", "docs/how-to-ai-decomp/*.md"]
WIKI_DIRS = ("docs/wiki/", "docs/how-to-ai-decomp/")
INDEX_PAGES = ("docs/wiki/Reference-index.md", "docs/wiki/Archive-index.md")
ARCHIVE_DIR = "docs/sunset/"
# the wiki page that covers a docs/ file's topic — for the wiki-first WARNING only (a hand-kept map; small on purpose)
TOPIC_PAGE = {
    "docs/SETUP.md": "docs/wiki/Toolchain-setup.md",
    "docs/verification.md": "docs/wiki/Verification-and-progress.md",
    "docs/public-flip-runbook.md": "docs/wiki/The-ROM-firewall.md",
    "docs/gen3-standards.md": "docs/wiki/Where-the-project-goes-next.md",
    "docs/gen3-handoff.md": "docs/wiki/Where-the-project-goes-next.md",
    "docs/wave-playbook.md": "docs/wiki/The-matching-workflow.md",
    "docs/formats.md": "docs/wiki/Overlays-and-modules.md",
    "docs/memory-map.md": "docs/wiki/Overlays-and-modules.md",
}


def default_files():
    out = list(DEFAULT)
    for g in DEFAULT_GLOBS:
        out += [p.relative_to(REPO).as_posix() for p in sorted(REPO.glob(g))]
    return out


PENDING_FILE = REPO / "docs" / "doc_links_pending.txt"
LINK_RE = re.compile(r"(?<!\!)\[[^\]]*\]\(([^)\s]+)(?:\s+\"[^\"]*\")?\)")
CITE_RE = re.compile(r"`((?:docs|\.run)/[^`\s]+)`(?! \(not kept\))")   # `path` (not kept) = declared gone, not dangling
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


def tracked():
    """Every tracked path (R33: git is the oracle, never the disk) plus every directory some tracked file lives under."""
    out = subprocess.run(["git", "-C", str(REPO), "ls-files", "-z"], capture_output=True, text=True, check=True).stdout
    files = set(p for p in out.split("\0") if p)
    dirs = set()
    for p in files:
        parts = p.split("/")
        for i in range(1, len(parts)):
            dirs.add("/".join(parts[:i]))
    return files, dirs


def rel_of(fp, target):
    """Resolve a link/citation target relative to the linking file; None when it leaves the repository."""
    path = target.split("#", 1)[0]
    if not path:
        return None
    resolved = (REPO / path.lstrip("/")) if path.startswith("/") else (fp.parent / path)
    r = resolved.resolve()
    if not r.is_relative_to(REPO):
        return None
    return r.relative_to(REPO).as_posix()


def link_targets(doc):
    """The resolved targets a document links (files and directories), for the derived allow-list."""
    fp = REPO / doc
    out = set()
    if not fp.exists():
        return out
    for m in LINK_RE.finditer(fp.read_text(encoding="utf-8", errors="replace")):
        if m.group(1).startswith(SKIP_PREFIX):
            continue
        rel = rel_of(fp, m.group(1))
        if rel:
            out.add(rel.rstrip("/"))
    return out


def covered(rel, allow):
    if rel in allow:
        return True
    return any(rel.startswith(d + "/") for d in allow if (REPO / d).is_dir())


def check(files, strict, disk):
    pend = pending()
    tracked_files, tracked_dirs = tracked()
    allow = link_targets("docs/wiki/Reference-index.md") | link_targets("README.md")
    n_links, broken, pend_hits, warns = 0, [], [], []
    n_cites, n_cite_tracked, n_cite_untracked, private, dangling = 0, 0, 0, [], []
    for f in files:
        fp = REPO / f
        if not fp.exists():
            if f in pend:
                pend_hits.append((f, "<the document itself>", pend[f]))   # promised by a later task, tracked
            else:
                broken.append((f, "<file itself>", "document missing"))
            continue
        text = fp.read_text(encoding="utf-8", errors="replace")
        in_wiki = f.startswith(WIKI_DIRS)
        for m in LINK_RE.finditer(text):
            tgt = m.group(1)
            if tgt.startswith(SKIP_PREFIX):
                continue
            n_links += 1
            path = tgt.split("#", 1)[0]
            if not path:
                continue
            resolved = (REPO / path.lstrip("/")) if path.startswith("/") else (fp.parent / path)
            rel = rel_of(fp, tgt)
            if not resolved.exists():
                if rel in pend:
                    pend_hits.append((f, tgt, pend[rel]))
                else:
                    broken.append((f, tgt, "does not exist"))
                continue
            if rel is None:
                continue
            # 2. the archive: nothing links into docs/sunset/
            if rel.startswith(ARCHIVE_DIR):
                broken.append((f, tgt, "links into the archive (docs/sunset/) — cite it as a path, never a link"))
                continue
            # 3. wiki-first: a wiki page's docs/ target must be on the derived allow-list
            if in_wiki and f not in INDEX_PAGES and rel.startswith("docs/") and not rel.startswith(WIKI_DIRS):
                if not covered(rel.rstrip("/"), allow):
                    broken.append((f, tgt, "a docs/ target the Reference index does not list (wiki-first policy)"))
                    continue
            # 6. wiki-first warnings for everything else (never the README, never a wiki page)
            if not in_wiki and f != "README.md" and rel in TOPIC_PAGE:
                warns.append((f, tgt, TOPIC_PAGE[rel]))
        # 5. citations
        for m in CITE_RE.finditer(text):
            cite = m.group(1).rstrip(".,;:)")
            if any(ch in cite for ch in "<>*{}…") or cite.endswith("/…"):
                continue                                          # a placeholder or a glob, not a path
            n_cites += 1
            # `path:12`, `path:12-19`, `path:8017EC48-8017EC70` cite lines/addresses inside the file — look up the file
            key = re.sub(r":[0-9A-Fa-f]+(?:[-,][0-9A-Fa-f]+)*$", "", cite).rstrip("/")
            if key in tracked_files or key in tracked_dirs:
                n_cite_tracked += 1
                continue
            n_cite_untracked += 1
            if in_wiki:
                broken.append((f, cite, "cites an UNTRACKED path — a wiki reader cannot follow it"))
            if disk:
                (private if (REPO / key).exists() else dangling).append((f, cite))
    # 4. coverage of docs/ by the index + the README
    out = subprocess.run(["git", "-C", str(REPO), "ls-files", "-z", "docs"], capture_output=True, text=True, check=True).stdout
    docs_files = [p for p in out.split("\0") if p and not p.startswith(WIKI_DIRS) and not p.startswith(ARCHIVE_DIR)]
    uncovered = sorted(p for p in docs_files if not covered(p, allow))
    print(f"doc_links: {len(files)} documents, {n_links} relative links checked, {len(pend_hits)} pending "
          f"({len(pend)} planned targets on the list), {len(broken)} broken; citations {n_cites} "
          f"({n_cite_tracked} tracked, {n_cite_untracked} untracked); docs/ coverage {len(docs_files) - len(uncovered)} of "
          f"{len(docs_files)} covered by the Reference index + README; {len(warns)} wiki-first warnings")
    for f, t, why in broken:
        print(f"  BROKEN  {f}: ({t}) {why}")
    for p in uncovered:
        print(f"  UNCOVERED {p}: no Reference-index or README row covers it")
    for f, t, task in sorted(set(pend_hits)):
        print(f"  PENDING {f}: ({t}) — created by {task}")
    for f, t, page in sorted(set(warns)):
        print(f"  WARN    {f}: ({t}) has a wiki page — {page}")
    if disk:
        print(f"doc_links --disk: of {n_cite_untracked} untracked citations, {len(private)} PRIVATE (on this disk), "
              f"{len(dangling)} DANGLING (nowhere)")
        for f, c in dangling:
            print(f"  DANGLING {f}: `{c}`")
    if broken or uncovered:
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
    ap.add_argument("--disk", action="store_true", help="local only: split untracked citations by on-disk presence")
    a = ap.parse_args(argv)
    return check(a.files or default_files(), a.strict, a.disk)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
