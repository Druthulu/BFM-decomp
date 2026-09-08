/* func_8018C038 — shared body (overlay slot 0x80128158, h_exact a0f48779). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern void func_80184CB8(s32 *a0, s32 a1);
extern short D_801E05C4;
void func_8018C038(s32 *arg0) {
    register s32 *s0 asm("$16") = arg0;
    s32 v0, v1;
    *(s32 *)((u8 *)(*(s32 **)((u8 *)s0 + 0xCC)) + 0xB0) = 2;
    v0 = func_80184BAC(6, 0x12);
    if (v0 != 0) {
        v1 = 1;
    } else {
        v0 = func_80184BAC(0x12, 0x15);
        v1 = (v0 != 0) ? 2 : 0;
    }
    if (v1 != 2) {
        *(s16 *)((u8 *)s0 + 2) = 1;
        func_80184CB8(s0, (s32)&D_801E05C4);
    }
}
