#!/usr/bin/env python3
"""dedup_propagate.py — match once, share many across the overlay fleet (Phase 15, cookbook §14).

The overlay fleet is position-locked at vram 0x80128158, so a shared engine function has the
SAME vaddr (hence the same `func_<ADDR>` symbol) and BYTE-IDENTICAL body in every overlay that
contains it. This tool takes a function already matched in ONE overlay and propagates that single
matched C body to every onboarded overlay whose signature shows the same `h_exact` at that addr:

  1. extract the matched body from the source overlay's .c  (externs + the function def)
  2. author it ONCE as a `DEFINE_func_<ADDR>()` macro in src/shared/<header>.h  (idempotent)
  3. at each member overlay, replace that function's INCLUDE_ASM stub (or, in the source overlay,
     its inline def) in place with `DEFINE_func_<ADDR>()` — address order preserved
  4. BYTE-GATE every touched overlay (`make build BINARY=<ov>` == its check.sha); on ANY miss,
     restore every file from an in-memory snapshot and abort (fail-closed; nothing wrong can land)
  5. register the group in config/dedup.us.yaml (the byte-honesty registry, validated by
     tools/dedup_integrate.py --check)

Everything is keyed by the integer address: the sig uses lowercase hex ("0x80144b9c"), splat emits
the uppercase symbol ("func_80144B9C") — never compare the strings, always the int.

Lead with h_exact (guaranteed byte-identity). The per-overlay `make check` is the sole arbiter
(G3/P9): a wrong propagation cannot pass it.

Usage:
  tools/dedup_propagate.py --addr 0x8013xxxx[,0x...] [--source-overlay ov_SC01_077]
  tools/dedup_propagate.py --auto-from ov_SC01_077 [--min-reach 2] [--limit N]
  tools/dedup_propagate.py ... --check-only         # dry run: print the plan, touch nothing
Options:
  --header src/shared/engine_core.h   target cluster header (created/appended)
  --tier h_exact|h_norm               default h_exact (h_norm requires the byte-gate to pass on ALL)
  --binaries a,b,c                    restrict members to these onboarded overlays (default: all that share)
  --no-gate                           skip the per-overlay build gate (CI / batch re-gate later)
"""
import argparse, collections, functools, json, pathlib, re, subprocess, sys
import os as _os
import threading as _threading
sys.path.insert(0, _os.path.dirname(_os.path.abspath(__file__)))
import cdecl    # the comment/string masking oracle (Phase 26-A) — see _skippable below
import shared_lock  # Stage 1: fleet-shared RW lock — propagation is an EXCLUSIVE writer

ROOT = pathlib.Path(__file__).resolve().parent.parent


# ---------------------------------------------------------------- fleet / sig helpers
def onboarded_overlays():
    """Overlay aliases + (S44) module aliases — every non-main/resident binary a shared body can
    propagate into. Modules carry engine functions too; excluding them re-creates the SC07
    invisible-work bug one class over."""
    out = []
    for f, var in (("config/overlays.mk", "OVERLAY_BINARIES"), ("config/modules.mk", "MODULE_BINARIES")):
        fp = ROOT / f
        if fp.exists():
            m = re.search(rf"^{var}\s*:=\s*(.*)$", fp.read_text(), re.M)
            if m:
                out += m.group(1).split()
    return out


def sig_path(ov):
    return ROOT / f".run/sig.{ov}.jsonl"


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
    p = ROOT / "config/dedup.us.yaml"
    if not p.exists():
        return set()
    try:
        import yaml
        sys.path.insert(0, str(ROOT / "tools"))
        from dedup_integrate import group_members
        data = yaml.safe_load(p.read_text()) or {}
        return {v for g in (data.get("groups") or []) for (_b, v, _n) in group_members(g)}
    except Exception:
        return set()


def sym(addr):
    return f"func_{addr:08X}"  # splat convention: uppercase 8-hex


def c_path(ov):
    return ROOT / f"src/{ov}/{ov}.c"


def overlay_files(ov):
    """[(path, asm_subdir)] for ov's source file(s): the main .c plus any Phase-19 split files
    (ov_SC01_077_a.c / _o0.c). Single-file overlays return just the main .c — default behaviour
    preserved. Lets a fn matched in a split file propagate ×reach (its stub/def lives in _a/_o0)."""
    # DERIVED from the tree — a GLOB, never an allowlist (Phase 26-A audit, HIGH).
    #
    # This was a hardcoded suffix list ("_a","_o0","_o0b","_after") that predated the Phase-26 jr
    # carves, so it returned 404 of the fleet's 811 overlay .c. The 407-file gap held **36,135
    # INCLUDE_ASM stubs and ~32,000 inline defs — half the corpus** — and overlay_files gates ALL of
    # dedup_propagate (source_text / find_site / apply_plan / struct_check / reconcile_caller_extern).
    # 435 of ov_SC01_077's 689 inline defs were invisible to --auto-from.
    #
    # It is also WHY the 4 functions in .run/audit/a1_harvest_fuel.json were never propagated: three
    # of them are defined in ov_SC01_077_jr_8012ACE0.c, which this list could not see. The dedup group
    # was registered anyway and dedup_integrate greenlit the lie (A1). Two silent-skip bugs compounding.
    #
    # Do NOT "fix" this by adding _jr_* to the tuple: the NEXT split family would re-open the hole.
    # The asm_subdir is always the file stem — an invariant the four old entries already satisfied.
    out = [(c_path(ov), ov)]
    for p in sorted(ROOT.glob(f"src/{ov}/{ov}_*.c")):
        out.append((p, p.stem))
    return out


def source_text(ov):
    """Concatenation of all of ov's split files — for SOURCE-side def finding + body extraction
    only (find_site uses the body lines, so cross-file concat is safe; never used to EDIT)."""
    return "\n".join(p.read_text() for p, _ in overlay_files(ov))


def stub_line(ov, addr):
    return f'INCLUDE_ASM("asm/{ov}/nonmatchings/{ov}", {sym(addr)});'


# ---------------------------------------------------------------- body extraction
@functools.lru_cache(maxsize=8)
def _split_masked(text):
    """(lines, mlines) for one source text — MEMOIZED, because it does not depend on the address.

    THE WHOLE COST OF THIS TOOL WAS HERE (P31 S75, measured). `find_site` re-ran `cdecl._mask`
    (four regex passes, one with `re.S`) plus two `splitlines()` over the ENTIRE concatenated
    source on EVERY call, and the caller loops over every function in the binary. On
    `ov_SC01_005` (2.50 MB of source, 2,503 functions in the sig):

        splitlines(text)          6.5 ms
        cdecl._mask(text)        38.9 ms     <- 4 regex passes, one re.S
        splitlines(mask)          4.6 ms
        ------------------------------- 54 ms PER CALL, before a single line is searched

    and `find_site` is called per-address in the `--auto-from` enumeration, again per-target while
    building the plan, and again during propagation. Observed: **29m38s of CPU on ONE core**
    (`nlwp=1` — the `ThreadPoolExecutor` below covers only the cpp/cc1 probe, not this), ~92% CPU,
    no subprocesses, no writes. The mask is a pure function of the text, so every call after the
    first recomputed an identical result: the shape was O(functions x source-bytes) where it should
    be O(source-bytes + functions).

    `lru_cache` is the right primitive here rather than a hand-rolled dict: callers already hold one
    `txt_cache`/`ctext` string OBJECT per binary and pass it repeatedly, and CPython caches a str's
    hash on the object, so a repeat lookup is a pointer compare. maxsize=8 covers source + members
    in flight without pinning many megabytes.

    NB this is the SECOND half of this phase's cost to be fixed; the comment on the cc probe below
    records the first ("~5 minutes pegged at one core on a 32-core box"). Fixing the subprocess half
    left the regex half as the dominant term."""
    lines = text.splitlines()
    # Comments blanked ONCE by the project's single masking oracle (R33). Length-preserving, so
    # index i into mlines is index i into lines. This is what makes _skippable MULTI-LINE aware.
    mlines = cdecl._mask(text).splitlines()
    if len(mlines) != len(lines):        # R32: the invariant this rests on, asserted not assumed
        mlines = lines
    return lines, mlines


