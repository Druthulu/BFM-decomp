---
ts: 2026-11-06T21:46:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BMzMhWVPneZRgawCrURD
---
This is getting deep. Simpler path: use the recipe from delever_search itself via a small script that mimics Scorer's tgt extraction:

```python
import sys
sys.path.insert(0,'tools')
import delever_search as ds, delever_oracle as oracle, masked_diff as md
recs = ds.recs_for(tu, fn)   # check signature
base = oracle.baseline_path(recs[0]['obj'])
for i, ins in enumerate(md.insns_from_object(str(base), fn)):
    print(i, ins.get('asm') or ...)
```
Need the insn dict fields. Let me check md.insns_from_object return fields.

Actually, do I really need the target asm? It'd help but maybe I can infer. The diff already says the only difference is the missing `move v1,a0` (plus shifted positions). So target has that move at 27. I know enough.

Let me try candidate w4: move the copy into both arms.

Actually simpler idea first: put the copy in the then/else arms only, or restructure as:

```
{
    int iv2c;
    if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; }
    else { t = ...; iVar2 = t + 1; param_2 <<= 4; }
    iv2c = iVar2;
    one = 1;
    if (iv2c != one) uVar5 = 0;
}
```
same as now.

Try: copy in the else arm and then-arm:
```
if ((short)iVar4 == six) { iVar2 = 1; iv2c = iVar2; uVar5 = 0; }
else { t = ...; iVar2 = t + 1; param_2 = param_2 << 4; iv2c = iVar2; }
```
Hmm, iv2c declared in the enclosing block. The then-arm: iVar2 = 1 then iv2c = iVar2 → cse equates iv2c with iVar2 within the block, and iv2c's use is in the join block → copy stays? The copy `iv2c = iVar2` at the end of the then block: cse's local copy table would note it, but since iv2c is used only in another block, the copy isn't deleted (it can't rewrite the use). And local-alloc: iVar2 in the then-arm is 1 (li), and iv2c = move → might be coalesced? iVar2 lives on (used later), so no.

But wait — the target has exactly ONE move v1,a0 in the else path. Adding an extra copy in the then path might add an extra move (li v1,1?) — but perhaps the target also has that. Since the target's instruction count is 56 and mine 55, only one extra instruction total. If I add copies in both arms, I might add 2 → 57. Hmm, unless one is folded.

Alternative: assign iv2c only in the else arm; in the then-arm, iv2c = 1 is also needed semantically for the compare. But wait, in the target the compare `if (iv2c != one)` happens for both paths. Where does iv2c get its then-arm value in the target? Let me actually get the target asm to see. I'll write the dis script — it's worth it.

Let me write .run/P40/T11/RM3x/dis.py that prints target asm and candidate asm side by side (or separately). Need insns_from_object fields. Let me check masked_diff.
