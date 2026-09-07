#!/usr/bin/env python3
"""wiki_render.py — render docs/wiki/ + docs/how-to-ai-decomp/ into GitHub-wiki pages (P33 F3; used by tools/wiki_sync.sh).

    tools/wiki_render.py OUT_DIR        # write every rendered page into OUT_DIR (created if needed; other files untouched)
    tools/wiki_render.py --list         # print `source -> page` for every page, render nothing
    tools/wiki_render.py --selftest     # the link-rewrite fixture (exit 0 = OK); in `make tools-health`

The wiki is AUTHORED IN THE REPOSITORY (owner decision 8, gate 1): `docs/wiki/*.md` are the project-wiki pages and
`docs/how-to-ai-decomp/NN-*.md` the how-to chapters, written as ordinary Markdown with RELATIVE links so that
`tools/doc_links.py` checks them like every other document. A GitHub wiki is a separate repository whose pages are
addressed by NAME (no `.md`, no directories, `-` shown as a space), so the render rewrites every relative link
deterministically:

  * a link to another `docs/wiki/X.md`                  -> `X`                       (fragment kept)
  * a link to `docs/how-to-ai-decomp/NN-name.md`        -> `How-to-AI-decomp-NN-name`
  * any other relative link that resolves INSIDE the repo -> https://github.com/Druthulu/BFM-decomp/blob/main/<path>
                                                            (`tree/main/` for a directory; `raw.githubusercontent.com` for images)
  * URLs, `mailto:`, bare `#anchors`                     -> untouched
  * a relative link that resolves to NOTHING              -> an ERROR (exit 1) — the render refuses to publish a dead link (R43)

Page names: `docs/wiki/X.md` -> `X.md`; `docs/how-to-ai-decomp/NN-name.md` -> `How-to-AI-decomp-NN-name.md`;
`_Sidebar.md` / `_Footer.md` keep their names (GitHub's navigation files). The repository copy is the source of truth:
a page edited on GitHub is overwritten by the next sync.
"""
import argparse
import pathlib
import re
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
WIKI_DIR = REPO / "docs" / "wiki"
HOWTO_DIR = REPO / "docs" / "how-to-ai-decomp"
HOWTO_PREFIX = "How-to-AI-decomp-"
GH = "https://github.com/Druthulu/BFM-decomp"
RAW = "https://raw.githubusercontent.com/Druthulu/BFM-decomp/main"
SKIP_PREFIX = ("http://", "https://", "mailto:", "#", "ftp://")
# `![alt](target "title")` and `[text](target "title")`; group 1 = "!" for an image
LINK_RE = re.compile(r"(!?)\[([^\]]*)\]\(([^)\s]+)((?:\s+\"[^\"]*\")?)\)")


class RenderError(Exception):
    pass


def page_name(src: pathlib.Path) -> str:
    """The wiki page file name for a source file (with .md)."""
    if src.parent == WIKI_DIR:
        return src.name
    if src.parent == HOWTO_DIR:
        return HOWTO_PREFIX + src.name
    raise RenderError(f"{src}: not under docs/wiki/ or docs/how-to-ai-decomp/")


def sources():
    return sorted(WIKI_DIR.glob("*.md")) + sorted(HOWTO_DIR.glob("*.md"))


def rewrite_target(src: pathlib.Path, target: str, is_image: bool) -> str:
    if target.startswith(SKIP_PREFIX):
        return target
    path, sep, frag = target.partition("#")
    if not path:
        return target
    resolved = (REPO / path.lstrip("/")) if path.startswith("/") else (src.parent / path)
    try:
        resolved = resolved.resolve()
        rel = resolved.relative_to(REPO)
    except (OSError, ValueError):
        raise RenderError(f"{src.relative_to(REPO)}: link ({target}) leaves the repository")
    if not resolved.exists():
        raise RenderError(f"{src.relative_to(REPO)}: link ({target}) resolves to nothing — refusing to render a dead link")
    if resolved.suffix == ".md" and resolved.parent == WIKI_DIR:
        return resolved.stem + sep + frag
    if resolved.suffix == ".md" and resolved.parent == HOWTO_DIR:
        return HOWTO_PREFIX + resolved.stem + sep + frag
    if is_image:
        return f"{RAW}/{rel.as_posix()}"
    kind = "tree" if resolved.is_dir() else "blob"
    return f"{GH}/{kind}/main/{rel.as_posix()}" + sep + frag


def render_text(src: pathlib.Path, text: str) -> str:
    def sub(m):
        bang, label, target, title = m.groups()
        return f"{bang}[{label}]({rewrite_target(src, target, bang == '!')}{title})"
    return LINK_RE.sub(sub, text)


def render_all(out_dir: pathlib.Path):
    out_dir.mkdir(parents=True, exist_ok=True)
    n_pages, n_links = 0, 0
    for src in sources():
        text = src.read_text(encoding="utf-8")
        n_links += sum(1 for m in LINK_RE.finditer(text) if not m.group(3).startswith(SKIP_PREFIX))
        (out_dir / page_name(src)).write_text(render_text(src, text), encoding="utf-8")
        n_pages += 1
    if n_pages == 0:
        raise RenderError("no source pages found (docs/wiki/*.md, docs/how-to-ai-decomp/*.md) — nothing to render")
    print(f"wiki_render: {n_pages} pages rendered into {out_dir} ({n_links} relative links rewritten)")


def selftest():
    """Known-true fixture: one of every link kind against files that exist (R39 — a control before any publish)."""
    src = WIKI_DIR / "Home.md"
    cases = [
        ("[a](Build-from-your-own-disc.md)", "[a](Build-from-your-own-disc)"),
        ("[b](Build-from-your-own-disc.md#recipe)", "[b](Build-from-your-own-disc#recipe)"),
        ("[c](../how-to-ai-decomp/00-README.md)", "[c](How-to-AI-decomp-00-README)"),
        ("[d](../verification.md)", f"[d]({GH}/blob/main/docs/verification.md)"),
        ("[e](../../README.md#license)", f"[e]({GH}/blob/main/README.md#license)"),
        ("[f](../../tools/)", f"[f]({GH}/tree/main/tools)"),
        ("[g](/docs/SETUP.md)", f"[g]({GH}/blob/main/docs/SETUP.md)"),
        ("![h](../story-timeline.svg)", f"![h]({RAW}/docs/story-timeline.svg)"),
        ("[i](https://example.org/x.md)", "[i](https://example.org/x.md)"),
        ("[j](#anchor)", "[j](#anchor)"),
        ("[k](mailto:x@y.z)", "[k](mailto:x@y.z)"),
    ]
    bad = 0
    for given, want in cases:
        got = render_text(src, given)
        if got != want:
            bad += 1
            print(f"  FAIL {given!r} -> {got!r} (want {want!r})")
    # the negative control: a dead link must raise, never render
    try:
        render_text(src, "[z](No-such-page.md)")
        bad += 1
        print("  FAIL a dead link rendered instead of raising")
    except RenderError:
        pass
    print(f"wiki_render --selftest: {len(cases) + 1} cases, {bad} failed")
    return 1 if bad else 0


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("out_dir", nargs="?")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--selftest", action="store_true")
    a = ap.parse_args(argv)
    if a.selftest:
        return selftest()
    if a.list:
        for src in sources():
            print(f"{src.relative_to(REPO)} -> {page_name(src)}")
        return 0
    if not a.out_dir:
        ap.error("OUT_DIR is required (or --list / --selftest)")
    try:
        render_all(pathlib.Path(a.out_dir))
    except RenderError as e:
        print(f"wiki_render: ERROR {e}")
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
