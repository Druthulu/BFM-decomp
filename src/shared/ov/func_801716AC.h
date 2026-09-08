/* func_801716AC — shared body (overlay slot 0x80128158, h_exact 357e4888). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80012FC8(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_800A5E94;
extern u8 D_800A5E95;
extern u8 D_800A5E96;
s32 func_801716AC(s32 a0, void * a1, s32 * a2)
{
    s32 d;
    s32 p;
    a0 = a0 * 0x10;
    p = a0 + (s32)a1;
    d = (s16)func_80012FC8(*(u8 *)(p + 0xC), (&D_800A5E94)[a0], 10, 1);
    *a2 += d;
    *(char *)(p + 0xC) = *(u8 *)(p + 0xC) + d;
    d = (s16)func_80012FC8(*(u8 *)(p + 0xD), (&D_800A5E95)[a0], 10, 1);
    *a2 += d;
    *(char *)(p + 0xD) = *(u8 *)(p + 0xD) + d;
    d = (s16)func_80012FC8(*(u8 *)(p + 0xE), (&D_800A5E96)[a0], 10, 1);
    *a2 += d;
    *(char *)(p + 0xE) = *(u8 *)(p + 0xE) + d;
}
