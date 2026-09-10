void func_80168D94(int a0) {
    int s1 = a0;
    short v10[4];   /* sp+0x10 SVECTOR */
    short v18[16];  /* sp+0x18 MATRIX_L48 */
    short v38[16];  /* sp+0x38 MATRIX_L48 */
    int v1;
    register int v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus2)
    v10[0] = *(unsigned short *)(s1 + 0x12);
    v10[1] = *(unsigned short *)(s1 + 0x16);
    v10[2] = *(unsigned short *)(s1 + 0x1A);
    RotMatrixYXZ(v10, v38);
    if (*(int *)(s1 + 0x2C) == 0) {
        v0 = rand();
        v1 = (v0 & 0x7F) << 3;
        v0 = (int)((unsigned int)(v0 & 0x7F00) >> 5);
        __asm__("" : "=r"(v0) : "0"(v0));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus2)
        v0 += 0xC00;
    } else {
        v0 = rand();
        v1 = ((v0 & 0x7F) << 3) + 0xE00;
        v0 = (int)((unsigned int)(v0 & 0x7F00) >> 5) + 0xE00;
    }
    v10[0] = v1;
    v10[1] = v0;
    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus2)
    v10[2] = 0;
    RotMatrixYXZ(v10, v18);
    func_80048EAC(v38, v18);
    v10[0] = 0;
    v10[1] = 0;
    v10[2] = 0x24;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(v18, v10, v10);
    {
        register s32 a __asm__("$4") = *(unsigned short *)(s1 + 0x6);  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus2)
        s32 b = *(unsigned short *)(s1 + 0xA);
        register s32 c __asm__("$3") = *(unsigned short *)(s1 + 0xE);  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus2)
        *(unsigned short *)(s1 + 0x12) = v10[0];
        *(unsigned short *)(s1 + 0x16) = v10[1];
        {
            s32 z = (unsigned short)v10[2];
            s32 t = *(unsigned short *)(s1 + 0x2);
            *(unsigned short *)(s1 + 0x10) = a;
            *(unsigned short *)(s1 + 0x14) = b;
            *(unsigned short *)(s1 + 0x18) = c;
            *(int *)(s1 + 0x1C) = 0;
            *(unsigned short *)(s1 + 0x2) = t + 1;
            *(unsigned short *)(s1 + 0x1A) = z;
        }
    }
}
