/* func_8016FED0 — shared body (overlay slot 0x80128158, h_exact e00f3bf5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80172664(s32 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern void func_80171928(void *a0);
extern void *D_8011F738;
void func_8016FED0(s32 *a0) {
    if (func_80172664(a0) != 0) {
        *(u16 *)((u8 *)a0 + 0xAA) |= 0x40;
    }
    if (func_80171CC4(a0, &D_8011F738) != 0) {
        func_80171928(a0);
    }
}
