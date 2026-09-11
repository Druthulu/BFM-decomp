# func_8017F0F4 (ov_SC06_018_jr_8017C24C.c) — T7 d28, P36 S104

**Score 0, ZERO levers** (tree: 2 pins, $16 on case 0's `s0v` and $4 on case 0's `p20` → 0). PACK/body.c is agent d21's
port of its func_8018179C close (`.run/P36/agents/ov_SC06_010__func_8018179C/scratch/copies/func_8017F0F4_body.c`),
confirmed by d28's own `--try`: `score 0 (OTHER; mine 207 ins, target 207) — MATCH`. The full mechanism is d21's:
`.run/P36/agents/ov_SC06_010__func_8018179C/mechanism.md`. This file gives the summary and what d28's own reading
added before the coordinator stopped the search.

## (a) Residual (body_free = 63; regen best free_109 = 7)
1. A register permutation: the parameter `a0` in $s0 and case 0's `s0v = a0+0x88` / case 3's `ret` in $s1; the target
   has a0=$s1, s0v=$s0, ret=$s0, s2v=$s2. Same instruction count.
2. Case 0's tail: `p20 = *(a0+0x20)` in $v1 and the lhu/addu temp in $a0; the target has p20=$a0, temp=$v1 (case 2's
   identical code already gets this right in the free body).

## (b) Passes and decisions
1. global.c `allocno_compare` (:594-607) and `find_reg` (:945-990). With no REG_ALLOC_ORDER on MIPS (`config/mips/mips.h`
   has none), a call-crossing allocno takes the lowest free callee-saved register, so a0 lands in $17 only if something
   already holds $16 while a0 is live, or outranks it. a0's allocno (r72: 56 refs over 179 insns, priority 15642) comes
   before every other call-crossing pseudo in the free body (`.greg` order `144 72 127 …`; ret r149 4000, s0v r101 2307,
   s2v r148 1875), so it takes $16.
   - d28's reading (`scratch/dumps_b109`): free_109's score 7 got the permutation right by accident. Its R9 swap hoists
     case 3's `v1p` read above the B744 call, so v1p is block-local and crosses a call. local-alloc gives it $16, and
     r72's `.greg` conflict line gains `s0`, pushing a0 to $17. The target reads v1p AFTER the call, so the $16 holder
     in the target has to be something else. That is the question d21's merge answers.
   - d21's answer: one function-scope `s32 ret;` shared by the three func_8012BE98 results gives ONE allocno with
     6 refs over a summed live length of 5. Its priority is floor_log2(6)·6/5·10000 = 24000, which beats 15642. It crosses
     a call in case 3, so it takes $16 first and a0 takes $17. Combine then folds the case-0/case-1 `(set ret v0)` copies
     into their compares (combine.c:914-917), so those pieces never show in the bytes. flow counted them before combine
     ran, though, so the priority keeps them.
2. local-alloc `block_alloc`, three-quantity birth order (local-alloc.c:1486-1500). Case 0's tail block has 3 qtys, so
   they are allocated in birth order: p20 → $v1. The compound `*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;` adds a
   4th quantity, which sends the block through the real qsort (`qty_compare_1`, :1598), so p20 → $a0.
   - d28's independent check of this channel: on the free_109 base, the ov_SC06_010 sibling func_8017FE3C's own
     spelling (`tmp0 = *(s32 *)(a0 + 0x20); v1p = tmp0;` with a function-scope `s32 tmp0`) also closed the case-0 hunk
     (7 → 3, `scratch/t1_score3.c`). It changes the quantity count the same way. d21's compound is the cleaner text and
     is what PACK/body.c uses.

## (c) Moves (in PACK/body.c)
- Replace the three per-case `s32 ret;` declarations with one function-scope `s32 ret;` (global.c:594-607 priority).
- Case 0: write the re-read + mask as the compound `*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;`
  (local-alloc.c:1486-1500).

## (d) Generator proposal
Two rules:
- **R-merge-callret:** when the self pointer lands one callee-saved register too low, merge the same-typed call-result
  temps declared per case/arm into one function-scope variable. The summed refs over the summed live length outrank the
  pointer (global.c:594-607).
- **R-qty3:** when a block-local pair is swapped in one block while identical code elsewhere allocates correctly, change
  that block's quantity count to or from 3 (inline a re-read into a compound, or merge/split a temp) (local-alloc.c:1486).

## (e) What did not work (bytes, d28)
- free_109 as the base (R9 swap in case 3) scores 7. It gets the permutation right for the wrong reason (a local-alloc'd
  v1p holds $16), so it leaves a case-3 `lw s0` vs `lw v1` hunk plus the case-0 swap.
- free_109 + the sibling's `tmp0` idiom scores 3. The only hunk left is case 3's hoisted v1p read, the compensating error.

## (f) Method notes
- A strong trigger for step 4: when the self pointer holds the wrong callee-saved register and nothing visible in the
  target holds the lower one, compute what could OUTRANK the pointer (merged call-result temps whose copies combine
  deletes). A reading that only uses the target bytes misses this, because the merged pieces do not show in them.
- The regen best's accidental fix, read in `.greg` (r72's conflict line gaining `s0`), is what pointed at the channel.

## (g) Structs question
Not needed: the body closes at 0 with no levers. A struct type for `a0` (fields at 0x20 `*rot_owner`, 0x34 `u16 state`,
0x88 target position, 0xDC `s32 speed`, 0x100/0x102 `s16` timers) would read better. It does not touch either deciding
channel, which are an allocno's refs/live length and one block's quantity count. That is not proven on bytes.

## Copies (same text, all at 0 — d21's table `.run/P36/agents/ov_SC06_010__func_8018179C/scratch/copies/TABLE.md`)
| function | TU | file | --try |
|---|---|---|---|
| func_8017F0F4 | src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c | PACK/body.c | 0 (d28 re-confirmed) |
| func_8018179C | src/ov_SC06_010/ov_SC06_010_jr_8017A4AC.c | ov_SC06_010__func_8018179C/body.c | 0 (d21) |
| func_8017F2E8 | src/ov_SC06_008/ov_SC06_008_jr_8017C294.c | ov_SC06_010__func_8018179C/scratch/copies/func_8017F2E8_body.c | 0 (d21) |
| func_8018BDE0 | src/ov_SC06_032/ov_SC06_032_jr_80182890.c | …/copies/func_8018BDE0_body.c | 0 (d21) |
| func_8018E428 | src/ov_SC06_024/ov_SC06_024_jr_80186F00.c | …/copies/func_8018E428_body.c | 0 (d21) |
| func_8018FA80 | src/ov_SC06_033/ov_SC06_033_jr_8018D98C.c | …/copies/func_8018FA80_body.c | 0 (d21) |
| func_8018BF50 | src/ov_SC06_022/ov_SC06_022_jr_80184A28.c | …/copies/func_8018BF50_body.c | 0 (d21) |
