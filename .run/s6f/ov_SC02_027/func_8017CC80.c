void func_8017CC80(s32 a0) {
    s32 rand_val = rand();
    func_8017BEBC(a0, rand_val & 0xF);
    if (func_80178970(a0) == 0) {
        return;
    }
    func_80178D18(a0);
    *(s16 *)(a0 + 0x2) = 1;
}
