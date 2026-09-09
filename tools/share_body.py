#!/usr/bin/env python3
"""share_body.py — give a byte-identical function class ONE source (Phase 35 T5): the permanent successor of dedup_propagate +
dedup_extend for the include-at-site form.

    tools/share_body.py --plan                             # the buckets: extend (registered-incomplete) / new (unregistered same-vram)
    tools/share_body.py --apply --bucket extend            # bucket 0: the registered classes whose members are not all sharing
    tools/share_body.py --apply --bucket new --batch 120 --limit N   # the unregistered same-vram classes, largest reach first
    tools/share_body.py --apply ... --only <h_exact>       # one class (the R37 probe)

WHAT ONE SHARE IS. A class = one h_exact (the raw instruction bytes) at one vram, with >=2 instances across the fleet, some of which
are still PRIVATE COPIES (a definition in that binary's own TU). Sharing it: the class's ONE body goes to (or already is) a plain-C
header under src/shared/<space>/ (macro_to_header's naming: func_<VRAM>[__h8].h, keyed by the class — R48), every private copy becomes
`#include "../shared/<space>/<header>"` at the SAME position (the copy's definition lines, nothing else — the TU keeps its own
declarations), and the registry gains the group (shorthand form, appended by text) or the members (dedup_extend.add_members_surgical).

THE EXEMPLAR (for an unregistered class) — printed with every share: the copy whose normalized text the MOST copies share; a tie goes
to a pin-free copy; a further tie to the shortest. A body defined under an asm-label alias (aF<ADDR>) gets its own binding
(macro_to_header.bind_alias_header). 91% of the backlog's classes have identical text in every copy (the census), so the exemplar is
usually every copy; the 9% with differing texts are where the gate earns its keep.

THE GATE, per batch: every private copy's edits applied bottom-up per TU (line numbers stay valid), then for every touched binary
(a twin's primary counts for the twin too): the objects snapshotted before, `make check BINARY=<b> -j16` (exit code), every object
compared. A red binary is BISECTED: its TUs restored, the batch's classes re-applied one at a time, the culprit's members in that
binary stay private and the class is LEDGERED in config/dedup_exceptions.tsv with the compiler's line (TU-CONFLICT / GATE-REJECT);
the class is registered with the members that passed. "shared" is printed only from the gate's success (R66). The clean fleet run
after the batch is the caller's (R22). Never `yaml.safe_dump` the registry (H5).

RUN IT ON A COMMITTED TREE, ONE BATCH PER INVOCATION (the default `--batches 1`). The edit positions come from the census taken at the
start of the run; a second batch in the same run would edit TUs the first batch already changed (stale lines → a red gate → a bisect
that restores the TU to its pre-batch text, dropping the first batch's shares). The bisect restores from an in-memory snapshot of the
TU taken before the batch's edits — never `git checkout` (S94 run 2 lost ~50 kept sites to exactly that). The failure cause is the
first `file:line: message` diagnostic that is not a warning (gcc 2.7.2 prints errors without the word "error"); the ledger's reason
code is derived from it: SYMBOL-NAME (undefined reference), GATE-REJECT (bytes differ), PARSE-ERROR (a parse error at or near the
site — replay it before believing the TU), TU-CONFLICT (a declaration conflict).
"""
import argparse
import collections
import json
import os
import pathlib
import re
import subprocess
import sys
import time

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
import share_census as sc            # noqa: E402
import macro_to_header as m2h        # noqa: E402 — Oracles (naming, spaces, sigs), bind_alias_header, include_line, banner
import dedup_extend as de            # noqa: E402 — add_members_surgical (the registry's surgical text edit)

LEDGER = REPO / "config/dedup_exceptions.tsv"
RUN = REPO / ".run/P35/share"


def log(msg):
    print(msg, flush=True)


