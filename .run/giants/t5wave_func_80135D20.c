// @class: regalloc-order
// @stuck: none — MATCH (match_one 100/100 + rtu_match real-TU); needs the PAIRED //@EDIT on func_80135480 (return s16->s32 + `s32 result;`->`s16 result;`, whole-TU byte-neutral, verified) + one $s1 pin on `flag`
//@EDIT s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4)||s32 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4)
//@EDIT     s32 result;||    s16 result;

/* func_80135D20 — "is <thing> visible/hittable from <pos>" gate (100 ins, ov_SC06_018 jr_8012ACE0).
 *
 * Builds a second probe point 0x300 above the caller's point on the stack, asks func_80135480 to
 * cull/transform it, then dispatches on that result (jtbl_801D2A90, cases 0..4; default falls
 * through with p/flag/q UNINITIALISED — reproduced by leaving the switch without a default).
 *
 * Load-bearing details (do not "clean up"):
 *  - `u8 dead[96];` is a DEAD aggregate whose only job is the frame layout: it forces the probe
 *    buffer to sp+0x70 and the frame to 0x98 (gcc-2.7.2 assign_stack_local runs at expand time, so
 *    an unreferenced aggregate still owns its slot). Remove it and every sp offset shifts by 0x60.
 *  - `__asm__ __volatile__("")` is the §5a CROSS-JUMP BARRIER: without it jump.c merges the peeled
 *    first func_80135EB0 probe into the list loop (100 ins -> 88).
 *  - the explicit goto layout (loop / hit / body / elsepath) reproduces the target's basic-block
 *    ORDER: the `hit` block sits physically between the loop test and the loop body. A structured
 *    while/do-while emits the inverted layout (-3 ins, 39 diffs).
 *  - `register s32 flag __asm__("$17")` is a §17 pin. WITHOUT it gcc ties `arg1`->$s1 / `flag`->$s2,
 *    the reverse of the target (12 diffs, everything else already byte-exact). Pin-free attempts
 *    (declaring `flag` before `p`; assigning `flag` first in every case body) were both tried and
 *    do NOT flip the tie-break. The pin's live range does cross calls, so prefer ×1 banking.
 *  - func_80135480 must be declared INT-returning here: the target does NOT re-extend the callee's
 *    result before the switch (`addu $v1,$v0,$zero` only), while an s16-returning prototype costs a
 *    `sll/sra 16` pair. The two //@EDIT lines flip the in-TU definition s16->s32 and narrow its local
 *    `result` to s16 instead — the narrowing simply moves from the return-type conversion to the
 *    assignment, so the WHOLE TU compiles byte-identically (objdump-diffed: only the filename line
 *    changes). Both edits are required; flipping the return type alone drops func_80135480's tail
 *    `sll/sra` and shortens it by one instruction.
 */
extern s32 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
extern s32 func_80135EB0(s32 *p, s32 flag);
extern s32 func_801345F8(s32 arg);
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 D_801D3C5C;
extern s32 D_801D3C7C;

s32 func_80135D20(s32 arg0, s32 arg1, u16 *arg2)
{
    u8 dead[96];
    u16 sp[3];
    s32 *p;
    register s32 flag __asm__("$17");
    s32 q;

    sp[0] = arg2[0];
    sp[1] = arg2[1] + 0x300;
    sp[2] = arg2[2];
    switch (func_80135480((void *)arg0, arg1, (s16 *)arg2, (s16 *)sp)) {
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
        p = &D_801D3C7C;
        flag = 0;
        break;
    case 4:
        q = (s32)&D_801D3C5C;
        p = &D_801D3C7C;
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
    if (p == NULL) {
        return 0;
    }
    __asm__ __volatile__("");
loop:
    if (func_80135EB0(p, 0) == 0) {
        goto body;
    }
hit:
    func_80136A94(flag, arg0, (s32)arg2, q);
    return 1;
body:
    p = (s32 *)*p;
    if (p != NULL) {
        goto loop;
    }
    return 0;
elsepath:
    if (func_801345F8(arg1) != 0) {
        goto hit;
    }
    return 0;
}
