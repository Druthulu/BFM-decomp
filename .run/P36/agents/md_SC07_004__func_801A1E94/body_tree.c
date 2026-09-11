void func_801A1E94(void)
{
    register s32 param_1 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    s32 p;
    s32 *s0;
    s32 *s1;

    p = param_1;
    s0 = (s32 *)p;
    s1 = &D_801BF01C;
    func_8001C924(*(s32 *)(p + 0x20), s1);
    func_80132288(&D_801F8724, &D_801AFB58, *s1);
    *(s16 *)(p + 0xA) = -0x240;
    *(s16 *)(p + 0xE) = 0x30;
    *(s32 *)(p + 0xD4) = func_801A8528(p);
    func_80178B18(p, (s32)&D_801AFCF8);
    *(s32 *)(p + 0x1C) = 0x60;
    *(s16 *)(p + 0x100) = 0xFF;
    *(s16 *)(p + 0x84) = 0;
    func_8012AD44((s32 *)p, 0xE);
}
