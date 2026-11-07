---
ts: 2026-11-06T09:09:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LQYPrHMtw2OzioNhQQQM
---
141 includers. Now I need score 0 on all 141. That's 141 compiles per candidate. Each compile ~? dt.sh was fast (~seconds). 141 compiles maybe a few minutes. Let me write a loop script that tests all k and reports the first failing k. But each tryinc run spawns a full python process (import cost). Better write a script that imports delever_search and rotates over all includers in one process, printing scores. But delever_search's main with args... I can write a script under my shard dir that loops over k calling ds.main()? main() may re-parse args and re-run; better to call _score_file-like directly.

Actually simpler: write a script that reuses _score_file with a rotation. Let me write .run/P40/T11/G25x/allinc.py:

```python
import sys
sys.path.insert(0,'/home/musashi/bfm-decomp/tools')
import delever_search as ds
orig = ds.recs_for
def run(header, fn, body):
    results=[]
    # get recs
    import delever_oracle as oracle, delever as dl
    by_src = oracle.recipes_by_src(oracle.load_recipes()['recipes'])
    inc = dl.includers()
    recs = orig(header, by_src, inc)
    print(f'{len(recs)} includers')
    for k in range(len(recs)):
        def rot(tu, by_src, inc, k=k):
            r = orig(tu, by_src, inc)
            return r[k:]+r[:k]
        ds.recs_for = rot
        a = argparse.Namespace(try_=(header, fn, body), body=True)
        try:
            rc = ds._score_file(a)
        ...
```

But _score_file prints the score line; I want to capture. It prints one line. I can capture stdout with contextlib.redirect_stdout to a StringIO, then parse score. Compiles are cached? Each k is a different includer src, so distinct compile.

141 compiles × maybe 1-3 s = 3-7 min. For each candidate. That's heavy but needed only for the final MATCH verification, not each candidate. For iteration, use dt.sh (includer 0) and a couple of representative ones. But includer 0 might pass while others fail. The risk: a body scores 0 on includer 0 but not all. Typically for headers, the target object differs per binary? Actually the target insns come from baseline object per includer, and the source body is identical; but surrounding TU differs (different constants/functions). The function's own insns should be identical across includers if it compiles the same; differences arise from... in MIPS, same body -> same insns regardless of TU context (except literal pool/addresses). So score 0 on one includer likely means 0 on all. But addresses of globals could differ (e.g. D_ symbols per overlay?) — no, this function uses no globals. Item 2 uses memcpy and calls; item 3 uses calls and constants. Calls resolve to same addresses within overlay slot 0x80128158? All members share vram 0x80139D04... the function is at same vram, and calls target absolute addresses (same). So likely identical across includers.

Still, the brief demands MATCH only if score 0 on every includer. I'll run all includers for the final body of each item. 141×3 = 423 compiles. Time per compile: dt.sh ~2s. So ~15 min total. Acceptable.

Let me check the actual per-compile cost by timing 5 includers.

But first: item 1 win.c with keepalive removed scored 0 on includer 0. Wait — but does it still contain the $3 pin (pm)? Yes, pins remain (other kind). Kinds row = keepalive only, so MATCH = keepalive gone. win.c has no keepalive asm. But hold on: the pin `register u32 pm __asm__("$3")` — with the keepalive gone, does pm still get used? pm = param_2 & 0xffff; dm = div & 0xffff; rem = pm % dm. So pm is used. Fine.

But wait: the score 0 on includer 0 — is that because the keepalive was redundant? That seems plausible (maybe the keepalive was added historically but current compiler/body doesn't need it). Let me verify on a few includers, then all.

Let me write the allinc.py script.
