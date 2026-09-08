/* func_80172E94 — shared body (overlay slot 0x80128158, h_exact 31054b7a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800D5A34[];
extern s32 D_80126B58;
extern s16 D_80126B30;
extern void func_8017303C(void *);
extern s32 func_80174650(s32);
void func_80172E94(void) {
    func_8017303C((void *)D_800D5A34);
    D_80126B30 = 0;
    func_80174650((s32)&D_80126B58);
}
