#!/usr/bin/env python3
"""asm_in_c.py — find every function that is ASSEMBLY POSING AS C.

WHY THIS EXISTS (P31 S75). A `.c` file in `src/` looks decompiled. Some of it is not: a §265
verbatim body is the target assembly pasted into a C string literal, byte-identical BY CONSTRUCTION
and completely unexplained. Those functions are real work still to do, and until now nothing counted
them — `progress.py`'s `classify()` matched `INCLUDE_ASM`, `INCLUDE_RODATA` and C definitions, and a
file-scope `__asm__` block matched none of them, so it fell into the `UNPLACED (parse hole)` line or
was swallowed by a surrounding construct.

THE MEASUREMENT THIS TOOL EXISTS TO GET RIGHT. Counting them by hand went 116 -> 112 -> 108 -> 178
across four attempts in one session, every number confidently reported, because:

  * the sources use BOTH `".ent\\tNAME\\n"` (tab) and `".ent NAME\\n"` (space) — a pattern anchored
    on one silently drops every instance of the other;
  * a bare fragment `".ent\\t"` also occurs, and an optional-`\\t` pattern captured the literal name
    `t` from it, six times;
  * `__asm__` appears in 3,182 files, almost all of it the §3a zero-byte cross-jump barrier
    (`__asm__ __volatile__("" ::: "memory")`) — counting files, or counting `__asm__`, is meaningless.

So this tool does NOT trust one regex. It runs THREE independent detectors and makes them ARGUE
(R34): a disagreement is reported as a DEFECT, not silently resolved. It asserts its own coverage
(R32): every `__asm__` block is classified as function-defining or not, and an unclassifiable one
fails loudly. And `--selftest` checks it against known-true cases of EACH spelling before you are
allowed to believe its number.

THREE CLASSES, and only the first two are "posing":

  A  FILE-SCOPE VERBATIM  — a file-scope `__asm__("...")` that DEFINES a function
                            (`.ent NAME` / `.globl NAME` + `NAME:` / `.type NAME, @function`).
                            No C at all. This is §265.
  B  ASM-BODIED C         — a C function whose body contains nothing but asm statements. It has a
                            real signature and prototype, so it reads as decompiled in every report,
                            and it is not.
  C  LEGITIMATE INLINE    — a C function with real C plus some inline asm (the §3a barrier, register
                            pins from §17). NOT posing, NOT reported. Excluding these correctly is
                            most of the tool's value: they outnumber the real hits by ~20x.

Usage:
    tools/asm_in_c.py                    # report, all binaries
    tools/asm_in_c.py --binary main      # one binary
    tools/asm_in_c.py --json out.json    # machine-readable
    tools/asm_in_c.py --selftest         # prove the detectors on known-true cases (DO THIS FIRST)
    tools/asm_in_c.py --list             # bare "binary function" lines, for piping
"""
import argparse
import collections
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# PsyQ library subsegs: their stubs are byte-identical via LINKED SDK objects, not our source.
LINKED_SEGS = set(
    'apicard1 apicard2 apicard3 apicard4 libc2_1 libc2_2 libcd1 libcd2 libetc libgpu libgs1 libgs2 '
    'libgs3 libgs4 libgs5 libgs6 libgte1 libgte10 libgte11 libgte12 libgte13 libgte14 libgte15 '
    'libgte16 libgte17 libgte18 libgte19 libgte2 libgte20 libgte21 libgte22 libgte3 libgte4 libgte5 '
    'libgte6 libgte7 libgte8 libgte9 libmcrd1 libmcrd2 snd1 snd2 snd3 snd4 snd5 snd6 snd7 snd8 '
    'snd9'.split())

