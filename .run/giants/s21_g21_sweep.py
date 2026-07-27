#!/usr/bin/env python3
"""Variant sweep for func_80183814 on the NEW base (d9 = e1.c, cases 0/3 fixed).

Each variant is a (name, parts_patch, tmpl_patch) triple applied to copies of
g21_parts.py / g21_mktmpl.py in a private dir, then built / compiled / scored.
Prints: name | mine_len | blind residual | reg-sensitive | frame | saved regs
"""
import os, re, sys, shutil, subprocess, difflib

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = '/home/musashi/bfm-decomp'
sys.path.insert(0, ROOT + '/tools')

VARIANTS = {}


def V(name):
    def deco(f):
        VARIANTS[name] = f
        return f
    return deco


# ---------- §80 re-tests of the round-1 do-not-re-buy table, on the new base ----------

@V('r8_declorder')            # row 8: scalar locals in first-use order
def _(parts, tmpl):
    old = """    s32 s3;
    s32 s0;
    s32 s1;
    s32 s4;
    s32 s5;
    s32 c;
    s32 r;
    s32 t;
    s32 idx;
    s32 ok;"""
    new = """    s32 s0;
    s32 s3;
    s32 r;
    s32 c;
    s32 t;
    s32 idx;
    s32 ok;
    s32 s5;
    s32 s4;
    s32 s1;"""
    assert old in parts
    return parts.replace(old, new), tmpl


@V('r10_mergeidx')            # row 10: merge idx into t
def _(parts, tmpl):
    p = parts.replace('idx = t + ', 't = t + ').replace('D_8018E034[idx]', 'D_8018E034[t]')
    p = p.replace('    s32 idx;\n', '')
    return p, tmpl


@V('r11_okisc')               # row 11: reuse c for the ramp flag
def _(parts, tmpl):
    p = parts.replace('ok = 1;', 'c = 1;').replace('ok = 0;', 'c = 0;')
    p = p.replace('if (ok != 0)', 'if (c != 0)').replace('    s32 ok;\n', '')
    return p, tmpl


@V('r14_case19paren')         # row 14: case-19 parenthesisation (other spelling)
def _(parts, tmpl):
    old = '(*(u16 *)(s0 + 0xA) - 0x8B) - (rand() & 0x3F);'
    new = '*(u16 *)(s0 + 0xA) - (0x8B + (rand() & 0x3F));'
    assert old in parts
    return parts.replace(old, new), tmpl


# ---------- new probes aimed at the KIND==1 loop.c hoist ----------

@V('h1_sp40lit')              # store the literal KIND inside the loop
def _(parts, tmpl):
    return parts, tmpl.replace('sp40[7] = s5;', 'sp40[7] = {K};')


@V('h2_callusesvar')          # pass the variable to func_8012EC04
def _(parts, tmpl):
    return parts, tmpl.replace('func_8012EC04((s32)a0, {K}, sp18);',
                               'func_8012EC04((s32)a0, s5, sp18);')


@V('h3_cmpconstvar')          # a dedicated preheader variable for the compare constant
def _(parts, tmpl):
    t = tmpl.replace('        s5 = {K};\n', '        s5 = {K};\n        s2 = 1;\n')
    t = t.replace('if (p[1] == 1) {', 'if (p[1] == s2) {')
    p = parts.replace('    s32 s5;\n', '    s32 s5;\n    s32 s2;\n')
    return p, t


@V('h5_k1only')   # DIAGNOSTIC: preheader compare-constant variable, KIND==1 instances only
def _(parts, tmpl):
    t = tmpl.replace('        func_8012EC04((s32)a0, {K}, sp18);\n',
                     '        func_8012EC04((s32)a0, {K}, sp18);\n{CMPINIT}')
    t = t.replace('if (p[1] == 1) {', 'if (p[1] == {CMPOP}) {')
    p2 = parts.replace('    s32 s5;\n', '    s32 s5;\n    s32 s2;\n')
    return p2, t


