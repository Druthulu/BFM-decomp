---
ts: 2026-11-06T18:46:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DAnrwY3Lq1qlqKSbh4N5
---
The 4 global allocnos: 75 (a6, pri 28333, refs 17), 76 (pri 19285, refs 9, pointer), 72 (pri 18000, refs 15, pointer, prefers a0), 73 (pri 11666, refs 7).

Dispositions: 72→$4 (a0), 73→$6 (a2), 75→$5 (a1), 76→$3 (v1).

Hmm, which is which? Let me map: the source variables: a6 (int), a7 (pointer), a5 (int), v1 (pointer), v0 (pointer). 

r72 prefers a0 — a param copy? a0 is the param (unsigned short *a0); r72 = the param copy (used 15 refs). r73 = a5 (refs 7, dies in 0 places?); r75 = a6 (refs 17); r76 = v1? or a7?

Dispositions: 75→$5 (a1), 76→$3 (v1), 72→$4 (a0), 73→$6 (a2).

The target: a6 = a2 ($6), a5 = a1 ($5), v1 = $3, a7 = $7 (a3). Hmm, but the table shows only 4 global allocnos and $7 (a3) is used as a hard reg ("Hard regs used: 2 3 4 5 6 7") — 73→$6 (a2), and $7 (a3) is used by... one of the local pseudos? The dispositions list only the 13 pseudos; a3 ($7) appears in "Hard regs used" but no pseudo is assigned to $7? Hmm, the dispositions show 72 in 4, 73 in 6, 75 in 5, 76 in 3, and the locals in $2. So $7 is used by... the target uses a3 = $7. In mine, a3 is not used? But the diff showed mine using a3 ($7) for one insn (the copy). Hmm, the dispositions don't show a $7 assignment. Let me look at the final .s / the .lreg.

Wait, the diff said mine[3] = `move a3,v1` — so mine DOES use $7. But no pseudo is assigned $7 in the dispositions... unless the pinned orig has a7→$7 and mine has... Hmm, the dispositions are for MY build (w1). Let me re-read: mine[1] lui v1; mine[2] addiu v1; mine[3] move a3,v1. So mine uses $3 (v1) for the symbol and $7 (a3) for the copy. But the dispositions show 76 in 3 (v1) and none in 7.

Hmm, maybe a3 = $7 is the *target's* register (in the diff's right column). Let me re-read the dt.sh output:

```
  replace mine[1:4] target[1:4]
        1  lui	v1,0x0                         | lui	a3,0x0
        2  addiu	v1,v1,0                      | addiu	a3,a3,0
        3  move	a3,v1                         | move	v1,a3
```
The left column is mine, the right is target. So mine: `lui v1; addiu v1; move a3,v1`; target: `lui a3; addiu a3; move v1,a3`.

So in MINE, the symbol goes to $3 (v1) and is copied to $7 (a3). In TARGET, the symbol goes to $7 (a3) and is copied to $3 (v1).

Which pseudo is which? Source: `a7 = &D_8011FD10; v1 = a7;`. So a7 gets the symbol and v1 the copy. Mine: a7 = $3, v1 = $7. Target: a7 = $7, v1 = $3.

But the alloc_table dispositions say 76 in 3 and no 7... Hmm, maybe a7 and v1 are NOT global allocnos; they might be local? a7/v1 are live across the loop → global. The 4 global allocnos: 75 (a6, refs 17 — the loop counter, live across), 76, 72, 73.

Wait, maybe the pseudos are: 72 = a0 (param, prefers a0 — the prologue copy), 73 = a5? (refs 7), 75 = a6 (refs 17), 76 = ? (refs 9, pointer, conflicts v0,a3,sp).

Hmm, a7 and v1: two pointers, each with refs ~9-15. 76 has refs 9 (pointer) and 72 has refs 15 (pointer, prefers a0). But 72 prefers a0 → that's the param copy a0. Hmm, but a0 is used 7 times in the stores... 

Let me look at the .rtl dump for the pseudo mapping. Let me grep the .rtl for the function.
