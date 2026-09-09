#!/usr/bin/env python3
"""delever.py — take the compiler-forcing constructs ("levers") out of matched C, byte-gated per translation unit
(Phase 36; the probe engine at T2, the campaign tool at T3).

    tools/delever.py --probe --sample 150 [--seed 1] [-j 12]     # T2: rung A + rung B on a stratified sample of DISTINCT bodies
                                                                 #     -> .run/P36/probe/{probe_results.jsonl,probe_summary.json,probe_table.md}

THE LADDER PER BODY (deterministic, zero tokens):
  rung A  strip-all — every removable site of the body rewritten at once (pin -> plain declaration; barrier/launder/keep-alive ->
          deleted; a hand-placed instruction -> its C; `$0` pin -> its variable's uses replaced by 0; volatile -> dropped; register ->
          dropped), one compile, the object compared with the fleet run's (tools/delever_oracle.py). Measured twice: with the `register`
          keyword dropped from the pin (the target form) and with it kept (A').
  rung B  greedy — if A differs: from the untouched text, the sites are re-applied one at a time (asm statements first, then pins,
          volatile, register); a site whose removal keeps the object identical is REMOVED, one that changes it is NEEDED.
The verdict of a body = the set of NEEDED sites; a body with none is lever-free. Never touched: GTE ops, the manifest's verbatim
bodies, an asm-body (a whole routine — the manifest's DECOMPILE rows are another task's work), file-scope declarations.

EVERY EDIT IS POSITIONAL on the raw text (line/col from the census), the file is written in place for the compile and restored
from the in-memory snapshot right after (never `git checkout`, R102); a site whose raw token does not match the census is REFUSED
(R43), never guessed.
"""
import argparse
import collections
import json
import os
import pathlib
import random
import re
import sys
import time
from concurrent.futures import ThreadPoolExecutor

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
import delever_oracle as oracle   # noqa: E402
import lever_census as lc         # noqa: E402
import share_census as sc         # noqa: E402

SITES = REPO / ".run" / "P36" / "census" / "lever_sites.jsonl"
PROBE = REPO / ".run" / "P36" / "probe"
REMOVABLE = {("A", "pin"), ("B", "barrier"), ("B", "launder"), ("B", "keepalive"), ("B", "instruction"),
             ("C", "cast"), ("C", "decl-body"), ("D", "register")}
ORDER = {"barrier": 0, "launder": 1, "keepalive": 2, "instruction": 3, "pin": 4, "cast": 5, "decl-body": 6, "register": 7}
STRLIT = lc.STRLIT


class Refuse(Exception):
    pass


# ----------------------------------------------------------------------------------------------------------------------
# text helpers (positions on the RAW text; comments masked to equal-length spaces so a ';' in a comment never ends a statement)
# ----------------------------------------------------------------------------------------------------------------------
def same_len_mask(raw):
    return sc._TOK.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)) if m.group(0)[:2] in ("/*", "//") else m.group(0), raw)


def line_starts(text):
    ls = [0]
    for ln in text.split("\n"):
        ls.append(ls[-1] + len(ln) + 1)
    return ls


def stmt_end(m, pos):
    """index just past the ';' that ends the statement starting at pos (paren depth 0, string literals skipped); -1 if none."""
    depth, i, n = 0, pos, len(m)
    while i < n:
        c = m[i]
        if c == '"':
            mm = STRLIT.match(m, i)
            i = mm.end() if mm else i + 1
            continue
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
        elif c == ";" and depth <= 0:
            return i + 1
        elif c == "}" and depth == 0:
            return -1
        i += 1
    return -1


def ws_after(m, pos):
    i = pos
    while i < len(m) and m[i] in " \t":
        i += 1
    return i


