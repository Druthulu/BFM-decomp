/* func_8014F74C — shared body (overlay slot 0x80128158, h_exact f969fea3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_80029178(s32 arg);
extern u8 D_800D3918[];
extern u8 D_801152A8[];
extern s16 D_801152B0;
extern s32 D_801152BC;
int func_8014F74C(s32 arg0)
{
    PosT  sp10;
    MoveT sp18;
    PosT  sp20;
    u16 x6, xA, xE;
    s32 ret;
    sp10.x = *(u16 *)(arg0 + 0x88);
    sp10.y = *(u16 *)(arg0 + 0x8A);
    sp10.z = *(u16 *)(arg0 + 0x8C);
    sp18.x = sp20.x = x6 = *(u16 *)(arg0 + 6);
    sp18.y = sp20.y = xA = *(u16 *)(arg0 + 0xA);
    sp18.z = sp20.z = xE = *(u16 *)(arg0 + 0xE);
    if (*(s16 *)(arg0 + 0x146) != 0) {
        sp18.x = x6 + *(u16 *)(arg0 + 0x140);
        sp18.y = xA + *(u16 *)(arg0 + 0x142);
        sp18.z = xE + *(u16 *)(arg0 + 0x144);
    }
    ret = func_80133784(0, &sp10, (s32)&sp18);
    if (ret != 0) {
        *(s16 *)(arg0 + 6)   = sp18.x;
        *(s16 *)(arg0 + 0xA) = sp18.y;
        *(s16 *)(arg0 + 0xE) = sp18.z;
        if (*(u8 *)&sp18.w != 0) {
            *(u16 *)(arg0 + 0x16C) = *(u8 *)&sp18.w;
        }
        *(u16 *)(arg0 + 0x16E) = (u32)sp18.w >> 13;
        if (ret == 0x2000) {
            __builtin_memcpy((void *)(arg0 + 0x120), (void *)D_801152A8, 8);
        } else if (ret == 0x4000) {
            __builtin_memcpy((void *)(arg0 + 0x120), (void *)&D_801152B0, 8);
        }
        if (*(u16 *)(arg0 + 0x16C) != 0x1D) {
            return ret;
        }
        if ((func_80029178(0x21) & 0xFF) == 0) {
            ret &= ~0x2000;
            ret |= 0x4000;
            __builtin_memcpy((void *)&D_801152B0, (void *)D_801152A8, 8);
            D_801152BC = 1;
        }
        __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B headers1)
        return ret;
    }
    /* ret == 0 */
    __builtin_memcpy((void *)(arg0 + 0x120), (void *)D_800D3918, 8);
    if (*(u8 *)&sp18.w != 0) {
        *(u16 *)(arg0 + 0x16C) = *(u8 *)&sp18.w;
    }
    if (((sp10.x != sp20.x) || (sp10.y != sp20.y) || (sp10.z != sp20.z)) &&
        (sp10.x == (s16)sp18.x) && (sp10.y == (s16)sp18.y) && (sp10.z == (s16)sp18.z)) {
        return 0x8000;
    }
    return 0;
}
