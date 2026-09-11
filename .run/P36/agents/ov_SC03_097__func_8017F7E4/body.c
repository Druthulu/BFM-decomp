void func_8017F7E4(void *a0) {

    extern s32 D_80126B58;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern s16 D_8019AE44[];
    extern s16 D_8019AE46[];
    extern s16 D_8019AE48;
    extern s16 D_8019AE4A;
    extern s32 D_801AAAD8;

    s16 *p = (s16 *)&D_80126B58;
    s32 flag;

    flag = 0;
    switch (*(s16 *)((char *)a0 + 0x70)) {
    case 0:
    case 1:
        if (*(s16 *)&D_80126B66 < *(s16 *)((char *)a0 + 0xE) &&
            *(s16 *)((char *)a0 + 0xE) + D_8019AE44[*(s16 *)((char *)a0 + 0x70)] < *(s16 *)&D_80126B66) {
            flag = 1;
        }
        break;
    case 2:
        if (*(s16 *)&D_80126B66 > *(s16 *)((char *)a0 + 0xE) &&
            *(s16 *)&D_80126B66 < *(s16 *)((char *)a0 + 0xE) + D_8019AE48) {
            flag = 1;
        }
        break;
    case 3:
        if (*(s16 *)&D_80126B62 > *(s16 *)((char *)a0 + 0xA) &&
            *(s16 *)&D_80126B62 < *(s16 *)((char *)a0 + 0xA) + D_8019AE4A) {
            flag = 1;
        } else if (p[3] < *(s16 *)((char *)a0 + 0x6) &&
                   *(s16 *)((char *)a0 + 0x6) + D_8019AE46[*(s16 *)((char *)a0 + 0x70)] < p[3]) {
            flag = 1;
        }
        break;
    }

    if (flag != 0 && D_801AAAD8 == 0) {
        func_8017FC1C(0x12F);
        func_8017F994(a0);
    } else {
        if (*(s16 *)((char *)a0 + 0xFE) != 0) {
            s16 t = *(s16 *)((char *)a0 + 0xFE) - 0x10;
            *(s16 *)((char *)a0 + 0xFE) = t;
            if (t < 0) {
                *(s16 *)((char *)a0 + 0xFE) = 0;
            }
        }
    }
    func_8017FBB4(a0);
}
