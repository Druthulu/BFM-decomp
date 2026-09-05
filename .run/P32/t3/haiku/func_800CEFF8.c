extern s32 func_800167F0(s32 a0);
extern u16 D_800B99E6;

void func_800CEFF8(void) {
    if (func_800167F0(0x4) & 0xFFFF) {
        D_800B99E6 = 1;
    }
}
