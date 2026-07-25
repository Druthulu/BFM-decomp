#!/usr/bin/env python3
"""Lever/variant generator for func_8017BF14 drafts.
usage: bf14_mk.py <base.c> <out.c> lever [lever ...]
Every transformation asserts it applied, so a "neutral" reading can never be a
silent no-op edit (d960_mk.py discipline)."""
import sys, re

def _one(src, old, new, n=1):
    c = src.count(old)
    assert c == n, 'expected %d occurrences, found %d of %r' % (n, c, old[:80])
    return src.replace(old, new)

RDECL = ('    s16 r0;\n    s16 r1;\n    s16 r2;\n    s16 r3;\n'
         '    s16 r0lo;\n    s16 r1lo;\n    s16 r2lo;\n    s16 r3lo;\n')

LEVERS = {}
def lever(fn):
    LEVERS[fn.__name__] = fn
    return fn

def rdecl_order(src, order):
    """order: e.g. '0,0lo,1,1lo,2,2lo,3,3lo'"""
    new = ''.join('    s16 r%s;\n' % t for t in order.split(','))
    return _one(src, RDECL, new)

# ---- assignment order inside each box's if-block ---------------------------
BOXASN = {
 0: ('        r0lo = D_80197C34 - 0x200;\n        r0 = D_80197C34;\n',
     '        r0 = D_80197C34;\n        r0lo = D_80197C34 - 0x200;\n'),
 1: ('        r1 = D_80197C50;\n        r1lo = D_80197C50 - 0x200;\n',
     '        r1lo = D_80197C50 - 0x200;\n        r1 = D_80197C50;\n'),
 2: ('        r2 = D_80197C6C;\n        r2lo = D_80197C6C - 0x200;\n',
     '        r2lo = D_80197C6C - 0x200;\n        r2 = D_80197C6C;\n'),
 3: ('        r3lo = D_80197C6C - 0x200;\n        r3 = D_80197C88;\n',
     '        r3 = D_80197C88;\n        r3lo = D_80197C6C - 0x200;\n'),
}
def swapbox(src, k):
    a, b = BOXASN[k]
    return _one(src, a, b)

for k in range(4):
    def mk(k=k):
        def f(src): return swapbox(src, k)
        return f
    g = mk(); g.__name__ = 'swapasn%d' % k; lever(g)

# ---- the r-init block -------------------------------------------------------
RINIT = ('    r2lo = 0;\n    r1lo = 0;\n    r0lo = 0;\n'
         '    r2 = 0;\n    r1 = 0;\n    r0 = 0;\n')
def rinit(src, spec):
    new = ''.join('    r%s = 0;\n' % t for t in spec.split(',')) if spec else ''
    return _one(src, RINIT, new)

# ---- misc -------------------------------------------------------------------
@lever
def basefn(src):
    src = _one(src, '    base = D_800AF630;\n', '')
    return _one(src, '(*(u16 *)(base + 0xA3D2))', '(*(u16 *)(D_800AF630 + 0xA3D2))')

@lever
def baselate(src):
    src = _one(src, '    base = D_800AF630;\n', '')
    return _one(src, '    pkt = D_800A5E60;\n', '    base = D_800AF630;\n    pkt = D_800A5E60;\n')

@lever
def fzero_fwd(src):
    return _one(src, 'f3 = 0; f2 = 0; f1 = 0; f0 = 0;',
                     'f0 = 0; f1 = 0; f2 = 0; f3 = 0;', 2)

@lever
def mnydial1(src):
    o = '                                            s32 za, zb;\n'
    return _one(src, o, o + '                                            __asm__ __volatile__ ("" :: "r" (mny));\n')

@lever
def primorder(src):
    return _one(src,
        '                    nprim = part->nprim;\n                    prim = (Prim *)part->prim;',
        '                    prim = (Prim *)part->prim;\n                    nprim = part->nprim;')

@lever
def r3own(src):
    """box3 uses its OWN range global for r3lo (not the copy-paste of box2's)."""
    return _one(src, '        r3lo = D_80197C6C - 0x200;\n', '        r3lo = D_80197C88 - 0x200;\n')


