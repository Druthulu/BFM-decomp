void func_8012E364(s32 arg0_)
{

    extern s16 D_80126CE0;
    extern s32 D_801ED9D8;
    extern s32 D_801ED9DC;
    s32 arg0;
    register s32 prev __asm__("$5");  // !FAKE: pin $5 — local-alloc qty_compare_1 (local-alloc.c:1598) ranks prev (2 refs) above e1 (3 refs) and gives it $a0; target $a1 (P36 S103 c51 minimum-lever)
    register u16 flags __asm__("$2");  // !FAKE: pin $2 — holds $2 across the D_801ED9D8 chain, so the $2 suggestion d's pin gives v (local-alloc.c:1822) fails in block_alloc's suggested-reg pass (:1472) (P36 S103 c51 minimum-lever)
    s32 a;
    s32 diff;
    s32 v;
    register s32 d __asm__("$2");  // !FAKE: pin $2 — combine_regs (local-alloc.c:1722) otherwise ties d into v, which dies at the abs: abssi2 dest==src arm, nop for move (P36 S103 c51 minimum-lever)
    s32 spd;
    s32 e1;
    s32 e2;

    arg0 = arg0_;
    *(s16 *)(arg0 + 0x5C) = 0;
    a = D_80126CE0;
    if (a == 0) {
        D_801ED9D8 = 0x1000;
        D_801ED9DC = 0x1000;
    }
    a = ((0x90 - a) << 12) / 0x90;
    *(s32 *)(arg0 + 0x1C) += 1;
    spd = 0x1000;

    diff = D_801ED9D8 - a;
    if (diff > 0) {
        D_801ED9D8 -= diff >> 2;
    } else if (diff < 0) {
        D_801ED9D8 += (-diff) / 4;
    }

    prev = D_801ED9DC;
    e1 = *(s32 *)(arg0 + 0x20);
    v = D_801ED9D8 - prev + spd;
    D_801ED9DC = spd;
    flags = *(u16 *)(e1 + 0x2C);
    D_801ED9D8 = v;
    *(u16 *)(e1 + 0x2C) = flags | 0x10;

    e2 = *(s32 *)(arg0 + 0x20);
    d = __builtin_abs(v);
    *(s16 *)(e2 + 0x1C) = d;
    *(s16 *)(e2 + 0x18) = d;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = 0x1000;
}
