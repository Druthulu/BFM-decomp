#!/usr/bin/env python3
"""tools/corpus.py — THE corpus oracle. One DERIVED model of the source tree.

WHY THIS EXISTS  (Phase 26-A tooling audit; R33)
================================================
28 surviving audit findings collapsed to ONE bug, repeated ~10 times:

    a hand-maintained model of the corpus layout — a file allowlist, a single-.c assumption, a
    func_-only symbol regex, a REGION_SUB dict — sitting on top of a filesystem that already
    answers the question.

Every translation-unit split silently widened it. An overlay's source is now spread over up to 14
.c files (<ov>.c, _a, _o0, _o0b, _after, and the Phase-26 _jr_<ADDR> carves); tools written when
there was one file still believe there is one file.

PROOF OF DECAY: .run/fuel_manifest.json (written 2026-07-08) recorded 130 live stubs. The same tool
run today returns 30. The Phase-26 jr splits moved ~100 stubs out from under a dict literal last
edited in Phase 22 — and 91.6% of ALL remaining project gain became invisible to target selection.
NOBODY NOTICED, BECAUSE A TARGET THAT IS NEVER NOMINATED PRODUCES SILENCE, NOT AN ERROR.

The fix is therefore not ten repaired regexes. It is ONE derived oracle and ten deleted scanners.

WHAT IT DERIVES FROM
====================
1. THE FILESYSTEM. Which .c files make up a binary, and where a function's .s lives, are FACTS OF
   THE TREE THAT SPLAT ITSELF WROTE. Glob them; never keep a second copy. A dict literal is a
   strictly worse oracle than the filesystem, and it fails OPEN (silently yields a wrong path)
   rather than closed. Note the INCLUDE_ASM line is SELF-DESCRIBING — its first argument IS the
   asm subdir — so even the glob is unnecessary: the stub states its own home.

2. THE PROVEN INVARIANT. The fleet builds byte-identical, and INCLUDE_ASM pastes the ORIGINAL
   assembly. Therefore A FUNCTION NOT WRAPPED IN INCLUDE_ASM IS BYTE-EXACT. `matched` is DERIVED as
   sig − stubs. It is never re-parsed out of C text — that is what progress.py learned the hard
   way: its weighted_metrics() derived from the invariant and was right; its classify() re-parsed C
   and inherited a bug.

USE vs AUDIT — this separation is the whole point
=================================================
* The WORKING API (src_files / stubs / matched / asm_path) asserts what is ALWAYS true, and FAILS
  LOUD when it is not: every INCLUDE_ASM line parses, every stub symbol resolves to an address,
  every stub has a .s on disk. A silent skip is a DEFECT, not a no-op (R32).

* audit() additionally cross-checks the stub set against sig_image's INDEPENDENTLY-computed
  function boundaries. It reports two disagreements the working API cannot see:
      PHANTOM   — a stub address that is NOT a function in the sig: splat INVENTED a function.
      TRUNCATED — a stub whose .s instruction count differs from the sig's: splat MIS-SLICED one.

  audit() FAILS TODAY, and it must. That is how the listCdBuffer corpus defect is visible at all:
  config/symbols.us.txt:981 declares `listCdBuffer = 0x80180000`, a main-EXE DATA symbol, and every
  overlay's splat config loads that file — but in OVERLAY space 0x80180000 is CODE. splat therefore
  cuts 97 real functions in half and invents 96 phantom ones: 193 slices nobody can ever match (you
  cannot write C for a function that ends on a `lui` with no return, nor one that begins by reading
  the assembler temp $at). They sit in the harvest queue as ordinary work, so agents burn on them
  forever and the failure reads as an intrinsic compiler wall — AND THE FULL-BINARY BYTE-GATE STAYS
  GREEN THROUGHOUT, because the .s halves are pasted back verbatim in original order.

  THE LESSON THE AUDIT PAID FOR, and the reason this file has two modes:
      When one oracle is structurally blind to a class of error, the answer is not a better
      assertion inside it. It is a SECOND ORACLE THAT CAN DISAGREE WITH IT.
  sig_image is that second oracle here, and it was RIGHT — it agrees with spimdisasm on 58,524 of
  58,621 functions and is demonstrably correct on all 97 disagreements.

Usage:  tools/corpus.py <binary>|--all [--audit]
"""
import functools
import glob as _glob
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cdecl                                    # noqa: E402 — the ONE masking oracle (§134/R33)
from collections import namedtuple

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# OVER-APPROXIMATING candidate detector (R32). Any INCLUDE_ASM mention outside a comment is a
# candidate; anything the strict parser then fails to read is a COVERAGE DEFECT, not a shrug.
_INCLUDE_ASM_CAND = re.compile(r'^(?![ \t]*(?://|\*|/\*)).*INCLUDE_ASM\s*\(')
# The strict parser. NOTE the symbol group is ANY C identifier — a func_-only pattern silently
# misses curated stub names (listCdBuffer), which is how 100 real stubs went unseen fleet-wide.
_INCLUDE_ASM = re.compile(r'INCLUDE_ASM\(\s*"([^"]+)"\s*,\s*([A-Za-z_]\w*)\s*\)')
_SYM_LINE = re.compile(r'^\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)')
_INS = re.compile(r'/\* [0-9A-Fa-f]+ [0-9A-Fa-f]{8} [0-9A-Fa-f]{8} \*/')
# Data-directive lines carry the same /* off addr word */ comment shape as instructions — a
# module-class .s can legitimately hold its function's HEADER-region jump table (the paired
# .rodata migration, S45: `dlabel jtbl_*` + `.word .L*` lines ride inside func_*.s so the local
# labels resolve). Those are DATA, not instructions; counting them mis-read 24 correct module
# slices as TRUNCATED. The audit compares CODE extents — exclude directive lines.
_DATA_DIRECTIVE = re.compile(r'\*/\s*\.(word|short|byte|ascii|asciz|float|double)\b')
_FUNC_NAME = re.compile(r'^func_([0-9A-Fa-f]{6,8})$')