@lever
def cb101010(src):
    """unlit rgbc is (tp[0] & 0xFF000000) | 0x101010, not plain black."""
    return _one(src, 'cb = tp[0] & 0xFF000000;',
                     'cb = (tp[0] & 0xFF000000) | 0x101010;', 2)

@lever
def k101010(src):
    """same, but through a dedicated function-scope constant holder."""
    src = _one(src, '    u32 cb;\n', '    u32 cb;\n    u32 kk;\n')
    src = _one(src, '    base = D_800AF630;\n', '    base = D_800AF630;\n    kk = 0x101010;\n')
    return _one(src, 'cb = tp[0] & 0xFF000000;', 'cb = (tp[0] & 0xFF000000) | kk;', 2)


# ---- declaration-scope levers (cookbook 76) --------------------------------
CULL = ['\n' + ' '*44 + 's32 za, zb;\n',
        '\n' + ' '*48 + 's32 za, zb;\n']
LIT  = ['                                            u32 *otp;\n',
        '                                                u32 *otp;\n']
UNLIT= ['                                            u32 *otp;\n',
        '                                                u32 *otp;\n']

def _movedecl(src, fndecl, anchors):
    """delete the function-scope decl line and re-insert after each anchor."""
    src = _one(src, '    %s\n' % fndecl, '')
    for a in anchors:
        ind = ' ' * (len(a.rstrip('\n').split('\n')[-1]) - len(a.rstrip('\n').split('\n')[-1].lstrip()))
        src = _one(src, a, a + ind + fndecl + '\n')
    return src

def scope(src, fndecl, where):
    if where == 'cull':  return _movedecl(src, fndecl, CULL)
    if where == 'lit':
        # 4 occurrences of `u32 *otp;` (2 lit + 2 unlit arms); target only the LIT ones
        out = src.replace('    %s\n' % fndecl, '', 1)
        assert out != src
        for a in ('                                            if (f0 | f1 | f2 | f3) {\n                                            u32 *otp;\n',
                  '                                                if (f0 | f1 | f2 | f3) {\n                                                u32 *otp;\n'):
            ind = ' ' * (len(a.split('\n')[1]) - len(a.split('\n')[1].lstrip()))
            out = _one(out, a, a + ind + fndecl + '\n')
        return out
    raise KeyError(where)

def _mkscope(name, decl, where):
    def f(src): return scope(src, decl, where)
    f.__name__ = name; lever(f); return f

_mkscope('xyz_cull', 's16 x0, y0, z0, x1, y1, z1, x2, y2, z2;', 'cull')
_mkscope('a_cull',   's32 a0v, a1v, a2v, a3v;', 'cull')
_mkscope('c_cull',   's32 c0, c1, c2, c3;', 'cull')
_mkscope('d_cull',   's32 d;', 'cull')
_mkscope('f_cull',   's32 f0, f1, f2, f3;', 'cull')
_mkscope('tp_cull',  'u32 *tp;', 'cull')
_mkscope('a_lit',    's32 a0v, a1v, a2v, a3v;', 'lit')
_mkscope('c_lit',    's32 c0, c1, c2, c3;', 'lit')
_mkscope('d_lit',    's32 d;', 'lit')
_mkscope('xyz_lit',  's16 x0, y0, z0, x1, y1, z1, x2, y2, z2;', 'lit')

@lever
def novw(src):
    """drop the dedicated vertex-word temps; reuse w / wz."""
    src = _one(src, '    u32 vw, vzw;\n', '')
    src = src.replace('vw = *(u32 *)', 'w = *(u32 *)').replace('vzw = *(u32 *)', 'wz = *(u32 *)')
    src = re.sub(r'= vw;( |$)', r'= w;\1', src)
    src = src.replace('vw >> 16', 'w >> 16').replace('= vzw;', '= wz;')
    assert 'vw' not in src and 'vzw' not in src
    return src

def dial(src, name, n=2):
    """RC-15 zero-byte ref dial: first statement of each cull block."""
    for a in CULL:
        last = a.rstrip('\n').split('\n')[-1]
        ind = ' ' * (len(last) - len(last.lstrip()))
        src = _one(src, a, a + ind + '__asm__ __volatile__ ("" :: "r" (%s));\n' % name)
    return src

