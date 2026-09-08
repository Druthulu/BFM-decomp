/* func_8012C1DC — shared body (overlay slot 0x80128158, h_exact a7397612). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800B3DF0[];
s32 func_8012C1DC(s32 a0) {
    u8 *p;
    u8 *end;
    p = (u8 *)(*(s32 *)(a0 + 0x20) + 0x84);
    end = D_800B3DF0;
    if (p != end) {
        do {
            if (*(u16 *)p == 0) {
                return (s32)p;
            }
            p += 0x84;
        } while (p != end);
    }
    return 0;
}
