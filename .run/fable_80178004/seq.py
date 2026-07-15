import re, sys
# compact listing of an RTL dump: insn uid + one-line summary
txt = open(sys.argv[1]).read()
# split on top-level (insn/(jump_insn/(call_insn/(note/(code_label
toks = re.split(r'\n(?=\((?:insn|jump_insn|call_insn|note|code_label|barrier))', txt)
def summ(t):
    m = re.match(r'\((insn|jump_insn|call_insn|note|code_label|barrier) (-?\d+)', t)
    if not m: return None
    kind, uid = m.group(1), m.group(2)
    if kind == 'note':
        nm = re.search(r'NOTE_INSN_(\w+)', t)
        return ('note', uid, nm.group(1) if nm else '')
    if kind == 'code_label': return ('label', uid, '')
    if kind == 'barrier': return ('barrier', uid, '')
    body = ' '.join(t.split('\n')[0:6])
    body = re.sub(r'\s+', ' ', body)
    # find set dest and src heads
    m2 = re.search(r'\(set \(([a-z_]+)[:/ ]([A-Za-z0-9 ]*)', t)
    s = ''
    for pat, rep in [(r'\(set \(reg:SI (\d+)\)\s*\(const_int (-?\d+)\)', lambda g: 'r%s = %s' % (g[0], hex(int(g[1])&0xffffffff))),]:
        pass
    return (kind, uid, body[:150])
for t in toks:
    s = summ(t)
    if s: print('%s %s | %s' % (s[0][:4], s[1], s[2]))
