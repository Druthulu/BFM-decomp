void func_80039DEC(a0, a1, a2)
    void *a0;
    s16 a1;
    s16 a2;
{
    u8 cnt;
    s32 tmp;

    switch (a2) {
    case 0x14: {
        u8 *p = (u8 *)a0 + a1 * 26;
        p[0x1F] = a2;
        p[0x22] = 0x18;
        p[0x21] |= 3;
        break;
    }
    case 0x1E:
        if (*(u8 *)((u8 *)a0 + 0x1F6) == 0) {
            *(u8 *)((u8 *)a0 + 0x1F9) = 1;
            return;
        }
        cnt = *(u8 *)((u8 *)a0 + 0x1F5);
        if ((u8)cnt != 0x7F) {
            *(u8 *)((u8 *)a0 + 0x1F5) = cnt + 0xFF;
            if ((u8)cnt == 0) {
                return;
            }
        }
        tmp = *(s32 *)((u8 *)a0 + 0xC);
        *(u8 *)((u8 *)a0 + 0x1F7) = a1 | 0xB0;
        *(s32 *)a0 = tmp;
        break;
    case 0x28: {
        u8 *p = (u8 *)a0 + a1 * 26;
        p[0x1F] = a2;
        p[0x22] = 0x1A;
        p[0x21] |= 3;
        break;
    }
    default: {
        u8 *p = (u8 *)a0 + a1 * 26;
        p[0x1F] = a2;
        p[0x21] |= 1;
        break;
    }
    }
}
