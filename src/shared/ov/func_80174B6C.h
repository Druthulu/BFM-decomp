/* func_80174B6C — shared body (overlay slot 0x80128158, h_exact d9bde682). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80174BBC(void *a0);
extern void guess_SetMainCameraHandler(s32 a, s32 b);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern u8 guess_g_MainCamera[]; // Names ledger: config/names.tsv guess_g_MainCamera
void func_80174B6C(void) {
    func_80174BBC(guess_g_MainCamera);
    guess_SetMainCameraHandler((s32)func_80174BF4, 0);
    func_8012A0E0();
    func_80174BF4(guess_g_MainCamera);
}