# ----------------------------------------------------------------------------------------------------------------------------
def census(jobs):
    aliases, dirs = sc.fleet_and_dirs()
    spaces = sc.vram_bases()
    twins = sc.twin_sets(aliases)
    twin_of = sc.twin_of_map()
    sigs = {a: sc.sig_rows(a) for a in aliases}
    forms, notes = sc.build_forms(aliases, dirs, jobs, use_cache=True)
    groups = sc.load_groups()
    exceptions = sc.load_exceptions("config/dedup_exceptions.tsv")
    verb = sc.verbatim_instances()
    classes, cov = sc.classify(sigs, forms, groups, spaces, dirs, twins, twin_of, verb, exceptions, keep_instances=True)
    if cov["unaccounted"] or notes["multi_form"]:
        sys.exit(f"share_body: the census has {len(cov['unaccounted'])} unaccounted / {len(notes['multi_form'])} multi-form instances — fix "
                 f"the census first (R32)")
    return dict(aliases=aliases, dirs=dirs, spaces=spaces, twins=twins, twin_of=twin_of, forms=forms, groups=groups,
                exceptions=exceptions, classes=classes)


def candidates(cen):
    """(extend, new): the classes this tool shares. Same-vram only; twin-covered and excepted classes are satisfied already."""
    extend, new = [], []
    for c in cen["classes"]:
        if c["verdict"] == "A" or "E" in c["flags"] or "F" in c["flags"] or "TWIN-COVERED" in c["flags"] or c["excepted"]:
            continue
        priv = [i for i in c["insts"] if i["form"] == "def"]
        if c["verdict"] == "B":
            extend.append(c)
        elif priv:
            new.append(c)
    new.sort(key=lambda c: (-c["instances"], -c["nins"], c["h"]))
    extend.sort(key=lambda c: (-c["instances"], -c["nins"], c["h"]))
    return extend, new


def choose_exemplar(priv):
    by_text = collections.Counter(i["text_hash"] for i in priv)
    best = max(by_text.values())
    pool = [i for i in priv if by_text[i["text_hash"]] == best]
    pool.sort(key=lambda i: (i.get("pins", False), i.get("nlines", 0), i["alias"], i["tu"]))
    reason = "majority text" if best > 1 or len(priv) == 1 else "tie → pin-free, shortest"
    return pool[0], reason, dict(by_text)


def def_text(inst):
    """The definition's lines [line..end] of a private copy, from its TU."""
    tu = REPO / inst["tu"]
    lines = tu.read_text(errors="surrogateescape").split("\n")
    a, b = inst["line"] - 1, inst["end"]
    return "\n".join(lines[a:b]).rstrip("\n") + "\n"