# SDK vs GAME CODE — DERIVED FROM THE ACTUAL PsyQ ARCHIVES, not a hand-written list (R33).
#
# The first cut used a hardcoded set of ~35 names and reported "170 game code". Wrong: the run
# immediately surfaced `VectorNormalSS`, `SquareRoot12`, `OuterProduct12`, `OuterProduct0` as
# "game code" when every one is a libgte routine that simply was not on my list. A hand list cannot
# be complete and its incompleteness silently INFLATES the number that matters most here (how much
# real decompilation work is hiding). We ship the SDK archives, so ask them.
#
# Falls back to a small literal set only if the archives or `nm` are unavailable, and SAYS SO in the
# report rather than pretending the classification is authoritative.
_PSYQ_DIR = os.path.join(REPO, 'tools/psyq/lib40_elf')
_NM = 'mipsel-linux-gnu-nm'
_FALLBACK = set('DisableEvent WaitEvent ReturnFromException SysDeqIntRP GsSortBg GsSortClear '
                'MatrixNormal VectorNormal __main start _clr _drs _dws'.split())


def sdk_names():
    """Every function symbol DEFINED by the shipped PsyQ archives -> (set, provenance string)."""
    import subprocess
    if not os.path.isdir(_PSYQ_DIR):
        return _FALLBACK, 'FALLBACK literal list (no tools/psyq/lib40_elf) — classification is INDICATIVE'
    archives = sorted(f for f in os.listdir(_PSYQ_DIR) if f.lower().endswith('.a'))
    if not archives:
        return _FALLBACK, 'FALLBACK literal list (no archives found) — classification is INDICATIVE'
    names = set()
    for a in archives:
        try:
            r = subprocess.run([_NM, '--defined-only', os.path.join(_PSYQ_DIR, a)],
                               capture_output=True, text=True, timeout=120)
        except (OSError, subprocess.SubprocessError):
            return _FALLBACK, f'FALLBACK literal list ({_NM} unavailable) — classification is INDICATIVE'
        for ln in r.stdout.splitlines():
            parts = ln.split()
            if len(parts) >= 3 and parts[1] in ('T', 't', 'W'):
                names.add(parts[2])
    if not names:
        return _FALLBACK, 'FALLBACK literal list (archives defined no T symbols) — INDICATIVE'
    return names, f'derived from {len(archives)} PsyQ archive(s) in tools/psyq/lib40_elf ({len(names)} symbols)'


SDK_NAMES, SDK_PROVENANCE = sdk_names()

# --- the three detectors -------------------------------------------------------------------------
# Each takes ONE __asm__ block's text and returns the set of function names it believes are DEFINED.
# They are deliberately different shapes so that agreement is evidence and disagreement is a defect.
#
# NOTE the `(?:\\t|\s)+` in every one: the sources use BOTH the escaped tab and a literal space, and
# requiring the `\n` terminator is what stops a bare `".ent\t"` fragment from yielding the name `t`.
RE_ENT = re.compile(r'\.ent(?:\\t|[ \t])+(\w+)\\n')
RE_TYPE = re.compile(r'\.type(?:\\t|[ \t])+(\w+)\s*,\s*@function')
RE_GLOBL = re.compile(r'\.globl(?:\\t|[ \t])+(\w+)\\n')
RE_LABEL = re.compile(r'"(\w+):\\n"')


def detect_ent(txt):
    """`.ent NAME` — the MIPS function-start directive. The most direct evidence."""
    return set(RE_ENT.findall(txt))


def detect_type(txt):
    """`.type NAME, @function` — the ELF symbol-type directive."""
    return set(RE_TYPE.findall(txt))


# DATA-SHAPED NAMES. A `.globl NAME` + `NAME:` pair proves the symbol is EXPORTED, not that it is
# CODE — and jump tables and data blobs are exported too. Caught on the tool's first real run:
# `jtbl_80072ED4/EEC/F0C/F24` were reported as four "functions posing as C" when they are
# SaveLoadRoutine's jump tables sitting in the same §265 block. `.ent` and `.type @function` are
# code-specific and need no such filter; only the weakest detector does (R34 — the disagreement
# between detectors is what exposed this, which is the whole point of running three).
RE_DATA_NAME = re.compile(r'^(?:jtbl_|D_|_?LC?\d|\$L)')


