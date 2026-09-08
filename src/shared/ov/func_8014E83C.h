/* func_8014E83C — shared body (overlay slot 0x80128158, h_exact 37b0c830). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801202A0[];
s32 func_8014E83C(s32 arg0, s16 * arg1, s16 * arg2)
{
    register u8 *p   __asm__("$17");  /* $s1 */
    register u8 *q   __asm__("$16");  /* $s0 */
    u8 *end;
    s32 t;
    p = D_801202A0;
    if ((u32)p < (u32)(p + 0x6480)) {
        end = p + 0x6480;
        q = p + 0xE;
        do {
            if (*(u16 *)p != 0 && (*(u16 *)(q + 0x4E) & 0x20) &&
                (t = *(s32 *)(q + 0x4A), t != 0) &&
                func_80135888(*(s32 *)(q + 0x12), t, arg1, arg2) != 0) {
                *(s32 *)(arg0 + 0x180) = (s32)p;
                *(u16 *)(arg0 + 0x6) = *(u16 *)(q - 0x8);
                *(u16 *)(arg0 + 0xA) = *(u16 *)(q - 0x4);
                *(u16 *)(arg0 + 0xE) = *(u16 *)q;
                return 1;
            }
            p += 0x10C;
            q += 0x10C;
        } while ((u32)p < (u32)end);
    }
    return 0;
}
