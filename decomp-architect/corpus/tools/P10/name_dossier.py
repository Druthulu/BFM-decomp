"""name_dossier.py: one naming-evidence dossier per unit of config/names_worklist.tsv (from 3.43 T6).
Out: <DIR>/dossiers/R<rank>_<oldname>.md, <DIR>/evidence.tsv, <DIR>/evidence_summary.txt.
Usage: /usr/bin/python3 tools/name_dossier.py --out DIR [--ranks A-B,C] [-j N]
Callers/callees: .run/sig.<alias>.jsonl (byte truth); names: corpus.symbols(alias) (the splat-config stack)."""
import argparse, collections, json, multiprocessing as mp, os, re, subprocess, sys, time

REPO = "/home/musashi/bfm-decomp"
os.chdir(REPO)
sys.path.insert(0, os.path.join(REPO, "tools"))
import corpus  # noqa: E402

OUT = None  # set from --out in main()
DOS = None
CAP = 40
PLACE = re.compile(r"^(?:func|D|jtbl|jpt|FUN|LAB|DAT|E_func)_[0-9A-Fa-f]{6,8}$")
TOK = re.compile(r"[A-Za-z_]\w*")
STRLIT = re.compile(r'"(?:[^"\\\n]|\\.)*"')
KEYW = {"if", "while", "for", "switch", "return", "sizeof", "do", "else", "case", "typedef", "struct", "union", "enum"}
DEFRE = re.compile(r"^[A-Za-z_][\w\s\*]*?\b([A-Za-z_]\w*)\s*\(")
SPACE = {"8000F800": "main", "800CEDF8": "resident", "abs": "main"}
REGION = 0x10000  # a covering row wider than this is a load region, listed but not counted as evidence
PRIO = ["live RAM verified", "debug menu", "string", "xref chain", "community reported", "code only"]


def place(kind, addr):
    return (f"func_{addr:08X}" if kind == "func" else f"D_{addr:08X}")


# ---------------------------------------------------------------- sig workers
def sig_worker(args):
    alias, want = args
    p = f".run/sig.{alias}.jsonl"
    rows = []
    with open(p) as f:
        for ln in f:
            if ln.strip():
                r = json.loads(ln)
                rows.append((int(r["addr"], 16), r["h_exact"], [int(c, 16) for c in r.get("calls", ())]))
    inst = collections.defaultdict(list)
    for a, h, calls in rows:
        if h in want:
            inst[h].append((a, calls))
    targets = {a for v in inst.values() for a, _ in v}
    callers = collections.defaultdict(list)
    if targets:
        for a, h, calls in rows:
            for c in calls:
                if c in targets:
                    callers[c].append(a)
    stack = {}
    syms = corpus.symbols(alias)
    for nm, ad in syms.items():
        stack.setdefault(ad, nm)
    funcs = {a for a, _, _ in rows}
    need = set(targets)
    for v in inst.values():
        for _, calls in v:
            need.update(calls)
    for v in callers.values():
        need.update(v)
    names = {a: stack[a] for a in need if a in stack}
    datanames = {nm: ad for nm, ad in syms.items() if ad not in funcs}
    return alias, dict(inst), {k: sorted(set(v)) for k, v in callers.items()}, names, datanames, stack


# ---------------------------------------------------------------- C text helpers
def strip_code(line, inc):
    """Remove comments and string/char literals; inc = inside a block comment at line start."""
    out, i, n = [], 0, len(line)
    while i < n:
        if inc:
            j = line.find("*/", i)
            if j < 0:
                return "".join(out), True
            i, inc = j + 2, False
            continue
        c = line[i]
        if c == "/" and line.startswith("//", i):
            break
        if c == "/" and line.startswith("/*", i):
            inc, i = True, i + 2
            continue
        if c in "\"'":
            j = i + 1
            while j < n and line[j] != c:
                j += 2 if line[j] == "\\" else 1
            out.append(c + c)
            i = j + 1
            continue
        out.append(c)
        i += 1
    return "".join(out), inc


