void func_80013694(s16 angle, void *a1, void *a2)
{
    s16 matrix[16];
    s16 rot[16];
    s32 sin_val;
    s32 cos_val;
    s32 v;
    s16 *rotp;
    s16 *matp;

    func_80013F3C(matrix);
    sin_val = func_8004787C(angle);
    cos_val = func_80047948(angle);

    v = 0x1000;
    rot[0] = v;
    v = -sin_val;
    rot[4] = cos_val;
    rot[8] = cos_val;
    rotp = rot;
    rot[7] = sin_val;
    matp = matrix;
    rot[1] = 0;
    rot[2] = 0;
    rot[3] = 0;
    rot[5] = v;
    rot[6] = 0;

    gte_SetRotMatrix(matp);
    gte_ldclmv(rotp);
    gte_rtir();
    gte_stclmv(matp);
    gte_ldclmv(rotp + 1);
    gte_rtir();
    gte_stclmv(matp + 1);
    gte_ldclmv(rotp + 2);
    gte_rtir();
    gte_stclmv(matp + 2);

    func_8001282C(matp);
    ApplyMatrixSV(matp, a1, a2);
}
