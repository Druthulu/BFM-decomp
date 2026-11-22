void func_80175820(void)
{
    extern s16 guess_g_DoubleBufferIndex; // Names ledger: config/names.tsv guess_g_DoubleBufferIndex
    extern GsOT aFrontOrderingTables[] __asm__("guess_g_FrontOrderingTables"); // Names ledger: config/names.tsv guess_g_FrontOrderingTables
    extern S_AF634_80175820_80175820 guess_g_PacketBufferUsed[]; // Names ledger: config/names.tsv guess_g_PacketBufferUsed
    extern u8 guess_g_HudState; // Names ledger: config/names.tsv guess_g_HudState
    u8 *p = (u8 *)&guess_g_HudState;
    u32 *ptr;
    u32 old;
    u32 *p2;
    S2_800B9A02 *sq;
    sq = (S2_800B9A02 *)&guess_g_DoubleBufferIndex;
    ptr = ((u32 *)aFrontOrderingTables[sq->h].org);
    old = ptr[2];
    ptr[2] = (old & 0xff000000) | (*(u32 *)(p + sq->h * 4 + 0x20) & 0xffffff);
    p2 = *(u32 **)(p + sq->h * 4 + 0x18);
    *p2 = (*p2 & 0xff000000) | (old & 0xffffff);
    {
        s32 acc = guess_g_PacketBufferUsed[sq->h].vx;
        s32 t = *(s32 *)(p + sq->h * 4 + 0x18) - 0x14;
        guess_g_PacketBufferUsed[sq->h].vx = acc + ((*(s32 *)(p + sq->h * 4 + 0x20) - t) >> 2);
    }
}
