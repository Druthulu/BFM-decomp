#!/usr/bin/env python3
"""sig_evidence.py — the asm signature census (3.44 T3). Spec: docs/ops/sig-evidence.md.

Measures every function class's calling contract from the ORIGINAL bytes (never the C): return used / unused /
unknown with a closed reason list, argument reads and site setup, width evidence. Cites are
`<binary>:0x<vaddr> <insn>` at the instance's own vaddr.

  sig_evidence.py [-j N] [--only alias,...]    # census -> build/sig_evidence/{census.jsonl,summary.txt}
  sig_evidence.py --selftest                   # in-memory fixtures, one per rule
  sig_evidence.py --show <binary>:<vaddr>      # print the census row holding that instance
  sig_evidence.py --compare [-j N]             # C declarations/definitions vs the census -> build/sig_evidence/compare.*
  sig_evidence.py --check [-j N]               # --compare + config/lying_exceptions.tsv cites/coverage -> check.txt; rc 1 on any gap
"""
import argparse, array, bisect, collections, concurrent.futures, hashlib, json, os, pathlib, posixpath, re, struct, \
    subprocess, sys

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


def elf_path(a):
    return REPO / ("build/us/SLUS_007.26.elf" if a == "main" else f"build/{a}/{a}.elf")


def elf_syms(a):
    """[(vaddr, size|None, type, name)] — `mipsel-linux-gnu-nm -S --defined-only` of the alias's linked ELF (absolute included)."""
    p = elf_path(a)
    if not p.exists():
        raise SystemExit(f"sig_evidence: {p.relative_to(REPO)} missing; build the fleet first (ELF symbols fill sig gaps)")
    out = subprocess.run(["mipsel-linux-gnu-nm", "-S", "--defined-only", str(p)], capture_output=True, text=True,
                         check=True).stdout
    syms = []
    for ln in out.splitlines():
        f = ln.split()
        if len(f) == 4:
            syms.append((int(f[0], 16), int(f[1], 16), f[2], f[3]))
        elif len(f) == 3:
            syms.append((int(f[0], 16), None, f[1], f[2]))
    return syms


GAP_SKIP = (".L", "L8", "D_", "jtbl", "jr_")


def gap_rows(syms, have, base, data, own):
    """([(vaddr, nbytes, h, name)], skipped) — sized t/T function symbols inside the image with no nins>0 sig row at
    their vaddr (the filter of .run/3.44/t3/fleetgap.py:10-14); body = the original image slice [vaddr, vaddr+size),
    h = sha1(raw) as tools/sig_image.py:185, so equal bodies join existing classes. Unaligned or overrunning: skipped."""
    rows, seen, skipped = [], set(have), 0
    for va, size, t, name in sorted(syms, key=lambda s: (s[0], s[3])):
        if t not in ("T", "t") or not size or name.startswith(GAP_SKIP) or name.endswith(".NON_MATCHING"):
            continue
        if not base <= va < base + len(data) or va in seen:
            continue
        seen.add(va)
        if va % 4 or size % 4 or va + size > base + len(data):
            skipped += 1
            continue
        raw = data[va - base:va - base + size]
        rows.append((va, size, hashlib.sha1(raw).hexdigest(), own.get(va, name)))
    return rows, skipped


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
    with concurrent.futures.ThreadPoolExecutor(8) as ex:
        syms = dict(zip(keep, ex.map(elf_syms, keep)))
    gap = [0, 0]
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
        base, data = int(var[(a, "VRAM_BASE")], 16), (REPO / var[(a, "EXE")]).read_bytes()
        g, sk = gap_rows(syms[a], {r[0] for r in rows}, base, data, own)     # 3.44 T4: ELF functions with no sig row
        gap[0] += len(g)
        gap[1] += sk
        bins[a] = {"base": base, "data": data, "stack": st, "rows": rows + g}
    fleet = Fleet(bins)
    fleet.gap = tuple(gap)
    return fleet, (set(only) if only else set(keep))


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
    gap = getattr(fleet, "gap", (0, 0))
    summ += [f"instances from ELF symbols (no sig row) {gap[0]}", f"ELF symbols skipped (unaligned/overrun) {gap[1]}"]
    summ += [f"verdict {k} {V[k]}" for k in ("used", "unused", "unknown")]
    summ += [f"unknown verdict {k} {U[k]}" for k in REASONS[:8]]
    summ += [f"reason listed {k} {UA[k]}" for k in REASONS[:8]]
    summ += [f"{k} {X[k]}" for k in sorted(X)]
    summ += [f"{k} {S[k]}" for k in sorted(S)]
    return rows, "\n".join(summ) + "\n"


def dump(row):
    return json.dumps(row, sort_keys=True, separators=(",", ":"))


# ----------------------------------------------------------------------------------------------- compare (3.44 T4)
# Spec: docs/ops/sig-evidence.md "## Comparison (3.44 T4)". The C is read through argcheck's own patterns (DEF, KR_DEF +
# kr_params, SHARED_BIND, arity, norm_ret) on comment-masked text (lc.sc.mask_text, C0206); declarations through a
# balanced-paren `extern` parser (also the nested-paren and multi-line forms DECL misses, C0581).
RULES = ["RET-VOID-READ", "RET-NONE", "DECL-RET", "DECL-EMPTY", "ARG-OVER", "DECL-ARITY"]
SHAPES = ["(void)", "() unmarked", "() K&R-marked", "nested-paren", "multi-line", "other"]
KW = {"if", "for", "while", "switch", "return", "sizeof"}
DECL_HEAD = re.compile(r"\bextern\s+([A-Za-z_][\w \t\n*]*?)\b([A-Za-z_]\w*)\s*\(")
SEMI = re.compile(r"\s*;")
ALIAS_TAIL = re.compile(r'\)\s*__asm__\s*\(\s*"([^"\\]+)"\s*\)\s*;')     # `<ret> CNAME(...) __asm__("SYM");` (C0223)
IDENT_END = re.compile(r"([A-Za-z_]\w*)\s*$")
RET_CH = set("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_ \t\n*")
BRACE = re.compile(r"[{}]")
RET_AS_RX = re.compile(r"\b(RET_AS|KR_AS)\s*\(")                   # RET_AS(T, fn, params) (3.44 T5), KR_AS(T, fn) (T6) sites
RET_EXPR = re.compile(r"\breturn\b(?!\s*;)")
V0_EXIT = "$v0 at exit:"
_AC = None


def ac():
    global _AC
    if _AC is None:
        import argcheck                     # tools/ is sys.path[0]; imported only by --compare and its selftest
        _AC = argcheck
    return _AC


def nret(t):
    """argcheck.norm_ret; an empty spelling (storage class only, implicit int) is `int`."""
    return ac().norm_ret(t) or "int"


def split_top(p):
    out, d, cur = [], 0, ""
    for ch in p:
        d += (ch in "([") - (ch in ")]")
        if ch == "," and d == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    return out + [cur]


_AGG = None


def ret_words(ret):
    """1 when a definition returns a struct / union by value, else 0: gcc 2.x returns it in memory (pcc struct return,
    R3.44-001 calls.c:919-921) and the caller passes the return slot as a hidden pointer in $a0, ahead of the parameters.
    A canonical-header `typedef struct|union {...} Name;` without a tag counts (argcheck.typedefs keys tagged ones only)."""
    global _AGG
    if _AGG is None:
        _AGG = set()
        for h in ac().TYPEDEF_HEADERS:
            try:
                m = ac().lc.sc.mask_text((ac().REPO / h).read_text(errors="surrogateescape"))
            except OSError:
                continue
            for t in re.finditer(r"\btypedef\s+(?:struct|union)\s*\{", m):
                d, j = 0, t.end() - 1
                while j < len(m):
                    d += (m[j] == "{") - (m[j] == "}")
                    if d == 0:
                        break
                    j += 1
                k = m.find(";", j)
                if k > 0:
                    _AGG.update(p.strip() for p in m[j + 1:k].split(",") if re.fullmatch(r"\s*\w+\s*", p))
    n = nret(ret).split()
    if "*" in "".join(n):
        return 0
    return int("struct" in n or "union" in n or (len(n) == 1 and n[0] in _AGG))


