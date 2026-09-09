#!/usr/bin/env python3
"""gte_consolidate.py — the GTE coprocessor asm consolidated under Sony's names, and the dead lever-macro sweep (Phase 36 T5).

    tools/gte_consolidate.py --inventory                    # every asm-bearing macro definition + every direct GTE statement, SIGNED by the
                                                            # build's own maspsx→as tail; the canonical table → .run/P36/gte/{inventory,canonical}.json
    tools/gte_consolidate.py --header                       # write include/gte_inline.h (one canonical macro per signature) + the include in common.h
    tools/gte_consolidate.py --apply --batch N --label L [--only …] [-j 12]
                                                            # per file: canonical-duplicate definitions deleted, private/variant names renamed, direct
                                                            # statements rewritten into canonical calls; every file judged through every recipe
    tools/gte_consolidate.py --sweep --label L [--only …]    # dead asm-bearing macros deleted; a compound macro's inner asm dropped when byte-neutral
    tools/gte_consolidate.py --status | --selftest

A SIGNATURE is what the assembler makes of a template, not how it is spelled: the template with its operands bound to fixed registers
(%0.. → $4 $5 $6 $7 for inputs, $2 $3 for outputs) is assembled through the SAME tail as the build (maspsx --aspsx-version=2.56 →
mipsel-linux-gnu-as with include/macro.inc + include/gte_macros.inc, where `rtps`, `mvmva`, `sqr 0` are GAS macros), and the signature
is (bytes, #outputs, #inputs). `nop;nop;rtps`, `nop;nop;.word 0x4a180001` and `nop;nop;cop2 0x0180001` are one signature. Sony's
converted inline_c.h is the source of NAMES and of operand/clobber lists only — its `.word` opcode spellings assemble to nothing
useful (`gte_rtps` there is `.word 0x0000007f`).

THE CANONICAL TABLE: definitions grouped by signature; the canonical CLOBBER set of a signature is Sony's for that name (a store macro
legitimately clobbers "memory"), else the majority's; the canonical NAME is the most-used `gte_*` name in the group (Sony's convention),
else a name derived from gte_macros.inc, else `gte_seq_<hash>`; the canonical TEXT is the majority definition text (byte-proven in the
fleet — the header ships nothing that was not already in the tree). A definition with the canonical signature but EXTRA clobbers (the
`"memory"` a drafter added to a load or a compute op to force the schedule) is a LEVER VARIANT: it stays per TU, renamed `<name>_m`, and
its uses carry `// !FAKE:` markers for T7. A direct statement is rewritten into `NAME(args)` (or `NAME1(args); NAME2();` for the
concatenation of two canonical macros) when bytes and clobbers agree; with extra clobbers it is a lever variant too (marked); a sequence
that matches nothing is counted and left. Every file's final text is judged through every recipe of the file (tools/delever_oracle.py);
the clean fleet run gates every batch (tools/delever_cycle.sh MODE=gte).
"""
import argparse
import collections
import hashlib
import json
import os
import pathlib
import re
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
import delever as dl                # noqa: E402
import delever_oracle as oracle     # noqa: E402
import lever_census as lc           # noqa: E402
import share_census as sc           # noqa: E402

RUN = REPO / ".run" / "P36" / "gte"
SIG_CACHE = RUN / "sig_cache.json"
INVENTORY = RUN / "inventory.json"
CANON = RUN / "canonical.json"
LEDGER = REPO / ".run" / "P36" / "delever" / "ledger.jsonl"
HEADER = "include/gte_inline.h"
COMMON = "include/common.h"
SONY = REPO / "tools/psyq/conv47/psyq-4_7-converted/include/inline_c.h"
MASPSX = ".venv/bin/python tools/maspsx/maspsx.py --aspsx-version=2.56 --expand-div"
AS = "mipsel-linux-gnu-as -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0"
FAKE = dl.FAKE
DEFINE_LINE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)(\([^)]*\))?[ \t]*(.*)$")
_LOCK = dl._LOCK


class Refuse(Exception):
    pass


# ----------------------------------------------------------------------------------------------------------------------
# the signature engine
# ----------------------------------------------------------------------------------------------------------------------
def parse_asm(inner):
    """(template, outs, ins, clobbers) — delever's operand parser plus the clobber section."""
    tmpl, outs, ins = dl.parse_asm_operands(inner)
    s = inner.strip()
    i, n = 0, len(s)
    while i < n:
        if s[i] in " \t\r\n":
            i += 1
            continue
        mm = lc.STRLIT.match(s, i)
        if not mm:
            break
        i = mm.end()
    rest = s[i:].strip()
    secs = lc._split_sections(rest[1:]) if rest.startswith(":") else []
    clob = [m.group(1) for m in re.finditer(r'"([^"]*)"', secs[2])] if len(secs) > 2 else []
    return tmpl, outs, ins, sorted(set(clob))


def bind_regs(tmpl, nout, nin):
    regs = ["$2", "$3"][:nout] + ["$4", "$5", "$6", "$7"][:nin]
    def sub(m):
        k = int(m.group(1))
        return regs[k] if k < len(regs) else m.group(0)
    t = re.sub(r"%(\d+)", sub, tmpl)
    t = re.sub(r"\\n|\\t", "\n", t)
    return t


_sig_cache = None


def _load_cache():
    global _sig_cache
    if _sig_cache is None:
        _sig_cache = json.loads(SIG_CACHE.read_text()) if SIG_CACHE.exists() else {}
    return _sig_cache


def _save_cache():
    RUN.mkdir(parents=True, exist_ok=True)
    tmp = SIG_CACHE.with_suffix(".tmp")
    tmp.write_text(json.dumps(_sig_cache, indent=0))
    os.replace(tmp, SIG_CACHE)


def asm_bytes(bound_template):
    """hex of the .text bytes the build's tail makes of the template (cached by text); 'ERROR: …' when it does not assemble."""
    cache = _load_cache()
    key = bound_template
    if key in cache:
        return cache[key]
    d = RUN / "probe"
    d.mkdir(parents=True, exist_ok=True)
    tag = hashlib.sha1(key.encode()).hexdigest()[:10]
    s_path, o_path, b_path = d / f"{tag}.s", d / f"{tag}.o", d / f"{tag}.bin"
    s_path.write_text("\t.include \"include/macro.inc\"\n\t.include \"gte_macros.inc\"\n\t.set\tnoreorder\n\t.set\tnoat\n\t.text\n\t.align\t2\n"
                      "\t.globl\tprobe\n\t.ent\tprobe\nprobe:\n" + bound_template + "\n\t.end\tprobe\n")
    cmd = f"set -o pipefail; cat {s_path} | {MASPSX} | {AS} -o {o_path} && mipsel-linux-gnu-objcopy -O binary -j .text {o_path} {b_path}"
    r = subprocess.run(["bash", "-c", cmd], cwd=REPO, capture_output=True, text=True)
    if r.returncode != 0 or not b_path.exists():
        res = "ERROR: " + (r.stderr.strip().splitlines() or ["?"])[-1][:120]
    else:
        res = b_path.read_bytes().hex()
    for p in (s_path, o_path, b_path):
        try:
            p.unlink()
        except OSError:
            pass
    cache[key] = res
    return res


def signature(inner):
    """dict(bytes, nout, nin, clob, tmpl, ok) for the text between an asm statement's parens."""
    tmpl, outs, ins, clob = parse_asm(inner)
    bound = bind_regs(tmpl, len(outs), len(ins))
    b = asm_bytes(bound)
    return dict(bytes=b, nout=len(outs), nin=len(ins), clob=clob, tmpl=tmpl, ok=not b.startswith("ERROR"),
                ins=[e for _, e in ins], outs=[e for _, e in outs])


def set_clobbers(body, clob):
    """the macro body with the asm statement's clobber section replaced by `clob` (removed when empty)."""
    m_asm = lc.ASM_KW.search(body)
    o = body.find("(", m_asm.end())
    c = lc._paren_span(body, o)
    inner = body[o + 1:c]
    # the sections: template, then up to three ':'-separated parts outside string literals
    s = inner
    i, n = 0, len(s)
    while i < n:
        if s[i] in " \t\r\n":
            i += 1
            continue
        mm = lc.STRLIT.match(s, i)
        if not mm:
            break
        i = mm.end()
    head, rest = s[:i], s[i:]
    secs = lc._split_sections(rest.strip()[1:]) if rest.strip().startswith(":") else []
    while len(secs) < 3:
        secs.append("")
    secs[2] = ", ".join(f'"{x}"' for x in clob) if clob else ""
    while secs and secs[-1].strip() == "":
        secs.pop()
    new_inner = head.rstrip() + ("".join(" : " + x.strip() for x in secs) if secs else "") + " "
    return body[:o + 1] + new_inner + body[c:]


