#!/usr/bin/env python3
"""decl_from_use.py — infer a draft's MISSING data extern from the target .s + the draft's own use.

WHY THIS EXISTS (P31 S61; docs/tool-designs/frontier-analysis-s60.md §5 step 4). Two refusal sites
throw away drafts whose only defect is a data symbol the destination TU never declares:
  * aprop_autodraft.py (~:522) refuses `no seed decl for D_x` — the member body is correct, but no
    seed/destination/fleet TU spells the extern, so the A-prop lane never emits the draft;
  * integration_resolver's CC1 `undeclared` class (.run/resolver/undeclared_cases.json) — a
    finished draft dies at the REAL TU with `D_x undeclared (first use this function)`.
The declaration is COMPUTABLE (offline-tooling-first): the function's own target .s states every
access width, sign, index scale and address-take of the symbol, and the draft's C text states the
form of use. This tool derives the minimal C89 extern from those two facts and re-judges.

WHAT IT DOES, per (binary, fn, symbol, draft) case:
  evidence   asm/<binary>/nonmatchings/<split>/<fn>.s, read by a linear register-tracking scan:
             direct %lo accesses (lb/lbu 1, lh/lhu 2, lw/sw 4; lb-vs-lbu / lh-vs-lhu = sign),
             address materializations (addiu ..,%lo(SYM)), index scale (sll k before addu ->
             element size 2**k), pointer-value loads (lw of SYM later used as a base), and
             call-through (an element load feeding jalr -> fn-ptr table). §238: ONLY this binary's
             .s is evidence — overlays share VA ranges, so a same-named symbol elsewhere is not.
  form       how the DRAFT uses the symbol (comment/string-masked): SYM / &SYM / SYM[i] / *SYM /
             SYM(..) / SYM[i](..) / SYM.f / SYM->f / SYM[i][j].
  emit       the MINIMAL C89 extern consistent with both, spelled with the project typedefs
             (include/common.h), inserted at BLOCK scope in every draft function that uses the
             symbol (§8d: a block-scope extern establishes no global, so the TU's own later decls
             cannot hard-conflict; the corpus itself ships block(short) .. file(s32) pairs of the
             same symbol and builds). File scope only when the use itself sits at file scope.
  prefer     an existing spelling of the symbol in THIS binary's own TUs, verbatim, when it agrees
             with the byte evidence (kind+width); when it contradicts the .s (e.g. TU says s32,
             the .s stores sh), the inferred decl wins and the row records the conflict — a wrong
             width is a byte-DIFF, not an error, and rtu adjudicates (the TU decl is then a
             splice-ORDERING fact, noted, not adopted).
  judge      rtu_match against the real split TU (whole-TU compile, §42b); on a byte-DIFF, walk a
             small CANDIDATE LADDER (a sign-conflicting same-binary spelling, then the sign flip —
             a draft may cast some uses, so the access sign does not fix the decl sign; both
             directions byte-witnessed) and re-judge, max 4 compiles; on MATCH, reloc_identity
             (R34 second oracle). Slate = MATCH + AGREE only. This tool NEVER gates; the
             whole-binary SHA gate stays the sole arbiter (G3/P9).

REFUSALS (R43) — loud, classed, one ledger row per case (R32, nothing silent):
  NOT-A-STUB / DRAFT-MISSING / NEEDS-TU-EDIT / MAIN / CORPUS-ERROR   the resolver's own classes
  TU-BROKEN        the DESTINATION TU fails cc1 with NO draft spliced (validation compile, cached
                   per TU): the `undeclared` diagnostic belongs to the TU, not the draft. 39/42 of
                   the measured cases are ONE such TU (ov_SC04_018_jr_8017AE2C.c, RED since commit
                   commit:2833 restored func_8017E7CC without its `extern s32 D_801B9AA8;`).
  FUNCTION         the symbol is a jal target / func_ name — a callee tool's class, not data
  STRUCT           the use needs a struct type (SYM.f / SYM->f / SYM[i].f / SYM[i][j]) — the
                   A-prop lane's separate STRUCT class
  UNKNOWN-SYMBOL   the name resolves to no address in THIS binary's symbol files and is not a
                   splat-derived name — no declaration can make it link
  NO-EVIDENCE      the target .s never touches the symbol
  WIDTH-CONFLICT / SIGN-CONFLICT / STRUCT-SHAPE    conflicting evidence at one symbol (spec:
                   "refuse on conflicting width evidence"); STRUCT-SHAPE = an indexed element
                   larger than its accesses, or multi-offset multi-width — a struct in disguise
  OTHER-DIAG       after declaring, cc1 still fails OUTSIDE the spliced draft — not this class

NEGATIVE CONTROL FIRST (R39/R35): --negative-control N re-infers N ground-truth triples — a BANKED
function's own block-scope `extern .. D_x ..;` in src/<binary>/*.c whose original .s survives under
asm/<binary>/nonmatchings/*/ — through the SAME inference path (spelling tiers disabled) and scores
kind/width/sign agreement with denominators (R41). A tool that guesses wrong decls silently
manufactures byte-DIFFs; do not believe an inference whose control disagrees.

Usage:
  tools/decl_from_use.py --negative-control 500
  tools/decl_from_use.py --cases .run/resolver/undeclared_cases.json -j 8
  # outputs under --out-dir (.run/decl_from_use):
  #   <binary>/<fn>.c            the fixed draft (a COPY; the input draft is never edited)
  #   verdicts.jsonl             one row per case: decls, evidence, rtu verdict, reloc, refusals
  #   slate.json                 [{"fn","binary","draft"}] for rtu-MATCH + reloc-AGREE only
  #   negative_control.jsonl / negative_control_summary.json
"""
import argparse
import collections
import glob
import json
import os
import random
import re
import struct
import subprocess
import sys
import threading
import time
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cdecl                                                             # noqa: E402
import corpus                                                            # noqa: E402
import integration_resolver as IR                                        # noqa: E402
from reloc_identity import resolve_name                                  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# The build's own pipeline, verbatim from tools/rtu_match.py / Makefile (docs/SETUP.md §5.4).
CPP = 'mipsel-linux-gnu-cpp'
CC1 = 'tools/bin/gcc-2.7.2-psx/cc1'
CPPFLAGS = ('-lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ '
            '-Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C').split()


def cc1flags(o0):
    return ('-quiet %s -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker'
            % ('-O0' if o0 else '-O2')).split()


_print_lock = threading.Lock()


def say(*a):
    with _print_lock:
        print('[%s] [decl_from_use] %s' % (time.strftime('%H:%M:%S'),
                                           ' '.join(str(x) for x in a)), flush=True)


# =================================================================================================
# 1. the .s evidence collector — a linear register-tracking scan over the target assembly
# =================================================================================================
_S_LINE = re.compile(r'^\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*\*/\s+(\S+)\s*(.*)$')
_SYMREF = re.compile(r'%(hi|lo)\(\s*([A-Za-z_]\w*)\s*(?:([+-])\s*(0x[0-9A-Fa-f]+|\d+))?\s*\)')
_JAL_T = re.compile(r'^\s*/\*[^*]*\*/\s+jal\s+([A-Za-z_]\w*)')

