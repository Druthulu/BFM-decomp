extern s16 D_801AA252[];
extern void func_8012DFD4(u8 *a0);

void func_80181148(s32 a0) {
    s32 a1 = a0;
    s32 t = *(s32 *)(a1 + 0x1C) - 1;
    *(s32 *)(a1 + 0x1C) = t;
    if (t == 0) {
        s16 idx = *(s16 *)(a1 + 0xFC);
        s32 val = D_801AA252[idx * 4];

        *(s16 *)(a1 + 0x12) = -*(u16 *)(a1 + 0x12);
        *(s16 *)(a1 + 0x16) = -*(u16 *)(a1 + 0x16);
        *(s16 *)(a1 + 0x1A) = -*(u16 *)(a1 + 0x1A);
        *(s16 *)(a1 + 0x2) = 1;
        *(s32 *)(a1 + 0x1C) = val;
    }
    func_8012DFD4((u8 *)a0);
}
