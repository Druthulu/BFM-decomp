void func_80182560(void *arg0)
{
    extern s32 D_801B20E0;
    extern s32 D_8019FD8C;
    extern s32 D_801AEBCC;
    extern s32 D_801AEC60;
    extern s16 D_801AEAFE;
    extern void func_8017EF68(s32 a0, s32 a1, s32 a2);

    s32 *p;
    p = (s32)&D_801AEBCC;

    p[-7] = 0;
    p[0] = D_801AEAFE;
    func_8017EF68((s32)&D_801B20E0, (s32)&D_8019FD8C, (s32)(p - 7));
    if (D_801AEC60 != 0) {
        ((struct { u8 pad[2]; u16 f; } *)arg0)->f += 1;
    }
}
