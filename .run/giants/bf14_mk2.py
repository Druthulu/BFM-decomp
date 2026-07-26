#!/usr/bin/env python3
"""Round-2 lever generator for func_8017BF14.

Same contract as bf14_mk.py: EVERY transformation asserts it actually applied,
so a "neutral" reading can never be a silent no-op.

usage: bf14_mk2.py <base.c> <out.c> lever [lever ...]
"""
import sys, re

LEVERS = {}
def lever(fn):
    LEVERS[fn.__name__] = fn
    return fn

def _one(src, old, new, n=1):
    c = src.count(old)
    assert c == n, 'expected %d of %r, found %d' % (n, old, c)
    return src.replace(old, new)

def _all(src, old, new, n):
    c = src.count(old)
    assert c == n, 'expected %d of %r, found %d' % (n, old, c)
    return src.replace(old, new)

# --------------------------------------------------------------------------
# UNPIN levers -- the b1 base carries four pins baked in.
# --------------------------------------------------------------------------
@lever
def unpin_va(src):
    return _one(src, '    register u8 *va __asm__("$10");\n    u8 *vb, *vc;\n',
                     '    u8 *va, *vb, *vc;\n')
@lever
def unpin_w(src):
    return _one(src, '    register u32 w __asm__("$5");\n    s32 code;\n',
                     '    u32 w;\n    s32 code;\n')
@lever
def unpin_f0(src):
    return _one(src, '    register s32 f0 __asm__("$19");\n    s32 f1, f2, f3;\n',
                     '    s32 f0, f1, f2, f3;\n')
@lever
def unpin_c1(src):
    return _all(src, 'register s32 c1 __asm__("$4"); s32 c0, c2, c3;',
                     's32 c0, c1, c2, c3;', 2)

# --- re-pin at other registers -------------------------------------------
def _repin_c(src, spec):
    """spec like 'c0=12,c2=10' -> pin those, leave the rest plain."""
    want = dict(kv.split('=') for kv in spec.split(','))
    out = []
    for nm in ('c0', 'c1', 'c2', 'c3'):
        if nm in want:
            out.append('register s32 %s __asm__("$%s");' % (nm, want[nm]))
    plain = [nm for nm in ('c0', 'c1', 'c2', 'c3') if nm not in want]
    if plain:
        out.append('s32 %s;' % ', '.join(plain))
    new = ' '.join(out)
    for old in ('register s32 c1 __asm__("$4"); s32 c0, c2, c3;',
                's32 c0, c1, c2, c3;'):
        if src.count(old) in (1, 2):
            return src.replace(old, new)
    raise AssertionError('no c-decl found')

# --------------------------------------------------------------------------
# rgb emit-word FORM levers
# --------------------------------------------------------------------------
_CHAIN_Q = [
    ('rgbw = c0 | cb; rgbw |= c0 << 8; rgbw |= c0 << 16;',
     'rgbw = (c0 | cb) | (c0 << 8) | (c0 << 16);'),
    ('rgbw = c1 | cb; rgbw |= c1 << 8; rgbw |= c1 << 16;',
     'rgbw = (c1 | cb) | (c1 << 8) | (c1 << 16);'),
    ('rgbw = c2 | cb; rgbw |= c2 << 8; rgbw |= c1 << 16;',
     'rgbw = (c2 | cb) | (c2 << 8) | (c1 << 16);'),
    ('rgbw = c3 | cb; rgbw |= c3 << 8; rgbw |= c1 << 16;',
     'rgbw = (c3 | cb) | (c3 << 8) | (c1 << 16);'),
]

@lever
def qsingle(src):
    """QUAD lit arm: revert the 3-statement accumulator to ONE expression."""
    for a, b in _CHAIN_Q:
        src = _one(src, a, b)
    return src

@lever
def qsingle23(src):
    """QUAD lit arm: single-expression for rgb2/rgb3 ONLY (keep 0/1 chained)."""
    for a, b in _CHAIN_Q[2:]:
        src = _one(src, a, b)
    return src

@lever
def qsingle01(src):
    for a, b in _CHAIN_Q[:2]:
        src = _one(src, a, b)
    return src

