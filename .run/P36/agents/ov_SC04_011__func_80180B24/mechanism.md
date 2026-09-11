# func_80180B24 (ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent e30)

**Result: score 0 in plain C.** No pin, no asm, no added volatile. Levers go from 3 to 0 (the three `"=r"/"0"` launder
re-ties on `ta`, `tb`, `tc`). Signature unchanged. The `ta`/`tb`/`tc` locals are gone. No copy of the class elsewhere in
`src/` that I found.

## (a) The residual in one sentence
Same count (215/215), order only, in switch cases 0 and 1. The target does all three loads, then all three `addiu`, then
all three stores (case 0), and in case 1 it loads `unk34` first. Mine glues each `addiu` to its store (`lhu; addiu; sh`
interleaved).

## (b) The pass and the decision (proven on the `.combine`/`.sched` RTL and bytes)
**sched1's birthing boost.** When an insn becomes ready in the backward list scheduler, `adjust_priority`
(`sched.c:2507-2550`) raises it to the current maximum priority if `birthing_insn_p` (`sched.c:2477-2490`) holds: the
pattern is `(set (REG r) …)` with `r` set once and live below. The boosted insn is scheduled right above its consumer.
- Free body: `ta = *(u16 *)(s0 + 0xF4) + 1;` expands to `(set (reg/v:SI 75) (plus (reg 127) 1))`, a REG destination
  set once, so the add is birthing and sticks to its store (`.combine` insns 199/205/216).
- `(*(u16 *)(s0 + 0xF4))++` / `p->unkF4++` expands the increment in HImode as
  `(set (subreg:SI (reg:HI 125) 0) (plus:SI (subreg:SI (reg:HI 123) 0) 1))` (`.combine` insns 200/209/218). The SUBREG
  destination fails `birthing_insn_p`'s `GET_CODE (SET_DEST (pat)) == REG` test, so no add is boosted, and priority plus
  LUID order gives loads ×3, adds ×3, stores ×3. The launders faked the same thing by making each temp set twice
  (`reg_n_sets == 1` fails). This is METHOD S104 d8 ("the WIDTH of an incremented local decides sched1's birth
  priority"). Its note that `+= 1` does not work holds here too.
- Case 1 needs `p->unk34++` on the STRUCT member. The cast spelling `(*(u16 *)(s0 + 0x34))++` scores 11
  (`scratch/c1/*__cast_pp.c`). The struct access is `MEM_IN_STRUCT_P` (`expr.c:4873/4888`), and `true_dependence`
  (`sched.c:817-839`) lets the fixed-address scalar store to `D_801EFD40` pass it. That is what puts the `unk34` load
  first, as in the target. The same channel is noted in the body's own case-1 comment.

## (c) The move that closed it
```c
        case 0:
            p->unkF4++;
            p->unkF2++;
            p->unk34++;
            func_8002D4C8(0x992, 0);
            break;
        case 1:
            D_801EFD40 = D_801EFD40 & 0xFFFE;
            a = p->unkF4 + 1;
            p->unkF4 = a + (p->unkF2 & 1);
            p->unk34++;
            break;
```
Also 0 (`scratch/c1/scores.txt`): the cast-deref post-increments in case 0 (`pp__pp.c`), `u16 ta, tb` with `ta++`
(`u16t__pp.c`), and `ta = load; ta += 1;` (`twoset__pp.c`, where the set-twice temp is not birthing). `+= 1` on the field
(`pe__*`) scores 9. It folds back to an SImode REG destination.

## (d) Generator proposal
When an ORDER residual shows `load; add; store` triples interleaved in mine but grouped (loads, adds, stores) in the target,
and the source reads `t = *(u16 *)(p + K) + 1; … *(u16 *)(p + K) = t;`: rewrite each as the post-increment `(*(u16 *)(p +
K))++` (or `s->f++`), deleting the temp. The `u16`/HImode increment gives a SUBREG destination that `birthing_insn_p`
rejects. R32 already generates `x++`, but only on one statement per candidate. Here all three are needed in case 0 plus
the one in case 1, and every single step scored 9.

## (e) What did NOT work
- Case 0 alone or case 1 alone as `++` (`*__orig.c`, `orig__pp.c`): 9 each. The close needs both.
- `+= 1` spellings (`pe`): 9. The cast `++` in case 1 (`cast_pp`): 11.
- The sweep's best was 9 (R21 chain / R32 `(p->unk34)++`), which is the case-1 half on its own.

## (f) Where the method fell short
Nothing blocked. METHOD step 12 (d8) named the mechanism, and the body's own comment named the pass
(`birthing_insn_p`, `reg_n_sets`). One 28-body batch (7 case-0 spellings × 4 case-1 spellings) closed it. The lesson for the
generators is JOINT application of one move at several sites.

## (g) Structs question
Yes, for case 1, and the struct is already there: `struct Ent_80180B24 { … u16 unk34 @0x34; … u16 unkF2 @0xF2; u16 unkF4
@0xF4; }`. The struct-member access is what lets sched move the `unk34` load across the `D_801EFD40` scalar store
(`MEM_IN_STRUCT_P` vs a fixed-address scalar in `true_dependence`, `sched.c:817-839`), and the cast spelling scores 11 on
bytes (`scratch/c1/*__cast_pp.c`). For case 0 the struct is optional: the cast-deref `++` also scores 0. The rest of the
body (`s0 + 0xE0`, `+0x76`, `+0x106`, `+0x100`, `+0x1C`) could move into the same struct in the structs phase. Not tested
beyond the case-1 pair.

Files: `body.c` (score 0, `= scratch/final.c`), `scratch/c1/` (the 28-body batch with `scores.txt`),
`scratch/d_win/`, `scratch/d_free/` (dumps).
