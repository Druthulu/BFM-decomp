#!/usr/bin/env python3
"""verbatim_check.py — the REGRESSION GUARD for §265 verbatim-`__asm__` bodies. Replaces asm_in_c.py.

WHY THIS IS A GUARD AND NOT A CENSUS (P31 S75, R33: "the best outcome is a DELETED SCANNER").

`tools/asm_in_c.py` existed to DISCOVER this class by parsing `__asm__` blocks. That job is done, and
regex was the wrong instrument for it — five successive censuses returned **116 → 112 → 108 → 178 →
199**, and the classification was worse than the count: it called **154 rows "game code"** when the
authoritative answer is **24**. The real answers came from evidence regex cannot see:

  * the `<OBJ>_OBJ_<hex>` naming key — every one is `placed_PsyQ_object.text_start + hex`, so those
    symbols are OFFSETS INTO LIBRARY OBJECTS, not functions;
  * the PsyQ archive symbol tables in `.run/obj40/`, which keep statics as `W` symbols, so for a
    byte-identical object the archive IS the function map (`checkRECT` = SYS.o+0x52C = func_80059760,
    and NONE of the 44 `SYS_OBJ_*` symbols is a function).

So the taxonomy is now DATA — `config/verbatim_manifest.json`, derived once and committed — and this
tool only answers the one question that recurs: **has the tree drifted from it?** It detects verbatim
bodies (the cheap part, and the only part regex is good at), diffs the names against the manifest,
and fails on:

    NEW      a verbatim body not in the manifest -> someone banked assembly; classify it before
             it becomes invisible work, and NEVER let it inherit a disposition by default
    GONE     a manifest row no longer present    -> decompiled or converted; update the manifest
    MOVED    same name, different file

It deliberately does NOT classify, count units, or judge SDK-vs-game. Those were the wrong answers
last time and they live in the manifest now.

    tools/verbatim_check.py               # diff the tree against the manifest
    tools/verbatim_check.py --strict      # exit 1 on any drift (for tools-health)
    tools/verbatim_check.py --update      # rewrite the manifest's row set from the tree
"""
import argparse
import collections
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MANIFEST = os.path.join(REPO, 'config/verbatim_manifest.json')

LINKED_SEGS = set(
    'apicard1 apicard2 apicard3 apicard4 libc2_1 libc2_2 libcd1 libcd2 libetc libgpu libgs1 libgs2 '
    'libgs3 libgs4 libgs5 libgs6 libgte1 libgte10 libgte11 libgte12 libgte13 libgte14 libgte15 '
    'libgte16 libgte17 libgte18 libgte19 libgte2 libgte20 libgte21 libgte22 libgte3 libgte4 libgte5 '
    'libgte6 libgte7 libgte8 libgte9 libmcrd1 libmcrd2 snd1 snd2 snd3 snd4 snd5 snd6 snd7 snd8 '
    'snd9'.split())

# BOTH spellings, and the `\n` terminator is what stops a bare `".ent\t"` fragment from yielding a
# phantom function literally named `t` (it did, six times). A `.globl`+label pair proves EXPORT, not
# CODE — jump tables are exported too — so it is only trusted for a name that is not data-shaped.
RE_ENT = re.compile(r'\.ent(?:\\t|[ \t])+(\w+)\\n')
RE_TYPE = re.compile(r'\.type(?:\\t|[ \t])+(\w+)\s*,\s*@function')
RE_GLOBL = re.compile(r'\.globl(?:\\t|[ \t])+(\w+)\\n')
RE_LABEL = re.compile(r'"(\w+):\\n"')
RE_DATA_NAME = re.compile(r'^(?:jtbl_|D_|_?LC?\d|\$L)')


def defined_in(block):
    """Function names DEFINED by one `__asm__` block."""
    names = set(RE_ENT.findall(block)) | set(RE_TYPE.findall(block))
    both = set(RE_GLOBL.findall(block)) & set(RE_LABEL.findall(block))
    return names | {n for n in both if not RE_DATA_NAME.match(n)}



