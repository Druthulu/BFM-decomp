extern void func_8017CF98(void);

s32 func_8017CE7C(s32 a0) {
    func_8017CF98();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}
