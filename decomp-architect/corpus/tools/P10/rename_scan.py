#!/usr/bin/env python3
"""rename_scan.py — every mention of a renamed symbol, accounted for; and the names ledger, validated.

docs/gen3-standards.md §2 rule 1: every name carries evidence; a best guess is named `guess_<X>` with a
row in config/names.tsv (basis, confidence, evidence kind, conflict, history). This tool keeps both halves:

  --spec <tsv> | --range A..B   scan: `git grep -n -I` (one joined -e per 32 renames, wall-bounded) for the union of every rename's
                                candidate forms (old name, func_/D_<addr>, 0x<addr>, bare <addr>); every hit
                                gets exactly one class (R32: candidates == classified, asserted):
                                  history            path under HISTORY (dated records; never rewritten)
                                  rewritten          the line also carries the new name
                                  other-binary       (wide spec) a strong hit in a src/ or symbol file whose
                                                     binaries are disjoint from the rename's scope (the binaries
                                                     stacking its row's symbol file): another function; or a line
                                                     whose every strong token is qualified by an object id
                                                     `src/<dir>/...:<token>` mapping out of scope; or a line that
                                                     itself names another entity (_other_entity: other-kind
                                                     placeholder, out-of-scope dedup member / lever_residue row,
                                                     leverage.tsv row of another kind or hash, type_folds.tsv
                                                     owner note whose target type only out-of-scope src uses). Passes.
                                  address-key        (a) the only candidate token is a share header's name
                                                     `func_<ADDR>(__x)?.h` (headers are named by vram, never
                                                     renamed); (b) a 0x / bare address in an ADDRESS_KEYED
                                                     path (keyed by vram on purpose). Passes.
                                  stale-build-input  old name / func_ / D_ form in a build input -> breaks a build
                                  stale-invisible    old name / func_ / D_ form anywhere else -> a stale doc
                                  unclassified       only a bare / 0x address, no new name -> a human looks
                                exit 1 on any stale or unclassified hit. Spec TSV: old<TAB>new<TAB>addr|-,
                                or tools/rename_sym.py's wider spec (header line; first 3 columns used;
                                a `class:<id>` binary expands to its registry members like rename_sym).
                                -v prints every classified hit (path:line class).
                                --range: per config/symbols*.txt, a name removed and another added at the same
                                address in `git diff A B` (B empty = the working tree).
  --ledger [--gate-citations]   validate config/names.tsv; gate guess_-without-basis and dead rows; print the
                                curated names with no citation row (gated only with --gate-citations).
                                A `class:<id>` scope is ONE row per registry class; it stands for name and
                                name_<k> (same-binary members) for dead / basis / citation.
  --worklist FILE [--complete]  check config/names_worklist.tsv: a `# ... source: <path> @ <commit>` header line;
                                disposition empty (undisposed) | cited | guess | no-evidence. cited/guess: new_name
                                (guess iff guess_), every instance (func: .run/sig.<alias>.jsonl rows of h_exact;
                                data: space -> binary, vram = addr) resolves through its binary's splat symbol
                                stack to new_name[_<k>] and has a names.tsv row of that tier ((name, file alias)
                                or a class:<id> row holding it). no-evidence: new_name = the placeholder name,
                                no instance named, a reason. Prints counts and each bad row; exit 1 on any,
                                and with --complete on any undisposed row.
  --selftest                    in-memory fixtures for classify(), check_ledger(), check_worklist() and
                                rename_sym's planner (prepare); no repo, no temp dir.

Symbol files are read through tools/lint_symbol_refs.py (iter_symbol_defs, _symbol_files): one parser.
"""
import argparse, glob, os, re, subprocess, sys, time

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
EVIDENCE = ("code inference", "string", "xref chain", "debug menu", "live RAM", "community label",
            "library symbol")
HISTORY = ("cookbook/", "phase-ends/", "docs/decision-log.md", "docs/story.md", "docs/retrospective.md",
           "docs/retired/", "docs/research-archive/", ".claude-state/",
           "decomp-architect/corpus/record/", "decomp-architect/corpus/cookbook/",   # verbatim kit copies of the above
           "config/names_worklist.tsv",            # 3.43's frozen worklist: placeholder names kept as frozen
           "config/names.tsv",                     # the ledger: basis/citation quote names as at naming time (3.43 T7)
           ".run/")                                # tracked raw logs / generated census output: never hand-edited
BUILD_INPUTS = ("src/", "include/", "config/symbols", "config/splat.", "Makefile", "config/undefined_")
CLASSES = ("history", "rewritten", "address-key", "other-binary", "stale-build-input", "stale-invisible",
           "unclassified")
BAD = ("stale-build-input", "stale-invisible", "unclassified")
# Closed list: paths whose 0x / bare address mentions are keyed by vram ON PURPOSE (a strong hit there stays
# stale). Kit copies decomp-architect/corpus/tools/<P>/<x> of a listed tools/<x> count as listed.
ADDRESS_KEYED = {
    "tools/share_census.py": "coverage asserts find share classes by vram (`0x... in c['addrs']`), never by name",
    "docs/duplicates.cross.md": "dup_report --cross lists group members as binary:vram, no names",
    "docs/duplicates.md": "dup_report lists each group's representative as `<sig name> (<vram>)`; see NAMES_FROM_VRAM",
    "docs/leverage.md": "leverage_rank lists one row per unit keyed by space:addr",
    "docs/leverage.tsv": "leverage_rank writes one row per unit keyed by space:addr",
    "config/dedup.us.yaml": "the registry keys each group by `vram:` (and member vram); its name is the `func:`/`name:` field",
    "docs/struct-twins.md": "## Twins is generated (struct_twins.py --write, no hand edits): objects keyed binary/vram:var, "
                            "structs S<vram>",
}
# Closed list: generated files rename_sym rewrites as text instead of printing `regenerate:` (shared with rename_sym).
TEXT_GENERATED = {
    "docs/leverage.md": "rewritten as text; regenerated once at the 3.43 close, T15",
    "docs/leverage.tsv": "rewritten as text; regenerated once at the 3.43 close, T15",
}
# config/names_worklist.tsv: the frozen naming worklist --worklist checks (3.43).
WORKLIST_TSV = "config/names_worklist.tsv"
WORKLIST_COLS = ("rank43", "kind", "key", "h_exact", "space", "addr", "name", "refs", "fan", "binaries", "owner",
                 "instances", "group", "target", "disposition", "new_name", "reason")
DISPOSITIONS = ("cited", "guess", "no-evidence")
SOURCE_RE = re.compile(r"\bsource:\s*\S+\s*@\s*[0-9a-fA-F]{7,40}\b")
DATA_SPACE = {"8000F800": "main", "800CEDF8": "resident", "abs": "main"}   # data unit space -> binary
# Closed sub-list: generated files whose func_/D_<ADDR> tokens are synthesized from the vram by their generator, so they
# are placeholders, never a curated name a rename could miss (a curated old name there still counts as strong -> stale).
NAMES_FROM_VRAM = {
    "docs/duplicates.md": "names from .run/sig.main.jsonl: main's seeds carry no names (tools/main_seed_ends.py:4), "
                          "so sig_image names every function func_<vram> (tools/sig_image.py:200)",
}
VRAM_NAME = re.compile(r'\b(?:func|D)_[0-9A-Fa-f]{6,8}\b')
HEADER_TOKEN = re.compile(r'\b(?:func|D)_[0-9A-Fa-f]{6,8}(?:__\w+)?\.h\b')   # share headers: named by vram
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


def _address_keyed(path):
    m = re.match(r"decomp-architect/corpus/tools/[^/]+/(.+)$", path)
    return path in ADDRESS_KEYED or bool(m and "tools/" + m.group(1) in ADDRESS_KEYED)