def detect_globl_label(txt):
    """`.globl NAME` AND a `NAME:` label — a definition without the directives.

    Exported-DATA names are excluded (see RE_DATA_NAME): this detector proves export, not code."""
    both = set(RE_GLOBL.findall(txt)) & set(RE_LABEL.findall(txt))
    return {n for n in both if not RE_DATA_NAME.match(n)}


DETECTORS = (('ent', detect_ent), ('type', detect_type), ('globl+label', detect_globl_label))

# A block with any of these and NO definition is inline asm inside a function, not a definition.
RE_BARRIER = re.compile(r'__asm__\s+__volatile__\s*\(\s*""')


def asm_blocks(text):
    """[(start_line, end_line, block_text, is_file_scope)] for every __asm__/asm statement.

    Brace-depth tracking decides file scope, so a block INSIDE a C function (class B or C) is
    distinguished from a file-scope one (class A) without guessing from indentation."""
    lines = text.split('\n')
    out, depth, i, n = [], 0, 0, len(lines)
    while i < n:
        raw = lines[i]
        code = re.sub(r'//.*$', '', raw)
        if re.match(r'\s*(__asm__|asm)\b', code) or re.search(r'\b(__asm__|asm)\s*\(', code):
            start, d2, opened = i, 0, False
            while i < n:
                c = re.sub(r'//.*$', '', lines[i])
                d2 += c.count('(') - c.count(')')
                if '(' in c:
                    opened = True
                i += 1
                if opened and d2 <= 0:
                    break
            blk = '\n'.join(lines[start:i])
            out.append((start + 1, i, blk, depth == 0))
            # a statement inside a function still moves brace depth
            depth += blk.count('{') - blk.count('}')
            continue
        depth += code.count('{') - code.count('}')
        i += 1
    return out


C_SIG = re.compile(r'^[A-Za-z_][\w \*]*\b(\w+)\s*\([^;]*\)\s*\{?\s*$')


def c_functions(text):
    """[(name, start, end, body)] for each C function DEFINITION, by brace matching."""
    lines = text.split('\n')
    out, i, n = [], 0, len(lines)
    while i < n:
        m = C_SIG.match(re.sub(r'//.*$', '', lines[i]).rstrip())
        if m and '(' in lines[i] and not lines[i].lstrip().startswith(('return', 'if', 'while', 'for', 'switch')):
            j, kind = i, None
            while j < n:
                c = re.sub(r'//.*$', '', lines[j])
                br, sm = c.find('{'), c.find(';')
                if br != -1 and (sm == -1 or br < sm):
                    kind = 'def'
                    break
                if sm != -1:
                    kind = 'decl'
                    break
                j += 1
            if kind == 'def':
                start, depth, opened, k = i, 0, False, j
                while k < n:
                    c = re.sub(r'//.*$', '', lines[k])
                    depth += c.count('{') - c.count('}')
                    if '{' in c:
                        opened = True
                    k += 1
                    if opened and depth <= 0:
                        break
                out.append((m.group(1), start + 1, k, '\n'.join(lines[start:k])))
                i = k
                continue
        i += 1
    return out


def strip_comments_and_strings(s):
    """Blank comments and string literals so a body can be tested for REAL C content."""
    s = re.sub(r'/\*.*?\*/', ' ', s, flags=re.S)
    s = re.sub(r'//[^\n]*', ' ', s)
    s = re.sub(r'"(?:\\.|[^"\\])*"', '""', s)
    return s