def param_words(params, kr_types=None, hidden=0):
    """(words, varargs, struct_by_value) — the argument words a definition receives: 1 per parameter; double / long long
    (s64, u64) take 2 from an even register; a K&R float is promoted to double. `...` and by-value structs are flagged.
    `hidden` words come first (ret_words: a struct-return slot in $a0)."""
    if kr_types is None:
        p = " ".join(params.split())
        if p in ("", "void"):
            return hidden, False, False
        ps = split_top(p)
    else:
        ps = kr_types
    td = ac().typedefs()
    w, va, sv = hidden, False, False
    for x in ps:
        x = x.strip()
        if x == "...":
            va = True
            continue
        if "*" in x or "(" in x or "[" in x:
            w += 1
            continue
        toks = re.findall(r"\w+", x)
        if kr_types is None and len(toks) > 1 and toks[-1] not in td and toks[-1] not in (
                "int", "char", "short", "long", "unsigned", "signed", "float", "double", "void"):
            toks = toks[:-1]                                        # the parameter's name
        n = nret(" ".join(toks)).split()
        if "*" in n[-1]:
            w += 1
        elif "struct" in n or "union" in n:
            sv = True
            w += 1
        elif n == ["double"] or n.count("long") >= 2 or (kr_types is not None and n == ["float"]):
            w += (w & 1) + 2
        else:
            w += 1
    return w, va, sv


def parse_text(rel, raw):
    """One pass over one file: {defs, decls, binds, inner}. Lines are 1-based and match the raw file."""
    A = ac()
    masked = A.lc.sc.mask_text(raw)
    rl, ml = raw.split("\n"), masked.split("\n")
    nl = [m.start() for m in re.finditer("\n", masked)]
    opens = [m.start() for m in re.finditer(r"\{", masked)]
    closes = [m.start() for m in re.finditer(r"\}", masked)]

    def line(pos):
        return bisect.bisect_left(nl, pos) + 1

    def body_end(i):
        d = 0
        for m in BRACE.finditer(masked, i):
            d += 1 if m.group() == "{" else -1
            if d == 0:
                return m.start()
        return len(masked) - 1

    defs, seen, inner = [], set(), 0

    def add(m, kind, ret, params, arity, words, varargs, sv):
        nonlocal inner
        if m.group(1) in KW or m.start(1) in seen:
            return
        if bisect.bisect_left(opens, m.start()) - bisect.bisect_left(closes, m.start()) > 0:
            inner += 1                                              # a head inside a body is not a definition
            return
        seen.add(m.start(1))
        b0 = m.end() - 1
        b1 = body_end(b0)
        l0, l1, hl = line(b0), line(b1), line(m.start())
        v0 = any(V0_EXIT in rl[k] for k in range(l0 - 1, min(l1, len(rl))))
        k = hl - 2
        while not v0 and k >= 0 and rl[k].strip() and not ml[k].strip():   # comment lines directly above the head
            v0 = V0_EXIT in rl[k]
            k -= 1
        defs.append({"line": line(m.start(1)), "name": m.group(1), "kind": kind, "ret": ret, "params": params,
                     "arity": arity, "words": words, "varargs": varargs, "sv": sv,
                     "has_ret": bool(RET_EXPR.search(masked, b0, b1 + 1)), "v0": v0})

    for m in A.DEF.finditer(masked):
        params = " ".join(m.group(2).split())
        ret = masked[m.start():m.start(1)].strip()
        w, va, sv = param_words(params, hidden=ret_words(ret))
        add(m, "DEF", nret(ret), params, A.arity(params), w, va, sv)
    for m in A.KR_DEF.finditer(masked):
        names = [n.strip() for n in m.group(2).split(",")]
        types = A.kr_params(names, m.group(3))
        ret = masked[m.start():m.start(1)].strip()
        w, va, sv = param_words(None, types, hidden=ret_words(ret))
        add(m, "KR", nret(ret), ", ".join(types), len(names), w, va, sv)
    defs.sort(key=lambda d: d["line"])

    decls, aliases, objlabels = [], {}, 0

    def decl(p0, p1, name, ret, params):
        params = " ".join(params.split())
        l0, l1 = line(p0), line(p1)
        kr = any("// K&R:" in rl[k] for k in range(l0 - 1, min(l1, len(rl))))
        shape = ("multi-line" if l1 > l0 else "nested-paren" if "(" in params else "(void)" if params == "void"
                 else ("() K&R-marked" if kr else "() unmarked") if params == "" else "other")
        decls.append({"line": l0, "name": name, "ret": nret(ret), "params": params,
                      "arity": A.arity(params), "shape": shape, "kr": kr,
                      "text": " ".join(" ".join(rl[l0 - 1:l1]).split())[:200]})

    for m in DECL_HEAD.finditer(masked):
        if m.group(2) in KW:
            continue
        if m.group(2) == "__asm__":                                 # `extern T obj __asm__("S");`: an object, not a function
            objlabels += 1
            continue
        j, d = m.end(), 1
        while j < len(masked) and d:
            c = masked[j]
            d += (c == "(") - (c == ")")
            j += 1
        if d or not SEMI.match(masked, j):
            continue                                                # an asm-label tail is taken below
        decl(m.start(), j - 1, m.group(2), m.group(1), masked[m.end():j - 1])
    # asm-label prototypes, `extern` or not: a declaration of SYM (the jal target), and CNAME's definition is SYM (C0223)
    for m in ALIAS_TAIL.finditer(masked):
        po, d = m.start(), 0
        while po >= 0:
            d += (masked[po] == ")") - (masked[po] == "(")
            if d == 0:
                break
            po -= 1
        n = IDENT_END.search(masked, max(0, po - 200), po) if po > 0 else None
        if n is None or n.group(1) in KW or n.group(1).startswith("__"):
            continue                                                # `(*fp)(...)`, `__attribute__((...))`: not a prototype
        r = n.start(1) - 1
        while r >= 0 and masked[r] in RET_CH:
            r -= 1
        if r >= 0 and masked[r] == "#":                             # a directive line above the head is not the return type
            r = masked.find("\n", r)
        ret = masked[r + 1:n.start(1)]
        p0 = r + 1 + len(ret) - len(ret.lstrip())
        decl(p0, m.start(), m.group(1), re.sub(r"\bextern\b", " ", ret), masked[po + 1:m.start()])
        aliases[n.group(1)] = m.group(1)
    decls.sort(key=lambda dc: dc["line"])
    binds = [(m.group(1), m.group(2)) for m in A.SHARED_BIND.finditer(raw)]
    ret_as, kr_as = [], []                                          # 3.44 T5/T6: [(line, fn, T)]; a `#define` line is no site
    for m in RET_AS_RX.finditer(masked):
        if ml[line(m.start()) - 1].lstrip().startswith("#"):
            continue
        j, d, args, a0 = m.end(), 1, [], m.end()
        while j < len(masked) and d:
            c = masked[j]
            d += (c == "(") - (c == ")")
            if (c == "," and d == 1) or d == 0:
                args.append(" ".join(masked[a0:j].split()))
                a0 = j + 1
            j += 1
        want, out = (3, ret_as) if m.group(1) == "RET_AS" else (2, kr_as)
        out.append((line(m.start()), args[1] if len(args) == want else "?", args[0] if args else "?"))   # malformed: no row backs it
    return {"defs": defs, "decls": decls, "binds": binds, "inner": inner, "aliases": aliases, "objlabels": objlabels,
            "ret_as": ret_as, "kr_as": kr_as}