def find_site(text, ov, addr):
    """Locate this function in ov's .c. Returns (kind, start, end, body_lines):
       kind 'stub'   -> the INCLUDE_ASM line (start==end, body_lines None)
       kind 'def'    -> an inline definition block (preceding contiguous externs .. closing brace)
       kind 'macro'  -> already a DEFINE_func_<ADDR>() instantiation (already propagated)
       None          -> not present / matched in some other form."""
    lines, mlines = _split_masked(text)
    s = sym(addr)
    stub = stub_line(ov, addr)
    for i, l in enumerate(lines):
        if l.strip() == stub:
            return ("stub", i, i, None)
    for i, l in enumerate(lines):
        if l.strip() == f"DEFINE_{s}()" or l.strip().startswith(f"DEFINE_{s}()"):
            return ("macro", i, i, None)
    # inline definition: "<type> func_XXXX(...)" at column 0 OR indented (recover_integration/harvest
    # write the def block indented -> a column-0-only match silently dropped every indented def from
    # propagation, T6 blocker 1), brace on the SAME or the NEXT line (drafts vary the brace placement).
    # SAFE against indented CALL-exprs: the pattern requires a TYPE prefix ([A-Za-z_][\w \*]*, which
    # admits neither '(' nor '=') before the name AND the whole line to BE the signature (ends ')' or
    # '){'), so `if (func_X(...)) {`, `x = func_X(...);`, and a bare `func_X(a);` call never match.
    # The signature HEAD. Anchored on a type prefix ([A-Za-z_][\w \*]*, which admits neither '(' nor
    # '=') followed by the name and an open paren — so `if (func_X(...))`, `x = func_X(...);` and a
    # bare `func_X(a);` call can never match. Deliberately NOT anchored on the line ENDING in ')':
    # that anchor silently dropped every MULTI-LINE signature (Phase 26-A audit).
    # S33: a function defined under the §37/§73 ASM-LABEL ALIAS is named `aF<ADDR>` in C and only
    # BINDS the real symbol via `__asm__("func_<ADDR>")`. A head regex anchored on the literal
    # `func_<ADDR>` is structurally blind to it, so find_site returned None and every caller read
    # "not matched" — func_801466F0 (137 members / 3,288 ins) sat unreachable behind exactly this.
    # family_remap._alias_decl_for already resolves the form (and, since S33, its WRAPPED variant);
    # reuse it rather than write a second matcher (R33 — one oracle).
    names = [s]
    try:
        import family_remap as _FR
        _alias, _ = _FR._alias_decl_for(lines, addr)
        if _alias and _alias.lower() != s.lower():
            names.append(_alias)
    except Exception:
        pass
    defhead = re.compile(r"^\s*[A-Za-z_][\w \*]*\b(?:" + "|".join(re.escape(n) for n in names) + r")\s*\(")
    # A K&R parameter declaration, e.g. `s32 arg0;` / `struct S *p[4];`
    kr_param = re.compile(r"^\s*[A-Za-z_][\w \t\*]*\b\w+\s*(\[[^\]]*\])?\s*;\s*$")
    for i, l in enumerate(lines):
        m = defhead.match(l)
        if not m:
            continue
        # Walk from the '(' that opens the parameter list to ITS matching ')', character by character
        # and across lines. Do NOT use line.count('(')-count(')') or split(')')[-1]: a single-line body
        # containing a call (`void f(int a) { g(a); }`) has balanced parens of its own, so both
        # shortcuts land on the WRONG paren and then misread the body's `;` as a prototype terminator.
        depth, li, ci = 0, i, m.end() - 1
        while li < len(lines):
            line = lines[li]
            while ci < len(line):
                if line[ci] == "(":
                    depth += 1
                elif line[ci] == ")":
                    depth -= 1
                    if depth == 0:
                        break
                ci += 1
            if depth == 0 and ci < len(lines[li]):
                break
            li += 1
            ci = 0
        if li >= len(lines):
            continue
        close = li                      # the line on which the parameter list closes
        rest = lines[close][ci + 1:]    # everything AFTER the signature's own ')'
        if rest.lstrip().startswith(";"):
            continue                    # `... );`  -> a PROTOTYPE, not a definition
        tail = rest
        # locate the body's opening brace. It is on the closing line, OR on a following line — and in
        # a K&R definition the PARAMETER DECLARATIONS sit between ')' and '{'. The old code demanded
        # the next non-blank line start with '{', so it silently dropped EVERY K&R definition — which
        # is the project's house style for exactly the biggest, highest-reach functions (func_8015AE2C
        # 562 ins, func_80166994, func_80133CD4, func_8015A3C8). Those live in the _jr_* files this
        # function could not even open until the overlay_files glob above; fixing one without the other
        # would have exposed the files and still dropped their biggest prizes.
        if "{" in tail:
            bstart = close             # single-line body / brace on the signature line
        else:
            k = close + 1
            while k < len(lines) and (lines[k].strip() == "" or kr_param.match(lines[k])):
                k += 1                 # skip blanks AND K&R parameter declarations
            if k >= len(lines) or "{" not in lines[k]:
                continue               # no body -> a prototype
            bstart = k
        if True:
            # brace-match forward to the closing '}'
            depth = 0
            end = None
            for j in range(bstart, len(lines)):
                depth += lines[j].count("{") - lines[j].count("}")
                if depth <= 0:
                    end = j
                    break
            if end is None:
                return None
            # collect contiguous preceding extern declarations (skip blank lines). A trailing
            # `/* comment */` after the ; is allowed (a banked extern block often annotates a decl,
            # e.g. `extern u8 D_x[];   /* canonical TU type */` — a comment-blind `;\s*$` stopped the
            # scan there and dropped every EARLIER extern, failing compiles_standalone on the now-
            # undeclared callees/data; T6.4 fix for func_8014E048's pin/asm body).
            # SESSION-18: the walk skipped BLANK lines but not STANDALONE COMMENT lines, so a
            # full-line `/* ---- */` between two extern groups halted it and silently dropped every
            # extern ABOVE the comment. That is the whole "CARRY-FIXABLE" class: the body then fails
            # compiles_standalone on now-undeclared data/callees, and the caller filed it under
            # "overlay-local TYPE (the real cap)" — a mislabel that wrote the class off for ~4 phases.
            # (T6.4 had already fixed the TRAILING-comment case, `extern u8 D_x[]; /* note */`; this
            # is the standalone-LINE case it did not reach.) Skip comment-only lines exactly like
            # blanks, and drop them from the emitted body so make_macro never sees a `//`.
            # S11: the SESSION-18 fix handled BLANK, `//`, and SINGLE-LINE `/* … */` lines, but a
            # MULTI-LINE block comment still halted the walk — its middle lines start with `*` and
            # its last line ends `*/` without starting `/*`. That is the §134 multi-line-blindness
            # class (S6b fixed the same shape three times in family_remap). Deciding on the MASK
            # instead of on line syntax subsumes every comment form in one oracle and cannot be
            # fooled by a `/*` inside a string. Byte-measured: this is the whole CARRY-FIXABLE
            # bucket for func_8012A598 (3,288 templatable ins that were being written off).
            def _skippable(idx):
                return mlines[idx].strip() == ""
            start = i
            k = i - 1
            while k >= 0 and _skippable(k):
                k -= 1
            while k >= 0 and re.match(r"^\s*extern\b.*;\s*(/\*.*\*/\s*)?$", lines[k]):
                start = k
                k -= 1
                while k >= 0 and _skippable(k):
                    k -= 1
            body = [lines[j] for j in range(start, end + 1) if not _skippable(j)]
            return ("def", start, end, body)
    return None


