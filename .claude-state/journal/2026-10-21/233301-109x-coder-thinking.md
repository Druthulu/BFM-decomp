---
ts: 2026-10-22T05:33:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_nJP36o8439Pd0ZnjhV3F
---
p_qt's residual (4): the c6c byte load and the `q-0x48` s32 load are swapped:
- mine[29] `lbu a0,108(s0)` (c6c → a0) and mine[31] `lw v0,-72(s0)` (the q-0x48 load → v0).
- the target: mine[29] should be `lw a0,-72(s0)` and mine[31] `lbu v0,108(s0)`.

So the target loads the q-0x48 value FIRST (into a0) and the c6c byte second (into v0 = $2). Mine loads c6c first (into a0) and the q-0x48 second (into v0).

The notes said: "the residue is the `lw a0,-72(s0)` / `lbu v0,108(s0)` pair: the ROM loads the `q - 0x48` value FIRST and into $4, the body loads `c6c` first and into $4".

So I need to reorder the statements: the `*(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);` store's load BEFORE the `c6c = *(u8 *)(q + 0x6C);` load.

Hmm! The p_q00-p_q05 permutations (with the q pin only) put the three s32 copies in various orders but the c6c load was always last. Let me now permute with the c6c load in different positions, keeping the q+tbl pins.

Current block:
```
func_8017869C((s32)p);
*(s32 *)(q - 0x1C) = *(s32 *)(q - 0x50);
c6c = *(u8 *)(q + 0x6C);
*(s32 *)(q - 0x18) = *(s32 *)(q - 0x4C);
tbl = D_8011DB08;
*(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);
```
The target's order (from the ROM listing):
```
80178508: lw v0,-80(s0)     ; q-0x50
8017850c: lw v1,-76(s0)     ; q-0x4C
80178510: lw a0,-72(s0)     ; q-0x48
80178514: sw v0,-28(s0)     ; q-0x1C = q-0x50
80178518: lbu v0,108(s0)    ; c6c
8017851c: sw v1,-24(s0)     ; q-0x18 = q-0x4C
80178520: lui v1,0x8012
80178524: lw v1,-9464(v1)   ; tbl
80178528: beqz v0,...
8017852c: sw a0,-20(s0)     ; q-0x14 = q-0x48
80178530: lbu v0,109(s0)    ; q+0x6D
```
So the ROM's order: the three loads (q-0x50, q-0x4C, q-0x48) FIRST, then the c6c load, then the stores.

So the source order should be: load all three values, then the c6c load, then the stores. I.e.:
```
s32 w1 = *(s32 *)(q - 0x50);
s32 w2 = *(s32 *)(q - 0x4C);
s32 w3 = *(s32 *)(q - 0x48);
c6c = *(u8 *)(q + 0x6C);
*(s32 *)(q - 0x1C) = w1;
*(s32 *)(q - 0x18) = w2;
*(s32 *)(q - 0x14) = w3;
tbl = D_8011DB08;
```
Hmm, but that's the "m11/p_qtmp" style (the temps) which scored 6 (92 ins) ✗ hmm.

Hmm, p_qtmp = 6 with 92 ins. Hmm.

Hmm, the difference: the temps version has 92 ins (one extra). Hmm.

Hmm, but the ROM's order is: the three loads, then c6c, then the stores. The scheduler reorders anyway. Hmm.

Let me try the permutation where the c6c load comes after the three s32 copies (in the source):
```
*(s32 *)(q - 0x1C) = *(s32 *)(q - 0x50);
*(s32 *)(q - 0x18) = *(s32 *)(q - 0x4C);
*(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);
c6c = *(u8 *)(q + 0x6C);
tbl = D_8011DB08;
```
That's the p_q00 variant (the permutations with the c6c last) — hmm, p_q00 = 8 (94 ins) ✗.

Hmm, p_q00 = 8 with 94 ins. Hmm, so that reordering gave 94 ins.

Hmm. The best is p_qt = 4 (91 ins ✓) with the original order.

The residual: the c6c load and the q-0x48 load are in the wrong ORDER (mine: c6c first into a0; the target: q-0x48 first into a0).

So in mine, the c6c load takes $4 (a0) and the q-0x48 load takes $2 (v0); in the target, the q-0x48 load takes $4 and c6c takes $2.

Hmm! So the c6c pseudo (no pin) got a0 and the q-0x48 temp got v0; the target has them swapped.

Since the c6c load is a byte load and the q-0x48 is a word load, maybe their priorities differ.

Hmm, the target's order: the q-0x48 load is the third of the three s32 loads (in the same chain as the others: v0, v1, a0 ✓ — the three loads take $2/$3/$4 in order) and the c6c load comes after (into $2, reusing the dead v0 ✓).

So in the target, the three s32 loads form a chain in $2/$3/$4 and the c6c byte load reuses $2 (after the first s32 load dies) ✓.

In mine, the c6c load took $4 and the q-0x48 load took $2 → so the ORDER of the loads differs: mine loads c6c BEFORE the q-0x48 value.

So the source order matters: in mine, the c6c load comes before the q-0x48 load in the source (the c6c assignment is before the `*(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);` statement ✓) and gcc kept that order (the loads are not reordered by the scheduler? or the scheduler did but the register assignment differs).

So: to match, the q-0x48 load must come BEFORE the c6c load in the source:
```
*(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);   <- before the c6c load
c6c = *(u8 *)(q + 0x6C);
```
Hmm! But that's what the permutations p_q00-p_q05 did (the q-0x48 store first) → 8 with 94 ins. Hmm, but those permutations moved ALL three s32 copies before the c6c load.

Let me try just moving the q-0x48 store before the c6c load (keeping the others):
```
func_8017869C((s32)p);
*(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);   <- moved up
*(s32 *)(q - 0x1C) = *(s32 *)(q - 0x50);
c6c = *(u8 *)(q + 0x6C);
*(s32 *)(q - 0x18) = *(s32 *)(q - 0x4C);
tbl = D_8011DB08;
```
and a few other variants. Let me generate ~12 variants with the q+tbl pins and different orders of the 5 statements, and score them. This is promising — the residual is only 4!

Let me do it now.