_RGBW_RE = re.compile(
    r'rgbw = (?P<e>[^;]+?);(?P<mid>\s*(?:rgbw \|= [^;]+;\s*)*)'
    r'\(\(PolyGT(?P<n>[34]) \*\)pkt\)->rgb(?P<k>\d) = rgbw;')

def _direct(src, poly):
    """collapse `rgbw = ...; rgbw |= ...; pkt->rgbN = rgbw;` into one store."""
    hits = [0]
    def rep(m):
        if m.group('n') != poly:
            return m.group(0)
        expr = m.group('e')
        for extra in re.findall(r'rgbw \|= ([^;]+);', m.group('mid')):
            expr = '(%s) | %s' % (expr, extra)
        hits[0] += 1
        return '((PolyGT%s *)pkt)->rgb%s = %s;' % (poly, m.group('k'), expr)
    out = _RGBW_RE.sub(rep, src)
    assert hits[0] == int(poly), 'direct(GT%s): %d sites' % (poly, hits[0])
    return out

@lever
def qdirect(src):
    """QUAD lit arm: no rgbw temp at all -- store the expression directly.
    Each rgb word then becomes a 1-death LOCAL temp, so local-alloc places
    them independently and they can alternate $v0/$v1 the way the target does."""
    return _direct(src, '4')

@lever
def tdirect2(src):
    """TRI lit arm: same, no rgbw temp."""
    return _direct(src, '3')

# --------------------------------------------------------------------------
# residual (c) part 1: the UNLIT rgbc word.
#   target: and $a1,$v0,$a2 / or $v1,$a1,$v1 / sw $v1
#   mine  : and $a1,$v0,$a2 / or $a1,$a1,$v1 / sw $a1
#   `cb` is a function-scope global allocno ($a1).  `cb |= 0x101010` writes it
#   in place.  The target instead stores `cb | 0x101010` as a 1-death LOCAL
#   temp, which combine_regs ties to the DYING constant register ($v1).
# --------------------------------------------------------------------------
@lever
def cb_expr(src):
    """unlit arms: `pkt->rgbc = cb | 0x101010;` (drop the `cb |=` statement)."""
    out, n = re.subn(
        r'cb = tp\[0\] & 0xFF000000;\s*\n\s*cb \|= 0x101010;\s*\n(\s*)'
        r'\(\(PolyFT(\d) \*\)pkt\)->rgbc = cb;',
        lambda m: ('cb = tp[0] & 0xFF000000;\n%s((PolyFT%s *)pkt)->rgbc'
                   ' = cb | 0x101010;' % (m.group(1), m.group(2))), src)
    assert n == 2, n
    return out

@lever
def cb_expr_one(src):
    """unlit arms: the whole thing as ONE expression, no `cb` at all."""
    out, n = re.subn(
        r'cb = tp\[0\] & 0xFF000000;\s*\n\s*cb \|= 0x101010;\s*\n(\s*)'
        r'\(\(PolyFT(\d) \*\)pkt\)->rgbc = cb;',
        lambda m: ('((PolyFT%s *)pkt)->rgbc = (tp[0] & 0xFF000000) | 0x101010;'
                   % m.group(2)), src)
    assert n == 2, n
    return out

_CHAIN_T = [
    ('rgbw = (c0 | cb) | (c0 << 8) | (c0 << 16);',
     'rgbw = c0 | cb; rgbw |= c0 << 8; rgbw |= c0 << 16;'),
    ('rgbw = (c1 | cb) | (c1 << 8) | (c1 << 16);',
     'rgbw = c1 | cb; rgbw |= c1 << 8; rgbw |= c1 << 16;'),
    ('rgbw = (c2 | cb) | (c2 << 8) | (c2 << 16);',
     'rgbw = c2 | cb; rgbw |= c2 << 8; rgbw |= c2 << 16;'),
]
@lever
def tchain(src):
    """TRI lit arm: 3-statement accumulator (base is single-expression)."""
    for a, b in _CHAIN_T:
        src = _one(src, a, b)
    return src

