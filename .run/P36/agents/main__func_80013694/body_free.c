void func_80013694(s16 angle, void *a1, void *a2)
{
    s16 matrix[16];
    s16 vec0[9];
    s16 pad[4];
    s32 sin_val;
    s32 cos_val;
    s32 v1;
    s16 *v0p;
    s16 *m0p;

    func_80013F3C(matrix);
    sin_val = func_8004787C((s32)angle);
    cos_val = func_80047948((s32)angle);

    v1 = 0x1000;
    vec0[0] = (s16)v1;
    v1 = -sin_val;
    vec0[4] = (s16)cos_val;
    vec0[8] = (s16)cos_val;
    v0p = vec0;
    vec0[7] = (s16)sin_val;
    m0p = matrix;
    vec0[1] = 0;
    vec0[2] = 0;
    vec0[3] = 0;
    vec0[5] = (s16)v1;
    vec0[6] = 0;

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

    func_8001282C(matrix);
    ApplyMatrixSV(matrix, a1, a2);
}