# ----------------------------------------------------------------------------------------------------------------------
# the rewrite of one site -> [(start, end, replacement)] on the raw text
# ----------------------------------------------------------------------------------------------------------------------
ASM_HEAD = re.compile(r"(?:__asm__|__asm|asm)\s*(?:__volatile__|volatile)?\s*\(")
PIN_CLAUSE = re.compile(r"\s*(?:__asm__|__asm|asm)\s*\(\s*\"[^\"]*\"\s*\)")
INSTR_TABLE = {
    # mnemonic -> (arity, C template) using OUT / IN1 / IN2 / IMM; the operands come from the asm's "=r"(..) / "r"(..) lists
    "addu": ("OUT = IN1;", "zero"), "move": ("OUT = IN1;", None), "addiu": ("OUT = IN1 + IMM;", None), "sll": ("OUT = IN1 << IMM;", None),
    "srl": ("OUT = (u32)IN1 >> IMM;", None), "and": ("OUT = IN1 & IN2;", None), "andi": ("OUT = IN1 & IMM;", None),
    "lui": ("OUT = IMM << 16;", None), "li": ("OUT = IMM;", None), "lw": ("OUT = *(s32 *)((s32)IN1 + IMM);", None),
    "lh": ("OUT = *(s16 *)((s32)IN1 + IMM);", None), "la": ("OUT = (s32)&SYM;", None),
}


def parse_asm_operands(inner):
    """(template, outputs, inputs) — outputs/inputs as [(constraint, expr)]; the asm's own parser rules (lever_census)."""
    s = inner.strip()
    parts, i, n = [], 0, len(s)
    while i < n:
        if s[i] in " \t\r\n":
            i += 1
            continue
        mm = STRLIT.match(s, i)
        if not mm:
            break
        parts.append(mm.group(0)[1:-1])
        i = mm.end()
    rest = s[i:].strip()
    secs = lc._split_sections(rest[1:]) if rest.startswith(":") else []
    def ops(sec):
        out = []
        for mm in re.finditer(r'"([^"]*)"\s*\(', sec):
            c = lc._paren_span(sec, mm.end() - 1)
            out.append((mm.group(1), sec[mm.end():c].strip()))
        return out
    outs = ops(secs[0]) if len(secs) > 0 else []
    ins = ops(secs[1]) if len(secs) > 1 else []
    return "".join(parts), outs, ins


def instruction_to_c(inner, indent):
    """The C statement for a hand-placed single-instruction asm, or None (residue)."""
    tmpl, outs, ins = parse_asm_operands(inner)
    t = re.sub(r"\\[nt]", " ", tmpl).strip()
    if len(outs) != 1:
        return None
    out_expr = outs[0][1]
    allops = [e for _, e in outs] + [e for _, e in ins]
    def resolve(tok):
        mm = re.fullmatch(r"%(\d+)", tok)
        if mm:
            k = int(mm.group(1))
            return allops[k] if k < len(allops) else None
        return None
    IMM = r"-?(?:0x[0-9A-Fa-f]+|\d+)"
    # two-instruction address / constant materializations (one C expression each)
    mm = re.fullmatch(r"lui\s+%0\s*,\s*%%hi\((\w+)\)\s*;?\s*addiu\s+%0\s*,\s*%0\s*,\s*%%lo\(\1\)", t)
    if mm:
        return f"{indent}{out_expr} = (s32)&{mm.group(1)};"
    mm = re.fullmatch(r"lui\s+%0\s*,\s*(" + IMM + r")\s*;?\s*ori\s+%0\s*,\s*%0\s*,\s*(" + IMM + r")", t)
    if mm:
        return f"{indent}{out_expr} = ({mm.group(1)} << 16) | {mm.group(2)};"
    if ";" in t or "\n" in t:
        return None                              # other multi-instruction templates are residue
    toks = [x for x in re.split(r"[\s,]+", t) if x]
    if not toks:
        return None
    mnem = toks[0].lower()
    if mnem not in INSTR_TABLE:
        return None
    templ, note = INSTR_TABLE[mnem]
    refs = [x for x in toks[1:]]
    if mnem == "addu":
        if len(refs) != 3:
            return None
        if refs[2] in ("$zero", "$0"):
            in1 = resolve(refs[1])
            return None if in1 is None else f"{indent}{out_expr} = {in1};"
        in1, in2 = resolve(refs[1]), resolve(refs[2])
        return None if in1 is None or in2 is None else f"{indent}{out_expr} = (s32){in1} + (s32){in2};"
    if mnem == "addiu" and len(refs) == 3 and refs[1] in ("$zero", "$0") and re.fullmatch(IMM, refs[2]):
        return f"{indent}{out_expr} = {refs[2]};"
    if mnem == "move":
        if len(refs) != 2:
            return None
        in1 = resolve(refs[1])
        return None if in1 is None else f"{indent}{out_expr} = {in1};"
    if mnem == "la":
        if len(refs) != 2 or not re.fullmatch(r"[A-Za-z_]\w*", refs[1]):
            return None
        return f"{indent}{out_expr} = (s32)&{refs[1]};"
    if mnem in ("lw", "lh"):
        mm = re.fullmatch(r"(-?\w+)\((%\d+)\)", refs[1]) if len(refs) == 2 else None
        if not mm:
            return None
        base = resolve(mm.group(2))
        return None if base is None else templ.replace("OUT", out_expr).replace("IN1", base).replace("IMM", mm.group(1)) and f"{indent}{templ.replace('OUT', out_expr).replace('IN1', base).replace('IMM', mm.group(1))}"
    if mnem in ("addiu", "sll", "srl", "andi"):
        if len(refs) != 3:
            return None
        in1 = resolve(refs[1])
        if in1 is None or not re.fullmatch(IMM, refs[2]):
            return None
        return f"{indent}{templ.replace('OUT', out_expr).replace('IN1', '(s32)' + in1).replace('IMM', refs[2])}"
    if mnem == "and":
        if len(refs) != 3:
            return None
        in1, in2 = resolve(refs[1]), resolve(refs[2])
        return None if in1 is None or in2 is None else f"{indent}{out_expr} = (s32){in1} & (s32){in2};"
    if mnem in ("lui", "li"):
        if len(refs) != 2 or not re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)", refs[1]):
            return None
        return f"{indent}{templ.replace('OUT', out_expr).replace('IMM', refs[1])}"
    return None


