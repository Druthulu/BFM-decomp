/* func_80153490 — shared body (overlay slot 0x80128158, h_exact 376c5f93). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_80146CA0(void *a0);
void func_80153490(s32 a0) {
    func_80149020((s32 *)a0);
    if (!func_801536DC(a0)) {
        *(s8 *)(a0 + 0xDE) = 1;
        *(s8 *)(a0 + 0xDF) = 0;
        func_80146CA0((void *)a0);
    }
}
