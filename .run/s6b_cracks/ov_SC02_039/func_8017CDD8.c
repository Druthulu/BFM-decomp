extern void func_8017CFCC(void);
extern void func_800167B8(s32 a0);

s32 func_8017CDD8(s32 a0) {
    func_8017CFCC();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}
