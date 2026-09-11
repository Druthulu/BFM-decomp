void func_801898E4(void)
{
    s32 pad[2];
    s16 i;
    s16 cnt;
    s16 k;
    s16 b;
    u8 *s;
    char *d;
    char *srcA;
    char *srcB;
    char *tmpl;
    s32 count;
    u8 *table;

    /* ---- phase 1: default template + 16-row fill ---- */
    srcA = D_801ED214;
    srcB = D_801ED234;
    if (D_80115126 == 4) {
        tmpl = D_801ED254;
    } else {
        tmpl = D_801ED034;
        if (D_80115126 == 5) {
            tmpl = D_801ED278;
        }
    }

    for (i = 0; i < 16; i++) {
        strcpy(&D_801EEB14[i * 36], srcA);
        strcpy(&D_801EED54[i * 36], srcB);
        strcpy(&D_801EEF94[i * 36], tmpl);
    }

    /* ---- phase 2: item table / count dispatch ---- */
    switch (D_80115126) {
    case 0:
        {
            #define flags i

            if ((u8)func_80029178(0xFB) != 0) {
                flags = 1;
            } else {
                flags = (((u32 (*)(void))func_80029504)() >= 0x258);
            }
            if ((u8)func_80029178(0x9B) != 0) {
                flags |= 2;
            }
            if ((u8)func_800291B4(0x5B) >= 3) {
                flags |= 4;
            }
            count = D_801C16AC[flags];
            D_8011515A = count | 0x100;
            table = *(u8 **)(D_801C168C + flags * 4);
            D_801EF1D4 = table;
            #undef flags
        }
        break;
    case 1:
        count = 7;
        if (((u32 (*)(void))func_80029504)() < 0x258) {
            count = 5;
        }
        table = D_801C16B4;
        D_8011515A = count | 0x100;
        D_801EF1D4 = table;
        break;
    case 5:
        table = D_801C16BC;
        D_801EF1D4 = table;
        count = 7;
        break;
    default:
        count = 0;
        break;
    }

    /* ---- phase 3: name copy + quantity render ---- */
    i = 0;
    if (count != 0) {
        do {
            s32 pct;
            s32 sub;
            s32 raw;
            u16 q;

            b = table[i];
            s = *(u8 **)(D_8010EDE8 + b * 12);
            d = &D_801EEB14[i * 36];
            COPY2(d, s)

            pct = D_801EF26C;
            sub = pct;
            if (pct != 0) {
                if (D_80115126 == 0) {
                    raw = (*(s16 *)(D_8010EDE8 + b * 12 + 4) * (100 - pct)) / 100;
                } else {
                    raw = *(u16 *)(D_8010EDEC + b * 12) - sub;
                }
            } else {
                raw = *(u16 *)(D_8010F468 - 0x67C + b * 12);
            }

            q = ((s32 (*)(s16, s32))func_801783D0)(raw, 0);
            RENDER_QTY(&D_801EEB2F[i * 36], q, 0x82, cnt, k, d)

            i++;
        } while (i < count);
    }

    /* ---- phase 4: side-table lookup + conditional strcpy ---- */
    {
        u8 sel = D_801EF290[D_8011514A];

        table = D_801EB574[sel];
        count = D_801EB56C[sel];
        D_801EF1DC = table;
        D_8011515E = count | 0x100;

        if (D_80115126 == 0) {
            if (func_800D0F8C(0xA) != 0) {
                strcpy(D_801EEB94, D_801C12EC);
            }
        }
    }

    /* ---- phase 5 (mode 3): second builder + the 64-entry filter ---- */
    if (D_80115126 == 3) {
        i = 0;
        if (count != 0) {
            do {

                b = table[i];
                s = *(u8 **)(D_8010F468 + b * 8);
                d = &D_801EED54[i * 36];
                COPY2(d, s)

                cnt = (u8)func_800291B4(b + 0x62);
                if ((cnt & 0x80) != 0) {
                    if ((cnt & 0x40) == 0) {
                        u16 q = ((s32 (*)(s16, s32))func_801783D0)(D_800A6586[b], 0);
                        RENDER_QTY(&D_801EED6F[i * 36], q, 0x82, cnt, k, d)
                    } else {
                        strcpy(&D_801EED6A[i * 36], D_801C12EC + 2);
                    }
                } else {
                    strcpy(&D_801EED54[i * 36], D_801C12F0[0]);
                }

                i++;
            } while (i < count);
        }

        if (D_8011511A != 1 && D_8011511A != 2) {
            i = 0;
            cnt = 0;

            for (; i < 0x40; i++) {
                if ((func_800291B4(i + 0x63) & 0x40) != 0) {
                    D_801EF298[cnt++] = i;
                }
            }

            D_8011515C = cnt | 0x100;
            if (D_8011514C >= cnt) {
                if (cnt != 0) {
                    D_8011514C = cnt - 1;
                } else {
                    D_8011514C = 0;
                }
            }
        }
    }

    /* ---- phase 6 (mode 4): 6-entry name/description assembly ---- */
    if (D_80115126 == 4) {
        i = 0;
        do {
            s32 *p;

            s = D_801C12F4[i];
            d = &D_801EEF98[i * 36];
            d[0] = s[0];
            d[1] = s[1];

            d = &D_801EEF98[i * 36 + 4];
            p = ((s32 *)D_801EF254)[i];
            if (p != 0) {
                s = (u8 *)D_801C1264[p[2]];

                COPY2(d, s)
            } else {
                strcpy(&D_801EEF98[i * 36 + 0x16], (char *)D_801C12F4[i + 6]);
            }

            i++;
        } while (i < 6);
    }

    /* ---- phase 7 (mode 5): 6-entry variant ---- */
    if (D_80115126 == 5) {
        i = 0;
        do {
            s32 *p;

            d = &D_801EEF94[i * 36];
            if (i == 0) {
                s = (u8 *)D_801C1324;
            } else {
                s = (u8 *)D_801C12F0[i];
                d += 8;
            }

            COPY2(d, s)

            p = ((s32 *)D_801EF254)[i];
            if (p != 0) {
                strcpy(&D_801EEFA0[i * 36], D_801C1264[p[2]]);
            }

            i++;
        } while (i < 6);
    }
}
