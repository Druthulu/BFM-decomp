/* func_8014350C — shared body (overlay slot 0x80128158, h_exact f81e8c37). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014358C();
extern void func_8012931C(struct vec *a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(u8 *a0);
void func_8014350C(s32 *a0) {
    if (*(u16 *)((u8 *)a0 + 2) == 0) {
        func_8014358C();
        return;
    }
    func_8012931C((struct vec *)a0);
    if (func_80128ED8((void *)a0[0x20 / 4], (void *)((u8 *)a0 + 0x24)) != 0) {
        func_801292C8((u8 *)a0);
        return;
    }
    *(u8 *)(a0[0x20 / 4] + 0x27) = *(u8 *)((u8 *)a0 + 0x28) - 0x70;
}
