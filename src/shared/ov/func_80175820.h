s32 func_80175820(void)
{
    extern s16 D_800B9A02;
    extern S_AE7BC_80175820_80175820 guess_g_FrontOrderingTablesOrg[];
    extern S_AF634_80175820_80175820 guess_g_PacketBufferUsed[];
    extern u8 D_8011F7A8;
    u8 *p = (u8 *)&D_8011F7A8;
    u32 *ptr;
    u32 old;
    u32 *p2;
    S2_800B9A02 *sq;
    sq = (S2_800B9A02 *)&D_800B9A02;
    ptr = guess_g_FrontOrderingTablesOrg[sq->h].f0;
    old = ptr[2];
    ptr[2] = (old & 0xff000000) | (*(u32 *)(p + sq->h * 4 + 0x20) & 0xffffff);
    p2 = *(u32 **)(p + sq->h * 4 + 0x18);
    *p2 = (*p2 & 0xff000000) | (old & 0xffffff);
    {
        s32 acc = guess_g_PacketBufferUsed[sq->h].g0;
        s32 t = *(s32 *)(p + sq->h * 4 + 0x18) - 0x14;
        guess_g_PacketBufferUsed[sq->h].g0 = acc + ((*(s32 *)(p + sq->h * 4 + 0x20) - t) >> 2);
    }
}
