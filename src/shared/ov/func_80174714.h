/* func_80174714 — shared body (overlay slot 0x80128158, h_exact b4f7b74a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_800CF8CC(void);
extern void func_80147060(u8 *a0);
extern s32 func_8016F0AC();
extern s32 D_80126B58;
void func_80174714(void) {
    if (func_800CF8CC() == 0) {
        func_80147060((u8 *)&D_80126B58);
        func_8016F0AC();
    }
}
