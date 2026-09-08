/* func_801554B8 — shared body (overlay slot 0x80128158, h_exact 935863b1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801659DC();
s32 func_801554B8(void *arg0) {
    s32 var_v0;
    u8 temp_a0;
    temp_a0 = M2C_FIELD(arg0, u8 *, 0x1A0);
    var_v0 = 0;
    if (temp_a0 != M2C_FIELD(arg0, u8 *, 0x196)) {
        if (func_800D02D0(temp_a0) != 0) {
            M2C_FIELD(arg0, u8 *, 0x196) = (u8) M2C_FIELD(arg0, u8 *, 0x1A0);
            func_801659DC(arg0);
            return 0;
        }
        var_v0 = 1;
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}
