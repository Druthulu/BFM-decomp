/* func_8013339C — shared body (overlay slot 0x80128158, h_exact f8dd95c2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013339C(short *param_1, short *param_2)
{
    short sVar4;
    short sVar5;
    short sVar6;
    sVar4 = 1;
    if (*param_2 != 0) {
        sVar4 = *param_2;
    }
    sVar5 = 1;
    if (param_2[1] != 0) {
        sVar5 = param_2[1];
    }
    sVar6 = 1;
    if (param_2[2] != 0) {
        sVar6 = param_2[2];
    }
    param_1[0] = (short)(((int)param_1[0] << 0xc) / (int)sVar4);
    param_1[3] = (short)(((int)param_1[3] << 0xc) / (int)sVar4);
    param_1[6] = (short)(((int)param_1[6] << 0xc) / (int)sVar4);
    param_1[1] = (short)(((int)param_1[1] << 0xc) / (int)sVar5);
    param_1[4] = (short)(((int)param_1[4] << 0xc) / (int)sVar5);
    param_1[7] = (short)(((int)param_1[7] << 0xc) / (int)sVar5);
    param_1[2] = (short)(((int)param_1[2] << 0xc) / (int)sVar6);
    param_1[5] = (short)(((int)param_1[5] << 0xc) / (int)sVar6);
    param_1[8] = (short)(((int)param_1[8] << 0xc) / (int)sVar6);
}
