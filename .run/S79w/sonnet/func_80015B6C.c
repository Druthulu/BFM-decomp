extern void *func_80010A08(s32 a0);
extern u16 D_800B9A02;

typedef struct { s32 a; s32 b[4]; } OtBlk_80016450;

void func_80015B6C(s32 x, s32 y, s32 width, s32 height, u8 c1, u8 c2, u8 c3, u8 c4, u8 c5, u8 c6)
{
    extern OtBlk_80016450 D_800A651C[];
    u8 *p;
    s32 otp;
    register u32 m24 __asm__("$5");
    register u32 mFF __asm__("$7");
    register u32 one __asm__("$8");

    otp = D_800A651C[D_800B9A02].a;
    p = (u8 *)func_80010A08(0x34);
    m24 = 0xFFFFFF;
    one = 1;

    {
        register u32 tag __asm__("$4");
        p[3] = (u8)one;
        tag = *(u32 *)p;
        mFF = 0xFF000000;
        *(u32 *)(p + 4) = 0xE1000000;
        tag = (tag & mFF) | (*(u32 *)(otp + 0x3FFC) & m24);
        *(u32 *)p = tag;
        __asm__ __volatile__("" : "=r"(p) : "0"(p));
        tag = (u32)p & m24;
        p += 8;
        *(u32 *)(otp + 0x3FFC) = (*(u32 *)(otp + 0x3FFC) & mFF) | tag;
        __asm__ __volatile__("" ::: "memory");
    }

    {
        register s32 xa __asm__("$4");
        s32 ya;
        register u32 tag2 __asm__("$6");

        p[3] = 8;
        p[7] = 0x38;
        xa = x;
        ya = y;
        __asm__ __volatile__("" : "=r"(xa) : "0"(xa));
        __asm__ __volatile__("" : "=r"(ya) : "0"(ya));
        p[4] = c1; p[5] = c2; p[6] = c3;
        p[0xC] = c1; p[0xD] = c2; p[0xE] = c3;
        p[0x14] = c4; p[0x15] = c5; p[0x16] = c6;
        p[0x1C] = c4; p[0x1D] = c5; p[0x1E] = c6;
        *(s16 *)(p + 8) = xa;
        *(s16 *)(p + 0xA) = ya;
        tag2 = *(u32 *)p;
        x += width;
        *(s16 *)(p + 0x10) = x;
        *(s16 *)(p + 0x12) = ya;
        *(s16 *)(p + 0x18) = xa;
        y += height;
        tag2 = (tag2 & mFF) | (*(u32 *)(otp + 0x3FFC) & m24);
        *(s16 *)(p + 0x1A) = y;
        *(s16 *)(p + 0x20) = x;
        *(s16 *)(p + 0x22) = y;
        *(u32 *)p = tag2;
        xa = (s32)((u32)p & m24);
        p += 0x24;
        *(u32 *)(otp + 0x3FFC) = (*(u32 *)(otp + 0x3FFC) & mFF) | (u32)xa;
    }

    {
        register u32 tag3 __asm__("$4");
        p[3] = (u8)one;
        tag3 = *(u32 *)p;
        *(u32 *)(p + 4) = 0xE1000200;
        tag3 = (tag3 & mFF) | (*(u32 *)(otp + 0x3FFC) & m24);
        *(u32 *)p = tag3;
        p = (u8 *)((u32)p & m24);
        *(u32 *)(otp + 0x3FFC) = (*(u32 *)(otp + 0x3FFC) & mFF) | (u32)p;
    }
}