def _class_of(path, text, new_re, s_re, w_re):
    if path.startswith(HISTORY):
        return "history"
    if new_re.search(text):
        return "rewritten"
    bare = HEADER_TOKEN.sub(" ", text)
    if path in NAMES_FROM_VRAM:
        bare = VRAM_NAME.sub(" ", bare)               # generator-made placeholders: address keys, not names
    strong = bool(s_re.search(bare))
    if s_re.search(text) and not strong and not (w_re and w_re.search(bare)):
        return "address-key"                           # (a) only a share header's file name / a vram-made name
    if not strong and _address_keyed(path):
        return "address-key"                           # (b) weak hit in a vram-keyed path
    if strong:
        build = path.startswith(BUILD_INPUTS) or re.match(r"config/[^/]+\.mk$", path)
        return "stale-build-input" if build else "stale-invisible"
    return "unclassified"


OBJ_ID = re.compile(r"(src/[\w./-]+):$")


def _qualified_out(text, s_re, scope, where):
    """True when every strong token on the line is qualified by an object id `src/<dir>/...:<token>` (struct-twins)
    whose path maps to binaries disjoint from scope; an unqualified, unmapped or in-scope occurrence -> False."""
    ms = list(s_re.finditer(text))
    for m in ms:
        q = OBJ_ID.search(text, 0, m.start())
        fb = where(q.group(1)) if q else set()
        if not fb or (fb & scope):
            return False
    return bool(ms)


MEMBER_BIN = re.compile(r"^\s*-\s*\{\s*binary:\s*([\w.]+)\s*,")   # config/dedup.us.yaml: one member per line


OWNER_NOTE = "owner:"


def _other_entity(path, text, s_re, kind, scope, where, hashes, uses=None):
    """Scoped renames: -> the rule ('a'..'e') by which the line itself names ANOTHER entity at the address, else None.
    (a) every strong token is the other kind's placeholder (D_<addr> for a func rename, func_<addr> for data);
    (b) a config/dedup.us.yaml member line whose binary is out of scope; (c) a config/lever_residue.tsv row whose src
    path (column 1) maps out of scope; (d) a docs/leverage.tsv row, every strong token in its name column, of another
    kind, or a func row whose hash key prefixes none of hashes() (the rename's h_exact at its address in scope;
    empty -> no proof); (e) a config/type_folds.tsv row whose every strong token is an `owner:<token>` note and whose
    target type (column 3) uses(type) -> src paths finds only in files mapping out of scope (no src use -> no proof)."""
    other = {"func": "D_", "data": "func_"}.get(kind)
    ms = [m.group(0) for m in s_re.finditer(text)]
    if other and ms and all(VRAM_NAME.fullmatch(t) and t.startswith(other) for t in ms):
        return "a"
    if path == "config/dedup.us.yaml":
        m = MEMBER_BIN.match(text)
        if m and m.group(1) not in scope:
            return "b"
    elif path == "config/lever_residue.tsv":
        fb = where(text.split("\t", 1)[0])
        if fb and not (fb & scope):
            return "c"
    elif path == "docs/leverage.tsv":
        f = text.split("\t")
        if len(f) < 6 or not kind or any(s_re.search(c) for i, c in enumerate(f) if i != 5):
            return None
        if f[1] in ("func", "data") and f[1] != kind:
            return "d"
        if kind == f[1] == "func" and hashes:
            hs = hashes()
            if hs and not any(h.startswith(f[2]) for h in hs):
                return "d"
    elif path == "config/type_folds.tsv" and uses:
        f = text.split("\t")
        if len(f) < 3 or not ms or any(text[m.start() - len(OWNER_NOTE):m.start()] != OWNER_NOTE
                                       for m in s_re.finditer(text)):
            return None
        fbs = [where(u) for u in uses(f[2])]
        if fbs and all(fb and not (fb & scope) for fb in fbs):
            return "e"
    return None


def classify(hits, rename, scope=None, where=None, kind=None, hashes=None, uses=None):
    """hits = [(path, line, text)]; rename = (old, new, addr). Pure. -> {class: [hit]} over the hits that
    carry one of this rename's candidate forms; asserts candidates == classified. scope = the rename's binaries
    (wide spec) and where(path) -> a file's binaries (empty = unmapped): a stale (strong) hit in a mapped file
    whose binaries are disjoint from scope is `other-binary` (the token names another function there, C0571).
    kind = the rename's spec kind, hashes() -> its unit's h_exact set, uses(type) -> src paths using a type:
    for _other_entity's line-level rules."""
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
        c = _class_of(h[0], h[2], new_re, s_re, w_re)
        if scope is not None and c in ("stale-build-input", "stale-invisible"):
            fb = where(h[0])
            if fb and not (fb & scope):
                c = "other-binary"
            elif _qualified_out(h[2], s_re, scope, where):
                c = "other-binary"
            elif _other_entity(h[0], h[2], s_re, kind, scope, where, hashes, uses):
                c = "other-binary"
        out[c].append(h)
    assert cand == sum(len(v) for v in out.values()), "R32: candidates != classified"
    return out


def scan(hits, renames, scopes=None, where=None, kinds=None, hashes=None, uses=None):
    """Pure. -> (per-rename results, grand class counts); asserts every hit belongs to some rename.
    scopes = {rename: binaries} (wide specs) for classify's other-binary class; kinds = {rename: spec kind};
    hashes(rename) -> its unit's h_exact set; uses(type) -> the src paths using a type."""
    results, total, owned = [], {c: 0 for c in CLASSES}, set()
    for r in renames:
        res = classify(hits, r, scopes.get(r) if scopes else None, where, (kinds or {}).get(r),
                       (lambda r=r: hashes(r)) if hashes else None, uses)
        for c in CLASSES:
            total[c] += len(res[c])
            owned.update(res[c])
        results.append((r, res))
    assert owned == set(hits), "R32: %d grep hit(s) matched no rename" % len(set(hits) - owned)
    return results, total


def _git(*args, timeout=None):
    try:
        p = subprocess.run(("git",) + args, cwd=REPO, capture_output=True, text=True, errors="replace",
                           timeout=timeout)
    except subprocess.TimeoutExpired:
        sys.exit("[rename_scan] git %s exceeded its %d s wall-clock bound (GREP_WALL_S); "
                 "split the spec or raise the bound" % (args[0], timeout))
    if p.returncode not in (0, 1):
        sys.exit("[rename_scan] git %s failed: %s" % (args[0], p.stderr.strip()))
    return p.stdout


GREP_CHUNK = 32       # renames per git grep call
GREP_WALL_S = 1800    # wall-clock bound over all of grep_hits' git grep calls


def grep_chunks(renames, size=GREP_CHUNK):
    """Pure. -> one ERE per chunk of `size` renames: the chunk's strong/weak forms joined into ONE alternation.
    One -e, never one -e per form: git grep 2.43 with several -e patterns matched 669 MB / 20k files at 24 s for
    2 patterns and >60 s for 10 (B1's 96 ran 11 CPU-h); the same alternation as one -e is 6.9 s for 96 (T9.c4)."""
    out = []
    for i in range(0, len(renames), size):
        forms = []
        for old, new, addr in renames[i:i + size]:
            s, w = rename_forms(old, new, addr)
            forms += [s] + ([w] if w else [])
        out.append("|".join(forms))
    return out


def grep_hits(renames, rev=None):
    deadline, out = time.monotonic() + GREP_WALL_S, ""
    for pat in grep_chunks(renames):
        left = max(1, int(deadline - time.monotonic()))
        out += _git("grep", "-n", "-I", "-E", "-e", pat, *([rev] if rev else []), timeout=left)
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


