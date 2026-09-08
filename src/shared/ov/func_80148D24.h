/* func_80148D24 — shared body (overlay slot 0x80128158, h_exact 62313960). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80148D24(void *a0, int a1) {
    int p = *(int *)((char *)a0 + 0x20);
    *(short *)(p + 0x12) = (a1 - 0x800) & 0xFFF;
    return 1;
}