def file_worker(args):
    path, enc_lines, def_lines = args
    try:
        lines = open(path, encoding="utf-8", errors="replace").read().split("\n")
    except OSError:
        return path, {}, {}
    enc, bodies = {}, {}
    if enc_lines:
        depth, inc, pending, cur = 0, False, None, None
        for i, ln in enumerate(lines, 1):
            code, inc = strip_code(ln, inc)
            if depth == 0:
                s = code.lstrip()
                if s.startswith("#") or s.startswith("INCLUDE_ASM"):
                    pending = None
                elif code[:1] and not code[:1].isspace():
                    m = DEFRE.match(code)
                    if m and m.group(1) not in KEYW and not code.startswith(("extern", "typedef")):
                        pending = m.group(1)
                    elif code.rstrip().endswith(";"):
                        pending = None
            o, c = code.count("{"), code.count("}")
            if depth == 0 and o:
                cur, pending = pending, None
            if i in enc_lines:
                enc[i] = cur if depth > 0 or o else None
            depth = max(0, depth + o - c)
            if depth == 0:
                cur = None
    for d in def_lines:
        depth, inc, seen, buf = 0, False, False, []
        for ln in lines[d - 1:d - 1 + 6000]:
            buf.append(ln)
            code, inc = strip_code(ln, inc)
            if not seen and "{" not in code and code.rstrip().endswith(";"):
                buf = None
                break
            depth += code.count("{") - code.count("}")
            if "{" in code:
                seen = True
            if seen and depth <= 0:
                break
        bodies[d] = "\n".join(buf) if buf else None
    return path, enc, bodies


def git_grep(patterns, extra=()):
    pf = f"{OUT}/.grep_{os.getpid()}_{len(patterns)}.txt"
    with open(pf, "w") as f:
        f.write("\n".join(sorted(patterns)) + "\n")
    # git grep -F -f is ~100x slower than GNU grep's Aho-Corasick on many patterns: feed it git's file list
    r = subprocess.run(f"git ls-files -z src include | xargs -0 -n 2000 grep -n -I -F -w -H -f {pf}",
                       shell=True, capture_output=True, text=True, errors="replace")
    os.remove(pf)
    out = []
    for ln in r.stdout.split("\n"):  # not splitlines(): C text may hold \f or U+2028
        if not ln:
            continue
        p, n, t = ln.split(":", 2)
        out.append((p, int(n), t))
    return out


# ---------------------------------------------------------------- docs
def load_docs():
    docs = []  # (path, line, text, debugsec)
    mm = open("docs/memory-map.md", encoding="utf-8").read().split("\n")
    dbg, rows, blocks = False, [], []
    hdr = None
    head = ""
    for i, ln in enumerate(mm, 1):
        if ln.startswith("#"):
            head = ln
            dbg = bool(re.search(r"debug[- ]menu", ln, re.I))
            hdr = None
            m = re.search(r"\(0x([0-9A-Fa-f]{8})\s*[–-]\s*0x([0-9A-Fa-f]{8})\)", ln)
            mx = re.search(r"\(0x([0-9A-Fa-f]+)(x+)\)", ln)
            if m:
                blocks.append((int(m.group(1), 16), int(m.group(2), 16), i, ln))
            elif mx:
                pre, k = mx.group(1), len(mx.group(2))
                blocks.append((int(pre + "0" * k, 16), int(pre + "F" * k, 16), i, ln))
        docs.append(("docs/memory-map.md", i, ln, dbg))
        if ln.startswith("|"):
            cells = [c.strip() for c in ln.strip().strip("|").split("|")]
            if "Confidence" in cells:
                hdr = {c.split()[0].split("/")[0] if c else "": k for k, c in enumerate(cells)}
                continue
            if hdr is None or not cells or set(cells[0]) <= set("-: "):
                continue
            c0 = cells[0].replace("*", "")
            conf = cells[hdr["Confidence"]] if hdr.get("Confidence", 99) < len(cells) else ""
            srcc = cells[hdr["Source"]] if hdr.get("Source", 99) < len(cells) else ""
            spans = []
            for m in re.finditer(r"0x([0-9A-Fa-f]{8})\s*[–-]\s*0x([0-9A-Fa-f]{8})", c0):
                spans.append((int(m.group(1), 16), int(m.group(2), 16)))
            if not spans:
                spans = [(int(a, 16), int(a, 16)) for a in re.findall(r"0x([0-9A-Fa-f]{8})", c0)]
            for lo, hi in spans:
                rows.append((lo, hi, conf, srcc, i, ln, head))
    for i, ln in enumerate(open("docs/debug-menu-list.txt", encoding="utf-8").read().split("\n"), 1):
        docs.append(("docs/debug-menu-list.txt", i, ln, True))
    for fn in sorted(os.listdir("config/ghidra")):
        if not fn.endswith(".jsonl"):
            continue
        for i, ln in enumerate(open(f"config/ghidra/{fn}", encoding="utf-8"), 1):
            if '"k":"comment"' not in ln:
                continue
            r = json.loads(ln)
            docs.append((f"config/ghidra/{fn}", i, f'{r.get("addr", "")} {r.get("type", "")}: '
                         + r.get("text", "").replace("\n", " "), False))
    return docs, rows, blocks


