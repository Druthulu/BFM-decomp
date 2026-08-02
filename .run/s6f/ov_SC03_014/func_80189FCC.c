extern s32 func_80029178(s32 arg);
extern s32 D_801E2FF0[];

s32 func_80189FCC(void) {
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801E2FF0[i]) == 0) {
            return 0;
        }
    }
    return 1;
}
