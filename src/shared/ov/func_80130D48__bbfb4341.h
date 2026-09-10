/* func_80130D48 — shared body (overlay slot 0x80128158, h_exact bbfb4341). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80130D48(s32 arg0)
{
    s16 *tbl;
    u8 *p = D_80078E78;
    s32 val;
    s32 i;
    s32 j;
    s32 r;
    s32 ret;

    val = func_80131CF4(*(s32 *)((s8 *)arg0 + 0xBC), 0x15);
    if (val == 0) {
        return;
    }

    if (*(u8 *)((s8 *)arg0 + 0x5E) == 0xB) {
        ret = func_8012C658(0x33, 0, arg0);
    } else {
        switch (val & 0xFFFF0000) {
        case 0x10000: {
            u32 x = D_80078EB4;
            u32 y = D_80078EB2;
            u32 b;
            u32 a;

            val = 0;
            if (x == y) {
                val = 0xC;
            } else if ((y >> 1) >= x) {
                val = 3;
            }

            b = *(u16 *)(p + 0x40);
            a = *(u16 *)(p + 0x3E);
            if (b == a) {
                val += 0x18;
            } else if ((a >> 1) >= b) {
                val += 6;
            }
            tbl = D_8017EED4 + val;

            r = rand() % 100;
            for (i = 0; i < 3; i++, tbl++) {
                if (r < *tbl) {
                    break;
                }
            }

            val = 0;
            switch (i) {
            case 0:
                tbl = D_8017EF34;
                val = 0x31;
                break;
            case 1: {
                s32 mx = *(u16 *)(p + 0x3A);
                s32 cur = *(u16 *)(p + 0x3C);
                if (((mx * 7) / 10) >= cur) {
                    val = 4;
                    if ((mx / 2) >= cur) {
                        val = 8;
                        if ((mx / 5) >= cur) {
                            val = 0xC;
                        }
                    }
                }
                tbl = D_8017EF3C + val;
                val = 0x32;
                break;
            }
            case 2: {
                s32 mx = *(u16 *)(p + 0x3E);
                s32 cur = *(u16 *)(p + 0x40);
                if (((mx * 7) / 10) >= cur) {
                    val = 4;
                    if ((mx / 2) >= cur) {
                        val = 8;
                        if ((mx / 5) >= cur) {
                            val = 0xC;
                        }
                    }
                }
                tbl = D_8017EF5C + val;
                val = 0x33;
                break;
            }
            }

            r = rand() % 100;
            for (j = 0; j < 4; j++, tbl++) {
                if (r < *tbl) {
                    break;
                }
            }
            ret = func_8012C658(val, j, arg0);
            break;
        }
        case 0x20000:
            ret = func_8012C658(0x33, 0, arg0);
            break;
        case 0x30000:
            ret = func_8012C658(0x31, 0, arg0);
            break;
        case 0x40000:
            ret = func_8012C658(0x32, 0, arg0);
            break;
        case 0x50000:
            ret = func_8012C658(0x33, 0, arg0);
            break;
        case 0x60000: {
            s32 rr = rand() & 0xFF;
            s32 id;
            tbl = D_8017EEA4;
            while (rr >= *tbl) {
                tbl += 3;
            }
            id = tbl[1];
            if (*(u16 *)(p + 0x40) < 4U) {
                id = 0x33;
            }
            ret = func_8012C658(id, tbl[2], arg0);
            break;
        }
        case 0x70000:
            ret = func_8012C658(0x27B, 0, arg0);
            break;
        default:
            return;
        }
    }

    if (ret != 0) {
        *(u16 *)(ret + 0xA) -= 0x20;
    }
}
