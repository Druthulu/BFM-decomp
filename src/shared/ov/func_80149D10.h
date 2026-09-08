/* func_80149D10 — shared body (overlay slot 0x80128158, h_exact 2511bb94). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 func_8014B5B8(s32 *a0);
extern u8 D_80078EBF;
extern u8 D_80078EC0;
s32 func_80149D10(s32 a0) {
    if (*(s32 *)(a0 + 0x44) & 0x400) {
        return 0;
    }
    if (D_80078EBF != 0x80) {
        return 0;
    }
    if ((D_80078EC0 & 0x7F) == 0) {
        return 0;
    }
    if (*(u16 *)(a0 + 0xAC) & 0x10) {
        if ((func_8014B5B8((s32 *)a0) & 0xFF) != 0) {
            return 2;
        }
        return 1;
    }
    return 0;
}
