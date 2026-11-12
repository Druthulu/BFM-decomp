#!/usr/bin/python3
"""map_cite_check.py: recheck every build/us/SLUS_007.26.map:<line> citation in config/names.tsv and src/ comments
against the current linker map (from 3.43 T9; run after a clean build, from the repo root).
Usage: /usr/bin/python3 tools/map_cite_check.py [--fix]
  --fix: move a drifted line number to the unique map line holding the cited name/object.
Exit 1 when any citation drifted and --fix was not given."""
import re, subprocess, sys
MAP = open('build/us/SLUS_007.26.map').read().split('\n')
fix = '--fix' in sys.argv
RX = re.compile(r'SLUS_007\.26\.map:(\d+)(?: \((\w+)|: linked PsyQ \w+ (\S+\.o))')
def want(name, obj):
    return (lambda l: re.search(r'\b%s\b' % re.escape(name), l) is not None) if name else (lambda l: obj in l and '.text' in l)
files = ['config/names.tsv'] + [f for f in subprocess.run(['git', 'grep', '-l', 'SLUS_007.26.map:', '--', 'src'],
                                                       capture_output=True, text=True).stdout.split()]
bad = 0; checked = 0
for f in files:
    t = open(f).read(); out = t
    for m in set(RX.finditer(t)):
        pass
    def sub(m):
        global bad, checked
        n, name, obj = int(m.group(1)), m.group(2), m.group(3)
        ok = want(name, obj); checked += 1
        if 0 < n <= len(MAP) and ok(MAP[n - 1]): return m.group(0)
        hits = [i for i, l in enumerate(MAP, 1) if ok(l) and (('0x' in l) if name else True)]
        # a name's defining line: the symbol line (address then the name) or the alias assignment
        hits = [i for i in hits if (not name) or re.match(r'^\s+0x[0-9a-f]+\s+%s(\s|$| =)' % re.escape(name), MAP[i - 1])]
        bad += 1
        print('DRIFT %s: map:%d (%s) -> candidates %s' % (f, n, name or obj, hits[:4]))
        if fix and len(hits) == 1: return m.group(0).replace(':%d' % n, ':%d' % hits[0], 1)
        return m.group(0)
    out = RX.sub(sub, t)
    if fix and out != t: open(f, 'w').write(out)
print('citations checked', checked, 'drifted', bad)
sys.exit(1 if bad and not fix else 0)