# ----------------------------------------------------------------------------------------------------------------------------
class Batch:
    """Edits for a batch of classes: per TU a list of (start_line, end_line, replacement) applied bottom-up."""

    def __init__(self, orc, cen):
        self.orc, self.cen = orc, cen
        self.edits = collections.defaultdict(list)      # tu_rel -> [(line, end, new_text, h)]
        self.headers = {}                                # header rel -> text
        self.register = []                               # (id, hash, source, func, vram, [binaries])
        self.extend = collections.defaultdict(list)      # group id -> [binaries]
        self.touched = set()                             # binaries
        self.members = collections.defaultdict(list)     # h -> [(alias, tu)]
        self.exemplar_note = {}

    def add_class(self, c):
        h = c["h"]
        vram = int(c["addrs"][0], 16)
        priv = [i for i in c["insts"] if i["form"] == "def"]
        base = self.orc.bases[priv[0]["alias"]] if priv else self.orc.bases[c["insts"][0]["alias"]]
        fn = f"func_{vram:08X}"
        if c["verdict"] == "B":
            g = c["groups"][0]
            hdr = g["source"]
            defined = {n for n, _ in sc.header_defs(REPO / hdr)}
            if g.get("func") not in defined:
                return f"refused: {g['id']}'s source {hdr} does not define {g.get('func')}"
            listed = {b for b, _, _ in m2h.sc_group_members(g)}
            for i in c["insts"]:
                if i["alias"] not in listed:
                    self.extend[g["id"]].append(i["alias"])
            self.exemplar_note[h] = f"extend {g['id']} (+{len(self.extend.get(g['id'], []))} members, {len(priv)} private sites → include)"
        else:
            ex, reason, texts = choose_exemplar(priv)
            hdr = self.orc.header_rel(base, vram, h)
            if (REPO / hdr).exists():
                defined = {n for n, _ in sc.header_defs(REPO / hdr)}
                if fn not in defined:
                    return f"refused: {hdr} exists and does not define {fn} (defines {sorted(defined)[:3]})"
            else:
                body = def_text(ex)
                space_name = "overlay slot" if base == m2h.OV_BASE else self.orc.space_dir(base)
                text = m2h.banner(fn, base, h, space_name) + body
                text, _ = m2h.bind_alias_header(text, fn)
                self.headers[hdr] = text
            self.register.append((f"S_{fn}", h, hdr, fn, vram, sorted({i["alias"] for i in c["insts"]})))
            self.exemplar_note[h] = f"exemplar {ex['tu']}:{ex['line']} ({reason}; texts {len(texts)}), {len(priv)} private sites → include"
        seen_sites = set()
        for i in priv:
            inc = m2h.include_line(i["tu"], hdr)
            # ONE edit per site: a twin's instance resolves to its PRIMARY's TU, so a twin pair yields two identical (tu, line) records;
            # applied twice, the second replacement swallowed the NEXT function (S94 run 2: "parse error before `if'" and "undefined
            # reference to <the following function>" in exactly the five twin primaries — 7 classes rejected on the tool's own artifact)
            if (i["tu"], i["line"]) not in seen_sites:
                seen_sites.add((i["tu"], i["line"]))
                self.edits[i["tu"]].append((i["line"], i["end"], inc, h))
            self.touched.add(i["alias"])
            self.members[h].append((i["alias"], i["tu"]))
        for i in c["insts"]:
            self.touched.add(i["alias"])                 # twins of a touched primary are gated too (their objects change)
        return None

    def apply_edits(self, only_tus=None):
        n = 0
        for tu, eds in self.edits.items():
            if only_tus is not None and tu not in only_tus:
                continue
            p = REPO / tu
            lines = p.read_text(errors="surrogateescape").split("\n")
            for line, end, new, _ in sorted(eds, key=lambda e: -e[0]):
                lines[line - 1:end] = [new]
                n += 1
            p.write_text("\n".join(lines))
        return n

    def write_headers(self):
        for hdr, text in self.headers.items():
            p = REPO / hdr
            if p.exists():
                if p.read_text(errors="surrogateescape") != text:
                    sys.exit(f"share_body: {hdr} exists with different text — the naming rule missed a collision (R43)")
                continue
            p.parent.mkdir(parents=True, exist_ok=True)
            p.write_text(text)


# ----------------------------------------------------------------------------------------------------------------------------
def objdir(alias):
    return REPO / ("build/src" if alias == "main" else f"build/src/{alias}")


def snapshot(aliases):
    snap = {}
    for a in aliases:
        d = objdir(a)
        snap[a] = {p.name: p.read_bytes() for p in d.glob("*.o")} if d.exists() else {}
    return snap


def gate(alias, snap):
    """(ok, detail): make check by exit code, then every object compared with the snapshot."""
    log_p = RUN / f"check_{alias}.log"
    with open(log_p, "w") as f:
        r = subprocess.run(["make", "check", f"BINARY={alias}", "-j16"], cwd=REPO, stdout=f, stderr=subprocess.STDOUT)
    if r.returncode != 0:
        return False, failure_cause(log_p.read_text(errors="replace"))
    d = objdir(alias)
    same = diff = 0
    for name, data in snap.get(alias, {}).items():
        q = d / name
        if q.exists() and q.read_bytes() == data:
            same += 1
        else:
            diff += 1
    if diff:
        return False, f"object A/B: {same}/{same + diff} — {diff} object(s) differ"
    return True, f"BYTE-IDENTICAL, obj A/B {same}/{same + diff}"


