/* func_8012E4C8 — shared body (overlay slot 0x80128158, h_exact c42e890e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8012E4C8(s32 a0) {
    s32 v1;
    s32 t;
    v1 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v1 + 0x1C) = 0x1000;
    *(s16 *)(v1 + 0x18) = 0x1000;
    *(s16 *)(a0 + 0x60) = 0;
    *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) | 1;
    t = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
    *(s16 *)(a0 + 0x5E) = 1;
    *(s16 *)(a0 + 0x62) = t + 0x800;
}