def scan_file(path, binary):
    """-> (rows, defects). rows are the POSING functions; defects are coverage failures."""
    text = open(path, errors='ignore').read()
    rows, defects = [], []
    if '__asm__' not in text and 'asm(' not in text:
        return rows, defects

    blocks = asm_blocks(text)
    cfuncs = c_functions(text)

    for (ln0, ln1, blk, file_scope) in blocks:
        votes = {name: fn(blk) for name, fn in DETECTORS}
        union = set().union(*votes.values())

        if file_scope and union:
            # CLASS A — a file-scope block that defines functions. Detectors must agree.
            disagree = {n: sorted(v) for n, v in votes.items() if v and v != union}
            for fname in sorted(union):
                agreeing = [n for n, v in votes.items() if fname in v]
                rows.append(dict(binary=binary, fn=fname, cls='A-FILE-SCOPE-VERBATIM',
                                 path=os.path.relpath(path, REPO), line=ln0,
                                 detectors=agreeing, lines=blk.count('\n') + 1))
            if disagree:
                defects.append(f"{os.path.relpath(path, REPO)}:{ln0}: detectors DISAGREE on which "
                               f"functions this block defines: {votes} — resolve before trusting the count")
        elif file_scope and not union:
            # A file-scope asm block that defines nothing is data or a directive island. Only a
            # defect if it looks like it MEANT to define something (R32: never skip silently).
            if re.search(r'\.(ent|globl|type)\b', blk) or RE_LABEL.search(blk):
                defects.append(f"{os.path.relpath(path, REPO)}:{ln0}: file-scope __asm__ carries "
                               f"definition-shaped directives but NO detector claimed a function — "
                               f"a spelling this tool does not know (R43). Inspect it.")

    # CLASS B — a C function whose body is ONLY asm statements.
    for (fname, s0, s1, body) in cfuncs:
        inner = body[body.find('{') + 1:body.rfind('}')]
        has_asm = re.search(r'\b(__asm__|asm)\s*\(', inner)
        if not has_asm:
            continue
        # remove every asm statement, then ask whether any C remains
        rest = re.sub(r'\b(?:__asm__|asm)\b(?:\s+__volatile__)?\s*\([^;]*\)\s*;', ' ',
                      inner, flags=re.S)
        rest = strip_comments_and_strings(rest)
        # declarations alone are not "real C content" for this purpose; a return of a constant is.
        meaningful = re.sub(r'\b(register|volatile|const|static|unsigned|signed|struct|union|'
                            r'char|short|int|long|float|double|void|[su](?:8|16|32|64)|f32)\b', ' ', rest)
        meaningful = re.sub(r'[\s;{}()\[\],*]|(?<![\w.])\w+(?![\w.])', ' ', meaningful).strip()
        if not meaningful and not RE_BARRIER.search(inner):
            rows.append(dict(binary=binary, fn=fname, cls='B-ASM-BODIED-C',
                             path=os.path.relpath(path, REPO), line=s0,
                             detectors=['c-body-is-only-asm'], lines=s1 - s0 + 1))
    return rows, defects


def sources(binary=None):
    out = []
    for root, dirs, files in os.walk(os.path.join(REPO, 'src')):
        for f in files:
            if not f.endswith('.c') or f[:-2] in LINKED_SEGS:
                continue
            rel = os.path.relpath(root, os.path.join(REPO, 'src'))
            b = 'main' if rel == '.' else rel.split(os.sep)[0]
            if binary and b != binary:
                continue
            out.append((os.path.join(root, f), b))
    return sorted(out)


