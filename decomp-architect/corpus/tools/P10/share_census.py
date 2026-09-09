#!/usr/bin/env python3
"""share_census.py — the census of duplicate function bodies across the fleet, and the S1 invariant checker:
"ONE SOURCE PER UNIQUE FUNCTION" (Phase 35 T1, 2026-09-08).

    tools/share_census.py                      # the census: summary + controls to stdout; .run/P35/census/{share_census.json,share_census.txt}
    tools/share_census.py --check              # S1: every same-address byte-identical class with >=2 instances shares ONE source,
                                               #     is twin-covered, or is ledgered in config/dedup_exceptions.tsv -> exit 1 otherwise
    tools/share_census.py --check --strict-macros --strict-text   # the post-conversion form of S1 (T7 wires it into tools-health)
    tools/share_census.py --selftest           # the R39 fixture: every verdict/flag exercised in memory, no tree needed
    tools/share_census.py --scope all          # count the deferred cross-address / cross-space classes as violations too

WHAT IT MEASURES (keyed by h_exact = SHA1 of the raw instruction bytes, tools/sig_image.py; relocated immediates INCLUDED, so two
instances with one h_exact reference identical addresses and their derived names coincide). A CLASS is one h_exact with >=2 instances
fleet-wide (218 binaries). Every instance gets exactly ONE source form from the binary's own translation units:
    macro          DEFINE_func_X()                       (the Phase-15 shared-body form; retired at T4)
    macro-param    SETTER(func_X,..)/RETCONST/CLEAR_TBL40  (the three legacy name-parameterized headers)
    include        #include "../shared/<..>.h" that DEFINES the function   (the Phase-35 form; sotn's shape)
    param-include  #define SHARED_FN func_X / #include ../shared/<..>.h / #undef   (the cross-address form; clearTbl40 after T4)
    def            an inline C definition (a private copy)
    stub           INCLUDE_ASM(...)  (none left in game code; kept so the census can never mistake one for a copy)
    asm-verbatim   the five PERMANENT hand-asm bodies of config/verbatim_manifest.json (the authoritative list, never a regex)
and a sig instance with ZERO or >=2 forms is a COVERAGE DEFECT that fails the run (R32) — a silent skip is exactly the defect class
this project has paid for most often.

VERDICT per class      A  registered (config/dedup.us.yaml) and every instance is a member whose site is a shared form
                       B  registered but an instance is missing from the group, or a member's site is still a private copy
                       C  unregistered; every copy is a private definition with the SAME normalized text (name-blind, comment-free)
                       D  unregistered; the copies' texts DIFFER (matched independently) — one text must be chosen and re-gated
                       M  unregistered, MIXED forms (a shared-form site without a group — e.g. a macro instantiated in one binary)
FLAGS (orthogonal)     E  cross-address (the member's own name differs per site -> the name-parameterized form; DEFERRED by decision)
                       F  cross-space (instances in different address spaces: the overlay slot, a module slot base, main, resident)
                       TWIN-COVERED  every instance's source dir is one directory (a twin binary built from its primary, T3)
                       TWIN-PENDING  every instance lives in binaries of ONE identical-payload twin set (T3 will cover it)
                       TYPEDEF / PINS / ALIAS  the copy carries a local type definition / register pins / an asm-label alias
S1 (--check): violations = classes with verdict != A that are neither TWIN-COVERED nor (E or F, unless --scope all) nor ledgered in
config/dedup_exceptions.tsv (h_exact  reason  nins  instances  note). --strict-macros adds "no DEFINE_func_ token under src/";
--strict-text adds the SECOND, sig-blind oracle (R34): no name-blind normalized definition text appears in >1 translation unit
outside src/shared/. Both are informational until T7.

ORACLES (derived, never hand-listed — R33): the fleet and each binary's source dir from the Makefile (`compile_only.src_dirs`, asserted
equal to the set of config/check.*.sha contracts, R32); address spaces from `<alias>_VRAM_BASE`; twin sets from equal contracts;
names from each binary's own symbol stack (`corpus.symbols`) else func_<ADDR>; groups through the ONE registry parser
`dedup_integrate.group_members`. Outputs: the small summary JSON + the human table are tracked evidence; classes.jsonl (every class)
and the per-TU scan cache stay ignored scratch. R41: every number in the summary names its denominator.
"""
import argparse
import collections
import hashlib
import json
import os
import pathlib
import re
import sys
import time
from concurrent.futures import ProcessPoolExecutor

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))

SHARED_FORMS = {"macro", "macro-param", "include", "param-include"}
KEYWORDS = {"if", "while", "for", "switch", "return", "else", "goto", "case", "sizeof", "do", "typedef",
            "struct", "union", "enum", "defined", "break", "continue", "default"}
FUNC_RE = re.compile(r"func_([0-9A-Fa-f]{8})$")
OUT_DIR_DEFAULT = ".run/P35/census"

# ----------------------------------------------------------------------------------------------------------------------
# text masking: comments, dead preprocessor halves, macro-continuation blocks -> spaces (newlines kept, so line numbers hold)
# ----------------------------------------------------------------------------------------------------------------------
_TOK = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)


def _blank_keep_newlines(s):
    return re.sub(r"[^\n]", " ", s)


def mask_text(text):
    """Comments become spaces (string/char literals are KEPT — include paths and asm labels live in them; the brace walk skips them);
    dead `#if 0` blocks and the `#ifdef NON_MATCHING` half are blanked; `#define ... \\` continuation blocks are blanked (a
    definition inside a macro body is macro text, not a definition)."""
    def repl(m):
        s = m.group(0)
        if s.startswith("/*") or s.startswith("//"):
            return _blank_keep_newlines(s)
        return s
    t = _TOK.sub(repl, text)
    lines = t.split("\n")
    out, i, n = [], 0, len(lines)
    depth_stack = []        # entries: 'dead' (blank until the matching #endif) / 'live' (an #if we do not evaluate)
    in_macro = False
    for ln in lines:
        s = ln.strip()
        if in_macro:
            out.append("")
            in_macro = ln.rstrip().endswith("\\")
            continue
        if s.startswith("#"):
            d = s[1:].strip()
            if re.match(r"if\s+0\b", d) or d.startswith("ifdef NON_MATCHING"):
                depth_stack.append("dead")
                out.append("")
                continue
            if d.startswith(("if", "ifdef", "ifndef")):
                depth_stack.append("live")
                out.append("")
                continue
            if d.startswith("else") or d.startswith("elif"):
                if depth_stack and depth_stack[-1] == "dead":
                    depth_stack[-1] = "live-else"          # the #else half of a dead block is live
                elif depth_stack and depth_stack[-1] == "live-else":
                    depth_stack[-1] = "dead"
                out.append("")
                continue
            if d.startswith("endif"):
                if depth_stack:
                    depth_stack.pop()
                out.append("")
                continue
            if d.startswith("define") and ln.rstrip().endswith("\\"):
                in_macro = True
                out.append("")
                continue
        if any(x == "dead" for x in depth_stack):
            out.append("")
            continue
        out.append(ln)
    return "\n".join(out)


