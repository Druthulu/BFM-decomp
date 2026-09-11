void func_80013B64(s32 param_1, s32 param_2, s32 param_3)
{
    s16 matrix[16];
    s16 rot[16];
    s32 sin_val;
    s32 cos_val;
    u16 v1;
    s16 *rotp;
    s16 *matp;

    func_80013F3C(matrix);
    sin_val = func_8004787C((s16)param_1);
    cos_val = func_80047948((s16)param_1);

    v1 = -sin_val;
    rot[0] = cos_val;
    rot[4] = cos_val;
    rot[8] = 0x1000;
    rotp = rot;
    rot[3] = sin_val;
    matp = matrix;
    rot[1] = v1;
    rot[2] = 0;
    rot[5] = 0;
    rot[6] = 0;
    rot[7] = 0;

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
    func_800484EC(matp, param_2, param_3);
}