@V('h6_blockscope')   # NATURAL: block-scoped compare variable, SAME source for all 35 instances
def _(parts, tmpl):
    t = tmpl.replace('        s5 = {K};\n',
                     '        {{\n            s32 kk = 1;\n        s5 = {K};\n')
    t = t.replace('if (p[1] == 1) {{', 'if (p[1] == kk) {{')
    t = t.rstrip('\n') + '\n        }}\n'
    return parts, t


@V('h7_blockscope_all')   # h6 + row-13 re-test: scope every template local in the block
def _(parts, tmpl):
    t = tmpl.replace('        s5 = {K};\n',
                     '        {{\n            s32 kk = 1;\n            s32 *p, *q;\n'
                     '            s32 s0, s1, s4, s5;\n        s5 = {K};\n')
    t = t.replace('if (p[1] == 1) {{', 'if (p[1] == kk) {{')
    t = t.rstrip('\n') + '\n        }}\n'
    return parts, t


@V('h8_scopeonly')   # row-13 re-test on the NEW base: scope template locals, keep literal compare
def _(parts, tmpl):
    t = tmpl.replace('        s5 = {K};\n',
                     '        {{\n            s32 *p, *q;\n'
                     '            s32 s0, s1, s4, s5;\n        s5 = {K};\n')
    t = t.rstrip('\n') + '\n        }}\n'
    return parts, t


@V('h10_k1only_declfirst')   # h5 with s2 declared BEFORE s5 (allocno order, §79)
def _(parts, tmpl):
    t = tmpl.replace('        func_8012EC04((s32)a0, {K}, sp18);\n',
                     '        func_8012EC04((s32)a0, {K}, sp18);\n{CMPINIT}')
    t = t.replace('if (p[1] == 1) {{', 'if (p[1] == {CMPOP}) {{')
    p2 = parts.replace('    s32 s5;\n', '    s32 s2;\n    s32 s5;\n')
    return p2, t


@V('h11_k1blockvar')   # K==1-only compare constant, declared in the template block
def _(parts, tmpl):
    t = tmpl.replace('            s32 s0, s1, s4, s5;\n',
                     '            s32 s0, s1, s4, s5;\n{CMPDECL}')
    t = t.replace('        func_8012EC04((s32)a0, {K}, sp18);\n',
                  '        func_8012EC04((s32)a0, {K}, sp18);\n{CMPINIT}')
    t = t.replace('if (p[1] == 1) {{', 'if (p[1] == {CMPOP}) {{')
    return parts, t


@V('p1_rampscope')     # scope t/idx inside the ramp's if-block (h8 lever, applied to RAMP)
def _(parts, tmpl):
    old = "        o.append('        if (r >= c) {\\n')\n"
    new = ("        o.append('        if (r >= c) {\\n')\n"
           "        o.append('            s32 t, idx;\\n')\n")
    assert old in parts
    return parts.replace(old, new), tmpl


@V('p2_rampscope_rc')  # p1 + r/c scoped per ramp step
def _(parts, tmpl):
    old = "        o.append('        r = func_8004787C(*(s16 *)((s32)a0 + 0xFC));\\n')\n"
    new = ("        o.append('        {\\n')\n"
           "        o.append('        s32 r, c;\\n')\n"
           "        o.append('        r = func_8004787C(*(s16 *)((s32)a0 + 0xFC));\\n')\n")
    assert old in parts, 'p2 anchor'
    p2 = parts.replace(old, new)
    p2 = p2.replace("        o.append('        }\\n')\n    return ''.join(o)",
                    "        o.append('        }\\n')\n        o.append('        }\\n')\n    return ''.join(o)")
    old2 = "        o.append('            s32 t, idx;\\n')\n"
    p2 = p2.replace("        o.append('        if (r >= c) {\\n')\n",
                    "        o.append('        if (r >= c) {\\n')\n"
                    "        o.append('            s32 t, idx;\\n')\n")
    return p2, tmpl


@V('m1_declswap')      # morph: swap msa/msb + pa/pb declaration order
def _(parts, tmpl):
    p = parts.replace("            s16 *msa;\n            s16 *msb;\n",
                      "            s16 *msb;\n            s16 *msa;\n")
    p = p.replace("            s16 *pa;\n            s16 *pb;\n",
                  "            s16 *pb;\n            s16 *pa;\n")
    return p, tmpl


