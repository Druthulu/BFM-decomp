/* func_80176144 — shared body (overlay slot 0x80128158, h_exact 036f6784). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80176144(s32 a0)
{
    extern S_AF634 guess_g_PacketBufferUsed[];
    extern S_AF634 guess_g_PacketBufferBase[];
    extern u8  guess_g_HudState;
    extern s16 guess_g_HudGoldPanelX;
    extern s16 guess_g_HudGoldPanelY;
    extern s32 func_80178004(uint *param_1, uint param_2, int param_3);
    u32 *slot;
    u32 *p;
    s16 param_1 = (s16)a0;
    p = (u32 *)(guess_g_PacketBufferBase[param_1].g0 + guess_g_PacketBufferUsed[param_1].g0 * 4);
    slot = (u32 *)(param_1 * 4 + (s32)&guess_g_HudState);
    do { slot[14] = (u32)p; } while (0);
    p = (u32 *)func_80178004((s32)p,
                             (s16)((*(u16 *)&guess_g_HudGoldPanelX) - 0x17),
                             (s16)((*(u16 *)&guess_g_HudGoldPanelY) + 0x65));
    slot[16] = (u32)p - 0x14;
    p += 5;
    guess_g_PacketBufferUsed[param_1].g0 += ((s32)p - (s32)slot[14]) >> 2;
}
