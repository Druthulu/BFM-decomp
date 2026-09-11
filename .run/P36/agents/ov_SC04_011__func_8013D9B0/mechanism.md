# func_8013D9B0 (ov_SC04_011_jr_8013C98C.c): T7 agent c47, minimum-lever pass (P36 S103)

**Final score: 0 with 2 marked levers** (down from 34 per copy in the tree). The starting point was c17's plain-C body at 15
(copied to `scratch/prev_body.c`; c17's reading is in `scratch/prev_mechanism.md`). No single lever reaches 0; the
table below gives every single-lever attempt. Three different 2-lever sets reach 0. All three also reach 0 on the
ov_MAIN_012 copy (`src/ov_MAIN_012/ov_MAIN_012_jr_8013C98C.c`, same function name) with the globals renamed
(`D_801EDABC→D_801841AC`, `D_801EDAB4→D_801841A4`, `D_801EDAD4→D_801841C4`, `D_801EDACC→D_801841BC`; that TU has no
file-scope declarations for them, so the body needs its own body-local externs; see `scratch/c47/m012_body.c`).

`PACK/body.c` (set P1) is c17's body with two changes, one line each:
```
__asm__ __volatile__("mtc2 $0, $8\n\tlwc2 $6, 0(%0)\n\tlwc2 $28, 0(%1)" :: "r"(fc), "r"(&gte[1]) : "memory");  // !FAKE: asm gte_ldIR0z+gte_ldrgb+gte_ldIRGB — the header spells these as three volatile asms (sched.c:1957 barriers), so the IRGB address lands after lwc2 $6, and a pointer set before mtc2 has life 4 and is hoisted (loop.c:1631); one asm keeps its addiu adjacent (life 1) and before mtc2 (P36 S103 c47 minimum-lever)
__asm__ __volatile__("move $12, %0\n\tswc2 $29, 0($12)" :: "r"(&gte[2]) : "$12", "memory");  // !FAKE: asm gte_stORGB — the header macro does not write $12 itself; the target's move t4,v0 needs it (S103 c17; the header respelling is Drew's T5 call) (P36 S103 c47 minimum-lever)
```
It has no register pin, no launder and no barrier. Both levers are GTE op spellings: the header macros the body calls,
written out in the form the bytes require.

## The residual c17 left, and its two independent causes
With only the stORGB asm in place (c17's `PA.c`, = `scratch/c47/s1_stasm.c`) the score is **2**. One `addiu v0,sp,28`
(the IRGB address) is emitted between `lwc2 $6` and `lwc2 $28`; the target has it before `mtc2`. The two defects sit on
opposite sides of the volatile `dpcl`. No one construct reaches both (s7 below), so each needs its own lever.

1. **`move t4,v0` before `swc2 $29`.** c17 settled this (prev_mechanism (b)7): the copy must be written by the asm itself
   into `$12`, because combine and cse fold every C copy. Nothing new here.
2. **The IRGB address before `mtc2`.** Three facts, all proven on bytes and dumps (`scratch/c47/dumps_*`):
   - Every header GTE macro is a volatile asm. That makes each one a full scheduling barrier (`sched.c:1957`,
     `code != ASM_OPERANDS || MEM_VOLATILE_P`). The address that `gte_ldIRGB(&gte[1])` forces into a register therefore
     stays after the `gte_ldrgb` barrier: this is the score-2 hunk.
   - Setting the pointer in C before `gte_ldIR0z()` gives it life 4 (set, mtc2, lwc2 $6, lwc2 $28). loop.c's test
     `threshold*savings*lifetime >= insn_count` (`loop.c:1631`) then hoists it. The `.loop` dump of p4 reads
     `Insn 137: regno 92 (life 4), savings 1 moved to 343`, against `life 1 ... not desirable` at 64 real insns. Only a
     life-1 set survives, which means the set must sit directly before its user, and that user must be an insn placed
     before `mtc2`.
   - A pointer set twice (c17's PA_5, and a launder whose input and output are the same variable, p2) is not hoisted,
     but sched1 lifts it above the three `andi`s. `adjust_priority` gives maximum priority only to birthing insns
     (`sched.c:2539-2544`), and `birthing_insn_p` requires `reg_n_sets == 1` (`sched.c:2490`). Once lifted, the pointer
     conflicts with `pix` in v0 and lands in a0/v1 or a lower register (p2 `.sched`: insn 137 moves above 128/130/132;
     p2c's single-set insn 137 stays after 132).

   The fix therefore has to be a construct before `mtc2` that reads a single-set, life-1 address and that loop.c does not
   hoist. Three constructs do this, and each is one lever:
   - (P1) one asm that performs mtc2, lwc2 $6 and lwc2 $28 together;
   - (P3) a hard-register pin, which loop.c never hoists because `may_not_optimize` is set for every hard register
     (`loop.c:595-596`);
   - (P2c) a volatile launder `"=r"(irgb) : "0"(&gte[1])`: the input temp is life 1, and the volatile asm itself is not
     invariant.

   Plain C cannot build any of these. c17 already refused the dead second store (PA_4 = 0).

## Single-lever table (each starts from c17's plain-C body at 15; file = scratch/c47/<name>.c)
| attempt | the one lever | score |
|---|---|---|
| s1_stasm | asm gte_stORGB (`move $12,%0; swc2 $29,0($12)`, clobber `$12`) | **2** (ORDER: IRGB addiu one slot late) |
| s5_pin12 | `register u32 *orgb __asm__("$12")` + header gte_stORGB | 10 (`addiu t4,sp,32` directly, no `move`) |
| s2_ldasm | merged asm mtc2+lwc2 $6+lwc2 $28, header gte_stORGB | 13 |
| s4_pin2 | `register u32 *irgb __asm__("$2")` set before gte_ldIR0z | 13 |
| s3b_launder_nv | non-volatile launder on irgb (same var in/out) | 14 |
| s6_barrier | irgb set, then `__asm__ __volatile__("" ::: "memory")` | 16 (the pointer is still hoisted, life 4) |
| s7_allasm | ONE asm for all five GTE ops (mtc2 … dpcl … move $12; swc2) | 16 (the ORGB addiu is forced before mtc2, and both load pointers are hoisted into s4/s5; 143 ins) |
| s3_launder | volatile launder on irgb (same var in/out) | 32 |

## Two-lever sets (stORGB asm + one more)
| set | second lever | score |
|---|---|---|
| **P1 = body.c** | merged asm gte_ldIR0z+gte_ldrgb+gte_ldIRGB | **0** |
| P3 (`p3_st_pin2.c`) | `register u32 *irgb __asm__("$2");` + `irgb = &gte[1];` before gte_ldIR0z | **0** |
| P2c (`p2c_st_launder_sep.c`) | `__asm__ __volatile__("" : "=r"(irgb) : "0"(&gte[1]));` before gte_ldIR0z | **0** |
| p4 | memory barrier after `irgb = &gte[1]` | 4 (hoisted, life 4) |
| p2b / p2d | non-volatile launder (same var / separate input) | 8 / 13 |
| p2 | volatile launder, same var in/out | 25 (n_sets 2 → not birthing → lifted above the andi's) |
| p5 / p6 | `$12` pin + merged asm / `$12` pin + `$2` pin | 8 / 8 |

P1, P3 and P2c tie at 2 levers. P1 is in body.c for three reasons: it has zero register levers; both of its levers are
the GTE spellings that c17 showed were the original's (a PsyQ-inline_o-style `move $12` store, and one load asm whose two
pointers are both computed before it); and it leaves nothing behind if T5 respells the header (below).

## The two paths
- **Path A: the header stays as it is (the tree today).** Bank P1: 2 levers per copy instead of 34 (125 + 7 copies). If
  register pins are preferred over GTE asm text, P3 and P2c are drop-in 2-lever alternatives, byte-proven on both TUs.
- **Path B: Drew's T5 respells the header.** (i) `gte_stORGB` respelled as `"move $12, %0\n\tswc2 $29, 0($12)" :: "r"(p) : "$12", "memory"`
  plus a new three-op load macro, e.g. `gte_ldIR0z_rgb_IRGB(r0, r1)` = `"mtc2 $0, $8\n\tlwc2 $6, 0(%0)\n\tlwc2 $28, 0(%1)" :: "r"(r0), "r"(r1) : "memory"`:
  body.c's two asm lines become two macro calls, and the body has **0 levers** (c17's PROOF_K1 = this). (ii) Only
  gte_stORGB respelled: 1 lever is left (P1's load asm, or P3's `$2` pin / P2c's launder). The macros are used only by
  these 136 copies, so the respelling touches nothing else. It must ship with the new bodies, because the tree's
  levered bodies pin `pb` to `$12` and would emit `move t4,t4` under a `move $12,%0` macro (c17).

## Generator proposal
When the only residual is a GTE address `addiu` on the wrong side of a volatile GTE asm (a load pointer needed before
the preceding `mtc2`/`lwc2`), stop searching plain C. A C pointer set earlier is hoisted (life ≥ 3 at `loop.c:1631`), and
a reused one loses the birthing priority (`sched.c:2490`). Merge the GTE loads that follow into one asm whose inputs are
all the pointers (0 register levers), or else pin that pointer to the register the bytes show.

## What did not work (besides the tables)
- Any spelling of the IRGB pointer set in C before gte_ldIR0z without a lever: life 4, hoisted (p4's `.loop`).
- Reusing one pointer for IRGB and ORGB (c17's PA_5 = 11): n_sets 2, lifted above the andi's, lands in a0.

## Where the method fell short
- `sched.c` `birthing_insn_p`/`adjust_priority` is not in METHOD's list. Here it decided why a reused pointer (c17's
  METHOD c11 "reuse one temp" move) fails: a set that is not unique loses the birthing priority, so sched1 hoists it over
  the insns that kill registers. That belongs next to the c1/c8 "split one name per value" entry as its reason.
- The `.loop` dump line `(life L) … moved / not desirable` was the deciding instrument for all three GTE-pointer
  residues, but neither alloc_table nor the pack surfaces it.

## Files
`PACK/body.c` (P1, score 0); scratch/c47/: `gen.py` (writes every variant from prev_body.c), `try.sh` (score, keep, disassemble, optional
dumps), `rtlsum.py` (one line per RTL insn), all variant `.c/.res/.s`, `m012_*.c` (the ov_MAIN_012 remaps),
`dumps_{a0,p2_st_launder,p2c_st_launder_sep,p4_st_barrier}/`, `target.s` (baseline objdump).