DIAG = re.compile(r"^(\S+?):(\d+|\(\.\w+\+0x[0-9a-f]+\)): (.*)$")
BANNER = re.compile(r"^(warning:|note:|In function|At top level|In file included|previous (declaration|definition|external))")


def failure_cause(txt):
    """The FIRST real diagnostic in a red gate's log. gcc 2.7.2 prints an error as `file:line: message` with NO 'error' token
    (`too many arguments to function`, `conflicting types for`, `parse error before`) and a warning as `file:line: warning: …`; the linker
    prints `file:(.text+0x..): undefined reference to …`; the assembler `{standard input}:N: Error: …`. Matching the word "error"
    labelled 254 of 303 rejections `make: *** [...] Error 33` (cc1's fatal exit status) in S94 run 2 — the message was never read."""
    lines = txt.splitlines()
    for ln in lines:
        m = DIAG.match(ln)
        # gcc 2.7.2 sometimes chains locations: `a.h:65: b.h:15: warning: passing arg …` — a warning anywhere on the line disqualifies it
        if m and not BANNER.match(m.group(3)) and " warning: " not in ln and " note: " not in ln:
            return ln[:200]
    for ln in lines:
        if re.search(r"\{standard input\}.*Error|undefined reference|multiple definition|\[FAIL\]", ln):
            return ln[:200]
    err = [ln for ln in lines if "warning:" not in ln and re.search(r"\berror\b|Error\b", ln)]
    return (err[0] if err else lines[-1] if lines else "make check failed")[:200]


def reason_for(cause):
    """The ledger's reason code from the cause line (config/dedup_exceptions.tsv's header documents the codes)."""
    if "undefined reference" in cause:
        return "SYMBOL-NAME"
    if "[FAIL]" in cause or "object A/B" in cause:
        return "GATE-REJECT"
    if "parse error" in cause:
        return "PARSE-ERROR"
    return "TU-CONFLICT"


def tu_snapshot(tus):
    """The text of every TU about to be edited — the ONLY restore source. (A `git checkout` restored the COMMITTED text and wiped the
    previous batch's uncommitted shares in every bisected TU — S94 run 2 lost ~50 kept sites that way; R42 applies to tools too.)"""
    return {tu: (REPO / tu).read_text(errors="surrogateescape") for tu in tus}


def restore(tus, tu_snap):
    for tu in tus:
        (REPO / tu).write_text(tu_snap[tu])


def ledger_row(h, reason, nins, instances, note):
    with open(LEDGER, "a") as f:
        f.write(f"{h}\t{reason}\t{nins}\t{instances}\t{note}\n")


def registry_append(entries):
    """Append shorthand groups by text at the end of config/dedup.us.yaml (never a yaml dump — H5)."""
    p = REPO / "config/dedup.us.yaml"
    t = p.read_text()
    if not t.endswith("\n"):
        t += "\n"
    out = []
    for gid, h, src, fn, vram, bins in entries:
        out.append(f"  - id: {gid}\n    tier: h_exact\n    hash: {h}\n    source: {src}\n    func: {fn}\n    vram: 0x{vram:08X}\n"
                   f"    binaries: [{', '.join(bins)}]\n")
    p.write_text(t + "".join(out))


