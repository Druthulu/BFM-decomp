# func_80180D54 (ov_SC03_097) — score 0, ZERO levers (agent e37, P36 S104)

(a) Residual (free body, score 8): one EXTRA `move v0,a0` at the end and the compare temps shifted one register
    (`lw v0/lw v1/addu v0/slt v0` vs the target's `lw v1/lw a0/addu v1/slt v1`, `move a0,zero` vs `move v0,zero`,
    `slti a0` vs `slti v0`). The tree's lever: `register s32 ret __asm__("$2")`.

(b) Pass + decision. `ret = 0; if (c) ret = (s16)e < 4; return ret;` makes `ret` a MULTI-BLOCK pseudo (r76): local-alloc
    refuses to tie it to `$2` (`local-alloc.c:1761`, `reg_qty[ureg] < 0`), so the block-local compare temps (r84, r90, r105)
    are allocated FIRST and take `v0`/`v1` (first free in `reg_alloc_order`); in global, r76's copy preference for `$2`
    (insn `(set (reg/i:SI 2) (reg 76))`, `global.c` `set_preference`) loses to the recorded hard-reg conflict with `v0`
    (`.greg`: `76 conflicts: 75 76 107 2 3 29`), r76 lands in `a0`, and the final copy stays. The pin makes the pseudo
    itself the hard `$2`, so the temps avoid it.
    A `return c ? X : 0` / two-`return` spelling does NOT close either (score 10/11): `X = (s16)e < 4` expands to THREE
    insns (mips.md `extendhisi2` = sll+sra for a register operand, then slt), so jump1's `x = b; if (...) x = a;` rewrite
    (`jump.c:699-741`) fails its "single insn before the jump" test (`prev_active_insn (temp3)` must be the condjump).

(c) The move: RETURN CONSTANTS from nested ifs (S104 d27):
        if (out[0] + out[2] < (u16)a1 * (u16)a1) { if (d < 4) return 1; } return 0;
    jump1's store-flag rewrite of `if (x < 4) return 1; return 0;` (`jump.c:1140-1210`) builds `$2 = slt x,4` on the HARD
    return register, and the outer test's `return 0` becomes `$2 = 0` before the branch — exactly the pinned shape.
    Also folded `d`/`e` into one `s16 d` (`if (d < 0) d = -d;`), the shape the lever-free siblings in ov_SC03_089/091/104
    already have (their headers are `func_801885A4` etc.).
    Proved on bytes: vH (ret-constants, e kept) 0; vJ (the sibling shape) 0 — delivered as body.c.

(d) GENERATOR PROPOSAL: when the tree's body is `r = 0; if (A) r = (CMP); return r;` with `r` pinned to `$2` (or the
    residual is one trailing `move v0,aN` + a register shift of the compare temps), rewrite to
    `if (A) { if (CMP) return 1; } return 0;` — and BEFORE any search, grep the whole src/ for the same first statement
    line: 5 sibling overlays (SC03_089/090/091/104, SC02_028) already carried this exact lever-free text.

(e) Did NOT work (bytes): `return c ? X : 0` (11), `if (c) return X; return 0;` (10), `if (!c) return 0; else return X`
    (11), `return c && X` (8), `e` as s32 (14), if/else arms (11), `ret` as s16 (8), ret as u8 (8).

(f) Method shortfall: the brief's "grep the WHOLE src/ for a lever-free same-shape sibling first" would have closed this in
    one --try; I read the residual and the dumps first (~15 tries). The d27 rule in METHOD step 15 is the direct hit.

(g) Structs: no. The lever is on the RETURN value's register, decided by jump1's store-flag on the hard `$2`; the `a0`
    field reads (`+6`, `+0xA`, `+0xE` of the actor) are `lh`/`lhu` from `s0` either way and never touch the allocator's
    decision here. A struct for `a0` (an actor with s16 pos fields at 6/0xA/0xE) is a readability gain only.

Copies: func_8018412C in src/ov_SC03_092/ov_SC03_092_jr_80181694.c — same text, score 0 (scratch/copies/LIST.tsv).