def make_macro(addr, body_lines):
    """Turn an extracted body (externs + def) into a `#define DEFINE_func_<ADDR>() \\`-continued macro.
       Fails loud on constructs that don't survive line-continuation (// comments, trailing backslash)."""
    s = sym(addr)
    for ln in body_lines:
        if "//" in ln:
            raise SystemExit(f"[refuse] {s}: body has a // comment — not macro-safe (handle manually)")
        if ln.rstrip().endswith("\\"):
            raise SystemExit(f"[refuse] {s}: body line ends with backslash — not macro-safe")
    out = [f"#define DEFINE_{s}() \\"]
    for idx, ln in enumerate(body_lines):
        cont = " \\" if idx < len(body_lines) - 1 else ""
        out.append("    " + ln.rstrip() + cont)
    return "\n".join(out) + "\n"


# ---------------------------------------------------------------- file edits (in memory)
INCLUDE_RE = re.compile(r'^#include\s+"\.\./shared/')


def ensure_include(text, header):
    rel = f'#include "../shared/{pathlib.Path(header).name}"'
    if rel in text:
        return text
    lines = text.splitlines(keepends=True)
    for i, l in enumerate(lines):
        if l.strip() == '#include "common.h"':
            lines.insert(i + 1, rel + "\n")
            return "".join(lines)
    return rel + "\n" + text  # fallback: prepend


def replace_site(text, ov, addr, kind, start, end):
    lines = text.splitlines(keepends=True)
    repl = f"DEFINE_{sym(addr)}()  /* dedup: shared engine-core @0x{addr:08X} (src/shared) */\n"
    lines[start:end + 1] = [repl]
    return "".join(lines)


# ---------------------------------------------------------------- dedup.us.yaml registration
def append_groups(groups):
    """Append new groups textually (preserve the file's header comments). Idempotent by id."""
    path = ROOT / "config/dedup.us.yaml"
    text = path.read_text()
    blocks = []
    for g in groups:
        if re.search(rf"^\s*-\s*id:\s*{re.escape(g['id'])}\s*$", text, re.M):
            continue  # already present
        # position-locked share -> compact shorthand (vram + binaries list), ~20x smaller than verbose
        # members for fleet-wide groups; group_members() in dedup_integrate expands it.
        bins = ", ".join(m["binary"] for m in g["members"])
        blocks.append(
            f"  - id: {g['id']}\n"
            f"    tier: {g['tier']}\n"
            f"    hash: {g['hash']}\n"
            f"    source: {g['source']}\n"
            f"    func: DEFINE_{sym(g['addr'])}\n"
            f"    vram: 0x{g['addr']:08X}\n"
            f"    binaries: [{bins}]")
    if not blocks:
        return 0
    if not text.endswith("\n"):
        text += "\n"
    path.write_text(text + "\n".join(blocks) + "\n")
    return len(blocks)


_BJOBS = int(_os.environ.get('BFM_BUILD_JOBS') or (_os.cpu_count() or 8))


# ---------------------------------------------------------------- byte gate
def byte_gate(ov):
    # -j — see harvest_verify's note: ~6x on a per-binary build, and this gate runs once per
    # propagation candidate, which is why a wide propagation dominated a 33-minute gate in P31 S67.
    r = subprocess.run(["make", "-j%d" % _BJOBS, "build", f"BINARY={ov}"], cwd=ROOT,
                       capture_output=True, text=True)
    return r.returncode == 0, r.stdout + r.stderr


def _jobs():
    """Parallel overlay gates. Env JOBS wins; otherwise use EVERY core.

    Deliberately NOT capped at the Makefile's conservative `JOBS ?= 16` default: each worker is a
    `make build` that spends nearly all its wall-clock in cc1/as/ld subprocesses, so the box is the
    limit, not Python. Measured 2026-08-07: the serial version ran a propagation for 95 minutes at
    load 1.6 on a 32-core machine — ~5% utilisation. Saturate it (Drew, same session).
    """
    try:
        j = int(_os.environ.get("JOBS", "0"))
    except ValueError:
        j = 0
    return max(1, j or (_os.cpu_count() or 4))


_SRC_BYTES = {}


def _src_bytes(ov):
    """Total bytes of an overlay's C sources — the build-cost proxy for longest-first scheduling.

    Cheap and good enough: `make build BINARY=<ov>` spends nearly all its time in cc1 on those
    files, so source size ranks the giants (ov_SC01_077 & co) to the front of the queue."""
    if ov not in _SRC_BYTES:
        try:
            _SRC_BYTES[ov] = sum(p.stat().st_size for p, _ in overlay_files(ov) if p.exists())
        except OSError:
            _SRC_BYTES[ov] = 0
    return _SRC_BYTES[ov]


def gate_all(changed, label=""):
    """Byte-gate every touched overlay in parallel; return the FIRST failure (compat wrapper)."""
    f = gate_failures(changed, label)
    return f[0] if f else None


def gate_failures(changed, label=""):
    """Byte-gate EVERY touched overlay in parallel; return ALL failures in `changed` ORDER.

    The sweep already builds every overlay and already knows every verdict — returning only the
    first threw ~26 of 27 answers away, and the recovery loop then paid a FULL sweep to rediscover
    each one (S45: the same two functions were excluded from 27 overlays, one sweep apiece). Same
    builds, same determinism, all the information.

    WHY (measured 2026-08-07): this loop used to be serial — one `make build BINARY=<ov>` at a
    time, over up to 141 members, for each of ~30 functions. A propagation ran 95 minutes at load
    1.6 on a 32-core box: ~5% utilisation. The Makefile has parallelised `extract-all`/`check-all`
    since Phase 26 (`xargs -P$(JOBS)`), but dedup_propagate predates that and drives the
    SINGLE-binary `build` target from Python, so it never saw any of it.

    SAFE for the same reason `check-all` is: byte_gate only runs `make build BINARY=<ov>`, which
    writes solely to the per-binary-disjoint `build/<bin>/**`; it mutates NO source. The splice has
    already happened before this is called, and the restore happens after — only the *verification*
    is parallel. Threads, not processes: subprocess.run releases the GIL while the build runs.

    DETERMINISM: ThreadPoolExecutor.map preserves input order, so the reported first failure is the
    first in `changed` order — identical to the serial loop's verdict, not whichever build finished
    first. The serial version short-circuited on the first failure and so did fewer builds; this
    does them all, but in parallel, and the all-pass case (the common one) is a straight win.
    """
    order = list(changed)
    if not order:
        return []
    j = min(_jobs(), len(order))
    if j <= 1:
        return [ov for ov in order if not byte_gate(ov)[0]]
    from concurrent.futures import ThreadPoolExecutor
    print(f"[gate] byte-gating {len(order)} overlay(s) with {j} parallel builds{label}", flush=True)
    # LONGEST-FIRST (LPT). ThreadPoolExecutor.map starts work in list order, and the giant overlays
    # (ov_SC01_077 & co — 15k lines at -O2) sit late in it, so every sweep ended with 31 cores
    # watching ONE build: measured 31 s saturated then ~25 s of a single cc1. Starting the big ones
    # first overlaps that tail with the crowd. Execution order only — results are re-sorted into
    # `changed` order below, so the reported verdict is bit-for-bit the same as the serial loop's.
    sched = sorted(order, key=lambda ov: -_src_bytes(ov))
    with ThreadPoolExecutor(max_workers=j) as ex:
        results = dict(ex.map(lambda o: (o, byte_gate(o)[0]), sched))
    return [ov for ov in order if not results[ov]]


