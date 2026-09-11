void func_8017E830(s32 a0)
{
    /* frame: vars = 0x50 - ROUND8(args 0x10) - ROUND8(4*6 regs) = 0x28  (cookbook 164-53/162i1) */
    s32 pad[10];
    s32 fval;
    s32 n1;
    s32 s4;
    s32 s1, s2;
    u8 *p;
    s32 u;
    u8 u_lo;
    s32 u_hi;
    s32 X, Y;
    s32 x_lo, y_lo, x_hi, y_hi;

    if (*(s16 *)(a0 + 0) == 2) {
        fval = *(s16 *)(a0 + 0x18);
        D_801C8C60 = 1;

        n1 = fval + 1;
        s4 = ((n1 & 7) << 2) + 0x140;
        s1 = (n1 / 8) * 24;

        p = (u8 *)func_80010A08(0x28);
        s2 = s1 + 0x160;
        *(u16 *)(p + 0xE) = GetClut(0x160, 0x1BA);
        *(u16 *)(p + 0x16) = GetTPage(0, 0, s4 & 0x3C0, s2 & -0x100);

        p[3] = 9;
        *(u32 *)(p + 4) = 0x808080;
        p[7] = 0x2C;

        u = (s4 & 0x3F) << 2;
        u_lo = u;
        u_hi = u + 0x10;
        s1 = s1 + 0x178;
        p[0xC] = u_lo;
        p[0xD] = s2;
        p[0x14] = u_hi;
        p[0x15] = s2;
        p[0x1C] = u_lo;
        p[0x1D] = s1;
        p[0x24] = u_hi;
        p[0x25] = s1;

        X = *(s16 *)(a0 + 0x10);
        Y = *(s16 *)(a0 + 0x14);
        x_lo = X - 8;
        y_lo = Y - 9;
        x_hi = X + 8;
        y_hi = Y + 0xF;
        *(s16 *)(p + 0x8) = x_lo;
        *(s16 *)(p + 0xA) = y_lo;
        *(s16 *)(p + 0x10) = x_hi;
        *(s16 *)(p + 0x12) = y_lo;
        *(s16 *)(p + 0x18) = x_lo;
        *(s16 *)(p + 0x1A) = y_hi;
        *(s16 *)(p + 0x20) = x_hi;
        *(s16 *)(p + 0x22) = y_hi;

        AddPrim(*(s32 *)((u8 *)&D_800A651C + ((u16)D_800B9A02 * 0x14)) + 4, p);
    }
}