def sig_key(s):
    return f"{s['bytes']}|{s['nout']}|{s['nin']}"


# ----------------------------------------------------------------------------------------------------------------------
# the inventory
# ----------------------------------------------------------------------------------------------------------------------
def asm_inner(body_masked):
    """the text between the parens of the FIRST asm statement in a macro body (None if none / more than one)."""
    ms = list(lc.ASM_KW.finditer(body_masked))
    if len(ms) != 1:
        return None
    o = body_masked.find("(", ms[0].end())
    c = lc._paren_span(body_masked, o) if o >= 0 else -1
    return body_masked[o + 1:c] if (o >= 0 and c > 0) else None


def define_params(raw, l0):
    m = DEFINE_LINE.match(raw.split("\n")[l0 - 1])
    return (m.group(2) or "") if m else ""


def sony_table():
    """name -> (nout, nin, clobbers) from Sony's inline_c.h — the parts of it that are plain C text."""
    out = {}
    if not SONY.exists():
        return out
    raw = SONY.read_text(errors="surrogateescape")
    for (l0, l1, name, body) in lc.define_blocks(raw):
        inner = asm_inner(sc.mask_text(body) if "/*" in body else body)
        if inner is None:
            continue
        try:
            _, outs, ins, clob = parse_asm(inner)
        except Exception:   # noqa: BLE001
            continue
        out[name] = (len(outs), len(ins), clob)
    return out


def inc_names():
    """bytes -> name for gte_macros.inc's single-op macros (assembled as `nop;nop;<macro>`), for signatures without a gte_* name."""
    raw = (REPO / "include/gte_macros.inc").read_text(errors="surrogateescape")
    out = {}
    for m in re.finditer(r"^\.macro\s+(\w+)\s*$", raw, re.M):
        b = asm_bytes(f"nop\nnop\n{m.group(1)}")
        if not b.startswith("ERROR"):
            out[f"{b}|0|0"] = m.group(1)
    return out


def files_under_src():
    return [p for p in sorted((REPO / "src").rglob("*")) if p.suffix in (".c", ".h") and not p.name.startswith(".")]


def inventory_files():
    """the tree's definitions AND the header's own (the canonical table must stay stable once definitions have moved into the header:
    without it a signature whose per-TU definitions were all deleted dropped out of the table and its direct statements silently
    stopped being classified — 357 levers vanished from the census after batch gte2)."""
    files = files_under_src()
    if (REPO / HEADER).exists():
        files.append(REPO / HEADER)
    return files


def inventory(jobs=12, quiet=False):
    """definitions: [{tu, l0, l1, name, params, body, kind, sig}], direct: [{tu, line, col, inner, sig}], uses: Counter(name)."""
    sites = dl.load_sites()
    uses = collections.Counter(s["via"] for s in sites if s.get("via") and s["kind"] == "gte")
    direct_sites = [s for s in sites if s["kind"] == "gte" and not s.get("via")]
    defs, direct = [], []
    for p in inventory_files():
        raw = p.read_text(errors="surrogateescape")
        if "#define" not in raw and "asm" not in raw:
            continue
        rel = p.relative_to(REPO).as_posix()
        for (l0, l1, name, body) in lc.define_blocks(raw):
            kind = lc.macro_kind(body)
            if not kind:
                continue
            d = dict(tu=rel, l0=l0, l1=l1, name=name, params=define_params(raw, l0), body=body, kind=kind, sig=None)
            if kind == "gte":
                inner = asm_inner(sc.mask_text(body) if ("/*" in body or "//" in body) else body)
                if inner is not None:
                    try:
                        d["sig"] = signature(inner)
                    except Exception as ex:   # noqa: BLE001
                        d["sig"] = dict(bytes=f"ERROR: {ex}"[:100], ok=False, nout=0, nin=0, clob=[], tmpl="", ins=[], outs=[])
            defs.append(d)
    by_tu = collections.defaultdict(list)
    for s in direct_sites:
        by_tu[s["tu"]].append(s)
    for tu, ss in by_tu.items():
        raw = (REPO / tu).read_text(errors="surrogateescape")
        m = dl.same_len_mask(raw)
        ls = dl.line_starts(raw)
        for s in ss:
            pos = ls[s["line"] - 1] + s["col"] - 1
            o = m.find("(", pos)
            c = lc._paren_span(m, o) if o >= 0 else -1
            if o < 0 or c < 0:
                continue
            inner = m[o + 1:c]
            try:
                sg = signature(inner)
            except Exception as ex:   # noqa: BLE001
                sg = dict(bytes=f"ERROR: {ex}"[:100], ok=False, nout=0, nin=0, clob=[], tmpl="", ins=[], outs=[])
            direct.append(dict(tu=tu, line=s["line"], col=s["col"], fn=s.get("fn"), inner=inner, sig=sg, marked=s.get("marked", False)))
    _save_cache()
    inv = dict(generated=time.strftime("%Y-%m-%d %H:%M"), definitions=defs, direct=direct, uses=dict(uses))
    RUN.mkdir(parents=True, exist_ok=True)
    INVENTORY.write_text(json.dumps(inv))
    if not quiet:
        gte = [d for d in defs if d["kind"] == "gte"]
        print(f"gte_consolidate --inventory: {len(defs)} asm-bearing macro definitions ({len(gte)} GTE, {sum(1 for d in gte if d['sig'] and d['sig']['ok'])} signed), "
              f"{len(direct)} direct GTE statements ({sum(1 for d in direct if d['sig']['ok'])} signed), {sum(uses.values())} macro-carried GTE uses")
    return inv


