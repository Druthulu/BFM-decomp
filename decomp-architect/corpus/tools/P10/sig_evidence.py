#!/usr/bin/env python3
"""sig_evidence.py — the asm signature census (3.44 T3). Spec: docs/ops/sig-evidence.md.

Measures every function class's calling contract from the ORIGINAL bytes (never the C): return used / unused /
unknown with a closed reason list, argument reads and site setup, width evidence. Cites are
`<binary>:0x<vaddr> <insn>` at the instance's own vaddr.

  sig_evidence.py [-j N] [--only alias,...]    # census -> build/sig_evidence/{census.jsonl,summary.txt}
  sig_evidence.py --selftest                   # in-memory fixtures, one per rule
  sig_evidence.py --show <binary>:<vaddr>      # print the census row holding that instance
"""
import argparse, array, collections, hashlib, json, os, pathlib, re, struct, sys

REPO = pathlib.Path(__file__).resolve().parent.parent
try:
    import rabbitizer as R
except ImportError:                       # rabbitizer lives in .venv only (requirements-python.txt:21)
    venv = REPO / ".venv" / "bin" / "python"
    if os.environ.get("SIG_EVIDENCE_REEXEC") or not venv.exists():
        raise
    os.environ["SIG_EVIDENCE_REEXEC"] = "1"
    os.execv(str(venv), [str(venv), str(pathlib.Path(__file__).resolve()), *sys.argv[1:]])

OUT_DIR = REPO / "build" / "sig_evidence"
M32 = 0xFFFFFFFF
V0, V1, A0, SP, FP, RA = 2, 3, 4, 29, 30, 31
CLOBBER = (1 << 1) | (1 << 2) | (1 << 3) | (0xF << 4) | (0xFF << 8) | (1 << 24) | (1 << 25) | (1 << 31)
EXIT, LEAVE, UNRES, TAIL = -1, -2, -3, -4          # CFG terminals: jr $ra, past the end, jr <reg> unresolved, j out
ENTRY = -1                                         # reaching-def id for "not written since entry"
REASONS = ["indirect call", "address taken", "tail position unresolved", "recursion", "jump table with $v0 live",
           "path leaves body", "cross-binary target unresolved", "no callers", "frame unresolved",
           "no width evidence"]
RANK = {r: i for i, r in enumerate(REASONS)}
SPECIAL = {0x00: "sll", 0x02: "srl", 0x03: "sra", 0x20: "add", 0x21: "addu", 0x25: "or"}
PRIMARY = {0x08: "addi", 0x09: "addiu", 0x0C: "andi", 0x0D: "ori", 0x0F: "lui", 0x20: "lb", 0x21: "lh",
           0x22: "lwl", 0x23: "lw", 0x24: "lbu", 0x25: "lhu", 0x26: "lwr", 0x28: "sb", 0x29: "sh", 0x2A: "swl",
           0x2B: "sw", 0x2E: "swr"}
LOADS = {"lb", "lh", "lwl", "lw", "lbu", "lhu", "lwr"}
STORES = {"sb", "sh", "swl", "sw", "swr"}
NARROW_LOAD = {"lbu": "u8", "lb": "s8", "lhu": "u16", "lh": "s16"}


def make_insn(word, vram):
    """tools/sig_image.py:37 — cop2/GTE words (opcode 0x12) need the GTE category."""
    if (word >> 26) == 0x12:
        try:
            return R.Instruction(word, vram, category=R.InstrCategory.R3000GTE)
        except Exception:
            pass
    return R.Instruction(word, vram)


