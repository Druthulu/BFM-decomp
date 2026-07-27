#!/usr/bin/env python3
"""Close the three gates match_one is blind to, for func_80183814.

match_one masks R_MIPS_26 (jal / internal j) and HI16/LO16, so a wrong callee
(§87), a duplicated-or-wrong jump destination (§81) and a mis-derived data
address (§84) all pass it clean.  Every symbol in this project encodes its own
vram address in its name, so each relocation can be RESOLVED and compared with
the address the target's disassembly names at the same instruction index.

MIPS ELF is REL: the addend is implicit in the instruction field, so
  A = (imm_hi << 16) + sign_extend16(imm_lo)   for a HI16/LO16 pair
and objdump -r does NOT print it.  That is exactly the §84 trap.

usage: reloc_verify.py <obj.o> <target.s>
"""
import re, sys, subprocess

OBJ, TGT = sys.argv[1], sys.argv[2]
BASE = 0x80183814


def addr_of(sym):
    m = re.search(r'(8[0-9A-Fa-f]{7})', sym)
    return int(m.group(1), 16) if m else None


def s16(x):
    return x - 0x10000 if x & 0x8000 else x


# ---------------- target: index -> record -----------------------------------
tgt_call, tgt_data, tgt_jump = {}, {}, {}
i = 0
for line in open(TGT, errors='replace'):
    m = re.match(r'\s*/\*\s*\S+\s+([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})\s*\*/\s*(\S+)\s*(.*)', line)
    if not m:
        continue
    mnem, ops = m.group(3), m.group(4).strip()
    if mnem in ('jal', 'j'):
        if ops.startswith('.L'):
            tgt_jump[i] = (int(ops[2:], 16) - BASE) // 4      # internal jump -> index
        else:
            tgt_call[i] = (addr_of(ops), ops)
    else:
        h = re.search(r'%(hi|lo)\(([^)]+)\)', ops)
        if h:
            a = addr_of(h.group(2))
            if a is not None:
                tgt_data[i] = (h.group(1).upper(), a)
    i += 1
NT = i

# ---------------- mine: index -> record -------------------------------------
dis = subprocess.run(['mipsel-linux-gnu-objdump', '-dr', '--section=.text', OBJ],
                     capture_output=True, text=True).stdout
words, relocs = [], {}
idx = -1
for line in dis.splitlines():
    m = re.match(r'\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*)', line)
    if m:
        idx += 1
        words.append((int(m.group(2), 16), m.group(3), m.group(4)))
        continue
    r = re.match(r'\s*[0-9a-f]+:\s+(R_MIPS_\S+)\s+(\S+)', line)
    if r and idx >= 0:
        relocs[idx] = (r.group(1), r.group(2))

# pair HI16 with its LO16 to recover the implicit addend
mine_data, mine_call, mine_jump, local = {}, {}, {}, []
hi_pending = {}
for k in sorted(relocs):
    kind, sym = relocs[k]
    w = words[k][0]
    if kind == 'R_MIPS_26':
        if sym.startswith('.'):
            mine_jump[k] = (w & 0x3FFFFFF)          # local: word target index
            local.append(k)
        else:
            a = addr_of(sym)
            mine_call[k] = ((a + ((w & 0x3FFFFFF) << 2)) if a is not None else None, sym)
    elif kind == 'R_MIPS_HI16':
        hi_pending.setdefault(sym, []).append(k)
    elif kind == 'R_MIPS_LO16':
        if sym.startswith('.'):
            local.append(k)
            continue
        lo = s16(w & 0xFFFF)
        ks = hi_pending.get(sym)
        if ks:
            khi = ks.pop(0)
            A = ((words[khi][0] & 0xFFFF) << 16) + lo
            mine_data[khi] = ('HI', addr_of(sym) + A)
            mine_data[k] = ('LO', addr_of(sym) + A)
        else:
            mine_data[k] = ('LO', addr_of(sym) + lo)
for sym, ks in hi_pending.items():
    for k in ks:
        local.append(k)

bad = []
for k, v in tgt_call.items():
    m = mine_call.get(k)
    ok = m is not None and ((v[0] is not None and m[0] == v[0]) or m[1] == v[1])
    if not ok:
        bad.append(('CALL', k, v[1], m[1] if m else None))
for k, v in tgt_data.items():
    m = mine_data.get(k)
    if m is None or m[1] != v[1]:
        bad.append(('DATA', k, '%s %08X' % (v[0], v[1]),
                    (m[0], '%08X' % m[1]) if m else None))
for k, v in tgt_jump.items():
    if mine_jump.get(k) != v:
        bad.append(('JUMP', k, v, mine_jump.get(k)))

print('checked: %d jal callees, %d %%hi/%%lo data addresses, %d internal j targets'
      % (len(tgt_call), len(tgt_data), len(tgt_jump)))
print('mismatches: %d' % len(bad))
for b in bad[:25]:
    print('   %-5s idx %5d  target=%s  mine=%s' % b)
extra = sorted(set(mine_data) - set(tgt_data)) + sorted(set(mine_call) - set(tgt_call))
if extra:
    print('mine has reloc where target has none at idx: %s' % extra[:10])
if not bad and not extra:
    print('\nALL RESOLVED: every jal callee, every %hi/%lo address (INCLUDING the '
          'derived-offset sites) and every internal j destination matches the target.')
