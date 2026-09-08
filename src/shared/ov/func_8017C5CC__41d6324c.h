/* func_8017C5CC — shared body (overlay slot 0x80128158, h_exact 41d6324c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_80190CCC[])(void);
void func_8017C5CC(void *a0) {
    D_80190CCC[*(u16 *)((s32)a0 + 0x2)]();
}
