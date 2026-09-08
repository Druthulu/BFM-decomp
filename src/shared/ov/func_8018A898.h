/* func_8018A898 — shared body (overlay slot 0x80128158, h_exact 4a8440b5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_801E051C[])(void);
void func_8018A898(void *a0) {
    D_801E051C[*(u16 *)((s32)a0 + 0x2)]();
}