@lever
def tdirect(src):
    """TRI lit arm: store the expression directly, no rgbw."""
    for k in range(3):
        old = 'rgbw = (c%d | cb) | (c%d << 8) | (c%d << 16);' % (k, k, k)
        assert src.count(old) == 1, old
        expr = old.split('= ', 1)[1].rstrip(';')
        src = src.replace(old, '')
        st = '((PolyGT3 *)pkt)->rgb%d = rgbw;' % k
        assert src.count(st) == 1, st
        src = src.replace(st, '((PolyGT3 *)pkt)->rgb%d = %s;' % (k, expr))
    return src

@lever
def rgbw_fn(src):
    """ONE function-scope `u32 rgbw;` (matched-relative style) instead of per-arm."""
    n = src.count('                                                u32 rgbw;\n')
    m = src.count('                                            u32 rgbw;\n')
    assert n + m == 4, (n, m)
    src = src.replace('                                                u32 rgbw;\n', '')
    src = src.replace('                                            u32 rgbw;\n', '')
    return _one(src, '    u32 cb;\n', '    u32 cb;\n    u32 rgbw;\n')

# --------------------------------------------------------------------------
# residual (a): named producer-offset temps.
# --------------------------------------------------------------------------
_PROD = """                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
"""

@lever
def prod1(src):
    """ONE shared offset variable `vo` for all 3 head offsets -> 3 deaths."""
    new = """                        w = prim->w1;
                        vo = w & 0xFFFF;
                        va = vtx + vo;
                        vo = w >> 16;
                        vb = vtx + vo;
                        w = prim->w2;
                        vo = w & 0xFFFF;
                        vc = vtx + vo;
                        w = w >> 16;
"""
    src = _one(src, _PROD, new)
    return _one(src, '    u32 vw, vzw;\n', '    u32 vw, vzw;\n    u32 vo;\n')

@lever
def prod2(src):
    """TWO offset variables: `vo` (masked, 2 deaths) and `vs` (shifted, 1)."""
    new = """                        w = prim->w1;
                        vo = w & 0xFFFF;
                        va = vtx + vo;
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vo = w & 0xFFFF;
                        vc = vtx + vo;
                        w = w >> 16;
"""
    src = _one(src, _PROD, new)
    return _one(src, '    u32 vw, vzw;\n', '    u32 vw, vzw;\n    u32 vo;\n')

@lever
def prod3(src):
    """`vo` shared by the head offsets AND the vd offset (4 deaths)."""
    src = prod1(src)
    return _one(src, 'vd = vtx + (w & 0xFFF8);',
                     'vo = w & 0xFFF8; vd = vtx + vo;')

@lever
def prodvd(src):
    """only the vd offset gets a named temp (shared with nothing)."""
    src = _one(src, 'vd = vtx + (w & 0xFFF8);',
                    'vo = w & 0xFFF8; vd = vtx + vo;')
    return _one(src, '    u32 vw, vzw;\n', '    u32 vw, vzw;\n    u32 vo;\n')

@lever
def prodswap(src):
    """commute the producer adds: (w & 0xFFFF) + vtx."""
    new = """                        w = prim->w1;
                        va = (w & 0xFFFF) + vtx;
                        vb = (w >> 16) + vtx;
                        w = prim->w2;
                        vc = (w & 0xFFFF) + vtx;
                        w = w >> 16;
"""
    return _one(src, _PROD, new)

# --------------------------------------------------------------------------
# residual (b): variable REUSE merges (RC-14 MERGE / cookbook 45-A).
# The four colours are simultaneously live, so they cannot merge with each
# other -- merge them with values that are DEAD by then instead.
# --------------------------------------------------------------------------
def _arm(src, which):
    """return (start,end) slice of the TRI or QUAD lit arm."""
    if which == 'tri':
        a = src.index('/* ---------------- TRI')
        b = src.index('case 2:')
    else:
        a = src.index('/* ---------------- QUAD')
        b = src.index('D_800A5E60 = pkt;')
    return a, b

