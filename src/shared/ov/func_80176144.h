/* func_80176144 — shared body (overlay slot 0x80128158, h_exact 036f6784). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80176144(s32 a0)
{
    extern S_AF634 aAF634[] __asm__("D_800AF634");
    extern S_AF634 aAF638[] __asm__("D_800AF638");
    extern u8  D_8011F7A8;
    extern s16 D_8011F7BC;
    extern s16 D_8011F7BE;
    extern s32 func_80178004();
    u32 *slot;
    u32 *p;
    s16 param_1 = (s16)a0;
    p = (u32 *)(aAF638[param_1].g0 + aAF634[param_1].g0 * 4);
    slot = (u32 *)(param_1 * 4 + (s32)&D_8011F7A8);
    slot[14] = (u32)p;
    __asm__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B headers1)
    p = (u32 *)func_80178004((s32)p,
                             (s16)((*(u16 *)&D_8011F7BC) - 0x17),
                             (s16)((*(u16 *)&D_8011F7BE) + 0x65));
    slot[16] = (u32)p - 0x14;
    p += 5;
    aAF634[param_1].g0 += ((s32)p - (s32)slot[14]) >> 2;
}
