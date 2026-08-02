extern s32 func_80184DD0(s32 a0);
extern s32 D_80191918[];

void func_80180504(s32 a0) {
    s32 idx = func_80184DD0(a0);
    *(s32 *)(a0 + 0xE4) = D_80191918[idx];
}
