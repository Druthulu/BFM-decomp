/* func_80162CCC — shared body (overlay slot 0x80128158, h_exact 14311349). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void aF80162CCC(u8 *a0) __asm__("func_80162CCC");
void aF80162CCC(u8 *a0)
{
    u8 *s0 = a0;
    u16 *p = *(u16 **)(s0 + 0x20);
    if (p != 0) {
        s32 a1;
        if (*p == 1) {
            a1 = 0x84;
        } else {
            a1 = 0x38;
        }
        func_80016714(p, a1);
    }
    func_80016714(s0, 0x68);
}
