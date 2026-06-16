#!/usr/bin/env python3
"""BFM matching-progress report (authoritative; supersedes the Phase-6 PhaseEnd estimate).

Classifies every matchable function across all src/*.c and prints a deterministic summary
(also written to docs/progress.md). Ghidra-free. The REAL count is the number the
Gen1-exit "≥25 matched functions" bar counts (splat-auto empties do NOT count).

Usage:
  tools/progress.py            # print summary + write docs/progress.md
  tools/progress.py --audit    # also verify every empty no-op's asm is exactly {jr,nop}
  tools/progress.py --check     # also hash build/us/SLUS_007.26 vs config/check.us.sha
  tools/progress.py --binary <alias>   # report a non-default binary (default: main = the EXE)
"""
import re, sys, hashlib, pathlib

ROOT = pathlib.Path(__file__).resolve().parent.parent

# Per-binary report config (Phase 9). `main` = the retail EXE; its paths are the originals
# (no-op default). A second binary (Phase 10) adds an entry — its build/check + src/asm tree;
# the overlay src/asm subtree LAYOUT is a Phase-10 decision, not invented here.
BINARIES = {
    "main": dict(build="build/us/SLUS_007.26", check="config/check.us.sha",
                 src="src", asm="asm/nonmatchings", out="docs/progress.md"),
    "resident": dict(build="build/resident/resident", check="config/check.resident.sha",
                     src="src/resident", asm="asm/resident/nonmatchings", out="docs/progress.resident.md"),
}
BINARY = next((sys.argv[i + 1] for i, x in enumerate(sys.argv)
               if x == "--binary" and i + 1 < len(sys.argv)), "main")
if BINARY not in BINARIES:
    sys.exit(f"progress.py: unknown --binary '{BINARY}' (known: {', '.join(BINARIES)})")
_cfg = BINARIES[BINARY]
SRCS = sorted((ROOT / _cfg["src"]).glob("*.c"))   # every c-segment (src/boot.c, src/800.c, ...)
ASM_ROOT = ROOT / _cfg["asm"]                      # per-segment subdirs (boot/, 800/, ...)
OUT  = ROOT / _cfg["out"]
BUILD = ROOT / _cfg["build"]
CHECK = ROOT / _cfg["check"]
MAKEFILE = ROOT / "Makefile"

def linked_subsegs():
    """Library subsegments swapped to real PsyQ objects at build time = the 5th positional arg
    of each `psyq_integrate.py` call in the Makefile (e.g. `libcd1,libcd2`). Parsing the Makefile
    keeps it the SINGLE source of truth: a new library integration adds its psyq_integrate call and
    its stubs are auto-counted LINKED (no separate manifest to drift). Stubs in these subsegs build
    byte-identically from the real SDK objects when present, and from the committed asm fallback
    otherwise (fresh clone) — so they are LINKED regardless of local .run/obj40 state (a property of
    the project, not the machine).

    Scoped to the active binary: every psyq_integrate call lives inside the Makefile's
    `ifeq ($(BINARY),main)` block (PsyQ library linking is the EXE's layout — Phase 8), so only
    `main` has LINKED subsegs. A second binary (e.g. resident) has none. When a future binary gains
    its own gated integration, parse that gate here instead of the main-only shortcut."""
    if BINARY != "main":
        return set()
    if not MAKEFILE.exists():
        return set()
    txt = MAKEFILE.read_text()
    # stub lists may be passed inline (`libcd1,libcd2`) or via a make var (`$(LIBGTE_STUBS)` for the
    # long multi-block ones) — collect `NAME := <comma,list>` defs so either form resolves.
    mvars = dict(re.findall(r'^(\w+)\s*:=\s*([A-Za-z0-9_,]+)\s*$', txt, re.M))
    segs = set()
    # leading --flag value pairs (Phase 9: --vram-base/--exe/--symbols) precede the 4 positionals
    # (elf_dir ld_path objdir syms_ld); the 5th positional is the stub list captured below.
    for m in re.finditer(r'psyq_integrate\.py(?:\s+--\S+\s+\S+)*\s+\S+\s+\S+\s+\S+\s+\S+\s+(\S+)', txt):
        arg = m.group(1)
        vm = re.fullmatch(r'\$\((\w+)\)', arg)
        if vm:
            arg = mvars.get(vm.group(1), '')
        segs.update(s for s in arg.split(',') if re.fullmatch(r'[A-Za-z0-9_]+', s))
    return segs

