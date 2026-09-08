/* func_8016D5EC — shared body (overlay slot 0x80128158, h_exact 53a6e34a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern short func_8016CF04();
extern void func_80146C3C();
void func_8016D5EC(s32 *a0) {
    u16 *rec = (u16 *)a0[8];   /* lw 0x20(s0) */
    rec[0xC] -= 0x60;          /* 0x18 */
    rec[0xD] -= 0x60;          /* 0x1A */
    if ((s16)((s32 (*)(s32, s32))func_8016CF04)((s32)a0, 2) != 0) {
        ((void (*)(s32 *))func_80146C3C)(a0);
    }
}