def site_edits(raw, m, ls, site, keep_register=False):
    """[(start, end, replacement)] for one site, or raise Refuse. `m` = same_len_mask(raw)."""
    pos = ls[site["line"] - 1] + site["col"] - 1
    cls, kind = site["cls"], site["kind"]
    indent_start = m.rfind("\n", 0, pos) + 1
    indent = re.match(r"[ \t]*", raw[indent_start:pos]).group(0)
    if cls == "A":
        if not m.startswith("register", pos):
            raise Refuse(f"token mismatch at {site['tu']}:{site['line']}: expected `register`")
        e = stmt_end(m, pos)
        if e < 0:
            raise Refuse(f"no statement end for the pin at {site['tu']}:{site['line']}")
        stmt = raw[pos:e]
        if site.get("zero"):
            # the zero-register variable: delete the declaration, replace every use in the body by 0
            mm = re.search(r"([A-Za-z_]\w*)\s*(?:__asm__|__asm|asm)\s*\(", stmt)
            if not mm:
                raise Refuse("zero pin without a name")
            name = mm.group(1)
            edits = [(indent_start if raw[indent_start:pos].strip() == "" else pos, e + (1 if raw[e:e + 1] == "\n" and raw[indent_start:pos].strip() == "" else 0), "")]
            b0, b1 = ls[site["fn_line"] - 1], ls[site["fn_end"]] - 1
            for um in re.finditer(r"\b%s\b" % re.escape(name), m[b0:b1]):
                s = b0 + um.start()
                if s < pos or s >= e:
                    edits.append((s, s + len(name), "0"))
            return edits
        new = stmt if keep_register else re.sub(r"\bregister\b[ \t]*", "", stmt, count=1)
        new = PIN_CLAUSE.sub("", new)
        return [(pos, e, new)]
    if cls == "B" and site.get("via"):
        name = site["via"]
        if not m.startswith(name, pos):
            raise Refuse(f"token mismatch at {site['tu']}:{site['line']}: expected `{name}(`")
        if kind not in ("barrier", "launder", "keepalive"):
            raise Refuse(f"macro-carried {kind} is residue")
        e = stmt_end(m, pos)
        if e < 0:
            raise Refuse("no statement end for the macro use")
        whole_line = raw[indent_start:pos].strip() == "" and raw[e:ws_after(m, e)].strip() == "" and raw[ws_after(m, e):ws_after(m, e) + 1] == "\n"
        return [(indent_start, ws_after(m, e) + 1, "")] if whole_line else [(pos, e, "")]
    if cls == "B":
        if not ASM_HEAD.match(m, pos):
            raise Refuse(f"token mismatch at {site['tu']}:{site['line']}: expected an asm statement")
        o = m.find("(", pos)
        c = lc._paren_span(m, o)
        e = stmt_end(m, pos)
        if c < 0 or e < 0:
            raise Refuse("unterminated asm statement")
        if kind in ("barrier", "launder", "keepalive"):
            new = ""
        elif kind == "instruction":
            new = instruction_to_c(m[o + 1:c] if '"' in m[o + 1:c] else raw[o + 1:c], "")
            if new is None:
                raise Refuse(f"instruction `{site['detail']}` has no C spelling in the table")
            new = new.strip()
        else:
            raise Refuse(f"asm kind {kind} is not removable")
        whole_line = raw[indent_start:pos].strip() == "" and raw[e:ws_after(m, e)].strip() == "" and raw[ws_after(m, e):ws_after(m, e) + 1] == "\n"
        if new == "" and whole_line:
            return [(indent_start, ws_after(m, e) + 1, "")]
        return [(pos, e, new)]
    if cls == "C":
        if not m.startswith("volatile", pos):
            raise Refuse(f"token mismatch at {site['tu']}:{site['line']}: expected `volatile`")
        return [(pos, ws_after(m, pos + len("volatile")), "")]
    if cls == "D":
        if not m.startswith("register", pos):
            raise Refuse(f"token mismatch at {site['tu']}:{site['line']}: expected `register`")
        return [(pos, ws_after(m, pos + len("register")), "")]
    raise Refuse(f"class {cls}/{kind} is not removable")


