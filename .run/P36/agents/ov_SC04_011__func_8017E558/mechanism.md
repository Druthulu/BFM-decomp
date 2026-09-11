# func_8017E558 (ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent e17)

**Result: score 0 in plain C.** No pin, no asm, no added volatile. Levers go from 2 to 0 (the `$5` pin on `base` and the
`$2` pin on `sym`). Signature unchanged. **The same two moves close five copies in other TUs (10 more levers), all at 0**:
`scratch/copies/LIST.txt` lists them with their files (`func_8017D994` ov_SC03_105, `func_8017F278` ov_SC03_028,
`func_8017E1D4` ov_SC05_010, `func_8017E7E8` ov_SC07_002, `func_8017DDE0` ov_SC06_029).

## (a) The residual in one sentence
Two defects stacked. First a COUNT one (99 vs 101): mine hoists `&D_801EEDC8` out of the outer loop and walks the group
pointer (`lui/addiu s0` before the loop, `addiu s0,s0,464`), where the target walks an OFFSET (`s1 += 464`) and rebuilds
the address every iteration (`lui v0; addiu v0; addu a1,s1,v0`). Under it, a REGISTER permutation of the four
caller-saved loop values: target base→`a1`, p→`a2`, the inner offset→`a3`, j→`t0`; mine gives p `a1` and base `t0`.

## (b) The passes and the decisions (proven on the `-dL`/`.greg` dumps and bytes)
1. **loop.c keeps the symbol load in the loop only when its pseudo lives ONE insn.** `move_movables` hoists an invariant
   only if `threshold * savings * lifetime >= insn_count` (`loop.c:1631`, threshold from `loop.c:532`). In the free body
   the block-local `s32 sym = …;` is set, then the five-insn `i * 0x1D0` expansion runs, then the add: life 6, and the
   `.loop` dump says `Insn 28: regno 83 (life 6), move-insn savings 1  moved to 296`. Once hoisted, `sym` is invariant and
   `base = sym + i*464` is a giv (`Insn 40: giv … mult 464 add (reg/v:SI 83)`), reduced to a walked pointer (mine).
   Written as ONE expression, `&D_801EEDC8[i * 0x1D0]`, the address is forced into a register right at the add: life 1,
   `Insn 35: regno 89 (life 1), move-insn savings 1 not desirable`. It stays in the loop, is not invariant
   (`n_times_set == 1`), so `simplify_giv_expr`'s REG case fails and `base` is NOT a giv. Only `i*464` is reduced
   (`giv at 33 reduced to (reg:SI 135)` = `s1`). That is the target's count and shape (`scratch/v_a.c`, `v_c.c`: 101/101).
