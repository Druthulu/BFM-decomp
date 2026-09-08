/* func_8016236C — shared body (overlay slot 0x80128158, h_exact 9d5c9feb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014706C(void *a0);
extern s32 D_80126B58;
s32 func_8016236C(u8 *a0) {
    func_8014706C(&D_80126B58);
    *(s32 *)(a0 + 0x28) = 0xA;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}
