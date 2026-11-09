#!/usr/bin/env python3
"""rename_scan.py — every mention of a renamed symbol, accounted for; and the names ledger, validated.

docs/gen3-standards.md §2 rule 1: every name carries evidence; a best guess is named `guess_<X>` with a
row in config/names.tsv (basis, confidence, evidence kind, conflict, history). This tool keeps both halves:

  --spec <tsv> | --range A..B   scan: one `git grep -n -I` over tracked text for the union of every rename's
                                candidate forms (old name, func_/D_<addr>, 0x<addr>, bare <addr>); every hit
                                gets exactly one class (R32: candidates == classified, asserted):
                                  history            path under HISTORY (dated records; never rewritten)
                                  rewritten          the line also carries the new name
                                  stale-build-input  old name / func_ / D_ form in a build input -> breaks a build
                                  stale-invisible    old name / func_ / D_ form anywhere else -> a stale doc
                                  unclassified       only a bare / 0x address, no new name -> a human looks
                                exit 1 on any stale or unclassified hit. Spec TSV: old<TAB>new<TAB>addr|-.
                                --range: per config/symbols*.txt, a name removed and another added at the same
                                address in `git diff A B` (B empty = the working tree).
  --ledger [--gate-citations]   validate config/names.tsv; gate guess_-without-basis and dead rows; print the
                                curated names with no citation row (gated only with --gate-citations).
  --selftest                    in-memory fixtures for classify() and check_ledger(); no repo, no temp dir.

Symbol files are read through tools/lint_symbol_refs.py (iter_symbol_defs, _symbol_files): one parser.
"""
import argparse, os, re, subprocess, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import lint_symbol_refs as lsr      # the ONE symbol-file parser and the stale func_<ADDR> checker

REPO = lsr.REPO
NAMES_TSV = "config/names.tsv"
COLUMNS = ("name", "kind", "scope", "addr", "tier", "basis", "confidence", "evidence", "conflict",
           "history", "citation")
KINDS = ("func", "data", "type", "field", "local")
TIERS = ("cited", "guess")
CONFIDENCE = ("low", "medium", "high")
# Rule 1's six evidence kinds. Adding one is a developer amendment of rule 1, not a tool edit.
EVIDENCE = ("code inference", "string", "xref chain", "debug menu", "live RAM", "community label")
HISTORY = ("cookbook/", "phase-ends/", "docs/decision-log.md", "docs/story.md", "docs/retrospective.md",
           "docs/retired/", "docs/research-archive/", ".claude-state/",
           ".run/")                                # tracked raw logs / generated census output: never hand-edited
BUILD_INPUTS = ("src/", "include/", "config/symbols", "config/splat.", "Makefile", "config/undefined_")
CLASSES = ("history", "rewritten", "stale-build-input", "stale-invisible", "unclassified")
PLACEHOLDER = re.compile(r'^(?:func|D|jtbl|L|sym|jpt|lbl)_[0-9A-Fa-f]{6,8}$')
GUESS_TOKEN = re.compile(r'\bguess_\w+')


# ---------------------------------------------------------------- scan (pure core)
def _ci(hexs):
    """ERE/Python-re common: each hex letter as [aA]."""
    return "".join("[%s%s]" % (c.lower(), c.upper()) if c.isalpha() else c for c in hexs)


def rename_forms(old, new, addr):
    """-> (strong pattern, weak pattern or None). strong = old name / func_ / D_ forms; weak = 0x / bare hex.
    Both are valid as git-grep ERE and as Python re."""
    strong = [r"\b%s\b" % re.escape(old)]
    weak = []
    if addr not in ("-", ""):
        h = addr.lower()
        h = h[2:] if h.startswith("0x") else h
        h0 = h.lstrip("0") or "0"
        digits = [h0.rjust(n, "0") for n in (6, 7, 8) if len(h0) <= n]
        if digits:
            alt = "|".join(_ci(d) for d in digits)
            strong.append(r"\b(func_|D_)(%s)\b" % alt)
            weak.append(r"\b(%s)\b" % alt)
        weak.append(r"\b0[xX]0*%s\b" % _ci(h0))
    return "|".join(strong), ("|".join(weak) or None)


