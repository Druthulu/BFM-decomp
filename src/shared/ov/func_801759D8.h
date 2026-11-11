s32 func_801759D8(void)
{
    extern u8 D_8011F7B1;
    extern s16 guess_g_DoubleBufferIndex;
    extern S_AE7BC_801759D8 guess_g_FrontOrderingTablesOrg[];
    extern S_AF634_801759D8 guess_g_PacketBufferUsed[];
    extern u8 D_8011F7A8;
    u8 *p = (u8 *)&D_8011F7A8;
    u32 *ptr;
    u32 old;
    u32 *p2;
    S2_800B9A02 *sq;
    if (D_8011F7B1 != 0) {
        return;
    }
    sq = (S2_800B9A02 *)&guess_g_DoubleBufferIndex;
    ptr = guess_g_FrontOrderingTablesOrg[sq->h].f0;
    old = ptr[1];
    ptr[1] = (old & 0xff000000) | (*(u32 *)(p + sq->h * 4 + 0x40) & 0xffffff);
    p2 = *(u32 **)(p + sq->h * 4 + 0x38);
    *p2 = (*p2 & 0xff000000) | (old & 0xffffff);
    {
        s32 acc = guess_g_PacketBufferUsed[sq->h].g0;
        s32 t = *(s32 *)(p + sq->h * 4 + 0x38) - 0x14;
        guess_g_PacketBufferUsed[sq->h].g0 = acc + ((*(s32 *)(p + sq->h * 4 + 0x40) - t) >> 2);
    }
}