# ----------------------------------------------------------------------------------------------------------------------
# the canonical table
# ----------------------------------------------------------------------------------------------------------------------
def canonical_table(inv, quiet=False, write=True):
    """write=False for fixtures: the selftest once overwrote the real table with its two-signature fixture (the census then classified
    every direct statement against a fixture and 362 levers vanished twice) — a selftest never writes an instrument's real state."""
    sony = sony_table()
    incn = inc_names()
    groups = collections.defaultdict(list)
    for d in inv["definitions"]:
        if d["kind"] == "gte" and d["sig"] and d["sig"]["ok"]:
            groups[sig_key(d["sig"])].append(d)
    table, variants, unsigned = {}, {}, [d for d in inv["definitions"] if d["kind"] == "gte" and not (d["sig"] and d["sig"]["ok"])]
    names_taken = set()
    for key, ds in sorted(groups.items(), key=lambda kv: -len(kv[1])):
        names = collections.Counter(d["name"] for d in ds)
        # candidates: the names with their address / variant suffixes stripped (`gte_stsxy01_80181E04` is Sony's gte_stsxy01;
        # `LDV0_DA34` is a private copy of gte_ldv0), Sony's spelling preferred, then the most-used gte_* spelling
        stripped = collections.Counter()
        for n, cnt in names.items():
            base = re.sub(r"(_[0-9A-Fa-f]{3,8}|X|_m|_A|_B)$", "", n)
            base = re.sub(r"_v[0-9a-f]{4}$", "", base)
            stripped[base] += cnt
        nout0, nin0 = ds[0]["sig"]["nout"], ds[0]["sig"]["nin"]
        from_header = [d for d in ds if d["tu"] == HEADER]
        if from_header:
            h = from_header[0]
            names_taken.add(h["name"])
            canon_clob = tuple(h["sig"]["clob"])
            canon_defs = [d for d in ds if tuple(d["sig"]["clob"]) == canon_clob]
            table[key] = dict(name=h["name"], params=h["params"], body=re.sub(r"[ \t]+\n", "\n", h["body"]).strip(), clob=list(canon_clob),
                              defs=len(canon_defs) - 1, files=len({d["tu"] for d in canon_defs}) - 1, synthesized=False,
                              names=dict(collections.Counter(d["name"] for d in ds)), sony=(h["name"] in sony), nin=nin0, nout=nout0, tmpl=h["sig"]["tmpl"])
            clob_sets = collections.Counter(tuple(d["sig"]["clob"]) for d in ds if d["tu"] != HEADER)
            for cs, cnt in clob_sets.items():
                if cs != canon_clob:
                    extra = sorted(set(cs) - set(canon_clob))
                    fewer = sorted(set(canon_clob) - set(cs))
                    vname = f"{h['name']}_m" if extra == ["memory"] and not fewer else f"{h['name']}_v{hashlib.sha1('|'.join(cs).encode()).hexdigest()[:4]}"
                    variants[f"{key}|{'|'.join(cs)}"] = dict(name=vname, of=h["name"], key=key, clob=list(cs), extra=extra, fewer=fewer, defs=cnt,
                                                           files=len({d["tu"] for d in ds if tuple(d["sig"]["clob"]) == cs and d["tu"] != HEADER}))
            continue
        # a Sony name is taken only when the operand counts agree with Sony's macro (a private compound that borrowed the name is not it)
        sony_named = [n for n, _ in stripped.most_common() if n in sony and (sony[n][0], sony[n][1]) == (nout0, nin0)]
        gte_names = [n for n, _ in stripped.most_common() if n.startswith("gte_")]
        name = (sony_named or gte_names or [None])[0]
        if name is None:
            base = incn.get(key)
            priv = stripped.most_common(1)[0][0]
            name = f"gte_{base}" if base else f"gte_{re.sub(r'[^A-Za-z0-9]', '', priv).lower()}"
        if name in sony and not sony_named:
            name = f"{name}_alt"
        base_name, k = name, 2
        while name in names_taken:
            name = f"{base_name}{k}" if base_name.endswith("_alt") else f"{base_name}_alt{k}"
            k += 1
        names_taken.add(name)
        clob_sets = collections.Counter(tuple(d["sig"]["clob"]) for d in ds)
        if name in sony:
            canon_clob = tuple(sony[name][2])
        else:
            canon_clob = clob_sets.most_common(1)[0][0]
        canon_defs = [d for d in ds if tuple(d["sig"]["clob"]) == canon_clob]
        synthesized = False
        if canon_defs:
            texts = collections.Counter((d["params"], re.sub(r"[ \t]+\n", "\n", d["body"]).strip()) for d in canon_defs)
            (params, body), _ = texts.most_common(1)[0]
        else:
            # nobody spells it with Sony's clobbers (every definition carries the steer): the canonical text is the majority body
            # with its clobber list set to Sony's — the steer must not become canonical by being universal
            texts = collections.Counter((d["params"], re.sub(r"[ \t]+\n", "\n", d["body"]).strip()) for d in ds)
            (params, body), _ = texts.most_common(1)[0]
            body = set_clobbers(body, list(canon_clob))
            synthesized = True
        table[key] = dict(name=name, params=params, body=body, clob=list(canon_clob), defs=len(canon_defs), files=len({d["tu"] for d in canon_defs}),
                          synthesized=synthesized,
                          names=dict(names), sony=(name in sony), nin=ds[0]["sig"]["nin"], nout=ds[0]["sig"]["nout"], tmpl=ds[0]["sig"]["tmpl"])
        for cs, cnt in clob_sets.items():
            if cs != canon_clob:
                extra = sorted(set(cs) - set(canon_clob))
                fewer = sorted(set(canon_clob) - set(cs))
                vname = f"{name}_m" if extra == ["memory"] and not fewer else f"{name}_v{hashlib.sha1('|'.join(cs).encode()).hexdigest()[:4]}"
                variants[f"{key}|{'|'.join(cs)}"] = dict(name=vname, of=name, key=key, clob=list(cs), extra=extra, fewer=fewer, defs=cnt,
                                                       files=len({d["tu"] for d in ds if tuple(d["sig"]["clob"]) == cs}))
    out = dict(generated=time.strftime("%Y-%m-%d %H:%M"), canonical=table, variants=variants, unsigned=[dict(tu=d["tu"], name=d["name"], l0=d["l0"]) for d in unsigned])
    if write:
        CANON.write_text(json.dumps(out, indent=1))
    if not quiet:
        print(f"gte_consolidate: canonical table — {len(table)} signatures ({sum(1 for t in table.values() if t['sony'])} with Sony's name), "
              f"{sum(t['defs'] for t in table.values())} canonical definitions; {len(variants)} lever variants holding {sum(v['defs'] for v in variants.values())} definitions; "
              f"{len(unsigned)} unsigned definitions")
        for v in sorted(variants.values(), key=lambda v: -v["defs"])[:12]:
            print(f"   variant {v['name']:24s} of {v['of']:18s} defs {v['defs']:4d} files {v['files']:4d} extra {v['extra']} fewer {v['fewer']}")
        for u in unsigned[:8]:
            print(f"   unsigned {u['tu']}:{u['l0']} {u['name']}")
    return out


def render_header(canon):
    L = ["/* include/gte_inline.h — the GTE coprocessor macros under Sony's names, ONE definition per signature (Phase 36 T5).",
         " *",
         " * Every macro here is the majority spelling the tree already carried in its per-TU definitions (byte-proven in the fleet),",
         " * named by PsyQ's inline_c.h convention; the signature of each (the bytes the build's maspsx → as tail makes of the template,",
         " * its operand counts, its clobbers) was computed by tools/gte_consolidate.py, which also deleted the per-TU duplicates.",
         " * A definition that differs from the one here only by an extra clobber (a scheduling steer) lives on in its TU as <name>_m",
         " * and is a marked lever, not a second spelling. Generated: do not edit by hand — regenerate with `tools/gte_consolidate.py --header`.",
         " */", "#ifndef GTE_INLINE_H", "#define GTE_INLINE_H", ""]
    for key, t in sorted(canon["canonical"].items(), key=lambda kv: kv[1]["name"]):
        body_lines = t["body"].split("\n")
        L.append(f"/* {t['tmpl'][:90]}{' …' if len(t['tmpl']) > 90 else ''}  ({t['defs']} definitions in {t['files']} files{'' if t['sony'] else '; not a PsyQ name'}) */")
        if len(body_lines) == 1:
            L.append(f"#define {t['name']}{t['params']} {body_lines[0]}")
        else:
            L.append(f"#define {t['name']}{t['params']} \\")
            for i, bl in enumerate(body_lines):
                L.append(f"    {bl.strip()}" + (" \\" if i < len(body_lines) - 1 else ""))
        L.append("")
    L += ["#endif /* GTE_INLINE_H */", ""]
    return "\n".join(L)


def write_header(canon):
    RUN.mkdir(parents=True, exist_ok=True)
    (REPO / HEADER).write_text(render_header(canon))
    c = REPO / COMMON
    t = c.read_text()
    if '#include "gte_inline.h"' not in t:
        t = t.replace("#endif /* COMMON_H */", '#include "gte_inline.h"   /* Phase 36 T5: the GTE coprocessor macros, one definition each */\n#endif /* COMMON_H */', 1)
        c.write_text(t)
    print(f"gte_consolidate --header: {HEADER} written ({len(canon['canonical'])} macros); {COMMON} includes it")


# ----------------------------------------------------------------------------------------------------------------------
# --apply: per file
# ----------------------------------------------------------------------------------------------------------------------
def header_bound_names(inv):
    """tu -> the set of asm-macro names that the headers the TU includes USE (a shared header's `gte_x(...)` binds to the includer's
    definition — the 20 h_text headers are byte-variant per includer for exactly this reason). A local definition of such a name
    whose canonical name differs is a HOMONYM the includer supplies: it cannot be deleted (the header's use would bind to the global
    header's macro of that name), so it is kept and counted for the names phase."""
    names = {d["name"] for d in inv["definitions"]}
    use_re = re.compile(r"\b(" + "|".join(sorted(map(re.escape, names), key=len, reverse=True)) + r")\s*\(") if names else None
    hdr_uses = {}
    tu_headers = collections.defaultdict(set)
    for h, tus in dl.includers().items():
        if not h.endswith(".h") or not (REPO / h).exists():
            continue
        text = sc.mask_text((REPO / h).read_text(errors="surrogateescape"))
        used = set(m.group(1) for m in use_re.finditer(text)) if use_re else set()
        # a name defined in the header itself is the header's own, not the includer's
        own = {n for (_, _, n, _) in lc.define_blocks((REPO / h).read_text(errors="surrogateescape"))}
        hdr_uses[h] = used - own
        for tu in tus:
            tu_headers[tu].add(h)
    return {tu: set().union(*(hdr_uses[h] for h in hs)) for tu, hs in tu_headers.items()}