Stub = namedtuple("Stub", "addr symbol path region asm_dir asm_path")


class CorpusError(RuntimeError):
    """A coverage defect. The corpus does not mean what the tool assumed; refuse to guess."""


# --------------------------------------------------------------------------------------------
# the tree
# --------------------------------------------------------------------------------------------
def splat_config(binary):
    return os.path.join(REPO, "config",
                        "splat.us.exe.yaml" if binary == "main" else f"splat.{binary}.yaml")


def src_files(binary):
    """The .c files that make up a binary. A GLOB — never an allowlist.

    An allowlist is a second, decaying model of a tree that already answers the question; every
    split since Phase 19 widened the hole in the last one. If a new split kind appears tomorrow,
    this function is already correct."""
    if binary == "main":
        return sorted(_glob.glob(os.path.join(REPO, "src", "*.c")))
    return sorted(_glob.glob(os.path.join(REPO, "src", binary, f"{binary}*.c")))


def region_of(path, binary):
    """'main' for the bare TU, else its suffix ('a', 'o0', 'o0b', 'after', 'jr_8015AE2C', ...).

    Derived from the filename, so a new split kind names itself and needs no code change."""
    stem = os.path.basename(path)[:-2]
    if binary == "main":
        return stem
    return "main" if stem == binary else stem[len(binary) + 1:]


@functools.lru_cache(maxsize=None)
def symbols(binary):
    """name -> addr, from the symbol files THIS binary's splat config actually stacks.

    Per-binary, never a union: symbols.resident.txt is deliberately NOT stacked by main (0x8005C324
    is DEFINED there by MEMCPY.o), so a fleet-wide merge invents conflicts that do not exist."""
    cfg, out, in_list = splat_config(binary), {}, False
    if os.path.exists(cfg):
        for ln in open(cfg):
            if re.match(r'\s*symbol_addrs_path:', ln):
                in_list = True
                continue
            if in_list:
                m = re.match(r'\s*-\s*(\S+)', ln)
                if not (m and m.group(1).endswith(".txt")):
                    break
                p = os.path.join(REPO, m.group(1))
                if os.path.exists(p):
                    for line in open(p):
                        sm = _SYM_LINE.match(line)
                        if sm:
                            out.setdefault(sm.group(1), int(sm.group(2), 16))
    return out


