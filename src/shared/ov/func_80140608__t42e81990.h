/* func_80140608 — shared body (overlay slot 0x80128158, h_text 42e81990). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80140608(s32 a0) {
    s16 t;
    s32 iVar2;
    s32 uVar3;
    u16 uVar4;
    s32 uVar5 = 1;

    switch (guess_g_MenuPanelCursors[(s16)a0 * 2]) {
    case 0:
        t = func_80028D58() ^ 1;
        func_80028D78(t);
        if (t != 0) {
            return uVar5;
        }
        func_80019064(&D_80062BDC);
        return uVar5;
    case 1:
        func_80028E00((s16)(func_80028DE0() ^ 1));
        return uVar5;
    case 2:
        iVar2 = func_80028FBC();
        if (guess_g_MenuPadPressed & 0x8000) {
            iVar2 = iVar2 - 1;
            uVar4 = iVar2 + 0;
            if ((s16)iVar2 < 0) {
                uVar4 = 0;
                uVar5 = 0;
            }
        } else {
            iVar2 = iVar2 + 1;
            uVar4 = iVar2 + 0;
            if ((s16)iVar2 >= 8) {
                uVar4 = 7;
                uVar5 = 0;
            }
        }
        func_80028FDC((s16)uVar4);
        guess_RequestSound(0x21, uVar4 & 0xFFFF);
        goto ret;
    case 3:
        iVar2 = func_80029000();
        if (guess_g_MenuPadPressed & 0x8000) {
            iVar2 = iVar2 - 1;
            uVar4 = iVar2 + 0;
            if ((s16)iVar2 < 0) {
                uVar4 = 0;
                uVar5 = 0;
            }
        } else {
            iVar2 = iVar2 + 1;
            uVar4 = iVar2 + 0;
            if ((s16)iVar2 >= 8) {
                uVar4 = 7;
                uVar5 = 0;
            }
        }
        func_80029020((s16)uVar4);
        guess_RequestSound(0x22, uVar4 & 0xFFFF);
        goto ret;
    case 4:
        t = func_80028D9C() ^ 1;
        func_80028DBC(t);
        uVar3 = 0xB;
        if (t == 0) {
            uVar3 = 0xC;
        }
        guess_RequestSound(uVar3, 0);
        goto ret;
    default:
        goto ret;
    }
ret:
    return uVar5;
}
