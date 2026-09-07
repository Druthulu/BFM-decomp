#!/usr/bin/env python3
"""gitignore_template_check.py — the ROM-firewall wiki page's `.gitignore` template IS the kit's template, byte for byte
(P33.5 task 7; in tools-health once decomp-architect/templates/gitignore.decomp exists).

    tools/gitignore_template_check.py            # exit 1 on any difference; exit 2 when either source is missing (R43)

The wiki page docs/wiki/The-ROM-firewall.md carries one fenced block tagged ```gitignore; the day-one kit stamps
decomp-architect/templates/gitignore.decomp into a new repository. One source, two copies: this check refuses drift
between them (the same idea as `progress.py --check` for the README block — R75, generated once, copied never by hand).
"""
import pathlib
import re
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
PAGE = REPO / "docs" / "wiki" / "The-ROM-firewall.md"
TEMPLATE = REPO / "decomp-architect" / "templates" / "gitignore.decomp"
FENCE_RE = re.compile(r"```gitignore\n(.*?)\n```", re.S)


def main():
    if not PAGE.exists():
        sys.exit(f"gitignore_template_check: {PAGE.relative_to(REPO)} missing (R43)")
    fences = FENCE_RE.findall(PAGE.read_text(encoding="utf-8"))
    if len(fences) != 1:
        sys.exit(f"gitignore_template_check: expected exactly one ```gitignore fence in the page, found {len(fences)} (R43)")
    if not TEMPLATE.exists():
        print(f"gitignore_template_check: {TEMPLATE.relative_to(REPO)} does not exist yet — nothing to compare")
        return 2
    page_block = fences[0].rstrip("\n") + "\n"
    template = TEMPLATE.read_text(encoding="utf-8")
    if page_block == template:
        print(f"gitignore_template_check: OK — {len(template.splitlines())} lines identical in the page and the template")
        return 0
    import difflib
    diff = list(difflib.unified_diff(page_block.splitlines(), template.splitlines(), "wiki page", "kit template", lineterm=""))
    print("\n".join(diff[:60]))
    print(f"gitignore_template_check: DRIFT — {len(diff)} diff lines between the page's fence and the template")
    return 1


if __name__ == "__main__":
    sys.exit(main())
