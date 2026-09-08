/* func_80174C80 — shared body (overlay slot 0x80128158, h_exact bb1095bd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80174CB0();
void func_80174C80(s32 a0) {
    s32 v;
    v = (*(u16 *)(a0 + 0xA0) - 0x16) & 0xFFF;
    *(s16 *)(a0 + 0xA0) = v;
    func_80174CB0(a0, v);
}
