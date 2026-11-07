---
ts: 2026-11-06T05:10:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WYY0EMYJBUTFaJpYVjxg
---
Baseline orig scores 0. Now I need to remove pin+launder and still score 0.

Let's think about what the pins do here. `raw` pinned $3 (v1), `t` pinned $2 (v0). The launder is between `raw = t;` and `t = raw;`.

Interesting: raw and t are both used. Let's think about the target assembly. I can get a dump. Let me look at the expected diff by scoring a naive lever-free version.

Naive: remove pins and asm:

```c
void func_800CB2C8(void *arg0) {
    ...
    s32 raw;
    s32 t;
    ...
    s1 = CAST_SIGN(...);
    p = ...;
    raw = *(u8*)((u8*)s1 + 0x24);
    t = raw - 0x10;
    if (t < 0) { ... return; }
    raw = t;
    t = raw;   // dead copy, will be removed
    ...
}
```

Hmm. Note `raw = t; t = raw;` — with pins, raw=$3, t=$2, so this materializes moves: move $3,$2 then move $2,$3. The launder prevents cse from merging them. Actually the launder on raw: `__asm__("" : "=r"(raw) : "0"(raw))` forces raw to be set again. Then `t = raw` copies back.

The target asm presumably has: after computing t = raw - 0x10 (v0 = v1 - 0x10?), it stores... Let's dump the target assembly to understand.

Let me check tools to dump. There's tools/cc1_dumps_tu.sh and hdump.sh. But maybe delever_search --explain gives residual. Let's first try a naive lever-free body and see the diff.

Also let me check what the target's expected asm is. Perhaps there's a way: `tools/delever_search.py --explain TU FN` reads one body's residual (no writes). Let me try that on orig to see the diff, and on naive.

Let me write n1.c naive.