def _merge(src, victim, survivor, which, ndecl):
    """rename `victim` -> `survivor` inside one arm, and drop victim's decl."""
    a, b = _arm(src, which)
    seg = src[a:b]
    new, n = re.subn(r'\b%s\b' % victim, survivor, seg)
    assert n == ndecl, 'merge %s->%s in %s: %d hits' % (victim, survivor, which, n)
    return src[:a] + new + src[b:]

def _mrg(src, which, victim, survivor, dropdecl):
    a, b = _arm(src, which)
    seg = src[a:b]
    seg2 = seg.replace(*dropdecl)
    assert seg2 != seg, 'decl %r not found in %s arm' % (dropdecl[0], which)
    seg2, n = re.subn(r'\b%s\b' % victim, survivor, seg2)
    assert n > 0, 'no %s in %s arm' % (victim, which)
    return src[:a] + seg2 + src[b:]

@lever
def merge_za_c0_t(src):
    """TRI: the max-z temp `za` and `c0` never overlap -> one variable."""
    return _mrg(src, 'tri', 'za', 'c0', ('s32 za, zb;', 's32 zb;'))

@lever
def merge_za_c0_q(src):
    return _mrg(src, 'quad', 'za', 'c0', ('s32 za, zb;', 's32 zb;'))

@lever
def merge_zb_c1_q(src):
    return _mrg(src, 'quad', 'zb', 'c1', ('s32 za, zb;', 's32 za;'))

@lever
def merge_zb_c0_q(src):
    return _mrg(src, 'quad', 'zb', 'c0', ('s32 za, zb;', 's32 za;'))

def _mrg_tail(src, which, anchor, victim, survivor, decls):
    a, b = _arm(src, which)
    seg = src[a:b]
    i = seg.index(anchor)
    head, tail = seg[:i], seg[i:]
    tail2, n = re.subn(r'\b%s\b' % victim, survivor, tail)
    assert n > 0, (victim, n)
    for old, new in decls:
        if old in head:
            head = head.replace(old, new)
            break
    else:
        raise AssertionError('no c-decl in %s arm' % which)
    return src[:a] + head + tail2 + src[b:]

@lever
def merge_f0_c3_q(src):
    """QUAD: f0..f3 are dead once the last ATTEN3 has run -> f0 doubles as c3."""
    return _mrg_tail(src, 'quad', 'CLAMP80(c3', 'c3', 'f0',
                     [('s32 c0, c2, c3;', 's32 c0, c2;'),
                      ('s32 c0, c1, c2, c3;', 's32 c0, c1, c2;')])

@lever
def merge_f0_c2_t(src):
    """TRI: f0..f3 dead after the last ATTEN3 -> f0 doubles as c2."""
    return _mrg_tail(src, 'tri', 'CLAMP80(c2', 'c2', 'f0',
                     [('s32 c0, c2, c3;', 's32 c0, c3;'),
                      ('s32 c0, c1, c2, c3;', 's32 c0, c1, c3;')])

@lever
def merge_f1_c2_t(src):
    return _mrg_tail(src, 'tri', 'CLAMP80(c2', 'c2', 'f1',
                     [('s32 c0, c2, c3;', 's32 c0, c3;'),
                      ('s32 c0, c1, c2, c3;', 's32 c0, c1, c3;')])

@lever
def merge_f1_c3_q(src):
    return _mrg_tail(src, 'quad', 'CLAMP80(c3', 'c3', 'f1',
                     [('s32 c0, c2, c3;', 's32 c0, c2;'),
                      ('s32 c0, c1, c2, c3;', 's32 c0, c1, c2;')])

# --------------------------------------------------------------------------
# residual (b2): the CLAMP80 sum accumulator.
#   target: addu $v0,..  addu $v0,..  addu $v0,..  addiu <c>,$v0,0x10
#   mine  : the whole chain is tied INTO the pinned c1 ($a0) by
#           combine_regs' `sreg < FIRST_PSEUDO_REGISTER` phys_sugg path.
#   fix   : give the sum its own NAMED variable with >1 death, so
#           local-alloc.c:472 refuses it a qty and combine_regs bails at its
#           very first test (`reg_qty[ureg] < 0`).
# --------------------------------------------------------------------------
_CL = ('#define CLAMP80(C, A0, A1, A2, A3)  C = (A0) + (A1) + (A2) + (A3)'
       ' + 0x10; if ((C) > 0x80) C = 0x80\n')