# ---------------------------------------------------------------- straggler caller-extern reconcile (--recover)
def reconcile_caller_extern(ov, addr):
    """no-proto every conflicting `extern <ret> func_<ADDR>(<params>);` caller decl in ov's src files
    (main + _a/_o0 splits), keeping the return type, dropping the params. A member overlay that
    forward-declares the banked fn with a prototype INCOMPATIBLE with the def (`extern void
    func_X(s32,s32,s32);` vs the def's (s32,s32,u32)) makes its TU fail `conflicting types` once the
    macro def lands. No-proto'ing that decl is byte-NEUTRAL (the call `func_X(a,b,c)` emits identical
    code; a K&R decl is compatible with any promotion-safe def) and lets the def compile — the same
    lever as tools/fix_arity_callers.py --any-proto, applied surgically to the failing overlay. The
    whole-binary byte-gate stays the sole arbiter (G3/P9). Returns (snapshot, n_edits); the snapshot
    restores the files VERBATIM (fix_arity_callers --revert is LOSSY for non-(void) forms)."""
    rx = re.compile(rf'(extern\s+[A-Za-z_][\w \t\*]*?\b{sym(addr)}\s*\()\s*[^;)]+?\s*(\)\s*;)', re.I)
    snap, n = {}, 0
    for cp, _ in overlay_files(ov):
        txt = cp.read_text()
        snap[cp] = txt
        new, k = rx.subn(r"\1\2", txt)
        if k:
            cp.write_text(new)
            n += k
    return snap, n


def restore_snapshot(snap):
    for cp, txt in snap.items():
        cp.write_text(txt)


CC1 = ROOT / "tools/bin/gcc-2.7.2-psx/cc1"

def compiles_standalone(body_lines):
    """True iff the lifted body compiles with ONLY common.h (cpp -> cc1). A body that uses overlay-
    LOCAL struct types (named in the SOURCE overlay's .c but not common.h) compiles in the source yet
    FAILS in every other overlay — it cannot be mechanically lifted. Pre-filtering on this avoids an
    all-or-nothing byte-gate revert and lets us report the non-liftable count honestly (P9)."""
    # include the shared engine types so struct-USING bodies (that reference header types like
    # `struct Vec`) resolve; a body using an overlay-local typedef not in the header still fails -> skip.
    src = ('#include "common.h"\n#include "engine_types.h"\n'
           + "\n".join(body_lines) + "\n")
    d = ROOT / ".run/dpcc"; d.mkdir(parents=True, exist_ok=True)
    # UNIQUE per call: this used to be a fixed `t.c`, so two concurrent probes would compile each
    # other's body — the same fake-isolation class as match_one's shared --work dir (P28 T5). The
    # plan phase now runs these in parallel, so the shared path is a correctness bug, not a style one.
    f = d / f"t.{_os.getpid()}.{_threading.get_ident()}.c"; f.write_text(src)
    cpp = subprocess.run(["mipsel-linux-gnu-cpp", "-lang-c", f"-I{ROOT}/include",
                          f"-I{ROOT}/src/shared", "-undef",
                          "-fno-builtin", "-Dmips", "-D__GNUC__=2", "-D__OPTIMIZE__", "-Dpsx",
                          "-D_PSYQ", "-D_MIPSEL", "-D_LANGUAGE_C", str(f)], capture_output=True, text=True)
    if cpp.returncode != 0:
        return False, (cpp.stderr or "cpp failed")
    cc1 = subprocess.run([str(CC1), "-quiet", "-O2", "-G0", "-mips1", "-mcpu=3000", "-mgas",
                          "-msoft-float", "-fgnu-linker", "-o", "/dev/null"],
                         input=cpp.stdout, capture_output=True, text=True)
    return cc1.returncode == 0, (cc1.stderr or "")



MACRO_RE = re.compile(r'^\s*DEFINE_func_([0-9A-Fa-f]+)\(\)')


def place_in_overlay(ov, subplan, header_rel, edit):
    """Instantiate each subplan fn's DEFINE_ macro at its site in ONE overlay, via the `edit`
    callback (path, newtext). Returns (placed_anything, [unresolved addrs]).

    Module-level ON PURPOSE: the per-overlay search runs in a PROCESS pool (the work is regex over
    15k-line files, which threads cannot parallelise — measured: 138 "parallel" thread searches kept
    0-4 builds alive because they all serialised on the GIL). A process pool needs a picklable
    top-level entry point, and both the in-process apply and the workers must use the SAME placement
    logic or they will drift (R33)."""
    remaining = {p["addr"]: p for p in subplan}
    ovc = False
    for cp, asm_sub in overlay_files(ov):           # main + Phase-19 split files (_a/_o0)
        if not remaining:
            break
        lines = ensure_include(cp.read_text(), header_rel).splitlines(keepends=True)
        sp = re.compile(rf'^\s*INCLUDE_ASM\("asm/{re.escape(ov)}/nonmatchings/{re.escape(asm_sub)}",\s*func_([0-9A-Fa-f]+)\);\s*$')
        stub_idx, macro_set = {}, set()
        for i, l in enumerate(lines):
            ms = sp.match(l)
            if ms: stub_idx[int(ms.group(1), 16)] = i; continue
            mm = MACRO_RE.match(l)
            if mm: macro_set.add(int(mm.group(1), 16))
        joined = "".join(lines)
        line_repls, def_ranges = {}, []
        for ad in list(remaining):
            if ad in macro_set:
                del remaining[ad]; continue            # already instantiated in this file (idempotent)
            repl = f"DEFINE_{sym(ad)}()  /* dedup: shared engine-core @0x{ad:08X} (src/shared) */\n"
            if ad in stub_idx:
                line_repls[stub_idx[ad]] = repl; del remaining[ad]; ovc = True
            else:
                site = find_site(joined, ov, ad)   # inline def in THIS file? (else the next split file)
                if site and site[0] == "def":
                    def_ranges.append((site[1], site[2], repl)); del remaining[ad]; ovc = True
                elif site and site[0] == "stub":
                    # A stub whose INCLUDE_ASM asm-subdir != this file's stem: the `sp` regex anchors
                    # on the stem and is structurally blind to it, and acting only on 'def' silently
                    # skipped the site. find_site's stub match is an EXACT stub_line(ov, addr) compare
                    # against THIS file's text, so placing here cannot cross files or TUs.
                    line_repls[site[1]] = repl; del remaining[ad]; ovc = True
                elif site and site[0] == "macro":
                    del remaining[ad]              # already instantiated (path-mismatch variant)
        if line_repls or def_ranges:
            for idx, repl in line_repls.items():
                lines[idx] = repl
            for start, end, repl in sorted(def_ranges, key=lambda x: -x[0]):
                lines[start:end + 1] = [repl]
            edit(cp, "".join(lines))
    return ovc, sorted(remaining)


