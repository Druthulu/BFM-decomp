# func_80185214 (ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent e11)

**Result: score 0 in plain C.** No pin, no asm, no added volatile, no goto. Levers go from 1 to 0 (the `$16` pin on
`s0`). Signature unchanged. No copy of this class elsewhere: `c = *(u8 *)(s0 + 6);` occurs only here. The
same-name functions in ov_SC02_005 and ov_SC06_029 are different bodies, and the similar walk in `func_80184CCC`
(same TU) is already lever-free.

## (a) The residual in one sentence
One extra instruction. Mine walks a pointer to the entry's `+6` field (`addiu s0,v0,6` and `addiu s1,v0,46`, then
fields at `0(s0)`/`-4(s0)`). The target walks the entry base (`lw s0,204(v0)` straight into s0, `addiu s1,s0,40`,
fields at `6(s0)`/`2(s0)`).

## (b) The pass and the decision (proven on the `-dL` dumps and bytes)
loop.c strength reduction. In the free body `s0` is a pointer biv, and the three field ADDRESSES are its givs:
`Insn 26/42/59: dest address src reg 73 … mult 1 add 6 / add 2 / add 6` (`record_giv`, `loop.c:4341`, dump text
`:4508`). `combine_givs` (`loop.c:5494`, `:5527`) merges them onto the add-6 giv ("giv at 42 combined with giv at
59", "giv at 26 combined with giv at 59"). That giv is reduced to a new register holding `s0+6`, and "biv 73 was
eliminated", so the exit test is rewritten against `s1+6`. The pin hid `s0` from loop.c (a hard register is never
a biv), which is why the lever "worked".

## (c) The move that closed it
Index the entries by a counter instead of walking a pointer (the S103 c2 / S104 d16/d18 family):
```c
    p = *(s32 *)(D_801EFC48 + 0xCC);
    for (i = 0; i < 5; i++) {
        c = *(u8 *)(p + i * 8 + 6);
        if (c < 0x15 && D_80194724[c] == 0) {
            func_80185A18(c, (s16)(*(u16 *)(p + i * 8 + 2) + a0));
        }
        if (*(s16 *)(p + i * 8 + 6) & 0x8000) {
            break;
        }
    }
```
Now the givs are the SUMS `p + i*8` (`Insn 31/78: giv reg … mult 8 add (reg 73)`, a DEST_REG giv with
`add_val = p`). The reduced register holds the entry base itself (initial value `p`), and the field offsets stay in
the addressing mode (`6(s0)`, `2(s0)`). Biv `i` is eliminated against `p + 40`, which gives `addiu s1,s0,40` and
the signed `slt`. `s2 = a0` is gone (`a0` is used directly). Also proven:
- `scratch/v_do_i.c` (the same loop as a do-while with `i++`): 0.
- `scratch/v_goto.c` (the ORIGINAL pointer walk as a goto loop, no LOOP notes, so loop.c never runs): 0.
- `scratch/v_struct.c` (a body-local `struct Ent { u16 f0, f2, f4; union { u8 id; s16 flags; } f6; } *e;` indexed
  as `e[i]`): 0.

## (d) Generator proposal
When a loop's residual shows a walked pointer whose reduced register sits at a field offset (fields read at
`0(sN)`/negative offsets, the end pointer `base+K+off`), and the target reads the same fields at `off(sN)` with
`sN` = the loaded base: rewrite `for/do (p…; p < end; p += S)` as `for (i = 0; i < (end-base)/S; i++)` with every
`*(T *)(p + K)` becoming `*(T *)(base + i * S + K)`. The DEST_REG giv `base + i*S` then becomes the reduced register.

## (e) What did NOT work (byte evidence)
- `for (s1 = s0 + 0x28; s0 < s1; s0 += 8)` (`scratch/v_for_ptr.c`): 11. It keeps the entry test and the
  offset giv.
- The sweep (R4 declaration moves, R6/R10 parameter moves, R7/R8/R9) stayed at 6. No generator turns a pointer walk
  into an indexed loop.

## (f) Where the method fell short
METHOD step 3 (S103 c2) and step 14 (d16/d18) already name this family. The `-dL` dump's "giv … combined … reduced
to" lines settle it in one compile. The residual's "register pairs v0->s0" line pointed at allocation, but the
defect was the +6 bias of the reduced register.

## (g) Structs question
Yes, plausibly for readability, but it is not needed for the bytes. `D_801EFC48 + 0xCC` points to an array of
8-byte entries (`+2` u16 value, `+6` u8 id whose halfword also carries a 0x8000 end flag). With a struct array
indexed `e[i]` (`scratch/v_struct.c`) the loop also scores 0, because the channel is the loop's giv shape (an
indexed sum vs a walked pointer), not MEM_IN_STRUCT_P. A struct POINTER walked with `e++` would presumably
reproduce the free body's defect. Not tested.

Files: `body.c` (score 0), `scratch/v_{for_i,do_i,goto,struct}.c` (0), `scratch/v_for_ptr.c` (11),
`scratch/dumps_{free,for_i}/` (`.loop` dumps).
