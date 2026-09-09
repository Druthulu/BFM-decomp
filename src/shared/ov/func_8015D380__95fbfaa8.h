/* func_8015D380 — shared body (overlay slot 0x80128158, h_exact 95fbfaa8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015D380(s32 a0) {
    s16 out[4];
    s32 buf[8];
    s32 s1 = a0;
    s32 *s0 = buf;
    ((void (*)(void *))func_80013F3C)((void *)s0);
    ((void (*)(void *, s32))func_80012558)((void *)s0, *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12));
    ((void (*)(void *, s32))func_800126C4)((void *)s0, *(s16 *)(*(s32 *)(s1 + 0x20) + 0x10));
    ApplyMatrixSV((void *)s0, (void *)&D_80181B44, (void *)out);
    memcpy((void *)(s1 + 0x138), (void *)out, 8);
}