# --------------------------------------------------------------------------------------------
# the stub set — the primitive everything else rests on
# --------------------------------------------------------------------------------------------
@functools.lru_cache(maxsize=None)
def stubs(binary):
    """addr -> Stub, for every function this binary still ships as INCLUDE_ASM.

    Coverage-asserted (R32): every candidate INCLUDE_ASM line must parse, every symbol must resolve
    to an address, and every stub must have a .s on disk. Any of those failing means the oracle
    cannot answer 'is this function banked?' — so it refuses to answer rather than guess 'banked'."""
    syms = symbols(binary)
    out, unparsed, unresolved, missing_s = {}, [], [], []

    for p in src_files(binary):
        # CANDIDACY IS DECIDED ON COMMENT-MASKED TEXT (P30 S48, byte-witnessed — the FOURTH instance
        # of this class in one session, after jr_isolate_all's alias scan, overlay_src_split's
        # def-proto scan and scope_data_externs' brace scan). `_INCLUDE_ASM_CAND` only skips a line
        # that BEGINS with a comment marker, so a crack agent's decl annotated
        #     extern void func_801842DC(s32 a0);   /* TU:4023 INCLUDE_ASM (no decl) */
        # is CODE followed by a comment whose prose contains `INCLUDE_ASM (` — the candidate filter
        # fires, the strict parser finds no quoted path, and the whole binary's stub oracle REFUSES
        # (correctly, per its own R32 contract). One such draft then broke `gate_stage` for every
        # LATER binary in the run too, because they all walk the corpus. Mask first (§134/R33 — one
        # masking oracle), then PARSE FROM THE ORIGINAL, since `_mask` also blanks string content
        # and would erase the asm path.
        raw = open(p, errors="replace").read()
        masked = cdecl._mask(raw)
        if len(masked) != len(raw):          # length invariant broken -> do not mis-index; scan raw
            masked = raw
        for i, (line, mline) in enumerate(zip(raw.split("\n"), masked.split("\n")), 1):
            if not _INCLUDE_ASM_CAND.match(mline):
                continue
            m = _INCLUDE_ASM.search(line)
            if not m:                                   # candidate the strict parser cannot read
                unparsed.append(f"{os.path.relpath(p, REPO)}:{i}: {line.strip()[:90]}")
                continue
            asm_dir, sym = m.group(1), m.group(2)
            # A data-shaped INCLUDE_ASM (D_*/jtbl_*) is a BLOB include, not a function stub —
            # splat emits an in-text data word this way (md_MAIN_003's 0x800D3200 sentinel, S45).
            # progress.py already classifies these as blobs (is_data_blob); the stub oracle must
            # agree: they are not functions, so they belong in NO stub set. Not a silent skip
            # (R32): the bytes still paste via the .s, and progress counts them in `blobs`.
            if re.match(r"(D_|jtbl_)[0-9A-Fa-f]+$", sym):
                continue
            fm = _FUNC_NAME.match(sym)
            addr = int(fm.group(1), 16) if fm else syms.get(sym)
            if addr is None:
                unresolved.append(f"{os.path.relpath(p, REPO)}:{i}: {sym}")
                continue
            sp = os.path.join(REPO, asm_dir, f"{sym}.s")
            if not os.path.exists(sp):
                missing_s.append(f"{os.path.relpath(p, REPO)}:{i}: {asm_dir}/{sym}.s")
            out[addr] = Stub(addr, sym, os.path.relpath(p, REPO), region_of(p, binary),
                             asm_dir, os.path.relpath(sp, REPO))

    if unparsed:
        raise CorpusError(f"{binary}: {len(unparsed)} INCLUDE_ASM line(s) the parser cannot read "
                          f"(a silent skip here hides real work):\n  " + "\n  ".join(unparsed[:10]))
    if unresolved:
        raise CorpusError(f"{binary}: {len(unresolved)} INCLUDE_ASM symbol(s) resolve to NO address "
                          f"— the bank oracle is blind to them:\n  " + "\n  ".join(unresolved[:10]))
    if missing_s:
        raise CorpusError(f"{binary}: {len(missing_s)} stub(s) have NO .s on disk — the tree and the "
                          f"source disagree:\n  " + "\n  ".join(missing_s[:10]))
    return out


