extern void (*D_80186658[])(void);
extern s32 D_80126B58;
extern s32 func_80013328(s32 a0, s32 a1);

void func_8017FE64(s32 *p) {
    register s32 *q __asm__("$17");

    D_80186658[*(u16 *)((s32)p + 0x2)]();
    q = &D_80126B58;
    if (p[8] != 0) {
        if (func_80013328((s32)p + 4, (s32)(q + 1)) >= 0xA01) {
            *(s32 *)(p[8] + 4) |= 0x80000000;
        } else {
            *(s32 *)(p[8] + 4) &= 0x7FFFFFFF;
        }
    }
}