def _parse_file(rel):
    try:
        raw = (REPO / rel).read_text(errors="surrogateescape")
    except OSError:
        return rel, None
    return rel, parse_text(rel, raw)


def load_tus(aliases):
    """{alias: [(object, c_file, [src/ and include/ deps])]} from build/src/*.d (main) and build/src/<alias>/*.d."""
    tus = {}
    for a in aliases:
        d = REPO / "build" / "src" / ("" if a == "main" else a)
        lst = []
        for p in sorted(d.glob("*.d")):
            head = []
            for ln in p.read_text().splitlines():
                head.append(ln.rstrip().rstrip("\\"))
                if not ln.rstrip().endswith("\\"):
                    break
            toks = " ".join(head).split()
            deps = list(dict.fromkeys(n for n in (posixpath.normpath(t) for t in toks[1:])   # .d spells src/<b>/../shared/
                                      if n.startswith(("src/", "include/"))))
            if deps:
                lst.append((toks[0].rstrip(":"), deps[0], deps))
        tus[a] = lst
    return tus


def join_fns(parsed, tus, symtab, images, stacks, cls_of):
    """The placement join of compare_core (3.45 T2: shared with struct_twins.py --links). dict(U, US, cov, resolve, place, dinst,
    cinst, defrec, def_at, defs [(b, va, h, f, ln, name, d, I)], decls [(b, f, ln, dc, objs, va, h, owners, dd)]); defs in sorted
    dinst order, decls in sorted cinst order; dd = the callee's placed definition (def_at entry) or None."""
    U = collections.Counter()                                   # unplaced, by (what, reason)
    US = collections.defaultdict(set)                           # 3.45 T2.c2: the same, as unique sites (file, line)
    cov = collections.Counter()
    at_va = collections.defaultdict(set)
    at_own = collections.defaultdict(list)
    for (b, va), h in cls_of.items():
        at_va[va].add(h)
        at_own[va].append(b)

    def resolve(b, name):
        ads = symtab.get(b, {}).get(name)
        if not ads:
            return None, "name not in the symtab"
        if len(ads) > 1:
            return None, "name has several addresses"
        return next(iter(ads)), None

    def place(b, va):
        """(h, owners) or (None, reason): own image, then the splat stack order, then fleet-wide (OUTSIDE-STACK)."""
        for x in [b] + [s for s in stacks.get(b, []) if s != b]:
            lo, hi = images[x]
            if lo <= va < hi:
                h = cls_of.get((x, va))
                return (h, [x]) if h else (None, "address in no class")
        hs = at_va.get(va)
        if not hs:
            return None, "address in no class"
        if len(hs) > 1:
            return None, ">1 class (OUTSIDE-STACK)"
        h = next(iter(hs))
        return h, sorted(x for x in at_own[va] if cls_of[(x, va)] == h)

    # definition and declaration instances, per binary
    dinst, cinst = {}, {}                                       # key -> {"objs": set, "bind": c_file|None}
    for b in sorted(tus):
        for obj, cfile, deps in tus[b]:
            dep = set(deps)
            amap = {}                                           # CNAME -> SYM from the TU's asm-label prototypes (C0223)
            for f in deps:
                if parsed.get(f):
                    amap.update(parsed[f]["aliases"])
            for f in deps:
                P = parsed.get(f)
                if P is None:
                    U[("file", "file missing")] += 1
                    US[("file", "file missing")].add((f, 0))
                    continue
                for d in P["defs"]:
                    if d["name"] != "SHARED_FN":
                        dinst.setdefault((b, f, d["line"], amap.get(d["name"], d["name"])),
                                         {"objs": set(), "bind": None})["objs"].add(obj)
                for dc in P["decls"]:
                    cinst.setdefault((b, f, dc["line"]), set()).add(obj)
                for own, inc in P["binds"]:
                    hdr = posixpath.normpath(posixpath.join(posixpath.dirname(f), inc))
                    if hdr not in dep:
                        hdr = next((x for x in deps if x.endswith("/" + inc.lstrip("./"))), None)
                    if hdr is None or parsed.get(hdr) is None:
                        U[("definition", "SHARED_FN header not in the TU")] += 1
                        US[("definition", "SHARED_FN header not in the TU")].add((f, inc))
                        continue
                    for d in parsed[hdr]["defs"]:
                        if d["name"] == "SHARED_FN":
                            dinst.setdefault((b, hdr, d["line"], amap.get(own, own)),
                                             {"objs": set(), "bind": f})["objs"].add(obj)
    defrec = {}
    for f, P in parsed.items():
        if P:
            for d in P["defs"]:
                defrec[(f, d["line"])] = d
    defs, def_at = [], collections.defaultdict(list)
    for (b, f, ln, name), I in sorted(dinst.items()):
        d = defrec[(f, ln)]
        va, why = resolve(b, name)
        if why is None and not images[b][0] <= va < images[b][1]:
            why = "definition address outside own image"
        if why is None and (b, va) not in cls_of:
            why = "address in no class"
        if why:
            U[("definition", why)] += 1
            US[("definition", why)].add((f, ln))
            continue
        cov["definitions placed"] += 1
        h = cls_of[(b, va)]
        def_at[(b, va)].append((b, f, ln, name, d, I))
        defs.append((b, va, h, f, ln, name, d, I))

    declrec = {}
    for f, P in parsed.items():
        if P:
            for dc in P["decls"]:
                declrec[(f, dc["line"])] = dc
    decls = []
    for (b, f, ln), objs in sorted(cinst.items()):
        dc = declrec[(f, ln)]
        va, why = resolve(b, dc["name"])
        h = owners = None
        if why is None:
            h, owners = place(b, va)
            if h is None:
                why = owners
        if why:
            U[("declaration", why)] += 1
            US[("declaration", why)].add((f, ln))
            continue
        cov["declarations placed"] += 1
        ds = [x for o in owners for x in def_at.get((o, va), [])]
        dd = None
        if not ds:
            cov["declarations placed, callee has no placed C definition"] += 1
        elif len({(x[4]["ret"], x[4]["arity"], x[4]["varargs"]) for x in ds}) > 1:
            cov["declarations placed, the callee's definitions disagree"] += 1
        else:
            dd = min(ds, key=lambda x: x[:4])
        decls.append((b, f, ln, dc, objs, va, h, owners, dd))
    return dict(U=U, US=US, cov=cov, resolve=resolve, place=place, dinst=dinst, cinst=cinst, defrec=defrec, def_at=def_at, defs=defs, decls=decls)