def asm_path(binary, symbol):
    """The .s for a symbol, taken from the stub that names it. The INCLUDE_ASM line is
    SELF-DESCRIBING — splat wrote the subdir into it — so there is nothing to guess and no dict to
    rot. Returns None for a matched function (which correctly has no .s)."""
    for s in stubs(binary).values():
        if s.symbol == symbol:
            return s.asm_path
    return None


# --------------------------------------------------------------------------------------------
# the optimization level — DERIVED FROM THE MAKEFILE, never from a filename convention
# --------------------------------------------------------------------------------------------
# gcc-2.7.2 has no per-function optimize pragma, so opt level is PER FILE and lives in the
# Makefile as target-specific CC1FLAGS. Four rules currently select -O0: src/boot.c, the
# ov_SC01_077 -O0 cluster, the whale's <ov>_o0b, and the Phase-29 per-overlay -O0 cluster.
#
# WHY THIS IS DERIVED AND COVERAGE-ASSERTED RATHER THAN `path.endswith("_o0.c")`:
# compiling an -O0 target's draft at -O2 (or the reverse) produces a residual that is 100%
# ARTEFACT — the C may be byte-perfect and still "mismatch" everywhere. This project has paid for
# that exact confusion four times (§53 missing carve, the -O0 flag, the member's canonical
# declaration, and Task-1's "~3% ceiling", which was two -O0 families swept at -O2). A hardcoded
# suffix list is the same class of hand-maintained model corpus.py exists to delete: it fails
# OPEN, silently mislabelling any future -O0 rule. So parse the rules, and if a rule appears in a
# form this parser does not understand, REFUSE TO ANSWER (R32/R33/R35).
_O0_RULE = re.compile(r'^([^:\s#][^:\n]*):\s*CC1FLAGS\s*:?=\s*(.*)$', re.M)
_MAKE_VAR = re.compile(r'^\s*%s\s*:?=\s*(.*)$', re.M)
_WILDCARD = re.compile(r'\$\(wildcard\s+([^)]*)\)')
_FILTEROUT = re.compile(r'\$\(filter-out\s+([^,]*),')


@functools.lru_cache(maxsize=1)
def o0_sources():
    """The set of repo-relative .c files the Makefile compiles at -O0. Coverage-asserted."""
    mk = open(os.path.join(REPO, "Makefile"), errors="replace").read()
    out, unresolved = set(), []
    for target, flags in _O0_RULE.findall(mk):
        if "-O0" not in flags.split("#")[0]:
            continue
        for tok in target.split():
            if tok.startswith("$(") and tok.endswith(")"):          # a wildcard-built object list
                var = tok[2:-1]
                m = re.search(_MAKE_VAR.pattern % re.escape(var), mk, re.M)
                if not m:
                    unresolved.append(tok)
                    continue
                value = m.group(1)
                globs = [g for spec in _WILDCARD.findall(value) for g in spec.split()]
                if not globs:
                    unresolved.append(tok)
                    continue
                drop = {os.path.normpath(x) for spec in _FILTEROUT.findall(value)
                        for x in spec.split()}
                hit = False
                for g in globs:
                    for p in _glob.glob(os.path.join(REPO, g)):
                        rel = os.path.relpath(p, REPO)
                        if os.path.normpath(rel) not in drop:
                            out.add(rel)
                            hit = True
                if not hit:
                    # a glob matching nothing is legitimate (no such split exists yet); the RULE
                    # was still understood, so this is not a coverage defect.
                    pass
            elif tok.startswith("build/src/") and tok.endswith(".o"):
                out.add("src/" + tok[len("build/src/"):-2] + ".c")
            else:
                unresolved.append(tok)
    if unresolved:
        raise CorpusError(
            "Makefile has -O0 CC1FLAGS rule target(s) this parser cannot resolve: %s. "
            "Refusing to answer 'is this file -O0?' — a wrong answer makes every residual it "
            "touches a pure artefact (R32/R35)." % ", ".join(sorted(set(unresolved))))
    if not out:
        raise CorpusError("Makefile has NO -O0 CC1FLAGS rule — src/boot.c alone should match. "
                          "The parser is broken or the rules moved.")
    return frozenset(out)