def run_batch(orc, cen, classes, label):
    b = Batch(orc, cen)
    refused = []
    for c in classes:
        why = b.add_class(c)
        if why:
            refused.append((c["h"], why))
    for h, why in refused:
        log(f"  refuse {h[:10]}: {why}")
    twins_of = collections.defaultdict(list)
    for t, prim in cen["twin_of"].items():
        twins_of[prim].append(t)
    gated = sorted(b.touched | {t for a in b.touched for t in twins_of.get(a, [])})
    snap = snapshot(gated)
    tu_snap = tu_snapshot(b.edits.keys())          # the pre-edit text of every TU this batch touches (the bisect restores from it)
    b.write_headers()
    b.apply_edits()
    log(f"  [{label}] {len(classes) - len(refused)} classes · {sum(len(v) for v in b.edits.values())} sites in {len(b.edits)} TUs · "
        f"{len(b.headers)} new headers · gating {len(gated)} binaries")
    failed_classes = set()
    causes = {}                                      # h -> (binary, the first cause line)
    results = {}
    for a in gated:
        ok, detail = gate(a, snap)
        results[a] = (ok, detail)
        if ok:
            continue
        # BISECT this binary: restore its TUs, re-apply the batch's classes one at a time
        my_tus = {tu for tu in b.edits if tu.startswith(cen["dirs"][a] + "/") or (a == "main" and tu.count("/") == 1)}
        prim = cen["twin_of"].get(a)
        if prim:
            my_tus = {tu for tu in b.edits if tu.startswith(cen["dirs"][prim] + "/")}
        restore(my_tus, tu_snap)
        by_class = collections.defaultdict(lambda: collections.defaultdict(list))
        for tu in my_tus:
            for e in b.edits[tu]:
                by_class[e[3]][tu].append(e)
        def apply_selected(selected):
            """From the RESTORED original text: every selected class's edits per TU in ONE bottom-up pass, so the original line
            numbers stay valid (a per-class sequential re-application shifted later classes' lines — the first bisect rejected
            125 of 183 classes on artifacts of its own: duplicate definitions and parse errors at the shifted sites)."""
            restore(my_tus, tu_snap)
            per_tu = collections.defaultdict(list)
            for hh in selected:
                for tu, eds in by_class[hh].items():
                    per_tu[tu].extend(eds)
            for tu, eds in per_tu.items():
                p = REPO / tu
                lines = p.read_text(errors="surrogateescape").split("\n")
                for line, end, new, _ in sorted(eds, key=lambda e: -e[0]):
                    lines[line - 1:end] = [new]
                p.write_text("\n".join(lines))

        good = []
        for h, tus in sorted(by_class.items(), key=lambda kv: kv[0]):
            apply_selected(good + [h])
            ok2, det2 = gate(a, snap)
            if ok2:
                good.append(h)
            else:
                failed_classes.add(h)
                causes.setdefault(h, (a, det2))
                log(f"  [{label}] {a}: class {h[:10]} REJECTED — {det2}")
                apply_selected(good)              # leave the good ones applied
        ok3, det3 = gate(a, snap)
        results[a] = (ok3, det3 + f" (after bisect: {len(good)} classes kept, {len(by_class) - len(good)} rejected)")
        if not ok3:
            sys.exit(f"share_body: {a} still red after the bisect ({det3}) — stopping (R43)")
    # register: new groups with the members that passed; extensions likewise; ledger the rejected
    reg_entries = []
    for gid, h, src, fn, vram, bins in b.register:
        if h in failed_classes:
            # members that passed = private sites whose binary gated green with this class kept... a class rejected in ANY
            # binary is registered with the others only when its header exists and at least 2 members share it
            kept = [a for a in bins if a not in {al for al, tu in b.members[h] if not results.get(al, (True,))[0]}]
            # conservative: a rejected class is ledgered whole; its passing members keep the include, the group lists them
            passing = [a for a in bins if results.get(a, (True,))[0] and a not in rejected_in(b, h, cen)]
            if len(passing) >= 2:
                reg_entries.append((gid, h, src, fn, vram, passing))
            c = next(x for x in classes if x["h"] == h)
            cb, cause = causes.get(h, ("?", "?"))
            ledger_row(h, reason_for(cause), c["nins"], c["instances"],
                       f"share_body {label}: rejected in {sorted(rejected_in(b, h, cen))}; registered for {len(passing)}; cause ({cb}): {cause}")
        else:
            reg_entries.append((gid, h, src, fn, vram, bins))
    if reg_entries:
        registry_append(reg_entries)
    # a rejected EXTEND class is ledgered too (its private copies in the rejecting binaries stay)
    for c in classes:
        if c["verdict"] == "B" and c["h"] in failed_classes:
            cb, cause = causes.get(c["h"], ("?", "?"))
            ledger_row(c["h"], reason_for(cause), c["nins"], c["instances"],
                       f"share_body {label}: extend of {c['groups'][0]['id']} rejected in {sorted(rejected_in(b, c['h'], cen))}; "
                       f"cause ({cb}): {cause}")
    # extend a group ONLY with members whose sharing survived the gate (a rejected class's binaries keep their private copy
    # and must not be listed as sharing — the registry never runs ahead of the source)
    rejected_bins = {}
    for c in classes:
        if c["h"] in failed_classes:
            rejected_bins[c["h"]] = rejected_in(b, c["h"], cen)
    ext = {}
    for c in classes:
        if c["verdict"] != "B":
            continue
        gid = c["groups"][0]["id"]
        bins = [x for x in b.extend.get(gid, []) if x not in rejected_bins.get(c["h"], set())]
        if bins:
            ext[gid] = bins
    n_ext = de.add_members_surgical(ext) if ext else 0
    ok_n = sum(1 for a in gated if results[a][0])
    log(f"  [{label}] gated {ok_n}/{len(gated)} binaries green · registered {len(reg_entries)} groups · extended {n_ext} members · "
        f"rejected classes {len(failed_classes)}")
    (RUN / f"batch_{label}.json").write_text(json.dumps(dict(classes=[c["h"] for c in classes], refused=refused,
                                                                results=results, registered=[e[0] for e in reg_entries],
                                                                extended=ext, rejected=sorted(failed_classes),
                                                                causes=causes, exemplars=b.exemplar_note), indent=1) + "\n")
    return len(failed_classes) == 0 and all(results[a][0] for a in gated)


