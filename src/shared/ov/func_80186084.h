/* func_80186084 — shared body (overlay slot 0x80128158, h_exact a92965d5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_801B8A3C[])(void);
void func_80186084(void *a0) {
    D_801B8A3C[*(u16 *)((s32)a0 + 0x2)]();
}
