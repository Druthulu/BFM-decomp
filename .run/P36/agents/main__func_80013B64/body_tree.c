void func_80013B64(s32 param_1, s32 param_2, s32 param_3)
{
    s16 ident[16];
    s16 rot[16];
    s32 sin_val;
    s32 cos_val;
    s32 v1;
    register s16 *v0p __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    s16 *m0p;

    func_80013F3C(ident);
    sin_val = func_8004787C((s16)param_1);
    cos_val = func_80047948((s16)param_1);

    v1 = -sin_val;
    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
    rot[0] = (s16)cos_val;
    rot[4] = (s16)cos_val;
    rot[8] = 0x1000;
    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
    v0p = rot;
    rot[3] = (s16)sin_val;
    m0p = ident;
    rot[1] = (s16)v1;
    rot[2] = 0;
    rot[5] = 0;
    rot[6] = 0;
    rot[7] = 0;

    __asm__ __volatile__ (
        "lw $12, 0(%1);"
        "lw $13, 4(%1);"
        "ctc2 $12, $0;"
        "ctc2 $13, $1;"
        "lw $12, 8(%1);"
        "lw $13, 12(%1);"
        "lw $14, 16(%1);"
        "ctc2 $12, $2;"
        "ctc2 $13, $3;"
        "ctc2 $14, $4;"
        "lhu $12, 0(%0);"
        "lhu $13, 6(%0);"
        "lhu $14, 12(%0);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%1);"
        "sh $13, 6(%1);"
        "sh $14, 12(%1);"
        "addiu $2, $sp, 50;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, $sp, 18;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2);"
        "addiu $2, $sp, 52;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, $sp, 20;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2)"
        :
        : "r"(v0p), "r"(m0p)
        : "$12", "$13", "$14", "$2"
    );

    func_8001282C(m0p);
    func_800484EC(m0p, param_2, param_3);
}