def repair_registry(cen):
    """Remove every listed member whose site is still a PRIVATE definition — the registry ahead of the source. Derived from the census
    (a verdict-B class's `def` instances whose alias the group lists), never typed; shorthand `binaries: [...]` lines edited by text;
    a verbose group with such a member is reported and left alone. (S94's first pass extended 788 members wholesale before the
    "only members that passed" rule existed; 317 of them were private after run 2, plus the sites a bisect had wiped.)"""
    removals = collections.defaultdict(set)
    verbose = []
    for c in cen["classes"]:
        if c["verdict"] != "B":
            continue
        for g in c.get("groups", []):
            # match on (binary, vram): h_exact is position-independent, so one class can span several vrams and a listed binary
            # may carry a PRIVATE copy of the same bytes at ANOTHER address (the first cut matched the name alone and removed 9,269)
            listed = {(bn, addr) for bn, addr, _ in m2h.sc_group_members(g)}
            for i in c["insts"]:
                if i["form"] == "def" and (i["alias"], i["addr"]) in listed:
                    (verbose.append((g["id"], i["alias"])) if g.get("members") else removals[g["id"]].add(i["alias"]))
    p = REPO / "config/dedup.us.yaml"
    lines = p.read_text().splitlines(keepends=True)
    cur, n_removed, touched, thin = None, 0, 0, []
    for k, ln in enumerate(lines):
        m = re.match(r"^\s*-?\s*id:\s*(\S+)\s*$", ln)
        if m:
            cur = m.group(1)
            continue
        if cur and cur in removals and re.match(r"^\s*binaries:\s*\[", ln):
            head, rest = ln.split("[", 1)
            inner, tail = rest.split("]", 1)
            names = [x.strip() for x in inner.split(",") if x.strip()]
            keep = [x for x in names if x not in removals[cur]]
            n_removed += len(names) - len(keep)
            touched += 1
            if len(keep) < 2:
                thin.append((cur, keep))
            lines[k] = f"{head}[{', '.join(keep)}]{tail}"
            cur = None
    p.write_text("".join(lines))
    rec = dict(groups=touched, members_removed=n_removed, removals={g: sorted(v) for g, v in removals.items()},
               thin_groups=thin, verbose_skipped=verbose)
    (RUN / "repair_registry.json").write_text(json.dumps(rec, indent=1) + "\n")
    log(f"repair-registry: {n_removed} listed-but-private members removed from {touched} groups; groups left with <2 members: "
        f"{len(thin)} {thin[:5]}; verbose groups with a private member (left alone): {len(verbose)} {verbose[:5]}")
    return rec


