/* func_8017F058 — shared body (overlay slot 0x80128158, h_exact c1e50dcd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_8019155C[])(void);
void func_8017F058(void *a0) {
    D_8019155C[*(u16 *)((s32)a0 + 0x2)]();
}
