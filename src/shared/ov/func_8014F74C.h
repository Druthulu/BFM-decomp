/* func_8014F74C — shared body (overlay slot 0x80128158, h_exact f969fea3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 guess_TestGameFlag(s32 arg);
extern u8 D_800D3918[];
extern u8 guess_g_BoxHitNormalX[]; // Names ledger: config/names.tsv guess_g_BoxHitNormalX
extern s16 D_801152B0;
extern s32 D_801152BC;
int func_8014F74C(s32 arg0)
{
    PosT  sp10;
    MoveT sp18;
    PosT  sp20;
    u16 x6, xA, xE;
    s32 ret;
    sp10.vx = *(u16 *)(arg0 + 0x88);
    sp10.vy = *(u16 *)(arg0 + 0x8A);
    sp10.vz = *(u16 *)(arg0 + 0x8C);
    sp18.unk0 = sp20.vx = x6 = *(u16 *)(arg0 + 6);
    sp18.unk2 = sp20.vy = xA = *(u16 *)(arg0 + 0xA);
    sp18.unk4 = sp20.vz = xE = *(u16 *)(arg0 + 0xE);
    if (*(s16 *)(arg0 + 0x146) != 0) {
        sp18.unk0 = x6 + *(u16 *)(arg0 + 0x140);
        sp18.unk2 = xA + *(u16 *)(arg0 + 0x142);
        sp18.unk4 = xE + *(u16 *)(arg0 + 0x144);
    }
    ret = func_80133784(0, &sp10, (s32)&sp18);
    if (ret != 0) {
        *(s16 *)(arg0 + 6)   = sp18.unk0;
        *(s16 *)(arg0 + 0xA) = sp18.unk2;
        *(s16 *)(arg0 + 0xE) = sp18.unk4;
        if (*(u8 *)&sp18.unk6 != 0) {
            *(u16 *)(arg0 + 0x16C) = *(u8 *)&sp18.unk6;
        }
        *(u16 *)(arg0 + 0x16E) = (u32)sp18.unk6 >> 13;
        if (ret == 0x2000) {
            __builtin_memcpy((void *)(arg0 + 0x120), (void *)guess_g_BoxHitNormalX, 8);
        } else if (ret == 0x4000) {
            __builtin_memcpy((void *)(arg0 + 0x120), (void *)&D_801152B0, 8);
        }
        if (*(u16 *)(arg0 + 0x16C) == 0x1D) {
            if ((guess_TestGameFlag(0x21) & 0xFF) == 0) {
                ret &= ~0x2000;
                ret |= 0x4000;
                __builtin_memcpy((void *)&D_801152B0, (void *)guess_g_BoxHitNormalX, 8);
                D_801152BC = 1;
            }
        }
        return ret;
    }
    /* ret == 0 */
    __builtin_memcpy((void *)(arg0 + 0x120), (void *)D_800D3918, 8);
    if (*(u8 *)&sp18.unk6 != 0) {
        *(u16 *)(arg0 + 0x16C) = *(u8 *)&sp18.unk6;
    }
    if (((sp10.vx != sp20.vx) || (sp10.vy != sp20.vy) || (sp10.vz != sp20.vz)) &&
        (sp10.vx == (s16)sp18.unk0) && (sp10.vy == (s16)sp18.unk2) && (sp10.vz == (s16)sp18.unk4)) {
        return 0x8000;
    }
    return 0;
}