def parse_spec(text, groups=None, stackers=None, scopes=None, kinds=None):
    """Pure. old<TAB>new<TAB>addr rows, or rename_sym's wide spec (header `old<TAB>new<TAB>addr<TAB>binary...`,
    first 3 columns used; a `class:<id>` binary expands through rename_sym.expand over groups). With stackers
    (rename_sym.stackers_of) and a scopes dict, a wide row's rename also gets its binary scope in scopes:
    {(old, new, addr): binaries stacking the row's symbol-file alias}, unioned (rename_sym.pair_scope); a kinds dict
    gets {(old, new, addr): the row's kind column}."""
    out, wide = [], False
    for ln in text.splitlines():
        if not ln.strip() or ln.startswith("#"):
            continue
        f = ln.split("\t")
        if f[:3] == ["old", "new", "addr"]:
            wide = True
            continue
        if len(f) != 3 and not (wide and len(f) > 3):
            sys.exit("[rename_scan] spec row needs old<TAB>new<TAB>addr: %r" % ln)
        if len(f) > 3 and f[3].startswith("class:"):
            import rename_sym
            exp = rename_sym.expand([{"old": f[0], "new": f[1], "addr": "0", "binary": f[3]}], groups or {})
            out += [(r["old"], r["new"], r["addr"]) for r in exp]
            if kinds is not None and len(f) > 4:
                kinds.update(((r["old"], r["new"], r["addr"]), f[4]) for r in exp)
            if scopes is not None:
                for r in exp:
                    scopes.setdefault((r["old"], r["new"], r["addr"]), set()).update(
                        rename_sym.pair_scope([r], stackers)[(r["old"], r["new"])])
            continue
        out.append(tuple(f[:3]))
        if kinds is not None and len(f) > 4:
            kinds[tuple(f[:3])] = f[4]
        if scopes is not None and len(f) > 3:
            import rename_sym
            scopes.setdefault(tuple(f[:3]), set()).update(
                rename_sym.pair_scope([{"old": f[0], "new": f[1], "binary": f[3]}], stackers)[(f[0], f[1])])
    # distinct renames only: a class row expands to one identical (old, new, addr) per member (141 for an overlay-base
    # class), and scan() classifies every hit once per rename; the verdict and the distinct bad hits are unchanged
    return sorted(set(out))


def renames_from_spec(p):
    """-> (renames, scopes, where, kinds, hashes, uses): all but renames None for a 3-column spec (no binary column).
    hashes(rename) -> the h_exact of every function at its address in its scope's .run/sig.<binary>.jsonl (lazy);
    uses(type) -> the src/ paths naming the type word-bounded (git grep, cached)."""
    text = open(p).read()
    if not any(ln.split("\t")[:3] == ["old", "new", "addr"] for ln in text.splitlines()):
        return parse_spec(text), None, None, None, None, None
    import json, rename_sym
    groups, reg = rename_sym.load_groups()
    stackers, aliases, scopes, kinds = rename_sym.stackers_of(symbol_stacks()), rename_sym._aliases(), {}, {}
    cache, hcache, ucache = {}, {}, {}
    def where(path):
        if path not in cache:
            cache[path] = rename_sym.file_binaries(path, reg, aliases, stackers)
        return cache[path]
    def hashes(r):
        if r not in hcache:
            hs = set()
            if re.fullmatch(r"(0[xX])?[0-9A-Fa-f]+", r[2]):
                pat = re.compile(r'"addr":"0x0*%x"' % int(r[2], 16))
                for b in sorted(scopes.get(r, ())):
                    for stem in (b, "SLUS_007.26") if b == "main" else (b,):
                        sp = os.path.join(REPO, ".run/sig.%s.jsonl" % stem)
                        for ln in (open(sp) if os.path.exists(sp) else ()):
                            if pat.search(ln):
                                hs.add(json.loads(ln)["h_exact"])
            hcache[r] = hs
        return hcache[r]
    def uses(t):
        if t not in ucache:
            ucache[t] = _git("grep", "-l", "-w", "-F", "-e", t, "--", "src/").split() if t else []
        return ucache[t]
    return parse_spec(text, groups, stackers, scopes, kinds), scopes, where, kinds, hashes, uses


def run_scan(renames, rev, verbose=False, scopes=None, where=None, kinds=None, hashes=None, uses=None):
    if not renames:
        print("[rename_scan] no renames")
        return 0
    results, total = scan(grep_hits(renames, rev), renames, scopes, where, kinds, hashes, uses)
    print("[rename_scan] %d rename(s); %s" % (len(renames), ", ".join("%s %d" % (c, total[c]) for c in CLASSES)))
    for (old, new, addr), res in results:
        if verbose:
            for path, lno, c in sorted((h[0], h[1], c) for c in CLASSES for h in res[c]):
                print("  %s:%d %s" % (path, lno, c))
        for c in BAD:
            for path, lno, _ in res[c]:
                print("  %s  %s:%d  %s -> %s (%s)" % (c, path, lno, old, new, addr))
    bad = sum(total[c] for c in BAD)
    print("[rename_scan] %s" % ("FAIL: %d stale/unclassified hit(s)" % bad if bad else "OK"))
    return 1 if bad else 0


# ---------------------------------------------------------------- ledger (pure core)
def _base(name):
    return name.rsplit(".", 1)[-1]


def _family(name):
    """-> a regex for name and its class-member forms name_<k> (rename_sym numbers same-binary members)."""
    return re.compile(r"%s(?:_\d+)?$" % re.escape(name))


def row_errors(r, aliases, groups):
    """One names row (dict per COLUMNS) -> [bad column]. aliases = symbol-file aliases (scope `us`, ...);
    groups = registry ids a `class:<id>` scope may name. Pure; shared with rename_sym's pre-write check."""
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
        if scope.startswith("class:"):
            if scope[len("class:"):] not in groups: bad.append("scope")
        elif scope != "global" and scope not in aliases: bad.append("scope")
    elif addr != "-":
        bad.append("addr")
    for col in ("conflict", "history", "citation", "scope"):
        if not r[col]: bad.append(col)
    return bad


def check_ledger(rows, symbols, tokens, groups=()):
    """rows = [dict per COLUMNS]; symbols = {name: set(aliases)} from the stacked symbol files;
    tokens = [(path, token)]: every guess_ token in src/ include/ config/symbols*.txt and every ledger
    type/field/local name found word-bounded in src/ include/; groups = registry ids (scope `class:<id>`:
    ONE row per class, standing for name and name_<k> in every member). Pure.
    -> {errors, guess_without_basis, dead, curated_without_citation} (sorted lists)."""
    aliases = set().union(*symbols.values()) if symbols else set()
    errors, seen, based = [], set(), set()
    src_words = {t for p, t in tokens if p.startswith(("src/", "include/"))}
    guess_toks = {t for _, t in tokens if t.startswith("guess_")}
    dead, fams = [], []
    for i, r in enumerate(rows, 1):
        nm, kind, scope = r["name"], r["kind"], r["scope"]
        bad = row_errors(r, aliases, groups)
        if (nm, scope) in seen: bad.append("duplicate (name, scope)")
        seen.add((nm, scope))
        if bad:
            errors.append("row %d %s: %s" % (i, nm, ", ".join(bad)))
            continue
        fam = _family(nm) if scope.startswith("class:") else None
        if fam and r["citation"] not in ("", "-"):
            fams.append(fam)
        if r["basis"] not in ("", "-"):
            based.add(_base(nm))
            if fam:
                based |= {t for t in guess_toks if fam.match(t)}
        if fam:
            live = any(fam.match(n) for n in symbols)
        else:
            live = nm in symbols if kind in ("func", "data") else _base(nm) in src_words
        if not live:
            dead.append("%s (%s, %s)" % (nm, kind, scope))
    gwb = sorted(guess_toks - based)
    cited = {r["name"] for r in rows if r["citation"] not in ("", "-")}
    curated = sorted(n for n in symbols if not PLACEHOLDER.match(n) and not n.startswith("guess_")
                     and n not in cited and not any(f.match(n) for f in fams))
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
    groups = ()
    if any(r["scope"].startswith("class:") for r in rows):
        import rename_sym
        groups = rename_sym.load_groups()[0]
    res = check_ledger(rows, symbols, load_tokens(rows), groups)
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


