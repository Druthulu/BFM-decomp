/* func_80163764 — shared body (overlay slot 0x80128158, h_exact fa4fafa0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
extern s32 func_801506A4();
extern u8 D_801202A0[];
s32 func_80163764(s32 a0)
{
    s32 counter;
    u8 *ptr;
    s32 loaded_value;
    counter = 0;
    ptr = D_801202A0;
    loaded_value = *(s32 *)(a0 + 0x4C);
    while (1) {
        if (*(u16 *)ptr != 0) {
            if ((*(u16 *)(ptr + 0x5C) & 0x100) != 0) {
                if (func_8014C278(a0, (s32)ptr, 0x40) != 0) {
                    ((s32 (*)(s32, s32))func_801506A4)(loaded_value, (s32)ptr);
                    return 1;
                }
            }
        }
        counter++;
        if ((u32)counter >= 0x60) {
            break;
        }
        ptr += 0x10C;
    }
    return 0;
}