# ----------------------------------------------------------------------------------------------------------------------
# the per-TU scanner
# ----------------------------------------------------------------------------------------------------------------------
# a head may follow a line start OR a ';' on the same line (a one-line `extern …; int f(…) { … }` is a real shape in the tree)
HEAD = re.compile(r"(?:^|(?<=;))[ \t]*([A-Za-z_][\w \t\*]*?)\b([A-Za-z_]\w*)[ \t]*\(", re.M)
# a name at line start with NO type prefix (implicit int / the type on the line above); the body-extent check decides
BARE_HEAD = re.compile(r"^[ \t]*([A-Za-z_]\w*)[ \t]*\(", re.M)
MACRO_SITE = re.compile(r"^[ \t]*DEFINE_(func_[0-9A-Fa-f]{8})\(\)", re.M)
MACRO_PARAM_SITE = re.compile(r"^[ \t]*(SETTER|RETCONST|CLEAR_TBL40)\(\s*([A-Za-z_]\w*)", re.M)
INCLUDE_LINE = re.compile(r'^[ \t]*#[ \t]*include[ \t]+"([^"]+)"', re.M)
STUB = re.compile(r"INCLUDE_ASM\([^)]*,\s*([A-Za-z_]\w*)\s*\)")
# the parameter list may not contain parentheses (a function-pointer parameter would surface as an unaccounted instance, loudly)
ALIAS_DECL = re.compile(r"\b([A-Za-z_]\w*)\s*\([^;{}()]*\)\s*(?:__asm__|asm)\s*\(\s*\"(func_[0-9A-Fa-f]{8})\"\s*\)")
SHARED_FN_DEF = re.compile(r"^[ \t]*#[ \t]*define[ \t]+SHARED_FN[ \t]+([A-Za-z_]\w*)", re.M)
SHARED_FN_UNDEF = re.compile(r"^[ \t]*#[ \t]*undef[ \t]+SHARED_FN\b", re.M)
PIN_RE = re.compile(r'register [^;]*__asm__\("\$?[a-z0-9]+"\)')
TYPEDEF_RE = re.compile(r"\b(typedef\b|(struct|union|enum)\s+\w*\s*\{)")
_BRACE = re.compile(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|[{}]')     # literals are matched and ignored


def _body_extent(masked, head_end):
    """From the '(' at head_end-1: walk the parameter parens, then decide prototype / definition; return (kind, open_idx, close_idx).
    kind: 'proto' or 'def'. For a def, open_idx/close_idx index the body's braces in `masked`."""
    i, depth, n = head_end - 1, 0, len(masked)
    while i < n:
        c = masked[i]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                break
        i += 1
    if i >= n:
        return ("proto", None, None)
    j = i + 1
    # after the parameter list: whitespace, then ';' (prototype), '{' (definition) or K&R declarations / an asm label
    while j < n and masked[j] in " \t\r\n":
        j += 1
    if j >= n:
        return ("proto", None, None)
    if masked[j] == ";":
        return ("proto", None, None)
    if masked[j] != "{":
        # Something stands between the parameter list and the next '{'. It is a DEFINITION only if that something is K&R
        # parameter declarations (`type name;` parts, nothing after the last ';'); an asm label, a directive, a call statement,
        # or the head of the NEXT function all make this a declaration/statement, not a body.
        seg_end_brace = masked.find("{", j)
        if seg_end_brace == -1:
            return ("proto", None, None)
        seg = masked[j:seg_end_brace]
        if "__asm__" in seg or "asm(" in seg or "#" in seg:
            return ("proto", None, None)
        parts = seg.split(";")
        if len(parts) < 2 or parts[-1].strip() or not all(re.fullmatch(r"\s*[A-Za-z_][\w \t\*\[\],]*\s*", p) for p in parts[:-1]):
            return ("proto", None, None)
        j = seg_end_brace
    # brace walk from j
    depth = 0
    for m in _BRACE.finditer(masked, j):
        tok = m.group(0)
        if tok == "{":
            depth += 1
        elif tok == "}":
            depth -= 1
            if depth == 0:
                return ("def", j, m.start())
    return ("proto", None, None)


def _norm(body, names):
    t = body
    for nm in sorted(set(names), key=len, reverse=True):
        t = re.sub(r"\b%s\b" % re.escape(nm), "@FN@", t)
    t = re.sub(r"\s+", " ", t).strip()
    return hashlib.sha1(t.encode("utf-8", "surrogateescape")).hexdigest()


def scan_text(text, rel, shared_defs=None):
    """All site records of one file. Records: dict(form, name, line, ...). shared_defs: header path -> defined names (for includes)."""
    masked = mask_text(text)
    recs = []
    line_of = lambda idx: masked.count("\n", 0, idx) + 1
    aliases = {a: s for a, s in ALIAS_DECL.findall(masked)}             # alias ident -> real symbol
    for m in MACRO_SITE.finditer(masked):
        recs.append(dict(form="macro", name=m.group(1), line=line_of(m.start())))
    for m in MACRO_PARAM_SITE.finditer(masked):
        recs.append(dict(form="macro-param", name=m.group(2), line=line_of(m.start()), via=m.group(1)))
    for m in STUB.finditer(masked):
        recs.append(dict(form="stub", name=m.group(1), line=line_of(m.start())))
    # includes (resolved by the caller through shared_defs), with the SHARED_FN state
    if shared_defs is not None:
        events = [(m.start(), "def", m.group(1)) for m in SHARED_FN_DEF.finditer(masked)]
        events += [(m.start(), "undef", None) for m in SHARED_FN_UNDEF.finditer(masked)]
        events += [(m.start(), "inc", m.group(1)) for m in INCLUDE_LINE.finditer(masked)]
        cur = None
        for pos, kind, val in sorted(events):
            if kind == "def":
                cur = val
            elif kind == "undef":
                cur = None
            else:
                key = os.path.normpath(os.path.join(os.path.dirname(rel), val))
                defs = shared_defs.get(key)
                if not defs:
                    continue
                for nm in defs:
                    if nm == "SHARED_FN":
                        if cur:
                            recs.append(dict(form="param-include", name=cur, line=line_of(pos), header=key))
                    else:
                        recs.append(dict(form="include", name=nm, line=line_of(pos), header=key))
    # definitions
    seen_heads = set()
    heads = [(m.start(), m.end(), m.group(2), m.group(1)) for m in HEAD.finditer(masked)]
    heads += [(m.start(), m.end(), m.group(1), "") for m in BARE_HEAD.finditer(masked)]
    for start, end, name, prefix in heads:
        if name in KEYWORDS or end in seen_heads:
            continue
        seen_heads.add(end)
        if "inline" in prefix.split():
            continue        # a `static inline` helper is expanded into its callers: it owns no address and is no sig instance
        kind, o, c = _body_extent(masked, end)
        if kind != "def":
            continue
        body = masked[start:c + 1]
        real = aliases.get(name, name)
        recs.append(dict(form="def", name=real, line=line_of(start), end=line_of(c), alias=(real != name),
                         text_hash=_norm(body, [name, real]), pins=bool(PIN_RE.search(body)),
                         typedef=bool(TYPEDEF_RE.search(body)), nlines=body.count("\n") + 1,
                         empty=(not masked[o + 1:c].strip())))
    return recs


def header_defined_names(path):
    """The function names a shared header DEFINES (masked: macro bodies never count)."""
    return sorted({n for n, _ in header_defs(path)})


def header_defs(path):
    """[(name, empty)] for every function a shared header DEFINES, in file order — the one reader every consumer of the
    Phase-35 include form shares (progress.py, overlay_src_split.py, dedup_integrate.py); `empty` = nothing between the braces.
    A header that only defines macros (engine_core.h) defines no function here, by masking."""
    p = pathlib.Path(path)
    if not p.is_absolute():
        p = REPO / p
    if not p.exists():
        return []
    text = p.read_text(errors="surrogateescape")
    rel = p.relative_to(REPO).as_posix() if p.is_relative_to(REPO) else str(p)
    recs = scan_text(text, rel, shared_defs=None)
    return [(r["name"], r["empty"]) for r in recs if r["form"] == "def"]


def _scan_worker(args):
    rel, mtime, size, shared_defs = args
    p = REPO / rel
    text = p.read_text(errors="surrogateescape")
    return rel, scan_text(text, rel, shared_defs)


# ----------------------------------------------------------------------------------------------------------------------
# oracles
# ----------------------------------------------------------------------------------------------------------------------
def contracts():
    """alias -> its config/check.<x>.sha path, from the Makefile's `<alias>_CHECK_SHA :=` (main's contract is check.us.sha)."""
    out = {}
    texts = [(REPO / "Makefile").read_text()] + [p.read_text() for p in sorted((REPO / "config").glob("*.mk"))]
    for t in texts:
        for m in re.finditer(r"^(\w+)_CHECK_SHA\s*:?=\s*(\S+)", t, re.M):
            out[m.group(1)] = m.group(2)
    return out


def fleet_and_dirs():
    import compile_only
    dirs = compile_only.src_dirs()
    con = contracts()
    on_disk = {p.relative_to(REPO).as_posix() for p in (REPO / "config").glob("check.*.sha")}
    if set(dirs) != set(con) or set(con.values()) != on_disk:
        sys.exit("share_census: the Makefile's binaries, its _CHECK_SHA contracts and config/check.*.sha DISAGREE (R32): "
                 f"dirs-only {sorted(set(dirs) - set(con))[:8]}, contracts-only {sorted(set(con) - set(dirs))[:8]}, "
                 f"files-not-declared {sorted(on_disk - set(con.values()))[:8]}, declared-not-on-disk {sorted(set(con.values()) - on_disk)[:8]}")
    return sorted(dirs), dirs


def vram_bases():
    out = {}
    texts = [(REPO / "Makefile").read_text()] + [p.read_text() for p in sorted((REPO / "config").glob("*.mk"))]
    for t in texts:
        for m in re.finditer(r"^(\w+)_VRAM_BASE\s*:?=\s*(0x[0-9A-Fa-f]+)", t, re.M):
            out[m.group(1)] = int(m.group(2), 16)
    return out


def twin_sets(aliases):
    by_sha = collections.defaultdict(list)
    con = contracts()
    for a in aliases:
        sha = (REPO / con[a]).read_text().split()[0]
        by_sha[sha].append(a)
    sets = {}
    for sha, members in by_sha.items():
        if len(members) > 1:
            for a in members:
                sets[a] = tuple(sorted(members))
    return sets


def twin_of_map():
    out = {}
    for p in sorted((REPO / "config").glob("*.mk")):
        for m in re.finditer(r"^(\w+)_TWIN_OF\s*:?=\s*(\w+)", p.read_text(), re.M):
            out[m.group(1)] = m.group(2)
    return out


def sig_rows(alias):
    p = REPO / ".run" / f"sig.{alias}.jsonl"
    if not p.exists():
        sys.exit(f"share_census: {p.relative_to(REPO)} is missing — run `make tools-health` (or the sig-* targets) first; the census "
                 f"refuses to measure a fleet it cannot see (R43)")
    rows = []
    for ln in p.read_text().splitlines():
        if not ln.strip():
            continue
        r = json.loads(ln)
        rows.append((int(r["addr"], 16), int(r.get("nins", 0)), r["h_exact"], r.get("name")))
    return rows


def curated_names(alias):
    import corpus
    try:
        syms = corpus.symbols(alias)
    except Exception:
        syms = {}
    return {addr: nm for nm, addr in syms.items()}


def load_groups():
    import yaml
    d = yaml.safe_load((REPO / "config" / "dedup.us.yaml").read_text())
    return d["groups"] if isinstance(d, dict) else d


def verbatim_instances():
    d = json.loads((REPO / "config" / "verbatim_manifest.json").read_text())
    return {(r["binary"], int(r["addr"], 16)) for r in d["rows"]}


def load_exceptions(path):
    out = {}
    p = REPO / path
    if not p.exists():
        return out
    for ln in p.read_text().splitlines():
        if not ln.strip() or ln.startswith("#") or ln.startswith("h_exact\t"):
            continue
        parts = ln.split("\t")
        out[parts[0]] = dict(reason=parts[1] if len(parts) > 1 else "?", note=parts[-1])
    return out


# ----------------------------------------------------------------------------------------------------------------------
# the census
# ----------------------------------------------------------------------------------------------------------------------
def build_forms(aliases, dirs, jobs, use_cache=True, out_dir=None):
    """(alias -> {addr: rec}), coverage notes. One scan per TU, cached by (mtime, size)."""
    import compile_only
    # shared headers: which function names each defines (masked, so macro-only headers define nothing)
    shared_defs = {}
    for p in sorted((REPO / "src" / "shared").rglob("*.h")):
        shared_defs[p.relative_to(REPO).as_posix()] = header_defined_names(p)
    cache_p = (REPO / (out_dir or OUT_DIR_DEFAULT) / "cache" / "scan_cache.json")
    cache = {}
    if use_cache and cache_p.exists():
        try:
            cache = json.loads(cache_p.read_text())
        except Exception:
            cache = {}
    work, tu_of = [], {}
    for a in aliases:
        for p in compile_only.tus_of(a, dirs):
            rel = p.relative_to(REPO).as_posix()
            st = p.stat()
            tu_of.setdefault(a, []).append(rel)
            key = f"{rel}|{int(st.st_mtime)}|{st.st_size}"
            if key not in cache:
                work.append((rel, int(st.st_mtime), st.st_size, shared_defs))
    scanned = {}
    if work:
        with ProcessPoolExecutor(max_workers=jobs) as ex:
            for rel, recs in ex.map(_scan_worker, work, chunksize=8):
                scanned[rel] = recs
    new_cache = {}
    forms, notes = {}, dict(unresolved_names=[], multi_form=[], stubs_unsigned=0)
    for a in aliases:
        names = curated_names(a)
        rev = {nm: addr for addr, nm in names.items()}
        per = {}
        for rel in tu_of.get(a, []):
            st = (REPO / rel).stat()
            key = f"{rel}|{int(st.st_mtime)}|{st.st_size}"
            recs = scanned.get(rel) if rel in scanned else cache.get(key)
            if recs is None:
                recs = scan_text((REPO / rel).read_text(errors="surrogateescape"), rel, shared_defs)
            new_cache[key] = recs
            for r in recs:
                nm = r["name"]
                m = FUNC_RE.match(nm)
                addr = int(m.group(1), 16) if m else rev.get(nm)
                if addr is None:
                    if r["form"] != "stub":
                        notes["unresolved_names"].append(f"{a}:{rel}:{r['line']}:{nm}:{r['form']}")
                    continue
                rec = dict(r, tu=rel)
                if addr in per and per[addr]["form"] != "stub" and rec["form"] != "stub":
                    notes["multi_form"].append(f"{a}:0x{addr:08X}:{per[addr]['form']}@{per[addr]['tu']}:{per[addr]['line']} vs "
                                               f"{rec['form']}@{rel}:{rec['line']}")
                    continue
                if addr in per and rec["form"] == "stub":
                    continue
                per[addr] = rec
        forms[a] = per
    if use_cache:
        cache_p.parent.mkdir(parents=True, exist_ok=True)
        cache_p.write_text(json.dumps(new_cache))
    return forms, notes


def classify(sigs, forms, groups, spaces, dirs, twins, twin_of, verbatim, exceptions, scope="same-vram", keep_instances=False):
    """Pure: sigs {alias: [(addr,nins,h,name)]}, forms {alias: {addr: rec}}, groups (registry list), spaces {alias: base},
    dirs {alias: src dir}, twins {alias: twin-set tuple}, twin_of {alias: primary}, verbatim {(alias,addr)}, exceptions {h: ...}."""
    from dedup_integrate import group_members
    # registry index
    reg = collections.defaultdict(list)
    reg_text = {}                     # (binary, vram) -> the h_text group listing that site (Phase 35 T5b: groups keyed by TEXT, not bytes)
    for g in groups:
        if g.get("tier") == "h_text":
            for b, addr, _ in group_members(g):
                reg_text[(b, addr)] = g
            continue
        reg[g.get("hash")].append(g)
    # instances
    classes = collections.defaultdict(list)
    unaccounted = []
    n_inst = 0
    for a, rows in sigs.items():
        per = forms.get(a, {})
        for addr, nins, h, name in rows:
            n_inst += 1
            rec = per.get(addr)
            if rec is None and (a, addr) in verbatim:
                rec = dict(form="asm-verbatim", name=name, tu=None, line=None)
            if rec is None:
                unaccounted.append(f"{a}:0x{addr:08X}:{name}:nins={nins}")
                continue
            classes[h].append(dict(alias=a, addr=addr, nins=nins, name=name, form=rec["form"], tu=rec.get("tu"),
                                   text_hash=rec.get("text_hash"), pins=rec.get("pins", False), typedef=rec.get("typedef", False),
                                   alias_form=rec.get("alias", False), line=rec.get("line"), end=rec.get("end"),
                                   nlines=rec.get("nlines", 0)))
    out = []
    for h, insts in classes.items():
        if len(insts) < 2:
            continue
        gs = reg.get(h, [])
        members = set()
        text_tier = False
        for g in gs:
            for b, addr, _ in group_members(g):
                members.add((b, addr))
        inst_set = {(i["alias"], i["addr"]) for i in insts}
        if not gs:
            tgs = {id(reg_text[s]): reg_text[s] for s in inst_set if s in reg_text}
            if tgs:                        # the sites share by TEXT (h_text tier): registered iff every site is listed
                gs = list(tgs.values()); text_tier = True
                members = {s for s in inst_set if s in reg_text}
        forms_seen = collections.Counter(i["form"] for i in insts)
        addrs = sorted({i["addr"] for i in insts})
        aliases = sorted({i["alias"] for i in insts})
        space_set = {spaces.get(i["alias"], -1) for i in insts}
        flags = []
        if len(addrs) > 1:
            flags.append("E")
        if len(space_set) > 1:
            flags.append("F")
        src_dirs = {dirs.get(i["alias"]) for i in insts}
        if len(aliases) > 1 and len(src_dirs) == 1:
            flags.append("TWIN-COVERED")
        elif len(aliases) > 1 and all(a in twins for a in aliases) and len({twins[a] for a in aliases}) == 1:
            flags.append("TWIN-PENDING")
        if any(i["typedef"] for i in insts):
            flags.append("TYPEDEF")
        if any(i["pins"] for i in insts):
            flags.append("PINS")
        if any(i["alias_form"] for i in insts):
            flags.append("ALIAS")
        if any(i["form"] == "stub" for i in insts):
            flags.append("STUB")
        if gs:
            missing = sorted(inst_set - members)
            extra = [] if text_tier else sorted(members - inst_set)
            bad_site = [i for i in insts if (i["alias"], i["addr"]) in members and i["form"] not in SHARED_FORMS]
            verdict = "A" if not missing and not bad_site and not extra else "B"
            detail = dict(groups=[g.get("id") for g in gs], missing=len(missing), extra=len(extra), bad_site=len(bad_site))
        else:
            defs = [i for i in insts if i["form"] == "def"]
            if len(defs) == len(insts):
                texts = {i["text_hash"] for i in insts}
                verdict = "C" if len(texts) == 1 else "D"
                detail = dict(texts=len(texts))
            else:
                verdict = "M"
                detail = dict(forms=dict(forms_seen))
        nins = max(i["nins"] for i in insts)
        band = "1-7" if nins < 8 else "8-15" if nins < 16 else "16-31" if nins < 32 else "32+"
        excepted = exceptions.get(h)
        deferred = ("E" in flags or "F" in flags) and scope != "all"
        violation = (verdict != "A") and ("TWIN-COVERED" not in flags) and not deferred and not excepted
        # copies = DISTINCT private-definition sites (a twin's instance resolves to its primary's TU — one source, not two)
        copies = len({i["tu"] for i in insts if i["form"] == "def" and i["tu"]})
        row = dict(h=h, verdict=verdict, flags=flags, nins=nins, band=band, instances=len(insts), copies=copies,
                   aliases=aliases, addrs=[f"0x{x:08X}" for x in addrs], forms=dict(forms_seen), detail=detail,
                   excepted=(excepted or {}).get("reason"), deferred=deferred, violation=violation,
                   names=sorted({i["name"] for i in insts})[:4])
        if keep_instances:
            row["insts"] = insts                      # for share_body.py: the per-instance records (never written to classes.jsonl)
            row["groups"] = gs
        out.append(row)
    out.sort(key=lambda c: (-c["instances"] * c["nins"], c["h"]))
    return out, dict(instances=n_inst, classified=n_inst - len(unaccounted), unaccounted=unaccounted)


def summarize(classes, cov, notes, aliases):
    by_v = collections.Counter(c["verdict"] for c in classes)
    by_f = collections.Counter(f for c in classes for f in c["flags"])
    inst_by_v = collections.Counter()
    ins_by_v = collections.Counter()
    for c in classes:
        inst_by_v[c["verdict"]] += c["instances"]
        ins_by_v[c["verdict"]] += c["instances"] * c["nins"]
    same_vram_unreg = [c for c in classes if c["verdict"] in ("B", "C", "D", "M") and "E" not in c["flags"] and "F" not in c["flags"]
                       and "TWIN-COVERED" not in c["flags"]]
    twin_covered = [c for c in classes if "TWIN-COVERED" in c["flags"] and c["verdict"] != "A"]
    cross = [c for c in classes if ("E" in c["flags"] or "F" in c["flags"]) and c["verdict"] != "A"]
    return dict(
        binaries=len(aliases), sig_instances=cov["instances"], classified=cov["classified"], unaccounted=len(cov["unaccounted"]),
        classes_ge2=len(classes), verdicts=dict(by_v), instances_by_verdict=dict(inst_by_v), ins_by_verdict=dict(ins_by_v),
        flags=dict(by_f),
        # the backlog = same-vram classes NOT yet one source: `copies` counts distinct private sites, `collapsible` the sites
        # that will disappear when each class has one source (copies − 1), never instances (a twin's instance is no site)
        same_vram_unregistered=dict(classes=len(same_vram_unreg), instances=sum(c["instances"] for c in same_vram_unreg),
                                    copies=sum(c["copies"] for c in same_vram_unreg),
                                    collapsible=sum(max(c["copies"] - 1, 0) for c in same_vram_unreg),
                                    ins=sum(c["instances"] * c["nins"] for c in same_vram_unreg),
                                    twin_pending=sum(1 for c in same_vram_unreg if "TWIN-PENDING" in c["flags"]),
                                    twin_pending_instances=sum(c["instances"] for c in same_vram_unreg if "TWIN-PENDING" in c["flags"])),
        twin_covered=dict(classes=len(twin_covered), instances=sum(c["instances"] for c in twin_covered)),
        cross_address_deferred=dict(classes=len(cross), instances=sum(c["instances"] for c in cross),
                                    copies=sum(c["copies"] for c in cross)),
        violations=sum(1 for c in classes if c["violation"]),
        multi_form=len(notes.get("multi_form", [])), unresolved_names=len(notes.get("unresolved_names", [])),
    )


def controls(classes, sigs, forms):
    """The known-true cases (R39). Each returns (name, got, expected)."""
    out = []
    # func_80144B9C: the -O0 whale — 141 include sites, registered for 134 (never extended to the 7 later-onboarded overlays)
    w = [c for c in classes if "0x80144B9C" in c["addrs"] and "ov_SC01_077" in c["aliases"]]
    out.append(("func_80144B9C", f"{w[0]['verdict']}/{w[0]['instances']}/{w[0]['forms']}/missing {w[0]['detail'].get('missing')}" if w else "absent",
                "B/141/{'include': 141}/missing 7  (the registry lists 134; T5 bucket 0 extends it)"))
    # clearTbl40: main 0x80037004 + 0x80037334, one class, registered, cross-vram
    ct = [c for c in classes if "0x80037004" in c["addrs"] and "main" in c["aliases"]]
    out.append(("clearTbl40", f"{ct[0]['verdict']}+{'E' if 'E' in ct[0]['flags'] else '-'}/{ct[0]['instances']}" if ct else "absent", "A+E/2"))
    # ov_setters: the three SC01_005/006 groups — registered for 2 of the 141 instances each (the same trivial body sits at that
    # vram in every overlay); B by construction until T5 extends them
    # Measured S94: the 2-instruction bodies of two of them also sit at OTHER vrams (282 and 145 instances, cross-address), the
    # third only at its own (141) — so the known-true answer is three B classes of 282(E) / 145(E) / 141 instances.
    st = sorted([c for c in classes if any(x in c["addrs"] for x in ("0x8012AD64", "0x8012BF4C", "0x8012E27C")) and "ov_SC01_005" in c["aliases"]],
                key=lambda c: -c["instances"])
    out.append(("ov_setters x3", ",".join(f"{c['verdict']}/{c['instances']}{'(E)' if 'E' in c['flags'] else ''}" for c in st) or "absent",
                "B/282(E),B/145(E),B/141"))
    # twin symmetry: ov_SC01_005 and ov_SC01_006 are one payload, so their unregistered-class counts must be EQUAL (a known-true
    # invariant rather than a remembered number: S75 counted 557 at 174 binaries, the S94 Explore 657 at 218, this census's rule differs)
    def unreg(alias):
        return sum(1 for c in classes if c["verdict"] in ("C", "D", "M") and alias in c["aliases"])
    a5, a6 = unreg("ov_SC01_005"), unreg("ov_SC01_006")
    out.append(("twin symmetry SC01_005 / SC01_006", f"{a5} / {a6}", "equal (each = the twin's unregistered classes)"))
    return out


def render_table(classes, summary, cov_notes, ctrl):
    L = []
    s = summary
    L.append(f"share_census: {s['binaries']} binaries · {s['sig_instances']:,} sig instances · {s['classified']:,} classified · "
             f"{s['unaccounted']} UNACCOUNTED · {s['classes_ge2']:,} h_exact classes with >=2 instances")
    L.append(f"  verdicts (classes): " + " · ".join(f"{k} {v:,}" for k, v in sorted(s['verdicts'].items())))
    L.append(f"  instances by verdict: " + " · ".join(f"{k} {v:,}" for k, v in sorted(s['instances_by_verdict'].items())))
    L.append(f"  flags: " + " · ".join(f"{k} {v:,}" for k, v in sorted(s['flags'].items())))
    u = s["same_vram_unregistered"]
    L.append(f"  SAME-VRAM UNREGISTERED (the phase's backlog): {u['classes']:,} classes · {u['instances']:,} instances · {u['copies']:,} private "
             f"copies · {u['collapsible']:,} collapsible · {u['ins']:,} ins; of which twin-pending {u['twin_pending']:,} classes / "
             f"{u['twin_pending_instances']:,} instances")
    t = s.get("twin_covered", {})
    if t:
        L.append(f"  TWIN-COVERED (one source directory per payload, T3): {t.get('classes', 0):,} classes · {t.get('instances', 0):,} instances")
    d = s["cross_address_deferred"]
    L.append(f"  CROSS-ADDRESS / CROSS-SPACE (deferred to the names phase): {d['classes']:,} classes · {d['instances']:,} instances · "
             f"{d['copies']:,} private copies")
    L.append(f"  S1 violations (scope as run): {s['violations']:,} · multi-form instances {s['multi_form']} · unresolved names {s['unresolved_names']}")
    L.append("  controls (R39):")
    for name, got, exp in ctrl:
        L.append(f"    {name:34s} got {got:40s} expected {exp}")
    L.append("  top classes by instances x nins (verdict flags instances nins addrs names):")
    for c in classes[:25]:
        L.append(f"    {c['verdict']} {','.join(c['flags']) or '-':22s} {c['instances']:4d} x {c['nins']:5d}  {','.join(c['addrs'][:3])}  {','.join(c['names'][:2])}")
    if cov_notes.get("unaccounted"):
        L.append("  UNACCOUNTED (first 20): " + "; ".join(cov_notes["unaccounted"][:20]))
    return "\n".join(L)


# ----------------------------------------------------------------------------------------------------------------------
# the second oracle: duplicate definition TEXT across translation units (sig-blind)
# ----------------------------------------------------------------------------------------------------------------------
def text_duplicates(forms):
    """ANY-address duplicates: a name-blind normalized definition text present in >1 TU (the cross-address ones are the names
    phase's — reported as a count, never a violation here)."""
    by_text = collections.defaultdict(set)
    for a, per in forms.items():
        for addr, rec in per.items():
            if rec["form"] == "def" and rec.get("text_hash") and rec.get("nlines", 0) >= 2:
                by_text[rec["text_hash"]].add((a, rec["tu"], addr))
    return {h: sorted(v) for h, v in by_text.items() if len({(a, tu) for a, tu, _ in v}) > 1}


def text_classes(forms, classes, exceptions):
    """Phase 35 T5b — the classes the TEXT tier shares: the same normalized definition text, still a private `def`, at the SAME
    address in >=2 distinct TUs, outside the E/F-deferred byte classes and the ledgered ones. Each: dict(text_hash, addr, sites=[(alias,
    tu, rec)], nins). The byte tier cannot register these (their bytes differ per binary through the TU's declarations)."""
    exc_sites = {(al, int(s, 16)) for c in classes if c["excepted"] for s in c["addrs"] for al in c["aliases"]}
    def_sites = {(al, int(s, 16)) for c in classes if ("E" in c["flags"] or "F" in c["flags"]) for s in c["addrs"] for al in c["aliases"]}
    nins_of = {(i["alias"], i["addr"]): i["nins"] for c in classes for i in c.get("insts", [])}
    by_key = collections.defaultdict(list)
    for a, per in forms.items():
        for addr, rec in per.items():
            if rec["form"] == "def" and rec.get("text_hash") and rec.get("nlines", 0) >= 2 and (a, addr) not in exc_sites | def_sites:
                by_key[(rec["text_hash"], addr)].append((a, rec["tu"], rec))
    out = []
    for (th, addr), sites in by_key.items():
        if len({tu for _, tu, _ in sites}) < 2:
            continue
        nins = max((nins_of.get((a, addr), 0) for a, _, _ in sites), default=0)
        out.append(dict(text_hash=th, addr=addr, sites=sorted(sites, key=lambda s: (s[0], s[1])), nins=nins))
    out.sort(key=lambda c: (-len(c["sites"]), -c["nins"], c["text_hash"]))
    return out


def text_duplicates_same_addr(forms, excepted_sites=frozenset()):
    """S1's SECOND, sig-blind oracle (R34; --strict-text): the same normalized definition text, at the SAME address, still a private
    `def` in >1 TU — exactly what the h_exact join must have shared and did not. Ledgered sites (the exception ledger's classes) are
    excluded, as they are from the first oracle. Keyed by (text, addr) so the deferred cross-address duplicates never count."""
    by_key = collections.defaultdict(set)
    for a, per in forms.items():
        for addr, rec in per.items():
            if rec["form"] == "def" and rec.get("text_hash") and rec.get("nlines", 0) >= 2 and (a, addr) not in excepted_sites:
                by_key[(rec["text_hash"], addr)].add((a, rec["tu"]))
    # distinct TUs, not distinct aliases: a twin's instance resolves to its primary's TU (one source already)
    return {k: sorted(v) for k, v in by_key.items() if len({tu for _, tu in v}) > 1}


# ----------------------------------------------------------------------------------------------------------------------
# self-test fixture (R39): every verdict and flag, in memory
# ----------------------------------------------------------------------------------------------------------------------
def selftest():
    A, B, C = "fx_A", "fx_B", "fx_C"
    spaces = {A: 0x80128158, B: 0x80128158, C: 0x800CAE08}
    dirs = {A: "src/fx_A", B: "src/fx_B", C: "src/fx_C"}
    twins = {}
    sigs = {A: [], B: [], C: []}
    forms = {A: {}, B: {}, C: {}}
    groups = []

    def put(alias, addr, h, form, text="t", nins=12, **kw):
        sigs[alias].append((addr, nins, h, f"func_{addr:08X}"))
        forms[alias][addr] = dict(form=form, name=f"func_{addr:08X}", tu=f"{dirs[alias]}/x.c", line=1, text_hash=text, **kw)

    # 1 A: registered, both macro sites
    put(A, 0x80130000, "h1", "macro"); put(B, 0x80130000, "h1", "macro")
    groups.append(dict(id="g1", hash="h1", vram=0x80130000, binaries=[A, B]))
    # 2 B: registered but B's instance is missing from the group
    put(A, 0x80130010, "h2", "macro"); put(B, 0x80130010, "h2", "def")
    groups.append(dict(id="g2", hash="h2", vram=0x80130010, binaries=[A]))
    # 3 C: unregistered, identical text
    put(A, 0x80130020, "h3", "def", text="same"); put(B, 0x80130020, "h3", "def", text="same")
    # 4 D: unregistered, differing text
    put(A, 0x80130030, "h4", "def", text="x"); put(B, 0x80130030, "h4", "def", text="y", pins=True)
    # 5 C+E: cross-vram identical
    put(A, 0x80130040, "h5", "def", text="same"); put(B, 0x80130050, "h5", "def", text="same")
    # 6 C+F: cross-space
    put(A, 0x80130060, "h6", "def", text="same"); put(C, 0x800CB000, "h6", "def", text="same")
    # 7 M: unregistered mixed (a macro site in one binary, a private copy in the other)
    put(A, 0x80130070, "h7", "macro"); put(B, 0x80130070, "h7", "def", typedef=True)
    # a singleton (must not be a class) and an unaccounted instance (must be reported)
    put(A, 0x80130080, "h8", "def")
    sigs[B].append((0x80130090, 4, "h9", "func_80130090"))
    classes, cov = classify(sigs, forms, groups, spaces, dirs, twins, {}, set(), {}, scope="same-vram")
    got = {c["h"]: (c["verdict"], tuple(c["flags"])) for c in classes}
    exp = {"h1": ("A", ()), "h2": ("B", ()), "h3": ("C", ()), "h4": ("D", ("PINS",)), "h5": ("C", ("E",)), "h6": ("C", ("E", "F")),
           "h7": ("M", ("TYPEDEF",))}
    ok = 0
    for h, e in exp.items():
        g = got.get(h)
        if g == e:
            ok += 1
        else:
            print(f"selftest: {h}: got {g} expected {e}")
    if "h8" in got:
        print("selftest: a singleton became a class"); ok -= 1
    if cov["unaccounted"] != [f"{B}:0x80130090:func_80130090:nins=4"]:
        print(f"selftest: unaccounted reporting wrong: {cov['unaccounted']}"); ok -= 1
    viol = sorted(c["h"] for c in classes if c["violation"])
    if viol != ["h2", "h3", "h4", "h7"]:
        print(f"selftest: violations wrong: {viol} (E/F deferred by default)"); ok -= 1
    classes_all, _ = classify(sigs, forms, groups, spaces, dirs, twins, {}, set(), {"h3": dict(reason="TEST")}, scope="all")
    viol_all = sorted(c["h"] for c in classes_all if c["violation"])
    if viol_all != ["h2", "h4", "h5", "h6", "h7"]:
        print(f"selftest: --scope all / exceptions wrong: {viol_all}"); ok -= 1
    # the masker + scanner on a synthetic TU
    tu = ('#include "common.h"\n#include "../shared/engine_core.h"\n\nDEFINE_func_80128158()  /* dedup: shared */\n'
          '/* void func_DEAD0001(void) { } */\n#if 0\nvoid func_DEAD0002(void) { }\n#endif\n'
          'extern s32 D_1;\ns32 func_80128218(void) {\n    return D_1; /* } */\n}\n'
          'int aF80128300(int a) __asm__("func_80128300");\nint aF80128300(int a) {\n    register int r __asm__("$16");\n    return a;\n}\n'
          'INCLUDE_ASM("asm/x", func_80128400);\nSETTER(func_8012AD64, 0x34, s16)\n'
          '#define SHARED_FN func_80037334\n#include "../shared/main/func_80037004__a0744d60.h"\n#undef SHARED_FN\n'
          'void\nfunc_80128500(void)\n{\n}\n')
    sd = {"src/shared/main/func_80037004__a0744d60.h": ["SHARED_FN"], "src/shared/engine_core.h": []}
    recs = scan_text(tu, "src/fx_A/x.c", shared_defs=sd)
    want = {("macro", "func_80128158"), ("def", "func_80128218"), ("def", "func_80128300"), ("stub", "func_80128400"),
            ("macro-param", "func_8012AD64"), ("param-include", "func_80037334"), ("def", "func_80128500")}
    gotset = {(r["form"], r["name"]) for r in recs}
    if gotset != want:
        print(f"selftest: scanner: got {sorted(gotset)}\n          want {sorted(want)}"); ok -= 1
    else:
        pins = [r for r in recs if r["form"] == "def" and r["name"] == "func_80128300"][0]
        if not (pins["pins"] and pins["alias"]):
            print("selftest: the alias-form def lost its PINS/ALIAS flags"); ok -= 1
    total = len(exp)
    print(f"selftest: {ok}/{total} verdicts correct" + ("" if ok == total else " — FAIL"))
    return ok == total


# ----------------------------------------------------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--check", action="store_true", help="the S1 invariant; exit 1 on any violation")
    ap.add_argument("--strict-macros", action="store_true", help="with --check: any DEFINE_func_ token under src/ is a violation")
    ap.add_argument("--strict-text", action="store_true", help="with --check: any definition text duplicated across TUs is a violation")
    ap.add_argument("--scope", choices=["same-vram", "all"], default="same-vram")
    ap.add_argument("--exceptions", default="config/dedup_exceptions.tsv")
    ap.add_argument("--out-dir", default=OUT_DIR_DEFAULT)
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
    ap.add_argument("--no-cache", action="store_true")
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--quiet", action="store_true")
    a = ap.parse_args()
    if a.selftest:
        sys.exit(0 if selftest() else 1)
    t0 = time.time()
    aliases, dirs = fleet_and_dirs()
    spaces = vram_bases()
    missing_space = [x for x in aliases if x not in spaces]
    if missing_space:
        sys.exit(f"share_census: no _VRAM_BASE for {missing_space[:5]} (R32)")
    twins = twin_sets(aliases)
    twin_of = twin_of_map()
    sigs = {x: sig_rows(x) for x in aliases}
    forms, notes = build_forms(aliases, dirs, a.jobs, use_cache=not a.no_cache, out_dir=a.out_dir)
    groups = load_groups()
    exceptions = load_exceptions(a.exceptions)
    verb = verbatim_instances()
    classes, cov = classify(sigs, forms, groups, spaces, dirs, twins, twin_of, verb, exceptions, scope=a.scope, keep_instances=True)
    summary = summarize(classes, cov, notes, aliases)
    ctrl = controls(classes, sigs, forms)
    macro_tokens = 0
    for x in aliases:
        for per in [forms[x]]:
            macro_tokens += sum(1 for r in per.values() if r["form"] == "macro")
    dup_text = text_duplicates(forms)
    summary["macro_sites"] = macro_tokens
    summary["duplicate_text_classes"] = len(dup_text)
    summary["duplicate_text_sites"] = sum(len(v) for v in dup_text.values())
    summary["twin_sets"] = sorted({v for v in twins.values()})
    summary["elapsed_s"] = round(time.time() - t0, 1)
    summary["controls"] = [dict(name=n, got=g, expected=e) for n, g, e in ctrl]
    out = REPO / a.out_dir
    out.mkdir(parents=True, exist_ok=True)
    (out / "share_census.json").write_text(json.dumps(summary, indent=1, sort_keys=True) + "\n")
    with open(out / "classes.jsonl", "w") as f:
        for c in classes:
            f.write(json.dumps(c) + "\n")
    (out / "coverage_notes.txt").write_text("\n".join(
        ["# unaccounted sig instances (alias:addr:name:nins)"] + cov["unaccounted"] +
        ["# instances with >=2 non-stub forms"] + notes["multi_form"] +
        ["# unresolved (non-func_, not in the binary's symbol stack) definition/site names"] + notes["unresolved_names"]) + "\n")
    table = render_table(classes, summary, cov, ctrl)
    table += f"\n  macro sites {macro_tokens:,} · duplicate-text classes {len(dup_text):,} ({summary['duplicate_text_sites']:,} sites) · elapsed {summary['elapsed_s']} s"
    (out / "share_census.txt").write_text(table + "\n")
    if not a.quiet:
        print(table)
    rc = 0
    if cov["unaccounted"]:
        print(f"share_census: COVERAGE DEFECT — {len(cov['unaccounted'])} sig instance(s) have no source form (R32); see {a.out_dir}/coverage_notes.txt")
        rc = 1
    if notes["multi_form"]:
        print(f"share_census: COVERAGE DEFECT — {len(notes['multi_form'])} instance(s) carry two non-stub forms; see coverage_notes.txt")
        rc = 1
    if a.check:
        v = [c for c in classes if c["violation"]]
        bad = len(v)
        if a.strict_macros and macro_tokens:
            print(f"share_census: S1 — {macro_tokens} DEFINE_func_ site(s) remain under src/ (--strict-macros)"); bad += 1
        if a.strict_text:
            # the second oracle mirrors the first's scope: ledgered classes AND the gate-1 deferral (E/F cross-address classes — an
            # empty body's hash spans every address, so its same-address pairs sit inside a deferred class) are excluded; the deferred
            # same-address duplicates are PUBLISHED as the names phase's inheritance, never silently dropped (R41)
            exc_sites = {(i_alias, int(addr_s, 16)) for c in classes if c["excepted"] for addr_s in c["addrs"] for i_alias in c["aliases"]}
            def_sites = {(i_alias, int(addr_s, 16)) for c in classes if ("E" in c["flags"] or "F" in c["flags"]) for addr_s in c["addrs"] for i_alias in c["aliases"]}
            dup_deferred = text_duplicates_same_addr(forms, exc_sites)
            dup_rest = text_duplicates_same_addr(forms, exc_sites | def_sites)
            n_def = len(dup_deferred) - len(dup_rest)
            summary["same_address_text_duplicates_deferred"] = {"texts": n_def, "sites": sum(len(v) for v in dup_deferred.values()) - sum(len(v) for v in dup_rest.values())}
            print(f"share_census: second oracle — {n_def:,} same-address duplicated texts sit inside the deferred cross-address classes "
                  f"({summary['same_address_text_duplicates_deferred']['sites']:,} sites; the names phase's inheritance)")
            # what is left is either a class the byte join has (a VIOLATION the first oracle missed — must be 0) or the same text at
            # the same address compiling to DIFFERENT bytes per binary (singleton h_exact classes: data addresses differ per overlay);
            # the latter is one source the byte tier cannot register — published as PENDING (a decision, not a pass)
            # a violation only when two DISTINCT TUs hold private copies of the SAME byte class at that address (a twin pair is one
            # TU); every other same-address text duplicate is byte-variant across its TUs — the byte tier cannot register it
            site_h = {(i["alias"], i["addr"]): c["h"] for c in classes for i in c["insts"]}
            def _shared_class_across_tus(k, v):
                by_h = {}
                for a, tu in v:
                    h = site_h.get((a, k[1]))
                    if h:
                        by_h.setdefault(h, set()).add(tu)
                return any(len(tus) > 1 for tus in by_h.values())
            dup_same = {k: v for k, v in dup_rest.items() if _shared_class_across_tus(k, v)}
            dup_pending = {k: v for k, v in dup_rest.items() if k not in dup_same}
            summary["same_address_text_duplicates_pending"] = {"texts": len(dup_pending), "sites": sum(len(v) for v in dup_pending.values())}
            (out / "share_census.json").write_text(json.dumps(summary, indent=1, sort_keys=True) + "\n")   # the json carries the oracle's counts (progress.py reads them)
            if dup_pending:
                print(f"share_census: S1 text half — {len(dup_pending):,} same-address definition texts ({summary['same_address_text_duplicates_pending']['sites']:,} "
                      f"sites) are duplicated across TUs with DIFFERENT bytes per binary: the h_text tier shares them (share_body.py --apply --bucket text)"
                      f" — VIOLATION until shared or ledgered"); bad += 1
            if dup_same:
                print(f"share_census: S1 second oracle — {len(dup_same)} definition text(s) duplicated at the SAME address across TUs and not "
                      f"ledgered (--strict-text): " + "; ".join(f"0x{addr:08X} in {[a for a, _ in v][:4]}" for (_, addr), v in list(dup_same.items())[:6])); bad += 1
            else:
                print(f"share_census: S1 second oracle — 0 same-address definition texts duplicated across TUs (any-address duplicates "
                      f"{len(dup_text):,}, the names phase's)")
        exc = sum(1 for c in classes if c["excepted"])
        twinc = sum(1 for c in classes if "TWIN-COVERED" in c["flags"] and c["verdict"] != "A")
        print(f"S1: one source per unique function — {len(classes):,} classes, {len(classes) - len(v):,} satisfied "
              f"({twinc:,} twin-covered, {exc:,} excepted, {summary['cross_address_deferred']['classes']:,} deferred cross-address), "
              f"{len(v):,} VIOLATION(S)" + (" — OK" if bad == 0 else " — FAIL"))
        for c in v[:15]:
            print(f"  {c['verdict']} {','.join(c['flags']) or '-'} h={c['h'][:10]} {c['instances']} inst x {c['nins']} ins {c['addrs'][:2]} {c['aliases'][:3]}")
        if bad:
            rc = 1
    sys.exit(rc)


if __name__ == "__main__":
    main()
