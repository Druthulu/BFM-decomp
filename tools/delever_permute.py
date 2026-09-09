#!/usr/bin/env python3
"""delever_permute.py — rung D of the lever ladder: decomp-permuter on the RESIDUE exemplars (Phase 36 T6).

    tools/delever_permute.py --plan [--limit N] [--only X ...]          # the exemplar list from the ledger (no writes)
    tools/delever_permute.py --prepare TU FN                            # one exemplar's draft.c + target .s, no permuter
    tools/delever_permute.py --run [--limit K] [--workers W] [--secs S] [--cycles C] [-j J] [--only X ...]
    tools/delever_permute.py --bank [--label dN] [--only X ...] [--dirty-ok]
    tools/delever_permute.py --status
    tools/delever_permute.py --selftest

WHY A PERMUTER RUNG AT ALL. Rungs A–C (tools/delever.py) asked "does the object stay identical without this site?" and left
12,970 bodies where the answer was no for at least one site. Those sites are not magic: each is a shape the compiler would have
produced anyway from DIFFERENT C. The permuter's randomizer moves exactly those shapes (temps, statement and declaration order,
scoping, operand order), so the residue is its natural population — and the seed is the LEVER-FREE body, which is what makes this
different from every earlier permuter run in this project: the search starts from C that has no pins and no asm at all, and any
score-0 it reaches is by construction a lever-free match.

THE PIPELINE PER EXEMPLAR (probe-proven at S98, the T6 log entry):
  1. the lever-free TU text  — delever's own rung-A rewrite of every REMOVABLE site of the body (a site it REFUSES makes the
     exemplar UNSTRIPPABLE: recorded, skipped — never a silently narrowed scope, R43/silently-narrowed-tool-scope).
  2. the ISOLATED TU         — every OTHER definition replaced by its prototype, every `#include "…/shared/…/func_*.h"` replaced
     by the prototypes that header defines, INCLUDE_ASM/INCLUDE_RODATA lines and file-scope asm statements dropped: the object
     the permuter compiles must hold ONE .text function, because the masked scorer compares whole .text.
  3. cpp -P with the BUILD's own CPPFLAGS + -I<the TU's directory> (common.h, the prelude, engine_types.h and the GTE header
     expand here — p16_permute.make_base_c runs its own cpp WITHOUT includes and would lose them) -> draft.c.
  4. the target             — the tree's OWN (levered) body compiled by the build's tail into a one-function object, so it
     carries the candidates' relocations by construction; `tools/verbatim_target_s.py` regenerates the ROM listing beside it
     and `match_one` must call that body a MATCH before the search starts (R34: the ROM image is the independent oracle that
     PROVES the target; R56: check the baseline). S99 learned this the hard way — see THE INSTRUMENT below.
  5. tools/permuter_ils.py    — warm-restarting decomp-permuter, the weight profile chosen from the NEEDED sites' kinds AND
     the register each pin names (callee-saved -> regalloc, caller-saved -> cse, barriers/launders/keep-alives -> schedule).
  6. a score-0 winner is a CANDIDATE, never a bank: --bank puts the function's definition back through
     `delever.py --apply-body` (which refuses a body that still carries a class A/B lever and judges it on the object's bytes
     through every recipe of the TU), then re-folds the cpp-expanded GTE asm with `gte_consolidate.py --apply --rejudge`.
     The clean fleet run (R22) gates the batch, as it gates every batch of this phase.

SCRATCH IS KEYED BY ALIAS+FN (R48): `.run/P36/permuter/<alias>__<fn>/` — a function NAME is not unique across the fleet (the
overlays overlap in RAM, so two different bodies can both be `func_8013B274`), and the permuter's own scratch/winner paths are
keyed by the bare name. Every attempt is recorded in `.run/P36/permuter/outcomes.jsonl`, which is also the skip list.

THE INSTRUMENT, AND WHY IT IS CHECKED BEFORE IT IS BELIEVED (S99). The first two campaigns returned 0 of 16 with a straight
face. Both were the harness: the target had been ASSEMBLED FROM A DISASSEMBLY LISTING, which is a second toolchain with its own
answers — objdump prints the pseudo-instruction `move` for `addu rX,rY,$zero` and gas assembles it as `or` (24 wrong words in
one 234-instruction function), and a listing's %hi/%lo pairs come back resolved with no relocation while every candidate carries
one. The permuter scored 28 for a body that IS byte-identical, so score 0 was unreachable and every NO-MATCH was its own. The
control that names this in one line is `--positive-control`, and the base score of the tree's own body is now 0. R40: exonerate
the instrument before attributing a failure to its subject; the campaign that skips this control cannot tell a hard population
from a broken scorer.

NEVER RUN THE CAMPAIGN AS A HARNESS BACKGROUND TASK (the low-memory guard kills it): `setsid nohup … &` + a Monitor on the log.
"""
import argparse
import collections
import json
import os
import pathlib
import re
import shutil
import subprocess
import sys
import threading
import time
from concurrent.futures import ThreadPoolExecutor

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
import delever as dl                # noqa: E402
import delever_oracle as oracle     # noqa: E402
import lever_census as lc           # noqa: E402
import p16_permute as p16           # noqa: E402
import share_census as sc           # noqa: E402

RUN = REPO / ".run" / "P36" / "permuter"
OUTCOMES = RUN / "outcomes.jsonl"
PY = str(REPO / ".venv" / "bin" / "python")
CPP = "mipsel-linux-gnu-cpp"
# the Makefile's own CPPFLAGS (line 1010) — the draft must see the same macro world the build sees
CPPFLAGS = ["-lang-c", "-Iinclude", "-undef", "-Wall", "-fno-builtin", "-Dmips", "-D__GNUC__=2",
            "-D__OPTIMIZE__", "-Dpsx", "-D_PSYQ", "-D_MIPSEL", "-D_LANGUAGE_C"]
