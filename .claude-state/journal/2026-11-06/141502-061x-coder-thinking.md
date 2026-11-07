---
ts: 2026-11-06T21:15:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_csKGEj23BCxl7PVcanng
---
All still 4. m.c ((void)e) probably dropped. l/o still 4 — maybe cse merged and e still 1 use, or the index changed.

Let me check whether l.c/o.c changed the refs: the score is same 4 REG, so likely cse merged.

Time check: ~14:22, 24 min. I should wrap up item 1 soon. But let me try a couple more targeted ideas.

Key realization: I need to raise e's allocno priority. The launder raises n_refs to 4. What real C gives e a 2nd set+use with no code?

Idea: use a conditional assignment with the same value but where the compiler can't fold:
```
if (t < lim) e = (s16 *)D_801E8F78; else e = (s16 *)D_801E8F78;
```
Both arms same → compiler folds to one assignment.

Idea: `e = (t < lim) ? (s16 *)D_801E8F78 : (s16 *)D_801E8F78;` folded.

Idea: use `off` in the e assignment: `e = (s16 *)((u8 *)D_801E8F78 + (off - off));` identity, folded by combine.

Hmm. What about a REAL computation that's value-preserving but not obviously identity: e = (s16*)((u8*)D_801E8F78 + off) then the condition uses e - off? No.

Wait. Maybe the target's semantics allow e to be computed differently. Let me re-read the source:
```
e = (s16 *)D_801E8F78;
if (t < lim) {
    if (*(s16 *)((u8 *)e + off + 2) == 0 || ...) idx = -1;
}
```
off = idx*4. So the address is D_801E8F78 + idx*4 + 2 = D_801E8F78[idx][1]? Since D_801E8F78 is s16[][2], D_801E8F78[idx][1] is at byte offset idx*4 + 2. YES! So the condition is exactly `D_801E8F78[idx][1]`.

So we could write:
```
lim = D_801E8F78[idx][0];
if (t < lim) {
    if (D_801E8F78[idx][1] == 0 || (func(D_801E8F78[idx][1]) & 0xFF) == 0) idx = -1;
}
```
But then off and e might disappear, changing code. The target has sll a1 (off) and e materialized. Let me test this natural form and see. It might produce a different allocation that happens to match, or a different instruction count.

Also, maybe the original C was written with `e` because it needed the pointer. Let me test the natural array form.

Also: what if e is used for the condition but declared as the address of the row: `e = D_801E8F78[idx];` (row pointer)? Then e = D_801E8F78 + idx*4 (row address), and condition `e[1]`. That's a real computation: e = (s16*)D_801E8F78 + idx*... hmm, `e = D_801E8F78[idx]` where D_801E8F78 is s16[][2] → D_801E8F78[idx] is s16*, pointing to row idx. Then e[1] = D_801E8F78[idx][1]. And lim = D_801E8F78[idx][0] = e[0]. 

This is a REAL restructure where e depends on idx, so e's computation uses off! Then e is born after off, and e's live range is short. Let me test:

```
off = idx * 4;
lim = D_801E8F78[idx][0];
e = D_801E8F78[idx];          // = sym + off, real computation
if (t < lim) {
    if (e[1] == 0 || (func(e[1]) & 0xFF) == 0) idx = -1;
}
```
Now e = sym+off (addiu after addu?), and e[1] = e+2. Target: e = sym (lui+addiu), condition address = e+off = sym+off (addu v0,a0,a1). Here e would be sym+off already, so e[1] = e+2 (addiu a0,a0,2?). Different code. Hmm.

But maybe it's worth testing — could produce the same 147 insns with different structure? Unlikely but cheap.

Let me test the natural array forms:
- P: `if (D_801E8F78[idx][1] == 0 || (func(D_801E8F78[idx][1])&0xFF)==0)`
- Q: e = D_801E8F78[idx]; lim = e[0]; condition e[1]
- R: keep e=sym but condition uses `((s16*)e)[off/2+1]`? no.

Let me test P and Q.

Also idea S: the `pad[2]` unused array — remove it. Might change frame/reg. Test.

Let me batch P, Q, S.