def reexemplar(orc, cen, prefix):
    """A registered class whose header carries a MINORITY text (T4 wrote the header from whichever group existed — for E_func_80168B70
    the 7 late overlays' spelling, refused by the 134 main overlays' declaration environments): rewrite the header from the MAJORITY
    private text (the same rule a new class gets), gate every current includer's binary FIRST (the header rolled back on any red), then
    share the private copies as a normal extend batch. The class's ledger row is dropped when the run shares anything."""
    cs = [c for c in cen["classes"] if c["h"].startswith(prefix)]
    if len(cs) != 1:
        sys.exit(f"share_body: --reexemplar {prefix}: {len(cs)} classes match (R43)")
    c = cs[0]
    if c["verdict"] != "B" or len(c.get("groups", [])) != 1:
        sys.exit(f"share_body: --reexemplar: {c['h'][:10]} is verdict {c['verdict']} with {len(c.get('groups', []))} groups — only a registered "
                 f"(B) class with one group can be re-exemplared")
    g = c["groups"][0]
    hdr = g["source"]
    priv = [i for i in c["insts"] if i["form"] == "def"]
    incl = [i for i in c["insts"] if i["form"] == "include"]
    if len(priv) <= len(incl):
        sys.exit(f"share_body: --reexemplar: {g['id']} has {len(priv)} private copies vs {len(incl)} includers — the header already carries "
                 f"the majority; nothing to re-exemplar")
    ex, reason, texts = choose_exemplar(priv)
    vram = int(c["addrs"][0], 16)
    fn = f"func_{vram:08X}"
    base = orc.bases[ex["alias"]]
    space_name = "overlay slot" if base == m2h.OV_BASE else orc.space_dir(base)
    new_text = m2h.banner(fn, base, c["h"], space_name) + def_text(ex)
    new_text, _ = m2h.bind_alias_header(new_text, fn)
    p = REPO / hdr
    old_text = p.read_text(errors="surrogateescape")
    (RUN / f"reexemplar_{c['h'][:8]}.old.h").write_text(old_text)
    p.write_text(new_text)
    if fn not in {n for n, _ in sc.header_defs(p)}:
        p.write_text(old_text)
        sys.exit(f"share_body: --reexemplar: the majority text does not define {fn} (R32); header restored")
    log(f"reexemplar {g['id']}: header {hdr} ← {ex['tu']}:{ex['line']} ({reason}; texts {len(texts)}); {len(priv)} private copies, "
        f"{len(incl)} includers to re-gate first")
    twins_of = collections.defaultdict(list)
    for t, prim in cen["twin_of"].items():
        twins_of[prim].append(t)
    gated = sorted({i["alias"] for i in incl} | {t for i in incl for t in twins_of.get(i["alias"], [])})
    snap = snapshot(gated)
    for a in gated:
        ok, det = gate(a, snap)
        if not ok:
            p.write_text(old_text)
            gate(a, snap)                                  # rebuild the includer with the old header so its objects are green again
            sys.exit(f"share_body: --reexemplar: includer {a} REJECTS the majority text — {det}; header restored, nothing shared (R43)")
    log(f"reexemplar {g['id']}: {len(gated)}/{len(gated)} includer binaries green under the majority text")
    ok = run_batch(orc, cen, [c], f"reex_{c['h'][:8]}")
    # the old ledger row (written for the minority header) is superseded by this run's verdict
    lines = LEDGER.read_text().split("\n")
    kept = [ln for ln in lines if not (ln.startswith(c["h"]) and "reex_" not in ln)]
    if len(kept) != len(lines):
        LEDGER.write_text("\n".join(kept))
        log(f"reexemplar {g['id']}: the previous ledger row dropped ({len(lines) - len(kept)})")
    return ok


