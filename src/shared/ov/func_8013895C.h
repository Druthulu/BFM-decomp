/* func_8013895C — shared body (overlay slot 0x80128158, h_exact 30d23db2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80127524;
extern s16 func_80138DB8(s32 a0, u8 a1, s32 a2);
extern void func_80138B88(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
void func_8013895C(s32 a0) {
    if ((s32)D_80127524 == a0 || (*(s32 *)(a0 + 8) & 0x2000)) {
        if ((s16)func_80138DB8(a0, 0, 0x40)) {
            *(s8 *)(a0 + 0x1F) = *(u8 *)(a0 + 0x1F) + 1;
            func_80138B88(a0);
            func_8002D4C8(0x630, 0);
        } else if ((s16)func_80138DB8(a0, 0, 0x1000)) {
            *(s8 *)(a0 + 0x1F) = *(u8 *)(a0 + 0x1F) - 1;
            if ((s8)*(s8 *)(a0 + 0x1F) < 0) {
                *(s8 *)(a0 + 0x1F) = *(u8 *)(a0 + 0x21) - 1;
            }
            func_8002D4C8(0x62F, 0);
        } else if ((s16)func_80138DB8(a0, 0, 0x4000)) {
            u8 cur = *(u8 *)(a0 + 0x1F);
            u8 lim = *(u8 *)(a0 + 0x21);
            *(s8 *)(a0 + 0x1F) = cur + 1;
            if (!((s32)(s8)(*(s8 *)(a0 + 0x1F)) < (s32)lim)) {
                *(s8 *)(a0 + 0x1F) = 0;
            }
            func_8002D4C8(0x62F, 0);
        } else if (*(s32 *)(a0 + 8) & 0x2) {
            if ((s16)func_80138DB8(a0, 0, 0x30)) {
                *(s8 *)(a0 + 0x1F) = *(u8 *)(a0 + 0x21) - 1;
                func_8002D4C8(0x62F, 0);
            }
        }
    }
}
