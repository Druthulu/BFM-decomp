/* func_80155344 — shared body (overlay slot 0x80128158, h_exact a58bff3d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_800DE2A4[];
void func_80155344(s32 a0) {
    s32 *p = D_800DE2A4;
    s32 v0 = *p;
    if (v0 != 0) {
        do {
            v0 |= 0x1000000;
            *p = v0;
            p += 1;
            v0 = *p;
        } while (v0 != 0);
    }
    *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x44) & 0xCFFFFFFF;
}
