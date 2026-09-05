void func_800CEF94(void) {
    extern s32 func_80014CAC(s32 a0, s32 a1);
    extern void func_800167B8(s32 a0);
    extern void func_800118AC(void);
    extern u16 D_800B99E8;

    u16 counter = D_800B99E8;
    counter++;
    D_800B99E8 = counter;

    if ((s16)counter < 0x81) {
        s32 result = func_80014CAC(0, 0x800);
        if ((result << 16) == 0) {
            goto end;
        }
    }
    func_800167B8(4);
    func_800118AC();
end:;
}