def _probe_overlay(ov, plan, header_rel, excl):
    """Apply plan-minus-`excl` to ONE overlay, byte-gate it, restore. True iff byte-identical."""
    journal = {}

    def edit(path, newtext):
        if path not in journal:
            journal[path] = path.read_text() if path.exists() else None
        path.write_text(newtext)

    placed, _rem = place_in_overlay(
        ov, [p for p in plan if p["addr"] not in excl and ov in p["members"]], header_rel, edit)
    try:
        return byte_gate(ov)[0] if placed else True
    finally:
        for path, orig in journal.items():
            if orig is None:
                path.unlink(missing_ok=True)
            else:
                path.write_text(orig)


def search_worker(job):
    """The minimal exclusion set that makes ONE overlay byte-identical. Runs in its own PROCESS:
    an overlay owns its .c files and its build/<bin>/ dir, and the shared header is written once by
    the parent and never touched here — so these are genuinely independent."""
    ov, plan, header_rel, suspects = job
    cands = [p for p in plan if ov in p["members"]]
    sus_here = [p for p in cands if p["addr"] in suspects]

    def probe(excl):
        return _probe_overlay(ov, plan, header_rel, excl)

    # FAST PATH: the same 1-2 functions break every overlay, so try the known culprits first. When it
    # hits (the common case) this overlay costs 1 + |suspects| builds instead of a full bisection.
    excl = None
    if sus_here and probe({p["addr"] for p in sus_here}):
        excl = sus_here
    if excl is None:
        order = sus_here + [p for p in cands if p["addr"] not in suspects]
        if not probe({p["addr"] for p in order}):
            return ov, None                      # diverges even with everything excluded
        lo, hi = 0, len(order)
        while lo < hi:                           # shortest sufficient PREFIX
            mid = (lo + hi) // 2
            if probe({p["addr"] for p in order[:mid]}):
                hi = mid
            else:
                lo = mid + 1
        excl = order[:lo]
    # SHRINK: drop anything this overlay does not actually need, so the batch never over-excludes
    # and silently costs an overlay a member it could have kept.
    i = 0
    while i < len(excl):
        trial = excl[:i] + excl[i + 1:]
        if probe({p["addr"] for p in trial}):
            excl = trial
        else:
            i += 1
    return ov, sorted(p["addr"] for p in excl)


