/* func_80171B10 — shared body (overlay slot 0x80128158, h_exact a47cc82d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014C568(s16 *a0, s16 *a1);
void func_80171B10(void *a0) {
    s32 ret = ((s32 (*)())func_8014C568)(a0);
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = ret;
}
