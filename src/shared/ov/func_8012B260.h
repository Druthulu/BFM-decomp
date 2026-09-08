/* func_8012B260 — shared body (overlay slot 0x80128158, h_exact 6ec86c60). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8012B260(u8 *a0) {
    u8 *a1;
    s32 a, b, c;
    u16 t;
    a1 = *(u8 **)(a0 + 0x20);
    a = (u16)*(u16 *)(a0 + 6) + (u16)*(u16 *)(a0 + 0x50);
    *(u16 *)(a1 + 8) = a;
    *(s32 *)(a1 + 0x48) = (s16)a;
    b = (u16)*(u16 *)(a0 + 0xA) + (u16)*(u16 *)(a0 + 0x52);
    *(u16 *)(a1 + 0xA) = b;
    *(s32 *)(a1 + 0x4C) = (s16)b;
    c = (u16)*(u16 *)(a0 + 0xE);
    t = *(u16 *)(a1 + 0x2C) | 1;
    c = c + (u16)*(u16 *)(a0 + 0x54);
    *(u16 *)(a1 + 0xC) = c;
    *(u16 *)(a1 + 0x2C) = t;
    *(s32 *)(a1 + 0x50) = (s16)c;
}
