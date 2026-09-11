void func_80181744(s32 a0) {
    s32 local[4]; 
    s32 v0;
    s32 sum;

    v0 = func_80180AF0(a0, 0xFFFB0000, local);
    if (v0 == 1) {
        func_8012ADE4((u8 *)a0);
        *(s32 *)(a0 + 0x1C) = 8;
        func_8012A8B0((u8 *)a0, (s32)&D_80199644);
        func_8012B23C(a0);
        func_8012AD44((s32 *)a0, 1);
    } else {
        v0 = *(s16 *)(a0 + 0x102);
        if (v0 != 0) {
            
            s32 tmp;
            tmp = v0;
            v0 = tmp - 1;
        } else {
            s16 cnt;

            if (*(s16 *)(a0 + 0xAA) == 0) {
                func_80180FF8((void *)a0);
            }
            cnt = *(u16 *)(a0 + 0x104) - 1;
            *(s16 *)(a0 + 0x104) = cnt;
            if (cnt != 0) {
                v0 = 4;
            } else {
                *(s16 *)(a0 + 0x104) = 3;
                v0 = 0x20;
            }
        }
        *(s16 *)(a0 + 0x102) = v0;

        v0 = *(s32 *)(a0 + 0x20);
        sum = *(u16 *)(v0 + 0x12) + *(u16 *)(a0 + 0x106);
        *(u16 *)(v0 + 0x12) = sum;
        if (func_8012BEE8(a0) != 0) {
            *(s32 *)(a0 + 0x1C) = 0x80;
            v0 = rand();
            *(s16 *)(a0 + 0x106) = (v0 & 0x20) - 0x10;
        }
    }
}
