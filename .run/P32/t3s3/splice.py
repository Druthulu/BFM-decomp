import sys, re
tu, asmdir, fn, draft = sys.argv[1:5]
src = open(tu).read()
line = 'INCLUDE_ASM("%s", %s);' % (asmdir, fn)
n = src.count(line)
assert n == 1, "INCLUDE_ASM line for %s occurs %d times in %s" % (fn, n, tu)
body = open(draft).read().rstrip('\n') + '\n'
open(tu, 'w').write(src.replace(line, body))
print("spliced", fn, "into", tu)