_CLS = (_CL +
        '#define CLAMP80S(C, A0, A1, A2, A3)  sv = (A0) + (A1) + (A2) + (A3);'
        ' C = sv + 0x10; if ((C) > 0x80) C = 0x80\n')

@lever
def sumvar_c1(src):
    """shared sum variable `sv` on the two c1 CLAMP80 sites only (2 deaths)."""
    src = _one(src, _CL, _CLS)
    src = _all(src, 'CLAMP80(c1,', 'CLAMP80S(c1,', 2)
    return _one(src, '    u32 cb;\n', '    u32 cb;\n    s32 sv;\n')

@lever
def sumvar_all(src):
    """shared sum variable `sv` on ALL seven CLAMP80 sites."""
    src = _one(src, _CL, _CLS)
    n = src.count('CLAMP80(c')
    assert n == 7, n
    src = src.replace('CLAMP80(c', 'CLAMP80S(c')
    return _one(src, '    u32 cb;\n', '    u32 cb;\n    s32 sv;\n')

@lever
def sumvar_q(src):
    """shared sum variable on the four QUAD CLAMP80 sites."""
    src = _one(src, _CL, _CLS)
    a, b = _arm(src, 'quad')
    seg = src[a:b]
    n = seg.count('CLAMP80(c')
    assert n == 4, n
    src = src[:a] + seg.replace('CLAMP80(c', 'CLAMP80S(c') + src[b:]
    return _one(src, '    u32 cb;\n', '    u32 cb;\n    s32 sv;\n')

@lever
def sumvar_t(src):
    """shared sum variable on the three TRI CLAMP80 sites."""
    src = _one(src, _CL, _CLS)
    a, b = _arm(src, 'tri')
    seg = src[a:b]
    n = seg.count('CLAMP80(c')
    assert n == 3, n
    src = src[:a] + seg.replace('CLAMP80(c', 'CLAMP80S(c') + src[b:]
    return _one(src, '    u32 cb;\n', '    u32 cb;\n    s32 sv;\n')

# --- more producer-offset partitions -------------------------------------
@lever
def prod_cd(src):
    """`vo` shared by the vc offset and the vd offset (target puts both in $v0)."""
    new = """                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vo = w & 0xFFFF;
                        vc = vtx + vo;
                        w = w >> 16;
"""
    src = _one(src, _PROD, new)
    src = _one(src, 'vd = vtx + (w & 0xFFF8);', 'vo = w & 0xFFF8; vd = vtx + vo;')
    return _one(src, '    u32 vw, vzw;\n', '    u32 vw, vzw;\n    u32 vo;\n')

@lever
def prod_ad(src):
    """`vo` shared by the va offset and the vd offset."""
    new = """                        w = prim->w1;
                        vo = w & 0xFFFF;
                        va = vtx + vo;
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
"""
    src = _one(src, _PROD, new)
    src = _one(src, 'vd = vtx + (w & 0xFFF8);', 'vo = w & 0xFFF8; vd = vtx + vo;')
    return _one(src, '    u32 vw, vzw;\n', '    u32 vw, vzw;\n    u32 vo;\n')

@lever
def prod_a(src):
    """`vo` on the va offset only, but made multi-death by also carrying vd."""
    return prod_ad(src)

@lever
def cdrop3_t(src):
    """TRI arm declares c3 but never uses it -- drop it."""
    a, b = _arm(src, 'tri')
    seg = src[a:b]
    for old, new in (('s32 c0, c2, c3;', 's32 c0, c2;'),
                     ('s32 c0, c1, c2, c3;', 's32 c0, c1, c2;')):
        if old in seg:
            return src[:a] + seg.replace(old, new) + src[b:]
    raise AssertionError('no c-decl in tri arm')

@lever
def cdropzb_t(src):
    """TRI arm declares zb but never uses it -- drop it."""
    a, b = _arm(src, 'tri')
    seg = src[a:b]
    assert 's32 za, zb;' in seg
    return src[:a] + seg.replace('s32 za, zb;', 's32 za;') + src[b:]