def compare_core(parsed, tus, symtab, images, stacks, cls_of, info, return_lie, orphans):
    """(rows, cov). parsed {file: parse_text|None}; tus load_tus; symtab {alias: {name: {vaddr}}}; images {alias: (lo, hi)};
    stacks {alias: [alias]}; cls_of {(alias, vaddr): h}; info {h: (verdict, cite, arity_lb, highest args.read entry, ret.tail,
    produces: an exit writer other than `entry`, or no `jr $ra` exit (tail / leave only: not provably empty))}; return_lie {h}; orphans [src files in no .d]."""
    J = join_fns(parsed, tus, symtab, images, stacks, cls_of)
    U, cov, dinst, cinst, defrec = J["U"], J["cov"], J["dinst"], J["cinst"], J["defrec"]
    novalue = set()                                             # RET-VOID-READ classes skipped: no value produced

    def void_read(base, cite, tail, produces):
        if produces:
            rows.append(dict(base, rule="RET-VOID-READ", cite=cite, tail=None if cite else tail))   # used by RET-FIX only
        else:                                                   # every exit writer is `entry` (C0587)
            cov["RET-VOID-READ skipped: no value produced (rows)"] += 1
            novalue.add(base["h"])
    seen_files = {f for b in tus for _, _, deps in tus[b] for f in deps}

    rows = []
    for b, va, h, f, ln, name, d, I in J["defs"]:
        verdict, cite, alb, hi_read, tail, produces = info[h]
        base = {"binary": b, "owner": b, "vaddr": hx(va), "h": h, "name": name, "def_file": f"{f}:{ln}", "bind_tu": I["bind"],
                "def_ret": d["ret"], "kr_marked": False, "objs": sorted(I["objs"])}
        if verdict == "used" and d["ret"] == "void":
            void_read(base, cite, tail, produces)
        if d["ret"] != "void" and not d["has_ret"] and not d["v0"]:
            rows.append(dict(base, rule="RET-NONE", cite=None))
        if not d["varargs"]:
            if d["sv"]:
                cov["ARG-OVER skipped: struct by value"] += 1
            elif alb > d["words"]:
                rows.append(dict(base, rule="ARG-OVER", cite=hi_read[1] if hi_read else None, arity_lb=alb,
                                 def_words=d["words"], def_params=d["params"]))

    for b, f, ln, dc, objs, va, h, owners, dd in J["decls"]:
        verdict, cite, alb, hi_read, tail, produces = info[h]
        base ={"binary": b, "owner": ",".join(owners), "vaddr": hx(va), "h": h, "name": dc["name"], "decl_file": f"{f}:{ln}",
                "decl_text": dc["text"], "decl_ret": dc["ret"], "kr_marked": dc["kr"], "objs": sorted(objs),
                "def_file": f"{dd[1]}:{dd[2]}" if dd else None, "bind_tu": dd[5]["bind"] if dd else None,
                "def_ret": dd[4]["ret"] if dd else None}
        if dc["ret"] == "void" and verdict == "used":
            void_read(base, cite, tail, produces)
        if dc["params"] == "":
            rows.append(dict(base, rule="DECL-EMPTY", cite=None))
        if dd is None:
            continue
        d = dd[4]
        if dc["ret"] != d["ret"]:
            rows.append(dict(base, rule="DECL-RET", cite=None))
        if dc["params"] != "":
            bad = dc["arity"] < d["arity"] - 1 if d["varargs"] else dc["arity"] != d["arity"]
            if bad:
                rows.append(dict(base, rule="DECL-ARITY", cite=None, decl_args=dc["arity"],
                                 def_args=d["arity"] - d["varargs"], def_params=d["params"]))

    # files in no TU: their definitions and declarations are unplaced, never guessed
    for f in orphans:
        P = parsed.get(f)
        if P:
            U[("definition", "file in no TU")] += len(P["defs"])
            U[("declaration", "file in no TU")] += len(P["decls"])

    if novalue:
        cov["RET-VOID-READ skipped: no value produced (functions)"] = len(novalue)
    # coverage
    L = ["coverage"]
    L.append(f"  files seen (in a .d) {len(seen_files)}; parsed {sum(1 for f in seen_files if parsed.get(f))}; "
             f"TUs {sum(len(v) for v in tus.values())}; binaries {len(tus)}")
    ds_ = [(f, d) for f in sorted(seen_files) if parsed.get(f) for d in parsed[f]["defs"]]
    L.append(f"  definitions: sites {len(ds_)}, names {len({d['name'] for _, d in ds_})}, "
             f"K&R heads {sum(d['kind'] == 'KR' for _, d in ds_)} (names {len({d['name'] for _, d in ds_ if d['kind'] == 'KR'})}), "
             f"SHARED_FN bodies {sum(d['name'] == 'SHARED_FN' for _, d in ds_)}, "
             f"heads inside a body skipped {sum(parsed[f]['inner'] for f in seen_files if parsed.get(f))}")
    L.append(f"  definition instances (binary, site): {len(dinst)}, placed {cov['definitions placed']}, "
             f"bound by SHARED_FN {sum(1 for I in dinst.values() if I['bind'])}, "
             f"joined by asm label {sum(1 for (_, f, ln, n) in dinst if defrec[(f, ln)]['name'] not in (n, 'SHARED_FN'))}")
    L.append(f"  asm-label C names (per file): function prototypes {sum(len(parsed[f]['aliases']) for f in seen_files if parsed.get(f))} "
             f"(declarations of the label), object declarations skipped "
             f"{sum(parsed[f]['objlabels'] for f in seen_files if parsed.get(f))}")
    L.append("  declaration lines by shape (lines / callees / files):")
    for s in SHAPES:
        xs = [(f, dc) for f in sorted(seen_files) if parsed.get(f) for dc in parsed[f]["decls"] if dc["shape"] == s]
        L.append(f"    {s}: {len(xs)} / {len({dc['name'] for _, dc in xs})} / {len({f for f, _ in xs})}")
    L.append(f"  declaration instances (binary, line): {len(cinst)}, placed {cov['declarations placed']}")
    for k in sorted(cov):
        if k not in ("definitions placed", "declarations placed"):
            L.append(f"  {k}: {cov[k]}")
    L.append("  unplaced (instances, by reason):")
    for (w, r), n in sorted(U.items()):
        L.append(f"    {w}: {r}: {n}")
    L.append(f"  src files in no .d: {len(orphans)}")
    for f in orphans:
        L.append(f"    {f}")
    rows.sort(key=lambda r: (RULES.index(r["rule"]), r["binary"], r["vaddr"], r.get("def_file") or "",
                             r.get("decl_file") or "", r["name"]))
    # per rule
    T = ["rule            rows  functions  names  def_sites  decl_lines  files  objects  return_lie"]
    for ru in RULES:
        rs = [r for r in rows if r["rule"] == ru]
        files = {(r.get("decl_file") or r["def_file"]).rsplit(":", 1)[0] for r in rs}
        T.append(f"{ru:<14} {len(rs):>6} {len({r['h'] for r in rs}):>10} {len({r['name'] for r in rs}):>6} "
                 f"{len({r['def_file'] for r in rs if 'decl_file' not in r}):>10} "
                 f"{len({r['decl_file'] for r in rs if 'decl_file' in r}):>11} {len(files):>6} "
                 f"{len({o for r in rs for o in r['objs']}):>8} {len({r['h'] for r in rs} & return_lie):>11}")
    for r in rows:
        r["objects"] = len(r.pop("objs"))
    return rows, "\n".join(T + L) + "\n"


