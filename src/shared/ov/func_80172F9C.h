/* func_80172F9C — shared body (overlay slot 0x80128158, h_exact aff7fdc6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8017303C(void *);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80174650(s32);
extern u8 D_800D46E4[];
extern s32 D_80126B58;
extern s16 D_80126B30;
void func_80172F9C(void) {
    func_8017303C(D_800D46E4);
    func_80154A74((s32)&D_80126B58, 0x11);
    D_80126B30 = 0;
    func_80174650((s32)&D_80126B58);
}