def apply_edits(raw, edits):
    """Splice non-overlapping edits (bottom-up). Overlap -> Refuse."""
    es = sorted(edits, key=lambda x: (x[0], x[1]))
    for a, b in zip(es, es[1:]):
        if b[0] < a[1]:
            raise Refuse(f"overlapping edits at {a[0]}..{a[1]} / {b[0]}..{b[1]}")
    out = raw
    for s, e, r in sorted(es, key=lambda x: -x[0]):
        out = out[:s] + r + out[e:]
    return out


# ----------------------------------------------------------------------------------------------------------------------
# the population
# ----------------------------------------------------------------------------------------------------------------------
def load_sites():
    return [json.loads(l) for l in SITES.read_text().splitlines() if l.strip()]


def bodies_from_sites(sites):
    bodies = {}
    for s in sites:
        if not s.get("fn"):
            continue
        b = bodies.setdefault((s["tu"], s["fn"]), dict(tu=s["tu"], fn=s["fn"], fn_line=s["fn_line"], fn_end=s["fn_end"], nhash=s.get("nhash"),
                                                        aliases=s["aliases"], header=s.get("header", False), sites=[], frozen=[]))
        if (s["cls"], s["kind"]) in REMOVABLE:
            b["sites"].append(s)
        else:
            b["frozen"].append(s)
    return bodies


def kind_of(tu):
    return "shared" if tu.startswith("src/shared/") else "ov" if tu.startswith("src/ov_") else "md" if tu.startswith("src/md_") \
        else "resident" if tu.startswith("src/resident/") else "main"


def includers():
    """header rel -> [TU rel] from the #include lines of every TU (the recipe to compile a header's body is an includer's)."""
    inc = collections.defaultdict(list)
    for p in sorted((REPO / "src").rglob("*.c")):
        rel = p.relative_to(REPO).as_posix()
        text = p.read_text(errors="surrogateescape")
        for mm in sc.INCLUDE_LINE.finditer(sc.mask_text(text)):
            inc[os.path.normpath(os.path.join(os.path.dirname(rel), mm.group(1)))].append(rel)
    return inc


