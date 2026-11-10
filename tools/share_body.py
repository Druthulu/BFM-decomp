#!/usr/bin/env python3
"""share_body.py — give a byte-identical function class ONE source (Phase 35 T5): the permanent successor of dedup_propagate +
dedup_extend for the include-at-site form.

    tools/share_body.py --plan                             # the buckets: extend (registered-incomplete) / new (unregistered same-vram)
    tools/share_body.py --apply --bucket extend            # bucket 0: the registered classes whose members are not all sharing
    tools/share_body.py --apply --bucket new --batch 120 --limit N   # the unregistered same-vram classes, largest reach first
    tools/share_body.py --apply ... --only <h_exact>       # one class (the R37 probe)
    tools/share_body.py --plan|--apply --bucket cross      # (3.42 T4) verdict-C classes at SEVERAL addresses: one cls_<h12>.h defining SHARED_FN,
                                                           # each site `#define SHARED_FN <own name>` / include / undef (the I0_clearTbl40 form);
                                                           # a red class is undone at every site, never ledgered; ledgers re-keyed to the header
                                                           # (T6) + verdict D (texts ranked by raw casts + !FAKE markers, lowest address; a
                                                           # reject retries the next text in the same run), verdict B (group headers' bodies
                                                           # are candidates too; their include sites take the param form; groups merge into
                                                           # one X_ group, old headers removed) and twin-covered classes
                                                       # (T6.c2) after the gate, type_census --check: a class whose text raises an
                                                       # unledgered lie or a dead type is rejected like a gate red (next text); a class
                                                       # whose every text leaves a type dead deletes that unreferenced type (rank 1)

WHAT ONE SHARE IS. A class = one h_exact (the raw instruction bytes) at one vram, with >=2 instances across the fleet, some of which
are still PRIVATE COPIES (a definition in that binary's own TU). Sharing it: the class's ONE body goes to (or already is) a plain-C
header under src/shared/<space>/ (macro_to_header's naming: func_<VRAM>[__h8].h, keyed by the class — R48), every private copy becomes
`#include "../shared/<space>/<header>"` at the SAME position (the copy's definition lines, nothing else — the TU keeps its own
declarations), and the registry gains the group (shorthand form, appended by text) or the members (add_members_surgical, inherited from the retired dedup_extend).

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

LEDGER = REPO / "config/dedup_exceptions.tsv"
RUN = REPO / ".run/P35/share"


# ----------------------------------------------------------------------------------------------------------------------------
# The library surface inherited from the retired propagate/extend tools in tools/sunset (Phase 35 T6; verbatim, so their importers
# change one line: `import share_body as dp`). load_sig/sig_path read the per-binary sig files; registered_addrs the registry.
def sig_path(ov):
    return REPO / f".run/sig.{ov}.jsonl"


def onboarded_overlays():
    """Overlay aliases + (S44) module aliases — every non-main/resident binary a shared body can
    propagate into. Modules carry engine functions too; excluding them re-creates the SC07
    invisible-work bug one class over."""
    out = []
    for f, var in (("config/overlays.mk", "OVERLAY_BINARIES"), ("config/modules.mk", "MODULE_BINARIES")):
        fp = REPO / f
        if fp.exists():
            m = re.search(rf"^{var}\s*:=\s*(.*)$", fp.read_text(), re.M)
            if m:
                out += m.group(1).split()
    return out
def load_sig(ov):
    """addr(int) -> {h_exact, h_norm, nins, ...}; {} if absent."""
    p = sig_path(ov)
    if not p.exists():
        return {}
    out = {}
    for ln in p.read_text().splitlines():
        ln = ln.strip()
        if ln:
            r = json.loads(ln)
            out[int(r["addr"], 16)] = r
    return out
def registered_addrs():
    """Vaddrs already in config/dedup.us.yaml (shared via ANY mechanism — engine_core, ov_setters,
    clearTbl40). --auto-from skips these so the bulk is purely additive and never collides with an
    existing share (e.g. a SETTER-matched function) — which would trip the structural check."""
    p = REPO / "config/dedup.us.yaml"
    if not p.exists():
        return set()
    try:
        import yaml
        sys.path.insert(0, str(REPO / "tools"))
        from dedup_integrate import group_members
        data = yaml.safe_load(p.read_text()) or {}
        return {v for g in (data.get("groups") or []) for (_b, v, _n) in group_members(g)}
    except Exception:
        return set()
def sym(addr):
    return f"func_{addr:08X}"  # splat convention: uppercase 8-hex


def add_members_surgical(additions):
    """Append binaries to each group's `binaries: [...]` list by TEXT EDIT, in place.

    NEVER `yaml.safe_dump` this file. The first cut of this tool round-tripped it through
    safe_dump and silently destroyed BOTH of the things a human needs from it (H5 — "never
    silently drop comments on a rewrite"):
      * all 47 comment lines — including the curated Phase-11 header explaining WHY the share is
        source-level (the linker cannot excise bytes interior to an object) — dumped to nothing;
      * every `vram: 0x80162FF4` re-serialized as `vram: 2148937716` (PyYAML parses YAML-1.1 hex
        to int, and dumps int as decimal), making 1,832 entries unreadable.
    It was invisible to every gate: dedup-check passed 1840/0 and check-all stayed 140/140,
    because `_addr()` accepts both forms — the data was fine and the DOCUMENT was ruined. A
    formatting-destructive write that all your oracles call green is exactly the class this
    project keeps re-learning: the gate measures bytes, not intent.

    `additions` = {group_id: [binary, ...]}. Idempotent: a binary already listed is skipped.
    """
    p = str(REPO / "config/dedup.us.yaml")
    lines = open(p).read().splitlines(keepends=True)
    cur, n = None, 0
    seen = set()
    for i, ln in enumerate(lines):
        m = re.match(r"^\s*-?\s*id:\s*(\S+)\s*$", ln)
        if m:
            cur = m.group(1)
            continue
        if cur and cur in additions and re.match(r"^\s*members:\s*$", ln):
            # a VERBOSE group has no `binaries:` line — silently skipping it left five 141-member groups listed at 16 (P35 S94/S96)
            raise SystemExit(f"add_members_surgical: {cur} is in the verbose `members:` form — convert it to shorthand first "
                             f"(share_body.py --repair-registry does), never skip it (R43)")
        if cur and cur in additions and re.match(r"^\s*binaries:\s*\[", ln):
            seen.add(cur)
            add = [b for b in additions[cur] if re.search(rf"\b{re.escape(b)}\b", ln) is None]
            if add:
                lines[i] = ln.rstrip("\n").rstrip()[:-1].rstrip() + ", " + ", ".join(add) + "]\n"
                n += len(add)
            cur = None
    open(p, "w").write("".join(lines))
    return n


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
                exceptions=exceptions, classes=classes, sigs=sigs)


def candidates(cen):
    """(extend, new): the classes this tool shares. Same-vram only; twin-covered and excepted classes are satisfied already."""
    extend, new = [], []
    for c in cen["classes"]:
        if c["verdict"] == "A" or "E" in c["flags"] or "F" in c["flags"] or "TWIN-COVERED" in c["flags"] or (c["excepted"] and not RETRY_EXCEPTED):
            continue                         # `--retry-excepted` (P37 T4): a ledgered class re-enters the plan; this run's verdict replaces its row
        priv = [i for i in c["insts"] if i["form"] == "def"]
        if c["verdict"] == "B":
            extend.append(c)
        elif priv:
            new.append(c)
    new.sort(key=lambda c: (-c["instances"], -c["nins"], c["h"]))
    extend.sort(key=lambda c: (-c["instances"], -c["nins"], c["h"]))
    return extend, new


def text_candidates(cen):
    """Phase 35 T5b: the TEXT-tier classes as census-shaped class dicts (verdict 'T'): one normalized text at one address in >=2
    distinct TUs, outside the deferred/ledgered sets; every site a private `def`. The bytes differ per binary, so the group is
    registered in the verbose form with each member's own h_exact (dedup_integrate checks C1 per member)."""
    hx = {(a, addr): h for a, rows in cen["sigs"].items() for addr, _n, h, _name in rows}
    out = []
    for tc in sc.text_classes(cen["forms"], cen["classes"], cen["exceptions"]):
        insts = [dict(alias=a, addr=tc["addr"], nins=tc["nins"], name=f"func_{tc['addr']:08X}", form="def", tu=tu,
                      text_hash=rec.get("text_hash"), pins=rec.get("pins", False), typedef=rec.get("typedef", False),
                      alias_form=rec.get("alias", False), line=rec.get("line"), end=rec.get("end"), nlines=rec.get("nlines", 0),
                      h_exact=hx.get((a, tc["addr"])))
                 for a, tu, rec in tc["sites"]]
        out.append(dict(h=tc["text_hash"], tier="h_text", verdict="T", flags=[], nins=tc["nins"], instances=len(insts), copies=len({i["tu"] for i in insts}),
                        aliases=sorted({i["alias"] for i in insts}), addrs=[f"0x{tc['addr']:08X}"], insts=insts, groups=[], excepted=None))
    return out


_C_TOKENS = re.compile(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|/\*.*?\*/|//[^\n]*', re.S)


def own_name(inst, text):
    """The name the private copy's definition is written under: the sig name, or its asm-label alias aF<ADDR> (§37/§73)."""
    m = re.search(rf"\b{re.escape(inst['name'])}\b", text, re.I)    # sig names are lower-hex (func_8017d290), the source upper
    if m:
        return m.group(0)
    m = re.search(rf"\baF{inst['addr']:08X}\b", text, re.I)
    return m.group(0) if m else inst["name"]


def def_head_name(inst, text):
    """T6 (3.42): the name a copy's definition head is written under — the identifier before the head's first `(`. An alias-form copy can
    carry ANOTHER address's alias (ov_SC03_001 defines `aF801848DC`, bound by asm label to func_8018739C), which own_name misses (it
    looks for the copy's own name and own aF<ADDR>, then falls back to a name not in the text: nothing masked). Else own_name."""
    m = re.match(r"\s*[^(;{]*?\b([A-Za-z_]\w*)\s*\(", text)
    if m and (m.group(1).lower() == inst["name"].lower() or re.fullmatch(r"aF[0-9A-Fa-f]{8}", m.group(1))):
        return m.group(1)
    # T6.c3: any head name its TU binds by asm label to the copy's own symbol (`func_8017D698_x(...) __asm__("func_8017F01C")`, cross23:
    # the name was not masked, the header defined it verbatim, the census left the 3 sites UNACCOUNTED)
    if m and inst.get("tu") and tu_binds(inst["tu"]).get(m.group(1)) == inst["name"].lower():
        return m.group(1)
    return own_name(inst, text)


_TU_BINDS = {}


def tu_binds(tu):  # T6.c3: a TU's asm-label bindings {ident: func_<addr> lower} (share_census.ALIAS_DECL), read once per run (pre-edit text)
    if tu not in _TU_BINDS:
        p = REPO / tu
        _TU_BINDS[tu] = {a: s.lower() for a, s in sc.ALIAS_DECL.findall(p.read_text(errors="surrogateescape"))} if p.exists() else {}
    return _TU_BINDS[tu]


def cross_norm(text, name):
    """T4 (3.42): the cross-address equality key — comments stripped, the copy's OWN name -> SHARED_FN, whitespace collapsed."""
    t = _C_TOKENS.sub(lambda m: m.group(0) if m.group(0)[0] in "\"'" else " ", text)
    t = re.sub(rf"\b{re.escape(name)}\b", "SHARED_FN", t)
    return re.sub(r"\s+", " ", t).strip()


def cross_candidates(cen):
    """(pool, differs): the cross-address classes (flag E with or without F, not excepted; twin-covered included since T6). Verdict C:
    every private copy's text under cross_norm must be equal — a class whose copies differ is reported (TEXT-DIFFERS), never ledgered.
    T6 (3.42): verdict D (the copies' texts differ: ranked by cross_texts, retried text by text) and verdict B (registered at one or more
    addresses, private copies elsewhere: the group headers' bodies join the candidate texts, the groups merge into one X_ group)."""
    pool, differs = [], []
    for c in cen["classes"]:
        if c["excepted"] and not RETRY_EXCEPTED:
            continue
        if c["verdict"] in ("B", "D") and ("E" in c["flags"] or "F" in c["flags"]):
            pool.append(dict(c, cross=True))
            continue
        if c["verdict"] != "C" or "E" not in c["flags"]:
            continue
        priv = [i for i in c["insts"] if i["form"] == "def"]
        keys = set()
        for i in priv:
            t = def_text(dict(i, cross=True))
            keys.add(cross_norm(t, own_name(i, t)))
        (pool if len(keys) == 1 else differs).append(dict(c, cross=True))
    pool.sort(key=lambda c: (-c["instances"], -c["nins"], c["h"]))
    return pool, differs


def cross_settled():  # T6.c3 (3.42): the classes a T6 cross batch already settled red — `rejected` (every ranked text failed) or `refused` in
    """batch_t6probe*.json and batch_cross<k>.json with k >= 19 (the T6 sweep; cross1..18 are T4/T5's). The sweep skips them, so its empty
    test (`done — 0 of 0 classes`) fires when only these remain; the remainder is bucketed from the same files."""
    out = set()
    for p in sorted(RUN.glob("batch_*.json")):
        m = re.fullmatch(r"batch_(t6probe\w*|cross(\d+))\.json", p.name)
        if not m or (m.group(2) and int(m.group(2)) < 19):
            continue
        bj = json.loads(p.read_text())
        out |= set(bj.get("rejected") or []) | {r[0] for r in bj.get("refused") or []}
    return out


_RAW_FORMS = []


def rank_counts(text):
    """(raw casts, `// !FAKE:` markers) of a candidate text — the D exemplar rule's key (T6): raw casts = the project's raw pointer-cast
    dereferences, type_census's four forms P `*(T *)(`, I `*(T *)ident`, X `((T *)e)[`, M `M2C_FIELD(` on the masked text. A typed
    cast-member `((T *)e)->f` is no raw cast (t6probe1: a cast regex that counted it ranked the cast-form text over the struct-typed
    copies of 6fc432ca3671 / 962117a4d87d and left Unkstruct_8017ED3C, _80181D08, _8018337C with no user: type_census dead=3)."""
    if not _RAW_FORMS:
        import type_census as tc                     # heavy: only the D/B ranking needs it
        _RAW_FORMS.extend((tc.FORM_P, tc.FORM_I, tc.FORM_X, tc.FORM_M))
    code = sc.mask_text(text)
    return sum(len(rx.findall(code)) for rx in _RAW_FORMS), text.count("!FAKE:")


_TYPE_NAMES, _TYPE_FILES = set(), []


def lost_types(cands, copies_text):
    """T6 (t6probe1): per candidate, the first typedef name (from the type headers include/*.h, src/shared/*.h) that the other texts use,
    this one does not, and nothing in src/ outside the class's copies and the type headers uses — sharing that text would leave the type
    with no user (type_census --check dead; t6probe1b: Loc_80180E10, defined in src/shared/engine_types.h). Sets x["dead"] = name or
    None. Conservative: uses inside the type headers are not counted."""
    if not _TYPE_NAMES:
        files = sorted(REPO.glob("include/*.h")) + sorted(REPO.glob("src/shared/*.h"))
        _TYPE_FILES.extend(str(f.relative_to(REPO)) for f in files if f.parts[-2] == "shared")
        for f in files:
            st = f.read_text(errors="surrogateescape")
            _TYPE_NAMES.update(re.findall(r"^\}\s*([A-Za-z_]\w*)\s*;", st, re.M) + re.findall(r"^typedef\s+[^;{]*?\b([A-Za-z_]\w*)\s*;", st, re.M))
    used = [set(re.findall(r"\b[A-Za-z_]\w*\b", sc.mask_text(x["body"]))) & _TYPE_NAMES for x in cands]
    union = set().union(*used)
    outside = {}
    for n in sorted(union - set.intersection(*used)):
        r = subprocess.run(["git", "grep", "-w", "-o", "-F", n, "--", "src", *[f":(exclude){f}" for f in _TYPE_FILES]], cwd=REPO,
                           capture_output=True, text=True)
        outside[n] = len(r.stdout.splitlines()) - len(re.findall(rf"\b{re.escape(n)}\b", copies_text))
    for x, u in zip(cands, used):
        x["dead_all"] = [n for n in sorted(union - u) if outside.get(n, 1) <= 0]     # T6.c2: every type the text leaves dead
        x["dead"] = x["dead_all"][0] if x["dead_all"] else None


def type_def_span(name):
    """T6.c2: (file, first line, last line) of the one definition of type `name` in the type headers (include/*.h, src/shared/*.h):
    a `typedef ... name;` line, or the brace block ending `} name;` back to its `typedef` line. None when absent, ambiguous or not
    a whole-line definition."""
    hits = []
    for f in sorted(REPO.glob("include/*.h")) + sorted(REPO.glob("src/shared/*.h")):
        lines = f.read_text(errors="surrogateescape").split("\n")
        for j, ln in enumerate(lines):
            if re.match(rf"\s*typedef\b[^;]*\b{re.escape(name)}\s*;", ln) and ln.count("{") == ln.count("}"):
                hits.append((str(f.relative_to(REPO)), j + 1, j + 1))
            elif re.match(rf"\}}\s*{re.escape(name)}\s*;", ln):
                depth, k = 0, j
                while k >= 0:
                    depth += lines[k].count("}") - lines[k].count("{")
                    if depth <= 0:
                        break
                    k -= 1
                if k >= 0 and depth == 0 and re.match(r"\s*typedef\b", lines[k]):
                    hits.append((str(f.relative_to(REPO)), k + 1, j + 1))
    return hits[0] if len(hits) == 1 else None


def drop_type_plan(names, copies_text):
    """T6.c2: the dead-type rule. A class whose every text leaves a type with no user may delete that type's definition in the same
    batch, only when nothing else references it: src/ and include/ (outside its definition and the class's copies), docs/struct-twins.md
    and tools/type_census.py (the controls). Returns ([(name, file, first, last, block text)], None) or (None, reason)."""
    out = []
    for n in names:
        span = type_def_span(n)
        if not span:
            return None, f"{n}: no single whole-line definition in the type headers"
        f, a, z = span
        block = "\n".join((REPO / f).read_text(errors="surrogateescape").split("\n")[a - 1:z])
        r = subprocess.run(["git", "grep", "-w", "-o", "-F", n, "--", "src", "include", "docs/struct-twins.md", "tools/type_census.py"],
                           cwd=REPO, capture_output=True, text=True)
        refs = len(r.stdout.splitlines()) - len(re.findall(rf"\b{re.escape(n)}\b", copies_text)) - len(re.findall(rf"\b{re.escape(n)}\b", block))
        if refs > 0:
            where = sorted({x.split(":", 1)[0] for x in r.stdout.splitlines()})
            return None, f"{n}: {refs} other reference(s) ({', '.join(where[:4])})"
        out.append((n, f, a, z, block))
    return out, None


def type_check():
    """T6.c2: `type_census --check` on the batch's tree (out-dir RUN/type_census, its walk cache kept warm). Returns (rc, the verdict
    line, unledgered lying rows [{callee, defined_in, kind}], dead type names). The census re-renders docs/struct-map.md: its text is
    put back (a tools-health product, never this tool's)."""
    keep = {p: p.read_bytes() for p in [REPO / "docs/struct-map.md"] if p.exists()}
    out = RUN / "type_census"
    r = subprocess.run([sys.executable, str(REPO / "tools/type_census.py"), "--check", "--quiet", "--out-dir", str(out.relative_to(REPO))],
                       cwd=REPO, capture_output=True, text=True)
    for p, data in keep.items():
        p.write_bytes(data)
    j = json.loads((out / "type_census.json").read_text())
    import type_census as tc
    exc = tc.lying_exceptions()
    unl = [x for x in j["summary"]["decls"]["lying_rows"] if (x["callee"], x.get("defined_in"), x["kind"]) not in exc]
    line = next((ln for ln in r.stdout.splitlines() if ln.startswith("type_census --check")), r.stdout.strip()[-200:])
    return r.returncode, line, unl, list(j.get("structs_dead") or [])


def next_text(cands, k):
    """The index of the next candidate after k that leaves no type dead (len(cands) when none)."""
    k += 1
    while k < len(cands) and cands[k].get("dead"):
        k += 1
    return k


def strip_banner(text):
    """A same-vram header's text without its leading banner comment (the body a header candidate contributes)."""
    t = text.lstrip()
    if t.startswith("/*") and "*/" in t:
        t = t[t.index("*/") + 2:].lstrip("\n")
    return t


def cross_texts(c, old):
    """T6 (3.42): the D/B exemplar candidates — the distinct cross_norm texts of the private copies (and, for a B class, of its group
    headers `old` = [(group, own name, header text)]), ranked by (raw casts + !FAKE markers, lowest address); each text represented by its
    lowest-address copy. Returns [dict(src, addr, body (own name -> SHARED_FN), casts, fakes)]."""
    cands = {}
    priv = sorted((i for i in c["insts"] if i["form"] == "def"), key=lambda i: (i["addr"], i["alias"], i["tu"], i["line"]))
    items = [(i["addr"], f"{i['tu']}:{i['line']}", def_text(dict(i, cross=True)), None, i) for i in priv]
    # T6.c3: a verbose-member group (h_text/cross form) has no top-level `vram`: its lowest member address stands in (cross19 KeyError)
    items += [(dedup_addr(g["vram"]) if "vram" in g else min(dedup_addr(a) for _bn, a, *_ in m2h.sc_group_members(g)),
               g["source"], strip_banner(t), own, None) for g, own, t in old]
    for addr, src, t, own, i in sorted(items, key=lambda x: (x[0], x[1])):
        own = own or def_head_name(i, t)
        key = cross_norm(t, own)
        if key in cands:
            continue
        casts, fakes = rank_counts(t)
        cands[key] = dict(src=src, addr=addr, body=re.sub(rf"\b{re.escape(own)}\b", "SHARED_FN", t), casts=casts, fakes=fakes)
    return sorted(cands.values(), key=lambda x: (x["casts"] + x["fakes"], x["addr"], x["src"]))


def dedup_addr(v):
    return int(v, 16) if isinstance(v, str) else int(v)


def choose_exemplar(priv):
    by_text = collections.Counter(i["text_hash"] for i in priv)
    best = max(by_text.values())
    pool = [i for i in priv if by_text[i["text_hash"]] == best]
    pool.sort(key=lambda i: (i.get("pins", False), i.get("nlines", 0), i["alias"], i["tu"]))
    reason = "majority text" if best > 1 or len(priv) == 1 else "tie → pin-free, shortest"
    return pool[0], reason, dict(by_text)


_TU_LINES = {}


def def_text(inst):
    """The definition's lines [line..end] of a private copy, from its TU."""
    tu = REPO / inst["tu"]
    if inst.get("cross"):                                # the cross bucket reads every copy of thousands of classes: cache the TU
        lines = _TU_LINES.setdefault(inst["tu"], tu.read_text(errors="surrogateescape").split("\n"))
    else:
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
        self.register_text = []                          # (id, text_hash, source, func, [(binary, vram, name, h_exact)])
        self.extend = collections.defaultdict(list)      # group id -> [binaries]
        self.register_cross = []                         # (id, h, source, [(binary, vram, name)]) — the cross bucket (T4, 3.42)
        self.moves = []                                  # (h, tu, own name, header, def line): each cross site's body moved to the header
        self.touched = set()                             # binaries
        self.members = collections.defaultdict(list)     # h -> [(alias, tu)]
        self.exemplar_note = {}
        self.cross = {}                                  # T6: h -> dict(hdr, gid, fn, cands, k, rejects, old_groups, old_headers) — D/B classes

    def add_class(self, c):
        h = c["h"]
        vram = int(c["addrs"][0], 16)
        priv = [i for i in c["insts"] if i["form"] == "def"]
        base = self.orc.bases[priv[0]["alias"]] if priv else self.orc.bases[c["insts"][0]["alias"]]
        fn = f"func_{vram:08X}"
        if c.get("cross") and c["verdict"] in ("B", "D"):
            return self.add_cross_ranked(c, priv, base, fn)
        if c.get("cross"):
            # T4 (3.42): ONE body at several addresses — the name-parameterized include form (I0_clearTbl40): the header defines
            # SHARED_FN, each site defines SHARED_FN to its own name around the include; members verbose {binary, vram, name}
            ex, reason, texts = choose_exemplar(priv)
            multi = "F" in c["flags"]
            hdr = f"src/shared/{'multi' if multi else self.orc.space_dir(base)}/cls_{h[:12]}.h"
            if (REPO / hdr).exists():
                return f"refused: {hdr} exists already"
            body = def_text(ex)
            nm = own_name(ex, body)
            body = re.sub(rf"\b{re.escape(nm)}\b", "SHARED_FN", body)
            gid = f"X_{h[:12]}"
            text = f"/* class h_exact {h} · registry {gid} · generated by tools/share_body.py --bucket cross at {head_sha()} */\n" + body
            text, _ = m2h.bind_alias_header(text, fn)
            self.headers[hdr] = text
            owns = {(i["tu"], i["line"]): own_name(i, def_text(i)) for i in priv}    # members named as the source spells them
            self.register_cross.append((gid, h, hdr, sorted((i["alias"], i["addr"], owns.get((i["tu"], i["line"]), i["name"]))
                                                            for i in c["insts"])))
            self.exemplar_note[h] = f"cross exemplar {ex['tu']}:{ex['line']} ({reason}; texts {len(texts)}), {len(priv)} private sites → param-include"
            seen_sites = set()
            for i in priv:
                if (i["tu"], i["line"]) in seen_sites:   # the twin rule (below)
                    continue
                seen_sites.add((i["tu"], i["line"]))
                own = own_name(i, def_text(i))
                inc = f"#define SHARED_FN {own}\n{m2h.include_line(i['tu'], hdr)}\n#undef SHARED_FN"
                self.edits[i["tu"]].append((i["line"], i["end"], inc, h))
                self.moves.append((h, i["tu"], own, hdr, i["line"]))
            for i in priv:
                self.members[h].append((i["alias"], i["tu"]))
            for i in c["insts"]:
                self.touched.add(i["alias"])
            return None
        if c.get("tier") == "h_text":
            # T5b: the header is named by the TEXT hash (a byte-class header at the same vram must never collide); the body is any
            # site's text (identical by construction); every member is registered with its own h_exact
            ex = priv[0]
            hdr = f"src/shared/{self.orc.space_dir(base)}/func_{vram:08X}__t{h[:8]}.h"
            if (REPO / hdr).exists():
                return f"refused: {hdr} exists already (a text-tier header for this text/address)"
            space_name = "overlay slot" if base == m2h.OV_BASE else self.orc.space_dir(base)
            text = m2h.banner(fn, base, h, space_name).replace("h_exact", "h_text") + def_text(ex)
            text, _ = m2h.bind_alias_header(text, fn)
            self.headers[hdr] = text
            self.register_text.append((f"T_{fn}", h, hdr, fn, sorted((i["alias"], i["addr"], i["name"], i["h_exact"]) for i in c["insts"])))
            self.exemplar_note[h] = f"text tier {ex['tu']}:{ex['line']} — {len(priv)} private sites → include ({len({i['h_exact'] for i in c['insts']})} byte patterns)"
        elif c["verdict"] == "B":
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

    def add_cross_ranked(self, c, priv, base, fn):
        """T6 (3.42): a D or B cross class. Candidates ranked by cross_texts; the header carries text k (0 first; run_batch retries the
        next on a gate reject). B: every include site of a group header becomes the param-include form as well; the groups are dropped and
        their headers removed only once the class is green (run_batch), so an undo leaves them untouched."""
        h = c["h"]
        hdr = f"src/shared/{'multi' if 'F' in c['flags'] else self.orc.space_dir(base)}/cls_{h[:12]}.h"
        if (REPO / hdr).exists():
            return f"refused: {hdr} exists already"
        # T6.c2: the alias-form refusal (t6probe1: share_census recorded `#define SHARED_FN aF<ADDR>` verbatim) is lifted — the census
        # maps the site through the TU's ALIAS_DECL table now (scan_text); the own name comes from the def head (def_head_name, C0558)
        old, own_of_hdr, site_own, hdr_moves = [], {}, {}, []
        incl = [i for i in c["insts"] if i["form"] == "include"]
        inst_keys = {(i["alias"], i["addr"]) for i in c["insts"]}
        inc_sites = {(i["tu"], i["line"]) for i in incl}
        for g in c.get("groups") or []:
            src, gf = g["source"], g.get("func")
            p = REPO / src
            if not gf or gf == "SHARED_FN" or not p.exists():
                return f"refused: group {g['id']} (func {gf}, source {src}) is not a same-vram header group"
            t = p.read_text(errors="surrogateescape")
            if "__asm__" in t:
                return f"refused: {src} carries an asm-label binding"
            defs = [x for x in sc.scan_text(t, src, shared_defs=None) if x["form"] == "def"]
            if len(defs) != 1 or defs[0]["name"].lower() != gf.lower():
                return f"refused: {src} defines {[x['name'] for x in defs][:3]}, not exactly {gf}"
            missing = [(bn, a) for bn, a, _ in m2h.sc_group_members(g) if (bn, a) not in inst_keys]
            if missing:
                return f"refused: {g['id']} lists members outside the class {missing[:3]}"
            base_nm = os.path.basename(src)
            r = subprocess.run(["git", "grep", "-n", "-F", f"/{base_nm}\"", "--", "src"], cwd=REPO, capture_output=True, text=True)
            users = {(x.split(":", 2)[0], int(x.split(":", 2)[1])) for x in r.stdout.splitlines() if x.split(":", 1)[0] != src}
            if users - inc_sites:
                return f"refused: {src} has includers outside the class {sorted(users - inc_sites)[:3]}"
            own = re.search(rf"\b{re.escape(gf)}\b", t, re.I).group(0)
            old.append((g, own, t))
            own_of_hdr[base_nm] = own
            hdr_moves.append((h, src, own, hdr, defs[0]["line"]))        # header-to-header: (old header, func_<VRAM>) -> (hdr, SHARED_FN)
        for i in incl:
            ln = (REPO / i["tu"]).read_text(errors="surrogateescape").split("\n")[i["line"] - 1]
            hit = [b for b in own_of_hdr if re.match(rf'\s*#include\s+"[^"]*/{re.escape(b)}"', ln)]
            if len(hit) != 1:
                return f"refused: include site {i['tu']}:{i['line']} is not an include of one group header ({ln.strip()[:60]})"
            site_own[(i["tu"], i["line"])] = own_of_hdr[hit[0]]
        for i in priv:
            site_own[(i["tu"], i["line"])] = def_head_name(i, def_text(i))
        cands = cross_texts(c, old)
        if not cands:
            return "refused: no candidate text"
        copies = "\n".join([def_text(i) for i in {(i["tu"], i["line"]): i for i in priv}.values()] + [t for _g, _o, t in old])
        lost_types(cands, copies)
        pre = [dict(rank=k + 1, src=x["src"], binary="type_census --check", cause=f"dead type {x['dead']}: no user outside the class's copies")
               for k, x in enumerate(cands) if x["dead"]]
        k0, drops = next_text(cands, -1), []
        if len(pre) == len(cands):
            # T6.c2: every text leaves a type dead -> rank 1 with its dead types' definitions deleted in the same batch (nothing else
            # may reference them); otherwise refused, one reason per text
            drops, why = drop_type_plan(cands[0]["dead_all"], copies)
            if why:
                return f"refused: every text leaves a type with no user — {[(r['rank'], r['cause']) for r in pre]}; rank 1's not deletable: {why}"
            k0, pre = 0, pre[1:]
        gid = f"X_{h[:12]}"
        self.moves.extend(hdr_moves)
        self.cross[h] = dict(hdr=hdr, gid=gid, fn=fn, cands=cands, k=k0, rejects=pre, old_groups=[g["id"] for g, _o, _t in old],
                             old_headers=[g["source"] for g, _o, _t in old], dropped=[d[0] for d in drops])
        for _n, f, a, z, _blk in drops:
            self.edits[f].append((a, z, None, h))       # None = delete the lines (the dead type's definition)
        self.headers[hdr] = self.cross_header(h)
        self.register_cross.append((gid, h, hdr, sorted((i["alias"], i["addr"], site_own[(i["tu"], i["line"])]) for i in c["insts"])))
        seen_sites = set()
        for i in priv + incl:
            if (i["tu"], i["line"]) in seen_sites:       # the twin rule (add_class)
                continue
            seen_sites.add((i["tu"], i["line"]))
            own = site_own[(i["tu"], i["line"])]
            inc = f"#define SHARED_FN {own}\n{m2h.include_line(i['tu'], hdr)}\n#undef SHARED_FN"
            end = i["end"] if i["form"] == "def" else i["line"]
            self.edits[i["tu"]].append((i["line"], end, inc, h))
            if i["form"] == "def":
                self.moves.append((h, i["tu"], own, hdr, i["line"]))
        for i in c["insts"]:
            self.members[h].append((i["alias"], i["tu"]))
            self.touched.add(i["alias"])
        self.note_cross(h)
        return None

    def cross_header(self, h):
        """The D/B header text for the class's current candidate k; the provenance comment carries the rule: the chosen text, its rank,
        cast and marker counts, and the binary that rejected each earlier text."""
        x = self.cross[h]
        cd = x["cands"][x["k"]]
        lines = [f"/* class h_exact {h} · registry {x['gid']} · generated by tools/share_body.py --bucket cross at {head_sha()}",
                 f" * exemplar {cd['src']} · rank {x['k'] + 1}/{len(x['cands'])} by (raw casts + !FAKE markers, lowest address): "
                 f"casts {cd['casts']}, markers {cd['fakes']}"]
        lines += [f" * rank {r['rank']} {r['src']} rejected by {r['binary']}" for r in sorted(x["rejects"], key=lambda r: r["rank"])]
        text = "\n".join(lines) + " */\n" + cd["body"]
        return m2h.bind_alias_header(text, x["fn"])[0]

    def note_cross(self, h):
        x = self.cross[h]
        cd = x["cands"][x["k"]]
        self.exemplar_note[h] = (f"cross rank {x['k'] + 1}/{len(x['cands'])} {cd['src']} (casts {cd['casts']}, markers {cd['fakes']}; "
                                 f"rejected {[(r['rank'], r['binary']) for r in x['rejects']]}), {sum(1 for e in self.edits_of(h) if e[2] is not None)} sites → param-include"
                                 + (f"; merges {x['old_groups']}" if x["old_groups"] else "")
                                 + (f"; deletes dead types {x['dropped']}" if x.get("dropped") else ""))

    def edits_of(self, h):
        return [e for eds in self.edits.values() for e in eds if e[3] == h]

    def apply_edits(self, only_tus=None):
        n = 0
        for tu, eds in self.edits.items():
            if only_tus is not None and tu not in only_tus:
                continue
            p = REPO / tu
            lines = p.read_text(errors="surrogateescape").split("\n")
            for line, end, new, _ in sorted(eds, key=lambda e: -e[0]):
                lines[line - 1:end] = [] if new is None else [new]
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


RETRY_EXCEPTED = False


def ledger_drop(h):
    """Drop every ledger row of class `h` (a retried exception: the row this run writes — or does not — is the verdict now)."""
    lines = LEDGER.read_text().split("\n")
    kept = [ln for ln in lines if not ln.startswith(h)]
    if len(kept) != len(lines):
        LEDGER.write_text("\n".join(kept))
    return len(lines) - len(kept)


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


def registry_append_text(entries):
    """Append h_text groups by text (H5): verbose members, each with its own h_exact."""
    p = REPO / "config/dedup.us.yaml"
    t = p.read_text()
    if not t.endswith("\n"):
        t += "\n"
    out = []
    for gid, th, src, fn, members in entries:
        out.append(f"  - id: {gid}\n    tier: h_text\n    hash: {th}\n    source: {src}\n    func: {fn}\n    members:\n")
        for b, vram, name, hx in members:
            out.append(f"      - {{ binary: {b}, vram: 0x{vram:08X}, name: {name}, h_exact: {hx} }}\n")
    p.write_text(t + "".join(out))


def registry_append_cross(entries):
    """Append the cross-address groups by text (H5): the I0_clearTbl40 form — func SHARED_FN, verbose members {binary, vram, name}."""
    p = REPO / "config/dedup.us.yaml"
    t = p.read_text()
    if not t.endswith("\n"):
        t += "\n"
    out = []
    for gid, h, src, members in entries:
        out.append(f"  - id: {gid}\n    tier: h_exact\n    hash: {h}\n    source: {src}\n    func: SHARED_FN\n    members:\n")
        for bn, vram, name in members:
            out.append(f"      - {{ binary: {bn}, vram: 0x{vram:08X}, name: {name} }}\n")
    p.write_text(t + "".join(out))


def registry_merge(b, green, label):
    """T6 (3.42): for each green B cross class, drop its old groups from config/dedup.us.yaml (by text: the `  - id:` block) and remove
    every old header no file includes any more (a deletion the commit stages); its one X_ group is appended by registry_append_cross.
    A header still included is kept and reported (add_cross_ranked refused classes whose headers had includers outside them)."""
    out = {}
    drop = {g: h for h in green for g in b.cross[h]["old_groups"]}
    if not drop:
        return out
    p = REPO / "config/dedup.us.yaml"
    lines, kept, skip, found = p.read_text().splitlines(keepends=True), [], False, set()
    for ln in lines:
        m = re.match(r"^  - id:\s*(\S+)\s*$", ln)
        if m:
            skip = m.group(1) in drop
            if skip:
                found.add(m.group(1))
        elif skip and not ln.startswith("    "):
            skip = False
        if not skip:
            kept.append(ln)
    if found != set(drop):
        sys.exit(f"share_body: registry_merge: groups not found in config/dedup.us.yaml: {sorted(set(drop) - found)[:5]} (R43)")
    p.write_text("".join(kept))
    for h in sorted(g for g in green if b.cross[g]["old_groups"]):
        gone, left = [], []
        for hdr in b.cross[h]["old_headers"]:
            r = subprocess.run(["git", "grep", "-l", "-F", f"/{os.path.basename(hdr)}\"", "--", "src"], cwd=REPO, capture_output=True, text=True)
            users = [u for u in r.stdout.split() if u != hdr]
            if users:
                left.append((hdr, users[:3]))
                continue
            (REPO / hdr).unlink()
            gone.append(hdr)
        out[h] = dict(groups_dropped=b.cross[h]["old_groups"], headers_removed=gone, headers_kept=left)
        log(f"  [{label}] {h[:10]}: merged {len(b.cross[h]['old_groups'])} groups into {b.cross[h]['gid']} · {len(gone)} old headers removed"
                + (f" · KEPT (still included) {left}" if left else ""))
    return out


_HEAD = []


def head_sha():
    if not _HEAD:
        _HEAD.append(subprocess.run(["git", "rev-parse", "--short", "HEAD"], cwd=REPO, capture_output=True, text=True).stdout.strip())
    return _HEAD[0]


def rekey_ledgers(moves):
    """T4 (3.42): re-key every ledger row of a body moved into a cross header to the header — as each census emits a header def:
    lever_census (file, func) = (header, SHARED_FN), the def name written in it; verbatim_check (binary, fn, path) = ('shared',
    SHARED_FN, header); type_census's lying key (callee, def_file): NOT re-keyed (T6.c3: type_census keeps the site's TU as def_file).
    Rows that collapse onto one key are deduped (first kept). Returns {ledger: rows re-keyed}. Text edits; a file is written only on change."""
    out = {}
    site = {(tu, own.lower()): hdr for _h, tu, own, hdr, _l in moves}
    # config/lever_residue.tsv — file func kind pass instrument cause; key (file, func, kind)
    p = REPO / "config/lever_residue.tsv"
    lines, seen, n, kept = p.read_text().split("\n"), set(), 0, []
    for ln in lines:
        f = ln.split("\t")
        if not ln.startswith("#") and len(f) >= 3 and f[0] != "file":
            hdr = site.get((f[0], f[1].lower()))
            if hdr:
                f[0], f[1] = hdr, "SHARED_FN"; ln = "\t".join(f); n += 1
            if (f[0], f[1], f[2]) in seen:
                continue
            seen.add((f[0], f[1], f[2]))
        kept.append(ln)
    if n:
        p.write_text("\n".join(kept))
    out["lever_residue.tsv"] = n
    # config/lying_exceptions.tsv — callee def_file kind cause task; key (callee, def_file, kind)
    p = REPO / "config/lying_exceptions.tsv"
    lines, seen, n, kept = p.read_text().split("\n"), set(), 0, []
    for ln in lines:
        f = ln.split("\t")
        if not ln.startswith("#") and len(f) >= 3 and f[0] != "callee":
            # DISABLED: lying-ledger re-key — 3.42 T6.c3 / Original intent: def_file follows the body into the cross header /
            # Why disabled: type_census keys a `#define SHARED_FN` + include def by the SITE's TU (cross35 re-keyed func_80014CF8
            # src/800.c -> cls_dafdc8bf94f5.h: tools-health `unledgered lying=1`) / Re-enable if type_census reports the header as def_file
            hdr = None
            if hdr:
                f[1] = hdr; ln = "\t".join(f); n += 1
            if (f[0], f[1], f[2]) in seen:
                continue
            seen.add((f[0], f[1], f[2]))
        kept.append(ln)
    if n:
        p.write_text("\n".join(kept))
    out["lying_exceptions.tsv"] = n
    # config/verbatim_manifest.json — rows {binary, fn, path, ...}; key (binary, fn)
    p = REPO / "config/verbatim_manifest.json"
    man = json.loads(p.read_text())
    seen, n, rows = set(), 0, []
    for r in man["rows"]:
        hdr = site.get((r.get("path"), r["fn"].lower()))
        if hdr:
            r = dict(r, binary="shared", fn="SHARED_FN", path=hdr); n += 1
        if (r["binary"], r["fn"]) in seen:
            continue
        seen.add((r["binary"], r["fn"]))
        rows.append(r)
    if n:
        man["rows"] = rows
        p.write_text(json.dumps(man, indent=1, ensure_ascii=False) + "\n")
    out["verbatim_manifest.json"] = n
    return out


def rekey_restruct(moves, label):
    """T4.c3 (3.42): the restruct ledger (.run/P37/restruct/ledger.jsonl, key (rung, tu, unit)) re-keyed like rekey_ledgers: each header gets
    ONE appended rung-S row (tu=header, unit=fn=SHARED_FN) built from its private copies' latest rung-S rows, every entry (KEPT(<cls>)
    macro backing included) with its line shifted by (header def line - private def line). Copies of one class union as a multiset (per
    entry, the max count over copies: one RESIDUAL entry covers one site); a union that differs from any copy is logged. Row fields come
    from a copy whose verdict backs macros (type_census.BACKED_S_VERDICTS), else the first. Old rows are never rewritten. Idempotent: a
    header whose latest row carries `rekey_of` is skipped. Runs BEFORE the residue step (residue_rows merges onto this row).
    Returns {copied, unioned, skipped, no_row}."""
    import restruct as rs                            # heavy (type_census, delever): only the cross bucket needs it
    latest = rs.ledger_latest(rs.load_ledger())
    by_hdr = collections.defaultdict(list)
    for m in moves:
        by_hdr[m[3]].append(m)
    out, rows = collections.Counter(), []
    for hdr in sorted(by_hdr):
        text = (REPO / hdr).read_text(errors="surrogateescape")
        d = next((x for x in sc.scan_text(text, hdr, shared_defs=None) if x["form"] == "def" and x["name"] == "SHARED_FN"), None)
        if d is None:
            log(f"  [{label}] rekey_restruct: {hdr} has no SHARED_FN def — skipped")
            continue
        prev = latest.get(("S", hdr, "SHARED_FN")) or {}
        # idempotent per header TEXT (T6): a rerun after an undo may write the same header with another ranked text
        if prev.get("rekey_of") and prev.get("nhash_after") == rs.body_nhash(rs.dl.same_len_mask(text), d):
            out["skipped"] += 1
            continue
        copies, srcs = [], []
        for _h, tu, own, _hd, line in sorted(by_hdr[hdr], key=lambda m: (m[1], m[2])):
            r = next((latest[k] for k in (("S", tu, own), ("S", tu, own.lower())) if k in latest), None)
            if r is None:
                out["no_row"] += 1
                continue
            shift = d["line"] - line
            ents = collections.Counter()
            first = {}
            for e in r.get("sites") or []:
                e2 = dict(e, line=e["line"] + shift) if isinstance(e.get("line"), int) else dict(e)
                # union key: line only where the gate matches by line (KEPT(REINTERP)); old rows' lines drift per copy (rows written
                # against older text: copies' def-relative lines differ by up to ~80), which would multiply every entry in the union
                k = json.dumps({x: v for x, v in e2.items() if x != "macro_of" and (x != "line" or e2.get("verdict") == "KEPT(REINTERP)")},
                               sort_keys=True)
                ents[k] += 1
                first.setdefault(k, e2)
            copies.append((r, ents, first))
            srcs.append([tu, r["unit"]])
        if not copies:
            continue
        union, first = collections.Counter(), {}
        for _r, ents, f in copies:
            for k, n in ents.items():
                union[k] = max(union[k], n)
                first.setdefault(k, f[k])
        if any(ents != union for _r, ents, _f in copies):
            out["unioned"] += 1
            log(f"  [{label}] rekey_restruct: {hdr}: {len(copies)} copies' rows differ — union {sum(union.values())} entries "
                f"(copies {[sum(e.values()) for _r, e, _f in copies]}, verdicts {sorted({r['verdict'] for r, _e, _f in copies})})")
        base = next((r for r, _e, _f in copies if r.get("verdict") in rs.tc.BACKED_S_VERDICTS), copies[0][0])
        nh = rs.body_nhash(rs.dl.same_len_mask(text), d)
        row = json.loads(json.dumps(base))
        row.update(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=f"rekey_{label}", tu=hdr, unit="SHARED_FN", fn="SHARED_FN", addr=None,
                   header=True, nhash_before=nh, nhash_after=nh, rekey_of=srcs,
                   sites=[first[k] for k in sorted(union, key=lambda k: (first[k].get("line") or 0, k)) for _ in range(union[k])])
        rows.append(row)
        out["copied"] += 1
    if rows:
        rs.ledger_append(rows)
    log(f"  [{label}] restruct ledger re-keyed to the headers: {dict(out)}")
    return dict(out)


def rekey_batch(label):
    """--rekey-batch <label> (T4.c3): the full cross re-key (rekey_ledgers, rekey_restruct) + the residue steps for an already-committed
    batch, from batch_<label>.json and the source. Moves are rebuilt from each kept class's header and its `#define SHARED_FN <own>` /
    include sites; the private def line is <own>'s def in the pre-batch text (the header's provenance commit). Idempotent."""
    bj = json.loads((RUN / f"batch_{label}.json").read_text())
    rejected = set(bj.get("rejected") or [])
    moves = []
    for h in bj["classes"]:
        if h in rejected:
            continue
        hdrs = sorted((REPO / "src/shared").glob(f"*/cls_{h[:12]}.h"))
        if len(hdrs) != 1:
            sys.exit(f"share_body --rekey-batch: class {h[:12]}: headers {hdrs}")
        hdr = str(hdrs[0].relative_to(REPO))
        sha = re.search(r"--bucket cross at (\w+)", (REPO / hdr).read_text().split("\n", 1)[0]).group(1)
        r = subprocess.run(["git", "grep", "-l", "-F", f"/cls_{h[:12]}.h\"", "--", "src"], cwd=REPO, capture_output=True, text=True)
        for tu in r.stdout.split():
            if tu == hdr:
                continue
            owns = re.findall(rf"#define SHARED_FN (\w+)\n#include \"[^\"]*/cls_{h[:12]}\.h\"", (REPO / tu).read_text(errors="surrogateescape"))
            old = subprocess.run(["git", "show", f"{sha}:{tu}"], cwd=REPO, capture_output=True, text=True, errors="surrogateescape").stdout
            defs = {x["name"].lower(): x["line"] for x in sc.scan_text(old, tu, shared_defs=None) if x["form"] == "def"}
            for own in owns:
                if own.lower() not in defs:
                    sys.exit(f"share_body --rekey-batch: {tu}: no def of {own} at {sha}")
                moves.append((h, tu, own, hdr, defs[own.lower()]))
    log(f"share_body --rekey-batch {label}: {len(moves)} moves in {len({m[3] for m in moves})} headers")
    log(f"  [{label}] ledgers re-keyed to the headers: {rekey_ledgers(moves)}")
    rekey_restruct(moves, label)
    segs = sorted(set(bj.get("residue_segments") or [])) or sorted({m[3] for m in moves})
    return restamp_residue(segs, f"{label}_rekey")


def restamp_residue(segments, label):
    """Rule T2: the restruct residue re-stamped and checked on every touched segment (the aliases + the new headers — src/shared/ is
    outside restruct's default ov_* scope, so the headers are named in --only). type_census --sites first: restruct reads its sites."""
    py = sys.executable
    for name, cmd in (("type_census_sites", [py, "tools/type_census.py", "--sites", "-j", "16"]),
                      # T4.c2: a header body has no rung-S row of its own (its private copies' rows stay keyed to the old TUs): append one
                      ("residue", [py, "tools/restruct.py", "--rung", "S", "--residue", "--forms", "P,I,X,M", "--only", *segments]),
                      ("restamp", [py, "tools/restruct.py", "--rung", "S", "--residue", "--restamp", "--only", *segments]),
                      ("check_residue", [py, "tools/restruct.py", "--check-residue", "--forms", "P,I,X,M", "--only", *segments])):  # forms: the check-casts gate's four
        log_p = RUN / f"{name}_{label}.log"
        with open(log_p, "w") as f:
            r = subprocess.run(cmd, cwd=REPO, stdout=f, stderr=subprocess.STDOUT)
        tail = (log_p.read_text(errors="replace").strip().splitlines() or [""])[-1]
        log(f"  [{label}] {name}: exit {r.returncode} — {tail[:160]}")
        if r.returncode != 0:
            return False
    return True


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
    cross_hs = {c["h"] for c in classes if c.get("cross")}
    other_dirs = sorted({d + "/" for al, d in cen["dirs"].items() if al != "main"})
    owner = {tu: next((d for d in other_dirs if tu.startswith(d)), "") for tu in b.edits}
    # T6.c3: a type-header edit (drop_type_plan's deletion in include/*.h, src/shared/*.h) is compiled by EVERY binary: it belongs to each
    # binary's set, so a bisect restores and re-applies it with its class (cross20: it stayed main's, ov_SC02_027 stayed red — R43 stop)
    every = {tu for tu in b.edits if tu.startswith("include/") or (tu.startswith("src/shared/") and tu.endswith(".h"))}

    def tus_of(a):
        """The edited TUs a binary compiles: a twin builds its primary's; main the TUs under no other binary's directory (its dir is
        `src`, a prefix of every TU — the bisect used to restore and re-apply the whole batch for main); every binary the type headers."""
        a = cen["twin_of"].get(a) or a
        d = "" if a == "main" else cen["dirs"][a] + "/"
        return {tu for tu in b.edits if owner[tu] == d or tu in every}

    def cur_texts(a):
        return {tu: (REPO / tu).read_text(errors="surrogateescape") for tu in sorted(tus_of(a))}

    last_text = {}                                   # binary -> its TUs' text at its last green build (the pre-batch text until gated)

    def apply_classes(tus, excluded):
        """From the pre-batch text: every edit of the TUs whose class is not `excluded`, in ONE bottom-up pass."""
        for tu in tus:
            lines = tu_snap[tu].split("\n")
            for line, end, new, hh in sorted(b.edits[tu], key=lambda e: -e[0]):
                if hh not in excluded:
                    lines[line - 1:end] = [] if new is None else [new]
            (REPO / tu).write_text("\n".join(lines))

    def gate_round(binaries, cands, rc):
        """Gate `binaries`; a red one is bisected over the round's candidate classes `cands` (every other applied class stays applied).
        Returns the classes rejected; rc[h] = (binary, cause). T6: a binary whose candidate classes are all cross classes already
        rejected this round is not gated — they are undone everywhere next, and undo_and_regate rebuilds it if its text changed."""
        red = set()
        for a in binaries:
            my_tus = tus_of(a)
            here = {e[3] for tu in my_tus for e in b.edits[tu]}
            mine = here & cands
            if mine and mine <= red and mine <= cross_hs:
                continue
            ok, detail = gate(a, snap)
            results[a] = (ok, detail)
            if ok:
                last_text[a] = cur_texts(a)
                continue
            # BISECT this binary: restore its TUs, re-apply the round's classes one at a time
            fixed = here - cands - failed_classes
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
                        lines[line - 1:end] = [] if new is None else [new]
                    p.write_text("\n".join(lines))

            good = []
            for h in sorted(mine):
                apply_selected(sorted(fixed) + good + [h])
                ok2, det2 = gate(a, snap)
                if ok2:
                    good.append(h)
                else:
                    red.add(h)
                    rc.setdefault(h, (a, det2))
                    log(f"  [{label}] {a}: class {h[:10]} REJECTED — {det2}")
                    apply_selected(sorted(fixed) + good)   # leave the good ones applied
            ok3, det3 = gate(a, snap)
            results[a] = (ok3, det3 + f" (after bisect: {len(good)} classes kept, {len(mine) - len(good)} rejected)")
            if not ok3:
                sys.exit(f"share_body: {a} still red after the bisect ({det3}) — stopping (R43)")
            last_text[a] = cur_texts(a)
        return red

    def undo_and_regate(red, why):
        """A red CROSS class is all-or-nothing: every site restored (from the pre-batch text, the other classes' edits re-applied); every
        binary whose TUs changed back is gated again — unless its TUs are back at the text of its last green build (or, never built in
        this batch, at the pre-batch text: its objects are the snapshot's), which is recorded as such."""
        redo = {tu for tu, eds in b.edits.items() if any(e[3] in red for e in eds)}
        apply_classes(redo, failed_classes)
        for a in sorted(x for x in gated if tus_of(x) & redo):
            now = cur_texts(a)
            if now == last_text.get(a, {tu: tu_snap[tu] for tu in now}):
                if a not in results:
                    results[a] = (True, "unchanged: TUs at the pre-batch text, objects = the snapshot (not rebuilt)")
                continue
            ok4, det4 = gate(a, snap)
            results[a] = (ok4, det4 + f" ({why})")
            if not ok4:
                sys.exit(f"share_body: {a} red after the cross undo ({det4}) — stopping (R43)")
            last_text[a] = now

    rc = {}
    red = gate_round(gated, {c["h"] for c in classes}, rc)
    failed_classes |= red
    causes.update(rc)
    cross_red = red & cross_hs
    if cross_red:
        undo_and_regate(cross_red, f"after the cross undo of {len(cross_red)} classes")
    # T6: a red D/B class retries its NEXT ranked text inside this run (the sites' edits do not depend on the text: only the header is
    # rewritten), round after round, until green or its texts are exhausted; each rejected text is recorded with its binary and cause
    # T6.c2: after the gate settles, type_census --check on the tree: an unledgered lie whose callee is a live class's name, or a dead
    # type a live class's copies (or a type it deleted) used, rejects that class's text like a gate red — the next text is retried
    # (the inner loop), an exhausted class is undone. Repeated until the check blames no class. An unattributed violation fails the batch.
    names, copies = collections.defaultdict(set), collections.defaultdict(list)
    for _gid, h, _hdr, mem in b.register_cross:
        for _al, ad, own in mem:
            names[h] |= {str(own).lower(), f"func_{ad:08x}" if isinstance(ad, int) else str(ad).lower()}
    for tu, eds in b.edits.items():
        for line, end, _new, h in eds:
            copies[h].append("\n".join(tu_snap[tu].split("\n")[line - 1:end]))
    for h, x in b.cross.items():
        copies[h] += [(REPO / f).read_text(errors="surrogateescape") for f in x["old_headers"] if (REPO / f).exists()]
    copies = {h: "\n".join(v) for h, v in copies.items()}
    rnd, type_checks, type_ok = 0, [], True
    while True:
        while True:
            for h in sorted(cross_red & set(b.cross)):
                x = b.cross[h]
                x["rejects"].append(dict(rank=x["k"] + 1, src=x["cands"][x["k"]]["src"], binary=rc[h][0], cause=rc[h][1]))
            retry = {h for h in cross_red if h in b.cross and next_text(b.cross[h]["cands"], b.cross[h]["k"]) < len(b.cross[h]["cands"])}
            if not retry:
                break
            rnd += 1
            for h in sorted(retry):
                x = b.cross[h]
                x["k"] = next_text(x["cands"], x["k"])
                b.headers[x["hdr"]] = b.cross_header(h)
                (REPO / x["hdr"]).write_text(b.headers[x["hdr"]])
                b.note_cross(h)
            failed_classes -= retry
            tus = {tu for tu, eds in b.edits.items() if any(e[3] in retry for e in eds)}
            apply_classes(tus, failed_classes)
            bins = [a for a in gated if tus_of(a) & tus]
            log(f"  [{label}] retry round {rnd}: {len(retry)} classes on their next text · gating {len(bins)} binaries")
            rc = {}
            red = gate_round(bins, retry, rc)
            failed_classes |= red
            causes.update(rc)
            cross_red = red
            if red:
                undo_and_regate(red, f"after the retry-{rnd} undo of {len(red)} classes")
            for h in sorted(retry - red):
                log(f"  [{label}] cross class {h[:10]} GREEN on rank {b.cross[h]['k'] + 1}/{len(b.cross[h]['cands'])}")
        live = cross_hs - failed_classes
        if not live:
            break
        rc_t, line_t, unl, dead = type_check()
        blame = {}
        for r in unl:
            for h in sorted(live):
                if r["callee"].lower() in names[h]:
                    blame.setdefault(h, []).append(f"unledgered lying {r['callee']} ({r['kind']}, def {r.get('defined_in')})")
        for n in dead:
            for h in sorted(live):
                if re.search(rf"\b{re.escape(n)}\b", copies.get(h, "")):
                    blame.setdefault(h, []).append(f"dead type {n}")
        hit_l = {id(r) for r in unl for h in blame if r["callee"].lower() in names[h]}
        loose = [r for r in unl if id(r) not in hit_l] + [n for n in dead if not any(re.search(rf"\b{re.escape(n)}\b", copies.get(h, "")) for h in blame)]
        type_checks.append(dict(line=line_t, rc=rc_t, unledgered=len(unl), dead=dead, blamed={h: v for h, v in blame.items()},
                                unattributed=[str(x) for x in loose][:20]))
        log(f"  [{label}] {line_t} · blamed {len(blame)} classes" + (f" · UNATTRIBUTED {len(loose)}" if loose else ""))
        if not blame:
            if rc_t or loose:
                type_ok = False
            break
        rc = {}
        for h, why in sorted(blame.items()):
            c_ = collections.Counter(why)
            rc[h] = ("type_census --check", "; ".join(f"{w}" + (f" x{k}" if k > 1 else "") for w, k in sorted(c_.items())))
            log(f"  [{label}] type_census: class {h[:10]} REJECTED — {rc[h][1][:300]}")
        failed_classes |= set(blame)
        causes.update(rc)
        done_ = {h for h in blame if h not in b.cross or next_text(b.cross[h]["cands"], b.cross[h]["k"]) >= len(b.cross[h]["cands"])}
        if done_:
            undo_and_regate(done_, f"after the type_census undo of {len(done_)} classes")
        cross_red = set(blame)
    if any(x.get("dropped") for h, x in b.cross.items() if h not in failed_classes):
        rg = subprocess.run([sys.executable, str(REPO / "tools/ghidra_types.py"), "--write"], cwd=REPO, capture_output=True, text=True)
        log(f"  [{label}] dead types deleted {sorted(n for h, x in b.cross.items() if h not in failed_classes for n in x['dropped'])} · "
            f"ghidra_types --write rc {rg.returncode}")
        type_ok = type_ok and rg.returncode == 0
    for gid, h, hdr, _m in b.register_cross:
        if h in failed_classes and hdr in b.headers:
            (REPO / hdr).unlink(missing_ok=True)
    for h in sorted(failed_classes & cross_hs):
        log(f"  [{label}] cross class {h[:10]} UNDONE at every site — {causes.get(h, ('?', '?'))}"
            + (f" · texts tried {len(b.cross[h]['rejects'])}/{len(b.cross[h]['cands'])}" if h in b.cross else ""))
    if RETRY_EXCEPTED:
        for c in classes:
            if c.get("excepted"):
                n_ = ledger_drop(c["h"])
                if n_:
                    log(f"  [{label}] retry: {n_} previous ledger row(s) of {c['h'][:10]} dropped — this run's verdict replaces them")
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
    text_entries = []
    for gid, th, src, fn, members in b.register_text:
        if th in failed_classes:
            rej = rejected_in(b, th, cen)
            passing = [m for m in members if m[0] not in rej and results.get(m[0], (True,))[0]]
            c = next(x for x in classes if x["h"] == th)
            cb, cause = causes.get(th, ("?", "?"))
            ledger_row(th, reason_for(cause), c["nins"], c["instances"], f"share_body {label} (text tier): rejected in {sorted(rej)}; registered for {len(passing)}; cause ({cb}): {cause}")
            if len(passing) >= 2:
                text_entries.append((gid, th, src, fn, passing))
        else:
            text_entries.append((gid, th, src, fn, members))
    if text_entries:
        registry_append_text(text_entries)
    cross_entries = [e for e in b.register_cross if e[1] not in failed_classes]
    repaired = registry_merge(b, {e[1] for e in cross_entries} & set(b.cross), label)   # T6: a green B class's old groups and headers go
    if cross_entries:
        registry_append_cross(cross_entries)
    reg_entries = reg_entries + text_entries + cross_entries
    # a rejected EXTEND class is ledgered too (its private copies in the rejecting binaries stay)
    for c in classes:
        if c["verdict"] == "B" and c["h"] in failed_classes and not c.get("cross"):    # a cross class is never ledgered (T6)
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
        if c["verdict"] != "B" or c.get("cross"):
            continue
        gid = c["groups"][0]["id"]
        bins = [x for x in b.extend.get(gid, []) if x not in rejected_bins.get(c["h"], set())]
        if bins:
            ext[gid] = bins
    n_ext = add_members_surgical(ext) if ext else 0
    ok_n = sum(1 for a in gated if results[a][0])
    log(f"  [{label}] gated {ok_n}/{len(gated)} binaries green · registered {len(reg_entries)} groups · extended {n_ext} members · "
        f"rejected classes {len(failed_classes)}")
    extra, residue_ok = {}, True
    if b.register_cross and all(results[a][0] for a in gated):
        moves = [m for m in b.moves if m[0] not in failed_classes]
        extra["rekeyed"] = rekey_ledgers(moves)
        log(f"  [{label}] ledgers re-keyed to the headers: {extra['rekeyed']}")
        if moves:
            # every binary whose TU a kept class edited (its include sites too, T6) + the new headers (a moved-from header is gone)
            segs = sorted({al for h_ in {m[0] for m in moves} for al, _t in b.members[h_]}) + sorted({m[3] for m in moves})
            extra["restruct_rows"] = rekey_restruct(moves, label)
            residue_ok = restamp_residue(segs, label)
            extra["residue_segments"] = segs
    (RUN / f"batch_{label}.json").write_text(json.dumps(dict(classes=[c["h"] for c in classes], refused=refused,
                                                                results=results, registered=[e[0] for e in reg_entries],
                                                                extended=ext, rejected=sorted(failed_classes),
                                                                causes=causes, exemplars=b.exemplar_note, merged=repaired,
                                                                # T6: per D/B class the chosen rank and, per rejected text, its binary and cause
                                                                cross_rules={h: dict(rank=x["k"] + 1, texts=len(x["cands"]), chosen=x["cands"][x["k"]]["src"],
                                                                                     casts=x["cands"][x["k"]]["casts"], markers=x["cands"][x["k"]]["fakes"],
                                                                                     green=h not in failed_classes, rejects=x["rejects"],
                                                                                     dropped_types=x.get("dropped", []))
                                                                             for h, x in b.cross.items()},
                                                                type_checks=type_checks, type_ok=type_ok, **extra), indent=1) + "\n")
    return len(failed_classes) == 0 and all(results[a][0] for a in gated) and residue_ok and type_ok


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
    # the INVERSE defect — the registry BEHIND the source: a same-vram class whose every instance already includes the header but
    # whose group lists fewer members (T4 converted every macro site; the P15-era group had listed a subset; the verbose `members:`
    # form was skipped silently by add_members_surgical — five 141-member groups sat at 16). Fix: the full member list, in shorthand.
    complete = {}                                  # gid -> (vram, sorted aliases) — only when every instance sits at ONE vram
    for c in cen["classes"]:
        if c["verdict"] != "B" or c["excepted"] or "E" in c["flags"] or "F" in c["flags"] or len(c.get("groups", [])) != 1:
            continue
        if any(i["form"] != "include" for i in c["insts"]) or len(c["addrs"]) != 1:
            continue
        g = c["groups"][0]
        listed = {bn for bn, _, _ in m2h.sc_group_members(g)}
        aliases = sorted({i["alias"] for i in c["insts"]})
        if set(aliases) - listed:
            complete[g["id"]] = (int(c["addrs"][0], 16), aliases, len(set(aliases) - listed))
    p = REPO / "config/dedup.us.yaml"
    lines = p.read_text().splitlines(keepends=True)
    cur, n_removed, touched, thin = None, 0, 0, []
    n_added, converted, k = 0, [], 0
    out = []
    while k < len(lines):
        ln = lines[k]
        m = re.match(r"^\s*-?\s*id:\s*(\S+)\s*$", ln)
        if m:
            cur = m.group(1)
            out.append(ln); k += 1
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
            out.append(f"{head}[{', '.join(keep)}]{tail}")
            cur = None; k += 1
            continue
        if cur and cur in complete and re.match(r"^\s*binaries:\s*\[", ln):
            vram, aliases, missing = complete[cur]
            head = ln.split("[", 1)[0]
            out.append(f"{head}[{', '.join(aliases)}]\n")
            n_added += missing
            cur = None; k += 1
            continue
        if cur and cur in complete and re.match(r"^\s*members:\s*$", ln):
            vram, aliases, missing = complete[cur]
            indent = ln[:len(ln) - len(ln.lstrip())]
            out.append(f"{indent}vram: 0x{vram:08X}\n{indent}binaries: [{', '.join(aliases)}]\n")
            k += 1
            while k < len(lines) and re.match(r"^\s+-\s*\{", lines[k]):   # drop the `- { binary: …, vram: …, name: … }` rows
                k += 1
            n_added += missing
            converted.append(cur)
            cur = None
            continue
        out.append(ln); k += 1
    p.write_text("".join(out))
    rec = dict(groups=touched, members_removed=n_removed, removals={g: sorted(v) for g, v in removals.items()},
               thin_groups=thin, verbose_skipped=verbose, members_added=n_added, completed_groups=sorted(complete),
               converted_to_shorthand=converted)
    (RUN / "repair_registry.json").write_text(json.dumps(rec, indent=1) + "\n")
    log(f"repair-registry: {n_removed} listed-but-private members removed from {touched} groups; groups left with <2 members: "
        f"{len(thin)} {thin[:5]}; verbose groups with a private member (left alone): {len(verbose)} {verbose[:5]}; "
        f"{n_added} including-but-unlisted members added to {len(complete)} groups ({len(converted)} converted to shorthand: {converted})")
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
    global RETRY_EXCEPTED
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--retry-excepted", action="store_true", help="let the classes ledgered in config/dedup_exceptions.tsv back into the plan; a class that shares loses its row, a rejection re-ledgers it with the fresh diagnostic (P37 T4)")
    ap.add_argument("--plan", action="store_true")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--bucket", choices=["extend", "new", "text", "cross"], default="new")
    ap.add_argument("--batch", type=int, default=120)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--batches", type=int, default=1,
                    help="batches per invocation (default 1: every batch's edit positions come from THIS run's census, which read "
                         "committed text; commit between runs — a later batch would edit TUs the earlier one already changed)")
    ap.add_argument("--only", default="", help="h_exact prefix(es), comma-separated: restrict the --apply pool to these classes")
    ap.add_argument("--label", default="", help="the batch label for the log lines and batch_<label>.json (default <bucket><n>)")
    ap.add_argument("--repair-registry", action="store_true",
                    help="remove every listed member whose site is still a private definition (derived from the census), then exit")
    ap.add_argument("--reexemplar", default="",
                    help="<h_exact prefix>: rewrite a registered class's header from the MAJORITY private text, re-gate its includers, "
                         "then share its private copies (the class's ledger row is dropped when anything shares)")
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
    ap.add_argument("--rekey-batch", default="", metavar="LABEL",
                    help="re-key the ledgers (restruct rung-S rows included) and re-run the residue steps for the committed cross batch "
                         "batch_<LABEL>.json, then exit (idempotent; T4.c3)")
    a = ap.parse_args()
    if a.rekey_batch:
        RUN.mkdir(parents=True, exist_ok=True)
        sys.exit(0 if rekey_batch(a.rekey_batch) else 1)
    RETRY_EXCEPTED = bool(getattr(a, "retry_excepted", False))
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
    if a.plan and a.bucket == "cross":
        cross, differs = cross_candidates(cen)
        ef = collections.Counter("E+F" if "F" in c["flags"] else "E-only" for c in cross)
        na = collections.Counter("2 addr" if len(c["addrs"]) == 2 else "3+ addr" for c in cross)
        by_v = collections.Counter(c["verdict"] + ("/twin" if "TWIN-COVERED" in c["flags"] else "") for c in cross)
        log(f"share_body: cross pool by verdict (T6: B, D and twin-covered join C): "
            + " · ".join(f"{v} {n} classes / {sum(c['instances'] for c in cross if c['verdict'] + ('/twin' if 'TWIN-COVERED' in c['flags'] else '') == v):,} inst"
                         for v, n in sorted(by_v.items())))
        log(f"share_body: cross (flag E/F) {len(cross)} classes / {sum(c['instances'] for c in cross):,} instances · "
            f"{dict(sorted(ef.items()))} · {dict(sorted(na.items()))} · alias-form {sum(1 for c in cross if 'ALIAS' in c['flags'])} · "
            f"TEXT-DIFFERS {len(differs)} classes (skipped, not ledgered)")
        for c in cross[:8]:
            log(f"    {c['verdict']} {c['h'][:12]} {','.join(c['flags']):14s} {c['instances']:4d} inst x {c['nins']:5d} ins {len(c['addrs'])} addrs {c['addrs'][:3]}")
        return
    if a.plan:
        bands = collections.Counter(c["band"] for c in new)
        log(f"  new by band: {dict(bands)}; differing-text classes {sum(1 for c in new if c['verdict'] == 'D')}; "
            f"with pins {sum(1 for c in new if 'PINS' in c['flags'])}; alias-form {sum(1 for c in new if 'ALIAS' in c['flags'])}")
        for c in new[:8]:
            log(f"    {c['verdict']} {','.join(c['flags']) or '-':14s} {c['instances']:4d} inst x {c['nins']:5d} ins {c['addrs'][0]} private {c['copies']}")
        return
    if not a.apply:
        return
    pool = extend if a.bucket == "extend" else new if a.bucket == "new" else cross_candidates(cen)[0] if a.bucket == "cross" else text_candidates(cen)
    if a.bucket == "cross":                          # T6.c3: classes a T6 batch already rejected on every text or refused
        settled = cross_settled()
        skipped = [c for c in pool if c["h"] in settled]
        pool = [c for c in pool if c["h"] not in settled]
        log(f"share_body: cross — skipped {len(skipped)} classes settled red by a T6 batch (rejected on every text or refused)")
    if a.bucket == "text":
        log(f"share_body: text tier — {len(pool)} same-address text classes / {sum(len(c['insts']) for c in pool):,} private sites")
    if a.only:
        pool = [c for c in pool if c["h"].startswith(tuple(a.only.split(",")))]  # comma-separated prefixes (P38 T6.c2)
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
        lbl = a.label if a.label and a.batches == 1 else f"{a.label or a.bucket}{k // a.batch + 1}"
        if a.bucket == "cross":                      # the headers, sites, registry and ledgers are fleet-shared state: hold the writer lock
            import shared_lock
            with shared_lock.hold(exclusive=True, announce="share_body --bucket cross"):
                ok = run_batch(orc, cen, chunk, lbl)
        else:
            ok = run_batch(orc, cen, chunk, lbl)
        all_ok = all_ok and ok
        done += len(chunk)
    log(f"share_body: done — {done} of {len(pool)} classes in {min(a.batches, (len(pool) + a.batch - 1) // a.batch)} batch(es); "
        f"{'all green' if all_ok else 'see the ledger'}; {time.time() - t0:.0f} s")


if __name__ == "__main__":
    main()
