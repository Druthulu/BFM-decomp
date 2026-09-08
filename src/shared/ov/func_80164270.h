/* func_80164270 — shared body (overlay slot 0x80128158, h_exact c3cb69d0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80162D88(s32 *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
void func_80164270(s32 *a0) {
    s32 *s = a0;
    func_80162D88(s);
    func_80146E90(s, 0x20);
    func_80146CA0(s);
}
