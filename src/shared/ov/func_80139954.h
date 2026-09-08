/* func_80139954 — shared body (overlay slot 0x80128158, h_exact 0972af43). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013A8B0(s32 *a0);
extern u16 D_80126A08;
extern s16 D_801269F4;
extern s32 D_801269F0;
extern s32 *D_80126A30;
void func_80139954(void) {
    u16 v = D_80126A08;
    D_801269F4 = 0;
    D_801269F0 = 0;
    if (v != 0) {
        if (D_80126A30 != 0) {
            func_8013A8B0(D_80126A30);
        }
    }
}
