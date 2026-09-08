/* func_80156670 — shared body (overlay slot 0x80128158, h_exact 65803f4f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80156B74(s32 param_1, u32 param_2, u8 *param_3);
extern void func_80157158(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
void func_80156670(s32 param_1, s32 param_2, s32 param_3, s32 param_4, s32 param_5, u16 param_6)
{
    extern s32 D_801151E0[];
    extern s32 D_801150E0[];
    extern u8 D_8011DAD8[];
    extern B8 D_80128120[];
    extern B8 D_80128138[];
    extern S8 D_80126AF0[];
    extern u8 D_80126730[];
    extern u8 D_8011520C[];
    extern S8 D_801270A8;
    u32 i;
    func_80156B74(param_1, param_4, (u8 *)(param_1 + 0x1A9));
    i = 0;
    do {
        D_801151E0[i] = 0;
        if (D_80126AF0[i].d == 0) {
            D_801151E0[i] = ((s32 (*)(s32, u16, u16, s32, s32, s32, s32, s32, s32,
                                      s32, u16, s32, s32))func_80157158)(
                param_1, param_2 & 0xFFFF, param_3 & 0xFFFF,
                (s32)&D_801270A8,
                (s32)&D_80126AF0[i],
                (s32)&D_80128120[i],
                (s32)&D_80128138[i],
                (s32)&D_801150E0[i],
                (s32)&D_8011DAD8[i * 8],
                param_5,
                param_6,
                (s32)&D_8011520C[i],
                (s32)&D_80126730[i]);
        }
        i = i + 1;
    } while (i < 3);
}
