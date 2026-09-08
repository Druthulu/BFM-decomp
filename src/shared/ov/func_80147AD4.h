/* func_80147AD4 — shared body (overlay slot 0x80128158, h_exact 3e1daedf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147CC8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80147B5C(s32 a0, void *a1);
void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3) {
    u8 buf[16];
    func_80147CC8(a0, a1, a2, a3, (s32)buf);
    func_80147B5C(a0, (s32)buf);
}