def plan_files(inv, canon, only=None, bound=None):
    """tu -> dict(defs=[definitions to delete/rename/keep], direct=[direct statements], renames={})"""
    by_key = canon["canonical"]
    var_by = {v["key"] + "|" + "|".join(v["clob"]): v for v in canon["variants"].values()}
    bound = bound if bound is not None else header_bound_names(inv)
    plan = collections.defaultdict(lambda: dict(defs=[], direct=[], renames={}))
    for d in inv["definitions"]:
        if d["kind"] != "gte" or not (d["sig"] and d["sig"]["ok"]) or d["tu"] == HEADER:
            continue
        key = sig_key(d["sig"])
        t = by_key.get(key)
        if not t:
            continue
        vkey = key + "|" + "|".join(d["sig"]["clob"])
        homonym = d["name"] != t["name"] and d["name"] in bound.get(d["tu"], ())
        if tuple(d["sig"]["clob"]) == tuple(t["clob"]):
            if homonym:
                plan[d["tu"]]["defs"].append(dict(d, action="keep", canonical=t["name"], why="header-bound homonym"))
            else:
                plan[d["tu"]]["defs"].append(dict(d, action="delete", canonical=t["name"]))
        elif vkey in var_by:
            v = var_by[vkey]
            plan[d["tu"]]["defs"].append(dict(d, action="rename", canonical=t["name"], variant=v["name"], extra=v["extra"], fewer=v["fewer"],
                                              header_bound=(d["name"] in bound.get(d["tu"], ()))))
    for s in inv["direct"]:
        plan[s["tu"]]["direct"].append(s)
    files = {tu: p for tu, p in plan.items() if p["defs"] or p["direct"]}
    if only:
        files = {tu: p for tu, p in files.items() if any(o == tu or tu.endswith("/" + o) or ("/" + o + "/") in tu for o in only)}
    return files


def direct_rewrite(s, canon):
    """('call', text, name) | ('lever', variant_name, extra) | ('none', why, None) for a direct GTE statement."""
    sg = s["sig"]
    if not sg["ok"]:
        return "none", "unsigned", None
    key = sig_key(sg)
    t = canon["canonical"].get(key)
    if t and sg["nout"] == 0:
        if tuple(sg["clob"]) == tuple(t["clob"]):
            return "call", f"{t['name']}({', '.join(sg['ins'])});", t["name"]
        extra = sorted(set(sg["clob"]) - set(t["clob"]))
        fewer = sorted(set(t["clob"]) - set(sg["clob"]))
        return "lever", (f"{t['name']}_m" if extra == ["memory"] and not fewer else f"{t['name']}_v"), extra or fewer
    # a concatenation of two canonical macros (a load then an op): bytes = b1 + b2, inputs = the first's, clobbers = the union
    b = sg["bytes"]
    for k1, t1 in canon["canonical"].items():
        b1 = k1.split("|")[0]
        if not b.startswith(b1) or len(b1) == 0 or len(b1) >= len(b):
            continue
        k2 = f"{b[len(b1):]}|0|0"
        t2 = canon["canonical"].get(k2)
        if not t2 or t1["nout"] or t1["nin"] != sg["nin"]:
            continue
        union = sorted(set(t1["clob"]) | set(t2["clob"]))
        if union == list(sg["clob"]):
            return "call", f"{t1['name']}({', '.join(sg['ins'])}); {t2['name']}();", f"{t1['name']}+{t2['name']}"
        extra = sorted(set(sg["clob"]) - set(union))
        return "lever", f"{t1['name']}+{t2['name']}_m" if extra == ["memory"] else f"{t1['name']}+{t2['name']}_v", extra or sorted(set(union) - set(sg["clob"]))
    return "none", "no canonical signature", None


def file_edits(tu, raw, p, canon, label):
    """[(start, end, repl)] + the record (per definition / use / direct statement) for one file's consolidation."""
    m = dl.same_len_mask(raw)
    ls = dl.line_starts(raw)
    edits, rec = [], dict(deleted=0, renamed_defs=0, use_renames=0, direct_calls=0, direct_levers=0, direct_none=0, marked=0, defs=[], direct=[])
    # definitions: delete or rename (the #define line's name token); a renamed variant gets a comment line above
    rec["kept"] = 0
    for d in sorted(p["defs"], key=lambda d: d["l0"]):
        start, end = ls[d["l0"] - 1], ls[d["l1"]] if d["l1"] < len(ls) else len(raw)
        if d["action"] in ("keep", "keep-variant"):
            rec["kept"] += 1
            rec["defs"].append(dict(name=d["name"], l0=d["l0"], action="kept", canonical=d["canonical"], why=d.get("why", "")))
            continue
        if d["action"] == "delete":
            edits.append((start, end, ""))
            rec["deleted"] += 1
            rec["defs"].append(dict(name=d["name"], l0=d["l0"], action="deleted", canonical=d["canonical"]))
        else:
            line = raw[start:ls[d["l0"]] - 1]
            k = line.find(d["name"])
            if k < 0:
                raise Refuse(f"{tu}:{d['l0']}: the #define line does not carry `{d['name']}`")
            note = f"/* GTE VARIANT `{d['variant']}`: {', '.join(d['extra']) or 'fewer clobbers'} beyond Sony's `{d['canonical']}` — a scheduling steer, its uses are marked (P36 T5) */\n"
            edits.append((start, start, note))
            edits.append((start + k, start + k + len(d["name"]), d["variant"]))
            rec["renamed_defs"] += 1
            rec["defs"].append(dict(name=d["name"], l0=d["l0"], action="renamed", variant=d["variant"], canonical=d["canonical"]))
    # uses: SCOPED to the definition that governs them — a name is redefined between functions in the same unit (~2 definitions per
    # name per file), so a use belongs to the last `#define NAME` above it; that definition's target (the canonical name, or the
    # variant name) decides the rename, and a use governed by a definition outside the plan (unsigned, unmatched) is left alone
    def_lines = {ln for d in p["defs"] for ln in range(d["l0"], d["l1"] + 1)}
    all_defs = collections.defaultdict(list)          # name -> [(l0, target | None)] over EVERY definition of the name in the file
    planned = {(d["name"], d["l0"]): d for d in p["defs"]}
    for (l0, l1, name, body) in lc.define_blocks(raw):
        d = planned.get((name, l0))
        target = (d["canonical"] if d["action"] == "delete" else d["variant"] if d["action"] == "rename" else name) if d else None
        all_defs[name].append((l0, target, d))
    for name in all_defs:
        all_defs[name].sort()
    marked_lines = set()
    for name, dlist in all_defs.items():
        if not any(d for _, _, d in dlist):
            continue
        objlike = any(d and d.get("params", "") == "" for _, _, d in dlist)
        use_pat = (r"\b%s\b(?!\s*\()" if objlike else r"\b%s\b(?=\s*\()") % re.escape(name)
        for mm in re.finditer(use_pat, m):
            ln = m.count("\n", 0, mm.start()) + 1
            if ln in def_lines:
                continue
            gov = None
            for l0, target, d in dlist:
                if l0 < ln:
                    gov = (target, d)
            if gov is None or gov[1] is None:
                continue                                   # a use before any definition (the header's), or one of an unplanned definition
            target, d = gov
            if objlike and d.get("params", "") == "" and d["action"] == "delete":
                target = target + "()"                     # an object-like use becomes a call of the function-like canonical
            if target != name:
                edits.append((mm.start(), mm.end(), target))
                rec["use_renames"] += 1
            if d["action"] in ("rename", "keep-variant") and ln not in marked_lines:
                le = m.find("\n", mm.start())
                le = len(raw) if le < 0 else le
                if FAKE not in raw[ls[ln - 1]:le]:
                    edits.append((le, le, f"  {FAKE} gte via {target} — {', '.join(d.get('extra') or d.get('fewer') or ['a clobber'])} beyond Sony's `{d['canonical']}` (P36 T5 {label})"))
                    marked_lines.add(ln)
                    rec["marked"] += 1
    # direct statements
    for s in p["direct"]:
        pos = ls[s["line"] - 1] + s["col"] - 1
        e = dl.stmt_end(m, pos)
        if e < 0 or not dl.ASM_HEAD.match(m, pos):
            rec["direct"].append(dict(line=s["line"], action="refused", why="statement not found at the census position"))
            continue
        how, text, name = direct_rewrite(s, canon)
        if how == "call":
            edits.append((pos, e, text))
            rec["direct_calls"] += 1
            rec["direct"].append(dict(line=s["line"], action="call", name=name))
        elif how == "lever":
            le = m.find("\n", pos)
            le = len(raw) if le < 0 else le
            if FAKE not in raw[ls[s["line"] - 1]:le] and s["line"] not in marked_lines:
                edits.append((le, le, f"  {FAKE} gte direct — clobbers {name} ({', '.join(text if isinstance(text, list) else [str(text)])}) beyond Sony's (P36 T5 {label})".replace("clobbers " + str(text) + " (", "as " + str(text) + " (")))
                marked_lines.add(s["line"])
                rec["marked"] += 1
            rec["direct_levers"] += 1
            rec["direct"].append(dict(line=s["line"], action="lever", variant=text, delta=name))
        else:
            rec["direct_none"] += 1
            rec["direct"].append(dict(line=s["line"], action="none", why=text))
    return edits, rec


