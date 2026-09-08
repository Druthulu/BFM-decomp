/* func_80170A48 — shared body (overlay slot 0x80128158, h_exact 88494ff2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800D5DA8;
extern void *D_8011F738;
extern s32 D_80126B58;
extern void func_80170AD8(void *a0);
extern void func_80171904(s32 a0);
extern void func_80170B48(int a0);
void func_80170A48(void) {
    D_8011F738 = &D_800D5DA8;
    func_80171904((s32)func_80170AD8);
    func_80170B48((int)&D_80126B58);
}