_LOADS = {32: (1, 's', 'lb'), 33: (2, 's', 'lh'), 35: (4, 'n', 'lw'),
          36: (1, 'u', 'lbu'), 37: (2, 'u', 'lhu')}
_PARTIAL = {34: 'lwl', 38: 'lwr', 42: 'swl', 46: 'swr'}          # unaligned word halves: width 4
_STORES = {40: (1, 'sb'), 41: (2, 'sh'), 43: (4, 'sw')}
CALLER_SAVED = set(range(1, 16)) | {24, 25, 31}                  # $at,$v*,$a*,$t0-9,$ra


def _decode(w):
    """One MIPS-I word -> a small dict. Only the fields this scan consumes."""
    op = w >> 26
    rs, rt, rd, sa, fn = (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, (w >> 6) & 31, w & 63
    imm = w & 0xFFFF
    if imm & 0x8000:
        imm -= 0x10000
    d = {'op': op, 'rs': rs, 'rt': rt, 'rd': rd, 'sa': sa, 'fn': fn, 'imm': imm,
         'dest': None, 'cls': 'other', 'width': None, 'sign': None, 'call': False}
    if op == 0:
        if fn in (0, 2, 3, 4, 6, 7):
            d.update(dest=rd, cls='shift' if fn in (0, 2, 3) else 'shiftv')
            if fn == 0:
                d['cls'] = 'sll'
        elif fn == 9:
            d.update(dest=rd, cls='jalr', call=True)
        elif fn in (16, 18):
            d.update(dest=rd)                                    # mfhi/mflo
        elif fn in (32, 33, 37):                                 # add/addu/or (move-capable)
            d.update(dest=rd, cls='addu')
        elif fn in (34, 35, 36, 38, 39):
            d.update(dest=rd)                                    # sub/subu/and/xor/nor
        elif fn in (42, 43):
            d.update(dest=rd, cls='slt' if fn == 42 else 'sltu')
        elif fn == 8:
            d['cls'] = 'jr'
        elif fn in (24, 25):
            d['cls'] = 'mult' if fn == 24 else 'multu'
        elif fn in (26, 27):
            d['cls'] = 'div' if fn == 26 else 'divu'
    elif op == 3:
        d.update(dest=31, cls='jal', call=True)
    elif op == 1 and rt in (16, 17):
        d.update(dest=31, call=True)                             # bltzal/bgezal
    elif op in (8, 9):
        d.update(dest=rt, cls='addiu')
    elif op in (10, 11):
        d.update(dest=rt, cls='slti' if op == 10 else 'sltiu')
    elif op in (12, 13, 14):
        d.update(dest=rt)                                        # andi/ori/xori
    elif op == 15:
        d.update(dest=rt, cls='lui')
    elif op in _LOADS:
        w_, s_, _ = _LOADS[op]
        d.update(dest=rt, cls='load', width=w_, sign=s_)
    elif op in _STORES:
        w_, _ = _STORES[op]
        d.update(cls='store', width=w_)
    elif op in _PARTIAL:
        d.update(cls='partial', width=4, dest=(rt if op in (34, 38) else None))
    elif op in (16, 17, 18, 19):
        if rs in (0, 2):
            d.update(dest=rt)                                    # mfcz/cfcz
    elif op in (48, 49, 50, 51, 56, 57, 58, 59):
        d['cls'] = 'copmem'                                      # lwcz/swcz: mem op, cop dest
    return d


def collect(s_path, binary=None):
    """Read one target .s -> {symbol: evidence}. Evidence keys:
       direct   [(width, sign, is_store, off, line)]   memory op at %lo(SYM+off)(hi-base)
       addr     [(off, line)]                          addiu ..,%lo(SYM+off) address-take
       derived  [(k, width, sign, is_store, indexed, scale, line)]  access through the address
       deref    [(k, width, sign, is_store, indexed, scale, line)]  access through a LOADED value
       jal      [line]                                 the symbol is a call target
       jalr_via n                                      an element loaded from SYM fed jalr
       u_hint/s_hint n                                 sltu/srl/divu vs slt/sra/div on a loaded word
    """
    syms = corpus.symbols(binary) if binary else {}

    def addr_of(name, off):
        base = resolve_name(name, syms)
        return None if base is None else (base + off) & 0xFFFFFFFF

    ev = collections.defaultdict(lambda: {'direct': [], 'addr': [], 'derived': [], 'deref': [],
                                          'jal': [], 'jalr_via': 0, 'u_hint': 0, 's_hint': 0})
    hi, ptr, shift, lval = {}, {}, {}, {}
    hiix = {}                    # reg -> index scale: the reg holds %hi(SYM) PLUS an index
    pending_clobber = False
    in_text, seen_section = True, False

    def invalidate(r):
        for m in (hi, ptr, shift, lval, hiix):
            m.pop(r, None)

    def clobber():
        for r in CALLER_SAVED:
            invalidate(r)

    for raw in open(os.path.join(REPO, s_path), errors='replace'):
        sec = re.match(r'\s*\.section\s+([.\w]+)', raw)
        if sec:
            seen_section = True
            in_text = sec.group(1).startswith('.text')
            continue
        if not in_text:
            continue
        m = _S_LINE.match(raw)
        if not m:
            continue                                             # labels, directives, glabel
        # the comment shows the four bytes in MEMORY order (little-endian) — swap, as insns_from_s does
        word, mnem, ops = struct.unpack('<I', bytes.fromhex(m.group(1)))[0], m.group(2), m.group(3)
        if mnem.startswith('.'):
            continue                                             # .word etc. riding in .text
        was_pending, pending_clobber = pending_clobber, False
        d = _decode(word)
        line = ('%s %s' % (mnem, ops)).strip()
        refs = {g[0]: (g[1], (int(g[3], 0) if g[3] else 0) * (-1 if g[2] == '-' else 1))
                for g in _SYMREF.findall(ops)}                   # 'hi'/'lo' -> (sym, off)

        jm = _JAL_T.match(raw)
        if jm and d['cls'] == 'jal':
            ev[jm.group(1)]['jal'].append(line)

        if d['cls'] == 'lui' and 'hi' in refs:
            invalidate(d['dest'])                                # also clears any hiix
            hi[d['dest']] = refs['hi']
        elif d['cls'] == 'addiu' and 'lo' in refs:
            s, off = refs['lo']
            base_ok = hi.get(d['rs'], (None,))[0] == s
            if not base_ok and d['rs'] in hi:                    # paired lui names another symbol;
                a1 = addr_of(hi[d['rs']][0], hi[d['rs']][1])     # accept if the hi halves agree
                a2 = addr_of(s, off)
                base_ok = (a1 is not None and a2 is not None and
                           ((a1 + 0x8000) >> 16) == ((a2 + 0x8000) >> 16))
            invalidate(d['dest'])
            if base_ok:
                ptr[d['dest']] = (s, off, False, None, 'addr')
                ev[s]['addr'].append((off, line))
        elif d['cls'] in ('load', 'store', 'partial', 'copmem'):
            is_store = d['cls'] == 'store' or (d['cls'] == 'partial' and d['dest'] is None) \
                       or (d['cls'] == 'copmem' and (word >> 26) >= 56)
            width = d['width'] or 4
            sign = d['sign']
            base = d['rs']
            kept_lval = False
            if 'lo' in refs:
                s, off = refs['lo']
                hs = hi.get(base, (None,))[0]
                ok = hs == s
                if not ok and hs is not None:
                    a1, a2 = addr_of(hs, hi[base][1]), addr_of(s, off)
                    ok = (a1 is not None and a2 is not None and
                          ((a1 + 0x8000) >> 16) == ((a2 + 0x8000) >> 16))
                if ok:
                    if base in hiix:     # lui %hi + addu idx + mem %lo — an INDEXED direct access
                        ev[s]['derived'].append((off, width, sign, is_store, True, hiix[base],
                                                 line))
                    else:
                        ev[s]['direct'].append((width, sign, is_store, off, line))
                        if d['dest'] is not None and d['cls'] == 'load' and width == 4:
                            invalidate(d['dest'])
                            lval[d['dest']] = (s, off, 'direct')
                            kept_lval = True
            elif base in ptr:
                s, off, indexed, scale, src = ptr[base]
                key = 'derived' if src == 'addr' else 'deref'
                ev[s][key].append((off + d['imm'], width, sign, is_store, indexed, scale, line))
            elif base in lval:
                s, off, _src = lval[base]
                ev[s]['deref'].append((d['imm'], width, sign, is_store, False, None, line))
            if d['dest'] is not None and not kept_lval:
                invalidate(d['dest'])
        elif d['cls'] == 'addu':
            a, b_ = d['rs'], d['rt']
            if a == 0 or b_ == 0:                                # a move
                src = b_ if a == 0 else a
                invalidate(d['dest'])
                if src in hi:
                    hi[d['dest']] = hi[src]
                if src in ptr:
                    ptr[d['dest']] = ptr[src]
                if src in lval:
                    lval[d['dest']] = lval[src]
                if src in shift:
                    shift[d['dest']] = shift[src]
            elif a in hi or b_ in hi:
                # the gcc indexed-global idiom: the index is added to the HI half, BEFORE %lo
                #   lui $at,%hi(S) ; addu $at,$at,$idx ; lw .., %lo(S)($at)
                # CHECKED BEFORE ptr/lval: only a %hi symbol half can be in `hi`, and hi+hi is
                # nonsense — but the OTHER operand is frequently a loaded word (in lval), and the
                # lval branch would mis-attribute the access to the loaded-from symbol and drop
                # the hi half (the ov_SC06_010 func_801804B0 control miss).
                pr, ir = (a, b_) if a in hi else (b_, a)
                h = hi[pr]
                sc = (1 << shift[ir]) if ir in shift else None
                invalidate(d['dest'])
                hi[d['dest']] = h
                hiix[d['dest']] = sc
            elif a in ptr or b_ in ptr:
                pr, ir = (a, b_) if a in ptr else (b_, a)
                s, off, _ix, _sc, src = ptr[pr]
                sc = (1 << shift[ir]) if ir in shift else None
                invalidate(d['dest'])
                ptr[d['dest']] = (s, off, True, sc, src)
            elif a in lval or b_ in lval:
                pr, ir = (a, b_) if a in lval else (b_, a)
                s, off, _src = lval[pr]
                sc = (1 << shift[ir]) if ir in shift else None
                invalidate(d['dest'])
                ptr[d['dest']] = (s, off, True, sc, 'load')
            else:
                invalidate(d['dest'])
        elif d['cls'] == 'addiu':                                # numeric addiu: walk a pointer
            src = d['rs']
            invalidate(d['dest'])
            if src in ptr:
                s, off, ix, sc, so = ptr[src]
                ptr[d['dest']] = (s, off + d['imm'], ix, sc, so)
            elif src in lval:
                s, off, so = lval[src]
                lval[d['dest']] = (s, off + d['imm'], so)
        elif d['cls'] == 'sll':
            if d['dest']:
                invalidate(d['dest'])
                shift[d['dest']] = d['sa']
        elif d['cls'] in ('sltu', 'slt', 'slti', 'sltiu', 'div', 'divu', 'mult', 'multu', 'shift',
                          'shiftv'):
            for r in (d['rs'], d['rt']):
                if r in lval:
                    s = lval[r][0]
                    if d['cls'] in ('sltu', 'sltiu', 'divu', 'multu') or \
                       (d['cls'] == 'shift' and (word & 63) == 2):        # srl
                        ev[s]['u_hint'] += 1
                    elif d['cls'] in ('slt', 'slti', 'div') or \
                            (d['cls'] == 'shift' and (word & 63) == 3):   # sra
                        ev[s]['s_hint'] += 1
            if d['dest'] is not None:
                invalidate(d['dest'])
        elif d['cls'] == 'jalr':
            if d['rs'] in lval or d['rs'] in ptr:
                s = (lval.get(d['rs']) or ptr.get(d['rs']))[0]
                ev[s]['jalr_via'] += 1
            if d['dest'] is not None:
                invalidate(d['dest'])
        else:
            if d['dest'] is not None:
                invalidate(d['dest'])

        if was_pending:
            clobber()
        if d['call']:
            pending_clobber = True
    return dict(ev), seen_section


# =================================================================================================
# 2. how the draft's C text uses the symbol
# =================================================================================================
def _skip_ws(t, i, step=1):
    while 0 <= i < len(t) and t[i] in ' \t\n':
        i += step
    return i


def _match_bracket(t, i):
    """i at '['; return index just past the matching ']' (or len)."""
    depth = 0
    while i < len(t):
        if t[i] == '[':
            depth += 1
        elif t[i] == ']':
            depth -= 1
            if depth == 0:
                return i + 1
        i += 1
    return i


def usage_forms(masked, sym):
    """Set of forms in {PLAIN, ADDR, SUBSCRIPT, DEREF, MEMBER, CALL, FNPTR_ARRAY_CALL, SUBSCRIPT2,
    CALL_VALUE_USED}. `masked` must have comments/strings blanked and decl statements blanked."""
    forms = set()
    for m in re.finditer(r'\b%s\b' % re.escape(sym), masked):
        i = _skip_ws(masked, m.start() - 1, -1)
        before = masked[i] if i >= 0 else ''
        j = _skip_ws(masked, m.end())
        after = masked[j] if j < len(masked) else ''
        if after == '[':
            k = _match_bracket(masked, j)
            n = _skip_ws(masked, k)
            nxt2 = masked[n:n + 2]
            if nxt2[:1] == '.' or nxt2 == '->':
                forms.add('MEMBER')
            elif nxt2[:1] == '(':
                forms.add('FNPTR_ARRAY_CALL')
                if _call_value_used(masked, m.start()):
                    forms.add('CALL_VALUE_USED')
            elif nxt2[:1] == '[':
                forms.add('SUBSCRIPT2')
            else:
                forms.add('SUBSCRIPT')
        elif after == '.' or masked[j:j + 2] == '->':
            forms.add('MEMBER')
        elif after == '(':
            forms.add('CALL')
            if _call_value_used(masked, m.start()):
                forms.add('CALL_VALUE_USED')
        elif before == '&':
            forms.add('ADDR')
        elif before == '*':
            i2 = _skip_ws(masked, i - 1, -1)
            prev = masked[i2] if i2 >= 0 else ''
            forms.add('PLAIN' if (prev.isalnum() or prev in ')]_') else 'DEREF')
        else:
            forms.add('PLAIN')
    return forms


def _call_value_used(masked, pos):
    """Is the call expression at `pos` used as a value (assigned / returned / compared)?"""
    i = _skip_ws(masked, pos - 1, -1)
    while i >= 0 and masked[i] in '*&([':
        i = _skip_ws(masked, i - 1, -1)
    if i < 0:
        return False
    if masked[i] in '=<>!+-/%|^,':
        return not (masked[i] == '=' and i > 0 and masked[i - 1] in '=!<>')
    return bool(re.search(r'\breturn$', masked[max(0, i - 6):i + 1]))


def blank_decl_statements(text):
    """Blank every `extern`/`typedef`-leading statement (file and one block level) so a decl's own
    mention of the symbol is not read as a use. Length-preserving."""
    masked = cdecl._mask(text)
    if len(masked) != len(text):
        masked = text
    out = list(masked)

    def blank_spans(seg_text, seg_off):
        try:
            stmts = cdecl.split_statements(seg_text)
        except Exception:
            return []
        return [(seg_off + s.start, seg_off + s.end) for s in stmts
                if re.match(r'\s*(extern|typedef|INCLUDE_ASM)\b', s.text)]

    spans = blank_spans(masked, 0)
    for st in cdecl.split_statements(masked):
        mb = re.search(r'\{', st.text)
        if not mb:
            continue
        head = st.text[:mb.start()]
        if re.match(r'\s*(typedef|struct|union|enum)\b', head) or ')' not in head:
            continue
        off = st.start + mb.end()
        spans += blank_spans(masked[off:st.end], off)
    for a, b in spans:
        for i in range(a, min(b, len(out))):
            if out[i] != '\n':
                out[i] = ' '
    return ''.join(out)


# =================================================================================================
# 3. inference: (evidence, forms) -> a minimal C89 extern, or a refusal
# =================================================================================================
TYPE = {(1, 's'): 's8', (1, 'u'): 'u8', (2, 's'): 's16', (2, 'u'): 'u16',
        (4, 's'): 's32', (4, 'u'): 'u32'}


class Refuse(Exception):
    def __init__(self, cls, note):
        self.cls, self.note = cls, note
        super().__init__('%s: %s' % (cls, note))


def flip_sign(res, sym):
    """The sign-flipped spelling of an inferred decl, or None. The .s access sign is evidence about
    the ACCESSES; a draft may cast some uses, so the decl sign the UNCAST uses need can be the other
    one (both directions byte-witnessed in the selftest: func_801E2D34 wants u16 where a sibling TU
    spells s16, func_801EE730 wants s16 under lhu evidence). Not statically decidable — offer the
    alternate and let rtu adjudicate."""
    if res['width'] not in (1, 2, 4) or res['kind'] not in ('scalar', 'array', 'ptr'):
        return None
    t = TYPE[(res['width'], 'u' if (res['sign'] or 's') == 's' else 's')]
    return {'scalar': 'extern %s %s;', 'array': 'extern %s %s[];',
            'ptr': 'extern %s *%s;'}[res['kind']] % (t, sym)


def _consolidate(accs, tag):
    """[(width, sign)] -> (width, sign, flags). Refuses on conflicting width / sign evidence."""
    widths = sorted({w for w, _s in accs})
    if len(widths) > 1:
        raise Refuse('WIDTH-CONFLICT', '%s widths %s at one symbol' % (tag, widths))
    signs = {s for _w, s in accs if s in ('s', 'u')}
    if len(signs) > 1:
        raise Refuse('SIGN-CONFLICT', '%s: both lb/lh and lbu/lhu observed' % tag)
    return widths[0], (signs.pop() if signs else None)


def infer(sym, ev, forms):
    """-> dict(kind, width, sign, decl, flags, why). Raises Refuse."""
    e = ev.get(sym)
    if e and e['jal']:
        raise Refuse('FUNCTION', 'jal target in the .s: %s' % e['jal'][0])
    if 'MEMBER' in forms or 'SUBSCRIPT2' in forms:
        raise Refuse('STRUCT', 'draft uses %s — needs a struct/2-D type (aprop STRUCT class)'
                     % ('member access' if 'MEMBER' in forms else 'a 2-D subscript'))
    if re.match(r'func_[0-9A-Fa-f]{6,8}$', sym):
        raise Refuse('FUNCTION', 'func_-shaped symbol — a callee, not data')
    if not e or not (e['direct'] or e['addr'] or e['derived'] or e['deref']):
        raise Refuse('NO-EVIDENCE', 'the target .s never touches %s' % sym)

    flags, why = [], []
    direct = [(w, s) for (w, s, _st, off, _l) in e['direct']]
    d_offs = sorted({off for (_w, _s, _st, off, _l) in e['direct']})
    derived = e['derived']
    deref = e['deref']

    # call-through: an element/value of SYM feeds jalr -> function-pointer storage
    if e['jalr_via'] or 'FNPTR_ARRAY_CALL' in forms or ('CALL' in forms and (deref or direct)):
        ret = 's32' if 'CALL_VALUE_USED' in forms else 'void'
        if 'FNPTR_ARRAY_CALL' in forms or 'SUBSCRIPT' in forms or derived:
            decl = 'extern %s (*%s[])();' % (ret, sym)
            kind = 'fnptr_array'
        else:
            decl = 'extern %s (*%s)();' % (ret, sym)
            kind = 'fnptr'
        why.append('call-through (jalr_via=%d)' % e['jalr_via'])
        return {'kind': kind, 'width': 4, 'sign': None, 'decl': decl, 'flags': flags, 'why': why}
    if 'CALL' in forms:
        raise Refuse('FUNCTION', 'draft calls %s() and the .s shows no data-load call-through' % sym)

    def elem_from(accs, tag):
        pairs = [(w, s) for (_k, w, s, _st, _ix, _sc, _l) in accs]
        w, s = _consolidate(pairs, tag)
        scales = {sc for (_k, _w, _s, _st, ix, sc, _l) in accs if ix and sc}
        for sc in scales:
            if sc == w:
                continue
            if sc % w == 0:
                # scale = width x K is compatible with elem=width and a C index the DRAFT itself
                # scales (SYM[i*K] -> one sll of log2(w*K)); a struct elem would need MEMBER use,
                # which usage_forms refuses separately. The gate arbitrates either way.
                flags.append('scaled-index-x%d' % (sc // w))
                continue
            raise Refuse('STRUCT-SHAPE', 'index scale %d not a multiple of access width %d '
                         '(element is a struct)' % (sc, w))
        offs = sorted({k for (k, _w, _s, _st, ix, _sc, _l) in accs if not ix})
        if offs and any(k % w for k in offs):
            raise Refuse('STRUCT-SHAPE', 'offsets %s not multiples of width %d' % (offs[:4], w))
        return w, s

    if 'SUBSCRIPT' in forms:
        if derived or e['addr'] or (direct and (len(d_offs) > 1 or d_offs != [0])):
            if derived:
                w, s = elem_from(derived, 'indexed')
            elif direct:
                w, s = _consolidate(direct, 'direct')
            else:
                w, s = 1, None
                flags.append('elem-default-u8')
            t = TYPE[(w, s or 's')]
            if s is None:
                flags.append('sign-default')
            why.append('array: %d derived + %d direct + %d addr accesses'
                       % (len(derived), len(direct), len(e['addr'])))
            return {'kind': 'array', 'width': w, 'sign': s,
                    'decl': 'extern %s %s[];' % (t, sym), 'flags': flags, 'why': why}
        if deref:                                                # SYM holds a pointer, draft indexes it
            w, s = elem_from(deref, 'pointer-deref')
            t = TYPE[(w, s or 's')]
            if s is None:
                flags.append('sign-default')
            why.append('pointer: value of %s used as an indexed base' % sym)
            return {'kind': 'ptr', 'width': w, 'sign': s,
                    'decl': 'extern %s *%s;' % (t, sym), 'flags': flags, 'why': why}
        w, s = _consolidate(direct, 'direct')
        why.append('array (subscripted; direct accesses only)')
        return {'kind': 'array', 'width': w, 'sign': s,
                'decl': 'extern %s %s[];' % (TYPE[(w, s or 's')], sym), 'flags': flags, 'why': why}

    if 'DEREF' in forms:
        if not deref:
            raise Refuse('NO-EVIDENCE', 'draft derefs *%s but the .s shows no load-then-deref' % sym)
        w, s = elem_from(deref, 'pointer-deref')
        if s is None:
            flags.append('sign-default')
        why.append('pointer deref')
        return {'kind': 'ptr', 'width': w, 'sign': s,
                'decl': 'extern %s *%s;' % (TYPE[(w, s or 's')], sym), 'flags': flags, 'why': why}

    # PLAIN / ADDR
    if direct:
        if len(d_offs) > 1:
            widths = {w for w, _s in direct}
            if len(widths) > 1:
                raise Refuse('STRUCT-SHAPE', 'multi-offset multi-width direct accesses %s'
                             % d_offs[:4])
            w = widths.pop()
            if any(off % w for off in d_offs):
                raise Refuse('STRUCT-SHAPE', 'direct offsets %s not multiples of %d'
                             % (d_offs[:4], w))
            _w, s = _consolidate(direct, 'direct')
            why.append('array (direct accesses at offsets %s)' % d_offs[:4])
            return {'kind': 'array', 'width': w, 'sign': s,
                    'decl': 'extern %s %s[];' % (TYPE[(w, s or 's')], sym),
                    'flags': flags, 'why': why}
        w, s = _consolidate(direct, 'direct')
        if w == 4 and s is None:
            if e['u_hint'] and not e['s_hint']:
                s = 'u'
                why.append('u32 (unsigned compare/shift on the loaded value)')
            else:
                s = None
        t = TYPE[(w, s or 's')]
        if s is None:
            flags.append('sign-default')
        why.append('scalar: %d direct accesses, width %d' % (len(direct), w))
        return {'kind': 'scalar', 'width': w, 'sign': s,
                'decl': 'extern %s %s;' % (t, sym), 'flags': flags, 'why': why}

    # address-only evidence
    if derived:
        try:
            w, s = elem_from(derived, 'via-address')
        except Refuse:
            raise
        if 'ADDR' in forms and not e['addr']:
            pass
        if 'PLAIN' in forms and 'ADDR' not in forms:
            why.append('decayed array (address materialized; element from derived accesses)')
            if s is None:
                flags.append('sign-default')
            if 'SUBSCRIPT' not in forms:
                # the draft only DECAYS the array — the element type touches nothing but the
                # pointer-assignment conversion (a gcc-2.7.2 warning), so a different spelling
                # in the TU is byte-neutral
                flags.append('decay-elem')
            return {'kind': 'array', 'width': w, 'sign': s,
                    'decl': 'extern %s %s[];' % (TYPE[(w, s or 's')], sym),
                    'flags': flags, 'why': why}
        why.append('scalar whose address is taken (derived width %d)' % w)
        if s is None:
            flags.append('sign-default')
        return {'kind': 'scalar', 'width': w, 'sign': s,
                'decl': 'extern %s %s;' % (TYPE[(w, s or 's')], sym), 'flags': flags, 'why': why}
    if 'ADDR' in forms:
        flags += ['width-default-s32']
        why.append('&%s only; no access width anywhere — type is byte-neutral for a pure '
                   'address-take' % sym)
        return {'kind': 'scalar', 'width': None, 'sign': None,
                'decl': 'extern s32 %s;' % sym, 'flags': flags, 'why': why}
    flags += ['elem-default-u8']
    why.append('decayed array (address materialized, no access width) — element type byte-neutral')
    return {'kind': 'array', 'width': None, 'sign': None,
            'decl': 'extern u8 %s[];' % sym, 'flags': flags, 'why': why}


# =================================================================================================
# 4. same-binary spelling tier (cases only; §238 keeps this INSIDE one binary)
# =================================================================================================
_PRIM_WIDTH = {'char': (1, 's'), 'signed char': (1, 's'), 'unsigned char': (1, 'u'),
               'short': (2, 's'), 'unsigned short': (2, 'u'),
               'int': (4, 's'), 'long': (4, 's'), 'unsigned int': (4, 'u'),
               'unsigned long': (4, 'u'), 'void': (None, None), 'float': (4, 'f')}


def decl_shape(d):
    """cdecl.Declarator -> (kind, width, sign) with kind in scalar/array/ptr/fnptr/fnptr_array/func;
    width None for non-primitive bases."""
    prim = cdecl._prim(d.base)
    w, s = _PRIM_WIDTH.get(prim, (None, None))
    return d.kind, w, s


_spell_cache = {}


def binary_spellings(binary, sym):
    """Every parsed `extern` declaration of `sym` in THIS binary's own .c files (any scope) —
    a spelling source, not a scope model. Cached per binary+symbol."""
    key = (binary, sym)
    if key in _spell_cache:
        return _spell_cache[key]
    out = []
    for p in corpus.src_files(binary):
        try:
            txt = open(p, errors='replace').read()
        except OSError:
            continue
        for i, line in enumerate(txt.split('\n'), 1):
            if 'extern' not in line or sym not in line:
                continue
            mm = re.match(r'\s*extern\b[^;{}]*;\s*(?:\\\s*)?$', line)
            if not mm or not re.search(r'\b%s\b' % re.escape(sym), line):
                continue
            try:
                for d in cdecl.parse(line.strip().rstrip('\\').strip()):
                    if d.name == sym:
                        out.append((os.path.relpath(p, REPO), i, d))
            except cdecl.CDeclError:
                continue
    _spell_cache[key] = out
    return out


# =================================================================================================
# 5. draft surgery: find function bodies, insert block-scope externs
# =================================================================================================
def defs_in(text):
    """[{name, brace, body_start, body_end}] for every function definition in the draft."""
    out = []
    masked = cdecl._mask(text)
    if len(masked) != len(text):
        masked = text
    for st in cdecl.split_statements(text):
        seg = masked[st.start:st.end]
        mb = re.search(r'\{', seg)
        if not mb:
            continue
        head = seg[:mb.start()]
        if re.match(r'\s*(typedef|struct|union|enum)\b', head) or ')' not in head:
            continue
        hm = re.search(r'\b([A-Za-z_]\w*)\s*\([^;{]*\)\s*(?:[^{;]*;\s*)*$', head, re.S)
        if not hm:
            continue
        out.append({'name': hm.group(1), 'brace': st.start + mb.start(),
                    'body_start': st.start + mb.end(), 'body_end': st.end})
    return out


def insert_decls(text, decls_by_sym):
    """Insert each decl at block scope inside every function whose body uses the symbol; file scope
    (top of draft) when a use sits outside every body. Returns new text."""
    blanked = blank_decl_statements(text)
    funcs = defs_in(text)
    ins = collections.defaultdict(list)                          # insertion offset -> [decl]
    top = []
    for sym, decl in decls_by_sym.items():
        placed = False
        spans = []
        for f in funcs:
            body = blanked[f['body_start']:f['body_end']]
            if re.search(r'\b%s\b' % re.escape(sym), body):
                ins[f['body_start']].append(decl)
                placed = True
            spans.append((f['body_start'], f['body_end']))
        outside = blanked
        for a, b in spans:
            outside = outside[:a] + ' ' * (b - a) + outside[b:]
        if re.search(r'\b%s\b' % re.escape(sym), outside) or not placed:
            top.append(decl)
    pieces, pos = [], 0
    for off in sorted(ins):
        pieces.append(text[pos:off])
        pieces.append('\n' + ''.join('    %s\n' % d for d in ins[off]))
        pos = off
    pieces.append(text[pos:])
    body = ''.join(pieces)
    if top:
        body = ''.join('%s\n' % d for d in top) + '\n' + body
    return body


# =================================================================================================
# 6. TU validation compile (the TU-BROKEN pre-check) — cached per TU
# =================================================================================================
_tu_cache, _tu_lock = {}, threading.Lock()


def tu_compiles(binary, tu_relpath):
    """(ok, first_diag_lines) — cpp+cc1 the TU IN PLACE with -DINCLUDE_ASM(a,b)= (no draft).
    Exactly rtu_match's pipeline; relative includes resolve from the TU's own directory."""
    with _tu_lock:
        if tu_relpath in _tu_cache:
            return _tu_cache[tu_relpath]
    o0 = corpus.is_o0(tu_relpath)
    p1 = subprocess.run([CPP] + CPPFLAGS + ['-Isrc/%s' % binary, '-DINCLUDE_ASM(a,b)=',
                                            tu_relpath],
                        capture_output=True, cwd=REPO)
    if p1.returncode:
        res = (False, ['CPP: ' + p1.stderr.decode('utf-8', 'replace')[-400:]])
    else:
        p2 = subprocess.run([CC1] + cc1flags(o0), input=p1.stdout, capture_output=True, cwd=REPO)
        if p2.returncode:
            keep = [l for l in p2.stderr.decode('utf-8', 'replace').splitlines()
                    if l.strip() and 'warning:' not in l
                    and not re.search(r'In function|At top level', l)][:8]
            res = (False, keep or ['cc1 exit %d, no non-warning diagnostic' % p2.returncode])
        else:
            res = (True, [])
    with _tu_lock:
        _tu_cache[tu_relpath] = res
    return res


# =================================================================================================
# 7. one case
# =================================================================================================
def undeclared_from_stderr(work, fn, body_text):
    """Parse rtu's persisted stderr for `X' undeclared lines INSIDE the spliced draft. Returns
    (inside_syms, outside_lines)."""
    inside, outside = [], []
    serr = os.path.join(work, 'rtu_stderr.txt')
    tc = os.path.join(work, fn, 't.c')
    lo = hi = None
    try:
        tc_txt = open(tc, errors='replace').read()
        at = tc_txt.find(body_text.strip().split('\n', 1)[0])
        if at >= 0:
            lo = tc_txt[:at].count('\n') + 1
            hi = lo + body_text.count('\n') + 1
    except OSError:
        pass
    try:
        for line in open(serr, errors='replace'):
            m = re.search(r"t\.c:(\d+): `(\w+)' undeclared", line)
            if not m:
                continue
            ln, s = int(m.group(1)), m.group(2)
            if lo is not None and lo <= ln <= hi:
                inside.append(s)
            else:
                outside.append(line.strip())
    except OSError:
        pass
    return inside, outside


def run_case(case, a):
    b, fn = case['binary'], case['fn']
    sym0, draft = case.get('symbol'), case['draft']
    row = {'ts': time.strftime('%Y-%m-%d %H:%M:%S'), 'binary': b, 'fn': fn, 'symbol': sym0,
           'draft': draft, 'class': None, 'note': '', 'decls': {}, 'evidence': {},
           'rtu': None, 'reloc': None, 'fixed_draft': None, 'flags': []}
    if b == 'main':
        row.update(**{'class': 'MAIN'}, note='rtu_match has no split model for main (R43)')
        return row
    stubs, err = IR.stub_index(b)
    if err:
        row.update(**{'class': 'CORPUS-ERROR'}, note=err)
        return row
    stub = (stubs or {}).get(fn)
    if stub is None:
        row.update(**{'class': 'NOT-A-STUB'}, note='already banked or unknown in %s' % b)
        return row
    if not os.path.exists(os.path.join(REPO, draft)):
        row.update(**{'class': 'DRAFT-MISSING'}, note=draft)
        return row
    text = open(os.path.join(REPO, draft), errors='replace').read()
    if '//@EDIT' in text:
        row.update(**{'class': 'NEEDS-TU-EDIT'},
                   note='draft carries //@EDIT TU pre-edits; the gate cannot apply them (R43)')
        return row
    ok, diag = tu_compiles(b, stub.path)
    if not ok:
        row.update(**{'class': 'TU-BROKEN'},
                   note='destination TU %s fails cc1 with NO draft spliced; the diagnostic is the '
                        "TU's, not the draft's. First error(s): %s" % (stub.path, ' | '.join(diag)))
        return row

    o0 = corpus.is_o0(stub.path)
    try:
        ev, _ = collect(stub.asm_path, b)
    except OSError as e:
        row.update(**{'class': 'CORPUS-ERROR'}, note='cannot read %s: %s' % (stub.asm_path, e))
        return row

    work = os.path.join(a.out_dir, 'work', '%s__%s' % (b, fn))
    os.makedirs(work, exist_ok=True)
    todo, done, alts = {sym0} if sym0 else set(), {}, {}
    text0 = text
    attempts = 0
    while attempts < 4:
        for s in sorted(todo - set(done)):
            syms_map = corpus.symbols(b)
            unresolvable = resolve_name(s, syms_map) is None
            blanked = blank_decl_statements(text0)
            forms = usage_forms(blanked, s)
            if 'MEMBER' in forms or 'SUBSCRIPT2' in forms:      # the spec's STRUCT class first
                row.update(**{'class': 'STRUCT'},
                           note='%s: draft uses %s — needs a struct/2-D type (aprop STRUCT '
                                'class)%s' % (s, 'member access' if 'MEMBER' in forms
                                              else 'a 2-D subscript',
                                              '; name also resolves to no address in %s symbol '
                                              'files' % b if unresolvable else ''))
                return row
            if unresolvable:
                hint = ''
                m = re.search(r'_([0-9A-Fa-f]{8})$', s)
                if m and ('D_' + m.group(1).upper() in ev or 'D_' + m.group(1) in ev):
                    hint = (" — the .s references D_%s at the embedded address; the draft's name "
                            'looks like a rename defect' % m.group(1))
                row.update(**{'class': 'UNKNOWN-SYMBOL'},
                           note='%s resolves to no address in %s symbol files%s' % (s, b, hint))
                return row
            if not forms:
                row.update(**{'class': 'NO-EVIDENCE'},
                           note='%s never used in the draft outside declarations' % s)
                return row
            try:
                res = infer(s, ev, forms)
            except Refuse as r:
                row.update(**{'class': r.cls}, note='%s: %s' % (s, r.note))
                row['evidence'][s] = _ev_brief(ev.get(s))
                return row
            # same-binary spelling tier: adopt verbatim only when it AGREES with the bytes
            spell = binary_spellings(b, s)
            adopted = None
            for path, ln, d in spell:
                k, w, sg = decl_shape(d)
                # adopt only a spelling the BYTES agree with — kind, width AND sign. The selftest
                # caught the sign hole: lhu evidence (u16) + an existing `extern s16` spelling in a
                # sibling TU adopted verbatim = a 2-instruction byte-DIFF (func_801E2D34).
                if k == res['kind'] and (res['width'] in (None, w)) and w is not None \
                        and (res['sign'] is None or sg in (None, 'f') or sg == res['sign']):
                    adopted = (path, ln, d.declaration(storage='extern'))
                    break
            if adopted:
                res['decl'] = adopted[2]
                res['why'].append('spelling adopted verbatim from %s:%d' % adopted[:2])
            elif spell:
                res['flags'].append('tu-spelling-conflict')
                res['why'].append('existing spellings disagree with the bytes: %s'
                                  % '; '.join('%s:%d %s' % (p, l, d.type) for p, l, d in spell[:3]))
            # CANDIDATE LADDER, adjudicated by rtu on a byte-DIFF (never guessed): the primary
            # decl, then a sign-conflicting same-binary spelling, then the sign flip.
            cands = [res['decl']]
            if not adopted:
                for path, ln, d in spell:
                    k, w, _sg = decl_shape(d)
                    if k == res['kind'] and w == (res['width'] or w) and w is not None:
                        alt = d.declaration(storage='extern')
                        if alt not in cands:
                            cands.append(alt)
                        break
            fl = flip_sign(res, s)
            if fl and fl not in cands:
                cands.append(fl)
            done[s] = res
            alts[s] = cands[:3]
            row['decls'][s] = cands[0]
            row['evidence'][s] = _ev_brief(ev.get(s))
            row['flags'] += ['%s:%s' % (s, f) for f in res['flags']]
            row['why_%s' % s] = res['why']
        if not done:
            row.update(**{'class': 'NO-EVIDENCE'}, note='no undeclared symbol to work on')
            return row
        cur_text = insert_decls(text0, {s: row['decls'][s] for s in done})
        fixed_rel = os.path.join(a.out_dir, b, fn + '.c')
        os.makedirs(os.path.dirname(os.path.join(REPO, fixed_rel)), exist_ok=True)
        open(os.path.join(REPO, fixed_rel), 'w').write(cur_text)
        row['fixed_draft'] = fixed_rel
        v = IR.rtu(b, fn, stub, fixed_rel, work, o0)
        attempts += 1
        row['rtu'] = {k: v.get(k) for k in ('verdict', 'nins', 'ndiff', 'note')}
        if v['verdict'] == 'CC1':
            inside, outside = undeclared_from_stderr(work, fn, cur_text)
            new_syms = [s for s in inside if s not in done]
            if new_syms:
                todo |= set(new_syms)
                continue
            if outside and not inside:
                row.update(**{'class': 'OTHER-DIAG'},
                           note='cc1 fails OUTSIDE the spliced draft after declaring: %s'
                                % (outside[0] if outside else v.get('note', '')))
                return row
            row.update(**{'class': 'CC1-RESIDUAL'}, note=v.get('note', ''))
            return row
        if v['verdict'] == 'DIFF':
            swapped = False
            for s in sorted(done):                               # vary ONE symbol at a time
                cur = row['decls'][s]
                i = alts[s].index(cur) if cur in alts[s] else len(alts[s])
                if i + 1 < len(alts[s]):
                    row['decls'][s] = alts[s][i + 1]
                    row['flags'].append('%s:alternate->%s' % (s, alts[s][i + 1]))
                    swapped = True
                    break
            if swapped:
                continue
        break
    if row['rtu'] and row['rtu']['verdict'] == 'MATCH':
        r = IR.reloc(b, fn, stub, os.path.join(REPO, row['fixed_draft']), work, o0, 'dfu')
        row['reloc'] = {k: r.get(k) for k in ('status', 'checked', 'mismatches')}
        row['class'] = 'MATCH-' + (r.get('status') or '?')
    elif row['rtu']:
        row['class'] = row['rtu']['verdict']
        row['note'] = row['rtu'].get('note') or ''
    else:
        row['class'] = 'NO-RTU'
    return row


def _ev_brief(e):
    if not e:
        return None
    return {'direct': [l for (*_x, l) in e['direct']][:6],
            'addr': [l for (_o, l) in e['addr']][:4],
            'derived': [l for (*_x, l) in e['derived']][:6],
            'deref': [l for (*_x, l) in e['deref']][:4],
            'jalr_via': e['jalr_via'], 'u_hint': e['u_hint'], 's_hint': e['s_hint']}


# =================================================================================================
# 8. the negative control (R39/R35): banked ground truth through the same inference path
# =================================================================================================
def control_triples():
    """Yield (binary, tu_relpath, fn, sym, Declarator, body_text, s_relpath) for every banked
    function that block-scope-declares an extern D_ symbol its own body uses, with a unique
    surviving .s. Deterministic order."""
    bins = sorted(d for d in os.listdir(os.path.join(REPO, 'src'))
                  if os.path.isdir(os.path.join(REPO, 'src', d)) and d != 'shared'
                  and os.path.isdir(os.path.join(REPO, 'asm', d)))
    bins.append('main')
    for b in bins:
        for p in corpus.src_files(b):
            rel = os.path.relpath(p, REPO)
            try:
                txt = open(p, errors='replace').read()
            except OSError:
                continue
            for f in defs_in(txt):
                fn = f['name']
                if not re.match(r'func_[0-9A-Fa-f]{6,8}$', fn):
                    continue
                ss = glob.glob(os.path.join(REPO, 'asm', b, 'nonmatchings', '*', fn + '.s'))
                if len(ss) != 1:
                    continue
                body = txt[f['body_start']:f['body_end']]
                masked = cdecl._mask(body)
                if len(masked) != len(body):
                    masked = body
                blanked = blank_decl_statements(body)
                try:
                    stmts = cdecl.split_statements(masked)
                except Exception:
                    continue
                for st in stmts:
                    if not re.match(r'\s*extern\b', st.text):
                        continue
                    stmt_txt = body[st.start:st.end]
                    try:
                        ds = cdecl.parse(stmt_txt.strip())
                    except cdecl.CDeclError:
                        continue
                    for d in ds:
                        if not re.match(r'D_[0-9A-Fa-f]{6,8}$', d.name):
                            continue
                        if not re.search(r'\b%s\b' % re.escape(d.name), blanked):
                            continue
                        yield (b, rel, fn, d.name, d, body,
                               os.path.relpath(ss[0], REPO))


def negative_control(a):
    say('enumerating control triples (banked fn + block-scope D_ extern + surviving .s)...')
    trips = list(control_triples())
    say('universe: %d triples across %d binaries'
        % (len(trips), len({t[0] for t in trips})))
    rng = random.Random(0)
    rng.shuffle(trips)
    take = trips[:a.negative_control]
    rows = []
    agree = collections.Counter()
    n = collections.Counter()
    ev_cache = {}
    for (b, tu, fn, sym, d, body, s_rel) in take:
        rrow = {'binary': b, 'tu': tu, 'fn': fn, 'symbol': sym, 'declared': d.type,
                'declared_kind': None, 'inferred': None, 'outcome': None}
        dk, dw, dsg = decl_shape(d)
        rrow['declared_kind'] = [dk, dw, dsg]
        n['total'] += 1
        try:
            if s_rel not in ev_cache:
                ev_cache[s_rel] = collect(s_rel, b)[0]
            ev = ev_cache[s_rel]
            forms = usage_forms(blank_decl_statements(body), sym)
            res = infer(sym, ev, forms)
            rrow['inferred'] = res['decl']
            rrow['inferred_kind'] = [res['kind'], res['width'], res['sign']]
            rrow['flags'] = res['flags']
            cast = bool(re.search(r'\(\s*[\w \t]+\s*\*?\s*\)\s*&?\s*%s\b' % re.escape(sym),
                                  blank_decl_statements(body)))
            rrow['cast_at_use'] = cast
            if dw is None:
                n['declared_nonprim'] += 1
                rrow['outcome'] = 'declared-nonprim'
            else:
                n['both_prim'] += 1
                kind_ok = (res['kind'] == dk) or \
                          ({res['kind'], dk} == {'scalar', 'ptr'} and res['width'] in (4, None))
                if res['kind'] == dk:
                    n['kind_exact'] += 1
                if kind_ok:
                    n['kind_ok'] += 1
                if res['kind'] != dk and not kind_ok:
                    n['kind_disagree'] += 1
                    rrow['outcome'] = 'kind-disagree(%s vs %s)' % (res['kind'], dk)
                    if cast:
                        n['disagree_with_cast'] += 1
                elif res['width'] is None:
                    n['width_unknowable'] += 1
                    rrow['outcome'] = 'width-unknowable(default)'
                elif res['width'] == dw:
                    n['kind_width_agree'] += 1
                    rrow['outcome'] = 'agree'
                    if res['sign'] is not None and dsg in ('s', 'u'):
                        n['sign_evidence'] += 1
                        if res['sign'] == dsg:
                            n['sign_agree'] += 1
                        else:
                            rrow['outcome'] = 'sign-disagree'
                elif 'decay-elem' in res['flags']:
                    n['elem_decay_neutral'] += 1                 # element differs; use only DECAYS
                    rrow['outcome'] = 'elem-decay-neutral(%s vs %s)' % (res['width'], dw)
                else:
                    n['width_disagree'] += 1
                    rrow['outcome'] = 'width-disagree(%s vs %s)' % (res['width'], dw)
                    if cast:
                        n['disagree_with_cast'] += 1
        except Refuse as r:
            rrow['outcome'] = 'refused-%s' % r.cls
            n['refused'] += 1
            n['refused_%s' % r.cls] += 1
            if dw is None:
                n['refused_declared_nonprim'] += 1
        except Exception as e:                                   # R32: a crash is a row, not a skip
            rrow['outcome'] = 'ERROR: %s: %s' % (type(e).__name__, e)
            n['error'] += 1
        rows.append(rrow)
    out = os.path.join(REPO, a.out_dir)
    os.makedirs(out, exist_ok=True)
    with open(os.path.join(out, 'negative_control.jsonl'), 'w') as f:
        for r in rows:
            f.write(json.dumps(r) + '\n')
    summary = {'universe': len(trips), 'sampled': len(take), 'counts': dict(n)}
    json.dump(summary, open(os.path.join(out, 'negative_control_summary.json'), 'w'), indent=1)
    say('=== negative control (denominators explicit, R41) ===')
    say('sampled %d of %d triples' % (len(take), len(trips)))
    for k in sorted(n):
        say('  %-28s %d' % (k, n[k]))
    if n['both_prim']:
        say('  kind agreement:        %d/%d' % (n['kind_ok'], n['both_prim']))
        scored = n['both_prim'] - n['width_unknowable']
        say('  kind+width agreement:  %d/%d (excluding %d width-unknowable defaults)'
            % (n['kind_width_agree'], scored, n['width_unknowable']))
    if n['sign_evidence']:
        say('  sign agreement (where the .s carries sign evidence): %d/%d'
            % (n['sign_agree'], n['sign_evidence']))
    return summary


# =================================================================================================
# main
# =================================================================================================
def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--cases', help="the resolver's cases file (.run/resolver/undeclared_cases.json)")
    ap.add_argument('--negative-control', type=int, default=0,
                    help='score N ground-truth triples through the same inference path FIRST')
    ap.add_argument('--out-dir', default='.run/decl_from_use')
    ap.add_argument('-j', type=int, default=4)
    a = ap.parse_args()
    os.makedirs(os.path.join(REPO, a.out_dir), exist_ok=True)

    if a.negative_control:
        negative_control(a)
    if not a.cases:
        return

    cases = json.load(open(os.path.join(REPO, a.cases)))
    say('judging %d cases from %s' % (len(cases), a.cases))
    ledger = os.path.join(REPO, a.out_dir, 'verdicts.jsonl')
    lock = threading.Lock()
    rows = []

    def one(c):
        try:
            r = run_case(c, a)
        except Exception as e:                                   # R32: a crash is a row
            r = {'binary': c.get('binary'), 'fn': c.get('fn'), 'symbol': c.get('symbol'),
                 'draft': c.get('draft'), 'class': 'TOOL-ERROR',
                 'note': '%s: %s' % (type(e).__name__, e)}
        with lock:
            rows.append(r)
            with open(ledger, 'a') as f:
                f.write(json.dumps(r) + '\n')
            say('%-16s %-14s %s %s' % (r.get('fn'), r.get('class'), r.get('binary'),
                                       (r.get('note') or '')[:90]))
        return r

    with ThreadPoolExecutor(max_workers=a.j) as ex:
        list(ex.map(one, cases))

    slate = [{'fn': r['fn'], 'binary': r['binary'], 'draft': r['fixed_draft']}
             for r in rows if r.get('class') == 'MATCH-AGREE' and r.get('fixed_draft')]
    json.dump(slate, open(os.path.join(REPO, a.out_dir, 'slate.json'), 'w'), indent=1)
    cnt = collections.Counter(r.get('class') for r in rows)
    say('=== per-class counts over %d cases (R41) ===' % len(rows))
    for k, v in cnt.most_common():
        say('  %-16s %d/%d' % (k, v, len(rows)))
    say('slate: %d draft(s) -> %s' % (len(slate), os.path.join(a.out_dir, 'slate.json')))


if __name__ == '__main__':
    main()
