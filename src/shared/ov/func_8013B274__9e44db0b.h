/* func_8013B274 — shared body (overlay slot 0x80128158, h_exact 9e44db0b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013B274(s32 a0, s32 a1, void *a2)
{
    u8 *p;
    s32 L[10];
    s16 sa;
    s32 quot;
    s16 ang;

    p = (u8 *)func_80010A08(0x28);
    p[3] = 9;
    p[7] = 0x2C;
    p[4] = 0x80;
    p[5] = 0x80;
    p[6] = 0x80;
    *(s16 *)(p + 0x16) = 0x37;
    *(s16 *)(p + 0xE) = 0x6FD6;
    p[0xC] = 0xE0;
    p[0xD] = 0;
    p[0x14] = 0xEF;
    p[0x15] = 0;
    p[0x1C] = 0xE0;
    p[0x1D] = 0xF;
    p[0x24] = 0xEF;
    p[0x25] = 0xF;

    sa = (s16)a1;
    if (sa == 0) {
        *(s16 *)L = 0;
    } else {
        quot = ((s32)sa << 12) / ((s16*)a2)[0];
        ang = (s16)quot;
        if (!(D_8017F20E < ang)) goto outer_else;
        if (!(ang < D_8017F214)) goto inner_else;
        if (ang < D_8017F210) { *(s16 *)L = D_8017F210; goto done; }
        if (D_8017F212 < ang) { *(s16 *)L = D_8017F212; goto done; }
        *(s16 *)L = quot;
        goto done;
    outer_else:
        if (ang < D_8017F20C) { *(s16 *)L = D_8017F20C; goto done; }
        *(s16 *)L = quot;
        goto done;
    inner_else:
        if (D_8017F216 < ang) { *(s16 *)L = D_8017F216; goto done; }
        *(s16 *)L = quot;
    done: ;
    }
    *(s16 *)((u8 *)L + 2) = D_800D45F6;

    __asm__ __volatile__(
        "lwc2 $0, 0(%0)\n"
        "lwc2 $1, 4(%0)\n"
        "nop\n" "nop\n"
        "mvmva 1, 0, 0, 0, 0\n"
        : : "r"(L) : "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldv0+gte_rt_m) beyond Sony's (P36 T5 gte2)
    gte_stlvnl((u8 *)L + 8);

    if (((s16*)a2)[1] > 0)
        *(s32 *)((u8 *)L + 0xC) -= 1;
    else
        *(s32 *)((u8 *)L + 0xC) += 2;

    *(s16 *)L = 9;
    *(s16 *)((u8 *)L + 2) = 9;
    __asm__ __volatile__(
        "lwc2 $0, 0(%0)\n"
        "lwc2 $1, 4(%0)\n"
        "nop\n" "nop\n"
        "mvmva 1, 0, 0, 3, 0\n"
        : : "r"(L) : "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldv0+gte_rtv0_m) beyond Sony's (P36 T5 gte2)
    gte_stlvnl((u8 *)L + 0x18);

    *(s16 *)(p + 8) = *(s32 *)((u8 *)L + 8);
    *(s16 *)(p + 0xA) = *(s32 *)((u8 *)L + 0xC);
    *(s16 *)(p + 0x10) = *(volatile s32 *)((u8 *)L + 8) + *(s32 *)((u8 *)L + 0x18);
    *(s16 *)(p + 0x12) = *(volatile s32 *)((u8 *)L + 0xC);
    *(s16 *)(p + 0x18) = *(volatile s32 *)((u8 *)L + 8);
    *(s16 *)(p + 0x1A) = *(volatile s32 *)((u8 *)L + 0xC) + *(s32 *)((u8 *)L + 0x1C);
    *(s16 *)(p + 0x20) = *(volatile s32 *)((u8 *)L + 8) + *(volatile s32 *)((u8 *)L + 0x18);
    *(s16 *)(p + 0x22) = *(volatile s32 *)((u8 *)L + 0xC) + *(volatile s32 *)((u8 *)L + 0x1C);

    ((P_TAG *)p)->addr = ((P_TAG *)a0)->addr;
    ((P_TAG *)a0)->addr = (u32)p;
}
