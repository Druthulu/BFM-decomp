/* func_8014CBF8 — shared body (overlay slot 0x80128158, h_exact 0820809e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8014CBF8(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x174);
    if (v1 != 0) {
        if (*(u16 *)(v1 + 0) != 0) {
            *(s32 *)((s32)a0 + 0x174) = 0;
            *(s8 *)(v1 + 0x74) = 0;
        }
    }
}
