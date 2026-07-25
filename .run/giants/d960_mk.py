#!/usr/bin/env python3
"""Lever/variant generator for func_8017D960 drafts.

usage: d960_mk.py <base.c> <out.c> lever [lever ...]

Each lever is a named source transformation (see LEVERS below). Fails loudly if a
transformation does not apply (so a "neutral" measurement can never silently be a
no-op edit).
"""
import sys, re

def _one(src, old, new, n=1):
    c = src.count(old)
    assert c == n, 'expected %d occurrences, found %d of %r' % (n, c, old[:70])
    return src.replace(old, new)

# ---- arm openers (the four emit tails) -------------------------------------
ARMS = [(44, 'if (f0 | f1 | f2) {'), (44, '} else {'),
        (48, 'if (f0 | f1 | f2) {'), (48, '} else {')]

def decl_per_arm(src, decl, fnscope_line):
    """Move `decl` (e.g. 'u32 *otp;') from function scope into all four arms."""
    src = _one(src, '    %s\n' % fnscope_line, '')
    for ind, text in ARMS:
        opener = '\n' + ' ' * ind + text + '\n'
        src = _one(src, opener, opener + ' ' * ind + decl + '\n')
    return src

def decl_per_case(src, decl, fnscope_line):
    """Move `decl` into the two switch cases (tri body / quad body)."""
    src = _one(src, '    %s\n' % fnscope_line, '')
    a = '                                    gte_stsxy3c(&tmpxy[0]);\n                                    gte_stsz3'
    b = '                                    gte_stsxy3c(&tmpxy[0]);\n                                    gte_ldv0(vd);'
    src = _one(src, a, '                                    %s\n' % decl + a)
    src = _one(src, b, '                                    %s\n' % decl + b)
    return src

LEVERS = {}
def lever(fn):
    LEVERS[fn.__name__] = fn
    return fn

@lever
def otparm(src):
    return decl_per_arm(src, 'u32 *otp;', 'u32 *otp;')

@lever
def tparm(src):
    return decl_per_arm(src, 'u32 *tp;', 'u32 *tp;')

@lever
def otpcase(src):
    return decl_per_case(src, 'u32 *otp;', 'u32 *otp;')

@lever
def tpcase(src):
    return decl_per_case(src, 'u32 *tp;', 'u32 *tp;')

@lever
def uvwarm(src):
    return decl_per_arm(src, 'u32 uvw;', 'u32 uvw;')

@lever
def rgbchain(src):
    """3-statement accumulator, using the existing shared `uvw` temp."""
    for K, n in (('0x34000000', 3), ('0x3C000000', 4)):
        for i in range(n):
            old = ('rgb%d = c%d | %s | (c%d << 8) | (c%d << 16);' % (i, i, K, i, i))
            new = ('rgb%d = XX;' % i)
            assert old in src, old
    def rep(m):
        ind, cast, idx, c, K = m.group(1), m.group(2), m.group(3), m.group(4), m.group(5)
        return ('%suvw = %s | %s;\n%suvw |= %s << 8;\n%suvw |= %s << 16;\n'
                '%s((%s *)pkt)->rgb%s = uvw;' % (ind, c, K, ind, c, ind, c, ind, cast, idx))
    out, n = re.subn(
        r'( *)\(\((\w+) \*\)pkt\)->rgb(\d) = (c\d) \| (0x[0-9A-F]+) \| \(c\d << 8\) \| \(c\d << 16\);',
        rep, src)
    assert n == 7, n
    return out

@lever
def rgbw(src):
    """dedicated `rgbw` temp (not the shared uvw) for the lit rgb word, 4-term expr."""
    src = _one(src, '    u32 uvw;\n', '    u32 uvw;\n    u32 rgbw;\n')
    def rep(m):
        ind, cast, idx, c, K = m.group(1), m.group(2), m.group(3), m.group(4), m.group(5)
        return ('%srgbw = %s | %s | (%s << 8) | (%s << 16);\n'
                '%s((%s *)pkt)->rgb%s = rgbw;' % (ind, c, K, c, c, ind, cast, idx))
    out, n = re.subn(
        r'( *)\(\((\w+) \*\)pkt\)->rgb(\d) = (c\d) \| (0x[0-9A-F]+) \| \(c\d << 8\) \| \(c\d << 16\);',
        rep, src)
    assert n == 7, n
    return out

@lever
def rgbwchain(src):
    """dedicated `rgbw` temp, 3-statement accumulator."""
    src = _one(src, '    u32 uvw;\n', '    u32 uvw;\n    u32 rgbw;\n')
    def rep(m):
        ind, cast, idx, c, K = m.group(1), m.group(2), m.group(3), m.group(4), m.group(5)
        return ('%srgbw = %s | %s;\n%srgbw |= %s << 8;\n%srgbw |= %s << 16;\n'
                '%s((%s *)pkt)->rgb%s = rgbw;' % (ind, c, K, ind, c, ind, c, ind, cast, idx))
    out, n = re.subn(
        r'( *)\(\((\w+) \*\)pkt\)->rgb(\d) = (c\d) \| (0x[0-9A-F]+) \| \(c\d << 8\) \| \(c\d << 16\);',
        rep, src)
    assert n == 7, n
    return out

