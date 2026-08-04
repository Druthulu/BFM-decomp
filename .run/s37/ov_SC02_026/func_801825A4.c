extern u8 *func_801290DC(s32 a0, u8 *a1);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 rand(void);
extern u16 D_801AC2F0[][4];
extern s32 D_801AC2E4[];

s32 func_801825A4(void *a0, s32 a1, s32 a2, s32 a3) {
    u8 *obj;
    s32 sub;
    s32 rvA;
    s16 rvB;
    s32 p1;

    p1 = a1;
    obj = func_801290DC(0x41, (u8 *)a0);
    if (obj == 0) {
        return 0;
    }
    {
        s32 idx;

        rvA = rand();
        rvB = rvA;
        sub = *(s32 *)(obj + 0x20);
        *(s32 *)(sub + 0x20) = (s32) D_801AC2E4;
        idx = a3 & 0xF;
        {
            u16 *tbl = D_801AC2F0[idx];
            *(u8 *)(sub + 0x27) = (u8) tbl[2];
            *(u16 *)(sub + 0x28) = tbl[0];
            *(u16 *)(sub + 0x2A) = tbl[1];
        }

        if ((a3 & 0x8000) != 0) {
            s16 spd = (rvA * 0x10000 >> 0x10) % 0x200 + 0x400;
            *(u16 *)(sub + 0x1A) = spd;
            *(u16 *)(sub + 0x18) = spd;
            *(s32 *)(obj + 0x34) = spd;
        } else {
            s16 spd = (rvA * 0x10000 >> 0x10) % 0xC00 + 0x400;
            *(u16 *)(sub + 0x1A) = spd;
            *(u16 *)(sub + 0x18) = spd;
            *(s32 *)(obj + 0x34) = spd;
        }

        {
            s32 sign;
            s32 h;
            s32 mod128;
            s16 srcvec[4];
            s32 buf[8];
            s32 trailing[4];

            sign = -1;
            if ((rvB & 1) != 0) {
                sign = 1;
            }
            h = rvB;
            mod128 = h % 128;

            srcvec[2] = 0;
            trailing[1] = 0;
            trailing[0] = 0;
            trailing[2] = a2;

            srcvec[0] = (s16) (sign * mod128 - 0x300);
            srcvec[1] = (s16) (p1 + sign * (h % 0x300));

            func_80049CAC((s32) srcvec, (s32) buf);
            func_800484EC((s32) buf, (s32) trailing, (s32) (obj + 0x10));
            *(s32 *)(obj + 0x1C) = 0x2D;
        }
    }
    return (s32) obj;
}
