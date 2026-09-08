/* func_8018B614 — shared body (overlay slot 0x80128158, h_exact d4ff4631). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8018B5AC(void);
extern void func_8018B564(void *a0);
void func_8018B614(void *a0) {
    s32 s0;
    s0 = 1;
    *(s32 *)(*(s32 *)((char *)a0 + 0xCC) + 0xB0) = s0;
    if (func_8018B5AC() != s0) {
        return;
    }
    func_8018B564(a0);
}
