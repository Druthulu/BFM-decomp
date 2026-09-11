void func_8018AD74(s32 p1, s32 p2, s32 p3, s32 p4)
{
    /* [T51] block-scoped decls (house idiom in this TU, cf. func_8018AF88): a file-scope
       decl of these symbols would constrain every LATER function in the object. */
    extern Blk20_8018AF88 D_800AE620;
    extern s32 func_8012C658(s32, s32, s32);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void func_800484EC(s32, s32, s32);
    extern u8 D_801CD468[];

    Blk20_8018AF88 local_30;   /* sp+0x10 */
    Blk20_8018AF88 *m;
    s32 obj;
    s32 out[3];                /* sp+0x30, only [0] and [2] used */

    local_30 = D_800AE620;
    obj = func_8012C658((s16)p2, (s16)p3, p1);
    do { } while (0);  // !FAKE: do-while — its NOTE_INSN_LOOP_END ends cse1's extended block (cse.c:8054), so m below is not folded onto the struct copy's address pseudo (cse.c:846-862) and is set AFTER obj's copy: sched1 then ranks it last by LUID (sched.c:2428) (P36 S104 e5 minimum-lever)
    m = &local_30;
    if (obj != 0) {
        *(u16 *)(obj + 0xA) = *(u16 *)(obj + 0xA) - 0x80;
        RotMatrixY((s16)p4, m);
        func_800484EC((s32)m, (s32)&D_801CD468, (s32)out);
        *(s32 *)(obj + 0x10) = out[0];
        *(s32 *)(obj + 0x14) = 0xFFD80000;
        *(s32 *)(obj + 0x18) = out[2];
    }
}
