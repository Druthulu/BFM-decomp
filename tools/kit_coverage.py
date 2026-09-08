#!/usr/bin/env python3
"""Assert that the day-one kit's distillation cites (or explicitly dispositions) EVERY rule and EVERY hindsight entry of the source project.

P33.5 task 14.5 (Drew, 2026-09-07: "the whole of our experience?"). The kit's registry seed (G-rules) and kernels (DK) were written
from the distilled records; this tool derives the two source populations and refuses a silent gap (R32):

  * the RULES — every `- **R<n>` heading of phase-ends/DIGEST.md §3 (asserted contiguous 1..N) — must be cited by a `provenance:`
    line of decomp-architect/templates/registry-E.decomp.md, OR have a disposition row in config/kit_coverage_map.tsv
    (kind=rule): `G<ids>` (it became those rules — the ids must exist), `DK-<n>` (realised as a kernel), `ENV`
    (environment-specific, not portable), `PA` (ProjectArchitect's own rule), `FOLDED:G<id>` (absorbed into a named rule without
    a citation), `SEED:<file>` (a memory seed of the kit), `KIT:<path>` (a template or installer step), `RECORD` (kept only in the
    verbatim record — a project-specific procedure rule);
  * the ACCELERATORS — every entry of docs/accelerators.md at SUB-ENTRY granularity (the `## ` headings, and within a heading
    the bold `**(n)` / `**n.` items) — must be cited by a `provenance:` line of decomp-architect/corpus/decomp-kernels.md or of
    the registry seed, OR have a disposition row (kind=accelerator): `DK-<n>` / `G<n>` (folded, uncited), `COOKBOOK` (an
    idiom-level entry that lives in the cookbook corpus), `RECORD`, `NOT-PORTABLE` (this project only — the note says why).

Every count is printed with its denominator (R41); an unknown key or an unknown G/DK id in the map is refused (R43); a row for an
entry that IS cited is informational (printed, not an error). Exit 1 on any gap. In `make tools-health` after tool_census --check.
"""
import csv
import pathlib
import re
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
DIGEST = REPO / "phase-ends" / "DIGEST.md"
ACCEL = REPO / "docs" / "accelerators.md"
REGISTRY = REPO / "decomp-architect" / "templates" / "registry-E.decomp.md"
KERNELS = REPO / "decomp-architect" / "corpus" / "decomp-kernels.md"
MAP = REPO / "config" / "kit_coverage_map.tsv"
RULE_DISPOSITIONS = ("ENV", "PA", "RECORD")
ACCEL_DISPOSITIONS = ("COOKBOOK", "RECORD", "NOT-PORTABLE")


def provenance_lines(path):
    return [ln for ln in path.read_text(encoding="utf-8").splitlines() if ln.startswith("provenance:")]


def rule_ids():
    ids = sorted({int(m) for m in re.findall(r"^- \*\*R(\d+)\b", DIGEST.read_text(encoding="utf-8"), re.M)})
    if ids != list(range(1, ids[-1] + 1)):
        sys.exit(f"kit_coverage: DIGEST §3 rule ids are not contiguous 1..{ids[-1]}: missing {sorted(set(range(1, ids[-1] + 1)) - set(ids))}")
    return ids


def g_ids():
    return {int(m) for m in re.findall(r"^### G(\d+)\b", REGISTRY.read_text(encoding="utf-8"), re.M)}


def dk_ids():
    return {int(m) for m in re.findall(r"^### DK-(\d+)\b", KERNELS.read_text(encoding="utf-8"), re.M)}