def sources(binary=None):
    """[(path, binary)] for every non-LINKED .c in src/. The ONE enumerator (R33)."""
    out = []
    for root, _d, files in os.walk(os.path.join(REPO, 'src')):
        for f in files:
            if not f.endswith('.c') or f[:-2] in LINKED_SEGS:
                continue
            rel = os.path.relpath(root, os.path.join(REPO, 'src'))
            b = 'main' if rel == '.' else rel.split(os.sep)[0]
            if binary and b != binary:
                continue
            out.append((os.path.join(root, f), b))
    return sorted(out)


def asm_blocks(text):
    """[(start_line, end_line, block_text, is_file_scope)] for every __asm__/asm statement.

    Brace-depth tracking decides file scope, so a block INSIDE a function (inline asm, e.g. the §3a
    zero-byte barrier that appears in 3,182 of 4,224 sources) is never mistaken for a definition."""
    lines = text.split('\n')
    out, depth, i, n = [], 0, 0, len(lines)
    while i < n:
        code = re.sub(r'//.*$', '', lines[i])
        if re.search(r'\b(__asm__|asm)\s*\(', code):
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
            depth += blk.count('{') - blk.count('}')
            continue
        depth += code.count('{') - code.count('}')
        i += 1
    return out


DETECTORS = (('defined_in', defined_in),)


def scan_in_function():
    """{(binary, fn): path} for every function whose body is ONE asm statement (declarations aside) — the IN-FUNCTION form of the
    lane (P36 T1b, 2026-09-09): a C shell around a whole routine written in assembly. Detected STRUCTURALLY through
    tools/lever_census.whole_body_asm_functions (the one detector, R33), in every non-LINKED .c and in src/shared/**/*.h (binary
    'shared' — a shared header's routine is instantiated in every includer)."""
    sys.path.insert(0, os.path.join(REPO, 'tools'))
    import lever_census
    found = {}
    files = list(sources())
    shared = os.path.join(REPO, 'src', 'shared')
    for root, _d, fs in os.walk(shared):
        for f in fs:
            if f.endswith('.h'):
                files.append((os.path.join(root, f), 'shared'))
    for path, binary in files:
        text = open(path, errors='ignore').read()
        if '__asm__' not in text and 'asm(' not in text and '__asm(' not in text:
            continue
        rel = os.path.relpath(path, REPO)
        for fn, _line, _blk in lever_census.whole_body_asm_functions(text, rel):
            found[(binary, fn)] = rel
    return found


