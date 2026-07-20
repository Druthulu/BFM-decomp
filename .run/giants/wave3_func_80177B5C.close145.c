extern unsigned char D_8018A300[];

unsigned int *func_80177B5C(unsigned int *param_1, unsigned int param_2,
                            unsigned short param_3, int param_4, unsigned short param_5)
{
    unsigned char bVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned int *puVar6;
    short iVar7;
    unsigned int uVar8;
    unsigned int uVar9;

    uVar8 = param_4 + 0xe;
    uVar9 = 0x1000000;
    iVar7 = 0;
    bVar1 = D_8018A300[(short)param_3];
    param_1[0] = (unsigned int)(param_1 - 5) & 0xffffff | 0x3000000;
    param_1[1] = 0x74808080;
    uVar3 = ((short)param_5 + 1) << 0x10;
    uVar2 = ((unsigned int)bVar1 << 6 | 0x4016) << 0x10;
    param_1[2] = uVar3 | (param_4 - 3U & 0xffff);
    param_1[3] = uVar2 | 0x1800;
    param_1 += 5;
    param_1[0] = (unsigned int)(param_1 - 5) & 0xffffff | 0x3000000;
    param_1[1] = 0x74808080;
    param_1[2] = uVar3 | (param_4 + 5U & 0xffff);
    param_1[3] = uVar2 | 0x1808;
    param_1 += 5;

    puVar6 = param_1;
    do {
        uVar3 = (param_2 << 0x10) >> 0x1c;
        if (((uVar3 != 0) || (iVar7 == 2)) || (iVar7 == 0xff)) {
            uVar9 = 0;
        }
        puVar6[0] = (unsigned int)(puVar6 - 5) & 0xffffff | 0x3000000;
        puVar6[2] = (int)(short)param_5 << 0x10 | (uVar8 & 0xffff) | uVar9;
        puVar6[1] = 0x74808080;
        puVar6[3] = uVar2 | (uVar3 * 8 + 8) | 0x4000;
        puVar6 = puVar6 + 5;
        uVar8 = uVar8 + 8;
        iVar7 = iVar7 + 1;
        param_2 = param_2 << 4;
    } while (iVar7 < 3);

    puVar6[0] = (unsigned int)(puVar6 - 5) & 0xffffff | 0x3000000;
    uVar2 = ((unsigned int)bVar1 << 6 | 0x4016) << 0x10;
    uVar3 = (int)((unsigned int)param_3 << 0x10) >> 0xc;
    puVar6[2] = (unsigned int)param_5 << 0x10 | (param_4 + 0x2aU & 0xffff);
    puVar6[1] = 0x74808080;
    puVar6[3] = uVar2 | uVar3 | 0x1000;
    puVar6 += 5;
    puVar6[0] = (unsigned int)(puVar6 - 5) & 0xffffff | 0x3000000;
    puVar6[1] = 0x74808080;
    puVar6[2] = (unsigned int)param_5 << 0x10 | (param_4 + 0x32U & 0xffff);
    puVar6[3] = uVar2 | uVar3 | 0x1008;
    return puVar6 + 5;
}
