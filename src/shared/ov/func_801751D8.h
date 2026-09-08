/* func_801751D8 — shared body (overlay slot 0x80128158, h_exact ba880ced). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80161104(void);
extern s32 func_80175218(void *a0);
extern void func_80146CA0(void *a0);
void func_801751D8(void *a0) {
    void *s = a0;
    if (func_80161104()) {
        func_80175218(s);
        func_80146CA0(s);
    }
}