def accel_entries():
    """[(key, heading-or-item text, line)] — one per `## ` heading; a heading with bold numbered items yields one per item instead."""
    lines = ACCEL.read_text(encoding="utf-8").splitlines()
    heads = [(i, ln[3:].strip()) for i, ln in enumerate(lines) if ln.startswith("## ")]
    out = []
    for n, (i, title) in enumerate(heads):
        end = heads[n + 1][0] if n + 1 < len(heads) else len(lines)
        m = re.match(r"(A\d+|#\d+|S\d+(?: \(\d+\))?|P\d+(?:\.\d+)?(?: [A-Z]\w*)?(?: S\d+)?)\b", title)
        if m:
            group = m.group(1)
        else:
            t = re.search(r"\((P\d+ S\d+)\)", title)
            group = t.group(1) if t else title
        items = [(j, lines[j]) for j in range(i + 1, end) if re.match(r"^\*\*(\(\d+\)|\d+\.)\s", lines[j])]
        if items:
            for j, ln in items:
                num = re.match(r"^\*\*\(?(\d+)", ln).group(1)
                out.append((f"{group} ({num})", ln[2:80].strip("* "), j + 1))
        else:
            out.append((group, title, i + 1))
    return out


def accel_cited(key, prov_text):
    """Is this entry cited by any provenance line? Token rules mirror how the kernels cite the ledger (see the census in the task log)."""
    m = re.match(r"^(A\d+|#\d+|S\d+|P\d+(?:\.\d+)?(?: [A-Z]\w*)?(?: S\d+)?)(?: \((\d+)\))?$", key)
    if not m:
        return False
    group, num = m.group(1), m.group(2)
    tok = re.escape(group.split(" ")[0])
    if group.startswith("P31 S58"):        # the harness wounds, cited as "harness wound n" or "… wounds" 1–5 (a range)
        for ln in prov_text:
            if "accelerator" not in ln.lower() or "wound" not in ln.lower():
                continue
            tail = ln.lower().split("wound", 1)[1][:60]
            nums = set()
            for a, b in re.findall(r"(\d+)\s*[–-]\s*(\d+)", tail):
                nums |= set(range(int(a), int(b) + 1))
            nums |= {int(x) for x in re.findall(r"(?<![\d–-])(\d+)(?![\d–-])", tail)}
            if num is None or int(num) in nums:
                return True
        return False
    if group.startswith("P31 S71"):      # the journals entry
        pat = r"(journal|S71)"
    elif num:
        pat = rf"\b{tok}\b(?: [A-Z]\w*)? \({num}\b"
    else:
        pat = rf"(?<![\w.]){tok}\b(?! \()"
    for ln in prov_text:
        if "accelerator" in ln.lower() and re.search(pat, ln):
            return True
    return False


def read_map():
    rows = []
    if not MAP.exists():
        sys.exit(f"kit_coverage: {MAP.relative_to(REPO)} is missing (R43 — refuse, never assume an empty map)")
    with MAP.open(encoding="utf-8", newline="") as f:
        rd = csv.DictReader(f, delimiter="\t")
        if rd.fieldnames != ["kind", "key", "disposition", "note"]:
            sys.exit(f"kit_coverage: map columns must be kind/key/disposition/note, got {rd.fieldnames}")
        for r in rd:
            if r["kind"] not in ("rule", "accelerator") or not r["key"] or not r["disposition"]:
                sys.exit(f"kit_coverage: bad map row {r}")
            rows.append(r)
    return rows


def check_disposition(kind, disp, gs, dks):
    """Validate a disposition string; return an error string or None."""
    parts = [x.strip() for x in disp.split("+")]
    for part in parts:
        if kind == "rule" and part in RULE_DISPOSITIONS:
            continue
        if kind == "accelerator" and part in ACCEL_DISPOSITIONS:
            continue
        m = re.match(r"^(FOLDED:)?G(\d+)$", part)
        if m:
            if int(m.group(2)) not in gs:
                return f"G{m.group(2)} does not exist in the registry seed"
            continue
        m = re.match(r"^DK-(\d+)$", part)
        if m:                                  # a rule realised as a kernel, or an accelerator folded into one
            if int(m.group(1)) not in dks:
                return f"DK-{m.group(1)} does not exist in the kernels"
            continue
        m = re.match(r"^SEED:([\w-]+\.md)$", part)   # realised as a memory seed of the kit
        if m:
            if not (REPO / "decomp-architect" / "memory-seed" / m.group(1)).exists():
                return f"memory seed {m.group(1)} does not exist"
            continue
        m = re.match(r"^KIT:([\w./-]+)$", part)       # realised as a kit template / installer step (a file under the package)
        if m:
            if not (REPO / "decomp-architect" / m.group(1)).exists():
                return f"kit file {m.group(1)} does not exist"
            continue
        return f"unknown disposition token {part!r} for kind {kind}"
    return None