@lever
def nopins(src):
    """drop all five register __asm__ pins."""
    src = _one(src, '    register s16 r1 __asm__("$25");\n', '    s16 r1;\n')
    src = _one(src, '    register s16 r2 __asm__("$17");\n', '    s16 r2;\n')
    src = _one(src, '    register s16 r0lo __asm__("$19");\n', '    s16 r0lo;\n')
    src = _one(src, '    register s16 r1lo __asm__("$20");\n', '    s16 r1lo;\n')
    src = _one(src, '    register s16 r2lo __asm__("$21");\n', '    s16 r2lo;\n')
    return src

@lever
def basefn(src):
    """rematerialise `base` at the point of use instead of hoisting it."""
    src = _one(src, '    base = D_800AF630;\n', '')
    src = _one(src, '(*(u16 *)(base + 0xA3D2))', '(*(u16 *)(D_800AF630 + 0xA3D2))')
    return src

RGB_RE = (r'( *)\(\((\w+) \*\)pkt\)->rgb(\d) = (c\d) \| (0x[0-9A-F]+) \| '
          r'\(c\d << 8\) \| \(c\d << 16\);')

def rgbexpr(src, tmpl, ntmp=0, tmpdecl=''):
    """Replace all 7 lit rgb stores. tmpl may use %C (colour), %K (tag const),
    %D (store lhs) and may contain ';' to make several statements."""
    if tmpdecl:
        src = _one(src, '    u32 uvw;\n', '    u32 uvw;\n' + tmpdecl)
    def rep(m):
        ind, cast, idx, c, K = m.groups()
        body = tmpl.replace('%C', c).replace('%K', K)
        body = body.replace('%D', '((%s *)pkt)->rgb%s' % (cast, idx))
        return '\n'.join(ind + s for s in body.split('\n'))
    out, n = re.subn(RGB_RE, rep, src)
    assert n == 7, n
    return out

LIT_ARMS = [(44, 'if (f0 | f1 | f2) {'), (48, 'if (f0 | f1 | f2) {')]

def kvar(src, tmpl, name='kk', ty='u32', scope='arm', where='rgb0'):
    """Introduce a VARIABLE holding the poly tag constant, so `fold` cannot
    reassociate it out of the first `|` of the colour chain."""
    if scope == 'none':
        pass
    elif scope == 'fn':
        src = _one(src, '    u32 uvw;\n', '    u32 uvw;\n    %s %s;\n' % (ty, name))
    else:
        for ind, text in LIT_ARMS:
            opener = '\n' + ' ' * ind + text + '\n'
            src = _one(src, opener, opener + ' ' * ind + '%s %s;\n' % (ty, name))
    def rep(m):
        ind, cast, idx, c, K = m.groups()
        body = tmpl.replace('%C', c).replace('%K', K).replace('%N', name)
        body = body.replace('%D', '((%s *)pkt)->rgb%s' % (cast, idx))
        pre = ''
        if (where == 'rgb0' and idx == '0'):
            pre = ind + '%s = %s;\n' % (name, K)
        return pre + '\n'.join(ind + s for s in body.split('\n'))
    out, n = re.subn(RGB_RE, rep, src)
    assert n == 7, n
    return out

@lever
def vw(src):
    """dedicated vertex-word temps (f510's `vw`/`vzw`), instead of reusing w/wz."""
    src = _one(src, '    u32 wx, wy, wz;\n', '    u32 vw, vzw;\n    u32 wx, wy, wz;\n')
    out, n = re.subn(r'w = \*\(u32 \*\)(v[abcd]);', r'vw = *(u32 *)\1;', src)
    assert n == 7, n
    out, n = re.subn(r'wz = \*\(u32 \*\)\((v[abcd]) \+ 4\);', r'vzw = *(u32 *)(\1 + 4);', out)
    assert n == 7, n
    out, n = re.subn(r'x(\d) = w; y\1 = w >> 16; z\1 = wz;',
                     r'x\1 = vw; y\1 = vw >> 16; z\1 = vzw;', out)
    assert n == 7, n
    return out

@lever
def mnydial(src):
    """RC-15 zero-byte ref dial on `mny` at the head of BOTH cull blocks (f510 L4)."""
    for ind in (40, 44):
        o = '\n' + ' ' * ind + 'if (my >= -0x6E && mny < 0x6F) {\n'
        src = _one(src, o, o + ' ' * ind + '    __asm__ __volatile__ ("" :: "r" (mny));\n')
    return src

