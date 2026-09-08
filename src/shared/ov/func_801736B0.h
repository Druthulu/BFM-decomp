/* func_801736B0 — shared body (overlay slot 0x80128158, h_exact 88b8795a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014C118(void *a0, s32 a1, s32 a2);
extern void func_80174684(void *);
extern s32 func_801736FC();
extern s32 D_80126B58;
extern s32 D_80127508;
void func_801736B0(s32 a0, s32 a1) {
    D_80127508 = func_8014C118(&D_80126B58, a0, (s16)a1);
    func_80174684(func_801736FC);
}
