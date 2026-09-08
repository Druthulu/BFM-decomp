/* func_801485B8 — shared body (overlay slot 0x80128158, h_exact 5ab3182a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801485B8(s32 arg0, s32 arg1, s32 arg2)
{
    M2C_FIELD(arg1, s16 *, 0) = (s16) (s8) M2C_FIELD(arg0, u8 *, 0);
    M2C_FIELD(arg1, s16 *, 2) = (s16) (s8) M2C_FIELD(arg0, u8 *, 1);
    M2C_FIELD(arg1, s16 *, 4) = (s16) (s8) M2C_FIELD(arg0, u8 *, 2);
    M2C_FIELD(arg2, s16 *, 0) = (s16) (s8) M2C_FIELD(arg0, u8 *, 3);
    M2C_FIELD(arg2, s16 *, 2) = (s16) (s8) M2C_FIELD(arg0, u8 *, 4);
    M2C_FIELD(arg2, s16 *, 4) = (s16) (s8) M2C_FIELD(arg0, u8 *, 5);
}