@lever
def mnydial1(src):
    """same dial, TRI cull block only."""
    o = '\n' + ' ' * 40 + 'if (my >= -0x6E && mny < 0x6F) {\n'
    return _one(src, o, o + ' ' * 40 + '    __asm__ __volatile__ ("" :: "r" (mny));\n')

@lever
def cbmerge(src):
    """route the unlit rgbc through a named temp (f510 L2)."""
    src = _one(src, '    u32 uvw;\n', '    u32 uvw;\n    u32 cb;\n')
    out, n = re.subn(r'( *)\(\((\w+) \*\)pkt\)->rgbc = tp\[0\] & 0xFF000000;',
                     r'\1cb = tp[0] & 0xFF000000;\n\1((\2 *)pkt)->rgbc = cb;', src)
    assert n == 2, n
    return out

@lever
def primorder(src):
    return _one(src,
        'nprim = part->nprim;\n' + ' ' * 20 + 'prim = (Prim *)part->prim;',
        'prim = (Prim *)part->prim;\n' + ' ' * 20 + 'nprim = part->nprim;')

@lever
def basetop(src):
    src = _one(src, '    base = D_800AF630;\n', '')
    src = _one(src, '    lim = func_800491EC()',
               '    base = D_800AF630;\n    lim = func_800491EC()')
    return src

@lever
def fzero(src):
    out, n = re.subn(r'f0 = 0; f1 = 0; f2 = 0;', 'f2 = 0; f1 = 0; f0 = 0;', src)
    assert n == 2, n
    return out

CULL = [(40, 'if (my >= -0x6E && mny < 0x6F) {'),
        (44, 'if (my >= -0x6E && mny < 0x6F) {')]

def _decl_cull(src, decl):
    src = _one(src, '    %s\n' % decl, '')
    for ind, text in CULL:
        o = '\n' + ' ' * ind + text + '\n'
        src = _one(src, o, o + ' ' * (ind + 4) + decl + '\n')
    return src

@lever
def zacase(src):
    return _decl_cull(src, 's32 za, zb;')

@lever
def ccase(src):
    return _decl_cull(src, 's32 c0, c1, c2, c3;')

@lever
def fcase(src):
    return _decl_cull(src, 's32 f0, f1, f2;')

@lever
def xyzcase(src):
    return _decl_cull(src, 's16 x0, y0, z0, x1, y1, z1, x2, y2, z2;')

@lever
def acase(src):
    return _decl_cull(src, 's32 a0v, a1v, a2v;')

@lever
def declrgbw(src):
    return _one(src, '    u32 uvw;\n', '    u32 uvw;\n    u32 rgbw;\n')

@lever
def declcb(src):
    return _one(src, '    u32 uvw;\n', '    u32 uvw;\n    u32 cb;\n')

@lever
def wzlate(src):
    """move `wz = part->zz;` to just before its first use (after the box vx/vy block)."""
    src = _one(src, '        wz = part->zz;\n', '')
    src = _one(src, '        wy = wz >> 16;\n', '        wz = part->zz;\n        wy = wz >> 16;\n')
    return src

def main():
    base, out, levers = sys.argv[1], sys.argv[2], sys.argv[3:]
    src = open(base).read()
    for lv in levers:
        if lv.startswith('K:'):
            _, scope, tmpl = lv.split(':', 2)
            src = kvar(src, tmpl.replace('\\n', '\n'), scope=scope)
            continue
        if lv.startswith('KN:'):
            _, nm, scope, tmpl = lv.split(':', 3)
            src = kvar(src, tmpl.replace('\\n', '\n'), name=nm, scope=scope)
            continue
        if lv.startswith('C:'):
            # route the UNLIT rgbc through an existing variable
            nm = lv.split(':', 1)[1]
            src2, n = re.subn(r'( *)\(\((\w+) \*\)pkt\)->rgbc = tp\[0\] & 0xFF000000;',
                              r'\1%s = tp[0] & 0xFF000000;\n\1((\2 *)pkt)->rgbc = %s;'
                              % (nm, nm), src)
            assert n == 2, n
            src = src2
            continue
        if lv.startswith('R:'):
            # reuse an EXISTING function-scope variable as the tag holder
            _, name, tmpl = lv.split(':', 2)
            src = kvar(src, tmpl.replace('\\n', '\n'), name=name, scope='none')
            continue
        if lv.startswith('X:'):
            _, decl, tmpl = lv.split(':', 2)
            src = rgbexpr(src, tmpl.replace('\\n', '\n'),
                          tmpdecl=('    %s\n' % decl if decl else ''))
            continue
        src = LEVERS[lv](src)
    open(out, 'w').write(src)
    print('wrote %s (%s)' % (out, ','.join(levers) or 'identity'))

main()