def _class_of(path, text, new_re, strong):
    if path.startswith(HISTORY):
        return "history"
    if new_re.search(text):
        return "rewritten"
    if strong:
        build = path.startswith(BUILD_INPUTS) or re.match(r"config/[^/]+\.mk$", path)
        return "stale-build-input" if build else "stale-invisible"
    return "unclassified"


def classify(hits, rename):
    """hits = [(path, line, text)]; rename = (old, new, addr). Pure. -> {class: [hit]} over the hits that
    carry one of this rename's candidate forms; asserts candidates == classified."""
    old, new, addr = rename
    s, w = rename_forms(old, new, addr)
    s_re, w_re = re.compile(s), (re.compile(w) if w else None)
    new_re = re.compile(r"\b%s\b" % re.escape(new))
    out = {c: [] for c in CLASSES}
    cand = 0
    for h in hits:
        strong = bool(s_re.search(h[2]))
        if not strong and not (w_re and w_re.search(h[2])):
            continue
        cand += 1
        out[_class_of(h[0], h[2], new_re, strong)].append(h)
    assert cand == sum(len(v) for v in out.values()), "R32: candidates != classified"
    return out


def scan(hits, renames):
    """Pure. -> (per-rename results, grand class counts); asserts every hit belongs to some rename."""
    results, total, owned = [], {c: 0 for c in CLASSES}, set()
    for r in renames:
        res = classify(hits, r)
        for c in CLASSES:
            total[c] += len(res[c])
            owned.update(res[c])
        results.append((r, res))
    assert owned == set(hits), "R32: %d grep hit(s) matched no rename" % len(set(hits) - owned)
    return results, total


def _git(*args):
    p = subprocess.run(("git",) + args, cwd=REPO, capture_output=True, text=True, errors="replace")
    if p.returncode not in (0, 1):
        sys.exit("[rename_scan] git %s failed: %s" % (args[0], p.stderr.strip()))
    return p.stdout


def grep_hits(renames, rev=None):
    pats = []
    for old, new, addr in renames:
        s, w = rename_forms(old, new, addr)
        pats += ["-e", s] + (["-e", w] if w else [])
    out = _git("grep", "-n", "-I", "-E", *pats, *([rev] if rev else []))
    hits = []
    for ln in out.splitlines():
        if rev and ln.startswith(rev + ":"):
            ln = ln[len(rev) + 1:]
        path, lno, text = ln.split(":", 2)
        hits.append((path, int(lno), text))
    return sorted(set(hits))


def renames_from_range(a, b):
    return renames_from_diff(_git("diff", "--no-color", "-U0", a, *([b] if b else []), "--", "config/symbols*.txt"))


def renames_from_diff(diff):
    """Pure. A removed+added name at one (file, addr) is a rename; an added name with nothing removed there is a
    first naming of the splat auto-name (old = func_/D_<ADDR>, `// data` -> D_), which has no line of its own."""
    per = {}                                   # (file, addr) -> [removed names, added names]
    kind = {}                                  # added name -> "D_" | "func_"
    path = None
    for ln in diff.splitlines():
        if ln.startswith("+++ "):
            path = ln[6:] if ln.startswith("+++ b/") else path
        elif ln.startswith("--- ") or not path:
            continue
        elif ln[:1] in "+-":
            for nm, ad in lsr.iter_symbol_defs(ln[1:]):
                per.setdefault((path, ad), [set(), set()])[0 if ln[0] == "-" else 1].add(nm)
                kind[nm] = "D_" if re.search(r"//\s*data\b", ln) else "func_"
    out = set()
    for (_, ad), (rm, ad_) in sorted(per.items()):
        rm, ad_ = rm - ad_, ad_ - rm
        if not rm:
            h = ad.lower()[2:] if ad.lower().startswith("0x") else ad.lower()
            for n in sorted(ad_):
                if not PLACEHOLDER.match(n):
                    out.add((kind[n] + h.upper().rjust(8, "0"), n, ad))
        for o, n in zip(sorted(rm), sorted(ad_)):
            out.add((o, n, ad))
    return sorted(out)


