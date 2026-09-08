/* func_801848E4 — shared body (overlay slot 0x80128158, h_exact dac153f2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_8018FE80[])(void);
void func_801848E4(void *a0) {
    D_8018FE80[*(u16 *)((s32)a0 + 0x2)]();
}