# decomp-permuter parses base.c with pycparser, which rejects `__attribute__((packed, aligned(1)))` outright
# ("Syntax error in base.c" -> the run REFUSES and permutes nothing). The draft therefore defines the keyword away.
# This is a fidelity LOSS, not a correctness one: a packed struct the exemplar actually uses will lay out differently
# in the search, so that exemplar simply cannot reach score 0 — and the bank gate is the real object oracle either
# way. The count is recorded per attempt (`attrs`) so the yield report can say whether it mattered (76 sites in the
# whole tree at T5; the class belongs to the types phase, R95).
CPP_ATTR = "-D__attribute__(x)="
INCLUDE_ASM_LINE = re.compile(r"^[ \t]*INCLUDE_(?:ASM|RODATA)\b[^\n]*\n", re.M)
INCLUDE_LINE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*"([^"]+)"[^\n]*\n', re.M)
SCHED_KINDS = {"barrier", "launder", "keepalive"}
_LOCK = threading.Lock()


class Unstrippable(Exception):
    """the body cannot be made lever-free by the rewrite table — the exemplar is T7's, not rung D's."""


# ----------------------------------------------------------------------------------------------------------------------
# the population: the residue's classes, one exemplar each
# ----------------------------------------------------------------------------------------------------------------------
def load_outcomes():
    rows = []
    if OUTCOMES.exists():
        for l in OUTCOMES.read_text().splitlines():
            if l.strip():
                rows.append(json.loads(l))
    return rows


def outcome_append(row):
    RUN.mkdir(parents=True, exist_ok=True)
    with _LOCK, open(OUTCOMES, "a") as f:
        f.write(json.dumps(row) + "\n")


def alias_of(tu, row=None):
    """the binary whose object holds this TU (a shared header: its first includer's). The ledger row's own aliases first."""
    al = (row or {}).get("aliases")
    if al:
        return al[0]
    by_src = oracle.recipes_by_src(oracle.load_recipes()["recipes"])
    src = tu
    if tu.endswith(".h"):
        inc = dl.includers().get(tu) or []
        src = next((t for t in inc if t in by_src), None)
        if src is None:
            return None
    recs = by_src.get(src) or []
    return recs[0]["alias"] if recs else None


def matches(ex, only):
    if not only:
        return True
    return any(o == ex["fn"] or o == ex["tu"] or o in ex["tu"] or ex["nhash"].startswith(o) or o == ex["alias"] for o in only)


def exemplars(only=(), limit=None, include_done=False):
    """One exemplar per RESIDUE text class, largest class first (a match banks every copy), then fewest NEEDED sites."""
    cur, order = {}, []
    for r in dl.load_ledger():
        k = (r.get("tu"), r.get("fn"))
        if not k[0] or not k[1]:
            continue
        if k not in cur:
            order.append(k)
        cur[k] = r
    groups = collections.OrderedDict()
    for k in order:
        r = cur[k]
        if r.get("verdict") != "RESIDUE" or r["fn"] == dl.FILE_SCOPE_FN:
            continue                                      # a TU's file-scope `volatile` pseudo-body is not a function to permute
        groups.setdefault(r.get("nhash_after") or r.get("nhash_before"), []).append((k, r))
    done = set() if include_done else {o["nhash"] for o in load_outcomes() if o.get("kind") == "attempt"}
    out = []
    for nh, members in groups.items():
        if nh in done:
            continue
        (tu, fn), r = members[0]
        needed = [s for s in r.get("sites", []) if s.get("verdict") == "NEEDED"]
        out.append(dict(nhash=nh, tu=tu, fn=fn, alias=(r.get("aliases") or [None])[0], copies=len(members),
                        needed=len(needed), kinds=sorted({s["kind"] for s in needed}),
                        regs=sorted({s.get("detail", "") for s in needed if s["kind"] == "pin"}),
                        members=[dict(tu=t, fn=f) for (t, f), _ in members], row=r))
    out.sort(key=lambda e: (-e["copies"], e["needed"], e["tu"], e["fn"]))
    out = [e for e in out if matches(e, only)]
    return out[:limit] if limit else out


CALLEE_SAVED = {f"${n}" for n in range(16, 24)} | {f"$s{n}" for n in range(8)} | {"$fp", "$30"}


def klass_for(kinds, regs=()):
    """the permuter_weights profile for a residue, from the NEEDED sites' kinds AND the REGISTER each pin names (the profile
    name is accepted verbatim by classify()).

    The register is the part S99 learned by reading a residual instead of assuming one. A pin on a CALLEE-SAVED register
    ($16-$23) is an allocation-ORDER residual — the regalloc profile's declaration/statement reordering is its lever. A pin
    on a CALLER-SAVED one ($2/$3/$4-$7/…) is not: the S99 control on func_80163EC8 (`register … __asm__("$2")`) left exactly
    a v0/v1 swap — `lw v1,68(s1); li v0,-33; and v0,v1,v0` against `lw v0,68(s1); li v1,-33; and v0,v0,v1` — which is the
    operand ORDER of one `&`, and the regalloc profile weights `perm_commutative` 2.0 while the cse profile weights it 40.0.
    Steering that search by "it was a pin, so regalloc" spends the whole budget 20x away from the one lever that closes it."""
    ks = set(kinds)
    rs = {r for r in regs if r}
    if "pin" in ks and rs and rs & CALLEE_SAVED:
        return "regalloc"
    if "pin" in ks and rs and not (rs & CALLEE_SAVED):
        return "cse"
    if ks and ks <= SCHED_KINDS:
        return "schedule"
    return "regalloc"


