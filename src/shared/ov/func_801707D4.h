/* func_801707D4 — shared body (overlay slot 0x80128158, h_exact 6c6b39b2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80174ED4(void);
extern void func_80171928(void *a0);
void func_801707D4(void *a0) {
    if ((s16)func_80174ED4() != 0) {
        func_80171928(a0);
    }
}