def apply_batch(a):
    clean, dirty = dl.src_clean()
    if not clean:
        sys.exit(f"gte_consolidate --apply: src/ is dirty — commit or tools/delever.py --restore first:\n{dirty[:400]}")
    ok, why = oracle.calibration_current()
    if not ok:
        sys.exit(f"gte_consolidate --apply: calibration not current ({why})")
    if not (REPO / HEADER).exists() or '#include "gte_inline.h"' not in (REPO / COMMON).read_text():
        sys.exit("gte_consolidate --apply: the header is not in place (--header first, then the fleet run and its commit)")
    dl.ensure_census(a.jobs)
    inv = inventory(a.jobs, quiet=True)
    canon = canonical_table(inv, quiet=True)
    files = plan_files(inv, canon, a.only, bound=header_bound_names(inv))
    order = sorted(files, key=lambda tu: (-len(files[tu]["defs"]) - len(files[tu]["direct"]), tu))
    ledger_rows = [json.loads(l) for l in LEDGER.read_text().splitlines() if l.strip()] if LEDGER.exists() else []
    # a REFUSED file (restored to its original text, its reason in the ledger) is not drawn again without --rejudge
    done = {r["tu"] for r in ledger_rows if r.get("rung") == "gte" and r.get("verdict") in ("CONSOLIDATED", "CONSOLIDATED-DEFS-ONLY", "UNCHANGED", "REFUSED")}
    order = [tu for tu in order if tu not in done or a.rejudge][:a.batch]
    print(f"gte_consolidate --apply {a.label}: {len(order)} files of {len(files)} with work ({len(done)} done) — "
          f"{sum(len(files[t]['defs']) for t in order)} definitions, {sum(len(files[t]['direct']) for t in order)} direct statements", flush=True)
    if not order:
        print("gte_consolidate --apply: nothing to do")
        return 0
    recipes = oracle.load_recipes()["recipes"]
    by_src = oracle.recipes_by_src(recipes)
    inc = dl.includers()
    def recipes_for(tu):
        return [r for t in inc.get(tu, []) for r in by_src.get(t, [])] if tu.endswith(".h") else by_src.get(tu, [])
    dl.INFLIGHT.write_text(json.dumps(dict(label=a.label, files={tu: (REPO / tu).read_text(errors="surrogateescape") for tu in order})))
    log_p = RUN / f"apply_{a.label}.log"
    log_f = open(log_p, "a")
    def log(msg):
        line = f"{time.strftime('%H:%M:%S')} {msg}"
        with _LOCK:
            print(line, flush=True)
            log_f.write(line + "\n")
            log_f.flush()
    pool = ThreadPoolExecutor(max_workers=a.jobs)
    results = []

    def work(tu):
        path = REPO / tu
        st = path.stat()
        raw = path.read_text(errors="surrogateescape")
        recs = recipes_for(tu)
        row = dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=a.label, rung="gte", calib=dict(head=oracle.head(), stamp=oracle.config_stamp()),
                   tu=tu, fn=None, addr=None, aliases=None, header=tu.endswith(".h"), sites=[], compiles=0, seconds=0.0)
        if not recs:
            row["verdict"] = "NO-RECIPE"
            return row
        plan_tu = files[tu]
        # the variant trial: a definition whose only difference from the canonical one is a clobber is tried AS canonical (deleted, its
        # uses renamed to the canonical name), one at a time on the untouched text; IDENTICAL -> the clobber was no lever here
        variants = [d for d in plan_tu["defs"] if d["action"] == "rename"]
        freed = 0
        for d in variants:
            trial = dict(defs=[dict(d, action="delete")], direct=[], renames={})
            try:
                ed, _ = file_edits(tu, raw, trial, canon, a.label)
                cand = dl.apply_edits(raw, ed)
                if cand == raw:
                    continue
                try:
                    v, dt, err = oracle.judge_all(recs, cand, tag="gtev", write_path=(tu if tu.endswith(".h") else None))
                finally:
                    dl.restore_file(path, raw, st)
                row["compiles"] += len(recs)
                row["seconds"] += dt
                if v == "IDENTICAL":
                    d["action"], d["trial"] = "delete", "IDENTICAL"
                    freed += 1
                else:
                    d["trial"] = v
                    if d.get("header_bound"):
                        d["action"], d["why"] = "keep-variant", "header-bound variant (its uses in the unit marked; the header's use binds to it)"
            except (Refuse, dl.Refuse) as ex:
                d["trial"] = f"REFUSED {ex}"
        try:
            edits, rec = file_edits(tu, raw, plan_tu, canon, a.label)
        except Refuse as ex:
            row.update(verdict="REFUSED", why=str(ex))
            log(f"  {tu}: REFUSED {ex}")
            return row
        rec["variants_freed"] = freed
        rec["variants_kept"] = sum(1 for d in variants if d["action"] in ("rename", "keep-variant"))
        row["record"] = rec
        cands = []
        try:
            cands.append(("all", dl.apply_edits(raw, edits)))
            no_direct = [e for e in edits if not any(e[0] == dl.line_starts(raw)[s["line"] - 1] + s["col"] - 1 for s in files[tu]["direct"])]
            if len(no_direct) != len(edits):
                cands.append(("defs-only", dl.apply_edits(raw, no_direct)))
        except dl.Refuse as ex:
            row.update(verdict="REFUSED", why=f"edits: {ex}")
            log(f"  {tu}: REFUSED edits {ex}")
            return row
        verdict = "UNCHANGED"
        for tag, cand in cands:
            if cand == raw:
                continue
            try:
                if tu.endswith(".h") and len(recs) > 1:
                    path.write_text(cand, errors="surrogateescape")
                    vs = list(pool.map(lambda r: oracle.judge(r, None, tag="gte"), recs))
                    bad = [v for v in vs if v[0] != "IDENTICAL"]
                    v, dt, err = (bad[0][0], sum(x[1] for x in vs), bad[0][2]) if bad else ("IDENTICAL", sum(x[1] for x in vs), "")
                else:
                    v, dt, err = oracle.judge_all(recs, cand, tag="gte", write_path=(tu if tu.endswith(".h") else None))
            finally:
                dl.restore_file(path, raw, st)
            row["compiles"] += len(recs)
            row["seconds"] += dt
            if v == "IDENTICAL":
                path.write_text(cand, errors="surrogateescape")
                verdict = "CONSOLIDATED" if tag == "all" else "CONSOLIDATED-DEFS-ONLY"
                if tag != "all":
                    rec["direct_calls_refused"] = rec.pop("direct_calls", 0)
                    log(f"  {tu}: the direct-statement rewrites DIFFER — kept the definition edits only")
                break
            verdict = f"DIFFERS-{tag}" if v == "DIFFERS" else f"{v}-{tag}"
            log(f"  {tu}: {tag} {v} {err[:120]}")
        row["verdict"] = verdict if verdict.startswith(("CONSOLIDATED", "UNCHANGED")) else "REFUSED"
        if not verdict.startswith(("CONSOLIDATED", "UNCHANGED")):
            row["why"] = verdict
        log(f"  {tu}: {row['verdict']} — deleted {rec['deleted']} defs, renamed {rec['renamed_defs']}, use renames {rec['use_renames']}, "
            f"direct calls {rec.get('direct_calls', 0)}, direct levers {rec['direct_levers']}, unmatched {rec['direct_none']}, marked {rec['marked']}")
        return row
    tus = [tu for tu in order if not tu.endswith(".h")]
    hdrs = [tu for tu in order if tu.endswith(".h")]
    with ThreadPoolExecutor(max_workers=a.jobs) as ex:
        results = list(ex.map(work, tus))
    for h in hdrs:
        results.append(work(h))
    pool.shutdown(wait=True)
    dl.ledger_append(results)
    agg = collections.Counter()
    for r in results:
        agg[r["verdict"]] += 1
        for k in ("deleted", "renamed_defs", "use_renames", "direct_calls", "direct_levers", "direct_none", "marked", "variants_freed", "variants_kept", "kept"):
            agg[k] += r.get("record", {}).get(k, 0)
        agg["compiles"] += r["compiles"]
    line = (f"gte_consolidate: batch {a.label} — {len(order)} files: {agg['CONSOLIDATED']} consolidated, {agg['CONSOLIDATED-DEFS-ONLY']} defs-only, "
            f"{agg['UNCHANGED']} unchanged, {agg['REFUSED']} refused, {agg['NO-RECIPE']} no-recipe · definitions deleted {agg['deleted']} / renamed as lever variants "
            f"{agg['renamed_defs']} (variant trials: {agg['variants_freed']} freed, {agg['variants_kept']} kept) · header-bound definitions kept {agg['kept']} · use renames {agg['use_renames']} · direct statements → calls {agg['direct_calls']} / lever {agg['direct_levers']} / "
            f"unmatched {agg['direct_none']} · markers {agg['marked']} · compiles {agg['compiles']} · "
            f"final {agg['CONSOLIDATED'] + agg['CONSOLIDATED-DEFS-ONLY']}/{agg['CONSOLIDATED'] + agg['CONSOLIDATED-DEFS-ONLY']} written files identical · "
            f"refused {agg['REFUSED']} (restored, ledgered)")
    log(line)
    (RUN / f"batch_{a.label}.json").write_text(json.dumps(dict(label=a.label, files=order, totals=dict(agg), rows=results), indent=1))
    # a refused file is restored and ledgered — a report, not a failure of the tree; the cycle's gate is the fleet run
    return 0


