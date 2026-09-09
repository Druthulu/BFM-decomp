/* func_80130D48 — shared body (overlay slot 0x80128158, h_exact f3dfe4ca). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80130D48(s32 arg0)
{
    register s16 *tbl __asm__("$16");
    register s32 pa __asm__("$18") = arg0;
    register u8 *p  __asm__("$19") = D_80078E78;
    s32 s1v;
    s32 call_a0;
    s32 call_a1;
    s32 cnt;
    s32 r;
    void *ret;

    s1v = func_80131CF4(*(s32 *)((s8 *)pa + 0xBC), 0x15);
    if (s1v == 0) {
        return;
    }

    if (*(u8 *)((s8 *)pa + 0x5E) == 0xB) {
        call_a0 = 0x33;
        call_a1 = 0;
        goto do_call;
    }

    switch (s1v & 0xFFFF0000) {
    case 0x10000: {
        u32 x = D_80078EB4;
        u32 y = D_80078EB2;
        u32 b;
        u32 a;

        s1v = 0;
        if (x == y) {
            s1v = 0xC;
        } else if ((y >> 1) >= x) {
            s1v = 3;
        }

        b = *(u16 *)(p + 0x40);
        a = *(u16 *)(p + 0x3E);
        if (b == a) {
            s1v += 0x18;
        } else if ((a >> 1) >= b) {
            s1v += 6;
        }
        { register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2"); v1 = s1v * 2; bp = (s8 *)D_8017F688; tbl = (s16 *)(bp + v1); }

        r = rand() % 100;
        cnt = 0;
    loop27:
        if (r >= *tbl) {
            cnt += 1;
            tbl += 1;
            if (cnt < 3) {
                goto loop27;
            }
        }

        s1v = 0;
        switch (cnt) {
        case 0:
            tbl = D_8017F6E8;
            s1v = 0x31;
            break;
        case 1: {
            s32 mx = *(u16 *)(p + 0x3A);
            s32 cur = *(u16 *)(p + 0x3C);
            if (((mx * 7) / 10) >= cur) {
                s1v = 4;
                if ((mx / 2) >= cur) {
                    s1v = 8;
                    if ((mx / 5) >= cur) {
                        s1v = 0xC;
                    }
                }
            }
            { register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2"); v1 = s1v * 2; bp = (s8 *)D_8017F6F0; tbl = (s16 *)(bp + v1); }
            s1v = 0x32;
            break;
        }
        case 2: {
            s32 mx = *(u16 *)(p + 0x3E);
            s32 cur = *(u16 *)(p + 0x40);
            if (((mx * 7) / 10) >= cur) {
                s1v = 4;
                if ((mx / 2) >= cur) {
                    s1v = 8;
                    if ((mx / 5) >= cur) {
                        s1v = 0xC;
                    }
                }
            }
            { register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2"); v1 = s1v * 2; bp = (s8 *)D_8017F710; tbl = (s16 *)(bp + v1); }
            s1v = 0x33;
            break;
        }
        }

        r = rand() % 100;
        call_a1 = 0;
    loop50:
        if (r >= *tbl) {
            call_a1 += 1;
            tbl += 1;
            if (call_a1 < 4) {
                goto loop50;
            }
        }
        call_a0 = s1v;
        goto do_call;
    }
    case 0x20000:
        call_a0 = 0x33;
        call_a1 = 0;
        goto do_call;
    case 0x30000:
        call_a0 = 0x31;
        call_a1 = 0;
        goto do_call;
    case 0x40000:
        call_a0 = 0x32;
        call_a1 = 0;
        goto do_call;
    case 0x50000:
        call_a0 = 0x33;
        call_a1 = 0;
        goto do_call;
    case 0x60000: {
        s32 rr = rand() & 0xFF;
        tbl = D_8017F658;
        if (rr >= *tbl) {
            do {
                tbl += 3;
            } while (rr >= *tbl);
        }
        call_a0 = tbl[1];
        if (*(u16 *)(p + 0x40) < 4U) {
            call_a0 = 0x33;
        }
        call_a1 = tbl[2];
        goto do_call;
    }
    case 0x70000:
        call_a0 = 0x27B;
        call_a1 = 0;
        goto do_call;
    default:
        return;
    }

do_call:
    ret = func_8012C658(call_a0, call_a1, pa);
    if (ret != 0) {
        *(u16 *)((s8 *)ret + 0xA) -= 0x20;
    }
}
