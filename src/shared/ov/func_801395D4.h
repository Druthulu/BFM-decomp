/* func_801395D4 — shared body (overlay slot 0x80128158, h_exact 16b2a102). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);
void func_801395D4(void * a0)
{
    Stk801395D4 sp10;
    u16 mul;
    u16 base;
    sp10.f0 = *(u16 *)(a0 + 0x38);
    mul = *(u16 *)(a0 + 0x12);
    base = *(u16 *)(a0 + 0x3A);
    sp10.f4 = 0x38;
    sp10.f6 = 0xC;
    sp10.f2 = base + mul * 12;
    func_80059888(&sp10, 0, 0, 0);
}
