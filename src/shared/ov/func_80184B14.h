/* func_80184B14 — shared body (overlay slot 0x80128158, h_exact 6a947e56). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801819F4(void);
extern void func_801831F8(void);
extern s32 D_801E873C;
extern s32 D_801E874C;
void func_80184B14(s32 a0) {
    s32 ptr;
    s32 v1;
    ptr = *(s32 *)(a0 + 0x20);
    *(u16 *)(ptr + 0x12) = *(u16 *)(ptr + 0x12) + 0x20;
    *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x8) + 0xFFFA0000;
    if (*(s16 *)(a0 + 0xA) < -0x4F0) {
        *(s32 *)(a0 + 0x18) = 0xFFF24000;
        func_801819F4();
        func_801831F8();
        v1 = 0xFFF46667;
        *(s32 *)(a0 + 0x18) = v1;
        __asm__("");
        v1 = *(u16 *)(a0 + 0x2);
        *(s16 *)(a0 + 0xDC) = 0x10;
        D_801E874C = 0x20;
        *(s32 *)(a0 + 0x14) = 0xFFF80000;
        *(s16 *)(a0 + 0xDE) = 0;
        D_801E873C = 0;
        *(s32 *)(a0 + 0x44) = 0;
        *(s32 *)(a0 + 0x48) = 0x8000;
        *(s32 *)(a0 + 0x4C) = 0;
        v1 = v1 + 1;
        *(u16 *)(a0 + 0x2) = v1;
    }
}