def compare_inputs(jobs):
    """compare_core's inputs (3.45 T2: shared with struct_twins.py --links): (parsed, tus, symtab, images, stacks, cls_of,
    info, return_lie, orphans), as compare_core's signature."""
    aliases, var = mk_vars()
    aset = set(aliases)
    stacks = {a: yaml_stack(var[(a, "SPLAT_YAML")], aset) for a in aliases}
    images = {}
    for a in aliases:
        lo = int(var[(a, "VRAM_BASE")], 16)
        images[a] = (lo, lo + (REPO / var[(a, "EXE")]).stat().st_size)
    with concurrent.futures.ThreadPoolExecutor(8) as ex:
        syms = dict(zip(aliases, ex.map(elf_syms, aliases)))
    symtab = {}
    for a in aliases:
        t = collections.defaultdict(set)
        for va, size, typ, name in syms[a]:
            t[name].add(va)
        symtab[a] = t
    p = OUT_DIR / "census.jsonl"
    if not p.exists():
        raise SystemExit("sig_evidence: build/sig_evidence/census.jsonl missing; run the census first")
    cls_of, info = {}, {}
    with p.open() as fh:
        for ln in fh:
            r = json.loads(ln)
            a = r["args"]
            info[r["h"]] = (r["ret"]["verdict"], r["ret"]["cite"], a["arity_lb"], max(a["read"], default=None),
                            r["ret"]["tail"], not r["exit"] or any(w != "entry" for _, ws in r["exit"] for w in ws))
            for b, va, _ in r["instances"]:
                cls_of[(b, int(va, 16))] = r["h"]
    rl = set()
    for ln in (REPO / "config" / "dedup_exceptions.tsv").read_text().splitlines():
        c = ln.split("\t")
        if len(c) > 1 and c[1] == "RETURN-LIE":
            rl.add(c[0])
    tus = load_tus(aliases)
    seen = {f for a in tus for _, _, deps in tus[a] for f in deps}
    srcs = subprocess.run(["git", "ls-files", "src"], cwd=REPO, capture_output=True, text=True,
                          check=True).stdout.split()
    orphans = sorted(f for f in srcs if f.endswith((".c", ".h")) and f not in seen)
    files = sorted(seen | set(orphans))
    ac().typedefs()
    if jobs > 1:
        import multiprocessing as mp
        with mp.get_context("fork").Pool(jobs) as pool:
            parsed = dict(pool.imap(_parse_file, files, chunksize=8))
    else:
        parsed = dict(map(_parse_file, files))
    return parsed, tus, symtab, images, stacks, cls_of, info, rl, orphans


def compare(jobs):
    parsed, tus, symtab, images, stacks, cls_of, info, rl, orphans = compare_inputs(jobs)
    rows, txt = compare_core(parsed, tus, symtab, images, stacks, cls_of, info, rl, orphans)
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    with open(OUT_DIR / "compare.jsonl", "w") as f:
        for r in rows:
            f.write(dump(r) + "\n")
    (OUT_DIR / "compare.txt").write_text(txt)
    return rows, txt, parsed


# ----------------------------------------------------------------------------------------------- check (3.44 T4)
# Spec: docs/ops/sig-evidence.md "## Ledger (3.44 T4)". config/lying_exceptions.tsv: callee def_file kind cause task cites.
LEDGER = "config/lying_exceptions.tsv"
RV_LEDGER = "config/ret_view_casts.tsv"          # 3.44 T5: callee def_file view cause task cites; one row per RET_AS callee
KV_LEDGER = "config/kr_view_casts.tsv"           # 3.44 T6: callee def_file cause task cites; one row per KR_AS callee
CITE_RE = re.compile(r"^(\S+):0x([0-9A-Fa-f]{8}) (.+)$")
KIND_RULE = {"return": "DECL-RET"}


def load_ledger(text):
    """[{callee, def_file, kind, cause, task, cites [str]}] from the ledger's text; `#` lines and the header skipped."""
    out = []
    for ln in text.splitlines():
        if not ln.strip() or ln.startswith("#") or ln.startswith("callee\t"):
            continue
        f = ln.split("\t") + [""] * 6
        out.append({"callee": f[0], "def_file": f[1], "kind": f[2], "cause": f[3], "task": f[4],
                    "cites": [c for c in f[5].split("; ") if c.strip()]})
    return out


def verify_cites(ledger, decode):
    """[(callee, cite, decoded)] for each ledger cite that does not decode to itself (or a row with no cites)."""
    norm = lambda t: " ".join(t.split())
    failed = []
    for L in ledger:
        if not L["cites"]:
            failed.append((L["callee"], "", "no cites"))
        for c in L["cites"]:
            m = CITE_RE.match(c.strip())
            got = decode(m.group(1), int(m.group(2), 16)) if m else None
            if got is None or norm(got) != norm(c):
                failed.append((L["callee"], c, got or ("unparsable" if not m else "outside every image")))
    return failed


def check_core(ledger, rows, decode):
    """(failed, unused, unledgered, txt). decode(binary, vaddr) -> the census cite text, or None (no such image/address).
    A row with def_file `-` (3.44 T6) matches a disagreement of its callee+kind whose def_file is None (no C definition)."""
    failed = verify_cites(ledger, decode)
    by_name = collections.defaultdict(list)
    for i, L in enumerate(ledger):
        by_name[L["callee"]].append(i)
    used, unl = set(), []
    for r in rows:
        paths = {x for x in ((r.get("def_file") or "").rsplit(":", 1)[0], r.get("bind_tu")) if x}
        if not r.get("def_file"):
            paths.add("-")                                       # 3.44 T6: def_file `-` = no C definition (asm-only callee)
        hit = [i for i in by_name.get(r["name"], ())
               if ledger[i]["def_file"] in paths and KIND_RULE.get(ledger[i]["kind"], ledger[i]["kind"]) == r["rule"]]
        used.update(hit)
        if not hit:
            unl.append(r)
    unused = [L for i, L in enumerate(ledger) if i not in used]
    T = [f"ledger rows {len(ledger)}, cites {sum(len(L['cites']) for L in ledger)}",
         f"failed cites {len(failed)}", f"unused rows {len(unused)}", f"unledgered disagreements {len(unl)}"]
    per = collections.Counter(r["rule"] for r in unl)
    T += [f"  {ru} {per[ru]}" for ru in RULES if per[ru]]
    T.append("unledgered by rule: " + " ".join(f"{ru} {per[ru]}" for ru in RULES))   # 3.44 T14: every rule, fixed order (readability_progress)
    T.append("failed cites (first 20): callee | cite | decoded")
    T += [f"  {a} | {b} | {c}" for a, b, c in failed[:20]]
    T.append("unused rows (first 20): callee def_file kind")
    T += [f"  {L['callee']} {L['def_file']} {L['kind']}" for L in unused[:20]]
    T.append("unledgered (first 20): rule binary vaddr name def_file|decl_file")
    T += [f"  {r['rule']} {r['binary']} {r['vaddr']} {r['name']} {r.get('decl_file') or r.get('def_file')}"
          for r in unl[:20]]
    return failed, unused, unl, "\n".join(T) + "\n"


def load_kr_ledger(text):
    """3.44 T6: config/kr_view_casts.tsv (callee def_file cause task cites) as load_ledger rows with kind ""."""
    return [dict(L, kind="", cause=L["kind"], task=L["cause"], cites=[c for c in L["task"].split("; ") if c.strip()])
            for L in load_ledger(text)]