# ----------------------------------------------------------------------------------------------------------------------
# --sweep: dead asm-bearing macros; a compound macro's inner asm dropped when byte-neutral
# ----------------------------------------------------------------------------------------------------------------------
def sweep(a):
    clean, dirty = dl.src_clean()
    if not clean:
        sys.exit(f"gte_consolidate --sweep: src/ is dirty:\n{dirty[:400]}")
    ok, why = oracle.calibration_current()
    if not ok:
        sys.exit(f"gte_consolidate --sweep: calibration not current ({why})")
    dl.ensure_census(a.jobs)
    sites = dl.load_sites()
    uses_by_file = collections.defaultdict(collections.Counter)
    for s in sites:
        if s.get("via"):
            uses_by_file[s["tu"]][s["via"]] += 1
    inc = dl.includers()
    # a macro used by an included shared header counts as used by every includer
    hdr_uses = {h: uses_by_file.get(h, collections.Counter()) for h in inc}
    recipes = oracle.load_recipes()["recipes"]
    by_src = oracle.recipes_by_src(recipes)
    rows, n_dead, n_inner, n_files = [], 0, 0, 0
    files = files_under_src()
    if a.only:
        files = [p for p in files if any(o in p.as_posix() for o in a.only)]
    for p in files:
        rel = p.relative_to(REPO).as_posix()
        raw = p.read_text(errors="surrogateescape")
        if "#define" not in raw:
            continue
        blocks = [(l0, l1, name, body) for (l0, l1, name, body) in lc.define_blocks(raw) if lc.macro_kind(body) and lc.macro_kind(body) != "gte"]
        if not blocks:
            continue
        used = collections.Counter(uses_by_file.get(rel, {}))
        for h, hu in hdr_uses.items():
            if rel in inc.get(h, []):
                used.update(hu)
        m = dl.same_len_mask(raw)
        ls = dl.line_starts(raw)
        edits, dead, inner = [], [], []
        # the file's text with EVERY #define line of a name blanked: a sibling definition (SHB is defined twice per unit) is not a use
        def_spans = collections.defaultdict(list)
        for (l0, l1, name, body) in lc.define_blocks(raw):
            def_spans[name].append((ls[l0 - 1], ls[l1] if l1 < len(ls) else len(raw)))
        def mentions(name, l0=None, next_l0=None):
            text = m
            for s0, e0 in def_spans.get(name, ()):
                text = text[:s0] + " " * (e0 - s0) + text[e0:]
            if l0 is not None:
                a = ls[l0 - 1]
                b = ls[next_l0 - 1] if next_l0 else len(text)
                text = text[a:b]
            return re.search(r"\b%s\b" % re.escape(name), text) is not None
        # uses per DEFINITION: a use (a census site via the name, or an #include of a header that uses the name) is governed by the last
        # definition of that name above it; a definition with no governed use is dead even when a sibling definition is used
        use_lines = collections.defaultdict(list)
        for s in sites:
            if s["tu"] == rel and s.get("via"):
                use_lines[s["via"]].append(s["line"])
        inc_lines = []
        for mm in sc.INCLUDE_LINE.finditer(m):
            h = os.path.normpath(os.path.join(os.path.dirname(rel), mm.group(1)))
            inc_lines.append((m.count("\n", 0, mm.start()) + 1, hdr_uses.get(h, collections.Counter())))
        def governed_uses(name, l0, next_l0):
            n = sum(1 for ln in use_lines.get(name, []) if l0 < ln and (next_l0 is None or ln < next_l0))
            n += sum(1 for ln, hu in inc_lines if hu.get(name, 0) and l0 < ln and (next_l0 is None or ln < next_l0))
            return n
        same_name = collections.defaultdict(list)
        for (l0, l1, name, body) in lc.define_blocks(raw):
            same_name[name].append(l0)
        for (l0, l1, name, body) in blocks:
            start, end = ls[l0 - 1], ls[l1] if l1 < len(ls) else len(raw)
            later = sorted(x for x in same_name[name] if x > l0)
            next_l0 = later[0] if later else None
            if governed_uses(name, l0, next_l0) == 0 and not mentions(name, l0, next_l0):
                edits.append((start, end, ""))
                dead.append(name)
                continue
            # a compound macro: drop the asm statement line(s) inside the definition (the launder/barrier steer), keep the code
            lines = raw[start:end].split("\n")
            keep, dropped = [], 0
            for ln in lines:
                if lc.ASM_KW.search(ln) and ("__asm__" in ln or "asm" in ln) and ('"' in ln):
                    dropped += 1
                    continue
                keep.append(ln)
            if dropped and len(keep) > 1:
                new = "\n".join(keep)
                if not new.endswith("\n") and raw[start:end].endswith("\n"):
                    new += "\n"
                edits.append((start, end, new))
                inner.append(name)
        if not edits:
            continue
        recs = [r for t in inc.get(rel, []) for r in by_src.get(t, [])] if rel.endswith(".h") else by_src.get(rel, [])
        if not recs:
            print(f"  {rel}: no recipe — skipped")
            continue
        st = p.stat()
        try:
            cand = dl.apply_edits(raw, edits)
        except dl.Refuse as ex:
            print(f"  {rel}: REFUSED {ex}")
            continue
        verdict_all = None
        for tag, cand_t in (("all", cand), ("dead-only", dl.apply_edits(raw, [e for e in edits if e[2] == ""]) if inner and dead else None)):
            if cand_t is None or cand_t == raw:
                continue
            try:
                v, dt, err = oracle.judge_all(recs, cand_t, tag="sweep", write_path=(rel if rel.endswith(".h") else None))
            finally:
                dl.restore_file(p, raw, st)
            if v == "IDENTICAL":
                p.write_text(cand_t, errors="surrogateescape")
                verdict_all = tag
                break
            print(f"  {rel}: {tag} {v} {err[:100]}")
        n_files += verdict_all is not None
        if verdict_all == "all":
            n_dead += len(dead)
            n_inner += len(inner)
        elif verdict_all == "dead-only":
            n_dead += len(dead)
            inner_kept = inner
            inner = []
        rows.append(dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=a.label, rung="sweep", calib=dict(head=oracle.head(), stamp=oracle.config_stamp()),
                         tu=rel, fn=None, addr=None, aliases=None, header=rel.endswith(".h"), verdict=("SWEPT-" + verdict_all if verdict_all else "REFUSED"),
                         dead=dead, inner_dropped=(inner if verdict_all else []), sites=[], compiles=len(recs)))
        print(f"  {rel}: {rows[-1]['verdict']} — dead {dead} inner-asm dropped {inner if verdict_all else []}")
    dl.ledger_append(rows)
    print(f"gte_consolidate --sweep {a.label}: {n_dead} dead asm-bearing macro definitions deleted, {n_inner} compound macros' inner asm dropped, "
          f"{n_files} files written, {sum(1 for r in rows if r['verdict'] == 'REFUSED')} refused")
    return 0


