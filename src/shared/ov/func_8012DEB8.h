/* func_8012DEB8 — shared body (overlay slot 0x80128158, h_exact 5214ae1f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2);
extern s16 D_80126B9A;
s32 func_8012DEB8(s32 a0, s32 a1, s32 a2) {
    s32 sp10[2];
    s32 sp18[2];
    func_8012F214(a0, a1, (s32)sp10);
    func_8012F214(a0, a2, (s32)sp18);
    if (func_8012DF34(a0, (s32)sp10, (s32)sp18) != 0) {
        D_80126B9A = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
        return 1;
    }
    return 0;
}
