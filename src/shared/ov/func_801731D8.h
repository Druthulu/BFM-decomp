/* func_801731D8 — shared body (overlay slot 0x80128158, h_exact 558b0033). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800D5AA0[];
extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171A1C(u8 *a0);
extern void func_80173220(void *a0);
void func_801731D8(s32 *a0) {
    func_8014706C(a0);
    func_80154274(a0, (s32)D_800D5AA0);
    func_80171A1C((u8 *)a0);
    func_80173220(a0);
}
