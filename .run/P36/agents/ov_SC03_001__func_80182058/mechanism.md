# func_80182058 (ov_SC03_001_jr_8017AE2C.c) — T7 agent c42 — score 10 -> 0, the barrier gone

## (a) The residual in one sentence
COUNT 58 vs 60: the early `if (func_8012BD14(..) > 0x4000) return 0;` block (`j epi / move v0,zero`) is missing — mine
branches `beqz v0` into the case-2 failure's `v0 = 0; j epi` block instead, and that block, now a join, loses the
`move v0,zero` fill of the case-2 `beq` delay slot (a `nop` there). Every `j` offset after it shifts by 8.

## (b) The pass and the decision (read, then proven on `scratch/dumps_free`, `dumps_tree`, `dumps_w2` — `.greg` vs `.jump2`)
Post-reload cross-jumping (`toplev.c:3142` `jump_optimize (insns, 1, 1, 0)`; `jump.c:1969-2000` simple jumps tried
against every other jump to the same label, in chain order; `find_cross_jump` `jump.c:2371`, minimum 2).
Every `return 0` is `(set v0 0)` + `(jump epi)`. Before jump2 the lever-free body has FOUR such blocks: A (the early
return), B (case-2 failure), C (case-4 failure), D (the `default:`). A and C FALL OUT OF A CONDITIONAL JUMP whose label is
right after them. A is processed first; against B: `v0=0` matches (1 insn, minimum 2->1), then both streams reach a
JUMP_INSN (A's `if` jump 18 vs B's `beq` 54) that differ — and because jump 18's label follows A's own jump, the
jump-around-jump discount fires (`jump.c:2516-2519`, `prev_real_insn (JUMP_LABEL (i1)) == e1`): minimum 0, A is MERGED
INTO B (dumps_free `fn.jump2`: label 156 in front of B's insn 58, jump 18 retargeted there; C and D follow).
The target (= the tree's barrier body, dumps_tree) merges everything INTO A instead: the asm insn before A's `v0=0` makes
A's backward walk stop on an INSN-vs-JUMP code mismatch (`jump.c:2412`, no discount), so A finds no partner; D,
preceded by its own label, then merges into A through the label discount (`jump.c:2406-2410`), and B follows once it is
labelled. A survives in place, B becomes `beq hit / j A'` and reorg fills exactly as the target.

## (c) The move that closed it (10 -> 0, byte-proven)
Route the case-2 and case-4 failures to the `default:` block's `return 0` instead of returning in place:

    case 2:
        if (*(u16 *)((s32)p + 0x34) == 1) {
            goto hit;
        }
        goto fail;
    case 4:
        if (*(u16 *)((s32)p + 0x34) != 0) {
            goto fail;
        }
    hit: ...
        break;
    default:
    fail:
        return 0;

Now only TWO `v0=0; j epi` blocks reach jump2 (dumps_w2 `fn.greg`): A (after its conditional) and `fail` (after a
barrier + label). A vs fail: 1 match, then JUMP_INSN vs BARRIER (the stream-2 walk skips the label) -> code mismatch,
no discount, no merge. fail vs A: 1 match + its own label -> minimum 0 -> `fail` merged into A (dumps_w2 `fn.jump2`:
new `code_label 150` before A's insn 22, jumps 115/121/62/70 all retargeted to 150). The target's jump graph exactly.
No asm, no pin, no volatile, no invented term; the stale "LOAD-BEARING barrier" comment is dropped (refuted).

## (d) GENERATOR PROPOSAL
When a `__asm__ __volatile__("")` cross-jump barrier sits before an early `if (..) return K;` and several OTHER
`return K;` statements also fall out of conditionals (`if (..) return K;` inside switch cases / if-chains), rewrite those
others as `goto fail;` to ONE labelled `return K;` (the switch `default:` if it already returns K, else a new label after
the last statement): a labelled block can only be merged INTO the early return (label discount, `jump.c:2406`), never the
reverse, while fall-out-of-conditional returns carry the jump-around-jump discount (`jump.c:2518`) that lets the FIRST
return in insn order be merged away. Keep each branch's polarity: `if (ok) goto hit; goto fail;` (w1's
`if (!ok) goto fail; goto hit;` scores 2 — the `beq`/`bne` inverts).

## (e) What did NOT work (byte evidence)
* w1 (`if (x != 1) goto fail; goto hit;` in case 2): 2 — right jump graph, inverted case-2 branch (`bne ..,epi` + `j hit`).
* w4 (case 2 via `fail`, case 4 keeps `return 0;`): 11 — C is still a fall-out-of-conditional return; A merges into C.
* w6 (`fail:` as a trailing `return 0;` after the final return, default keeps its own): 11 — A merges again.
* w3 (switch restructured so failures `break` to a `return 0` after the switch, successes `goto done`): 12 — layout moves.
* The mechanical search (646 compiles, R7/R8/R10) has no move that re-targets a `return` to a shared label.

## (f) Where the method fell short
* The METHOD's cross-jump entries (c6/c10/c15) speak of merges the target keeps apart and of SHAPES made to differ; this
  one is about merge DIRECTION: the same two blocks merge either way, and which survives is decided by which one owns
  the discount (`jump.c:2406` label vs `:2518` jump-around-jump) and by insn order. Reading `.greg` (pre-jump2) against
  `.jump2` for the surviving `code_label` settled it in one comparison — worth a METHOD line: "for a cross-jump
  residual, find the SURVIVOR label in `.jump2` for both the tree body and yours".
* The TU/comment note ("LOAD-BEARING zero-byte cross-jump barrier (cookbook §5a)") was a claim; refuted on bytes.

Paths: body `.run/P36/agents/ov_SC03_001__func_80182058/body.c`; dumps `scratch/dumps_free/`, `scratch/dumps_tree/`,
`scratch/dumps_w2/`; variants `scratch/w1..w6.c`.
