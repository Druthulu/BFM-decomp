/* func_8018553C — shared body (overlay slot 0x80128158, h_exact 3d02f43e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_801903DC[])(void);
void func_8018553C(void *a0) {
    D_801903DC[*(u16 *)((s32)a0 + 0x2)]();
}