@lever
def dial_mny(src):  return dial(src, 'mny')
@lever
def dial_my(src):   return dial(src, 'my')
@lever
def dial_r1lo(src): return dial(src, 'r1lo')
@lever
def dial_r0lo(src): return dial(src, 'r0lo')
@lever
def dial_r1(src):   return dial(src, 'r1')


# ---- generic zero-byte ref dial on any variable, at a chosen anchor --------
PRIMHEAD = ('                    for (i = 0; i < nprim; i++, prim++) {\n'
            '                        w = prim->w1;\n')
LITARM = ['\n' + ' '*44 + 'if (f0 | f1 | f2 | f3) {\n' + ' '*44 + 'u32 *otp;\n',
          '\n' + ' '*48 + 'if (f0 | f1 | f2 | f3) {\n' + ' '*48 + 'u32 *otp;\n']

def dialat(src, name, where):
    stmt = '__asm__ __volatile__ ("" :: "r" (%s));\n'
    if where == 'cull':
        for a in CULL:
            last = a.rstrip('\n').split('\n')[-1]
            ind = ' ' * (len(last) - len(last.lstrip()))
            src = _one(src, a, a + ind + stmt % name)
    elif where == 'prim':
        src = _one(src, PRIMHEAD, PRIMHEAD + ' '*24 + stmt % name)
    elif where == 'lit':
        for a in LITARM:
            last = a.rstrip('\n').split('\n')[-1]
            ind = ' ' * (len(last) - len(last.lstrip()))
            src = _one(src, a, a + ind + stmt % name)
    else: raise KeyError(where)
    return src

# ---- move the whole r-declaration block ------------------------------------
def rpos(src, where):
    src2 = _one(src, RDECL, '')
    if where == 'top':
        return _one(src2, '    s32 j;\n', RDECL + '    s32 j;\n')
    if where == 'bot':
        return _one(src2, '    u32 rgbw;\n', '    u32 rgbw;\n' + RDECL)
    if where == 'prelo':
        return _one(src2, '    s16 lo0x, hi0x,', RDECL + '    s16 lo0x, hi0x,')
    if where == 'precxy':
        return _one(src2, '    s16 cx0, cy0, cz0,', RDECL + '    s16 cx0, cy0, cz0,')
    raise KeyError(where)

# ---- per-EMIT-ARM declaration scope (cookbook 76 / d960 L1) ----------------
def armdecl(src, decl, arms='all'):
    src = _one(src, '    %s\n' % decl, '')
    for ind, n in ((44, 2), (48, 2)):
        a = '\n' + ' ' * ind + 'u32 *otp;\n'
        c = src.count(a)
        assert c == n, 'arm anchor %d: expected %d found %d' % (ind, n, c)
        src = src.replace(a, a + ' ' * ind + decl + '\n')
    return src

# ---- reposition a declaration line (slot order == pseudo order == decl order) ----
def declmove(src, decl, anchor):
    src = _one(src, '    %s\n' % decl, '')
    return _one(src, '    %s\n' % anchor, '    %s\n    %s\n' % (anchor, decl))

def armdecl_pre(src, decl):
    """same as armdecl but the decl goes BEFORE `u32 *otp;` in each arm."""
    src = _one(src, '    %s\n' % decl, '')
    for ind, n in ((44, 2), (48, 2)):
        a = '\n' + ' ' * ind + 'u32 *otp;\n'
        assert src.count(a) == n
        src = src.replace(a, '\n' + ' ' * ind + decl + '\n' + ' ' * ind + 'u32 *otp;\n')
    return src

@lever
def dial_mny_tri(src):
    a = CULL[0]
    last = a.rstrip('\n').split('\n')[-1]
    ind = ' ' * (len(last) - len(last.lstrip()))
    return _one(src, a, a + ind + '__asm__ __volatile__ ("" :: "r" (mny));\n')

@lever
def dial_mny_quad(src):
    a = CULL[1]
    last = a.rstrip('\n').split('\n')[-1]
    ind = ' ' * (len(last) - len(last.lstrip()))
    return _one(src, a, a + ind + '__asm__ __volatile__ ("" :: "r" (mny));\n')

