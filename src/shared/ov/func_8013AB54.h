/* func_8013AB54 — shared body (overlay slot 0x80128158, h_exact ff32a6ba). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013AD38(void *a0, s32 a1, void *a2, void *a3);
extern void func_8013B274(s32 a0, s32 a1, void *a2);
extern void func_8013AF20();
extern s32 D_800A5E60;
s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3) {
    u8 buf[0xE4];          /* spans 0x10 .. 0xF4 */
    s32 neg;
    s32 a, b;
    s32 t4, t6;
    t4 = *(s16 *)(a2 + 4) * 12;
    *(s16 *)(buf + 0xE0) = t4 + 0x10;   /* sp+0xF0 */
    neg = a3 & 0x8000;
    t6 = *(s16 *)(a2 + 6) * 12 + (*(s16 *)(a2 + 6) - 1) * 2;
    *(s16 *)(buf + 0xE2) = t6 + 8;
    if (neg == 0) {
        *(s16 *)(buf + 0xE0) = t4 + 0x38;
        *(s16 *)(buf + 0xE2) = t6 + 0x10;
    }
    a = ((s32)*(s16 *)(buf + 0xE0) << 12) / 154;
    b = ((s32)*(s16 *)(buf + 0xE2) << 12) / 42;
    *(s16 *)(buf + 0xE0) = a;
    *(s16 *)(buf + 0xE2) = b;
    if (neg != 0) {
        *(s16 *)(buf + 0xE0) = -a;
    }
    *(s16 *)(buf + 0xC8) = b;          /* 0xD8 */
    *(s16 *)(buf + 0xC2) = 0;          /* 0xD2 */
    *(s16 *)(buf + 0xC4) = 0;          /* 0xD4 */
    *(s16 *)(buf + 0xC6) = 0;          /* 0xD6 */
    *(s16 *)(buf + 0xCA) = 0;          /* 0xDA */
    *(s16 *)(buf + 0xCC) = 0;          /* 0xDC */
    *(s16 *)(buf + 0xCE) = 0;          /* 0xDE */
    *(s16 *)(buf + 0xD0) = 0x1000;     /* 0xE0 */
    *(s16 *)(buf + 0xC0) = *(u16 *)(buf + 0xE0);   /* 0xD0 */
    *(s32 *)(buf + 0xD4) = *(s16 *)(a2 + 0);       /* 0xE4 */
    *(s32 *)(buf + 0xD8) = *(s16 *)(a2 + 2);       /* 0xE8 */
    *(s32 *)(buf + 0xDC) = 0;                       /* 0xEC */
    {
        s32 *p = (s32 *)(buf + 0xC0);
        __asm__ __volatile__(  // !FAKE: gte direct — clobbers beyond Sony's macro (a scheduling steer; P36 T5 t5_remark3)
            "lw $12, 0(%0)\n"
            "lw $13, 4(%0)\n"
            "ctc2 $12, $0\n"
            "ctc2 $13, $1\n"
            "lw $12, 8(%0)\n"
            "lw $13, 12(%0)\n"
            "lw $14, 16(%0)\n"
            "ctc2 $12, $2\n"
            "ctc2 $13, $3\n"
            "ctc2 $14, $4\n"
            "lw $12, 20(%0)\n"
            "lw $13, 24(%0)\n"
            "ctc2 $12, $5\n"
            "lw $14, 28(%0)\n"
            "ctc2 $13, $6\n"
            "ctc2 $14, $7\n"
            : : "r"(p) : "$12", "$13", "$14", "memory");
    }
    func_8013AD38(buf + 0xE0, 0, buf + 0x00, buf + 0x80);
    D_800A5E60 = a0;
    if (a3 != 0) {
        func_8013B274(a1, 0x80, buf + 0xE0);
    }
    func_8013AF20(a1, a2, buf + 0x00, buf + 0x80);
    return D_800A5E60;
}
