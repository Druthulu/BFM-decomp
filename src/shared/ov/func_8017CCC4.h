/* func_8017CCC4 — shared body (overlay slot 0x80128158, h_exact bd4481ec). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017CCC4(void *a0) {
    s32 *a1 = *(s32 **)((s32)a0 + 0x20);
    if (*(s32 *)((s32)a0 + 0x1C) & 1) {
        *(s32 *)(a1 + 1) |= 0x80000000;
    } else {
        *(s32 *)(a1 + 1) &= 0x7FFFFFFF;
    }
    *(s16 *)((s32)a0 + 0x24) = 3;
    *(s32 *)((s32)a0 + 0x1C) += 1;
}
