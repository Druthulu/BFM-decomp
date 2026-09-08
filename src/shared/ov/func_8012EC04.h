/* func_8012EC04 — shared body (overlay slot 0x80128158, h_exact 32bb75a9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80049CAC(s32 a0, s32 a1);
void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3)
{
    struct { s16 h[8]; } buf;
    s32 iVar4;
    s32 M;
    s32 c;
    register u32 v __asm__("$17");   /* $s1 */
    iVar4 = *(s32 *)(param_1 + 0x20);
    v = *(u32 *)(iVar4 + 0x20);
    if (v == 0) {
        *(Blk16 *)(param_3)             = *(Blk16 *)(iVar4 + 0x34);
        *(Blk16 *)((s32)param_3 + 0x10) = *(Blk16 *)(iVar4 + 0x44);
    } else if ((v & 0x1000000) != 0) {
        register s32 p __asm__("$16");
        s32 w;
        p = (s32)(v & 0xfeffffff);
        p = p + param_2 * 8;
        buf.h[0] = *(s16 *)(p + 6);
        w = *(s32 *)p;
        buf.h[1] = (s16)(*(u8 *)(p + 1) | ((w & 0xf) << 8));
        buf.h[2] = (s16)(((w >> 0x10) & 0xff) | ((w & 0xf0) << 4));
        func_80049CAC((s32)&buf, (s32)param_3);
        param_3[5] = *(s8 *)(p + 3);
        param_3[6] = *(s8 *)(p + 4);
        param_3[7] = *(s8 *)(p + 5);
    } else {
        s32 q;
        v = v + param_2 * 0xc;
        q = (s32)v;
        buf.h[0] = *(s16 *)(q + 6);
        buf.h[1] = *(s16 *)(q + 8);
        buf.h[2] = *(s16 *)(q + 0xa);
        func_80049CAC((s32)&buf, (s32)param_3);
        param_3[5] = *(s16 *)(q + 0);
        param_3[6] = *(s16 *)(q + 2);
        param_3[7] = *(s16 *)(q + 4);
    }
    /* --- GTE tail --- */
    /* gte_SetRotMatrix(M) */
    M = *(s32 *)(param_1 + 0x20) + 0x34;
    __asm__ __volatile__(
        "lw $12, 0(%0)\n" "lw $13, 4(%0)\n"
        "ctc2 $12, $0\n" "ctc2 $13, $1\n"
        "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n"
        "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n"
        : : "r"(M) : "$12", "$13", "$14", "memory");
    /* column 0: param_3 in place */
    __asm__ __volatile__(
        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
        : : "r"((s32)param_3) : "$12", "$13", "$14", "memory");
    __asm__ __volatile__(
        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
        : : "r"((s32)param_3) : "$12", "$13", "$14", "memory");
    /* column 1: param_3 + 2 */
    c = (s32)param_3 + 2;
    __asm__ __volatile__(
        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
        : : "r"(c) : "$12", "$13", "$14", "memory");
    __asm__ __volatile__(
        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
        : : "r"(c) : "$12", "$13", "$14", "memory");
    /* column 2: param_3 + 4 */
    c = (s32)param_3 + 4;
    __asm__ __volatile__(
        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
        : : "r"(c) : "$12", "$13", "$14", "memory");
    __asm__ __volatile__(
        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
        : : "r"(c) : "$12", "$13", "$14", "memory");
    /* gte_SetTransMatrix(M) — M reloaded */
    M = *(s32 *)(param_1 + 0x20) + 0x34;
    __asm__ __volatile__(
        "lw $12, 20(%0)\n" "lw $13, 24(%0)\n"
        "ctc2 $12, $5\n" "lw $14, 28(%0)\n"
        "ctc2 $13, $6\n" "ctc2 $14, $7\n"
        : : "r"(M) : "$12", "$13", "$14", "memory");
    /* gte_ldlv0(param_3->t) ; gte_rt() ; gte_stlvnl(param_3->t) */
    c = (s32)param_3 + 0x14;
    __asm__ __volatile__(
        "lhu $13, 4(%0)\n" "lhu $12, 0(%0)\n"
        "sll $13, $13, 16\n" "or $12, $12, $13\n"
        "mtc2 $12, $0\n" "lwc2 $1, 8(%0)\n"
        "nop\n" "nop\n" "mvmva 1, 0, 0, 0, 0\n"
        : : "r"(c) : "$12", "$13", "memory");
    __asm__ __volatile__(
        "swc2 $25, 0(%0)\n" "swc2 $26, 4(%0)\n" "swc2 $27, 8(%0)\n"
        : : "r"(c) : "memory");
}
