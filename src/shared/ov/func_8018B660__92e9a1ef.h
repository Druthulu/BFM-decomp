/* func_8018B660 — shared body (overlay slot 0x80128158, h_exact 92e9a1ef). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8018B660(s32 a0) {
    s32 *v1;
    v1 = *(s32 **)((s32)a0 + 0xCC);
    *(s32 *)((s32)v1 + 0xB0) = 2;
    if (func_8018B5AC() == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
    }
}
