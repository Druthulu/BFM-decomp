---
ts: 2026-11-06T08:36:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ejRRfQ9KjSNZCUJL2NBY
---
Interesting! Each single keepalive alone suffices for score 0. So either one keeps the allocation right. The mechanism: the keepalive extends the live range of off (or t3), increasing priority of... hmm, how does that fix the a0-copy register?

Wait — maybe it's not priority but death notes / REG_N_DEATHS or the "last use" of the params. Let me test removing both (w1) = score 9. So one of them is needed. Now we need real C that achieves the same liveness.

Key insight: keepalive on `off` makes off live across the whole body; keepalive on t3 makes t3 live across h[0..1] updates. Either one restores score 0. Why would either fix the a2/a3 assignment? Maybe both affect register priority of the a0 copy? Hmm, that seems unrelated. Perhaps they affect the scheduler (sched1) rather than allocation: the asm is a scheduling barrier, preventing reordering. But the instruction order is identical in mine w1 and target... Let me check: in w1, the diff was only register names, same order. And score 9 is REG-caller. So the *order* is fine; only register assignment differs.

Maybe the asm keeps a pseudo live so that global/local alloc sees different conflict sets. Let's get dumps to see.

Let me create a dump script under G25 (copy of T10 dump.sh with paths adapted).

Actually the T10 dump.sh writes to .run/P40/T10/<fn>/dump — outside my shard. I'll write G25/dump.sh:

```bash
#!/bin/bash
# dump.sh <itemdir> <body.c> <tag>: cc1 pass dumps of the spliced candidate into <itemdir>/dump_<tag>
d=$(realpath $1); f=$(realpath $2); tag=$3; out=$d/dump_$tag
rm -rf $out; mkdir -p $out/sub
cd /home/musashi/bfm-decomp; tu=$(cat $d/tu)
k=$(/usr/bin/python3 tools/delever_search.py --try $tu $(cat $d/fn) $f --body --keep 2>&1 | grep -o '/[^ ]*cand.o'); dd=$(dirname $k)
cp $dd/*.c $out/sub/; [ -d $dd/shared ] && cp -r $dd/shared $out/; [ -d $dd/inc ] && cp -r $dd/inc/. $out/sub/ 2>/dev/null
DUMP_ROOT=$out bash tools/cc1_dumps_tu.sh $(ls $out/sub/*.c) $tag >/dev/null 2>&1
rm -rf $dd
echo $out
```

Need to check cc1_dumps_tu.sh usage. Let me read its head.
