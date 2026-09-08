/* func_8014F4C0 — shared body (overlay slot 0x80128158, h_exact c378aa01). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_80029178(s32 arg);
extern int func_8014F74C();
extern u8 D_800D3918[];
extern u8 D_801152A8[];
extern s16 D_801152B0;
extern s32 D_801152BC;
s32 func_8014F4C0(s32 arg0)
{
    PosT  sp10;
    MoveT sp18;
    u16 x6, xA, xE;
    s32 ret;
    if (*(s16 *)(arg0 + 0x146) != 0) {
        return func_8014F74C();
    }
    sp10.x = *(u16 *)(arg0 + 0x88);
    sp10.y = *(u16 *)(arg0 + 0x8A);
    sp10.z = *(u16 *)(arg0 + 0x8C);
    sp18.x = x6 = *(u16 *)(arg0 + 6);
    sp18.y = xA = *(u16 *)(arg0 + 0xA) + 8;
    sp18.z = xE = *(u16 *)(arg0 + 0xE);
    if (*(s16 *)(arg0 + 0x146) != 0) {
        sp18.x = x6 + *(u16 *)(arg0 + 0x140);
        sp18.y = xA + *(u16 *)(arg0 + 0x142);
        sp18.z = xE + *(u16 *)(arg0 + 0x144);
    }
    ret = func_80133784(0, &sp10, (s32)&sp18);
    if (ret != 0) {
        if (*(u8 *)&sp18.w != 0) {
            *(u16 *)(arg0 + 0x16C) = *(u8 *)&sp18.w;
        }
        *(u16 *)(arg0 + 0x16E) = (u32)sp18.w >> 13;
        if (ret == 0x2000) {
            __builtin_memcpy((void *)(arg0 + 0x120), (void *)D_801152A8, 8);
        } else if (ret == 0x4000) {
            __builtin_memcpy((void *)(arg0 + 0x120), (void *)&D_801152B0, 8);
        }
        /* NOT the sibling's `if (x != 0x1D) return ret;` early-return form — that inverts the
         * branch polarity here (beq instead of the target's bne) and costs +2 ins. The
         * short-circuit && is what folds the 0x1D test and the func_80029178 test into the
         * single fallthrough chain the target uses. */
        if (*(u16 *)(arg0 + 0x16C) == 0x1D && (func_80029178(0x21) & 0xFF) == 0) {
            ret &= ~0x2000;
            ret |= 0x4000;
            __builtin_memcpy((void *)&D_801152B0, (void *)D_801152A8, 8);
            D_801152BC = 1;
        }
        return ret;
    }
    /* ret == 0 */
    __builtin_memcpy((void *)(arg0 + 0x120), (void *)D_800D3918, 8);
    if (*(u8 *)&sp18.w != 0) {
        *(u16 *)(arg0 + 0x16C) = *(u8 *)&sp18.w;
    }
    return 0;
}