def load_asm_strings():
    r = subprocess.run(["grep", "-R", "-n", "-B2", "--include=*.s", r"\.asci", "asm"], capture_output=True, text=True,
                       errors="replace")
    strs = {}
    last = {}
    for ln in r.stdout.splitlines():
        m = re.match(r"^(asm/[^:]+?)[:-](\d+)[:-](.*)$", ln)
        if not m:
            continue
        p, n, t = m.group(1), int(m.group(2)), m.group(3)
        if t.startswith("dlabel "):
            last[p] = (n, t.split()[1])
        elif ".asci" in t and p in last and n - last[p][0] <= 2:
            am = re.search(r"/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*\*/\s*\.asci[iz]\s*(.*)", t)
            if am:
                parts = p.split("/")
                al = "main" if parts[1] == "data" else parts[1]
                strs[(al, int(am.group(1), 16))] = (am.group(2)[:120], f"{p}:{n}")
            del last[p]
    return strs


# ---------------------------------------------------------------- main
def parse_ranks(s):
    out = set()
    for part in s.split(","):
        if "-" in part:
            a, b = part.split("-")
            out.update(range(int(a), int(b) + 1))
        elif part:
            out.add(int(part))
    return out


def main():
    global OUT, DOS
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", required=True, help="output directory (dossiers/ and evidence files go under it)")
    ap.add_argument("--ranks")
    ap.add_argument("-j", type=int, default=8)
    a = ap.parse_args()
    OUT = a.out.rstrip("/")
    DOS = f"{OUT}/dossiers"
    t0 = time.time()
    os.makedirs(DOS, exist_ok=True)
    pool = mp.Pool(a.j)

    lines = [ln.rstrip("\n").split("\t") for ln in open("config/names_worklist.tsv", encoding="utf-8")
             if not ln.startswith("#")]
    cols = lines[0]
    units, seen, dup_rows = [], set(), 0
    for ln in lines[1:]:
        r = dict(zip(cols, ln))
        k = (int(r["rank43"]), r["key"])
        if k in seen:
            dup_rows += 1
            continue
        seen.add(k)
        units.append(r)
    nall = len(units)
    if a.ranks:
        rs = parse_ranks(a.ranks)
        units = [u for u in units if int(u["rank43"]) in rs]

    # background greps that do not need names
    asm_p = pool.apply_async(load_asm_strings)
    inc_p = subprocess.Popen(["git", "grep", "-h", "-E", r'^#include ".*shared/', "--", "src"], stdout=subprocess.PIPE,
                             text=True)

    srcdirs = corpus.src_dirs()
    aliases = sorted(al for al in srcdirs if os.path.exists(f".run/sig.{al}.jsonl"))
    want = {u["h_exact"] for u in units if u["kind"] == "func" and u["h_exact"]}
    inst = collections.defaultdict(list)  # h -> [(alias, addr, calls)]
    callers, names, datanames, stacks = {}, {}, {}, {}
    for al, ins, cal, nm, dn, st in pool.imap_unordered(sig_worker, [(al, want) for al in aliases]):
        for h, v in ins.items():
            for ad, calls in v:
                inst[h].append((al, ad, calls))
        callers[al], names[al] = cal, nm
        for k, v in dn.items():
            datanames.setdefault(k, v)
        if al in ("main", "resident"):
            stacks[al] = st
    for h in inst:
        inst[h].sort(key=lambda x: (x[0], x[1]))
    t_sig = time.time() - t0

    ledger = []
    for ln in open("config/names.tsv", encoding="utf-8"):
        if ln.startswith("#") or ln.startswith("name\t"):
            continue
        f = ln.rstrip("\n").split("\t")
        if len(f) >= 11:
            ledger.append(dict(zip("name kind scope addr tier basis confidence evidence conflict history citation".split(), f)))
    evid_of = {r["name"]: r["evidence"] for r in ledger}

    hist = collections.defaultdict(dict)  # old-name token in history -> {addr: name}
    for r in ledger:
        for tk in TOK.findall(r["history"]):
            if r["addr"].lower().startswith("0x"):
                hist[tk][int(r["addr"], 16)] = r["name"]

    def cur_name(al, ad, kind, old=None):
        n = names.get(al, {}).get(ad)
        if n is None and al in stacks:
            n = stacks[al].get(ad)
        if n:
            return n
        if old and ad in hist.get(old, {}):
            return hist[old][ad]
        return place(kind, ad)

    def is_place(n):
        return bool(PLACE.match(n))

    # unit instances + current names
    owned = sorted({d for al, d in srcdirs.items() if d != "src"}, key=len, reverse=True)

    def dir_of(path):
        if os.path.dirname(path) == "src":
            return "src"
        for d in owned:
            if path.startswith(d + "/"):
                return d
        return None  # shared / include

    for u in units:
        u["rank"] = int(u["rank43"])
        if u["kind"] == "func":
            u["inst"] = [(al, ad) for al, ad, _ in inst.get(u["h_exact"], [])]
            u["calls"] = {(al, ad): calls for al, ad, calls in inst.get(u["h_exact"], [])}
        else:
            al = SPACE.get(u["space"], u["target"]) or u["target"]
            u["inst"] = [(al, int(u["addr"], 16))]
            u["calls"] = {}
        u["cur"] = {}
        for al, ad in u["inst"]:
            u["cur"][(al, ad)] = cur_name(al, ad, u["kind"], u["name"])
        prim = [x for x in u["inst"] if x[1] == int(u["addr"], 16)] or u["inst"]
        u["prim"] = prim[0] if prim else None
        u["current"] = u["cur"][u["prim"]] if u["prim"] else u["name"]
        u["ndirs"] = collections.defaultdict(set)  # name -> allowed src dirs (None = any)
        for (al, ad), n in u["cur"].items():
            u["ndirs"][n].add(srcdirs.get(al) if u["kind"] == "func" else None)
        if not u["cur"]:
            u["ndirs"][u["name"]].add(None)

    allnames = {n for u in units for n in u["ndirs"]}
    owners = {u["owner"] for u in units if u["owner"]}
    tg = time.time()
    hits = git_grep(allnames)
    t_grep = time.time() - tg
    idx = collections.defaultdict(list)
    for p, n, t in hits:
        for tk in set(TOK.findall(t)) & allnames:
            idx[tk].append((p, n, t))
    own_hits = git_grep(owners) if owners else []
    incl = collections.Counter()
    for ln in inc_p.communicate()[0].splitlines():
        m = re.search(r'(shared/[^"]+)"', ln)
        if m:
            incl[m.group(1)] += 1

    # classify hits per unit; collect file jobs
    jobs = collections.defaultdict(lambda: [set(), set()])
    for u in units:
        defs, uses, incs = [], [], []
        for n, dset in u["ndirs"].items():
            for p, ln, t in idx.get(n, ()):
                d = dir_of(p)
                if None not in dset and d is not None and d not in dset:
                    continue
                s = t.lstrip()
                m = re.search(rf'INCLUDE_ASM\(\s*"([^"]+)"\s*,\s*{re.escape(n)}\s*\)', t)
                if m and t.startswith("INCLUDE_ASM"):
                    defs.append((p, ln, n, "asm", f"{m.group(1)}/{n}.s"))
                    continue
                if s.startswith("#include"):
                    incs.append((p, ln, n))
                    continue
                if s.startswith(("//", "/*", "*")):
                    uses.append((p, ln, n, t, "comment"))
                    continue
                if s.startswith("extern") or s.startswith("#"):
                    uses.append((p, ln, n, t, "decl"))
                    continue
                if t[:1] and not t[:1].isspace():
                    code = strip_code(t, False)[0]
                    if u["kind"] == "func" and re.match(rf"^[A-Za-z_][\w\s\*]*\b{re.escape(n)}\s*\(", code) \
                            and not code.rstrip().endswith((";", ",")):
                        defs.append((p, ln, n, "c", None))
                        jobs[p][1].add(ln)
                        continue
                    if u["kind"] == "data" and re.match(rf"^[A-Za-z_][\w\s\*]*\b{re.escape(n)}\b\s*(\[[^\]]*\]\s*)*(=|;)", code):
                        defs.append((p, ln, n, "cdata", None))
                        continue
                    if re.match(rf"^[A-Za-z_][\w\s\*]*\b{re.escape(n)}\s*\(", code) and code.rstrip().endswith(";"):
                        uses.append((p, ln, n, t, "decl"))
                        continue
                uses.append((p, ln, n, t, "use"))
                if u["kind"] == "data":
                    jobs[p][0].add(ln)
        u["defs"], u["uses"], u["incs"] = defs, uses, incs
    res = {}
    for p, enc, bodies in pool.imap_unordered(file_worker, [(p, v[0], v[1]) for p, v in jobs.items()], chunksize=4):
        res[p] = (enc, bodies)
    t_files = time.time() - t0
    asm_strs = asm_p.get()
    docs, mrows, blocks = load_docs()
    pool.close()

    os.makedirs(DOS, exist_ok=True)
    WRE = r"(?:\s*(?:\[[^\]]*\]|\.\s*\w+|->\s*\w+))*\s*(?:(?:[-+*/%&|^]|<<|>>)?=(?!=)|\+\+|--)"
    tsv, summ = [], []
    for u in units:
        n0 = u["current"]
        kind = u["kind"]
        addrs = sorted({ad for _, ad in u["inst"]}) or [int(u["addr"], 16)]
        L = [f"# R{u['rank']} {u['name']} -> current `{n0}`", "",
             f"kind {kind} · key {u['key']} · space {u['space']} · addr 0x{u['addr']} · refs {u['refs']} · fan {u['fan']}"
             f" · worklist instances {u['instances'] or '-'} · target {u['target'][:80]}"
             + ("..." if len(u["target"]) > 80 else ""),
             f"sig instances {len(u['inst'])} in {len({al for al, _ in u['inst']})} binaries at {len(addrs)} addresses"
             if kind == "func" else f"binary {u['inst'][0][0]}"]
        cn = collections.Counter(u["cur"].values())
        L.append(f"current names {len(cn)}: " + ", ".join(f"`{k}`x{v}" for k, v in sorted(cn.items(), key=lambda x: (-x[1], x[0]))[:CAP])
                 + (f" ... (+{len(cn) - CAP})" if len(cn) > CAP else ""))
        # definition
        L += ["", "## Definition"]
        defs = sorted(u["defs"], key=lambda d: (d[0], d[1]))
        prim_body, prim_def, asm_path = None, None, None
        pdir = srcdirs.get(u["prim"][0]) if u["prim"] else None
        order = sorted(defs, key=lambda d: (0 if d[2] == n0 and dir_of(d[0]) in (pdir, None) else 1, d[0], d[1]))
        for d in order:
            if d[3] == "c":
                prim_def, prim_body = d, res.get(d[0], ({}, {}))[1].get(d[1])
                break
            if d[3] == "asm" and asm_path is None:
                asm_path, prim_def = d[4], d
        if not order and kind == "data":
            L.append("no C definition (asm data)")
        for d in defs[:CAP]:
            p = d[0]
            extra = ""
            if p.startswith("src/shared/"):
                extra = f" (shared header; #included by {incl.get(p[len('src/'):], 0)} src files)"
            L.append(f"- {p}:{d[1]} `{d[2]}` {d[3]}" + (f" -> {d[4]}" if d[4] else "") + extra)
        if len(defs) > CAP:
            L.append(f"- ... {len(defs)} definition sites total")
        L.append(f"definition sites {len(defs)}")
        body_text = ""
        if prim_body:
            body_text = prim_body
            L += ["", f"### Body ({prim_def[0]}:{prim_def[1]})", "```c", prim_body, "```"]
        elif asm_path:
            L += ["", f"### Body: INCLUDE_ASM -> {asm_path}"]
            if os.path.exists(asm_path):
                body_text = open(asm_path, encoding="utf-8", errors="replace").read()
        # callers / callees
        xref_names = set()
        L += ["", "## Callers and callees" if kind == "func" else "## Accessors"]
        if kind == "func":
            for title, get in (("callees", lambda al, ad: u["calls"].get((al, ad), [])),
                               ("callers", lambda al, ad: callers.get(al, {}).get(ad, []))):
                cnt, bins = collections.Counter(), collections.defaultdict(set)
                for al, ad in u["inst"]:
                    for c in get(al, ad):
                        nm = cur_name(al, c, "func")
                        cnt[nm] += 1
                        bins[nm].add(al)
                xref_names |= set(cnt)
                L.append(f"### {title}: {len(cnt)} distinct names, {sum(cnt.values())} edges")
                for nm, c in sorted(cnt.items(), key=lambda x: (-x[1], x[0]))[:CAP]:
                    L.append(f"- `{nm}` x{c} in {len(bins[nm])} binaries")
                if len(cnt) > CAP:
                    L.append(f"- ... +{len(cnt) - CAP} more")
        # data read / written
        L += ["", "## Data read and written"]
        if kind == "func":
            rw = {}
            code_lines, inc = [], False
            for ln in body_text.split("\n"):
                c, inc = strip_code(ln, inc)
                code_lines.append(c)
            is_asm = not prim_body and asm_path
            for c in code_lines:
                for m in TOK.finditer(c):
                    t = m.group(0)
                    if not (re.match(r"^D_[0-9A-Fa-f]{8}$", t) or t in datanames) or c[m.end():].lstrip().startswith("("):
                        continue
                    if is_asm:
                        w = bool(re.match(r"\s*s[bhwd]\b|\s*swc", c))
                    else:
                        w = bool(re.match(WRE, c[m.end():])) or bool(re.search(r"(?:\+\+|--)\s*$", c[:m.start()]))
                    rw[t] = rw.get(t, False) or w
            for t in sorted(rw):
                L.append(f"- `{t}` {'W' if rw[t] else 'R'}")
            if not rw:
                L.append("none found (text-level)")
            u["data_refs"] = rw
        else:
            rd, wr = collections.Counter(), collections.Counter()
            nuse = 0
            for p, ln, n, t, k in u["uses"]:
                if k != "use":
                    continue
                nuse += 1
                c = strip_code(t, False)[0]
                fn = res.get(p, ({}, {}))[0].get(ln) or f"<top-level {p}>"
                m = re.search(rf"\b{re.escape(n)}\b", c)
                w = bool(m and (re.match(WRE, c[m.end():]) or re.search(r"(?:\+\+|--)\s*$", c[:m.start()])))
                (wr if w else rd)[fn] += 1
                if not fn.startswith("<"):
                    xref_names.add(fn)
            L.append(f"use lines {nuse}; writer functions {len(wr)}, reader functions {len(rd)}")
            for title, cnt in (("writers", wr), ("readers", rd)):
                L.append(f"### {title}")
                for nm, c in sorted(cnt.items(), key=lambda x: (-x[1], x[0]))[:CAP]:
                    L.append(f"- `{nm}` x{c}")
                if len(cnt) > CAP:
                    L.append(f"- ... +{len(cnt) - CAP} more")
        # strings
        L += ["", "## Strings"]
        strs = []
        if prim_body:
            in_asm = False
            for ln in prim_body.split("\n"):
                if ln.lstrip().startswith(("#include", "INCLUDE_ASM")):
                    continue
                if re.search(r"\b(?:__asm__|asm)\b\s*(?:volatile\s*|__volatile__\s*)?\(", ln):
                    in_asm = True  # inline-asm text is not a game string
                if in_asm:
                    in_asm = not re.search(r"\)\s*;", ln)
                    continue
                for m in STRLIT.finditer(ln.split("//")[0]):
                    strs.append(f"literal {m.group(0)[:120]}")
        pal = u["prim"][0] if u["prim"] else "main"
        refs = list(u.get("data_refs", {}))
        if kind == "data":
            refs = [n0]
        for t in refs:
            m = re.match(r"^D_([0-9A-Fa-f]{8})$", t)
            ad = int(m.group(1), 16) if m else datanames.get(t)
            if ad is None:
                continue
            for al in (pal, "main", "resident"):
                if (al, ad) in asm_strs:
                    s, where = asm_strs[(al, ad)]
                    strs.append(f"data `{t}` .asci {s} ({where})")
                    break
        L += [f"- {s}" for s in strs[:CAP]] or ["none"]
        # doc hits
        hexs = set()
        for ad in addrs:
            h = f"{ad:08x}"
            hexs.add(h)
            if h.startswith("80"):
                hexs.add("00" + h[2:])
        are = re.compile(r"(?i)(?<![0-9a-f])(?:0x)?(?:" + "|".join(sorted(hexs)) + r")(?![0-9a-f])")
        nre = re.compile(r"\b(?:" + "|".join(re.escape(n) for n in sorted(u["ndirs"])) + r")\b")
        L += ["", "## Doc hits (memory-map, debug-menu-list, ghidra comments)"]
        dhits, dbg_hit, ghid_rep, mm_exact = [], False, False, False
        for p, ln, t, dbg in docs:
            ah, nh = bool(are.search(t)), bool(nre.search(t))
            if ah or nh:
                dhits.append(f"- {p}:{ln} [{'addr' if ah else ''}{'+' if ah and nh else ''}{'name' if nh else ''}] {t[:200]}")
                # T6 expert: prose in a debug section (e.g. the web-API gotcha naming 0x80000000) is no evidence; only table rows or the list
                dbg_hit = dbg_hit or (dbg and (p != 'docs/memory-map.md' or t.lstrip().startswith('|')))
                if p.startswith("config/ghidra") and "REPORTED" in t:
                    ghid_rep = True
                if p == "docs/memory-map.md" and ah:
                    mm_exact = True
        L += dhits or ["none"]
        u["mm_exact"] = mm_exact
        cov = [r for r in mrows if any(r[0] <= ad <= r[1] for ad in addrs)]
        ecov = [r for r in cov if r[1] - r[0] <= REGION]  # whole-blob region rows are not evidence
        blk = [b for b in blocks if any(b[0] <= ad <= b[1] for ad in addrs)] if kind == "data" else []
        u["blocks"] = blk
        if kind == "data":
            L += ["", "## Memory-map rows and blocks covering the address"]
            L += [f"- row {'docs/memory-map.md'}:{r[4]} conf `{r[2][:30]}`{' (region row, not evidence)' if r[1] - r[0] > REGION else ''} {r[5][:200]}" for r in cov]
            L += [f"- block docs/memory-map.md:{b[2]} {b[3][:200]}" for b in blk]
            if not cov and not blk:
                L.append("none")
        # owner
        if u["owner"]:
            T = u["owner"]
            hre = re.compile(rf"^(?:extern\s+)?(?:static\s+)?(?:volatile\s+)?(?:const\s+)?(?:struct\s+)?{re.escape(T)}\b\s*\**\s*[A-Za-z_]\w*\s*(?:\[|;|=)")
            hold = [(p, n, t) for p, n, t in own_hits if hre.match(t)]
            L += ["", f"## Owner struct `{T}`: {len(hold)} holder declarations"]
            L += [f"- {p}:{n} {t.strip()[:200]}" for p, n, t in hold[:20]]
            if len(hold) > 20:
                L.append(f"- ... +{len(hold) - 20} more")
        # evidence
        kinds = []
        if any(re.search(r"verified", r[2], re.I) and not re.search(r"unverified", r[2], re.I)
               and re.search(r"live|RAM", r[3] + " " + r[6]) for r in ecov):
            kinds.append("live RAM verified")
        if dbg_hit:
            kinds.append("debug menu")
        # weak = every string is shorter than 4 chars (splat's .asciz guess on a 4-byte word, e.g. "ENE")
        u["weakstr"] = bool(strs) and all(len(re.search(r'"(.*)"', x).group(1)) < 4 if re.search(r'"(.*)"', x) else False
                                          for x in strs)
        if strs and not u["weakstr"]:  # T6 expert: a <4-char .asciz (splat's word guess) is no string evidence
            kinds.append("string")
        cited = [x for x in xref_names if not is_place(x) and not x.startswith("guess_") and x != n0]
        lib = [x for x in cited if evid_of.get(x) == "library symbol"]
        game = [x for x in cited if evid_of.get(x) != "library symbol"]
        if cited:
            kinds.append("xref chain")
        if any(re.search(r"reported", r[2], re.I) for r in ecov) or ghid_rep:
            kinds.append("community reported")
        if not kinds:
            kinds.append("code only")
        primk = min(kinds, key=PRIO.index)
        u["kinds"], u["primk"], u["xsub"] = kinds, primk, ("game" if game else "") + ("+lib" if lib else "")
        L += ["", "## Evidence", f"kinds: {', '.join(kinds)}; primary: {primk}"]
        if cited:
            L.append(f"xref cited names: game {len(game)} ({', '.join(sorted(game)[:20])}); "
                     f"library {len(lib)} ({', '.join(sorted(lib)[:20])})")
        with open(f"{DOS}/R{u['rank']}_{u['name']}.md", "w", encoding="utf-8") as f:
            f.write("\n".join(L) + "\n")
        tsv.append([u["rank43"], kind, u["name"], n0, ",".join(kinds), primk])

    # evidence.tsv + summary (full runs only overwrite; subset runs write *.subset)
    sfx = "" if not a.ranks else ".subset"
    with open(f"{OUT}/evidence{sfx}.tsv", "w") as f:
        f.write("rank43\tkind\toldname\tcurrent\tevidence-kinds\tprimary\n")
        for r in tsv:
            f.write("\t".join(r) + "\n")
    S = [f"# T6.c1 evidence summary: {len(units)} units (worklist distinct {nall}, duplicate rows dropped {dup_rows})"]
    for kd in ("func", "data", "all"):
        us = [u for u in units if kd == "all" or u["kind"] == kd]
        S.append(f"\n## {kd} ({len(us)})")
        for k in PRIO:
            S.append(f"{k}: any-of {sum(k in u['kinds'] for u in us)}, primary {sum(u['primk'] == k for u in us)}")
        xs = collections.Counter(u["xsub"] for u in us if "xref chain" in u["kinds"])
        S.append(f"xref sub-split: game-only {xs['game']}, library-only {xs['+lib']}, both {xs['game+lib']}")
        S.append(f"string units whose strings are all < 4 chars: {sum(u['weakstr'] for u in us)}")
    S.append("\n## controls")
    for nm in ("func_8002D4C8", "D_80078EB4", "D_80078EB2", "D_800B99F6", "D_80078EAF", "D_80000000"):
        us = [u for u in units if u["name"] == nm]
        S.append(f"{nm}: " + (f"memory-map exact addr hit {us[0]['mm_exact']}" if us else "not in run"))
    bc = collections.Counter()
    for u in units:
        for b in u["blocks"]:
            bc[f"{b[3].strip('# ')[:60]} (line {b[2]})"] += 1
    for k, v in sorted(bc.items()):
        S.append(f"data units in block {k}: {v}")
    wall = time.time() - t0
    S.append(f"\nwall {wall:.1f} s (sig {t_sig:.1f}, grep {t_grep:.1f}, files {t_files:.1f}); grep hit lines {len(hits)}, "
             f"files parsed {len(jobs)}, names grepped {len(allnames)}")
    with open(f"{OUT}/evidence_summary{sfx}.txt", "w") as f:
        f.write("\n".join(S) + "\n")
    print("\n".join(S))
    print(f"wrote {len(units)} dossiers to {DOS}")


if __name__ == "__main__":
    main()