def is_o0(src_path):
    """Is this .c compiled at -O0? `src_path` is repo-relative (a Stub.path) or absolute."""
    rel = os.path.relpath(src_path, REPO) if os.path.isabs(src_path) else src_path
    return os.path.normpath(rel) in {os.path.normpath(p) for p in o0_sources()}


# --------------------------------------------------------------------------------------------
# the invariant
# --------------------------------------------------------------------------------------------
@functools.lru_cache(maxsize=None)
def sig(binary):
    """addr -> sig row (.run/sig.<bin>.jsonl). Signs the ORIGINAL bytes: immutable w.r.t. src/."""
    import dup_report
    cfg = dup_report.BINARIES.get(binary)
    if not cfg:
        raise CorpusError(f"{binary}: not in dup_report.BINARIES")
    p = os.path.join(REPO, cfg["sig"])
    if not os.path.exists(p):
        raise CorpusError(f"{binary}: no signature at {cfg['sig']} — run `make sig-overlays`")
    out = {}
    for line in open(p):
        line = line.strip()
        if line:
            r = json.loads(line)
            out[int(r["addr"], 16)] = r
    return out


def matched(binary):
    """addr -> sig row, for every function this binary builds from C.

    DERIVED from the proven invariant — sig MINUS stubs — never re-parsed out of C text. The build
    is byte-identical and INCLUDE_ASM pastes the ORIGINAL asm, so 'not stubbed' IS 'byte-exact'.
    A parse hole in a C-text scanner would make this WRONG; a derivation cannot be."""
    st = stubs(binary)
    return {a: r for a, r in sig(binary).items() if a not in st}


# --------------------------------------------------------------------------------------------
# the second oracle
# --------------------------------------------------------------------------------------------
def sig_is_independent(binary):
    """Is this binary's sig a SECOND, INDEPENDENT oracle for function boundaries?

    Only for the overlays. Their sigs come from tools/sig_image.py — a Ghidra-free rabbitizer
    signer that derives boundaries from the ORIGINAL bytes, independently of splat, and was
    validated at 58,524/58,621 agreement with spimdisasm (correct on all 97 disagreements).

    main and resident are signed by the GHIDRA dumper (DumpFunctionSignatures.java), whose function
    boundaries are Ghidra's own and are routinely SHORTER than splat's (Ghidra ends functions early
    on unreachable tails; it also never analysed the linked PsyQ library subsegs at all). Comparing
    splat against it measures GHIDRA'S limits, not splat's errors.

    This distinction is load-bearing. Running the boundary cross-check over all 136 binaries reports
    914 'unmatchable slices'; restricted to the domain where the oracle is actually independent it
    reports 193 — and the 193 are real, reproduce the audit exactly, and are all one defect. The
    721 difference was an artefact of comparing two oracles that were never measuring the same thing.
    A check applied outside its valid domain does not become more thorough; it becomes noise (R14).

    RESIDENT (Phase-27 T10): now covered. `make sig-resident` signs the resident flat blob with
    sig_image (the same byte-derived signer, `--vram-base 0x800CEDF8`) instead of Ghidra, so its sig
    IS independent — probed clean (144 sig fns, all 21 source stubs present, 0 phantom). The check is
    valid IFF .run/sig.resident.jsonl is the sig_image sig; run `make sig-resident` first (a stale
    Ghidra sig there would resurrect the 'measuring Ghidra's limits' artefact). MAIN stays excluded —
    sig_image cannot yet sign the EXE (0x800 header offset, interleaved data islands, one text range);
    that second oracle is scoped-and-deferred in docs/second-oracle.md."""
    return binary.startswith(("ov_", "md_")) or binary == "resident"


