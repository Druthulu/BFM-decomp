void func_80185994(s32 a0)
{
    s32 t;
    u32 *p;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        p = *(u32 **)(a0 + 0x20);
        p[1] ^= 0x80000000;
        func_8012B370(a0);

        if ((*(s32 *)(a0 + 0x1C) & 0x3) != 0) {
            s32 obj = func_8012C588(0x281, a0);
            if (obj != 0) {
                *(s32 *)(obj + 0x1C) = 2;
                *(s16 *)(obj + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(obj + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(obj + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    func_8012C218((void *)a0);
}