def renames_from_spec(p):
    out = []
    for ln in open(p):
        if not ln.strip() or ln.startswith("#"):
            continue
        f = ln.rstrip("\n").split("\t")
        if len(f) != 3:
            sys.exit("[rename_scan] spec row needs old<TAB>new<TAB>addr: %r" % ln)
        out.append(tuple(f))
    return sorted(out)


def run_scan(renames, rev):
    if not renames:
        print("[rename_scan] no renames")
        return 0
    results, total = scan(grep_hits(renames, rev), renames)
    print("[rename_scan] %d rename(s); %s" % (len(renames), ", ".join("%s %d" % (c, total[c]) for c in CLASSES)))
    for (old, new, addr), res in results:
        for c in CLASSES[2:]:
            for path, lno, _ in res[c]:
                print("  %s  %s:%d  %s -> %s (%s)" % (c, path, lno, old, new, addr))
    bad = total["stale-build-input"] + total["stale-invisible"] + total["unclassified"]
    print("[rename_scan] %s" % ("FAIL: %d stale/unclassified hit(s)" % bad if bad else "OK"))
    return 1 if bad else 0


# ---------------------------------------------------------------- ledger (pure core)
def _base(name):
    return name.rsplit(".", 1)[-1]


def check_ledger(rows, symbols, tokens):
    """rows = [dict per COLUMNS]; symbols = {name: set(aliases)} from the stacked symbol files;
    tokens = [(path, token)]: every guess_ token in src/ include/ config/symbols*.txt and every ledger
    type/field/local name found word-bounded in src/ include/. Pure.
    -> {errors, guess_without_basis, dead, curated_without_citation} (sorted lists)."""
    aliases = set().union(*symbols.values()) if symbols else set()
    errors, seen, based = [], set(), set()
    src_words = {t for p, t in tokens if p.startswith(("src/", "include/"))}
    dead = []
    for i, r in enumerate(rows, 1):
        bad = []
        nm, kind, scope, addr, tier = r["name"], r["kind"], r["scope"], r["addr"], r["tier"]
        if kind not in KINDS: bad.append("kind")
        if tier not in TIERS: bad.append("tier")
        if (tier == "guess") != _base(nm).startswith("guess_"): bad.append("tier/guess_ prefix")
        if tier == "guess":
            if not r["basis"] or r["basis"] == "-": bad.append("basis")
            if r["confidence"] not in CONFIDENCE: bad.append("confidence")
            if r["evidence"] not in EVIDENCE: bad.append("evidence")
        else:
            if r["citation"] in ("", "-"): bad.append("citation")
            if r["confidence"] not in CONFIDENCE + ("-",): bad.append("confidence")
            if r["evidence"] not in EVIDENCE + ("-",): bad.append("evidence")
        if kind in ("func", "data"):
            if not re.match(r"^0x[0-9A-Fa-f]+$", addr): bad.append("addr")
            if scope != "global" and scope not in aliases: bad.append("scope")
        elif addr != "-":
            bad.append("addr")
        for col in ("conflict", "history", "citation", "scope"):
            if not r[col]: bad.append(col)
        if (nm, scope) in seen: bad.append("duplicate (name, scope)")
        seen.add((nm, scope))
        if bad:
            errors.append("row %d %s: %s" % (i, nm, ", ".join(bad)))
            continue
        if r["basis"] not in ("", "-"):
            based.add(_base(nm))
        live = nm in symbols if kind in ("func", "data") else _base(nm) in src_words
        if not live:
            dead.append("%s (%s, %s)" % (nm, kind, scope))
    gwb = sorted({t for _, t in tokens if t.startswith("guess_")} - based)
    cited = {r["name"] for r in rows if r["citation"] not in ("", "-")}
    curated = sorted(n for n in symbols if not PLACEHOLDER.match(n) and not n.startswith("guess_")
                     and n not in cited)
    return {"errors": errors, "guess_without_basis": gwb, "dead": sorted(dead),
            "curated_without_citation": curated}