def check_ret_views(ledger, parsed, decode, kr=False):
    """3.44 T5: (failed, unbacked, unused, wrong_def, txt) for config/ret_view_casts.tsv (load_ledger; field 2 = the view T).
    parsed {file: parse_text|None}. A RET_AS site needs a row (fn, T); a row needs a site; def_file must define fn.
    A site's fn that is an asm-label alias in its file names the label (C0223); a `#define SHARED_FN own` + `#include`
    bind defines own in the binding file (T5.c5).
    3.44 T6 kr=True: config/kr_view_casts.tsv (load_kr_ledger) against the KR_AS sites, keyed on fn alone (T is the
    definition's return; the def_file test pins the row to the definition). def_file `-`: right iff no parsed file defines fn."""
    failed = verify_cites(ledger, decode)
    norm = (lambda t: "") if kr else (lambda t: " ".join(t.split()))
    tag, mac = ("kr-view", "KR_AS") if kr else ("ret-view", "RET_AS")
    sites = [(f, ln, p.get("aliases", {}).get(fn, fn), T) for f, p in sorted(parsed.items()) if p
             for ln, fn, T in p.get("kr_as" if kr else "ret_as", ())]
    defs = collections.defaultdict(set)
    for f, p in parsed.items():
        for d in (p or {}).get("defs", ()):
            defs[d["name"]].add(f)
            defs[p["aliases"].get(d["name"], d["name"])].add(f)    # `T cname(...) __asm__("label");` + cname's body defines label
        for own, inc in (p or {}).get("binds", ()):
            hdr = parsed.get(posixpath.normpath(posixpath.join(posixpath.dirname(f), inc)))
            if hdr and any(d["name"] == "SHARED_FN" for d in hdr["defs"]):
                defs[own].add(f)
                defs[p["aliases"].get(own, own)].add(f)              # 3.44 T8: `#define SHARED_FN aF…` + its asm label
    keys = {(L["callee"], norm(L["kind"])) for L in ledger}
    unbacked = [x for x in sites if (x[2], norm(x[3])) not in keys]
    used = {(x[2], norm(x[3])) for x in sites}
    unused = [L for L in ledger if (L["callee"], norm(L["kind"])) not in used]
    wrong = [L for L in ledger if (bool(defs.get(L["callee"])) if L["def_file"] == "-"     # 3.44 T6: `-` = no C definition
                                   else L["def_file"] not in defs.get(L["callee"], ()))]
    T = [f"{tag} rows {len(ledger)}, cites {sum(len(L['cites']) for L in ledger)}, {mac} sites {len(sites)}",
         f"{tag} failed cites {len(failed)}", f"{tag} unused rows {len(unused)}",
         f"{tag} unbacked sites {len(unbacked)}", f"{tag} wrong def_file {len(wrong)}"]
    T += [f"  failed: {a} | {b} | {c}" for a, b, c in failed[:20]]
    T += [f"  unused: {L['callee']} {L['def_file']} {L['kind']}" for L in unused[:20]]
    T += [f"  unbacked: {f}:{ln} {mac}({t}, {fn}{'' if kr else ', …'})" for f, ln, fn, t in unbacked[:20]]
    T += [f"  wrong def_file: {L['callee']} {L['def_file']} (defined in {', '.join(sorted(defs.get(L['callee'], ()))) or 'none'})"
          for L in wrong[:20]]
    return failed, unbacked, unused, wrong, "\n".join(T) + "\n"


