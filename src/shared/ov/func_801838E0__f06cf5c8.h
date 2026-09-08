/* func_801838E0 — shared body (overlay slot 0x80128158, h_exact f06cf5c8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_8018E858[])(void);
void func_801838E0(void *a0) {
    D_8018E858[*(u16 *)((s32)a0 + 0x2)]();
}
