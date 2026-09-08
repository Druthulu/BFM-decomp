/* func_8017DC4C — shared body (overlay slot 0x80128158, h_exact 48877b49). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014706C(void *arg0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_8013C938(void);
extern void func_8012943C(void);
extern void func_80171A1C(u8 *a0);
extern s32 D_8018F0BC;
extern u8 D_800B9A11;
void func_8017DC4C(s32 *a0) {
    s32 v0 = a0[0x80];
    s32 v1;
    v1 = v0 - 1;
    a0[0x80] = v1;
    if (v1 != -1) {
        return;
    }
    func_8014706C(a0);
    func_80154274(a0, (s32)&D_8018F0BC);
    func_8013C938();
    D_800B9A11 = 0xC0;
    func_8012943C();
    func_80171A1C((u8 *)a0);
}