# --- c declaration ORDER inside the arm ----------------------------------
def _corder(src, order):
    plain = [c for c in order]
    txt = 's32 %s;' % ', '.join(plain)
    for old in ('register s32 c1 __asm__("$4"); s32 c0, c2, c3;',
                's32 c0, c1, c2, c3;'):
        if src.count(old) == 2:
            if 'register' in old:
                txt = ('register s32 c1 __asm__("$4"); s32 %s;'
                       % ', '.join([c for c in order if c != 'c1']))
            return src.replace(old, txt)
    raise AssertionError('no c-decl')

# --- ref dials -----------------------------------------------------------
def _dial(src, name, which, n=1):
    """insert n zero-byte ref bumps on `name` right after the c-decl of an arm."""
    a, b = _arm(src, which)
    seg = src[a:b]
    m = re.search(r'( *)(register s32 c1 __asm__\("\$4"\); s32 c0, c2, c3;|s32 c0, c1, c2, c3;)\n', seg)
    assert m, 'no anchor'
    ins = ''.join('%s__asm__ __volatile__ ("" :: "r" (%s));\n' % (m.group(1), name)
                  for _ in range(n))
    seg = seg[:m.end()] + ins + seg[m.end():]
    return src[:a] + seg + src[b:]


# --------------------------------------------------------------------------
# residual (b1): the TRI arm's c0/c2 grants.
#   The target's TRI grants (c0=$t4, c1=$a0, c2=$t2) are IDENTICAL to its QUAD
#   grants -- i.e. c0..c3 are ONE set of function-scope variables shared by
#   both arms, exactly as in the matched relatives func_8017D960 /
#   func_8017F510.  Per-cull-block scope splits them into two independent
#   allocno sets, which is why the TRI set drifts.
# --------------------------------------------------------------------------
_CDECLS = ('register s32 c1 __asm__("$4"); s32 c0, c2, c3;',
           's32 c0, c1, c2, c3;')

def _cfn(src, anchor, pinned):
    for old in _CDECLS:
        if src.count(old) == 2:
            break
    else:
        raise AssertionError('no per-arm c-decl')
    # drop the two per-arm declarations (whole lines)
    out, n = re.subn(r'[ \t]*%s\n' % re.escape(old), '', src)
    assert n == 2, n
    decl = ('register s32 c1 __asm__("$4"); s32 c0, c2, c3;' if pinned
            else 's32 c0, c1, c2, c3;')
    assert out.count(anchor) == 1, anchor
    return out.replace(anchor, anchor + '    %s\n' % decl)

@lever
def cfn(src):
    """c0..c3 at FUNCTION scope, c1 still pinned to $a0."""
    return _cfn(src, '    s32 a0v, a1v, a2v, a3v;\n', True)

@lever
def cfn_np(src):
    """c0..c3 at FUNCTION scope, PIN-FREE (matched-relative style)."""
    return _cfn(src, '    s32 a0v, a1v, a2v, a3v;\n', False)

@lever
def cfn_cb(src):
    """c0..c3 at function scope, declared just before `u32 cb;`."""
    return _cfn(src, '    u32 uvw;\n', True)

@lever
def cfn_top(src):
    """c0..c3 at function scope, declared early (before the r/lo/hi block)."""
    return _cfn(src, '    Part *part;\n', True)

@lever
def cfn_end(src):
    """c0..c3 at function scope, declared LAST."""
    return _cfn(src, '    u32 cb;\n', True)

@lever
def cfn_d(src):
    """c0..c3 at function scope, declared right after `s32 d;`."""
    return _cfn(src, '    s32 d;\n', True)


@lever
def unpin_c1n(src):
    """drop the c1 pin (function-scope c-decl form, single occurrence)."""
    return _one(src, 'register s32 c1 __asm__("$4"); s32 c0, c2, c3;',
                     's32 c0, c1, c2, c3;')