FDECL = '    s32 f0, f1, f2, f3;\n'
@lever
def fsplit_pre(src):
    """f0,f1 declared BEFORE pkt (lower pseudo nos); f2,f3 after pkt (slot order kept)."""
    src = _one(src, FDECL, '')
    return _one(src, '    u8 *pkt;\n',
                '    s32 f0, f1;\n    u8 *pkt;\n    s32 f2, f3;\n')
@lever
def fsplit_post(src):
    src = _one(src, FDECL, '')
    return _one(src, '    u8 *pkt;\n', '    u8 *pkt;\n    s32 f2, f3;\n    s32 f0, f1;\n')
@lever
def fdecl_pkt(src):
    src = _one(src, FDECL, '')
    return _one(src, '    u8 *pkt;\n', '    u8 *pkt;\n' + FDECL)
@lever
def xyz_split(src):
    """x2,y2,z2 declared last (higher pseudo nos -> lower tiebreak priority)."""
    o = '    s16 x0, y0, z0, x1, y1, z1, x2, y2, z2;\n'
    return _one(src, o, '    s16 x0, y0, z0, x1, y1, z1;\n    s16 x2, y2, z2;\n')
@lever
def xyz_late(src):
    o = '    s16 x0, y0, z0, x1, y1, z1, x2, y2, z2;\n'
    src = _one(src, o, '')
    return _one(src, '    u32 rgbw;\n', '    u32 rgbw;\n' + o)

def pin(src, decl, reg):
    """turn a plain decl into a `register ... __asm__("$N")` pin (72: PREFERENCE)."""
    return _one(src, '    %s;\n' % decl, '    register %s __asm__("%s");\n' % (decl, reg))

@lever
def pin_va(src):
    return _one(src, '    u8 *va, *vb, *vc;\n',
                '    register u8 *va __asm__("$10");\n    u8 *vb, *vc;\n')
@lever
def pin_f0(src):
    return _one(src, '    s32 f0, f1, f2, f3;\n',
                '    register s32 f0 __asm__("$19");\n    s32 f1, f2, f3;\n')
@lever
def pin_f0_pkt(src):
    return _one(src, '    u8 *pkt;\n    s32 f0, f1, f2, f3;\n',
                '    u8 *pkt;\n    register s32 f0 __asm__("$19");\n    s32 f1, f2, f3;\n')

@lever
def pin_w(src):
    return _one(src, '    u32 w; s32 code;\n',
                '    register u32 w __asm__("$5");\n    s32 code;\n')
@lever
def pin_c1(src):
    o = '                                            s32 c0, c1, c2, c3;\n'
    o2 = '                                                s32 c0, c1, c2, c3;\n'
    assert src.count(o) >= 1
    src = src.replace('s32 c0, c1, c2, c3;',
                      'register s32 c1 __asm__("$4"); s32 c0, c2, c3;')
    return src

@lever
def pin_call(src):
    """pin the four vertex colours to the target's grants: c0=$t4 c1=$a0 c2=$t2 c3=$a2."""
    n = src.count('s32 c0, c1, c2, c3;')
    assert n == 2, n
    return src.replace('s32 c0, c1, c2, c3;',
        'register s32 c0 __asm__("$12"); register s32 c1 __asm__("$4"); '
        'register s32 c2 __asm__("$10"); register s32 c3 __asm__("$6");')

@lever
def pin_c01(src):
    n = src.count('s32 c0, c1, c2, c3;')
    assert n == 2, n
    return src.replace('s32 c0, c1, c2, c3;',
        'register s32 c0 __asm__("$12"); register s32 c1 __asm__("$4"); s32 c2, c3;')

@lever
def pin_c012(src):
    n = src.count('s32 c0, c1, c2, c3;')
    assert n == 2, n
    return src.replace('s32 c0, c1, c2, c3;',
        'register s32 c0 __asm__("$12"); register s32 c1 __asm__("$4"); '
        'register s32 c2 __asm__("$10"); s32 c3;')

