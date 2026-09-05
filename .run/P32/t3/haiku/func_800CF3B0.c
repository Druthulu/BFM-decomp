extern s32 func_800149E0(s32);
extern u16 D_800B99E6;

s32 func_800CF3B0(void *a0, void *a1, void *a2) {
    s32 result0 = func_800149E0(0);
    s32 result1 = func_800149E0(1);
    s32 combined = result0 | result1;

    if ((combined & 0x800) != 0) {
        D_800B99E6 = 1;
        return 1;
    }
    return 0;
}
