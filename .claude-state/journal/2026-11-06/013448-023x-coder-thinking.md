---
ts: 2026-11-06T08:34:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_o5a9ipBjgXA1gvVH44l2
---
I'll write a helper script under my shard dir `tgt.py`:

```python
import sys, pathlib
REPO = pathlib.Path('/home/musashi/bfm-decomp')
sys.path.insert(0, str(REPO/'tools'))
import delever_oracle as oracle, masked_diff as md
tu, fn = sys.argv[1], sys.argv[2]
recs = oracle.recipes_by_src(oracle.load_recipes()['recipes']).get(tu, [])
base = oracle.baseline_path(recs[0]['obj'])
for i,x in enumerate(md.insns_from_object(str(base), fn)):
    print(i, x['mnem'])
```

This is a scratch helper under my shard dir — allowed ("write only under .run/P40/T11/G25/ plus appends to moves.md"). Good.

Also for mine, objfn.sh style. But dt diff gives positions with mine|target; I want full mine too. Let me write `mine.py` too or use --keep + objdump. Perhaps one script `both.py` that takes item dir and body file and prints numbered mine and target. Let's do:

```python
# both.py <itemdir> <body.c> [--keep]
import sys, subprocess, pathlib, re
REPO=...
sys.path.insert(0, str(REPO/'tools'))
import delever_oracle as oracle, masked_diff as md
import delever_search as ds
d=pathlib.Path(sys.argv[1]).resolve(); body=pathlib.Path(sys.argv[2]).resolve()
tu=(d/'tu').read_text().strip(); fn=(d/'fn').read_text().strip()
```

But to compile mine I'd need the same mechanism (--try --keep). Easiest: shell script combining delever_search --try --keep and objdump. Like objfn.sh. I'll copy the objfn pattern but adapted:

```bash
#!/bin/bash
# both.sh <itemdir> <body.c>: numbered mine and target listings
d=$(realpath $1); f=$(realpath $2); tu=$(cat $d/tu); fn=$(cat $d/fn)
cd /home/musashi/bfm-decomp
k=$(/usr/bin/python3 tools/delever_search.py --try $tu $fn $f --body --keep 2>&1 | grep -o '/[^ ]*cand.o')
mipsel-linux-gnu-objdump -drz --disassemble=$fn $k | grep -P '^\s+[0-9a-f]+:' | sed ...
/usr/bin/python3 .run/P40/T11/G25/tgt.py $tu $fn
rm -rf $(dirname $k)
```

Hmm, --keep prints the object path; does it remove it otherwise? dis.sh does rm -rf dirname. OK.

But wait: "One action per command" and commands printing >40 lines go through tools/run.sh. Listings are ~47 lines for item 1; over 40. Rule: "A command that may print more than ~40 lines runs through bash tools/run.sh <name> -- <cmd>". Hmm, but my helper prints to a file under shard; I could write listing to a file and Read it (Read tool). That avoids dumping. I'll have both.sh write to $d/listing.txt and print nothing; then Read the file. Good — Read tool on ~50 lines is fine (<20k chars).

Let me create both.sh and tgt.py.

Actually simpler: one python script that does both via subprocess. But bash is fine.

Let me write tgt.py and both.sh under G25/.