# ----------------------------------------------------------------------------------------------------------------------
# step 1-3: the lever-free, isolated, preprocessed draft
# ----------------------------------------------------------------------------------------------------------------------
_sites_cache = None


def tu_sites(tu):
    """the census's sites for one TU. Built ONCE, into a local, and published under the lock: the workers are threads, and
    publishing the empty dict before filling it (2 s for 53,355 rows) let every other worker read "no site in this TU" and
    report a whole batch UNSTRIPPABLE — a race that lies in the tool's own voice."""
    global _sites_cache
    with _LOCK:
        if _sites_cache is None:
            built = collections.defaultdict(list)
            for s in dl.load_sites():
                built[s["tu"]].append(s)
            _sites_cache = built
        return _sites_cache.get(tu, [])


def body_sites(tu, fn):
    return [s for s in tu_sites(tu) if s.get("fn") == fn]


def file_asm_sites(tu):
    """the TU's file-scope asm STATEMENTS (13 in the fleet: 7 rodata carves, 6 barriers) — asked of the census, never
    re-parsed: a bare `__asm__(` scan cannot tell a statement from the asm-LABEL clause of a declaration
    (`extern void func_8005C324(…) __asm__("memcpy");` — 6,423 of those), and eating one leaves a headless K&R body."""
    return [s for s in tu_sites(tu) if s.get("scope") == "file" and s["cls"] == "B"
            and s["kind"] not in lc.NON_LEVER_KINDS and s["kind"] != "asm-label"]


def lever_free_text(tu, raw, fn, sites, strip=True):
    """the TU's text with every REMOVABLE site of THIS body rewritten away (delever's own table) and its file-scope asm
    statements deleted (the draft compares .text only); Unstrippable if any body site refuses.
    strip=False keeps every lever — that is the CALIBRATION seed: the body as the tree has it, which must score MATCH
    against the regenerated target or the harness (target, isolation, cpp, compile) is not measuring this function."""
    m = dl.same_len_mask(raw)
    ls = dl.line_starts(raw)
    edits, refused = [], []
    for s in file_asm_sites(tu):
        pos = ls[s["line"] - 1] + s["col"] - 1
        e = dl.stmt_end(m, pos)
        if dl.ASM_HEAD.match(m, pos) and e > 0:
            edits.append((pos, dl.consume_marker(raw, m, e), ""))
    for s in (sites if strip else []):
        if (s["cls"], s["kind"]) not in dl.REMOVABLE:
            if s["kind"] in dl.DEFERRED_KINDS:
                refused.append((s["kind"], s["line"], "asm-body: T7's work"))
            continue
        try:
            edits += dl.site_edits(raw, m, ls, s)
        except dl.Refuse as ex:
            refused.append((s["kind"], s["line"], str(ex)[:120]))
    if refused:
        raise Unstrippable(refused)
    if not edits:
        return raw
    try:
        return dl.apply_edits(raw, edits)
    except dl.Refuse as ex:
        raise Unstrippable([("<combination>", 0, str(ex)[:120])])


def prototype_at(text, m, start):
    """`<head>;` for the definition that starts at index `start` — the head up to the last `)` before its opening `{`."""
    o = m.find("{", start)
    if o < 0:
        return None
    close = m.rfind(")", start, o)
    if close < 0:
        return None
    head = " ".join(text[start:close + 1].split())
    return head + ";"


def header_prototypes(path):
    """the prototypes of every function a shared header DEFINES (a static one keeps `static`)."""
    p = REPO / path
    if not p.exists():
        return []
    text = p.read_text(errors="surrogateescape")
    m = dl.same_len_mask(text)
    ls = dl.line_starts(text)
    out = []
    for r in sc.scan_text(text, path, shared_defs=None):
        if r["form"] != "def":
            continue
        pr = prototype_at(text, m, ls[r["line"] - 1])
        if pr:
            out.append(pr)
    return out


def isolate(tu, text, fn):
    """every OTHER definition -> its prototype; shared-header includes -> their prototypes; INCLUDE_ASM/file-scope asm dropped."""
    m = dl.same_len_mask(text)
    ls = dl.line_starts(text)
    recs = sc.scan_text(text, tu, shared_defs=None)
    defs = [r for r in recs if r["form"] == "def"]
    if not any(r["name"] == fn for r in defs):
        raise Unstrippable([("<isolate>", 0, f"{fn} is not defined in {tu}")])
    edits = []
    for r in defs:
        s, e = ls[r["line"] - 1], ls[r["end"]]

        if r["name"] == fn:
            continue
        pr = prototype_at(text, m, s)
        if pr is None:
            raise Unstrippable([("<isolate>", r["line"], f"no prototype for {r['name']}")])
        edits.append((s, e, pr + "\n"))
    for mm in INCLUDE_ASM_LINE.finditer(m):
        edits.append((mm.start(), mm.end(), ""))
    for mm in INCLUDE_LINE.finditer(m):
        inc = mm.group(1)
        rel = os.path.normpath(os.path.join(os.path.dirname(tu), inc))
        if not rel.startswith("src/shared/"):
            continue
        pr = header_prototypes(rel)
        if pr:                                            # a macro-only header (the prelude) has none: keep the include
            edits.append((mm.start(), mm.end(), "\n".join(pr) + "\n"))
    return dl.apply_edits(text, sorted(edits, key=lambda x: x[0]))