def features(b):
    ks = collections.Counter(s["kind"] for s in b["sites"])
    n = len(b["sites"])
    mix = "pins-only" if set(ks) <= {"pin"} else "asm-only" if not (set(ks) & {"pin", "cast", "decl-body", "register"}) else "mixed"
    return dict(kind=kind_of(b["tu"]), n=n, bucket=("1" if n == 1 else "2-4" if n <= 4 else "5-9" if n <= 9 else "10+"), mix=mix,
                zero=any(s.get("zero") for s in b["sites"]), init=any(s.get("init") for s in b["sites"] if s["kind"] == "pin"),
                instr=any(s["kind"] == "instruction" for s in b["sites"]), cast=any(s["kind"] == "cast" for s in b["sites"]),
                register=any(s["kind"] == "register" for s in b["sites"]), volatile=any(s["cls"] == "C" for s in b["sites"]),
                launder=any(s["kind"] == "launder" for s in b["sites"]), barrier=any(s["kind"] == "barrier" for s in b["sites"]),
                keepalive=any(s["kind"] == "keepalive" for s in b["sites"]))


def stratified_sample(bodies, n, seed):
    rnd = random.Random(seed)
    # one exemplar per normalized class
    by_class = {}
    for key, b in bodies.items():
        if not b["sites"]:
            continue
        h = b["nhash"] or key
        cur = by_class.get(h)
        pref = {"main": 0, "resident": 1, "md": 2, "shared": 3, "ov": 4}[kind_of(b["tu"])]
        if cur is None or pref < cur[0]:
            by_class[h] = (pref, key)
    pool = [bodies[k] for _, k in by_class.values()]
    rnd.shuffle(pool)
    # quotas scale with --sample (the shape of the population: main/resident/md are few but distinct, overlays are many)
    base = {"main": 20, "resident": 16, "md": 15, "shared": 20, "ov": 79}
    scale = n / sum(base.values())
    quota = {k: max(3, int(round(v * scale))) for k, v in base.items()}
    picked, seen = [], set()
    for kind, q in quota.items():
        cands = [b for b in pool if kind_of(b["tu"]) == kind]
        # round-robin over (bucket, mix)
        groups = collections.defaultdict(list)
        for b in cands:
            f = features(b)
            groups[(f["bucket"], f["mix"])].append(b)
        keys = sorted(groups)
        i = 0
        while len([b for b in picked if kind_of(b["tu"]) == kind]) < q and any(groups[k] for k in keys):
            k = keys[i % len(keys)]
            i += 1
            if groups[k]:
                b = groups[k].pop()
                if (b["tu"], b["fn"]) not in seen:
                    picked.append(b)
                    seen.add((b["tu"], b["fn"]))
    # the special features, topped up from the pool
    for flag, want in (("zero", 10), ("init", 10), ("instr", 12), ("cast", 8), ("register", 5), ("launder", 8), ("keepalive", 6)):
        have = sum(1 for b in picked if features(b)[flag])
        for b in pool:
            if have >= want:
                break
            if (b["tu"], b["fn"]) not in seen and features(b)[flag]:
                picked.append(b)
                seen.add((b["tu"], b["fn"]))
                have += 1
    return picked