@V('m2_assignswap')    # morph: assign msa before msb
def _(parts, tmpl):
    return parts.replace("            msb = %(SB)s;\n            msa = %(SA)s;\n",
                         "            msa = %(SA)s;\n            msb = %(SB)s;\n"), tmpl


@V('m3_walkswap')      # morph: init pb before pa
def _(parts, tmpl):
    return parts.replace("            pa = msa;\n            pb = msb;\n",
                         "            pb = msb;\n            pa = msa;\n"), tmpl


@V('m4_decl_msb_first')  # morph: only the msa/msb decl order
def _(parts, tmpl):
    return parts.replace("            s16 *msa;\n            s16 *msb;\n",
                         "            s16 *msb;\n            s16 *msa;\n"), tmpl


@V('m5_incswap')       # morph: increment pb before pa
def _(parts, tmpl):
    return parts.replace("                pa += 4;\n                pb += 4;\n",
                         "                pb += 4;\n                pa += 4;\n"), tmpl


@V('m6_m2m3')
def _(parts, tmpl):
    p = parts.replace("            msb = %(SB)s;\n            msa = %(SA)s;\n",
                      "            msa = %(SA)s;\n            msb = %(SB)s;\n")
    p = p.replace("            pa = msa;\n            pb = msb;\n",
                  "            pb = msb;\n            pa = msa;\n")
    return p, tmpl


@V('m7_m2m3_decl')
def _(parts, tmpl):
    p = parts.replace("            msb = %(SB)s;\n            msa = %(SA)s;\n",
                      "            msa = %(SA)s;\n            msb = %(SB)s;\n")
    p = p.replace("            pa = msa;\n            pb = msb;\n",
                  "            pb = msb;\n            pa = msa;\n")
    p = p.replace("            s16 *msa;\n            s16 *msb;\n",
                  "            s16 *msb;\n            s16 *msa;\n")
    p = p.replace("            s16 *pa;\n            s16 *pb;\n",
                  "            s16 *pb;\n            s16 *pa;\n")
    return p, tmpl


@V('m8_m3_mdlast')     # m3 + md computed after the pa/pb copies
def _(parts, tmpl):
    p = parts.replace("            pa = msa;\n            pb = msb;\n",
                      "            pb = msb;\n            pa = msa;\n")
    return p, tmpl


@V('m9_pd')            # row-6c RE-TEST on the new base: walk a copy of md too
def _(parts, tmpl):
    p = parts.replace("            s16 *pb;\n", "            s16 *pb;\n            s16 *pd;\n")
    p = p.replace("            pb = msb;\n            pa = msa;\n",
                  "            pb = msb;\n            pa = msa;\n            pd = md;\n")
    p = p.replace("                md[0] =", "                pd[0] =")
    p = p.replace("                md[1] =", "                pd[1] =")
    p = p.replace("                md[2] =", "                pd[2] =")
    p = p.replace("                md += 4;\n", "                pd += 4;\n")
    return p, tmpl


@V('m10_incorder1')    # increments: md, pa, pb
def _(parts, tmpl):
    return parts.replace("                pa += 4;\n                pb += 4;\n                md += 4;\n",
                         "                md += 4;\n                pa += 4;\n                pb += 4;\n"), tmpl


@V('m11_incorder2')    # increments: pb, pa, md
def _(parts, tmpl):
    return parts.replace("                pa += 4;\n                pb += 4;\n                md += 4;\n",
                         "                pb += 4;\n                pa += 4;\n                md += 4;\n"), tmpl


