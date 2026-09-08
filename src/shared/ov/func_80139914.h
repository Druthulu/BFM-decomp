/* func_80139914 — shared body (overlay slot 0x80128158, h_exact b62f6b5d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013A8B0(s32 *a0);
void func_80139914(s32 arg0)
{
    s32 temp_a0;
    M2C_FIELD(arg0, s16 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    if (M2C_FIELD(arg0, u16 *, 0x18) != 0) {
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x40);
        if (temp_a0 != 0) {
            func_8013A8B0(temp_a0);
        }
    }
}
