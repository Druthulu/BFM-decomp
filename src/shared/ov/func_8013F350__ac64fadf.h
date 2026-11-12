/* func_8013F350 — shared body (overlay slot 0x80128158, h_exact ac64fadf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8013F350(void) {
    u16 *pd = &guess_g_MenuPadHeld;
    u16 *ps;
    u16 *pf;
    u16 *pg;
    u16 pad;
    u16 st;
    u8 *pcur;
    u8 *pmax;
    u8 *p2e;
    u8 *p3e;
    s32 off;
    s16 i;
    s32 r;
    s16 rs;
    s16 d;
    u8 b;
    u8 bb;
    u8 m;
    s32 chg;

    pad = *pd;
    chg = 0;
    pf = pd + 2;
    if (pad != 0) {
        if (pad == *pf) {
            guess_g_MenuPadRepeatTimer = guess_g_MenuPadRepeatTimer - 1;
            if (guess_g_MenuPadRepeatTimer == 0) {
                guess_g_MenuPadPressed = pad & 0xF000;
                guess_g_MenuPadRepeatTimer = 3;
            }
        } else {
            *pf = pad;
            guess_g_MenuPadRepeatTimer = 6;
        }
    } else {
        D_80115120 = 0;
        guess_g_MenuPadRepeatTimer = 0xC;
    }


    i = 0;
    do {
        if ((guess_TestGameFlag(D_80180314[i]) & 0xFF) == 0) {
            break;
        }
        i = i + 1;
    } while (i < 6);
    *(u16 *)guess_g_MenuPanelSizes = i | 0x100;

    switch (guess_g_MenuPanel) { /* jtbl_801D8860 */
    case 0:
        r = ((s32 (*)(s32))guess_GetMenuPanelCursorIndex)(0);
        rs = (s16)r;
        if ((guess_TestGameFlag(D_80180314[rs]) & 0xFF) != 0 && (guess_g_MenuPadPressed & 0x40) != 0) {
            func_8014AA04((r + 1) & 0xFF);
            if (rs != 0) {
                guess_RequestSound(0x461, 0);
            } else {
                guess_RequestSound(0x460, 0);
            }
        }
        break;
    case 1:
        if ((guess_g_MenuPadPressed & 0x40) != 0) {
            guess_g_MenuCategory = ((s32 (*)(s32))guess_GetMenuPanelCursorIndex)(1) + 1;
            guess_g_MenuPanel = 2;
            func_80141C0C(3);
            return 1;
        }
        if (guess_g_MenuCategory != 4) {
            break;
        }
        goto tail7;
    case 2:
        switch (guess_g_MenuCategory) { /* jtbl_801D8880 */
        case 0:
            break;
        case 1:
            r = ((s32 (*)(s32))guess_GetMenuPanelCursorIndex)(2);
            pf = &guess_g_MenuPadPressed;
            if ((*pf & 0x40) != 0) {
                if ((*(s16 *)&guess_g_MenuSwapSlot) == 0) {
                    if ((func_800291B4(D_8018032C[(s16)r]) & 0xFF) != 0 && (*pf & 0x40) != 0) {
                        guess_g_MenuPanel = 5;
                        *(s16 *)&D_80115152 = 0;
                        func_80141C0C(3);
                        return 1;
                    }
                    func_80141C0C(5);
                } else {
                    func_801415C0((s16)r, (*(s16 *)&guess_g_MenuSwapSlot) & 0xF);
                    guess_g_MenuSwapSlot = 0;
                    func_80141C0C(3);
                    return 1;
                }
            } else if ((*pf & 0x20) != 0) {
                if ((*(s16 *)&guess_g_MenuSwapSlot) == 0) {
                    guess_g_MenuSwapSlot = r | 0x8000;
                } else {
                    func_801415C0((s16)r, (*(s16 *)&guess_g_MenuSwapSlot) & 0xF);
                    guess_g_MenuSwapSlot = 0;
                }
                func_80141C0C(3);
            }
            break;
        case 4:
            if ((guess_g_MenuPadPressed & 0xA000) != 0) {
                chg = func_80140608(2);
            }
            func_801407F4();
            break;
        case 2:
            break;
        case 3:
            break;
        }
        if (guess_g_MenuCategory != 0 && (guess_g_MenuPadPressed & 0x10) != 0 && guess_g_OpenMenuId != 1) {
            guess_g_MenuPadPressed = guess_g_MenuPadPressed & 0xFFEF;
            guess_g_MenuPanel = 1;
            guess_g_MenuSwapSlot = 0;
            func_80141C0C(6);
        }
        break;
    case 3:
        if (D_8011514E == 0 && (guess_g_MenuPadPressed & 0x40) != 0) {
            guess_g_MenuPanel = guess_g_MenuPanel + 3;
            func_80141C0C(3);
            return 1;
        }
        break;
    case 5:
        if ((guess_g_MenuPadPressed & 0x40) != 0) {
            rs = (s16)((s32 (*)(s32))func_801416D4)(D_80115152);
            if (rs != 0) {
                if (rs < 0) {
                    guess_g_MenuExitRequest = 1;
                } else {
                    guess_g_MenuPanel = guess_g_MenuPanel - 3;
                    func_80141C0C(4);
                    return 1;
                }
            }
            break;
        }
        if ((guess_g_MenuPadPressed & 0x10) != 0) {
            goto tail6;
        }
        break;
    case 6:
        if ((guess_g_MenuPadPressed & 0x10) == 0) {
            break;
        }
    tail6:
        pg = &guess_g_MenuPadPressed;
        *pg = *pg & 0xFFEF;
        guess_g_MenuPanel = guess_g_MenuPanel - 3;
        func_80141C0C(6);
        return 1;
    case 7:
        if ((guess_g_MenuPadPressed & 0xA000) != 0) {
            chg = func_80140608(7);
        }
    tail7:
        func_801407F4();
        break;
    }

    ps = &guess_g_MenuPanel;
    
    st = *ps;
    off = st << 1;
    p2e = (u8 *)ps + 0x2E;
    p3e = (u8 *)ps + 0x3E;
    pcur = p2e + off;
    pmax = p3e + off;
    if (st == 2 || 1 < pmax[0]) {
        if ((guess_g_MenuPadPressed & 0x1000) != 0) {
            pcur[0] = pcur[0] - 1;
            chg = 1;
            if (0x7F < pcur[0]) {
                if (guess_g_MenuPanel != 3) {
                    pcur[0] = pmax[0] - 1;
                } else {
                    pcur[0] = 0;
                    chg = 0;
                }
            }
        }
        if ((guess_g_MenuPadPressed & 0x4000) != 0) {
            b = pcur[0];
            pcur[0] = b + 1;
            chg = 1;
            if (pmax[0] <= (u8)(b + 1)) {
                if (guess_g_MenuPanel != 3) {
                    pcur[0] = 0;
                } else {
                    pcur[0] = b;
                    chg = 0;
                }
            }
        }
        if (guess_g_MenuPanel == 2 && guess_g_MenuCategory == 1) {
            if ((guess_g_MenuPadPressed & 0x8000) != 0) {
                pcur[1] = pcur[1] - 1;
                chg = 1;
                if (0x7F < pcur[1]) {
                    pcur[1] = pmax[1] - 1;
                }
            }
            if ((guess_g_MenuPadPressed & 0x2000) != 0) {
                pcur[1] = pcur[1] + 1;
                chg = 1;
                if (pmax[1] <= pcur[1]) {
                    pcur[1] = 0;
                }
            }
        } else {
            bb = pcur[0];
            m = guess_g_MenuPanelScrollTops[guess_g_MenuPanel];
            d = (s8)bb - (s8)m;
            if (d > 0) {
                guess_g_MenuPanelScrollTops[guess_g_MenuPanel] = bb;
            } else if (d < 0) {
                guess_g_MenuPanelScrollTops[guess_g_MenuPanel] = bb;
            }
        }
        if (guess_g_MenuPanel == 1) {
            guess_g_MenuCategory = ((s32 (*)(s32))guess_GetMenuPanelCursorIndex)(1) + 1;
            if ((guess_g_MenuPadPressed & 0x5000) != 0) {
                D_8011514C = 0;
            }
        }
        *(u16 *)&D_8011515C = D_80180230[guess_g_MenuCategory];
        if ((chg << 0x10) != 0) {
            func_80141C0C(1);
        }
    }
    return 0;
}