# ---------------------------------------------------------------- worklist (pure core)
def parse_worklist(text):
    """Pure. -> (header `#` lines, [dict per WORKLIST_COLS]). Raises ValueError on a bad header / row width."""
    heads, rows, header = [], [], None
    for ln in text.splitlines():
        if ln.startswith("#"):
            heads.append(ln)
            continue
        if not ln.strip():
            continue
        f = ln.split("\t")
        if header is None:
            if tuple(f) != WORKLIST_COLS:
                raise ValueError("worklist header must be: " + "\\t".join(WORKLIST_COLS))
            header = f
            continue
        if len(f) != len(WORKLIST_COLS):
            raise ValueError("worklist row has %d fields, needs %d: %r" % (len(f), len(WORKLIST_COLS), ln[:80]))
        rows.append(dict(zip(WORKLIST_COLS, f)))
    return heads, rows


def _placeholder(kind, vram):
    return "%s_%08X" % ("D" if kind == "data" else "func", vram)


def check_worklist(heads, rows, ledger, inst, names, members, complete=False):
    """Pure. heads/rows from parse_worklist; ledger = names.tsv rows; inst = {rank43: [(binary, vram int)]};
    names = {(binary, vram): (name, symbol-file alias)} (first hit through the binary's stack; absent =
    placeholder); members = {group id: {(binary, vram)}}. -> (counts per disposition + undisposed,
    [(rank43, unit, reason)])."""
    counts = {d: 0 for d in DISPOSITIONS + ("undisposed",)}
    bad = []
    if not any(SOURCE_RE.search(h) for h in heads):
        bad.append(("-", "header", "no `source: <path> @ <commit>` header line"))
    led = {(r["name"], r["scope"]): r["tier"] for r in ledger}
    cls = [(r["scope"][len("class:"):], r["name"], r["tier"]) for r in ledger if r["scope"].startswith("class:")]
    for w in rows:
        d, new, why = w["disposition"], w["new_name"], []
        if not d:
            counts["undisposed"] += 1
            if complete:
                why.append("undisposed")
        elif d not in DISPOSITIONS:
            why.append("disposition %r not in %s" % (d, "/".join(DISPOSITIONS)))
        else:
            counts[d] += 1
            got = sorted((i, names.get(i, (_placeholder(w["kind"], i[1]), None))) for i in inst.get(w["rank43"], ()))
            if d == "no-evidence":
                if new != w["name"] or not PLACEHOLDER.match(w["name"]):
                    why.append("new_name must be the placeholder `name` column")
                # an instance already carrying a cited name is no claim of ours (3.43 T7.c3: rank 1's 28 PsyQ labels)
                why += ["%s:%08X carries %s" % (i + (n,)) for i, (n, fa) in got if not PLACEHOLDER.match(n) and not (
                    led.get((n, fa)) == "cited"
                    or any(t == "cited" and cn == n and i in members.get(g, ()) for g, cn, t in cls))]
                if not w["reason"].strip():
                    why.append("no reason")
            else:
                tier = "guess" if d == "guess" else "cited"
                if not new:
                    why.append("no new_name")
                elif (d == "guess") != new.startswith("guess_"):
                    why.append("disposition %s but new_name %s" % (d, new))
                if not got:
                    why.append("no instances")
                fam = _family(new) if new else None
                for i, (n, fa) in got:
                    if not fam or not fam.match(n):
                        why.append("%s:%08X named %s, not %s" % (i + (n, new)))
                    elif led.get((n, fa)) != tier and not any(
                            # cn == n: a suffixed copy ledgered by its own class row (3.43 T7: guess_Vec3sDotAdd_2)
                            t == tier and cn in (new, n) and i in members.get(g, ()) for g, cn, t in cls):
                        why.append("%s:%08X %s has no %s names.tsv row" % (i + (n, tier)))
        if why:
            more = " (+%d more)" % (len(why) - 3) if len(why) > 3 else ""
            bad.append((w["rank43"], "%s %s" % (w["kind"], w["name"]), "; ".join(why[:3]) + more))
    return counts, bad


def symbol_stacks():
    """-> {binary: [symbol-file alias]} in each config/splat.<alias>.yaml symbol_addrs_path order
    (splat.us.exe.yaml is main). Comment lines inside the list are skipped."""
    out = {}
    for p in sorted(glob.glob(os.path.join(REPO, "config/splat.*.yaml"))):
        b = os.path.basename(p)[len("splat."):-len(".yaml")]
        if b.endswith(".template"):
            continue
        stack, on = [], False
        for ln in open(p):
            s = ln.strip()
            if not on:
                on = s.startswith("symbol_addrs_path:")
                continue
            if not s or s.startswith("#"):
                continue
            if not s.startswith("- "):
                break
            stack.append(_alias(s[2:].strip()))
        out["main" if b == "us.exe" else b] = stack
    return out


def load_worklist_inputs(rows):
    """-> (ledger, inst, names, members) for check_worklist; reads .run/sig.*.jsonl only for disposed rows."""
    import json
    ledger = parse_ledger(open(os.path.join(REPO, NAMES_TSV)).read())
    members = {}
    if any(r["scope"].startswith("class:") for r in ledger):
        import rename_sym
        members = {g: {(m["binary"], int(m["vram"], 16)) for m in ms}
                   for g, ms in rename_sym.load_groups()[0].items()}
    todo = [w for w in rows if w["disposition"] in DISPOSITIONS]
    stacks = symbol_stacks()
    inst = {}
    want = {w["h_exact"] for w in todo if w["kind"] == "func" and w["h_exact"]}
    by_h = {}
    if want:
        for p in sorted(glob.glob(os.path.join(REPO, ".run/sig.*.jsonl"))):
            stem = os.path.basename(p)[len("sig."):-len(".jsonl")]
            b = "main" if stem == "SLUS_007.26" else stem
            if b not in stacks:
                continue                                   # protos, oracles, images: not fleet binaries
            for ln in open(p):
                if '"h_exact"' in ln and any(h in ln for h in want):
                    r = json.loads(ln)
                    if r["h_exact"] in want:
                        by_h.setdefault(r["h_exact"], set()).add((b, int(r["addr"], 16)))
    for w in todo:
        if w["kind"] == "func":
            inst[w["rank43"]] = sorted(by_h.get(w["h_exact"], ()))
        elif w["space"] in DATA_SPACE:
            inst[w["rank43"]] = [(DATA_SPACE[w["space"]], int(w["addr"], 16))]
    syms = {}
    names = {}
    for i in {i for v in inst.values() for i in v}:
        for fa in stacks.get(i[0], ()):
            if fa not in syms:
                fp = os.path.join(REPO, "config/symbols.%s.txt" % fa)
                syms[fa] = ({int(a, 16): n for n, a in lsr.iter_symbol_defs(open(fp).read())}
                            if os.path.exists(fp) else {})
            if i[1] in syms[fa]:
                names[i] = (syms[fa][i[1]], fa)
                break
    return ledger, inst, names, members


def run_worklist(path, complete):
    try:
        heads, rows = parse_worklist(open(path).read())
    except (OSError, ValueError) as e:
        print("[rename_scan] worklist %s: %s\n[rename_scan] worklist FAIL" % (path, e))
        return 1
    counts, bad = check_worklist(heads, rows, *load_worklist_inputs(rows), complete=complete)
    print("[rename_scan] worklist %s: %d rows; %s" % (path, len(rows), ", ".join(
        "%s %d" % (d, counts[d]) for d in DISPOSITIONS + ("undisposed",))))
    for rk, unit, why in bad:
        print("  %s  %s  %s" % (rk, unit, why))
    print("[rename_scan] worklist %s" % ("FAIL: %d bad row(s)" % len(bad) if bad else "OK"))
    return 1 if bad else 0


