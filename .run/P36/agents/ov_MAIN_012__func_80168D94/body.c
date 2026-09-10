void func_80168D94(int a0) {
    int s1 = a0;
    short v10[4];   /* sp+0x10 SVECTOR */
    short v18[16];  /* sp+0x18 MATRIX_L48 */
    short v38[16];  /* sp+0x38 MATRIX_L48 */
    v10[0] = *(unsigned short *)(s1 + 0x12);
    v10[1] = *(unsigned short *)(s1 + 0x16);
    v10[2] = *(unsigned short *)(s1 + 0x1A);
    RotMatrixYXZ(v10, v38);
    if (*(int *)(s1 + 0x2C) == 0) {
        int r = rand();
        v10[0] = (r & 0x7F) << 3;
        v10[1] = (int)((unsigned int)(r & 0x7F00) >> 5) + 0xC00;
    } else {
        int r = rand();
        v10[0] = ((r & 0x7F) << 3) + 0xE00;
        v10[1] = (int)((unsigned int)(r & 0x7F00) >> 5) + 0xE00;
    }
    v10[2] = 0;
    RotMatrixYXZ(v10, v18);
    func_80048EAC(v38, v18);
    v10[0] = 0;
    v10[1] = 0;
    v10[2] = 0x24;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(v18, v10, v10);
    {
        s32 a = *(unsigned short *)(s1 + 0x6);
        s32 b = *(unsigned short *)(s1 + 0xA);
        *(unsigned short *)(s1 + 0x12) = v10[0];
        *(unsigned short *)(s1 + 0x16) = v10[1];
        {
            s32 z = (unsigned short)v10[2];
            s32 t = *(unsigned short *)(s1 + 0x2);
            *(unsigned short *)(s1 + 0x10) = a;
            *(unsigned short *)(s1 + 0x14) = b;
            *(unsigned short *)(s1 + 0x18) = *(unsigned short *)(s1 + 0xE);
            *(int *)(s1 + 0x1C) = 0;
            *(unsigned short *)(s1 + 0x2) = t + 1;
            *(unsigned short *)(s1 + 0x1A) = z;
        }
    }
}
