extern s32 D_801E2FF0[];
extern void func_80029124(s32, s32);

void func_80189F34(void *a0) {
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801E2FF0[idx], 1);
}
