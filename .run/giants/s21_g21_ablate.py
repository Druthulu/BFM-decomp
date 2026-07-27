#!/usr/bin/env python3
"""Drop-one ablations on the FINAL func_80183814 draft.

Each entry reverts exactly ONE lever from the final source and re-measures, so
every lever's contribution is load-bearing and quantified on the final base.
"""
import os, re, sys, subprocess, difflib

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = '/home/musashi/bfm-decomp'
sys.path.insert(0, ROOT + '/tools')
sys.path.insert(0, HERE)

ABL = {}


def A(name):
    def deco(f):
        ABL[name] = f
        return f
    return deco


@A('L1  §84 derived-base, cases 0/3')
def _(p, t):
    p = p.replace("func_8017D8A4(D_801BFCBC + 0x3C, &D_8018E2DC - 0x60, &D_8018E2DC - 0x30, s3, 1);",
                  "func_8017D8A4(D_801BFCBC + 0x3C, &D_8018E27C, &D_8018E27C + 0x30, s3, 1);")
    p = p.replace("func_8017D8A4(D_801BFCBC + 0x48, &D_8018E2E8 - 0x60, &D_8018E2E8 - 0x30, s3, 1);",
                  "func_8017D8A4(D_801BFCBC + 0x48, &D_8018E288, &D_8018E288 + 0x30, s3, 1);")
    p = p.replace("func_8017D8A4(D_801BFCBC + 0x54, &D_8018E2F4 - 0x60, &D_8018E2F4 - 0x30, s3, 1);",
                  "func_8017D8A4(D_801BFCBC + 0x54, &D_8018E294, &D_8018E294 + 0x30, s3, 1);")
    p = p.replace("func_8017D8A4(D_801BFCC4 + 0x84, &D_8018E27C + 0x60, &D_8018E27C + 0x90, s3, 1);",
                  "func_8017D8A4(D_801BFCC4 + 0x84, &D_8018E2DC, &D_8018E2DC + 0x30, s3, 1);")
    p = p.replace("func_8017D8A4(D_801BFCC4 + 0x90, &D_8018E288 + 0x60, &D_8018E288 + 0x90, s3, 1);",
                  "func_8017D8A4(D_801BFCC4 + 0x90, &D_8018E2E8, &D_8018E2E8 + 0x30, s3, 1);")
    p = p.replace("func_8017D8A4(D_801BFCC4 + 0x9C, &D_8018E294 + 0x60, &D_8018E294 + 0x90, s3, 1);",
                  "func_8017D8A4(D_801BFCC4 + 0x9C, &D_8018E2F4, &D_8018E2F4 + 0x30, s3, 1);")
    return p, t


@A('L2  template locals block-scoped')
def _(p, t):
    t = t.replace("        {{\n            s32 *p, *q;\n            s32 s0, s1, s4, s5;\n", "        {{\n")
    return p, t


@A('L3  KIND==1 compare var')
def _(p, t):
    t = t.replace("{CMPDECL}", "").replace("{CMPFOR}", "").replace("{CMPOP}", "1")
    return p, t


@A('L4  ramp t/idx block-scoped')
def _(p, t):
    return p.replace("        o.append('            s32 t, idx;\\n')\n", ""), t


@A('L5  morph: pb=msb before pa=msa')
def _(p, t):
    return p.replace("            pb = msb;\n            pa = msa;\n",
                     "            pa = msa;\n            pb = msb;\n"), t


@A('L6  morph: increment order md,pb,pa')
def _(p, t):
    return p.replace("                md += 4;\n                pb += 4;\n                pa += 4;\n",
                     "                pa += 4;\n                pb += 4;\n                md += 4;\n"), t


@A('L7  case19 signed s16 read')
def _(p, t):
    return p.replace("(*(s16 *)(s0 + 0xA) - 0x8B) - (rand() & 0x3F);",
                     "(*(u16 *)(s0 + 0xA) - 0x8B) - (rand() & 0x3F);"), t


def run(name, fn):
    d = os.path.join(HERE, 'abl', re.sub(r'\W+', '_', name))
    os.makedirs(d, exist_ok=True)
    parts = open(HERE + '/g21_parts.py').read()
    tsrc = open(HERE + '/g21_mktmpl.py').read()
    m = re.search(r"BODY = '''(.*?)'''", tsrc, re.S)
    p2, b2 = fn(parts, m.group(1))
    open(d + '/v_parts.py', 'w').write(p2)
    open(d + '/v_mktmpl.py', 'w').write(tsrc[:m.start(1)] + b2 + tsrc[m.end(1):])
    drv = open(HERE + '/abl_drv.py').read().replace('__DIR__', d)
    open(d + '/drv.py', 'w').write(drv)
    c = d + '/v.c'
    r = subprocess.run([ROOT + '/.venv/bin/python', d + '/drv.py', c],
                       capture_output=True, text=True, cwd=d)
    if r.returncode:
        return 'BUILD ' + r.stderr.strip().splitlines()[-1][:70]
    r = subprocess.run([HERE + '/../g14/g14_cc.sh', c, d + '/w'], capture_output=True, text=True)
    if r.returncode:
        return 'CC ' + (r.stderr.strip().splitlines() or ['?'])[-1][:70]
    return score(d + '/w/t.o', d + '/w/t.s')


def score(obj, sfile):
    import masked_diff
    FN = 'func_80183814'
    TGT = ROOT + '/asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8017BEBC/%s.s' % FN
    a_r = masked_diff.insns_from_object(obj, FN)
    b_r = masked_diff.insns_from_s(TGT)

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
        x = [key(d, blind) for d in a_r]; y = [key(d, blind) for d in b_r]
        sm = difflib.SequenceMatcher(None, x, y, autojunk=False)
        out.append(len(y) - sum(n for _, _, n in sm.get_matching_blocks()))
    s = open(sfile).read()
    fr = re.search(r'\.frame\s+\$sp,(\d+)', s)
    mk = re.search(r'\.mask\s+(0x[0-9a-f]+)', s)
    return 'len=%-5d blind=%-5d regsens=%-5d frame=%s regs=%d' % (
        len(a_r), out[0], out[1], fr.group(1) if fr else '?',
        bin(int(mk.group(1), 16)).count('1') if mk else -1)


print('FINAL DRAFT (all levers)   len=5122  blind=0     regsens=0     frame=248 regs=8')
print('-- drop one lever ---------------------------------------------------------')
for n in sorted(ABL):
    print('%-34s %s' % (n, run(n, ABL[n])))