@V('m12_mdcopyonly')   # md walked via a copy, pa/pb direct
def _(parts, tmpl):
    p = parts.replace("            s16 *pb;\n", "            s16 *pb;\n            s16 *pd;\n")
    p = p.replace("            pb = msb;\n            pa = msa;\n", "            pd = md;\n")
    p = p.replace("pb[0]", "msb[0]").replace("pb[1]", "msb[1]").replace("pb[2]", "msb[2]")
    p = p.replace("pa[0]", "msa[0]").replace("pa[1]", "msa[1]").replace("pa[2]", "msa[2]")
    p = p.replace("                md[0] =", "                pd[0] =")
    p = p.replace("                md[1] =", "                pd[1] =")
    p = p.replace("                md[2] =", "                pd[2] =")
    p = p.replace("                pa += 4;\n                pb += 4;\n                md += 4;\n",
                  "                msa += 4;\n                msb += 4;\n                pd += 4;\n")
    return p, tmpl


@V('q1_md_pb_pa')
def _(parts, tmpl):
    p = parts.replace("                pa += 4;\n                pb += 4;\n                md += 4;\n",
                      "                md += 4;\n                pb += 4;\n                pa += 4;\n")
    
    return p, tmpl


@V('q2_pa_md_pb')
def _(parts, tmpl):
    p = parts.replace("                pa += 4;\n                pb += 4;\n                md += 4;\n",
                      "                pa += 4;\n                md += 4;\n                pb += 4;\n")
    
    return p, tmpl


@V('q3_pb_md_pa')
def _(parts, tmpl):
    p = parts.replace("                pa += 4;\n                pb += 4;\n                md += 4;\n",
                      "                pb += 4;\n                md += 4;\n                pa += 4;\n")
    
    return p, tmpl


@V('q4_md_pa_pb_initpa')
def _(parts, tmpl):
    p = parts.replace("                pa += 4;\n                pb += 4;\n                md += 4;\n",
                      "                md += 4;\n                pa += 4;\n                pb += 4;\n")
    p = p.replace("            pb = msb;\\n            pa = msa;\\n", "            pa = msa;\\n            pb = msb;\\n")
    return p, tmpl


@V('c1_randfirst')
def _(parts, tmpl):
    old = '                *(u16 *)(s0 + 0xA) = (*(u16 *)(s0 + 0xA) - 0x8B) - (rand() & 0x3F);'
    assert old in parts
    return parts.replace(old, '                *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - (rand() & 0x3F) - 0x8B;'), tmpl


@V('c2_tempvar')
def _(parts, tmpl):
    old = '                *(u16 *)(s0 + 0xA) = (*(u16 *)(s0 + 0xA) - 0x8B) - (rand() & 0x3F);'
    assert old in parts
    return parts.replace(old, '                c = rand() & 0x3F;\n                *(u16 *)(s0 + 0xA) = (*(u16 *)(s0 + 0xA) - 0x8B) - c;'), tmpl


@V('c3_cast')
def _(parts, tmpl):
    old = '                *(u16 *)(s0 + 0xA) = (*(u16 *)(s0 + 0xA) - 0x8B) - (rand() & 0x3F);'
    assert old in parts
    return parts.replace(old, '                *(u16 *)(s0 + 0xA) = (u16)(*(u16 *)(s0 + 0xA) - 0x8B) - (rand() & 0x3F);'), tmpl


@V('c4_s16')
def _(parts, tmpl):
    old = '                *(u16 *)(s0 + 0xA) = (*(u16 *)(s0 + 0xA) - 0x8B) - (rand() & 0x3F);'
    assert old in parts
    return parts.replace(old, '                *(u16 *)(s0 + 0xA) = (*(s16 *)(s0 + 0xA) - 0x8B) - (rand() & 0x3F);'), tmpl


