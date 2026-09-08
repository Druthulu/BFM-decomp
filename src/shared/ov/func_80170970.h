/* func_80170970 — shared body (overlay slot 0x80128158, h_exact 2d6dafd3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800D59EC[];
extern void *D_8011F738;
extern s32 D_80126B58;
extern void func_80170AD8(void *a0);
extern void func_80171904(s32 a0);
extern void func_80170B48(int a0);
void func_80170970(void) {
    D_8011F738 = D_800D59EC;
    func_80171904((s32)func_80170AD8);
    func_80170B48((int)&D_80126B58);
}
