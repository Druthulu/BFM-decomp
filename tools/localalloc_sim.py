#!/usr/bin/env python3
"""localalloc_sim.py <lreg dump> <fn> <uid-in-block> [verbose]   (built by T7 agent c26 as lsim.py, P36 S103; promoted)

WHY. `tools/alloc_table.py` prints GLOBAL-allocation priorities on flow's live length; for a register permutation inside
ONE basic block the decider is local-alloc's own per-block ranking (`qty_compare_1`, local-alloc.c:1598, over quantity
births/deaths numbered per block), which gave `pb0` 7105 where alloc_table said 13500/16500. Four S103 agents needed this
ranking (c1, c8, c16, c26) and two wrote partial scripts; this one reproduces the dump's own `;; Register N in M.` lines.
VALIDATED (coordinator, S103): 126 block simulations over five dumps of func_80133CD4 and 24 over func_8013D178 /
func_8013D8FC / func_8013D53C — `mismatches vs dump: 0` in every one. Feed it the `.lreg` dump that
`tools/cc1_dumps_tu.sh` writes. A hypothesis tool: its MATCH column is its own control.

Simulate gcc 2.7.2 local-alloc (block_alloc, local-alloc.c:1123) for the basic block containing insn <uid>:
qty births/deaths (2n / 2n, 2n+1 for REG_UNUSED), ties (combine_regs: output tied to a dying input), copy suggestions
from hard regs, qty_compare_1 priority, find_free_reg lowest-numbered.  Prints each qty with priority, range, the
simulated hard reg and the hard reg the dump says (';; Register N in M.').  A hypothesis tool, validated against the
dump's own assignments (the MATCH column)."""
import re, sys, math

NAMES = {2: "v0", 3: "v1", 4: "a0", 5: "a1", 6: "a2", 7: "a3", 8: "t0", 9: "t1", 10: "t2", 11: "t3", 12: "t4",
         13: "t5", 14: "t6", 15: "t7", 16: "s0", 17: "s1", 18: "s2", 19: "s3", 20: "s4", 21: "s5", 22: "s6",
         23: "s7", 24: "t8", 25: "t9", 31: "ra", 64: "hi", 65: "lo"}


def tok(s):
    out = []
    i = 0
    n = len(s)
    while i < n:
        c = s[i]
        if c in '([':
            out.append('('); i += 1
        elif c in ')]':
            out.append(')'); i += 1
        elif c.isspace():
            i += 1
        elif c == '"':
            j = s.index('"', i + 1); out.append(s[i:j + 1]); i = j + 1
        elif c == '{':
            j = s.index('}', i); out.append(s[i:j + 1]); i = j + 1
        else:
            j = i
            while j < n and not s[j].isspace() and s[j] not in '()[]':
                j += 1
            out.append(s[i:j]); i = j
    return out


def parse(tokens, i=0):
    if tokens[i] == '(':
        lst = []
        i += 1
        while tokens[i] != ')':
            x, i = parse(tokens, i)
            lst.append(x)
        return lst, i + 1
    return tokens[i], i + 1


def code(x):
    return x[0].split(':')[0].split('/')[0] if isinstance(x, list) and x and isinstance(x[0], str) else None


def mode(x):
    h = x[0]
    return h.split(':')[1] if ':' in h else None


def regno(x):
    if code(x) == 'reg':
        return int(x[1])
    return None


def strip_subreg(x):
    while code(x) == 'subreg':
        x = x[1]
    return x


def notes_of(ins, kind):
    """REG_* notes: the last list element(s) chain expr_list:REG_X (reg) (next)."""
    res = []
    for e in ins:
        if isinstance(e, list) and e and isinstance(e[0], str) and e[0].startswith('expr_list'):
            x = e
            while isinstance(x, list) and x and isinstance(x[0], str) and x[0].startswith(('expr_list', 'insn_list')):
                if x[0] == 'expr_list:' + kind and regno(x[1]) is not None:
                    res.append(regno(x[1]))
                x = x[2] if len(x) > 2 else None
    return res


def sets_of(pat):
    out = []
    c = code(pat)
    if c in ('set', 'clobber'):
        d = strip_subreg(pat[1])
        if regno(d) is not None:
            out.append((regno(d), c))
    elif c == 'parallel':
        for p in pat[1]:
            out += sets_of(p)
    return out