def drop_file_scope_asm(text, tu):
    """delete every asm STATEMENT that is not inside a function — after cpp, `include/include_asm.h` has injected
    `__asm__(".include \\"include/labels.inc\\"");` at the top of every draft, and the permuter's own compile.sh
    already prepends `.include "macro.inc"`, so the assembler dies on `Macro 'glabel' was already defined`.
    An asm-LABEL clause (`extern void f(…) __asm__("memcpy");`, 6,423 of them) is NOT a statement: it follows a
    declarator, so the preceding non-space character is not `;` or `}`."""
    m = dl.same_len_mask(text)
    ls = dl.line_starts(text)
    spans = [(ls[r["line"] - 1], ls[r["end"]]) for r in sc.scan_text(text, tu, shared_defs=None) if r["form"] == "def"]
    edits = []
    for mm in dl.ASM_HEAD.finditer(m):
        p = mm.start()
        if any(s <= p < e for s, e in spans):
            continue
        prev = m[:p].rstrip()
        if prev and prev[-1] not in ";}":
            continue                                      # an asm-label clause on a declaration
        e = dl.stmt_end(m, p)
        if e > 0:
            edits.append((p, e, ""))
    return dl.apply_edits(text, edits) if edits else text


def cpp_expand(tu, text):
    """the build's cpp over the isolated text (fed on stdin, so `-I<the TU's directory>` is what resolves its relative includes)."""
    p = subprocess.run([CPP, "-P"] + CPPFLAGS + [CPP_ATTR, "-I" + os.path.dirname(tu), "-"],
                       input=text, capture_output=True, text=True, cwd=REPO)
    if p.returncode or not p.stdout.strip():
        raise Unstrippable([("<cpp>", 0, (p.stderr.strip().splitlines() or ["empty output"])[-1][:160])])
    return p.stdout


def scratch_of(alias, fn):
    return RUN / f"{alias}__{fn}"


def prepare(ex, quiet=False, require_sites=True):
    """(scratch dir, draft path, target path, klass) for one exemplar — the whole probe-2 pipeline."""
    tu, fn = ex["tu"], ex["fn"]
    alias = ex["alias"] or alias_of(tu, ex.get("row"))
    if not alias:
        raise Unstrippable([("<alias>", 0, f"no binary compiles {tu}")])
    ex["alias"] = alias
    raw = (REPO / tu).read_text(errors="surrogateescape")
    sites = body_sites(tu, fn)
    if not sites and require_sites:
        raise Unstrippable([("<census>", 0, f"the census has no site in {tu}:{fn} (stale? rerun lever_census --sites)")])
    d = scratch_of(alias, fn)
    if d.exists():
        shutil.rmtree(d)
    (d / "gas").mkdir(parents=True)
    (d / "splat").mkdir()
    for strip, name in ((True, "draft.c"), (False, "levered.c")):
        free = lever_free_text(tu, raw, fn, sites, strip=strip)
        iso = isolate(tu, free, fn)
        text = drop_file_scope_asm(cpp_expand(tu, iso), tu)
        if strip:
            (d / "tu.c").write_text(free, errors="surrogateescape")     # the lever-free TU (what rung A would have written)
            (d / "iso.c").write_text(iso, errors="surrogateescape")     # + one body, the rest prototypes (pre-cpp; for reading)
        (d / name).write_text(text, errors="surrogateescape")
        if strip:
            base = p16.make_base_c(text)
            if not p16.defines_fn(base, fn):
                raise Unstrippable([("<base>", 0, f"base.c would lose the definition of {fn} (inspect {d}/draft.c)")])
    # TWO target forms, for the two instruments. --gas is the ASSEMBLABLE one ($-registers, .L labels, symbol names) that
    # `p16_permute.setup` turns into target.o; the default splat listing is the WORD oracle `match_one.py` reads. Nothing
    # ever assembles the splat form — pasting it into decomp.me was P34's `invalid operands 'li a2,2'` (R98/DK-81), and
    # `mipsel-as` refuses its bare `addiu sp,sp,-152` the same way.
    for args, sub, name in (( ["--gas"], "gas", f"{fn}.gas.s"), ([], "splat", f"{fn}.s")):
        r = subprocess.run([PY, "tools/verbatim_target_s.py", "--binary", alias, "--fn", fn] + args
                           + ["--out", str(d / "tgt")], capture_output=True, text=True, cwd=REPO)
        tgt = d / "tgt" / alias / name
        if r.returncode or not tgt.exists():
            raise Unstrippable([("<target>", 0, ((r.stderr or r.stdout).strip().splitlines() or ["no listing"])[-1][:160])])
        shutil.copy(tgt, d / sub / f"{fn}.s")              # p16_permute.setup / match_one.py read <dir>/<fn>.s
    # THE TARGET OBJECT: the tree's own (levered) body through the build's own tail, so it carries the candidates'
    # relocations by construction. Its fidelity is not assumed — `closeness(levered)` must be MATCH against the ROM
    # listing above before any search runs (R34: the independent oracle proves the target; R56: check the baseline).
    r = subprocess.run(["tools/permuter/compile.sh", str(d / "levered.c"), "-o", str(d / "target.o")],
                       capture_output=True, text=True, cwd=REPO)
    if r.returncode or not (d / "target.o").exists():
        raise Unstrippable([("<target.o>", 0, ((r.stderr or r.stdout).strip().splitlines() or ["compile failed"])[-1][:160])])
    if not quiet:
        n = len((d / "draft.c").read_text(errors="surrogateescape").splitlines())
        print(f"  prepared {alias}__{fn}: draft {n} lines, target {(r.stdout or '').strip().split()[-3:]}", flush=True)
    return d, d / "draft.c", d / "gas" / f"{fn}.s", klass_for(ex["kinds"], ex.get("regs", ()))


