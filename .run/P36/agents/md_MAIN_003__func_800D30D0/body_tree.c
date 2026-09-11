s32 aF800D30D0(char *arg0) {
    s32 ret;
    s32 s0;

    func_8005C604(D_800CEEB8, arg0);
    s0 = *(volatile s32 *)D_800DB670;
    func_8005C604(D_800CEE58,
        (*(volatile u32 *)D_800DB644 >> 24) & 1,
        (*(volatile u32 *)D_800DB650 >> 24) & 1,
        *D_800DB63C,
        *D_800DB648);
    func_8005C604(D_800CEE80,
        ((u32)~s0 >> 31),
        ((u32)s0 >> 30) & 1,
        ((u32)s0 >> 29) & 1,
        ((u32)s0 >> 28) & 1,
        ((u32)s0 >> 27) & 1,
        ((u32)s0 >> 25) & 1,
        ((u32)s0 >> 23) & 1);
    *D_800DB670 = 0x80000000;
    *D_800DB644 = 0;
    *D_800DB650 = 0;
    __asm__ volatile("" : "=r"(ret) : "0"(0));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    (void)*(volatile s32 *)D_800DB650;
    *D_800DB670 = 0x60000000;
    return ret;
}
