/* func_80165A78 — shared body (overlay slot 0x80128158, h_exact 533abb89). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80165AC8(void);
void func_80165A78(s32 arg0)
{
    void *temp_a0;
    func_80165AC8();
    temp_a0 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(arg0, s8 *, 0x197) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = (s32) (M2C_FIELD(arg0, s32 *, 0x44) & ~8);
    M2C_FIELD(temp_a0, u16 *, 0x2C) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x2C) & 0xFFDF);
}