# ----------------------------------------------------------------------------------------------------------------------
# the calibration (R39/R56): the harness must agree with the tree before it may judge a candidate
# ----------------------------------------------------------------------------------------------------------------------
MISMATCH_RE = re.compile(r"(\d+) mismatched")


def closeness(d, fn, c):
    """(mismatched instructions, first line) from tools/match_one.py against the SPLAT listing — 0 == byte-identical
    (relocation-masked). None when the tool could not judge (R61: not judged is not a verdict)."""
    r = subprocess.run([PY, "tools/match_one.py", fn, "--c", str(c), "--asm-subdir", (d / "splat").as_posix()],
                       capture_output=True, text=True, cwd=REPO)
    first = ((r.stdout or "") + (r.stderr or "")).strip().splitlines()
    first = first[0] if first else "(no output)"
    if "MATCH" in first and "mismatched" not in first:
        return 0, first
    mm = MISMATCH_RE.search(first)
    return (int(mm.group(1)) if mm else None), first


def positive_control(a):
    """Can rung D close a gap it is KNOWN to be able to close? Take a body the tree already matches, perturb it by ONE
    reversible source change (the first commutative operand swap `delever` can generate), confirm the perturbed body no
    longer matches, and give the permuter one cycle to find its way back to score 0.

    Without this, "0 of 16" says nothing about the residue: it could equally be a harness that cannot reach ANY target
    (R40 — exonerate the instrument before attributing the failure to its subject). With it, a PASS means the search
    space, the target, the scorer and the winner path all work, and a 0-yield campaign is a fact about the population."""
    tu, fn = a.positive_control
    raw = (REPO / tu).read_text(errors="surrogateescape")
    d_ = next((r for r in sc.scan_text(raw, tu, shared_defs=None) if r["form"] == "def" and r["name"] == fn), None)
    if d_ is None:
        sys.exit(f"delever_permute --positive-control: {fn} is not defined in {tu}")
    swaps = dl.commutative_swaps(raw, tu, fn, d_)
    if not swaps:
        sys.exit(f"delever_permute --positive-control: {tu}:{fn} has no commutative operator to perturb — pick another body")
    ex = dict(nhash="", tu=tu, fn=fn, alias=alias_of(tu), copies=1, needed=0, kinds=[], regs=[], members=[], row={})
    d, draft, tgt, _ = prepare(ex, quiet=False, require_sites=False)
    base, base_line = closeness(d, fn, draft)
    desc, perturbed = swaps[a.which]
    (d / "perturbed_tu.c").write_text(perturbed, errors="surrogateescape")
    pert = drop_file_scope_asm(cpp_expand(tu, isolate(tu, perturbed, fn)), tu)
    (d / "draft.c").write_text(pert, errors="surrogateescape")       # the permuter's seed IS the perturbed body
    after, after_line = closeness(d, fn, d / "draft.c")
    print(f"positive control {alias_of(tu)}__{fn}: the tree's own body {base_line[:40]} · perturbed by `{desc}` {after_line[:60]}",
          flush=True)
    if base != 0:
        sys.exit("delever_permute --positive-control: the UNPERTURBED body does not match — calibrate first (R56)")
    if after == 0:
        sys.exit(f"delever_permute --positive-control: `{desc}` is byte-neutral here — nothing to find; try --which {a.which + 1}")
    rel = d.relative_to(REPO).as_posix()
    log = d / "positive.log"
    cmd = [PY, "tools/permuter_ils.py", fn, "--draft", rel + "/draft.c", "--asm-subdir", rel + "/gas",
           "--klass", "cse", "--cycles", str(a.cycles), "--secs", str(a.secs), "--j", str(a.j),
           "--winners", rel, "--pd", rel + "/pd"]
    with open(log, "w") as f:
        f.write(" ".join(cmd) + "\n\n")
        f.flush()
        subprocess.run(cmd, cwd=REPO, stdout=f, stderr=subprocess.STDOUT, timeout=a.cycles * (a.secs + 45) + 300)
    out = log.read_text(errors="replace")
    won = (d / f"{fn}.c").exists()
    print(f"positive control: {'PASS — the permuter recovered score 0' if won else 'FAIL — it did not, in '
          f'{a.cycles}x{a.secs}s'} ({[l for l in out.splitlines() if 'cycle' in l][-1:] or ['no cycle line']})")
    return 0 if won else 1


def calibrate_one(ex, quiet=False):
    """the control: the body AS THE TREE HAS IT (levers and all) must be MATCH against the regenerated target. It proves the
    whole chain — the target from the ROM image, the isolation, the cpp expansion, the pinned triple — is measuring THIS
    function. Then the lever-free draft's distance is the search's real starting point, and it is worth recording (R37)."""
    d, draft, tgt, klass = prepare(ex, quiet=quiet)
    lev, lev_line = closeness(d, ex["fn"], d / "levered.c")
    free, free_line = closeness(d, ex["fn"], draft)
    ok = (lev == 0)
    if not quiet:
        print(f"  {'OK  ' if ok else 'FAIL'} {ex['alias']}__{ex['fn']}: levered {lev_line[:60]} · lever-free {free_line[:60]}",
              flush=True)
    return dict(ok=ok, levered=lev, free=free, levered_line=lev_line, free_line=free_line, klass=klass, d=d)


# ----------------------------------------------------------------------------------------------------------------------
# step 5: the permuter
# ----------------------------------------------------------------------------------------------------------------------
BEST_RE = re.compile(r"best score = (\d+)")