@lever
def pin_c0(src):
    n = src.count('s32 c0, c1, c2, c3;'); assert n == 2, n
    return src.replace('s32 c0, c1, c2, c3;',
        'register s32 c0 __asm__("$12"); s32 c1, c2, c3;')
@lever
def pin_c2(src):
    n = src.count('s32 c0, c1, c2, c3;'); assert n == 2, n
    return src.replace('s32 c0, c1, c2, c3;',
        'register s32 c2 __asm__("$10"); s32 c0, c1, c3;')
@lever
def pin_c1c2(src):
    n = src.count('s32 c0, c1, c2, c3;'); assert n == 2, n
    return src.replace('s32 c0, c1, c2, c3;',
        'register s32 c1 __asm__("$4"); register s32 c2 __asm__("$10"); s32 c0, c3;')
@lever
def vab_swap(src):
    o = ('                        va = vtx + (w & 0xFFFF);\n'
         '                        vb = vtx + (w >> 16);\n')
    return _one(src, o, ('                        vb = vtx + (w >> 16);\n'
                         '                        va = vtx + (w & 0xFFFF);\n'))
@lever
def vd_late(src):
    o = '                            vd = vtx + (w & 0xFFF8);\n'
    src = _one(src, o, '')
    a = '                            gte_stopz(&g.opz);\n'
    return _one(src, a, o + a)

@lever
def cb_two(src):
    """unlit rgbc as a 2-statement accumulator."""
    n = src.count('cb = (tp[0] & 0xFF000000) | 0x101010;'); assert n == 2, n
    return src.replace('cb = (tp[0] & 0xFF000000) | 0x101010;',
                       'cb = tp[0] & 0xFF000000;\n                                                cb |= 0x101010;')
@lever
def rgb_chain(src):
    """lit rgb word as a 3-statement accumulator instead of one 4-term expr."""
    out, n = re.subn(r'rgbw = \((c\d) \| cb\) \| \((c\d) << 8\) \| \((c\d) << 16\);',
                     lambda m: 'rgbw = %s | cb; rgbw |= %s << 8; rgbw |= %s << 16;'
                               % (m.group(1), m.group(2), m.group(3)), src)
    assert n == 7, n
    return out
@lever
def rgb_chain_q(src):
    """3-statement accumulator in the QUAD lit arm only (4 sites)."""
    i = src.index('PolyGT4 *)pkt)->rgb0')
    head, tail = src[:i], src[i:]
    out, n = re.subn(r'rgbw = \((c\d) \| cb\) \| \((c\d) << 8\) \| \((c\d) << 16\);',
                     lambda m: 'rgbw = %s | cb; rgbw |= %s << 8; rgbw |= %s << 16;'
                               % (m.group(1), m.group(2), m.group(3)), tail)
    assert n == 3, n
    # the rgb0 one sits just before the marker
    j = head.rindex('rgbw = ')
    h2 = head[:j] + re.sub(r'rgbw = \((c\d) \| cb\) \| \((c\d) << 8\) \| \((c\d) << 16\);',
                           lambda m: 'rgbw = %s | cb; rgbw |= %s << 8; rgbw |= %s << 16;'
                                     % (m.group(1), m.group(2), m.group(3)), head[j:])
    return h2 + out
def main():
    base, out, levers = sys.argv[1], sys.argv[2], sys.argv[3:]
    src = open(base).read()
    for lv in levers:
        if lv.startswith('D:'):
            src = rdecl_order(src, lv[2:]); continue
        if lv.startswith('W:'):
            _, d, a = lv.split('@'); src = declmove(src, d.replace('~',' '), a.replace('~',' ')); continue
        if lv.startswith('E:'):
            src = armdecl_pre(src, lv[2:].replace('~', ' ')); continue
        if lv.startswith('A:'):
            src = armdecl(src, lv[2:].replace('~', ' ')); continue
        if lv.startswith('V:'):
            _, nm, wh = lv.split(':'); src = dialat(src, nm, wh); continue
        if lv.startswith('P:'):
            src = rpos(src, lv[2:]); continue
        if lv.startswith('I:'):
            src = rinit(src, lv[2:]); continue
        src = LEVERS[lv](src)
    open(out, 'w').write(src)

main()