def s_ins_count(asm_path):
    """Instruction count of a splat .s stub: `/* off vaddr word */` lines that are not data
    directives. Factored from audit() (P31 T3) so the sig-main seed-ends path and any verifier
    share ONE counter (R33). The .s count is what a C match must reproduce — it is the
    authoritative per-function length for main, where sig_image's func_end heuristic mis-slices."""
    p = asm_path if os.path.isabs(asm_path) else os.path.join(REPO, asm_path)
    return sum(1 for ln in open(p, errors="replace")
               if _INS.search(ln) and not _DATA_DIRECTIVE.search(ln))


def audit(binary):
    """Cross-check splat's function boundaries against the sig's independent ones.

    PHANTOM   : a stub address that is not a function in the sig -> splat INVENTED a function.
    TRUNCATED : a stub in the sig whose .s length != the sig's -> splat MIS-SLICED a function.

    Neither is visible to the byte-gate: the .s pieces are pasted back verbatim in original order,
    so the image stays byte-identical either way. Only a second, independent oracle can see them --
    which is the entire reason this function exists. See sig_is_independent(): the verdict is only
    meaningful where the sig genuinely is one."""
    st, sg = stubs(binary), sig(binary)
    phantom, truncated = [], []
    if sig_is_independent(binary):
        for a, s in sorted(st.items()):
            row = sg.get(a)
            if row is None:
                phantom.append(s)
                continue
            p = os.path.join(REPO, s.asm_path)
            if os.path.exists(p):
                n = s_ins_count(s.asm_path)
                if n != row["nins"]:
                    truncated.append((s, n, row["nins"]))
    return {"binary": binary, "stubs": len(st), "matched": len(matched(binary)),
            "independent": sig_is_independent(binary),
            "phantom": phantom, "truncated": truncated}


def main():
    args = sys.argv[1:]
    do_audit = "--audit" in args
    args = [a for a in args if a != "--audit"]
    if "--seed-ends" in args:
        # P31 T3: emit `0xADDR NINS` per stub (sig_image --seeds input; splat-true lengths).
        args = [a for a in args if a != "--seed-ends"]
        if len(args) != 1:
            sys.exit("usage: corpus.py <binary> --seed-ends")
        for a_, s in sorted(stubs(args[0]).items()):
            print(f"0x{a_:08X} {s_ins_count(s.asm_path)}")
        return
    sys.path.insert(0, os.path.join(REPO, "tools"))
    import dup_report
    bins = sorted(dup_report.BINARIES) if (not args or args[0] == "--all") else args

    tot_p = tot_t = 0
    for b in bins:
        try:
            st, mt = stubs(b), matched(b)
        except CorpusError as e:
            print(f"[FAIL] {e}")
            sys.exit(1)
        regions = {}
        for s in st.values():
            regions[s.region] = regions.get(s.region, 0) + 1
        line = f"{b:16s} files={len(src_files(b)):2d}  stubs={len(st):5d}  matched={len(mt):5d}"
        if do_audit:
            r = audit(b)
            tot_p += len(r["phantom"])
            tot_t += len(r["truncated"])
            flag = ""
            if r["phantom"]:
                flag += f"  PHANTOM={len(r['phantom'])}"
            if r["truncated"]:
                flag += f"  TRUNCATED={len(r['truncated'])}"
            line += flag
        print(line + (f"   regions={dict(sorted(regions.items()))}" if len(bins) == 1 else ""))

    if do_audit:
        print(f"\ncorpus audit: {tot_p} PHANTOM + {tot_t} TRUNCATED = {tot_p + tot_t} unmatchable slices")
        if tot_p or tot_t:
            print("  splat's boundaries disagree with sig_image's. sig_image is the independent oracle;\n"
                  "  a stub it does not recognise is a function NOBODY CAN EVER MATCH.")
            sys.exit(1)


if __name__ == "__main__":
    sys.path.insert(0, os.path.join(REPO, "tools"))
    main()