def scan():
    """{(binary, fn): path} for every file-scope __asm__ body defining a function."""
    found = {}
    for root, _d, files in os.walk(os.path.join(REPO, 'src')):
        for f in files:
            if not f.endswith('.c') or f[:-2] in LINKED_SEGS:
                continue
            path = os.path.join(root, f)
            text = open(path, errors='ignore').read()
            if '__asm__' not in text and 'asm(' not in text:
                continue
            rel = os.path.relpath(root, os.path.join(REPO, 'src'))
            binary = 'main' if rel == '.' else rel.split(os.sep)[0]
            # file scope = brace depth 0; a block inside a function is inline asm, not a definition
            lines, depth, i, n = text.split('\n'), 0, 0, len(text.split('\n'))
            while i < n:
                code = re.sub(r'//.*$', '', lines[i])
                if re.search(r'\b(__asm__|asm)\s*\(', code):
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
                    if depth == 0:
                        for fn in defined_in(blk):
                            found[(binary, fn)] = os.path.relpath(path, REPO)
                    depth += blk.count('{') - blk.count('}')
                    continue
                depth += code.count('{') - code.count('}')
                i += 1
    return found


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--strict', action='store_true', help='exit 1 on any drift')
    ap.add_argument('--update', action='store_true', help='rewrite the manifest row set from the tree')
    a = ap.parse_args()

    if not os.path.exists(MANIFEST):
        sys.exit(f'verbatim_check: {os.path.relpath(MANIFEST, REPO)} is missing — it is the '
                 f'authoritative census and this tool does not recompute one (R33).')
    man = json.load(open(MANIFEST))
    rows = man['rows']
    known = {(r['binary'], r['fn']): r for r in rows}
    # the manifest carries names as they were spelled at derivation; an address is a NUMBER, so
    # compare case-insensitively on the hex (R48 in its case-sensitivity form, measured this session)
    def key(b, fn):
        m = re.match(r'(func_|D_)([0-9A-Fa-f]{8})$', fn)
        return (b, m.group(1) + m.group(2).upper()) if m else (b, fn)
    known_k = {key(*k): v for k, v in known.items()}
    # a row with binary "ov_*" (P36 T1b) covers that routine in EVERY overlay and in the shared headers
    wild = {key('ov_*', r['fn'])[1]: r for r in rows if r['binary'] == 'ov_*'}

    found_file = scan()
    found_in = scan_in_function()
    found = dict(found_file)
    found.update(found_in)
    found_k = {key(*k): v for k, v in found.items()}
    form_of = {key(*k): 'file-scope' for k in found_file}
    form_of.update({key(*k): 'in-function' for k in found_in})

    def covered(k):
        return k in known_k or (k[1] in wild and (k[0].startswith('ov_') or k[0] == 'shared'))

    new = sorted(k for k in found_k if not covered(k))
    gone = sorted(k for k in known_k if k[0] != 'ov_*' and k not in found_k)
    gone += sorted(('ov_*', fn) for fn in wild if not any(fk[1] == fn and (fk[0].startswith('ov_') or fk[0] == 'shared') for fk in found_k))
    moved = sorted(k for k in set(found_k) & set(known_k) if found_k[k] != known_k[k].get('path'))

    n_in = sum(1 for k in found_k if form_of[k] == 'in-function')
    print(f'verbatim bodies in tree: {len(found_k)} ({len(found_k) - n_in} file-scope, {n_in} in-function sites across '
          f'{len({k[1] for k in found_k if form_of[k] == "in-function"})} routines)   manifest rows: {len(known_k)} '
          f'({len(wild)} of them fleet-wide "ov_*" in-function rows)')
    d = collections.Counter((r['disposition'], r.get('form', 'file-scope')) for r in rows)
    for (k, f), v in d.most_common():
        print(f'   {k:22s} {f:12s} {v:4d}')
    print()
    if new:
        print(f'!! {len(new)} NEW verbatim body(ies) NOT in the manifest — assembly was banked and is '
              f'now invisible work. Classify each before it inherits a disposition by default:')
        for b, fn in new[:20]:
            print(f'     {b:14s} {fn:24s} {found_k[(b, fn)]}')
    if gone:
        print(f'-- {len(gone)} manifest row(s) no longer verbatim (decompiled or converted — good; '
              f'update the manifest with --update):')
        for b, fn in gone[:20]:
            print(f'     {b:14s} {fn}')
    if moved:
        print(f'~~ {len(moved)} moved file:')
        for b, fn in moved[:10]:
            print(f'     {b:14s} {fn}: {known_k[(b, fn)].get("path")} -> {found_k[(b, fn)]}')
    if not (new or gone or moved):
        print('no drift — the tree matches the manifest.')

    if a.update:
        # the fleet-wide in-function rows are kept as they are (their dispositions are ratified, not derived)
        keep = [r for r in rows if r['binary'] == 'ov_*' or key(r['binary'], r['fn']) in found_k]
        for b, fn in new:
            keep.append(dict(binary=b, fn=fn, addr=None, nins=None, cls='UNCLASSIFIED',
                             disposition='UNKNOWN', form=form_of.get((b, fn), 'file-scope'), unit_entry=fn, unit_nins=None,
                             path=found_k[(b, fn)], why='added by --update; NEEDS CLASSIFICATION'))
        # the manifest's row ORDER and its non-ASCII text (§, —, ·) are part of the file: the first --update of P36 S103
        # re-sorted every row and escaped every character, a 588-line diff for one removed row. Keep the order, append
        # the new rows, write UTF-8 as it was written (R57 — the instrument's write path is part of the instrument).
        man['rows'] = keep
        with open(MANIFEST, 'w') as fh:
            fh.write(json.dumps(man, indent=1, ensure_ascii=False) + '\n')
        print(f'\nmanifest updated: {len(rows)} -> {len(man["rows"])} rows '
              f'({len(new)} added as UNCLASSIFIED — classify them)')
    if a.strict and (new or gone or moved):
        sys.exit(1)


if __name__ == '__main__':
    main()