# ----------------------------------------------------------------------------------------------------------------------
# the ladder on one body
# ----------------------------------------------------------------------------------------------------------------------
def run_body(b, recipe, write_path, raw, m, ls, log):
    """Returns the per-body result dict; the caller restores the file."""
    sites = sorted(b["sites"], key=lambda s: (ORDER.get(s["kind"], 9), s["line"], s["col"]))
    res = dict(tu=b["tu"], fn=b["fn"], nhash=b["nhash"], kind=kind_of(b["tu"]), aliases=b["aliases"], header=b["header"],
               obj=recipe["obj"], n_sites=len(sites), sites=[dict(kind=s["kind"], cls=s["cls"], detail=s["detail"], line=s["line"]) for s in sites],
               refused=[], compiles=0, seconds=0.0, features=features(b))
    per_site, edits_all, edits_keep = {}, [], []
    usable = []
    for s in sites:
        try:
            ed = site_edits(raw, m, ls, s)
            edk = site_edits(raw, m, ls, s, keep_register=True) if s["kind"] == "pin" else ed
            per_site[id(s)] = (ed, edk)
            usable.append(s)
            edits_all += ed
            edits_keep += edk
        except Refuse as ex:
            res["refused"].append(dict(kind=s["kind"], line=s["line"], why=str(ex)))
    res["n_usable"] = len(usable)
    if not usable:
        res["verdict"] = "NOTHING-USABLE"
        return res

    def judge(edits, tag):
        try:
            cand = apply_edits(raw, edits)
        except Refuse as ex:
            return "REFUSED", str(ex)
        if cand == raw:
            return "REFUSED", "no-op edit (the candidate equals the original — an identical object would prove nothing, R37)"
        v, dt, err = oracle.judge(recipe, cand, tag=tag, write_path=write_path)
        res["compiles"] += 1
        res["seconds"] += dt
        return v, err
    # rung A (register dropped) and A' (register kept)
    vA, errA = judge(edits_all, "A")
    res["rung_A"] = vA
    res["rung_A_err"] = errA[:200] if vA == "COMPILE-ERROR" else ""
    if any(s["kind"] == "pin" for s in usable):
        vK, _ = judge(edits_keep, "Ak")
        res["rung_A_keep_register"] = vK
    else:
        res["rung_A_keep_register"] = vA
    if vA == "IDENTICAL":
        res["removed"] = [dict(kind=s["kind"], detail=s["detail"], line=s["line"]) for s in usable]
        res["needed"] = []
        res["verdict"] = "LEVER-FREE"
        return res
    # rung B greedy
    accepted, needed, removed = [], [], []
    for s in usable:
        ed, _ = per_site[id(s)]
        v, err = judge(accepted + ed, "B")
        if v == "IDENTICAL":
            accepted += ed
            removed.append(dict(kind=s["kind"], detail=s["detail"], line=s["line"]))
        else:
            needed.append(dict(kind=s["kind"], detail=s["detail"], line=s["line"], verdict=v, err=(err[:120] if v == "COMPILE-ERROR" else "")))
    res["removed"], res["needed"] = removed, needed
    res["verdict"] = "LEVER-FREE" if not needed else "RESIDUE"
    log(f"  {b['tu']}:{b['fn']} A={vA} B: removed {len(removed)} needed {len(needed)} compiles {res['compiles']}")
    return res


def probe(sample_n, seed, jobs):
    PROBE.mkdir(parents=True, exist_ok=True)
    ok, why = oracle.calibration_current()
    if not ok:
        sys.exit(f"delever: the oracle's calibration is not current ({why}) — run tools/delever_oracle.py --calibrate first (R56)")
    recipes = oracle.load_recipes()["recipes"]
    sites = load_sites()
    bodies = bodies_from_sites(sites)
    inc = includers()
    sample = stratified_sample(bodies, sample_n, seed)
    log_f = open(PROBE / "probe_log.txt", "a")

    def log(msg):
        line = f"{time.strftime('%H:%M:%S')} {msg}"
        print(line, flush=True)
        log_f.write(line + "\n")
        log_f.flush()
    log(f"probe: {len(sample)} bodies sampled from {len(bodies)} lever bodies ({len({b['nhash'] for b in bodies.values() if b['sites']})} distinct classes); seed {seed}")
    # group by the FILE that gets written (a TU, or a header) — one worker per file
    by_file = collections.defaultdict(list)
    for b in sample:
        by_file[b["tu"]].append(b)

    def work(tu):
        out = []
        if tu.endswith(".h"):
            tus = [t for t in inc.get(tu, []) if ("build/" + t[:-2] + ".o") in recipes]
            if not tus:
                return [dict(tu=tu, fn=b["fn"], verdict="NO-INCLUDER-RECIPE") for b in by_file[tu]]
            recipe = recipes["build/" + tus[0][:-2] + ".o"]
            write_path = tu
        else:
            obj = "build/" + tu[:-2] + ".o"
            if obj not in recipes:
                return [dict(tu=tu, fn=b["fn"], verdict="NO-RECIPE") for b in by_file[tu]]
            recipe = recipes[obj]
            write_path = None
        path = REPO / tu
        raw = path.read_text(errors="surrogateescape")
        m = same_len_mask(raw)
        ls = line_starts(raw)
        try:
            for b in by_file[tu]:
                out.append(run_body(b, recipe, write_path, raw, m, ls, log))
        finally:
            path.write_text(raw, errors="surrogateescape")
        return out
    results = []
    t0 = time.time()
    # phase 1: translation units, one worker per TU (no two candidates of one file at once, and no header is being edited);
    # phase 2: shared headers, SERIAL — a header's edit reaches every includer, so nothing else may compile meanwhile
    # (the dry run's three "compile errors" were two workers' candidates crossing inside one includer)
    tu_files = sorted(f for f in by_file if not f.endswith(".h"))
    hdr_files = sorted(f for f in by_file if f.endswith(".h"))
    with ThreadPoolExecutor(max_workers=jobs) as ex:
        for r in ex.map(work, tu_files):
            results.extend(r)
    for f in hdr_files:
        results.extend(work(f))
    wall = time.time() - t0
    with open(PROBE / "probe_results.jsonl", "w") as f:
        for r in results:
            f.write(json.dumps(r) + "\n")
    summary = summarize(results, bodies, wall, seed)
    (PROBE / "probe_summary.json").write_text(json.dumps(summary, indent=1) + "\n")
    (PROBE / "probe_table.md").write_text(render(summary) + "\n")
    print(render(summary))
    return summary


