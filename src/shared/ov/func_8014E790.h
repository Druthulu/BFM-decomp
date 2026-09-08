/* func_8014E790 — shared body (overlay slot 0x80128158, h_exact dbe2dc59). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8014E790(s32 arg0, s16 * arg1, s16 * arg2)
{
    s32 temp_a1;
    void *temp_s0;
    temp_s0 = M2C_FIELD(arg0, void **, 0x180);
    if ((M2C_FIELD(temp_s0, u16 *, 0) == 0) || !(M2C_FIELD(temp_s0, u16 *, 0x5C) & 0x20) || (temp_a1 = M2C_FIELD(temp_s0, s32 *, 0x58), (temp_a1 == 0)) || (func_80135888(M2C_FIELD(temp_s0, s32 *, 0x20), temp_a1, arg1, arg2) == 0)) {
        M2C_FIELD(arg0, void **, 0x180) = NULL;
        return 0;
    }
    M2C_FIELD(arg0, u16 *, 6) = (u16) M2C_FIELD(temp_s0, u16 *, 6);
    M2C_FIELD(arg0, u16 *, 0xA) = (u16) M2C_FIELD(temp_s0, u16 *, 0xA);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(temp_s0, u16 *, 0xE);
    return 1;
}
