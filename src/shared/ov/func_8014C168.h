/* func_8014C168 — shared body (overlay slot 0x80128158, h_exact dbf14d45). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
s32 func_8014C168(s32 * param_1, s32 param_2)
{
    u32 i;
    u16 *p;
    i = 0;
    p = (u16 *)D_801202A0;
    for (; i < 0x60; i++) {
        if (*p == param_2) {
            return p;
        }
        p = (u16 *)((u8 *)p + 0x10C);
    }
    return (u16 *)0;
}