def remark(a):
    """--remark: every `gte-lever` site the census reports UNMARKED gets `// !FAKE: gte …` at the end of its (first) line; a variant
    note that still carries the census's marker token is rewritten; each file judged through every recipe (comments only, but the
    oracle says so). Run tools/delever.py --scrub first when misplaced markers exist (they are orphans)."""
    clean, dirty = dl.src_clean()
    if not clean and not a.dirty_ok:
        sys.exit(f"gte_consolidate --remark: src/ is dirty (or --dirty-ok after a scrub, both comment-only and judged):\n{dirty[:400]}")
    ok, why = oracle.calibration_current()
    if not ok:
        sys.exit(f"gte_consolidate --remark: calibration not current ({why})")
    dl.ensure_census(a.jobs)
    sites = [s for s in dl.load_sites() if s["kind"] == lc.GTE_LEVER_KIND and not s["marked"]]
    by_tu = collections.defaultdict(list)
    for s in sites:
        by_tu[s["tu"]].append(s)
    recipes = oracle.load_recipes()["recipes"]
    by_src = oracle.recipes_by_src(recipes)
    inc = dl.includers()
    note_re = re.compile(r"^([ \t]*)/\* !FAKE: gte variant `([^`]+)` — (.*?) beyond Sony's `([^`]+)` \(a scheduling steer; P36 T5\) \*/[ \t]*$", re.M)
    files = set(by_tu) | {p.relative_to(REPO).as_posix() for p in files_under_src() if "/* !FAKE: gte variant" in p.read_text(errors="surrogateescape")}
    if a.only:
        files = {f for f in files if any(o in f for o in a.only)}
    rows, n_marks, n_notes, n_files, bad = [], 0, 0, 0, 0
    for tu in sorted(files):
        path = REPO / tu
        st = path.stat()
        raw = path.read_text(errors="surrogateescape")
        ls = dl.line_starts(raw)
        edits = []
        for s in by_tu.get(tu, []):
            le = ls[s["line"]] - 1 if s["line"] < len(ls) else len(raw)
            if FAKE in raw[ls[s["line"] - 1]:le]:
                continue
            what = f"gte via {s['via']}" if s.get("via") else "gte direct"
            edits.append((le, le, f"  {FAKE} {what} — clobbers beyond Sony's macro (a scheduling steer; P36 T5 {a.label})"))
        n_marks += len(edits)
        for mm in note_re.finditer(raw):
            edits.append((mm.start(), mm.end(), f"{mm.group(1)}/* GTE VARIANT `{mm.group(2)}`: {mm.group(3)} beyond Sony's `{mm.group(4)}` — a scheduling steer, its uses are marked (P36 T5) */"))
            n_notes += 1
        if not edits:
            continue
        cand = dl.apply_edits(raw, edits)
        recs = [r for t_ in inc.get(tu, []) for r in by_src.get(t_, [])] if tu.endswith(".h") else by_src.get(tu, [])
        if not recs:
            print(f"  {tu}: no recipe — skipped")
            continue
        try:
            v, dt, err = oracle.judge_all(recs, cand, tag="remark", write_path=(tu if tu.endswith(".h") else None))
        finally:
            dl.restore_file(path, raw, st)
        if v == "IDENTICAL":
            path.write_text(cand, errors="surrogateescape")
            n_files += 1
        else:
            bad += 1
            print(f"  {tu}: {v} — NOT written ({err[:120]})")
        rows.append(dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=a.label, rung="remark", calib=dict(head=oracle.head(), stamp=oracle.config_stamp()),
                         tu=tu, fn=None, addr=None, aliases=None, header=tu.endswith(".h"), verdict=("REMARKED" if v == "IDENTICAL" else f"REMARK-{v}"),
                         marks=len([e for e in edits if e[2].startswith("  //")]), notes=len([e for e in edits if e[2].lstrip().startswith("/*")]), sites=[], compiles=len(recs)))
    dl.ledger_append(rows)
    print(f"gte_consolidate --remark {a.label}: {n_marks} markers placed, {n_notes} variant notes rewritten, {n_files} files written, {bad} refused")
    return 0 if not bad else 1


def status():
    rows = [json.loads(l) for l in LEDGER.read_text().splitlines() if l.strip()] if LEDGER.exists() else []
    g = [r for r in rows if r.get("rung") in ("gte", "sweep")]
    print(f"gte_consolidate --status: {len(g)} rows — {dict(collections.Counter(r['verdict'] for r in g))}")
    return 0


