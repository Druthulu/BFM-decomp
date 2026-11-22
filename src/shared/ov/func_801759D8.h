/* $v0 at exit: lbu $v0, -0x84F($v0) at ov_MAIN_012:0x801759DC or addu $v0, $v0, $a0 at ov_MAIN_012:0x80175AA0; no byte-neutral return: `return 0;` moved `bnez v0,<func_801759D8+0xdc>` at +0x10, ov_MAIN_012 objdump */
s32 func_801759D8(void)
{
    extern u8 D_8011F7B1;
    extern s16 guess_g_DoubleBufferIndex; // Names ledger: config/names.tsv guess_g_DoubleBufferIndex
    extern GsOT aFrontOrderingTables[] __asm__("guess_g_FrontOrderingTables"); // Names ledger: config/names.tsv guess_g_FrontOrderingTables
    extern S_AF634_801759D8 guess_g_PacketBufferUsed[]; // Names ledger: config/names.tsv guess_g_PacketBufferUsed
    extern u8 guess_g_HudState; // Names ledger: config/names.tsv guess_g_HudState
    u8 *p = (u8 *)&guess_g_HudState;
    u32 *ptr;
    u32 old;
    u32 *p2;
    S2_800B9A02 *sq;
    if (D_8011F7B1 != 0) {
        return;
    }
    sq = (S2_800B9A02 *)&guess_g_DoubleBufferIndex;
    ptr = ((u32 *)aFrontOrderingTables[sq->h].org);
    old = ptr[1];
    ptr[1] = (old & 0xff000000) | (*(u32 *)(p + sq->h * 4 + 0x40) & 0xffffff);
    p2 = *(u32 **)(p + sq->h * 4 + 0x38);
    *p2 = (*p2 & 0xff000000) | (old & 0xffffff);
    {
        s32 acc = guess_g_PacketBufferUsed[sq->h].vx;
        s32 t = *(s32 *)(p + sq->h * 4 + 0x38) - 0x14;
        guess_g_PacketBufferUsed[sq->h].vx = acc + ((*(s32 *)(p + sq->h * 4 + 0x40) - t) >> 2);
    }
}