# --------------------------------------------------------------------------
# residual 3889: one CLAMP80 site sums its attenuations in a different
# ORDER (a0v+a1v+a3v+a2v).  Its `sra` therefore lands in a3v's own register
# ($a3) instead of being written in place over a2v's.  Another hand-edit
# copy-paste artefact, of the same family as report-1 artefacts 1-4.
# --------------------------------------------------------------------------
_CLAMP_RE = re.compile(r'CLAMP80S?\((c\d), (a0v), (a1v), (a2v), (a3v)\);')

def _clampswap(src, which, sites):
    a, b = _arm(src, which)
    seg = src[a:b]
    hits = [-1]
    def rep(m):
        hits[0] += 1
        if hits[0] not in sites:
            return m.group(0)
        return m.group(0).replace('a2v, a3v', 'a3v, a2v')
    seg2 = _CLAMP_RE.sub(rep, seg)
    assert seg2 != seg, 'clampswap %s %s: no site changed' % (which, sites)
    return src[:a] + seg2 + src[b:]

# --------------------------------------------------------------------------
# residual 3889 -- a FIFTH copy-paste artefact.
#   At ONE of the seven ATTEN3 sites the y-axis `else if` branch accumulates
#   into a2v instead of a3v, while the y-axis KILL branch still says a3v.
#   Byte-evidence in the target:
#       3875  addu $a2,$zero,$zero    <- kill branch writes a3v ($a2)   [matches]
#       3889  sra  $a3,$s2,7          <- else branch writes a2v ($a3)   [differs]
#   Cost: zero instructions.  Same shape as report-1 artefacts 1-4.
# --------------------------------------------------------------------------
_A3 = """#define ATTEN3(A, F, X, Y, Z, CX, CY, CZ, R, RLO, RZ, RY)               \\
"""
_A3W = """#define ATTEN3W(A, AW, F, X, Y, Z, CX, CY, CZ, R, RLO, RZ, RY)          \\
    A = 0;                                                              \\
    if (F) {                                                            \\
        d = (X) - (CX);   if (d < 0) d = (CX) - (X);                    \\
        if (d < (R)) { A = 0x80; if (d >= (RLO)) A = ((R) - d) / 4; }   \\
        d = (Z) - (CZ);   if (d < 0) d = (CZ) - (Z);                    \\
        if ((RZ) < d) A = 0;                                            \\
        else if ((RLO) < d) A = (A * (((R) - d) / 4)) >> 7;             \\
        d = (Y) - (CY);   if (d < 0) d = (CY) - (Y);                    \\
        if ((RY) < d) A = 0;                                            \\
        else if ((RLO) < d) AW = (A * (((R) - d) / 4)) >> 7;            \\
    }

"""
_A3CALL = re.compile(r'ATTEN3\((a\dv), (f\d),')

def _atten3w(src, which, sites, dst):
    if 'ATTEN3W' not in src:
        src = _one(src, _A3, _A3W + _A3)
    a, b = _arm(src, which)
    seg = src[a:b]
    hits = [-1]
    def rep(m):
        hits[0] += 1
        if hits[0] not in sites:
            return m.group(0)
        return 'ATTEN3W(%s, %s, %s,' % (m.group(1), dst, m.group(2))
    seg2 = _A3CALL.sub(rep, seg)
    assert seg2 != seg, 'atten3w %s %s: no site changed' % (which, sites)
    return src[:a] + seg2 + src[b:]