def summarize(results, bodies, wall, seed):
    judged = [r for r in results if r.get("verdict") in ("LEVER-FREE", "RESIDUE")]
    def pct(a, b):
        return round(100.0 * a / b, 1) if b else None
    by_kind = {}
    for k in ("main", "resident", "md", "shared", "ov"):
        rs = [r for r in judged if r["kind"] == k]
        if not rs:
            continue
        by_kind[k] = dict(bodies=len(rs), A_identical=sum(1 for r in rs if r["rung_A"] == "IDENTICAL"),
                          A_keep_register_identical=sum(1 for r in rs if r.get("rung_A_keep_register") == "IDENTICAL"),
                          lever_free=sum(1 for r in rs if r["verdict"] == "LEVER-FREE"),
                          sites=sum(r["n_usable"] for r in rs), removed=sum(len(r["removed"]) for r in rs), needed=sum(len(r["needed"]) for r in rs),
                          compiles=sum(r["compiles"] for r in rs), mean_s_per_compile=round(sum(r["seconds"] for r in rs) / max(sum(r["compiles"] for r in rs), 1), 3))
    needed_kinds = collections.Counter(n["kind"] for r in judged for n in r["needed"])
    needed_detail = collections.Counter(f"{n['kind']}:{n['detail']}" for r in judged for n in r["needed"])
    removed_kinds = collections.Counter(x["kind"] for r in judged for x in r["removed"])
    refused = collections.Counter(x["why"].split(":")[0][:60] for r in results for x in r.get("refused", []))
    sites_total = sum(r["n_usable"] for r in judged)
    sites_needed = sum(len(r["needed"]) for r in judged)
    flags = {}
    for flag in ("zero", "init", "instr", "cast", "register", "launder", "barrier", "keepalive", "volatile"):
        rs = [r for r in judged if r["features"].get(flag)]
        flags[flag] = dict(bodies=len(rs), lever_free=sum(1 for r in rs if r["verdict"] == "LEVER-FREE"))
    pop_bodies = sum(1 for b in bodies.values() if b["sites"])
    pop_sites = sum(len(b["sites"]) for b in bodies.values())
    mean_compiles = sum(r["compiles"] for r in judged) / max(len(judged), 1)
    mean_s = sum(r["seconds"] for r in judged) / max(sum(r["compiles"] for r in judged), 1)
    return dict(generated=time.strftime("%Y-%m-%d %H:%M"), seed=seed, sampled=len(results), judged=len(judged),
                not_judged=collections.Counter(r.get("verdict") for r in results if r not in judged),
                rung_A_identical=sum(1 for r in judged if r["rung_A"] == "IDENTICAL"),
                rung_A_keep_register_identical=sum(1 for r in judged if r.get("rung_A_keep_register") == "IDENTICAL"),
                lever_free_after_B=sum(1 for r in judged if r["verdict"] == "LEVER-FREE"),
                sites=dict(total=sites_total, removed=sites_total - sites_needed, needed=sites_needed, pct_removed=pct(sites_total - sites_needed, sites_total)),
                needed_by_kind=dict(needed_kinds), needed_by_detail=dict(needed_detail.most_common(30)), removed_by_kind=dict(removed_kinds),
                refused=dict(refused), by_kind=by_kind, flags=flags,
                compiles=sum(r["compiles"] for r in judged), mean_compiles_per_body=round(mean_compiles, 2), mean_s_per_compile=round(mean_s, 3),
                wall_s=round(wall, 1),
                population=dict(bodies=pop_bodies, sites=pop_sites),
                pricing=dict(T4_compiles_est=int(pop_bodies * mean_compiles), T4_cpu_hours_est=round(pop_bodies * mean_compiles * mean_s / 3600, 2),
                             T4_wall_hours_at_16_est=round(pop_bodies * mean_compiles * mean_s / 3600 / 12, 2),
                             residue_bodies_est=int(pop_bodies * (1 - (sum(1 for r in judged if r["verdict"] == "LEVER-FREE") / max(len(judged), 1)))),
                             residue_sites_est=int(pop_sites * (sites_needed / max(sites_total, 1)))))


