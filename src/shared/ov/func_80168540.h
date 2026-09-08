/* func_80168540 — shared body (overlay slot 0x80128158, h_exact 2fc5326f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80166690();
extern void func_80146C3C();
void func_80168540(s32 a0) {
    s32 v0;
    if (((*(u32 *)(*(s32 *)(a0 + 0x34) + 0x44) & 2) == 0) ||
        (v0 = *(s32 *)(a0 + 0x1c) - 1, *(s32 *)(a0 + 0x1c) = v0, v0 == 0)) {
        *(s16 *)(a0 + 2) = *(s16 *)(a0 + 2) + 1;
        func_80166994(a0, 2, 2, 0);
    } else {
        func_80166994(a0, 1, 2, (s32)*(s16 *)(a0 + 0x30));
    }
    if ((short)func_80166690(2, 1) == 0) {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}