def parse_ledger(text):
    rows, header = [], None
    for ln in text.splitlines():
        if not ln.strip() or ln.startswith("#"):
            continue
        f = ln.split("\t")
        if header is None:
            if tuple(f) != COLUMNS:
                sys.exit("[rename_scan] %s header must be: %s" % (NAMES_TSV, "\\t".join(COLUMNS)))
            header = f
            continue
        if len(f) != len(COLUMNS):
            sys.exit("[rename_scan] %s row has %d fields, needs %d: %r" % (NAMES_TSV, len(f), len(COLUMNS), ln))
        rows.append(dict(zip(COLUMNS, f)))
    return rows


def _alias(path):
    b = os.path.basename(path)
    return b[len("symbols."):-len(".txt")]


def load_symbol_names():
    out = {}
    for p in lsr._symbol_files():
        for nm, _ in lsr.iter_symbol_defs(open(p).read()):
            out.setdefault(nm, set()).add(_alias(p))
    return out


def load_tokens(rows):
    toks = set()
    out = _git("grep", "-o", "-I", "-E", r"\bguess_\w+", "--", "src", "include", "config/symbols*.txt")
    for ln in out.splitlines():
        p, t = ln.split(":", 1)
        toks.add((p, t))
    words = sorted({_base(r["name"]) for r in rows if r["kind"] in ("type", "field", "local")})
    if words:
        pats = [a for w in words for a in ("-e", w)]
        out = _git("grep", "-o", "-I", "-w", "-F", *pats, "--", "src", "include")
        for ln in out.splitlines():
            p, t = ln.split(":", 1)
            toks.add((p, t))
    return sorted(toks)


def run_ledger(gate_citations):
    rows = parse_ledger(open(os.path.join(REPO, NAMES_TSV)).read())
    symbols = load_symbol_names()
    res = check_ledger(rows, symbols, load_tokens(rows))
    for e in res["errors"]:
        print("  invalid " + e)
    for t in res["guess_without_basis"]:
        print("  guess_ without basis: " + t)
    for d in res["dead"]:
        print("  dead row: " + d)
    print("[rename_scan] ledger rows: %d; invalid rows: %d" % (len(rows), len(res["errors"])))
    print("guess_ without basis: %d" % len(res["guess_without_basis"]))
    print("dead rows: %d" % len(res["dead"]))
    print("curated without citation: %d  (unique names in the %d stacked config/symbols*.txt, proto excluded)"
          % (len(res["curated_without_citation"]), len(lsr._symbol_files())))
    bad = len(res["errors"]) + len(res["guess_without_basis"]) + len(res["dead"])
    if gate_citations:
        bad += len(res["curated_without_citation"])
    print("[rename_scan] ledger %s" % ("FAIL" if bad else "OK"))
    return 1 if bad else 0


