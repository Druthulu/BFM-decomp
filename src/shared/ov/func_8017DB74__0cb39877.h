/* func_8017DB74 — shared body (overlay slot 0x80128158, h_exact 0cb39877). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80171CC4(void *a0, void *a1);
extern void func_80171A1C(u8 *a0);
extern s16 D_80126B36;
void func_8017DB74(u8 *a0) {
    s16 *p = &D_80126B36;
    if (*p != 0) {
        if (func_80171CC4(a0, p - 3) == 0) {
            return;
        }
    }
    func_80171A1C(a0);
}
