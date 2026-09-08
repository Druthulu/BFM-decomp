/* func_80168328 — shared body (overlay slot 0x80128158, h_exact a26f1e54). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80166690();
extern void func_80146C3C();
void func_80168328(s32 arg0) {
    s32 a1;
    s32 a2;
    s32 a3;
    s32 v;
    if (((*(s32 *)(*(s32 *)(arg0 + 0x34) + 0x44) & 2) == 0) ||
        (v = *(s32 *)(arg0 + 0x1c) - 1, *(s32 *)(arg0 + 0x1c) = v, v == 0)) {
        a1 = 2;
        a3 = 0;
        a2 = *(s16 *)(arg0 + 0x2c);
        *(s16 *)(arg0 + 2) = *(s16 *)(arg0 + 2) + 1;
        func_80166994(arg0, a1, a2, a3);
    } else {
        a2 = *(s16 *)(arg0 + 0x2c);
        a3 = *(s16 *)(arg0 + 0x30);
        a1 = 1;
        func_80166994(arg0, a1, a2, a3);
    }
    if ((s16)func_80166690(*(s16 *)(arg0 + 0x2c), *(s16 *)(arg0 + 0x28)) == 0) {
        ((void (*)(s32))func_80146C3C)(arg0);
    }
}
