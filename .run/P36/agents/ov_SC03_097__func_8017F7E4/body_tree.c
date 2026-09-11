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
    s32 cond;

    __asm__ __volatile__("" : "=r"(p) : "0"(p));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)

    flag = 0;
    if (*(s16 *)((char *)a0 + 0x70) == 2) {
        goto CASE2;
    }
    if (*(s16 *)((char *)a0 + 0x70) < 3) {
        goto CASE01;
    }
    if (*(s16 *)((char *)a0 + 0x70) == 3) {
        goto CASE3;
    }
    goto TAIL;

CASE01:
    if (*(s16 *)((char *)a0 + 0x70) < 0) {
        goto TAIL;
    }
    if (*(s16 *)&D_80126B66 < *(s16 *)((char *)a0 + 0xE)) {
        cond = *(s16 *)((char *)a0 + 0xE) + D_8019AE44[*(s16 *)((char *)a0 + 0x70)] < *(s16 *)&D_80126B66;
        goto CHECK;
    }
    goto TAIL;

CASE2:
    if (*(s16 *)&D_80126B66 > *(s16 *)((char *)a0 + 0xE)) {
        cond = *(s16 *)&D_80126B66 < *(s16 *)((char *)a0 + 0xE) + D_8019AE48;
        goto CHECK;
    }
    goto TAIL;

CASE3:
    if (*(s16 *)&D_80126B62 > *(s16 *)((char *)a0 + 0xA)) {
        if (*(s16 *)&D_80126B62 < *(s16 *)((char *)a0 + 0xA) + D_8019AE4A) {
            goto SUCCESS;
        }
    }
    {
        s16 base = p[3];
        s16 posx = *(s16 *)((char *)a0 + 0x6);
        if (base < posx) {
            __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus9)
            cond = posx + D_8019AE46[*(s16 *)((char *)a0 + 0x70)] < base;
            goto CHECK;
        }
    }
    goto TAIL;

CHECK:
    if (!cond) {
        goto TAIL;
    }
SUCCESS:
    flag = 1;

TAIL:
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
