extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800167B8(s32 a0);

s32 func_8017CEBC(void *a0) {
    s32 v0;
    s32 v1 = -1;
    v0 = *(s32 *)(a0 + 0x28);
    v0 += -1;
    *(s32 *)(a0 + 0x28) = v0;
    if (v0 == v1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800167B8(4);
        *(u8 *)(a0 + 0x15) = *(u8 *)(a0 + 0x15) + 1;
    }
    return 0;
}