def main():
    rules = rule_ids()
    gs, dks = g_ids(), dk_ids()
    reg_prov = provenance_lines(REGISTRY)
    ker_prov = provenance_lines(KERNELS)
    cited_rules = {int(m) for ln in reg_prov for m in re.findall(r"\bR(\d+)\b", ln)}
    entries = accel_entries()
    prov_all = reg_prov + ker_prov
    cited_accel = {k for k, _, _ in entries if accel_cited(k, prov_all)}
    rows = read_map()
    errs, info = [], []
    map_rules = {}
    map_accel = {}
    for r in rows:
        e = check_disposition(r["kind"], r["disposition"], gs, dks)
        if e:
            errs.append(f"map row {r['kind']} {r['key']}: {e}")
        if r["kind"] == "rule":
            m = re.match(r"^R(\d+)$", r["key"])
            if not m or int(m.group(1)) not in rules:
                errs.append(f"map row names an unknown rule {r['key']!r} (rules are R1..R{rules[-1]})")
                continue
            map_rules[int(m.group(1))] = r
        else:
            if r["key"] not in {k for k, _, _ in entries}:
                errs.append(f"map row names an unknown accelerator entry {r['key']!r}")
                continue
            map_accel[r["key"]] = r
    uncovered_rules = [n for n in rules if n not in cited_rules and n not in map_rules]
    uncovered_accel = [(k, t, ln) for k, t, ln in entries if k not in cited_accel and k not in map_accel]
    for n in sorted(map_rules):
        if n in cited_rules:
            info.append(f"R{n} is cited AND dispositioned ({map_rules[n]['disposition']}) — the row is informational")
    for k in map_accel:
        if k in cited_accel:
            info.append(f"accelerator {k!r} is cited AND dispositioned ({map_accel[k]['disposition']}) — the row is informational")
    from collections import Counter
    rd = Counter(r["disposition"].split("+")[0].split(":")[0] for r in map_rules.values() if int(r["key"][1:]) not in cited_rules)
    ad = Counter(r["disposition"].split("+")[0] for k, r in map_accel.items() if k not in cited_accel)
    print(f"kit_coverage: rules R1..R{rules[-1]} — {len(cited_rules & set(rules))} cited by the registry seed's provenance lines, "
          f"{len([n for n in rules if n not in cited_rules and n in map_rules])} dispositioned ({dict(rd)}), {len(uncovered_rules)} UNCOVERED")
    print(f"kit_coverage: accelerators — {len(entries)} entries (headings + numbered items of docs/accelerators.md), "
          f"{len(cited_accel)} cited by kernel/registry provenance lines, {len([k for k, _, _ in entries if k not in cited_accel and k in map_accel])} dispositioned ({dict(ad)}), {len(uncovered_accel)} UNCOVERED")
    for i in info:
        print("  INFO", i)
    for n in uncovered_rules:
        errs.append(f"rule R{n} is neither cited by a registry provenance line nor dispositioned in {MAP.relative_to(REPO)}")
    for k, t, ln in uncovered_accel:
        errs.append(f"accelerator {k!r} (docs/accelerators.md:{ln} — {t[:60]}) is neither cited by a kernel/registry provenance line nor dispositioned")
    for e in errs:
        print("  GAP", e)
    print("kit_coverage: OK" if not errs else f"kit_coverage: FAIL ({len(errs)} gap(s))")
    return 1 if errs else 0


if __name__ == "__main__":
    sys.exit(main())