class Ins:
    """One decoded word, vram-independent (targets are computed from the raw fields)."""
    __slots__ = ("word", "op", "rs", "rt", "rd", "sa", "simm", "uimm", "reads", "writes", "kind", "ds")

    def __init__(self, w):
        x = make_insn(w, 0x80000000)
        self.word = w
        self.rs, self.rt, self.rd, self.sa = (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, (w >> 6) & 31
        self.uimm = w & 0xFFFF
        self.simm = self.uimm - 0x10000 if self.uimm & 0x8000 else self.uimm
        p = w >> 26
        self.op = SPECIAL.get(w & 63, "other") if p == 0 else PRIMARY.get(p, "other")
        reads = writes = 0
        kind = None
        if x.isValid():
            if x.readsRs(): reads |= 1 << self.rs
            if x.readsRt(): reads |= 1 << self.rt   # lwl/lwr: write-only (the unaligned pair overwrites rt)
            if x.readsRd(): reads |= 1 << self.rd
            if x.modifiesRt(): writes |= 1 << self.rt
            if x.modifiesRd(): writes |= 1 << self.rd
            if x.modifiesRs(): writes |= 1 << self.rs
            if x.isFunctionCall():
                kind = "jalr" if (p == 0) else ("jal" if p == 3 else "bal")
                writes |= 1 << RA
            elif x.isJrRa():
                kind = "ret"
            elif x.isJrNotRa():
                kind = "jr"
            elif x.isJump():
                kind = "j"
            elif x.isBranch():
                kind = "b" if x.isUnconditionalBranch() else "br"
        self.reads, self.writes = reads & ~1, writes & ~1
        self.kind = kind
        self.ds = kind is not None

    def target(self, vram):
        if self.kind in ("j", "jal"):
            return ((vram + 4) & 0xF0000000) | ((self.word & 0x3FFFFFF) << 2)
        return (vram + 4 + self.simm * 4) & M32


_DEC = {}


def dec(w):
    x = _DEC.get(w)
    if x is None:
        x = _DEC[w] = Ins(w)
    return x


def read_kind(x, reg):
    """RET-READ / W-ARG-USE kind of a read of `reg` by x."""
    if x.op == "andi" and x.rs == reg:
        return f"andi:0x{x.uimm:x}"
    if x.op == "sll" and x.rt == reg:
        return f"sll:{x.sa}"
    if x.op in ("sb", "sh") and x.rt == reg and x.rs != reg:
        return x.op
    return "full"


# ----------------------------------------------------------------------------------------------- per-class analysis
def analyze(words, start, img_base, img_data):
    n = len(words)
    end = start + 4 * n
    ins = [dec(w) for w in words]

    def idx(t):
        return (t - start) >> 2 if start <= t < end and not (t - start) & 3 else None

    # linear lui/%lo tracking: formed constants (address taken) and the latest table candidate per insn
    hi, der, consts, latest = {}, {}, set(), None
    cand = [None] * n
    for i, x in enumerate(ins):
        cand[i] = latest
        nh = nd = None
        if x.op == "lui":
            nh = (x.rt, (x.uimm << 16) & M32)
        elif x.op in ("addiu", "addi") and x.rs in hi:
            v = (hi[x.rs] + x.simm) & M32
            consts.add(v)
            latest = v
        elif x.op == "ori" and x.rs in hi:
            v = hi[x.rs] | x.uimm
            consts.add(v)
            latest = v
        elif x.op in LOADS and (x.rs in hi or x.rs in der):
            latest = (hi.get(x.rs, der.get(x.rs, 0)) + x.simm) & M32
        elif x.op == "addu" and (x.rs in hi) != (x.rt in hi):
            nd = (x.rd, hi[x.rs] if x.rs in hi else hi[x.rt])
        w = x.writes
        if w:
            for r in [r for r in hi if w >> r & 1]: del hi[r]
            for r in [r for r in der if w >> r & 1]: del der[r]
        if nh: hi[nh[0]] = nh[1]
        if nd: der[nd[0]] = nd[1]

    # CFG with delay slots: a CTI's transfer happens after its delay slot (the DS node carries the edges)
    succ = [None] * n
    call_ds = {}          # ds index -> site index
    sites = []            # [c, kind, target]
    rets, tabs = [], [0, 0]
    for i in range(n):
        nxt = i + 1 if i + 1 < n else LEAVE
        if i > 0 and ins[i - 1].ds:
            c = i - 1
            cx = ins[c]
            k = cx.kind
            if k in ("jal", "jalr", "bal"):
                call_ds[i] = len(sites)
                sites.append([c, k, None if k == "jalr" else cx.target(start + 4 * c)])
                succ[i] = [nxt]
            elif k in ("br", "b"):
                t = idx(cx.target(start + 4 * c))
                tt = t if t is not None else LEAVE
                succ[i] = [tt, nxt] if k == "br" else [tt]
            elif k == "j":
                t = cx.target(start + 4 * c)
                ti = idx(t)
                if ti is not None:
                    succ[i] = [ti]
                else:
                    call_ds[i] = len(sites)
                    sites.append([c, "j", t])
                    succ[i] = [TAIL]
            elif k == "ret":
                rets.append(c)
                succ[i] = [EXIT]
            else:                                                  # jr <reg>: jump table
                base, tg = cand[c], []
                if base is not None:
                    o = base - img_base
                    while 0 <= o <= len(img_data) - 4 and len(tg) < 4096:
                        ti = idx(struct.unpack_from("<I", img_data, o)[0])
                        if ti is None:
                            break
                        tg.append(ti)
                        o += 4
                tabs[0 if tg else 1] += 1
                succ[i] = sorted(set(tg)) if tg else [UNRES]
        else:
            succ[i] = [nxt]
    preds = [[] for _ in range(n)]
    for i in range(n):
        for s in succ[i]:
            if s >= 0:
                preds[s].append(i)

    # frame: entry-$sp offset of $sp / $fp (int), "nf" ($fp not a frame copy), "conf" (paths disagree)
    spin, fpin = [None] * n, [None] * n
    spin[0], fpin[0] = 0, "nf"
    work = collections.deque([0])

    def mv_from(x, src):
        return x.op in ("addu", "or", "add") and ((x.rs == src and x.rt == 0) or (x.rt == src and x.rs == 0))

    def frame_out(m):
        x, sp, fp = ins[m], spin[m], fpin[m]
        if x.writes >> SP & 1:
            if x.op in ("addiu", "addi") and x.rs == SP:
                sp = sp + x.simm if type(sp) is int else "conf"
            elif x.op in ("addiu", "addi") and x.rs == FP:
                sp = fp + x.simm if type(fp) is int else "conf"
            elif mv_from(x, FP):
                sp = fp if type(fp) is int else "conf"
            else:
                sp = "conf"
        if x.writes >> FP & 1:
            if mv_from(x, SP):
                fp = spin[m] if type(spin[m]) is int else "conf"
            elif x.op in ("addiu", "addi") and x.rs == SP:
                fp = spin[m] + x.simm if type(spin[m]) is int else "conf"
            else:
                fp = "nf"
        return sp, fp

    while work:
        m = work.popleft()
        sp, fp = frame_out(m)
        for s in succ[m]:
            if s < 0:
                continue
            ch = False
            if spin[s] is None:
                spin[s], fpin[s], ch = sp, fp, True
            else:
                if spin[s] != sp and spin[s] != "conf":
                    spin[s], ch = "conf", True
                if fpin[s] != fp and fpin[s] != "conf":
                    fpin[s], ch = "conf", True
            if ch:
                work.append(s)
    acc, unresolved = [], []                  # acc: (m, is_load, entry_off)
    fp_frame = any(type(v) is int for v in fpin)
    for m, x in enumerate(ins):
        if spin[m] is None or not (x.op in LOADS or x.op in STORES) or x.rs not in (SP, FP):
            continue
        b = spin[m] if x.rs == SP else fpin[m]
        if b == "nf":
            continue
        if b == "conf":
            unresolved.append(m)
            continue
        acc.append((m, x.op in LOADS, b + x.simm))

    # ARG-READ / ARG-PASS / W-ARG-USE: incoming $a_k reachability from entry
    arg_read, arg_pass, incoming = {}, set(), []
    for k in range(4):
        bit, seen, stack, first = 1 << (A0 + k), set(), [0], None
        while stack:
            m = stack.pop()
            if m < 0:
                if m == TAIL:
                    arg_pass.add(k)
                continue
            if m in seen:
                continue
            seen.add(m)
            x = ins[m]
            if x.reads & bit and (first is None or m < first):
                first = m
            if x.writes & bit:
                continue
            if m in call_ds:
                arg_pass.add(k)
                continue
            stack.extend(succ[m])
        incoming.append(seen)
        if first is not None:
            arg_read[k] = (first, read_kind(ins[first], A0 + k))
    stack_reads = {}
    for m, ld, eo in acc:
        if ld and eo >= 16:
            k = 4 + (eo - 16) // 4
            if k not in stack_reads or m < stack_reads[k]:
                stack_reads[k] = m
    spilled = {eo // 4 for m, ld, eo in acc
               if not ld and ins[m].op == "sw" and eo in (0, 4, 8, 12) and ins[m].rt == A0 + eo // 4
               and m in incoming[eo // 4]}
    varargs = None
    if 3 in spilled:
        varargs = 3
        while varargs - 1 in spilled:
            varargs -= 1

    # ARG-SITE: arg slots written on every path since entry / the previous call event (must, intersection)
    gen = [(x.writes >> A0) & 0xF for x in ins]
    loaded = {eo >> 2 for m, ld, eo in acc if ld}       # a slot the function reads back is a local/save
    taken_lo = min([(spin[m] if x.rs == SP else fpin[m]) + x.simm for m, x in enumerate(ins)
                    if x.op in ("addiu", "addi") and x.rs in (SP, FP) and x.rt not in (SP, FP)
                    and type(spin[m] if x.rs == SP else fpin[m]) is int], default=1 << 30)
    for m, ld, eo in acc:                              # outgoing args lie below the first address-taken local
        if not ld and type(spin[m]) is int and eo - spin[m] >= 16 and eo >> 2 not in loaded and eo < taken_lo:
            k = 4 + (eo - spin[m] - 16) // 4
            if k < 60:
                gen[m] |= 1 << k
    inm = [None] * n
    inm[0] = 0
    work = collections.deque([0])
    while work:
        m = work.popleft()
        out = 0 if m in call_ds else inm[m] | gen[m]
        for s in succ[m]:
            if s >= 0:
                v = out if inm[s] is None else inm[s] & out
                if v != inm[s]:
                    inm[s] = v
                    work.append(s)

    # reaching definitions of $v0, $a0-$a3 (RET-EXIT, W-ARG-SITE)
    regs = (V0, A0, A0 + 1, A0 + 2, A0 + 3)
    rin = [None] * n
    rin[0] = tuple(frozenset((ENTRY,)) for _ in regs)

    def rd_pre(m):
        x, cur = ins[m], rin[m]
        return tuple(frozenset((m,)) if x.writes >> r & 1 else cur[j] for j, r in enumerate(regs))

    work = collections.deque([0])
    while work:
        m = work.popleft()
        out = rd_pre(m)
        if m in call_ds:
            out = tuple(frozenset((-2 - (m - 1),)) for _ in regs)
        for s in succ[m]:
            if s >= 0:
                v = out if rin[s] is None else tuple(a | b for a, b in zip(rin[s], out))
                if v != rin[s]:
                    rin[s] = v
                    work.append(s)

    def narrow(m, reg):
        if m < 0:
            return None
        x = ins[m]
        if x.op == "andi" and x.rt == reg:
            return {0xFF: "u8", 0xFFFF: "u16"}.get(x.uimm)
        if x.op in NARROW_LOAD and x.rt == reg:
            return NARROW_LOAD[x.op]
        if x.op in ("sra", "srl") and x.rd == reg and x.sa in (16, 24):
            for j in range(m - 1, -1, -1):
                y = ins[j]
                if y.writes >> x.rt & 1:
                    if y.op == "sll" and y.rd == x.rt and y.sa == x.sa:
                        return ("s" if x.op == "sra" else "u") + ("8" if x.sa == 24 else "16")
                    break
        return None

    # per-site outcomes: RET-READ / RET-V1 / RET-DEAD / RET-TAIL and setup
    def scan(d, reg):
        bit, first, terms, seen = 1 << reg, None, set(), set()
        stack = list(succ[d])
        while stack:
            m = stack.pop()
            if m < 0:
                terms.add(m)
                continue
            if m in seen:
                continue
            seen.add(m)
            x = ins[m]
            if x.reads & bit:
                if first is None or m < first:
                    first = m
                continue
            if x.writes & bit or m in call_ds:
                continue
            stack.extend(succ[m])
        return first, terms

    out_sites = []
    for d, si in sorted(call_ds.items()):
        c, kind, t = sites[si]
        if kind == "j":
            oc = {"tail": True}
        else:
            r0, t0 = scan(d, V0)
            r1, t1 = scan(d, V1)
            oc = {}
            if r0 is not None:
                oc["read"] = [r0, read_kind(ins[r0], V0)]
            if r1 is not None:
                oc["v1"] = r1
            if EXIT in t0:
                oc["tail"] = True
            rs = []
            if UNRES in t0: rs.append("jump table with $v0 live")
            if LEAVE in t0: rs.append("path leaves body")
            if rs:
                oc["reasons"] = rs
        setup = 0 if inm[d] is None else inm[d] | gen[d]
        k = 4
        while setup >> k & 1:                          # stack slots count as a contiguous run from $sp+16
            k += 1
        setup = (setup & 0xF) | (setup & ((1 << k) - 1))
        pre = rd_pre(d) if rin[d] is not None else None
        widths = {}
        for k in range(4):
            if setup >> k & 1 and pre is not None:
                cls = {narrow(m, A0 + k) for m in pre[1 + k]}
                if len(cls) == 1 and None not in cls:
                    widths[k] = cls.pop()
        out_sites.append([c, kind, t, oc, setup.bit_length(), widths])

    exits = []
    for c in rets:
        d = c + 1
        if d >= n or rin[d] is None:
            continue
        ws = sorted(rd_pre(d)[0])
        exits.append([c, ws])
    ret_narrow = sorted({cl for c, ws in exits for m in ws if (cl := narrow(m, V0))})
    exits = [[c, [("call", ins[-2 - m].kind, ins[-2 - m].target(start - 8 - 4 * m)
                   if ins[-2 - m].kind != "jalr" else None) if m <= -2 else m for m in ws]] for c, ws in exits]
    return {"n": n, "sites": out_sites, "exits": exits, "ret_narrow": ret_narrow,
            "arg_read": sorted(arg_read.items()), "stack_reads": sorted(stack_reads.items()),
            "arg_pass": sorted(arg_pass), "varargs": varargs, "fp": fp_frame, "unresolved": unresolved,
            "consts": sorted(consts), "tabs": tabs}


# ----------------------------------------------------------------------------------------------- fleet
class Fleet:
    """bins: alias -> {"base", "data", "stack": [aliases], "rows": [(vaddr, nbytes, h, name)]}"""

    def __init__(self, bins):
        self.bins = bins


_FLEET = None


def _work(task):
    b, va, nb = task
    B = _FLEET.bins[b]
    o = va - B["base"]
    if o < 0 or o + nb > len(B["data"]) or nb % 4:
        raise ValueError(f"sig_evidence: body {b}:0x{va:08X}+{nb} outside the image")
    words = struct.unpack_from(f"<{nb // 4}I", B["data"], o)
    return analyze(words, va, B["base"], B["data"])


def mk_vars():
    texts = [(REPO / "Makefile").read_text()] + [p.read_text() for p in sorted((REPO / "config").glob("*.mk"))]
    var = {}
    for t in texts:
        for m in re.finditer(r"^(\w+?)_(EXE|SIG|SPLAT_YAML|VRAM_BASE)\s*:?=\s*(\S+)", t, re.M):
            var[(m.group(1), m.group(2))] = m.group(3)
    lists = {}
    for t in texts:
        for m in re.finditer(r"^(OVERLAY_BINARIES|MODULE_BINARIES)\s*:?=\s*(.*)$", t, re.M):
            lists[m.group(1)] = m.group(2).split()
    return ["main", "resident"] + lists.get("OVERLAY_BINARIES", []) + lists.get("MODULE_BINARIES", []), var


def yaml_stack(path, aliases):
    lines = (REPO / path).read_text().splitlines()
    out, on = [], False
    for ln in lines:
        s = ln.strip()
        if s.startswith("symbol_addrs_path:"):
            on = True
            continue
        if on:
            if not s or s.startswith("#"):
                continue
            if not s.startswith("- "):
                break
            f = pathlib.Path(s[2:].strip()).name
            m = re.fullmatch(r"symbols\.(.+)\.txt", f)
            a = {"us": "main"}.get(m.group(1), m.group(1)) if m else None
            if a in aliases:
                out.append(a)
    return out


def own_names(path):
    names = {}
    for ln in (REPO / path).read_text().splitlines():
        m = re.match(r"\s*([A-Za-z_.$][\w.$]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;(.*)$", ln)
        if m:
            a, isf = int(m.group(2), 16), "func" in m.group(3)
            if a not in names or (isf and not names[a][1]):
                names[a] = (m.group(1), isf)
    return {a: v[0] for a, v in names.items()}


def load_fleet(only=None):
    aliases, var = mk_vars()
    aset = set(aliases)
    stacks = {}
    for a in aliases:
        st = yaml_stack(var[(a, "SPLAT_YAML")], aset)
        if a not in st:
            raise SystemExit(f"sig_evidence: {a}'s symbol stack {st} does not hold its own file (contract)")
        stacks[a] = st
    keep = list(aliases)
    if only:
        want = set(only)
        bad = want - aset
        if bad:
            raise SystemExit(f"sig_evidence: --only names unknown binaries {sorted(bad)}")
        for a in list(want):
            want |= set(stacks[a])
        keep = [a for a in aliases if a in want]
    bins = {}
    for a in keep:
        sigp = REPO / var[(a, "SIG")]
        if not sigp.exists():
            raise SystemExit(f"sig_evidence: {sigp.relative_to(REPO)} missing; refuse to measure a partial fleet (R43)")
        st = stacks[a]
        own = own_names(f"config/symbols.{'us' if a == 'main' else a}.txt")
        rows = []
        for ln in sigp.read_text().splitlines():
            if not ln.strip():
                continue
            r = json.loads(ln)
            if r.get("src") == "IMPORTED" or not r.get("nins"):
                continue
            va = int(r["addr"], 16)
            rows.append((va, int(r["nbytes"]), r["h_exact"], own.get(va, r.get("name", ""))))
        bins[a] = {"base": int(var[(a, "VRAM_BASE")], 16), "data": (REPO / var[(a, "EXE")]).read_bytes(),
                   "stack": st, "rows": rows}
    return Fleet(bins), (set(only) if only else set(keep))


# ----------------------------------------------------------------------------------------------- census
def hx(v):
    return f"0x{v:08X}"


def cite(fleet, b, va):
    B = fleet.bins[b]
    w = struct.unpack_from("<I", B["data"], va - B["base"])[0]
    return f"{b}:{hx(va)} " + " ".join(make_insn(w, va).disassemble().split())


def tarjan(nodes, edges):
    """Iterative Tarjan; SCCs emitted so that an SCC comes after every SCC its edges reach."""
    index, low, on, st, out, cnt = {}, {}, set(), [], [], 0
    for root in nodes:
        if root in index:
            continue
        work = [(root, 0)]
        while work:
            v, i = work.pop()
            if i == 0:
                index[v] = low[v] = cnt
                cnt += 1
                st.append(v)
                on.add(v)
            es = edges.get(v, ())
            recurse = False
            while i < len(es):
                w = es[i]
                i += 1
                if w not in index:
                    work.append((v, i))
                    work.append((w, 0))
                    recurse = True
                    break
                if w in on:
                    low[v] = min(low[v], index[w])
            if recurse:
                continue
            if low[v] == index[v]:
                comp = []
                while True:
                    w = st.pop()
                    on.discard(w)
                    comp.append(w)
                    if w == v:
                        break
                out.append(sorted(comp))
            if work:
                u = work[-1][0]
                low[u] = min(low[u], low[v])
    return out


def census(fleet, measured, jobs):
    global _FLEET
    _FLEET = fleet
    bins = fleet.bins
    classes = collections.defaultdict(list)
    cls_of = {}
    for b in sorted(bins):
        for va, nb, h, name in bins[b]["rows"]:
            cls_of[(b, va)] = h
            classes[h].append((b, va, nb, name))
    for h in classes:
        classes[h].sort()
    order = sorted(classes, key=lambda h: classes[h][0][:2])
    tasks = [classes[h][0][:3] for h in order]
    if jobs > 1:
        import multiprocessing as mp
        with mp.get_context("fork").Pool(jobs) as p:
            res = dict(zip(order, p.imap(_work, tasks, chunksize=16)))
    else:
        res = dict(zip(order, map(_work, tasks)))

    # address taken: aligned image words + lui/addiu|ori constants, of every binary whose stack holds the target's
    # a reference outside every image of the referrer's stack (a module calling the overlay loaded beside it) is
    # resolved fleet-wide by function start: at_va[va] = the classes of every row starting at va
    starts = collections.defaultdict(set)
    at_va, owners = collections.defaultdict(set), collections.defaultdict(list)
    for b, va in cls_of:
        starts[b].add(va)
        at_va[va].add(cls_of[(b, va)])
        owners[va].append(b)
    allstarts = set(va for _, va in cls_of)
    taken = collections.defaultdict(set)
    for c in sorted(bins):
        B = bins[c]
        o = (-B["base"]) % 4
        arr = array.array("I")
        arr.frombytes(B["data"][o:o + (len(B["data"]) - o) // 4 * 4])
        if sys.byteorder != "little":
            arr.byteswap()
        X = allstarts.intersection(arr)
        for va, nb, h, name in B["rows"]:
            X |= allstarts.intersection(res[h]["consts"])
        for b in B["stack"]:
            taken[b] |= X & starts[b]
        imgs = [(bins[b]["base"], bins[b]["base"] + len(bins[b]["data"])) for b in B["stack"]]
        for va in X:
            if not any(lo <= va < hi for lo, hi in imgs):
                for b in owners[va]:
                    taken[b].add(va)

    # sites, per caller instance
    S = collections.Counter()
    agg = {h: {"direct": 0, "read": [], "reads": collections.Counter(), "ret64": False, "tail": set(),
               "reasons": set(), "ar": [], "sw": collections.defaultdict(collections.Counter)} for h in order}
    for h in order:
        r = res[h]
        S["jump tables resolved (classes)"] += r["tabs"][0]
        S["jump tables unresolved (classes)"] += r["tabs"][1]
        rep_va = classes[h][0][1]
        for b, va, nb, name in classes[h]:
            if b not in measured:
                continue
            st = bins[b]["stack"]
            for c, kind, t, oc, arity, widths in r["sites"]:
                S["sites"] += 1
                S[f"sites {kind}"] += 1
                if kind == "jalr":
                    continue
                if kind == "bal":
                    t = (t - rep_va + va) & M32
                cl = [x for x in st if bins[x]["base"] <= t < bins[x]["base"] + len(bins[x]["data"])]
                if not cl:
                    hs = at_va.get(t)
                    if not hs:
                        S["sites outside stack: no sig row at target"] += 1
                        continue
                    if len(hs) > 1:
                        S["sites outside stack: several classes"] += 1
                        for g in hs:
                            agg[g]["reasons"].add("cross-binary target unresolved")
                        continue
                    S["sites outside stack: one class (credited)"] += 1
                    tc = next(iter(hs))
                else:
                    if len(cl) > 1:
                        S["sites cross-binary ambiguous"] += 1
                        for x in cl:
                            if (x, t) in cls_of:
                                agg[cls_of[(x, t)]]["reasons"].add("cross-binary target unresolved")
                        continue
                    if (cl[0], t) not in cls_of:
                        S["sites target has no sig row"] += 1
                        continue
                    tc = cls_of[(cl[0], t)]
                S["sites credited"] += 1
                A = agg[tc]
                A["direct"] += 1
                A["ar"].append(arity)
                for k, wc in widths.items():
                    A["sw"][k][wc] += 1
                if "read" in oc:
                    S["sites outcome read"] += 1
                    A["read"].append((b, va + 4 * oc["read"][0]))
                    A["reads"][oc["read"][1]] += 1
                if "v1" in oc:
                    S["sites outcome v1 read"] += 1
                    A["ret64"] = True
                    A["read"].append((b, va + 4 * oc["v1"]))
                if oc.get("tail"):
                    S["sites outcome tail"] += 1
                    A["tail"].add(h)
                for rs in oc.get("reasons", ()):
                    S[f"sites outcome {rs}"] += 1
                    A["reasons"].add(rs)
                if not ("read" in oc or "v1" in oc or oc.get("tail") or oc.get("reasons")):
                    S["sites outcome dead"] += 1

    # RET-FIX: tail graph callee -> caller, SCCs callers first
    verdict, rsn = {}, {}
    edges = {h: sorted(agg[h]["tail"], key=lambda g: classes[g][0][:2]) for h in order}
    for comp in tarjan(order, edges):
        cs = set(comp)
        used = any(agg[x]["read"] for x in comp) or any(
            verdict[y] == "used" for x in comp for y in edges[x] if y not in cs)
        cyc = len(comp) > 1 or any(x in edges[x] for x in comp)
        for x in comp:
            if used:
                verdict[x], rsn[x] = "used", []
                continue
            A, rs = agg[x], set(agg[x]["reasons"])
            tk = any(va in taken[b] for b, va, _, _ in classes[x])
            if tk:
                rs.add("address taken" if A["direct"] else "indirect call")
            elif not A["direct"]:
                rs.add("no callers")
            if cyc:
                rs.add("recursion")
            for y in edges[x]:
                if y not in cs and verdict[y] != "used" and verdict[y] != "unused":
                    rs.add("recursion" if verdict[y] == "unknown:recursion" else "tail position unresolved")
            rs = sorted(rs, key=RANK.get)
            rsn[x] = rs
            verdict[x] = f"unknown:{rs[0]}" if rs else "unused"

    rows, V, U, UA, X = [], collections.Counter(), collections.Counter(), collections.Counter(), collections.Counter()
    for h in order:
        r, A, inst = res[h], agg[h], classes[h]
        rb, rv = inst[0][:2]
        if not any(b in measured for b, *_ in inst):
            continue
        ret = {"verdict": verdict[h], "reasons": rsn[h],
               "cite": cite(fleet, *min(A["read"])) if A["read"] else None,
               "reads": dict(sorted(A["reads"].items())), "ret64": A["ret64"],
               "tail": sorted(f"{classes[g][0][0]}:{hx(classes[g][0][1])}" for g in A["tail"])}
        exits = [[cite(fleet, rb, rv + 4 * c),
                  sorted(("entry" if w == ENTRY else cite(fleet, rb, rv + 4 * w)) if type(w) is int else
                         (f"call {hx(w[2])}" if w[2] is not None else "call jalr") for w in ws)]
                 for c, ws in r["exits"]]
        read = [[k, cite(fleet, rb, rv + 4 * m)] for k, (m, kd) in r["arg_read"]] + \
               [[k, cite(fleet, rb, rv + 4 * m)] for k, m in r["stack_reads"]]
        use = {str(k): kd for k, (m, kd) in r["arg_read"]}
        site_w = {str(k): dict(sorted(c.items())) for k, c in sorted(A["sw"].items())}
        arity_lb = max([k for k, _ in read], default=-1) + 1
        ret_width = [f"exit:{c}" for c in r["ret_narrow"]] + [f"read:{k}" for k in sorted(A["reads"]) if k != "full"]
        areasons = []
        if r["unresolved"]:
            areasons.append("frame unresolved")
        if not (ret_width or site_w or any(v != "full" for v in use.values())):
            areasons.append("no width evidence")
        row = {"h": h, "nins": r["n"], "instances": [[b, hx(va), name] for b, va, nb, name in inst],
               "ret": ret, "exit": exits, "ret_width": ret_width,
               "args": {"read": read, "arity_lb": arity_lb, "passthrough": r["arg_pass"],
                        "sites": {"n": len(A["ar"]), "min": min(A["ar"], default=None),
                                  "max": max(A["ar"], default=None)},
                        "widths": {"site": site_w, "use": use}, "reasons": areasons},
               "varargs_spill": r["varargs"],
               "frame": {"kind": "fp" if r["fp"] else "sp",
                         "unresolved": [cite(fleet, rb, rv + 4 * m) for m in r["unresolved"]]}}
        rows.append(row)
        V[verdict[h].split(":")[0]] += 1
        if rsn[h]:
            U[rsn[h][0]] += 1
            for x in rsn[h]:
                UA[x] += 1
        for x in areasons:
            X[f"args {x}"] += 1
        X["ret64"] += A["ret64"]
        X["varargs_spill"] += r["varargs"] is not None
        X[f"frame {row['frame']['kind']}"] += 1
    summ = [f"classes {len(rows)}", f"instances {sum(len(r['instances']) for r in rows)}"]
    summ += [f"verdict {k} {V[k]}" for k in ("used", "unused", "unknown")]
    summ += [f"unknown verdict {k} {U[k]}" for k in REASONS[:8]]
    summ += [f"reason listed {k} {UA[k]}" for k in REASONS[:8]]
    summ += [f"{k} {X[k]}" for k in sorted(X)]
    summ += [f"{k} {S[k]}" for k in sorted(S)]
    return rows, "\n".join(summ) + "\n"


def dump(row):
    return json.dumps(row, sort_keys=True, separators=(",", ":"))


# ----------------------------------------------------------------------------------------------- selftest
def _r(f, rs=0, rt=0, rd=0, sa=0): return (rs << 21) | (rt << 16) | (rd << 11) | (sa << 6) | f
def _i(op, rs, rt, imm): return (op << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF)


class E:
    """Tiny MIPS I encoder (register numbers)."""
    nop = 0
    move = staticmethod(lambda d, s: _r(0x21, s, 0, d))
    addu = staticmethod(lambda d, s, t: _r(0x21, s, t, d))
    addiu = staticmethod(lambda t, s, imm: _i(0x09, s, t, imm))
    andi = staticmethod(lambda t, s, imm: _i(0x0C, s, t, imm))
    lui = staticmethod(lambda t, imm: _i(0x0F, 0, t, imm))
    sll = staticmethod(lambda d, t, sa: _r(0x00, 0, t, d, sa))
    lw = staticmethod(lambda t, off, s: _i(0x23, s, t, off))
    sw = staticmethod(lambda t, off, s: _i(0x2B, s, t, off))
    jal = staticmethod(lambda a: (3 << 26) | ((a >> 2) & 0x3FFFFFF))
    j = staticmethod(lambda a: (2 << 26) | ((a >> 2) & 0x3FFFFFF))
    jr = staticmethod(lambda s: _r(0x08, s))
    jalr = staticmethod(lambda s, d=31: _r(0x09, s, 0, d))
    beq = staticmethod(lambda s, t, off: _i(0x04, s, t, off))
    mfc2 = staticmethod(lambda t, d: (0x12 << 26) | (0 << 21) | (t << 16) | (d << 11))
    mtc2 = staticmethod(lambda t, d: (0x12 << 26) | (4 << 21) | (t << 16) | (d << 11))
    lwc2 = staticmethod(lambda t, off, s: _i(0x32, s, t, off))
    mflo = staticmethod(lambda d: _r(0x12, 0, 0, d))
    ret = [0x03E00008, 0]


def _fleet(spec):
    """spec: alias -> (base, size, stack, [(vaddr, words, name)], [(vaddr, dataword)])"""
    bins = {}
    for a, (base, size, stack, funcs, datas) in spec.items():
        data = bytearray(size)
        rows = []
        for va, ws, name in funcs:
            raw = struct.pack(f"<{len(ws)}I", *ws)
            data[va - base:va - base + len(raw)] = raw
            rows.append((va, len(raw), hashlib.sha1(raw).hexdigest(), name))
        for va, w in datas:
            struct.pack_into("<I", data, va - base, w)
        bins[a] = {"base": base, "data": bytes(data), "stack": stack, "rows": rows}
    return Fleet(bins)


def _rows(spec):
    f = _fleet(spec)
    rows, summ = census(f, set(f.bins), 1)
    by = {}
    for r in rows:
        for b, va, name in r["instances"]:
            by[name] = r
    return by, summ


def selftest():
    t9, t0, t1, at, s0, a1 = 25, 8, 9, 1, 16, 5
    M = 0x80010000
    F, G, H, K = M + 0x100, M + 0x200, M + 0x300, M + 0x400
    ok = True

    def check(name, cond, detail=""):
        nonlocal ok
        print(f"{'PASS' if cond else 'FAIL'} {name}{'' if cond else ' :: ' + str(detail)}")
        ok &= bool(cond)

    def one(funcs, datas=(), extra=None):
        spec = {"main": (M, 0x2000, ["main"], funcs, list(datas))}
        spec.update(extra or {})
        return _rows(spec)

    def fret(v=1):                               # a callee returning v (distinct v = distinct class)
        return [E.addiu(V0, 0, v)] + E.ret

    # register sets (cop2, mfhi/mflo, jalr) against the decoder
    x = dec(E.mfc2(V0, 5)); check("regs mfc2 writes rt", x.writes == 1 << V0 and not x.reads, (x.reads, x.writes))
    x = dec(E.mtc2(V0, 5)); check("regs mtc2 reads rt", x.reads == 1 << V0 and not x.writes, (x.reads, x.writes))
    x = dec(E.lwc2(V0, 8, A0)); check("regs lwc2 reads base only", x.reads == 1 << A0 and not x.writes)
    x = dec(E.mflo(V0)); check("regs mflo writes rd", x.writes == 1 << V0 and not x.reads)
    x = dec(E.jalr(t9)); check("regs jalr reads rs writes $ra", x.reads == 1 << t9 and x.writes == 1 << RA)
    x = dec(_i(0x22, A0, a1, 0)); check("regs lwl writes rt, reads base only", x.reads == 1 << A0 and x.writes == 1 << a1)

    # C0244 delay slot: `jal F; move a0,v0` reads v0 before F's call event; C0284: that move is F's setup
    by, _ = one([(F, fret(1), "F"), (G, [E.jal(F), E.move(A0, V0), E.jal(H), E.nop] + E.ret, "G"),
                 (H, fret(3), "H")])
    check("RET-READ delay slot is not the call's return (C0244)", by["F"]["ret"]["verdict"] == "unused",
          by["F"]["ret"])
    check("ARG-SITE delay-slot copy is setup (C0284)", by["F"]["args"]["sites"] == {"n": 1, "min": 1, "max": 1},
          by["F"]["args"]["sites"])
    check("RET-TAIL unresolved: caller has no callers",
          by["H"]["ret"]["verdict"] == "unknown:tail position unresolved", by["H"]["ret"])
    check("RET-EXIT writer instruction", by["F"]["exit"][0][1][0].startswith("main:0x80010100 addiu"),
          by["F"]["exit"])

    # ARG-SITE stack slots: $sp+16 store is argument 4; a reloaded slot ($sp+24 local, $ra save) and a slot at
    # or above an address-taken local ($sp+20, its address in $a0) are not
    g = [E.addiu(SP, SP, -32), E.sw(RA, 28, SP), E.sw(t1, 24, SP), E.sw(t0, 16, SP), E.sw(10, 20, SP),
         E.addiu(A0, SP, 20), E.jal(F), E.nop,
         E.lw(t1, 24, SP), E.lw(RA, 28, SP), E.jr(RA), E.addiu(SP, SP, 32)]
    by, _ = one([(F, fret(6), "F"), (G, g, "G")])
    check("ARG-SITE stack argument, reloaded slots excluded", by["F"]["args"]["sites"] == {"n": 1, "min": 5, "max": 5},
          by["F"]["args"]["sites"])

    # read on one branch arm only; W-ARG-SITE andi 0xff
    g = [E.andi(a1, t0, 0xFF), E.jal(F), E.nop, E.beq(A0, 0, 2), E.nop, E.addu(t0, V0, a1),
         E.addiu(V0, 0, 1)] + E.ret
    by, _ = one([(F, fret(1), "F"), (G, g, "G")])
    check("RET-READ one branch arm", by["F"]["ret"]["verdict"] == "used" and
          by["F"]["ret"]["cite"].startswith("main:0x80010214 addu"), by["F"]["ret"])
    check("W-ARG-SITE andi 0xff -> u8", by["F"]["args"]["widths"]["site"] == {"1": {"u8": 1}},
          by["F"]["args"]["widths"])

    # $v0 written before any read (and cop2 mfc2 as the writer)
    by, _ = one([(F, fret(1), "F"), (G, [E.jal(F), E.nop, E.mfc2(V0, 3), E.addu(t0, V0, A0)] + E.ret, "G")])
    check("RET-DEAD v0 written first (mfc2)", by["F"]["ret"]["verdict"] == "unused", by["F"]["ret"])

    # resolved tail call (jal + jr $ra) and tail jump (j), both through a reading caller
    by, _ = one([(F, fret(1), "F"), (G, [E.jal(F), E.nop] + E.ret, "G"),
                 (H, [E.jal(G), E.nop, E.addu(t0, V0, 0), E.jal(K), E.nop] + E.ret, "H"),
                 (K, [E.j(F + 0x40), E.nop], "K"), (F + 0x40, fret(4), "F2")])
    check("RET-TAIL/RET-FIX resolved tail call", by["F"]["ret"]["verdict"] == "used" and
          by["F"]["ret"]["tail"] == ["main:0x80010200"], by["F"]["ret"])
    check("RET-TAIL tail jump site", by["F2"]["ret"]["tail"] == ["main:0x80010400"] and
          by["F2"]["ret"]["verdict"] == "unknown:tail position unresolved", by["F2"]["ret"])

    # jalr site + indirect-call function (address formed by lui/addiu); address-taken function (data word)
    g = [E.lui(t9, F >> 16), E.addiu(t9, t9, F & 0xFFFF), E.jalr(t9), E.nop, E.addu(t0, V0, 0),
         E.jal(H), E.nop, E.addiu(V0, 0, 0)] + E.ret
    by, summ = one([(F, fret(1), "F"), (G, g, "G"), (H, fret(3), "H")], [(M + 0x1000, H)])
    check("jalr site counted", "sites jalr 1" in summ.splitlines(), summ)
    check("indirect call (lui/addiu formed, no direct site)", by["F"]["ret"]["verdict"] == "unknown:indirect call",
          by["F"]["ret"])
    check("address taken (data word, direct site dead)", by["H"]["ret"]["verdict"] == "unknown:address taken",
          by["H"]["ret"])

    # stack-argument read through a frame: entry $sp+20 = argument 5
    by, _ = one([(F, [E.addiu(SP, SP, -24), E.lw(t0, 44, SP), E.addu(V0, t0, A0), E.jr(RA),
                      E.addiu(SP, SP, 24)], "F")])
    a = by["F"]["args"]
    check("ARG-READ stack argument", [k for k, _ in a["read"]] == [0, 5] and a["arity_lb"] == 6, a)

    # varargs spill a1..a3 to entry $sp+4k
    by, _ = one([(F, [E.sw(a1, 4, SP), E.sw(6, 8, SP), E.sw(7, 12, SP), E.addiu(SP, SP, -8),
                      E.jr(RA), E.addiu(SP, SP, 8)], "F")])
    check("ARG-VARARGS spill from a1", by["F"]["varargs_spill"] == 1, by["F"]["varargs_spill"])

    # -O0 $fp frame: fp = sp - 16; lw 36($fp) = entry +20 = argument 5; frame kind fp
    by, _ = one([(F, [E.addiu(SP, SP, -16), E.sw(FP, 8, SP), E.move(FP, SP), E.sw(A0, 16, FP),
                      E.lw(V0, 36, FP), E.move(SP, FP), E.lw(FP, 8, SP), E.jr(RA), E.addiu(SP, SP, 16)], "F")])
    r = by["F"]
    check("frame -O0 $fp", r["frame"] == {"kind": "fp", "unresolved": []} and r["args"]["arity_lb"] == 6 and
          r["varargs_spill"] is None, (r["frame"], r["args"], r["varargs_spill"]))

    # 64-bit return read through $v1
    by, _ = one([(F, fret(1), "F"), (G, [E.jal(F), E.nop, E.addu(t0, V1, 0), E.addiu(V0, 0, 0)] + E.ret, "G")])
    check("RET-V1 64-bit read", by["F"]["ret"]["verdict"] == "used" and by["F"]["ret"]["ret64"], by["F"]["ret"])

    # tail recursion cycle F <-> G, entered by a dropping caller
    by, _ = one([(F, [E.jal(G), E.nop] + E.ret, "F"), (G, [E.jal(F), E.nop] + E.ret, "G"),
                 (H, [E.jal(F), E.nop, E.addiu(V0, 0, 0)] + E.ret, "H")])
    check("RET-FIX recursion cycle", by["F"]["ret"]["verdict"] == "unknown:recursion" and
          by["G"]["ret"]["verdict"] == "unknown:recursion", (by["F"]["ret"], by["G"]["ret"]))

    # cross-binary ambiguous target: main and resident images both hold 0x80011000; ov stacks both
    T = 0x80011000
    spec = {"main": (M, 0x2000, ["main"], [(T, fret(5), "Tm")], []),
            "resident": (M + 0x800, 0x2000, ["main", "resident"], [(T, [E.addiu(V0, 0, 2)] + E.ret, "Tr")], []),
            "ov": (0x80100000, 0x100, ["main", "resident", "ov"],
                   [(0x80100000, [E.jal(T), E.nop, E.addu(t0, V0, 0)] + E.ret, "O")], [])}
    by, summ = _rows(spec)
    check("cross-binary target unresolved", by["Tm"]["ret"]["verdict"] == "unknown:cross-binary target unresolved"
          and by["Tr"]["ret"]["verdict"] == "unknown:cross-binary target unresolved", (by["Tm"]["ret"], summ))

    # target outside every image of the caller's stack (a module calling the overlay beside it): resolved by
    # function start fleet-wide; one class -> credited, two classes at that start -> cross-binary for both
    O = 0x80100000
    md = ("md", (0x80200000, 0x100, ["main", "md"],
                 [(0x80200000, [E.jal(O), E.nop, E.addu(t0, V0, 0)] + E.ret, "D")], []))
    by, _ = _rows(dict([("main", (M, 0x100, ["main"], [], [])), md,
                        ("ov", (O, 0x100, ["main", "ov"], [(O, fret(7), "Ov")], []))]))
    check("outside stack, one class at the start: credited", by["Ov"]["ret"]["verdict"] == "used", by["Ov"]["ret"])
    by, _ = _rows(dict([("main", (M, 0x100, ["main"], [], [])), md,
                        ("ov", (O, 0x100, ["main", "ov"], [(O, fret(7), "Ov")], [])),
                        ("ov2", (O, 0x100, ["main", "ov2"], [(O, fret(8), "Ov2")], []))]))
    check("outside stack, two classes at the start: cross-binary",
          by["Ov"]["ret"]["verdict"] == "unknown:cross-binary target unresolved" and
          by["Ov2"]["ret"]["verdict"] == "unknown:cross-binary target unresolved", (by["Ov"]["ret"], by["Ov2"]["ret"]))

    # unresolved jump table with $v0 live; and a resolved one whose target reads $v0
    by, _ = one([(F, fret(1), "F"), (G, [E.jal(F), E.nop, E.jr(t0), E.nop], "G")])
    check("jump table with $v0 live", by["F"]["ret"]["verdict"] == "unknown:jump table with $v0 live",
          by["F"]["ret"])
    tbl = M + 0x1800
    g = [E.jal(F), E.nop, E.lui(at, (tbl + 0x8000) >> 16), E.addu(at, at, A0), E.lw(t1, tbl & 0xFFFF, at),
         E.jr(t1), E.nop, E.addu(t0, V0, 0)] + E.ret
    by, summ = one([(F, fret(1), "F"), (G, g, "G")], [(tbl, G + 28)])
    check("jump table resolved, target reads", by["F"]["ret"]["verdict"] == "used" and
          "jump tables resolved (classes) 1" in summ.splitlines(), (by["F"]["ret"], summ))

    print("selftest", "OK" if ok else "FAILED")
    return 0 if ok else 1


# ----------------------------------------------------------------------------------------------- main
def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("-j", type=int, default=1, help="worker processes")
    ap.add_argument("--only", help="comma-separated aliases to measure (their stacks are loaded too)")
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--show", metavar="BINARY:VADDR")
    a = ap.parse_args()
    if a.selftest:
        return selftest()
    if a.show:
        b, v = a.show.split(":")
        v = int(v, 16)
        p = OUT_DIR / "census.jsonl"
        for ln in p.open():
            r = json.loads(ln)
            if any(ib == b and int(iv, 16) == v for ib, iv, _ in r["instances"]):
                print(json.dumps(r, sort_keys=True, indent=1))
                return 0
        print(f"sig_evidence: no row holds {a.show}", file=sys.stderr)
        return 1
    fleet, measured = load_fleet(a.only.split(",") if a.only else None)
    rows, summ = census(fleet, measured, a.j)
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    with open(OUT_DIR / "census.jsonl", "w") as f:
        for r in rows:
            f.write(dump(r) + "\n")
    (OUT_DIR / "summary.txt").write_text(summ)
    print(summ, end="")
    return 0


if __name__ == "__main__":
    sys.exit(main())
