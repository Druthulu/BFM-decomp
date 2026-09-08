/* func_8013361C — shared body (overlay slot 0x80128158, h_exact f523834f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8013361C(s16 *a0, s16 *a1, s16 *a2, s16 *a3) {
    if ((*(s16 *)((s32)a0 + 4) + *(s16 *)((s32)a2 + 0) > *(s16 *)((s32)a1 + 6) + *(s16 *)((s32)a3 + 0)) ||
        (*(s16 *)((s32)a0 + 6) + *(s16 *)((s32)a2 + 0) < *(s16 *)((s32)a1 + 4) + *(s16 *)((s32)a3 + 0)) ||
        (*(s16 *)((s32)a0 + 0xC) + *(s16 *)((s32)a2 + 4) > *(s16 *)((s32)a1 + 0xE) + *(s16 *)((s32)a3 + 4)) ||
        (*(s16 *)((s32)a0 + 0xE) + *(s16 *)((s32)a2 + 4) < *(s16 *)((s32)a1 + 0xC) + *(s16 *)((s32)a3 + 4)) ||
        (*(s16 *)((s32)a0 + 8) + *(s16 *)((s32)a2 + 2) > *(s16 *)((s32)a1 + 0xA) + *(s16 *)((s32)a3 + 2)) ||
        (*(s16 *)((s32)a0 + 0xA) + *(s16 *)((s32)a2 + 2) < *(s16 *)((s32)a1 + 8) + *(s16 *)((s32)a3 + 2))) {
        return 0;
    }
    return 1;
}
