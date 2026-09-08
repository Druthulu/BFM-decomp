/* func_80163328 — shared body (overlay slot 0x80128158, h_exact 6830db40). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80115100;
extern u16 D_80126B18[];
extern s32 D_80115200;
void func_80163328(void) {
    u32 i;
    s32 *table;
    u16 *src;
    s32 *flags;
    i = 0;
    table = &D_80115100;
    src = D_80126B18;
    flags = &D_80115200;
    do {
        if (*flags & 1) {
            u8 *dst = (u8 *)*table;
            *(struct Vec4s *)(dst + 0x7C) = *(struct Vec4s *)src;
            *(s16 *)((u8 *)*table + 0x82) = 0;
        }
        table += 1;
        src += 4;
        i += 1;
        flags += 1;
    } while (i < 3);
}