def rejected_in(b, h, cen):
    """The binaries in which class h was rejected (their private sites restored by the bisect)."""
    out = set()
    for alias, tu in b.members[h]:
        p = REPO / tu
        text = p.read_text(errors="surrogateescape")
        hdr_inc = [e[2] for e in b.edits[tu] if e[3] == h]
        if hdr_inc and hdr_inc[0] not in text:
            out.add(alias)
    return out


# ----------------------------------------------------------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--plan", action="store_true")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--bucket", choices=["extend", "new"], default="new")
    ap.add_argument("--batch", type=int, default=120)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--batches", type=int, default=1,
                    help="batches per invocation (default 1: every batch's edit positions come from THIS run's census, which read "
                         "committed text; commit between runs — a later batch would edit TUs the earlier one already changed)")
    ap.add_argument("--only", default="")
    ap.add_argument("--repair-registry", action="store_true",
                    help="remove every listed member whose site is still a private definition (derived from the census), then exit")
    ap.add_argument("--reexemplar", default="",
                    help="<h_exact prefix>: rewrite a registered class's header from the MAJORITY private text, re-gate its includers, "
                         "then share its private copies (the class's ledger row is dropped when anything shares)")
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()
    RUN.mkdir(parents=True, exist_ok=True)
    t0 = time.time()
    cen = census(a.jobs)
    if a.repair_registry:
        repair_registry(cen)
        return
    if a.reexemplar:
        orc = m2h.Oracles()
        ok = reexemplar(orc, cen, a.reexemplar)
        log(f"share_body: reexemplar done — {'all green' if ok else 'see the ledger'}; {time.time() - t0:.0f} s")
        return
    orc = m2h.Oracles()
    extend, new = candidates(cen)
    log(f"share_body: census {time.time() - t0:.0f} s · extend (registered-incomplete) {len(extend)} classes · new (unregistered same-vram) "
        f"{len(new)} classes / {sum(len([i for i in c['insts'] if i['form'] == 'def']) for c in new):,} private sites")
    if a.plan:
        bands = collections.Counter(c["band"] for c in new)
        log(f"  new by band: {dict(bands)}; differing-text classes {sum(1 for c in new if c['verdict'] == 'D')}; "
            f"with pins {sum(1 for c in new if 'PINS' in c['flags'])}; alias-form {sum(1 for c in new if 'ALIAS' in c['flags'])}")
        for c in new[:8]:
            log(f"    {c['verdict']} {','.join(c['flags']) or '-':14s} {c['instances']:4d} inst x {c['nins']:5d} ins {c['addrs'][0]} private {c['copies']}")
        return
    if not a.apply:
        return
    pool = extend if a.bucket == "extend" else new
    if a.only:
        pool = [c for c in pool if c["h"].startswith(a.only)]
    if a.limit:
        pool = pool[:a.limit]
    all_ok = True
    done = 0
    for k in range(0, len(pool), a.batch):
        if k // a.batch >= a.batches:
            log(f"share_body: stopping after {a.batches} batch(es) — {len(pool) - k} classes of this bucket remain; COMMIT, then re-run "
                f"(the census re-derives the pool from the committed text)")
            break
        chunk = pool[k:k + a.batch]
        ok = run_batch(orc, cen, chunk, f"{a.bucket}{k // a.batch + 1}")
        all_ok = all_ok and ok
        done += len(chunk)
    log(f"share_body: done — {done} of {len(pool)} classes in {min(a.batches, (len(pool) + a.batch - 1) // a.batch)} batch(es); "
        f"{'all green' if all_ok else 'see the ledger'}; {time.time() - t0:.0f} s")


if __name__ == "__main__":
    main()