def run_one(ex, secs, cycles, j, max_start=None):
    t0 = time.time()
    row = dict(kind="attempt", ts=time.strftime("%Y-%m-%d %H:%M:%S"), nhash=ex["nhash"], tu=ex["tu"], fn=ex["fn"],
               alias=ex["alias"], copies=ex["copies"], needed=ex["needed"], kinds=ex["kinds"], regs=ex.get("regs", []),
               secs=secs, cycles=cycles, j=j)
    try:
        d, draft, tgt, klass = prepare(ex)
    except Unstrippable as ex_:
        row.update(verdict="UNSTRIPPABLE", why=ex_.args[0][:6], seconds=round(time.time() - t0, 1))
        outcome_append(row)
        print(f"  {ex['alias'] or '?'}__{ex['fn']}: UNSTRIPPABLE — {ex_.args[0][:2]}", flush=True)
        return row
    # EVERY attempt calibrates itself first (R56): the body as the tree has it must be MATCH against the regenerated
    # target, or this harness is not measuring this function and its budget would buy a meaningless number. ~15 s
    # against ~12 min of search.
    lev, lev_line = closeness(d, ex["fn"], d / "levered.c")
    free, free_line = closeness(d, ex["fn"], draft)
    row.update(levered=lev, free=free, levered_line=lev_line[:120], free_line=free_line[:120])
    if lev != 0:
        row.update(verdict="UNCALIBRATED", seconds=round(time.time() - t0, 1))
        outcome_append(row)
        print(f"  {ex['alias']}__{ex['fn']}: UNCALIBRATED — the LEVERED body is not MATCH ({lev_line[:80]})", flush=True)
        return row
    if max_start is not None and (free is None or free > max_start):
        # TRIAGE, not a verdict about the function: a lever-free body this far from the target (usually because removing a
        # hand-placed instruction changed the instruction COUNT and shifted everything after it) will not close in a
        # 12-minute search. Recorded with its distance; `--include-done` draws it again when the budget or the rung grows.
        row.update(verdict="FAR", seconds=round(time.time() - t0, 1))
        outcome_append(row)
        print(f"  {ex['alias']}__{ex['fn']}: FAR start={free} > {max_start} — not searched ({ex['copies']} copies)", flush=True)
        return row
    rel = d.relative_to(REPO).as_posix()
    log = d / "ils.log"
    cmd = [PY, "tools/permuter_ils.py", ex["fn"], "--draft", (draft.relative_to(REPO)).as_posix(),
           "--asm-subdir", rel + "/gas", "--klass", klass, "--cycles", str(cycles), "--secs", str(secs),
           "--j", str(j), "--winners", rel, "--pd", rel + "/pd", "--target-o", rel + "/target.o"]
    row["klass"] = klass
    row["cmd"] = " ".join(cmd)
    rc = None
    with open(log, "w") as f:
        f.write(" ".join(cmd) + "\n\n")
        f.flush()
        try:
            rc = subprocess.run(cmd, cwd=REPO, stdout=f, stderr=subprocess.STDOUT,
                                timeout=cycles * (secs + 45) + 300).returncode
        except subprocess.TimeoutExpired:
            f.write("\n[delever_permute] the ILS wrapper overran its own budget — killed\n")
    out = log.read_text(errors="replace")
    scores = [int(x) for x in BEST_RE.findall(out)]
    win = d / f"{ex['fn']}.c"
    # NOT JUDGED IS NOT A VERDICT (R61): a setup failure, a parser refusal or a wrapper that never iterated is its own
    # outcome — reporting it as NO-MATCH is how a tool reports work it never did.
    if win.exists():
        verdict = "MATCH"
    elif "setup FAILED" in out:
        verdict = "SETUP-FAILED"
    elif "ABORTED" in out or "REFUSED" in out:
        verdict = "ABORTED"
    elif "cycle 1:" not in out:
        verdict = "NOT-JUDGED"
    else:
        verdict = "NO-MATCH"
    row.update(best=(min(scores) if scores else None), seconds=round(time.time() - t0, 1), rc=rc,
               winner=(win.relative_to(REPO).as_posix() if win.exists() else None), verdict=verdict)
    outcome_append(row)
    print(f"  {ex['alias']}__{ex['fn']}: {row['verdict']} start={row['free']} best={row['best']} "
          f"({row['seconds']}s, {ex['copies']} copies, {ex['needed']} needed, {klass})", flush=True)
    return row


# ----------------------------------------------------------------------------------------------------------------------
# step 6: the bank (serial — every step here runs `make`)
# ----------------------------------------------------------------------------------------------------------------------
def winner_body(winner_c, fn, tu):
    """the winner's definition of fn, as the text `delever --apply-body` splices in."""
    draft = p16.winner_to_draft(pathlib.Path(winner_c).read_text(errors="surrogateescape"))
    ls = dl.line_starts(draft)
    for r in sc.scan_text(draft, tu, shared_defs=None):
        if r["form"] == "def" and r["name"] == fn:
            return draft[ls[r["line"] - 1]:ls[r["end"]]]
    return None


