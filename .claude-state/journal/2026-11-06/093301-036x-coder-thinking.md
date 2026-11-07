---
ts: 2026-11-06T16:33:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gFe1FHEYDgVgZHZehfVT
---
So -dl = local_reg_dump (after local_alloc), -dg = global_reg_dump, -df = flow dump, -dc = combine dump. Good.

Let me build the splice+dump script.

cc1 invocation: need `-quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker`. Output .s and dumps in the dir. The dump file names: dump_base_name = output base? print_rtl to files like `tag.lreg`? Let's just run and list.

I'll write a script d.sh in the item dir:

```bash
#!/bin/bash
# d.sh <body.c> <tag>
cd /home/musashi/bfm-decomp
D=.run/P40/T11/O05x/func_8017EAD8__ov_SC05_007_jr_8017BEBC
/usr/bin/python3 $D/splice.py $D/t.i "$(realpath $1)" $D/$2.i
(cd $D && /home/musashi/bfm-decomp/tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -dr -ds -dj -dl -dg -df -dc -dS -dL -dR -dt -dJ -dd $2.i -o $2.s 2>$2.err)
ls $D/$2.* | head
```

splice.py:
```python
import sys
src, bodyf, out = sys.argv[1:4]
lines = open(src).read().split('\n')
start = next(i for i,l in enumerate(lines) if l.startswith('void func_8017EAD8(arg0)'))
# find opening brace
i = start
while '{' not in lines[i]: i += 1
depth = 0
j = i
while True:
    depth += lines[j].count('{') - lines[j].count('}')
    if depth == 0: break
    j += 1
body = open(bodyf).read().rstrip('\n')
new = lines[:start] + body.split('\n') + lines[j+1:]
open(out,'w').write('\n'.join(new))
```

Careful: strings with braces? Body may have none problematic (struct defs no). The .i has no braces in strings here.

Let me write these.
