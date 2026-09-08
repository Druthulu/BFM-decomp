/* func_801477C8 — shared body (overlay slot 0x80128158, h_exact 89d8e94a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801477C8(void *a0, s32 a1) {
    void *v1 = *(void **)((s32)a0 + 0x20);
    *(s16 *)((s32)v1 + 0x14) = (*(u16 *)((s32)v1 + 0x14) + a1) & 0xFFF;
}
