/* func_8016C74C — shared body (overlay slot 0x80128158, h_exact b41b10af). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 VectorNormalSS(void *a0, void *a1);
void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    s32 r; s32 lim; s32 sh2;
    sh2 = (s16)a2;
    __asm__ __volatile__("" : "=r"(sh2) : "0"(sh2));
    __asm__ __volatile__("" : : "r"(a3));
    *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) + (*(s16 *)(a1 + 0x0) << sh2);
    *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) + (*(s16 *)(a1 + 0x2) << sh2);
    *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) + (*(s16 *)(a1 + 0x4) << sh2);
    *(s16 *)(a1 + 0x0) = *(u16 *)(a0 + 0x12);
    *(s16 *)(a1 + 0x2) = *(u16 *)(a0 + 0x16);
    *(s16 *)(a1 + 0x4) = *(u16 *)(a0 + 0x1a);
    lim = *(volatile s32 *)&a4;
    __asm__ __volatile__("" ::: "memory");
    r = ((s32 (*)(void *))VectorNormalSS)((void *)a1);
    if (lim < r) {
        *(s32 *)(a0 + 0x10) = *(s16 *)(a1 + 0x0) << (s16)a3;
        *(s32 *)(a0 + 0x14) = *(s16 *)(a1 + 0x2) << (s16)a3;
        *(s32 *)(a0 + 0x18) = *(s16 *)(a1 + 0x4) << (s16)a3;
    }
}