def main():
    path, fn, uid = sys.argv[1], sys.argv[2], sys.argv[3]
    verbose = len(sys.argv) > 4
    verbose_from = sys.argv[4] if verbose else 0
    s = open(path, errors='surrogateescape').read()
    i = s.find(f';; Function {fn}\n'); j = s.find(';; Function ', i + 20); s = s[i:j if j > 0 else None]
    info = {}
    for m in re.finditer(r'\nRegister (\d+) used (\d+) times across (\d+) insns([^\n]*)', s):
        info[int(m.group(1))] = (int(m.group(2)), int(m.group(3)), m.group(4))
    hard = {int(a): int(b) for a, b in re.findall(r';; Register (\d+) in (\d+)\.', s)}
    parts = re.split(r'\n(?=\((?:insn|call_insn|jump_insn|note|code_label|barrier) )', s)
    insns = []
    for p in parts:
        m = re.match(r'\((insn|call_insn|jump_insn|note|code_label|barrier) (\d+)', p)
        if not m:
            continue
        body = p[:p.rfind(')') + 1] if m.group(1) != 'note' else p
        insns.append((m.group(1), int(m.group(2)), body))
    # block containing uid
    idx = [k for k, x in enumerate(insns) if x[1] == int(uid)][0]
    a = idx
    while a > 0 and insns[a][0] != 'code_label' and insns[a - 1][0] not in ('jump_insn', 'barrier'):
        a -= 1
    b = idx
    while b < len(insns) - 1 and insns[b][0] != 'jump_insn' and insns[b + 1][0] != 'code_label':
        b += 1
    blk = insns[a:b + 1]
    blkno = None
    local = set()
    for r, (refs, live, ex) in info.items():
        if 'in block' in ex and 'dies in' not in ex and 'LO_REG' not in ex and 'HI_REG' not in ex:
            local.add(r)
    reg_qty = {}
    qties = []  # dict(regs, birth, death, refs, sugg, copysugg, size)
    hard_live = []  # (hreg, start, end)
    hard_birth = {}
    n = 0
    order_rows = []
    for kind, u, body in blk:
        if kind in ('note', 'barrier'):
            continue
        n += 1
        if kind == 'code_label':
            continue
        t = tok(body)
        ins, _ = parse(t)
        pat = ins[4]
        dead = notes_of(ins, 'REG_DEAD')
        unused = notes_of(ins, 'REG_UNUSED')
        combined = None
        # tie attempt
        s0 = pat if code(pat) == 'set' else (pat[1][0] if code(pat) == 'parallel' and code(pat[1][0]) == 'set' else None)
        if s0 is not None:
            dest = s0[1]; src = s0[2]
            dr = strip_subreg(dest)
            cands = []
            if code(src) in ('reg', 'subreg'):
                cands = [src]
            elif isinstance(src, list) and code(src) not in ('mem', 'const_int', 'symbol_ref', 'const', 'high', 'lo_sum', 'if_then_else', 'call'):
                cands = [o for o in src[1:] if code(o) in ('reg', 'subreg')]
            elif code(src) == 'lo_sum':
                cands = [o for o in src[1:] if code(o) in ('reg', 'subreg')]
            if regno(dr) is not None:
                sreg = regno(dr)
                for cnd in cands:
                    ur = strip_subreg(cnd)
                    ureg = regno(ur)
                    if ureg is None or ureg == sreg:
                        continue
                    if ureg >= 64 and ureg not in reg_qty:
                        continue
                    if ureg < 64 and sreg < 64:
                        continue
                    if ureg < 64:
                        # hard -> pseudo: suggestion
                        if sreg in local:
                            if sreg not in reg_qty:
                                reg_qty[sreg] = len(qties)
                                qties.append(dict(regs=[sreg], birth=2 * n, death=None, refs=info[sreg][0], sugg=set(), copysugg=set(), born_uid=u))
                            q = qties[reg_qty[sreg]]
                            (q['copysugg'] if code(src) in ('reg', 'subreg') else q['sugg']).add(ureg)
                        break  # returns 0: stops? combine_regs returns 0 -> loop continues to next operand
                    if sreg < 64:
                        if ureg in reg_qty:
                            q = qties[reg_qty[ureg]]
                            (q['copysugg'] if code(src) in ('reg', 'subreg') else q['sugg']).add(sreg)
                        continue
                    if sreg not in local or sreg in reg_qty:
                        continue
                    if ureg in dead:
                        qi = reg_qty[ureg]
                        reg_qty[sreg] = qi
                        qties[qi]['regs'].append(sreg)
                        qties[qi]['refs'] += info[sreg][0]
                        combined = ureg
                        break
        # deaths
        for r in dead:
            if r == combined:
                continue
            if r in reg_qty and r >= 64:
                qties[reg_qty[r]]['death'] = 2 * n
            elif r < 64:
                st = hard_birth.pop(r, None)
                hard_live.append((r, st if st is not None else 0, 2 * n))
        # births
        for r, c in sets_of(pat):
            if r >= 64 and r in local and r not in reg_qty:
                reg_qty[r] = len(qties)
                qties.append(dict(regs=[r], birth=2 * n, death=None, refs=info[r][0], sugg=set(), copysugg=set(), born_uid=u))
            if r < 64 and r not in (0, 29):
                hard_birth[r] = 2 * n
            if r in unused:
                if r >= 64 and r in reg_qty:
                    qties[reg_qty[r]]['death'] = 2 * n + 1
                elif r < 64:
                    hard_birth.pop(r, None)
                    hard_live.append((r, 2 * n, 2 * n + 1))
        if kind == 'call_insn':
            for r in list(range(1, 16)) + [24, 25, 31]:
                hard_live.append((r, 2 * n, 2 * n + 1))
        order_rows.append((n, u, kind, ' '.join(body.split())[len(kind)+20:][:90]))
    for r, st in hard_birth.items():
        hard_live.append((r, st, 2 * n + 2))
    for q in qties:
        if q['death'] is None:
            q['death'] = 2 * n + 1
    live_at = {}
    for r, st, en in hard_live:
        for k in range(st, en):
            live_at.setdefault(k, set()).add(r)

    def pri(q):
        L = q['death'] - q['birth']
        if L <= 0:
            return 0
        return int((math.floor(math.log2(q['refs'])) * q['refs'] * 1) / L * 10000) if q['refs'] > 0 else 0

    def free(q, allowed):
        used = set()
        for k in range(q['birth'], q['death']):
            used |= live_at.get(k, set())
        for r in allowed:
            if r not in used:
                return r
        return None

    GR = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 16, 17, 18, 19, 20, 21, 22, 23, 31]
    GR = sorted(GR)
    ids = list(range(len(qties)))
    # suggested first (qty_sugg_compare_1 approx: fewer suggestions first, then priority)
    sug = [q for q in ids if qties[q]['sugg'] or qties[q]['copysugg']]
    sug.sort(key=lambda q: (len(qties[q]['copysugg']) or len(qties[q]['sugg']) * 64, -pri(qties[q]), q))
    phys = {}
    for q in sug:
        cs = qties[q]['copysugg'] or qties[q]['sugg']
        r = free(qties[q], sorted(cs))
        if r is not None:
            phys[q] = r
            for k in range(qties[q]['birth'], qties[q]['death']):
                live_at.setdefault(k, set()).add(r)
    ids.sort(key=lambda q: (-pri(qties[q]), q))
    for q in ids:
        if q in phys:
            continue
        r = free(qties[q], GR)
        phys[q] = r
        if r is not None:
            for k in range(qties[q]['birth'], qties[q]['death']):
                live_at.setdefault(k, set()).add(r)
    uid2n = {r[1]: r[0] for r in order_rows}
    print(f"block insns {blk[0][1]}..{blk[-1][1]}  ({n} numbered)   qtys {len(qties)}")
    print("  rank qty  pri    refs birth death  regs              sim   dump  sugg")
    bad = 0
    for rank, q in enumerate(ids):
        Q = qties[q]
        d = [NAMES.get(hard.get(r), hard.get(r)) for r in Q['regs']]
        sim = NAMES.get(phys[q], phys[q])
        ok = all(x == sim for x in d)
        bad += not ok
        if verbose or not ok or True:
            print(f"  {rank:3d} q{q:<3d} {pri(Q):6d} {Q['refs']:4d} {Q['birth']:5d} {Q['death']:5d}  {','.join('r%d' % r for r in Q['regs']):16s} {sim!s:5s} {','.join(map(str, d)):6s} {'*' if not ok else ''} {sorted(Q['copysugg'])}{sorted(Q['sugg'])}")
    print(f"mismatches vs dump: {bad}")
    if verbose:
        for k, u, kind, txt in order_rows:
            if k >= int(verbose_from):
                print(f"   {2*k:4d} {u:5d} {txt}")


main()
