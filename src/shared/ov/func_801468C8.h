/* func_801468C8 — shared body (overlay slot 0x80128158, h_exact ef82362d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_8011F750;
extern s32 D_8011F754;
u8 *func_801468C8(s32 arg0, u8 arg1) {
    u8 *var_a2;   /* $a2 — returned base ptr  */
    register u8 *var_v1 __asm__("$3");   /* $v1 — scan/store ptr     */  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1)
    s32 var_t0;
    s32 var_a3;
    var_t0 = 0;
    var_a2 = (u8 *)(s32)&D_8011F750;
    var_v1 = var_a2;
    var_a3 = 0;
    do {
        if (*var_v1 != 0) {
            var_a2 += 0x2C;
            var_v1 += 0x2C;
            var_t0 += 1;
            var_a3 += 0x2C;
        } else {
            *(s32 *)((s32)&D_8011F754 + var_a3) = arg0;
            *var_v1 = arg1;
            return var_a2;
        }
    } while (var_t0 < 2);
    return (u8 *)0;
}
