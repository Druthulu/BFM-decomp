/* func_80158548 — shared body (overlay slot 0x80128158, h_exact cb20cb05). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80161208();
void func_80158548(s32 param_1) {
    *(u32 *)(param_1 + 0x44) = *(u32 *)(param_1 + 0x44) | 2;
    if (*(u16 *)(param_1 + 0xb8) & 0x8000) {
        ((void (*)(void))func_801599A4)();
        ((void (*)(s32))func_80159B3C)(param_1);
    } else {
        ((void (*)(s32))func_80161208)(param_1);
    }
}
