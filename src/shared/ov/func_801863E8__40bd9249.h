/* func_801863E8 — shared body (overlay slot 0x80128158, h_exact 40bd9249). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_8018F2FC[])(void);
void func_801863E8(void *a0) {
    D_8018F2FC[*(u16 *)((s32)a0 + 0x2)]();
}
