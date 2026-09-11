void func_80183B9C(u8 *arg0) {
    extern int func_80178970(void);
    extern void func_80178D18(void);
    extern void func_8017F644(void);
    extern s32 D_801270C8;
    extern s32 D_801EF9F8;
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_801836A8(void*);

    D_801270C8 = 1;
    if (*(u16 *)(arg0 + 0x34) == 0) {
        if (((s32 (*)(u8 *))func_80178970)(arg0) != 0) {
            ((void (*)(s32))func_80178D18)((s32)arg0);
            if (D_801EF9F8 != 0) {
                func_8017F644();
            }
            *(u16 *)(arg0 + 0x34) = 1;
        }
    } else {
        func_8002D4C8(0x13, 0);
        ((s32 (*)(u8 *))func_801836A8)(arg0);
    }
}
