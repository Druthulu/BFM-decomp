/* func_80182D00 — shared body (overlay slot 0x80128158, h_exact ed044b29). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_8018ED5C[])(void);
void func_80182D00(void *a0) {
    D_8018ED5C[*(u8 *)((s32)a0 + 0x214)]();
}