# --------------------------------------------------------------------------
# last residual (2258/2259): `c1 << 16` in the TRI arm.
#   c1 is pinned, so it is a HARD reg from the start; it DIES at the `sll`, so
#   combine_regs takes its `sreg < FIRST_PSEUDO_REGISTER` branch and records
#   $a0 in qty_phys_sugg for the sll's temp -> the temp lands in $a0 and the
#   shift is done in place.  The target keeps the temp in $v0.
#   Cure family: make the temp NOT a 1-death local (a named var used in both
#   arms), or move the pin off c1 onto a colour whose grant we already match.
# --------------------------------------------------------------------------
@lever
def hivar(src):
    """named `hi` for the `c1 << 16` term in BOTH arms -> 2 deaths, no qty."""
    out, n = re.subn(r'\(c1 << 16\)', 'hi', src)
    assert n >= 1, n
    out, m = re.subn(r'rgbw \|= c1 << 16;', 'rgbw |= hi;', out)
    tri = out.index('/* ---------------- TRI')
    quad = out.index('/* ---------------- QUAD')
    # one `hi = c1 << 16;` immediately before the first rgb store of each arm
    def ins(s, marker):
        i = s.index(marker)
        j = s.rindex('\n', 0, s.rindex('rgbw', 0, i) if 'rgbw' in s[:i] else i)
        return s
    for anchor in ('rgbw = (c1 | cb)', 'rgbw = c1 | cb'):
        while anchor in out:
            k = out.index(anchor)
            ln = out.rindex('\n', 0, k) + 1
            pad = out[ln:k]
            out = out[:ln] + pad + 'hi = c1 << 16;\n' + out[ln:]
            k2 = out.index(anchor, ln + len(pad) + 14)
            out = out[:k2] + anchor.replace('rgbw', 'rgbw$') + out[k2 + len(anchor):]
    out = out.replace('rgbw$', 'rgbw')
    assert 'hi = c1 << 16;' in out
    return _one(out, '    u32 cb;\n', '    u32 cb;\n    u32 hi;\n')

@lever
def _noop(src):
    return src

def _c1live(src, which, anchor):
    """RC-15 zero-byte ref that keeps the PINNED c1 ($a0) live past the
    `sll` of `c1 << 16`.  combine_regs records $a0 in qty_phys_sugg
    unconditionally (local-alloc.c:1798, no death guard), but find_free_reg
    can only honour a suggestion whose hard reg is actually free over the
    temp's live range -- so extending c1 past the shift is what refuses it."""
    a, b = _arm(src, which)
    seg = src[a:b]
    assert seg.count(anchor) == 1, (anchor, seg.count(anchor))
    k = seg.index(anchor) + len(anchor)
    ln = seg.rindex('\n', 0, seg.index(anchor)) + 1
    pad = seg[ln:seg.index(anchor)]
    seg = seg[:k] + '\n' + pad + '__asm__ __volatile__ ("" :: "r" (c1));' + seg[k:]
    return src[:a] + seg + src[b:]

def main():
    base, out, levers = sys.argv[1], sys.argv[2], sys.argv[3:]
    src = open(base).read()
    for lv in levers:
        if lv.startswith('RC:'):          # RC:c0=12,c2=10
            src = _repin_c(src, lv[3:]); continue
        if lv.startswith('CO:'):          # CO:c2,c0,c1,c3
            src = _corder(src, lv[3:].split(',')); continue
        if lv.startswith('CL:'):          # CL:tri:rgb1
            _, wh, tag = lv.split(':')
            poly = '3' if wh == 'tri' else '4'
            anc = {'rgb0': '((PolyGT%s *)pkt)->rgb0 = rgbw;' % poly,
                   'rgb1': '((PolyGT%s *)pkt)->rgb1 = rgbw;' % poly,
                   'rgb2': '((PolyGT%s *)pkt)->rgb2 = rgbw;' % poly,
                   'uv0': '((PolyGT%s *)pkt)->uv0 = tp[1];' % poly,
                   'end': 'pkt += 0x%s;' % ('28' if wh == 'tri' else '34')}[tag]
            src = _c1live(src, wh, anc); continue
        if lv.startswith('AW:'):          # AW:quad:1:a2v
            _, wh, ix, dst = lv.split(':')
            src = _atten3w(src, wh, set(int(x) for x in ix.split(',')), dst); continue
        if lv.startswith('CS:'):          # CS:quad:1  or CS:tri:0,2
            _, wh, ix = lv.split(':')
            src = _clampswap(src, wh, set(int(x) for x in ix.split(','))); continue
        if lv.startswith('DL:'):          # DL:name:tri[:n]
            p = lv[3:].split(':')
            src = _dial(src, p[0], p[1], int(p[2]) if len(p) > 2 else 1); continue
        src = LEVERS[lv](src)
    open(out, 'w').write(src)

main()
