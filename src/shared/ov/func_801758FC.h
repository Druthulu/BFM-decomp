s32 func_801758FC(void)
{
    extern s16 D_800B9A02;
    extern S_AE7BC_801758FC D_800AE7BC[];
    extern S_AF634_801758FC D_800AF634[];
    extern u8 D_8011F7A8;
    u8 *p = (u8 *)&D_8011F7A8;
    u32 *ptr;
    u32 old;
    u32 *p2;
    struct S9 { u16 v; };
    struct S9 *sq;
    sq = (struct S9 *)&D_800B9A02;
    ptr = D_800AE7BC[sq->v].f0;
    old = ptr[3];
    ptr[3] = (old & 0xff000000) | (*(u32 *)(p + sq->v * 4 + 0x30) & 0xffffff);
    p2 = *(u32 **)(p + sq->v * 4 + 0x28);
    *p2 = (*p2 & 0xff000000) | (old & 0xffffff);
    {
        s32 acc = D_800AF634[sq->v].g0;
        s32 t = *(s32 *)(p + sq->v * 4 + 0x28) - 0x14;
        D_800AF634[sq->v].g0 = acc + ((*(s32 *)(p + sq->v * 4 + 0x30) - t) >> 2);
    }
}
