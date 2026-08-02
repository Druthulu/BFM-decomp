extern s32 func_8012C354(void *a0, void *a1);
extern void *D_801E2F88;
extern s32 D_801E2FF0[];
extern s32 func_80029178(s32 arg);
extern void func_8018A224(void);
extern s32 func_801788B8(void *a0, void (*a1)(void));
extern s32 func_8012C658(s32 a0, s16 a1, void *a2);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(void *a0, void *a1);
extern void *D_8018B898;

void func_80189B78(void *a0) {
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354(a0, &D_801E2F88);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)(a0 + 0xDC);
    idx = *(u16 *)(ptr + 0xA);
    arr_elem = D_801E2FF0[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8(a0, (void *)func_8018A224);
        *(s32 *)(a0 + 0xCC) = res2;
    } else {
        val = *(s16 *)(a0 + 0x70);
        val |= 0x4000;
        *(s16 *)(a0 + 0x70) = val;
    }

    res2 = func_8012C658(0x8F, *(s16 *)(a0 + 0x70), a0);
    *(s32 *)(a0 + 0x6C) = res2;

    if (res2 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8012A828(a0, &D_8018B898);
        *(u16 *)(a0 + 0x2) = 1;
    }
}
