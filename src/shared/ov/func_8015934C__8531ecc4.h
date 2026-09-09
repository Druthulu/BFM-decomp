/* func_8015934C — shared body (overlay slot 0x80128158, h_exact 8531ecc4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015934C(void *arg0) {
    void *temp_v1;

    if (D_8018E850 == 4) {
        D_8018E850 = 5;
    }
    if (D_8018E858 != 0) {
        func_80145BF8();
        func_80146CA0(arg0);
        D_800AE6BD += 1;
    }
    temp_v1 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_v1, u16 *, 0x12) = (u16) ((M2C_FIELD(temp_v1, u16 *, 0x12) + 0x16) & 0xFFF);
}
