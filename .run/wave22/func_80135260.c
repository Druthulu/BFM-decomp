/* func_80135260 — "is <target> reachable/hittable" gate (136 ins, ov_SC01_077 jr_8012ACE0).
 *
 * Sibling of the already-banked func_80135D20 (src/ov_SC03_099/ov_SC03_099_jr_80135D20.c L659+):
 * same func_80135480 switch (jtbl_801D8158, cases 0..4, default falls through with p/flag/q
 * UNINITIALISED — reproduced by leaving the switch without a default), same peeled-probe +
 * rotated list loop, different `elsepath`.
 *
 * Load-bearing details (all byte-proven by ablation against match_one):
 *  - func_80135480 is DEFINED later in this same TU (L3261) returning s16. Calling it through an
 *    `s32 (*)(...)` cast is REQUIRED: the target does NOT re-extend the callee result before the
 *    switch (`addu $v1,$v0,$zero` only); a plain s16-returning call costs an extra `sll/sra 16`.
 *    The cast is call-site-local, so func_80135480's own definition is untouched (no //@EDIT).
 *  - D_801870AC / D_801870B0 / D_801870B8 MUST be declared as 4-byte POINTERS
 *    (`extern u16 *D_801870Bx;`), not the canonical `extern u8` + `(*(u16**)&sym)` cast. With the
 *    u8 form gcc CSEs `&sym` into two callee-saved regs ($s1/$s5), which costs a 7th saved
 *    register ($s6 for arg3) and 3 extra instructions. This is exactly the retype already
 *    documented in this TU's @stuck note at L3127. The decls are BLOCK-SCOPE-compatible with the
 *    TU's other `extern u8 D_801870AC;` bodies (the TU already mixes both forms: L2461 vs L2587).
 *  - `u8 dead[56];` is a DEAD local that only sets the frame: without it the frame is 0x30, the
 *    target's is 0x68 (gcc-2.7.2 assign_stack_local runs at expand time, so an unreferenced
 *    aggregate still owns its slot). Body bytes are already exact at 136/136 without it — the 16
 *    residual diffs are purely the sp/save-slot immediates.
 *  - explicit goto layout (loop / hit / body / elsepath) reproduces the target's block ORDER: the
 *    `hit` block sits physically between the loop test and the loop body, and its leading
 *    `move a0,flag` gets copied into all four branch delay slots.
 *  - the two D_801870xx compare fields are read `lhu` -> u16; the func_80134A74 args are `(s16)`
 *    casts of those u16 lvalues (combine folds the fresh ones into `lh`, and sll/sra the one that
 *    is still live in $a1 from the 0xFF80 compare).
 *  - func_80135D20's §5a cross-jump barrier is NOT needed here (ablated: MATCH either way).
 */
extern s16 func_80135480(void*, s32, s16*, s16*);
extern s32 func_80135EB0(void *arg0, s32 arg1_);
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern int func_80134A74(int, s16, s16, int);

s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3)
{
    /* BLOCK scope on purpose: this TU already declares D_801870AC/B0/B8 as `extern u8` inside
     * other function bodies (L2461-2463) and as `extern u16 *` inside others (L2587-2589).
     * A FILE-scope pointer decl here would make those inner `extern u8` decls conflicting-types.
     * The same reason keeps D_801D9504/D_801D9524 local (cf. the TU's own L3268-3270). */
    extern u16 *D_801870AC;
    extern u16 *D_801870B0;
    extern u16 *D_801870B8;
    extern s32 D_801D9504;
    extern s32 D_801D9524;

    u8 dead[56];
    s32 *p;
    s32 flag;
    s32 q;
    u16 *pa;
    u16 *pb;
    u16 *pc;
    u16 *pd;
    u16 *pe;
    u16 t;

    switch (((s32 (*)(void *, s32, s16 *, s16 *))func_80135480)((void *)arg0, arg1, arg2, arg3)) {
    case 0:
        return 0;
    case 1:
        q = arg0 + 0x34;
        p = (s32 *)((arg1 & 0xFFFFFFF) | 0x80000000);
        flag = 0;
        break;
    case 2:
        q = arg0 + 0x34;
        p = (s32 *)((arg1 & 0xFFFFFFF) | 0x80000000);
        flag = 1;
        break;
    case 3:
        q = arg0 + 0x34;
        p = &D_801D9524;
        flag = 0;
        break;
    case 4:
        q = (s32)&D_801D9504;
        p = &D_801D9524;
        flag = 1;
        break;
    }
    if (arg1 >= 0) {
        goto elsepath;
    }
    if (func_80135EB0(p, 0) != 0) {
        goto hit;
    }
    p = (s32 *)*p;
    if (p == 0) {
        return 0;
    }
loop:
    if (func_80135EB0(p, 0) == 0) {
        goto body;
    }
hit:
    func_80136A94(flag, arg0, (s32)arg3, q);
    return 1;
body:
    p = (s32 *)*p;
    if (p != 0) {
        goto loop;
    }
    return 0;
elsepath:
    pa = D_801870B0;
    pb = D_801870AC;
    pc = D_801870B8;
    pc[0] = pa[0] - pb[0];
    pc[1] = pa[1] - pb[1];
    pc[2] = pa[2] - pb[2];
    if (func_80134A74(0, (s16)pb[0], (s16)pb[2], (int)p) != 0) {
        goto hit;
    }
    pd = D_801870AC;
    pe = D_801870B0;
    t = pe[0];
    if (((pd[0] & 0xFF80) == (t & 0xFF80)) && ((pd[2] & 0xFF80) == (pe[2] & 0xFF80))) {
        return 0;
    }
    if (func_80134A74(0, (s16)t, (s16)pe[2], (int)p) != 0) {
        goto hit;
    }
    return 0;
}