def bank(a):
    outs = load_outcomes()
    banked = {(o["alias"], o["fn"], o["nhash"]) for o in outs if o.get("kind") == "bank" and o.get("applied")}
    todo = [o for o in outs if o.get("kind") == "attempt" and o.get("verdict") == "MATCH"
            and (o["alias"], o["fn"], o["nhash"]) not in banked
            and (not a.only or any(x in (o["fn"], o["tu"], o["alias"]) or o["nhash"].startswith(x) for x in a.only))]
    if not todo:
        print("delever_permute --bank: no unbanked winner (R68: nothing to do, loudly)")
        return 1
    ok, bad = 0, 0
    for o in todo:
        d = scratch_of(o["alias"], o["fn"])
        body = winner_body(REPO / o["winner"], o["fn"], o["tu"]) if o.get("winner") else None
        if not body:
            print(f"  {o['alias']}__{o['fn']}: the winner holds no definition of {o['fn']} — SKIPPED", flush=True)
            bad += 1
            continue
        bf = d / "body.c"
        bf.write_text(body, errors="surrogateescape")
        cmd = [PY, "tools/delever.py", "--apply-body", o["tu"], o["fn"], bf.relative_to(REPO).as_posix(),
               "--label", a.label, "--rung", "D"] + (["--dirty-ok"] if a.dirty_ok else [])
        r = subprocess.run(cmd, cwd=REPO, capture_output=True, text=True)
        print("   " + (r.stdout or r.stderr).strip().splitlines()[-1][:220], flush=True)
        row = dict(kind="bank", ts=time.strftime("%Y-%m-%d %H:%M:%S"), nhash=o["nhash"], tu=o["tu"], fn=o["fn"],
                   alias=o["alias"], label=a.label, applied=(r.returncode == 0),
                   apply_out=(r.stdout or r.stderr).strip()[-400:])
        if r.returncode == 0:
            g = subprocess.run([PY, "tools/gte_consolidate.py", "--apply", "--only", o["tu"], "--rejudge",
                                "--label", a.label + "g"], cwd=REPO, capture_output=True, text=True)
            row["gte_refold"] = (g.stdout or g.stderr).strip()[-300:]
            ok += 1
        else:
            bad += 1
        outcome_append(row)
    print(f"delever_permute --bank: {ok} applied, {bad} rejected of {len(todo)} — "
          f"now the clean fleet run (R22) and one commit per batch (R42)")
    return 0 if ok else 1


# ----------------------------------------------------------------------------------------------------------------------
# the commands
# ----------------------------------------------------------------------------------------------------------------------
def cmd_plan(a):
    ex = exemplars(a.only, a.limit, a.include_done)
    tot = exemplars(include_done=True)
    kinds = collections.Counter(k for e in ex for k in e["kinds"])
    print(f"delever_permute --plan: {len(ex)} exemplars drawable of {len(tot)} residue classes "
          f"({sum(e['copies'] for e in ex):,} bodies behind them); NEEDED kinds {dict(kinds)}")
    for e in ex[:a.show]:
        print(f"  {e['copies']:4d} copies · {e['needed']:2d} needed {','.join(e['kinds']):<28} "
              f"{klass_for(e['kinds'], e.get('regs', ())):8} {','.join(e.get('regs', [])) or '-':<12} "
              f"{e['alias'] or alias_of(e['tu'], e['row'])} {e['tu']}:{e['fn']}")
    if len(ex) > a.show:
        print(f"  … {len(ex) - a.show} more")
    return 0