def build(name, fn):
    d = os.path.join(HERE, 'sw', name)
    os.makedirs(d, exist_ok=True)
    parts = open(os.path.join(HERE, 'g21_parts.py')).read()
    tmplsrc = open(os.path.join(HERE, 'g21_mktmpl.py')).read()
    m = re.search(r"BODY = '''(.*?)'''", tmplsrc, re.S)
    body = m.group(1)
    parts2, body2 = fn(parts, body)
    tmpl2 = tmplsrc[:m.start(1)] + body2 + tmplsrc[m.end(1):]
    open(os.path.join(d, 'v_parts.py'), 'w').write(parts2)
    open(os.path.join(d, 'v_mktmpl.py'), 'w').write(tmpl2)
    drv = '''import re, sys, os
sys.path.insert(0, %r)
from v_mktmpl import tmpl
import v_parts as parts
TP = re.compile(r'^([ \\t]*)/\\*TEMPLATE\\(([^,]+),([^,]+),([^)]+)\\)\\*/[ \\t]*$', re.M)
def expand(text):
    def rep(m):
        ind = len(m.group(1)) or 8
        return tmpl(m.group(2).strip(), m.group(3).strip(), m.group(4).strip(), indent=ind).rstrip('\\n')
    return TP.sub(rep, text)
out = [parts.HEADER, parts.PREAMBLE]
for i in range(21):
    b = getattr(parts, 'C%%02d' %% i, None)
    out.append('    case %%d:\\n' %% i)
    if b: out.append(expand(b))
    out.append('        break;\\n')
out.append(parts.TAIL)
open(sys.argv[1], 'w').write(''.join(out))
''' % d
    open(os.path.join(d, 'drv.py'), 'w').write(drv)
    c = os.path.join(d, 'v.c')
    r = subprocess.run([ROOT + '/.venv/bin/python', os.path.join(d, 'drv.py'), c],
                       capture_output=True, text=True, cwd=d)
    if r.returncode:
        return None, 'BUILD: ' + r.stderr.strip().splitlines()[-1][:90]
    r = subprocess.run([HERE + '/../g14/g14_cc.sh', c, os.path.join(d, 'w')],
                       capture_output=True, text=True)
    if r.returncode:
        return None, 'CC: ' + (r.stderr.strip().splitlines() or ['?'])[-1][:90]
    return os.path.join(d, 'w', 't.o'), None


def score(obj):
    import masked_diff
    FN = 'func_80183814'
    TGT = (ROOT + '/asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8017BEBC/%s.s' % FN)
    mine_r = masked_diff.insns_from_object(obj, FN)
    tgt_r = masked_diff.insns_from_s(TGT)

    def key(d, blind):
        v = d['word']; rel = d['reloc_kind']
        if rel is None and ('%hi(' in d['mnem'] or '%lo(' in d['mnem']): rel = 'HI16'
        if rel is None and (v >> 26) in (2, 3): rel = '26'
        if not blind:
            return v & masked_diff.mask_for(v, rel)
        op = (v >> 26) & 0x3F
        if op in (2, 3) or rel == '26': return ('J',)
        imm = 0 if rel in ('HI16', 'LO16', 'PC16') else v & 0xFFFF
        if op == 0: return ('R', v & 0x3F, (v >> 6) & 0x1F)
        if op == 0x1C: return ('R2', v & 0x3F)
        if op in (1, 4, 5, 6, 7): return ('B', op, (v >> 16) & 0x1F)
        return ('I', op, imm)

    out = []
    for blind in (True, False):
        a = [key(d, blind) for d in mine_r]
        b = [key(d, blind) for d in tgt_r]
        sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
        ok = sum(n for _, _, n in sm.get_matching_blocks())
        out.append(len(b) - ok)
    return len(mine_r), out[0], out[1]


def main():
    want = sys.argv[1:] or sorted(VARIANTS)
    print('%-18s %6s %6s %7s  %s' % ('variant', 'len', 'blind', 'regsens', 'note'))
    print('%-18s %6d %6d %7d  BASE (e6.c)' % ('--base--', 5122, 1, 1))
    for n in want:
        obj, err = build(n, VARIANTS[n])
        if err:
            print('%-18s %s' % (n, err)); continue
        L, bl, rs = score(obj)
        s = open(os.path.join(os.path.dirname(obj), 't.s')).read()
        fr = re.search(r'\.frame\s+\$sp,(\d+)', s)
        mk = re.search(r'\.mask\s+(0x[0-9a-f]+)', s)
        nreg = bin(int(mk.group(1), 16)).count('1') if mk else -1
        print('%-18s %6d %6d %7d  frame=%s regs=%d' %
              (n, L, bl, rs, fr.group(1) if fr else '?', nreg))


main()
