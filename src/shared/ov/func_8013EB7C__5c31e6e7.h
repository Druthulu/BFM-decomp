/* func_8013EB7C — shared body (overlay slot 0x80128158, h_exact 5c31e6e7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013EB7C(void) {
    s32 sp10[2];
    short sVar1;
    s32 iVar4;

    if ((s16)func_80141C50() == 0) {
        guess_g_MenuPacketPtr = *(s32 *)&guess_g_MenuPacketBases[(u16)guess_g_DoubleBufferIndex * 4];
        sVar1 = ((short (*)(void))func_8013F350)();
        if (guess_g_MenuPanel >= 4) {
            func_8013FAF8((s16)guess_g_MenuPanel, (s16)(guess_g_MenuPanel + 1));
        }
        func_8013FAF8(0, 5);
        if (guess_g_MenuPanel == 5) {
            iVar4 = func_8014032C((2), (((short (*)(s32))func_8014168C)(2)));
        } else {
            iVar4 = func_8014032C(((s16)guess_g_MenuPanel), (((short (*)(s32))func_8014168C)((s16)guess_g_MenuPanel)));
        }
        if (iVar4 != 0) {
            s32 *p130 = &guess_g_MenuHelpText;
            if (iVar4 != *p130) {
                *p130 = iVar4;
                func_80139954();
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_801805F4));
            }
        }
        func_80137B80();
        if ((guess_g_MenuPadPressed & 0x10) != 0 && guess_g_MenuPanel < 5 && sVar1 == 0) {
            (*(s16 *)&guess_g_MenuCategory) = 0;
            func_8002D4C8(0x466, 0);
            if (guess_g_MenuPanel != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_801805F4));
            }
            (*(unsigned short *)&guess_g_MenuStep) -= 1;
        } else {
            if ((guess_g_MenuPadPressed & 0x800) != 0 || guess_g_MenuExitRequest != 0) {
                func_8013E958();
            }
        }
    }
    (void)sp10;
}
