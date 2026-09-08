/* func_80172A8C — shared body (overlay slot 0x80128158, h_exact bc24eefd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80126B30;
extern s32 func_80171CC4(void *a0, void *a1);
extern void func_80171A1C(u8 *a0);
void func_80172A8C(void *a0) {
    if (func_80171CC4(a0, &D_80126B30)) {
        func_80171A1C((u8 *)a0);
    }
}
