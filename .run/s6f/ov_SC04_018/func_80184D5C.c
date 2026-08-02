extern s32 func_80029504(void);

s32 func_80184D5C(void) {
    s32 v0 = func_80029504();

    if (v0 < 0xC8) return 5;
    if (v0 < 0x12C) return 0;
    if (v0 < 0x258) return 1;
    if (v0 < 0x2BC) return 2;
    if (v0 < 0x2E4) return 3;
    if (v0 < 0x384) return 4;
    return 6;
}
