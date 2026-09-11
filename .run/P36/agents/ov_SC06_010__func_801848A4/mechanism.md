# func_801848A4 — CLOSED, score 0 (274/274 ins; objdump -drz incl. relocations identical to the baseline) — T7 agent c52, S103

**Same mechanism as func_8018315C — read ../ov_SC06_010__func_8018315C/mechanism.md for the full reading.**

(a) Residual: COUNT −2 — mine builds `&D_800AF648` once in callee-saved `$s0` (`lui s0/addiu s0`) and copies
`move a0,s0` before `jal func_8004914C` and `jal func_800491AC`; the target rebuilds it in `$a0` (`lui a0/addiu a0`)
before each call. Branch-target shifts (and, where present, the `li a0,641` delay-slot fill) are knock-ons.

(b) Pass: cse replaces the second `(set (reg) (symbol_ref "D_800AF648"))` with the first pseudo, its cheapest
equivalent (`cse.c:6722-6803`; dead set removed, `delete_dead_from_cse` `cse.c:8684`), which then lives across the first
call → `$s0`. cse hashes/compares SYMBOL_REFs by NAME POINTER (`canon_hash` `cse.c:1937`, `exp_equiv_p` `cse.c:2107`); an
asm-label declaration gets its own `"*D_800AF648"` string (`varasm.c:479-485`), so it is never merged.
(Proven in the .rtl/.cse dumps for func_8018315C; proven on bytes here.)

(c) Move (body-local declaration alias, class E; nothing outside the body):
```c
    extern u8 D_800AF648_b __asm__("D_800AF648");   /* next to extern u8 D_800AF648; */
    ...
        func_8004914C(&D_800AF648);
        func_800491AC(&D_800AF648_b);
```
(the `{ void *r4; r4 = &D_800AF648; f(r4); }` blocks become plain calls.)

(d) Generator: a `register void *r4 __asm__("$4"); r4 = &SYM;` pin (111 left in the tree, all `&D_800AF648`) → write the
second `&SYM` as `&SYM_b` with `extern T SYM_b __asm__("SYM");` in the body.

(e) Control: the same body with `&D_800AF648` in both calls scores 11 (verified on func_8018315C).

(f) Method: closed on the first `--try` from the brief's R26/c45 pointer; nothing fell short.
