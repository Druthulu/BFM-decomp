/* func_80165374 — shared body (overlay slot 0x80128158, h_exact 366f1d42). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801653F4(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80165580(s32 a0);
void func_80165374(s32 a0) {
    func_801653F4(a0);
    func_80147078((s32 *)a0, 0x17);
    *(u8 *)(a0 + 0x197) = 1;
    func_80165580(a0);
}