def selftest():
    """Prove the detectors on known-true cases of EVERY spelling before anyone believes a number.

    These are the exact cases that broke four hand counts in one session. If the sources change
    spelling again, this fails LOUDLY rather than silently returning a smaller number."""
    cases = [
        ('tab-spelled  .ent',      '__asm__(\n    ".ent\\tSaveLoadRoutine\\n"\n    "SaveLoadRoutine:\\n");', {'SaveLoadRoutine'}),
        ('space-spelled .ent',     '__asm__(\n    ".ent func_80047D3C\\n"\n    "func_80047D3C:\\n");', {'func_80047D3C'}),
        ('.type @function',        '__asm__(\n    ".type\\tfoo, @function\\n");', {'foo'}),
        ('globl + label',          '__asm__(\n    ".globl\\tbar\\n"\n    "bar:\\n");', {'bar'}),
        ('BARE FRAGMENT (phantom)','__asm__(\n    ".ent\\t"\n);', set()),
        ('barrier is NOT a def',   '__asm__ __volatile__("" ::: "memory");', set()),
        # regression: a jump table is EXPORTED but is not a function (first real run, S75)
        ('jtbl is data, not a fn',  '__asm__(\n    ".globl\\tjtbl_80072ED4\\n"\n    "jtbl_80072ED4:\\n");', set()),
        ('D_ is data, not a fn',    '__asm__(\n    ".globl\\tD_80073140\\n"\n    "D_80073140:\\n");', set()),
    ]
    ok = True
    print('SELFTEST — the detectors against known-true cases:')
    for label, txt, want in cases:
        got = set().union(*[fn(txt) for _, fn in DETECTORS])
        good = got == want
        ok &= good
        print(f"  [{'PASS' if good else 'FAIL'}] {label:26s} want={sorted(want) or '-'} got={sorted(got) or '-'}")
    print('SELFTEST:', 'ALL PASS' if ok else '*** FAILURE — do not trust this tool until fixed ***')
    return 0 if ok else 1


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--binary')
    ap.add_argument('--json')
    ap.add_argument('--list', action='store_true', help='bare "<binary> <function>" lines')
    ap.add_argument('--selftest', action='store_true')
    ap.add_argument('--strict', action='store_true', help='exit non-zero if any coverage defect')
    a = ap.parse_args()

    if a.selftest:
        sys.exit(selftest())

    rows, defects, files = [], [], 0
    for path, b in sources(a.binary):
        r, d = scan_file(path, b)
        rows += r
        defects += d
        files += 1

    if a.list:
        for r in sorted(rows, key=lambda x: (x['binary'], x['fn'])):
            print(f"{r['binary']} {r['fn']}")
        sys.exit(0)

    by_cls = collections.Counter(r['cls'] for r in rows)
    by_bin = collections.Counter(r['binary'] for r in rows)
    sdk = [r for r in rows if r['fn'] in SDK_NAMES]
    game = [r for r in rows if r['fn'] not in SDK_NAMES]

    print(f"ASSEMBLY POSING AS C — {len(rows)} function(s) across {len(by_bin)} binaries "
          f"({files} sources scanned)\n")
    for c, n in sorted(by_cls.items()):
        print(f"  {c:24s} {n:5d}")
    print(f"\n  PsyQ/CRT SDK routines : {len(sdk):5d}   [{SDK_PROVENANCE}]")
    print(f"  GAME CODE — real decompilation work remaining  : {len(game):5d}")
    print(f"\n  by binary:")
    for b, n in by_bin.most_common():
        print(f"    {b:16s} {n:5d}")

    # every row carries WHICH detectors claimed it — a row claimed by only one is weaker evidence
    weak = [r for r in rows if len(r['detectors']) == 1 and r['cls'] == 'A-FILE-SCOPE-VERBATIM']
    if weak:
        print(f"\n  {len(weak)} row(s) claimed by a SINGLE detector (weaker evidence — spot-check these):")
        for r in weak[:8]:
            print(f"    {r['binary']:14s} {r['fn']:24s} {r['detectors']}  {r['path']}:{r['line']}")

    if defects:
        print(f"\n!! {len(defects)} COVERAGE DEFECT(S) — a silent skip is a defect, not a no-op (R32):")
        for d in defects[:12]:
            print(f"   {d}")
    else:
        print(f"\n  coverage: every file-scope __asm__ block classified; 0 defects.")

    if a.json:
        json.dump(rows, open(a.json, 'w'), indent=1)
        print(f"\n-> {a.json}")
    if a.strict and defects:
        sys.exit(1)


if __name__ == '__main__':
    main()