def render(s):
    L = [f"# probe — {s['sampled']} bodies sampled, {s['judged']} judged (seed {s['seed']}, {s['generated']}, wall {s['wall_s']} s)", "",
         f"- rung A (strip-all) identical: **{s['rung_A_identical']} / {s['judged']}** (register dropped) · {s['rung_A_keep_register_identical']} with `register` kept",
         f"- lever-free after rung B: **{s['lever_free_after_B']} / {s['judged']}**",
         f"- sites: {s['sites']['total']} usable · removed {s['sites']['removed']} ({s['sites']['pct_removed']} %) · needed {s['sites']['needed']}",
         f"- needed by kind: {s['needed_by_kind']}", f"- needed by detail (top): {s['needed_by_detail']}",
         f"- removed by kind: {s['removed_by_kind']}", f"- refused (rewrite not applicable): {s['refused']}",
         f"- compiles {s['compiles']} · mean {s['mean_compiles_per_body']} per body · {s['mean_s_per_compile']} s per compile", "",
         "| kind | bodies | A identical | A (register kept) | lever-free after B | sites | removed | needed | compiles | s/compile |", "|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|"]
    for k, v in s["by_kind"].items():
        L.append(f"| {k} | {v['bodies']} | {v['A_identical']} | {v['A_keep_register_identical']} | {v['lever_free']} | {v['sites']} | {v['removed']} | {v['needed']} | {v['compiles']} | {v['mean_s_per_compile']} |")
    L += ["", "| feature | bodies | lever-free |", "|---|---:|---:|"]
    for k, v in s["flags"].items():
        L.append(f"| {k} | {v['bodies']} | {v['lever_free']} |")
    p = s["pricing"]
    L += ["", f"**Pricing (R41; population {s['population']['bodies']:,} lever bodies / {s['population']['sites']:,} removable sites):** "
          f"T4 ≈ {p['T4_compiles_est']:,} compiles ≈ {p['T4_cpu_hours_est']} CPU-h ≈ {p['T4_wall_hours_at_16_est']} h wall at 12 workers; "
          f"residue after the mechanical ladder ≈ {p['residue_bodies_est']:,} bodies / {p['residue_sites_est']:,} sites (the sample's rates applied to the population)."]
    return "\n".join(L)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--probe", action="store_true")
    ap.add_argument("--sample", type=int, default=150)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("-j", "--jobs", type=int, default=12)
    a = ap.parse_args()
    if a.probe:
        probe(a.sample, a.seed, a.jobs)
        return
    ap.print_help()


if __name__ == "__main__":
    main()
