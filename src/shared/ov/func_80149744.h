/* func_80149744 — shared body (overlay slot 0x80128158, h_exact 13b4f28e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EBF;
s32 func_80149744(struct S_80149744 *a0) {
    if ((a0->w44 & 0x4) == 0 && D_80078EBF >= 0x80) {
        if (a0->h_AC & 0x80) {
            return 1;
        }
    }
    return 0;
}
