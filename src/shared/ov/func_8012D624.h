/* func_8012D624 — shared body (overlay slot 0x80128158, h_exact 2b11831e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_8012D664();
void func_8012D624(s32 a0) {
    u16 sp[3];
    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA);
    sp[2] = *(u16 *)(a0 + 0xE);
    func_8012D664((void *)sp);
}
