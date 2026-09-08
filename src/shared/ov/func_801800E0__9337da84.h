/* func_801800E0 — shared body (overlay slot 0x80128158, h_exact 9337da84). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_801918E4[])(void);
void func_801800E0(void *a0) {
    D_801918E4[*(u16 *)((s32)a0 + 0x2)]();
}