# ---------------------------------------------------------------- main
def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--addr", help="comma-separated target vaddrs (hex)")
    ap.add_argument("--auto-from", help="propagate every matched+shared function of this overlay")
    ap.add_argument("--source-overlay", help="overlay to extract the matched body from (default: auto)")
    ap.add_argument("--min-reach", type=int, default=2, help="min #overlays sharing (auto mode; default 2)")
    ap.add_argument("--limit", type=int, default=0, help="cap #functions (auto mode; 0 = no cap)")
    ap.add_argument("--header", default="src/shared/engine_core.h")
    ap.add_argument("--tier", default="h_exact", choices=("h_exact", "h_norm"))
    ap.add_argument("--binaries", help="restrict members to these onboarded overlays (comma list)")
    ap.add_argument("--check-only", action="store_true", help="dry run: print the plan, touch nothing")
    ap.add_argument("--no-gate", action="store_true")
    ap.add_argument("--recover", action="store_true",
                    help="on a straggler byte-gate failure, FIRST no-proto that overlay's conflicting "
                         "caller extern for the fn and re-gate (Part B reconcile — byte-neutral, same "
                         "lever as fix_arity_callers --any-proto); if still failing, EXCLUDE only that "
                         "overlay from the fn's members (Part A, ×N-1) rather than dropping the fn from "
                         "ALL overlays (the historical all-or-nothing). Recovers T6 caller-decl stragglers.")
    a = ap.parse_args()

    onb = onboarded_overlays()
    restrict = set(a.binaries.split(",")) if a.binaries else None
    pool = [ov for ov in onb if (restrict is None or ov in restrict)]
    sigs = {ov: load_sig(ov) for ov in pool}

    # ---- choose target addresses + source overlay per target
    targets = []  # list of (addr, source_overlay)
    if a.auto_from:
        src = a.auto_from
        ssig = load_sig(src)
        ctext = source_text(src)   # scan main + split files for matched defs
        reg = registered_addrs()   # skip functions already shared (additive + resumable)
        # -O0 split-file functions are OVERLAY-LOCAL (§18/§20, cont.4): -O0 codegen embeds per-overlay
        # %lo data addresses, so their bytes diverge per overlay even though the relocation-MASKED
        # h_exact falsely reports reach-134. Cross-overlay-propagating one fails the byte-gate and,
        # under the all-or-nothing batch revert, poisons every CLEAN match in the batch (cont.4:
        # func_8013C360 reverted 10 good ×134 matches). Never auto-propagate them — detect by def-site
        # in the -O0 split file (*_o0.c). (--addr still forces them, for an explicit override.)
        o0_skip = set()
        for _p, _tag in overlay_files(src):
            if _p.name.endswith("_o0.c"):
                _o0txt = _p.read_text()
                for _ad in ssig:
                    _s = find_site(_o0txt, src, _ad)
                    if _s and _s[0] == "def":
                        o0_skip.add(_ad)
        for addr in sorted(ssig):
            if addr in reg or addr in o0_skip:
                continue
            site = find_site(ctext, src, addr)
            if not site or site[0] != "def":   # only functions matched (inline def) in the source
                continue
            h = ssig[addr].get(a.tier)
            reach = sum(1 for ov in pool if sigs[ov].get(addr, {}).get(a.tier) == h)
            if reach >= a.min_reach:
                targets.append((addr, src))
        targets.sort(key=lambda t: ssig[t[0]]["nins"])
        if a.limit:
            targets = targets[:a.limit]
    elif a.addr:
        for tok in a.addr.split(","):
            addr = int(tok, 16)
            src = a.source_overlay
            if not src:  # auto: an onboarded overlay where it is an inline def
                for ov in pool:
                    site = find_site(source_text(ov), ov, addr)
                    if site and site[0] == "def":
                        src = ov
                        break
            if not src:
                sys.exit(f"[error] 0x{addr:08X}: no source overlay has it matched — give --source-overlay")
            targets.append((addr, src))
    else:
        sys.exit("give --addr or --auto-from")

    # ---- build the per-target plan (members + body + hash). Cache the source sig/.c (one src in
    # auto-from). Filter out bodies that aren't self-contained (overlay-local types -> not liftable).
    plan = []
    cc_queue = []          # candidates awaiting the (parallelised) self-containment probe
    sig_cache, txt_cache = {}, {}
    n_nondef = n_local = n_lowreach = 0
    # R32: a skip that only increments a counter is invisible work — and `n_local` aggregates THREE
    # unrelated causes (macro-unsafe body / inline type def / genuinely overlay-local type), which
    # mislabels the queue: a body skipped for containing a `//` comment is a 1-line fix, not the
    # per-camp type reconcile. Track and NAME each class separately.
    skipped = collections.defaultdict(list)
    for addr, src in targets:
        ssig = sig_cache.setdefault(src, load_sig(src))
        if addr not in ssig:
            continue
        h = ssig[addr].get(a.tier)
        ctext = txt_cache.setdefault(src, source_text(src))
        site = find_site(ctext, src, addr)
        if not site or site[0] != "def":
            n_nondef += 1; skipped["not-inline-def"].append(addr); continue
        body = site[3]
        members = [ov for ov in pool if sigs[ov].get(addr, {}).get(a.tier) == h]
        if len(members) < 2:
            n_lowreach += 1; skipped["reach<2"].append(addr); continue
        if any("//" in l or l.rstrip().endswith("\\") for l in body):
            n_local += 1; skipped["macro-unsafe (// or \\)"].append(addr); continue
        # A body that inline-DEFINES a named struct/union or a typedef can't be lifted as a macro
        # (two macros defining the same type redefine it when both instantiate in one overlay). But
        # USING a type that lives in the shared src/shared/engine_types.h header (§14c struct follow-up)
        # is fine — the header is included via engine_core.h in every overlay. Anonymous local structs
        # (`struct {...} v;`, no name, no typedef) are unique per instantiation -> also fine. So skip
        # ONLY inline named-struct defs + typedefs; compiles_standalone (which includes engine_types.h)
        # then rejects any body using an overlay-local type NOT yet promoted to the header.
        if re.search(r'(\b(struct|union)\s+\w+\s*\{)|(\btypedef\b)', "\n".join(body)):
            n_local += 1; skipped["inline type def in body"].append(addr); continue
        cc_queue.append(dict(addr=addr, src=src, hash=h, body=body, members=members))

    # The cpp+cc1 self-containment probe is one INDEPENDENT subprocess pair per candidate and was
    # the whole plan phase's cost: ~5 minutes pegged at one core on a 32-core box while every other
    # core idled. Run them concurrently (subprocess.run drops the GIL) and keep the plan in the
    # original order so the printed plan and every downstream index are unchanged.
    if cc_queue:
        from concurrent.futures import ThreadPoolExecutor
        with ThreadPoolExecutor(max_workers=_jobs()) as ex:
            verdicts = list(ex.map(lambda c: compiles_standalone(c["body"]), cc_queue))
        for c, (ok, why) in zip(cc_queue, verdicts):
            if not ok:
                # SESSION-18: this bucket asserted "overlay-local TYPE" for EVERY failure, which is a
                # mislabel — the dominant real cause is that the body references file-scope `extern`
                # decls that live OUTSIDE the extracted block (func_80174CB0: 22 of them), exactly the
                # gap Phase-27's family_remap._carry_macros closed for file-scope #defines. Name the
                # causes apart so the queue can be sized honestly (R32/R33).
                undecl = sorted(set(re.findall(r"`([A-Za-z_]\w*)' undeclared", why)))
                if undecl:
                    n_local += 1
                    skipped["missing file-scope extern (CARRY-FIXABLE): " + ",".join(undecl[:4])].append(c["addr"])
                else:
                    n_local += 1; skipped["overlay-local TYPE (the real cap)"].append(c["addr"])
                continue
            plan.append(c)

    if n_local or n_nondef or n_lowreach:
        print(f"[skip] {n_local} not self-contained (local types), {n_nondef} not inline-def, "
              f"{n_lowreach} reach<{a.min_reach}")
        for why, addrs in sorted(skipped.items()):
            print(f"    [{why}] {len(addrs)}: {' '.join('0x%08x' % x for x in sorted(addrs))}")
    if not plan:
        sys.exit("[error] nothing to propagate")

    print(f"== plan: {len(plan)} function(s), tier={a.tier}, header={a.header} ==")
    for p in plan:
        print(f"  0x{p['addr']:08X}  body={len(p['body'])}L  members={len(p['members'])}  "
              f"[{','.join(m.replace('ov_','') for m in p['members'][:6])}{'…' if len(p['members'])>6 else ''}]")
    if a.check_only:
        print("(--check-only: no files touched)")
        return

    # ---- apply machinery (extracted so the drop-straggler retry can re-apply a sub-plan).
    header_path = ROOT / a.header
    DEFAULT_H = ("/* src/shared/engine_core.h — Phase 15 shared engine-core bodies (cross-overlay dedup, §14).\n"
                 " * Each DEFINE_func_XXXX() expands to the WHOLE matched body once; instantiated in place at the\n"
                 " * func_XXXX site in every overlay that shares it (address order preserved). Registry +\n"
                 " * byte-honesty: config/dedup.us.yaml + tools/dedup_integrate.py. Tool-generated; do not hand-edit. */\n"
                 "#ifndef SHARED_ENGINE_CORE_H\n#define SHARED_ENGINE_CORE_H\n#include \"common.h\"\n\n#endif\n")

    def apply_plan(subplan, restrict=None, gaps=None, journal=None, header=True):
        """Author each fn's macro into engine_core.h + instantiate it at its site in every member
        overlay (optionally restricted to a set — the per-fn straggler trial uses one overlay). Edit
        each member overlay ONCE (group by overlay; stub lines replace 1:1, inline defs splice in
        REVERSE order). Returns (touched, changed); caller byte-gates `changed` then restore(touched).

        `gaps` (optional dict) collects {overlay: [addrs]} for every claimed member site this could
        NOT place. That set used to be dropped on the floor (R32 silent skip): the address simply
        stayed in `remaining`, the overlay still landed in `changed` because some OTHER fn placed,
        and the only symptom was struct_check's terse "not instantiated" — 92 minutes into a run,
        naming no mechanism. The caller now fails on `gaps` FIRST, with a per-site diagnosis."""
        touched = {} if journal is None else journal
        _tlock = _threading.Lock()

        def _edit(path, newtext):
            with _tlock:                      # overlays never share a path; the lock guards the dict
                if path not in touched:
                    touched[path] = path.read_text() if path.exists() else None
            path.write_text(newtext)
        if header:
            htext = header_path.read_text() if header_path.exists() else DEFAULT_H
            for p in subplan:
                if f"DEFINE_{sym(p['addr'])}()" not in htext:
                    htext = htext.replace("\n#endif\n",
                                          "\n" + make_macro(p["addr"], p["body"]) + "\n#endif\n")
            _edit(header_path, htext)
        by_ov = {}
        for p in subplan:
            for ov in p["members"]:
                if restrict and ov not in restrict:
                    continue
                by_ov.setdefault(ov, []).append(p)
        changed = []

        def _place(ov):
            """Instantiate every planned macro in ONE overlay. Delegates to the module-level
            place_in_overlay so the in-process apply and the process-pool searches can never drift."""
            ovc, rem = place_in_overlay(ov, by_ov[ov], a.header, _edit)
            return ov, ovc, rem

        ovs = sorted(by_ov)
        if len(ovs) > 4:
            from concurrent.futures import ThreadPoolExecutor
            with ThreadPoolExecutor(max_workers=_jobs()) as ex:
                placed = list(ex.map(_place, ovs))     # map preserves order -> `changed` is stable
        else:
            placed = [_place(ov) for ov in ovs]
        for ov, ovc, rem in placed:
            if rem and gaps is not None:
                gaps[ov] = rem                 # R32: assert coverage, never skip silently
            if ovc:
                changed.append(ov)
        return touched, changed

    def restore(touched):
        for path, orig in touched.items():
            if orig is None:
                path.unlink(missing_ok=True)
            else:
                path.write_text(orig)

    def _dirty_set():
        r = subprocess.run(["git", "status", "--porcelain", "--", "src", "config"],
                           cwd=ROOT, capture_output=True, text=True)
        return {l[3:].strip() for l in r.stdout.splitlines() if l.strip()}

    dirty0 = _dirty_set()   # the tree's PRE-EXISTING modifications; residue is measured against this

    def _abort(msg, touched=None):
        """Fail CLOSED, and PROVE it (R32/R35). Every abort path must leave the tree exactly as it
        found it — but struct_check's exits restored only `touched`, so any Part-B reconcile kept on
        disk (and anything else outstanding) survived the "REVERTED" message. That is the §156 class
        on a different path, and it is the expensive one: a tree that is dirty in a way nobody knows
        about makes EVERY later byte-gate report `near`, so its verdicts are void and get misread as
        draft failures (S45p7 lost two whole batches to exactly this).

        So: undo this call's edits AND every kept reconcile, then diff the worktree against the
        baseline and SAY which files (if any) survived. A silent leak becomes a loud one."""
        if touched:
            restore(touched)
        n = _undo_reconciles({ad for ad, _ in kept_reconciles})
        residue = sorted(_dirty_set() - dirty0)
        if residue:
            print(f"[BUG] abort did NOT fully restore — {len(residue)} file(s) still dirty. "
                  f"Run `git checkout -- src/ config/` before trusting ANY later byte-gate (R35):")
            for f in residue[:20]:
                print(f"    {f}")
            if len(residue) > 20:
                print(f"    … and {len(residue) - 20} more")
        else:
            print(f"[revert] tree restored to baseline"
                  + (f" (undid {n} kept reconcile(s))" if n else "") + "; no residue")
        sys.exit(msg)

    def struct_check(subplan, changed, touched):
        # the byte-gate CANNOT catch a leftover stub (it is itself byte-identical): every claimed
        # member must now instantiate the macro and have no stub. One read per changed overlay.
        incasm = lambda ad: re.compile(rf'INCLUDE_ASM\("[^"]+",\s*{sym(ad)}\)')
        for ov in changed:
            t = source_text(ov)   # all split files (post-edit, from disk)
            for p in (pp for pp in subplan if ov in pp["members"]):
                if f"DEFINE_{sym(p['addr'])}()" not in t:
                    _abort(f"[FAIL] {ov}: 0x{p['addr']:08X} not instantiated — REVERTED", touched)
                if incasm(p["addr"]).search(t):
                    _abort(f"[FAIL] {ov}: 0x{p['addr']:08X} stub still present — REVERTED", touched)

    # ---- apply with DROP-STRAGGLER retry. A fn whose shared C body, in some OTHER overlay's TU,
    # byte-mismatches (-O0 per-overlay %lo data) or compile-errors (cross-overlay loose-typed callee
    # decls — cont.4 wave-2) would, under an all-or-nothing batch revert, poison every CLEAN match.
    # So on a byte-gate failure: isolate the culprit(s) for the failing overlay (per-fn trial), drop
    # them (they stay matched ×1 in the source), and retry the batch with the survivors. The byte-gate
    # stays the sole arbiter (G3/P9) — a dropped fn is never banked anywhere it isn't byte-identical.
    # P30 S45p7 — RECONCILE LEDGER (the 141/213 breakage, root-caused 2026-08-07).
    # Part B below deliberately LEAVES its caller-extern reconcile on disk when it buys the match
    # ("keep the reconcile on disk"). That is correct only while the fn ultimately survives. A fn can
    # still be dropped by a LATER iteration (a different fail_ov), and when `plan` finally empties the
    # `sys.exit` at the bottom used to leave every kept reconcile orphaned — a no-proto'd caller extern
    # for a function that was never propagated. Measured cost: dedup_propagate exited 1 leaving
    # ov_SC07_* rewritten, and 141 of 213 binaries failed check-all (the wave-2 propagation, this
    # session). The byte-gate never mis-banked — it fails closed — but every SUBSEQUENT gate then
    # reports `near` against the broken tree, so its verdicts are void (R35), which is how two whole
    # batches (4/4 and 20/20) were mis-read as draft failures.
    # Fix: ledger every kept reconcile against its fn, and undo it the moment that fn leaves `plan`.
    kept_reconciles = []                                 # [(addr, snapshot)] in apply order
    suspects = []                                        # culprit addrs found so far, tried first

    def _undo_reconciles(addrs):
        """Restore reconciles for addrs that did not survive. Reverse order: each snapshot is the
        file text captured BEFORE its own edit, so replaying newest->oldest ends on the original."""
        drop = [r for r in kept_reconciles if r[0] in addrs]
        for _a, _s in reversed(drop):
            restore_snapshot(_s)
        if drop:
            kept_reconciles[:] = [r for r in kept_reconciles if r[0] not in addrs]
        return len(drop)

    while plan:
        gaps = {}
        touched, changed = apply_plan(plan, gaps=gaps)
        if gaps:
            # A claimed member whose site this pass could not place. Diagnose it HERE, where the
            # per-site evidence still exists, instead of letting struct_check report it as a bare
            # "not instantiated" with no mechanism (S45p9: that message cost a whole re-run to
            # even locate). Print, per site, what the whole-overlay oracle says the site IS.
            print(f"[GAP] {sum(len(v) for v in gaps.values())} instantiation(s) unplaced in "
                  f"{len(gaps)} overlay(s):")
            for ov in sorted(gaps):
                t = source_text(ov)
                for ad in gaps[ov]:
                    v = find_site(t, ov, ad)
                    print(f"    {ov} 0x{ad:08X}: whole-overlay find_site="
                          f"{v[0] if v else None}, in-sig={ad in load_sig(ov)}, "
                          f"files={[p.name for p, _ in overlay_files(ov)]}")
            _abort("[FAIL] unplaced instantiation(s) — REVERTED (see [GAP] above)", touched)
        struct_check(plan, changed, touched)
        if a.no_gate:
            break
        fails = gate_failures(changed, f" ({len(plan)} fn(s) in plan)")
        if not fails:
            print(f"[ OK ] {len(changed)} overlays byte-identical after propagation")
            break
        restore(touched)
        print(f"[gate] {len(fails)} overlay(s) diverge: "
              + ", ".join(fails[:8]) + ("…" if len(fails) > 8 else ""))

        # ---- BATCHED culprit resolution.
        # The old loop took the FIRST failure, probed each of the ~30 plan fns against it one build
        # at a time, then paid a whole fresh 141-overlay sweep to rediscover the NEXT failure — so
        # S45's two divergent functions cost 27 sweeps ×(30 serial builds + a full sweep). But the
        # sweep already tells us EVERY failing overlay (gate_failures), and the culprits are almost
        # always the SAME functions in all of them. So: find a sufficient exclusion set once, on one
        # pivot overlay (binary search, ~log2 builds), then decide per-overlay necessity for the
        # whole failing set with ONE PARALLEL SWEEP PER CANDIDATE — 32 builds at a time instead of 1.
        def diverging(excl_addrs, ovs, label=""):
            """Apply the plan MINUS `excl_addrs` to `ovs`; return the subset still byte-diverging.
            This is the overlays' FINAL intended state (every other plan fn applied), so a pass here
            is direct evidence for the bank — stronger than the old one-function-in-isolation probe."""
            sub = [p for p in plan if p["addr"] not in excl_addrs]
            t, c = apply_plan(sub, restrict=set(ovs))
            inplay = [o for o in c if o in set(ovs)]
            bad = set(gate_failures(inplay, label))
            restore(t)
            return bad          # an overlay nothing was applied to never changed -> counts as passing

        # PER-OVERLAY INDEPENDENT SEARCH. Each overlay's answer depends only on its own .c files and
        # its own build/<bin>/ dir — the shared header carries EVERY plan macro regardless of which
        # sites get instantiated, so writing it once up front makes the searches disjoint. That means
        # 138 searches can run at once instead of |E| fleet-wide sweeps in lock-step, and it cuts
        # BUILDS (not just overlap): a sweep pass rebuilds all 138 to answer one question, while a
        # search asks each overlay only the questions that overlay's own answer needs.
        hdr_journal = {}
        # Header-only: author every plan macro once, edit NO overlay. `restrict` is a whitelist, so a
        # sentinel alias that matches nothing gives exactly that while reusing apply_plan's macro
        # authoring (an empty set would be FALSY and disable the filter entirely — editing all 141).
        apply_plan(plan, restrict={"\0no-overlay"}, journal=hdr_journal)
        try:
            # PROCESSES, not threads. The first cut used a ThreadPoolExecutor and measured 0-4 builds
            # alive across 138 "parallel" searches: the work is regex over 15k-line files, so every
            # thread queued on the GIL and the box sat at load 3 with 32 cores. Each search only
            # touches its own overlay's .c and its own build/<bin>/ dir, and the shared header is
            # written once above and never touched by a worker — so separate processes are safe.
            order_fails = sorted(fails, key=lambda o: -_src_bytes(o))   # longest-first
            # Seed the suspect list with ONE overlay first: the same 1-2 fns break every overlay, and
            # a pool submitted all at once would give every worker an EMPTY suspect list and make all
            # 138 of them pay a full bisection instead of the 1+|suspects| fast path.
            seed_ov, seed_excl = search_worker((order_fails[0], plan, a.header, list(suspects)))
            if seed_excl:
                for ad in seed_excl:
                    if ad not in suspects:
                        suspects.append(ad)
            rest = order_fails[1:]
            print(f"[search] {len(fails)} independent per-overlay searches "
                  f"({_jobs()} processes; seeded with {len(suspects)} suspect(s) from {seed_ov})",
                  flush=True)
            found = [(seed_ov, seed_excl)]
            if rest:
                from concurrent.futures import ProcessPoolExecutor
                jobs = [(ov, plan, a.header, list(suspects)) for ov in rest]
                with ProcessPoolExecutor(max_workers=_jobs()) as ex:
                    found += list(ex.map(search_worker, jobs))
        finally:
            restore(hdr_journal)
        broken = [ov for ov, e in found if e is None]
        if broken:
            # Diverges with NOTHING of ours applied => already broken before this run, so every
            # verdict in this sweep is void (R35). Stop rather than "recover" from a bad baseline.
            _abort(f"[FAIL] {', '.join(broken[:5])} diverge with the whole plan excluded — ALREADY "
                   f"broken at baseline; this run's gate verdicts are not evidence (R35).")
        need = {ov: set(e) for ov, e in found}
        byfn0 = collections.Counter(ad for e in need.values() for ad in e)
        print("[culprit] " + ", ".join(f"0x{ad:08X}x{n}" for ad, n in byfn0.most_common(8)))

        recovered, excluded = [], []
        # Part B (batched) — try the caller-extern reconcile for every (overlay, fn) pair at once,
        # then ONE sweep with the full plan: whoever passes keeps its reconcile and its membership.
        if a.recover and any(need.values()):
            snaps = collections.defaultdict(list)          # ov -> [(addr, snapshot)] in apply order
            for ov in sorted(need):
                for ad in sorted(need[ov]):
                    snap, n = reconcile_caller_extern(ov, ad)
                    if n:
                        snaps[ov].append((ad, snap))
            if snaps:
                bad = diverging(set(), sorted(snaps), " (post-reconcile re-gate)")
                for ov, lst in snaps.items():
                    if ov in bad:
                        for _ad, snap in reversed(lst):    # newest->oldest ends on the original text
                            restore_snapshot(snap)
                    else:
                        for ad, snap in lst:
                            need[ov].discard(ad)
                            kept_reconciles.append((ad, snap))   # LEDGERED — undone if the fn drops
                            recovered.append((ov, ad))
        # Part A — exclude only the overlays that still need it (the fn stays for everyone else).
        byaddr = {p["addr"]: p for p in plan}
        for ov in sorted(need):
            for ad in sorted(need[ov]):
                p = byaddr.get(ad)
                if not p:
                    continue
                if not a.recover:                 # historical all-or-nothing: drop the fn outright
                    p["members"] = []
                else:
                    p["members"] = [m for m in p["members"] if m != ov]
                excluded.append((ov, ad))
        survivors = [p for p in plan if len(p["members"]) >= 2]
        dropped = [p for p in plan if len(p["members"]) < 2]

        if recovered:
            print(f"[recover] reconciled the conflicting caller extern for {len(recovered)} "
                  f"(overlay, fn) pair(s) across {len({o for o, _ in recovered})} overlay(s)")
        if excluded:
            byfn = collections.Counter(ad for _ov, ad in excluded)
            print(f"[exclude] {len(excluded)} (overlay, fn) pair(s): "
                  + ", ".join(f"0x{ad:08X}×{n}" for ad, n in byfn.most_common(6)))
        if dropped:
            print(f"[drop] {len(dropped)} fn(s) below reach 2 after exclusion: "
                  + ", ".join(f"0x{p['addr']:08X}" for p in dropped))
        if not (recovered or excluded or dropped):
            # Every search came back with an EMPTY exclusion set even though the sweep said these
            # overlays diverge -> a multi-fn interaction no per-fn exclusion explains. Conservatively
            # drop every fn targeting them (rare; each stays matched ×1) so the rest can proceed, and
            # so the loop cannot spin forever making no progress.
            stuck = set(fails)
            tofail = [p for p in plan if stuck & set(p["members"])]
            print(f"[drop] {len(stuck)} overlay(s) fail with no single-fn culprit (interaction) — "
                  f"dropping their {len(tofail)} fn(s), kept ×1")
            survivors = [p for p in plan if not (stuck & set(p["members"]))]
        # Any fn that just left `plan` must give back its kept reconcile — otherwise a no-proto'd
        # caller extern survives for a function that was never propagated (see the ledger note above).
        _gone = {p["addr"] for p in plan} - {p["addr"] for p in survivors}
        _n = _undo_reconciles(_gone)
        if _n:
            print(f"[restore] undid {_n} kept caller-extern reconcile(s) for dropped fn(s)")
        plan = survivors
    if not plan:
        # Nothing survived ⇒ NOTHING may remain edited. _abort undoes every outstanding reconcile
        # and PROVES the tree is back at baseline, so a failed propagation cannot leave a poisoned
        # tree behind for the next gate to misread (R35).
        _abort("[error] all candidates dropped — no cleanly-shareable function")

    # ---- register groups (compact shorthand: position-locked -> vram + binaries list)
    groups = [dict(id=f"E_{sym(p['addr'])}", tier=a.tier, hash=p["hash"],
                   source=a.header, addr=p["addr"],
                   members=[dict(binary=ov, vram=p["addr"], name=sym(p["addr"])) for ov in p["members"]])
              for p in plan]
    n = append_groups(groups)
    print(f"== propagated {len(plan)} function(s); {len(changed)} overlays rebuilt byte-identical; "
          f"registered {n} new group(s) in config/dedup.us.yaml ==")


if __name__ == "__main__":
    # Stage 1 (docs/concurrency-design.md): propagation is THE fleet-shared writer —
    # it rewrites src/shared/engine_core.h, config/dedup.us.yaml and every member
    # overlay .c. It may never overlap a gate reading that state (verdict decay,
    # design §2.2b). No-op when gate_stage already holds the lock (BFM_SHARED_LOCK_HELD).
    with shared_lock.hold(exclusive=True, announce="dedup_propagate"):
        main()
