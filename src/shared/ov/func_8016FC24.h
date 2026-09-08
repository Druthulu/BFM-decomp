/* func_8016FC24 — shared body (overlay slot 0x80128158, h_exact 4847286e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *D_8011F738;
extern s32 func_80171B4C(s32 a0, s32 a1);
extern s32 func_80171990(u8 *a0);
void func_8016FC24(s32 a0) {
    if (func_80171B4C(a0, *(u8 *)&D_8011F738)) {
        func_80171990((u8 *)a0);
    }
}
