/* func_801391F0 — shared body (overlay slot 0x80128158, h_exact a09742db). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80139634(void *);
extern void func_80139DC8(void);
void func_801391F0(void *a0) {
    *(s16 *)((s32)a0 + 0x12) = 0;
    *(s16 *)((s32)a0 + 0x14) = 0;
    *(s16 *)((s32)a0 + 0x16) = 0;
    func_80139634(a0);
    func_80139DC8();
}