2. **The call takes `base` as its second argument.** `func_8017E6EC` is defined later in the TU as `(s32 a0, s32 a1)` and
   its first act is `move s7,a1` (it reads `14(a1)`, `2(a1)`: the group record). The body called it with one argument
   (the TU's no-prototype `extern void func_8017E6EC();` let it). Passing `base` adds the copy `(set (reg:SI 5) base)`
   before the call. jump2 deletes it as a no-op once `base` sits in `a1`. global.c records the preference: the `.greg`
   of `scratch/dumps_v_c2/` shows `r76 … prefers a1`. `find_reg`'s first pass skips registers that a conflicting allocno
   prefers (`regs_someone_prefers`, built from the LATER conflicting allocnos' preferences at `global.c:864-880`,
   applied at `global.c:945-953`), so `p` (r77, priority 98571, allocated first) passes over `a1` and
   takes `a2`. The inner offset giv (r131) takes `a3`, `j` (r75) `t0`, and `base` gets its preferred `a1`. Dispositions:
   `75 in 8  76 in 5  77 in 6  131 in 7`, exactly the target.

## (c) The moves that closed it (joint; each alone scores worse)
```c
        base = (s32)&D_801EEDC8[i * 0x1D0];     /* was: { s32 sym = (s32)D_801EEDC8; base = sym + i * 0x1D0; } */
        ...
        func_8017E6EC(arg0, base);               /* was: func_8017E6EC(arg0); the callee is (s32, s32) */
```
- Move 1 alone (`scratch/v_a.c`, `v_b.c`, `v_c.c`: the three one-expression spellings): 34, count right, registers wrong.
- Move 2 alone (`scratch/v_free2.c`): 56, worse than the start (53).
- Both: `v_a2.c` (`(s32)D_801EEDC8 + i * 0x1D0`), `v_b2.c` (`i * 0x1D0 + (s32)D_801EEDC8`), `v_c2.c` = `body.c`, and
  `v_f2.c` (`(s32)((u8 *)D_801EEDC8 + i * 0x1D0)`): all 0.
- The offset split into its own statement (`base = i * 0x1D0; base += (s32)D_801EEDC8;`, `v_d2.c`/`v_e2.c`): 8, 102 ins.
  A self-updating `base` is two sets, so it is no longer the single-expression shape.

## (d) Generator proposals
- (count) When the target rebuilds a `lui/addiu` of a symbol INSIDE a loop and adds a walked offset (`addu rB,sOff,v0`)
  but mine hoists the symbol and walks a pointer: fold every `T sym = &SYM; … x = sym + i*K;` into the one expression
  `x = (s32)&SYM[i*K]` (and delete the temp). The symbol pseudo's lifetime must be 1 insn for `loop.c:1631` to refuse the
  hoist.
- (register) When a call's callee is defined in the same TU with MORE parameters than the call passes (`extern void f();`
  with no prototype, the definition `f(s32, s32)`), and the target has a loop-carried value sitting in the next argument
  register at the call: pass that value as the missing argument. This is METHOD step 3's first bullet ("a dropped call
  argument") with a way to find it: compare the callee's DEFINITION arity with the call.

## (e) What did NOT work
The sweep's best was 27 (R6 inline sym + R7 do-while); R6 inline sym alone reached 34, the same as my move 1. No generator
adds a call argument whose value is not already the next argument register's source. That is why move 2 was never
reached.

## (f) Where the method fell short
- The tree's own header (`src/…_jr_8017D494.c:3153-3155`) says "the no-prototype forward decl is required so the
  1-argument call site here does not become a 2-argument call". That is an old lever's reasoning, written as a law, and
  it is wrong: the 2-argument call IS the original. The header is now stale (pins and the 1-arg claim), and so are the
  matching comments in the five twins (e.g. ov_SC06_029's "is called here with one argument").
- What found move 2 was the `.greg` table: base had priority 5322 against p's 98571, so no order move could put it
  first. The only other way for `a1` to go to the lower allocno is a hard-register preference, and a preference for `a1`
  is a call's second argument. The callee's objdump (`move s7,a1` as its first act) confirmed it.
- Count first (METHOD step 2) worked. The count gap was a loop.c hoist, not a missing insn of mine, and the `-dL` dump's
  "moved to" / "not desirable" lines named it in one compile.

## (g) Structs question
Partly. The TU already has the struct (`GroupRec_801EB5C8_8017E3B0`, 0x1D0 bytes, 16 `SubRec` of 0x1C at +0x10,
block-scope in `func_8017E3B0`), and two twins declare their symbol with it. With the struct array, `base = (s32)&D[i];`
closes too (proven on ov_SC03_028 and ov_SC06_029, `scratch/copies/`). So a struct gives the natural single-expression
spelling for move 1 for free. It does not give move 2: the call argument is an allocation preference, not a memory-order
channel. The inner loop's `p = base + 0x10 + j*0x1C` would be `&grp->subs[j]` in the structs phase. Not tested here, and
it could change the inner loop's giv shape (today `16 + 28j` is the reduced giv and `base +` it is not, because
`simplify_giv_expr` cannot add a REG invariant to a constant, `loop.c` PLUS/USE case). Test it on bytes before assuming.

Files: `body.c` (score 0), `scratch/v_*.c` (the variants above with their scores), `scratch/dumps_{free,v_a,v_c2}/`,
`scratch/copies/` (the five twins' ported bodies, their tree text, `LIST.txt`, `port.py`), `scratch/try.sh`.
