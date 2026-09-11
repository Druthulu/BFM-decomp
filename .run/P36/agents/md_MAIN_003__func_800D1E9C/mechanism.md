# func_800D1E9C — score 0, ZERO levers, but a SIGNATURE change (PARKED per METHOD step 15 d29 / Drew S104 (d))

(a) Residual (start 20 lever-free, best 5 in the sweep, COUNT): (1) the two early-exit tails (`func_800D2D44(0); func_800468FC();
    func_8002D8D4(); func_800D2AA0(0); goto ret`) are CROSS-JUMPED into one in mine (`bnez v0,<tail2>`), the target keeps both
    copies (the tree's `__asm__("")` barrier kept them apart); (2) the target's `li v0,1` after the last call — the function RETURNS 1.

(b) Pass + decision: jump2 cross-jump (`toplev.c` post-reload `jump_optimize(…, 1, …)`), `jump.c:1969-1998`. For a simple jump,
    `find_cross_jump(insn, JUMP_LABEL, 1)` (:1978) first compares against the code FALLING INTO the label; only when that finds
    nothing does the "other jumps to the same label" loop run — and it is guarded by `INSN_UID (JUMP_LABEL (insn)) < max_uid`
    (`jump.c:1985`). In the original each exit is `…; func_80010A98(); return 1;`: the fall-through tail before the return label is
    `call 80059658(1); call 80010A98; set v0,1`, so each early-exit jump matches its last two insns against it, `do_cross_jump`
    (:2537) redirects it to a NEW label created by `get_label_before` (:2586) in front of `call 80010A98` — a label whose UID is
    ≥ max_uid — and the reprocessed jump never enters the other-jumps loop, so the two identical 4-call tails are never compared.
    In the tree's text the shared `ret:` label is OLD (UID < max_uid), the jump_chain loop runs, and the tails merge.

(c) Moves (proven at 0 through a whole-TU `--try`, `scratch/tu_sig.c`; the caller func_800D1E58 scores 0 in the same file):
    1. `s32 func_800D1E9C(void *arg0)`; each `goto ret;` → `func_80010A98(); return 1;` written at the site; the `ret:` label deleted,
       the final tail ends `func_80010A98(); return 1;`.
    2. REQUIRES `src/md_MAIN_003/md_MAIN_003_jr_800D1E18.c:102` → `extern s32 func_800D1E9C(void *arg0);` (its only caller,
       func_800D1E58 at :107, discards the value; bytes unchanged).
    The barrier, the `$2` pin and the keepalive all go: 3 levers → 0.

(d) GENERATOR PROPOSAL: when the residual is "mine merges N identical call-tails that end in `goto <label>`, the target keeps them"
    and the label's block is the function's final tail, write the label's statements out at every `goto` site (a goto-shared
    tail per site — the sites then cross-jump against the FALL-THROUGH tail onto a NEW label and never against each other,
    `jump.c:1985`). Pair it with d29: a `void` whose tail ends in a keepalive of `$v0` returns that value.

(e) Not needed: nothing else was tried; the first spelling from the reading closed. NOT proven: a `void` plain-C spelling — the
    `li v0,1` is a return value and a void function cannot emit it.

(f) Method: `--try --body` cannot carry the extern edit; the whole-TU `--try` (no `--body`) does, and the same file scores the caller.

(g) STRUCTS: `arg0` is a `D_800D942C_entry *` (the TU already has the struct, fields at +4/+0x10/+0x14/+0x18/+0x1C); the `D_800EC9A4…F8`
    cluster is one stream-state struct. Neither touches THIS residual (cross-jump compares call insns, not addresses). Using the
    struct type for `p` would replace `p[1]`, `p[4]`… with names and is byte-neutral in principle — a structs-phase readability move.