LINKED_SEGS = linked_subsegs()

def dedup_members(binary):
    """Function names matched-once-and-shared via config/dedup.us.yaml for this binary. They are
    hand-matched byte-identical C, but instantiated from a shared body (a macro in src/shared/),
    so classify()'s function-definition scan does NOT recognize the macro form — count them REAL
    via the registry instead (the source of truth for code shares, Phase 11). Returns a set."""
    p = ROOT / "config/dedup.us.yaml"
    if not p.exists():
        return set()
    try:
        import yaml
        data = yaml.safe_load(p.read_text()) or {}
        return {m["name"] for g in (data.get("groups") or [])
                for m in (g.get("members") or []) if m.get("binary") == binary}
    except Exception:
        return set()

def find_s(name):
    """Locate <name>.s in any asm/nonmatchings/<seg>/ subdir (segments: boot, 800, ...)."""
    for p in sorted(ASM_ROOT.glob(f"*/{name}.s")):
        return p
    return None

INSTR = re.compile(r'^\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s*\*/\s+[a-z]')

def strip_comments(s):
    s = re.sub(r'/\*.*?\*/', '', s, flags=re.S)
    return re.sub(r'//[^\n]*', '', s)

def is_data_blob(name):
    """A .s with a code label (glabel/jlabel) is a function; data-only (dlabel, no code) is a blob."""
    p = find_s(name)
    if p is None:
        return False
    txt = p.read_text()
    return ('glabel' not in txt and 'jlabel' not in txt and 'dlabel' in txt)

def asm_is_trivial(name):
    """True iff the function's asm is exactly {jr, nop} (the empty-no-op shape splat emits void{} for)."""
    p = find_s(name)
    if p is None:
        return None
    mnem = []
    for ln in p.read_text().splitlines():
        m = re.match(r'^\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s*\*/\s+([a-z0-9.]+)', ln)
        if m:
            mnem.append(m.group(1))
    return set(mnem) <= {'jr', 'nop'} and len(mnem) <= 2

SIG = re.compile(r'^\s*[A-Za-z_][\w \t\*]*\b([A-Za-z_]\w*)\s*\(')

def classify():
    real, empty, nonmatching, stubs, blobs, linked = [], [], [], [], [], []
    for src in SRCS:
        lines = src.read_text().split('\n')
        n = len(lines); i = 0
        while i < n:
            s = lines[i].strip()
            if s.startswith('#ifdef NON_MATCHING'):
                blk = []
                while i < n and not lines[i].strip().startswith('#endif'):
                    blk.append(lines[i]); i += 1
                i += 1
                m = re.search(r'INCLUDE_ASM\("[^"]+",\s*(\w+)\)', '\n'.join(blk))
                if m: nonmatching.append(m.group(1))
                continue
            m = re.match(r'INCLUDE_ASM\("([^"]+)",\s*(\w+)\)', s)
            if m:
                seg, fn = m.group(1).rstrip('/').rsplit('/', 1)[-1], m.group(2)
                if is_data_blob(fn):
                    blobs.append(fn)
                elif seg in LINKED_SEGS:     # subseg swapped to a real PsyQ object (byte-identical)
                    linked.append(fn)
                else:
                    stubs.append(fn)
                i += 1; continue
            if s.startswith('INCLUDE_RODATA'):
                i += 1; continue
            fm = SIG.match(lines[i])
            if fm and '(' in lines[i]:
                # Definition ({ ... }) vs forward declaration (ends ;)? Scan to the first { or ;.
                # extern/prototype lines (e.g. `extern s32 CdQueueBusy(void);`) are NOT functions.
                j = i; kind = None
                while j < n:
                    c = strip_comments(lines[j])
                    br = c.find('{'); sm = c.find(';')
                    if br != -1 and (sm == -1 or br < sm): kind = 'def'; break
                    if sm != -1: kind = 'decl'; break
                    j += 1
                if kind != 'def':
                    i = j + 1; continue            # skip the declaration
                start = i; depth = 0; opened = False
                while i < n:
                    c = strip_comments(lines[i]); depth += c.count('{') - c.count('}')
                    if '{' in c: opened = True
                    i += 1
                    if opened and depth <= 0: break
                body = '\n'.join(lines[start:i])
                a, b = body.index('{'), body.rindex('}')
                (real if strip_comments(body[a+1:b]).strip() else empty).append(fm.group(1))
                continue
            i += 1
    return real, empty, nonmatching, stubs, blobs, linked