def check(jobs):
    rows, _, parsed = compare(jobs)
    aliases, var = mk_vars()
    bins = {}

    def decode(b, va):
        if b not in bins:
            if b not in aliases or (b, "EXE") not in var:
                return None
            bins[b] = {"base": int(var[(b, "VRAM_BASE")], 16), "data": (REPO / var[(b, "EXE")]).read_bytes()}
        B = bins[b]
        if va % 4 or not 0 <= va - B["base"] <= len(B["data"]) - 4:
            return None
        return cite(Fleet(bins), b, va)
    failed, unused, unl, txt = check_core(load_ledger((REPO / LEDGER).read_text()), rows, decode)
    rv = check_ret_views(load_ledger((REPO / RV_LEDGER).read_text()), parsed, decode)
    kv = check_ret_views(load_kr_ledger((REPO / KV_LEDGER).read_text()), parsed, decode, kr=True)
    txt += rv[4] + kv[4]
    (OUT_DIR / "check.txt").write_text(txt)
    print(txt, end="")
    return 1 if failed or unused or unl or any(rv[:4]) or any(kv[:4]) else 0


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

    # 3.44 T4 gap: sized t/T ELF symbols inside the image with no sig row become instances, h = sha1 of the slice
    data = bytes(range(64))
    syms = [(M, 8, "T", "has_row"), (M + 8, 8, "t", "gap_f"), (M + 16, 8, "T", "D_80010010"), (M + 24, 6, "T", "odd"),
            (M + 32, 8, "A", "abs"), (M + 0x1000, 8, "T", "outside"), (M + 40, None, "T", "nosize")]
    g, sk = gap_rows(syms, {M}, M, data, {M + 8: "own_name"})
    check("GAP ELF function with no sig row -> instance (sha1 of the image slice)",
          g == [(M + 8, 8, hashlib.sha1(data[8:16]).hexdigest(), "own_name")] and sk == 1, (g, sk))

    # 3.44 T4 compare: one in-memory world (ov over main), one check per rule
    O = 0x80100000
    a_c = "\n".join([
        '#define SHARED_FN f_ret', '#include "../shared/cls_1.h"',
        'extern void f_used(void);', 'extern s32 f_none();', 'extern s32 f_kr(); // K&R: unspecified',
        'extern s32 f_ret(void);', 'extern s32 f_ar(s32 a,', '    s32 b);', 'extern s32 f_va(s32 a);',
        'extern void m_used(void);', 'extern void f_empty(void);',
        'void f_used(void) { m_used(); }',
        's32 f_none(a)', 's32 a;', '{', '    return;', '}',
        '/* $v0 at exit: 1 (li v0,1) */', 's32 f_kr(a)', 's32 a;', '{', '    m_used();', '}',
        's32 f_ar(s32 a) { return a; }', 's32 f_va(s32 a, ...) { return a; }',
        'void f_dbl(s32 a, double d) { }', 'void f_sv(struct Foo v) { }', 'void f_empty(void) { }', ''])
    parsed = {"src/ov/a.c": parse_text("src/ov/a.c", a_c),
              "src/shared/cls_1.h": parse_text("src/shared/cls_1.h", "void SHARED_FN(void) {\n}\n"),
              "src/ov/orphan.c": parse_text("src/ov/orphan.c", "extern void q(void);\nvoid q(void) { }\n")}
    names = ["f_used", "f_none", "f_kr", "f_ret", "f_ar", "f_va", "f_dbl", "f_sv", "f_empty"]
    symtab = {"ov": {n: {O + 16 * i} for i, n in enumerate(names)}, "main": {}}
    symtab["ov"]["m_used"] = {M}
    cls_of = {("ov", O + 16 * i): "h_" + n for i, n in enumerate(names)}
    cls_of[("main", M)] = "h_m"
    info = {h: ("unused", None, 0, None, [], True) for h in cls_of.values()}
    info["h_f_used"] = info["h_m"] = ("used", "ov:0x80100004 addu", 0, None, [], True)
    info["h_f_empty"] = ("used", "ov:0x80100004 addu", 0, None, [], False)      # every exit writer `entry` (C0587)
    info["h_f_dbl"] = ("unused", None, 5, [4, "ov:0x80100064 lw"], [], True)
    info["h_f_sv"] = ("unused", None, 9, [8, "ov:0x80100074 lw"], [], True)
    rows, txt = compare_core(parsed, {"main": [], "ov": [("build/src/ov/a.o", "src/ov/a.c",
                                                          ["src/ov/a.c", "src/shared/cls_1.h"])]},
                             symtab, {"main": (M, M + 0x100), "ov": (O, O + 0x100)},
                             {"main": ["main"], "ov": ["main", "ov"]}, cls_of, info, {"h_f_ret"}, ["src/ov/orphan.c"])
    R = collections.defaultdict(list)
    for r in rows:
        R[r["rule"]].append(r)
    x = R["RET-VOID-READ"]
    check("RET-VOID-READ void def + void decls of a used class, cite ret.cite",
          sorted((r["name"], r.get("decl_file") or "") for r in x) ==
          [("f_used", ""), ("f_used", "src/ov/a.c:3"), ("m_used", "src/ov/a.c:10")]
          and all(r["cite"] == "ov:0x80100004 addu" for r in x), x)
    check("RET-VOID-READ skipped when every exit writer is `entry` (def + decl counted apart)",
          "RET-VOID-READ skipped: no value produced (rows): 2" in txt and
          "RET-VOID-READ skipped: no value produced (functions): 1" in txt, txt)
    x = R["RET-NONE"]
    check("RET-NONE bare return / no return, `$v0 at exit:` above a K&R head exempts",
          [r["name"] for r in x] == ["f_none"], x)
    x = R["DECL-RET"]
    check("DECL-RET against a SHARED_FN definition (def_file = header, bind_tu = TU)",
          [(r["name"], r["decl_ret"], r["def_ret"], r["def_file"], r["bind_tu"]) for r in x] ==
          [("f_ret", "int", "void", "src/shared/cls_1.h:1", "src/ov/a.c")] and
          re.search(r"^DECL-RET\s+1\s.*\s1$", txt, re.M), (x, txt))
    x = R["DECL-EMPTY"]
    check("DECL-EMPTY () rows, K&R-marked flagged", sorted((r["name"], r["kr_marked"]) for r in x) ==
          [("f_kr", True), ("f_none", False)], x)
    x = R["ARG-OVER"]
    check("ARG-OVER double from an even register (4 words), struct by value skipped and counted",
          [(r["name"], r["def_words"], r["cite"]) for r in x] == [("f_dbl", 4, "ov:0x80100064 lw")] and
          "ARG-OVER skipped: struct by value: 1" in txt, (x, txt))
    sr = parse_text("src/ov/sr.c", "struct S { int a; };\nstruct S f_s(int a, int b) { }\nW4_8018020C f_w(s32 a) { }\n"
                    "struct S *f_p(int a) { }\nunion U f_d(double d) { }\nstruct S f_k(a)\nint a;\n{ }\n")["defs"]
    check("ARG-OVER words: a struct/union return (tagged or anonymous typedef) takes a hidden $a0 slot; a pointer does not",
          [(d["name"], d["words"]) for d in sr] == [("f_s", 3), ("f_w", 2), ("f_p", 1), ("f_d", 4), ("f_k", 2)], sr)
    x = R["DECL-ARITY"]
    check("DECL-ARITY multi-line decl 2 vs def 1; varargs def only below its named count",
          [(r["name"], r["decl_args"], r["def_args"]) for r in x] == [("f_ar", 2, 1)] and
          "multi-line: 1 / 1 / 1" in txt, x)
    check("unplaced: file in no TU counted apart", "definition: file in no TU: 1" in txt and
          "declaration: file in no TU: 1" in txt, txt)

    # 3.44 T5 asm labels (C0223): a declaration `CNAME(...) __asm__("SYM");` is SYM's; a definition of CNAME is SYM's
    b_c = "\n".join([
        '#include "x.h"', 'extern s32 aF1(s32 a) __asm__("f_al");', 'extern u8 aD1 __asm__("d_x");',
        'void aF2_impl(s32 a,', '    s32 b) __asm__("f_def");', 'void f_al(s32 a) { }', 'void aF2_impl(s32 a, s32 b) { }', ''])
    P5 = parse_text("src/ov/b.c", b_c)
    cls5 = {("ov", O): "h_al", ("ov", O + 16): "h_def", ("ov", O + 32): "h_decoy"}
    info5 = {h: ("unused", None, 0, None, [], True) for h in cls5.values()}
    info5["h_def"] = ("used", "ov:0x80100014 addu", 0, None, [], True)
    rows5, txt5 = compare_core({"src/ov/b.c": P5}, {"main": [], "ov": [("build/src/ov/b.o", "src/ov/b.c", ["src/ov/b.c"])]},
                               {"ov": {"f_al": {O}, "f_def": {O + 16}, "aF1": {O + 32}}, "main": {}},
                               {"main": (M, M + 0x100), "ov": (O, O + 0x100)},
                               {"main": ["main"], "ov": ["main", "ov"]}, cls5, info5, set(), [])
    check("asm-label declaration: named by its label, ret/params from the C head; an object label is no declaration",
          [(d["name"], d["line"], d["ret"], d["params"], d["shape"]) for d in P5["decls"]] ==
          [("f_al", 2, "int", "s32 a", "other"), ("f_def", 4, "void", "s32 a, s32 b", "multi-line")] and
          P5["objlabels"] == 1 and [(r["name"], r["decl_ret"], r["def_ret"], r["vaddr"]) for r in rows5
                                    if r["rule"] == "DECL-RET"] == [("f_al", "int", "void", hx(O))],
          (P5["decls"], rows5))
    check("asm-label definition: joined by its label (RET-VOID-READ def + its prototype), never by the C name",
          sorted((r["name"], r.get("decl_file") or r["def_file"]) for r in rows5 if r["rule"] == "RET-VOID-READ") ==
          [("f_def", "src/ov/b.c:4"), ("f_def", "src/ov/b.c:7")] and "joined by asm label 1" in txt5 and
          "object declarations skipped 1" in txt5 and "name not in the symtab" not in txt5, (rows5, txt5))

    # 3.44 T4 --check: the ledger's cites decode from the image with cite(); a row is used by a matching disagreement
    fl = _fleet({"ov": (O, 0x100, ["ov"], [(O, [E.andi(V0, V0, 0xFF)] + E.ret, "f_ret")], [])})
    dec_ = lambda b, va: cite(fl, b, va) if b in fl.bins and 0 <= va - O < 0x100 else None
    good = cite(fl, "ov", O)
    led = load_ledger("\n".join([
        "# comment", "callee\tdef_file\tkind\tcause\ttask\tcites",
        f"f_ret\tsrc/shared/cls_1.h\treturn\tc\tT4\t{good.replace(' ', '  ')}",
        f"f_dbl\tsrc/ov/a.c\tARG-OVER\tc\tT4\tov:0x80100000 lui $v0, 0x1; {good}",
        "f_gone\tsrc/ov/a.c\treturn\tc\tT4\t" + good, ""]))
    f, un, ul, ctxt = check_core(led, rows, dec_)
    check("--check good cite passes (whitespace-normalized), bad cite fails",
          [(a, b) for a, b, _ in f] == [("f_dbl", "ov:0x80100000 lui $v0, 0x1")] and good.startswith("ov:0x80100000 andi"),
          (f, good))
    check("--check unused row (no matching disagreement), matched rows used (bind_tu / def_file path, kind -> rule)",
          [L["callee"] for L in un] == ["f_gone"], un)
    check("--check unledgered = disagreements matched by no row",
          len(ul) == len(rows) - 2 and not any(r["name"] in ("f_ret", "f_dbl") and r["rule"] in ("DECL-RET", "ARG-OVER")
                                               for r in ul) and "unledgered disagreements" in ctxt, ctxt)

    # 3.44 T5 --check ret views: RET_AS sites (comments and the common.h #define masked/skipped) need a (fn, T) row; rows need a site
    # and fn's definition file
    rvp = {"include/common.h": parse_text("include/common.h", "#define RET_AS(T, fn, params) ((T (*)params)(fn))\n"),
           "src/ov/r.c": parse_text("src/ov/r.c", "u8 f_ret(void) {\n    return 1;\n}\n"),
           "src/ov/s.c": parse_text("src/ov/s.c", "void g(void) {\n    s32 x = RET_AS(s32, f_ret, (void))();\n"
                                    "    /* RET_AS(u8, f_ret, (void)) */\n    x += RET_AS( s16 , f_ret, (void))();\n}\n")}
    rvl = load_ledger("\n".join(["callee\tdef_file\tview\tcause\ttask\tcites",
                                 f"f_ret\tsrc/ov/r.c\ts32\tc\tT5\t{good}", f"f_ret\tsrc/ov/s.c\tu16\tc\tT5\t{good}", ""]))
    rf, rub, run_, rw, rtxt = check_ret_views(rvl, rvp, dec_)
    check("--check ret views: sites parsed, #define and comments skipped; unbacked, unused, wrong def_file found",
          rvp["src/ov/s.c"]["ret_as"] == [(2, "f_ret", "s32"), (4, "f_ret", "s16")] and rvp["include/common.h"]["ret_as"] == []
          and rf == [] and [(x[2], x[3]) for x in rub] == [("f_ret", "s16")] and [L["kind"] for L in run_] == ["u16"]
          and [L["def_file"] for L in rw] == ["src/ov/s.c"] and "RET_AS sites 2" in rtxt, (rvp["src/ov/s.c"]["ret_as"], rtxt))
    rvp2 = {"src/b.c": parse_text("src/b.c", '#define SHARED_FN f_sh\n#include "shared/h.h"\n'),
            "src/shared/h.h": parse_text("src/shared/h.h", "u8 SHARED_FN(void) {\n    return 1;\n}\n"),
            "src/a.c": parse_text("src/a.c", 'void g(void) {\n    extern u8 xa(void) __asm__("f_sh");\n'
                                  "    s32 x = RET_AS(s32, xa, (void))();\n}\n")}
    rvp2["src/c.c"] = parse_text("src/c.c", 'void cx(void) __asm__("f_al");\nvoid cx(void) {\n}\n'
                                 "void h(void) {\n    s32 y = RET_AS(s32, f_al, (void))();\n}\n")
    rvl2 = load_ledger("\n".join(["callee\tdef_file\tview\tcause\ttask\tcites", f"f_sh\tsrc/b.c\ts32\tc\tT5\t{good}",
                                  f"f_al\tsrc/c.c\ts32\tc\tT5\t{good}", ""]))
    rf2, rub2, run2, rw2, rtxt2 = check_ret_views(rvl2, rvp2, dec_)
    check("--check ret views: a SHARED_FN bind defines its name in the binding file; an asm-label alias site names the label "
          "and an aliased body defines it",
          rf2 == [] and rub2 == [] and run2 == [] and rw2 == [], rtxt2)
    # 3.44 T6 --check kr views: KR_AS(T, fn) sites (comments and the #define skipped) need a (fn) row of kr_view_casts.tsv
    # (5 fields, no view); rows need a site and fn's definition file; a bad cite fails; an alias site names the label
    kvp = {"include/common.h": parse_text("include/common.h", "#define KR_AS(T, fn) ((T (*)())(fn))\n"),
           "src/ov/r.c": parse_text("src/ov/r.c", "void f_kr(s32 a, s32 b) {\n}\nvoid f_k2(s32 a) {\n}\n"),
           "src/ov/s.c": parse_text("src/ov/s.c", 'void ka(void) __asm__("f_k2");\nvoid g(void) {\n    KR_AS(void, f_kr)(1);\n'
                                    "    /* KR_AS(void, f_zz)(1); */\n    KR_AS(void, ka)();\n    KR_AS(s32, f_zz)();\n}\n")}
    kvl = load_kr_ledger("\n".join(["callee\tdef_file\tcause\ttask\tcites", f"f_kr\tsrc/ov/r.c\tc\tT6\t{good}",
                                    f"f_k2\tsrc/ov/r.c\tc\tT6\t{good}", f"f_k3\tsrc/ov/s.c\tc\tT6\tmain:0x80010000 nop", ""]))
    kf, kub, kun, kw, ktxt = check_ret_views(kvl, kvp, dec_, kr=True)
    check("--check kr views: sites parsed (alias names the label); unbacked, unused, wrong def_file, failed cite found",
          kvp["src/ov/s.c"]["kr_as"] == [(3, "f_kr", "void"), (5, "ka", "void"), (6, "f_zz", "s32")]
          and kvp["src/ov/s.c"]["ret_as"] == [] and kvp["include/common.h"]["kr_as"] == [] and kvl[0]["cites"] == [good]
          and [x[0] for x in kf] == ["f_k3"] and [x[2] for x in kub] == ["f_zz"] and [L["callee"] for L in kun] == ["f_k3"]
          and [L["callee"] for L in kw] == ["f_k3"] and "kr-view rows 3, cites 3, KR_AS sites 3" in ktxt, (kvp["src/ov/s.c"]["kr_as"], ktxt))
    # 3.44 T6 def_file `-` (no C definition): a lying row matches only a disagreement of its callee+kind with def_file None;
    # a kr row is right iff no parsed file defines fn
    drows = [{"rule": "DECL-EMPTY", "binary": "ov", "vaddr": "0x80100000", "name": "f_asm", "def_file": None, "bind_tu": None,
              "decl_file": "src/ov/a.c:1"},
             {"rule": "DECL-EMPTY", "binary": "ov", "vaddr": "0x80100010", "name": "f_asm", "def_file": "src/ov/b.c:4",
              "bind_tu": None, "decl_file": "src/ov/b.c:1"}]
    dled = load_ledger("\n".join(["callee\tdef_file\tkind\tcause\ttask\tcites", f"f_asm\t-\tDECL-EMPTY\tc\tT6\t{good}",
                                  f"f_asm\t-\tARG-OVER\tc\tT6\t{good}", ""]))
    df_, dun, dul, _ = check_core(dled, drows, dec_)
    check("--check ledger def_file `-` matches a def_file-None disagreement of callee+kind only",
          df_ == [] and [L["kind"] for L in dun] == ["ARG-OVER"] and [r["vaddr"] for r in dul] == ["0x80100010"], (dun, dul))
    kvp3 = dict(kvp, **{"src/ov/t.c": parse_text("src/ov/t.c", "void h(void) {\n    KR_AS(void, f_asm)(1);\n"
                                                 "    KR_AS(void, f_kr)();\n}\n")})
    kvl3 = load_kr_ledger("\n".join(["callee\tdef_file\tcause\ttask\tcites", f"f_asm\t-\tc\tT6\t{good}",
                                     f"f_kr\t-\tc\tT6\t{good}", ""]))
    kw3 = check_ret_views(kvl3, kvp3, dec_, kr=True)[3]
    check("--check kr views: def_file `-` right iff no parsed file defines fn", [L["callee"] for L in kw3] == ["f_kr"], kw3)

    print("selftest", "OK" if ok else "FAILED")
    return 0 if ok else 1


# ----------------------------------------------------------------------------------------------- main
def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("-j", type=int, default=1, help="worker processes")
    ap.add_argument("--only", help="comma-separated aliases to measure (their stacks are loaded too)")
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--show", metavar="BINARY:VADDR")
    ap.add_argument("--compare", action="store_true", help="C declarations/definitions vs census.jsonl (3.44 T4)")
    ap.add_argument("--check", action="store_true", help="--compare, then the ledger's cites and coverage (3.44 T4)")
    a = ap.parse_args()
    if a.selftest:
        return selftest()
    if a.compare:
        print(compare(a.j)[1], end="")
        return 0
    if a.check:
        return check(a.j)
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