# ---------------------------------------------------------------- selftest
def selftest():
    R = ("func_8003ABC8", "guess_ClearTbl", "0x8003ABC8")
    def scan_ok(hits):
        _, t = scan(hits, [R])
        assert sum(t.values()) == len(set(hits)), t
        return t["stale-build-input"] + t["stale-invisible"] + t["unclassified"] == 0, t
    clean = [("config/symbols.us.txt", 5, "guess_ClearTbl = 0x8003ABC8; // func"),
             ("src/main/a.c", 9, "    guess_ClearTbl(); /* was func_8003ABC8 */")]
    ok, t = scan_ok(clean); assert ok and t["rewritten"] == 2, t
    build = clean + [("src/main/b.c", 3, "    func_8003ABC8();")]
    ok, t = scan_ok(build); assert not ok and t["stale-build-input"] == 1, t
    st = lsr.stale_refs({"0x8003abc8":"guess_ClearTbl"}, set(), [("src/main/b.c", "void f(void){\n    func_8003ABC8();\n}\n")])
    assert [(s[0], s[1], s[2]) for s in st] == [("src/main/b.c", 2, "func_8003ABC8")], st
    ok, t = scan_ok(clean + [("docs/memory-map.md", 40, "| func_8003ABC8 | clears the table |")])
    assert not ok and t["stale-invisible"] == 1, t
    ok, t = scan_ok(clean + [("phase-ends/P30/log.md", 1, "renamed func_8003ABC8 today"),
                             ("cookbook/C0001.md", 2, "see 0x8003ABC8")])
    assert ok and t["history"] == 2, t
    ok, t = scan_ok(clean + [("docs/memory-map.md", 41, "0x8003ABC8 table clear")])
    assert not ok and t["unclassified"] == 1, t
    P = ("D_03ABC8", "guess_Pad", "0x3ABC8")                            # zero-padding / case forms
    ph = [("src/x.c", 1, "D_003ABC8 = 1;"), ("src/y.c", 2, "func_0003ABC8();"), ("tools/z.py", 3, "0X3ABC8"),
          ("docs/a.md", 4, "3ABC8 and 0x003ABC8"), ("src/w.c", 5, "D_8003ABC81; x03ABC8")]
    _, t = scan([h for h in ph if h[0] != "src/w.c"], [P])
    assert t["stale-build-input"] == 2 and t["unclassified"] == 2, t
    ch = grep_chunks([R, P, ("a_x", "b_x", "-")], size=2)                # one joined -e per chunk, same lines
    assert len(ch) == 2 and ch[1] == r"\ba_x\b", ch
    for h in clean + ph:
        assert bool(re.search(ch[0], h[2])) == any(re.search(f, h[2]) for r in (R, P)
                                                   for f in rename_forms(*r) if f), h
    try:                                                                # R32: a hit no rename owns is an error
        scan(ph, [P]); raise SystemExit("selftest: unowned hit not caught")
    except AssertionError:
        pass
    ak = [("src/800_c.c", 7, '#include "shared/main/func_8003ABC8.h"'),          # (a) header name only
          ("docs/wiki/x.md", 8, "  main/  func_8003ABC8.h  # the share header"),
          ("tools/share_census.py", 9, "    if '0x8003ABC8' in c['addrs']:"),         # (b) weak, listed path
          ("decomp-architect/corpus/tools/P10/share_census.py", 9, "    # main 0x8003ABC8 + its twin"),
          ("docs/duplicates.cross.md", 10, "| ei176 | main:0x8003ABC8; main:0x80037334 |"),
          ("decomp-architect/corpus/record/x.md", 3, "func_8003ABC8 matched"),         # kit copy of a record
          ("decomp-architect/corpus/cookbook/y.md", 4, "0x8003ABC8")]
    ak.append(("docs/duplicates.md", 16, "| 18 | 9 | 2 | func_8003ABC8 (0x8003ABC8) | 0x80037334 |"))
    ok, t = scan_ok(clean + ak); assert ok and t["address-key"] == 6 and t["history"] == 2 and t["rewritten"] == 2, t
    for h in (("src/800_c.c", 7, '#include "shared/main/func_8003ABC8.h" /* func_8003ABC8 */'),   # header + strong
              ("tools/share_census.py", 9, "func_8003ABC8 = 1"),                    # strong in a listed path
              ("decomp-architect/corpus/tools/P10/other.py", 9, "0x8003ABC8"),     # unlisted tool copy
              ("docs/duplicates.resident.md", 1, "| func_8003ABC8 (0x8003ABC8) |"),  # not on NAMES_FROM_VRAM
              ("src/800_c.c", 8, '#include "shared/main/func_8003ABC8.h" // 0x8003ABC8')):   # header + weak
        ok, t = scan_ok(clean + [h]); assert not ok and t["address-key"] == 0, (h, t)
    _, t = scan([("docs/duplicates.md", 1, "| OldName (0x8003ABC8) |")], [("OldName", "New", "0x8003ABC8")])
    assert t["stale-invisible"] == 1, t                                 # a curated old name there is still stale
    wide = ("# spec\nold\tnew\taddr\tbinary\tkind\tbasis\tconfidence\tevidence\tconflict\tcitation\n"
            "func_8003ABC8\tguess_ClearTbl\t0x8003ABC8\tmain\tfunc\tzeroes it\tmedium\tcode inference\t-\t-\n")
    assert parse_spec(wide) == [R], parse_spec(wide)
    assert parse_spec("func_8003ABC8\tguess_ClearTbl\t0x8003ABC8\n") == [R]
    G = {"I0_t": [{"binary": "main", "vram": "0x8003ABC8", "name": "func_8003ABC8"},
                  {"binary": "ov_SC01_005", "vram": "0x8012AD64", "name": "func_8012AD64"},
                  {"binary": "main", "vram": "0x8003A000", "name": "func_8003A000"}]}
    assert parse_spec(wide.replace("\tmain\t", "\tclass:I0_t\t"), G) == sorted(
        [("func_8003A000", "guess_ClearTbl", "0x8003A000"), ("func_8003ABC8", "guess_ClearTbl_2", "0x8003ABC8"),
         ("func_8012AD64", "guess_ClearTbl", "0x8012AD64")])
    # rename_sym's pure planner: symbol-file choice, class expansion, distinct names, add vs replace
    import rename_sym as rsy
    assert rsy.symbol_file("main") == "config/symbols.us.txt" and rsy.file_alias("main") == "us"
    assert rsy.symbol_file("ov_SC01_005") == "config/symbols.ov_SC01_005.txt"
    row = dict(zip(rsy.SPEC_COLS, wide.splitlines()[2].split("\t")))
    us = ("// hdr\n// count=2\n\nstart                            = 0x80010000; // func\n"
          "Later                            = 0x80050000; // func\n")
    ov = "// count=1\nOvFn                             = 0x8012A000; // func\n"
    texts = {"config/symbols.us.txt": us, "config/symbols.ov_SC01_005.txt": ov}
    pl, nt = rsy.plan([dict(row, binary="class:I0_t")], G, texts)
    assert [(r["old"], r["new"], r["symfile"]) for r in pl] == [
        ("func_8003A000", "guess_ClearTbl", "config/symbols.us.txt"),
        ("func_8003ABC8", "guess_ClearTbl_2", "config/symbols.us.txt"),
        ("func_8012AD64", "guess_ClearTbl", "config/symbols.ov_SC01_005.txt")], pl
    assert nt["config/symbols.us.txt"].splitlines() == [
        "// hdr", "// count=4", "", "start                            = 0x80010000; // func",
        "guess_ClearTbl                   = 0x8003A000; // func",
        "guess_ClearTbl_2                 = 0x8003ABC8; // func",
        "Later                            = 0x80050000; // func"], nt
    assert nt["config/symbols.ov_SC01_005.txt"].splitlines() == [                # appended after the last line
        "// count=2", "OvFn                             = 0x8012A000; // func",
        "guess_ClearTbl                   = 0x8012AD64; // func"], nt
    # binary scope (C0571, R124): pair_scope from symbol stacks, scope_decide per file, the scan's other-binary class
    stk = rsy.stackers_of({"main": ["us", "us.ram"], "ov_A": ["us", "resident", "ov_A"], "ov_B": ["us", "resident", "ov_B"],
                           "resident": ["us", "resident"]})
    sc = rsy.pair_scope([{"old": "func_80FFFFF0", "new": "guess_Step", "binary": "ov_A"},
                         {"old": "D_80078EB4", "new": "g_Hp", "binary": "main"}], stk)
    assert sc == {("func_80FFFFF0", "guess_Step"): {"ov_A"}, ("D_80078EB4", "g_Hp"): {"main", "ov_A", "ov_B", "resident"}}, sc
    P1, P2 = ("func_80FFFFF0", "guess_Step"), ("D_80078EB4", "g_Hp")
    hold = {"func_80FFFFF0": {"ov_A", "ov_B"}, "D_80078EB4": {"ov_A", "main"}}
    dec = lambda fb, prs, sco=sc: {k: v for k, v in rsy.scope_decide(fb, prs, sco, hold).items() if v}
    assert dec({"ov_A"}, [P1, P2]) == {"in": [P1, P2]}
    assert dec({"ov_B"}, [P1, P2]) == {"out": [P1], "in": [P2]}                 # ov_B's func_80FFFFF0 is another fn
    assert dec({"ov_A", "ov_B"}, [P1]) == {"straddle": [P1]}                     # a share header over both
    assert dec(set(), [P1, P2]) == {"unscoped": [P1], "in": [P2]}               # unmapped: P1 ambiguous, P2 not
    assert dec(set(), [P1], {**sc, P1: {"ov_A", "ov_B"}}) == {"in": [P1]}
    assert rsy.file_binaries("config/symbols.us.ram.txt", [], {"ov_A"}, stk) == {"main"}
    assert rsy.file_binaries("src/ov_B/x.c", [], {"ov_A", "ov_B"}, stk) == {"ov_B"}
    assert rsy.file_binaries("include/x.h", [], {"ov_A"}, stk) == set()
    SR, wh = ("func_80FFFFF0", "guess_Step", "0x80FFFFF0"), (lambda p: {"ov_B"} if "ov_B" in p else set())
    sh = [("src/ov_A/a.c", 1, "    guess_Step(); /* func_80FFFFF0 */"), ("src/ov_B/b.c", 2, "    func_80FFFFF0();"),
          ("include/x.h", 3, "void func_80FFFFF0(void);")]
    _, t = scan(sh, [SR], {SR: {"ov_A"}}, wh)
    assert t["other-binary"] == 1 and t["stale-build-input"] == 1 and t["rewritten"] == 1, t   # unmapped stays stale
    _, t = scan(sh, [SR], {SR: {"ov_A", "ov_B"}}, wh)
    assert t["other-binary"] == 0 and t["stale-build-input"] == 2, t                           # in-scope stale is bad
    _, t = scan(sh, [SR]); assert t["other-binary"] == 0 and t["stale-build-input"] == 2, t    # 3-column: as before
    qh = [("docs/t.md", 1, "- `S1`: 2 obj — 0x8001CC3C(arg0), src/ov_B/0x800D21C4:func_80FFFFF0, src/ov_B/0x800D21C4:s0")]
    _, t = scan(qh, [SR], {SR: {"ov_A"}}, wh); assert t["other-binary"] == 1, t                # object id in ov_B
    _, t = scan(qh, [SR], {SR: {"ov_A", "ov_B"}}, wh); assert t["stale-invisible"] == 1, t     # in-scope id: stale
    qu = [("docs/t.md", 2, qh[0][2] + " func_80FFFFF0")]
    _, t = scan(qu, [SR], {SR: {"ov_A"}}, wh); assert t["stale-invisible"] == 1, t             # unqualified: stale
    # _other_entity's line-level rules (T9.c9): each passes as other-binary; each counter-case stays stale
    hx = lambda r: {"981b4c9251c519a22d1e4cf67a36d06c000df0ba"}
    def oe(h, kind="func", hashes=hx, r=SR):
        _, t = scan([h], [r], {r: {"ov_A"}}, wh, {r: kind}, hashes)
        return "other-binary" if t["other-binary"] else [c for c in BAD if t[c]][0]
    LV = "9\t%s\t%s\t80128158\t80FFFFF0\t%s\tno\t1"
    for h, kind, hs, want in (
            (("docs/t.md", 1, "last={'other:D_80FFFFF0[a0]': 1}"), "func", hx, "other-binary"),        # (a)
            (("docs/t.md", 2, "D_80FFFFF0 and func_80FFFFF0"), "func", hx, "stale-invisible"),
            (("docs/t.md", 3, "D_80FFFFF0 only"), "data", hx, "stale-invisible"),                    # data rename: D_ is it
            (("config/dedup.us.yaml", 4, "      - { binary: ov_B, vram: 0x80FFFFF0, name: func_80FFFFF0 }"),
             "func", hx, "other-binary"),                                                            # (b)
            (("config/dedup.us.yaml", 5, "      - { binary: ov_A, vram: 0x80FFFFF0, name: func_80FFFFF0 }"),
             "func", hx, "stale-invisible"),
            (("config/lever_residue.tsv", 6, "src/ov_B/x.c\tfunc_80FFFFF0\tpin"), "func", hx, "other-binary"),  # (c)
            (("config/lever_residue.tsv", 7, "include/x.h\tfunc_80FFFFF0\tpin"), "func", hx, "stale-invisible"),
            (("docs/leverage.tsv", 8, LV % ("func", "7c2da22d4126", "func_80FFFFF0")), "func", hx, "other-binary"),  # (d)
            (("docs/leverage.tsv", 9, LV % ("func", "981b4c9251c5", "func_80FFFFF0")), "func", hx, "stale-invisible"),
            (("docs/leverage.tsv", 10, LV % ("func", "7c2da22d4126", "func_80FFFFF0")), "func", lambda r: set(),
             "stale-invisible"),                                                                     # no hash: no proof
            (("docs/leverage.tsv", 11, LV % ("func", "7c2da22d4126", "func_80FFFFF0") + "\tfunc_80FFFFF0"), "func", hx,
             "stale-invisible")):                                                                    # token off the name column
        assert oe(h, kind, hs) == want, (h, kind, want)
    OR = ("OldFn", "guess_Step", "0x80FFFFF0")                                                       # (d) another kind
    assert oe(("docs/leverage.tsv", 12, LV % ("data", "80128158:80FFFFF0", "OldFn")), r=OR) == "other-binary"
    assert oe(("docs/leverage.tsv", 13, LV % ("func", "981b4c9251c5", "OldFn")), r=OR) == "stale-invisible"
    _, t = scan([("docs/t.md", 1, "'other:D_80FFFFF0[a0]'")], [SR], {SR: {"ov_A"}}, wh)
    assert t["stale-invisible"] == 1, t                                                              # no kind: as before
    us = {"T_B": ["src/ov_B/x.c"], "T_AB": ["src/ov_B/x.c", "src/ov_A/y.c"], "T_U": ["include/x.h"]}.get  # (e)
    wa = lambda p: {"ov_B"} if "ov_B" in p else {"ov_A"} if "ov_A" in p else set()
    tf = lambda ty, ev="owner:func_80FFFFF0": ("config/type_folds.tsv", 14, "U_1\tdefine\t%s\t%s\tnote" % (ty, ev))
    for h, want in ((tf("T_B"), "other-binary"), (tf("T_AB"), "stale-invisible"), (tf("T_NONE"), "stale-invisible"),
                    (tf("T_U"), "stale-invisible"),                                                  # unmapped user
                    (tf("T_B", "func_80FFFFF0"), "stale-invisible")):                                # no owner: note
        _, t = scan([h], [SR], {SR: {"ov_A"}}, wa, {SR: "func"}, hx, lambda ty: us(ty, []))
        assert t[want] == 1, (h, t)
    scs = {}
    kds = {}
    assert parse_spec(wide.replace("\tmain\t", "\tov_A\t"), {}, stk, scs, kds) == [R] and scs == {R: {"ov_A"}}, scs
    assert kds == {R: "func"}, kds
    pl, nt = rsy.plan([dict(row, old="Later", addr="0x80050000")], {}, texts)    # curated old: replace in place
    assert nt["config/symbols.us.txt"].splitlines()[1:] == [
        "// count=2", "", "start                            = 0x80010000; // func",
        "guess_ClearTbl                   = 0x80050000; // func"], nt
    for bad in (dict(row, old="NoSuch"), dict(row, binary="ov_NOPE"), dict(row, new="Later"),
                dict(row, old="func_80050000", addr="0x80050000")):                 # address already named
        try:
            rsy.plan([bad], G, texts); raise SystemExit("selftest: planner accepted %r" % bad)
        except ValueError:
            pass
    assert rsy.names_row(rsy.names_fields(pl[0], G)).split("\t")[:5] == [
        "guess_ClearTbl", "func", "us", "0x80050000", "guess"]
    S = row                                                             # the wide spec row, kept for prepare()
    assert rsy.rewrite_re("func_8003ABC8").sub("N", '#define F func_8003ABC8\n#include "func_8003ABC8.h"') \
        == '#define F N\n#include "func_8003ABC8.h"'
    d = ("+++ b/config/symbols.us.txt\n-OldA = 0x80010000; // func\n+NewA = 0x80010000; // func\n"
         "+guess_Tbl = 0x80076251; // data\n+guess_Fn = 0x8003700C; // func\n+func_80040000 = 0x80040000; // func\n")
    assert renames_from_diff(d) == [("D_80076251", "guess_Tbl", "0x80076251"), ("OldA", "NewA", "0x80010000"),
                                    ("func_8003700C", "guess_Fn", "0x8003700c")], renames_from_diff(d)
    # ledger
    sym = {"func_8003ABC8": {"us"}, "guess_ClearTbl": {"us"}, "InitHeap": {"us"}, "D_80012340": {"us"},
           "SysEnqIntRP": {"ov_SC02_003"}}
    row = dict(zip(COLUMNS, ("guess_ClearTbl", "func", "us", "0x8003ABC8", "guess", "zeroes 0x40 words",
                             "medium", "code inference", "-", "func_8003ABC8", "-")))
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
    assert not check_ledger([dict(row, evidence="library symbol"), cit], sym, toks)["errors"]
    # ledger: a class row is ONE row, scope class:<id>; its _2 member counts as based / cited / live
    crow = dict(row, scope="class:I0_t", history="func_8003ABC8 (3.43 T2)")
    r = check_ledger([crow, cit], dict(sym, guess_ClearTbl_2={"us"}), toks + [("src/main/b.c", "guess_ClearTbl_2")], G)
    assert not r["errors"] and not r["dead"] and not r["guess_without_basis"], r
    ccit = dict(cit, name="Heap", scope="class:I0_t")
    r = check_ledger([row, cit, ccit], dict(sym, Heap={"us"}, Heap_2={"ov_SC01_005"}), toks, G)
    assert not r["errors"] and r["curated_without_citation"] == ["SysEnqIntRP"], r
    assert check_ledger([dict(crow, scope="class:NOPE")], sym, toks, G)["errors"]
    assert check_ledger([dict(crow, name="guess_Gone")], sym, [], G)["dead"] == ["guess_Gone (func, class:I0_t)"]
    # worklist
    H = ["# names_worklist.tsv", "# generator: x; source: docs/leverage.tsv @ e328006dab; classes at HEAD 5e69f147c5"]
    def wl(**kw):
        w = dict.fromkeys(WORKLIST_COLS, "")
        w.update(rank43="7", kind="func", space="8000F800", addr="8003ABC8", name="func_8003ABC8", **kw)
        return w
    inst = {"7": [("main", 0x8003ABC8), ("ov_SC01_005", 0x8012AD64)]}
    nm2 = {("main", 0x8003ABC8): ("guess_ClearTbl", "us"), ("ov_SC01_005", 0x8012AD64): ("guess_ClearTbl_2", "ov_SC01_005")}
    led = [row, dict(row, name="guess_ClearTbl_2", scope="ov_SC01_005")]
    def cw(rows, heads=H, led=led, names=nm2, members={}, complete=False):
        return check_worklist(heads, rows, led, inst, names, members, complete)
    c, b = cw([wl()]); assert c["undisposed"] == 1 and not b, (c, b)
    c, b = cw([wl()], complete=True); assert [x[2] for x in b] == ["undisposed"], b           # --complete
    _, b = cw([wl()], heads=["# names_worklist.tsv; no source"]); assert [x[1] for x in b] == ["header"], b
    assert parse_worklist("\n".join(H + ["\t".join(WORKLIST_COLS), "\t".join(wl().values())]))[1] == [wl()]
    _, b = cw([wl(disposition="maybe")]); assert len(b) == 1 and "not in" in b[0][2], b         # outside the list
    c, b = cw([wl(disposition="guess", new_name="guess_ClearTbl")]); assert c["guess"] == 1 and not b, b
    _, b = cw([wl(disposition="cited", new_name="guess_ClearTbl")]); assert b, "guess_ name under cited"
    cn = {i: ("Clear" + s, a) for (i, (_, a)), s in zip(sorted(nm2.items()), ("", "_2"))}
    _, b = cw([wl(disposition="cited", new_name="Clear")], names=cn)                         # no ledger row
    assert len(b) == 1 and "no cited names.tsv row" in b[0][2], b
    _, b = cw([wl(disposition="cited", new_name="Clear")], names=cn, led=[dict(cit, name="Clear", scope="class:I0m")],
              members={"I0m": set(inst["7"])}); assert not b, b                              # covered by a class row
    _, b = cw([wl(disposition="guess", new_name="guess_ClearTbl")], names={("main", 0x8003ABC8): nm2[("main", 0x8003ABC8)]})
    assert len(b) == 1 and "ov_SC01_005:8012AD64 named func_8012AD64" in b[0][2], b            # a member unnamed
    ne = wl(disposition="no-evidence", new_name="func_8003ABC8", reason="no xref, no string")
    c, b = cw([ne], names={}); assert c["no-evidence"] == 1 and not b, b
    _, b = cw([dict(ne, new_name="guess_ClearTbl")], names={}); assert b and "placeholder" in b[0][2], b
    _, b = cw([dict(ne, reason="")], names={}); assert b and "no reason" in b[0][2], b
    _, b = cw([ne]); assert b and "carries guess_ClearTbl" in b[0][2], b
    c, b = cw([ne], names={("ov_SC01_005", 0x8012AD64): ("SPU_OBJ_98C", "ov_SC01_005")},
              led=led + [dict(cit, name="SPU_OBJ_98C", scope="ov_SC01_005")])
    assert c["no-evidence"] == 1 and not b, b                                                  # an instance with a cited name
    # rename_sym.prepare: names rows validated before any write; history; re-rename rewrites the row
    NT = "# hdr\n" + "\t".join(COLUMNS) + "\n"
    al = {"us", "ov_SC01_005", "main"}
    _, nt1, n1, w1 = rsy.prepare([S], G, texts, NT, al, "3.43 T2")
    assert [v["history"] for v in w1] == ["func_8003ABC8 (3.43 T2)"] and len(parse_ledger(n1)) == 1, n1
    S2 = dict(S, old="guess_ClearTbl", new="guess_ClearTbl2")                                   # guess_A -> guess_B
    _, nt2, n2, _ = rsy.prepare([S2], G, {"config/symbols.us.txt": nt1["config/symbols.us.txt"]}, n1, al, "3.43 T2")
    lr = parse_ledger(n2)
    assert [(v["name"], v["history"]) for v in lr] == [
        ("guess_ClearTbl2", "func_8003ABC8 (3.43 T2); guess_ClearTbl (3.43 T2)")], lr
    s2 = {n: {"us"} for n, _ in lsr.iter_symbol_defs(nt2["config/symbols.us.txt"])}
    r = check_ledger(lr, s2, [("config/symbols.us.txt", "guess_ClearTbl2")])
    assert not r["errors"] and not r["dead"] and not r["guess_without_basis"] and "guess_ClearTbl" not in s2, r
    cur = NT + "\t".join(dict(cit, name="Later", addr="0x80050000")[c] for c in COLUMNS) + "\n"  # Foo -> guess_Foo
    _, _, n3, _ = rsy.prepare([dict(S, old="Later", new="guess_Later", addr="0x80050000")], G, texts, cur, al, "3.43 T2")
    lr = parse_ledger(n3)
    assert len(lr) == 1 and lr[0]["tier"] == "guess" and lr[0]["history"] == "Later (3.43 T2)", lr
    for bad in (dict(S, evidence="hunch"), dict(S, confidence="sure"), dict(S, basis="-"), dict(S, kind="type")):
        try:
            rsy.prepare([bad], G, texts, NT, al, "3.43 T2"); raise SystemExit("selftest: prepare accepted %r" % bad)
        except ValueError:
            pass
    pl, _, n4, w4 = rsy.prepare([dict(S, binary="class:I0_t")], G, texts, NT, al, "3.43 T2")
    assert len(pl) == 3 and [(v["name"], v["scope"]) for v in w4] == [("guess_ClearTbl", "class:I0_t")], w4
    assert len(parse_ledger(n4)) == 1 and not check_ledger(parse_ledger(n4), dict(sym, guess_ClearTbl_2={"us"}),
                                                            toks, G)["errors"]
    G2 = {"A": [G["I0_t"][2]], "B": [G["I0_t"][0]]}                                           # _k across the spec
    assert [r["new"] for r in rsy.expand([dict(S, binary="class:A"), dict(S, binary="class:B")], G2)] == [
        "guess_ClearTbl", "guess_ClearTbl_2"]
    # registry: the vram + binaries form, YAML int vram -> hex
    gs, reg = rsy.groups_from_registry({"groups": [
        {"id": "E_f", "func": "func_80FFFFF0", "vram": 0x80FFFFF0, "binaries": ["ov_A", "ov_B"]},
        {"id": "M", "members": [{"binary": "ov_A", "vram": 0x80100000, "name": "func_80100000"}]}]})
    assert gs["E_f"] == [{"binary": b, "vram": "0x80FFFFF0", "name": "func_80FFFFF0"} for b in ("ov_A", "ov_B")], gs
    assert gs["M"][0]["vram"] == "0x80100000" and reg[0]["members"] == gs["E_f"], (gs, reg)
    assert [(r["old"], r["addr"], r["binary"]) for r in rsy.expand([dict(S, binary="class:E_f")], gs)] == [
        ("func_80FFFFF0", "0x80FFFFF0", "ov_A"), ("func_80FFFFF0", "0x80FFFFF0", "ov_B")]
    # rename_sym.ledger_row_rename: fn, unit and the sites[]/bases[] residue keys follow the rename; tu paths do not (C0572)
    olds = {"D_80078EB4": "g_Hp", "func_80147078": "guess_Set"}
    lrx = re.compile(r"\b(?:D_80078EB4|func_80147078)\b")
    lrow = {"rung": "S", "tu": "src/shared/ov/func_80147078.h", "unit": "func_80147078", "fn": "guess_Set", "cause": "D_80078EB4",
            "sites": [{"base": "global:D_80078EB4"}, {"base": "nested:*(s32 *)&D_80078EB4"}, {"base": "param:a0"}],
            "bases": [{"base": "gaddr:D_80078EB4"}]}
    r2, ch = rsy.ledger_row_rename(lrow, lrx, olds)
    assert ch and r2["unit"] == "guess_Set" and r2["tu"] == lrow["tu"] and r2["cause"] == "D_80078EB4" and [
        e["base"] for e in r2["sites"] + r2["bases"]] == ["global:g_Hp", "nested:*(s32 *)&g_Hp", "param:a0", "gaddr:g_Hp"], r2
    assert rsy.ledger_row_rename(r2, lrx, olds) == (r2, False)
    # generated outputs: leverage.md / .tsv rewritten as text, address-keyed; regen_cmd from `regenerate:`
    LH = "<!-- generated by tools/leverage_rank.py; do not edit; regenerate: /usr/bin/python3 tools/leverage_rank.py -j 16 -->"
    assert rsy.regen_cmd("docs/leverage.md", LH) is None and rsy.regen_cmd("docs/leverage.tsv", LH) is None
    assert rsy.regen_cmd("docs/other.md", LH) == "/usr/bin/python3 tools/leverage_rank.py -j 16"
    assert rsy.regen_cmd("src/shared/ov/cls_x.h", "// generated by tools/share_body.py") is None
    assert rsy.regen_cmd("docs/x.md", "<!-- generated by tools/x.py; do not edit -->") == "/usr/bin/python3 tools/x.py"
    T = ("func_80DEAD10", "guess_Probe", "0x80DEAD10")
    md = "| 46 | func | af37952690c2 | func_80DEAD10 | no | 4074 | 0.000 | 1 | 4074.000 |  |"
    md2 = rsy.rewrite_re(T[0]).sub(T[1], md)
    assert md2 == md.replace(T[0], T[1]), md2
    _, t = scan([("docs/leverage.tsv", 47, "46\tfunc\taf37\t8000F800\t80DEAD10\tguess_Probe"),   # md2 has no form left
                 ("docs/leverage.tsv", 9, "9\tdata\tx\t8000F800\t80DEAD10\t")], [T])
    assert t["rewritten"] == 1 and t["address-key"] == 1 and not sum(t[c] for c in BAD), t
    _, t = scan([("docs/leverage.md", 95, md)], [T]); assert t["stale-invisible"] == 1, t
    print("[rename_scan] selftest OK")
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--selftest", action="store_true")
    g.add_argument("--ledger", action="store_true")
    g.add_argument("--spec", metavar="TSV", help="old<TAB>new<TAB>addr|- rows, or rename_sym's wide spec")
    g.add_argument("--range", metavar="A..B", help="renames in config/symbols*.txt between A and B (B empty = worktree)")
    g.add_argument("--worklist", metavar="FILE", help="check a names worklist's dispositions (e.g. " + WORKLIST_TSV + ")")
    ap.add_argument("--complete", action="store_true", help="with --worklist: an undisposed row also fails")
    ap.add_argument("-v", "--verbose", action="store_true", help="with --spec/--range: print every classified hit")
    ap.add_argument("--gate-citations", action="store_true", help="with --ledger: fail on curated names with no citation row")
    a = ap.parse_args()
    if a.selftest:
        return selftest()
    if a.ledger:
        return run_ledger(a.gate_citations)
    if a.worklist:
        return run_worklist(a.worklist, a.complete)
    if a.spec:
        renames, scopes, where, kinds, hashes, uses = renames_from_spec(a.spec)
        return run_scan(renames, None, a.verbose, scopes, where, kinds, hashes, uses)
    lo, _, hi = a.range.partition("..")
    return run_scan(renames_from_range(lo, hi or None), hi or None, a.verbose)


if __name__ == "__main__":
    sys.exit(main())