def main():
    audit = '--audit' in sys.argv
    check = '--check' in sys.argv
    real, empty, nonmatching, stubs, blobs, linked = classify()
    # Code-shared functions (dedup.us.yaml) are REAL byte-identical matches whose macro-instantiated
    # form classify() doesn't parse — fold them in (dedup-safe) so the count stays honest (P9).
    shared = sorted(dedup_members(BINARY) - set(real))
    real = sorted(set(real) | set(shared))
    matchable = len(real) + len(empty) + len(nonmatching) + len(stubs) + len(linked)
    byteident = len(real) + len(linked) + len(empty)   # all byte-identical in the build

    out = []
    out.append("# BFM matching progress  (generated by tools/progress.py — authoritative)")
    out.append("")
    out.append(f"REAL substantive matches : {len(real):5d}   <- the Gen1-exit >=25 bar counts THIS")
    if shared:
        out.append(f"  (of which dedup-shared : {len(shared):5d}   one body -> N sites, config/dedup.us.yaml)")
    out.append(f"LINKED real PsyQ objects : {len(linked):5d}   <- byte-identical via linked SDK objects")
    out.append(f"NON_MATCHING (near-miss) : {len(nonmatching):5d}")
    out.append(f"splat-auto empty no-ops  : {len(empty):5d}")
    out.append(f"INCLUDE_ASM stubs        : {len(stubs):5d}")
    out.append(f"data blobs (excluded)    : {len(blobs):5d}")
    out.append("-" * 40)
    out.append(f"matchable functions      : {matchable:5d}")
    out.append(f"REAL / matchable         : {len(real)} / {matchable} = {100*len(real)/matchable:.2f}%")
    out.append(f"byte-identical/ matchable: {byteident} / {matchable} = {100*byteident/matchable:.2f}%   (REAL+LINKED+empties)")
    out.append("")
    out.append("LINKED subsegs: " + " ".join(sorted(LINKED_SEGS)) + f"  ({len(linked)} fns)")
    out.append("REAL matches: " + " ".join(sorted(real)))
    out.append("NON_MATCHING: " + " ".join(sorted(nonmatching)))

    if BUILD.exists():
        h = hashlib.sha1(BUILD.read_bytes()).hexdigest()
        want = CHECK.read_text().split()[0] if CHECK.exists() else ""
        out.append("")
        out.append(f"build SHA1: {h}  ({'byte-identical' if h == want else 'MISMATCH'})")

    if audit:
        bad = [n for n in empty if asm_is_trivial(n) is False]
        out.append("")
        out.append(f"empties audit: {len(empty)-len(bad)}/{len(empty)} genuine jr;nop"
                   + (f"  !! SUSPICIOUS: {bad}" if bad else "  (all clean)"))

    text = "\n".join(out) + "\n"
    print(text, end="")
    OUT.write_text(text)

    if check:
        import subprocess
        sys.exit(subprocess.run(["make", "-C", str(ROOT), "check"]).returncode)

if __name__ == "__main__":
    main()