def cmd_run(a):
    dl.ensure_census(a.j)
    ex = exemplars(a.only, a.limit, a.include_done)
    if not ex:
        print("delever_permute --run: no drawable exemplar (every class attempted, or --only matched none)")
        return 1
    per = max(1, a.j // max(1, a.workers))
    print(f"delever_permute --run: {len(ex)} exemplars, {a.workers} at a time, {a.cycles} cycles x {a.secs}s @ -j{per} each "
          f"(budget ≈ {len(ex) / a.workers * a.cycles * a.secs / 3600:.1f} h)", flush=True)
    t0 = time.time()
    rows = []
    with ThreadPoolExecutor(max_workers=a.workers) as pool:
        for r in pool.map(lambda e: run_one(e, a.secs, a.cycles, per, a.max_start), ex):
            rows.append(r)
    won = [r for r in rows if r["verdict"] == "MATCH"]
    v = collections.Counter(r["verdict"] for r in rows)
    print(f"\npermuter: {len(won)} of {len(rows)} exemplars matched lever-free in {(time.time() - t0) / 3600:.2f} h "
          f"({sum(r['copies'] for r in won):,} of {sum(r['copies'] for r in rows):,} bodies behind them) — "
          + " · ".join(f"{k} {n}" for k, n in v.most_common()))
    return 0


def cmd_calibrate(a):
    ex = exemplars(a.only, a.limit or 6, include_done=True)
    print(f"delever_permute --calibrate: {len(ex)} exemplars — the levered body must be MATCH, the lever-free one is the "
          f"search's starting distance", flush=True)
    rows, dist = [], []
    for e in ex:
        try:
            r = calibrate_one(e)
        except Unstrippable as u:
            print(f"  SKIP {e['tu']}:{e['fn']} — {u.args[0][:2]}", flush=True)
            continue
        rows.append(r)
        if r["ok"] and r["free"] is not None:
            dist.append(r["free"])
    good = sum(1 for r in rows if r["ok"])
    print(f"\ncalibration: {good} of {len(rows)} levered bodies MATCH their regenerated target"
          + (f" · lever-free distance min {min(dist)} / median {sorted(dist)[len(dist) // 2]} / max {max(dist)} "
             f"over {len(dist)} exemplars" if dist else ""))
    (RUN / "calibration.json").write_text(json.dumps(
        [dict(tu=e["tu"], fn=e["fn"], alias=e["alias"], ok=r["ok"], levered=r["levered"], free=r["free"],
              levered_line=r["levered_line"], free_line=r["free_line"])
         for e, r in zip(ex, rows)], indent=1))
    return 0 if good == len(rows) and rows else 1


def cmd_status(a):
    outs = load_outcomes()
    att = [o for o in outs if o.get("kind") == "attempt"]
    bk = [o for o in outs if o.get("kind") == "bank"]
    left = exemplars()
    v = collections.Counter(o.get("verdict") for o in att)
    print(f"delever_permute --status: {len(att)} attempts {dict(v)} · {sum(1 for b in bk if b.get('applied'))} banked of "
          f"{len(bk)} tried · {len(left)} residue classes not yet attempted "
          f"({sum(e['copies'] for e in left):,} bodies)")
    for o in att:
        if o.get("verdict") == "MATCH":
            print(f"  MATCH {o['alias']}__{o['fn']} ({o['copies']} copies, best={o.get('best')}, {o.get('seconds')}s)")
    return 0


FIX_TU = """#include "common.h"
extern s32 D_800A0000;
s32 helper_one(s32 a0)
{
    return a0 + D_800A0000;
}
INCLUDE_ASM("asm/x/nonmatchings/x", func_dead);
s32 target_fn(s32 a0, s32 *a1)
{
    register s32 s __asm__("$16") = a0;
    __asm__ __volatile__("" ::: "memory");
    *a1 = helper_one(s);
    return s;
}
static void tail(void) { }
"""


def cmd_selftest(a):
    ok = True
    d = REPO / ".run" / "P36" / "permuter" / "_selftest"
    if d.exists():
        shutil.rmtree(d)
    d.mkdir(parents=True)
    tu = "src/selftest/fix.c"
    sites = [dict(tu=tu, fn="target_fn", cls="A", kind="pin", detail="$16", via="", line=10, col=5,
                  fn_line=9, fn_end=15, zero=False),
             dict(tu=tu, fn="target_fn", cls="B", kind="barrier", detail="", via="", line=11, col=5,
                  fn_line=9, fn_end=15, zero=False)]
    free = lever_free_text(tu, FIX_TU, "target_fn", sites)
    if "__asm__" in free or "register" in free:
        print(f"selftest: the lever-free text still carries a lever:\n{free}")
        ok = False
    iso = isolate(tu, free, "target_fn")
    if "helper_one(s32 a0);" not in " ".join(iso.split()):
        print(f"selftest: helper_one was not reduced to a prototype:\n{iso}")
        ok = False
    if "INCLUDE_ASM" in iso:
        print("selftest: the INCLUDE_ASM line survived isolation")
        ok = False
    if iso.count("{") != 1:
        print(f"selftest: {iso.count('{')} bodies left in the isolated TU (want 1)")
        ok = False
    if "static void tail(void);" not in " ".join(iso.split()):
        print("selftest: a static definition lost its `static` (or its prototype)")
        ok = False
    if klass_for(["pin"]) != "regalloc" or klass_for(["barrier", "launder"]) != "schedule" \
            or klass_for(["pin", "barrier"]) != "regalloc" or klass_for([]) != "regalloc":
        print("selftest: klass_for is wrong")
        ok = False
    base = p16.make_base_c(iso)
    if not p16.defines_fn(base, "target_fn"):
        print("selftest: base.c lost target_fn")
        ok = False
    shutil.rmtree(d)
    print(f"delever_permute --selftest: {'OK' if ok else 'FAILED'} — lever-free + isolation + prototypes + klass + base.c")
    return 0 if ok else 1


def main():
    ap = argparse.ArgumentParser()
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--plan", action="store_true")
    g.add_argument("--prepare", nargs=2, metavar=("TU", "FN"))
    g.add_argument("--positive-control", nargs=2, metavar=("TU", "FN"),
                   help="perturb a MATCHING body by one commutative swap and require the permuter to find its way back")
    g.add_argument("--calibrate", action="store_true",
                   help="the control: N exemplars' levered bodies must all be MATCH against their regenerated targets")
    g.add_argument("--run", action="store_true")
    g.add_argument("--bank", action="store_true")
    g.add_argument("--status", action="store_true")
    g.add_argument("--selftest", action="store_true")
    ap.add_argument("--only", nargs="*", default=[], help="fn, TU (substring), alias or nhash prefix")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--show", type=int, default=25)
    ap.add_argument("--workers", type=int, default=4)
    ap.add_argument("--secs", type=int, default=240)
    ap.add_argument("--cycles", type=int, default=3)
    ap.add_argument("-j", type=int, default=16)
    ap.add_argument("--label", default="d1")
    ap.add_argument("--dirty-ok", action="store_true")
    ap.add_argument("--which", type=int, default=0, help="--positive-control: which commutative swap to perturb with")
    ap.add_argument("--max-start", type=int,
                    help="skip (as FAR) an exemplar whose lever-free body is further than N instructions from the target")
    ap.add_argument("--include-done", action="store_true", help="draw classes that already have an outcome row")
    a = ap.parse_args()
    os.chdir(REPO)
    RUN.mkdir(parents=True, exist_ok=True)
    if a.selftest:
        return cmd_selftest(a)
    if a.plan:
        return cmd_plan(a)
    if a.status:
        return cmd_status(a)
    if a.prepare:
        tu, fn = a.prepare
        ex = next((e for e in exemplars(include_done=True) if e["tu"] == tu and e["fn"] == fn), None)
        if ex is None:
            ex = dict(nhash="", tu=tu, fn=fn, alias=None, copies=1, needed=0, kinds=[], members=[], row={})
        d, draft, tgt, klass = prepare(ex)
        print(f"delever_permute --prepare: {d.relative_to(REPO)} (draft.c, {tgt.name}, klass={klass})")
        return 0
    if a.positive_control:
        return positive_control(a)
    if a.calibrate:
        return cmd_calibrate(a)
    if a.run:
        return cmd_run(a)
    if a.bank:
        return bank(a)


if __name__ == "__main__":
    sys.exit(main())
