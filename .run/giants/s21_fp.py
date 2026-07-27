#!/usr/bin/env python3
"""§71 callee-set fingerprint: score every MATCHED function in src/ against a target callee set.
Shared symbols only (< 0x80128158)."""
import os, re, sys, collections

SHARED_MAX = 0x80128158
CALL = re.compile(r'\bfunc_([0-9A-Fa-f]{8})\b')
DEF  = re.compile(r'^[A-Za-z_][A-Za-z0-9_ \*]*\bfunc_([0-9A-Fa-f]{8})\s*\(')

def shared(names):
    return {n.upper() for n in names if int(n, 16) < SHARED_MAX}

# target set from the .s
tgt_asm = sys.argv[1]
tgt = shared(re.findall(r'jal\s+func_([0-9A-Fa-f]{8})', open(tgt_asm).read()))
print('TARGET shared callee set (%d):' % len(tgt), ' '.join(sorted(tgt)))

# walk src, split into functions by brace depth
results = []
for root, dirs, files in os.walk('src'):
    for f in files:
        if not f.endswith('.c'):
            continue
        p = os.path.join(root, f)
        try:
            lines = open(p, errors='replace').read().split('\n')
        except Exception:
            continue
        i = 0
        n = len(lines)
        while i < n:
            m = DEF.match(lines[i])
            if not m or 'INCLUDE_ASM' in lines[i] or lines[i].rstrip().endswith(';'):
                i += 1
                continue
            addr = m.group(1).upper()
            # gather body by brace balance
            depth = 0
            started = False
            body = []
            j = i
            while j < n:
                body.append(lines[j])
                depth += lines[j].count('{') - lines[j].count('}')
                if '{' in lines[j]:
                    started = True
                if started and depth <= 0:
                    break
                j += 1
            txt = '\n'.join(body)
            calls = shared(CALL.findall(txt)) - {addr}
            if calls:
                results.append((addr, p, calls, len(body)))
            i = j + 1

scored = []
for addr, p, calls, nl in results:
    inter = tgt & calls
    if not inter:
        continue
    jac = len(inter) / len(tgt | calls)
    cont = len(inter) / len(tgt)
    scored.append((jac, cont, len(inter), addr, p, nl, sorted(inter)))
scored.sort(reverse=True)
print('\n%-6s %-6s %-4s %-10s %-6s %s' % ('jac', 'cont', 'n', 'func', 'lines', 'file / shared-overlap'))
for jac, cont, ni, addr, p, nl, inter in scored[:30]:
    print('%.3f  %.3f  %-4d func_%s %-6d %s  {%s}' % (jac, cont, ni, addr, nl, p, ' '.join(inter)))
print('\ntotal matched fns scanned with >=1 shared callee: %d' % len(results))
