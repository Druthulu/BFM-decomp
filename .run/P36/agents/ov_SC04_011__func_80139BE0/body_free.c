s32 func_80139BE0(int param_1)
{

    extern unsigned char D_801909F8[];
    int v;

    if ((*(unsigned int *)(param_1 + 8) & 0x2000) == 0) {
        int t = *(unsigned char *)(param_1 + 0x22) & 0x60;
        int h = *(unsigned short *)(param_1 + 0x18);
        unsigned int idx;

        idx = (unsigned char)t;
        if (h < 7) {
            if (h >= 2) {
                v = D_801909F8[idx >> 5];
            } else {
                v = D_801909F8[0];
            }
        } else {
            v = D_801909F8[0];
        }
        *(short *)(param_1 + 0x2e) = 3;
        *(short *)(param_1 + 0x2c) = v;
    }
    *(short *)(param_1 + 0x34) = *(short *)(param_1 + 0x2c) * 6;
    {
        int x = *(short *)(param_1 + 0x2e);
        *(short *)(param_1 + 0x36) = x * 12 + (x - 1) * 2;
    }
}
