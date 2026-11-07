---
ts: 2026-11-06T18:48:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tP0Bc4aCG4b4OiffB0Ul
---
Dispositions: 72→$4 (a0), 73→$6 (a5 = a2), 74→$7 (a7 = a3), 75→$5 (a6 = a1), 76→$3 (v1).

So a7 = $7 (a3) and v1 = $3 — that MATCHES the target! But the score is 3 with the diff showing mine[1] lui v1... Hmm, that contradicts. Wait, this dump is for w1's body compiled standalone; the dispositions say 74→7, 76→3 — exactly the target.

But dt.sh scored w1 as 3 with mine using v1 for the symbol. Hmm! Maybe the standalone header TU differs from the includer TU (different codegen?). Or maybe the dt.sh score was computed with a *stale* w1? No...

Wait, the earlier diff was:
```
1  lui v1,0x0     | lui a3,0x0
2  addiu v1,v1,0  | addiu a3,a3,0
3  move a3,v1     | move v1,a3
```
The left column (mine) = the *candidate* asm. Hmm, but the dispositions from the standalone compile say a7=$7.

Hold on — maybe the diff's "mine" column is the function compiled from the *current src* (the pinned orig) and the "target" is the bank? No: delever_search --try compiles the candidate and compares to the target (the bank). The "mine" is the candidate.

But my standalone dump (w1 body) gives a7=$7. The includer compile might differ! The includer TU (ov_MAIN_012) may have other functions affecting global allocation? No, global-alloc is per-function. Hmm.

But wait: the diff's mine[1..3] = `lui v1; addiu v1; move a3,v1`. In the source, `a7 = &D_8011FD10; v1 = a7;` — the symbol goes to a7, copied to v1. If a7=$7 and v1=$3, the asm would be `lui a3; addiu a3; move v1,a3` — the TARGET's form. So mine should be the target's form... unless the diff columns are swapped in my reading!

Let me re-read the dt.sh output format:
```
  replace mine[1:4] target[1:4]
        1  lui	v1,0x0                         | lui	a3,0x0
        2  addiu	v1,v1,0                      | addiu	a3,a3,0
        3  move	a3,v1                         | move	v1,a3
```
Hmm, "mine[1:4] target[1:4]" — the left is mine, right is target. So mine = lui v1, addiu v1, move a3,v1 → a7=$3, v1=$7.

But my standalone dump says 74(a7)→$7, 76(v1)→$3. Contradiction!

Unless the standalone header compile differs from the includer compile because of... hmm. Let me directly check the candidate's asm from the standalone dump (t2.s) for the function.

Let me extract the function's asm from the dump's t2.s.