# ---------------------------------------------------------------- selftest
def selftest():
    R = ("func_80037004", "guess_ClearTbl", "0x80037004")
    def scan_ok(hits):
        _, t = scan(hits, [R])
        assert sum(t.values()) == len(set(hits)), t
        return t["stale-build-input"] + t["stale-invisible"] + t["unclassified"] == 0, t
    clean = [("config/symbols.us.txt", 5, "guess_ClearTbl = 0x80037004; // func"),
             ("src/main/a.c", 9, "    guess_ClearTbl(); /* was func_80037004 */")]
    ok, t = scan_ok(clean); assert ok and t["rewritten"] == 2, t
    build = clean + [("src/main/b.c", 3, "    func_80037004();")]
    ok, t = scan_ok(build); assert not ok and t["stale-build-input"] == 1, t
    st = lsr.stale_refs({"0x80037004": "guess_ClearTbl"}, set(), [("src/main/b.c", "void f(void){\n    func_80037004();\n}\n")])
    assert [(s[0], s[1], s[2]) for s in st] == [("src/main/b.c", 2, "func_80037004")], st
    ok, t = scan_ok(clean + [("docs/memory-map.md", 40, "| func_80037004 | clears the table |")])
    assert not ok and t["stale-invisible"] == 1, t
    ok, t = scan_ok(clean + [("phase-ends/P30/log.md", 1, "renamed func_80037004 today"),
                             ("cookbook/C0001.md", 2, "see 0x80037004")])
    assert ok and t["history"] == 2, t
    ok, t = scan_ok(clean + [("docs/memory-map.md", 41, "0x80037004 table clear")])
    assert not ok and t["unclassified"] == 1, t
    P = ("D_037004", "guess_Pad", "0x37004")                            # zero-padding / case forms
    ph = [("src/x.c", 1, "D_0037004 = 1;"), ("src/y.c", 2, "func_00037004();"), ("tools/z.py", 3, "0X37004"),
          ("docs/a.md", 4, "37004 and 0x0037004"), ("src/w.c", 5, "D_800370041; x037004")]
    _, t = scan([h for h in ph if h[0] != "src/w.c"], [P])
    assert t["stale-build-input"] == 2 and t["unclassified"] == 2, t
    try:                                                                # R32: a hit no rename owns is an error
        scan(ph, [P]); raise SystemExit("selftest: unowned hit not caught")
    except AssertionError:
        pass
    d = ("+++ b/config/symbols.us.txt\n-OldA = 0x80010000; // func\n+NewA = 0x80010000; // func\n"
         "+guess_Tbl = 0x80076251; // data\n+guess_Fn = 0x8003700C; // func\n+func_80040000 = 0x80040000; // func\n")
    assert renames_from_diff(d) == [("D_80076251", "guess_Tbl", "0x80076251"), ("OldA", "NewA", "0x80010000"),
                                    ("func_8003700C", "guess_Fn", "0x8003700c")], renames_from_diff(d)
    # ledger
    sym = {"func_80037004": {"us"}, "guess_ClearTbl": {"us"}, "InitHeap": {"us"}, "D_80012340": {"us"},
           "SysEnqIntRP": {"ov_SC02_003"}}
    row = dict(zip(COLUMNS, ("guess_ClearTbl", "func", "us", "0x80037004", "guess", "zeroes 0x40 words",
                             "medium", "code inference", "-", "func_80037004", "-")))
    cit = dict(zip(COLUMNS, ("InitHeap", "func", "us", "0x80030000", "cited", "-", "-", "-", "-", "-",
                             "docs/memory-map.md:12")))
    toks = [("src/main/a.c", "guess_ClearTbl")]
    r = check_ledger([row, cit], sym, toks)
    assert not r["errors"] and not r["guess_without_basis"] and not r["dead"], r
    assert r["curated_without_citation"] == ["SysEnqIntRP"], r
    r = check_ledger([cit], sym, toks)
    assert r["guess_without_basis"] == ["guess_ClearTbl"], r            # guess_ with no basis row
    r = check_ledger([row, cit, dict(row, name="guess_Gone", history="-")], sym, toks)
    assert r["dead"] == ["guess_Gone (func, us)"], r                    # dead ledger row
    fld = dict(row, name="Obj.guess_hp", kind="field", scope="Obj", addr="-", history="-")
    r = check_ledger([row, fld], sym, toks)
    assert r["dead"] == ["Obj.guess_hp (field, Obj)"], r
    r = check_ledger([row, fld], sym, toks + [("include/obj.h", "guess_hp")])
    assert not r["dead"] and not r["errors"], r
    for bad in (dict(row, tier="cited"), dict(row, basis="-"), dict(row, confidence="sure"),
                dict(row, evidence="hunch"), dict(cit, citation="-"), dict(row, kind="macro"),
                dict(row, scope="ov_NOPE"), dict(fld, addr="0x1")):
        assert check_ledger([bad], sym, toks)["errors"], bad
    assert check_ledger([row, row], sym, toks)["errors"], "duplicate (name, scope)"
    print("[rename_scan] selftest OK")
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--selftest", action="store_true")
    g.add_argument("--ledger", action="store_true")
    g.add_argument("--spec", metavar="TSV", help="old<TAB>new<TAB>addr|- rows")
    g.add_argument("--range", metavar="A..B", help="renames in config/symbols*.txt between A and B (B empty = worktree)")
    ap.add_argument("--gate-citations", action="store_true", help="with --ledger: fail on curated names with no citation row")
    a = ap.parse_args()
    if a.selftest:
        return selftest()
    if a.ledger:
        return run_ledger(a.gate_citations)
    if a.spec:
        return run_scan(renames_from_spec(a.spec), None)
    lo, _, hi = a.range.partition("..")
    return run_scan(renames_from_range(lo, hi or None), hi or None)


if __name__ == "__main__":
    sys.exit(main())
