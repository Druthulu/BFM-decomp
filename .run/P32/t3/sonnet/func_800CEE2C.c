extern u16 D_800B99E4;
extern u8 D_800CFABF;
extern u8 D_800CFAC4[];
extern u8 D_800CFAD4[];
extern void (*D_800CFADC[])(void);
extern s32 D_800D1364;
extern u8 D_800AF630[];
extern void func_8001534C(int, void *, int, int, int, int);

void func_800CEE2C(void) {
    u8 *base = D_800AF630;
    u8 *p;
    u8 v1;
    u16 idx;

    p = &D_800CFABF;
    v1 = *(u8 *)&D_800B99E4;
    v1 += 0x30;
    *p = v1;
    func_8001534C(1, p - 0xB, 0x60, 0x64, 0, 0);

    if (D_800D1364) {
        func_8001534C(2, D_800CFAC4, 0x60, 0x70, 0, 0);
    } else {
        func_8001534C(3, D_800CFAD4, 0x60, 0x70, 0, 0);
    }

    idx = *(u16 *)(base + 0xA3B4);
    if (idx < 4) {
        D_800CFADC[idx]();
    }
}
