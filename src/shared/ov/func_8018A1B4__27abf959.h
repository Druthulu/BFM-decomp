/* func_8018A1B4 — shared body (overlay slot 0x80128158, h_exact 27abf959). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801E3980[];
extern u8 D_801E3760[];
void func_8018A1B4(void *a0) {
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            func_8012A828((s32)a0, D_801E3980);
        } else {
            func_8012A828((s32)a0, D_801E3760);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}
