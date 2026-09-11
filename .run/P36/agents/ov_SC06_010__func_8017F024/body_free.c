void func_8017F024(s32 a0) {
    s32 *p;
    s32 self;

    D_8018AFBC[*(u16 *)(a0 + 2)]();
    if (*(u16 *)a0 != 0) {
        self = a0;
        p = *(s32 **)(a0 + 0x20);
        p[1] |= 0x80000000;
        func_8012B2CC(self);
    }
}
