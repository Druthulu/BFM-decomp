---
ts: 2026-11-06T11:34:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_q17qyNo5hUShW7GgCsvK
---
For header items, the primary rec is the first includer's object. I can get the target disassembly by using --keep on the original body and disassembling cand.o (which for a matching body equals the target). That's the easiest: disassemble orig.c candidate object → that's the target asm (since it matches baseline). Actually --keep prints the candidate object path. Since orig scores 0 (byte identical), its candidate object disassembly = target.

So I can use the objfn.sh pattern with orig.c to get target asm, and with each candidate to get mine.

Let me write a small script under my item dir: dis.sh adapted. Actually I can just copy .run/P40/T10/objfn.sh logic but it references .run/P40/T10/$1 for tu. Let me write my own in the item dir.

Wait, constraints say write only under .run/P40/T11/G29/ plus appends to moves.md. Fine.

Let me create .run/P40/T11/G29/dis.sh.

Actually, simpler: I can run the --try --keep command directly and objdump. Let me write a script:

```bash
#!/bin/bash
# dis.sh <itemdir> <body.c> : disassemble fn from candidate object
d=$(realpath $1); f=$(realpath $2)
tu=$(cat $d/tu); fn=$(cat $d/fn)
cd /home/musashi/bfm-decomp
k=$(/usr/bin/python3 tools/delever_search.py --try $tu $fn $f --body --keep 2>&1 | grep -o '/[^ ]*cand.o')
mipsel-linux-gnu-objdump -drz "$k" | awk -v f="<$fn>:" '$2==f{p=1;next} p&&/^[0-9a-f]+ <.*>:$/{exit} p' | grep -v R_MIPS | sed 's/^ *[0-9a-f]*:\t[0-9a-f]* \t//'
rm -rf $(dirname "$k")
```

Hmm but the --keep scratch removal — the script does rm -rf dirname. That should be under .run scratch. Fine.

But objdump prints "insn" with the raw hex; sed strips. Let me test.

Actually, more useful: get target asm once into a file, then diff mine vs target with a simple tool. Let me do that.

Let me create dis.sh in G29 dir.