# ----------------------------------------------------------------------------------------------------------------------
def selftest():
    ok = True
    def fail(msg):
        nonlocal ok
        ok = False
        print("selftest FAIL:", msg)
    # 1. the signature engine: three spellings of rtps are one signature; a template with an operand binds to $4
    s1 = signature('"nop;nop;rtps"')
    s2 = signature('"nop;" "nop;" ".word 0x4a180001"')
    s3 = signature('"nop;nop;cop2 0x0180001"')
    if not (s1["ok"] and s1["bytes"] == s2["bytes"] == s3["bytes"]):
        fail(f"rtps spellings: {s1['bytes'][:40]} {s2['bytes'][:40]} {s3['bytes'][:40]}")
    s4 = signature('"lwc2 $0, 0( %0 );" "lwc2 $1, 4( %0 )" : : "r"( r0 )')
    s5 = signature('"lwc2 $0, 0(%0)\\n" "lwc2 $1, 4(%0)\\n" : : "r"(r0) : "memory"')
    if not (s4["ok"] and s4["bytes"] == s5["bytes"] and s4["nin"] == 1 and s4["clob"] == [] and s5["clob"] == ["memory"]):
        fail(f"ldv0 spellings/clobbers: {s4} {s5}")
    if signature('"nop;nop;rtpt"')["bytes"] == s1["bytes"]:
        fail("rtps and rtpt must differ")
    # 2. the canonical table on a synthetic inventory: canonical / variant / private name / concatenated direct statement
    inv = dict(definitions=[
        dict(tu="a.c", l0=1, l1=2, name="gte_ldv0", params="( r0 )", body='__asm__ volatile ( "lwc2 $0, 0( %0 );" "lwc2 $1, 4( %0 )" : : "r"( r0 ) )', kind="gte", sig=s4),
        dict(tu="b.c", l0=1, l1=2, name="gte_ldv0", params="(r0)", body='__asm__ __volatile__( "lwc2 $0, 0(%0)\\n" "lwc2 $1, 4(%0)\\n" : : "r"(r0) : "memory")', kind="gte", sig=s5),
        dict(tu="c.c", l0=1, l1=2, name="LDV0_DA34", params="( r0 )", body='__asm__ volatile ("lwc2 $0, 0( %0 );lwc2 $1, 4( %0 )" : : "r"( r0 ))', kind="gte", sig=s4),
        dict(tu="a.c", l0=3, l1=3, name="gte_rtps", params="()", body='__asm__ volatile ("nop;nop;rtps")', kind="gte", sig=s1),
    ], direct=[], uses={})
    canon = canonical_table(inv, quiet=True, write=False)
    t = canon["canonical"].get(sig_key(s4))
    if not t or t["name"] != "gte_ldv0" or t["clob"] != [] or t["defs"] != 2:
        fail(f"canonical ldv0: {t}")
    v = [x for x in canon["variants"].values() if x["of"] == "gte_ldv0"]
    if len(v) != 1 or v[0]["name"] != "gte_ldv0_m" or v[0]["extra"] != ["memory"]:
        fail(f"ldv0 memory variant: {v}")
    # 3. direct statements: a canonical call, a lever, a concatenation
    d_call = dict(sig=signature('"lwc2 $0, 0(%0);" "lwc2 $1, 4(%0)" : : "r"(p)'))
    d_lever = dict(sig=signature('"lwc2 $0, 0(%0);" "lwc2 $1, 4(%0)" : : "r"(p) : "memory"'))
    d_cat = dict(sig=signature('"lwc2 $0, 0(%0);" "lwc2 $1, 4(%0);" "nop;nop;rtps" : : "r"(p)'))
    if direct_rewrite(d_call, canon) != ("call", "gte_ldv0(p);", "gte_ldv0"):
        fail(f"direct call: {direct_rewrite(d_call, canon)}")
    if direct_rewrite(d_lever, canon)[0] != "lever" or direct_rewrite(d_lever, canon)[1] != "gte_ldv0_m":
        fail(f"direct lever: {direct_rewrite(d_lever, canon)}")
    r = direct_rewrite(d_cat, canon)
    if r != ("call", "gte_ldv0(p); gte_rtps();", "gte_ldv0+gte_rtps"):
        fail(f"direct concatenation: {r}")
    # 4. the per-file edits on a fixture: the canonical def deleted, the private use renamed, the variant renamed + marked, a direct call
    fx = ('#define gte_ldv0( r0 ) __asm__ volatile ( "lwc2 $0, 0( %0 );" "lwc2 $1, 4( %0 )" : : "r"( r0 ) )\n'
          '#define LDV0_DA34( r0 ) __asm__ volatile ("lwc2 $0, 0( %0 );lwc2 $1, 4( %0 )" : : "r"( r0 ))\n'
          '#define gte_ldv0m( r0 ) __asm__ __volatile__( "lwc2 $0, 0(%0)\\n" "lwc2 $1, 4(%0)\\n" : : "r"(r0) : "memory")\n'
          'void f(s32 *v) {\n    LDV0_DA34(v);\n    gte_ldv0m(v);\n    __asm__ volatile("lwc2 $0, 0(%0);" "lwc2 $1, 4(%0)" : : "r"(v));\n}\n')
    defs = []
    for (l0, l1, name, body) in lc.define_blocks(fx):
        sg = signature(asm_inner(body))
        defs.append(dict(tu="fx.c", l0=l0, l1=l1, name=name, params=define_params(fx, l0), body=body, kind="gte", sig=sg))
    fm, fls = dl.same_len_mask(fx), dl.line_starts(fx)
    fpos = fls[6] + 4
    fo = fm.find("(", fpos)
    finner = fm[fo + 1:lc._paren_span(fm, fo)]
    inv2 = dict(definitions=defs, direct=[dict(tu="fx.c", line=7, col=5, fn="f", inner=finner, sig=signature(finner))], uses={})
    canon2 = canonical_table(inv2, quiet=True, write=False)
    plan = plan_files(inv2, canon2, bound={})
    edits, rec = file_edits("fx.c", fx, plan["fx.c"], canon2, "self")
    out = dl.apply_edits(fx, edits)
    if "#define gte_ldv0(" in out or "#define LDV0_DA34" in out:
        fail("canonical/private definitions must be deleted")
    if "#define gte_ldv0_m( r0 )" not in out or "GTE VARIANT `gte_ldv0_m`" not in out or "!FAKE" in out.split("#define gte_ldv0_m")[0]:
        fail(f"the variant definition renamed + noted (the note carries no marker token):\n{out}")
    # an object-like macro: `#define MVMVA __asm__ volatile ("nop;nop;rtps")` used as `MVMVA;` -> `gte_rtps();`
    fxo = ('#define MVMVA __asm__ volatile ("nop;nop;rtps")\nvoid h(void) {\n    MVMVA;\n}\n')
    defso = []
    for (l0, l1, name, body) in lc.define_blocks(fxo):
        defso.append(dict(tu="fo.c", l0=l0, l1=l1, name=name, params=define_params(fxo, l0), body=body, kind="gte", sig=signature(asm_inner(body))))
    invo = dict(definitions=defso + [dict(tu="fa.c", l0=1, l1=1, name="gte_rtps", params="()", body='__asm__ volatile ("nop;nop;rtps")', kind="gte", sig=signature('"nop;nop;rtps"'))], direct=[], uses={})
    canono = canonical_table(invo, quiet=True, write=False)
    plano = plan_files(invo, canono, bound={})
    editso, reco = file_edits("fo.c", fxo, plano["fo.c"], canono, "self")
    outo = dl.apply_edits(fxo, editso)
    if "#define" in outo or "    gte_rtps();\n" not in outo:
        fail(f"object-like macro: definition deleted, the bare use becomes a call:\n{outo}")
    if "    gte_ldv0(v);\n" not in out:
        fail(f"the private use renamed to the canonical name:\n{out}")
    if "gte_ldv0_m(v);  // !FAKE: gte via gte_ldv0_m" not in out:
        fail(f"the lever variant's use marked:\n{out}")
    if "    gte_ldv0(v);\n}" not in out:
        fail(f"the direct statement rewritten into the canonical call:\n{out}")
    if rec["deleted"] != 2 or rec["renamed_defs"] != 1 or rec["use_renames"] != 2 or rec["direct_calls"] != 1 or rec["marked"] != 1:
        fail(f"record: {rec}")
    # 4b. a name redefined in the same file: each use follows the definition above it (a wrong-target rename changed store offsets in T5's first run)
    fx2 = ('#define gte_stsxy3( r0 ) __asm__ volatile ( "swc2 $12, 0( %0 );" "swc2 $13, 4( %0 );" "swc2 $14, 8( %0 )" : : "r"( r0 ) : "memory" )\n'
           'void f(s32 *v) {\n    gte_stsxy3(v);\n}\n'
           '#define gte_stsxy3( r0 ) __asm__ volatile ( "swc2 $12, 0( %0 );" "swc2 $13, 12( %0 );" "swc2 $14, 24( %0 )" : : "r"( r0 ) : "memory" )\n'
           'void g(s32 *v) {\n    gte_stsxy3(v);\n}\n')
    defs2 = []
    for (l0, l1, name, body) in lc.define_blocks(fx2):
        defs2.append(dict(tu="fy.c", l0=l0, l1=l1, name=name, params=define_params(fx2, l0), body=body, kind="gte", sig=signature(asm_inner(body))))
    inv3 = dict(definitions=defs2, direct=[], uses={})
    canon3 = canonical_table(inv3, quiet=True, write=False)
    names3 = sorted(t_["name"] for t_ in canon3["canonical"].values())
    plan3 = plan_files(inv3, canon3, bound={})
    edits3, rec3 = file_edits("fy.c", fx2, plan3["fy.c"], canon3, "self")
    out3 = dl.apply_edits(fx2, edits3)
    body_f = out3.split("void f")[1].split("}")[0]
    body_g = out3.split("void g")[1].split("}")[0]
    tgt = {t_["tmpl"][:30]: t_["name"] for t_ in canon3["canonical"].values()}
    if len(names3) != 2 or "#define" in out3:
        fail(f"redefinition: two signatures, both definitions deleted: {names3} / {'#define' in out3}")
    name_of = {}
    for t_ in canon3["canonical"].values():
        name_of["f" if ", 4( %0 )" in t_["tmpl"] else "g"] = t_["name"]
    if f"{name_of.get('f')}(v)" not in body_f or f"{name_of.get('g')}(v)" not in body_g or name_of.get("f") == name_of.get("g"):
        fail(f"redefinition: each use must follow its own definition ({name_of}):\n{out3}")
    if any(n.endswith("_alt_alt") for n in names3):
        fail(f"names: {names3}")
    # 4c. a header-bound homonym is kept: the includer's `gte_stsxy3_f4` with f3's bytes, used by an included shared header
    plan4 = plan_files(inv2, canon2, bound={"fx.c": {"LDV0_DA34"}})
    kept = [d for d in plan4["fx.c"]["defs"] if d["action"] == "keep"]
    if len(kept) != 1 or kept[0]["name"] != "LDV0_DA34":
        fail(f"header-bound homonym must be kept: {[(d['name'], d['action']) for d in plan4['fx.c']['defs']]}")
    edits4, rec4 = file_edits("fx.c", fx, plan4["fx.c"], canon2, "self")
    out4 = dl.apply_edits(fx, edits4)
    if "#define LDV0_DA34" not in out4 or "    LDV0_DA34(v);\n" not in out4 or rec4["kept"] != 1:
        fail(f"a kept definition and its use untouched:\n{out4}")
    # 5. the header renders every canonical macro once, with its parameters
    h = render_header(canon2)
    if h.count("#define gte_ldv0(") != 1 or "#define gte_ldv0_m" in h:
        fail("header: one canonical definition, no variant")
    print(f"gte_consolidate --selftest: {'OK' if ok else 'FAIL'} — signatures rtps={s1['bytes'][16:24]} ldv0={s4['bytes'][:16]}; table {len(canon2['canonical'])} canonical / {len(canon2['variants'])} variant; fixture edits {len(edits)}")
    return ok


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--inventory", action="store_true")
    ap.add_argument("--header", action="store_true")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--sweep", action="store_true")
    ap.add_argument("--remark", action="store_true", help="re-mark the census's UNMARKED gte-lever sites on their own lines (after --scrub)")
    ap.add_argument("--status", action="store_true")
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--batch", type=int, default=400)
    ap.add_argument("--label", default=None)
    ap.add_argument("--only", nargs="*", default=None)
    ap.add_argument("--rejudge", action="store_true")
    ap.add_argument("--dirty-ok", action="store_true", help="--remark on a tree the scrub just modified (one fleet run for both)")
    ap.add_argument("-j", "--jobs", type=int, default=12)
    a = ap.parse_args()
    RUN.mkdir(parents=True, exist_ok=True)
    if a.selftest:
        sys.exit(0 if selftest() else 1)
    if a.status:
        sys.exit(status())
    if a.inventory:
        dl.ensure_census(a.jobs)
        inv = inventory(a.jobs)
        canonical_table(inv)
        return
    if a.header:
        inv = json.loads(INVENTORY.read_text()) if INVENTORY.exists() else inventory(a.jobs, quiet=True)
        canon = canonical_table(inv, quiet=True)
        write_header(canon)
        return
    if a.apply:
        if not a.label:
            sys.exit("--label is required")
        sys.exit(apply_batch(a))
    if a.sweep:
        if not a.label:
            sys.exit("--label is required")
        sys.exit(sweep(a))
    if a.remark:
        if not a.label:
            sys.exit("--label is required")
        sys.exit(remark(a))
    ap.print_help()


if __name__ == "__main__":
    main()
