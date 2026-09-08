/* func_8013A9F8 — shared body (overlay slot 0x80128158, h_exact 763dccb1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013A9F8(s32 a0, s32 a1) {
    s32 orig = a1;
    a1 -= 2;
    a1 &= 0xFFFF;
    if ((u32)a1 < 5) {
        s32 b = orig & 0xFFFF;
        b -= 2;
        b <<= 10;
        *(s16*)(a0 + 0xE) = b;
    }
}
