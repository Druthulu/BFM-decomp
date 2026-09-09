/* func_8013AA24 — shared body (overlay slot 0x80128158, h_exact 79bd864d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013AD38(void *a0, s32 a1, void *a2, void *a3);
extern void func_8013B204(s32 a0, s32 a1);
extern void func_8013AF20();
extern short D_800B9A02;
extern s32 D_800A651C;
void func_8013AA24(s32 a0, s32 a1) {
    s32 s2 = a0;
    s32 s0 = a1;
    u8 buf[0xE0];          /* spans 0x10 .. 0xF0 */
    s16 m00 = *(u16 *)(s0 + 8);
    s16 m11;
    *(s16 *)(buf + 0x02) = 0;                       /* 0x12 */
    *(s16 *)(buf + 0x04) = 0;                       /* 0x14 */
    *(s16 *)(buf + 0x06) = 0;                       /* 0x16 */
    *(s16 *)(buf + 0x00) = m00;                     /* 0x10 */
    m11 = *(u16 *)(s0 + 0xA);
    *(s16 *)(buf + 0x0A) = 0;                       /* 0x1A */
    *(s16 *)(buf + 0x0C) = 0;                       /* 0x1C */
    *(s16 *)(buf + 0x0E) = 0;                       /* 0x1E */
    *(s16 *)(buf + 0x10) = 0x1000;                  /* 0x20 */
    *(s16 *)(buf + 0x08) = m11;                     /* 0x18 */
    *(s32 *)(buf + 0x14) = *(s16 *)(s2 + 0x24);    /* 0x24 */
    *(s32 *)(buf + 0x18) = *(s16 *)(s2 + 0x26);    /* 0x28 */
    *(s32 *)(buf + 0x1C) = 0;                       /* 0x2C */
    {
        s32 *p = (s32 *)(buf + 0x00);
        __asm__ __volatile__(
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
    func_8013AD38((void *)(s0 + 8), *(s16 *)(s0 + 0xC), buf + 0x20, buf + 0xA0);
    func_8013B204(s2, s0);
    func_8013AF20(*(s32 *)((u8 *)&D_800A651C + (u16)D_800B9A02 * 20) +
                      *(u16 *)(s2 + 0x1A) * 4,
                  s2 + 0x24, buf + 0x20, buf + 0xA0);
}
